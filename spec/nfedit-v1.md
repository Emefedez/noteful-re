# Noteful RE Project v1 (.nfedit)

Formato propio de edición no destructiva; no pertenece a Noteful.
UTF-8 JSON con campos obligatorios y sin claves desconocidas:

```json
{
  "format": "noteful-re-project",
  "version": 1,
  "source_base64": "...",
  "history": [
    {"kind":"Add","page":0,"line":{"points":[[10,10],[100,10]],"width":2,"rgba":[0,0,1,1]}},
    {"kind":"Erase","page":0,"ids":["new:0"]}
  ],
  "cursor": 1
}
```

`source_base64`: bytes originales completos, Base64 RFC 4648 estándar con padding.
No se modifican ni reconstruyen al guardar. `history` contiene acciones ordenadas;
solo `[0,cursor)` está aplicado. El resto puede rehacerse. Una acción nueva tras
undo trunca la rama de redo. Undo/redo son globales al documento.

`page`: índice desde cero en orden de páginas importadas. `Add` dibuja un trazo
sobre todos los elementos previos, en coordenadas de página, diámetro `width`
constante y color sRGB normalizado RGBA. Sin presión ni radios por muestra.
Un punto produce un disco; varios producen polilínea de extremos/uniones redondos.

IDs de elementos importados: `stroke:N` y `object:N`, donde N es posición desde
cero en su colección original de la página, antes de ordenar por z. `new:N`
identifica el Add situado en el índice N del historial. IDs son locales a página.
`Erase` contiene IDs únicos, existentes y visibles; nunca imágenes/figuras que el
borrador no soporte. Los IDs importados dependen del decodificador de esta versión;
un cambio incompatible necesita migración de versión, no reinterpretación tácita.

Validación: página existente; 1–8192 puntos finitos con coordenadas |v|≤1e6;
0.1≤width≤100; RGBA finito dentro de [0,1]; cursor dentro del historial;
sin techo fijo de MB ni máximo global de acciones/puntos. La memoria del destino
puede impedir cargar un proyecto grande.
La apertura valida todas las acciones, incluyendo redo, antes de devolver sesión.
No hay escritura parcial al archivo original. No se evalúa código ni HTML del JSON.
