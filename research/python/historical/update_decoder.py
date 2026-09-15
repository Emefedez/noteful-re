"""Historical one-off migration. Expects obsolete tools/noteful.py; not a current maintenance command."""
from pathlib import Path
p=Path('tools/noteful.py');s=p.read_text();a=s.index('def decode_sample_strokes(');b=s.index('\n\ndef parse(',a)
s=s[:a]+'''def decode_sample_strokes(blob):
    """Decode observed F1 commands, preserving style and unknown auxiliary channels."""
    r = Reader(blob)
    strokes = []
    style = {"rgba": [0., 0., 0., 1.], "tool_raw": 0, "extra_hex": "00" * 8}
    while r.pos < len(blob):
        start = r.pos
        command = r.take(2)
        if command == b"\\xf1\\x02":
            rgba = r.number("dddd")
            tool = r.number("H")
            extra = r.take(8)
            if not all(math.isfinite(v) and 0 <= v <= 1 for v in rgba):
                raise FormatError(f"Invalid RGBA at +0x{start:x}")
            style = {"rgba": rgba, "tool_raw": tool, "extra_hex": extra.hex()}
            continue
        if command != b"\\xf1\\x01":
            raise FormatError(f"Unsupported stroke command {command.hex()} at +0x{start:x}")
        prefix = r.take(38)
        flags = struct.unpack_from(">H", prefix, 8)[0]
        if flags & ~3:
            raise FormatError(f"Unsupported stroke flags 0x{flags:x} at +0x{start:x}")
        thickness = r.number("d")
        unknown_30 = r.number("I")
        count = r.number("I")
        dim = 3 if flags & 1 else 2
        if count > len(blob) // 4:
            raise FormatError("Stroke coordinate count exceeds buffer")
        aux = r.take(count * 8) if flags & 2 else b""
        pairs, bounds = [], []
        if count <= 4:
            raw = [r.number("f" * dim) for _ in range(count)]
            encoding = "float32"
        else:
            bounds = r.number("f" * (dim * 2))
            pairs = [r.number("H" * dim) for _ in range(count)]
            raw = [[bounds[j * 2] + v / 65535 * bounds[j * 2 + 1]
                    for j, v in enumerate(point)] for point in pairs]
            encoding = "quantized_uint16"
        if not math.isfinite(thickness) or any(not math.isfinite(v) for point in raw for v in point):
            raise FormatError(f"Non-finite stroke values at +0x{start:x}")
        strokes.append({
            "offset_in_blob": start, "size": r.pos - start,
            "record_prefix": "f101", "opaque_header_hex": prefix.hex(),
            "id_raw": prefix[:8].hex(), "flags": flags,
            "z_order_raw": struct.unpack_from(">Q", prefix, 26)[0],
            "layer_raw": struct.unpack_from(">I", prefix, 34)[0],
            "thickness_candidate": thickness, "unknown_0x30": unknown_30,
            "point_count": count, "encoding": encoding,
            "float32_0x38_0x3c_0x40_0x44": bounds[:4],
            "uint16_pairs": [point[:2] for point in pairs],
            "candidate_points": [point[:2] for point in raw],
            "pressure_candidate": [point[2] for point in raw] if dim == 3 else [],
            "auxiliary_hex": aux.hex(), "style": dict(style),
            "geometry_status": "Decoded observed layout; rendering remains approximate",
        })
    return strokes
''' + s[b:]
s=s.replace('"asset_id": payload.get(10),','"asset_id": payload.get(10),\n                    "stroke_object_set_id": block["id"], "payload_fields": ov[6],\n                    "z_order_raw": ov.get(5, 0), "layer_raw": ov.get(4, 0),')
s=s.replace('"paper": json.loads(background[6]),','"paper": json.loads(background[6]) if background.get(6) else None,\n                    "background_page_raw": background.get(7, 0),\n                    "order_key": page.get(5, ""),')
s=s.replace('    return result\n\n\ndef extract(', '    result["pages"].sort(key=lambda p: p.get("order_key", ""))\n    return result\n\n\ndef extract(')
p.write_text(s)
