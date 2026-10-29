import {loadLanguage,t,L,escapeHTML as esc,languageDiagnostics} from './language.js';
import {renderHUD,ACTION_DEFS,EQUIPMENT} from './hud-layout.js';
const $ = id => document.getElementById(id);
const sprite = role => `<img data-sprite="${role}" alt="" draggable="false">`;

export async function createRFHUD({onPause,onFocus,onAction,onSetting,mapBackground}) {
  await loadLanguage();
  const ACTIONS=ACTION_DEFS.map(([a,id,icon])=>[a,t(id),icon]);
  const response = await fetch('assets/ui/manifest.json');
  if (!response.ok) throw Error(`Sprite UI gagal dimuat (${response.status})`);
  const manifest = await response.json(), images = {};
  await Promise.all(Object.entries(manifest).map(async ([role, info]) => {
    const image = new Image(); image.src = info.url;
    try { await image.decode(); } catch { throw Error(`Sprite UI gagal dimuat: ${role}`); }
    if (image.naturalWidth!==info.width || image.naturalHeight!==info.height) throw Error(`Dimensi sprite tidak cocok: ${role}`);
    images[role] = image;
  }));
  const root = document.createElement('section'); root.id = 'rfHUD'; root.hidden = true;root.classList.add('rf-belt-compact');
  root.setAttribute('aria-label','RF Online game HUD');
  root.innerHTML = renderHUD();
  document.body.append(root);
  const windows={other:$('rfWindow')};
  for(const kind of ['character','inventory']){
    const content=root.querySelector(`[data-panel="${kind}"]`),win=document.createElement('section');
    win.className='rf-window rf-native-window';win.id=kind==='character'?'rfCharacterWindow':'rfInventoryWindow';win.dataset.kind=kind;win.hidden=true;
    win.setAttribute('role','dialog');win.setAttribute('aria-label',t(kind==='character'?1125:1147));
    win.innerHTML=`<div class="rf-window-title"><button data-action="help" aria-label="${esc(t(108))}">${sprite('window-help')}</button><h2>${t(kind==='character'?1125:1147)}</h2><button data-close-window="${kind}" aria-label="${esc(t(2453))}">${sprite('window-close')}</button></div><div class="rf-window-content"></div>`;
    win.querySelector('.rf-window-content').append(content);root.append(win);windows[kind]=win;
  }
  for (const img of root.querySelectorAll('[data-sprite]')) img.src=manifest[img.dataset.sprite].url;
  let panel=null, name=t(0), labels=true, radarRange=80, visible=false, lastUI=0, lastState=null, systemOnly=false, noticeTimer, windowDrag=null, nextZ=6, activeBelt=1, editingSlot=null;
  const openPanels=new Set(), slots=new Map();
  const windowFor=kind=>windows[kind]||windows.other;
  const messages=[];
  const notify=text=>{ $('rfActionNotice').textContent=text; clearTimeout(noticeTimer); noticeTimer=setTimeout(()=>$('rfActionNotice').textContent='',2200); };
  function renderChat() {
    const log=$('rfChatLog'); log.replaceChildren();
    for (const message of messages.filter(m=>!systemOnly||m.system)) {
      const line=document.createElement('p'); line.className=message.system?'system':'local'; line.textContent=message.text; log.append(line);
    }
    log.scrollTop=log.scrollHeight;
  }
  function log(text,system=true){ messages.push({text,system}); if(messages.length>60)messages.shift(); renderChat(); }
  function closePanel(kind=panel){if(!kind)return;hideItem();windowFor(kind).hidden=true;openPanels.delete(kind);panel=[...openPanels].at(-1)||null;onFocus();}
  function closeAll(){for(const kind of [...openPanels])closePanel(kind);$('rfSlotEditor').hidden=true;editingSlot=null;}
  function showPanel(next){
    if(openPanels.has(next)){closePanel(next);return;}
    const win=windowFor(next);if(win===windows.other){for(const kind of [...openPanels])if(windowFor(kind)===win)closePanel(kind);}
    panel=next;openPanels.add(next);onFocus();win.hidden=false;win.dataset.kind=next;win.style.zIndex=++nextZ;
    if(win===windows.other){$('rfWindowTitle').textContent=t({map:58,settings:1129,help:108}[next]);win.querySelectorAll('[data-panel]').forEach(el=>el.hidden=el.dataset.panel!==next);}
    else win.querySelector('[data-panel]').hidden=false;
    win.querySelector('.rf-window-title button:last-child').focus({preventScroll:true});
  }
  for(const win of Object.values(windows)){
    win.addEventListener('pointerdown',()=>{panel=win.dataset.kind;openPanels.delete(panel);openPanels.add(panel);win.style.zIndex=++nextZ;});
    const title=win.querySelector('.rf-window-title');
    title.addEventListener('pointerdown',e=>{
      if(e.target.closest('button')||e.button!==0)return;
      e.preventDefault();onFocus();const box=win.getBoundingClientRect();
      windowDrag={win,x:e.clientX-box.x,y:e.clientY-box.y};win.style.transform='none';win.style.left=box.x+'px';win.style.top=box.y+'px';win.style.right='auto';title.setPointerCapture(e.pointerId);
    });
    title.addEventListener('pointermove',e=>{if(windowDrag?.win!==win)return;win.style.left=Math.max(0,Math.min(innerWidth-win.offsetWidth,e.clientX-windowDrag.x))+'px';win.style.top=Math.max(0,Math.min(innerHeight-45,e.clientY-windowDrag.y))+'px';});
    const stop=()=>windowDrag=null;title.addEventListener('pointerup',stop);title.addEventListener('pointercancel',stop);
  }
  root.querySelectorAll('[data-close-window]').forEach(b=>b.onclick=()=>closePanel(b.dataset.closeWindow));
  function selectBelt(row){activeBelt=row;root.querySelectorAll('[data-belt]').forEach(el=>el.classList.toggle('active',Number(el.dataset.belt)===row));$('rfNextBelt').textContent=row+' / 5';}
  function assignSlot(id,value){
    if(value)slots.set(id,value);else slots.delete(id);
    const button=root.querySelector(`[data-slot="${id}"]`),info=ACTIONS.find(a=>a[0]===value),n=Number(id.split(':')[1])+1;
    button.innerHTML=(info?`<img src="${manifest[info[2]].url}" alt="">`:'')+`<kbd>${n}</kbd>`;
    button.setAttribute('aria-label',`${id.split(':')[0]}:${n} ${info?info[1]:t(103)}`);button.title=info?info[1]:t(1127);
  }
  function useSlot(index){const value=slots.get(`${activeBelt}:${index}`);if(value)action(value);else notify(`${activeBelt}:${index+1} ${t(103)}`);}
  root.querySelectorAll('[data-belt-select]').forEach(b=>b.onclick=()=>selectBelt(Number(b.dataset.beltSelect)));
  root.querySelectorAll('[data-slot]').forEach(b=>{
    b.onclick=()=>{const id=b.dataset.slot;if(slots.has(id)){action(slots.get(id));return;}editingSlot=id;$('rfSlotAction').value='';$('rfSlotEditor').hidden=false;onFocus();$('rfSlotAction').focus();};
    b.oncontextmenu=e=>{e.preventDefault();assignSlot(b.dataset.slot,'');};
  });
  $('rfSlotDone').onclick=()=>{if(editingSlot)assignSlot(editingSlot,$('rfSlotAction').value);editingSlot=null;$('rfSlotEditor').hidden=true;};
  selectBelt(1);
  $('rfNextBelt').onclick=()=>selectBelt(activeBelt%5+1);
  function focusChat(){onFocus();root.querySelector('.rf-chat').classList.remove('collapsed');$('rfChatInput').focus();}
  function action(value){
    if(['inventory','character','map','settings','help'].includes(value))showPanel(value);
    else if(value==='chat')focusChat();
    else if(value==='labels'){labels=!labels;$('rfShowName').checked=labels;notify(t(1026)+': '+t(labels?104:105));}
    else {onFocus();const result=onAction(value);if(result){notify(result);log(t(1129)+' : '+result);}}
  }
  root.querySelectorAll('[data-action]').forEach(button=>button.onclick=()=>action(button.dataset.action));
  let hoveredSlot=null, tooltipPinned=false;
  function hideItem(){hoveredSlot=null;tooltipPinned=false;$('rfItemTooltip').hidden=true;}
  function showItem(slot,anchor,pinned=false){
    hoveredSlot=slot;tooltipPinned=pinned;
    const id=slot==='helmet'&&lastState?.headwear!=='helmet'?1170:EQUIPMENT[slot];
    $('rfItemName').textContent=t(id)+(id===1170?'':' · 171');$('rfItemType').textContent=t(id);$('rfItemType').dataset.languageId=String(id);
    const tip=$('rfItemTooltip');tip.hidden=false;tip.classList.toggle('pinned',pinned);tip.style.zIndex=String(++nextZ+100);
    const a=anchor.getBoundingClientRect(),w=tip.offsetWidth,h=tip.offsetHeight;
    const x=a.left-w-12>=8?a.left-w-12:Math.min(innerWidth-w-8,a.right+12);
    tip.style.left=Math.max(8,x)+'px';tip.style.top=Math.max(8,Math.min(innerHeight-h-8,a.top-20))+'px';
  }
  root.querySelectorAll('[data-equipment]').forEach(button=>{
    button.onpointerenter=e=>{if(e.pointerType!=='touch')showItem(button.dataset.equipment,button);};
    button.onpointerleave=()=>{if(!tooltipPinned)hideItem();};
    button.onfocus=()=>showItem(button.dataset.equipment,button);
    button.onblur=()=>{if(!tooltipPinned)hideItem();};
    button.onclick=()=>{if(matchMedia('(pointer:coarse)').matches){showItem(button.dataset.equipment,button,true);return;}if(button.dataset.equipment==='helmet')action('headwear');showItem(button.dataset.equipment,button);};
  });
  $('rfItemTooltipClose').onclick=hideItem;
  root.querySelectorAll('[data-character-section]').forEach(button=>button.onclick=()=>{
    const details=$('rfInfo-'+button.dataset.characterSection);details.open=true;
    const content=$('rfCharacterWindow').querySelector('.rf-window-content');content.scrollTop=details.offsetTop-content.offsetTop;
  });
  $('rfWindowClose').onclick=()=>closePanel(windows.other.dataset.kind);$('rfPause').onclick=onPause;
  $('rfNoticeClose').onclick=()=>$('rfNotice').hidden=true;
  $('rfChatCollapse').onclick=()=>root.querySelector('.rf-chat').classList.toggle('collapsed');
  $('rfAllChat').onclick=()=>{systemOnly=false;$('rfAllChat').classList.add('active');$('rfSystemChat').classList.remove('active');renderChat();};
  $('rfSystemChat').onclick=()=>{systemOnly=true;$('rfSystemChat').classList.add('active');$('rfAllChat').classList.remove('active');renderChat();};
  $('rfChatInput').addEventListener('focus',onFocus);
  $('rfChatForm').onsubmit=e=>{
    e.preventDefault();const input=$('rfChatInput'),text=input.value.trim().slice(0,160);if(!text){input.blur();return;}
    if(text==='/clear'){messages.length=0;renderChat();}
    else if(text==='/help')showPanel('help');
    else if(text==='/pos'&&lastState)log('Platform01 '+lastState.player.map(v=>v.toFixed(1)).join(' / '));
    else log(`[${t(1130)}] ${name} : ${text}`,false);
    input.value='';input.blur();
  };
  $('rfNameInput').oninput=()=>{name=$('rfNameInput').value.trim().slice(0,16)||t(0);$('rfPlayerName').textContent=name;$('rfOverheadName').textContent=name;};
  $('rfCameraDistance').oninput=()=>{const v=Number($('rfCameraDistance').value);$('rfCameraValue').textContent=v+' m';onSetting('distance',v);};
  $('rfBeltRows').onchange=()=>root.classList.toggle('rf-belt-compact',$('rfBeltRows').value==='1');
  $('rfUIScale').onchange=()=>{root.style.setProperty('--ui-user-scale',$('rfUIScale').value);};
  $('rfSky').onchange=()=>onSetting('sky',Number($('rfSky').value));
  $('rfControlMode').onchange=()=>onSetting('control-mode',$('rfControlMode').value);
  $('rfShowName').onchange=()=>labels=$('rfShowName').checked;
  $('rfRadarPlus').onclick=()=>radarRange=Math.max(25,radarRange-15);$('rfRadarMinus').onclick=()=>radarRange=Math.min(160,radarRange+15);
  // Keep all HUD interactions outside the scene's mouse/keyboard controls.
  root.addEventListener('pointerdown',e=>{if(e.target.closest('button,input,select,.rf-window,.rf-chat'))onFocus();});
  function drawRadar(state){
    const ctx=$('rfRadarCanvas').getContext('2d');ctx.clearRect(0,0,186,186);ctx.save();ctx.scale(2,2);
    ctx.drawImage(images['radar-face'],0,0);ctx.beginPath();ctx.arc(46.5,46.5,39,0,Math.PI*2);ctx.clip();
    const px=(state.player[0]+145)/290*240,pz=(state.player[2]+125)/250*190,scale=80/radarRange;
    ctx.globalAlpha=.7;ctx.drawImage(mapBackground,46.5-px*scale,46.5-pz*scale,240*scale,190*scale);ctx.globalAlpha=1;
    ctx.translate(46.5,46.5);ctx.rotate(Math.PI-state.yaw);ctx.drawImage(images['radar-cone'],-46.5,-46.5);ctx.fillStyle='#c8ffe0';ctx.beginPath();ctx.moveTo(0,-4);ctx.lineTo(-3,3);ctx.lineTo(3,3);ctx.closePath();ctx.fill();ctx.restore();
    if(openPanels.has('map')){
      const c=$('rfFullMap').getContext('2d');c.fillStyle='#10201c';c.fillRect(0,0,480,380);c.drawImage(mapBackground,0,0,480,380);
      c.save();c.translate(px*2,pz*2);c.rotate(Math.PI-state.yaw);c.fillStyle='#b9ffd8';c.beginPath();c.moveTo(0,-7);c.lineTo(-5,5);c.lineTo(5,5);c.closePath();c.fill();c.restore();
      $('rfFullMapCoords').textContent='Platform01 : '+state.player.map(v=>v.toFixed(1)).join(' / ');
    }
  }
  return {
    setVisible(value){visible=value;root.hidden=!value;document.body.classList.toggle('rf-playing',value);if(!value){$('rfChatInput').blur();hideItem();closeAll();}},
    get interacting(){return !!windowDrag||editingSlot!==null||root.contains(document.activeElement)&&['INPUT','SELECT','TEXTAREA'].includes(document.activeElement.tagName);},
    notify,
    setControlMode(mode){const id=mode==='keyboard'?2021:2022;$('rfInputMode').textContent=t(id)+' [H]';$('rfInputMode').dataset.languageId=id;$('rfControlMode').value=mode;$('rfSessionHint').textContent=mode==='keyboard'?'W A S D · Q E':'↑ ← ↓ →';$('rfNoticeText').textContent=t(id);log(t(1129)+' : '+t(id));},
    dispatch(command){
      const mapped={INVENTORY:'inventory',AVATAR_INFO_WINDOW:'character',MINIMAP:'map',RADAR_WINDOW:'map',OPTION_WINDOW:'settings',COMBAT_MODE:'combat',MOVE_MODE:'run',HIDE_CHAR_NAME:'labels'}[command];
      if(mapped){action(mapped);return;}
      if(command==='ALL_WINDOW_CLOSE'){closeAll();return;}
      if(command==='HIDE_UI'){root.classList.toggle('rf-ui-hidden');return;}
      if(command==='CHANGE_BELT_KEY'){selectBelt(activeBelt%5+1);return;}
      if(command.startsWith('SLOT_')){useSlot(Number(command.slice(5))-1);return;}
      if(command==='QUIT'){onPause();return;}
      notify(t(1718));
    },
    handleKey(e){
      if(!visible)return false;
      if(e.code==='Escape'&&tooltipPinned){hideItem();e.preventDefault();return true;}
      const typing=['INPUT','SELECT','TEXTAREA'].includes(e.target.tagName);
      if(e.code==='Escape'&&editingSlot!==null){editingSlot=null;$('rfSlotEditor').hidden=true;e.target.blur();return true;}
      if(e.code==='Escape'&&(typing||panel)){e.preventDefault();if(typing)e.target.blur();else closePanel();return true;}
      if(typing)return true;
      if(e.code==='Enter'){e.preventDefault();focusChat();return true;}
      return false;
    },
    update(state){
      lastState=state;if(!visible)return;
      const plate=$('rfNameplate');plate.hidden=!labels||!state.screen;
      if(state.screen){plate.style.left=state.screen[0]+'px';plate.style.top=state.screen[1]+'px';}
      $('rfMoveTarget').hidden=!state.targetScreen;if(state.targetScreen){$('rfMoveTarget').style.left=state.targetScreen[0]+'px';$('rfMoveTarget').style.top=state.targetScreen[1]+'px';}
      const now=performance.now();if(now-lastUI<100)return;lastUI=now;
      const sp=Math.ceil(state.stamina);$('rfSPText').textContent=sp+' / 100';$('rfCharacterSP').textContent=sp+' / 100';
      root.querySelector('.rf-sp img').style.clipPath=`inset(0 ${100-sp}% 0 0)`;
      root.querySelector('#rfNameplate img[data-sprite="overhead-sp"]').style.clipPath=`inset(0 ${100-sp}% 0 0)`;
      $('rfMotion').textContent=t(state.combat?1124:1123);
      if(hoveredSlot){const id=hoveredSlot==='helmet'&&state.headwear!=='helmet'?1170:EQUIPMENT[hoveredSlot];$('rfItemName').textContent=t(id)+(id===1170?'':' · 171');$('rfItemType').textContent=t(id);$('rfItemType').dataset.languageId=id;}
      $('rfHeadwearLabel').textContent=t(state.headwear==='helmet'?33:1170);$('rfStanceLabel').textContent=t(state.combat?1124:1123);
      $('rfRadarCoords').textContent=Math.round(state.player[0])+'  '+Math.round(state.player[2]);
      $('rfFPS').textContent='FPS: '+Math.round(state.fps);$('rfSessionTime').textContent=String(Math.floor(state.elapsed/60)).padStart(2,'0')+':'+String(Math.floor(state.elapsed%60)).padStart(2,'0');
      root.querySelectorAll('[data-action="combat"]').forEach(b=>b.classList.toggle('selected',state.combat));
      root.querySelectorAll('[data-action="run"]').forEach(b=>b.classList.toggle('selected',state.runMode));
      drawRadar(state);
    },
    syncDistance(value){$('rfCameraDistance').value=value;$('rfCameraValue').textContent=value.toFixed(1)+' m';},
    diagnostics:()=>({visible,panel,openPanels:[...openPanels],name,labels,radarRange,messages:messages.length,roles:Object.keys(images).length,language:languageDiagnostics(),tooltip:hoveredSlot,activeBelt,assignedSlots:slots.size}),
  };
}
