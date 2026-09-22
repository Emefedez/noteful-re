import path from 'node:path';
export function assetPath(root, address) {
  const url = new URL(address);
  if (url.protocol !== 'notecomplete:' || url.host !== 'reader') throw Error('Unknown origin');
  const relative = decodeURIComponent(url.pathname).replace(/^\//, '') || 'index.html';
  if (relative.split(/[\\/]/).some(part => part.startsWith('.') || part === 'node_modules')) throw Error('Private path');
  const file = path.resolve(root, relative);
  if (!file.startsWith(path.resolve(root) + path.sep)) throw Error('Outside reader');
  return file;
}
