#!/bin/sh

cd "$(dirname "$0")"

cd web/wasm/
wasm-pack build --dev

cd pkg/
mv core_bg.wasm core_bg.js ../../frontend/wasm