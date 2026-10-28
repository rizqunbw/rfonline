# RF Online browser prototype

The application and original uploaded assets are in [Map/Platform01](Map/Platform01/README.md), matching the game client map layout.

Player mesh archives, extracted RF meshes and inspection tools are in [Character/Player](Character/Player/README.md).

Original UI archives and the sprite decoder are in [SpriteImage](SpriteImage/README.md).
The website opens Bellato character mode with the original sprite HUD. Select
**Masuk Sektor**, then use I for inventory, C for character, M for map, O for
settings, or Enter for local chat. Flight exploration remains at `/?character=0`.

Vercel supports the repository root (`.`; recommended) or `Map/Platform01` as Root Directory. Use Framework Preset **Other** and the checked-in `vercel.json` without conflicting dashboard overrides. From repository root, `npm run build` produces `Map/Platform01/dist`; from `Map/Platform01` it produces `dist`. The public website remains at `/`.
