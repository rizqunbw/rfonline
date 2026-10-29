import json
import struct
import unittest
from inspect_client import PE32, ROOT, inspect


class ClientInspectionTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.data = (ROOT / 'rf_online.bin').read_bytes()
        cls.pe = PE32(cls.data)

    def test_inventory_matches_source_and_committed_report(self):
        report = inspect(self.data)
        self.assertEqual(report, json.loads((ROOT / 'System/analysis/rf-online.json').read_text()))
        self.assertEqual(len(report['imports']), 24)
        imported = {s['name'] for dll in report['imports'] for s in dll['symbols']}
        self.assertIn('GetPrivateProfileIntA', imported)
        self.assertEqual(len(report['exports']), 199)

    def test_truncated_and_invalid_files_fail_without_unbounded_reads(self):
        for data in [b'', b'MZ', b'x' * 1024, self.data[:512], self.data[:8000000]]:
            with self.assertRaises(ValueError):
                inspect(data)
        with self.assertRaises(ValueError):
            self.pe.offset(0xffffffff)

    def test_verified_integer_call_operands_resolve_to_documented_keys(self):
        verified = json.loads((ROOT / 'System/analysis/verified-settings.json').read_text())
        self.assertEqual(verified['binary_sha256'], inspect(self.data)['sha256'])
        for row in verified['settings'][:4]:
            offset = self.pe.offset(int(row['call_va'], 16) - self.pe.image_base)
            code = self.data[offset-12:offset+6]
            self.assertEqual(code[0], 0x6a)  # push imm8 fallback
            self.assertEqual(code[1], row['fallback'])
            self.assertEqual(code[2], 0x68)  # push key address
            self.assertEqual(code[7], 0x68)  # push section address
            self.assertEqual(code[12:], bytes.fromhex('ff1514f2af00'))
            for start, field in [(3, 'key'), (8, 'section')]:
                va = struct.unpack_from('<I', code, start)[0]
                self.assertEqual(self.pe.string(va-self.pe.image_base), row[field])


if __name__ == '__main__':
    unittest.main()
