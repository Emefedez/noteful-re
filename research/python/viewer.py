#!/usr/bin/env python3
"""Local Noteful viewer. Binds loopback, opens browser, never modifies input files."""
import argparse
import json
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path
import threading
from socketserver import TCPServer
import urllib.parse
import webbrowser
from noteful import FormatError
from render_note import render
ROOT=Path(__file__).resolve().parents[2]


class LocalServer(ThreadingHTTPServer):
    def server_bind(self):
        # HTTPServer's reverse DNS lookup stalls startup on this Mac.
        # The viewer always binds a numeric loopback address; DNS is unnecessary.
        TCPServer.server_bind(self)
        self.server_name = '127.0.0.1'
        self.server_port = self.server_address[1]


class Handler(BaseHTTPRequestHandler):
    def reply(self,status,body,mime='application/json'):
        if not isinstance(body,bytes):body=json.dumps(body,ensure_ascii=False).encode()
        self.send_response(status);self.send_header('Content-Type',mime);self.send_header('Content-Length',str(len(body)));self.send_header('Cache-Control','no-store');self.end_headers();self.wfile.write(body)
    def do_GET(self):
        url=urllib.parse.urlsplit(self.path);q=urllib.parse.parse_qs(url.query)
        if url.path=='/':return self.reply(200,(ROOT/'research/legacy-viewer/index.html').read_bytes(),'text/html; charset=utf-8')
        samples=self.server.samples
        if url.path=='/api/examples':return self.reply(200,{'examples':sorted(samples),'initial':self.server.initial})
        if url.path=='/api/example':
            name=q.get('name',[''])[0]
            if name not in samples:return self.reply(404,{'error':'Example not found.'})
            return self.open_note(samples[name].read_bytes(),name)
        if url.path=='/reference.pdf':return self.reply(200,(ROOT/'samples/Examen wuolah.pdf').read_bytes(),'application/pdf')
        return self.reply(404,{'error':'Route not found.'})
    def open_note(self,data,name):
        try:
            parser=getattr(self.server,'parser',None)
            result=render(data,name,parser=parser) if parser else render(data,name)
        except (FormatError,ValueError,KeyError,TypeError,IndexError) as e:
            return self.reply(422,{'error':'Could not decode file: '+str(e)})
        return self.reply(200,result)
    def do_POST(self):
        if self.path!='/api/open':return self.reply(404,{'error':'Route not found.'})
        origin=self.headers.get('Origin')
        allowed=f'http://127.0.0.1:{self.server.server_port}'
        if origin and origin!=allowed:return self.reply(403,{'error':'Origin not allowed.'})
        try:n=int(self.headers.get('Content-Length','0'))
        except ValueError:return self.reply(400,{'error':'Invalid length.'})
        if n<=0:return self.reply(400,{'error':'Empty file or invalid length.'})
        data=self.rfile.read(n)
        return self.open_note(data,'Local file')
    def log_message(self,fmt,*args):pass


def main(argv=None):
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--port',type=int,default=0);ap.add_argument('--no-browser',action='store_true');ap.add_argument('--example',default='Examen wuolah.noteful');ap.add_argument('--file',type=Path);ap.add_argument('--engine',choices=['python','rust'],default='python');a=ap.parse_args(argv)
    samples={p.name:p for p in (ROOT/'samples').glob('*.noteful')}
    if a.file:
        if not a.file.is_file():ap.error('File not found: '+str(a.file))
        samples[a.file.name]=a.file.resolve();a.example=a.file.name
    server=LocalServer(('127.0.0.1',a.port),Handler);server.initial=a.example
    server.samples=samples
    if a.engine=='rust':
        from rust_backend import parse as rust_parse
        server.parser=rust_parse
    url=f'http://127.0.0.1:{server.server_port}/';print('Noteful research viewer: '+url,flush=True);print('Ctrl+C to close. Files stay on this computer.',flush=True)
    if not a.no_browser:threading.Timer(.3,lambda:webbrowser.open(url)).start()
    try:server.serve_forever()
    except KeyboardInterrupt:pass
    finally:server.server_close()


if __name__=='__main__':main()
