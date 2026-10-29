const names={LEFT:'ArrowLeft',RIGHT:'ArrowRight',UP:'ArrowUp',DOWN:'ArrowDown',ESC:'Escape',ENTER:'Enter',SPACE:'Space',PGUP:'PageUp',PGDN:'PageDown',SNAPSHOT:'PrintScreen',TAB:'Tab',";":'Semicolon',"'":'Quote',',':'Comma','.':'Period','/':'Slash','\\':'Backslash','`':'Backquote'};
export function parseKeyMap(text){
 const bindings=[];let section='';
 for(const raw of text.split(/\r?\n/)){
  const line=raw.trim();if(!line||line.startsWith(';'))continue;
  if(/^\[\w+\]$/.test(line)){section=line.slice(1,-1);continue;}
  const pair=line.match(/^(\w+)\s*=\s*(.+?)\s*$/);if(!pair)throw Error('Invalid keymap line: '+line);
  const [,action,chord]=pair,parts=chord.toUpperCase().split('+'),key=parts.pop();
  const code=names[key]||(/^[A-Z]$/.test(key)?'Key'+key:/^[0-9]$/.test(key)?'Digit'+key:/^F([1-9]|1[0-2])$/.test(key)?key:null);
  bindings.push({section,action,chord,code,ctrl:parts.includes('CTRL'),alt:parts.includes('ALT'),shift:parts.includes('SHIFT')});
 }
 return bindings;
}
export function resolveKey(bindings,e){
 // Ctrl in these client tables is a command prefix. Outside text entry, accept
 // the plain key as requested; keep Alt/Shift explicit and ignore unknown '?'.
 const matches=bindings.filter(b=>b.code===e.code&&!e.metaKey&&b.alt===!!e.altKey&&b.shift===!!e.shiftKey);
 return matches.sort((a,b)=>Number(b.section==='BEHAVIOR')-Number(a.section==='BEHAVIOR')||Number(b.section==='COMBAT')-Number(a.section==='COMBAT'))[0]?.action||null;
}
export async function loadKeyMaps(){
 const modes={};
 for(const [mode,file] of [['mouse','KeyMap.dat'],['keyboard','KeyMap_NKM.dat']]){
  const r=await fetch('assets/keymaps/'+file);if(!r.ok)throw Error('Keymap gagal dimuat: '+file);
  modes[mode]=parseKeyMap(await r.text());
 }
 return modes;
}
