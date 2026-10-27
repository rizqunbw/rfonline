"""Integrity checks for the decoded terrain texture and lightmap assets."""
from pathlib import Path
import json,hashlib,unittest,struct
from PIL import Image
ROOT=Path(__file__).resolve().parents[1]
class TerrainTests(unittest.TestCase):
 def test_texture_pixels_and_sources(self):
  m=json.loads((ROOT/'assets/terrain/manifest.json').read_text())
  self.assertEqual(len(m['textures']),368);self.assertEqual(len(m['lights']),9)
  for source in m['sources']:
   self.assertEqual(hashlib.sha256((ROOT/'assets/source'/source['name']).read_bytes()).hexdigest(),source['sha256'])
  for t in m['textures']+m['lights']:
   im=Image.open(ROOT/t['url']).convert('RGBA');self.assertEqual(list(im.size),t['size']);self.assertEqual(hashlib.sha256(im.tobytes()).hexdigest(),t['pixelsSha256'])
 def test_mesh_positions_and_uvs(self):
  b=(ROOT/'assets/source/Platform01.bsp').read_bytes();h=struct.unpack_from('<170I',b,4);mesh=(ROOT/'assets/terrain/mesh.bin').read_bytes();cursor=0
  for g in struct.iter_unpack('<HHIhh3h3h3ffH',b[h[104]:h[104]+h[105]]):
   if g[3]<0 or g[-1]:continue
   for slot in range(g[2],g[2]+g[1]):
    f=struct.unpack_from('<I',b,h[100]+slot*4)[0];n,start=struct.unpack_from('<HI',b,h[98]+f*6)
    for j in range(1,n-1):
     for corner in [start,start+j,start+j+1]:
      v=struct.unpack_from('<I',b,h[102]+corner*4)[0];out=struct.unpack_from('<11f',mesh,cursor)
      for a,x in enumerate(struct.unpack_from('<3f',b,h[90]+v*12)):self.assertAlmostEqual(out[a],x/100,delta=.00002)
      self.assertEqual(out[7:9],struct.unpack_from('<2f',b,h[94]+corner*8))
      for a,x in enumerate(struct.unpack_from('<2h',b,h[96]+corner*4)):self.assertAlmostEqual(out[9+a],x/32767,delta=.000001)
      cursor+=44
  self.assertEqual(cursor,len(mesh));self.assertEqual(cursor//132,271641)
if __name__=='__main__':unittest.main(verbosity=2)
