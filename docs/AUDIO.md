# Audio and writing synchronization

The real source `samples/Practice book (vol. 1).noteful` contains 193 pages, one PDF, one M4A recording and three variable-width strokes on visible page 9. Source bytes and hash are preserved in `research/evidence/practice-source-manifest.json`. The index uses package version approximately 1.21.

Recording collection: drawing metadata tag `7`, live records at `7/0[]`. Recording fields:

| Tag | Observed meaning |
|---|---|
| 1 | Recording ID |
| 2 | Name (clocked string) |
| 3 | Playable resource ID (clocked string) |
| 4 | Original resource ID in this sample; same as tag 3 |
| 5 | Recording start, uint64 microseconds |
| 6 | Recorded duration in seconds, float64 |

Observed start: `811003055158749`; metadata duration: `13.395676000000094` seconds. The browser reports about 13.47 seconds for the M4A container. Media padding does not change the stored pen-down offsets.

F101 offsets +12 and +20 are consistent with stroke end/start microseconds, respectively. Subtract the recording start using integer arithmetic before dividing by 1,000,000:

| Stroke | Start seconds | End seconds |
|---|---:|---:|
| 1 | 7.475601 | 8.127483 |
| 2 | 8.818385 | 9.459884 |
| 3 | 10.261083 | 11.052481 |

A stroke is associated with every recording interval containing its pen-down time. Each timing entry retains the recording ID, so multiple recordings are not collapsed into one clock. Absolute clocks are serialized as decimal strings; relative seconds are browser-safe numbers. Invalid reversed intervals are not associated.

The reader applies an additional opacity of 0.2 before pen-down and 1 afterwards to the whole stroke, preserving its original alpha and highlighter blend. Selecting another recording changes the timing set, pauses the previous transport and restores that recording's playback position. Page scrolling and seeking work independently. Unrelated/untimed strokes remain fully visible. Disabling sync restores normal visibility.

This is evidence-based whole-stroke synchronization, not exact native point-by-point replay. No per-point timestamp has been established for these three records; their auxiliary flag is unset. Paused/edited/spliced recording variants and native multiple-recording exports need further corpus validation.

Audio signatures: CAF, WAV, M4A/M4B, ID3 MP3, FLAC and Ogg. Other indexed resources remain opaque bytes. Browser codec support determines playback; extraction/download works independently.

Fixtures: `audio-synthetic.noteful` adds a generated 0.25-second WAV. `multi-audio-synthetic.noteful` duplicates the real recording under a second resource ID, adds a second recording 20 seconds later and shifts only stroke 3 by 20 seconds. It tests independent association and playback selection; it is explicitly synthetic, not a native Noteful multi-recording export.

macOS denied app capture and container access during earlier exploration. No privacy permissions, app binaries or microphone settings were changed. The user-provided sample made that access unnecessary for the current implementation.

The player displays a nonempty stored recording name unchanged. Empty names use a clearly generated recording number and date derived from the Apple-epoch start timestamp. The real Practice recording name is empty; its displayed date is a fallback, not a recovered name.
