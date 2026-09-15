import {SelectionController} from './selection.js';
import {ChromeState,highlightPoints} from './chrome-state.js';
import {download} from './download.js';
import {enhanceSelects,refreshSelects} from './select.js';
import {decorateIcons} from './icons.js';
import {PdfBackgrounds} from './pdf-background.js';
import {AudioController} from './audio.js';
import {indexTimedInk,updateTimedInk} from './ink-timeline.js';
import {shapePoints} from './shapes.js';
const $=id=>document.getElementById(id),ns='http://www.w3.org/2000/svg';
enhanceSelects();decorateIcons();
const worker=new Worker('./worker.js',{type:'module'}),pending=new Map();
let request=0,epoch=0,revision=0,ready=false,dirty=false,editing=false,doc=null,page=0,tool='pan',activeLayer=0,gesture=null,backgrounds=null;

const chromeState=new ChromeState();let chromeSettling=false;
let panels=[],observer=null,scrollFrame=0;
const audio=new AudioController(resource=>call('audio',{resource}),jump,syncInk);
const selection=new SelectionController({call,patch:patchItem,remove:item=>action('remove',{page:item.page,itemId:item.id}),panel:index=>panels[index],editable:()=>!!doc&&!editing,changed:toolOptions,status});
function status(text,error=false){$('status').textContent=text;$('status').className=error?'error':'';}
function call(op,args={}){return new Promise((resolve,reject)=>{const id=++request;pending.set(id,{resolve,reject});worker.postMessage({id,op,page,...args},args.bytes?[args.bytes]:[]);});}
worker.onmessage=({data})=>{
 if(data.ready){ready=true;$('open').disabled=$('examples').disabled=false;status('Listo. Todo se procesa en tu dispositivo.');return;}
 if(data.fatal){status(data.fatal,true);return;}const p=pending.get(data.id);if(!p)return;pending.delete(data.id);data.error?p.reject(Error(data.error)):p.resolve(data.result);
};
worker.onerror=e=>{for(const p of pending.values())p.reject(Error(e.message));pending.clear();ready=false;status('Error del núcleo: '+e.message,true);};
function canReplace(){return !dirty||confirm('Hay cambios sin guardar. ¿Abrir otro documento y descartarlos?');}
function reset(){selection.clear();cancelGesture();chromeState.reset();setCompact(false);observer?.disconnect();backgrounds?.close();audio.reset();panels=[];doc=null;$('pages').replaceChildren();$('editor').hidden=true;$('empty').hidden=false;dirty=false;}
async function load(file,token=++epoch){
 if(!ready||token!==epoch)return;reset();editing=true;status('Abriendo documento…');
 try {
  const bytes=await file.arrayBuffer();if(token!==epoch)return;
  const result=await call('open',{bytes,project:file.name.toLowerCase().endsWith('.nfedit'),page:0});if(token!==epoch)return;
  revision++;doc=result;page=0;activeLayer=result.layers.find(l=>l.visible&&!l.locked)?.id??result.layers[0]?.id??0;
  backgrounds=new PdfBackgrounds(resource=>{if(token!==epoch)throw Error('Documento cerrado');return call('pdf',{resource});});
  $('examples').value=[...$('examples').options].some(o=>o.value===file.name)?file.name:'';
  $('title').textContent=result.title||'Nota sin título';$('editor').hidden=false;$('empty').hidden=true;
  $('pageNumber').max=result.pages;$('save').disabled=$('native').disabled=false;
  buildPages(result.page_sizes);updateTools(result);layerPanel(result.layers);audio.open(result.audio||[],result.recordings||[]);
  await renderPage(panels[0],result);if(token!==epoch)return;status('Nota abierta.');
 } catch(e){if(token===epoch)status('No se pudo abrir: '+e.message,true);}finally{if(token===epoch)editing=false;}
}
function buildPages(sizes){
 const fragment=document.createDocumentFragment();
 panels=sizes.map((size,index)=>{const el=document.createElement('article');el.className='sheet';el.dataset.page=index;el.dataset.tool=tool;el.setAttribute('aria-label',`Página ${index+1}`);el.style.aspectRatio=size.join('/');const p={index,size,el,view:null,near:false,token:0,loading:false,pdfReady:false};placeholder(p);fragment.append(el);el.onpointerdown=e=>pointerDown(e,p);el.onpointermove=pointerMove;el.onpointerup=pointerUp;el.onpointercancel=cancelGesture;el.onlostpointercapture=()=>{if(gesture?.panel===p)cancelGesture();selection.lostCapture(p);};return p;});
 $('pages').append(fragment);resize();$('viewport').scrollTop=0;
 observer=new IntersectionObserver(entries=>{for(const entry of entries){const p=panels[Number(entry.target.dataset.page)];if(!p||p.el!==entry.target)continue;p.near=entry.isIntersecting;if(p.near){if(!p.view)renderPage(p);}else if(gesture?.panel!==p){p.token++;p.view=null;p.ink=null;p.pdfReady=false;placeholder(p);}}},{root:$('viewport'),rootMargin:'600px 0px'});
 for(const p of panels)observer.observe(p.el);
}
function placeholder(p){p.render=null;p.overlay=null;p.ink=null;const span=document.createElement('span');span.className='page-placeholder';span.textContent=`Página ${p.index+1}`;p.el.replaceChildren(span);}
function resize(){if(!doc)return;const fit=$('zoom').value==='fit',space=$('viewport').clientWidth-48;for(const p of panels)p.el.style.width=(fit?Math.min(p.size[0],Math.max(100,space)):p.size[0]*Number($('zoom').value))+'px';}
async function renderPage(p,provided){
 if(p.loading){p.retry=true;return;}p.retry=false;p.loading=true;const token=++p.token,version=revision,note=epoch;
 try {
  const result=provided||await call('view',{page:p.index});if(note!==epoch||token!==p.token||version!==revision)return;
  p.view=result;const render=document.createElement('div');render.className='render';render.innerHTML=result.svg;
  const overlay=document.createElementNS(ns,'svg');overlay.classList.add('overlay');overlay.setAttribute('viewBox',`0 0 ${p.size.join(' ')}`);p.render=render;p.overlay=overlay;p.el.replaceChildren(render,overlay);p.pdfReady=!result.pdf_background;p.ink=indexTimedInk(render,result.timings);syncInk();shapeHandles(p);
  if(p.index===page)updateTools(result);
  if(result.pdf_background){
   const image=await backgrounds.image(result.pdf_background,p.size);if(note!==epoch||token!==p.token||version!==revision)return;
   const el=document.createElementNS(ns,'image');for(const [k,v] of Object.entries({href:image,width:p.size[0],height:p.size[1],preserveAspectRatio:'none'}))el.setAttribute(k,v);
   render.querySelector('[data-background]').replaceChildren(el);p.pdfReady=true;
  }
 } catch(e){if(note===epoch&&token===p.token){const error=document.createElement('p');error.className='page-error';error.textContent='No se pudo mostrar esta página: '+e.message;p.el.append(error);}}
 finally{p.loading=false;if(note===epoch){if(p.near&&(p.retry||version!==revision||token!==p.token))renderPage(p);if(p.index===page)$('svg').disabled=!p.pdfReady;}}
}
function updateTools(result){
 refreshSelects();
 $('undo').disabled=!doc.can_undo;$('redo').disabled=!doc.can_redo;
 $('pageNumber').value=page+1;$('pageLabel').textContent=`de ${doc.pages}`;$('counts').textContent=`${result.visible_imported} elementos · ${result.visible_added} nuevos`;$('warnings').textContent=result.warnings.join(' ');
 $('svg').disabled=!panels[page]?.pdfReady;
 $('textInfo').hidden=!result.texts?.length;$('textRuns').replaceChildren();
 for(const block of result.texts||[])for(const r of block.runs){if(!r.text.replaceAll('\u200b',''))continue;const li=document.createElement('li');li.textContent=`${r.text} · ${(r.font_size*6/11).toLocaleString('es',{maximumFractionDigits:2})} pt · ${r.font_family||r.font_name||'Sistema'}${r.bold?' · negrita':''}${r.italic?' · cursiva':''}${r.underline?' · subrayado':''}${r.strikethrough?' · tachado':''}`;$('textRuns').append(li);}
}
function setPage(index){if(index===page)return;panels[page]?.el.classList.remove('active');page=index;const p=panels[page];p.el.classList.add('active');$('pageNumber').value=page+1;if(p.view)updateTools(p.view);else renderPage(p);}
function jump(index){if(!doc||!Number.isInteger(index)||index<0||index>=doc.pages)return;cancelGesture();setPage(index);const viewport=$('viewport');viewport.scrollTop+=panels[index].el.getBoundingClientRect().top-viewport.getBoundingClientRect().top-24;status(`Página ${index+1}.`);}
$('viewport').onscroll=()=>{cancelAnimationFrame(scrollFrame);scrollFrame=requestAnimationFrame(()=>{if(!doc)return;const top=$('viewport').getBoundingClientRect().top+80;let low=0,high=panels.length-1;while(low<high){const mid=(low+high)>>1;if(panels[mid].el.getBoundingClientRect().bottom<top)low=mid+1;else high=mid;}setPage(low);if(!gesture&&!selection.active&&!chromeSettling)setCompact(chromeState.observe($('viewport').scrollTop));});};
function toolOptions(){
 $('shapeOptions').hidden=tool!=='shape';$('highlightOptions').hidden=tool!=='highlight';
 $('drawingOptions').hidden=tool==='select';$('selectionOptions').hidden=tool!=='select'||!selection.item;
 $('toolOptions').hidden=chromeState.compact||(!['draw','highlight','shape'].includes(tool)&&!(tool==='select'&&selection.item));
}
function setCompact(compact){
 const changed=document.body.classList.contains('compact-chrome')!==compact;
 document.body.classList.toggle('compact-chrome',compact);chromeState.compact=compact;
 $('toolbarToggle').setAttribute('aria-expanded',String(!compact));
 $('toolbarToggle').setAttribute('aria-label',compact?'Mostrar herramientas':'Compactar herramientas');
 $('toolbarToggle').title=compact?'Mostrar herramientas':'Compactar herramientas';toolOptions();
 if(changed){chromeSettling=true;requestAnimationFrame(()=>requestAnimationFrame(()=>{chromeState.anchor=$('viewport').scrollTop;chromeSettling=false;}));}
}
$('toolbarToggle').onclick=()=>{cancelGesture();setCompact(chromeState.toggle($('viewport').scrollTop));};
async function action(op,args={}){
 if(!doc||editing)return;editing=true;const token=epoch;
 try {const result=await call(op,args);if(token!==epoch)return;dirty=true;revision++;doc=result;
  if(op==='draw'&&args.line.shape){document.querySelector('[data-tool=select]').click();selection.selectId(args.page??page,`new:${result.edit_count-1}`);}else if(selection.item){selection.selectId(selection.item.page,selection.item.id);}updateTools(result);layerPanel(result.layers);
  for(const p of panels){p.token++;p.view=null;if(p.near||p.index===page)renderPage(p,p.index===result.page?result:undefined);}
  status(op==='erase'?'Borrado aplicado. Puedes deshacerlo.':'Cambios guardados en la sesión.');
 }catch(e){if(token===epoch)status(e.message,true);}finally{if(token===epoch){editing=false;for(const p of panels){p.overlay?.replaceChildren();shapeHandles(p);}}}
}
function syncInk(){
 const recording=audio.recording,time=audio.time;
 for(const p of panels){if(p.view)updateTimedInk(p.ink||[],recording?.id,time);}
}
function layerPanel(layers){
 if(!layers.some(l=>l.id===activeLayer))activeLayer=layers[0]?.id||0;
 $('layersList').replaceChildren();
 for(const layer of layers){
  const row=document.createElement('div');row.className='layer'+(layer.id===activeLayer?' active':'');
  const controls=document.createElement('div');controls.className='layer-controls';const select=document.createElement('button');select.textContent=layer.id===activeLayer?'●':'○';select.setAttribute('aria-label',`Seleccionar ${layer.name}`);select.setAttribute('aria-pressed',String(layer.id===activeLayer));select.onclick=()=>{activeLayer=layer.id;layerPanel(layers);};
  const name=document.createElement('input');name.className='layer-title';name.value=layer.name;name.setAttribute('aria-label',`Nombre de capa ${layer.id+1}`);name.onchange=()=>action('layer',{layer:{...layer,name:name.value}});
  const visible=document.createElement('input');visible.type='checkbox';visible.checked=layer.visible;visible.setAttribute('aria-label',`Mostrar ${layer.name}`);visible.onchange=()=>action('layer',{layer:{...layer,visible:visible.checked}});
  const lock=document.createElement('button');lock.textContent=layer.locked?'Bloqueada':'Bloquear';lock.setAttribute('aria-label',`Bloquear ${layer.name}`);lock.setAttribute('aria-pressed',String(layer.locked));lock.onclick=()=>action('layer',{layer:{...layer,locked:!layer.locked}});
  const opacity=document.createElement('input');opacity.type='range';opacity.min=0;opacity.max=1;opacity.step=.05;opacity.value=layer.opacity;opacity.setAttribute('aria-label',`Opacidad ${layer.name}`);opacity.onchange=()=>action('layer',{layer:{...layer,opacity:Number(opacity.value)}});
  controls.append(select,name,visible);row.append(controls,lock,opacity);$('layersList').append(row);
 }
}
$('layersToggle').onclick=()=>{$('layersPanel').hidden=!$('layersPanel').hidden;$('layersToggle').setAttribute('aria-expanded',String(!$('layersPanel').hidden));resize();};
$('addLayer').onclick=()=>{const id=Math.max(...doc.layers.map(l=>l.id),-1)+1;activeLayer=id;action('layer',{layer:{id,name:`Capa ${id+1}`,visible:true,locked:false,opacity:1}});};
function cancelGesture(){selection.cancel();const g=gesture;gesture=null;if(!g)return;g.panel.overlay?.replaceChildren();if(g.hidden)g.hidden.style.visibility='';shapeHandles(g.panel);if(g.panel.el.hasPointerCapture(g.id))g.panel.el.releasePointerCapture(g.id);}
function point(e,p){const r=p.el.getBoundingClientRect();return [Math.max(0,Math.min(p.size[0],(e.clientX-r.left)/r.width*p.size[0])),Math.max(0,Math.min(p.size[1],(e.clientY-r.top)/r.height*p.size[1]))];}
function pointerDown(e,p){
 if(gesture){if(e.pointerId!==gesture.id)cancelGesture();return;}if(!doc||editing||!p.view||e.button!==0)return;
 setPage(p.index);
 if(selection.down(e,p,tool))return;
 if(tool==='pan'){if(e.pointerType!=='mouse')return;e.preventDefault();gesture={id:e.pointerId,tool,panel:p,x:e.clientX,y:e.clientY,left:$('viewport').scrollLeft,top:$('viewport').scrollTop};p.el.setPointerCapture(e.pointerId);return;}
 const layer=doc.layers.find(l=>l.id===activeLayer);if(tool!=='erase'&&(!layer?.visible||layer.locked)){status('Selecciona una capa visible y desbloqueada.',true);return;}
 e.preventDefault();const start=point(e,p),width=tool==='erase'?20:Number($('width').value),color=$('color').value;
 const el=document.createElementNS(ns,'polyline'),dot=document.createElementNS(ns,'circle');
 for(const [k,v] of Object.entries({fill:'none',stroke:tool==='erase'?'#ed6b55':color,'stroke-width':width,'stroke-linecap':'round','stroke-linejoin':'round',opacity:tool==='erase'?.3:tool==='highlight'?.5:1}))el.setAttribute(k,v);
 dot.setAttribute('r',width/2);dot.setAttribute('fill',tool==='erase'?'#ed6b55':color);dot.setAttribute('opacity',tool==='highlight'?.5:tool==='erase'?.3:1);
 p.overlay.append(el,dot);gesture={id:e.pointerId,tool,straight:tool==='highlight'&&$('highlightMode').value==='straight',panel:p,points:[start],start,width,color,layer:activeLayer,el,dot};p.el.setPointerCapture(e.pointerId);preview();
}
function preview(){const g=gesture;if(!g||g.tool==='pan')return;g.el.setAttribute('points',g.points.map(p=>p.join(',')).join(' '));g.dot.style.display=g.points.length>1?'none':'';g.dot.setAttribute('cx',g.points[0][0]);g.dot.setAttribute('cy',g.points[0][1]);}
function appendPoint(e){const g=gesture;if(g.tool==='shape'){g.points=shapePoints($('shape').value,g.start,point(e,g.panel));}else if(g.straight){g.points=highlightPoints(g.start,point(e,g.panel));}else{const samples=e.getCoalescedEvents?.()||[];for(const sample of samples.length?samples:[e]){const p=point(sample,g.panel),last=g.points.at(-1);if(Math.hypot(p[0]-last[0],p[1]-last[1])>=.3&&g.points.length<8192)g.points.push(p);}}preview();}
function pointerMove(e){if(selection.move(e))return;if(!gesture||gesture.id!==e.pointerId)return;e.preventDefault();if(gesture.tool==='pan'){$('viewport').scrollLeft=gesture.left+gesture.x-e.clientX;$('viewport').scrollTop=gesture.top+gesture.y-e.clientY;}else appendPoint(e);}
function pointerUp(e){if(selection.up(e))return;if(!gesture||gesture.id!==e.pointerId)return;if(gesture.tool==='pan'){cancelGesture();return;}appendPoint(e);const g=gesture;gesture=null;g.panel.el.releasePointerCapture(e.pointerId);if(g.tool==='erase')action('erase',{page:g.panel.index,points:g.points,radius:10});else{const rgba=[1,3,5].map(i=>parseInt(g.color.slice(i,i+2),16)/255);action('draw',{page:g.panel.index,line:{points:g.points,width:g.width,rgba:[...rgba,1],tool:g.tool==='highlight'?1:0,layer:g.layer,...(g.tool==='shape'?{shape:{kind:$('shape').value,start:g.start,end:point(e,g.panel)}}:{})}});}}
for(const button of document.querySelectorAll('[data-tool]'))button.onclick=()=>{cancelGesture();tool=button.dataset.tool;if(tool!=='select')selection.clear();chromeState.reset($('viewport').scrollTop);setCompact(false);for(const p of panels)p.el.dataset.tool=tool;for(const b of document.querySelectorAll('button[data-tool]'))b.setAttribute('aria-pressed',String(b===button));for(const p of panels)shapeHandles(p);if(tool==='highlight'){$('color').value='#ffdf38';$('width').value='16';}else if(tool==='draw'){$('color').value='#246bce';$('width').value='2';}toolOptions();refreshSelects();status(tool==='select'?'Toca un elemento para moverlo o modificarlo.':tool==='highlight'?($('highlightMode').value==='straight'?'Subrayador recto: arrastra entre los dos extremos.':'Subrayador libre: dibuja sobre la página.'):tool==='erase'?'Arrastra para borrar trazos completos.':tool==='pan'?'Desplázate por las páginas.':'Dibuja en la capa seleccionada.');};
$('highlightMode').onchange=()=>{cancelGesture();status($('highlightMode').value==='straight'?'Subrayador recto: arrastra entre los dos extremos.':'Subrayador libre: dibuja sobre la página.');};
$('shape').onchange=()=>document.querySelector('[data-tool="shape"]').click();
$('pageNumber').onchange=()=>jump(Number($('pageNumber').value)-1);$('zoom').onchange=()=>{cancelGesture();resize();};new ResizeObserver(resize).observe($('viewport'));
$('undo').onclick=()=>{cancelGesture();action('undo');};$('redo').onclick=()=>{cancelGesture();action('redo');};
document.addEventListener('keydown',e=>{if(e.key==='Escape'){cancelGesture();return;}if(/INPUT|SELECT|TEXTAREA/.test(e.target.tagName))return;if((e.metaKey||e.ctrlKey)&&e.key.toLowerCase()==='z'){e.preventDefault();action(e.shiftKey?'redo':'undo');}});
$('open').onclick=()=>$('file').click();$('file').onchange=e=>{if(e.target.files[0]&&canReplace())load(e.target.files[0]);e.target.value='';};
$('examples').onchange=async e=>{if(!e.target.value||!canReplace())return;const name=e.target.value,token=++epoch;try{const r=await fetch('./samples/'+encodeURIComponent(name));if(!r.ok)throw Error('Ejemplo no disponible');await load(new File([await r.blob()],name),token);}catch(error){if(token===epoch)status(error.message,true);}};
fetch('./samples/index.json').then(r=>r.json()).then(names=>{for(const name of names){const o=document.createElement('option');o.value=name;o.textContent=name;$('examples').append(o);}}).catch(()=>{});
for(const event of ['dragover','drop'])$('drop').addEventListener(event,e=>{e.preventDefault();$('drop').classList.toggle('drag',event==='dragover');if(event==='drop'&&e.dataTransfer.files[0]&&canReplace())load(e.dataTransfer.files[0]);});$('drop').ondragleave=()=>$('drop').classList.remove('drag');
function filename(){return (doc?.title||'Nota').replace(/[<>:"/\\|?*\x00-\x1f]/g,'_');}
async function save(native){if(!doc||editing)return;cancelGesture();editing=true;const token=epoch;try{const data=await call(native?'export':'save');if(token!==epoch)return;const delivery=await download(data,filename()+(native?'.noteful':'.nfedit'),native?'application/octet-stream':'application/json');if(token!==epoch)return;if(!native&&!delivery.shared)dirty=false;status(delivery.shared?'Elige Guardar en el menú del dispositivo.':native?'Archivo .noteful exportado.':'Proyecto guardado.');document.querySelector('details.menu').open=false;}catch(e){status(e.message,true);}finally{if(token===epoch)editing=false;}}
$('save').onclick=()=>save(false);$('native').onclick=()=>save(true);
$('svg').onclick=async()=>{const p=panels[page];if(p?.pdfReady&&!editing){await download(new XMLSerializer().serializeToString(p.render.firstElementChild),`${filename()}-p${page+1}.svg`,'image/svg+xml').catch(e=>status(e.message,true));document.querySelector('details.menu').open=false;}};
window.addEventListener('beforeunload',e=>{if(dirty){e.preventDefault();e.returnValue='';}});
if('serviceWorker' in navigator)navigator.serviceWorker.register('./sw.js').catch(()=>{});

function shapeHandles(p){selection.render(p);}
async function patchItem(item,adjustment){
 if(editing||!doc)return null;editing=true;const token=epoch;
 try{
  const result=await call('adjust',{page:item.page,itemId:item.id,adjustment});if(token!==epoch)return null;
  dirty=true;Object.assign(doc,{can_undo:result.can_undo,can_redo:result.can_redo,edit_count:result.edit_count});
  const p=panels[item.page],el=p.render?.querySelector(`[data-item="${item.id}"]`);
  if(el){el.innerHTML=result.svg;el.removeAttribute('transform');}
  if(p.view){Object.assign(p.view,{can_undo:result.can_undo,can_redo:result.can_redo,edit_count:result.edit_count});}
  $('undo').disabled=!result.can_undo;$('redo').disabled=!result.can_redo;
  status('Elemento actualizado. Puedes deshacer el cambio.');return result;
 }catch(e){if(token===epoch)status(e.message,true);return null;}finally{if(token===epoch)editing=false;}
}
$('insertShape').onclick=()=>{
 if(!doc||editing)return;document.querySelector('[data-tool="shape"]').click();const p=panels[page],r=p.el.getBoundingClientRect(),v=$('viewport').getBoundingClientRect();
 const cy=Math.max(80,Math.min(p.size[1]-80,((Math.max(r.top,v.top)+Math.min(r.bottom,v.bottom))/2-r.top)/r.height*p.size[1]));
 const start=[p.size[0]/2-100,Math.min(p.size[1]-160,cy-60)],end=[p.size[0]/2+100,Math.min(p.size[1]-20,cy+60)],shape={kind:$('shape').value,start,end},rgba=[1,3,5].map(i=>parseInt($('color').value.slice(i,i+2),16)/255);
 action('draw',{page,line:{points:shapePoints(shape.kind,start,end),shape,width:Number($('width').value),rgba:[...rgba,1],tool:0,layer:activeLayer}});
};

$('audioDownload').onclick=async event=>{if(!window.ReactNativeWebView)return;event.preventDefault();try{const {href,download:name}=event.currentTarget;const blob=await (await fetch(href)).blob();await download(blob,name,blob.type);}catch(e){status(e.message,true);}};
