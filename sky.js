// Render decoded R3E geometry with its R3M -> R3T texture references.
// Sky geometry follows camera rotation only, so it remains a distant backdrop.
export async function createSkyRenderer(gl) {
  async function fetchOK(url) {
    const response = await fetch(url);
    if (!response.ok) throw Error(`Aset langit gagal dimuat: ${url} (${response.status})`);
    return response;
  }
  const manifest = await (await fetchOK('assets/sky/manifest.json')).json();
  const program = gl.createProgram();
  for (const [type,source] of [
    [gl.VERTEX_SHADER, `attribute vec3 position;attribute vec2 uv;attribute vec4 color;
      uniform mat4 projection,rotation;varying vec2 texcoord;varying vec4 tint;
      void main(){gl_Position=projection*rotation*vec4(position,1.0);texcoord=uv;tint=color;}`],
    [gl.FRAGMENT_SHADER, `precision mediump float;uniform sampler2D surface;uniform vec4 materialTint;
      uniform float opaque;varying vec2 texcoord;varying vec4 tint;
      void main(){vec4 c=texture2D(surface,texcoord)*tint*materialTint;c.a=mix(c.a,1.0,opaque);
      if(c.a<0.005)discard;gl_FragColor=c;}`]
  ]) {
    const shader = gl.createShader(type);
    gl.shaderSource(shader,source);gl.compileShader(shader);
    if(!gl.getShaderParameter(shader,gl.COMPILE_STATUS))throw Error(gl.getShaderInfoLog(shader));
    gl.attachShader(program,shader);
  }
  gl.linkProgram(program);
  if(!gl.getProgramParameter(program,gl.LINK_STATUS))throw Error(gl.getProgramInfoLog(program));
  const uniforms=Object.fromEntries(['projection','rotation','surface','materialTint','opaque'].map(n=>[n,gl.getUniformLocation(program,n)]));
  const attributes=[['position',3,0],['uv',2,12],['color',4,20]].map(([name,size,offset])=>({location:gl.getAttribLocation(program,name),size,offset}));
  const skies=await Promise.all(manifest.skies.map(async sky=>{
    const data=new Float32Array(await (await fetchOK(sky.mesh)).arrayBuffer());
    if(data.length!==sky.triangles*27)throw Error(`Geometri langit tidak lengkap: ${sky.name}`);
    const buffer=gl.createBuffer();gl.bindBuffer(gl.ARRAY_BUFFER,buffer);gl.bufferData(gl.ARRAY_BUFFER,data,gl.STATIC_DRAW);
    const textures=await Promise.all(sky.textures.map(async info=>{
      const image=await createImageBitmap(await (await fetchOK(info.url)).blob(),{premultiplyAlpha:'none',colorSpaceConversion:'none'});
      if(image.width!==info.width||image.height!==info.height)throw Error(`Dimensi tekstur tidak cocok: ${info.name}`);
      const texture=gl.createTexture();gl.bindTexture(gl.TEXTURE_2D,texture);
      gl.texImage2D(gl.TEXTURE_2D,0,gl.RGBA,gl.RGBA,gl.UNSIGNED_BYTE,image);
      const pot=(n)=>(n&(n-1))===0;
      const wrap=pot(image.width)&&pot(image.height)?gl.REPEAT:gl.CLAMP_TO_EDGE;
      gl.texParameteri(gl.TEXTURE_2D,gl.TEXTURE_WRAP_S,wrap);gl.texParameteri(gl.TEXTURE_2D,gl.TEXTURE_WRAP_T,wrap);
      gl.texParameteri(gl.TEXTURE_2D,gl.TEXTURE_MIN_FILTER,gl.LINEAR);gl.texParameteri(gl.TEXTURE_2D,gl.TEXTURE_MAG_FILTER,gl.LINEAR);
      image.close();return texture;
    }));
    return {...sky,buffer,textures};
  }));
  let active=0,frames=0;
  const rotation=new Float32Array(16);
  return {
    select(index){if(!Number.isInteger(index)||index<0||index>=skies.length)throw Error('Pilihan langit tidak valid');active=index;},
    diagnostics(){const s=skies[active];return {name:s.name,triangles:s.triangles,textures:s.textures.length,frames,available:skies.length};},
    draw(projection,view){
      const sky=skies[active];frames++;
      gl.useProgram(program);rotation.set(view);rotation[12]=rotation[13]=rotation[14]=0;
      gl.uniformMatrix4fv(uniforms.projection,false,projection);gl.uniformMatrix4fv(uniforms.rotation,false,rotation);
      gl.uniform1i(uniforms.surface,0);gl.activeTexture(gl.TEXTURE0);
      gl.disable(gl.DEPTH_TEST);gl.depthMask(false);gl.disable(gl.CULL_FACE);
      gl.enable(gl.BLEND);gl.blendFunc(gl.SRC_ALPHA,gl.ONE_MINUS_SRC_ALPHA);
      gl.bindBuffer(gl.ARRAY_BUFFER,sky.buffer);
      for(const a of attributes){gl.enableVertexAttribArray(a.location);gl.vertexAttribPointer(a.location,a.size,gl.FLOAT,false,36,a.offset);}
      // Preserve the asset's material-group order: base sky, celestial layers, clouds.
      for(const group of sky.draws){
        const layer=sky.materials[group.material].layers[0];
        gl.uniform4fv(uniforms.materialTint,layer.tint);gl.uniform1f(uniforms.opaque,layer.alphaType===0?1:0);
        gl.bindTexture(gl.TEXTURE_2D,sky.textures[layer.texture]);gl.drawArrays(gl.TRIANGLES,group.first,group.count);
      }
      for(const a of attributes)gl.disableVertexAttribArray(a.location);
      gl.disable(gl.BLEND);gl.depthMask(true);gl.enable(gl.DEPTH_TEST);
    }
  };
}
