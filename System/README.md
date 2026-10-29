# Original RF Online System files

The supplied main client is archived at [`../rf_online.bin`](../rf_online.bin).
See [static analysis and traced INI reads](analysis/README.md) and the
[new browser configuration system](WEB-CLIENT.md). The JSON system is active
in the web application; the original Windows executable is not executed.
The [native input port](NATIVE-PORT.md) now uses the BIN's extracted command and
key tables in the browser. Its documented scope distinguishes loaded command
definitions from implemented gameplay behavior.

All 57 files from the supplied `System.zip` are stored at the same relative
paths, including `mouse/` and `shader/`. `uploads.json` records the archive
hash and every original file hash. The only intentional modification is
`font.ini`: the original `Verdana` setting is changed to `Lucida Console`, as
requested. The original content and replacement hash are recorded in the
manifest; all other 56 source files are byte-identical.

Findings from binary headers and metadata are in `catalog.json`:

| Asset | Observed format / role |
| --- | --- |
| `font.ini` | Native font family setting, now Lucida Console |
| `uifont.ttf` | TrueType family `천리안체H`; not Lucida Console |
| `010.TTF` | TrueType, 2,542 glyphs, platform 3 / encoding 5 cmap; no decoded family name |
| `rfoemf.dat` | TrueType despite its extension; family `MDmorrisOEM9` |
| `unifont.ttf` | Empty in the uploaded archive; preserved as supplied |
| `mouse/*.ani` | Seven Windows animated cursors in RIFF ACON containers, distinct from RF player animation files |
| `shader/*.vsh`, `*.psh`, `*.nvv`, `*.nvp` | Legacy shader source/assembly |
| `shader/*.vso`, `*.pso` | Direct3D compiled shaders; cannot be loaded as WebGL GLSL |
| `shader/*.sho`, `init.r3o` | Opaque native RF resources; not decoded |
| `ccrlogo.dds`, `sun.dds`, `titlelogo.tga`, `console.jpg` | Original images; image payloads decode successfully |
| `ChatCommand.ini`, `default.cfg` | Native chat/editor configuration; not applied as website hotkeys |
| `DefaultSet.*`, `idll.rdt` | Retained native data; not decoded |

All seven ANI files declare a RIFF length eight bytes larger than their actual
file length. Their contained chunks fit the actual bytes; the catalog records
this source inconsistency without rewriting the originals.

The website's shared `Map/Platform01/fonts.css` applies Lucida Console to all
HTML text, including map HUD, panels, inputs, menus and the character preview.
It uses the font installed on the user's device. The archive contains no font
identified as Lucida Console, so none of its unrelated fonts is relabeled or
used as a substitute. Devices without Lucida Console use a monospace fallback.
Text already painted into original sprite artwork is preserved.

The native assets are archived in GitHub for later conversion. The static website
ships the assets it currently uses, not the unused native shaders and fonts.
Uploading the archive does not activate native client libraries, patch lists,
chat commands or rendering effects. Files such as `DeleteFileList.txt` are data
and are never executed as instructions.

To reproduce metadata and verify integrity with Pillow and fontTools installed:

```sh
python System/inspect_assets.py
```
