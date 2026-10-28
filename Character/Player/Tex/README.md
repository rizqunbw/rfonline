# Original player textures

All 15 supplied `.RFS` files are preserved byte-for-byte. `manifest.json` records
archive sizes, SHA-256 hashes and every embedded RFT entry. Texture and mesh
archives may have identical basenames: `Tex/BFF00.RFS` is distinct from
`Mesh/BFF00.rfs` and must never replace it.

RFT files in these archives are DDS images with an XOR-obfuscated 128-byte header.
The character converter decodes the five Bellato female 171 textures losslessly
to PNG. Other uploaded texture archives are retained and validated for future meshes.
