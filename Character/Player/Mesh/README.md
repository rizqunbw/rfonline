# Original player mesh archives

The 15 supplied `00` RFS archives contain 354 RF MSH files. Every payload parses
completely with the standard MSH inspector: 102,742 vertices and 172,745 triangles
across all variants, not one assembled player. `catalog.json` records payload
hashes, mesh metadata, workbook resource IDs and matching texture candidates.

`BFF00.RFS` in the new upload is byte-identical to the earlier `BFF00.rfs`. The
existing lowercase filename is retained as the only canonical copy so Windows
checkouts do not collide and existing references continue to work. All other
uploaded names and binary bytes are preserved. `uploads-00.json` records the
uploaded-to-repository path mapping and SHA-256 checksums, including `Player.xlsx`.

Only the previously extracted BFF00 files are checked in individually. Extract
other archives on demand into an ignored directory:

```sh
python Character/Player/tools/extract_rfs.py Character/Player/Mesh/AAF00.RFS Character/Player/Mesh/extracted/AAF00
```

Names alone do not establish rig or material compatibility. The Excel resource
table supplies the BoneID; each embedded MSH supplies its texture filename.
213 uploaded meshes have all referenced base textures available. Missing texture
names are listed in `../resource-summary.json`; missing workbook resources remain
explicit in `../resources.json`.
