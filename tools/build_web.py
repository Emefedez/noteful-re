#!/usr/bin/env python3
"""Build browser bindings from the same Rust core. No publishing."""
import json
import os
from pathlib import Path
import shutil
import subprocess
import tomllib

ROOT=Path(__file__).resolve().parents[1]

def main():
    env=dict(os.environ)
    cargo=shutil.which('cargo')
    if shutil.which('rustup') and 'RUSTC' not in env:
        # Homebrew cargo/rustc and rustup may use different sysroots.
        env['RUSTC']=subprocess.check_output(['rustup','which','rustc'],text=True).strip()
        cargo=subprocess.check_output(['rustup','which','cargo'],text=True).strip()
    suffix='.exe' if os.name=='nt' else ''
    bindgen=ROOT/'work/wasm-tools/bin'/('wasm-bindgen'+suffix)
    if not bindgen.is_file():
        found=shutil.which('wasm-bindgen')
        if not found:raise SystemExit('Install wasm-bindgen-cli matching Cargo.lock, then retry.')
        bindgen=Path(found)
    lock=tomllib.loads((ROOT/'Cargo.lock').read_text())
    version=next(p['version'] for p in lock['package'] if p['name']=='wasm-bindgen')
    installed=subprocess.check_output([str(bindgen),'--version'],text=True).split()[-1]
    if installed!=version:raise SystemExit(f'wasm-bindgen-cli {version} required, found {installed}')
    subprocess.run([cargo,'build','--locked','--release','-p','noteful-wasm','--target','wasm32-unknown-unknown'],cwd=ROOT,env=env,check=True)
    pkg=ROOT/'apps/reader/pkg';pkg.mkdir(parents=True,exist_ok=True)
    subprocess.run([str(bindgen),'--target','web','--out-dir',str(pkg),str(ROOT/'target/wasm32-unknown-unknown/release/noteful_wasm.wasm')],check=True)
    npm='npm.cmd' if os.name=='nt' else 'npm'
    subprocess.run([npm,'ci','--ignore-scripts'],cwd=ROOT/'apps/reader',check=True)
    pdfjs=ROOT/'apps/reader/node_modules/pdfjs-dist'
    vendor=ROOT/'apps/reader/vendor/pdfjs'
    if vendor.exists(): shutil.rmtree(vendor)
    (vendor/'build').mkdir(parents=True,exist_ok=True)
    for name in ['pdf.mjs','pdf.worker.mjs']: shutil.copy2(pdfjs/'build'/name,vendor/'build'/name)
    for folder in ['cmaps','standard_fonts','wasm']:
        shutil.copytree(pdfjs/folder,vendor/folder,dirs_exist_ok=True)
    shutil.copy2(pdfjs/'LICENSE',vendor/'LICENSE')
    # Bundle the local speech engine; model weights are fetched only on user request.
    speech=ROOT/'apps/reader/vendor/transformers'
    if speech.exists(): shutil.rmtree(speech)
    speech.mkdir(parents=True,exist_ok=True)
    transformers=ROOT/'apps/reader/node_modules/@huggingface/transformers'
    shutil.copy2(transformers/'dist/transformers.min.js',speech/'transformers.min.js')
    shutil.copy2(transformers/'LICENSE',speech/'LICENSE')
    runtime=ROOT/'apps/reader/node_modules/onnxruntime-web/dist'
    for name in ['ort-wasm-simd-threaded.asyncify.mjs','ort-wasm-simd-threaded.asyncify.wasm']:
        shutil.copy2(runtime/name,speech/name)
    reader=ROOT/'apps/reader'
    assets=sorted(p.name for p in reader.iterdir() if p.is_file() and p.suffix in ('.html','.js','.css','.svg','.webmanifest'))
    assets+=sorted(str(p.relative_to(reader)) for folder in ('pkg','vendor') for p in (reader/folder).rglob('*') if p.is_file() and p.suffix not in ('.map','.ts'))
    assets.append('./')
    (reader/'precache.json').write_text(json.dumps(assets)+'\n')
    print('Built apps/reader/. Serve with any static HTTP server. No Python/Rust server required at runtime.')

if __name__=='__main__':main()
