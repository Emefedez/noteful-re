# Attributed text and fonts

Source `samples/texto.noteful`, SHA-256 `b9d30b6f89bce4905ac61a9b802b1fb216aac22ffc8fa888a81045bf48ec673b`, contains three type-2 objects. Their content is in payload tag 4. Placement, dimensions, rotation, opacity and z-order use the ordinary object schema.

| Literal text | Family / PostScript name | UI points | Internal size | Traits |
|---|---|---:|---:|---|
| `texto texto ` | Helvetica | 16 | 29.3333333333 | Regular |
| `Bocadillo` | Gill Sans / GillSans-Bold | 16 | 29.3333333333 | Bold |
| `Hola` | Galvji / Galvji-Oblique | 12 | 22 | Italic |

The trailing space is real. U+200B terminal insertion markers are not rendered. Internal units equal UI points × 11/6; the SVG uses the stored size directly.

Content tags: 1 opaque clock/ID; 2 UTF-8 fragments; 3 attribute-change counts per fragment; 4 concatenated attribute keys; pools 5 strings, 6 bool/u8, 7 structured colors, 8 uint64 integers, 9 paragraph objects and 10 float64 values. Each pool has its own cursor. A fragment updates the current style, which carries into later fragments. Counts and pool consumption are checked.

| Wire key | Attribute | Pool |
|---:|---|---:|
| 1 | Legacy font descriptor, partially interpreted | 5 |
| 2 / 3 | Bold / italic | 6 |
| 4 / 5 | Underline / strikethrough integer style | 8 |
| 6 / 7 | Text / background color | 7 |
| 8 / 9 | Alignment / paragraph object | 8 / 9 |
| 10 | Font size | 10 |
| 11 / 12 | Line height / spacing | 10 |
| 13 / 14 | Family / PostScript name | 5 |

Content, size, bold, italic and family are checked against the user's real sample. Underline/strike are supported by static UIKit mappings in `research/evidence/ghidra-text/100a485ec.c` and `100a49e04.c`, plus synthetic inheritance tests. No native underlined/struck text sample has been supplied yet.

Rust/Python render escaped SVG text/tspan elements with whitespace, explicit line breaks, size, weight, italic and simple decorations. Unknown attributes retain readable text plus a warning. Fonts resolve from the destination platform, falling back to Arial/sans-serif; Apple fonts are not redistributed.

Baseline placement is approximate (horizontal inset 5, vertical inset 8 plus font size). Soft wrapping, justification, lists, complex paragraphs, background color and exact decoration variants remain incomplete. The actual embedded PDF paper now renders below the text in the product reader; the text is never taken from thumbnail pixels. The metadata panel describes requested fonts, not the actual installed font selected by the browser.
