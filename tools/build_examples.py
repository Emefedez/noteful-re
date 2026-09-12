#!/usr/bin/env python3
"""Build standalone HTML/SVG examples from the local corpus."""
import hashlib
import html
import json
from pathlib import Path
from render_note import render

ROOT = Path(__file__).resolve().parents[1]


def main():
    dest = ROOT / 'examples'
    dest.mkdir(exist_ok=True)
    links, manifest = [], []
    css = 'body{font:16px system-ui;background:#e9eeeb;color:#24312e;max-width:1100px;margin:auto;padding:24px}svg{width:100%;height:auto;background:white}article{margin:30px 0}a{color:#235e4b}p{line-height:1.5}'
    for source in sorted((ROOT / 'samples').glob('*.noteful')):
        data = source.read_bytes()
        doc = render(data, source.stem)
        label = html.escape(doc['name'])
        folder = dest / source.stem
        folder.mkdir(exist_ok=True)
        content = [f'<!doctype html><meta charset="utf-8"><title>{label}</title><style>{css}</style><h1>{label}</h1><p>{html.escape(doc["notes"])}</p><p><a href="../index.html">Todos los ejemplos</a></p>']
        for n, page in enumerate(doc['pages'], 1):
            (folder / f'page-{n}.svg').write_text(page['svg'])
            content.append(f'<article><h2>Página {n} · {page["stroke_count"]} trazos</h2><p>{html.escape(" ".join(page["warnings"]))}</p>{page["svg"]}</article>')
        (folder / 'index.html').write_text('\n'.join(content))
        links.append(f'<li><a href="{html.escape(source.stem, quote=True)}/index.html">{label}</a> · {doc["page_count"]} páginas · {doc["stroke_count"]} trazos</li>')
        manifest.append({k: v for k, v in doc.items() if k != 'pages'} | {'sample': source.name, 'sha256': hashlib.sha256(data).hexdigest(), 'pages': [{k: v for k, v in p.items() if k != 'svg'} for p in doc['pages']]})
    (dest / 'index.html').write_text(f'<!doctype html><meta charset="utf-8"><title>Ejemplos Noteful</title><style>{css}</style><h1>Ejemplos Noteful</h1><p>Vistas estáticas listas para abrir sin servidor. Para abrir otros archivos, doble clic en <b>Abrir Noteful.command</b> en la carpeta del proyecto.</p><ul>'+''.join(links)+'</ul><p><a href="../samples/Examen wuolah.pdf">PDF exportado de referencia</a></p>')
    (dest / 'manifest.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2)+'\n')
    print(f'{len(manifest)} ejemplos HTML; {sum(x["page_count"] for x in manifest)} páginas SVG.')


if __name__ == '__main__':
    main()
