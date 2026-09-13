#!/bin/zsh
cd -- "${0:A:h}"
node tools/serve_web.mjs 8765
