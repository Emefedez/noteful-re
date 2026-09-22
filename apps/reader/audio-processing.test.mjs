import test from 'node:test';
import assert from 'node:assert/strict';
import { normalizationGain } from './audio-processing.js';

test('normalization lifts quiet speech, bounds gain and preserves silence', () => {
  assert.equal(normalizationGain([new Float32Array([0, 0])], true), 1);
  assert.equal(normalizationGain([new Float32Array([0.01, -0.02])], true), 8);
  assert.equal(normalizationGain([new Float32Array([1, -1])], true), 0.9);
  assert.equal(normalizationGain([new Float32Array([0.2])], false), 1);
  assert.equal(normalizationGain([new Float32Array([1]), new Float32Array([-1])], true), 1);
});
