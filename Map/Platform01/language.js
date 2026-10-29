let catalog;
export function setLanguage(data){
 if(!data?.phrases||data.count!==Object.keys(data.phrases).length)throw Error('Invalid Language.xlsx catalog');
 catalog=data;
}
export async function loadLanguage(){
 if(catalog)return catalog;
 const r=await fetch('assets/language.json');if(!r.ok)throw Error(`Language.xlsx: HTTP ${r.status}`);
 setLanguage(await r.json());return catalog;
}
export function t(id,...args){
 const value=catalog?.phrases[String(id)];if(typeof value!=='string')throw Error(`Language.xlsx: missing serial ${id}`);
 let index=0;
 const text=value.replace(/%%|%(?:\d+)?(?:\.(\d+))?([sdf])/g,(match,precision,type)=>{
  if(match==='%%')return '%';
  if(index>=args.length)throw Error(`Language.xlsx: missing argument for serial ${id}`);
  const arg=args[index++];return type==='s'?String(arg):type==='d'?String(Math.trunc(Number(arg))):Number(arg).toFixed(Number(precision??6));
 });
 if(index!==args.length)throw Error(`Language.xlsx: extra argument for serial ${id}`);
 return text.replaceAll('\\n','\n');
}
export const escapeHTML=value=>String(value).replace(/[&<>"']/g,c=>({'&':'&amp;','<':'&lt;','>':'&gt;','"':'&quot;',"'":'&#39;'}[c]));
export const L=(id,...args)=>`<span data-language-id="${id}">${escapeHTML(t(id,...args))}</span>`;
export const languageDiagnostics=()=>({source:catalog?.source,sha256:catalog?.sha256,count:catalog?.count});
