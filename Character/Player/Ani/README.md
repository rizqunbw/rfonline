# Uploaded player animations

All **57 uploaded files** are stored here under their original names and casing, unchanged:

- 52 RFS animation archives (all 52 listed by `RFSInfo.dat`).
- 2 loose Bellato male standing ANI clips.
- 2 `.ANI.tmp` files and `RFSInfo.dat`.

`uploads.json` records original file sizes and SHA-256 hashes. `catalog.json` records every archive entry's offset, length and SHA-256, ANI object/key counts, end ticks and object-name inventory. All **4,102 archived ANI entries** parsed completely with finite key values and no trailing bytes. They have **3,844 distinct names**; repeated names remain associated with their archive and must not be blindly flattened or overwritten.

The loose combat stand clip is byte-identical to its entry in `BMCOA.RFS`; the loose peace stand clip is byte-identical to its entry in `BMETA.RFS`. Each `.tmp` is a ZIP containing the identical corresponding loose ANI. They are retained as uploaded and are not used as alternate animation formats.

Archive prefixes identify player groups: AC (Accretia), BF/BM (Bellato female/male), and CF/CM (Cora female/male). `NewGESTURE` and `RSTAFF` are also preserved. The 52 original RFS archives total 142,551,988 bytes. This completed ingestion supersedes the earlier pending-upload inventory.

## Inspect, extract and validate

From repository root, Python 3 only:

```sh
python Character/Player/tools/catalog_ani.py
python Character/Player/tools/test_ani.py
python Character/Player/tools/extract_rfs.py Character/Player/Ani/BMCOA.RFS Character/Player/Ani/extracted/BMCOA
python Character/Player/tools/inspect_ani.py Character/Player/Ani/BELMALE_COMBAT_STAND_NONE_NONE_01_00.ANI --keys
```

Original archives remain the committed source of truth. Extracted copies can be regenerated under the ignored `extracted/<archive>/` directory, keeping same-named clips from different archives separate. The inspector's optional `--keys` output includes quaternion XYZW, position, scale and scalar values at their original integer ticks. It applies no coordinate conversion or animation retargeting.

## ANI layout observed

Little-endian uint16 object count, followed by each object's 100-byte null-terminated EUC-KR name, two uint16 fields (activity and declared end tick), and 36 reserved bytes. Four tracks follow: uint16 count then float32 values and uint32 tick per key. Rotation has four floats; position and scale have three; the final scalar channel has one. That scalar channel's gameplay/rendering meaning is still unknown. Timestamps are preserved even when they exceed the declared end tick. The reference importer uses 160 ticks per frame; playback seconds/FPS are not inferred from the files alone.

Layout reference: [cbb-rf-online-addon](https://github.com/Cardboard-box-a/cbb-rf-online-addon/tree/02dfdc4f62fac8f266cf4c0ff85c57172b48bcbf), MIT license retained at `../THIRD_PARTY_LICENSE.txt`.

## Current scope

This step preserves, catalogs and validates animation data. It does not yet play animations on the browser character or establish that clips from different player groups share a compatible rig. Matching skeleton (`.bn`) files are still needed to establish hierarchy and rest pose; textures are also needed for the previously supplied BFF00 armor meshes. Object/bone names in the catalog support that next compatibility check.
