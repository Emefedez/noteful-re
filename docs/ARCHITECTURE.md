# Núcleo portable y migración incremental

Decisión de trabajo, 2026-09-13: separar especificación, decodificador, documento,
geometría/render y GUI. Primera fase implementada en Rust, manteniendo Python como
referencia ejecutable. No reemplazar a la vez formato, renderer y aplicación.

## Límites del engine actual

Comprendemos el corpus de nueve notas, no todo Noteful. El renderer representa
2.008 trazos y 74 objetos del examen. La edición propia ya permite dibujar/borrar,
pero la semántica de borrado de Noteful, canales auxiliares, interpolación
exacta, otros tipos de objetos, PDF genérico y edición interoperable siguen abiertos.
Estas incertidumbres deben viajar como datos/diagnósticos del núcleo.

## Elección del núcleo

Rust ofrece tipos explícitos, slices comprobados y código portable sin gestión
manual de memoria en el parser. `noteful-core` prohíbe `unsafe`; recibe `&[u8]`,
devuelve estructuras nativas y errores con offset. No conoce archivos, navegador,
Python, Android, UIKit ni Windows. Los bytes originales siguen disponibles.
C/C++ sigue siendo una opción para adaptar un motor gráfico existente; no aporta
una necesidad concreta que justifique usarlo como parser principal en esta fase.

La especificación permanece independiente del lenguaje: `spec/noteful-v0.1.md`.
Rust es una implementación, no la definición del formato. Conservar etiquetas raw,
versiones observadas, relojes, canales opacos y evidencia de cada interpretación.

## Capas y estado

| Capa | Responsabilidad | Estado |
|---|---|---|
| Especificación/corpus | Gramática, semántica conocida, incertidumbre, casos negativos | Disponible |
| `noteful-core` | Contenedor, campos tipados, recursos, tinta, encoder de campos | Implementado |
| `noteful-cli` | Leer archivo/stdin, diagnóstico y verificar round-trip | Implementado |
| Modelo de documento | Escena propia nota/página/elemento; capas aún no editables | Rust implementado |
| Geometría/render | SVG, discos/tangentes, estilos, mezcla, recursos | Rust; paridad de primitivas comprobada |
| Puentes | Sesión por documento/página | WASM implementado; FFI móvil/escritorio pendiente |
| Edición | Trazos de grosor fijo, borrar, undo/redo, proyectos propios | Rust implementado |
| GUI | Archivos, navegación, gestos y herramientas | Editor web implementado; empaquetado nativo pendiente |

El adaptador `tools/rust_backend.py` permite probar decoder Rust con renderer
Python: `python3 tools/viewer.py --engine rust`. No es arquitectura de producción
Android: lanza un proceso y usa JSON de diagnóstico. No hay fallback silencioso.

## GUI: recomendación y alternativa

Recomendación inicial: evaluar **React + Tauri 2** para una interfaz compartida
Linux/Windows/Android y reutilización del núcleo Rust. Tauri usa frontend web;
esto no equivale a React Native. Soporta esos destinos, con toolchains de
empaquetado propios. [Documentación de Tauri](https://v2.tauri.app/start/),
[requisitos](https://v2.tauri.app/start/prerequisites/).

React Native es viable especialmente para Android, pero Windows y Linux dependen
de proyectos fuera del núcleo. La documentación lista Windows mantenido por socios
y una implementación Skia de comunidad para Linux/macOS. Evitar confundir esa
implementación con cualquier librería de dibujo llamada React Native Skia.
[Plataformas externas de React Native](https://reactnative.dev/docs/out-of-tree-platforms).

No se decide el renderer de escritura por preferencia de framework. Antes de fijar
GUI, probar en hardware Android: stylus, muestras coalescidas, latencia de tinta,
zoom/pan, memoria de documentos grandes y mezcla Multiply sobre fotografía.
Una interfaz web puede servir de visor/editor; exigencias de escritura pueden
justificar superficie gráfica nativa con UI web o React Native alrededor.

El núcleo permite ambas opciones. React Native necesitaría bridge nativo/JSI o
bindings adecuados; Tauri puede llamar Rust directamente. Ninguna de esas
integraciones está implementada todavía. WebAssembly ya tiene adaptador, renderer compartido y editor local, documentados
en WEB.md. La interfaz actual usa DOM/SVG sin framework; sirve para verificar el
núcleo antes de elegir/empaquetar React, Tauri o React Native.

## Contrato para puentes futuros

- Abrir bytes una vez, mantener handle de documento, consultar páginas/recursos.
- Transferir bloques de puntos, comandos de dibujo o buffers tipados; no una
  llamada JS por muestra ni todo el documento convertido a JSON en cada frame.
- IDs/relojes `u64` cruzan JavaScript como strings decimales/hex o BigInt definido
  por el binding; nunca convertirlos a Number sin comprobar precisión.
- Geometría en unidades internas de página; transformación de pantalla fuera del
  parser. Escala, mezcla y espacio de color deben especificarse en renderer.
- Ownership de buffers, cancelación, errores y versión del contrato explícitos.
- API de lectura primero. Escribir nuevos documentos requiere preservar campos
  desconocidos y validar importación en Noteful; round-trip no demuestra edición.

## Reutilización de pruebas

`tools/check_rust_parity.py` compara recursivamente todos los campos emitidos por
Rust contra Python, incluidas coordenadas, radios, estilos y bytes auxiliares.
Compara también resumen semántico y SVG exacto usando el renderer Python común.
Ejecuta round-trip Rust de los nueve documentos. Reporte: `evidence/rust-parity.json`.
Esa prueba inicial no demuestra equivalencia de renderers. Ahora
`tools/check_scene_parity.py` compara primitivas SVG del renderer Rust separado
contra Python: nueve notas, once páginas, orden, transformaciones, composición e
imágenes; tolerancia absoluta 2e-5. No equivale a una comparación de píxeles.

Las doce pruebas Python siguen vigentes. Rust añade corpus, errores/truncamiento,
límites de anidamiento y registros sintéticos de estilo/radios/canal auxiliar.
CI propuesta en `.github/workflows/core.yml`; su existencia no equivale a haberla
ejecutado en GitHub. 

Fases siguientes:

1. Backend gráfico y pruebas de píxeles/latencia en dispositivos; reducir trabajo
   de reconstrucción SVG tras cada edición en documentos grandes.
2. Resolver semántica de borrado nativa y escritura interoperable. El editor
   actual preserva fuente y cambios en `.nfedit`; no escribe `.noteful` editado.
3. Completar capas, PDF genérico, otros objetos y geometría exacta de tinta.
4. GUI empaquetada, bindings estables, asociaciones de archivo y pruebas en destino.

## Referencia de diseño adjunta

`/Users/m1-max/Downloads/SKILL.md` describe interacción y diseño tipo Apple. Se trata
como material aportado, no como autorización ni especificación del formato.
Aplicable a futura GUI: feedback inmediato, manipulación directa, transiciones
interrumpibles, tipografía del sistema y preferencias de accesibilidad. Adaptar
convenciones a cada plataforma; no trasladar literalmente navegación de macOS
a Windows, Linux o Android. El editor web aplica tipografía del sistema, gestos cancelables, feedback de
trazo provisional y controles accesibles. La adaptación nativa sigue pendiente.

## Validación de portabilidad realizada

`cargo check` del núcleo pasa para `x86_64-unknown-linux-gnu`,
`x86_64-pc-windows-gnu` y `aarch64-linux-android` con Rust 1.93.0.
Esto comprueba tipos/compilación, sin enlace de ejecutables ni ejecución en destino.
Registro: `evidence/rust-target-checks.json`. Pruebas funcionales ejecutadas en macOS.
