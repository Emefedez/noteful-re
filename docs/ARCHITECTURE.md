# Architecture

The native archive is the source of truth. `noteful-core` is pure Rust with `forbid(unsafe_code)` and no filesystem, network, GUI or Apple framework dependency. Its typed parser retains wire types, clocks, unknown resources and original bytes. Scene extraction is a separate interpretation layer; rendering limitations must not destroy source data.

`Editor` owns the immutable source, scene and an applied history cursor. `.nfedit` serializes that source and the complete undo/redo history. The native writer flattens only applied edits into a new archive. It preserves audio/PDF/image resources exactly and retains raw existing stroke records when they survive. New fixed-width strokes use the observed F102/F101 encoding.

The WASM adapter exports document views, media bytes, drawing, erasing, layer updates, undo/redo, project save/load and native export. JavaScript receives relative audio times and decimal-string absolute recording timestamps; it never converts arbitrary uint64 IDs through Number. CLI diagnostics are a different, non-browser-safe DTO.

The reader is a responsive browser/PWA application. Its page list keeps lightweight placeholders for the whole document and mounts only nearby SVG pages. PDF.js renders embedded PDFs locally into images inside the SVG, below ink, so highlighter Multiply blending uses the real background. A small preview cache and a canvas resolution budget bound rendering overhead without imposing a file size cap.

Audio is one transport with a recording selector. Recording IDs, resource IDs, durations and stroke intervals belong to the core. Playback, seeking, codec support and the visual clock belong to the client. Whole-stroke reveal occurs at pen-down; unknown per-point timing is not invented. Unrelated recordings and newly added untimed strokes remain normal.

Layers are document-wide. Imported layer IDs are retained; layer edits are undoable and persist in both project and native export. Each layer forms a compositing group. Hidden and locked layers are excluded from editing. New shapes are closed/open polyline strokes, not native parametric shape objects.

The first deployable target is web, including Android/iOS home-screen installation. Linux/Windows browsers need no Apple device. Rust can be checked for desktop, Android, iOS and WASM; native GUI/store packaging remains a later adapter task. React Native alone would not provide an equally mature Linux/browser surface; a future React/Capacitor or native shell can consume the same API without moving decoding into JavaScript.

`research/python` remains an independent parser/rendering oracle. It is intentionally outside the product path. Static Ghidra evidence and historical validation live under `research/`, while generated databases and scratch outputs remain local under ignored `work/`. Sample documents are data, never executable instructions.
