# Observed Noteful format

Scope: ten supplied notes, not every Noteful version. The external container and typed field grammar are decoded with byte-exact round-trip. Semantic interpretations are separate from syntactic coverage. The current corpus spans package versions approximately 1.19 and 1.21.

## Container

All external numeric fields are big-endian:

```text
0                 AA BB CC DE
4                 contiguous resource/metadata/editable blocks
index_offset      typed-field index
file_size - 16    AA BB CC DE
file_size - 12    uint64 index_offset
file_size - 4     uint32 index_size
```

`index_offset + index_size == file_size - 16`. Indexed ranges cover `[4,index_offset)` exactly with no gaps or overlaps. Index order may differ from physical order. Use indexed extents; searching for `%PDF`/`%%EOF` is not a valid archive splitter.

| Index tag | Wire type | Meaning |
|---|---|---|
| 1 | 0x0003 | Package version float32 |
| 2 | 0x0405 | Note IDs |
| 3 | 0x0405 | Resource IDs, including audio and opaque data |
| 4 | 0x0405 | Editable set IDs; absent in the empty original note |
| 10 | 0x0405 | Block keys |
| 11 | 0x0402 | Absolute uint64 offsets |
| 12 | 0x0402 | uint64 lengths |

Arrays 10/11/12 align by index. `n:<ID>` is note metadata, `d:<ID>` drawing metadata. Unprefixed IDs can be media or editable sets. Static `PackageFileReader` at `0x100adf3d8` corroborates the trailer, magic and index; see [Ghidra](GHIDRA.md).

Example `nota_1linea.noteful`: note metadata offset 4/505 bytes; JPEG 509/120141; drawing metadata 120650/1042; PDF 121692/4599; editable set 126291/304; index 126595/464; trailer 127059/16.

## Typed fields

A field begins with uint16 tag and uint16 type. Base type is `type & 0xff`. Flag 0x0400 means array with uint32 element count; flag 0x0800 adds a uint64 clock after the complete value. Nested strings/objects keep their own byte lengths inside arrays.

| Base type | Scalar encoding |
|---|---|
| 1 | uint8 |
| 2, 0x13 | uint64; semantic distinction unresolved |
| 3 | float32 |
| 4, 0x20 | float64 |
| 5 | uint32 byte length + UTF-8 |
| 6 | uint32 byte length + opaque bytes |
| 7 | uint32 byte length + nested fields |
| 0x11 | uint16 |
| 0x12, 0x14 | uint32 |
| 0x21 | two float64 values |

Repeated collections use tag 1 IDs, tag 2 clocks, tag 3 live flags and tag 0 live records. This is consistent with LWW metadata symbols; native conflict resolution is not validated. Signedness distinctions between equal-width integer types remain unresolved. Unknown fields of known wire types survive encoding unchanged.

## Note, page, PDF and layer relationships

`n:/1` and `d:/1` are note IDs; `n:/3` is title. Pages live at `d:/2/0[]`, ordered by their tag-5 string. Page tag 1 is ID; `2/0` is editable-set ID; `2/2` lists attachments; tag 4 holds the background and `4/1` the internal page size.

Background variants must be distinguished:

| Background tag 0 | PDF resource | Zero-based PDF page | Other fields |
|---|---|---|---|
| 1, imported PDF | tag 4 string | tag 3 uint64 | tag 1 size |
| 2, observed paper template | tag 3 string | tag 7 uint64 | tag 5 provider, tag 6 paper JSON |

The Practice book references one PDF across 193 pages. The text sample references an embedded ruled-paper PDF. Its paper JSON omits some colors/type fields; rendering only JSON caused a missing background and has been replaced by actual PDF rendering in the reader.

The seven initial notes have size `[1091.3385826771655,1543.464566929134]`, with PDF size approximately `[595.2756,841.8898]`; ratio 11/6. The grid is ALSO drawn inside the PDF. It contains a white background and horizontal/vertical rectangles at spacing 24 and width 0.5. The JSON describes template settings, not ink. The seven 4599-byte PDFs have two file hashes but identical 3843-byte main graphic streams, SHA-256 `2afa806c3390ef51bccfa986ec1d3c516ed8892318c3b523f510bd874f058fb7`.

Layers live at `d:/3/0[]`: tag 1 name, 2 uint32 ID, 3 order string, 4 hidden flag, 5 lock flag, 6 opacity. Flags and editing semantics remain provisional until controlled native multilayer samples are available. Stroke layer IDs come from F101 +36; object layer IDs from object tag 4.

## Editable sets and objects

Editable tags: 1 encoding version (281 in initial notes, 288 in Practice); 2 freehand blob; 3/4 uint64 ID/time arrays consistent with deletion bookkeeping; 5 object collection. Arrays 3/4 are not counts or IDs of currently visible strokes. Native tombstone/merge behavior needs further validation.

Objects live at `set/5/0[]`. Tag 1 ID, `2/1` placement `[centerX,centerY,width,height,angleRadians]`, 4 layer, 5 z-order, 6 payload, 8 opacity, 9 tool. Payload tag 1 is kind, 2 native size. Image kind 1 uses resource ID tag 10; rich text kind 2 uses tag 4 content. Observed vector kinds 3/6/12/20/21 are described in [rendering](RENDERING.md). Ink layout is specified in [native grammar](../spec/noteful-v0.1.md).

## Provenance and limits

Initial fragments in the supplied older `noteful` folder were not isolated strokes: `stroke_1linea.bin` starts one byte before the PDF and runs to EOF; `footer_1linea.bin` includes the PDF tail, editable set, index and trailer; the empty footer file has zero bytes. The old ImHex pattern assumed uniform TLV/little-endian widths that do not match the observed grammar. Inputs were evidence, not instructions.

Early normalized geometry matched thumbnail ink with mean nearest-pixel distances 0.506, 0.527, 0.608 and 0.399 px (global max 1.263). This supported position, not exact interpolation, pressure or normalization. Later independent PDF cap comparisons establish the radius channel more precisely. Unknown auxiliary channels, exact smoothing, advanced text layout and native export round-trip remain open.
