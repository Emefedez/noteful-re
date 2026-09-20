import {fileKind} from './media-import.js';
// Native file intents enter through the same user-visible open flow as the picker.
export function receiveNativeFiles({open,canReplace,isBusy,status}) {
 const pending=new Set(),completed=new Set();
 const reply=(id,error)=>window.ReactNativeWebView.postMessage(JSON.stringify({type:'noteful-import-result',id,error}));
 async function receive(event) {
  if(!window.ReactNativeWebView)return;
  let message;try{message=typeof event.data==='string'?JSON.parse(event.data):event.data;}catch{return;}
  if(message?.type!=='noteful-import'||!Number.isSafeInteger(message.id)||typeof message.base64!=='string')return;
  if(completed.has(message.id)){reply(message.id);return;}if(pending.has(message.id))return;
  pending.add(message.id);let failure;
  try {
   if(isBusy())throw Error('An edit is still being saved. Open the file again when it finishes.');
   if(!canReplace())return;
   const bytes=Uint8Array.from(atob(message.base64),c=>c.charCodeAt(0));
   // Content-provider URIs often omit filenames. The bytes determine the format.
   const kind=fileKind(message.name||'',bytes);
   const suffix={note:'.noteful',project:'.nfedit',pdf:'.pdf',image:'.png'}[kind];
   const name=(typeof message.name==='string'?message.name:'Imported note').replace(/\.(noteful|nfedit|pdf|png|jpe?g|webp)$/i,'')+suffix;
   await open(new File([bytes],name));
  }catch(error){failure=error.message;status(failure,true);}
  finally{pending.delete(message.id);completed.add(message.id);reply(message.id,failure);}
 }
 window.addEventListener('message',receive);document.addEventListener('message',receive);
}
