#!/usr/bin/env python3
"""Static PE32 inventory. Never loads or executes the supplied Windows client."""
import argparse
import hashlib
import json
import math
import re
import struct
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


class PE32:
    def __init__(self, data):
        self.data = data
        if self.bytes(0, 2) != b'MZ':
            raise ValueError('Missing DOS MZ header')
        pe = self.u32(0x3c)
        if self.bytes(pe, 4) != b'PE\0\0':
            raise ValueError('Missing PE signature')
        self.machine, count, self.timestamp = self.unpack('<HHI', pe + 4)
        optional_size = self.u16(pe + 20)
        optional = pe + 24
        if self.machine != 0x14c or self.u16(optional) != 0x10b or optional_size < 96:
            raise ValueError('Only x86 PE32 is supported')
        if not 1 <= count <= 96:
            raise ValueError('Invalid section count')
        self.entry_rva = self.u32(optional + 16)
        self.image_base = self.u32(optional + 28)
        self.headers_size = self.u32(optional + 60)
        self.subsystem = self.u16(optional + 68)
        directories = min(self.u32(optional + 92), 16)
        if 96 + directories * 8 > optional_size:
            raise ValueError('Truncated optional header')
        self.directories = [self.unpack('<II', optional + 96 + i * 8) for i in range(directories)]
        self.sections = []
        for i in range(count):
            offset = optional + optional_size + i * 40
            name = self.bytes(offset, 8).rstrip(b'\0').decode('ascii', 'replace')
            virtual_size, rva, size, raw = self.unpack('<IIII', offset + 8)
            payload = self.bytes(raw, size) if size else b''
            entropy = -sum((n / size) * math.log2(n / size) for n in Counter(payload).values()) if size else 0
            self.sections.append(dict(name=name, rva=rva, virtual_size=virtual_size,
                                      file_offset=raw, file_size=size,
                                      characteristics=self.u32(offset + 36), entropy=round(entropy, 3)))

    def bytes(self, offset, size):
        if offset < 0 or size < 0 or offset + size > len(self.data):
            raise ValueError(f'Out-of-range read at 0x{offset:x}, size {size}')
        return self.data[offset:offset + size]

    def unpack(self, fmt, offset):
        return struct.unpack(fmt, self.bytes(offset, struct.calcsize(fmt)))

    def u16(self, offset):
        return self.unpack('<H', offset)[0]

    def u32(self, offset):
        return self.unpack('<I', offset)[0]

    def offset(self, rva, size=1):
        if 0 <= rva < self.headers_size and rva + size <= self.headers_size:
            self.bytes(rva, size)
            return rva
        for s in self.sections:
            delta = rva - s['rva']
            if 0 <= delta and delta + size <= s['file_size']:
                return s['file_offset'] + delta
        raise ValueError(f'RVA 0x{rva:x} is not backed by file bytes')

    def string(self, rva):
        offset = self.offset(rva)
        end = self.data.find(b'\0', offset, min(offset + 4096, len(self.data)))
        if end < 0:
            raise ValueError('Unterminated PE string')
        self.offset(rva, end - offset + 1)
        return self.data[offset:end].decode('ascii', 'replace')

    def imports(self):
        if len(self.directories) < 2 or not self.directories[1][0]:
            return []
        rva, size = self.directories[1]
        result = []
        for i in range(min(size // 20, 4096)):
            original, stamp, chain, name, first = self.unpack('<IIIII', self.offset(rva + i * 20, 20))
            if not any((original, stamp, chain, name, first)):
                return result
            symbols = []
            for j in range(65536):
                thunk = self.u32(self.offset((original or first) + j * 4, 4))
                if not thunk:
                    break
                symbols.append(dict(name=None if thunk & 0x80000000 else self.string(thunk + 2),
                                    ordinal=thunk & 0xffff if thunk & 0x80000000 else None,
                                    iat_va=hex(self.image_base + first + j * 4)))
            else:
                raise ValueError('Import thunk limit exceeded')
            result.append(dict(dll=self.string(name), symbols=symbols))
        raise ValueError('Unterminated import directory')

    def exports(self):
        if not self.directories or not self.directories[0][0]:
            return []
        rva, size = self.directories[0]
        offset = self.offset(rva, 40)
        base, functions, names, addresses, pointers, ordinals = self.unpack('<IIIIII', offset + 16)
        if max(functions, names) > 65536:
            raise ValueError('Export table limit exceeded')
        result = []
        for i in range(names):
            ordinal = self.u16(self.offset(ordinals + i * 2, 2))
            if ordinal >= functions:
                raise ValueError('Invalid export ordinal')
            target = self.u32(self.offset(addresses + ordinal * 4, 4))
            result.append(dict(name=self.string(self.u32(self.offset(pointers + i * 4, 4))),
                               ordinal=base + ordinal, rva=hex(target),
                               forwarder=self.string(target) if rva <= target < rva + size else None))
        return result


def inspect(data):
    pe = PE32(data)
    strings = []
    # Data sections only: do not mistake arbitrary instruction bytes for settings.
    for s in pe.sections:
        if s['name'] not in ('.rdata', '.data'):
            continue
        for m in re.finditer(rb'[\x20-\x7e]{4,}', data[s['file_offset']:s['file_offset'] + s['file_size']]):
            offset = s['file_offset'] + m.start()
            strings.append(dict(text=m.group().decode('ascii'), file_offset=hex(offset),
                                va=hex(pe.image_base + s['rva'] + m.start())))
    resource_pattern = re.compile(r'(?i)\.(?:ini|cfg|dat|rfs|spr|edf|r3m|r3t|bsp|ani|msh|bon|dds|ttf|swf|gfx)\b')
    references = [s for s in strings if len(s['text']) <= 512 and resource_pattern.search(s['text'])]
    neighborhoods = []
    for ref in references:
        if re.search(r'(?i)\.(ini|cfg)\b', ref['text']):
            center = int(ref['file_offset'], 16)
            neighborhoods.append(dict(reference=ref, confidence='Adjacent strings only; not proven key/section associations or defaults.',
                                      neighbors=[s for s in strings if abs(int(s['file_offset'], 16) - center) <= 160 and len(s['text']) <= 160]))
    end = max(s['file_offset'] + s['file_size'] for s in pe.sections)
    return dict(schema_version=1, source='rf_online.bin', bytes=len(data), sha256=hashlib.sha256(data).hexdigest(),
                format='Windows x86 PE32 executable', image_base=hex(pe.image_base), entry_rva=hex(pe.entry_rva),
                entry_va=hex(pe.image_base + pe.entry_rva), subsystem=pe.subsystem,
                timestamp_raw=pe.timestamp, timestamp_note='Header value only; not a verified release date.',
                sections=pe.sections, trailing_bytes=len(data) - end,
                imports=pe.imports(), exports=pe.exports(), resource_references=references,
                configuration_neighborhoods=neighborhoods,
                limitations=['Static inventory, not recovered source code or a decompiler.',
                             'String presence does not prove a reachable feature, a configuration value or protocol semantics.',
                             'Native dependencies, external configuration and server logic are not embedded in this report.',
                             'No executable, DLL, command or endpoint found in the input is executed or contacted.'])


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('binary', nargs='?', type=Path, default=ROOT / 'rf_online.bin')
    parser.add_argument('--output', type=Path, default=ROOT / 'System/analysis/rf-online.json')
    args = parser.parse_args()
    report = inspect(args.binary.read_bytes())
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2, ensure_ascii=False) + '\n')
    print(json.dumps({k: report[k] for k in ('bytes', 'sha256', 'format', 'entry_va', 'trailing_bytes')}))
    print(f"{len(report['imports'])} DLLs, {len(report['exports'])} named exports, {len(report['resource_references'])} resource references -> {args.output}")


if __name__ == '__main__':
    main()
