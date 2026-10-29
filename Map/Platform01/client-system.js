// New browser implementation. These tuning values are NOT decoded RF server rules.
const fail = path => { throw Error(`System/web-client.json: invalid ${path}`); };
function object(value, keys, path) {
  if (!value || typeof value !== 'object' || Array.isArray(value) ||
      Object.keys(value).length !== keys.length || keys.some(k => !Object.hasOwn(value,k))) fail(path);
}
function number(value, low, high, path) {
  if (typeof value !== 'number' || !Number.isFinite(value) || value < low || value > high) fail(path);
}
function asset(value,path) {
  if (typeof value !== 'string' || !/^assets\/(?:[A-Za-z0-9_-]+\/)*[A-Za-z0-9_-]+\.(json|dat)$/.test(value)) fail(path);
}
function freeze(value) {
  for (const child of Object.values(value)) if (child && typeof child === 'object') freeze(child);
  return Object.freeze(value);
}
export function validateClientSystem(data) {
  object(data,['schemaVersion','mode','assets','ui','input','renderer','camera','movement','stamina'],'root');
  if (data.schemaVersion !== 1) fail('schemaVersion');
  if (data.mode !== 'local-preview') fail('mode (server connection is not implemented)');
  object(data.assets,['language','keymaps'],'assets');
  object(data.assets.keymaps,['mouse','keyboard'],'assets.keymaps');
  asset(data.assets.language,'assets.language');
  for (const [key,path] of Object.entries(data.assets.keymaps)) asset(path,'assets.keymaps.'+key);
  object(data.ui,['fontFamily'],'ui');
  if (data.ui.fontFamily !== 'Lucida Console') fail('ui.fontFamily');
  object(data.input,['defaultMode'],'input');
  if (!['mouse','keyboard'].includes(data.input.defaultMode)) fail('input.defaultMode');
  const ranges = {
    renderer:{maxPixelRatio:[.5,3],maxFrameSeconds:[.01,.1]},
    camera:{fovDegrees:[30,100],near:[.01,1],far:[50,5000],distance:[1,50],minDistance:[1,50],maxDistance:[1,50],zoomStep:[.1,5],followHeight:[0,5],pitch:[-1.5,.5],minPitch:[-1.5,.5],maxPitch:[-1.5,.5],dragSensitivity:[.0001,.03],turnSpeed:[.1,10]},
    movement:{walkSpeed:[.1,20],runSpeed:[.1,30],stepUp:[0,2],stepDown:[0,3],arrivalRadius:[.01,1]},
    stamina:{drainPerSecond:[.1,100],recoverPerSecond:[.1,100],resumeAt:[1,100]}
  };
  for (const [group,fields] of Object.entries(ranges)) {
    object(data[group],Object.keys(fields),group);
    for (const [key,[low,high]] of Object.entries(fields)) number(data[group][key],low,high,group+'.'+key);
  }
  const c=data.camera;
  if (!(c.minDistance < c.maxDistance && c.distance >= c.minDistance && c.distance <= c.maxDistance)) fail('camera distance bounds');
  if (!(c.minPitch < c.maxPitch && c.pitch >= c.minPitch && c.pitch <= c.maxPitch)) fail('camera pitch bounds');
  if (data.movement.runSpeed < data.movement.walkSpeed) fail('movement.runSpeed');
  return freeze(structuredClone(data));
}
export async function loadClientSystem(fetcher=fetch) {
  const response=await fetcher('assets/system/web-client.json');
  if (!response.ok) throw Error(`System/web-client.json: HTTP ${response.status}`);
  // No fallback to hidden constants: invalid configuration must fail visibly.
  return validateClientSystem(await response.json());
}
export function clampCameraDistance(config,value) {
  if (!Number.isFinite(value)) fail('camera distance');
  return Math.max(config.camera.minDistance,Math.min(config.camera.maxDistance,value));
}
export function advanceStamina(config,value,exhausted,isRunning,dt) {
  value=Math.max(0,Math.min(100,value+(isRunning?-config.stamina.drainPerSecond:config.stamina.recoverPerSecond)*dt));
  return {value,exhausted:value===0?true:value>=config.stamina.resumeAt?false:exhausted};
}
