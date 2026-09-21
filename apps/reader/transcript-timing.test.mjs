import test from 'node:test';
import assert from 'node:assert/strict';
import { timedWords, wordAt } from './transcript-timing.js';

test('word sync follows seeking, silence, boundaries and the final word', () => {
  const words = timedWords([
    { text: ' Hola', timestamp: [1, 1.4] },
    { text: ' mundo', timestamp: [2, 2.8] },
    { text: ' fin', timestamp: [4, null] },
    { text: 'invalid', timestamp: [null, null] },
  ], 5);
  assert.equal(words.length, 3);
  assert.equal(wordAt(words, 0), -1);
  assert.equal(wordAt(words, 1), 0);
  assert.equal(wordAt(words, 1.4), -1);
  assert.equal(wordAt(words, 4.9), 2);
  assert.equal(wordAt(words, 2.2), 1);
  assert.equal(wordAt(words, 5), -1);
  assert.equal(wordAt([], 0), -1);
});
test('timestamps are sorted, bounded and never overlap the next word', () => {
  const words = timedWords([
    { text: 'two', timestamp: [2, 20] },
    { text: 'one', timestamp: [0, null] },
    { text: 'outside', timestamp: [8, 9] },
  ], 4);
  assert.deepEqual(words, [{ text: 'one', start: 0, end: 2 }, { text: 'two', start: 2, end: 4 }]);
});
