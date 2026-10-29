# Native client integration status

The browser now loads the input catalog recovered from the supplied
`rf_online.bin` (SHA-256
`951e1056875c27f717bfb62d25ffc68d36337416e16d0b7ccc0f7c42b534d2c6`).
The [extractor](tools/export_native_input.py) checks the exact binary hash and
instruction operands establishing the table layout. The build validates and
copies [the catalog](analysis/native-input.json) to
`assets/system/native-input.json`; the application loads it before parsing the
original `KeyMap.dat` and `KeyMap_NKM.dat`.

## Running in the website

- All 76 command records, seven sections, 86 key names/VK codes and three
  modifiers are loaded from that extraction. The browser adapter translates
  Windows virtual keys to physical browser codes, including numpad operators,
  Insert/Delete/Home/End and punctuation omitted by the previous hand-written
  token list. Native command indices are preserved on parsed bindings.
- Mouse mode binds 76 native commands; keyboard mode binds 72 because its
  supplied file omits four. This does **not** mean all command handlers are
  implemented. Existing movement, camera, panel and HUD handlers remain the
  browser implementation; commands without handlers do not gain native behavior.
- The three additional CHAT bindings remain explicitly marked `uploaded-chat`;
  they are present in the supplied INI files but absent from the generic native
  table. ENTER is a browser chat extension, not an invented native table entry.
- Plain keys for Ctrl chords, H mode switching, Shift sprinting and movement
  priority preserve the user's requested browser controls. Native Ctrl behavior
  is not being emulated exactly. Unknown key tokens (`?`) stay unbound; unknown
  command names/sections or a missing/invalid native catalog stop initialization
  with an error rather than silently falling back to guessed definitions.
- `platformDiagnostics().nativeInput` reports the source hash and record counts.

The map, character, sprite images, language catalog and web system settings
continue using the repository's existing converted original assets. They are
not extracted from the executable's machine code.

## Still not a complete native client

The [43,924 successfully decompiled native functions](analysis/decompiled/README.md)
are research pseudocode, not executable JavaScript or buildable C/WASM. Three
functions failed. A complete port requires verified implementations of game
state, combat, inventory rules, UI behavior, network protocol, audio and native
rendering dependencies. Imported DLL implementations and referenced native
configuration/EDF data are not included in the BIN. No server connection,
combat system or gameplay statistics are fabricated by this integration.

[Gommo Studio's separately decoded editor](../Tools/GommoStudio/README.md) provides
named archive, mesh, skeleton and animation readers for further format research;
its Go pseudocode is not silently substituted for the RF client's behavior.

## Validation

`npm test` checks real uploaded keymaps against the extracted records, both
control modes, malformed catalogs, missing loads and the browser VK adapter.
`npm run build` validates both system configuration and native input data.
`Map/Platform01/scripts/smoke_hud.py` exercises rendered desktop/mobile HUD,
movement, mode switching, chat isolation, equipment, camera and panels.
