# Observed Noteful grammar, revision 0.1

This versions our knowledge, not an official Noteful release. Corpus: ten original notes under `samples/`, with source manifests under `research/evidence/`. Separate syntax requirements from interpreted semantics.

## Container and fields

All wire numbers are big-endian. Leading/trailing magic: AA BB CC DE. The 16-byte trailer contains magic, uint64 index offset and uint32 index size. Offset+size equals file length−16. Index arrays 10/11/12 contain unique UTF-8 block IDs, uint64 offsets and lengths, with equal counts. Positive block ranges cover `[4,index_offset)` exactly. Index tag 3 identifies resources; optional tag 4 identifies editable sets.

Each field: uint16 tag + uint16 type. Base type is `type & 0xff`; flag 0x400 adds a uint32 array count, flag 0x800 adds a uint64 clock after the complete value. Types: 1 u8; 2/0x13 u64; 3 f32; 4/0x20 f64; 0x11 u16; 0x12/0x14 u32; 0x21 pair of f64; 5 uint32 byte length plus UTF-8; 6 length plus blob; 7 length plus nested fields.

The parser preserves exact wire variants, types, clocks and raw bytes. It rejects duplicate tags, unsupported types/flags, malformed extents, invalid UTF-8 and nonfinite floats. These are strict implementation policies for the observed grammar, not proof that no future version can introduce another variant.

## Ink

Editable set tag 2 contains a command stream. F102 is 44 bytes: opcode, four f64 RGBA values, u16 tool, eight opaque bytes. Style persists. F101 has a 56-byte header:

| Offset | Value |
|---:|---|
| 0 | F101 |
| 2 | u64 stroke ID |
| 10 | u16 flags |
| 12 | u64 end timestamp, consistent with microseconds in audio corpus |
| 20 | u64 start timestamp |
| 28 | u64 z-order |
| 36 | u32 layer ID |
| 40 | f64 scalar radius |
| 48 | unknown u32 |
| 52 | u32 point count N |

Flag 2 adds 8*N auxiliary bytes before geometry; meaning unresolved. D=3 for flag 1, otherwise D=2. N≤4 stores N*D raw f32 values. N>4 stores min/extent f32 pairs per dimension followed by N*D u16 coordinates, decoded as `min + q/65535 * extent`. Dimension three is radius, corroborated against 23 independent PDF endpoints; it does not establish device pressure.

Unsupported flags/commands retain the opaque blob and produce an ink diagnostic. Never scan forward for another signature after an error. Container verification may still succeed without semantic ink support.

## Semantics and resource references

[Format relationships](../docs/FORMAT.md), [rendering](../docs/RENDERING.md), [text](../docs/TEXT.md), [audio](../docs/AUDIO.md) and [native export](../docs/EXPORT.md) specify current interpretation. PDF-background variant 1 uses tags 4/3 for resource/page; paper variant 2 uses tags 3/7. Highlighter uses Multiply with factor 0.5, applied once per stroke/object.

## Implementation limits and conformance

No fixed file MB or note count ceiling. Nested field depth ≤40. Item/point budgets derive from input byte length; every read/array must fit its buffer. Target address space, available memory, uint32 wire lengths and finite coordinate constraints still apply.

Conformance checks: all ten notes parse without ink errors; typed field/index re-emission reproduces exact original bytes; Rust diagnostics and semantics match the independent Python oracle; shared-renderer SVG output matches exactly; ordered SVG primitives match within 2e−5 internal units; malformed cases fail without panics. Native modified export is tested by re-import into our decoders, not yet the official app.

CLI JSON may contain uint64 values beyond JavaScript's exact integer range. The editor/WASM view is a separate DTO with decimal-string absolute audio clocks and relative-second timing. SVG is an output representation, never the editable archive model.
