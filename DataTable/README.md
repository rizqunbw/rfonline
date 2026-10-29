# Original input tables

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
