# Reader guide

Build with `python3 tools/build_web.py`, then run `node tools/serve_web.mjs 8765`. Open the printed URL. For another port, pass its number. The double-click macOS launcher uses the same static reader.

Open a `.noteful` note or `.nfedit` project from the file picker, drag and drop, or choose a bundled example. Pages scroll continuously. The page field jumps directly to any page; Fit adapts to the viewport. Only nearby pages render, including the 193-page Practice book.

Select a shape and click Insert shape for immediate insertion, or draw its bounding box. In Shapes mode, select a new shape to reveal four corner handles. Drag a handle, or use arrow keys (Shift for 10-unit steps), to resize it. Each completed resize is undoable and persists in the project. Imported native parametric objects do not yet have these handles.

Select Pen for fixed-width freehand ink, Highlight for Multiply at 50%, Shapes for line/rectangle/ellipse/triangle/arrow outlines, or Erase for whole-stroke removal. Choose color and width. Move supports mouse dragging and native touch scrolling. Pointer cancellation/Escape cancels unfinished gestures. Undo/redo work across pages with Ctrl/Cmd Z and Shift Z. Pressure is not required.

Open Layers to choose the drawing layer, add one, rename it, change visibility/opacity or lock it. Hidden and locked layers cannot receive new strokes and are excluded from erasing. Original images, text and unsupported imported shape types are preserved. New outline shapes are erasable strokes.

A note with recordings shows one audio bar. Select a recording, play/pause or scrub; Ver escritura jumps to its first annotated page. Future strokes from that recording are shown at 20% until pen-down. Seeking backwards restores the shadowed state. Disable the synchronization checkbox to see all ink normally. The duration displayed by the browser can differ slightly from recording metadata due to media padding. A download link remains available for unsupported codecs.

Export menu:

- **Save project .nfedit** preserves original bytes, edits and redo history.
- **Export .noteful** writes applied edits into a new native container; see [export limitations](EXPORT.md).
- **Export page SVG** includes the rendered PDF background, visible layers and current audio appearance. Wait until that page's PDF has rendered.

Unsaved projects trigger a replacement/navigation confirmation. Exporting `.noteful` does not mark the richer editing project as saved. Files are downloaded, never overwritten in place.

The manifest and service worker support home-screen installation on compatible Android/iOS browsers over HTTPS. Once installed and cached, the app shell works offline with user-selected notes. Bundled examples are not part of the offline cache. Browser files, fonts, media codecs and memory limits vary by device. Native APK/IPA installers have not been produced.

## Reader materials and controls

Toolbars use restrained translucent materials, while option menus use an opaque light or dark surface. All dropdowns share the same layout, with a checked selection, wrapped long names and keyboard support: arrows, Home/End, typing to find an option, Enter/Space to select, Escape to dismiss and Tab to continue. The native select remains the data model; the custom trigger follows disabled state and option updates.

The welcome illustration and toolbar icons are local SVG/CSS assets. The mobile layout keeps the tool names, uses compact insertion/layer icons with accessible names, and wraps audio metadata without horizontal overflow. Reduced transparency, reduced motion and increased contrast preferences have independent fallbacks.

Playback indexes only timed ink when a page mounts. Unrecorded items are excluded, DOM references are reused, and opacity is written only when the timeline crosses a stroke start or when seeking/switching recordings changes its state. The static server streams files rather than reading whole assets for each request.

For the mobile QR workflow, see [Expo Go](EXPO.md).
