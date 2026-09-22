import test from 'node:test';
import assert from 'node:assert/strict';
import path from 'node:path';
import { assetPath } from './asset-path.js';
test('desktop protocol serves only bundled reader paths', () => {
  const root = path.resolve('reader');
  assert.equal(assetPath(root, 'notecomplete://reader/'), path.join(root, 'index.html'));
  assert.equal(assetPath(root, 'notecomplete://reader/pkg/core.wasm'), path.join(root, 'pkg/core.wasm'));
  for (const url of ['file:///etc/passwd', 'notecomplete://other/index.html', 'notecomplete://reader/%2e%2e%2fsecret', 'notecomplete://reader/.env', 'notecomplete://reader/node_modules/pkg/index.js', 'notecomplete://reader/%2e%2e%5csecret']) assert.throws(() => assetPath(root, url));
});
