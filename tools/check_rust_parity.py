#!/usr/bin/env python3
"""Compare every Rust diagnostic field against the Python reference decoder."""
import json
import math
from pathlib import Path
import subprocess
import sys
from noteful import parse, semantic_summary
from render_note import render

ROOT=Path(__file__).resolve().parents[1]
BIN=ROOT/'target/debug'/('noteful.exe' if sys.platform=='win32' else 'noteful')

def rust_parse(data):
    result=subprocess.run([str(BIN),'inspect','-'],input=data,capture_output=True,check=True,timeout=30)
    return json.loads(result.stdout)

def compare(actual,expected,path='root'):
    if isinstance(actual,dict):
        assert isinstance(expected,dict),path
        for k,v in actual.items():
            assert k in expected,(path,k)
            compare(v,expected[k],path+'.'+k)
    elif isinstance(actual,list):
        assert len(actual)==len(expected),(path,len(actual),len(expected))
        for i,(a,e) in enumerate(zip(actual,expected)):compare(a,e,f'{path}[{i}]')
    elif isinstance(actual,float):
        assert math.isclose(actual,expected,rel_tol=1e-13,abs_tol=1e-10),(path,actual,expected)
    else:
        assert actual==expected,(path,actual,expected)

def main():
    subprocess.run(['cargo','build','--locked','--workspace'],cwd=ROOT,check=True)
    rows=[]
    for file in sorted((ROOT/'samples').glob('*.noteful')):
        data=file.read_bytes();native=rust_parse(data);reference=parse(data)
        compare(native,reference)
        assert semantic_summary(native)==semantic_summary(reference),file.name
        # Use both parsers through the same renderer to catch lost object/style data.
        a=render(data,parser=lambda _:native);b=render(data)
        assert a==b,file.name
        subprocess.run([str(BIN),'verify',str(file)],capture_output=True,check=True,timeout=30)
        rows.append({'sample':file.name,'sha256':reference['sha256'],'blocks':len(native['blocks']),
                     'strokes':a['stroke_count'],'pages':a['page_count'],'objects':a['object_count'],
                     'all_native_fields_match':True,'semantic_equality':True,'svg_byte_equality':True,'binary_round_trip':True})
    output={'scope':'Rust decoder/field encoder vs Python reference; existing Python renderer; host execution only',
            'float_tolerance':{'relative':1e-13,'absolute':1e-10},'samples':rows}
    (ROOT/'evidence/rust-parity.json').write_text(json.dumps(output,indent=2,ensure_ascii=False)+'\n')
    print(f'Parity passed: {len(rows)} notes; all decoded fields, semantics, SVG and binary round-trip.')

if __name__=='__main__':main()
