import {loadNativeInput} from './native-input.js';
// These three uploaded CHAT entries are outside the native generic table.
const chatExtensions=new Set(['INPUT_CHAT','END_CHAT','WHISPER']);
export function parseKeyMap(text,native){
 const bindings=[];let section='';
 for(const raw of text.split(/\r?\n/)){
  const line=raw.trim();if(!line||line.startsWith(';'))continue;
  if(/^\[\w+\]$/.test(line)){section=line.slice(1,-1);continue;}
  const pair=line.match(/^(\w+)\s*=\s*(.+?)\s*$/);if(!pair)throw Error('Invalid keymap line: '+line);
  const [,action,chord]=pair,nativeIndex=native.action(section,action);
  const extension=section==='CHAT'&&chatExtensions.has(action);
  if(nativeIndex===undefined&&!extension)throw Error('Unknown RF command: '+section+'.'+action);
  // Match modifier prefixes instead of splitting on '+': NUM(+) is a key.
  let key=chord.toUpperCase(),parts=[];
  while(true){const prefix=key.match(/^(SHIFT|CTRL|ALT)\+/);if(!prefix)break;parts.push(prefix[1]);key=key.slice(prefix[0].length);}
  if(parts.some(p=>native.modifier(p)===undefined))throw Error('Unknown RF modifier');
  const record=native.key(key);
  const code=record?.code??(extension&&key==='ENTER'?'Enter':null);
  bindings.push({section,action,chord,code,nativeIndex:nativeIndex??null,virtualKey:record?.virtualKey??null,source:extension?'uploaded-chat':'native-table',ctrl:parts.includes('CTRL'),alt:parts.includes('ALT'),shift:parts.includes('SHIFT')});
 }
 return bindings;
}
export function resolveKey(bindings,e){
 // User-requested browser override: allow plain keys for Ctrl chords outside
 // text entry. This is not a claim that the native client ignores Ctrl.
 const matches=bindings.filter(b=>b.code===e.code&&!e.metaKey&&b.alt===!!e.altKey&&b.shift===!!e.shiftKey);
 return matches.sort((a,b)=>Number(b.section==='BEHAVIOR')-Number(a.section==='BEHAVIOR')||Number(b.section==='COMBAT')-Number(a.section==='COMBAT'))[0]?.action||null;
}
export async function loadKeyMaps(paths={mouse:'assets/keymaps/KeyMap.dat',keyboard:'assets/keymaps/KeyMap_NKM.dat'}){
 const modes={},native=await loadNativeInput();
 for(const [mode,file] of Object.entries(paths)){
  const r=await fetch(file);if(!r.ok)throw Error('Keymap gagal dimuat: '+file);
  modes[mode]=parseKeyMap(await r.text(),native);
 }
 modes.native=Object.freeze({sha256:native.sha256,commands:native.actionCount,keys:native.keyCount,mouseBindings:modes.mouse.filter(b=>b.nativeIndex!==null).length,keyboardBindings:modes.keyboard.filter(b=>b.nativeIndex!==null).length});
 return modes;
}
