# Verificación local de UI — 2026-09-13

Navegador integrado, editor estático en 127.0.0.1:8767, WASM compilado localmente.

- Nota vacía: trazo con ratón → contador 1; barrido que cruza línea → 0 y 1 borrado;
  deshacer → 1. Guardar `.nfedit`, abrir archivo descargado → línea e historial
  restaurados. Ejemplo conservado en `examples/edicion-basica.nfedit`.
- Archivo inválido: error visible de magic; abrir después el examen de Downloads
  recupera el editor, con 655 elementos en primera página y tres páginas.
- Examen: fotografía, figuras y tinta visibles; gesto Mover desplaza scrollTop 170.
- Texto real: `texto texto`, `Bocadillo`, `Hola` visibles; tamaños y atributos también
  validados en Rust, Python y WASM. Inspección visual de negrita/cursiva realizada.
- WAV sintético: panel detecta 8044 bytes; reproductor devuelve duration=0.25,
  readyState=4, error=null. No se usa esto para afirmar sincronización nativa.

La pestaña del usuario con cambios se conservó; las pruebas posteriores se hicieron
aparte. No se recargó deliberadamente esa nota para activar las nuevas capacidades.
