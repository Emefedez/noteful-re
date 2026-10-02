import test from 'node:test';
import assert from 'node:assert/strict';
import { driveBrowser } from './drive-browser.js';
import { FOLDER_MIME } from './drive-client.js';
const tick = () => new Promise(resolve => setImmediate(resolve));
class Element {
  constructor(tag = 'div') { this.tag = tag; this.children = []; this.dataset = {}; this.listeners = {}; this.value = ''; this.open = false; }
  append(...nodes) { for(const node of nodes) this.children.push(...(node.tag === 'fragment' ? node.children : [node])); }
  replaceChildren(...nodes) { this.children = []; this.append(...nodes); }
  setAttribute() {}
  closest() { return this; }
  querySelectorAll(tag) { return this.children.flatMap(child => [...(child.tag === tag ? [child] : []), ...child.querySelectorAll(tag)]); }
  addEventListener(type, fn) { this.listeners[type] = fn; }
  showModal() { this.open = true; }
  close() { this.open = false; this.listeners.close?.(); }
}
function setup(t, overrides = {}) {
  const originals = Object.fromEntries(['document','window','location','localStorage'].map(key => [key, Object.getOwnPropertyDescriptor(globalThis,key)]));
  t.after(() => { for(const [key,value] of Object.entries(originals)) { if(value) Object.defineProperty(globalThis,key,value); else delete globalThis[key]; } });
  const nodes = new Map(), node = id => { if(!nodes.has(id)) nodes.set(id,new Element()); return nodes.get(id); };
  globalThis.document = { getElementById:node, querySelector:selector=>selector.includes('google-drive-api-key')&&overrides.siteApiKey?{content:overrides.siteApiKey}:null, createElement:tag=>new Element(tag), createDocumentFragment:()=>new Element('fragment') };
  globalThis.window = { isSecureContext:true };
  globalThis.location = { protocol:'https:' };
  globalThis.localStorage = { getItem:()=>null,setItem:()=>{} };
  const opened = [], calls = [];
  const folder = {id:'folder',name:'Noteful',mimeType:FOLDER_MIME};
  const file = {id:'file',name:'Test.noteful'};
  const client = {
    connected:false,token:'',apiKey:'',
    get publicAccess(){ return !this.connected&&!!this.apiKey; },
    get ready(){ return this.connected||this.publicAccess; },
    clear(){ this.connected=false;this.token=''; },
    authorize(){ this.connected=true;this.token='test'; },
    async folders(){ calls.push('list-folders');return {files:[folder]}; },
    async children(){ calls.push('list-files');return {files:[file]}; },
    async folder(reference){ calls.push('open-folder:'+reference.id);return folder; },
    async download(){ calls.push('download');return new File(['bytes'],file.name); },
    ...Object.fromEntries(Object.entries(overrides).filter(([key])=>key!=='siteApiKey')),
  };
  let callback;
  driveBrowser({ open:async file=>{opened.push(file);return true;},client,identityLoader:async()=>({}),authorize:(_id,_key,success)=>{callback=success;} });
  return {node,opened,calls,client,authorize:()=>callback({})};
}
test('Drive panel lists without downloading and opens only the chosen file', async t => {
  const ui=setup(t);
  await ui.node('driveOpen').onclick();
  ui.node('driveConnect').onclick();ui.authorize();await tick();
  assert.deepEqual(ui.calls,['list-folders']);
  ui.node('driveList').querySelectorAll('button')[0].onclick();await tick();
  assert.deepEqual(ui.calls,['list-folders','list-files']);
  assert.equal(ui.opened.length,0);
  ui.node('driveList').querySelectorAll('button')[0].onclick();await tick();
  assert.deepEqual(ui.calls,['list-folders','list-files','download']);
  assert.equal(ui.opened[0].name,'Test.noteful');
  assert.equal(ui.node('driveDialog').open,false);
});
test('closing Drive during a download ignores even a late successful response', async t => {
  let resolveDownload, signal;
  const ui=setup(t,{download:(_file,abort)=>{signal=abort;return new Promise(resolve=>{resolveDownload=resolve;});}});
  await ui.node('driveOpen').onclick();ui.node('driveConnect').onclick();ui.authorize();await tick();
  ui.node('driveList').querySelectorAll('button')[0].onclick();await tick();
  ui.node('driveList').querySelectorAll('button')[0].onclick();
  ui.node('driveClose').onclick();
  assert.equal(signal.aborted,true);
  resolveDownload(new File(['bytes'],'late.noteful'));await tick();
  assert.equal(ui.opened.length,0);
});
test('late OAuth completion after dismissal does not reconnect or request files', async t => {
  const ui=setup(t);
  await ui.node('driveOpen').onclick();ui.node('driveConnect').onclick();
  ui.node('driveClose').onclick();ui.authorize();await tick();
  assert.equal(ui.client.connected,false);assert.deepEqual(ui.calls,[]);
});
test('an API key opens a public folder link and downloads without sign-in', async t => {
  const ui=setup(t);
  await ui.node('driveOpen').onclick();
  assert.equal(ui.node('driveUseFolder').disabled,true);
  ui.node('driveApiKey').value='AIza-test';ui.node('driveApiKey').oninput();
  assert.equal(ui.node('driveUseFolder').disabled,false);
  assert.equal(ui.node('driveFind').disabled,true);
  ui.node('driveFolderLink').value='https://drive.google.com/drive/folders/1Gm9OsGBbfXrtymnIUbHtDq3TO2KHllqs';
  ui.node('driveUseFolder').onclick();await tick();
  assert.deepEqual(ui.calls,['open-folder:1Gm9OsGBbfXrtymnIUbHtDq3TO2KHllqs','list-files']);
  assert.equal(ui.node('driveBack').disabled,true);
  ui.node('driveList').querySelectorAll('button')[0].onclick();await tick();
  assert.equal(ui.opened[0].name,'Test.noteful');
  assert.equal(ui.client.connected,false);
});
test('the site key opens public links by default and a personal key overrides it', async t => {
  const ui=setup(t,{siteApiKey:'AIza-site'});
  assert.equal(ui.client.apiKey,'AIza-site');
  assert.equal(ui.node('driveApiKey').value,'');
  await ui.node('driveOpen').onclick();
  assert.equal(ui.node('driveUseFolder').disabled,false);
  assert.equal(ui.node('driveLinkSetup').open,true);
  ui.node('driveApiKey').value='AIza-personal';ui.node('driveApiKey').oninput();
  assert.equal(ui.client.apiKey,'AIza-personal');
  ui.node('driveApiKey').value='';ui.node('driveApiKey').oninput();
  assert.equal(ui.client.apiKey,'AIza-site');
});
