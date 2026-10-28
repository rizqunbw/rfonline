# Player mesh research — BFF00

Player animations and their archive catalog are now stored in [Ani](Ani/README.md). Matching skeletons and mesh textures are the next dependencies for assembling and animating a character.

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

Next useful inputs: matching player texture files/archive, skeleton (`.bn`), and animations (`.ani`). A full character may also need separate body/head/face assets. This step extracts and validates the supplied armor meshes; it does not yet add a character to the browser game.

## RFS layout observed

All integers are little-endian. A uint32 entry count is followed by 64-byte records: 56 bytes for a null-terminated EUC-KR filename field, uint32 absolute payload offset, uint32 payload length. For this sample, the 20-record table ends at byte 1,284; payload ranges are contiguous and cover the remainder exactly. Bytes after a name's null terminator are ignored rather than interpreted as metadata.
