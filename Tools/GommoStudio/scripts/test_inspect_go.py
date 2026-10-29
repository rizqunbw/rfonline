import struct
import unittest
from inspect_go import Reader,inspect


def fixture():
    data=bytearray(2048);data[:2]=b'MZ';struct.pack_into('<I',data,0x3c,0x80)
    data[0x80:0x84]=b'PE\0\0';struct.pack_into('<HH',data,0x84,0x8664,2)
    struct.pack_into('<H',data,0x94,0xf0);struct.pack_into('<H',data,0x98,0x20b)
    struct.pack_into('<Q',data,0xb0,0x140000000)
    for at,name,rva,size,raw in [(0x188,b'.text',0x1000,256,0x200),(0x1b0,b'.rdata',0x2000,1280,0x300)]:
        data[at:at+len(name)]=name;struct.pack_into('<IIII',data,at+8,size,rva,size,raw)
    data[0x300:0x308]=bytes.fromhex('f1ffffff00000108')
    struct.pack_into('<8Q',data,0x308,2,1,0x140001000,96,160,192,224,256)
    names=b'gommo/pkg/assets/rfpack.ReadRFSEntries\0main.main\0'
    data[0x360:0x360+len(names)]=names
    path=b'gommo/pkg/assets/rfpack/rfs.go\0';data[0x3c0:0x3c0+len(path)]=path
    struct.pack_into('<IIIII',data,0x400,0,24,32,32,64)
    struct.pack_into('<IIII',data,0x418,0,0,32,names.index(b'main.main'))
    data[0x600:0x610]=b'\xff Go buildinf:\x08\x02'
    version=b'go1.25.14';module=b'0'*16+b'path\tgommo/cmd/gommostudio\n'+b'1'*16
    payload=bytes([len(version)])+version+bytes([len(module)])+module
    data[0x620:0x620+len(payload)]=payload
    return bytes(data)


class GoMetadataTests(unittest.TestCase):
    def test_index_comes_from_metadata_and_resolves_function_bounds(self):
        meta,module,all_functions,app,core,packages,files=inspect(fixture())
        self.assertEqual(meta['functions'],2);self.assertEqual(meta['go_version'],'go1.25.14')
        self.assertEqual(all_functions[0]['bytes'],32)
        self.assertEqual(all_functions[1]['address'],'0x140001020')
        self.assertEqual(len(core),1);self.assertEqual(len(app),2)
        self.assertEqual(files,['gommo/pkg/assets/rfpack/rfs.go'])

    def test_truncation_and_invalid_addresses_are_rejected(self):
        for data in [b'',b'MZ',fixture()[:512]]:
            with self.assertRaises(ValueError):inspect(data)
        bad=bytearray(fixture());struct.pack_into('<I',bad,0x400,33)
        with self.assertRaises(ValueError):inspect(bytes(bad))

    def test_untrusted_ranges_varints_and_strings_are_bounded(self):
        with self.assertRaises(ValueError):Reader(b'abc').take(-1,1)
        with self.assertRaises(ValueError):Reader(b'abc').string(0,3)
        with self.assertRaises(ValueError):Reader(b'\xff'*10).uvarint(0)


if __name__=='__main__':unittest.main()
