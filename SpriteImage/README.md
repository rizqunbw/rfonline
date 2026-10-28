# Original RF Online sprites

`common/` contains the 26 original uploaded SPR archives (746 images).
`en-gb/` contains the five additional original archives: `itemupgrade.spr`,
`common.spr`, `login.spr`, `CashShop.spr`, and `loading.spr` (368 images).
Original names and bytes are preserved. Each folder has an upload SHA-256
manifest and a decoded image catalog. Assets are data, never executed.

The supplied files use SPR version 1.1: a little-endian float version and u32
group count, followed by a u32 image count for each group. Every image starts
with six u32 values: D3DFORMAT, logical width/height, stored width/height,
payload byte count. Pixel payload follows directly. Observed formats are
DXT1, DXT5, A8R8G8B8 (BGRA byte order) and R5G6B5. The decoder validates sizes,
bounds and full-file consumption. Logical dimensions crop texture padding.

Run from the repository root with Python and Pillow installed:

```sh
python SpriteImage/tools/convert_spr.py
python SpriteImage/tools/test_spr.py
npm run build
```

The browser build ships 40 selected PNG roles from the original common sprites
with provenance in `Map/Platform01/assets/ui/manifest.json`. It includes the
status frame, bars, radar, footer, action icons and inventory equipment panel.
No replacement artwork is generated. The additional en-gb archives are cataloged
and retained for subsequent screens; login, cash shop and upgrade services are
not implemented by uploading their artwork.

The default map entry now opens character mode with the HUD. Inventory displays
the equipped Bellato armor and local empty bag slots; switching hair/helmet
changes the rendered mesh. Chat and names are session-local. Sprint uses SP;
HP, FP, level, currency and EXP are prototype starting values without combat or
server progression. The combat action switches the original animation only.
Movement still follows map ground; wall and camera collision are not implemented.

Keyboard: WASD move, Shift sprint, drag/arrow keys camera, wheel zoom, I inventory,
C character, M map, O settings, H help, 1–0 hotbar, Enter local chat, Escape close
panel/pause. Flight beacon mode remains available at `/?character=0`.
