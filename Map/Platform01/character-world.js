import * as THREE from './vendor/three.module.js';
import {loadCharacter} from './character-model.js';

// Share Platform01's existing WebGL context; do not duplicate terrain assets.
export async function createCharacterWorld(gl, canvas) {
  const character = await loadCharacter();
  character.setHeadwear(new URLSearchParams(location.search).get('headwear') === 'helmet' ? 'helmet' : 'hair');
  const renderer = new THREE.WebGLRenderer({canvas, context:gl, antialias:true});
  renderer.useLegacyLights = false;
  renderer.autoClear = false;
  renderer.outputColorSpace = THREE.SRGBColorSpace;
  const scene = new THREE.Scene();
  scene.add(character.root, new THREE.HemisphereLight(0xe3f2ff, 0x666f66, 2.5));
  const light = new THREE.DirectionalLight(0xffe7c6, 2.5); light.position.set(-10, 20, 10); scene.add(light);
  const camera = new THREE.PerspectiveCamera();
  camera.matrixAutoUpdate = false;
  return {
    setHeadwear: value => character.setHeadwear(value),
    diagnostics: () => character.diagnostics(),
    draw(projection, view, position, facing, clip, dt) {
      character.root.position.fromArray(position);
      character.root.rotation.y = facing;
      character.play(clip); character.update(dt);
      camera.projectionMatrix.fromArray(projection);
      camera.projectionMatrixInverse.copy(camera.projectionMatrix).invert();
      camera.matrixWorldInverse.fromArray(view);
      camera.matrixWorld.copy(camera.matrixWorldInverse).invert();
      camera.matrix.copy(camera.matrixWorld);
      renderer.resetState();
      renderer.setViewport(0, 0, canvas.width, canvas.height);
      renderer.render(scene, camera);
      renderer.resetState();
      gl.enable(gl.DEPTH_TEST);
    }
  };
}
