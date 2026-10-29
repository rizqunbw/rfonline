import assert from 'node:assert/strict';
import {readFileSync} from 'node:fs';
import {createNativeInput,loadNativeInput} from '../native-input.js';
import {loadKeyMaps,resolveKey} from '../keymap.js';
const data=JSON.parse(readFileSync(new URL('../../../System/analysis/native-input.json',import.meta.url),'utf8'));
const native=createNativeInput(data);
assert.equal(native.actionCount,76);assert.equal(native.keyCount,86);
for(const mutation of [d=>d.binary_sha256='wrong build',d=>d.keys[0].virtual_key=0,d=>d.keys[1].token=d.keys[0].token,d=>d.actions[0].section='COMBAT',d=>d.sections[0].count++,d=>d.modifiers[0].virtual_key=99]){
 const bad=structuredClone(data);mutation(bad);assert.throws(()=>createNativeInput(bad));
}
const originalFetch=globalThis.fetch,requests=[];
try{
 globalThis.fetch=async url=>{
  requests.push(url);
  if(url==='assets/system/native-input.json')return {ok:true,json:async()=>data};
  const file=new URL('../../../DataTable/en-gb/'+url.split('/').at(-1),import.meta.url);
  return {ok:true,text:async()=>readFileSync(file,'utf8')};
 };
 const maps=await loadKeyMaps();
 assert.equal(requests[0],'assets/system/native-input.json');
 assert.equal(maps.native.mouseBindings,76);assert.equal(maps.native.keyboardBindings,72);
 assert.equal(resolveKey(maps.keyboard,{code:'KeyW'}),'MOVE_UP');
 globalThis.fetch=async()=>({ok:false});
 await assert.rejects(loadNativeInput(),/catalog gagal/);
 globalThis.fetch=async()=>({ok:true,json:async()=>({...data,binary_sha256:'unknown'})});
 await assert.rejects(loadKeyMaps(),/Unsupported native input catalog/);
}finally{globalThis.fetch=originalFetch;}
