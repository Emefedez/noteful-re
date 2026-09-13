// Rasterize only the visible embedded PDF page. Ink stays editable SVG above it.
let pdfjs;
export class PdfBackgrounds {
  constructor(read){this.read=read;this.documents=new Map();this.images=new Map();this.closed=false;}
  async document(id){
    if(!this.documents.has(id)) this.documents.set(id,(async()=>{
      pdfjs ||= await import('./vendor/pdfjs/build/pdf.mjs');
      pdfjs.GlobalWorkerOptions.workerSrc=new URL('./vendor/pdfjs/build/pdf.worker.mjs',import.meta.url).href;
      const data=await this.read(id);
      if(this.closed)throw Error('Documento cerrado');
      const base=new URL('./vendor/pdfjs/',import.meta.url).href;
      const task=pdfjs.getDocument({data,cMapUrl:base+'cmaps/',cMapPacked:true,standardFontDataUrl:base+'standard_fonts/',wasmUrl:base+'wasm/',isEvalSupported:false});
      const doc=await task.promise;
      if(this.closed){await doc.destroy();throw Error('Documento cerrado');}
      return doc;
    })());
    return this.documents.get(id);
  }
  async image(background,size){
    const key=JSON.stringify([background,size]);
    if(this.images.has(key))return this.images.get(key);
    const doc=await this.document(background.resource_id);
    const page=await doc.getPage(background.page_index+1);
    const original=page.getViewport({scale:1});
    // Canvas budget bounds preview resolution, never the size of the input note.
    const scale=Math.min(size[0]*Math.min(devicePixelRatio||1,2)/original.width,4096/Math.max(original.width,original.height));
    const viewport=page.getViewport({scale});
    const canvas=document.createElement('canvas');canvas.width=Math.ceil(viewport.width);canvas.height=Math.ceil(viewport.height);
    try {
      await page.render({canvasContext:canvas.getContext('2d'),viewport}).promise;
      const url=canvas.toDataURL('image/png');
      if(!this.closed){this.images.set(key,url);if(this.images.size>3)this.images.delete(this.images.keys().next().value);}
      return url;
    } finally {canvas.width=canvas.height=0;page.cleanup();}
  }
  close(){this.closed=true;this.images.clear();for(const task of this.documents.values())task.then(d=>d.destroy()).catch(()=>{});this.documents.clear();}
}
