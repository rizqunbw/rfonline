"""Validate the standard weighted MSH format observed in BFF00.

MESH08 and other weight layouts deliberately fail instead of guessing.
Format reference: cbb-rf-online-addon; see ../THIRD_PARTY_LICENSE.txt.
"""
import argparse
import json
import math
from pathlib import Path
import struct


class Reader:
    def __init__(self,data): self.data,self.offset=data,0
    def take(self,size):
        if size<0 or self.offset+size>len(self.data): raise ValueError('Truncated MSH record')
        result=self.data[self.offset:self.offset+size];self.offset+=size;return result
    def unpack(self,fmt): return struct.unpack('<'+fmt,self.take(struct.calcsize('<'+fmt)))
    def name(self): return self.take(100).split(b'\0',1)[0].decode('euc-kr')


def inspect(data):
    if data.startswith(b'MESH08'): raise ValueError('MESH08 is not supported by this inspector')
    r=Reader(data);count,=r.unpack('H');objects=[]
    if not 0<count<=len(data)//693: raise ValueError('Invalid object count')
    for _ in range(count):
        name,parent=r.name(),r.name()
        matrices=r.unpack('48f')
        vertices,triangles,weights=r.unpack('3H')
        texture,effect=r.name(),r.name()
        r.take(44);weight_type,=r.unpack('I');r.take(47)
        if weight_type!=1: raise ValueError(f'Unsupported weight layout: {weight_type}')
        positions=[]
        for _ in range(vertices):
            values=r.unpack('7f')
            if not all(math.isfinite(x) for x in values): raise ValueError('Nonfinite vertex data')
            positions.append(values[:3])
        for _ in range(triangles):
            indices=r.unpack('3I');attributes=r.unpack('18f');r.take(4)
            if any(i>=vertices for i in indices): raise ValueError('Triangle vertex index out of range')
            if not all(math.isfinite(x) for x in attributes): raise ValueError('Nonfinite face data')
        bone_count,=r.unpack('I')
        if bone_count>(len(data)-r.offset)//100: raise ValueError('Invalid bone count')
        bones=[r.name() for _ in range(bone_count)]
        seen=set()
        for _ in range(weights):
            vertex,amount,*indices=r.unpack('II4i');values=r.unpack('4f')
            if vertex>=vertices or vertex in seen or amount>4: raise ValueError('Invalid weight vertex/count')
            if any(i < -1 or i>=bone_count for i in indices): raise ValueError('Bone index out of range')
            active=[value for bone,value in zip(indices,values) if bone!=-1]
            if len(active)!=amount: raise ValueError('Weight count does not match active bone slots')
            # Unused (-1 bone) slots contain legacy padding, sometimes NaN.
            if any(not math.isfinite(v) or not 0<=v<=1.00001 for v in active): raise ValueError('Invalid active bone weight')
            seen.add(vertex)
        if not all(math.isfinite(x) for x in matrices): raise ValueError('Invalid object matrix')
        objects.append({'name':name,'parent':parent,'vertices':vertices,'triangles':triangles,
                        'weightedVertices':weights,'bones':bones,
                        'texture':texture.replace('\\','/').split('/')[-1],
                        'effectTexture':effect.replace('\\','/').split('/')[-1],
                        'boundsLocal':[[min(p[a] for p in positions) for a in range(3)],
                                       [max(p[a] for p in positions) for a in range(3)]] if positions else None})
    if r.offset!=len(data): raise ValueError(f'Unparsed trailing bytes: {len(data)-r.offset}')
    return {'objects':objects,'vertices':sum(o['vertices'] for o in objects),
            'triangles':sum(o['triangles'] for o in objects),'bytesConsumed':r.offset}


if __name__=='__main__':
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('mesh',type=Path)
    args=parser.parse_args();print(json.dumps(inspect(args.mesh.read_bytes()),indent=2))
