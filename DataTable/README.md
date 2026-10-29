# Original input tables

## UI language

`en-gb/Language.xlsx` is the uploaded workbook, unchanged. Its `NDLanguage`
sheet contains 4,321 `serial` / `Phrase` records after the two header rows.
`python DataTable/tools/export_language.py` writes `Map/Platform01/assets/language.json`
with the workbook SHA-256 and the exact phrases; formulas, duplicate IDs and
invalid records are rejected. The exporter does not execute workbook content.

The game HUD uses serial IDs through `language.js` and `hud-layout.js`, including
the Character sections, item tooltip fields, menu labels and control mode
messages. `data-language-id` attributes identify label provenance in the DOM.
Source spelling, punctuation and capitalization are retained. The formatter
supports the native `%s`, `%d`, `%f` placeholders and literal `\\n` line breaks;
missing serials fail explicitly rather than falling back to invented text.

Character labels use IDs 1087–1121, 2025, 2074/2077/2078 and 4252. Item tooltip
fields use 872, 879–884, 892/893/895/900 and 2074/2075. Names/types come from
the known equipment slot and armor resource 171, not an invented item name.
Unknown combat, mastery, resistance and item values are `—`; percentages,
requirements, prices, descriptions and upgrades are not copied from screenshots.
The initial local HP/FP/SP and level remain existing prototype values.

The workbook does not contain the standalone `KILL`, `DEATH`, `FPS` labels or
the `White Hole` map title. These are retained from the user's reference/native
HUD and identified as reference labels or asset names; they are not presented
as Excel translations. Technical key names, numeric values, user-entered chat
and names are data. Native sprite text also remains original artwork.
Custom welcome text was removed. The HUD displays `Server: None`, composed
from serials 1979 and 103, since no live RF game server is connected.

The Character window has General, Status, Ability/Combat/Crafting, and elemental
resistance sections with independent scrolling. The item information frame
opens on equipment hover or keyboard focus; touch pins it until closed. Its
icon box is deliberately empty pending the actual item icons. One belt row is
visible by default, with five rows available under Options → Short key.

## Input

`en-gb/KeyMap.dat` (mouse mode) and `en-gb/KeyMap_NKM.dat` (keyboard mode)
are the uploaded originals, including their CRLF line endings. The build copies
them unchanged to `assets/keymaps/`; the browser parses the bindings as data.

The game starts in mouse mode. H switches modes and cancels held input and
the previous click destination. Per the user's interpretation of the client
tables, Ctrl is an optional command prefix outside text entry: NKM `Ctrl+W`
is W to move forward, and Ctrl+I is also I to open Inventory. Explicit Alt and
Shift bindings remain distinct. Browser-reserved combinations may be intercepted
by the browser; the plain-key bindings avoid needing those combinations.

Mouse mode: click walkable terrain to walk there, arrows to move, W toggles
walk/run, A switches the combat pose. Keyboard mode: WASD moves, Q/E turns the
camera, N toggles walk/run, semicolon switches the combat pose. Right drag and
wheel control the camera in both modes. Shift sprint and digit hotbar shortcuts
are retained browser conveniences. Enter focuses local chat; text entry prevents
movement, panel commands and H from firing.

I/C/M/O open Inventory/Character/map/settings. The two native character panels
can stay open together and be dragged. F1–F10 activate slots on the selected
belt; backslash cycles five belts. Empty slots open a local action picker when
clicked, and right click clears assignments. Alt+H hides/restores the HUD.
Backquote toggles character labels. Bindings containing `?` are unbound, and
unimplemented actions report that they are unavailable rather than simulate a
server action. N conflicts with POST_WINDOW in NKM; the implemented combat
MOVE_MODE binding takes precedence. No jump/attack/loot or server inventory is
implemented by these tables.

Click movement follows a straight line along valid sampled ground; it stops
at an unsupported step or missing floor. It is not a pathfinding or wall
collision system. Raw keymap hashes are recorded in `en-gb/uploads.json`.

All HTML text uses Lucida Console through the shared `fonts.css`. This references
the locally installed Windows font; no proprietary font binary is bundled.
Systems without Lucida Console fall back to their monospace font. Text baked
into supplied sprite images remains the original artwork.
