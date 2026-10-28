import hashlib
import json
from pathlib import Path
import struct
import unittest
from catalog_ani import catalog,ROOT
from inspect_ani import inspect


class AnimationTests(unittest.TestCase):
    def test_all_uploads_match_recorded_bytes(self):
        uploads=json.loads((ROOT/'uploads.json').read_text())
        self.assertEqual(len(uploads),57)
        for entry in uploads:
            with self.subTest(file=entry['name']):
                data=(ROOT/entry['name']).read_bytes()
                self.assertEqual(len(data),entry['bytes'])
                self.assertEqual(hashlib.sha256(data).hexdigest(),entry['sha256'])

    def test_all_archive_clips_and_catalog_are_reproducible(self):
        actual=catalog();saved=json.loads((ROOT/'catalog.json').read_text())
        self.assertEqual(actual,saved)
        self.assertEqual(actual['archiveCount'],52)
        self.assertEqual(actual['clipCount'],4102)
        self.assertEqual(actual['uniqueClipNames'],3844)
        self.assertEqual(actual['parseFailures'],[])
        self.assertEqual(actual['registry']['missing'],[])
        self.assertEqual(actual['registry']['unlisted'],[])
        for temporary in actual['temporaryFiles']:
            self.assertTrue(temporary['isZip'])
            self.assertTrue(all(m['identicalToLooseFile'] for m in temporary['members']))
        for loose in actual['looseAnimations']:
            self.assertTrue(loose['archiveCopies'])
            self.assertTrue(all(c['identical'] for c in loose['archiveCopies']))

    def test_key_values_order_and_raw_time_are_preserved(self):
        # One object with a quaternion and a position key, no scale/scalar keys.
        data=struct.pack('<H',1)+b'Bip01'.ljust(100,b'\0')+struct.pack('<HH',1,160)+bytes(36)
        data+=struct.pack('<H4fI',1,0,0,0,1,160)
        data+=struct.pack('<H3fI',1,1,2,3,320)+struct.pack('<HH',0,0)
        result=inspect(data,True)
        self.assertEqual(result['endTick'],320)
        tracks=result['objects'][0]['tracks']
        self.assertEqual(tracks['rotation']['values'],[{'tick':160,'value':[0,0,0,1]}])
        self.assertEqual(tracks['position']['values'],[{'tick':320,'value':[1,2,3]}])
        with self.assertRaises(ValueError):inspect(data[:-1])
        with self.assertRaises(ValueError):inspect(data+b'\0')
        damaged=bytearray(data);struct.pack_into('<f',damaged,144,float('inf'))
        with self.assertRaises(ValueError):inspect(damaged)


if __name__=='__main__':unittest.main(verbosity=2)
