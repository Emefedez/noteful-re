const { contextBridge, ipcRenderer } = require('electron');
contextBridge.exposeInMainWorld('notecompleteDrive', {
  signIn: () => ipcRenderer.invoke('drive:sign-in'),
  cancel: () => ipcRenderer.send('drive:cancel'),
});
