# Expo Go

The mobile entry point is `apps/mobile/`. It opens the same reader in the WebView included in Expo Go. Parsing, PDF rendering and editing still run locally in the WebView through the existing Rust/WASM core. There is no second rendering engine or native Rust module to build.

## Scan and open

Build the web reader once from the repository root:

```sh
python3 tools/build_web.py
```

Then start Expo Go:

```sh
cd apps/mobile
npm ci
npm start
```

Keep the computer and phone on the same Wi-Fi. Scan the terminal QR with Expo Go on Android, or the Camera app on iPhone/iPad. Keep the command running while using the development app. Ctrl-C stops Metro and the reader server.

The launcher serves the built reader on port 8768 and Metro on port 8081. It binds the reader to the LAN so the phone can reach it; the bundled examples are also readable by devices on that LAN. The desktop command `node tools/serve_web.mjs 8765` remains loopback-only. Files chosen inside the reader are not uploaded to either server.

The reader host is derived from the Expo manifest, so the phone does not need a manually entered IP. If necessary, set `EXPO_PUBLIC_READER_URL` to an existing HTTP(S) reader deployment before starting Expo. A Metro tunnel alone does not expose the separate reader server. This development setup requires the computer; a future hosted reader could remove that dependency.

## Compatibility

This entry point deliberately uses Expo SDK 54, React Native 0.81 and `react-native-webview` 13.15.0. Expo's current documentation identifies SDK 54 as compatible with the App Store version of Expo Go. Install a matching SDK 54 Expo Go build on Android if its store version differs.

- [Expo Go version compatibility](https://docs.expo.dev/troubleshooting/expo-go-version-mismatch/)
- [SDK 54 WebView](https://docs.expo.dev/versions/v54.0.0/sdk/webview/)
- [SDK 54 sharing](https://docs.expo.dev/versions/v54.0.0/sdk/sharing/)

The SDK 54 development toolchain currently reports inherited npm advisories. `npm audit fix --force` proposes SDK 57, which changes the requested store Expo Go compatibility; it is not applied automatically. Avoid using this development server on an untrusted network.

## Files and exports

The WebView file chooser opens `.noteful` and `.nfedit` notes. Generated projects, native archives, SVG pages and audio use an explicit WebView bridge to the OS share sheet. Choose Save to Files or another destination there. Export files are written to Expo Go's disposable cache; no separate storage or microphone permission is requested by this app.

The OS share-sheet API does not confirm that a file was actually saved. The mobile reader therefore keeps the session's unsaved-change protection after sharing. The WebView/base64 bridge temporarily copies export data in memory; there is no fixed file-size limit, but device memory still matters.

## Validation and limits

```sh
npm run check
npm test
npm run export
```

Both iOS and Android JavaScript/Hermes bundles have been generated successfully. Automated tests cover reader URL resolution, bridge origin validation and export request handling. Browser QA covers the reader UI at desktop and phone widths. Physical-device file selection, codec playback and OS sharing still need testing in Expo Go; successful bundling does not establish those behaviors.

Expo Go is the current mobile delivery path. Store builds, APKs/IPAs, native recording and official Noteful import validation are outside this iteration.
