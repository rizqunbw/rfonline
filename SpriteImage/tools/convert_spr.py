"""Decode observed RF SPR 1.1 groups to RGBA and export selected original HUD art.

Format derived from the supplied files: f32 version, u32 group count, then
u32 image count per group. Each image has six u32 fields: D3DFORMAT, logical
width/height, stored width/height, payload bytes; raw pixels follow immediately.
No cells, instructions, code or executables from assets are evaluated.
"""
from pathlib import Path
import hashlib
import io
import json
import math
import struct
from PIL import Image

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT.parent / 'Map/Platform01/assets/ui'
DXT1, DXT5, ARGB8888, RGB565 = 0x31545844, 0x35545844, 21, 23
FORMATS = {DXT1:'DXT1', DXT5:'DXT5', ARGB8888:'A8R8G8B8', RGB565:'R5G6B5'}
SELECTION = {
    'status-frame':('main',0,0), 'hp':('main',0,1), 'fp':('main',0,2), 'sp':('main',0,3),
    'level-ring':('main',0,7), 'hotbar':('main',1,0), 'hotbar-numbers':('main',1,1),
    'radar-frame':('main',3,0), 'radar-face':('main',3,1), 'radar-cone':('main',3,2),
    'radar-plus':('main',3,19), 'radar-minus':('main',3,22),
    'notice':('main',5,0), 'overhead-bg':('main',7,5), 'overhead-hp':('main',7,6),
    'overhead-fp':('main',7,7), 'overhead-sp':('main',7,8),
    'footer':('main',11,0), 'icon-target':('main',12,0), 'icon-walk':('main',12,2),
    'icon-run':('main',12,3), 'icon-combat':('main',12,5),
    'icon-character':('main',13,0), 'icon-inventory':('main',13,1), 'icon-settings':('main',13,2),
    'icon-chat':('main',13,10), 'icon-map':('main',13,13), 'icon-help':('main',4,6),
    'icon-emblem':('main',13,16), 'icon-headwear':('inventory',2,0),
    'inventory-equipment':('inventory',0,0), 'inventory-bag':('inventory',0,1),
    'equip-helmet':('inventory',2,0), 'equip-upper':('inventory',2,1), 'equip-lower':('inventory',2,2),
    'equip-boots':('inventory',2,4), 'equip-gloves':('inventory',2,6),
    'cursor':('mouse',0,0), 'close':('main',2,12),
}


def read_spr(data):
    cursor = 0
    def read(fmt):
        nonlocal cursor
        size = struct.calcsize('<'+fmt)
        if cursor+size > len(data): raise ValueError('Truncated SPR header')
        result = struct.unpack_from('<'+fmt, data, cursor); cursor += size
        return result
    version, count = read('fI')
    if not math.isclose(version, 1.1, abs_tol=1e-6) or not 0<count<1024:
        raise ValueError('Unsupported SPR version or group count')
    frames = []
    for group in range(count):
        images, = read('I')
        if not 0<images<4096: raise ValueError('Invalid SPR image count')
        for frame in range(images):
            fmt,w,h,pw,ph,size = read('6I')
            if fmt not in FORMATS: raise ValueError(f'Unsupported D3DFORMAT: {fmt}')
            if not 0<w<=pw<=8192 or not 0<h<=ph<=8192: raise ValueError('Invalid sprite dimensions')
            expected = ((pw+3)//4)*((ph+3)//4)*(8 if fmt==DXT1 else 16) if fmt in [DXT1,DXT5] else pw*ph*(4 if fmt==ARGB8888 else 2)
            if size != expected or cursor+size>len(data): raise ValueError('Invalid sprite payload size')
            frames.append(dict(group=group, frame=frame, format=FORMATS[fmt], formatId=fmt,
                width=w, height=h, storedWidth=pw, storedHeight=ph, offset=cursor, bytes=size,
                sha256=hashlib.sha256(data[cursor:cursor+size]).hexdigest()))
            cursor += size
    if cursor != len(data): raise ValueError('Trailing SPR bytes')
    return frames


def decode(data, record):
    fmt,w,h = record['formatId'],record['storedWidth'],record['storedHeight']
    raw = data[record['offset']:record['offset']+record['bytes']]
    if fmt in [DXT1,DXT5]:
        header = b'DDS '+struct.pack('<7I',124,0x81007,h,w,len(raw),0,0)+bytes(44)
        header += struct.pack('<II4s5I',32,4,struct.pack('<I',fmt),0,0,0,0,0)+struct.pack('<5I',0x1000,0,0,0,0)
        image = Image.open(io.BytesIO(header+raw)).convert('RGBA')
    elif fmt == ARGB8888:
        image = Image.frombytes('RGBA',(w,h),raw,'raw','BGRA')
    else:
        image = Image.frombytes('RGB',(w,h),raw,'raw','BGR;16').convert('RGBA')
    return image.crop((0,0,record['width'],record['height']))


def build():
    OUT.mkdir(parents=True,exist_ok=True)
    catalog, selected = [], {}
    # Some roles intentionally share the same original sprite.
    for path in sorted((ROOT/'common').glob('*.spr')):
        data = path.read_bytes(); records = read_spr(data)
        for record in records:
            image = decode(data,record)
            record['pixelsSha256'] = hashlib.sha256(image.tobytes()).hexdigest()
            for role, source in SELECTION.items():
                if source != (path.stem,record['group'],record['frame']): continue
                image.save(OUT/(role+'.png'))
                selected[role] = dict(source=path.name,group=record['group'],frame=record['frame'],
                    url='assets/ui/'+role+'.png',width=image.width,height=image.height,pixelsSha256=record['pixelsSha256'])
        catalog.append(dict(source=path.name,bytes=len(data),sha256=hashlib.sha256(data).hexdigest(),frames=records))
    if selected.keys() != SELECTION.keys(): raise ValueError('Selected HUD art not found')
    # Original hotbar cell, cropped only; no painting or generated replacement art.
    frame = Image.open(OUT/'footer.png').convert('RGBA')
    rect = [313,4,357,48]
    slot = frame.crop(rect); slot.save(OUT/'slot.png')
    selected['slot'] = dict(source='main.spr',group=11,frame=0,crop=rect,url='assets/ui/slot.png',
        width=44,height=44,pixelsSha256=hashlib.sha256(slot.tobytes()).hexdigest())
    (ROOT/'common/catalog.json').write_text(json.dumps(catalog,indent=2)+'\n')
    localized=[]
    for path in sorted((ROOT/'en-gb').glob('*.spr')):
        data=path.read_bytes(); records=read_spr(data)
        for record in records:
            record['pixelsSha256']=hashlib.sha256(decode(data,record).tobytes()).hexdigest()
        localized.append(dict(source=path.name,bytes=len(data),sha256=hashlib.sha256(data).hexdigest(),frames=records))
    (ROOT/'en-gb/catalog.json').write_text(json.dumps(localized,indent=2)+'\n')
    (OUT/'manifest.json').write_text(json.dumps(selected,indent=2)+'\n')
    print(f'Decoded {len(catalog)} SPR files / {sum(len(c["frames"]) for c in catalog)} images; exported {len(selected)} HUD roles')
    print(f'Decoded {len(localized)} en-gb SPR files / {sum(len(c["frames"]) for c in localized)} images; originals retained')


if __name__ == '__main__': build()
