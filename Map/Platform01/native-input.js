// Windows VK -> browser physical key adapter. RF tokens and command ordinals
// come from the extracted native table, not this platform translation layer.
const browserKeys={9:'Tab',27:'Escape',32:'Space',33:'PageUp',34:'PageDown',35:'End',36:'Home',37:'ArrowLeft',38:'ArrowUp',39:'ArrowRight',40:'ArrowDown',44:'PrintScreen',45:'Insert',46:'Delete',106:'NumpadMultiply',107:'NumpadAdd',109:'NumpadSubtract',110:'NumpadDecimal',111:'NumpadDivide',186:'Semicolon',187:'Equal',188:'Comma',189:'Minus',190:'Period',191:'Slash',192:'Backquote',220:'Backslash',222:'Quote'};
export const CLIENT_SHA256='951e1056875c27f717bfb62d25ffc68d36337416e16d0b7ccc0f7c42b534d2c6';
export function browserCode(vk){
 if(vk>=48&&vk<=57)return 'Digit'+(vk-48);
 if(vk>=65&&vk<=90)return 'Key'+String.fromCharCode(vk);
 if(vk>=96&&vk<=105)return 'Numpad'+(vk-96);
 if(vk>=112&&vk<=123)return 'F'+(vk-111);
 return browserKeys[vk]??null;
}
export function createNativeInput(data){
 if(data?.binary_sha256!==CLIENT_SHA256||!Array.isArray(data.actions)||data.actions.length!==76||!Array.isArray(data.keys)||data.keys.length!==86||!Array.isArray(data.sections)||data.sections.length!==7||!Array.isArray(data.modifiers)||data.modifiers.length!==3)throw Error('Unsupported native input catalog');
 const keys=new Map(),actions=new Map(),modifiers=new Map();
 for(const [i,row] of data.keys.entries()){
  if(row.index!==i||typeof row.token!=='string'||keys.has(row.token)||!Number.isInteger(row.virtual_key)||!browserCode(row.virtual_key))throw Error('Invalid native key record');
  keys.set(row.token,Object.freeze({code:browserCode(row.virtual_key),virtualKey:row.virtual_key}));
 }
 let ordinal=0;
 for(const [i,section] of data.sections.entries()){
  if(section.index!==i||typeof section.name!=='string'||!Number.isInteger(section.count)||section.count<1)throw Error('Invalid native input section');
  for(let n=0;n<section.count;n++,ordinal++){
   const row=data.actions[ordinal],id=section.name+':'+row?.action;
   if(!row||row.index!==ordinal||row.section!==section.name||row.section_index!==i||row.section_ordinal!==n||typeof row.action!=='string'||actions.has(id))throw Error('Invalid native command record');
   actions.set(id,row.index);
  }
 }
 if(ordinal!==data.actions.length)throw Error('Native command count mismatch');
 const modifierCodes={SHIFT:16,CTRL:17,ALT:18};
 for(const row of data.modifiers){
  if(modifierCodes[row.token]!==row.virtual_key||modifiers.has(row.token))throw Error('Invalid native modifier');
  modifiers.set(row.token,row.virtual_key);
 }
 return Object.freeze({sha256:data.binary_sha256,key:token=>keys.get(token),action:(section,action)=>actions.get(section+':'+action),modifier:token=>modifiers.get(token),actionCount:actions.size,keyCount:keys.size});
}
export async function loadNativeInput(){
 const response=await fetch('assets/system/native-input.json');
 if(!response.ok)throw Error('Native input catalog gagal dimuat');
 return createNativeInput(await response.json());
}
