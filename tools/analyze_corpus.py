#!/usr/bin/env python3
"""Reproduce corpus comparisons and provisional vector evidence. No dependencies."""
import hashlib
import json
from pathlib import Path
import re
import zlib
import sys
sys.path.insert(0, str(Path(__file__).resolve().parents[1]/"research/python"))
from noteful import parse, semantic_summary
from render_note import render

ROOT = Path(__file__).resolve().parents[1]


def main():
    summaries = []
    for source in sorted((ROOT / "samples").glob("*.noteful")):
        data = source.read_bytes()
        report = parse(data)
        summary = semantic_summary(report)
        target = ROOT / "research/evidence/extracted" / source.stem
        target.mkdir(parents=True, exist_ok=True)
        page = summary["pages"][0]
        w, h = page["size"]
        svg = [f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {w} {h}">',
               '<title>Provisional reconstruction of freehand coordinates; black uniform width</title>']
        strokes = []
        pdf_streams = []
        for block in report["blocks"]:
            for s in block.get("strokes", []):
                coords = " ".join(f"{x:.6f},{y:.6f}" for x, y in s["candidate_points"])
                svg.append(f'<polyline points="{coords}" fill="none" stroke="black" '
                           f'stroke-width="{s["thickness_candidate"]}"/>')
                strokes.append({k: v for k, v in s.items() if k not in ("candidate_points", "uint16_pairs")})
            if block["kind"] == "pdf":
                raw = data[block["offset"]:block["offset"] + block["size"]]
                # Corpus-specific stream extraction; not a general PDF parser.
                for match in re.finditer(rb'stream\r?\n(.*?)\r?\nendstream', raw, re.S):
                    try:
                        content = zlib.decompress(match[1])
                    except zlib.error:
                        continue
                    if content.startswith(b"q "):
                        (target / "pdf-page-content.txt").write_bytes(content)
                        pdf_streams.append({"size": len(content), "sha256": hashlib.sha256(content).hexdigest()})
        svg.append('</svg>')
        if strokes and len(summary["pages"]) == 1:
            (target / "freehand-provisional.svg").write_text("\n".join(svg) + "\n")
        for n, rendered in enumerate(render(data)["pages"], 1):
            (target / f"page-{n}.svg").write_text(rendered["svg"])
        summaries.append({"sample": source.name, "sha256": report["sha256"], "size": len(data),
                          "index_offset": report["index_offset"], "index_size": report["index_size"],
                          "blocks": [{k: b[k] for k in ("id", "offset", "size", "kind", "sha256")}
                                     for b in report["blocks"]],
                          "semantics": summary, "freehand": strokes, "pdf_content_streams": pdf_streams})
    (ROOT / "research/evidence/corpus.json").write_text(json.dumps(summaries, indent=2, ensure_ascii=False) + "\n")
    print(f"Compared {len(summaries)} samples; research/evidence/corpus.json")


if __name__ == "__main__":
    main()
