# Noteful RE Project v1 (.nfedit)

Our non-destructive UTF-8 JSON project format, not an official Noteful format. Required fields; unknown keys are rejected:

```json
{
  "format": "noteful-re-project",
  "version": 1,
  "source_base64": "...",
  "history": [
    {"kind":"Add","page":0,"line":{"points":[[10,10],[100,10]],"width":2,"rgba":[0,0,1,1],"tool":0,"layer":0}},
    {"kind":"Erase","page":0,"ids":["new:0"]}
  ],
  "cursor": 1
}
```

`source_base64` contains the complete, unchanged original archive using padded RFC 4648 Base64. Only history `[0,cursor)` is applied; the rest can be redone. A new action after undo truncates the redo branch. Undo/redo are global across pages.

`Add`: zero-based source page, fixed diameter `width`, normalized sRGB RGBA, page-space points, tool 0 normal or 1 highlighter, layer ID. Missing tool/layer default to zero for older v1 projects. One point is a disc; multiple points form a rounded polyline. The UI's shapes are point paths in this same representation, without pressure.

`Erase`: unique existing IDs supported by the whole-stroke eraser or explicit selected-item removal. Imported IDs are `stroke:N` / `object:N` at original collection indices before z-sorting; `new:N` is the Add action's history index. IDs are page-local. Hidden/locked layers cannot be erased interactively. Images/text/filled shapes are not whole-stroke eraser targets, but selectable objects can be removed explicitly.

`Layer`: `{ "kind":"Layer", "layer":{"id":1,"name":"Highlights","visible":true,"locked":false,"opacity":1} }`. Replaces a matching layer or appends a new layer. Applied in history order before subsequent drawing. Layer edits persist and are undoable. Older clients do not understand this added action and should reject it rather than silently omit it; current clients retain compatibility with earlier projects.

Validation: existing page/layer; 1–8192 finite points per gesture with coordinate absolute value ≤1e6; width 0.1–100; finite RGBA/opacity within 0–1; supported tool; nonempty layer name; valid history cursor and IDs. No global action/point or MB ceiling. Loading validates the entire history including redo before returning a session.

Saving a project never reconstructs the original archive. Native export is a separate flattening operation over applied edits and does not retain redo history. See [native writer](../docs/EXPORT.md). No script/HTML from a project is executed.

## Shape metadata and corner edits

A line may have optional `shape` metadata: `{ "kind":"rectangle", "start":[100,100], "end":[200,200] }`. Supported kinds: line, rectangle, ellipse, triangle and arrow. The core derives canonical outline points; projects retain the control corners for later resizing. Older ordinary lines omit this field.

`Replace` is an undoable resize of an existing newly added shape: page, `id` (`new:N`) and replacement line. Kind, color, width, tool and layer must remain unchanged. The latest applied replacement supplies geometry for drawing, hit testing and export. Erased or locked shapes cannot be resized. `.noteful` export emits the current outline as native ink, so project-specific corner metadata is retained only in `.nfedit`.

## Item adjustments

`Adjust` extends v1 history for newly added lines/shapes and supported imported ink, native shapes, images and text placement:

```json
{"kind":"Adjust","page":0,"id":"stroke:0","adjustment":{"translation":[20,30],"scale":[1.5,1],"rotation":30,"width":4,"rgba":[0.2,0.4,0.8,1]}}
```

Translation, scale and rotation are required. `width` and `rgba` may be omitted or null to retain the original style; they apply only to ink and shapes. Translation is in page units, scale is along the original object's local axes, and rotation is in degrees relative to its original orientation. Scale and rotation use the original bounds center as pivot; translation follows. The latest applied adjustment replaces earlier adjustment parameters for that item, rather than accumulating rounded geometry. A previous `Replace` supplies the base geometry for legacy added shapes.

Validation requires finite translation within ±1e6, scale in 0.001–1000, rotation within ±36000, optional width in 0.1–100 and RGBA in 0–1. Target IDs must exist and remain visible, unlocked and undeleted at that point in history. Identity/repeated adjustments do not add an action. Each completed gesture or inspector change is one undo step. Current readers load older v1 histories; older readers must reject the unfamiliar `Adjust` action rather than silently omit it.

Native export transforms current geometry while retaining original imported IDs, audio timing and auxiliary stroke data. `.nfedit` keeps the unchanged source and complete edit history.
