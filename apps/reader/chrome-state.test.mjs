import {test} from 'node:test';
import {strict as assert} from 'node:assert';
import {ChromeState,highlightPoints} from './chrome-state.js';
test('toolbar collapses after downward travel and expands on deliberate upward travel',()=>{
 const state=new ChromeState();
 assert.equal(state.observe(70),false);assert.equal(state.observe(97),true);
 assert.equal(state.observe(180),true);assert.equal(state.observe(145),true);assert.equal(state.observe(115),false);
 assert.equal(state.observe(180),false);assert.equal(state.observe(220),true);assert.equal(state.observe(0),false);
 state.toggle(400);assert.equal(state.compact,true);state.toggle(400);assert.equal(state.observe(410),false);
 state.reset();assert.equal(state.compact,false);
});
test('straight highlighter keeps only the endpoints, including reverse and diagonal strokes',()=>{
 const start=[80,70],end=[20,23];
 assert.deepEqual(highlightPoints(start,end),[[80,70],[20,23]]);
 const points=highlightPoints(start,end);start[0]=99;assert.equal(points[0][0],80);
 assert.deepEqual(highlightPoints([1,2],[1,2]),[[1,2],[1,2]]);
});
