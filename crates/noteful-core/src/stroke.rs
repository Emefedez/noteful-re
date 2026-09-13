use crate::{hex, Cursor, Error, Result, MAX_ITEMS};
use serde_json::{json, Value};

#[derive(Debug, Clone, PartialEq)]
pub struct Style {
    pub rgba: [f64; 4],
    pub tool: u16,
    pub extra: [u8; 8],
}
impl Default for Style {
    fn default() -> Self {
        Self {
            rgba: [0., 0., 0., 1.],
            tool: 0,
            extra: [0; 8],
        }
    }
}
#[derive(Debug, Clone, PartialEq)]
pub struct Stroke {
    pub offset: usize,
    pub size: usize,
    pub header: [u8; 38],
    pub flags: u16,
    pub id: u64,
    pub z_order: u64,
    pub layer: u32,
    pub radius: f64,
    pub unknown: u32,
    pub points: Vec<[f64; 2]>,
    pub radii: Vec<f64>,
    pub bounds: Vec<f64>,
    pub quantized: Vec<[u16; 2]>,
    pub auxiliary: Vec<u8>,
    pub style: Style,
}
impl Stroke {
    pub fn to_json(&self) -> Value {
        json!({"offset_in_blob":self.offset,"size":self.size,"record_prefix":"f101",
            "opaque_header_hex":hex(&self.header),"id_raw":format!("{:016x}",self.id),
            "flags":self.flags,"z_order_raw":self.z_order,"layer_raw":self.layer,
            "thickness_candidate":self.radius,"unknown_0x30":self.unknown,
            "point_count":self.points.len(),"encoding":if self.points.len()<=4 {"float32"} else {"quantized_uint16"},
            "float32_0x38_0x3c_0x40_0x44":&self.bounds[..self.bounds.len().min(4)],
            "uint16_pairs":self.quantized,"candidate_points":self.points,"radii":self.radii,
            "pressure_candidate":self.radii,"auxiliary_hex":hex(&self.auxiliary),
            "style":{"rgba":self.style.rgba,"tool_raw":self.style.tool,"extra_hex":hex(&self.style.extra)}})
    }
}
pub fn decode_strokes(data: &[u8]) -> Result<Vec<Stroke>> {
    let mut r = Cursor::new(data, 0);
    let mut style = Style::default();
    let mut out = Vec::new();
    let mut budget = MAX_ITEMS;
    while r.remaining() > 0 {
        let offset = r.pos;
        let cmd = r.uint(2)?;
        if cmd == 0xf102 {
            let rgba = [r.float(8)?, r.float(8)?, r.float(8)?, r.float(8)?];
            if rgba.iter().any(|x| !(0.0..=1.0).contains(x)) {
                return Err(Error::new(offset, "Invalid RGBA"));
            }
            let tool = r.uint(2)? as u16;
            let mut extra = [0; 8];
            extra.copy_from_slice(r.take(8)?);
            style = Style { rgba, tool, extra };
            continue;
        }
        if cmd != 0xf101 {
            return Err(Error::new(offset, "Unsupported stroke command"));
        }
        let mut header = [0; 38];
        header.copy_from_slice(r.take(38)?);
        let mut h = Cursor::new(&header, offset + 2);
        let id = h.uint(8)?;
        let flags = h.uint(2)? as u16;
        if flags & !3 != 0 {
            return Err(Error::new(offset, "Unsupported stroke flags"));
        }
        h.take(16)?;
        let z_order = h.uint(8)?;
        let layer = h.uint(4)? as u32;
        let radius = r.float(8)?;
        let unknown = r.uint(4)? as u32;
        let count = r.uint(4)? as usize;
        let dim = if flags & 1 != 0 { 3 } else { 2 };
        if count > budget || count > data.len() / 4 {
            return Err(Error::new(r.at(), "Stroke point budget exceeded"));
        }
        budget -= count;
        let auxiliary = if flags & 2 != 0 {
            r.take(count * 8)?.to_vec()
        } else {
            Vec::new()
        };
        let mut bounds = Vec::new();
        let mut points = Vec::new();
        let mut radii = Vec::new();
        let mut quantized = Vec::new();
        if count > 4 {
            for _ in 0..dim * 2 {
                bounds.push(r.float(4)?);
            }
        }
        for _ in 0..count {
            let mut p = [0.; 3];
            let mut q = [0u16; 3];
            for j in 0..dim {
                p[j] = if count <= 4 {
                    r.float(4)?
                } else {
                    q[j] = r.uint(2)? as u16;
                    bounds[j * 2] + f64::from(q[j]) / 65535. * bounds[j * 2 + 1]
                };
                if !p[j].is_finite() {
                    return Err(Error::new(r.at(), "Non-finite coordinate"));
                }
            }
            points.push([p[0], p[1]]);
            if dim == 3 {
                radii.push(p[2]);
            }
            if count > 4 {
                quantized.push([q[0], q[1]]);
            }
        }
        out.push(Stroke {
            offset,
            size: r.pos - offset,
            header,
            flags,
            id,
            z_order,
            layer,
            radius,
            unknown,
            points,
            radii,
            bounds,
            quantized,
            auxiliary,
            style: style.clone(),
        });
    }
    Ok(out)
}
