# Reading the supplied RF client

`../../rf_online.bin` is preserved byte for byte (8,451,006 bytes, SHA-256
`951e1056875c27f717bfb62d25ffc68d36337416e16d0b7ccc0f7c42b534d2c6`).
It is a **Windows x86 PE32 GUI executable**, not a configuration archive.
No native code was run. It is stored in GitHub but excluded from the web build.

`rf-online.json` is a reproducible static inventory: five sections, 24 imported
DLLs, 199 named exports, 159 resource references, and configuration string
neighborhoods with file offsets and virtual addresses. There are 17,854 bytes
after the last section; their purpose is not established. The `.LINGO2` section
name alone does not identify a packer. There is no COFF symbol table in objdump;
the exported names are not a recovered source tree. Header timestamps are not
proof of a release date.

Run `python System/tools/inspect_client.py` from the repository root to regenerate
the inventory using only Python's standard library. It validates PE bounds and
never invokes the uploaded executable. `objdump -d -Mintel rf_online.bin` can
generate disassembly locally; the full listing is deliberately not committed.

## Findings with different levels of evidence

| Observation | Evidence | Implication for the web implementation |
| --- | --- | --- |
| Direct3D 9 | Imports `d3d9.dll`, `d3dx9_36.dll` | Existing WebGL renderer replaces the Windows graphics API |
| Native input | Imports `DINPUT8.dll` | Browser pointer/keyboard events and original keymaps |
| Native audio | Imports `mss32.dll`, `WINMM.dll` | Audio still needs a browser implementation and suitable assets |
| Socket networking | Imports `WS2_32.dll` | Does not disclose the packet protocol or provide a game server |
| INI reader/writer | Imported `GetPrivateProfile*`, `WritePrivateProfileStringA` | Configuration is also loaded from external files |
| Sprite and player assets | RFS/SPR/BSP/EDF paths in data sections | Consistent with supplied assets; not proof every listed resource is used |
| Scaleform/GFx | SWF/GFX, font-library and RF_FontConfig strings | Native UI implementation references; browser HUD is separately implemented |
| Language table | `.\DataTable\%s\NDLanguage.edf` string | A native EDF reference, not evidence that the executable directly opens XLSX |

## Ten traced settings

`verified-settings.json` records ten section/key/fallback associations confirmed
from x86 call arguments. `config-calls.asm` contains the corresponding excerpts.
The imported `GetPrivateProfileIntA` IAT slot is `0xaff214`, and
`GetPrivateProfileStringA` is `0xaff1fc`. x86 stdcall arguments are pushed right
to left; strings were resolved through PE sections rather than guessed from
nearby text.

| File | Section / key | API fallback | Call address |
| --- | --- | --- | --- |
| DataTable/GameSetting.ini | Performance / AutoVisualFieldAdjustment | 0 | 0x5286d5 |
| DataTable/GameSetting.ini | Performance / VisualFieldAdjustmentLevel | 5 | 0x5286fd |
| DataTable/GameSetting.ini | Camera / Mode | 1 | 0x528725 |
| DataTable/ClientSystem.ini | Network / ConnectTime | 90 | 0x732263 |
| R3Engine.ini | Path / MapPath | `.\Map\` | 0x821a88 |
| R3Engine.ini | Path / SystemPath | `.\System\` | 0x821aa8 |
| R3Engine.ini | Path / EntityPath | `.\Map\Entity\` | 0x821ac8 |
| R3Engine.ini | Path / EffectPath | `.\Effect\` | 0x821ae8 |
| R3Engine.ini | Path / ScreenShotsPath | `.\ScreenShots\` | 0x821b08 |
| R3Engine.ini | Path / SoundPath | `.\Snd\` | 0x821b28 |

The camera reader resets values >= 5 to 1 at `0x52872e`; this does not establish
what each camera mode means. ConnectTime is multiplied by 1,000 at `0x732275`,
consistent with converting seconds to milliseconds. The actual installed INI
values can override every fallback. The readable `.ini` files in `fallbacks/`
are partial reconstructions, clearly labeled, and never overwrite native files.

Equivalent pseudocode for these reads (manually reconstructed, not original source):

```c
autoVisual = GetPrivateProfileIntA("Performance", "AutoVisualFieldAdjustment", 0, "./DataTable/GameSetting.ini");
visualLevel = GetPrivateProfileIntA("Performance", "VisualFieldAdjustmentLevel", 5, "./DataTable/GameSetting.ini");
cameraMode = GetPrivateProfileIntA("Camera", "Mode", 1, "./DataTable/GameSetting.ini");
if (cameraMode >= 5) cameraMode = 1;
connectInterval = GetPrivateProfileIntA("Network", "ConnectTime", 90, "./DataTable/ClientSystem.ini") * 1000;
GetPrivateProfileStringA("Path", "MapPath", ".\\Map\\", mapPath, 128, ".\\R3Engine.ini");
// Five more Path reads use the same API; see the table above.
```

Other nearby strings (ShadowDetail, SoundVol, MusicVol, Gamma, font names, etc.)
remain **candidates** in the inventory. Their proximity is not treated as a
verified section/key relationship or a value.

## New browser system

The active configuration is [`../web-client.json`](../web-client.json); its
contract and integration are in [`../WEB-CLIENT.md`](../WEB-CLIENT.md).
It preserves the working map, character, HUD, Lucida Console and Excel text.
It is a new browser implementation, not a decompilation or execution of the BIN.
Movement/stamina numbers come from the existing web prototype, not these ten
native settings. No native server, login, combat, inventory authority or packet
protocol is recreated by a PE inventory. Those require further asset/protocol
work; there is no automatic connection to endpoints found inside the binary.
