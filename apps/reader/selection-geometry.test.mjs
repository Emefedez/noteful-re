import {test} from 'node:test';
import {strict as assert} from 'node:assert';
import {matrix,point,inverse,multiply,corners,resizeAdjustment} from './selection-geometry.js';
const close=(a,b)=>a.forEach((v,i)=>assert.ok(Math.abs(v-b[i])<1e-8,`${v} != ${b[i]}`));
const item={bounds:[10,20,200,120],base_rotation:25,adjustment:{translation:[40,15],scale:[1.4,.8],rotation:35,width:null,rgba:null}};
test('transform and inverse preserve points and incremental preview matches final geometry',()=>{
 const before=matrix(item),after=matrix(item,{...item.adjustment,rotation:60,translation:[90,-10]});
 close(point(inverse(before),point(before,[22,35])),[22,35]);
 close(point(multiply(after,inverse(before)),point(before,[22,35])),point(after,[22,35]));
});
test('resizing a rotated object keeps its opposite corner fixed without accumulating transforms',()=>{
 const old=corners(item),moving=[old[2][0]+30,old[2][1]+50];
 const a=resizeAdjustment(item,2,moving),next=corners(item,a);
 close(next[0],old[0]);close(next[2],moving);
 assert.deepEqual(item.adjustment.scale,[1.4,.8]);
});
