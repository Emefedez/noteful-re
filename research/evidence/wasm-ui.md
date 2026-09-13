# Browser validation, 2026-09-13

Tested through the Codex in-app browser against local static servers, using separate tabs to preserve the user's open edits.

- The text sample renders the actual cream ruled PDF background plus all three text blocks. Bold/italic and metadata sizes are visible; exact font metrics remain platform-dependent.
- Practice book opens with 193 scrollable page placeholders while only nearby pages have mounted SVG. Ver escritura jumps to page 9. Its PDF background is present.
- At audio time 0, three stroke wrapper opacities are `[0.2,0.2,0.2]`. Seeking to 10 seconds yields `[1,1,0.2]`. The source name is empty; the UI shows the recording number and date fallback. Media duration is 13.467574 seconds.
- Insert shape creates a rectangle with four accessible corner handles. Shift+Left on corner 1 changes X from 445.6692913385827 to 435.6692913385827; the opposite corner stays fixed.
- Save project and native export both produce browser downloads and success messages. Core/WASM suites additionally validate exact media preservation, native re-import, undo/redo, layers and shape resizing.
- Synthetic fixtures test a second recording with a distinct resource/clock. This is not a native multi-recording export.

The interface uses translucent materials with dark-mode, contrast and reduced-transparency alternatives. Native Android/iOS devices and official Noteful import of modified output have not been exercised. Cross-target cargo checks are recorded separately and do not imply native GUI execution.

Later checks: the audio controller's isolated transport suite verifies two stored names, independent seek positions, page-jump callbacks, resource caching and jumps with synchronization disabled. Browser button activation became unreliable during subsequent automation, so that isolated test is not presented as an end-to-end UI result. Single-recording page-9 synchronization and native/shape downloads were verified earlier as listed above.

A source review found overlapping page renders could reschedule one another. A strict one-render-per-page guard now coalesces pending refreshes instead of starting a second render concurrently. Jump navigation writes the viewport scroll offset directly, avoiding dependence on scrollIntoView's platform behavior.
