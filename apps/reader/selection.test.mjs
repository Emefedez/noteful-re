import test from 'node:test';
import assert from 'node:assert/strict';
import {SelectionController} from './selection.js';

test('released tap waits for asynchronous hit testing; unexpected capture loss cancels drag',()=>{
 const selection=Object.create(SelectionController.prototype),panel={};
 let cancelled=0;selection.cancel=()=>cancelled++;
 selection.active={p:panel,ended:true};
 selection.lostCapture(panel);
 assert.equal(cancelled,0,'normal pointerup must not discard the pending selection');
 selection.active.ended=false;
 selection.lostCapture({});assert.equal(cancelled,0);
 selection.lostCapture(panel);assert.equal(cancelled,1);
 selection.active=null;selection.lostCapture(panel);assert.equal(cancelled,1);
});
