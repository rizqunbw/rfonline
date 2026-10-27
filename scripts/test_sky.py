"""Validate exported skies against their original uploaded binary assets."""
from pathlib import Path
import hashlib
import io
import json
import struct
import unittest
from PIL import Image, ImageChops

ROOT = Path(__file__).resolve().parents[1]
MANIFEST = json.loads((ROOT/'assets/sky/manifest.json').read_text())


class SkyIntegrity(unittest.TestCase):
    def test_source_checksums(self):
        for sky in MANIFEST['skies']:
            for source in sky['sources']:
                with self.subTest(source=source['name']):
                    data = (ROOT/'assets/source'/source['name']).read_bytes()
                    self.assertEqual(hashlib.sha256(data).hexdigest(),source['sha256'])

    def test_all_22_texture_images_match_original_dds_pixels(self):
        total = 0
        for sky in MANIFEST['skies']:
            data = (ROOT/'assets/source'/f"{sky['name']}.r3t").read_bytes()
            count = struct.unpack_from('<I', data,4)[0]
            self.assertEqual(count,len(sky['textures']))
            cursor = 8 + 128*count
            for texture in sky['textures']:
                with self.subTest(texture=texture['url']):
                    size = struct.unpack_from('<I',data,cursor)[0]
                    dds = data[cursor+4:cursor+4+size]
                    original = Image.open(io.BytesIO(dds)).convert('RGBA')
                    png = Image.open(ROOT/texture['url']).convert('RGBA')
                    self.assertEqual(original.size,png.size)
                    self.assertEqual(original.tobytes(),png.tobytes())
                    self.assertEqual(hashlib.sha256(dds).hexdigest(),texture['ddsSha256'])
                    cursor += 4 + size
                    total += 1
            self.assertEqual(cursor,len(data))
        self.assertEqual(total,22)

    def test_mesh_positions_uvs_colors_and_group_ranges_match_r3e(self):
        for sky in MANIFEST['skies']:
            data = (ROOT/'assets/source'/f"{sky['name']}.r3e").read_bytes()
            mesh = (ROOT/sky['mesh']).read_bytes()
            h = struct.unpack_from('<20I',data,8)
            x,y,z,scale,uv_min,uv_max = struct.unpack_from('<6f',data,h[0]+14)
            cursor,draw_index,skipped = 0,0,0
            for at in range(h[14],h[14]+h[15],22):
                count,first,material,obj = struct.unpack_from('<HIhH',data,at)
                if obj or material < 0:
                    skipped += 1
                    continue
                draw = sky['draws'][draw_index]
                self.assertEqual(draw['first'],cursor//36)
                self.assertEqual(draw['material'],material)
                for face_slot in range(first,first+count):
                    face_id = struct.unpack_from('<H',data,h[10]+face_slot*2)[0]
                    corners,start = struct.unpack_from('<HI',data,h[8]+face_id*6)
                    for j in range(1,corners-1):
                        for corner in (start,start+j,start+j+1):
                            vertex = struct.unpack_from('<H',data,h[12]+corner*2)[0]
                            actual = struct.unpack_from('<9f',mesh,cursor)
                            raw = struct.unpack_from('<3h',data,h[2]+vertex*6)
                            for k,center in enumerate((x,y,z)):
                                self.assertAlmostEqual(actual[k],raw[k]/32767*scale+center,delta=.00001)
                            uv = struct.unpack_from('<2h',data,h[6]+corner*4)
                            for k in range(2):
                                self.assertAlmostEqual(actual[3+k],uv[k]/32767*(uv_max-uv_min)/2+(uv_min+uv_max)/2,delta=.000001)
                            b,g,r,a = data[h[4]+vertex*4:h[4]+vertex*4+4]
                            for k,v in enumerate((r,g,b,a)):
                                self.assertAlmostEqual(actual[5+k],v/255,delta=.000001)
                            cursor += 36
                self.assertEqual(draw['first']+draw['count'],cursor//36)
                draw_index += 1
            self.assertEqual(cursor,len(mesh))
            self.assertEqual(len(mesh)//108,sky['triangles'])
            self.assertEqual(skipped,sky['skippedAnimatedGroups'])


if __name__ == '__main__':
    unittest.main(verbosity=2)
