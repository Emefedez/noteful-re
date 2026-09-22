const { contextBridge, ipcRenderer } = require('electron');
contextBridge.exposeInMainWorld('notecompleteDrive', {
  publicRequest: request => ipcRenderer.invoke('drive:public', request),
  signIn: () => ipcRenderer.invoke('drive:sign-in'),
  cancel: () => ipcRenderer.send('drive:cancel'),
});
