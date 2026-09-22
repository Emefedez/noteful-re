# Installable builds

Two GitHub Actions workflows generate downloadable artifacts. Both support **Actions → Run workflow** and run on pushed tags matching `v*`. Push the workflow files to the repository before running them; manual dispatch is available once they are on the default branch. They upload artifacts rather than publishing GitHub Releases or app-store submissions. Artifacts expire after 30 days.

## Desktop packages

Run **Desktop packages** (`.github/workflows/desktop.yml`). No repository secrets or hosted reader are required.

| Platform | Architecture | Artifact |
|---|---|---|
| Linux | x86-64 | AppImage |
| macOS | Apple Silicon / ARM64 | DMG and ZIP containing NoteComplete.app |
| macOS | Intel / x86-64 | DMG and ZIP containing NoteComplete.app |
| Windows | x86-64 | NSIS .exe installer |

The reader/WASM is built and tested once on Linux. Separate runners package the same assets using locked Electron and electron-builder dependencies. The package includes PDF rendering and the speech engine; Whisper model weights still download on first use. Original samples, development dependencies and research data are excluded.

The desktop shell uses a private, stable `notecomplete://reader/` origin so local settings and transcript caches survive restarts. Renderer Node integration is disabled, context isolation and sandboxing are enabled, navigation is restricted to the packaged reader, and new windows/permission requests are denied. Open files through the reader's picker or drop zone; OS file associations are not registered.

These are **unsigned preview distributions**, without Developer ID/notarization or Windows Authenticode certificates. OS trust prompts may apply. Production signing requires configuring the appropriate certificates and changing the current unsigned build settings; credentials are never committed. macOS ARM64 may receive an ad-hoc signature from the packager, which is not a verified publisher signature.

Local build (Rust/WASM build prerequisites are described in README):

```sh
python3 tools/build_web.py
npm ci --prefix apps/desktop
npm run stage --prefix apps/desktop
npm start --prefix apps/desktop
# Package on the target OS; macOS can package both Mac architectures.
npm run dist --prefix apps/desktop -- --mac --arm64
# Alternatives: --mac --x64, --linux --x64, --win --x64
```

Outputs are in ignored `apps/desktop/dist/`. Package version comes from `apps/desktop/package.json`, not the Git tag; update versions deliberately before tagging.

## Android APK

The current Expo wrapper loads the web reader from a configured HTTPS URL. It does **not** embed the reader assets. Deploy `apps/reader/` after running the web build to a static HTTPS host first. A placeholder URL will build but cannot open the reader on a device.

1. Set repository variable **READER_URL** under **Settings → Secrets and variables → Actions → Variables** to that reachable HTTPS URL.
2. Run **Android APK** (`.github/workflows/android.yml`). The optional `reader_url` input overrides the repository variable for this run. Tag builds use the variable.
3. Download **NoteComplete-android-preview** from the run's **Artifacts**, unzip it, and install the APK on a compatible Android device.

The workflow checks configuration, installs the locked Expo dependencies, generates Android with Expo prebuild, and runs Gradle `:app:assembleRelease`. It includes ARM64 and x86-64 native libraries. Java 17 and the Android SDK are configured by Actions. No Expo account, EAS subscription, Metro server or signing secret is needed for this preview build. The configured reader must remain available; its offline cache is opportunistic and is not a substitute for embedding assets.

The APK uses the Expo template's **debug signing key**, despite being compiled in release mode. This is for sideload testing, not Play Store distribution. Use a private, stable production keystore before distributing production updates; switching signing keys requires uninstalling the previous app or using a different application ID. Package version and Android application ID remain defined in `apps/mobile/app.json`.

### Local Android build

Install Android Studio's SDK and Java 17, then run from `apps/mobile`:

```sh
npm ci
EXPO_PUBLIC_READER_URL=https://your-reader-host.example/ npx expo prebuild --platform android --no-install
cd android
EXPO_PUBLIC_READER_URL=https://your-reader-host.example/ ./gradlew :app:assembleRelease
```

Replace the example URL with your deployed reader. On Windows use `gradlew.bat`. The APK is written under `app/build/outputs/apk/release/`; the same preview signing limitation applies. For a connected device/emulator, `EXPO_PUBLIC_READER_URL=https://your-reader-host.example/ npm run android` from `apps/mobile` builds and installs the development app. Generated native directories and signing keys are ignored.

## Validation and limitations

`actionlint` validates workflow syntax and expressions. Desktop protocol path tests reject traversal/private paths. Web/WASM tests run before desktop packaging; mobile tests and Expo dependency checks run before Android compilation. Native runner builds and installed-device smoke tests remain necessary, especially for codecs, downloads, audio transcription and platform trust behavior.

References: [Electron custom protocols](https://www.electronjs.org/docs/latest/api/protocol), [electron-builder targets](https://www.electron.build/v26/docs/cli/), [Expo local release builds](https://docs.expo.dev/guides/local-app-production/).

Local validation for this change: 27 Node tests and `actionlint` passed; Expo generated the Android project and its release signing configuration was inspected. Desktop dependencies audited with no reported vulnerabilities. A local macOS package attempt was stopped during the slow Electron binary download, so no successful native installer build or installed-app execution is claimed. The Android SDK is absent on this host. The first Actions runs must confirm native builds on all target runners.
