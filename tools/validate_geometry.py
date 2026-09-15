#!/usr/bin/env python3
"""Compare candidate coordinates to JPEG ink. Optional dependency: Pillow."""
import json
import math
import io
import sys
from pathlib import Path
from PIL import Image
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "research/python"))
from noteful import parse, semantic_summary

ROOT = Path(__file__).resolve().parents[1]


def sample(name):
    data = (ROOT / "samples" / (name + ".noteful")).read_bytes()
    report = parse(data)
    block = next(b for b in report["blocks"] if b["kind"] == "jpeg")
    image = Image.open(io.BytesIO(data[block["offset"]:block["offset"] + block["size"]])).convert("RGB")
    return report, image


def main():
    _, baseline = sample("nota_vacia")
    results = []
    for name in ("nota_1linea", "nota_2lineas", "nota_lineagruesa"):
        report, im = sample(name)
        w, h = semantic_summary(report)["pages"][0]["size"]
        sx, sy = im.width / w, im.height / h
        for block in report["blocks"]:
            for stroke in block.get("strokes", []):
                pts = stroke["candidate_points"]
                x0 = max(0, int(min(x for x, y in pts) * sx) - 4)
                x1 = min(im.width, int(max(x for x, y in pts) * sx) + 5)
                y0 = max(0, int(min(y for x, y in pts) * sy) - 4)
                y1 = min(im.height, int(max(y for x, y in pts) * sy) + 5)
                ink = [(x, y) for x in range(x0, x1) for y in range(y0, y1)
                       if sum(baseline.getpixel((x, y))) - sum(im.getpixel((x, y))) > 75]
                if not ink:
                    raise ValueError(f"No ink found for {name}")
                distances = [min(math.hypot(x * sx - ix, y * sy - iy) for ix, iy in ink)
                             for x, y in pts]
                results.append({
                    "sample": name, "stroke_offset": stroke["offset_in_blob"],
                    "jpeg_size": im.size, "scale": [sx, sy],
                    "threshold_rgb_sum_darkening": 75, "candidate_bbox_pixels": [x0, y0, x1, y1],
                    "ink_pixels": len(ink),
                    "mean_nearest_ink_pixel_distance": sum(distances) / len(distances),
                    "max_nearest_ink_pixel_distance": max(distances),
                    "note": "Corroborates position/shape only; does not verify engine smoothing, thickness or general codec.",
                })
    (ROOT / "work/reports").mkdir(parents=True, exist_ok=True)
    (ROOT / "work/reports/geometry-validation.json").write_text(json.dumps(results, indent=2) + "\n")
    print("Geometry evidence saved for", len(results), "strokes")


if __name__ == "__main__":
    main()
