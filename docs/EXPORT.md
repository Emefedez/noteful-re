# Native export

`Editor::export_noteful()` and `EditorSession.export_noteful()` flatten the applied `.nfedit` history into a native `.noteful` archive. CLI: `noteful export project.nfedit > edited.noteful`. The source is never changed. With cursor zero, export returns the exact original bytes.

The writer retains unknown fields and every original resource. PDF, image and audio blocks remain byte-exact. Existing surviving F101 records are copied without requantization, with their effective F102 style emitted explicitly. Removed imported ink is excluded from the stroke blob; deletion IDs/times are appended to the observed tombstone arrays. Removed straight-line objects leave the live object collection and update collection flags/clocks.

New pen/highlighter/shape-outline strokes use fixed width, normalized RGBA, tool 0/1, a collision-checked stroke ID, the selected layer and increasing z-order. Up to four points use direct float32 coordinates; longer strokes use per-axis float32 bounds and uint16 quantization. Maximum observed round-trip tolerance in the tests is 0.002 page units. New timestamps follow original clocks and all recordings, so new untimed strokes are not attached to old audio.

A page without an editable block receives one and its page/index references are updated. Layer metadata is updated with visibility, lock, opacity, name and order. All block offsets, lengths, index and trailer are rebuilt. The output is parsed again before being returned.

Regression coverage includes empty-note creation, imported stroke removal, straight-line object removal, new highlighter ink, five outline shapes, multiple layers, undo/redo cursor handling, preservation of every media resource, and reopening the output through Rust/WASM and the Python oracle.

**Interoperability is experimental.** Modified output has not yet been imported into the official Noteful app. Native CRDT merge behavior, tombstone semantics, layer flags and thumbnail invalidation require controlled native round-trip samples. The existing thumbnail is preserved and may remain stale until another app regenerates it. Exported shapes are stroke outlines, not native parametric objects. No unsupported field is intentionally discarded, but byte preservation alone does not prove every application-specific invariant.
