# Platform01 Expedition

Static WebGL exploration game using uploaded RF Online Platform01 data. Fly through the geometry and find five beacons, or open `character.html` to inspect the original Bellato female armor and enter `/?character=1` to walk around the map in third person. The character renderer uses a locally vendored Three.js module; no npm install or external CDN is needed. This is not a full RF Online client: combat, wall/camera collision, networking and persistence are not implemented.

## Run

Node 18+ and Python 3 are sufficient. No npm installation is required.

Run from the `Map/Platform01` folder:

```sh
cd Map/Platform01
npm run build
npm test
npm start
```

Open port 3000 in a browser. WASD moves horizontally, mouse (pointer lock) or arrow keys looks around, Q/E changes height, Shift boosts, Escape pauses. Touch devices use on-screen controls and drag to look. Five illuminated beacons are collected within 9 scene units. Flight has no collision. The overhead map shows position and objectives.

Character preview: drag to orbit, scroll/pinch to zoom, choose idle/walk/run/combat stance, pause or change playback speed, and optionally show bones. The original default face is included; choose default hair or the armor helmet, with the selection carried into the map link. WASD moves on the preview floor. In third-person map mode, WASD walks and Shift runs, with static terrain height sampling. This mode has no beacon objective. See `../../Character/Player/README.md` for source conversion details and reproducible validation.

Character browser tests: serve `dist` then run `python scripts/smoke_character.py http://127.0.0.1:3000` (Playwright and Chromium). This checks all four clips, pause, orbit, movement, mobile controls, map rendering and explicit missing-texture errors. Python converter dependencies are only needed to regenerate the committed character assets.

## Data and limitations

Original uploads remain in `assets/source`. BSP version/header value is 39. The experimental extraction reads 253,803 float32 XYZ records starting at byte 2,603,235, followed by BGRA vertex colors at byte 5,648,871. Positions are scaled by 0.01 for navigation; this scale is an application choice. Tests compare every exported coordinate and color with the source bytes. Structural consistency does not establish complete format semantics.

`scripts/convert.py` regenerates `assets/platform.points` and the manifest for this specific sample. The BSP header identifies vertices, colors, face records, face IDs, vertex IDs, and material groups. Polygon fans decode into 271,641 static triangles; 19 animated/invisible material groups are omitted. R3M records supply 595 material names. Original face topology is used. The browser now uses the terrain export from `scripts/convert_terrain.py`, with original base textures, per-corner UVs and baked lightmaps. The earlier flat-color mesh is retained for source-integrity tests. EBP and CAM are retained for later decoding. `am16.dds` was decoded to PNG using Pillow; it appears only in the asset panel because its material mapping is not established. Platform01.r3t and Platform01Lgt.r3t are now included. Remaining differences include secondary material layers, animated objects and effects. Beacon missions and flight controls are new prototype gameplay.

## Vercel

`vercel.json` builds the static site to `dist`. Import this project into Vercel with Root Directory **Map/Platform01**, Framework Preset **Other**, build command `npm run build`, output `dist`, and no dependency install requirement. Alternatively, run `vercel --prod` from an authenticated local Vercel CLI. Source binary uploads are excluded from CLI deployments; only extracted mesh/points, the manifest and decoded texture are copied to the public build.

Deployment requires access to a Vercel account and working network access. This workspace has not been deployed merely by generating this configuration.

Format layout reference: [cbb-rf-online-addon](https://github.com/Cardboard-box-a/cbb-rf-online-addon), commit `02dfdc4f62fac8f266cf4c0ff85c57172b48bcbf`. MIT notice is retained in THIRD_PARTY_LICENSE.txt.

Browser validation: `python scripts/smoke.py` against the running server (requires Playwright and Chromium). It flies to all five beacons using keyboard input, checks victory/restart/pause and mobile controls.

## Uploaded sky assets

The menu now switches between **Platform01 Sky 1** (2,132 static triangles, 9 textures) and **Platform01 Sky 2** (1,158 static triangles, 13 textures). Geometry comes from the uploaded R3E files, texture references and tints from R3M, and images from embedded DDS payloads in R3T. All 22 textures are decoded losslessly to PNG. UVs are indexed by polygon corner. Both sets are loaded locally without external services.

The sky is rendered around the camera using rotation only. These are static previews: Sky 2's two animated object groups are omitted, and secondary material layers and UV scroll effects are not simulated. MTF files are retained as metadata; rendering uses R3T's embedded texture directory. The original game's sky selection, animation timing and full rendering behavior have not been reproduced. Terrain textures and lightmaps are provided separately by the newly uploaded Platform01 archives.

To regenerate the sky outputs, run `python scripts/convert_sky.py` (requires Pillow), then `npm run build`. Validate original source hashes, all decoded texture pixels, and every exported sky position/UV/color using `python scripts/test_sky.py`. Browser tests also switch both skies, test mobile selection, and verify that missing textures produce an explicit load failure.

## Terrain textures and deployment fix

368 original terrain textures and 9 lightmaps are decoded by `python scripts/convert_terrain.py` (Pillow required) and rendered by terrain.js. DDS header obfuscation is decoded using the MIT reference format. Run `python scripts/test_terrain.py` to verify exported pixels, topology and UVs. The R3X/RVP/SPT files are retained but their gameplay/effect behavior is not interpreted.

A repository-root package.json and vercel.json now support Vercel projects imported with the default root directory. No dashboard change is required unless custom build/output overrides conflict. The alternative Map/Platform01 root remains supported.
