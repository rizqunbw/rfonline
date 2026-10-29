# Browser client system, version 1

Edit `System/web-client.json` and run `npm test && npm run build` from the repo
root. The build validates it before replacing `dist`; the application loads and
validates the same file at `/assets/system/web-client.json` before loading assets.
Missing/invalid settings stop startup with the offending field in the existing
load-error panel. Unknown fields are rejected to catch misspelled configuration.
There is no hidden fallback to another configuration.

| Group | Applied behavior | Origin |
| --- | --- | --- |
| mode | `local-preview` only; no network session | Existing browser scope |
| assets | Language catalog and mouse/keyboard keymap URLs | Converted uploaded assets |
| ui.fontFamily | Lucida Console, local installed font + monospace fallback | User instruction; applies to all HTML text |
| input.defaultMode | Startup mouse or keyboard mode; H still toggles | Existing two-mode controls |
| renderer | Pixel ratio cap and maximum simulation frame delta | Existing prototype tuning |
| camera | FOV, clipping planes, zoom bounds/step, follow height, pitch, drag sensitivity and keyboard turn rate | Existing prototype tuning |
| movement | Walk/run speed, supported step height/drop and arrival radius | Existing prototype tuning, world units/second |
| stamina | Drain/recovery per second and exhausted recovery threshold | Existing prototype tuning; capacity stays 100 |

These are **web defaults**, not extracted native client/server gameplay values.
The ten proven native INI reads are kept separately under `analysis/`.

Example: change `camera.distance` to `10` and `input.defaultMode` to `keyboard`.
After rebuilding, the game starts 10 world units away with WASD controls; the
Options slider and mode indicator match. Camera projection and mouse picking
use the same FOV. Settings changed through Options last for the current page
session; reloading restores JSON defaults. Query-string headwear selection is
preserved. Native keyboard bindings still come from the supplied DAT files.

`Map/Platform01/client-system.js` owns the strict schema, immutable runtime
configuration, camera clamp and stamina transition. `app.js` consumes it in the
real movement/render loop; this is not an unused config export. Diagnostics are
available at `platformDiagnostics().system` after successful startup. Language
and keymap loaders use the configured same-site relative paths. The frame cap
prevents huge movement after a stalled tab. Terrain height tests still gate
movement; there is no new wall collision or pathfinding claim.

Build output includes only the JSON and browser modules. `rf_online.bin`, INI
fallback reconstructions, disassembly and native libraries are not web assets.
Audio, server connection, combat simulation and item authority remain future
systems; unsupported settings are not presented as working options.
