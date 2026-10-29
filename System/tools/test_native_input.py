import unittest
from inspect_client import ROOT
from export_native_input import extract,audit_tables


class NativeInputTests(unittest.TestCase):
    def test_binary_sections_and_uploaded_files_are_cross_checked(self):
        catalog=extract((ROOT/'rf_online.bin').read_bytes())
        self.assertEqual([s['count'] for s in catalog['sections']],[15,8,11,2,18,11,11])
        self.assertEqual(len(catalog['actions']),76)
        actions={a['action']:a for a in catalog['actions']}
        self.assertEqual(actions['KEYBOARD_MOVE_METHOD']['section'],'BEHAVIOR')
        self.assertEqual(actions['MOVE_UP']['va'],'0xb07650')
        self.assertEqual(actions['SHOUT_ADMIN']['index'],75)
        self.assertEqual(len(catalog['keys']),86)
        keys={k['token']:k['virtual_key'] for k in catalog['keys']}
        self.assertEqual(keys['W'],0x57)
        self.assertEqual(keys['F12'],0x7b)
        self.assertNotIn('?',keys)
        self.assertEqual(catalog['modifiers'],[{'token':'SHIFT','virtual_key':16},{'token':'CTRL','virtual_key':17},{'token':'ALT','virtual_key':18}])
        audit=audit_tables(catalog)
        self.assertEqual(audit['KeyMap.dat']['known_commands'],76)
        self.assertEqual({r['action'] for r in audit['KeyMap_NKM.dat']['missing_from_file']},
                         {'GMREQUEST_WINDOW','ZOOM_IN','ZOOM_OUT','ALL_WINDOW_CLOSE'})

    def test_wrong_build_is_rejected_before_address_based_reads(self):
        with self.assertRaisesRegex(ValueError,'Unsupported client build'):
            extract(b'MZ not the supplied binary')


if __name__=='__main__':unittest.main()
