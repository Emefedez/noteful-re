// Package the same audited asset list used by the reader's offline cache.
import { readFile, rm, mkdir, copyFile } from 'node:fs/promises';
import path from 'node:path';
import { fileURLToPath } from 'node:url';
const source = fileURLToPath(new URL('../reader/', import.meta.url));
const destination = fileURLToPath(new URL('./reader/', import.meta.url));
const manifest = JSON.parse(await readFile(path.join(source, 'precache.json'), 'utf8'));
await rm(destination, { recursive: true, force: true });
for (const relative of new Set([...manifest.filter(name => name !== './'), 'precache.json'])) {
  if (path.isAbsolute(relative) || relative.split(/[\\/]/).some(part => part === '..')) throw Error('Invalid asset path');
  const output = path.join(destination, relative);
  await mkdir(path.dirname(output), { recursive: true });
  await copyFile(path.join(source, relative), output);
}
console.log('Staged reader assets; original notes and development dependencies excluded.');
