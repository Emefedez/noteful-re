export function readerURL(explicit, hostUri, port = 8768) {
 if (explicit) {
  const url = new URL(explicit);
  if (!['http:', 'https:'].includes(url.protocol)) throw Error('Reader URL must use HTTP or HTTPS.');
  return url.href;
 }
 if (!hostUri) throw Error('Computer not found. Run npm start and scan its QR code.');
 const host = new URL(`http://${hostUri}`).hostname;
 return `http://${host}:${port}/`;
}
export function exportRequest(data, origin, reader) {
 if (new URL(origin).origin !== new URL(reader).origin) throw Error('Unexpected reader origin.');
 const message = JSON.parse(data);
 if (message.type !== 'noteful-export' || !Number.isSafeInteger(message.id) || typeof message.base64 !== 'string' || typeof message.name !== 'string') throw Error('Invalid export request.');
 return {...message, name:message.name.replace(/[<>:"/\\|?*\x00-\x1f]/g, '_') || 'Note.nfedit'};
}

export function allowsNavigation(url, reader) {
 try { return url === 'about:blank' || new URL(url).origin === new URL(reader).origin; }
 catch { return false; }
}
