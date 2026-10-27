# RF Online Player Animation Assets

Animation archive inventory, validated from user-supplied files on 2026-10-28.

- 52 original RFS archives, 142,551,988 bytes, 4,102 archive entries.
- Four standalone BELMALE ANI/ANI.tmp files and RFSInfo.dat are separate.
- RFS entry headers use uint32 count and 64-byte entries (56-byte EUC-KR filename, uint32 offset, uint32 size).
- All 52 archive entry tables and payload bounds were checked. This is **not** yet a validation of animation decoding or skeleton compatibility.
- Prefixes: AC (Accretia), BF/BM (Bellato female/male), CF/CM (Cora female/male). Also NewGESTURE and RSTAFF.
- Existing extraction helper: ../tools/extract_rfs.py. Extract archives into individually named directories to avoid filename collisions.

## Pending source binary upload

The uploaded binary archives are **not included in this commit**: the connected GitHub API accepts text/base64 inputs but cannot read sandbox files directly, and embedding 142 MB in tool arguments is not feasible. Do not mistake this inventory for uploaded assets.

Expected layout: Character/Player/Ani/*.RFS, plus the four standalone ANI/TMP files and RFSInfo.dat. For local Git upload, copy the supplied files to this directory and use Git LFS for large archives before committing. Confirm that the remote accepts LFS and its quota before uploading. Keep original archives byte-for-byte and retain the mesh directory unchanged.

Next stages: ingest Bone and Tex; parse animation channels, skeleton bind poses and mesh skin weights; validate correspondence; render animated characters in WebGL.
