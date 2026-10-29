import {createSkyRenderer} from './sky.js';
import {createTerrainRenderer} from './terrain.js';
import {createRFHUD} from './rf-hud.js';
import {loadKeyMaps,resolveKey} from './keymap.js';
import {loadLanguage,t,languageDiagnostics} from './language.js';
const $ = id => document.getElementById(id);
const canvas = $('world');
const gl = canvas.getContext('webgl', {antialias:true, alpha:false});
let running = false, started = false, completed = false, last = 0, elapsed = 0, skyRenderer, terrainRenderer;
let yaw = Math.PI, pitch = -0.15, camera = [0, 35, 105], points, manifest, beaconGPU;
const characterMode = new URLSearchParams(location.search).get('character') !== '0';
document.body.classList.toggle('rf-mode',characterMode);
let rfHUD, cameraDistance=8, combatStance=false, runMode=false, stamina=100, exhausted=false, fps=60;
let headwear=new URLSearchParams(location.search).get('headwear')==='helmet'?'helmet':'hair';
let keyMaps,controlMode='mouse',moveTarget=null;
const heldCommands=new Map();
const movementKeys={MOVE_UP:'KeyW',MOVE_DOWN:'KeyS',MOVE_LEFT:'KeyA',MOVE_RIGHT:'KeyD',CAMERA_ROT_LEFT:'ArrowLeft',CAMERA_ROT_RIGHT:'ArrowRight'};
function clearControls(){keys.clear();heldCommands.clear();moveTarget=null;drag=null;}
function setControlMode(value){controlMode=value;clearControls();rfHUD?.setControlMode(value);}
let characterWorld, player = [0,0,10], playerFacing = 0, playerClip = 'idle';
function followPlayer() {
  const cp=Math.cos(pitch), sp=Math.sin(pitch);
  camera=[player[0]-Math.sin(yaw)*cp*cameraDistance,player[1]+1.2-sp*cameraDistance,player[2]-Math.cos(yaw)*cp*cameraDistance];
}
const keys = new Set(), beacons = [], m = new Float32Array(16), view = new Float32Array(16);
const mobile = matchMedia('(pointer:coarse)').matches;
function fail(e) { $('status').textContent = 'GAGAL MEMUAT'; $('play').textContent = 'MUAT ULANG HALAMAN'; $('play').disabled = true; $('assetInfo').textContent = e.message; console.error(e); }
function shader(type, source) {
  const s = gl.createShader(type); gl.shaderSource(s, source); gl.compileShader(s);
  if (!gl.getShaderParameter(s, gl.COMPILE_STATUS)) throw Error(gl.getShaderInfoLog(s)); return s;
}
let program, u;
if (gl) {
  try {
    program = gl.createProgram();
    gl.attachShader(program, shader(gl.VERTEX_SHADER, `attribute vec3 position; attribute vec3 color; uniform mat4 projection, view; uniform float size; varying vec3 tint; varying float depth;
      void main(){vec4 p=view*vec4(position,1.0);gl_Position=projection*p;gl_PointSize=clamp(size/max(1.0,-p.z),1.2,14.0);tint=color;depth=-p.z;}`));
    gl.attachShader(program, shader(gl.FRAGMENT_SHADER, `precision mediump float; varying vec3 tint; varying float depth; uniform float beacon, mesh;
      void main(){vec2 c=gl_PointCoord-0.5;if(mesh<0.5 && dot(c,c)>0.25)discard;vec3 col=mix(vec3(0.32,0.53,0.55),vec3(0.75,0.87,0.80),tint.r)*mix(0.55,1.0,tint.g);col=mix(col,tint,mesh);col=mix(col,vec3(0.72,1.0,0.55),beacon);float fog=1.0-exp(-max(depth,0.0)*0.0035);gl_FragColor=vec4(mix(col,vec3(0.031,0.082,0.106),fog),1.0);}`));
    gl.linkProgram(program); if (!gl.getProgramParameter(program, gl.LINK_STATUS)) throw Error(gl.getProgramInfoLog(program));
    gl.useProgram(program);
    u = Object.fromEntries(['projection','view','size','beacon','mesh'].map(n=>[n,gl.getUniformLocation(program,n)]));
    gl.enable(gl.DEPTH_TEST); gl.clearColor(.031,.082,.106,1);
  } catch(e) { fail(e); }
} else fail(Error('Browser ini memerlukan WebGL. Aktifkan akselerasi grafis lalu muat ulang.'));
function buffer(data) { const b=gl.createBuffer();gl.bindBuffer(gl.ARRAY_BUFFER,b);gl.bufferData(gl.ARRAY_BUFFER,data,gl.STATIC_DRAW);return b; }
function bind(b) { gl.bindBuffer(gl.ARRAY_BUFFER,b); for(const [n,o] of [['position',0],['color',12]]) {const a=gl.getAttribLocation(program,n);gl.enableVertexAttribArray(a);gl.vertexAttribPointer(a,3,gl.FLOAT,false,24,o);} }
function matrices(aspect) {
  const f = 1/Math.tan(Math.PI/6), near=.1, far=900;
  m.fill(0);m[0]=f/aspect;m[5]=f;m[10]=(far+near)/(near-far);m[11]=-1;m[14]=2*far*near/(near-far);
  const sx=Math.sin(yaw),cx=Math.cos(yaw),sp=Math.sin(pitch),cp=Math.cos(pitch);
  const right=[-cx,0,sx], up=[-sx*sp,cp,-cx*sp], back=[-sx*cp,-sp,-cx*cp];
  view.set([right[0],up[0],back[0],0,right[1],up[1],back[1],0,right[2],up[2],back[2],0,
    -dot(right,camera),-dot(up,camera),-dot(back,camera),1]);
  gl.uniformMatrix4fv(u.projection,false,m); gl.uniformMatrix4fv(u.view,false,view);
}
function dot(a,b){return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];}
function distance(a,b){return Math.hypot(a[0]-b[0],a[1]-b[1],a[2]-b[2]);}
function progress(){ $('score').textContent = `${beacons.filter(b=>b.found).length} / 5 BEACONS`;$('progress').innerHTML=beacons.map(b=>`<i class="${b.found?'found':''}"></i>`).join(''); }
function reset() {
  camera=[0,35,105];yaw=Math.PI;pitch=-.15;elapsed=0;completed=false;
  if(characterMode){player=[0,terrainRenderer.groundAt(0,10),10];if(player[1]===null)throw Error('Tidak menemukan lantai spawn');playerFacing=0;pitch=-.5;stamina=100;exhausted=false;followPlayer();}
  beacons.forEach(b=>b.found=false); progress(); $('finish').hidden=true;
}
function start(){ if(!points||(characterMode&&!rfHUD))return;if(!started)reset();started=true;running=true;$('menu').hidden=true;$('finish').hidden=true;$('hud').hidden=characterMode;$('touch').hidden=!mobile;$('mode').textContent=characterMode?'BELLATO / FREE WALK':'EXPEDITION';rfHUD?.setVisible(true);if(!mobile&&!characterMode)canvas.requestPointerLock?.()?.catch?.(()=>{}); }
function pause(){if(!running)return;running=false;clearControls();rfHUD?.setVisible(false);$('menu').hidden=false;$('hud').hidden=true;$('touch').hidden=true;$('play').innerHTML=(characterMode?t(1198):'LANJUT EKSPEDISI')+' <span>↗</span>';document.exitPointerLock?.();}
$('play').onclick=start;$('pause').onclick=pause;$('restart').onclick=()=>{reset();start();};$('explore').onclick=start;
document.addEventListener('keydown',e=>{
 if(!running)return;
 if(rfHUD?.handleKey(e)){keys.clear();heldCommands.clear();moveTarget=null;return;}
 if(characterMode){
  if(e.code==='Escape'){e.preventDefault();if(moveTarget){moveTarget=null;return;}pause();return;}
  if(['ShiftLeft','ShiftRight'].includes(e.code)){keys.add(e.code);return;}
  let command=resolveKey(keyMaps[controlMode],e);
  if(!command&&e.shiftKey){const candidate=resolveKey(keyMaps[controlMode],{...e,code:e.code,shiftKey:false,altKey:e.altKey,ctrlKey:e.ctrlKey,metaKey:e.metaKey});if(movementKeys[candidate])command=candidate;}
  if(!command&&/^Digit[0-9]$/.test(e.code)&&!e.altKey&&!e.ctrlKey&&!e.shiftKey)command='SLOT_'+(Number(e.code.slice(-1))||10);
  if(!command)return;e.preventDefault();
  if(movementKeys[command]){moveTarget=null;heldCommands.set(e.code,movementKeys[command]);keys.add(movementKeys[command]);return;}
  if(e.repeat)return;
  if(command==='KEYBOARD_MOVE_METHOD'){setControlMode(controlMode==='mouse'?'keyboard':'mouse');return;}
  if(command==='ZOOM_IN'||command==='ZOOM_OUT'){cameraDistance=Math.max(4.5,Math.min(14,cameraDistance+(command==='ZOOM_IN'?-.5:.5)));rfHUD.syncDistance(cameraDistance);return;}
  rfHUD.dispatch(command);return;
 }
 if(['KeyW','KeyA','KeyS','KeyD','KeyQ','KeyE','ShiftLeft','ShiftRight','ArrowLeft','ArrowRight','ArrowUp','ArrowDown'].includes(e.code)){e.preventDefault();keys.add(e.code);}if(e.code==='Escape')pause();
});
document.addEventListener('keyup',e=>{const semantic=heldCommands.get(e.code);heldCommands.delete(e.code);if(semantic&&!Array.from(heldCommands.values()).includes(semantic))keys.delete(semantic);if(!characterMode||e.code.startsWith('Shift'))keys.delete(e.code);});window.addEventListener('blur',pause);
document.addEventListener('visibilitychange',()=>{if(document.hidden)pause();});
document.addEventListener('pointerlockchange',()=>{if(!document.pointerLockElement && running && !mobile && !characterMode)pause();});
document.addEventListener('mousemove',e=>{if(running&&document.pointerLockElement===canvas){yaw-=e.movementX*.0025;pitch=Math.max(-1.5,Math.min(1.5,pitch-e.movementY*.0025));}});
let drag,press;
canvas.addEventListener('pointerdown',e=>{if(running&&!rfHUD?.interacting){drag=[e.clientX,e.clientY];press={x:e.clientX,y:e.clientY,button:e.button,moved:false};canvas.setPointerCapture(e.pointerId);}});
canvas.addEventListener('pointermove',e=>{if(running&&drag&&!document.pointerLockElement){yaw-=(e.clientX-drag[0])*.005;pitch=Math.max(-1.5,Math.min(1.5,pitch-(e.clientY-drag[1])*.005));drag=[e.clientX,e.clientY];}});
canvas.addEventListener('pointermove',e=>{if(press&&Math.hypot(e.clientX-press.x,e.clientY-press.y)>5)press.moved=true;});
canvas.addEventListener('pointerup',e=>{
 if(running&&characterMode&&controlMode==='mouse'&&press?.button===0&&!press.moved&&!rfHUD.interacting){
  const nx=(e.clientX/innerWidth*2-1)*innerWidth/innerHeight/Math.sqrt(3),ny=(1-e.clientY/innerHeight*2)/Math.sqrt(3),sx=Math.sin(yaw),cx=Math.cos(yaw),sp=Math.sin(pitch),cp=Math.cos(pitch);
  const direction=[sx*cp-cx*nx-sx*sp*ny,sp+cp*ny,cx*cp+sx*nx-cx*sp*ny];
  moveTarget=terrainRenderer.groundAt.pickRay(camera,direction);if(!moveTarget)rfHUD.notify(t(229));else{keys.clear();heldCommands.clear();}
 }
 drag=null;press=null;
});canvas.addEventListener('pointercancel',()=>{drag=null;press=null;});
canvas.addEventListener('contextmenu',e=>e.preventDefault());
canvas.addEventListener('wheel',e=>{if(characterMode&&running&&!rfHUD?.interacting){e.preventDefault();cameraDistance=Math.max(4.5,Math.min(14,cameraDistance+Math.sign(e.deltaY)*.5));rfHUD.syncDistance(cameraDistance);followPlayer();}},{passive:false});
for(const b of document.querySelectorAll('[data-key]')) {b.onpointerdown=e=>{e.preventDefault();b.setPointerCapture(e.pointerId);keys.add(b.dataset.key);}; b.onpointerup=b.onpointercancel=()=>keys.delete(b.dataset.key);}
let mapBackground;
function mapXY(p){return [(p[0]+145)/290*240,(p[2]+125)/250*190];}
function drawMap(){const c=$('minimap').getContext('2d');c.clearRect(0,0,240,190);c.drawImage(mapBackground,0,0);
 if(!characterMode)for(const b of beacons){const [x,y]=mapXY(b.p);c.fillStyle=b.found?'#4b6662':'#b9f6ad';c.beginPath();c.arc(x,y,b.found?2:4,0,Math.PI*2);c.fill();}
 const [x,y]=mapXY(characterMode?player:camera);c.save();c.translate(x,y);c.rotate(-yaw);c.fillStyle='#fff';c.beginPath();c.moveTo(0,6);c.lineTo(-3,-4);c.lineTo(3,-4);c.closePath();c.fill();c.restore();}
function frame(t){const rawDT=(t-last)/1000,dt=Math.min(rawDT,.05);last=t;if(rawDT>0)fps=fps*.9+.1/rawDT;
 const w=Math.round(innerWidth*Math.min(devicePixelRatio,1.5)),h=Math.round(innerHeight*Math.min(devicePixelRatio,1.5));if(canvas.width!==w||canvas.height!==h){canvas.width=w;canvas.height=h;gl.viewport(0,0,w,h);}
 if(running){if(!completed)elapsed+=dt;if(rfHUD?.interacting)keys.clear();const speed=(keys.has('ShiftLeft')||keys.has('ShiftRight')?45:16)*dt;
  yaw+=(Number(keys.has('ArrowLeft'))-Number(keys.has('ArrowRight')))*dt*1.5;pitch=Math.max(-1.5,Math.min(1.5,pitch+(Number(keys.has('ArrowUp'))-Number(keys.has('ArrowDown')))*dt));
  const forward=Number(keys.has('KeyW'))-Number(keys.has('KeyS')),side=Number(keys.has('KeyD'))-Number(keys.has('KeyA')),vertical=Number(keys.has('KeyE'))-Number(keys.has('KeyQ'));
  if(characterMode){
   pitch=Math.max(-.8,Math.min(.05,pitch));
   let dx=Math.sin(yaw)*forward-Math.cos(yaw)*side,dz=Math.cos(yaw)*forward+Math.sin(yaw)*side;
   if(moveTarget){dx=moveTarget[0]-player[0];dz=moveTarget[2]-player[2];if(Math.hypot(dx,dz)<.12){moveTarget=null;dx=dz=0;}}
   const len=Math.hypot(dx,dz);
   const sprint=(keys.has('ShiftLeft')||keys.has('ShiftRight')||runMode)&&!exhausted&&stamina>0,step=(sprint?5:2.2)*dt;
   playerClip=combatStance?'combat':'idle';
   if(len){const amount=moveTarget?Math.min(step,len):step,x=player[0]+dx/len*amount,z=player[2]+dz/len*amount,y=terrainRenderer.groundAt(x,z,player[1]+.45,player[1]-1.0);if(y!==null){player=[x,y,z];playerFacing=Math.atan2(-dx,-dz);playerClip=sprint?'run':'walk';}else if(moveTarget){moveTarget=null;rfHUD.notify(t(229));}}
   stamina=Math.max(0,Math.min(100,stamina+(playerClip==='run'?-14:8)*dt));
   if(stamina===0)exhausted=true;else if(stamina>=25)exhausted=false;
   followPlayer();
  }else{
   camera[0]+=(Math.sin(yaw)*forward-Math.cos(yaw)*side)*speed;camera[2]+=(Math.cos(yaw)*forward+Math.sin(yaw)*side)*speed;camera[1]+=vertical*speed;
   camera=camera.map((v,i)=>Math.max(manifest.bounds[0][i]-25,Math.min(manifest.bounds[1][i]+70,v)));
   for(const b of beacons)if(!b.found&&distance(camera,b.p)<9){b.found=true;progress();$('toast').textContent=`SIGNAL ${b.id} ACQUIRED`;setTimeout(()=>$('toast').textContent='',2500);}
   if(!completed&&beacons.every(b=>b.found)){completed=true;running=false;$('finish').hidden=false;$('hud').hidden=true;$('touch').hidden=true;$('result').textContent=`Lima beacon ditemukan dalam ${Math.floor(elapsed)} detik. Semua sektor ekspedisi berhasil dijelajahi.`;document.exitPointerLock?.();}
  }
 }else if(!started&&!characterMode){const a=t*.000025;camera=[Math.sin(a)*185,95,Math.cos(a)*185];yaw=a+Math.PI;pitch=-.43;}
 gl.clear(gl.COLOR_BUFFER_BIT|gl.DEPTH_BUFFER_BIT);gl.useProgram(program);matrices(w/h);skyRenderer.draw(m,view);terrainRenderer.draw(m,view);gl.useProgram(program);
 if(!characterMode){bind(beaconGPU);gl.uniform1f(u.mesh,0);gl.uniform1f(u.size,2200);gl.uniform1f(u.beacon,1);for(let i=0;i<beacons.length;i++)if(!beacons[i].found)gl.drawArrays(gl.POINTS,i*40,40);}
 if(characterWorld)characterWorld.draw(m,view,player,playerFacing,running?playerClip:'idle',running?dt:0);
 if(rfHUD){
  const p=[player[0],player[1]+1.95,player[2],1],v=[0,0,0,0],clip=[0,0,0,0];
  for(let r=0;r<4;r++)for(let c=0;c<4;c++)v[r]+=view[c*4+r]*p[c];
  for(let r=0;r<4;r++)for(let c=0;c<4;c++)clip[r]+=m[c*4+r]*v[c];
  const screen=clip[3]>0?[(clip[0]/clip[3]*.5+.5)*innerWidth,(-clip[1]/clip[3]*.5+.5)*innerHeight]:null;
  let targetScreen=null;
  if(moveTarget){const a=[...moveTarget,1],b=[0,0,0,0],c=[0,0,0,0];for(let r=0;r<4;r++)for(let k=0;k<4;k++)b[r]+=view[k*4+r]*a[k];for(let r=0;r<4;r++)for(let k=0;k<4;k++)c[r]+=m[k*4+r]*b[k];if(c[3]>0)targetScreen=[(c[0]/c[3]*.5+.5)*innerWidth,(-c[1]/c[3]*.5+.5)*innerHeight];}
  rfHUD.update({player,yaw,screen,targetScreen,stamina,clip:playerClip,headwear,combat:combatStance,runMode,fps,elapsed});
 }
 const remaining=beacons.filter(b=>!b.found).sort((a,b)=>distance(camera,a.p)-distance(camera,b.p));const target=remaining[0];
 $('target').textContent=characterMode?'BELLATO · WASD GERAK · SHIFT LARI':target?`SIGNAL ${target.id} · ${distance(camera,target.p).toFixed(0)} m · Q/E atur ketinggian`:'SEMUA SINYAL DITEMUKAN';
 $('coords').textContent=(characterMode?player:camera).map(v=>v.toFixed(0)).join(' / ');$('timer').textContent=`${String(Math.floor(elapsed/60)).padStart(2,'0')}:${String(Math.floor(elapsed%60)).padStart(2,'0')}`;
 drawMap(); requestAnimationFrame(frame);
}
async function load(){if(!gl||!program)return;
 await loadLanguage();
 if(characterMode){document.querySelector('#menu h1').textContent=t(1125);document.querySelector('#menu > p').textContent=t(2022)+' / '+t(2021)+' [H]';document.querySelector('.brand').textContent='RF Online';document.querySelector('.tag').textContent='Platform01';document.querySelector('#menu .eyebrow').textContent=t(6);document.querySelector('.facts').hidden=true;document.querySelector('.sky-choice').firstChild.textContent=t(1012);document.querySelector('#menu summary').textContent=t(108);$('scopeNote').textContent=t(1979)+': '+t(103);document.querySelector('.character-link').textContent=t(1126);$('play').textContent=t(528);}
 terrainRenderer=await createTerrainRenderer(gl,(n,total)=>{$('play').textContent=t(528)+` ${n} / ${total}`;},characterMode);
 skyRenderer=await createSkyRenderer(gl);$('skySelect').disabled=false;
 $('skySelect').onchange=()=>skyRenderer.select(Number($('skySelect').value));
 const responses=await Promise.all([fetch('assets/platform.points'),fetch('assets/manifest.json')]);for(const r of responses)if(!r.ok)throw Error(`Aset gagal dimuat: ${r.status}`);
 manifest=await responses[1].json();points=new Float32Array(await responses[0].arrayBuffer());if(points.length!==manifest.vertices*6)throw Error('Ukuran data map tidak cocok dengan manifest');

 // Select separated, existing map positions at accessible heights for flight objectives.
 const targets=[[-30,0,65],[65,0,35],[65,0,-65],[-65,0,-65],[-70,0,10]];
 for(let k=0;k<targets.length;k++){let best=Infinity,p;for(let i=0;i<points.length;i+=6){const q=[points[i],points[i+1],points[i+2]];if(q[1]<-5||q[1]>35)continue;const d=Math.hypot(q[0]-targets[k][0],q[2]-targets[k][2]);if(d<best){best=d;p=q;}} if(!p)throw Error('Tidak menemukan posisi beacon');p[1]+=5;beacons.push({id:String(k+1).padStart(2,'0'),p,found:false});}
 const beaconVertices=[];for(const b of beacons)for(let j=0;j<40;j++)beaconVertices.push(b.p[0],b.p[1]+j*.35,b.p[2],1,1,1);beaconGPU=buffer(new Float32Array(beaconVertices));
 mapBackground=document.createElement('canvas');mapBackground.width=240;mapBackground.height=190;const ctx=mapBackground.getContext('2d');ctx.fillStyle='#7ca7a329';for(let i=0;i<points.length;i+=24){const [x,y]=mapXY([points[i],points[i+1],points[i+2]]);ctx.fillRect(x,y,1,1);}
 $('pointCount').textContent=manifest.vertices.toLocaleString('en-US');$('assetInfo').textContent=`${manifest.sources.length} file sumber tersimpan; ${manifest.materials.length} nama material terdeteksi. BSP: ${manifest.triangles.toLocaleString()} segitiga statis; ${manifest.skippedGroups} grup animasi/tak terlihat dilewati. EBP dan CAM belum dipakai.`;
 $('status').textContent='ORIGINAL TEXTURES / BAKED LIGHTING';$('play').disabled=false;$('play').innerHTML='MULAI EKSPEDISI <span>↗</span>';progress();requestAnimationFrame(frame);
 if(characterMode){
  $('play').disabled=true;
  characterWorld=await (await import('./character-world.js')).createCharacterWorld(gl,canvas);
  keyMaps=await loadKeyMaps();
  rfHUD=await createRFHUD({mapBackground,onPause:pause,onFocus:clearControls,
   onAction(action){
    if(action==='input-mode'){setControlMode(controlMode==='mouse'?'keyboard':'mouse');return;}
    if(action==='combat'){combatStance=!combatStance;return t(combatStance?1124:1123);}
    if(action==='run'){runMode=!runMode;return t(1144);}
    if(action==='headwear'){headwear=headwear==='hair'?'helmet':'hair';characterWorld.setHeadwear(headwear);return t(headwear==='helmet'?33:1170);}
   },
   onSetting(key,value){if(key==='control-mode')setControlMode(value);if(key==='distance'){cameraDistance=value;followPlayer();}if(key==='sky'){skyRenderer.select(value);$('skySelect').value=String(value);}}
  });
  $('skySelect').onchange=()=>{skyRenderer.select(Number($('skySelect').value));document.getElementById('rfSky').value=$('skySelect').value;};
  reset();
  document.querySelector('#menu h1').textContent=t(1125);
  document.querySelector('#menu > p').textContent=t(2022)+' / '+t(2021)+' [H]';
  document.querySelector('.facts > div:nth-child(2)').innerHTML='<strong>01</strong><span>LOCAL CHARACTER</span>';
  $('scopeNote').textContent=t(1979)+': '+t(103);
  document.querySelector('.mission').hidden=true;document.querySelector('.crosshair').hidden=true;
  document.querySelector('footer > span:first-child').textContent='WASD GERAK · MOUSE / ← → LIHAT · SHIFT LARI';
  for(const key of ['KeyQ','KeyE'])document.querySelector(`[data-key="${key}"]`).hidden=true;
  $('play').textContent=t(1198);$('play').disabled=false;
 }
 // Read-only diagnostics for browser validation, no gameplay mutation API.
 window.platformDiagnostics=()=>({vertices:manifest.vertices,triangles:manifest.triangles,sky:skyRenderer.diagnostics(),terrain:terrainRenderer.diagnostics(),character:characterWorld?.diagnostics(),hud:rfHUD?.diagnostics(),language:languageDiagnostics(),controlMode,moveTarget:moveTarget?[...moveTarget]:null,stamina,combatStance,runMode,cameraDistance,player:[...player],characterMode,beacons:beacons.map(b=>({position:[...b.p],found:b.found})),camera:[...camera],running,completed,elapsed,glError:gl.getError()});
}
load().catch(fail);
