import * as THREE from './vendor/three.module.js';
import {loadCharacter} from './character-model.js';
const $ = id => document.getElementById(id);
const keys = new Set(), pointers = new Map();
let character, renderer, scene, camera, helper, previous = 0, paused = false, selected = 'idle';
let azimuth = .35, elevation = .12, distance = 4.8, frames = 0;
let viewportWidth = 0, viewportHeight = 0;
const target = new THREE.Vector3(0, .95, 0), offset = new THREE.Vector3();
const names = {idle: 'IDLE', walk: 'JALAN', run: 'LARI', combat: 'COMBAT STANCE'};
function syncControls() {
  document.querySelectorAll('[data-clip]').forEach(b => b.setAttribute('aria-pressed', String(b.dataset.clip === selected)));
  $('clipLabel').textContent = names[selected];
  $('togglePlayback').textContent = paused ? '▶ LANJUT' : 'Ⅱ JEDA';
  $('togglePlayback').setAttribute('aria-label', paused ? 'Lanjutkan animasi' : 'Jeda animasi');
}
function reset() { azimuth = .35; elevation = .12; distance = innerWidth <= 600 ? 6.2 : 4.8; character.root.position.set(0, 0, 0); character.root.rotation.y = Math.PI; keys.clear(); }
function render(time) {
  const dt = previous ? Math.min((time - previous) / 1000, .05) : 0;
  previous = time;
  const forward = Number(keys.has('KeyW')) - Number(keys.has('KeyS'));
  const side = Number(keys.has('KeyD')) - Number(keys.has('KeyA'));
  const moving = !paused && (forward || side);
  const sprint = keys.has('ShiftLeft') || keys.has('ShiftRight');
  if (moving) {
    const direction = new THREE.Vector3(side, 0, -forward).normalize().applyAxisAngle(THREE.Object3D.DEFAULT_UP, azimuth);
    character.root.position.addScaledVector(direction, dt * (sprint ? 2.5 : 1.2));
    character.root.position.x = THREE.MathUtils.clamp(character.root.position.x, -7, 7);
    character.root.position.z = THREE.MathUtils.clamp(character.root.position.z, -7, 7);
    character.root.rotation.y = Math.atan2(-direction.x, -direction.z);
  }
  character.play(moving ? (sprint ? 'run' : 'walk') : selected);
  if (!paused && !document.hidden) character.update(dt * Number($('speed').value));
  target.set(character.root.position.x, .95, character.root.position.z);
  const mobile = innerWidth <= 600;
  // Offset framing keeps the original armor clear of the information panel.
  offset.set(Math.sin(azimuth)*Math.cos(elevation), Math.sin(elevation), Math.cos(azimuth)*Math.cos(elevation)).multiplyScalar(distance);
  camera.position.copy(target).add(offset);
  camera.lookAt(target);
  const fullW = innerWidth, fullH = innerHeight;
  if (fullW !== viewportWidth || fullH !== viewportHeight) {
    renderer.setSize(fullW, fullH, false); viewportWidth = fullW; viewportHeight = fullH;
  }
  camera.aspect = fullW / fullH;
  camera.setViewOffset(fullW, fullH, -fullW * (mobile ? .17 : .14), fullH * (mobile ? .14 : .10), fullW, fullH);
  camera.updateProjectionMatrix();
  renderer.render(scene, camera);
  frames++;
  requestAnimationFrame(render);
}
async function init() {
  const canvas = $('characterCanvas');
  renderer = new THREE.WebGLRenderer({canvas, antialias: true});
  renderer.useLegacyLights = false;
  renderer.setPixelRatio(Math.min(devicePixelRatio, 1.5));
  renderer.outputColorSpace = THREE.SRGBColorSpace;
  renderer.toneMapping = THREE.ACESFilmicToneMapping;
  renderer.toneMappingExposure = 1.25;
  scene = new THREE.Scene(); scene.background = new THREE.Color('#09141b');
  scene.fog = new THREE.Fog('#09141b', 7, 22);
  camera = new THREE.PerspectiveCamera(38, 1, .05, 60);
  scene.add(new THREE.HemisphereLight(0xd8ecf1, 0x627165, 2));
  const key = new THREE.DirectionalLight(0xffe4c7, 3.1); key.position.set(3, 6, 4); scene.add(key);
  const rim = new THREE.DirectionalLight(0x92cbd1, 3); rim.position.set(-3, 3, -3); scene.add(rim);
  const ground = new THREE.Mesh(new THREE.PlaneGeometry(60, 60), new THREE.MeshStandardMaterial({color: 0x0c1c23, roughness: .95}));
  ground.rotation.x = -Math.PI / 2; ground.position.y = -.02; scene.add(ground);
  const grid = new THREE.GridHelper(40, 40, 0x345357, 0x1c343d); grid.position.y = -.015; scene.add(grid);
  const ring = new THREE.Mesh(new THREE.RingGeometry(1.2, 1.21, 96), new THREE.MeshBasicMaterial({color: 0x92bba9, transparent: true, opacity: .4, side: THREE.DoubleSide}));
  ring.rotation.x = -Math.PI / 2; ring.position.y = -.01; scene.add(ring);
  character = await loadCharacter(); scene.add(character.root); reset();
  helper = new THREE.SkeletonHelper(character.root); helper.visible = false; helper.material.depthTest = false; scene.add(helper);
  document.querySelectorAll('button,select,input').forEach(e => e.disabled = false);
  $('loading').hidden = true; $('status').textContent = 'ORIGINAL MESH · BONE · ANI · TEX';
  document.querySelectorAll('[data-clip]').forEach(b => b.onclick = () => { selected = b.dataset.clip; paused = false; syncControls(); });
  $('togglePlayback').onclick = () => { paused = !paused; keys.clear(); syncControls(); };
  $('skeleton').onchange = () => helper.visible = $('skeleton').checked;
  $('resetView').onclick = reset;
  $('headwear').onchange = () => {
    character.setHeadwear($('headwear').value);
    $('enterMap').href = `./?character=1&headwear=${$('headwear').value}`;
  };
  canvas.addEventListener('pointerdown', e => { canvas.setPointerCapture(e.pointerId); pointers.set(e.pointerId, [e.clientX, e.clientY]); });
  canvas.addEventListener('pointermove', e => {
    const prev = pointers.get(e.pointerId); if (!prev) return;
    if (pointers.size === 2) {
      const other = [...pointers].find(([id]) => id !== e.pointerId)[1];
      const before = Math.hypot(prev[0]-other[0], prev[1]-other[1]);
      const after = Math.hypot(e.clientX-other[0], e.clientY-other[1]);
      if (before && after) distance = THREE.MathUtils.clamp(distance * before / after, 2.4, 8);
    } else {
      azimuth -= (e.clientX-prev[0])*.008;
      elevation = THREE.MathUtils.clamp(elevation + (e.clientY-prev[1])*.006, -.15, 1.1);
    }
    pointers.set(e.pointerId, [e.clientX, e.clientY]);
  });
  for (const event of ['pointerup','pointercancel','lostpointercapture']) canvas.addEventListener(event, e => pointers.delete(e.pointerId));
  canvas.addEventListener('wheel', e => { e.preventDefault(); distance = THREE.MathUtils.clamp(distance*Math.exp(e.deltaY*.001), 2.4, 8); }, {passive:false});
  window.addEventListener('keydown', e => { if (/^(Key[WASD]|ShiftLeft|ShiftRight)$/.test(e.code) && !['INPUT','SELECT'].includes(document.activeElement.tagName)) { keys.add(e.code); e.preventDefault(); } });
  window.addEventListener('keyup', e => keys.delete(e.code));
  window.addEventListener('blur', () => { keys.clear(); pointers.clear(); });
  document.addEventListener('visibilitychange', () => { keys.clear(); previous = 0; });
  canvas.addEventListener('webglcontextlost', e => { e.preventDefault(); showError(Error('Konteks grafis terputus. Muat ulang untuk melanjutkan.')); });
  syncControls();
  window.characterDiagnostics = () => ({...character.diagnostics(), frames, paused, position:character.root.position.toArray(),
    azimuth, elevation, distance, skeletonVisible:helper.visible, glError:renderer.getContext().getError()});
  requestAnimationFrame(render);
}
function showError(error) {
  $('loading').hidden = false; $('loadText').textContent = error.message; $('retry').hidden = false;
  $('retry').onclick = () => location.reload(); $('status').textContent = 'KARAKTER GAGAL DIMUAT'; console.error(error);
}
init().catch(showError);
