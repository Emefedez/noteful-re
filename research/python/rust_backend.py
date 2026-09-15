"""Historical comparison adapter. Rust decodes; the Python oracle renders.

No silent fallback. The product uses WASM directly; this adapter is research-only.
"""
import json
from pathlib import Path
import subprocess
import sys
from noteful import FormatError

ROOT=Path(__file__).resolve().parents[2]

def parse(data):
    filename='noteful.exe' if sys.platform=='win32' else 'noteful'
    binary=ROOT/'target/release'/filename
    if not binary.is_file():binary=ROOT/'target/debug'/filename
    if not binary.is_file():raise FormatError('Rust core is not built. Run cargo build --workspace.')
    try:
        result=subprocess.run([str(binary),'inspect','-'],input=data,capture_output=True,timeout=30)
    except (OSError,subprocess.TimeoutExpired) as error:
        raise FormatError(f'Could not run the Rust core: {error}') from error
    if result.returncode:raise FormatError(result.stderr.decode('utf-8',errors='replace').strip())
    return json.loads(result.stdout)
