import { writeFile, rm } from 'node:fs/promises';
const target = new URL('../apps/desktop/google-desktop-client.json', import.meta.url);
const id = process.env.GOOGLE_DESKTOP_CLIENT_ID;
if (id) {
  if (!/^[\w-]+\.apps\.googleusercontent\.com$/.test(id)) throw Error('Invalid GOOGLE_DESKTOP_CLIENT_ID');
  await writeFile(target, JSON.stringify({ installed: { client_id: id, client_secret: process.env.GOOGLE_DESKTOP_CLIENT_SECRET || '' } }));
} else {
  await rm(target, { force: true });
  console.log('Desktop OAuth not bundled; users can choose their Desktop client JSON on first connection.');
}
