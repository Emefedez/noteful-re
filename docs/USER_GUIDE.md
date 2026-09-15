# User guide

## Open and navigate

Choose **Open note** or drop a `.noteful` / `.nfedit` file into the reader. The UI is English; note content, saved layer names and recording names retain their original text. Pages scroll continuously and only nearby pages render. **Page** jumps to a page. **Fit** adapts its width; **− / +** change zoom by ten percentage points, from 10% to 400%.

The toolbar compacts when scrolling down and returns when scrolling up. Its arrow provides a manual override. On phones, compact mode keeps playback and seeking available while hiding secondary controls.

## Draw and edit

| Tool | Behavior |
|---|---|
| Pan | Drag with a mouse or scroll with touch. |
| Edit | Select existing ink, supported shapes, images or text placement; drag to move, use four corners to resize, or the upper handle to rotate. The inspector changes dimensions/angle and ink/shape stroke color and width. |
| Pen | Fixed-width freehand ink; no pressure input required. |
| Highlight | Straight segment by default; choose Freehand for sampled ink. Multiply at 50% preserves the appearance over images. |
| Erase | Remove whole strokes and supported line objects. Other selected objects can be deleted with Edit. |
| Shapes | Draw a bounding box or use Insert for a line, rectangle, ellipse, triangle or arrow. New shapes are editable outlines. |

Arrow keys on selection handles adjust geometry; Shift uses larger steps. Undo/redo are global across pages (Ctrl/Cmd Z and Shift Z). Escape or a cancelled pointer gesture discards its unfinished preview. Text-content/font editing and separate shape fill-color editing are not currently provided.

**Layers** selects where to draw, creates/renames layers, controls visibility/opacity and locks them. Hidden or locked layers cannot be edited. New strokes inherit the selected layer.

## Audio

Select a recording in the single player, then play, pause or seek. Nonempty recording names are shown unchanged; otherwise the UI generates a recording number/date. **Show handwriting** jumps to the first associated page. **Dim future handwriting** shows strokes at 20% opacity before pen-down and normally afterwards; seeking backwards restores dimming. This is whole-stroke timing, not point-by-point replay. Unrelated/untimed ink remains visible. Each recording retains its own playback position.

The supplied native audio example contains one recording. Multiple-recording behavior is tested using an explicitly synthetic fixture. Codec support varies by browser/device; **Download** remains available when playback is unsupported.

## Save and export

- **Save project .nfedit** keeps unchanged source bytes, edits and undo/redo history.
- **Export .noteful** flattens applied edits into a new native archive. It is experimental; see [writer limitations](../spec/nfedit-v1.md#native-export).
- **Export page SVG** includes the rendered PDF background and current layers/audio appearance. Wait for the PDF page to finish rendering.

Files download as new files; originals are not overwritten. Replacing a dirty document prompts before discarding edits. Native export does not mark the richer project as saved. Fonts resolve from the device; Apple fonts are not bundled. Exact native ink smoothing, advanced text layout and some object variants remain incomplete.

## Mobile and Android file opening

The Expo wrapper uses SDK 57 and the same browser/WASM engine. Install dependencies and start it as shown in the [README](../README.md#expo-go). The launcher serves web assets on LAN port 8768 and Metro on 8081. It does not serve the original corpus. Files selected on the phone are not uploaded. A Metro tunnel alone does not expose the separate reader server.

Use a matching Expo Go client. Expo Go compatibility changes with SDK releases; consult [Expo's version guidance](https://docs.expo.dev/workflow/upgrading-expo-sdk-walkthrough/). SDK 58 was preview-only when checked on September 15, 2026; the user selected SDK 57 stable. The previous SDK 54-specific instructions no longer apply.

For an existing hosted reader, set `EXPO_PUBLIC_READER_URL` before starting or building the wrapper. A standalone build needs that reachable HTTP(S) URL; the development LAN host is not available when Metro is absent. The browser reader can also be installed to the home screen over HTTPS. Its application cache supports offline use after assets have been cached; opened notes are never stored in that cache.

Exports in the wrapper open the OS share sheet. Select Save to Files or another destination. Dismissing a share sheet does not prove a file was saved, so unsaved-change protection remains active. Large exports temporarily require base64 copies in memory; there is no fixed MB ceiling.

Android default-file handling requires an installed NoteComplete build. Expo Go cannot register this project's own file associations. See the Android build instructions below; default selection remains an Android/user decision. Physical-device URI permissions, file-manager behavior, codecs and sharing require device validation.

### Android installed build

The Android app ID is `com.notecomplete.viewer`. Its manifest registers ACTION_VIEW for `.noteful` file/content URIs, the `application/x-noteful` MIME type, and generic `application/octet-stream` content-provider files. The generic fallback is needed for providers that hide the filename; it can also offer NoteComplete for other binary files, which the decoder will reject if unsupported. Some file managers use other MIME types or do not offer persistent defaults.

Install Android Studio's SDK and a compatible JDK, then build locally from `apps/mobile`:

```sh
EXPO_PUBLIC_READER_URL=https://your-reader-host.example/ npm run android
```

Replace the example URL with your actual static reader deployment. This command generates/installs a development Android app and needs a connected device or emulator. For a locally built release use `npx expo run:android --variant release` with the same environment variable. Native generated directories are ignored. No APK, signing keys or cloud builds are committed.

In Android Files, choose a `.noteful` file, select **Open with → NoteComplete**, then **Always** if offered. Android controls that choice; the application cannot silently make itself the default. A running app receives new file intents too. The file is read using the provider's URI grant, queued until the reader is ready, and passed to the normal local decoder. Existing unsaved edits still require confirmation before replacement. This is file opening, not an ACTION_SEND share target.

Manifest generation and JavaScript bridge tests are validated. No Android SDK/device was available on the development host for APK compilation or an actual default-handler test. Physical-device validation is still required, particularly with opaque `content://` URIs and different file managers.
