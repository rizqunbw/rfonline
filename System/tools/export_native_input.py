"""Extract the key-command tables referenced by the native INI loader.

Addresses are verified for this exact binary only; reject a different build.
No inferred table names or web hotkey aliases are injected into the export.
"""
import hashlib
import json
from inspect_client import PE32, ROOT

SHA256 = '951e1056875c27f717bfb62d25ffc68d36337416e16d0b7ccc0f7c42b534d2c6'


def extract(data):
    if hashlib.sha256(data).hexdigest() != SHA256:
        raise ValueError('Unsupported client build: native addresses must be retraced')
    pe = PE32(data)
    counts = pe.unpack('<7I', pe.offset(0xb07f10-pe.image_base, 28))
    actions = []
    sections = []
    index = 0
    for section_index, count in enumerate(counts):
        section = pe.string(0xb07f30 + section_index*32 - pe.image_base)
        sections.append(dict(index=section_index, name=section, count=count))
        for ordinal in range(count):
            va = 0xb07290 + index*32
            action = pe.string(va-pe.image_base)
            if not action or len(action) >= 32:
                raise ValueError('Invalid fixed-width command record')
            actions.append(dict(index=index, section=section, section_index=section_index,
                                section_ordinal=ordinal, action=action,
                                va=hex(va), file_offset=hex(pe.offset(va-pe.image_base))))
            index += 1
    # Assert the instruction operands which establish record stride and section counts.
    proofs = [(0x5397d9, '83bdacfcffff07'), (0x53981c, '3b0c85107fb000'),
              (0x539860, 'c1e20581c29072b000'), (0x539870, 'c1e00505307fb000')]
    for va, expected in proofs:
        raw = bytes.fromhex(expected)
        if pe.bytes(pe.offset(va-pe.image_base,len(raw)),len(raw)) != raw:
            raise ValueError('Native keymap loader evidence mismatch')
    keys=[dict(index=i,token=pe.string(0xb06d30+i*12-pe.image_base),
               virtual_key=pe.u32(pe.offset(0xb07138+i*4-pe.image_base,4))) for i in range(86)]
    modifiers=[dict(token=pe.string(0xb06d00+i*12-pe.image_base),
                    virtual_key=pe.u32(pe.offset(0xb06d24+i*4-pe.image_base,4))) for i in range(3)]
    return dict(binary_sha256=SHA256, evidence=dict(loader_calls=['0x539879','0x539940'],
                api='GetPrivateProfileStringA', sections_va='0xb07f30', counts_va='0xb07f10',
                actions_va='0xb07290', record_bytes=32, key_decoder='0x538f50',
                key_names_va='0xb06d30', key_codes_va='0xb07138', key_record_bytes=12),
                sections=sections, actions=actions, keys=keys, modifiers=modifiers)


def audit_tables(catalog):
    lookup = {(r['section'],r['action']):r['index'] for r in catalog['actions']}
    output = {}
    for name in ('KeyMap.dat','KeyMap_NKM.dat'):
        source = ROOT / 'DataTable/en-gb' / name
        found = set();extras=[];section=''
        for raw in source.read_text().splitlines():
            line=raw.strip()
            if not line or line.startswith(';'):continue
            if line.startswith('[') and line.endswith(']'):section=line[1:-1];continue
            key=line.split('=',1)[0].strip();pair=(section,key)
            if pair in lookup:found.add(pair)
            else:extras.append(dict(section=section,action=key))
        output[name]=dict(sha256=hashlib.sha256(source.read_bytes()).hexdigest(),
                         known_commands=len(found),not_in_generic_native_table=extras,
                         missing_from_file=[r for r in catalog['actions'] if (r['section'],r['action']) not in found])
    return output


if __name__ == '__main__':
    catalog = extract((ROOT/'rf_online.bin').read_bytes())
    catalog['uploaded_keymaps'] = audit_tables(catalog)
    out=ROOT/'System/analysis/native-input.json'
    out.write_text(json.dumps(catalog,indent=2)+'\n')
    print(f"Exported {len(catalog['actions'])} commands / {len(catalog['sections'])} sections to {out}")
    print(json.dumps({k:dict(known=v['known_commands'],extra=len(v['not_in_generic_native_table']),missing=len(v['missing_from_file'])) for k,v in catalog['uploaded_keymaps'].items()}))
