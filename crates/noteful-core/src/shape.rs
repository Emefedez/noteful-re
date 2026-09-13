use serde::{Deserialize, Serialize};
#[derive(Clone, Debug, Serialize, Deserialize, PartialEq)]
#[serde(rename_all = "lowercase")]
pub enum ShapeKind {
    Line,
    Rectangle,
    Ellipse,
    Triangle,
    Arrow,
}
#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Shape {
    pub kind: ShapeKind,
    pub start: [f64; 2],
    pub end: [f64; 2],
}
impl Shape {
    pub fn points(&self) -> Vec<[f64; 2]> {
        let [x, y] = self.start;
        let [u, v] = self.end;
        match self.kind {
            ShapeKind::Line => vec![self.start, self.end],
            ShapeKind::Rectangle => vec![[x, y], [u, y], [u, v], [x, v], [x, y]],
            ShapeKind::Triangle => vec![[(x + u) / 2., y], [u, v], [x, v], [(x + u) / 2., y]],
            ShapeKind::Ellipse => (0..=64)
                .map(|i| {
                    let a = f64::from(i) * std::f64::consts::PI / 32.;
                    [
                        (x + u) / 2. + (u - x).abs() / 2. * a.cos(),
                        (y + v) / 2. + (v - y).abs() / 2. * a.sin(),
                    ]
                })
                .collect(),
            ShapeKind::Arrow => {
                let a = (v - y).atan2(u - x);
                let d = 24f64.min((u - x).hypot(v - y) / 3.);
                vec![
                    self.start,
                    self.end,
                    [u - d * (a - 0.5).cos(), v - d * (a - 0.5).sin()],
                    self.end,
                    [u - d * (a + 0.5).cos(), v - d * (a + 0.5).sin()],
                ]
            }
        }
    }
}
