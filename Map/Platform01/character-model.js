import * as THREE from './vendor/three.module.js';

// Shared native RF character asset used by the preview and the map renderer.
export async function loadCharacter() {
  const response = await fetch('assets/character/bellato-171.json');
  if (!response.ok) throw Error(`Karakter gagal dimuat (${response.status})`);
  const data = await response.json();
  const root = new THREE.Group();
  const bones = data.bones.map(info => {
    const bone = new THREE.Bone();
    bone.name = info.name;
    new THREE.Matrix4().fromArray(info.local).decompose(bone.position, bone.quaternion, bone.scale);
    return bone;
  });
  data.bones.forEach((info, i) => (info.parent < 0 ? root : bones[info.parent]).add(bones[i]));
  root.updateMatrixWorld(true);
  const skeleton = new THREE.Skeleton(bones, data.bones.map(info => new THREE.Matrix4().fromArray(info.inverseBind)));
  const loader = new THREE.TextureLoader();
  const textures = new Map(await Promise.all(data.textures.map(async info => {
    let texture;
    try { texture = await loader.loadAsync(`assets/character/${info.file}`); }
    catch { throw Error(`Tekstur karakter gagal dimuat: ${info.file}. Coba muat ulang.`); }
    texture.colorSpace = THREE.SRGBColorSpace;
    texture.wrapS = texture.wrapT = THREE.RepeatWrapping;
    return [info.file, texture];
  })));
  const meshes = data.meshes.map(info => {
    const geometry = new THREE.BufferGeometry();
    for (const [name, key, size] of [['position', 'positions', 3], ['normal', 'normals', 3], ['uv', 'uvs', 2], ['skinWeight', 'weights', 4]]) {
      geometry.setAttribute(name, new THREE.Float32BufferAttribute(info[key], size));
    }
    geometry.setAttribute('skinIndex', new THREE.Uint16BufferAttribute(info.joints, 4));
    const material = new THREE.MeshStandardMaterial({map: textures.get(info.texture), roughness: .76, metalness: .12, side: THREE.DoubleSide, alphaTest: .15});
    const mesh = new THREE.SkinnedMesh(geometry, material);
    mesh.name = info.name;
    mesh.frustumCulled = false;
    mesh.castShadow = true;
    root.add(mesh);
    mesh.bind(skeleton, new THREE.Matrix4());
    return mesh;
  });
  const mixer = new THREE.AnimationMixer(root);
  const clips = data.clips.map(info => new THREE.AnimationClip(info.name, info.duration, info.tracks.map(track => {
    const property = {rotation: 'quaternion', position: 'position', scale: 'scale'}[track.channel];
    const Track = track.channel === 'rotation' ? THREE.QuaternionKeyframeTrack : THREE.VectorKeyframeTrack;
    const values = [...track.values];
    // Keep locomotion in place; movement belongs to the player controller.
    if (track.bone === 0 && track.channel === 'position') {
      for (let i = 0; i < values.length; i += 3) { values[i] = 0; values[i + 2] = 0; }
    }
    return new Track(`${bones[track.bone].uuid}.${property}`, track.times, values);
  })));
  const actions = Object.fromEntries(clips.map(clip => [clip.name, mixer.clipAction(clip)]));
  let current = null, ticks = 0;
  function play(name, fade = .18) {
    if (!(name in actions) || current === name) return;
    const next = actions[name];
    if (current) actions[current].fadeOut(fade);
    next.reset().fadeIn(fade).play();
    current = name;
  }
  const height = data.bounds[1][1] - data.bounds[0][1];
  root.scale.setScalar(1.8 / height);
  play('idle', 0);
  return {root, skeleton, meshes, data, mixer, play,
    update(dt) { mixer.update(dt); ticks++; },
    diagnostics() {
      root.updateMatrixWorld(true);
      skeleton.update();
      const point = new THREE.Vector3().fromBufferAttribute(meshes[0].geometry.attributes.position, 0);
      meshes[0].applyBoneTransform(0, point);
      return {name: data.name, bones: bones.length, meshes: meshes.length, textures: textures.size,
        triangles: data.meshes.reduce((sum, m) => sum + m.positions.length / 9, 0),
        clip: current, time: mixer.time, frames: ticks, sampleVertex: point.toArray(),
        finitePose: Array.from(skeleton.boneMatrices).every(Number.isFinite)};
    }
  };
}
