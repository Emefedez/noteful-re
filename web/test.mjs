import {readFileSync,readdirSync} from 'node:fs';
import {strict as assert} from 'node:assert';
import init,{inspect_document,verify_document} from './pkg/noteful_wasm.js';
await init({module_or_path:readFileSync(new URL('./pkg/noteful_wasm_bg.wasm',import.meta.url))});
const folder=new URL('../samples/',import.meta.url);
const files=readdirSync(folder).filter(n=>n.endsWith('.noteful'));
assert.equal(files.length,10);
for(const name of files){
 const bytes=readFileSync(new URL(encodeURIComponent(name),folder));
 const result=JSON.parse(inspect_document(bytes));
 assert.equal(result.schema_version,1);assert.equal(verify_document(bytes),true);assert.deepEqual(result.warnings,[]);
 if(name==='Examen wuolah.noteful'){assert.equal(result.pages,3);assert.equal(result.strokes,2008);assert.equal(result.objects,74);}
 console.log(name,result.pages,result.strokes,result.objects);
}
assert.throws(()=>inspect_document(new Uint8Array([1,2,3])));
console.log('WASM runtime: ten samples verified; invalid file rejected.');
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
const textSession=new EditorSession(readFileSync(new URL('../samples/texto.noteful',import.meta.url)));
const textView=JSON.parse(textSession.view(0));assert.equal(textView.texts.length,3);assert.deepEqual(textView.warnings,[]);
for(const [content,size,bold,italic] of [['texto texto ',16,false,false],['Bocadillo',16,true,false],['Hola',12,false,true]]){
 const r=textView.texts.flatMap(t=>t.runs).find(r=>r.text===content);assert.ok(r);assert.ok(Math.abs(r.font_size*6/11-size)<1e-10);assert.equal(r.bold,bold);assert.equal(r.italic,italic);assert.ok(textView.svg.includes(content.trim()));
}
textSession.free();
const audioSession=new EditorSession(readFileSync(new URL('../tests/fixtures/audio-synthetic.noteful',import.meta.url)));
const audioView=JSON.parse(audioSession.view(0));assert.equal(audioView.audio[0].kind,'wav');const audioBytes=audioSession.audio_bytes('synthetic-audio');assert.equal(new TextDecoder().decode(audioBytes.slice(0,4)),'RIFF');
const audioRestored=EditorSession.load_project(audioSession.save_project());assert.deepEqual(audioRestored.audio_bytes('synthetic-audio'),audioBytes);audioSession.free();audioRestored.free();
console.log('WASM text: three real text blocks, sizes and traits verified. Synthetic WAV: exact project preservation verified; sync not claimed.');
const {inkOpacity}=await import('./timeline.js');
for(const file of ['../samples/Practice book (vol. 1).noteful','../tests/fixtures/multi-audio-synthetic.noteful']){
 const e=new EditorSession(readFileSync(new URL(file,import.meta.url))),v=JSON.parse(e.view(8));
 assert.equal(v.pages,193);assert.equal(v.timings.length,3);assert.equal(v.pdf_background.page_index,8);
 assert.equal(new TextDecoder().decode(e.pdf_bytes(v.pdf_background.resource_id).slice(0,5)),'%PDF-');
 const multi=file.includes('multi-audio');assert.equal(v.recordings.length,multi?2:1);assert.equal(v.audio.length,multi?2:1);
 for(const t of v.timings){assert.equal(inkOpacity(t,t.start-1e-6),.2);assert.equal(inkOpacity(t,t.start),1);}
 const first=v.timings.filter(t=>t.recording_id===v.recordings[0].id);
 for(const [time,count] of [[0,0],[8.5,1],[10,2],[13,multi?2:3]])assert.equal(first.filter(t=>inkOpacity(t,time)===1).length,count);
 if(multi)assert.equal(v.timings.filter(t=>t.recording_id===v.recordings[1].id).length,1);
 const restored=EditorSession.load_project(e.save_project());
 for(const asset of v.audio)assert.deepEqual(restored.audio_bytes(asset.id),e.audio_bytes(asset.id));
 assert.deepEqual(restored.pdf_bytes(v.pdf_background.resource_id),e.pdf_bytes(v.pdf_background.resource_id));
 restored.free();e.free();
}
assert.equal(inkOpacity(undefined,0),1);
console.log('PDF backgrounds: paper and imported PDF references. Audio: real timestamps, two independent recordings, seeking boundaries, exact media round-trip passed.');
