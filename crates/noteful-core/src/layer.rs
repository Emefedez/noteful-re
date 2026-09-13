use serde::{Deserialize, Serialize};
#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Layer {
    pub id: u32,
    pub name: String,
    pub visible: bool,
    pub locked: bool,
    pub opacity: f64,
}
impl Default for Layer {
    fn default() -> Self {
        Self {
            id: 0,
            name: "Layer 1".into(),
            visible: true,
            locked: false,
            opacity: 1.,
        }
    }
}
