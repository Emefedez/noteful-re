export function shapePoints(kind,a,b){
 const [x,y]=a,[u,v]=b;
 if(kind==='rectangle')return [[x,y],[u,y],[u,v],[x,v],[x,y]];
 if(kind==='ellipse')return Array.from({length:65},(_,i)=>[(x+u)/2+Math.abs(u-x)/2*Math.cos(i*Math.PI/32),(y+v)/2+Math.abs(v-y)/2*Math.sin(i*Math.PI/32)]);
 if(kind==='triangle')return [[(x+u)/2,y],[u,v],[x,v],[(x+u)/2,y]];
 if(kind==='arrow'){
  const angle=Math.atan2(v-y,u-x),d=Math.min(24,Math.hypot(u-x,v-y)/3);
  return [a,b,[u-d*Math.cos(angle-.5),v-d*Math.sin(angle-.5)],b,[u-d*Math.cos(angle+.5),v-d*Math.sin(angle+.5)]];
 }
 return [a,b];
}
export function resizedShape(kind,fixed,moving){
 return ['rectangle','ellipse','triangle'].includes(kind)
 ?{kind,start:[Math.min(fixed[0],moving[0]),Math.min(fixed[1],moving[1])],end:[Math.max(fixed[0],moving[0]),Math.max(fixed[1],moving[1])]}
 :{kind,start:fixed,end:moving};
}
