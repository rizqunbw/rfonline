import {mkdir, copyFile, rm, cp} from 'node:fs/promises';
import {fileURLToPath} from 'node:url';
process.chdir(fileURLToPath(new URL('..', import.meta.url)));
await rm('dist', {recursive:true, force:true});
await mkdir('dist/assets', {recursive:true});
for (const file of ['index.html','style.css','app.js','sky.js','terrain.js']) await copyFile(file, `dist/${file}`);
for (const file of ['platform.points','manifest.json','am16.png']) await copyFile(`assets/${file}`, `dist/assets/${file}`);
console.log('Built dist: static application, no downloaded dependencies.');
await cp('assets/sky','dist/assets/sky',{recursive:true});

await cp('assets/terrain','dist/assets/terrain',{recursive:true});
