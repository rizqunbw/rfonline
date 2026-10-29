const ACTIONS = [
  ['combat','Mode tempur','icon-combat'], ['run','Jalan / lari','icon-run'], ['headwear','Rambut / helm','icon-headwear'],
  ['inventory','Inventory','icon-inventory'], ['character','Karakter','icon-character'], ['map','Peta sektor','icon-map'],
  ['chat','Chat lokal','icon-chat'], ['help','Panduan','icon-help'], ['labels','Nama karakter','icon-target'], ['settings','Pengaturan','icon-settings'],
];
const $ = id => document.getElementById(id);
const sprite = role => `<img data-sprite="${role}" alt="" draggable="false">`;

export async function createRFHUD({onPause,onFocus,onAction,onSetting,mapBackground}) {
  const response = await fetch('assets/ui/manifest.json');
  if (!response.ok) throw Error(`Sprite UI gagal dimuat (${response.status})`);
  const manifest = await response.json(), images = {};
  await Promise.all(Object.entries(manifest).map(async ([role, info]) => {
    const image = new Image(); image.src = info.url;
    try { await image.decode(); } catch { throw Error(`Sprite UI gagal dimuat: ${role}`); }
    if (image.naturalWidth!==info.width || image.naturalHeight!==info.height) throw Error(`Dimensi sprite tidak cocok: ${role}`);
    images[role] = image;
  }));
  const root = document.createElement('section'); root.id = 'rfHUD'; root.hidden = true;
  root.setAttribute('aria-label','RF Online game HUD');
  root.innerHTML = `
    <section class="rf-status" aria-label="Status karakter">
      ${sprite('status-frame')}${sprite('level-ring')}
      <strong class="rf-level" title="Level prototype lokal">1</strong>
      <div class="rf-vital rf-hp">${sprite('hp')}<span>100 / 100</span></div>
      <div class="rf-vital rf-fp">${sprite('fp')}<span>100 / 100</span></div>
      <div class="rf-vital rf-sp">${sprite('sp')}<span id="rfSPText">100 / 100</span></div>
      <div class="rf-identity"><b id="rfPlayerName">Bellato</b><span>Lv. 1 · Female</span></div>
    </section>
    <div class="rf-sector-info">${sprite('icon-emblem')}<div><span>⚔ KILL: 0</span><span>☠ DEATH: 0</span><span>▴ Temporary Point: 0</span><span>▴ Certain Point: 0</span><span>▴ Gold Point: 0</span></div></div>
    <aside class="rf-notice" id="rfNotice"><span>Selamat datang di White Hole.</span><button aria-label="Tutup pemberitahuan" id="rfNoticeClose">×</button></aside>
    <section class="rf-radar" aria-label="Radar sektor">
      <canvas id="rfRadarCanvas" width="186" height="186"></canvas>${sprite('radar-frame')}
      <b class="rf-area">White Hole</b><span class="rf-radar-coords" id="rfRadarCoords">0 / 10</span>
      <button class="rf-radar-plus" id="rfRadarPlus" aria-label="Perbesar radar">${sprite('radar-plus')}</button>
      <button class="rf-radar-minus" id="rfRadarMinus" aria-label="Perkecil radar">${sprite('radar-minus')}</button>
      <button class="rf-radar-map" data-action="map" aria-label="Buka peta sektor">${sprite('icon-map')}</button>
      <button class="rf-radar-close" data-action="settings" aria-label="Pengaturan radar">⚙</button>
    </section>
    <div class="rf-nameplate" id="rfNameplate"><div>${sprite('overhead-hp')}${sprite('overhead-fp')}${sprite('overhead-sp')}</div><strong id="rfOverheadName">Bellato</strong></div>
    <div id="rfMoveTarget" hidden aria-label="Tujuan berjalan"></div>
    <section class="rf-chat" aria-label="Chat lokal">
      <div class="rf-chat-tabs"><button class="active" id="rfAllChat">Semua</button><button id="rfSystemChat">Sistem</button><span>LOKAL</span><button id="rfChatCollapse" aria-label="Lipat chat">−</button></div>
      <div id="rfChatLog" role="log" aria-label="Riwayat chat" aria-live="polite"></div>
      <form id="rfChatForm"><label for="rfChatInput">[ Lokal ]</label><input id="rfChatInput" maxlength="160" autocomplete="off" placeholder="Enter untuk chat…"><button aria-label="Kirim pesan lokal">↵</button></form>
    </section>
    <aside class="rf-session"><span class="rf-local-dot"></span> MODE LOKAL <span id="rfSessionTime">00:00</span><p><button data-action="input-mode" id="rfInputMode">Mouse mode [H]</button></p><p id="rfSessionHint">Klik tanah untuk berjalan</p><p id="rfMotion">Berdiri</p></aside>
    <nav class="rf-bottom" aria-label="Hotbar dan menu">
      ${sprite('footer')}
      <div class="rf-exp"><span>0.000%</span></div><div class="rf-fps" id="rfFPS">FPS: —</div>
      <div class="rf-quick"><button data-action="labels" title="Nama karakter">${sprite('icon-target')}</button><button data-action="run" title="Jalan / lari">${sprite('icon-walk')}</button><button data-action="combat" title="Mode tempur">${sprite('icon-combat')}</button></div>
      <div class="rf-belt-stack">${[5,4,3,2,1].map(row=>`<div class="rf-belt-row" data-belt="${row}"><button class="rf-belt-select" data-belt-select="${row}" aria-label="Aktifkan hotbar ${row}">${sprite('belt-handle')}<span>${row}</span></button><div class="rf-hotkeys">${Array.from({length:10},(_,i)=>`<button data-slot="${row}:${i}" aria-label="Hotbar ${row} slot ${i+1}: kosong" title="Pilih aksi untuk slot ${i+1}"><kbd>${i+1}</kbd></button>`).join('')}</div></div>`).join('')}</div>
      <div class="rf-menus"><button data-action="character" aria-label="Karakter (C)" title="Karakter [C]">${sprite('icon-character')}</button><button data-action="inventory" aria-label="Inventory (I)" title="Inventory [I]">${sprite('icon-inventory')}</button><button data-action="settings" aria-label="Pengaturan (O)" title="Pengaturan [O]">${sprite('icon-settings')}</button></div>
      <button id="rfPause" class="rf-menu-button">MENU <small>Esc</small></button>
      <button id="rfNextBelt" aria-label="Ganti hotbar aktif">Bar 1 / 5</button>
    </nav>
    <div class="rf-tooltip" id="rfActionNotice" role="status"></div>
    <div id="rfSlotEditor" hidden><label>Isi hotbar<select id="rfSlotAction"><option value="">Kosong</option>${ACTIONS.map(([action,label])=>`<option value="${action}">${label}</option>`).join('')}</select></label><button id="rfSlotDone">OK</button></div>
    <section class="rf-window" id="rfWindow" hidden role="dialog" aria-modal="false" aria-labelledby="rfWindowTitle">
      <div class="rf-window-title"><h2 id="rfWindowTitle"></h2><button id="rfWindowClose" aria-label="Tutup panel">${sprite('close')}</button></div>
      <div class="rf-window-content">
        <section data-panel="inventory" hidden>
          <div class="rf-inventory-layout"><div class="rf-equipment"><div class="rf-equipment-art">${sprite('inventory-equipment')}
            ${[['helmet',80,31,'Kepala'],['upper',80,103,'Upper 171'],['lower',80,173,'Lower 171'],['gloves',11,103,'Gloves 171'],['boots',80,244,'Shoes 171']].map(([slot,x,y,label])=>`<button style="left:${x}px;top:${y}px" data-equipment="${slot}" title="${label}" aria-label="${label}">${sprite('equip-'+slot)}</button>`).join('')}
          </div><span class="rf-equipment-label">BELLATO · ARMOR 171</span></div>
          <div class="rf-bag"><h3>Bag 1 <span>0 Dalant</span></h3><div class="rf-bag-grid" aria-label="20 slot tas kosong">${Array.from({length:20},(_,i)=>`<span aria-label="Slot ${i+1}: kosong"></span>`).join('')}</div><div class="rf-item-detail" id="rfItemDetail">Pilih perlengkapan untuk melihat detail.</div><button class="rf-button" data-action="headwear">Ganti rambut / helm</button></div></div>
        </section>
        <section data-panel="character" hidden><div class="rf-character-heading">${sprite('icon-emblem')}<div><h3>Bellato Female</h3><p>Level 1 · Armor 171</p></div></div>
          <label class="rf-field">Name:<input id="rfNameInput" maxlength="16" value="Bellato"></label>
          <details open><summary>General Info</summary><dl class="rf-stat-list"><dt>Race</dt><dd>Bellato</dd><dt>Gender</dt><dd>F</dd><dt>Level</dt><dd>1</dd><dt>Class</dt><dd>—</dd><dt>Guild</dt><dd>—</dd></dl></details>
          <details open><summary>Status Info</summary><dl class="rf-stat-list"><dt>HP</dt><dd>100 / 100</dd><dt>FP</dt><dd>100 / 100</dd><dt>SP</dt><dd id="rfCharacterSP">100 / 100</dd></dl></details><details open><summary>Equipment</summary><dl class="rf-stat-list"><dt>Head</dt><dd id="rfHeadwearLabel">Rambut default</dd><dt>Mode</dt><dd id="rfStanceLabel">Damai</dd></dl></details>
          <button class="rf-button" data-action="headwear">Ganti rambut / helm</button><a class="rf-button" href="character.html">Lihat model karakter ↗</a><p class="rf-muted">Stat awal mode lokal. Combat, EXP, dan progres server belum aktif.</p>
        </section>
        <section data-panel="map" hidden><h3>White Hole · Platform01</h3><canvas id="rfFullMap" width="480" height="380" aria-label="Peta Platform01 dan posisi karakter"></canvas><p id="rfFullMapCoords"></p><p class="rf-muted">Segitiga menunjukkan posisi dan arah pandangmu.</p></section>
        <section data-panel="settings" hidden>
          <label class="rf-field">Kontrol [H]<select id="rfControlMode"><option value="mouse">Mouse mode</option><option value="keyboard">Keyboard mode</option></select></label>
          <label class="rf-field">Jarak kamera <output id="rfCameraValue">8 m</output><input id="rfCameraDistance" type="range" min="4.5" max="14" step=".5" value="8"></label>
          <label class="rf-field">Ukuran HUD<select id="rfUIScale"><option value=".9">Kecil</option><option value="1" selected>Normal</option><option value="1.15">Besar</option></select></label>
          <label class="rf-field">Langit<select id="rfSky"><option value="0">Platform01 Sky 1</option><option value="1">Platform01 Sky 2</option></select></label>
          <label class="rf-check"><input id="rfShowName" type="checkbox" checked>Tampilkan nama karakter</label>
          <button class="rf-button" data-action="help">Lihat kontrol</button>
        </section>
        <section data-panel="help" hidden><h3>Kontrol lapangan</h3><dl class="rf-stat-list"><dt>H</dt><dd>Mouse / keyboard mode</dd><dt>Mouse mode</dt><dd>Klik tanah / tombol panah</dd><dt>Keyboard mode</dt><dd>W A S D gerak · Q E kamera</dd><dt>W / N</dt><dd>Jalan-lari (mouse / keyboard)</dd><dt>A / ;</dt><dd>Pose tempur (mouse / keyboard)</dd><dt>Seret kanan / scroll</dt><dd>Kamera / zoom</dd><dt>I / C / M / O</dt><dd>Inventory / karakter / peta / opsi</dd><dt>F1–F10 / 1–0</dt><dd>Slot hotbar aktif</dd><dt>\\</dt><dd>Ganti bar aktif</dd><dt>Enter / Esc</dt><dd>Chat / tutup panel</dd><dt>Alt+H / Backquote</dt><dd>Sembunyikan UI / nama</dd></dl><p class="rf-muted">Ctrl pada tabel diterima sebagai prefix opsional saat chat tidak aktif. Isi slot hotbar dengan klik slot kosong; klik kanan untuk mengosongkan. Chat dan stat bersifat lokal. Serangan, item, dan layanan server belum terhubung. Binding bertanda ? belum ditentukan oleh file sumber.</p></section>
      </div>
    </section>`;
  document.body.append(root);
  const windows={other:$('rfWindow')};
  for(const kind of ['character','inventory']){
    const content=root.querySelector(`[data-panel="${kind}"]`),win=document.createElement('section');
    win.className='rf-window rf-native-window';win.id=kind==='character'?'rfCharacterWindow':'rfInventoryWindow';win.dataset.kind=kind;win.hidden=true;
    win.setAttribute('role','dialog');win.setAttribute('aria-label',kind==='character'?'Character':'Inventory');
    win.innerHTML=`<div class="rf-window-title"><button data-action="help" aria-label="Panduan ${kind}">${sprite('window-help')}</button><h2>${kind==='character'?'Character':'Inventory'}</h2><button data-close-window="${kind}" aria-label="Tutup ${kind}">${sprite('window-close')}</button></div><div class="rf-window-content"></div>`;
    win.querySelector('.rf-window-content').append(content);root.append(win);windows[kind]=win;
  }
  for (const img of root.querySelectorAll('[data-sprite]')) img.src=manifest[img.dataset.sprite].url;
  let panel=null, name='Bellato', labels=true, radarRange=80, visible=false, lastUI=0, lastState=null, systemOnly=false, noticeTimer, windowDrag=null, nextZ=6, activeBelt=1, editingSlot=null;
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
  function closePanel(kind=panel){if(!kind)return;windowFor(kind).hidden=true;openPanels.delete(kind);panel=[...openPanels].at(-1)||null;onFocus();}
  function closeAll(){for(const kind of [...openPanels])closePanel(kind);$('rfSlotEditor').hidden=true;editingSlot=null;}
  function showPanel(next){
    if(openPanels.has(next)){closePanel(next);return;}
    const win=windowFor(next);if(win===windows.other){for(const kind of [...openPanels])if(windowFor(kind)===win)closePanel(kind);}
    panel=next;openPanels.add(next);onFocus();win.hidden=false;win.dataset.kind=next;win.style.zIndex=++nextZ;
    if(win===windows.other){$('rfWindowTitle').textContent={map:'World Map',settings:'System',help:'Guide'}[next];win.querySelectorAll('[data-panel]').forEach(el=>el.hidden=el.dataset.panel!==next);}
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
  function selectBelt(row){activeBelt=row;root.querySelectorAll('[data-belt]').forEach(el=>el.classList.toggle('active',Number(el.dataset.belt)===row));$('rfNextBelt').textContent='Bar '+row+' / 5';}
  function assignSlot(id,value){
    if(value)slots.set(id,value);else slots.delete(id);
    const button=root.querySelector(`[data-slot="${id}"]`),info=ACTIONS.find(a=>a[0]===value),n=Number(id.split(':')[1])+1;
    button.innerHTML=(info?`<img src="${manifest[info[2]].url}" alt="">`:'')+`<kbd>${n}</kbd>`;
    button.setAttribute('aria-label',`Hotbar ${id.split(':')[0]} slot ${n}: ${info?info[1]:'kosong'}`);button.title=info?info[1]:'Klik untuk isi slot';
  }
  function useSlot(index){const value=slots.get(`${activeBelt}:${index}`);if(value)action(value);else notify(`Hotbar ${activeBelt}, slot ${index+1} kosong`);}
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
    else if(value==='labels'){labels=!labels;$('rfShowName').checked=labels;notify(labels?'Nama karakter ditampilkan':'Nama karakter disembunyikan');}
    else {onFocus();const result=onAction(value);if(result){notify(result);log('System : '+result);}}
  }
  root.querySelectorAll('[data-action]').forEach(button=>button.onclick=()=>action(button.dataset.action));
  root.querySelectorAll('[data-equipment]').forEach(button=>button.onclick=()=>{
    $('rfItemDetail').textContent={helmet:'Kepala: rambut default atau helm armor 171. Gunakan tombol ganti untuk memilih.',upper:'Upper 171 · Bellato Female · Sedang dipakai.',lower:'Lower 171 · Bellato Female · Sedang dipakai.',gloves:'Gloves 171 · Bellato Female · Sedang dipakai.',boots:'Shoes 171 · Bellato Female · Sedang dipakai.'}[button.dataset.equipment];
    notify($('rfItemDetail').textContent);if(button.dataset.equipment==='helmet')action('headwear');
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
    else if(text==='/help')log('System : H ganti mode · Mouse: klik tanah / panah · Keyboard: WASD gerak, QE kamera · I inventory · C karakter.');
    else if(text==='/pos'&&lastState)log('System : Platform01 '+lastState.player.map(v=>v.toFixed(1)).join(' / '));
    else log(`[Lokal] ${name} : ${text}`,false);
    input.value='';input.blur();
  };
  $('rfNameInput').oninput=()=>{name=$('rfNameInput').value.trim().slice(0,16)||'Bellato';$('rfPlayerName').textContent=name;$('rfOverheadName').textContent=name;};
  $('rfCameraDistance').oninput=()=>{const v=Number($('rfCameraDistance').value);$('rfCameraValue').textContent=v+' m';onSetting('distance',v);};
  $('rfUIScale').onchange=()=>{root.style.setProperty('--ui-user-scale',$('rfUIScale').value);};
  $('rfSky').onchange=()=>onSetting('sky',Number($('rfSky').value));
  $('rfControlMode').onchange=()=>onSetting('control-mode',$('rfControlMode').value);
  $('rfShowName').onchange=()=>labels=$('rfShowName').checked;
  $('rfRadarPlus').onclick=()=>radarRange=Math.max(25,radarRange-15);$('rfRadarMinus').onclick=()=>radarRange=Math.min(160,radarRange+15);
  // Keep all HUD interactions outside the scene's mouse/keyboard controls.
  root.addEventListener('pointerdown',e=>{if(e.target.closest('button,input,select,.rf-window,.rf-chat'))onFocus();});
  log('System : Selamat datang di White Hole.');
  log('System : Mode lokal · HP/FP dan level memakai stat awal prototype.');
  log('System : Mouse mode. Klik tanah untuk berjalan, H untuk keyboard mode.');
  log('System : Enter untuk chat lokal. Ketik /help untuk kontrol.');
  function drawRadar(state){
    const ctx=$('rfRadarCanvas').getContext('2d');ctx.clearRect(0,0,186,186);ctx.save();ctx.scale(2,2);
    ctx.drawImage(images['radar-face'],0,0);ctx.beginPath();ctx.arc(46.5,46.5,39,0,Math.PI*2);ctx.clip();
    const px=(state.player[0]+145)/290*240,pz=(state.player[2]+125)/250*190,scale=80/radarRange;
    ctx.globalAlpha=.7;ctx.drawImage(mapBackground,46.5-px*scale,46.5-pz*scale,240*scale,190*scale);ctx.globalAlpha=1;
    ctx.translate(46.5,46.5);ctx.rotate(Math.PI-state.yaw);ctx.drawImage(images['radar-cone'],-46.5,-46.5);ctx.fillStyle='#c8ffe0';ctx.beginPath();ctx.moveTo(0,-4);ctx.lineTo(-3,3);ctx.lineTo(3,3);ctx.closePath();ctx.fill();ctx.restore();
    if(openPanels.has('map')){
      const c=$('rfFullMap').getContext('2d');c.fillStyle='#10201c';c.fillRect(0,0,480,380);c.drawImage(mapBackground,0,0,480,380);
      c.save();c.translate(px*2,pz*2);c.rotate(Math.PI-state.yaw);c.fillStyle='#b9ffd8';c.beginPath();c.moveTo(0,-7);c.lineTo(-5,5);c.lineTo(5,5);c.closePath();c.fill();c.restore();
      $('rfFullMapCoords').textContent='Posisi : '+state.player.map(v=>v.toFixed(1)).join(' / ');
    }
  }
  return {
    setVisible(value){visible=value;root.hidden=!value;document.body.classList.toggle('rf-playing',value);if(!value){$('rfChatInput').blur();closeAll();}},
    get interacting(){return !!windowDrag||editingSlot!==null||root.contains(document.activeElement)&&['INPUT','SELECT','TEXTAREA'].includes(document.activeElement.tagName);},
    notify,
    setControlMode(mode){$('rfInputMode').textContent=(mode==='keyboard'?'Keyboard mode':'Mouse mode')+' [H]';$('rfControlMode').value=mode;$('rfSessionHint').textContent=mode==='keyboard'?'WASD gerak · QE kamera':'Klik tanah / panah untuk berjalan';log('System : '+(mode==='keyboard'?'Keyboard mode':'Mouse mode'));},
    dispatch(command){
      const mapped={INVENTORY:'inventory',AVATAR_INFO_WINDOW:'character',MINIMAP:'map',RADAR_WINDOW:'map',OPTION_WINDOW:'settings',COMBAT_MODE:'combat',MOVE_MODE:'run',HIDE_CHAR_NAME:'labels'}[command];
      if(mapped){action(mapped);return;}
      if(command==='ALL_WINDOW_CLOSE'){closeAll();return;}
      if(command==='HIDE_UI'){root.classList.toggle('rf-ui-hidden');return;}
      if(command==='CHANGE_BELT_KEY'){selectBelt(activeBelt%5+1);return;}
      if(command.startsWith('SLOT_')){useSlot(Number(command.slice(5))-1);return;}
      if(command==='QUIT'){onPause();return;}
      notify(command.replaceAll('_',' ')+' belum tersedia di mode lokal');
    },
    handleKey(e){
      if(!visible)return false;
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
      $('rfMotion').textContent={idle:'Berdiri',walk:'Berjalan',run:'Berlari',combat:'Mode tempur'}[state.clip]||'Berdiri';
      $('rfHeadwearLabel').textContent=state.headwear==='helmet'?'Helm armor 171':'Rambut default';$('rfStanceLabel').textContent=state.combat?'Tempur':'Damai';
      $('rfRadarCoords').textContent=Math.round(state.player[0])+'  '+Math.round(state.player[2]);
      $('rfFPS').textContent='FPS: '+Math.round(state.fps);$('rfSessionTime').textContent=String(Math.floor(state.elapsed/60)).padStart(2,'0')+':'+String(Math.floor(state.elapsed%60)).padStart(2,'0');
      root.querySelectorAll('[data-action="combat"]').forEach(b=>b.classList.toggle('selected',state.combat));
      root.querySelectorAll('[data-action="run"]').forEach(b=>b.classList.toggle('selected',state.runMode));
      drawRadar(state);
    },
    syncDistance(value){$('rfCameraDistance').value=value;$('rfCameraValue').textContent=value.toFixed(1)+' m';},
    diagnostics:()=>({visible,panel,openPanels:[...openPanels],name,labels,radarRange,messages:messages.length,roles:Object.keys(images).length,activeBelt,assignedSlots:slots.size}),
  };
}
