import {createSkyRenderer} from './sky.js';
import {createTerrainRenderer} from './terrain.js';
const $ = id => document.getElementById(id);
const canvas = $('world');
const gl = canvas.getContext('webgl', {antialias:true, alpha:false});
let running = false, started = false, completed = false, last = 0, elapsed = 0, skyRenderer, terrainRenderer;
let yaw = Math.PI, pitch = -0.15, camera = [0, 35, 105], points, manifest, beaconGPU;
const characterMode = new URLSearchParams(location.search).get('character') === '1';
let characterWorld, player = [0,0,10], playerFacing = 0, playerClip = 'idle';
function followPlayer() {
  const cp=Math.cos(pitch), sp=Math.sin(pitch);
  camera=[player[0]-Math.sin(yaw)*cp*4.5,player[1]+1.2-sp*4.5,player[2]-Math.cos(yaw)*cp*4.5];
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
  if(characterMode){player=[0,terrainRenderer.groundAt(0,10),10];if(player[1]===null)throw Error('Tidak menemukan lantai spawn');playerFacing=0;pitch=-.22;followPlayer();}
  beacons.forEach(b=>b.found=false); progress(); $('finish').hidden=true;
}
function start(){ if(!points)return;if(!started)reset();started=true;running=true;$('menu').hidden=true;$('finish').hidden=true;$('hud').hidden=false;$('touch').hidden=!mobile;$('mode').textContent=characterMode?'BELLATO / FREE WALK':'EXPEDITION';if(!mobile)canvas.requestPointerLock?.()?.catch?.(()=>{}); }
function pause(){if(!running)return;running=false;keys.clear();$('menu').hidden=false;$('hud').hidden=true;$('touch').hidden=true;$('play').innerHTML='LANJUT EKSPEDISI <span>↗</span>';document.exitPointerLock?.();}
$('play').onclick=start;$('pause').onclick=pause;$('restart').onclick=()=>{reset();start();};$('explore').onclick=start;
document.addEventListener('keydown',e=>{if(['KeyW','KeyA','KeyS','KeyD','KeyQ','KeyE','ShiftLeft','ShiftRight','ArrowLeft','ArrowRight','ArrowUp','ArrowDown'].includes(e.code)){if(running)e.preventDefault();keys.add(e.code);}if(e.code==='Escape')pause();});
document.addEventListener('keyup',e=>keys.delete(e.code));window.addEventListener('blur',pause);
document.addEventListener('visibilitychange',()=>{if(document.hidden)pause();});
document.addEventListener('pointerlockchange',()=>{if(!document.pointerLockElement && running && !mobile)pause();});
document.addEventListener('mousemove',e=>{if(running&&document.pointerLockElement===canvas){yaw-=e.movementX*.0025;pitch=Math.max(-1.5,Math.min(1.5,pitch-e.movementY*.0025));}});
let drag;
canvas.addEventListener('pointerdown',e=>{if(running){drag=[e.clientX,e.clientY];canvas.setPointerCapture(e.pointerId);}});
canvas.addEventListener('pointermove',e=>{if(running&&drag&&!document.pointerLockElement){yaw-=(e.clientX-drag[0])*.005;pitch=Math.max(-1.5,Math.min(1.5,pitch-(e.clientY-drag[1])*.005));drag=[e.clientX,e.clientY];}});
canvas.addEventListener('pointerup',()=>drag=null);canvas.addEventListener('pointercancel',()=>drag=null);
for(const b of document.querySelectorAll('[data-key]')) {b.onpointerdown=e=>{e.preventDefault();b.setPointerCapture(e.pointerId);keys.add(b.dataset.key);}; b.onpointerup=b.onpointercancel=()=>keys.delete(b.dataset.key);}
let mapBackground;
function mapXY(p){return [(p[0]+145)/290*240,(p[2]+125)/250*190];}
function drawMap(){const c=$('minimap').getContext('2d');c.clearRect(0,0,240,190);c.drawImage(mapBackground,0,0);
 if(!characterMode)for(const b of beacons){const [x,y]=mapXY(b.p);c.fillStyle=b.found?'#4b6662':'#b9f6ad';c.beginPath();c.arc(x,y,b.found?2:4,0,Math.PI*2);c.fill();}
 const [x,y]=mapXY(characterMode?player:camera);c.save();c.translate(x,y);c.rotate(-yaw);c.fillStyle='#fff';c.beginPath();c.moveTo(0,6);c.lineTo(-3,-4);c.lineTo(3,-4);c.closePath();c.fill();c.restore();}
function frame(t){const dt=Math.min((t-last)/1000,.05);last=t;
 const w=Math.round(innerWidth*Math.min(devicePixelRatio,1.5)),h=Math.round(innerHeight*Math.min(devicePixelRatio,1.5));if(canvas.width!==w||canvas.height!==h){canvas.width=w;canvas.height=h;gl.viewport(0,0,w,h);}
 if(running){if(!completed)elapsed+=dt;const speed=(keys.has('ShiftLeft')||keys.has('ShiftRight')?45:16)*dt;
  yaw+=(Number(keys.has('ArrowLeft'))-Number(keys.has('ArrowRight')))*dt*1.5;pitch=Math.max(-1.5,Math.min(1.5,pitch+(Number(keys.has('ArrowUp'))-Number(keys.has('ArrowDown')))*dt));
  const forward=Number(keys.has('KeyW'))-Number(keys.has('KeyS')),side=Number(keys.has('KeyD'))-Number(keys.has('KeyA')),vertical=Number(keys.has('KeyE'))-Number(keys.has('KeyQ'));
  if(characterMode){
   pitch=Math.max(-.8,Math.min(.05,pitch));
   const dx=Math.sin(yaw)*forward-Math.cos(yaw)*side,dz=Math.cos(yaw)*forward+Math.sin(yaw)*side,len=Math.hypot(dx,dz);
   const sprint=keys.has('ShiftLeft')||keys.has('ShiftRight'),step=(sprint?5:2.2)*dt;
   playerClip='idle';
   if(len){const x=player[0]+dx/len*step,z=player[2]+dz/len*step,y=terrainRenderer.groundAt(x,z,player[1]+.45,player[1]-1.0);if(y!==null){player=[x,y,z];playerFacing=Math.atan2(-dx,-dz);playerClip=sprint?'run':'walk';}}
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
 const remaining=beacons.filter(b=>!b.found).sort((a,b)=>distance(camera,a.p)-distance(camera,b.p));const target=remaining[0];
 $('target').textContent=characterMode?'BELLATO · WASD GERAK · SHIFT LARI':target?`SIGNAL ${target.id} · ${distance(camera,target.p).toFixed(0)} m · Q/E atur ketinggian`:'SEMUA SINYAL DITEMUKAN';
 $('coords').textContent=(characterMode?player:camera).map(v=>v.toFixed(0)).join(' / ');$('timer').textContent=`${String(Math.floor(elapsed/60)).padStart(2,'0')}:${String(Math.floor(elapsed%60)).padStart(2,'0')}`;
 drawMap(); requestAnimationFrame(frame);
}
async function load(){if(!gl||!program)return;
 terrainRenderer=await createTerrainRenderer(gl,(n,total)=>{$('play').textContent=`MEMUAT TEKSTUR ${n} / ${total}`;},characterMode);
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
  reset();
  document.querySelector('#menu h1').innerHTML='Bellato.<br><em>Platform01.</em>';
  document.querySelector('#menu > p').textContent='Jelajahi Platform01 dengan armor Bellato dan animasi asli. WASD untuk jalan, Shift untuk lari, mouse untuk mengatur kamera.';
  $('scopeNote').textContent='Kaki mengikuti permukaan map. Tabrakan dinding dan kamera, wajah/rambut, combat, serta multiplayer belum tersedia.';
  document.querySelector('.mission').hidden=true;document.querySelector('.crosshair').hidden=true;
  document.querySelector('footer > span:first-child').textContent='WASD GERAK · MOUSE / ← → LIHAT · SHIFT LARI';
  for(const key of ['KeyQ','KeyE'])document.querySelector(`[data-key="${key}"]`).hidden=true;
  $('play').innerHTML='MASUK SEKTOR <span>↗</span>';$('play').disabled=false;
 }
 // Read-only diagnostics for browser validation, no gameplay mutation API.
 window.platformDiagnostics=()=>({vertices:manifest.vertices,triangles:manifest.triangles,sky:skyRenderer.diagnostics(),terrain:terrainRenderer.diagnostics(),character:characterWorld?.diagnostics(),player:[...player],characterMode,beacons:beacons.map(b=>({position:[...b.p],found:b.found})),camera:[...camera],running,completed,elapsed,glError:gl.getError()});
}
load().catch(fail);
