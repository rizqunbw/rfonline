"""RF static terrain conversion; format reference: cbb-rf-online-addon (MIT)."""
from pathlib import Path
import struct,json,io,hashlib,math
from PIL import Image
ROOT=Path(__file__).resolve().parents[1]
SRC=ROOT/'assets/source';OUT=ROOT/'assets/terrain';OUT.mkdir(exist_ok=True)
KEY=bytes.fromhex('2e804d762ef8d1f0bd3f8681582c3f3f2e2e676f3f403f783c3ff1c0a5f63b9fc1203fd7c8c1e98586bdef563fa1fb2e8786614c213b4eb47857ae973f2e4a2e3f4c2e44cdc55fe8e9ecebbdbebbf76c2ef2e42e3f3f979f9db321b97665543fe6f6c6f079dbe2b24b2e2eebd3d3caabeac7ed9cc7d9d06548b4fa352e2e6a9b')
def textures(name,prefix,directory):
 data=(SRC/name).read_bytes();version,count=struct.unpack_from('<fI',data);assert abs(version-1.2)<.001
 names=[data[8+i*128:8+(i+1)*128].split(b'\0')[0].decode('euc-kr') for i in range(count)] if directory else [str(i) for i in range(count)]
 cursor=8+128*count if directory else 8;result=[]
 for i,name in enumerate(names):
  size=struct.unpack_from('<I',data,cursor)[0];cursor+=4;blob=data[cursor:cursor+size];assert len(blob)==size
  if blob[:4]!=b'DDS ':blob=bytes(x^y for x,y in zip(blob[:128],KEY))+blob[128:]
  assert blob[:4]==b'DDS '
  image=Image.open(io.BytesIO(blob)).convert('RGBA');image.save(OUT/f'{prefix}{i}.png')
  result.append({'name':name,'url':f'assets/terrain/{prefix}{i}.png','size':list(image.size),'pixelsSha256':hashlib.sha256(image.tobytes()).hexdigest()});cursor+=size
 assert cursor==len(data)
 return result
if __name__=='__main__':
 tex=textures('Platform01.r3t','t',True);lights=textures('Platform01Lgt.r3t','l',False)
 data=(SRC/'Platform01.r3m').read_bytes();count=struct.unpack_from('<I',data,4)[0];o=8;materials=[]
 for i in range(count):
  n,flag=struct.unpack_from('<II',data,o);name=data[o+16:o+144].split(b'\0')[0].decode('euc-kr');o+=144;layers=[]
  for k in range(n):
   v=struct.unpack_from('<hiIIIhhhhhhhhhhHhhh',data,o);o+=46
   assert 1<=v[1]<=len(tex)
   layers.append({'texture':v[1]-1,'blend':v[2],'tint':[((v[3]>>s)&255)/255 for s in (16,8,0,24)],'flags':v[4]})
  materials.append({'name':name,'layers':layers})
 assert o==len(data)
 data=(SRC/'Platform01.bsp').read_bytes();h=struct.unpack_from('<170I',data,4)
 def records(i,fmt):return list(struct.iter_unpack(fmt,data[h[i]:h[i]+h[i+1]]))
 positions=records(90,'<3f');colors=records(92,'<4B');uvs=records(94,'<2f');luv=records(96,'<2h');faces=records(98,'<HI');faceids=records(100,'<I');vids=records(102,'<I');groups=records(104,'<HHIhh3h3h3ffH')
 mesh=bytearray();draws=[]
 for g in groups:
  _,n,first,mat,light,*_=g
  if mat<0 or g[-1]:continue
  start=len(mesh)//44;assert -1<=light<len(lights)
  for slot in range(first,first+n):
   amount,offset=faces[faceids[slot][0]]
   for j in range(1,amount-1):
    for corner in [offset,offset+j,offset+j+1]:
     v=vids[corner][0];b,gr,r,a=colors[v];values=[*(x/100 for x in positions[v]),r/255,gr/255,b/255,a/255,*uvs[corner],*(x/32767 for x in luv[corner])]
     assert all(math.isfinite(x) for x in values);mesh.extend(struct.pack('<11f',*values))
  draws.append({'first':start,'count':len(mesh)//44-start,'material':mat,'light':light})
 (OUT/'mesh.bin').write_bytes(mesh)
 manifest={'textures':tex,'lights':lights,'materials':materials,'draws':draws,'triangles':len(mesh)//132,'limitations':['Only first material layer rendered','Animated/invisible groups and EBP effects omitted'],'sources':[{'name':n,'sha256':hashlib.sha256((SRC/n).read_bytes()).hexdigest()} for n in ['Platform01.r3t','Platform01Lgt.r3t','Platform01.r3m','Platform01.bsp']]}
 (OUT/'manifest.json').write_text(json.dumps(manifest,indent=2));print(f'Converted {len(tex)} textures, {len(lights)} lightmaps, {len(mesh)//132} triangles')
