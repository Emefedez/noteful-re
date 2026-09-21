import test from 'node:test';
import assert from 'node:assert/strict';
globalThis.window = { addEventListener() {} };
globalThis.document = { addEventListener() {} };
const { TranscriptController } = await import('./transcript.js');

function element() {
  return { hidden: false, disabled: false, children: [], attrs: {},
    append(...nodes) { this.children.push(...nodes); },
    replaceChildren(...nodes) { this.children = nodes; },
    setAttribute(k, v) { this.attrs[k] = v; },
    removeAttribute(k) { delete this.attrs[k]; } };
}
test('transcripts isolate recordings, click to seek, and stop workers on reset', () => {
  const nodes = new Map();
  globalThis.document = {
    getElementById(id) { if (!nodes.has(id)) nodes.set(id, element()); return nodes.get(id); },
    createElement: element, createDocumentFragment: element, createTextNode: text => text,
  };
  const seeks = [];
  const audio = { time: 0, audio: { paused: true }, seek(t) { seeks.push(t); this.time = t; } };
  const controller = new TranscriptController(audio);
  controller.select({ id: 'a' });
  controller.finish([{ text: 'Hola', start: 1, end: 2 }], { id: 'a' });
  controller.buttons[0].onclick(); controller.update();
  assert.deepEqual(seeks, [1]);
  assert.equal(controller.buttons[0].attrs['aria-current'], 'true');
  let terminated = false;
  controller.worker = { terminate() { terminated = true; } };
  controller.select({ id: 'b' });
  assert.equal(terminated, true);
  assert.deepEqual(controller.words, []);
  controller.select({ id: 'a' });
  assert.equal(controller.words[0].text, 'Hola');
  controller.reset();
  assert.equal(controller.results.size, 0);
  assert.equal(nodes.get('transcribeAudio').disabled, true);
});
test('cancelling while bytes are being read prevents stale work from starting', async () => {
  let release;
  const audio = { time: 0, audio: { paused: true }, read: () => new Promise(r => release = r) };
  const controller = new TranscriptController(audio);
  controller.select({ id: 'a' });
  const pending = controller.start();
  controller.cancel();
  release(new Uint8Array([1, 2, 3]));
  await pending;
  assert.equal(controller.worker, null);
  assert.deepEqual(controller.words, []);
});
