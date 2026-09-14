// Expo Go hands generated files to the system share sheet; browsers use downloads.
let sequence = 0;
const pending = new Map();
function receive(event) {
 let message; try { message = typeof event.data === 'string' ? JSON.parse(event.data) : event.data; } catch { return; }
 if (message?.type !== 'noteful-export-result') return;
 const request = pending.get(message.id); if (!request) return;
 pending.delete(message.id); message.error ? request.reject(Error(message.error)) : request.resolve();
}
window.addEventListener('message', receive);
document.addEventListener('message', receive);
export async function download(data, name, type) {
 const blob = data instanceof Blob ? data : new Blob([data], {type});
 if (window.ReactNativeWebView) {
  const encoded = await new Promise((resolve, reject) => {
   const reader = new FileReader(); reader.onload = () => resolve(reader.result.split(',')[1]);
   reader.onerror = () => reject(reader.error); reader.readAsDataURL(blob);
  });
  const id = ++sequence;
  await new Promise((resolve, reject) => {
   pending.set(id, {resolve, reject});
   try { window.ReactNativeWebView.postMessage(JSON.stringify({type:'noteful-export', id, name, mime:blob.type, base64:encoded})); }
   catch (error) { pending.delete(id); reject(error); }
  });
  return {shared:true};
 }
 const url = URL.createObjectURL(blob), link = document.createElement('a');
 link.href = url; link.download = name; link.click(); setTimeout(() => URL.revokeObjectURL(url), 1000);
 return {shared:false};
}
