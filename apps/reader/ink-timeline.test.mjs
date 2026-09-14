import {test} from 'node:test';
import {strict as assert} from 'node:assert';
import {indexTimedInk,updateTimedInk} from './ink-timeline.js';
test('playback touches timed ink only, once per opacity transition; seeking and record changes restore it',()=>{
 let writes=0;
 const nodes=Array.from({length:2000},(_,i)=>({dataset:{item:String(i)},setAttribute(name,value){assert.equal(name,'opacity');this.opacity=value;writes++;}}));
 const index=indexTimedInk({querySelectorAll(){return nodes;}},[{item_id:'1',recording_id:'r1',start:5},{item_id:'2',recording_id:'r2',start:8}]);
 assert.equal(index.length,2);
 updateTimedInk(index,'r1',0);assert.equal(writes,2);assert.equal(nodes[1].opacity,.2);assert.equal(nodes[2].opacity,1);
 for(let frame=0;frame<200;frame++)updateTimedInk(index,'r1',frame/60);
 assert.equal(writes,2);
 updateTimedInk(index,'r1',6);assert.equal(writes,3);assert.equal(nodes[1].opacity,1);
 updateTimedInk(index,'r1',0);assert.equal(nodes[1].opacity,.2);
 updateTimedInk(index,'r2',0);assert.equal(nodes[1].opacity,1);assert.equal(nodes[2].opacity,.2);
 updateTimedInk(index,null,0);assert.equal(nodes[2].opacity,1);
});
