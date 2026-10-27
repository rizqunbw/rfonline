import test from 'node:test';
import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import {createHash} from 'node:crypto';
const manifest=JSON.parse(await readFile(new URL('../assets/manifest.json',import.meta.url)));
test('source files match recorded checksums',async()=>{
 for(const source of manifest.sources){const b=await readFile(new URL(`../assets/source/${source.name}`,import.meta.url));assert.equal(b.length,source.bytes);assert.equal(createHash('sha256').update(b).digest('hex'),source.sha256);}
});
test('exported points match BSP positions and BGRA colors',async()=>{
 const raw=await readFile(new URL('../assets/source/Platform01.bsp',import.meta.url));
 const points=await readFile(new URL('../assets/platform.points',import.meta.url));
 assert.equal(points.length,manifest.vertices*24);
 for(let i=0;i<manifest.vertices;i++){
  for(let axis=0;axis<3;axis++){const p=points.readFloatLE(i*24+axis*4);assert.ok(Number.isFinite(p));assert.ok(Math.abs(p-raw.readFloatLE(2603235+i*12+axis*4)/100)<.00002);}
  for(let c=0;c<3;c++)assert.ok(Math.abs(points.readFloatLE(i*24+12+c*4)-raw[5648871+i*4+2-c]/255)<.000001);
 }
});
test('static mesh triangles use the source polygon topology',async()=>{
 const raw=await readFile(new URL('../assets/source/Platform01.bsp',import.meta.url));
 const mesh=await readFile(new URL('../assets/platform.mesh',import.meta.url));
 const header=i=>raw.readUInt32LE(4+i*4);
 let cursor=0, skipped=0;
 for(let group=header(104);group<header(104)+header(105);group+=42){
  if(raw.readInt16LE(group+8)<0||raw.readUInt16LE(group+40)!==0){skipped++;continue;}
  const count=raw.readUInt16LE(group+2),first=raw.readUInt32LE(group+4);
  for(let f=0;f<count;f++){
   const face=header(98)+raw.readUInt32LE(header(100)+(first+f)*4)*6;
   const n=raw.readUInt16LE(face),start=raw.readUInt32LE(face+2);
   for(let j=1;j<n-1;j++)for(const corner of [0,j,j+1]){
    const vertex=raw.readUInt32LE(header(102)+(start+corner)*4);
    for(let a=0;a<3;a++)assert.ok(Math.abs(mesh.readFloatLE(cursor+a*4)-raw.readFloatLE(header(90)+vertex*12+a*4)/100)<.00002);
    for(let c=0;c<3;c++){const value=mesh.readFloatLE(cursor+12+c*4);assert.ok(Number.isFinite(value)&&value>=0&&value<=1);}
    cursor+=24;
   }
  }
 }
 assert.equal(cursor,mesh.length);assert.equal(cursor/72,manifest.triangles);assert.equal(skipped,manifest.skippedGroups);
});
