import { pipeline, env } from './vendor/transformers/transformers.min.js';

env.allowLocalModels = false;
env.useBrowserCache = true;
env.backends.onnx.wasm.wasmPaths = new URL('./vendor/transformers/', import.meta.url).href;
env.backends.onnx.wasm.numThreads = 1;
let transcriber;
self.onmessage = async ({ data }) => {
  try {
    if (!['tiny', 'base', 'small'].includes(data.model)) throw Error('Unknown Whisper model');
    transcriber ||= await pipeline('automatic-speech-recognition', `Xenova/whisper-${data.model}`, {
      device: 'wasm', dtype: 'q8',
      progress_callback: (progress) => self.postMessage({ type: 'progress', progress }),
    });
    self.postMessage({ type: 'working' });
    const result = await transcriber(data.samples, {
      task: 'transcribe', return_timestamps: 'word',
      ...(data.language ? { language: data.language } : {}),
      chunk_length_s: 30, stride_length_s: 5,
    });
    self.postMessage({ type: 'complete', result });
  } catch (error) {
    self.postMessage({ type: 'error', error: error.message || String(error) });
  }
};
