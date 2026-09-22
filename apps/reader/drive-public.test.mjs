import test from 'node:test';
import assert from 'node:assert/strict';
import { publicDriveURL, parsePublicFolder, PublicDriveClient } from './drive-public.js';
const listing = rows => `<title>Shared notes - Google Drive</title><script>window['_DRIVE_ivd'] = '${JSON.stringify([rows,null,null,null,null,1]).replace(/[\[\]"]/g, c => '\\x'+c.charCodeAt(0).toString(16))}';</script>`;
test('public folder parser reads metadata without executing page scripts', () => {
  const page = parsePublicFolder(listing([['child',['parent'],'Notes','application/vnd.google-apps.folder'],['note',[],"Lecture.noteful",'application/octet-stream']]), {id:'parent'});
  assert.equal(page.folder.name,'Shared notes');
  assert.equal(page.files.length,2);
  assert.equal(page.files[1].name,'Lecture.noteful');
  assert.throws(()=>parsePublicFolder('<html>Sign in</html>',{id:'private'}),/not publicly readable/);
  assert.throws(()=>parsePublicFolder("window['_DRIVE_ivd'] = 'alert(1)'",{id:'bad'}),/unreadable/);
});
test('public requests only construct Google read URLs and retain resource keys', () => {
  assert.equal(new URL(publicDriveURL({action:'folder',id:'folder',resourceKey:'key'})).searchParams.get('resourcekey'),'key');
  assert.equal(new URL(publicDriveURL({action:'download',id:'note'})).hostname,'drive.usercontent.google.com');
  for(const request of [{action:'delete',id:'note'},{action:'folder',id:'../private'},{action:'download',id:'note',resourceKey:'x/y'}])assert.throws(()=>publicDriveURL(request));
});
test('public browsing downloads only the selected supported file and rejects HTML', async () => {
  const calls=[];
  const client=new PublicDriveClient(async request=>{calls.push(request);return request.action==='folder'?listing([['note',[],'Lecture.noteful','application/octet-stream']]):{base64:btoa('note bytes')};});
  const folder=await client.folder({id:'parent'});
  const page=await client.children(folder);
  assert.equal(calls.length,1);
  assert.equal(await (await client.download(page.files[0])).text(),'note bytes');
  assert.equal(calls.length,2);
  client.transport=async()=>({base64:btoa('<!doctype html><html>Permission denied</html>')});
  await assert.rejects(client.download(page.files[0]),/did not allow/);
});
