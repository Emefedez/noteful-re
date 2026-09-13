# Editor web: Rust + WebAssembly

Implementado 2026-09-13. `noteful-core` contiene lectura, escena SVG y edición;
`noteful-wasm` expone sesiones a un Web Worker. JavaScript maneja controles,
coordenadas de pantalla y previsualización del gesto. No replica el parser.

## Qué funciona

- Abrir archivos locales `.noteful` y proyectos `.nfedit`, o arrastrarlos.
- Renderizar páginas, tinta, fotos y figuras. Subrayador Multiply al 50%.
- Dibujar trazos nuevos con grosor fijo de 1/2/4/8 unidades; elegir color.
  Ratón, touch o stylus mediante Pointer Events. No se utiliza presión.
- Borrar trazos completos importados y nuevos, además de objetos de línea recta.
  Barrido continuo entre muestras del borrador; un gesto es una acción deshacible.
- Deshacer/rehacer con botones o Ctrl/⌘ Z y Ctrl/⌘ Mayús Z.
- Cambiar página, zoom, desplazarse con rueda/touch o arrastrar con Mover.
- Guardar/reabrir proyectos con original, cambios e historial. Exportar SVG actual.
- Cancelar un gesto con Escape, pointercancel o pérdida de captura, sin confirmar
  una línea parcial. Avisar al reemplazar/cerrar con cambios sin guardar.

El render y las operaciones terminadas se ejecutan en Rust. El trazo provisional
se dibuja inmediatamente en un overlay SVG; se envía una operación al soltar.
No se envía el archivo al servidor. El puerto 8767 sirve solamente archivos web.
El visor histórico en 8765 y la variante Rust/Python en 8766 se conservan.

## Compilar y ejecutar

Desarrollo: Rust ≥1.93, Python ≥3.11 para build, Node para pruebas/servidor.
En el navegador no hace falta instalar Rust, Python o Node.

```sh
rustup target add wasm32-unknown-unknown
cargo install wasm-bindgen-cli --version 0.2.128 --locked --root work/wasm-tools
python3 tools/build_web.py
node web/test.mjs
node tools/serve_web.mjs
```

Abrir `http://127.0.0.1:8767/`. Cualquier servidor HTTP estático puede servir `web/`:
`.wasm` como `application/wasm`, CSS como `text/css`, JS como módulos. No abrir con
`file://`. El servidor incluido admite GET/HEAD y escucha solo en loopback.
`build_web.py` comprueba la versión de wasm-bindgen contra Cargo.lock y separa
los toolchains de Homebrew/rustup. `web/pkg` y las copias de muestras se generan.

## API

```ts
inspect_document(bytes: Uint8Array): string; // Resumen JSON seguro para JS
verify_document(bytes: Uint8Array): boolean; // Round-trip wire sin cambios
const editor = new EditorSession(bytes);
editor.view(page); // JSON: SVG actual, dimensiones, avisos, estado del historial
editor.draw(page, JSON.stringify({points:[[10,10],[100,10]], width:2, rgba:[0,0,1,1]}));
editor.erase(page, JSON.stringify([[50,0],[50,20]]), 10);
editor.undo(); editor.redo();
const saved = editor.save_project();
const reopened = EditorSession.load_project(saved);
editor.free(); reopened.free();
```

Las operaciones pueden lanzar errores. Páginas son índices desde cero. Los puntos
usan coordenadas de página; width es diámetro y el último argumento de erase es
radio. No convertir relojes/IDs uint64 a Number: el JSON diagnóstico completo del
CLI sigue reservado para RE/Python. La GUI recibe conteos acotados y IDs locales.
El Worker conserva una sesión y entrega solo la página actual tras cada operación.

Texto y fuentes: [TEXT.md](TEXT.md). Audio incrustado y sincronización pendiente:
[AUDIO.md](AUDIO.md).

## Límites explícitos

`.nfedit` es un formato propio: **no** es un `.noteful` editado que la app original
pueda importar. Especificación: `spec/nfedit-v1.md`. El `.noteful` original queda
intacto dentro del proyecto. No hay autosave; usar Guardar proyecto.

El borrador elimina elementos completos, no segmentos. No borra fotos, curvas
objeto ni figuras rellenas. El hit-test de tinta variable usa su radio máximo como
margen conservador. La interpolación importada sigue aproximada; PDF de fondo
genérico, semántica de borrado nativa, capas editables y exportación interoperable
siguen pendientes. La GUI tiene unidades fijas, no gestión de presión.

Por ahora, SVG de toda la página se reconstruye tras cada operación. Para notas
mucho mayores habrá que medir/trocear ese trabajo. No hay un techo fijo de MB
para notas/proyectos ni un máximo global de acciones/puntos. La memoria y el
direccionamiento de plataforma siguen importando. Cada gesto nuevo admite hasta
8.192 muestras. No se ha medido latencia en hardware Android.

## Validación

- Nueve notas: lectura/round-trip WASM real en Node.
- Once páginas: primitivas SVG Rust contra Python (tolerancia 2e-5), conservando
  orden, transformaciones, composición e imágenes; `evidence/rust-scene-parity.json`.
- Pruebas Rust y WASM de dibujo, barrido, undo/redo, proyectos y errores.
- Navegador integrado: apertura, dibujo real con ratón, borrado, recuperación,
  descarga y reapertura desde disco; `evidence/wasm-ui.md`.
- Linux/Windows/Android: `cargo check` del núcleo. No equivale a aplicaciones
  enlazadas, instaladas o probadas en esos dispositivos. CI preparada, no ejecutada
  en GitHub durante este trabajo.

[Documentación de wasm-bindgen](https://wasm-bindgen.github.io/wasm-bindgen/reference/cli.html).
