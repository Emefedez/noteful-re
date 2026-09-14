// Directional thresholds keep toolbar changes from flickering around a scroll boundary.
export class ChromeState {
 constructor() { this.reset(); }
 reset(top=0) { this.compact=false;this.anchor=top; }
 toggle(top) { this.compact=!this.compact;this.anchor=top;return this.compact; }
 observe(top) {
  if (this.compact) {
   this.anchor=Math.max(this.anchor,top);
   if(top<=8||this.anchor-top>=64){this.compact=false;this.anchor=top;}
  } else {
   this.anchor=Math.min(this.anchor,top);
   if(top-this.anchor>=96){this.compact=true;this.anchor=top;}
  }
  return this.compact;
 }
}
export function highlightPoints(start,end) { return [[...start],[...end]]; }
