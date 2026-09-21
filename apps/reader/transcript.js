import { timedWords, wordAt } from './transcript-timing.js';
import { download } from './download.js';
const $ = id => document.getElementById(id);

async function storedTranscript(key, value) {
  const db = await new Promise((resolve, reject) => {
    const request = indexedDB.open('notecomplete-transcripts', 1);
    request.onupgradeneeded = () => request.result.createObjectStore('transcripts');
    request.onsuccess = () => resolve(request.result);
    request.onerror = () => reject(request.error);
  });
  try {
    return await new Promise((resolve, reject) => {
      const tx = db.transaction('transcripts', value ? 'readwrite' : 'readonly');
      const store = tx.objectStore('transcripts');
      const request = value ? store.put(value, key) : store.get(key);
      tx.oncomplete = () => resolve(request.result);
      tx.onerror = () => reject(tx.error);
      tx.onabort = () => reject(tx.error);
    });
  } finally { db.close(); }
}

export class TranscriptController {
  constructor(audio) {
    this.audio = audio;
    this.generation = 0;
    this.words = [];
    this.results = new Map();
    $('transcribeAudio').onclick = () => this.start();
    $('cancelTranscript').onclick = () => this.cancel();
    $('downloadTranscript').onclick = async () => {
      try {
        await download(new Blob([JSON.stringify({ words: this.words }, null, 2)],
          { type: 'application/json' }), 'transcript.json', 'application/json');
      } catch (error) { this.status(error.message); }
    };
  }
  status(message) { $('transcriptStatus').textContent = message; }
  busy(value) {
    $('transcribeAudio').disabled = value || !this.asset;
    $('cancelTranscript').hidden = !value;
  }
  cancel() {
    this.generation++;
    this.worker?.terminate();
    this.worker = null;
    this.busy(false);
    this.status('Transcription cancelled.');
  }
  reset() { this.select(null); this.results.clear(); }
  select(asset) {
    this.cancel();
    this.asset = asset;
    this.busy(false);
    this.render(asset ? this.results.get(asset.id) || [] : []);
    this.status('Whisper downloads its model on first use. Audio stays on this device. Transcripts are stored in this browser.');
  }
  render(words) {
    this.words = words;
    this.active = -1;
    const fragment = document.createDocumentFragment();
    this.buttons = words.map(word => {
      const button = document.createElement('button');
      button.type = 'button';
      button.textContent = word.text;
      button.title = `Seek to ${word.start.toFixed(1)} seconds`;
      button.onclick = () => this.audio.seek(word.start);
      fragment.append(button, document.createTextNode(' '));
      return button;
    });
    $('transcriptWords').replaceChildren(fragment);
    $('downloadTranscript').hidden = !words.length;
    this.update();
  }
  update() {
    const index = wordAt(this.words, this.audio.time);
    if (index === this.active) return;
    this.buttons?.[this.active]?.removeAttribute('aria-current');
    this.active = index;
    const button = this.buttons?.[index];
    button?.setAttribute('aria-current', 'true');
    if (button && $('transcriptPanel').open && !this.audio.audio.paused) {
      const box = $('transcriptWords');
      const top = button.getBoundingClientRect().top - box.getBoundingClientRect().top;
      if (top < 0 || top > box.clientHeight - button.offsetHeight)
        box.scrollTop += top - box.clientHeight / 2;
    }
  }
  async start() {
    if (!this.asset || this.worker) return;
    const asset = this.asset, generation = ++this.generation;
    const language = $('transcriptLanguage').value || '';
    this.busy(true);
    $('transcriptPanel').open = true;
    this.status('Preparing audio on this device…');
    try {
      const bytes = await this.audio.read(asset.id);
      if (generation !== this.generation) return;
      const buffer = bytes instanceof ArrayBuffer ? bytes.slice(0) : bytes.buffer.slice(bytes.byteOffset, bytes.byteOffset + bytes.byteLength);
      // Local-network HTTP readers can run WASM but may lack SubtleCrypto.
      const digest = globalThis.crypto?.subtle ? await crypto.subtle.digest('SHA-256', buffer) : null;
      const key = digest ? 'whisper-tiny-v1:' + language + ':' + [...new Uint8Array(digest)].map(b => b.toString(16).padStart(2, '0')).join('') : null;
      const cached = key ? await storedTranscript(key).catch(() => null) : null;
      if (generation !== this.generation) return;
      if (cached) { this.finish(cached, asset); return; }
      const AudioContext = globalThis.OfflineAudioContext || globalThis.webkitOfflineAudioContext;
      if (!AudioContext) throw Error('Audio decoding is unavailable in this browser.');
      const decoder = new AudioContext(1, 1, 16000);
      const decoded = await decoder.decodeAudioData(buffer);
      if (generation !== this.generation) return;
      const context = new AudioContext(1, Math.ceil(decoded.duration * 16000), 16000);
      const source = context.createBufferSource();
      source.buffer = decoded;
      source.connect(context.destination);
      source.start();
      const pcm = await context.startRendering();
      if (generation !== this.generation) return;
      const samples = pcm.getChannelData(0);
      this.worker = new Worker(new URL('./transcript-worker.js', import.meta.url), { type: 'module' });
      this.status('Loading Whisper on this device… First use needs a model download.');
      const fail = message => {
        if (generation !== this.generation) return;
        this.worker?.terminate(); this.worker = null;
        this.busy(false); this.status(`Could not transcribe: ${message}. You can retry.`);
      };
      this.worker.onerror = event => fail(event.message || 'The local speech engine could not start');
      this.worker.onmessage = ({ data }) => {
        if (generation !== this.generation) return;
        if (data.type === 'progress' && data.progress.status === 'progress')
          this.status(`Loading speech model: ${Math.round(data.progress.progress || 0)}% (${data.progress.file})`);
        if (data.type === 'working') this.status('Transcribing on this device… Playback remains available.');
        if (data.type === 'error') fail(data.error);
        if (data.type === 'complete') {
          const words = timedWords(data.result.chunks, decoded.duration);
          this.worker.terminate(); this.worker = null;
          this.finish(words, asset);
          if (key) storedTranscript(key, words).catch(() => {
            if (generation === this.generation) this.status('Transcript ready for this session. Browser storage is unavailable; export to keep it.');
          });
          else this.status('Transcript ready for this session. Export to keep it.');
        }
      };
      this.worker.postMessage({ samples, language }, [samples.buffer]);
    } catch (error) {
      if (generation === this.generation) {
        this.worker?.terminate(); this.worker = null;
        this.busy(false); this.status(`Could not transcribe: ${error.message}. You can retry.`);
      }
    }
  }
  finish(words, asset) {
    this.results.set(asset.id, words);
    this.render(words); this.busy(false);
    this.status(words.length ? 'Transcript ready. Click a word to seek. Automatic words and timings may need correction.' : 'No timed speech detected.');
  }
}
