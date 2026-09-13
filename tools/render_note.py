"""Local SVG preview from decoded content; no Noteful/PDF reference pixels used for ink."""
import base64
import math
from noteful import FormatError, parse, semantic_summary, values
from rich_text import decode_rich_text, text_svg

HIGHLIGHTER_OPACITY = .5  # /ca and /CA in the supplied Noteful PDF export.


def num(v):
    return f'{v:.5f}'


def color(rgba):
    return 'rgb('+','.join(str(round(max(0,min(1,v))*255)) for v in rgba[:3])+')'


def composite(element, opacity=1., tool=0):
    """Use the same Multiply/50% composition for freehand and shape highlighters."""
    if tool not in (0, 1):
        raise FormatError(f'Unsupported drawing tool {tool}')
    if not math.isfinite(opacity) or not 0 <= opacity <= 1:
        raise FormatError('Invalid object opacity')
    opacity *= HIGHLIGHTER_OPACITY if tool == 1 else 1
    mode = ' style="mix-blend-mode:multiply"' if tool == 1 else ''
    return f'<g opacity="{num(opacity)}"{mode}>{element}</g>'


def path_geometry(coords, commands):
    """Observed M/L/C/Z commands; preserve exact control points and reject leftovers."""
    arities = {0: ('M', 2), 1: ('L', 2), 3: ('C', 6), 4: ('Z', 0)}
    cursor, result = 0, []
    for command in commands:
        if command not in arities:
            raise FormatError(f'Unsupported shape path command {command}')
        letter, count = arities[command]
        if cursor + count > len(coords):
            raise FormatError('Truncated shape coordinates')
        result.append(letter + ' '.join(num(v) for v in coords[cursor:cursor+count]))
        cursor += count
    if cursor != len(coords):
        raise FormatError('Unconsumed shape coordinates')
    return ' '.join(result)


def variable_ink(points, radii, rgba):
    """Union of sample discs and their external tangents; composited once by caller."""
    if len(points) != len(radii) or any(not math.isfinite(r) or r < 0 for r in radii):
        raise FormatError('Invalid per-point radii')
    parts = []
    for (x,y), r in zip(points,radii):
        parts.append(f'<circle cx="{num(x)}" cy="{num(y)}" r="{num(r)}"/>')
    for (x0,y0),(x1,y1),r0,r1 in zip(points,points[1:],radii,radii[1:]):
        dx,dy=x1-x0,y1-y0
        distance=math.hypot(dx,dy)
        if distance <= abs(r1-r0) or distance < 1e-9:
            continue  # One sample disc contains the other.
        ux,uy=dx/distance,dy/distance;k=(r0-r1)/distance;q=math.sqrt(1-k*k)
        ax,ay=k*ux-q*uy,k*uy+q*ux
        bx,by=k*ux+q*uy,k*uy-q*ux
        quad=[(x0+r0*ax,y0+r0*ay),(x1+r1*ax,y1+r1*ay),
              (x1+r1*bx,y1+r1*by),(x0+r0*bx,y0+r0*by)]
        parts.append('<polygon points="'+' '.join(f'{num(x)},{num(y)}' for x,y in quad)+'"/>')
    return f'<g fill="{color(rgba)}">'+''.join(parts)+'</g>'


def shape_element(obj, payload):
    """Draw shapes in native coordinates; apply placement scaling to the whole shape."""
    sw, sh = obj['size']
    _, _, ow, oh, _ = obj['transform_raw']
    st = values(payload.get(7, []))
    stroke = values(st.get(7, [])).get(0, [0, 0, 0, 1])
    width = st.get(2, 0)
    fill_data = values(payload.get(5, []))
    fill = values(fill_data.get(1, [])).get(0)
    attrs = f'stroke="{color(stroke)}" stroke-opacity="{num(stroke[3])}" stroke-width="{num(width)}" stroke-linecap="round" stroke-linejoin="round"'
    attrs += f' fill="{color(fill)}" fill-opacity="{num(fill[3])}"' if fill else ' fill="none"'
    if 13 in payload:
        geometry = values(payload[13])
        path = path_geometry(geometry.get(1, []), geometry.get(2, []))
        element = f'<path d="{path}" {attrs}/>'
    elif obj['type_raw'] == 6:
        element = f'<ellipse cx="{num(sw/2)}" cy="{num(sh/2)}" rx="{num(sw/2)}" ry="{num(sh/2)}" {attrs}/>'
    elif obj['type_raw'] == 3:
        radius = payload.get(20, 0)
        element = f'<rect width="{num(sw)}" height="{num(sh)}" rx="{num(radius)}" {attrs}/>'
    else:
        return None
    # Degenerate straight lines have a zero native height/width in valid notes.
    sx = ow/sw if abs(sw) > 1e-9 else 1
    sy = oh/sh if abs(sh) > 1e-9 else 1
    return f'<g transform="scale({num(sx)} {num(sy)})">{element}</g>'


def render(data, name='Nota', parser=parse):
    report = parser(data)
    summary = semantic_summary(report)
    blocks = {b['id']: b for b in report['blocks']}
    pages = []
    for page in summary['pages']:
        w,h = page['size']
        parts = [f'<svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" viewBox="0 0 {w} {h}" width="{w}" height="{h}">']
        paper = page.get('paper') or {}
        parts.append(f'<rect width="100%" height="100%" fill="#{paper.get("pc",16777215):06x}"/>')
        warnings=[]
        if paper.get('lt') in (1,2):
            gap=paper.get('lh',24)*11/6;linew=paper.get('lw',.5)*11/6
            path=f'M 0 {gap} L {gap} {gap}'
            if paper['lt']==2:path+=f' M {gap} 0 L {gap} {gap}'
            parts.append(f'<defs><pattern id="paper" width="{gap}" height="{gap}" patternUnits="userSpaceOnUse"><path d="{path}" fill="none" stroke="#9a9888" stroke-width="{linew}"/></pattern></defs><rect width="100%" height="100%" fill="url(#paper)"/>')
        if not paper:
            warnings.append('Fondo PDF genérico aún sin reconstruir; descarga recurso original.')
        editable=blocks.get(page.get('stroke_object_set_id'),{})
        strokes=editable.get('strokes',[])
        if editable.get('stroke_decode_error'):warnings.append(editable['stroke_decode_error'])
        objects=[o for o in summary['objects'] if o['stroke_object_set_id']==page.get('stroke_object_set_id')]
        elements=[]
        for s in strokes:
            pts=s['candidate_points'];style=s['style'];rgba=style['rgba'];tool=style['tool_raw']
            if not pts:continue
            # Scalar radius for uniform strokes; channel 3 supplies radius per sample.
            width=s['thickness_candidate']*2
            attrs=f'fill="none" stroke="{color(rgba)}" stroke-width="{num(width)}" stroke-linecap="round" stroke-linejoin="round"'
            if s.get('radii'):
                el=variable_ink(pts,s['radii'],rgba)
            elif len(pts)==1:
                el=f'<circle cx="{num(pts[0][0])}" cy="{num(pts[0][1])}" r="{num(width/2)}" fill="{color(rgba)}"/>'
            else:
                el='<polyline points="'+' '.join(','.join(num(v) for v in xy) for xy in pts)+f'" {attrs}/>'
            el=composite(el, rgba[3], tool)
            elements.append((s['z_order_raw'],el))
        unsupported=[]
        for o in objects:
            x,y,ow,oh,angle=o['transform_raw'];sw,sh=o['size'];payload=values(o['payload_fields'])
            transform=f'translate({num(x)} {num(y)}) rotate({num(math.degrees(angle))}) translate({num(-ow/2)} {num(-oh/2)})'
            el=None
            if o['kind_in_samples']=='image' and o['asset_id'] in blocks:
                b=blocks[o['asset_id']];raw=data[b['offset']:b['offset']+b['size']]
                mime={'jpeg':'image/jpeg','png':'image/png'}.get(b['kind'])
                if mime:el=f'<image width="{num(ow)}" height="{num(oh)}" preserveAspectRatio="none" href="data:{mime};base64,{base64.b64encode(raw).decode()}"/>'
            elif o['type_raw'] == 2:
                text = decode_rich_text(values(payload.get(4, [])))
                warnings.extend(text['warnings'])
                sx = ow/sw if abs(sw)>1e-9 else 1
                sy = oh/sh if abs(sh)>1e-9 else 1
                el = f'<g transform="scale({num(sx)} {num(sy)})">{text_svg(text,sw)}</g>'
            elif o['type_raw'] in (3,6,12,20,21):
                try:
                    el=shape_element(o,payload)
                except FormatError as error:
                    warnings.append(str(error))
            if el is None:unsupported.append(o['type_raw'])
            else:
                el=composite(f'<g transform="{transform}">{el}</g>',o['opacity'],o['tool_raw'])
                elements.append((o.get('z_order_raw',0),el))
        if unsupported:warnings.append(f'{len(unsupported)} objetos aún sin representación (tipos {sorted(set(unsupported))}).')
        parts.extend(el for _,el in sorted(elements,key=lambda pair:pair[0]))
        parts.append('</svg>')
        pages.append({'id':page['id'],'svg':''.join(parts),'stroke_count':len(strokes),'object_count':len(objects),'warnings':warnings,'variable_count':sum(bool(s['flags']&1) for s in strokes),'auxiliary_count':sum(bool(s['flags']&2) for s in strokes)})
    return {'name':summary.get('title') or name,'size':len(data),'page_count':len(pages),'stroke_count':sum(p['stroke_count'] for p in pages),'object_count':len(summary['objects']),'pages':pages,'notes':'Subrayador: Multiply al 50%. Grosor variable recuperado. Interpolación de tinta aproximada; canales auxiliares y borrado pendientes. Figuras no compatibles se indican por página.'}
