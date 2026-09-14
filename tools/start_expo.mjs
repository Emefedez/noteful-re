// One foreground command owns both servers; Ctrl-C stops both.
import {spawn} from 'node:child_process';
import {existsSync} from 'node:fs';
import {fileURLToPath} from 'node:url';
import {readerServer,root} from './serve_web.mjs';
import path from 'node:path';
if(!existsSync(path.join(root,'pkg/noteful_wasm_bg.wasm')))throw Error('Build the reader first: python3 tools/build_web.py');
const mobile=fileURLToPath(new URL('../apps/mobile/',import.meta.url));
const server=readerServer();
server.on('error',error=>{console.error(`Reader could not start: ${error.message}`);process.exitCode=1;});
server.listen(8768,'0.0.0.0',()=>{
 console.log('Reader ready on port 8768. Computer and phone must share Wi-Fi.\nThe reader and included examples are available to devices on this LAN.\nScan the Expo Go QR below. Ctrl-C stops both servers.');
 const expo=spawn(process.execPath,[path.join(mobile,'node_modules/expo/bin/cli'),'start','--go','--lan','--port','8081'],{cwd:mobile,stdio:'inherit',env:process.env});
 let stopping=false;
 const stop=()=>{if(stopping)return;stopping=true;expo.kill('SIGTERM');server.close();};
 process.on('SIGINT',stop);process.on('SIGTERM',stop);
 expo.on('error',error=>{console.error(error.message);stop();process.exitCode=1;});
 expo.on('exit',code=>{server.close();process.exitCode=code||0;});
});
