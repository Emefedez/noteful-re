# Development and reverse-engineering history

This file records how NoteComplete was built, what the user supplied, which conclusions changed, and how to reproduce the work. It describes observed evidence rather than claiming a complete implementation of Noteful. The normative reference for the current implementation is the [native format specification](spec/noteful-v0.1.md); our editing history and writer are specified in [`.nfedit`](spec/nfedit-v1.md).

## Starting material supplied by the user

The user asked for reverse engineering in `Documents/Noteful-RE`, starting from their existing `Downloads/noteful` work. That folder contained seven deliberately small native notes: empty, one freehand line, two lines, a thick line, a native straight-line object, an image, and a line with an image. It also contained an ImHex project/pattern, strings output, binary footer/stroke fragments and brief analysis. [Initial input hashes](research/evidence/initial-inputs.json) preserve provenance; [the corpus manifest](samples/manifest.json) identifies the unchanged files retained for tests.

The user also supplied an initial model: the file was a container with an embedded PDF, page/template metadata, and separate editable ink. They identified template keys and symbols such as `PaperConfiguration`, `StrokeSet`, `StrokeSetCore`, `StrokeSetDataPayload`, `StrokeEncoder`, `StrokeDecoder`, positional filters and BezierKit. These were useful search seeds and hypotheses, not a validated specification.

Noteful.app was installed locally and could create/edit the format. The user provided the Ghidra launcher path `/opt/homebrew/Cellar/ghidra/12.1.2/bin/ghidraRun`, described an MCP setup, authorized computer access if useful, and suggested OwenPawl's Cerberus RE skill. Later inputs expanded the evidence:

| User input | How it was used |
|---|---|
| `Examen wuolah.noteful` and its annotated `Examen wuolah.pdf` export | Real multi-page stress corpus; page ordering, 2,008 strokes, 74 objects, variable width, images and highlighter compositing. The exported PDF was an independent reference, never substituted for decoded editable ink. |
| `texto.noteful` with explicit text/font descriptions | Checked literal text, Helvetica 16, Gill Sans Bold 16 and Galvji Italic 12, including the conversion between UI points and internal units. |
| `Practice book (vol. 1).noteful` | Established recording metadata and stroke timing against a real M4A recording, plus PDF page references across 193 pages. |
| Uploaded Apple-style design `SKILL.md` | Informed restrained glass chrome, direct manipulation, legible menus and responsive controls. Its design guidance was not binary-format evidence. |
| User corrections and feature requests | Corrected missing PDF paper, requested highlighter transparency over photographs, multiple recordings, editing/export, cross-platform support, Expo Go, English UI and the NoteComplete name. |

No credentials are needed to reproduce the decoder or build the application. Attached documents and extracted strings were treated as data, not instructions to execute.

## Recovering the container

The first useful comparison was between the empty note and single-change notes. Searching for PDF markers alone was misleading: the supplied `stroke_1linea.bin` started one byte before a PDF and continued to EOF; `footer_1linea.bin` included a PDF tail, editable data, index and trailer. The empty footer fragment was zero bytes. The earlier uniform/little-endian TLV assumption did not fit the files.

Reading from the end exposed the actual archive boundary. This is an exact byte excerpt from `nota_1linea.noteful`:

```text
first 4 bytes:  aa bb cc de
last 16 bytes: aa bb cc de 00 00 00 00 00 01 ee 83 00 00 01 d0
```

The trailer decodes to index offset 126,595 and length 464; their sum is 127,059, exactly file size 127,075 minus the 16-byte trailer. Index arrays align resource keys with offsets and lengths. The parser therefore follows indexed extents, rather than guessing boundaries from media signatures.

A strict Python decoder recovered the big-endian typed field grammar: tag/type headers, scalar widths, arrays, nested records and optional clocks. Re-encoding the complete typed index and fields had to reproduce original bytes. Bounds checking and deliberately malformed inputs prevented accidental success caused by scanning past a bad record. Syntax coverage remained separate from understanding a field's meaning.

The paper JSON was useful but insufficient. For example:

```json
{"lh":24,"lt":2,"lw":0.5,"name":"Cuadrícula","pc":16777215,"pi":"…","si":[1091.3385826771655,1543.464566929134],"type":0}
```

This is an abbreviated illustration of the observed template structure; the identifier is omitted. Its presence in empty notes establishes that it is not ink. The user's original suggestion that the grid was separate from the PDF needed correction: the initial notes' embedded PDFs also draw the grid. Their main graphic streams shared SHA-256 `2afa806c3390ef51bccfa986ec1d3c516ed8892318c3b523f510bd874f058fb7`. Later, the text note exposed a ruled-paper PDF missing from the JSON-only preview. The product now renders the actual indexed PDF below editable content.

## Static analysis

The recorded binary was Noteful 1.4.36, build 200, ARM64, image base `0x100000000`, SHA-256 `edb8a4d5317b3a9d384a37acaef96c2026b22ac42876b2ca31066e53dfae84e0`. [Binary metadata](research/evidence/binary.json) and small [container](research/evidence/ghidra-targets/) / [text](research/evidence/ghidra-text/) decompilation excerpts are retained. Addresses apply only to that binary, before ASLR.

The configured localhost:8089 MCP bridge did not provide a working Ghidra connection. Headless Ghidra/Cerberus and the retained Java scripts supplied the static evidence. No successful live LLDB/Frida attachment, decrypted runtime image, app re-signing or native modified-file import was established. Cerberus setup was useful, but its presence does not imply a completed dynamic tracing session.

Exact excerpts from Ghidra's recovered pseudocode:

```c
// FUN_100991034
return 0xaabbccde;

// FUN_100adf3d8, PackageFileReader: excerpt, unrelated lines omitted
IVar8 = _objc_msgSend((ID)self,PTR_s_seekToEndOfFile_100ef43d0);
_objc_msgSend(*(ID *)(unaff_x20 + lVar11),PTR_s_seekToFileOffset__100ef43d8,IVar8 - 0x10);

// FUN_100ae2190, PackageFileWriter
local_a4 = 0xdeccbbaa;
```

The writer's little-endian ARM64 store emits the same `AA BB CC DE` bytes. It does not make archive numbers little-endian. Reader/writer targets corroborated the trailer and approximately 1.19/1.21 package versions. `StrokeDecoder.parse` string/xrefs were leads, not proof of successful stroke-parser decompilation.

Text targets also referenced these UIKit attribute names:

```text
NSUnderlineStyleAttributeName
NSStrikethroughStyleAttributeName
UIFontDescriptorFamilyAttribute
NSForegroundColorAttributeName
```

The symbol names support interpretation only in combination with recovered pool access and sample values. Ghidra output has synthetic variables and incomplete Swift signatures. The Mach-O reports `cryptid=1`, encrypted range `0x4000..0x5000`; no decrypted image was obtained. Import diagnostics included 73 unresolved dependencies and 52,718 names not demangled, so static results were not treated as reconstructed source code.

## Independent visual validation

Ink records were decoded from F102 persistent style changes and F101 stroke records. The one-line note contains 31 quantized points. Across the initial thumbnail comparisons, mean nearest-ink-pixel distances were 0.506, 0.527, 0.608 and 0.399 px; maximum distance was about 1.263 px. This corroborated position only, not native smoothing or pressure.

The exam made incorrect assumptions visible. It has 621, 939 and 448 strokes in displayed page order, 74 objects and 69 style commands. Physical block order is not display order. Twelve shapes missing from an early renderer were recovered as rounded rectangles, ellipses, polygons and cubic paths; old unsupported-count reports were superseded.

The independently exported PDF contains these graphics states (page 2 excerpt):

```text
/Gs3 << /Type /ExtGState /ca 0.5 >>
/Gs4 << /Type /ExtGState /BM /Multiply >>
/Gs6 << /Type /ExtGState /CA 0.5 >>
```

A width-28 highlighter line lies above a JPEG photograph. Rendering only ordinary alpha made it look wrong; applying Multiply and 50% opacity once per stroke/object reproduces the observed compositing rule. Applying alpha to each overlapping geometric piece separately would darken intersections incorrectly.

The third coordinate channel was initially labelled a pressure candidate. A nearest-outline experiment was inconclusive because overlap and contour matching distorted distances. The stronger check matched independent PDF circular caps by center and circularity, then tested radius separately. One retained measurement is:

```json
{"stroke_id":"10e45a7c0ef6c62e","points":42,"channel_first_radius":1.679563283920288,"pdf_cap_radii":[1.679562500000003,1.6795166666666148],"center_error":0.00010750781495507712,"radius_error":0.00004661725367327563}
```

Across all 23 variable-width exam strokes, maximum center error was 0.000128113 and maximum radius error 0.000071836 internal units. [The full small measurement baseline](research/evidence/variable-width-validation.json) remains a test dependency. The channel is interpreted as radius, not raw Apple Pencil pressure. Sample discs and external tangents provide an approximation; exact filtering/Bezier interpolation remains unresolved. Auxiliary bytes are preserved without inventing semantics.

## Text and audio: user-provided ground truth

The user described three text blocks before decoding. Recovered text was `texto texto ` (including its trailing space), `Bocadillo`, and `Hola`. Internal font sizes 29.3333333333 and 22 correspond to UI sizes 16 and 12 through a factor of 11/6. Attribute pools have independent cursors and styles persist across fragments. Actual content/size/bold/italic/family were checked against the supplied note; underline/strike rely on static mappings plus synthetic tests, not a supplied native decorated-text example. Platform fonts are resolved locally and are not redistributed.

The user then emphasized audio synchronized to writing and multiple recordings. Early app capture/container access was denied; the supplied Practice note made private app access unnecessary. It contains one real recording and three timed strokes on visible page 9:

```text
recording start (Apple-epoch microseconds): 811003055158749
recorded duration:                         13.395676000000094 s
stroke start/end offsets:                 7.475601 / 8.127483 s
                                          8.818385 / 9.459884 s
                                         10.261083 / 11.052481 s
```

Subtracting uint64 clocks before conversion to seconds preserved precision. Playback reveals each whole stroke at pen-down; future strokes receive opacity 0.2. No per-point replay timing was established. The real recording name is empty, so a generated date/number is a fallback, not a decoded title.

The multi-recording fixture is explicitly synthetic: a second recording is placed 20 seconds later and the third stroke is shifted with it. It validates separate clocks, assets and selection, but does not establish support for every native pause/splice/multiple-recording variant. Original PDFs, images and audio remain byte-exact through project saves and tested native exports.

## From Python prototype to portable engine

The original Python viewer made decoded geometry inspectable and enabled comparisons with the exported exam. It remains a research tool. Its JSON/template paper preview is intentionally less complete than the product's PDF.js adapter. Python scripts were retained at the user's request, including the historical viewer and migration adapter.

The user asked for Linux, Windows, Android, iOS and web, then preferred Expo Go over native app packaging. Decoding, scene extraction and editing moved into `crates/noteful-core`, a Rust library with `forbid(unsafe_code)` and no filesystem, network or UI APIs. CLI and WASM adapters consume the same library. Python stayed independent as a regression oracle rather than becoming a production dependency.

The browser owns page virtualization, SVG display, actual PDF rasterization and audio transport. The Expo wrapper loads the same reader in a WebView and shares exported files through the OS. It is not a second decoder. Runtime note bytes stay on the device. Development Expo Go still needs the computer serving its web assets on the LAN.

Editing uses immutable source bytes and an undoable history. `.nfedit` preserves the original archive plus edits/redo state; `.noteful` export flattens applied edits while retaining unknown fields and original resource bytes. New shapes export as ink; adjusted imported parametric shapes remain objects. Modified-file import into official Noteful remains unverified.

Post-drawing edits use absolute transforms and style overrides. Dragging previews only one SVG item at most once per animation frame; the worker receives one adjustment when the gesture ends. The returned patch replaces only that item, retaining PDF and audio nodes. Hidden/locked layers are excluded. A quick-tap race discovered in browser QA was fixed so normal pointer-capture release does not cancel pending hit testing.

The user named the app **NoteComplete - a RE noteful viewer**, requested an English interface, removed the example selector, and replaced the zoom menu with Fit/minus/percentage/plus. Glass remains on structural chrome; option menus use opaque contrast. These are product decisions, not recovered Noteful format rules.

## Reproducing and extending the work

Run the build and validation commands in the [README](README.md). Add a native sample that changes one feature at a time, retain its original bytes/hash, compare against a native PDF export where available, and require both parser round-trip and semantic checks before promoting an inference. Synthetic cases should remain labelled synthetic. A parser agreeing with itself is not independent interoperability evidence.

Ghidra is optional for normal development. To repeat static extraction, import the matching legally available binary into a separate project, then use the retained scripts. For an existing project:

```sh
"$GHIDRA_HOME/support/analyzeHeadless" "$PROJECT_DIRECTORY" "$PROJECT_NAME" \
  -process Noteful -noanalysis -readOnly -scriptPath research/ghidra \
  -postScript NotefulTargets.java work/ghidra-targets
```

Run `NotefulTextTargets.java` with a separate output directory for text. Set `GHIDRA_HOME` to the Ghidra installation's `libexec` directory and use a supported JDK. Addresses in these scripts are specific to the recorded binary. The old local database is backed up externally, not a prerequisite hidden inside this repository.

### Python tool inventory

All commands below run from the repository root. Core oracle scripts require only Python's standard library; optional evidence tools list their extra dependencies. Generated output belongs under ignored `work/`.

| Script | Purpose / invocation | Dependencies and output |
|---|---|---|
| `research/python/noteful.py` | Strict parser/encoder, semantic inspection; `python3 research/python/noteful.py samples/nota_1linea.noteful --extract work/one-line` | Standard library; extraction refuses an existing destination; preserves original input. `--view` opens the historical viewer. |
| `research/python/render_note.py` | Importable independent SVG scene oracle | Standard library; approximate paper/ink rendering, no production PDF rasterizer. |
| `research/python/rich_text.py` | Importable attributed-text pool decoder and SVG text renderer | Standard library; exercised by text tests and scene parity. |
| `research/python/rust_backend.py` | Historical adapter running the Rust CLI parser through the Python renderer | Built `target/debug/noteful` or release CLI; no silent Python fallback. |
| `research/python/viewer.py` | Optional historical loopback viewer; `python3 research/python/viewer.py --no-browser --port 8770` | Standard library; serves the corpus and independent PDF reference locally. `--engine rust` uses the migration adapter. Not the product app. |
| `tools/build_web.py` | Build WASM bindings and stage browser dependencies | Rust, matching wasm-bindgen CLI, Node/npm, Python 3.11+; no sample notes copied into the app. |
| `tools/build_examples.py` | Optional static research gallery | Standard library; writes `work/examples/`, not app assets. |
| `tools/analyze_corpus.py` | Recreate extracted blocks, diagnostic SVG and corpus comparison | Standard library; writes `work/reports/` and `work/extracted/`. |
| `tools/validate_geometry.py` | Compare decoded initial stroke positions with native JPEG thumbnails | Pillow; reads originals directly, writes `work/reports/geometry-validation.json`. Position evidence only. |
| `tools/validate_variable_width.py` | Independently measure PDF caps against the third coordinate channel | NumPy and pypdf; writes `work/reports/variable-width-validation.json`. Does not overwrite the committed baseline. |
| `tools/check_rust_parity.py` | Compare Rust fields/semantics and round-trip against Python | Rust CLI + standard library; current report under `work/reports/`. |
| `tools/check_scene_parity.py` | Compare ordered native/Python SVG primitives and inherited transforms | Rust CLI + standard library; tolerance 2e-5 internal units; no pixel-equivalence claim. |
| `tools/check_export.py` | Decode native writer output independently and check original media bytes | Rust CLI + standard library; current report under `work/reports/`. |
| `tools/build_audio_fixture.py` | Regenerate the synthetic 0.25-second WAV resource fixture | Standard library; intentionally writes the named test fixture and a scratch report. |
| `tools/build_multi_audio_fixture.py` | Regenerate the synthetic two-recording fixture | Standard library; intentionally writes the named test fixture. |
| `research/python/historical/update_decoder.py` | Preserved one-off early migration script | Historical only: expects obsolete `tools/noteful.py`; do not run against current source. Its replacement logic is already superseded by the maintained parser. |
| `tests/test_noteful.py`, `test_text.py`, `test_viewer.py` | Parser, text, rendering and historical HTTP regression tests | `python3 -m unittest discover -s tests -v`; standard library. |

Optional evidence environment:

```sh
python3 -m venv work/evidence-env
work/evidence-env/bin/pip install Pillow numpy pypdf
work/evidence-env/bin/python tools/validate_geometry.py
work/evidence-env/bin/python tools/validate_variable_width.py
```

The tests cover observed corpus syntax, malformed inputs, scene correspondence, media preservation, timing, edit history and writer output. CI checks desktop operating systems and Android/iOS compilation targets as well as actual WASM runtime behavior. Target compilation and Expo bundles do not prove physical-device file selection, codec playback or sharing.

## Repository cleanup and remaining work

The September 2026 cleanup removed duplicated extracted media/SVG, large import logs, stale test snapshots, generated reference rasters and tracked Python bytecode. The raw evidence snippets above were recorded before deletion. Small decompilation excerpts, the binary fingerprint, initial-input provenance, the independent radius baseline and one unchanged original corpus remain. Every Python script was preserved and documented. Checks now write scratch reports rather than editing committed evidence.

Before cleanup, the local source and Ghidra database were archived outside the repo as `Noteful-RE-backups/before-repo-cleanup-20260915-105234.tar.gz`: 343 files, 129,169,032 bytes, SHA-256 `8e8ffcfff2145b6708ccc1f68eda50d5cd2b99984ce23a153f107f9eab8fdcf5`. Archive members were read back successfully. Reinstallable dependencies and build caches were excluded. Earlier backups and Git history also remain outside the working tree; published history was not rewritten by this cleanup.

Open work: import modified exports into official Noteful; obtain native multiple-recording, pause/splice and decorated-text samples; validate layer merge/tombstone behavior; improve native ink smoothing and advanced text layout; test file selection, codecs and sharing on physical Expo Go devices. Unknown auxiliary channels, unsupported object variants, stale exported thumbnails and incomplete CRDT semantics remain explicit limitations.


### SDK 57 and Android file association

On September 15, 2026, the npm registry listed SDK 57 as stable and SDK 58 only under preview/canary tags. The user chose SDK 57 to keep the normal Expo Go workflow. Dependencies were aligned with `expo install --fix` (React Native 0.86.3, React 19.2.3), obsolete `newArchEnabled` / `edgeToEdgeEnabled` switches were removed, and `expo-system-ui` supplies automatic Android appearance. [Versioned SDK 57 reference](https://docs.expo.dev/versions/v57.0.0/) and [upgrade guidance](https://docs.expo.dev/workflow/upgrading-expo-sdk-walkthrough/) describe that compatibility. Exact patch versions are recorded in the lockfile.

The later request for Android default opening requires a separately installed app: Expo Go owns its own manifest and cannot register project-specific handlers. ACTION_VIEW filters are generated from `apps/mobile/app.json`. React Native Linking handles cold and warm launches; `IncomingFiles` retains one in-flight file and queues subsequent URI grants until the WASM reader announces readiness. The browser bridge preserves bytes, validates them through the normal decoder, deduplicates delivery and honors unsaved edits. No raw path is sent to a network API. A standalone build still needs the configured reader URL; packaging web assets inside an offline APK is not implemented.

The default choice belongs to Android's resolver. Generic binary MIME fallback covers content providers without filename extensions but can list the app for other binary files. This tradeoff and physical-device verification steps are documented in the user guide. Android manifest generation, 21 Expo doctor checks and Android/iOS Hermes bundling passed; no APK/device execution is claimed. The SDK 57 toolchain still reports inherited moderate npm advisories; no forced major upgrade was used to hide them.
