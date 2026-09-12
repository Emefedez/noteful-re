#!/usr/bin/env python3
"""Compare candidate coordinates to JPEG ink. Optional dependency: Pillow."""
import json
import math
from pathlib import Path
from PIL import Image

ROOT = Path(__file__).resolve().parents[1]


def main():
    baseline = Image.open(next((ROOT / "evidence/extracted/nota_vacia").glob("*.jpg"))).convert("RGB")
    results = []
    for name in ("nota_1linea", "nota_2lineas", "nota_lineagruesa"):
        folder = ROOT / "evidence/extracted" / name
        report = json.loads((folder / "manifest.json").read_text())
        im = Image.open(next(folder.glob("*.jpg"))).convert("RGB")
        w, h = report["semantic_summary"]["pages"][0]["size"]
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
    (ROOT / "evidence/geometry-validation.json").write_text(json.dumps(results, indent=2) + "\n")
    print("Geometry evidence saved for", len(results), "strokes")


if __name__ == "__main__":
    main()
