import { app, BrowserWindow, dialog, net, protocol, session } from 'electron';
import { fileURLToPath, pathToFileURL } from 'node:url';
import { assetPath } from './asset-path.js';

const home = 'notecomplete://reader/';
const root = fileURLToPath(new URL('./reader/', import.meta.url));
protocol.registerSchemesAsPrivileged([{ scheme: 'notecomplete', privileges: {
  standard: true, secure: true, supportFetchAPI: true, corsEnabled: true, stream: true,
} }]);
function createWindow() {
  const win = new BrowserWindow({ width: 1280, height: 900, minWidth: 360, minHeight: 480,
    title: 'NoteComplete', webPreferences: { nodeIntegration: false, contextIsolation: true, sandbox: true } });
  win.webContents.setWindowOpenHandler(() => ({ action: 'deny' }));
  win.webContents.on('will-navigate', (event, url) => { if (!url.startsWith(home)) event.preventDefault(); });
  win.loadURL(home).catch(error => dialog.showErrorBox('Could not open NoteComplete', error.message));
}
app.whenReady().then(() => {
  session.defaultSession.setPermissionRequestHandler((_contents, _permission, callback) => callback(false));
  session.defaultSession.setPermissionCheckHandler(() => false);
  protocol.handle('notecomplete', async request => {
    if (!['GET', 'HEAD'].includes(request.method)) return new Response('', { status: 405 });
    try { return await net.fetch(pathToFileURL(assetPath(root, request.url)).href); }
    catch { return new Response('Not found', { status: 404 }); }
  });
  createWindow();
  app.on('activate', () => { if (!BrowserWindow.getAllWindows().length) createWindow(); });
});
app.on('window-all-closed', () => { if (process.platform !== 'darwin') app.quit(); });
