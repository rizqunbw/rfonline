# Gommo Studio static decoding

The user-provided Drive file is a 73,209,856-byte **Windows x86-64 Go executable**.
SHA-256: `74ca40b941142511de43e4f912cfcd442b240810f351e8c0d6dfe3580de294e7`.
The upload exceeded the workspace transfer tool's 32 MiB limit, so the file was
downloaded from the user's shared Drive file ID
`1ZcJniuUnmj3V3uyJOypsEJ6OyGtwlP76`. Its code was never executed.

Retained Go metadata reports `go1.25.14`, entry package
`gommo/cmd/gommostudio`, module revision
`426dd69ff4c508b8d66ed9626ff1f4c547eca545`, and a modified working tree at build
time. These are embedded build records, not an authenticity or release-date
guarantee. `CGO_ENABLED=0`, `GOOS=windows`, `GOARCH=amd64`, `-trimpath=true` are
recorded in `analysis/build-info.txt`.

## What has been decoded

- **53,246 function names and entry addresses** from the Go pclntab, with checked
  function bounds and entry-offset agreement.
- **22,966 application function entries** named `gommo/…` or `main.…`.
- **896 RF format/editor functions** selected for close review. This selection
  is not the count of every RF-related function in the application.
- 3,828 source-file path entries, plus package counts and module dependencies.
  File paths are metadata; the original `.go` source text is not embedded there.

Ghidra exported **22,944 of 22,966 application functions** as pseudocode;
22 failed. Of the 896 selected RF format/editor functions, 894 exported.
The archive and index were checked for identical address ordering and counts.
[coverage.json](analysis/coverage.json) records failures, selected functions and
the archive hash. The full export is in
`analysis/application-decompiled.c.gz`, with completion/error records in
`analysis/decompilation-index.json.gz`. Twelve selected RF functions are readable
under [analysis/selected](analysis/selected).

Automatic analysis reached its 900-second limit, and Go type recovery reported
`java.io.EOFException: Invalid index: 6249792001`. The export script added 683
missing function entries from verified pclntab addresses before decompilation.
[The filtered log](analysis/analysis.log) preserves these limits. A successful
function export means the decompiler produced text; it does not validate Go ABI,
inferred pointer types, behavior, or complete executable coverage.

The executable is retained in the working analysis directory rather than
committed as a 70 MiB binary or shipped to Vercel. These reports contain no
launcher, license patch, executable replacement or runtime connection.

## Relevant modules and exact entry points

| Module | Observed named functions | Use for RF research |
| --- | --- | --- |
| `pkg/assets/rfpack` | `ReadRFSEntries` at `0x1408ea940`, `EncodeRFS` at `0x1408eae00`, RPK readers/writers | Archive layout and entry handling |
| `pkg/assets/r3char` | `LoadModel` at `0x14066ce80`, `LoadSkeleton` at `0x1406707c0`, `LoadClip` at `0x1406712e0` | Mesh/bone/animation loading paths |
| `pkg/assets/r3` | `LoadBSP` at `0x140694de0`, `LoadEBP` at `0x1406a4ee0`, environment/lightmap functions | Map and entity structures |
| `pkg/assets/r3compile` | `Compile`, grouping, lightmap and assembly functions | Map writer/compiler research |
| `pkg/assets/rfdata` | `Decode`, `ReadTableIn`, item/map readers and encoders | RF data-table formats |
| `pkg/assets/ifcfg`, `dsui`, `rml` | `Parse`, `Encode`, dialog/image-set functions | UI configuration readers; not proof that all are RF's sprite UI |
| `games/rf15`, `rf2232`, `rf415`, `rf455` | Client, protocol and game-data packages | Multiple RF version paths, not a single universal client layout |
| `internal/gommoclient/world/rf` | Renderer, materials and world loading | A separate RF-compatible implementation inside the editor |

Function names establish compiled code paths, not that every advertised feature
works or that their behavior is identical to the supplied native RF client.

## Concrete archive cross-check

Disassembly of `ReadRFSEntries` at `0x1408ea974` reads a 32-bit entry count,
shifts it left by six and adds four (`4 + count * 64`). `EncodeRFS` limits its
filename field to `0x38` bytes (56) at `0x1408eb0b0`.
The selected assembly excerpts preserve these operands.

The repository's existing independent RFS parser validates these table bounds
and payload ranges on the uploaded Mesh, Tex and Ani samples: 20, 5 and 129
entries respectively. `analysis/rfs-crosscheck.json` records exact sample hashes.
This is static format corroboration, **not** a test run of Gommo's decoder or
proof that every field/format variant has been ported. The existing parser's
stricter filename/overlap checks are its own validation policy.

## Read and reproduce

`analysis/metadata.json`, `packages.json`, `rf-format-functions.json` and
`source-files.txt` are readable directly. The complete symbol indexes are gzipped
to keep tool responses and the repository manageable. Use:

```sh
python Tools/GommoStudio/scripts/inspect_go.py /path/to/gommostudio.exe
python Tools/GommoStudio/scripts/read_editor.py --search rfpack --limit 10
python Tools/GommoStudio/scripts/read_editor.py --function 0x1408ea940 --output /tmp/ReadRFSEntries.c
python -m unittest discover -s Tools/GommoStudio/scripts -p 'test_*.py'
```

The metadata inspector uses Python's standard library, checks PE64/Go table
bounds, and does not load or execute the target. Its supported pclntab magic is
the Go 1.20+ layout (`0xfffffff1`) and inline little-endian 64-bit build info.

For Ghidra, `scripts/ExportGommo.java` accepts an uncompressed application target
index, output directory and scratch directory. The first input comes from
`application-functions.json.gz`. Use Ghidra 12.2 with Java 25, `-max-cpu 4`, and
an 8 GiB heap. Analysis logs/errors and exact pseudocode coverage are documented
alongside the exported results. Full editor source cannot be reconstructed
merely by renaming generated C to Go; calling conventions, types, errors,
dynamic dispatch and behavior need independent review and fixtures.
