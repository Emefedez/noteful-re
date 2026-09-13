import init, {EditorSession} from './pkg/noteful_wasm.js';
const ready = init(); let session;
ready.then(() => postMessage({ready:true})).catch(e => postMessage({fatal:String(e)}));
self.onmessage = async ({data:{id,op,page=0,...args}}) => {
  try {
    await ready;
    if (op === 'open') {
      session?.free(); session = undefined;
      const bytes = new Uint8Array(args.bytes);
      session = args.project ? EditorSession.load_project(new TextDecoder('utf-8',{fatal:true}).decode(bytes)) : new EditorSession(bytes);
    } else if (!session) { throw Error('Abre un documento primero.'); }
    if(op==='draw') session.draw(page,JSON.stringify(args.line));
    if(op==='erase') session.erase(page,JSON.stringify(args.points),args.radius);
    if(op==='undo') session.undo();
    if(op==='redo') session.redo();
    if(op==='audio'||op==='pdf') {
      const bytes=op==='audio'?session.audio_bytes(args.resource):session.pdf_bytes(args.resource);
      postMessage({id,result:bytes},[bytes.buffer]); return;
    }
    postMessage({id,result:op==='save' ? session.save_project() : JSON.parse(session.view(page))});
  } catch(e) { postMessage({id,error:String(e)}); }
};
