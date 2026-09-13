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
    vendor=ROOT/'apps/reader/vendor/pdfjs';vendor.mkdir(parents=True,exist_ok=True)
    for folder in ['build','cmaps','standard_fonts','wasm']:
        shutil.copytree(pdfjs/folder,vendor/folder,dirs_exist_ok=True)
    shutil.copy2(pdfjs/'LICENSE',vendor/'LICENSE')
    examples=ROOT/'apps/reader/samples';examples.mkdir(exist_ok=True)
    names=[]
    for p in sorted((ROOT/'samples').glob('*.noteful')):
        shutil.copy2(p,examples/p.name);names.append(p.name)
    demo=ROOT/'tests/fixtures/editing-demo.nfedit'
    if demo.is_file():
        shutil.copy2(demo,examples/demo.name);names.append(demo.name)
    multi=ROOT/'tests/fixtures/multi-audio-synthetic.noteful'
    shutil.copy2(multi,examples/multi.name);names.append(multi.name)
    (examples/'index.json').write_text(json.dumps(names,ensure_ascii=False)+'\n')
    assets=[str(p.relative_to(ROOT/'apps/reader')) for p in (ROOT/'apps/reader').rglob('*') if p.is_file() and not any(part in ('node_modules','samples') for part in p.relative_to(ROOT/'apps/reader').parts) and p.suffix not in ('.map',) and not p.name.endswith('.test.mjs') and p.name not in ('precache.json','package-lock.json','package.json','test.mjs')]
    assets.extend(['./'])
    (ROOT/'apps/reader/precache.json').write_text(json.dumps(assets)+'\n')
    print('Built apps/reader/. Serve with any static HTTP server. No Python/Rust server required at runtime.')

if __name__=='__main__':main()
