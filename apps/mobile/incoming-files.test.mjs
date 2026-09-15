import test from 'node:test';
import assert from 'node:assert/strict';
import {IncomingFiles,incomingFile} from './incoming-files.mjs';
const settle=()=>new Promise(resolve=>setImmediate(resolve));
test('file intents accept local grants and reject remote or malformed links',()=>{
 assert.deepEqual(incomingFile('content://downloads/42'),{uri:'content://downloads/42',name:'Imported note.noteful'});
 assert.equal(incomingFile('file:///tmp/My%20note.noteful').name,'My note.noteful');
 for(const uri of [null,'https://example.com/a.noteful','javascript:alert(1)','exp://192.0.2.1:8081','content://['])assert.equal(incomingFile(uri),null);
});
test('cold/warm opens wait for reader readiness, preserve order and release data on acknowledgement',async()=>{
 const sent=[],read=[],errors=[];
 const queue=new IncomingFiles({read:async uri=>{read.push(uri);return 'qrvM3g==';},post:m=>sent.push(m),error:e=>errors.push(e)});
 queue.open('content://notes/first');queue.open('content://notes/first');
 assert.equal(read.length,0);queue.setReady(true);await settle();
 assert.equal(read.length,1);assert.equal(sent.length,1);
 queue.open('content://notes/second');assert.equal(sent.length,1);
 queue.setReady(false);queue.setReady(true);assert.equal(sent.length,2);assert.equal(read.length,1,'reload reuses pending bytes');
 queue.acknowledge(999);assert.ok(queue.current);
 queue.acknowledge(1);await settle();assert.equal(sent.at(-1).id,2);
 queue.acknowledge(2);assert.equal(queue.current,null);assert.equal(queue.queue.length,0);assert.equal(errors.length,0);
});
test('expired URI grants report failure without blocking the next open',async()=>{
 const sent=[],errors=[];
 const queue=new IncomingFiles({read:async uri=>{if(uri.endsWith('bad'))throw Error('Permission denied');return 'qrvM3g==';},post:m=>sent.push(m),error:e=>errors.push(e.message)});
 queue.open('content://notes/bad');queue.open('content://notes/good');queue.setReady(true);await settle();
 assert.deepEqual(errors,['Permission denied']);assert.equal(sent[0].id,2);
});
