# Reader visual pass — September 2026

## Changes

- Consistent solid option menus replace native dropdown styling. Long names wrap in the menu and truncate only in the compact trigger. Selection, focus and disabled states remain distinct.
- A quieter blue/slate palette, local SVG toolbar icons and clearer spacing separate navigation, drawing controls, paper and audio.
- Glass is limited to structural chrome. Menus remain opaque in both themes; accessibility preferences reduce transparency independently.
- A small paper illustration gives the empty screen a recognizable note-taking context without external image assets.
- Phone layouts retain named tools, accessible compact actions, wrapped recording metadata and no horizontal page overflow.
- Expo Go opens this exact reader, with safe areas and a file-sharing bridge. The mobile entry point does not duplicate note decoding or rendering.

## Performance

Only audio-timed items enter the playback index. DOM references are reused for the lifetime of each mounted page. Repeated frames with unchanged opacity make no attribute writes. Offscreen pages release SVG, overlay and timing references. The static host streams assets and answers HEAD without loading file bytes.

## Checks performed

Browser checks used the actual built WASM and supplied notes:

- Desktop dark-theme menu and reader screenshots reviewed.
- Effective 390 CSS-pixel viewport: document width equals scroll width; no horizontal overflow.
- Type-to-select opened `texto.noteful`; text and its actual ruled PDF background appeared.
- Arrow-key shape selection inserted a rectangle with four corner controls.
- Multi-audio synthetic fixture: selecting the second named recording and using “Ver escritura” reached page 9. Its three ink opacities were `[1, 1, 0.2]` at zero; all were `1` at the end of the selected recording.
- Viewport override reset after phone-width QA. User editing tabs were preserved.

Automated checks cover the existing ten-note WASM/editor corpus, audio controller, opacity transitions without redundant writes, Expo host resolution, export bridge and static server. Both Expo platform bundles were produced successfully. The LAN manifest resolved the reader host and its WASM resource correctly.

Physical Expo Go execution, file picker behavior and the OS share sheet remain device-validation tasks. Current browser checks do not substitute for them.
