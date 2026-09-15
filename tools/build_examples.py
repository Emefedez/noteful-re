#!/usr/bin/env python3
"""Build standalone HTML/SVG examples from the local corpus."""
import hashlib
import html
import json
from pathlib import Path
import sys
sys.path.insert(0, str(Path(__file__).resolve().parents[1]/"research/python"))
from render_note import render

ROOT = Path(__file__).resolve().parents[1]


def main():
    dest = ROOT / 'work/examples'
    dest.mkdir(parents=True,exist_ok=True)
    links, manifest = [], []
    css = 'body{font:16px system-ui;background:#e9eeeb;color:#24312e;max-width:1100px;margin:auto;padding:24px}svg{width:100%;height:auto;background:white}article{margin:30px 0}a{color:#235e4b}p{line-height:1.5}'
    for source in sorted((ROOT / 'samples').glob('*.noteful')):
        data = source.read_bytes()
        doc = render(data, source.stem)
        label = html.escape(doc['name'])
        folder = dest / source.stem
        folder.mkdir(exist_ok=True)
        content = [f'<!doctype html><meta charset="utf-8"><title>{label}</title><style>{css}</style><h1>{label}</h1><p>{html.escape(doc["notes"])}</p><p><a href="../index.html">All examples</a></p>']
        for n, page in enumerate(doc['pages'], 1):
            (folder / f'page-{n}.svg').write_text(page['svg'])
            content.append(f'<article><h2>Page {n} · {page["stroke_count"]} strokes</h2><p>{html.escape(" ".join(page["warnings"]))}</p>{page["svg"]}</article>')
        (folder / 'index.html').write_text('\n'.join(content))
        links.append(f'<li><a href="{html.escape(source.stem, quote=True)}/index.html">{label}</a> · {doc["page_count"]} pages · {doc["stroke_count"]} strokes</li>')
        manifest.append({k: v for k, v in doc.items() if k != 'pages'} | {'sample': source.name, 'sha256': hashlib.sha256(data).hexdigest(), 'pages': [{k: v for k, v in p.items() if k != 'svg'} for p in doc['pages']]})
    (dest / 'index.html').write_text(f'<!doctype html><meta charset="utf-8"><title>Noteful research previews</title><style>{css}</style><h1>Noteful research previews</h1><p>Optional Python previews; paper reconstruction is approximate. Use the product reader for actual embedded PDF backgrounds.</p><ul>'+''.join(links)+'</ul><p><a href="../../samples/Examen wuolah.pdf">Independent exported PDF reference</a></p>')
    (dest / 'manifest.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2)+'\n')
    print(f'{len(manifest)} HTML examples; {sum(x["page_count"] for x in manifest)} pages SVG.')


if __name__ == '__main__':
    main()
