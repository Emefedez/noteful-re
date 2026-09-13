# Exam corpus evidence

The original note and exported reference PDF are copied unchanged into `samples/`. Hashes are in `research/evidence/exam-source-manifest.json`. The exported PDF is an independent visual reference; its ink pixels are not used as reconstructed strokes.

| Visible page | Editable set ID | Strokes |
|---|---|---:|
| 1 | C896C9EFB2724605AB0B482CF36D470A | 621 |
| 2 | 8565A79803934A4AB05848E4C1A0EC18 | 939 |
| 3 | 5A206DE7C4174AC5B8B80EEB407ED3F6 | 448 |

Total: 2,008 strokes, 74 objects, 69 style commands. All 74 observed objects now render. Earlier reports listed 12 unsupported shapes; [rendering](RENDERING.md) supersedes that limitation. Page physical order differs from display order; sorting the page's tag-5 key matches the reference.

F102 changes style persistently: RGBA float64 ×4, tool uint16, eight preserved bytes. F101 contains ID, flags, two clocks, z-order, layer, scalar radius, unknown uint32, point count and geometry. Twelve exam strokes have auxiliary flag 2; 23 have a third coordinate channel, now corroborated as radius. Small records use raw float32; larger records use minimum/extent plus uint16 quantization. See [specification](../spec/noteful-v0.1.md).

The exam introduced additional colors, placed images, line objects, rounded rectangles, ellipses, polygons and cubic paths. Highlighter transparency over the photograph on page 2 exposed missing object-level tool/opacity handling; both now use Multiply at 50%. Variable-width rendering uses sample discs and external tangent quads; exact native smoothing is still approximate.

The historical Python viewer is retained under `research/legacy-viewer` and `research/python/viewer.py`. It is a comparison tool, not the current reader. It uses a numeric loopback bind because reverse DNS in HTTPServer.server_bind caused long startup stalls on this Mac. Its static paper reconstruction is intentionally not the product PDF adapter.

The reader under `apps/reader` uses actual embedded PDFs and supports editing, layers, audio, continuous scrolling and export. Tests retain invalid-open recovery, all exam counts, object geometry/compositing, auxiliary bytes and independent radius evidence. No modified export has yet been verified inside Noteful.app.
