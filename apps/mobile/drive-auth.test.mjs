import test from 'node:test';
import assert from 'node:assert/strict';
import {mobileDriveToken} from './drive-auth.mjs';
const scope='https://www.googleapis.com/auth/drive.readonly';
test('mobile SDK asks for read-only Drive and returns only a short-lived access token',async()=>{
 let configuration;
 const sdk={configure:value=>configuration=value,hasPlayServices:async()=>true,signIn:async()=>({type:'success',data:{scopes:[scope]}}),getTokens:async()=>({accessToken:'test-only',idToken:'not-forwarded'})};
 assert.deepEqual(await mobileDriveToken(sdk,{webClientId:'web-client'}),{access_token:'test-only',scope,expires_in:3000});
 assert.deepEqual(configuration.scopes,[scope]);assert.equal(configuration.offlineAccess,false);
 sdk.signIn=async()=>({type:'cancelled'});await assert.rejects(mobileDriveToken(sdk,{}),/cancelled/);
 sdk.signIn=async()=>({type:'success',data:{scopes:[]}});await assert.rejects(mobileDriveToken(sdk,{}),/permission/);
});
