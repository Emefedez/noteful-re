// Android URI grants are used only for the file explicitly opened by the user.
export function incomingFile(uri) {
 if (typeof uri !== 'string' || !/^(content|file):\/\//i.test(uri)) return null;
 let path;try{path=new URL(uri).pathname;}catch{return null;}
 let name; try { name = decodeURIComponent(path.split('/').at(-1)); } catch { name = ''; }
 if (!/\.(noteful|nfedit)$/i.test(name)) name = 'Imported note.noteful';
 return {uri, name};
}
export class IncomingFiles {
 constructor({read,post,error}) { Object.assign(this,{read,post,error}); this.queue=[]; this.sequence=0; this.ready=false; this.busy=false; this.current=null; }
 open(uri) {
  const file=incomingFile(uri); if (!file || this.current?.uri===uri || this.queue.some(f=>f.uri===uri)) return;
  this.queue.push({...file,id:++this.sequence}); this.flush();
 }
 setReady(ready) { this.ready=ready; if (ready) { if(this.current?.base64) this.post(this.message()); else this.flush(); } }
 message() { const {id,name,base64}=this.current; return {type:'noteful-import',id,name,base64}; }
 async flush() {
  if(!this.ready || this.busy || this.current || !this.queue.length) return;
  this.busy=true; this.current=this.queue.shift();
  try { this.current.base64=await this.read(this.current.uri); if(this.ready)this.post(this.message()); }
  catch(error) { this.error(error); this.current=null; }
  finally { this.busy=false; if(!this.current)this.flush(); }
 }
 acknowledge(id) { if(this.current?.id!==id)return; this.current=null;this.flush(); }
}
