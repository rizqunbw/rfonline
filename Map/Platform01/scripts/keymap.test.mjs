import assert from 'node:assert/strict';
import {readFileSync} from 'node:fs';
import {parseKeyMap,resolveKey} from '../keymap.js';
const read=name=>parseKeyMap(readFileSync(new URL('../../../DataTable/en-gb/'+name,import.meta.url),'utf8'));
const mouse=read('KeyMap.dat'),keyboard=read('KeyMap_NKM.dat');
const key=(map,code,extra={})=>resolveKey(map,{code,ctrlKey:false,altKey:false,shiftKey:false,metaKey:false,...extra});
assert.equal(key(mouse,'KeyW'),'MOVE_MODE');
assert.equal(key(keyboard,'KeyW'),'MOVE_UP');
assert.equal(key(keyboard,'KeyW',{ctrlKey:true}),'MOVE_UP');
assert.equal(key(mouse,'ArrowUp'),'MOVE_UP');
assert.equal(key(keyboard,'KeyQ'),'CAMERA_ROT_LEFT');
assert.equal(key(keyboard,'KeyN'),'MOVE_MODE');
assert.equal(key(keyboard,'Semicolon'),'COMBAT_MODE');
for(const map of [mouse,keyboard]){
 assert.equal(key(map,'KeyH'),'KEYBOARD_MOVE_METHOD');
 assert.equal(key(map,'KeyH',{altKey:true}),'HIDE_UI');
 assert.equal(key(map,'KeyI'),'INVENTORY');
 assert.equal(key(map,'KeyI',{ctrlKey:true}),'INVENTORY');
 assert.equal(key(map,'F1'),'SLOT_1');
 assert.equal(key(map,'Digit1',{shiftKey:true}),'SHOUT_1');
 assert.equal(key(map,'KeyW',{metaKey:true}),null);
 assert(map.filter(b=>b.chord.includes('?')).every(b=>b.code===null));
}
assert.equal(key(mouse,'F12'),'ALL_WINDOW_CLOSE');
assert.equal(key(keyboard,'F12'),null); // Not present in the NKM source.
assert.throws(()=>parseKeyMap('[WINDOW]\nnot a binding'));
