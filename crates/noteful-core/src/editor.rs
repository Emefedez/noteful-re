//! Non-destructive edits over an immutable imported archive.
//! `.nfedit` is our project format, not an interoperable Noteful export.
use crate::{scene::line_svg, Error, Result, Scene, MAX_FILE_BYTES};
use base64::{engine::general_purpose::STANDARD, Engine};
use serde::{Deserialize, Serialize};
use serde_json::{json, Value};
use std::collections::HashSet;

#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Line {
    pub points: Vec<[f64; 2]>,
    pub width: f64,
    pub rgba: [f64; 4],
}
#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(tag = "kind", deny_unknown_fields)]
enum Edit {
    Add { page: usize, line: Line },
    Erase { page: usize, ids: Vec<String> },
}
#[derive(Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
struct Project {
    format: String,
    version: u32,
    source_base64: String,
    history: Vec<Edit>,
    cursor: usize,
}
pub struct Editor {
    source: Vec<u8>,
    pub scene: Scene,
    history: Vec<Edit>,
    cursor: usize,
}

fn points_valid(points: &[[f64; 2]]) -> bool {
    !points.is_empty()
        && points.len() <= 8192
        && points
            .iter()
            .flatten()
            .all(|v| v.is_finite() && v.abs() <= 1e6)
}
fn point_distance(p: [f64; 2], a: [f64; 2], b: [f64; 2]) -> f64 {
    let d = [b[0] - a[0], b[1] - a[1]];
    let len = d[0] * d[0] + d[1] * d[1];
    let t = if len > 0. {
        ((p[0] - a[0]) * d[0] + (p[1] - a[1]) * d[1]) / len
    } else {
        0.
    };
    (p[0] - a[0] - t.clamp(0., 1.) * d[0]).hypot(p[1] - a[1] - t.clamp(0., 1.) * d[1])
}
fn cross(a: [f64; 2], b: [f64; 2], c: [f64; 2]) -> f64 {
    (b[0] - a[0]) * (c[1] - a[1]) - (b[1] - a[1]) * (c[0] - a[0])
}
fn segments_hit(a: [f64; 2], b: [f64; 2], c: [f64; 2], d: [f64; 2], radius: f64) -> bool {
    // Reject separated bounding boxes before the more expensive distance tests.
    if (0..2).any(|i| {
        a[i].max(b[i]) + radius < c[i].min(d[i]) || c[i].max(d[i]) + radius < a[i].min(b[i])
    }) {
        return false;
    }
    let crosses = cross(a, b, c) * cross(a, b, d) < 0. && cross(c, d, a) * cross(c, d, b) < 0.;
    crosses
        || [
            point_distance(a, c, d),
            point_distance(b, c, d),
            point_distance(c, a, b),
            point_distance(d, a, b),
        ]
        .iter()
        .any(|v| *v <= radius)
}
fn hits(path: &[[f64; 2]], ink: &[[f64; 2]], radius: f64) -> bool {
    for (i, a) in path.iter().enumerate() {
        let b = path.get(i + 1).unwrap_or(a);
        for (j, c) in ink.iter().enumerate() {
            let d = ink.get(j + 1).unwrap_or(c);
            if segments_hit(*a, *b, *c, *d, radius) {
                return true;
            }
        }
    }
    false
}
impl Editor {
    pub fn open(source: &[u8]) -> Result<Self> {
        let scene = Scene::parse(source)?;
        Ok(Self {
            source: source.to_vec(),
            scene,
            history: Vec::new(),
            cursor: 0,
        })
    }
    fn page(&self, page: usize) -> Result<&crate::Page> {
        self.scene
            .pages
            .get(page)
            .ok_or_else(|| Error::new(0, "Page outside document"))
    }
    fn deleted(&self, page: usize) -> HashSet<&str> {
        self.history[..self.cursor]
            .iter()
            .filter_map(|e| match e {
                Edit::Erase { page: p, ids } if *p == page => Some(ids.iter().map(String::as_str)),
                _ => None,
            })
            .flatten()
            .collect()
    }
    fn additions(&self, page: usize) -> impl Iterator<Item = (String, &Line)> {
        self.history[..self.cursor]
            .iter()
            .enumerate()
            .filter_map(move |(i, e)| match e {
                Edit::Add { page: p, line } if *p == page => Some((format!("new:{i}"), line)),
                _ => None,
            })
    }
    fn commit(&mut self, edit: Edit) -> Result<()> {
        let points: usize = self.history[..self.cursor]
            .iter()
            .filter_map(|e| match e {
                Edit::Add { line, .. } => Some(line.points.len()),
                _ => None,
            })
            .sum();
        let added = match &edit {
            Edit::Add { line, .. } => line.points.len(),
            _ => 0,
        };
        if self.cursor >= 10_000 || points + added > 1_000_000 {
            return Err(Error::new(0, "Edit budget exceeded"));
        }
        self.history.truncate(self.cursor);
        self.history.push(edit);
        self.cursor += 1;
        Ok(())
    }
    pub fn add_line(&mut self, page: usize, line: Line) -> Result<()> {
        self.page(page)?;
        if !points_valid(&line.points)
            || !line.width.is_finite()
            || !(0.1..=100.).contains(&line.width)
            || line
                .rgba
                .iter()
                .any(|v| !v.is_finite() || !(0.0..=1.0).contains(v))
        {
            return Err(Error::new(0, "Invalid fixed-width line"));
        }
        self.commit(Edit::Add { page, line })
    }
    /// Sweep a round eraser; remove each touched whole stroke in one undo action.
    /// Imported images and filled shapes are not eraser targets.
    pub fn erase_path(&mut self, page: usize, path: &[[f64; 2]], radius: f64) -> Result<usize> {
        let p = self.page(page)?;
        if !points_valid(path) || !radius.is_finite() || !(0.1..=100.).contains(&radius) {
            return Err(Error::new(0, "Invalid eraser path"));
        }
        let deleted = self.deleted(page);
        let mut ids = Vec::new();
        for item in &p.items {
            if !deleted.contains(item.id.as_str()) && hits(path, &item.hit, radius + item.radius) {
                ids.push(item.id.clone());
            }
        }
        for (id, line) in self.additions(page) {
            if !deleted.contains(id.as_str()) && hits(path, &line.points, radius + line.width / 2.)
            {
                ids.push(id);
            }
        }
        let count = ids.len();
        if count > 0 {
            self.commit(Edit::Erase { page, ids })?;
        }
        Ok(count)
    }
    pub fn undo(&mut self) {
        self.cursor = self.cursor.saturating_sub(1);
    }
    pub fn redo(&mut self) {
        self.cursor = (self.cursor + 1).min(self.history.len());
    }
    pub fn view(&self, page: usize) -> Result<Value> {
        let p = self.page(page)?;
        let deleted = self.deleted(page);
        let mut content = p.background.clone();
        let mut imported = 0;
        let mut added = 0;
        for item in &p.items {
            if !deleted.contains(item.id.as_str()) {
                content.push_str(&format!("<g data-item=\"{}\">{}</g>", item.id, item.svg));
                imported += 1;
            }
        }
        for (id, line) in self.additions(page) {
            if !deleted.contains(id.as_str()) {
                content.push_str(&format!(
                    "<g data-item=\"{id}\">{}</g>",
                    line_svg(&line.points, line.width / 2., &line.rgba)
                ));
                added += 1;
            }
        }
        let [w, h] = p.size;
        let texts: Vec<_> = p
            .items
            .iter()
            .filter(|i| !deleted.contains(i.id.as_str()))
            .filter_map(|i| i.text.as_ref())
            .collect();
        let svg=format!("<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 {w} {h}\" width=\"{w}\" height=\"{h}\" style=\"isolation:isolate\">{content}</svg>");
        Ok(
            json!({"title":self.scene.title,"pages":self.scene.pages.len(),"page":page,"size":p.size,"svg":svg,"warnings":p.warnings,"texts":texts,"visible_imported":imported,"visible_added":added,"erased":deleted.len(),"can_undo":self.cursor>0,"can_redo":self.cursor<self.history.len(),"edit_count":self.cursor}),
        )
    }
    pub fn save_project(&self) -> Result<String> {
        let data = serde_json::to_string(&Project {
            format: "noteful-re-project".to_owned(),
            version: 1,
            source_base64: STANDARD.encode(&self.source),
            history: self.history.clone(),
            cursor: self.cursor,
        })
        .map_err(|e| Error::new(0, e.to_string()))?;
        if data.len() > MAX_FILE_BYTES * 2 {
            return Err(Error::new(0, "Project size limit exceeded"));
        }
        Ok(data)
    }
    pub fn open_project(data: &str) -> Result<Self> {
        if data.len() > MAX_FILE_BYTES * 2 {
            return Err(Error::new(0, "Project size limit exceeded"));
        }
        let project: Project =
            serde_json::from_str(data).map_err(|e| Error::new(0, e.to_string()))?;
        if project.format != "noteful-re-project"
            || project.version != 1
            || project.history.len() > 10_000
            || project.cursor > project.history.len()
        {
            return Err(Error::new(0, "Unsupported or invalid project"));
        }
        let source = STANDARD
            .decode(project.source_base64)
            .map_err(|e| Error::new(0, e.to_string()))?;
        let mut editor = Self::open(&source)?;
        for edit in project.history {
            match edit {
                Edit::Add { page, line } => editor.add_line(page, line)?,
                Edit::Erase { page, ids } => {
                    let p = editor.page(page)?;
                    let deleted = editor.deleted(page);
                    let valid: HashSet<String> = p
                        .items
                        .iter()
                        .filter(|i| !i.hit.is_empty())
                        .map(|i| i.id.clone())
                        .chain(editor.additions(page).map(|(id, _)| id))
                        .collect();
                    let unique: HashSet<_> = ids.iter().collect();
                    if ids.is_empty()
                        || unique.len() != ids.len()
                        || ids
                            .iter()
                            .any(|id| !valid.contains(id) || deleted.contains(id.as_str()))
                    {
                        return Err(Error::new(0, "Invalid erased item IDs"));
                    }
                    editor.commit(Edit::Erase { page, ids })?;
                }
            }
        }
        editor.cursor = project.cursor;
        Ok(editor)
    }
}
