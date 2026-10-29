// Spatially index terrain triangles for vertical foot placement. This does not
// implement wall, camera or moving-object collision.
export function createGroundSampler(vertices, stride = 11, cellSize = 4) {
  const cells = new Map(), triangles = [];
  for (let i = 0; i < vertices.length; i += stride * 3) {
    const a = [vertices[i], vertices[i+1], vertices[i+2]];
    const b = [vertices[i+stride], vertices[i+stride+1], vertices[i+stride+2]];
    const c = [vertices[i+2*stride], vertices[i+2*stride+1], vertices[i+2*stride+2]];
    const bx = b[0]-a[0], by = b[1]-a[1], bz = b[2]-a[2];
    const cx = c[0]-a[0], cy = c[1]-a[1], cz = c[2]-a[2];
    const nx = by*cz-bz*cy, ny = bz*cx-bx*cz, nz = bx*cy-by*cx;
    if (Math.abs(ny) < 1e-8 || Math.abs(ny)/Math.hypot(nx,ny,nz) < .65) continue;
    const id = triangles.length;
    triangles.push({a, bx, by, bz, cx, cy, cz, det:bx*cz-cx*bz});
    const loX = Math.floor(Math.min(a[0],b[0],c[0])/cellSize), hiX = Math.floor(Math.max(a[0],b[0],c[0])/cellSize);
    const loZ = Math.floor(Math.min(a[2],b[2],c[2])/cellSize), hiZ = Math.floor(Math.max(a[2],b[2],c[2])/cellSize);
    for (let x = loX; x <= hiX; x++) for (let z = loZ; z <= hiZ; z++) {
      const key = `${x},${z}`;
      if (!cells.has(key)) cells.set(key, []);
      cells.get(key).push(id);
    }
  }
  const sample = (x, z, ceiling = Infinity, floor = -Infinity) => {
    let height = null;
    for (const id of cells.get(`${Math.floor(x/cellSize)},${Math.floor(z/cellSize)}`) || []) {
      const t = triangles[id], dx = x-t.a[0], dz = z-t.a[2];
      const u = (dx*t.cz-t.cx*dz)/t.det, v = (t.bx*dz-dx*t.bz)/t.det;
      if (u < -1e-6 || v < -1e-6 || u+v > 1.000001) continue;
      const y = t.a[1]+u*t.by+v*t.cy;
      if (y <= ceiling && y >= floor && (height === null || y > height)) height = y;
    }
    return height;
  };
  sample.pickRay=(origin,direction)=>{
    let nearest=Infinity,hit=null;
    for(const t of triangles){
      const normal=[t.by*t.cz-t.bz*t.cy,t.bz*t.cx-t.bx*t.cz,t.bx*t.cy-t.by*t.cx];
      const denom=normal.reduce((v,n,i)=>v+n*direction[i],0);
      if(Math.abs(denom)<1e-9)continue;
      const distance=normal.reduce((v,n,i)=>v+n*(t.a[i]-origin[i]),0)/denom;
      if(distance<0||distance>=nearest||distance>500)continue;
      const p=origin.map((v,i)=>v+direction[i]*distance),dx=p[0]-t.a[0],dz=p[2]-t.a[2];
      const u=(dx*t.cz-t.cx*dz)/t.det,v=(t.bx*dz-dx*t.bz)/t.det;
      if(u>=-1e-6&&v>=-1e-6&&u+v<=1.000001){nearest=distance;hit=p;}
    }
    return hit;
  };
  return sample;
}
