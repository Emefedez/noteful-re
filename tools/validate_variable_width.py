#!/usr/bin/env python3
"""Read-only comparison of decoded third channel with initial circular caps in PDF.

Development dependencies: pypdf, numpy. PDF geometry is validation only.
"""
import json
from pathlib import Path
import numpy as np
from pypdf import PdfReader
import sys
sys.path.insert(0, str(Path(__file__).resolve().parents[1]/"research/python"))
from noteful import parse, semantic_summary

ROOT = Path(__file__).resolve().parents[1]
REPORTS = ROOT / "work/reports"
REPORTS.mkdir(parents=True, exist_ok=True)


def outlines(page):
    """Collect final filled contours; sufficient for standalone caps, not whole paths."""
    matrix = np.eye(3)
    stack, path, paths = [], [], []
    def transform(x, y):
        return (matrix @ np.array([float(x), float(y), 1]))[:2]
    for args, op in page.get_contents().operations:
        if op == b'q':
            stack.append(matrix.copy())
        elif op == b'Q':
            matrix = stack.pop()
        elif op == b'cm':
            a,b,c,d,e,f = map(float,args)
            matrix = matrix @ np.array([[a,c,e],[b,d,f],[0,0,1]])
        elif op == b'm':
            path = [transform(*args)]
        elif op == b'l' and path:
            path.append(transform(*args))
        elif op == b'c' and path:
            p0 = path[-1];p1=transform(*args[:2]);p2=transform(*args[2:4]);p3=transform(*args[4:])
            for t in np.linspace(0, 1, 17)[1:]:
                path.append((1-t)**3*p0+3*(1-t)**2*t*p1+3*(1-t)*t*t*p2+t**3*p3)
        elif op == b'h' and path:
            path.append(path[0])
        elif op in (b'f', b'f*'):
            if len(path)>3:
                p = np.array(path);p[:,1] = float(page.mediabox.height)-p[:,1]
                paths.append(p * (11/6))
            path=[]
        elif op in (b'S',b'n',b're'):
            path=[]
    return paths


def main():
    report=parse((ROOT/'samples/Examen wuolah.noteful').read_bytes())
    summary=semantic_summary(report);blocks={b['id']:b for b in report['blocks']}
    pdf=PdfReader(ROOT/'samples/Examen wuolah.pdf');results=[]
    for pn,page in enumerate(summary['pages']):
        paths=outlines(pdf.pages[pn])
        boxes=np.array([[*p.min(axis=0),*p.max(axis=0)] for p in paths])
        centers=(boxes[:,:2]+boxes[:,2:])/2
        radii=(boxes[:,2:]-boxes[:,:2])/2
        for stroke in blocks[page['stroke_object_set_id']]['strokes']:
            if not stroke['flags']&1:continue
            xy=np.array(stroke['candidate_points']);v=np.array(stroke['radii'])
            # Initial discs are separate filled paths in this export. Match center
            # and circularity only, independently of the radius channel under test.
            score=np.linalg.norm(centers-xy[0],axis=1)+np.abs(radii[:,0]-radii[:,1])
            idx=int(np.argmin(score))
            results.append({'page':pn+1,'stroke_id':stroke['id_raw'],'points':len(xy),
                            'outline_index':idx,'channel_first_radius':float(v[0]),
                            'pdf_cap_radii':radii[idx].tolist(),
                            'center_error':float(np.linalg.norm(centers[idx]-xy[0])),
                            'radius_error':float(np.max(np.abs(radii[idx]-v[0])))})
    target=REPORTS/'variable-width-validation.json'
    target.write_text(json.dumps({'method':'Initial circular caps in PDF, matched by center and circularity. Radius tested independently. Geometry sampled at 16 intervals; coordinates scaled 11/6. Corpus validation, not runtime tracing.','strokes':results},indent=2)+'\n')
    print('strokes:',len(results))
    print('max center error:',max(s['center_error'] for s in results))
    print('max radius error:',max(s['radius_error'] for s in results))
    assert len(results)==23 and all(s['center_error']<.001 and s['radius_error']<.001 for s in results)



if __name__=='__main__':main()
