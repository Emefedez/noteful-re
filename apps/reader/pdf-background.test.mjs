import assert from "node:assert/strict";
import test from "node:test";
import { rasterTarget } from "./pdf-background.js";

test("PDF raster target follows displayed width and keeps a bounded pixel budget", () => {
  const target = rasterTarget({ width: 612, height: 792 }, 960, 1);
  assert.equal(target.width, 1920);
  assert.equal(target.height, 2485);

  const capped = rasterTarget({ width: 5000, height: 7000 }, 6000, 3);
  assert.ok(capped.width <= 8192);
  assert.ok(capped.height <= 8192);
  assert.ok(capped.width > 5000);
});
