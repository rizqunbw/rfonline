"""Validate source integrity, decoded art and malformed SPR rejection."""
import hashlib
import json
import struct
import unittest
from PIL import Image
from convert_spr import ROOT, OUT, read_spr, decode, ARGB8888, RGB565

class SprTests(unittest.TestCase):
    def test_all_uploaded_sources_and_pixels(self):
        count=0
        for folder in ['common','en-gb']:
            catalogs={r['source']:r for r in json.loads((ROOT/folder/'catalog.json').read_text())}
            for source in json.loads((ROOT/folder/'uploads.json').read_text()):
                data=(ROOT/folder/source['name']).read_bytes()
                self.assertEqual(len(data),source['bytes'])
                self.assertEqual(hashlib.sha256(data).hexdigest(),source['sha256'])
                records=read_spr(data)
                self.assertEqual(len(records),len(catalogs[source['name']]['frames']))
                for actual,expected in zip(records,catalogs[source['name']]['frames']):
                    self.assertEqual(hashlib.sha256(decode(data,actual).tobytes()).hexdigest(),expected['pixelsSha256'])
                    count+=1
        self.assertEqual(count,1114)

    def test_exported_hud_pixels_match_original_sprites(self):
        for role,info in json.loads((OUT/'manifest.json').read_text()).items():
            data=(ROOT/info.get('folder','common')/info['source']).read_bytes()
            record=next(r for r in read_spr(data) if (r['group'],r['frame'])==(info['group'],info['frame']))
            image=decode(data,record)
            if 'crop' in info:image=image.crop(info['crop'])
            actual=Image.open(OUT/(role+'.png')).convert('RGBA')
            self.assertEqual(image.size,actual.size)
            self.assertEqual(image.tobytes(),actual.tobytes())

    def test_channel_order_alpha_and_padding(self):
        data=struct.pack('<fII6I',1.1,1,1,ARGB8888,1,1,2,1,8)+bytes([10,20,30,40,1,2,3,4])
        image=decode(data,read_spr(data)[0])
        self.assertEqual(image.size,(1,1));self.assertEqual(image.getpixel((0,0)),(30,20,10,40))
        data=struct.pack('<fII6I',1.1,1,1,RGB565,1,1,1,1,2)+struct.pack('<H',0xf800)
        self.assertEqual(decode(data,read_spr(data)[0]).getpixel((0,0)),(255,0,0,255))

    def test_reject_truncated_unknown_and_trailing_data(self):
        data=struct.pack('<fII6I',1.1,1,1,ARGB8888,1,1,1,1,4)+bytes(4)
        for bad in [data[:5],data[:-1],data+b'x',data[:12]+struct.pack('<I',999)+data[16:]]:
            with self.assertRaises(ValueError):read_spr(bad)

if __name__=='__main__':unittest.main()
