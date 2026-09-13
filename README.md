# Noteful Reader

A local-first reader and editor for `.noteful` archives, built on a portable Rust core. Open existing notes without running Noteful or depending on a Mac/iPad. The browser app targets desktop, Android and iOS browsers; native store packages are not included yet.

## Run

Build requirements: Rust 1.93+, the `wasm32-unknown-unknown` target, Node 22+, Python 3.11+ for the build helper, and `wasm-bindgen-cli` matching Cargo.lock (currently 0.2.128).

```sh
rustup target add wasm32-unknown-unknown
cargo install wasm-bindgen-cli --version 0.2.128 --locked --root work/wasm-tools
python3 tools/build_web.py
node tools/serve_web.mjs 8765
```

Open http://127.0.0.1:8765/. The generated `apps/reader/` directory can also be served by any static HTTP server. No Python, Rust server, Noteful installation or network API is needed at runtime. For mobile installation, serve over HTTPS and use the browser's Add to Home Screen / Install option. The service worker caches application assets for offline use; opened notes are never uploaded or cached by the service worker.

## Features

- Scrollable pages with lazy rendering; actual embedded PDF backgrounds, images, imported ink and rich text.
- Fixed-width pen, highlighter, line, rectangle, ellipse, triangle and arrow tools. New shapes are editable stroke outlines with direct insertion and draggable/keyboard corner handles.
- Whole-stroke eraser, global undo/redo and non-destructive `.nfedit` projects.
- Layer selection, creation, renaming, visibility, lock and opacity.
- Multiple audio recordings through one player. Seeking restores full opacity to traces whose pen-down time has passed; future traces stay at 20%. Original ink alpha/highlighter blend remains intact.
- Export the current page as SVG, including its PDF raster background and displayed audio state.
- Experimental `.nfedit → .noteful` export preserving original media and untouched records. Native-app import validation remains outstanding.
- No fixed note size or note count limit. Platform memory/address space and format field widths still apply.

The ten original notes in `samples/` cover 204 pages. `tests/fixtures/` contains explicitly synthetic cases and a saved editing project. User-supplied PDF exports are independent visual references, never substitutes for editable ink.

## Repository layout

| Path | Responsibility |
|---|---|
| `crates/noteful-core/` | Byte parser, typed wire encoder, scene, text, audio timing, layers, editing and native writer; no OS/UI APIs |
| `crates/noteful-wasm/` | Browser bindings around the same core |
| `crates/noteful-cli/` | Inspection, verification, scene output and native export CLI |
| `apps/reader/` | Responsive reader/PWA, PDF.js adapter, virtual pages, tools and audio controls |
| `spec/` | Observed native grammar and our project format |
| `docs/` | Architecture, user guide, evidence interpretation and limitations, in English |
| `research/python/` | Independent Python oracle and historical viewer backend |
| `research/ghidra/` | Reproducible read-only Ghidra extraction scripts |
| `research/evidence/` | Source manifests, extracted data, decompilation and validation reports |
| `research/legacy-viewer/` | Historical comparison UI; not the product reader |
| `tools/` | Build, serve, fixture generation and validation scripts |
| `samples/`, `tests/` | Original corpus and regression suites |

Generated dependencies, WASM bindings, galleries, Python caches and `work/` are ignored. The local Ghidra database and original Git history were backed up before removing build/research scratch data from published history.

## CLI

```sh
cargo run -p noteful-cli -- inspect 'samples/Practice book (vol. 1).noteful'
cargo run -p noteful-cli -- verify 'samples/Examen wuolah.noteful'
cargo run -p noteful-cli -- render 'samples/texto.noteful' > scene.json
cargo run -p noteful-cli -- export project.nfedit > edited.noteful
```

`render` emits scene SVG plus PDF resource references; the browser adapter composites the PDF. `verify` checks binary round-trip, not complete visual semantics. Redirect export to a new filename; it writes binary bytes to stdout.

## Validation

```sh
cargo fmt --all --check
cargo clippy --workspace --all-targets --locked -- -D warnings
cargo test --workspace --locked
python3 -m unittest discover -s tests -v
python3 tools/check_rust_parity.py
python3 tools/check_scene_parity.py
node apps/reader/test.mjs
node apps/reader/audio.test.mjs
```

The CI matrix runs core/reference checks on Linux, Windows and macOS, plus Android target checking and actual WASM runtime tests. Local cross-target checks do not substitute for device execution. Native `.noteful` export is tested by re-importing into both decoders, preserving resource bytes, undo/redo and edit semantics; it has not yet been validated by importing modified output into Noteful.app.

Known limitations: exact native ink interpolation, unknown auxiliary ink channels, advanced text layout, text editing, native parametric shape creation, native recording capture, and some format variants. See [architecture](docs/ARCHITECTURE.md), [reader guide](docs/WEB.md), [audio evidence](docs/AUDIO.md) and [native export](docs/EXPORT.md).
