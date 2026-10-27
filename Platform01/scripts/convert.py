"""Decode the uploaded BSP v39 static geometry; keep original source files.
Format layout adapted using the MIT-licensed cbb-rf-online-addon reference.
Only the inspected sample is supported; see README and third-party notice.
"""
from pathlib import Path
import hashlib
import json
import math
import re
import struct

ROOT = Path(__file__).resolve().parents[1]
source = ROOT / 'assets/source'
data = (source / 'Platform01.bsp').read_bytes()
assert len(data) == 19765451, 'Only the inspected Platform01 sample is supported'
assert struct.unpack_from('<I', data)[0] == 39
header = struct.unpack_from("<170I", data, 4)
start, size = header[90:92]
assert size % 12 == 0
count = size // 12
color_start, color_size = header[92:94]
assert color_size == count * 4
assert data[color_start:color_start + 4] == b'\xff' * 4
positions = list(struct.iter_unpack('<3f', data[start:color_start]))
assert all(math.isfinite(v) and abs(v) < 100000 for p in positions for v in p)
assert all(data[color_start + i * 4 + 3] == 255 for i in range(count)), 'Unexpected color block'
bounds = [[min(p[a] for p in positions) / 100 for a in range(3)],
          [max(p[a] for p in positions) / 100 for a in range(3)]]
out = bytearray()
for i, p in enumerate(positions):
    b, g, r, a = data[color_start + i * 4:color_start + i * 4 + 4]
    out.extend(struct.pack('<6f', *(v / 100 for v in p), r / 255, g / 255, b / 255))
(ROOT / 'assets/platform.points').write_bytes(out)
names = re.findall(rb'[A-Za-z][A-Za-z0-9_]{3,}', (source / 'Platform01.r3m').read_bytes())
manifest = {
    'name': 'Platform01', 'vertices': count, 'bounds': bounds,
    'representation': 'experimental point cloud; topology and UV mapping unverified',
    'materials': sorted(set(n.decode('ascii') for n in names)),
    'sources': [{'name': p.name, 'bytes': p.stat().st_size,
                 'sha256': hashlib.sha256(p.read_bytes()).hexdigest()}
                for p in sorted(source.iterdir())],
}
(ROOT / 'assets/manifest.json').write_text(json.dumps(manifest, indent=2))
print(f'Extracted {count:,} points; bounds: {bounds}')

# BSP v39 layout reference: Cardboard-box-a/cbb-rf-online-addon (MIT).
# See THIRD_PARTY_LICENSE.txt. Material groups reference face IDs, which
# reference polygon records, which in turn reference vertex IDs.
def block(index):
    offset, length = header[index:index + 2]
    assert offset + length <= len(data)
    return data[offset:offset + length]
faces = list(struct.iter_unpack('<HI', block(98)))
face_ids = [v[0] for v in struct.iter_unpack('<I', block(100))]
vertex_ids = [v[0] for v in struct.iter_unpack('<I', block(102))]
groups = list(struct.iter_unpack('<HHIhh3h3h3ffH', block(104)))
r3m = (source / 'Platform01.r3m').read_bytes()
material_count = struct.unpack_from('<I', r3m, 4)[0]
materials = []
offset = 8
for _ in range(material_count):
    layers = struct.unpack_from('<I', r3m, offset)[0]
    materials.append(r3m[offset + 16:offset + 144].split(b'\0')[0].decode('euc-kr'))
    offset += 144 + 46 * layers
assert offset == len(r3m)
mesh = bytearray()
skipped_groups = 0
rendered_faces = []
for group in groups:
    _, amount, first, material_id, *_ = group
    if material_id < 0 or group[-1] != 0:
        skipped_groups += 1
        continue
    assert 0 <= material_id < len(materials)
    name = materials[material_id].lower()
    base = (.78, .84, .85) if 'snow' in name else ((.36, .43, .47) if 'cliff' in name else (.49, .61, .62))
    assert first + amount <= len(face_ids)
    for face_id in face_ids[first:first + amount]:
        assert face_id < len(faces)
        n, first_vertex = faces[face_id]
        assert n in (3, 4) and first_vertex + n <= len(vertex_ids)
        ids = vertex_ids[first_vertex:first_vertex + n]
        assert all(i < count for i in ids)
        rendered_faces.append(face_id)
        for j in range(1, n - 1):
            triangle = [ids[0], ids[j], ids[j + 1]]
            a, b, c = [positions[i] for i in triangle]
            ab = [b[k] - a[k] for k in range(3)]
            ac = [c[k] - a[k] for k in range(3)]
            normal = [ab[1]*ac[2]-ab[2]*ac[1], ab[2]*ac[0]-ab[0]*ac[2], ab[0]*ac[1]-ab[1]*ac[0]]
            length = math.sqrt(sum(v*v for v in normal))
            shade = .45 + .55 * abs(sum(normal[k]*(-.4,.8,.4)[k] for k in range(3))) / max(length, 1e-8)
            for i in triangle:
                bgra = data[color_start + i*4:color_start + i*4+4]
                rgb = [base[k]*shade*(.5+.5*bgra[2-k]/255) for k in range(3)]
                mesh.extend(struct.pack('<6f', *(v/100 for v in positions[i]), *rgb))
(ROOT / 'assets/platform.mesh').write_bytes(mesh)
manifest.update({'representation': 'static BSP mesh with substitute materials', 'materials': materials,
    'triangles': len(mesh)//72, 'renderedFaces': len(rendered_faces), 'skippedGroups': skipped_groups,
    'decoderReference': 'https://github.com/Cardboard-box-a/cbb-rf-online-addon/tree/02dfdc4f62fac8f266cf4c0ff85c57172b48bcbf',
    'limitations': ['Animated and invisible groups omitted', 'R3T textures/lightmaps missing', 'EBP/CAM not interpreted']})
(ROOT / 'assets/manifest.json').write_text(json.dumps(manifest, indent=2))
print(f'Decoded {len(mesh)//72:,} triangles; skipped {skipped_groups} animated/invisible groups')
