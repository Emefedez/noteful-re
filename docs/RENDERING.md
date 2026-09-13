# Rendering evidence

## Highlighter over images

Object tag 8 is opacity and tag 9 selects normal ink (0) or highlighter (1) in the corpus. The supplied PDF uses `/BM /Multiply`, fill alpha `/ca 0.5` and stroke alpha `/CA 0.5`. Evidence: `research/evidence/pdf-blend-states.json`. The page-2 yellow line has width 28 and tool 1, above a JPEG photograph.

Shapes and freehand ink share a single compositing operation per object/stroke: Multiply at 0.5 for highlighter, multiplied by the original object/color alpha. This avoids darkening self-overlapping pieces separately. The actual embedded PDF is inserted as an SVG image below the ink in the product reader. Layer groups compose in order with their opacity.

## Recovered shapes

| Kind | Geometry | Previously missing exam objects |
|---|---|---:|
| 3 | Filled rounded rectangle; payload/20 radius, payload/5 fill | 1 |
| 6 | Ellipse; payload/7 outline | 5 |
| 12 | Closed polygon; payload/13 commands | 3 |
| 21 | Cubic curve; payload/13 commands | 3 |

Kind 20 handles straight lines. Path commands: 0 move (one point), 1 line (one), 3 cubic (three), 4 close (none). Unsupported commands and incomplete coordinates produce diagnostics. Native geometry is scaled into placement dimensions before center translation and rotation; zero width/height is valid for degenerate straight lines. The sample's 74 objects all render, without claiming support for every Noteful object type.

New UI shapes are fixed-width stroke outlines (line, rectangle, ellipse, triangle, arrow). They can be erased, undone, assigned to layers and exported as native ink. They are not native parametric objects with editing handles.

## Variable-width ink

For 23 exam strokes with flag 1, the third sample dimension matches the initial circle radius in the independent exported PDF. It is not normalized Apple Pencil pressure. The old diagnostic `pressure_candidate` alias is retained, but `radii` is the supported interpretation.

Independent endpoint comparisons: maximum center error 0.000128113 internal units, maximum radius error 0.000071836. Circle selection used position/circularity, not the candidate radius. See `research/evidence/variable-width-validation.json`. A prior failed nearest-outline experiment is retained separately and does not support the renderer.

Rendering uses a union of sample discs and their external tangents, composed once. It preserves measured endpoints and varying width but does not reproduce the native filtering/Bezier smoothing exactly. Auxiliary channel bytes are preserved without assigning unproven eraser/pressure semantics.

## Text and PDF

Text is decoded into escaped SVG text/tspans; [font details](TEXT.md) document approximations. PDF.js reads each page's actual indexed PDF resource and page index, including paper templates. Only nearby pages rasterize; the embedded image participates in the same SVG composition as strokes. SVG export includes that image. The native CLI scene carries a PDF descriptor, leaving rasterization to its host adapter.

## Backups

Before earlier rendering work: `Noteful-RE-20260912-190800.tar.gz`, 4,415 files verified, 162,836,122 bytes, SHA-256 `211a56a1546f865216792978a5603e8de552a10a1607880eb00eeed5bb9c8377`.

Before export/reorganization: `Noteful-RE-20260913-171805-source.tar.gz`, 469 files verified, SHA-256 `e75f2e9ed156be18303a027f4362058673252b8d425ba219b58ee8dfab1563ac`. This source/artifact snapshot excludes `.git`, `work`, `target`, dependency runtimes and Python caches. Original Git history is separately retained in `before-cleanup-20260913.bundle`. All backups are in the sibling `Noteful-RE-backups` directory.
