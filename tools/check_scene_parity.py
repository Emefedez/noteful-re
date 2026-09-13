#!/usr/bin/env python3
"""Compare native SVG primitives against the existing Python renderer.

Flatten groups while retaining inherited transforms/compositing. Compare geometry
and numeric attributes within 2e-5 page units, including ordering and image bytes.
No browser/PDF raster is used as reconstruction input.
"""
import json, math, re, subprocess, sys
from pathlib import Path
import xml.etree.ElementTree as ET
sys.path.insert(0,str(Path(__file__).resolve().parent))
import sys
sys.path.insert(0, str(Path(__file__).resolve().parents[1]/"research/python"))
from render_note import render
ROOT=Path(__file__).resolve().parents[1]
NUMBER=re.compile(r'[-+]?(?:\d+\.?\d*|\.\d+)(?:[eE][-+]?\d+)?')
def normalize_attr(key,value):
    if key in ('href','fill','stroke','id','patternUnits','preserveAspectRatio','stroke-linecap','stroke-linejoin','style'):
        return value
    return (NUMBER.sub('#',value).replace(' ','').replace(',',''),[float(v) for v in NUMBER.findall(value)])
def primitives(svg):
    result=[]
    def visit(node,parents):
        tag=node.tag.rsplit('}',1)[-1]
        attrs={k:normalize_attr(k,v) for k,v in node.attrib.items() if k not in ('data-item','data-background','data-layer') and not (k=='opacity' and float(v)==1.)}
        if tag=='svg': attrs={}
        if tag in ('svg','g'):
            chain=parents+([attrs] if attrs else [])
        else:
            result.append((tag,parents,attrs,node.text or ''));chain=parents
        for child in node:visit(child,chain)
    visit(ET.fromstring(svg),[])
    return result

def compare(a,b,path='root'):
    if isinstance(a,(int,float)) and isinstance(b,(int,float)):
        assert math.isclose(a,b,rel_tol=1e-9,abs_tol=2e-5),(path,a,b)
    elif isinstance(a,(list,tuple)):
        assert len(a)==len(b),(path,len(a),len(b))
        for i,(x,y) in enumerate(zip(a,b)):compare(x,y,f'{path}/{i}')
    elif isinstance(a,dict):
        assert a.keys()==b.keys(),(path,a.keys(),b.keys())
        for k,v in a.items():compare(v,b[k],f'{path}/{k}')
    else: assert a==b,(path,str(a)[:120],str(b)[:120])

def main():
    subprocess.run(['cargo','build','--locked','-p','noteful-cli'],cwd=ROOT,check=True)
    binary=ROOT/'target/debug'/('noteful.exe' if sys.platform=='win32' else 'noteful')
    result=[]
    for source in sorted((ROOT/'samples').glob('*.noteful')):
        native=json.loads(subprocess.check_output([str(binary),'render',str(source)]))
        reference=render(source.read_bytes())
        assert len(native['pages'])==len(reference['pages'])
        counts=[]
        for page,(a,b) in enumerate(zip(native['pages'],reference['pages'])):
            aa=primitives(a['svg']);bb=primitives(b['svg'])
            compare(aa,bb,f'{source.name}/page{page}')
            counts.append(len(aa))
        result.append({'file':source.name,'pages':len(counts),'primitives':counts,'passed':True})
    report={'scope':'Ordered SVG primitives, inherited transforms/compositing, image bytes; no pixel equivalence claim','absolute_tolerance':2e-5,'samples':result}
    (ROOT/'research/evidence/rust-scene-parity.json').write_text(json.dumps(report,indent=2,ensure_ascii=False)+'\n')
    print('Native scene parity:',len(result),'notes passed')
if __name__=='__main__':main()
