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
    pkg=ROOT/'web/pkg';pkg.mkdir(parents=True,exist_ok=True)
    subprocess.run([str(bindgen),'--target','web','--out-dir',str(pkg),str(ROOT/'target/wasm32-unknown-unknown/release/noteful_wasm.wasm')],check=True)
    npm='npm.cmd' if os.name=='nt' else 'npm'
    subprocess.run([npm,'ci','--ignore-scripts'],cwd=ROOT/'web',check=True)
    pdfjs=ROOT/'web/node_modules/pdfjs-dist'
    vendor=ROOT/'web/vendor/pdfjs';vendor.mkdir(parents=True,exist_ok=True)
    for folder in ['build','cmaps','standard_fonts','wasm']:
        shutil.copytree(pdfjs/folder,vendor/folder,dirs_exist_ok=True)
    shutil.copy2(pdfjs/'LICENSE',vendor/'LICENSE')
    examples=ROOT/'web/samples';examples.mkdir(exist_ok=True)
    names=[]
    for p in sorted((ROOT/'samples').glob('*.noteful')):
        shutil.copy2(p,examples/p.name);names.append(p.name)
    demo=ROOT/'examples/edicion-basica.nfedit'
    if demo.is_file():
        shutil.copy2(demo,examples/demo.name);names.append(demo.name)
    (examples/'index.json').write_text(json.dumps(names,ensure_ascii=False)+'\n')
    print('Built web/. Serve with any static HTTP server. No Python/Rust server required at runtime.')

if __name__=='__main__':main()
