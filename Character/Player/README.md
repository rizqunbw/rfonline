# RF player assets and Bellato character

Original animations are in [Ani](Ani/README.md), skeletons in `Bone`, and textures in [Tex](Tex/README.md). The website now renders Bellato female armor 171 with `BelFemale.bn`, five matching RFT textures, and idle/walk/run/combat-stance ANI clips. Open `/character.html` for the interactive preview and `/?character=1` for third-person walking in Platform01.

## Player.xlsx resource mapping

The original workbook is preserved at `Player.xlsx`. It contains 5 Bone rows,
6,808 Mesh rows and 2,056 Ani rows. `tools/catalog_player.py` reads cell values
as data, preserves hexadecimal IDs, and matches Windows paths/names without case
sensitivity. It does not execute formulas or follow workbook external links.

All 354 meshes in the 15 uploaded `00` archives have matching workbook IDs.
All 5 listed skeleton/BBX pairs and all 2,056 listed animation names are available.
6,454 mesh rows refer to files outside the uploaded archive subset; they remain
`missing`, not silently substituted. Matching base textures exist for 213 of the
354 uploaded meshes. This does not assert that all equipment sets are complete or
that every rig has been rendered. Default Bellato face meshes remain missing.

`resources.json` maps workbook IDs to actual repository paths and archive
offsets/hashes; `resource-summary.json` summarizes coverage. `Mesh/catalog.json`
adds geometry, bone and texture references for every uploaded mesh. Resource
metadata stays outside the static public build.

The Bellato converter now selects the five equipment IDs `001004AB`, `001000AB`,
`001003AB`, `001005AB`, `001002AB`, resolves them directly from the archive, and
uses their shared BoneID `00000001` to select `Bone/BelFemale.bn`. The resolved
geometry, rig, texture pixels and animation tracks are identical to the previously
rendered character. New races/equipment are cataloged but are not yet offered in
the website selector.

To regenerate the mapping, install `openpyxl`, then run these from repository root:

```sh
python Character/Player/tools/catalog_player.py
python Character/Player/tools/build_character.py
python Character/Player/tools/test_player_resources.py
```

`tools/player_resources.py` rejects missing, ambiguous or stale archive references
and verifies the selected skeleton hash before returning a payload. Mesh and Tex
archives with the same basename are separate assets and must stay in their own
directories. See [Mesh](Mesh/README.md) for extraction and upload checksums.

## Current browser character

The renderer assembles five armor parts (14 mesh objects, 3,098 triangles), with 25 skeleton bones. Helmet parenting is exported as a rigid one-bone skin; all other parts retain the supplied skin weights. Face and hair geometry were not supplied. Other armor sets refer to texture suffix 184, which is absent from these uploads, so they are not offered as textured variants.

`tools/build_character.py` produces the committed web assets under `Map/Platform01/assets/character`. Regeneration requires Python 3, numpy, scipy and Pillow; the static Vercel build only copies these outputs and needs no Python dependencies. The renderer vendors Three.js 0.152.2 locally with its MIT license.

```sh
python Character/Player/tools/build_character.py
python Character/Player/tools/test_character.py
npm run build
```

Coordinates are converted from source Max Z-up to right-handed Y-up; inverse bind matrices and matching bone-name ANI tracks drive real skeletal deformation. ANI quaternions are conjugated following the reference importer. Preview timing explicitly assumes 160 ticks/frame at 30 FPS and provides a speed selector. Root horizontal travel is removed for in-place animation; the movement controller supplies travel. Scalar/effect tracks and object channels outside the skeleton are omitted and listed in the generated manifest. Character height is normalized to 1.8 map units for this prototype; this is not a verified RF unit conversion.

The map controller follows static walkable triangle surfaces and rejects excessive steps or gaps. It does not implement wall/camera collision, RF combat, equipment stats, networking or persistence.

## Mesh archive research

Original upload: `Mesh/BFF00.rfs` (1,143,191 bytes), preserved byte-for-byte.
Extracted RF meshes: `Mesh/BFF00/*.msh`.
Archive offsets, payload checksums, mesh counts, bounds and texture/bone references: `Mesh/BFF00.manifest.json`.

## What was established

This RFS is a flat archive containing **20 uncompressed standard RF MSH files**, not an executable converter. Extraction is byte slicing; renaming the archive to `.msh` would not work.

The names identify Bellato female armor parts: GLOVES, HELMET, LOWER, SHOES and UPPER, each with variants 168, 171, 172 and 176. Together the entries contain **59 mesh objects, 5,018 vertices and 8,600 triangles**. These totals span alternative armor sets, not one assembled character.

Every extracted MSH was parsed completely, including object matrices, vertices, triangle indices, per-corner normals/UVs, texture references, bone-name tables and skin weights. Unused weight slots have bone index -1 and can contain arbitrary legacy padding (including NaNs); the inspector validates active slots and preserves all original bytes. No skeleton rest pose, animation or texture image is supplied by this archive.

Ten texture filenames are referenced: GLOVES, HELMET, LOWER, SHOES and UPPER with texture suffixes **171** and **184**. Do not assume the texture suffix equals the mesh variant. Parent and skin bone names are recorded in the manifest for matching a future skeleton.

## Reproduce

From repository root, using Python 3 (no external dependencies):

```sh
python Character/Player/tools/extract_rfs.py Character/Player/Mesh/BFF00.rfs Character/Player/Mesh/BFF00
python Character/Player/tools/inspect_msh.py Character/Player/Mesh/BFF00/BELFEMALE_ARMOR_UPPER_171.msh
python Character/Player/tools/test_rfs.py
```

The extractor validates names, unique entries, bounds and non-overlapping ranges before writing. Existing differing outputs are never overwritten. The MSH inspector supports the standard weighted layout verified in this upload; it explicitly rejects MESH08 and unsupported weight layouts.

## Import and next assets

The extracted `.msh` files are still RF-specific binary meshes. A compatible RF MSH importer/plugin is needed in 3ds Max; no 3ds Max import was executed here. The format was cross-checked with the [MIT-licensed RF Blender importer](https://github.com/Cardboard-box-a/cbb-rf-online-addon/tree/02dfdc4f62fac8f266cf4c0ff85c57172b48bcbf). Its license is retained alongside this document.

The supplied skeleton, ANI and Tex archives now satisfy the armor preview dependencies. A complete face/hair appearance still needs the matching default head/face meshes and textures. 3ds Max compatibility has not been tested.

## RFS layout observed

All integers are little-endian. A uint32 entry count is followed by 64-byte records: 56 bytes for a null-terminated EUC-KR filename field, uint32 absolute payload offset, uint32 payload length. For this sample, the 20-record table ends at byte 1,284; payload ranges are contiguous and cover the remainder exactly. Bytes after a name's null terminator are ignored rather than interpreted as metadata.
