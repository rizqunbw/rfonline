import {mkdir, copyFile, rm, cp, readFile} from 'node:fs/promises';
import {validateClientSystem} from '../client-system.js';
import {fileURLToPath} from 'node:url';
process.chdir(fileURLToPath(new URL('..', import.meta.url)));
validateClientSystem(JSON.parse(await readFile('../../System/web-client.json','utf8')));
await rm('dist', {recursive:true, force:true});
await mkdir('dist/assets', {recursive:true});
for (const file of ['index.html','style.css','app.js','sky.js','terrain.js','rf-hud.js','rf-hud.css']) await copyFile(file, `dist/${file}`);
for (const file of ['client-system.js','fonts.css','keymap.js','language.js','hud-layout.js']) await copyFile(file, `dist/${file}`);
await mkdir('dist/assets/keymaps',{recursive:true});
for(const file of ['KeyMap.dat','KeyMap_NKM.dat']) await copyFile(`../../DataTable/en-gb/${file}`,`dist/assets/keymaps/${file}`);
await copyFile('assets/language.json','dist/assets/language.json');
for (const file of ['character.html','character.css','character.js','character-model.js','character-world.js','ground.js']) await copyFile(file, `dist/${file}`);
await cp('vendor', 'dist/vendor', {recursive:true});
await cp('assets/character', 'dist/assets/character', {recursive:true});
await cp('assets/ui', 'dist/assets/ui', {recursive:true});
for (const file of ['platform.points','manifest.json','am16.png']) await copyFile(`assets/${file}`, `dist/assets/${file}`);
console.log('Built dist: static application, no downloaded dependencies.');
await cp('assets/sky','dist/assets/sky',{recursive:true});

await cp('assets/terrain','dist/assets/terrain',{recursive:true});

await mkdir('dist/assets/system',{recursive:true});
await copyFile('../../System/web-client.json','dist/assets/system/web-client.json');
