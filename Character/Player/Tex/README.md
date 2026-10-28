# Original player textures

All 28 supplied `.RFS` files are preserved byte-for-byte. `manifest.json` records
archive sizes, SHA-256 hashes and every embedded RFT entry. Texture and mesh
archives may have identical basenames: `Tex/BFF00.RFS` is distinct from
`Mesh/BFF00.rfs` and must never replace it.

RFT files in these archives are DDS images with an XOR-obfuscated 128-byte header.
All 752 embedded payloads are checked for DDS decodability. The character converter
decodes the five Bellato female 171 textures plus default face and hair textures
losslessly to PNG. Other uploaded texture archives are retained for future meshes.

`uploads-default.json` records the latest 13 archives and `RFSInfo.dat`, including
original byte counts and checksums. The registry remains separate from the Mesh
and Ani registries. Coverage is recorded in `../resource-summary.json`; archives
absent from its list are still preserved. Duplicate filenames with differing
payload hashes remain ambiguous rather than silently replacing an earlier texture.
