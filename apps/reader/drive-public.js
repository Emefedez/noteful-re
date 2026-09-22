import { FOLDER_MIME, supportedDriveFile } from './drive-client.js';

// Public Drive pages are fetched only by the native app, without cookies or OAuth.
export function publicDriveURL({ action, id, resourceKey }) {
  if (!/^[\w-]+$/.test(id || '') || (resourceKey && !/^[\w-]+$/.test(resourceKey))) throw Error('Invalid public Drive reference.');
  if (!['folder', 'download'].includes(action)) throw Error('Invalid public Drive operation.');
  const url = new URL(action === 'folder' ? `https://drive.google.com/drive/folders/${id}` : 'https://drive.usercontent.google.com/download');
  if (action === 'download') { url.searchParams.set('id', id); url.searchParams.set('export', 'download'); url.searchParams.set('confirm', 't'); }
  if (resourceKey) url.searchParams.set('resourcekey', resourceKey);
  return url.href;
}
export function parsePublicFolder(html, reference) {
  // Decode Google's JSON string without evaluating any downloaded JavaScript.
  const match = html.match(/window\['_DRIVE_ivd'\]\s*=\s*'((?:\\.|[^'\\])*)'/);
  if (!match) throw Error('This folder is not publicly readable, or Google changed its public listing. Connect Google Drive to access it.');
  const decoded = match[1].replace(/\\x([\da-f]{2})/gi, (_, hex) => String.fromCharCode(parseInt(hex, 16)))
    .replace(/\\'/g, "'").replace(/\\\//g, '/');
  let data;
  try { data = JSON.parse(decoded); } catch { throw Error('Google returned an unreadable public folder listing. Connect Google Drive and retry.'); }
  if (!Array.isArray(data[0]) && data[0] !== null) throw Error('Google returned an unsupported public folder listing.');
  const files = (data[0] || []).map(row => {
    if (!Array.isArray(row) || !/^[\w-]+$/.test(row[0]) || typeof row[2] !== 'string' || typeof row[3] !== 'string') throw Error('Google returned an unsupported public folder item.');
    return { id: row[0], name: row[2], mimeType: row[3], public: true };
  });
  const title = html.match(/<title>([^<]*)<\/title>/)?.[1]?.replace(/\s*[-–]\s*Google Drive\s*$/, '');
  return { folder: { ...reference, name: title || 'Public folder', mimeType: FOLDER_MIME, public: true }, files, publicListing: true };
}
let sequence = 0;
export async function publicDriveRequest(request, signal) {
  signal?.throwIfAborted();
  publicDriveURL(request);
  if (globalThis.window?.notecompleteDrive?.publicRequest) return window.notecompleteDrive.publicRequest(request);
  if (!globalThis.window?.ReactNativeWebView) throw Error('Open public folder links in the installed NoteComplete app, or connect Google Drive in this browser.');
  return new Promise((resolve, reject) => {
    const id = ++sequence;
    const cleanup = () => { clearTimeout(timer); window.removeEventListener('message', receive); document.removeEventListener('message', receive); signal?.removeEventListener('abort', abort); };
    const abort = () => { cleanup(); reject(new DOMException('Cancelled', 'AbortError')); };
    const receive = event => {
      if (event.origin && event.origin !== location.origin) return;
      let data; try { data = JSON.parse(event.data); } catch { return; }
      if (data.type !== 'notecomplete-drive-public-result' || data.id !== id) return;
      cleanup(); data.error ? reject(Error(data.error)) : resolve(data.result);
    };
    const timer = setTimeout(() => { cleanup(); reject(Error('Public Drive request timed out. Retry when online.')); }, 120000);
    window.addEventListener('message', receive); document.addEventListener('message', receive); signal?.addEventListener('abort', abort, { once: true });
    window.ReactNativeWebView.postMessage(JSON.stringify({ type: 'notecomplete-drive-public', id, request }));
  });
}
export class PublicDriveClient {
  constructor(transport = publicDriveRequest) { this.transport = transport; this.connected = true; this.pages = new Map(); }
  async folder(reference, signal) {
    const html = await this.transport({ action: 'folder', ...reference }, signal);
    signal?.throwIfAborted();
    const page = parsePublicFolder(html, reference);
    this.pages.set(reference.id, page);
    return page.folder;
  }
  async children(folder, _pageToken, signal) {
    if (!this.pages.has(folder.id)) await this.folder(folder, signal);
    const page = this.pages.get(folder.id); this.pages.delete(folder.id);
    return page;
  }
  async download(file, signal) {
    if (!supportedDriveFile(file)) throw Error('Unsupported file format.');
    const result = await this.transport({ action: 'download', id: file.id, resourceKey: file.resourceKey }, signal);
    signal?.throwIfAborted();
    const bytes = Uint8Array.from(atob(result.base64), c => c.charCodeAt(0));
    if (/^\s*(?:<!doctype html|<html)/i.test(new TextDecoder().decode(bytes.subarray(0, 200)))) throw Error('Google did not allow this public download. Connect Google Drive and retry.');
    return new File([bytes], file.name, { type: file.mimeType });
  }
}
