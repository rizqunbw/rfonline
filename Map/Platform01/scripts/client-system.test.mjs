import test from 'node:test';
import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import {validateClientSystem,loadClientSystem,clampCameraDistance,advanceStamina} from '../client-system.js';
const source=JSON.parse(await readFile(new URL('../../../System/web-client.json',import.meta.url)));
test('configuration rejects invalid tuning, unsupported modes and cross-origin assets',()=>{
  const mutations=[c=>c.camera.distance=100,c=>c.camera.minDistance=15,c=>c.camera.pitch=-1.4,c=>c.movement.runSpeed=.1,c=>c.renderer.maxPixelRatio=NaN,c=>c.input.defaultMode='invalid',c=>c.mode='online',c=>c.assets.language='https://example.com/x.json',c=>c.assets.language='assets/../secret.json',c=>c.assets.keymaps.mouse='assets/keymaps/KeyMap.dat?x',c=>c.ui.fontFamily='Verdana',c=>c.movement.walkSpeeed=2,c=>delete c.stamina,c=>c.camera=null];
  for(const mutate of mutations){const c=structuredClone(source);mutate(c);assert.throws(()=>validateClientSystem(c),/System\/web-client.json/);}
});
test('validated configuration is detached and immutable; zoom uses configured bounds',()=>{
  const input=structuredClone(source);input.camera.minDistance=6;input.camera.maxDistance=12;
  const c=validateClientSystem(input);input.camera.distance=9;assert.equal(c.camera.distance,8);
  assert.throws(()=>c.camera.distance=9,TypeError);
  assert.equal(clampCameraDistance(c,-100),6);assert.equal(clampCameraDistance(c,100),12);assert.equal(clampCameraDistance(c,9.5),9.5);
});
test('exhaustion drains, stays latched until threshold, and recovers using configured rates',()=>{
  const c=validateClientSystem(source);
  assert.deepEqual(advanceStamina(c,1,false,true,1),{value:0,exhausted:true});
  assert.deepEqual(advanceStamina(c,0,true,false,1),{value:8,exhausted:true});
  assert.deepEqual(advanceStamina(c,24,true,false,.25),{value:26,exhausted:false});
  assert.deepEqual(advanceStamina(c,99,false,false,1),{value:100,exhausted:false});
  const custom=structuredClone(source);custom.stamina.drainPerSecond=20;
  assert.equal(advanceStamina(validateClientSystem(custom),50,false,true,1).value,30);
});
test('configuration loader fails explicitly on HTTP errors and malformed documents',async()=>{
  await assert.rejects(loadClientSystem(async()=>({ok:false,status:404})),/HTTP 404/);
  await assert.rejects(loadClientSystem(async()=>({ok:true,json:async()=>({schemaVersion:2})})),/invalid/);
  const c=await loadClientSystem(async url=>{assert.equal(url,'assets/system/web-client.json');return{ok:true,json:async()=>source};});
  assert.equal(c.ui.fontFamily,'Lucida Console');
});
