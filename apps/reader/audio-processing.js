export function normalizationGain(channels, enabled) {
  if (!enabled || !channels.length) return 1;
  let peak = 0;
  for (let i = 0; i < channels[0].length; i++) {
    let mono = 0;
    for (const channel of channels) mono += channel[i] / channels.length;
    peak = Math.max(peak, Math.abs(mono));
  }
  // Avoid amplifying near-silence into noise. Limit automatic gain to +18 dB.
  return peak > 0.001 ? Math.min(8, 0.9 / peak) : 1;
}

export function speechSettings() {
  return {
    gain: Number(document.getElementById('speechGain').value) || 0,
    voice: document.getElementById('speechVoice').checked,
    normalize: document.getElementById('speechNormalize').checked,
  };
}

function chain(context, source, settings, normal = 1) {
  const high = context.createBiquadFilter(), low = context.createBiquadFilter();
  high.type = 'highpass'; high.frequency.value = settings.voice ? 100 : 0;
  low.type = 'lowpass'; low.frequency.value = settings.voice ? 6000 : context.sampleRate / 2;
  const gain = context.createGain();
  gain.gain.value = normal * 10 ** (settings.gain / 20);
  const limiter = context.createDynamicsCompressor();
  limiter.threshold.value = -3; limiter.knee.value = 0; limiter.ratio.value = 20;
  limiter.attack.value = 0.003; limiter.release.value = 0.15;
  source.connect(high).connect(low).connect(gain).connect(limiter).connect(context.destination);
  return { high, low, gain };
}

export async function prepareSpeech(buffer, settings) {
  const Offline = globalThis.OfflineAudioContext || globalThis.webkitOfflineAudioContext;
  if (!Offline) throw Error('Audio decoding is unavailable in this browser');
  const decoded = await new Offline(1, 1, 16000).decodeAudioData(buffer);
  const channels = Array.from({ length: decoded.numberOfChannels }, (_, i) => decoded.getChannelData(i));
  const normal = normalizationGain(channels, settings.normalize);
  const context = new Offline(1, Math.ceil(decoded.duration * 16000), 16000);
  const source = context.createBufferSource(); source.buffer = decoded;
  chain(context, source, settings, normal); source.start();
  const pcm = await context.startRendering();
  return { samples: pcm.getChannelData(0), duration: pcm.duration };
}

export class AudioProcessing {
  constructor(audio) {
    this.audio = audio;
    const update = async () => {
      const settings = speechSettings();
      document.getElementById('speechGainValue').textContent = `${settings.gain > 0 ? '+' : ''}${settings.gain} dB`;
      try {
        if (!this.context) {
          const Context = globalThis.AudioContext || globalThis.webkitAudioContext;
          this.context = new Context();
          this.nodes = chain(this.context, this.context.createMediaElementSource(audio), settings);
        }
        this.nodes.high.frequency.value = settings.voice ? 100 : 0;
        this.nodes.low.frequency.value = settings.voice ? 6000 : this.context.sampleRate / 2;
        this.nodes.gain.gain.value = 10 ** (settings.gain / 20);
        if (!this.audio.paused) await this.resume();
        else await this.suspend();
      } catch (error) { document.getElementById('audioState').textContent = `Audio adjustment unavailable: ${error.message}`; }
    };
    document.getElementById('speechGain').oninput = update;
    document.getElementById('speechVoice').onchange = update;
  }
  async resume() { if (this.context?.state === 'suspended') await this.context.resume(); }
  async suspend() { if (this.context?.state === 'running') await this.context.suspend(); }
}
