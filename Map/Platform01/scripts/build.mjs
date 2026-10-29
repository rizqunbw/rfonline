import {mkdir, copyFile, rm, cp} from 'node:fs/promises';
import {fileURLToPath} from 'node:url';
process.chdir(fileURLToPath(new URL('..', import.meta.url)));
await rm('dist', {recursive:true, force:true});
await mkdir('dist/assets', {recursive:true});
for (const file of ['index.html','style.css','app.js','sky.js','terrain.js','rf-hud.js','rf-hud.css']) await copyFile(file, `dist/${file}`);
for (const file of ['fonts.css','keymap.js']) await copyFile(file, `dist/${file}`);
await cp('../../DataTable/en-gb','dist/assets/keymaps',{recursive:true});
for (const file of ['character.html','character.css','character.js','character-model.js','character-world.js','ground.js']) await copyFile(file, `dist/${file}`);
await cp('vendor', 'dist/vendor', {recursive:true});
await cp('assets/character', 'dist/assets/character', {recursive:true});
await cp('assets/ui', 'dist/assets/ui', {recursive:true});
for (const file of ['platform.points','manifest.json','am16.png']) await copyFile(`assets/${file}`, `dist/assets/${file}`);
console.log('Built dist: static application, no downloaded dependencies.');
await cp('assets/sky','dist/assets/sky',{recursive:true});

await cp('assets/terrain','dist/assets/terrain',{recursive:true});
