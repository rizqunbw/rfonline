"""Decode uploaded RF R3E/R3M/R3T sky assets. Pillow is needed for DDS.

Format layout: cbb-rf-online-addon (MIT), see THIRD_PARTY_LICENSE.txt.
MTF files are preserved as source metadata. Object tracks and animated objects
are not evaluated. Material UV scrolling is exported as metadata only.
"""
from pathlib import Path
import hashlib
import io
import json
import math
import struct
from PIL import Image

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / 'assets/source'
OUTPUT = ROOT / 'assets/sky'
OUTPUT.mkdir(exist_ok=True)


def decode(stem):
    output = OUTPUT / stem
    output.mkdir(exist_ok=True)
    data = (SOURCE / f'{stem}.r3t').read_bytes()
    version, count = struct.unpack_from('<fI', data)
    assert abs(version - 1.2) < .001
    names = [data[8 + i*128:8 + (i+1)*128].split(b'\0')[0].decode('euc-kr') for i in range(count)]
    cursor = 8 + count * 128
    textures = []
    for i, name in enumerate(names, 1):
        size = struct.unpack_from('<I', data, cursor)[0]
        cursor += 4
        assert size >= 128 and cursor + size <= len(data)
        dds = data[cursor:cursor + size]
        assert dds[:4] == b'DDS ', 'Unsupported packed DDS header'
        image = Image.open(io.BytesIO(dds)).convert('RGBA')
        image.save(output / f'{i}.png')
        textures.append({'id': i, 'name': name.replace('\\', '/').split('/')[-1],
                         'url': f'assets/sky/{stem}/{i}.png', 'width': image.width, 'height': image.height,
                         'ddsSha256': hashlib.sha256(dds).hexdigest()})
        cursor += size
    assert cursor == len(data)

    data = (SOURCE / f'{stem}.r3m').read_bytes()
    version, count = struct.unpack_from('<fI', data)
    assert abs(version - 1.1) < .001
    cursor, materials = 8, []
    for _ in range(count):
        layers, flags = struct.unpack_from('<II', data, cursor)
        name = data[cursor+16:cursor+144].split(b'\0')[0].decode('euc-kr')
        cursor += 144
        material = {'name': name, 'flags': flags, 'layers': []}
        for _ in range(layers):
            layer = struct.unpack_from('<hiIIIhhhhhhhhhhHhhh', data, cursor)
            assert 1 <= layer[1] <= len(textures)
            material['layers'].append({'texture': layer[1]-1, 'alphaType': layer[2],
                'tint': [((layer[3] >> shift) & 255)/255 for shift in (16, 8, 0, 24)],
                'flags': layer[4], 'scroll': [layer[7], layer[8]]})
            cursor += 46
        materials.append(material)
    assert cursor == len(data)

    data = (SOURCE / f'{stem}.r3e').read_bytes()
    assert struct.unpack_from('<I', data)[0] == 113
    header = struct.unpack_from('<20I', data, 8)
    def records(index, fmt):
        offset, size = header[index:index+2]
        assert offset + size <= len(data)
        return list(struct.iter_unpack(fmt, data[offset:offset+size]))
    compression = struct.unpack_from('<H', data, header[0])[0]
    x, y, z, scale, uv_min, uv_max = struct.unpack_from('<6f', data, header[0]+14)
    assert compression == 0x4000, 'Only the inspected short-coordinate skies are supported'
    vertices = [[v[k]/32767*scale + (x,y,z)[k] for k in range(3)] for v in records(2, '<3h')]
    colors = records(4, '<4B')
    assert len(vertices) == len(colors)
    uv_scale = (uv_max-uv_min)/2
    uvs = [[v/32767*uv_scale+uv_min+uv_scale for v in pair] for pair in records(6, '<2h')]
    faces = records(8, '<HI')
    face_ids = [f[0] for f in records(10, '<H')]
    vertex_ids = [v[0] for v in records(12, '<H')]
    groups = records(14, '<HIhH3h3h')
    mesh, draws, skipped = bytearray(), [], 0
    for amount, first, material_id, object_id, *_ in groups:
        if object_id or material_id < 0:
            skipped += 1
            continue
        assert material_id < len(materials) and first+amount <= len(face_ids)
        start = len(mesh)//36
        for face_id in face_ids[first:first+amount]:
            assert face_id < len(faces)
            n, corner_start = faces[face_id]
            assert n >= 3 and corner_start+n <= len(vertex_ids)
            for j in range(1,n-1):
                for corner in (corner_start, corner_start+j, corner_start+j+1):
                    vertex = vertex_ids[corner]
                    assert vertex < len(vertices) and corner < len(uvs)
                    b,g,r,a = colors[vertex]
                    values = [*vertices[vertex], *uvs[corner], r/255,g/255,b/255,a/255]
                    assert all(math.isfinite(v) for v in values)
                    mesh.extend(struct.pack('<9f', *values))
        draws.append({'first':start,'count':len(mesh)//36-start,'material':material_id})
    (output/'mesh.bin').write_bytes(mesh)
    result = {'name':stem,'mesh':f'assets/sky/{stem}/mesh.bin','triangles':len(mesh)//108,
        'textures':textures,'materials':materials,'draws':draws,'skippedAnimatedGroups':skipped,
        'sources':[{'name':f'{stem}.{ext}', 'sha256':hashlib.sha256((SOURCE/f'{stem}.{ext}').read_bytes()).hexdigest()}
                   for ext in ('r3e','r3m','r3t','mtf')]}
    print(f'{stem}: {len(mesh)//108} static triangles, {len(textures)} DDS textures; {skipped} animated groups skipped')
    return result


if __name__ == '__main__':
    manifest = {'skies':[decode('Platform01Sky'),decode('Platform01sky2')],
        'limitations':['Object tracks/animated groups omitted','UV scrolling and secondary material layers not simulated',
                       'Sky is centered on the camera; original game sky-selection rules unknown']}
    (OUTPUT/'manifest.json').write_text(json.dumps(manifest,indent=2))
