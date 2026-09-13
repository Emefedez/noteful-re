# Ghidra / Cerberus reproduction

Local environment: Ghidra 12.1.2 at `/opt/homebrew/Cellar/ghidra/12.1.2/bin/ghidraRun`; Cerberus skill at `/Users/m1-max/.codex/skills/cerberus-re`; local CLI under ignored `work/cerberus-venv`. Project: `work/ghidra/projects/noteful/noteful.gpr`, program `Noteful`.

Analyzed binary: `/Applications/Noteful.app/Wrapper/Noteful.app/Noteful`, version 1.4.36/build 200, ARM64, image base `0x100000000`, SHA-256 `edb8a4d5317b3a9d384a37acaef96c2026b22ac42876b2ca31066e53dfae84e0`. Addresses below apply only to this binary and exclude ASLR.

An existing Python MCP bridge was configured for localhost:8089, but its Ghidra connection was refused and no callable Ghidra tools were available. Analysis used headless Ghidra/Cerberus and local scripts. The app was not modified/re-signed, and no live attach was performed.

| Address | Static interpretation |
|---|---|
| 0x100991034 | Returns magic 0xaabbccde |
| 0x100adf3d8 | PackageFileReader initialization; seek EOF−16, check magic and read index |
| 0x100ae186c | Trailer decode helper, calls 0x100ae1678 and callback 0x100ae20dc |
| 0x100ae197c | Index reader; float tag 1, compares version limit 1.21 |
| 0x100ae2190 | PackageFileWriter initialization, leading/trailing magic |

The writer's float bits 0x3f9ae148 represent approximately 1.21; initial corpus bits 0x3f9851ec represent approximately 1.19. The newly supplied Practice file uses 1.21. On little-endian ARM64, storing register value 0xdeccbbaa emits bytes AA BB CC DE; this does not contradict the archive's big-endian numeric fields.

Static targets and pseudocode are under `research/evidence/ghidra-targets`; text/font targets under `research/evidence/ghidra-text`. Ghidra temporary registers and recovered Swift signatures are not exact source declarations. StrokeDecoder.parse string: 0x100c5b130, data xref 0x100f81620; StrokeDecoder name 0x100bc51c3/descriptor reference 0x100c9cfcc; StrokeEncoder name 0x100bc51eb/reference 0x100c9d008. These references alone do not mean the stroke parser was decompiled successfully.

Mach-O reports LC_ENCRYPTION_INFO_64 cryptid=1, cryptoff=0x4000, cryptsize=0x1000. No decrypted runtime image was obtained. Selected results are outside that range, but analysis included decompiler/analyzer failures, 73 unresolved dependencies and 52,718 names DemangleAllScript could not demangle. Those names are not equivalent to invalid functions. Full import logs/database remain local under `work/`; the 345 MB database is intentionally excluded from Git history.

Read-only extraction from the existing project:

```sh
JAVA_HOME=/opt/homebrew/opt/openjdk@21/libexec/openjdk.jdk/Contents/Home \
/opt/homebrew/opt/ghidra/libexec/support/analyzeHeadless \
  work/ghidra/projects/noteful noteful -process Noteful -noanalysis -readOnly \
  -scriptPath research/ghidra \
  -postScript NotefulTargets.java research/evidence/ghidra-targets
```

Use `NotefulTextTargets.java` with a separate output directory for text attributes. Do not reimport over the preserved project; choose a new project name when changing import options. Native runtime/import validation remains outstanding.
