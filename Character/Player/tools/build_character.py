"""Build the supplied Bellato female 171 armor for the web viewer.

Format reference: cbb-rf-online-addon (MIT, ../THIRD_PARTY_LICENSE.txt).
Requires Python 3, numpy, scipy, Pillow. Run from any working directory.
Original assets are never modified. Only the supported standard MSH layout
and named skeleton tracks are exported; extra object/effect tracks are reported.
"""
from pathlib import Path
import hashlib
import io
import json
import sys
import numpy as np
from scipy.spatial.transform import Rotation
from PIL import Image
from extract_rfs import entries
from inspect_msh import Reader, inspect as inspect_mesh
from inspect_ani import inspect as inspect_animation
from player_resources import PlayerResources

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT.parents[1] / 'Map/Platform01/assets/character'
# Source Max coordinates -> right-handed Y-up. Preserve native unit size here.
C = np.array([[-1, 0, 0, 0], [0, 0, 1, 0], [0, 1, 0, 0], [0, 0, 0, 1]], dtype=float)
KEY = bytes.fromhex('2e804d762ef8d1f0bd3f8681582c3f3f2e2e676f3f403f783c3ff1c0a5f63b9fc1203fd7c8c1e98586bdef563fa1fb2e8786614c213b4eb47857ae973f2e4a2e3f4c2e44cdc55fe8e9ecebbdbebbf76c2ef2e42e3f3f979f9db321b97665543fe6f6c6f079dbe2b24b2e2eebd3d3caabeac7ed9cc7d9d06548b4fa352e2e6a9b')


def matrix(r):
    m = np.array(r.unpack('16f')).reshape(4, 4).T
    if not np.isfinite(m).all() or not np.allclose(m[3], [0, 0, 0, 1], atol=1e-5):
        raise ValueError('Invalid affine matrix')
    return m


def flat(m):
    return m.T.flatten().tolist()


def read_bones(data):
    r = Reader(data)
    count, = r.unpack('H')
    if not 0 < count <= len(data) // 693:
        raise ValueError('Invalid skeleton bone count')
    bones = []
    for _ in range(count):
        name, parent = r.name(), r.name()
        world, local, _inverse_parent = matrix(r), matrix(r), matrix(r)
        nv, nf, nw = r.unpack('3H')
        r.take(228)
        flags = r.unpack('16I')
        r.take(3 + nv * 28)
        if nf or flags[4]:
            r.take(4)
        for f in range(nf):
            r.take(84)
            if flags[4] or f != nf - 1:
                r.take(4)
        if nw:
            r.take(100 + 40 * nw)
        bones.append(dict(name=name, parentName=parent, world=world, local=local))
    if r.offset != len(data):
        raise ValueError('Unconsumed skeleton bytes')
    names = {b['name']: i for i, b in enumerate(bones)}
    if len(names) != count:
        raise ValueError('Duplicate bone name')
    for i, b in enumerate(bones):
        b['parent'] = -1 if b['parentName'] == 'NULL' else names[b['parentName']]
        ancestry = {i}
        p = b['parent']
        while p != -1:
            if p in ancestry:
                raise ValueError('Skeleton cycle')
            ancestry.add(p)
            p = -1 if bones[p]['parentName'] == 'NULL' else names[bones[p]['parentName']]
        parent_world = np.eye(4) if b['parent'] < 0 else bones[b['parent']]['world']
        if not np.allclose(parent_world @ b['local'], b['world'], atol=2e-4):
            raise ValueError(f'Inconsistent bind transform: {b["name"]}')
        # This converter deliberately rejects mirrored/nonrigid bones.
        if not np.allclose(b['world'][:3, :3].T @ b['world'][:3, :3], np.eye(3), atol=2e-4) or np.linalg.det(b['world'][:3, :3]) < 0:
            raise ValueError(f'Unsupported skeleton scale: {b["name"]}')
    return bones


def read_mesh(data, names):
    inspect_mesh(data)  # Validate finite fields, counts, face indices and weights.
    r = Reader(data)
    count, = r.unpack('H')
    result = []
    for _ in range(count):
        name, parent = r.name(), r.name()
        world = C @ matrix(r)
        r.take(128)
        nv, nf, nw = r.unpack('3H')
        texture, effect = r.name(), r.name()
        r.take(44)
        weight_type, = r.unpack('I')
        assert weight_type == 1
        r.take(47)
        positions = np.array([r.unpack('7f')[:3] for _ in range(nv)])
        faces = []
        for _ in range(nf):
            ids, attributes = r.unpack('3I'), r.unpack('18f')
            r.take(4)
            faces.append((ids, attributes))
        nb, = r.unpack('I')
        mesh_bones = [r.name() for _ in range(nb)]
        weights = {}
        for _ in range(nw):
            vertex, amount, *indices = r.unpack('II4i')
            values = r.unpack('4f')
            active = [(names[mesh_bones[i]], w) for i, w in zip(indices, values) if i != -1]
            total = sum(w for _, w in active)
            if not np.isclose(total, 1, atol=.002):
                raise ValueError(f'Weights do not sum to one: {name}/{vertex}')
            weights[vertex] = active
        if not nf:
            continue
        if not nw and parent not in names:
            raise ValueError(f'Rigid mesh has no matching parent: {name}/{parent}')
        positions = (world @ np.column_stack([positions, np.ones(nv)]).T).T[:, :3]
        normal_matrix = np.linalg.inv(world[:3, :3]).T
        out = dict(name=name, texture=Path(texture.replace('\\', '/')).stem.lower() + '.png',
                   positions=[], normals=[], uvs=[], joints=[], weights=[])
        for ids, attributes in faces:
            for corner, vi in enumerate(ids):
                out['positions'].extend(positions[vi].tolist())
                normal = normal_matrix @ np.array(attributes[corner*3:corner*3+3])
                normal /= max(np.linalg.norm(normal), 1e-9)
                out['normals'].extend(normal.tolist())
                out['uvs'].extend(attributes[9+corner*3:11+corner*3])
                active = weights[vi] if nw else [(names[parent], 1)]
                out['joints'].extend([j for j, w in active] + [0]*(4-len(active)))
                total = sum(w for j, w in active)
                out['weights'].extend([w/total for j, w in active] + [0]*(4-len(active)))
        result.append(out)
    return result


def build():
    OUT.mkdir(parents=True, exist_ok=True)
    sources = []
    def source(path):
        data = path.read_bytes()
        if not any(s['path'] == str(path.relative_to(ROOT)) for s in sources):
            sources.append(dict(path=str(path.relative_to(ROOT)), bytes=len(data), sha256=hashlib.sha256(data).hexdigest()))
        return data
    registry = PlayerResources()
    source(ROOT / 'Player.xlsx')
    source(ROOT / 'resources.json')
    # Resource IDs are selected equipment slots from the uploaded workbook.
    # Actual archive payloads and the skeleton are resolved through ID/BoneID.
    resource_ids = ['001004AB', '001000AB', '001003AB', '001005AB', '001002AB']
    selected = [registry.mesh(resource_id) for resource_id in resource_ids]
    bone_paths = {r['bone'] for r in selected}
    if len(bone_paths) != 1:
        raise ValueError('Selected equipment uses incompatible skeletons')
    bones = read_bones(source(selected[0]['bone']))
    names = {b['name']: i for i, b in enumerate(bones)}
    meshes = []
    for resource in selected:
        source(resource['archive'])
        meshes.extend(read_mesh(resource['payload'], names))
    texture_data = source(ROOT / 'Tex/BFF00.RFS')
    textures = []
    for e in entries(texture_data):
        blob = texture_data[e['offset']:e['offset']+e['size']]
        if blob[:4] != b'DDS ':
            if len(blob) < 128:
                raise ValueError('Truncated RFT')
            blob = bytes(x ^ y for x, y in zip(blob[:128], KEY)) + blob[128:]
        if blob[:4] != b'DDS ':
            raise ValueError('Invalid decoded DDS')
        image = Image.open(io.BytesIO(blob)).convert('RGBA')
        filename = Path(e['name']).stem.lower() + '.png'
        image.save(OUT / filename)
        textures.append(dict(file=filename, original=e['name'], size=list(image.size), pixelsSha256=hashlib.sha256(image.tobytes()).hexdigest()))
    if set(m['texture'] for m in meshes) != set(t['file'] for t in textures):
        raise ValueError('Mesh/texture mismatch')
    clips = []
    for archive, labels in [('BFETA', [('idle', 'PEACE_STAND'), ('walk', 'PEACE_WALK'), ('run', 'PEACE_RUN')]),
                            ('BFCOA', [('combat', 'COMBAT_STAND')])]:
        data = source(ROOT / f'Ani/{archive}.RFS')
        table = {e['name']: e for e in entries(data)}
        for label, motion in labels:
            filename = f'BELFEMALE_{motion}_NONE_NONE_01_00.ANI'
            e = table[filename]
            ani = inspect_animation(data[e['offset']:e['offset']+e['size']], True)
            tracks = []
            for o in ani['objects']:
                if o['name'] not in names:
                    continue
                for channel in ['rotation', 'position', 'scale']:
                    track = o['tracks'][channel]
                    if not track['keys']:
                        continue
                    if not track['nondecreasing']:
                        raise ValueError('Nonmonotonic animation keys')
                    # Duplicate timestamps retain the last value.
                    keys = {v['tick']: v['value'] for v in track['values']}
                    values, times = [], []
                    previous = None
                    for tick, value in keys.items():
                        if channel == 'rotation':
                            q = np.array(value)
                            if not np.isclose(np.linalg.norm(q), 1, atol=.002):
                                raise ValueError('Non-unit animation quaternion')
                            # RF ANI quaternion stores inverse rotation.
                            rotation = Rotation.from_quat(q).inv().as_matrix()
                            value = Rotation.from_matrix(C[:3, :3] @ rotation @ C[:3, :3].T).as_quat()
                            if previous is not None and np.dot(value, previous) < 0:
                                value *= -1
                            previous = value
                        elif channel == 'position':
                            value = C[:3, :3] @ value
                        else:
                            value = np.array(value)[[0, 2, 1]]
                        times.append(tick / 4800)  # Explicit preview timing: 160 ticks/frame at 30 FPS.
                        values.extend(list(value))
                    tracks.append(dict(bone=names[o['name']], channel=channel, times=times, values=values))
            clips.append(dict(name=label, source=filename, archive=archive+'.RFS', duration=ani['endTick']/4800,
                              tracks=tracks, omittedObjects=[o['name'] for o in ani['objects'] if o['name'] not in names]))
    points = np.concatenate([np.array(m['positions']).reshape(-1, 3) for m in meshes])
    model = dict(version=1, name='Bellato Female · Armor 171',
                 meshResourceIds=resource_ids, boneResourceId=selected[0]['record']['boneResourceId'],
                 bones=[dict(name=b['name'], parent=b['parent'], local=flat(C @ b['local'] @ C.T), inverseBind=flat(np.linalg.inv(C @ b['world'] @ C.T))) for b in bones],
                 meshes=meshes, textures=textures, clips=clips,
                 bounds=[points.min(axis=0).tolist(), points.max(axis=0).tolist()],
                 previewTicksPerSecond=4800,
                 limitations=['Face/hair mesh not supplied', 'Only armor set 171 has matching supplied textures',
                              'Scalar and non-skeleton ANI channels are not rendered', 'Preview assumes 30 FPS (160 ticks/frame)'], sources=sources)
    (OUT / 'bellato-171.json').write_text(json.dumps(model, separators=(',', ':'), allow_nan=False)+'\n')
    summary = {k: v for k, v in model.items() if k not in ['meshes', 'bones', 'clips']}
    summary.update(bones=len(bones), meshObjects=len(meshes), triangles=sum(len(m['positions'])//9 for m in meshes),
                   clips=[{k: v for k, v in c.items() if k != 'tracks'} for c in clips])
    (OUT / 'manifest.json').write_text(json.dumps(summary, indent=2)+'\n')
    print(json.dumps({k: summary[k] for k in ['bones', 'meshObjects', 'triangles', 'bounds']}))
    return model


if __name__ == '__main__':
    build()
