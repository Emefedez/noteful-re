//! Browser adapter; decoding remains in the platform-independent core.
use noteful_core::{Field, Package, WireValue};
use serde_json::json;
use wasm_bindgen::prelude::*;

/// Each browser editor owns its source, scene and undo history in Rust.
#[wasm_bindgen]
pub struct EditorSession {
    inner: noteful_core::Editor,
}
fn js_error(e: impl std::fmt::Display) -> JsValue {
    JsValue::from_str(&e.to_string())
}
#[wasm_bindgen]
impl EditorSession {
    #[wasm_bindgen(constructor)]
    pub fn new(data: &[u8]) -> Result<EditorSession, JsValue> {
        Ok(Self {
            inner: noteful_core::Editor::open(data).map_err(js_error)?,
        })
    }
    pub fn load_project(data: &str) -> Result<EditorSession, JsValue> {
        Ok(Self {
            inner: noteful_core::Editor::open_project(data).map_err(js_error)?,
        })
    }
    pub fn view(&self, page: usize) -> Result<String, JsValue> {
        Ok(self.inner.view(page).map_err(js_error)?.to_string())
    }
    pub fn draw(&mut self, page: usize, line: &str) -> Result<(), JsValue> {
        let line = serde_json::from_str(line).map_err(js_error)?;
        self.inner.add_line(page, line).map_err(js_error)
    }
    pub fn erase(&mut self, page: usize, path: &str, radius: f64) -> Result<usize, JsValue> {
        let path: Vec<[f64; 2]> = serde_json::from_str(path).map_err(js_error)?;
        self.inner.erase_path(page, &path, radius).map_err(js_error)
    }
    pub fn undo(&mut self) {
        self.inner.undo();
    }
    pub fn redo(&mut self) {
        self.inner.redo();
    }
    pub fn save_project(&self) -> Result<String, JsValue> {
        self.inner.save_project().map_err(js_error)
    }
}

fn get(fields: &[Field], tag: u16) -> Option<&WireValue> {
    fields.iter().find(|f| f.tag == tag).map(|f| &f.value)
}
fn summary(data: &[u8]) -> noteful_core::Result<String> {
    let package = Package::parse(data)?;
    let mut title = String::new();
    let mut pages = 0;
    let mut objects = 0;
    let mut strokes = 0;
    let mut warnings = Vec::new();
    let mut resources = Vec::new();
    for block in &package.blocks {
        if let Some(fields) = &block.fields {
            if block.kind == "note_metadata" {
                title = get(fields, 3)
                    .and_then(WireValue::as_text)
                    .unwrap_or("")
                    .to_owned();
            }
            if block.kind == "drawing_metadata" {
                pages += get(fields, 2)
                    .and_then(WireValue::as_fields)
                    .and_then(|fs| get(fs, 0))
                    .and_then(WireValue::as_array)
                    .map_or(0, |v| v.len());
            }
            if block.kind == "stroke_object_set" {
                objects += get(fields, 5)
                    .and_then(WireValue::as_fields)
                    .and_then(|fs| get(fs, 0))
                    .and_then(WireValue::as_array)
                    .map_or(0, |v| v.len());
            }
        }
        strokes += block.strokes.as_ref().map_or(0, |v| v.len());
        if let Some(e) = &block.stroke_error {
            warnings.push(format!("{}: {e}", block.id));
        }
        if matches!(block.kind, "pdf" | "png" | "jpeg") {
            resources.push(json!({"id":block.id,"kind":block.kind,"bytes":block.size}));
        }
    }
    // Only bounded counts and byte lengths cross as numbers. IDs remain strings.
    Ok(
        json!({"schema_version":1,"title":title,"bytes":data.len(),"pages":pages,
        "strokes":strokes,"objects":objects,"resources":resources,"warnings":warnings})
        .to_string(),
    )
}

/// Versioned, JavaScript-safe summary. Input is a Uint8Array; result is JSON text.
#[wasm_bindgen]
pub fn inspect_document(data: &[u8]) -> Result<String, JsValue> {
    summary(data).map_err(|error| JsValue::from_str(&error.to_string()))
}

/// Full wire re-encoding in WebAssembly, without exporting 64-bit numbers to JS.
#[wasm_bindgen]
pub fn verify_document(data: &[u8]) -> Result<bool, JsValue> {
    let package = Package::parse(data).map_err(|e| JsValue::from_str(&e.to_string()))?;
    Ok(package
        .rebuild()
        .map_err(|e| JsValue::from_str(&e.to_string()))?
        == data)
}

#[cfg(test)]
mod tests {
    #[test]
    fn summary_contains_only_browser_safe_values() {
        let data = include_bytes!("../../../samples/Examen wuolah.noteful");
        let value: serde_json::Value =
            serde_json::from_str(&super::summary(data).unwrap()).unwrap();
        assert_eq!(value["schema_version"], 1);
        assert_eq!(value["pages"], 3);
        assert_eq!(value["strokes"], 2008);
        assert_eq!(value["objects"], 74);
        assert_eq!(value["title"], "Examen wuolah");
    }
}
