"""Extract flat RF archives without modifying payload bytes (Python 3 only).

Format reference: Cardboard-box-a/cbb-rf-online-addon (MIT).
See ../THIRD_PARTY_LICENSE.txt. No Blender or game executable is run.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct


def entries(data):
    if len(data) < 4:
        raise ValueError('Truncated archive header')
    count = struct.unpack_from('<I', data)[0]
    table_end = 4 + count * 64
    if not count or table_end > len(data):
        raise ValueError('Invalid archive entry count')
    result, names = [], set()
    for i in range(count):
        at = 4 + i * 64
        raw_name = data[at:at+56]
        if b'\0' not in raw_name:
            raise ValueError('Unterminated entry name')
        name = raw_name.split(b'\0', 1)[0].decode('euc-kr')
        if not name or name in ('.', '..') or any(c in name for c in '/\\:') or any(ord(c)<32 for c in name):
            raise ValueError('Unsafe entry filename')
        if name.casefold() in names:
            raise ValueError('Duplicate entry filename')
        names.add(name.casefold())
        offset, size = struct.unpack_from('<II', data, at+56)
        if not size or offset < table_end or offset + size > len(data):
            raise ValueError('Invalid payload range')
        result.append({'name': name, 'offset': offset, 'size': size,
                       'sha256': hashlib.sha256(data[offset:offset+size]).hexdigest()})
    previous = table_end
    for entry in sorted(result, key=lambda e:e['offset']):
        if entry['offset'] < previous:
            raise ValueError('Overlapping payload ranges')
        previous = entry['offset'] + entry['size']
    return result


def extract(archive, output):
    data = Path(archive).read_bytes()
    records = entries(data)
    output = Path(output)
    if output.is_symlink():
        raise ValueError('Output directory must not be a symlink')
    # Check every destination before writing anything. Repeating extraction is safe.
    for e in records:
        dest = output/e['name']
        if dest.is_symlink() or (dest.exists() and (not dest.is_file() or dest.read_bytes()!=data[e['offset']:e['offset']+e['size']])):
            raise ValueError(f'Refusing to overwrite existing output: {e["name"]}')
    output.mkdir(parents=True, exist_ok=True)
    for e in records:
        (output/e['name']).write_bytes(data[e['offset']:e['offset']+e['size']])
    return records


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('archive', type=Path)
    parser.add_argument('output', type=Path)
    args = parser.parse_args()
    result = extract(args.archive,args.output)
    print(json.dumps({'archive':args.archive.name,'files':result},indent=2))
