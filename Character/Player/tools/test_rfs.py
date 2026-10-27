import hashlib
import json
from pathlib import Path
import struct
import tempfile
import unittest
from extract_rfs import entries,extract
from inspect_msh import inspect

ROOT=Path(__file__).resolve().parents[1]
ARCHIVE=ROOT/'Mesh/BFF00.rfs'


class RFSTests(unittest.TestCase):
    def test_all_extracted_meshes_match_original_bytes_and_parse_completely(self):
        data=ARCHIVE.read_bytes();manifest=json.loads((ROOT/'Mesh/BFF00.manifest.json').read_text())
        self.assertEqual(hashlib.sha256(data).hexdigest(),manifest['sha256'])
        records=entries(data);self.assertEqual(len(records),20)
        previous=4+64*len(records)
        for entry,saved in zip(records,manifest['files']):
            self.assertEqual(entry['offset'],previous)
            payload=data[entry['offset']:entry['offset']+entry['size']]
            self.assertEqual(payload,(ROOT/'Mesh/BFF00'/entry['name']).read_bytes())
            self.assertEqual(hashlib.sha256(payload).hexdigest(),saved['sha256'])
            self.assertEqual(inspect(payload),saved['mesh'])
            previous+=entry['size']
        self.assertEqual(previous,len(data))

    def test_repeat_extraction_preserves_files_and_refuses_conflicting_output(self):
        with tempfile.TemporaryDirectory() as folder:
            output=Path(folder)/'meshes';records=extract(ARCHIVE,output)
            self.assertEqual(extract(ARCHIVE,output),records)
            target=output/records[0]['name'];target.write_bytes(b'user edit')
            with self.assertRaises(ValueError):extract(ARCHIVE,output)
            self.assertEqual(target.read_bytes(),b'user edit')

    def test_malformed_archive_ranges_names_and_duplicates_are_rejected(self):
        data=ARCHIVE.read_bytes()
        corruptions=[]
        b=bytearray(data);b[4:60]=b'../escape.msh\0'.ljust(56,b'\0');corruptions.append(b)
        b=bytearray(data);b[68:124]=b[4:60];corruptions.append(b)
        b=bytearray(data);struct.pack_into('<I',b,60,0);corruptions.append(b)
        b=bytearray(data);struct.pack_into('<I',b,64,len(data));corruptions.append(b)
        b=bytearray(data);struct.pack_into('<I',b,124,1284);corruptions.append(b)
        corruptions.append(data[:100])
        for data in corruptions:
            with self.assertRaises(ValueError):entries(data)

    def test_truncated_mesh_and_bad_triangle_index_are_rejected(self):
        mesh=next((ROOT/'Mesh/BFF00').glob('*.msh')).read_bytes()
        with self.assertRaises(ValueError):inspect(mesh[:-1])
        b=bytearray(mesh);vertices=struct.unpack_from('<H',b,2+392)[0]
        struct.pack_into('<I',b,2+693+vertices*28,vertices)
        with self.assertRaises(ValueError):inspect(b)


if __name__=='__main__':unittest.main(verbosity=2)
