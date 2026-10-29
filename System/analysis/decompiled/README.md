# Native client decompilation

Input: the repository's `rf_online.bin`, SHA-256
`951e1056875c27f717bfb62d25ffc68d36337416e16d0b7ccc0f7c42b534d2c6`.
Static analysis used Ghidra 12.2, x86 little-endian 32-bit / Windows compiler
specification. The uploaded executable was never run.

The analysis discovered **43,927 non-external functions** and generated C-like
pseudocode for **43,924**. This is coverage of functions found by this analysis,
not a claim of 100% executable coverage, original source recovery or correct
behavior. Discovered functions include RF code, linked libraries, runtime code
and thunks. They are not all separate gameplay features.

## Files and how to read them

- `client-decompiled.c.gz`: all discovered functions, in address order, about
  26 million pseudocode characters. Failed functions have explicit placeholders.
- `functions.json.gz`: address, inferred signature/name, body size, direct
  callees and decompilation status. Indirect/dynamic calls are not a complete
  call graph. The uncompressed temporary index is excluded from Git.
- `resource-xrefs.json`: 159 resource strings linked to referring instructions
  and containing functions, where references were recognized.
- `selected/`: readable `.c` files for the key paths below, without downloading
  the full archive.
- `summary.json`, `retries.json`: exact coverage and unsuccessful retry results.
- `incomplete/`: linear objdump excerpts for the three unsuccessful functions.
  The interval is entry + Ghidra body byte count; non-contiguous chunks can be
  omitted. The original BIN remains the authoritative disassembly input.

Do not paste the entire archive into chat: it exceeds the tool message limit.
Use the bounded reader from the repository root:

```sh
python System/tools/read_decompiled.py --search KeyMap --limit 5
python System/tools/read_decompiled.py --function 00538c00 --output /tmp/keymap-constructor.c
```

## Verified paths through the recovered code

| Address | Role supported by code | Evidence / limitation |
| --- | --- | --- |
| `007bcf93` | PE entry -> CRT startup | Calls security-cookie initialization and `__tmainCRTStartup`; this is not the game loop |
| `00538c00` | Input object construction | Builds paths to KeyMap.dat and KeyMap_NKM.dat |
| `00539140` | Generic keymap INI reader | Seven sections, 76 command names, 32-byte records, `GetPrivateProfileStringA` |
| `00538e80` | Chord token splitting | Splits on `+`; the last prefix is retained if multiple separators occur |
| `00538f50` | Key/modifier lookup | Three modifiers and 86 key names/codes in embedded tables |
| `00539020` | Combines splitting and lookup | Decompiler's inferred return type disagrees with a caller's return use; manually verify ABI before porting |
| `00539ca0`, `00539d80` | Chord formatting | SHIFT/CTRL/ALT strings, lookup key label, `?` for unrecognized code |
| `00539a20` | INI keymap writer | Uses native section/command tables with WritePrivateProfileStringA |
| `005286a0` | Initial configuration reads | Previously traced GameSetting.ini values |
| `00732210` | Connection timeout setting | ClientSystem.ini Network/ConnectTime read, multiplied by 1,000 |
| `008217c0` | Engine initialization/configuration | R3Engine.ini path and rendering settings; see complete function |
| `005c4090` | PlayerCharacter.edf loading path | External data file and file-reader calls, not the uploaded XLSX directly |
| `005cb290` | NDLanguage.edf loading path | Reads count, then serial/length/payload records via a file-reader abstraction; no EDF fixture supplied to validate a decoder |
| `0088e160` | RFS directory/index loading path | Reads RFSINFO.DAT or scans DATA%d.RFS; different from assuming all resources are inside the executable |

The exact **76 commands, 7 sections, 86 key tokens and 3 modifiers** are exported
in [`../native-input.json`](../native-input.json), with binary addresses and
uploaded-keymap comparisons. Reproduce with
`python System/tools/export_native_input.py`. It refuses an unrecognized BIN
hash rather than applying version-specific offsets to another client.

The native INI reader uses the literal `NULL` as its missing-value fallback and
initializes stored modifier/key pairs to `-1`. Unknown key tokens do not resolve
in `00538f50`. Four generic commands are absent from the supplied NKM file:
GMREQUEST_WINDOW, ZOOM_IN, ZOOM_OUT and ALL_WINDOW_CLOSE. Three chat entries
(INPUT_CHAT, END_CHAT, WHISPER) are not part of this 76-command generic table;
this does not establish that the native client ignores chat controls elsewhere.

The web's plain-key Ctrl aliases, digit hotbar aliases and local movement/stamina
rules remain explicit prototype/user-requested behavior. They have not silently
been relabeled as native logic. This analysis commit does not replace those
rules with unverified decompiler output.

## Unsuccessful functions

`00595ce0` timed out at both 15 and 60 seconds. `0076d670` failed to collapse its
block structure. `007a0f30` contains a decode/p-code failure at `007a0fd4`.
The latter two failed again with a 60-second limit. Errors are retained in the
index and retries rather than substituting invented code.

Types, function boundaries and calling conventions are inferred. Some generated
functions contain apparently uninitialized `this`/stack variables, unresolved
globals, warnings or inaccurate signatures. These files are **pseudocode**,
not a buildable C project and not something to compile to WASM without manual
reconstruction and tests. Packed/indirect/unrecognized code can remain absent.

## What remains outside this BIN

The non-Windows imports include `StringLoaderA.dll` (string loader),
`PurifierA.dll`, `ABuse.dll`, `Adv.dll` (dictionary/filter APIs) and `mss32.dll`
(audio). None of those DLLs is supplied in the repository. Their implementation
cannot be recovered from this executable's import calls. Direct3D/DirectInput
also require browser implementations or an emulation layer.

Native R3Engine.ini, GameSetting.ini, ClientSystem.ini and the referenced EDF
files are also missing. Only explicitly labeled INI fallback reconstructions
exist here. Uploaded map, player and sprite archives remain separate assets.
A complete client port still needs data readers, a compatible renderer, game
state, audio, UI behavior and a verified server protocol. A list of network
imports is not a recovered server.

## Reproduce the static export

Install the official Ghidra 12.2 distribution and a Java 25 JDK in a tools
directory. No emulator or execution of the RF executable is required. From
the repo root, substituting absolute paths for Ghidra and the JDK:

```sh
mkdir -p /tmp/rf-project /tmp/rf-functions
JAVA_HOME=/path/to/jdk25 GHIDRA_HEADLESS_MAXMEM=4G /path/to/ghidra/support/analyzeHeadless \
  /tmp/rf-project RFClient -import "$PWD/rf_online.bin" -max-cpu 4 \
  -analysisTimeoutPerFile 600 -scriptPath "$PWD/System/tools" \
  -postScript ExportRFClient.java "$PWD/System/analysis/decompiled" \
  "$PWD/System/analysis/rf-online.json" /tmp/rf-functions
```

`RetryRFClient.java` accepts the output directory and scratch directory, and can
be run with `-process rf_online.bin -noanalysis` in the saved project to retry
failed entries. Keep retries as separate evidence; they do not retroactively
change the first-pass index. Ghidra's project/cache, JDK and installation are
not committed to Git or included in Vercel's build.
