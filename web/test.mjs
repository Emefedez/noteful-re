import {readFileSync,readdirSync} from 'node:fs';
import {strict as assert} from 'node:assert';
import init,{inspect_document,verify_document} from './pkg/noteful_wasm.js';
await init({module_or_path:readFileSync(new URL('./pkg/noteful_wasm_bg.wasm',import.meta.url))});
const folder=new URL('../samples/',import.meta.url);
const files=readdirSync(folder).filter(n=>n.endsWith('.noteful'));
assert.equal(files.length,8);
for(const name of files){
 const bytes=readFileSync(new URL(encodeURIComponent(name),folder));
 const result=JSON.parse(inspect_document(bytes));
 assert.equal(result.schema_version,1);assert.equal(verify_document(bytes),true);assert.deepEqual(result.warnings,[]);
 if(name==='Examen wuolah.noteful'){assert.equal(result.pages,3);assert.equal(result.strokes,2008);assert.equal(result.objects,74);}
 console.log(name,result.pages,result.strokes,result.objects);
}
assert.throws(()=>inspect_document(new Uint8Array([1,2,3])));
console.log('WASM runtime: eight samples verified; invalid file rejected.');
const {EditorSession}=await import('./pkg/noteful_wasm.js');
let session=new EditorSession(readFileSync(new URL('../samples/Examen%20wuolah.noteful',import.meta.url)));
const view=page=>JSON.parse(session.view(page));
assert.equal([0,1,2].reduce((n,p)=>n+view(p).visible_imported,0),2082);
const original=view(0).svg;
session.draw(0,JSON.stringify({points:[[10,10],[100,10]],width:2,rgba:[0,0,1,1]}));
assert.equal(view(0).visible_added,1);
session.erase(0,JSON.stringify([[50,0],[50,20]]),1);
assert.equal(view(0).visible_added,0);
session.undo();assert.equal(view(0).visible_added,1);
const saved=session.save_project();const loaded=EditorSession.load_project(saved);
assert.deepEqual(JSON.parse(loaded.view(0)),view(0));loaded.redo();assert.equal(JSON.parse(loaded.view(0)).visible_added,0);
session.undo();assert.equal(view(0).svg,original);
assert.throws(()=>session.draw(0,JSON.stringify({points:[],width:2,rgba:[0,0,1,1]})));
loaded.free();session.free();
console.log('WASM editor: 2082 imported elements, draw, swept erase, undo/redo, project reload, invalid edit rejection passed.');
