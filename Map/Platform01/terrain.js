import {createGroundSampler} from './ground.js';
export async function createTerrainRenderer(gl,onProgress=()=>{},grounded=false) {
 const get=async url=>{const r=await fetch(url);if(!r.ok)throw Error(`Aset map gagal: ${url} (${r.status})`);return r;};
 const manifest=await (await get('assets/terrain/manifest.json')).json();
 const mesh=new Float32Array(await (await get('assets/terrain/mesh.bin')).arrayBuffer());
 if(mesh.length!==manifest.triangles*33)throw Error('Ukuran mesh terrain tidak cocok');
 const groundAt=grounded?createGroundSampler(mesh):null;
 const buffer=gl.createBuffer();gl.bindBuffer(gl.ARRAY_BUFFER,buffer);gl.bufferData(gl.ARRAY_BUFFER,mesh,gl.STATIC_DRAW);
 const infos=[...manifest.textures,...manifest.lights],textures=new Array(infos.length);let next=0,loaded=0;
 await Promise.all(Array.from({length:8},async()=>{while(next<infos.length){const i=next++,info=infos[i];const image=await createImageBitmap(await (await get(info.url)).blob(),{premultiplyAlpha:'none',colorSpaceConversion:'none'});
  if(image.width!==info.size[0]||image.height!==info.size[1])throw Error('Dimensi tekstur map tidak cocok');
  const t=gl.createTexture();gl.bindTexture(gl.TEXTURE_2D,t);gl.texImage2D(gl.TEXTURE_2D,0,gl.RGBA,gl.RGBA,gl.UNSIGNED_BYTE,image);
  const pot=n=>(n&(n-1))===0;const wrap=i>=manifest.textures.length||!pot(image.width)||!pot(image.height)?gl.CLAMP_TO_EDGE:gl.REPEAT;
  gl.texParameteri(gl.TEXTURE_2D,gl.TEXTURE_WRAP_S,wrap);gl.texParameteri(gl.TEXTURE_2D,gl.TEXTURE_WRAP_T,wrap);gl.texParameteri(gl.TEXTURE_2D,gl.TEXTURE_MIN_FILTER,gl.LINEAR);gl.texParameteri(gl.TEXTURE_2D,gl.TEXTURE_MAG_FILTER,gl.LINEAR);
  textures[i]=t;image.close();onProgress(++loaded,infos.length);
 }}));
 const p=gl.createProgram();
 for(const [type,source] of [[gl.VERTEX_SHADER,`attribute vec3 position;attribute vec4 color;attribute vec2 uv,lightUV;uniform mat4 projection,view;varying vec4 tint;varying vec2 texcoord,lcoord;varying float depth;
 void main(){vec4 v=view*vec4(position,1.0);gl_Position=projection*v;tint=color;texcoord=uv;lcoord=lightUV;depth=-v.z;}`],
 [gl.FRAGMENT_SHADER,`precision mediump float;uniform sampler2D surface,lighting;uniform float hasLight,opaque;uniform vec4 materialTint;varying vec4 tint;varying vec2 texcoord,lcoord;varying float depth;
 void main(){vec4 c=texture2D(surface,texcoord)*tint*materialTint;c.a=mix(c.a,1.0,opaque);if(c.a<0.2)discard;vec3 lit=mix(vec3(1.0),texture2D(lighting,lcoord).rgb,hasLight);vec3 rgb=c.rgb*lit;float fog=1.0-exp(-max(depth,0.0)*0.0012);gl_FragColor=vec4(mix(rgb,vec3(0.15,0.20,0.27),fog),1.0);}`]]){
  const s=gl.createShader(type);gl.shaderSource(s,source);gl.compileShader(s);if(!gl.getShaderParameter(s,gl.COMPILE_STATUS))throw Error(gl.getShaderInfoLog(s));gl.attachShader(p,s);
 }
 gl.linkProgram(p);if(!gl.getProgramParameter(p,gl.LINK_STATUS))throw Error(gl.getProgramInfoLog(p));
 const u=Object.fromEntries(['projection','view','surface','lighting','hasLight','opaque','materialTint'].map(n=>[n,gl.getUniformLocation(p,n)]));
 const attrs=[['position',3,0],['color',4,12],['uv',2,28],['lightUV',2,36]].map(([n,size,offset])=>({loc:gl.getAttribLocation(p,n),size,offset}));let frames=0;
 return {groundAt,diagnostics:()=>({textures:manifest.textures.length,lightmaps:manifest.lights.length,triangles:manifest.triangles,frames}),draw(projection,view){
  frames++;gl.useProgram(p);gl.uniformMatrix4fv(u.projection,false,projection);gl.uniformMatrix4fv(u.view,false,view);gl.uniform1i(u.surface,0);gl.uniform1i(u.lighting,1);gl.bindBuffer(gl.ARRAY_BUFFER,buffer);
  for(const a of attrs){gl.enableVertexAttribArray(a.loc);gl.vertexAttribPointer(a.loc,a.size,gl.FLOAT,false,44,a.offset);}
  for(const d of manifest.draws){const layer=manifest.materials[d.material].layers[0];gl.activeTexture(gl.TEXTURE0);gl.bindTexture(gl.TEXTURE_2D,textures[layer.texture]);gl.activeTexture(gl.TEXTURE1);gl.bindTexture(gl.TEXTURE_2D,textures[manifest.textures.length+Math.max(0,d.light)]);gl.uniform1f(u.hasLight,d.light<0?0:1);gl.uniform1f(u.opaque,layer.blend===0?1:0);gl.uniform4fv(u.materialTint,layer.tint);gl.drawArrays(gl.TRIANGLES,d.first,d.count);}
  for(const a of attrs)gl.disableVertexAttribArray(a.loc);gl.activeTexture(gl.TEXTURE0);
 }};
}
