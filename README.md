# RF Online browser prototype

The application and original uploaded assets are in [Map/Platform01](Map/Platform01/README.md), matching the game client map layout.

Player mesh archives, extracted RF meshes and inspection tools are in [Character/Player](Character/Player/README.md).

Native fonts, cursors, shader assets and inspection findings are in [System](System/README.md).

Game HUD labels and the native Character/item information panels use serials from
`DataTable/en-gb/Language.xlsx`. Hover equipment (tap on mobile) for its information
frame; unknown item stats remain empty until item data is connected.

Original UI archives and the sprite decoder are in [SpriteImage](SpriteImage/README.md).
The website opens Bellato character mode with the original sprite HUD. Select
**Masuk Sektor**. Mouse mode uses click-to-move; H switches to keyboard mode
(WASD movement, Q/E camera). I/C open the movable Inventory/Character windows;
M/O open map/settings and Enter opens local chat. Original key tables and
font behavior are documented in [DataTable](DataTable/README.md). Flight exploration remains at `/?character=0`.

Vercel supports the repository root (`.`; recommended) or `Map/Platform01` as Root Directory. Use Framework Preset **Other** and the checked-in `vercel.json` without conflicting dashboard overrides. From repository root, `npm run build` produces `Map/Platform01/dist`; from `Map/Platform01` it produces `dist`. The public website remains at `/`.
