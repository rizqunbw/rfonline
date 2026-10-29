"""Inspect native System assets as data and verify the uploaded archive hashes.

Requires Pillow and fontTools. No configuration, shader or binary is executed.
"""
from pathlib import Path
import hashlib
import json
import struct
from PIL import Image
from fontTools.ttLib import TTFont

ROOT=Path(__file__).resolve().parent

def inspect():
    manifest=json.loads((ROOT/'uploads.json').read_text())
    overrides={r['path']:r for r in manifest['overrides']}
    records=[]
    for source in manifest['files']:
        path=ROOT/source['path'];data=path.read_bytes();digest=hashlib.sha256(data).hexdigest()
        expected=overrides.get(source['path'],source)['sha256']
        if digest!=expected:raise ValueError('Source integrity mismatch: '+source['path'])
        record=dict(path=source['path'],bytes=len(data),sha256=digest,kind='native data; format not decoded')
        ext=path.suffix.lower()
        if not data:record['kind']='empty source file'
        elif data.startswith(b'\x00\x01\x00\x00') and ext in ['.ttf','.dat']:
            font=TTFont(path)
            record.update(kind='TrueType font',family=font['name'].getDebugName(1),fullName=font['name'].getDebugName(4),glyphs=font['maxp'].numGlyphs,
                cmaps=[dict(platform=t.platformID,encoding=t.platEncID,characters=len(t.cmap)) for t in font['cmap'].tables])
        elif data[:4]==b'RIFF' and data[8:12]==b'ACON':
            declared=struct.unpack_from('<I',data,4)[0]+8
            if declared!=len(data):record['warning']=f'RIFF declares {declared} total bytes; actual file has {len(data)}. Original retained; chunks checked against actual bounds.'
            cursor=12;chunks=[];header=None
            while cursor<len(data):
                if cursor+8>len(data):raise ValueError('Truncated RIFF chunk')
                tag=data[cursor:cursor+4].decode('ascii');size=struct.unpack_from('<I',data,cursor+4)[0];cursor+=8
                if cursor+size>len(data):raise ValueError('Truncated RIFF payload')
                chunks.append(dict(type=tag,bytes=size))
                if tag=='anih':header=struct.unpack_from('<9I',data,cursor)
                cursor+=size+(size%2)
            if not header:raise ValueError('Missing ANI header')
            record.update(kind='Windows animated cursor (RIFF ACON)',frames=header[1],steps=header[2],defaultJiffies=header[7],chunks=chunks)
        elif ext in ['.jpg','.dds','.tga']:
            with Image.open(path) as im:
                im.load();record.update(kind='image',format=im.format,width=im.width,height=im.height,mode=im.mode)
        elif ext in ['.vso','.pso']:
            token=struct.unpack_from('<I',data)[0]
            record.update(kind='Direct3D shader bytecode',stage='vertex' if token>>16==0xfffe else 'pixel' if token>>16==0xffff else 'unknown',version=f'{(token>>8)&255}.{token&255}')
        elif ext in ['.vsh','.psh','.nvv','.nvp']:record['kind']='legacy shader assembly/source; not GLSL'
        elif ext=='.sho':record['kind']='opaque RF shader asset; not decoded'
        elif ext in ['.ini','.cfg','.txt']:record['kind']='native text/configuration; retained as data'
        records.append(record)
    (ROOT/'catalog.json').write_text(json.dumps(records,indent=2,ensure_ascii=False)+'\n')
    print(f'Verified {len(records)} System files; font.ini is the only intentional source override.')

if __name__=='__main__':inspect()
