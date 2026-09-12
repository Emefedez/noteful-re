# Ampliación: examen real y visor

Estado inicial: 2026-09-12. Actualización de figuras, transparencia y radio por
punto en [RENDERING.md](RENDERING.md).

Fecha: 2026-09-12. Muestras originales copiadas a `samples/`, verificadas byte a
byte contra Downloads. Tamaños y SHA-256: `evidence/exam-source-manifest.json`.
El PDF exportado es referencia visual independiente; no proporciona los trazos
de la reconstrucción SVG. Los enunciados del examen se tratan como datos.

## Resultado reproducible

| Página visible | Conjunto editable | Trazos | Objetos sin representación |
|---|---|---:|---:|
| 1 | C896C9EFB2724605AB0B482CF36D470A | 621 | 7 |
| 2 | 8565A79803934A4AB05848E4C1A0EC18 | 939 | 5 |
| 3 | 5A206DE7C4174AC5B8B80EEB407ED3F6 | 448 | 0 |

Total: 2.008 trazos y 74 objetos. Se dibujan imágenes y líneas simples: 62 objetos.
Los otros 12 incluyen tipos 3, 6, 12 y 21. Se conservan sus campos y se avisa por
página. Las tres páginas se contrastaron visualmente con el PDF aportado.
Orden físico de páginas difiere del visible; ordenar por campo `página/5`
reproduce orden del PDF en este documento. No se ha probado toda la gramática
de claves de orden de Noteful.

## Flujo de tinta

Todos los valores numéricos aquí son big-endian. El parser consume exactamente
los tres blobs, incluyendo 69 comandos de estilo. No busca firmas para saltarse
bytes desconocidos: un comando no soportado produce advertencia explícita.

### Estilo `F1 02`, 44 bytes

| Offset | Tipo | Evidencia |
|---|---|---|
| 0 | 2 bytes | F1 02 |
| 2 | 4 × float64 | RGBA entre 0 y 1 |
| 34 | uint16 | 0 tinta, 1 resaltador en este corpus |
| 36 | 8 bytes | Opacos, conservados |

El estilo persiste hasta el siguiente cambio. Valor inicial observado: negro,
alpha 1, herramienta 0. Los colores recuperados coinciden visualmente con rojo,
azul, negro, naranja, verde, amarillo y morado del PDF.

### Geometría `F1 01`

| Offset | Tipo | Interpretación |
|---|---|---|
| 0 | 2 bytes | F1 01 |
| 2 | uint64 | ID raw |
| 10 | uint16 | Flags observados: 0, 1, 2 |
| 12, 20 | uint64 | Valores similares a relojes; no resueltos |
| 28 | uint64 | Candidato a orden de dibujo |
| 36 | uint32 | Candidato a ID de capa |
| 40 | float64 | Candidato a radio/grosor |
| 48 | uint32 | Desconocido |
| 52 | uint32 | N, cantidad de puntos |
| 56 | variable | Canal auxiliar opcional, después geometría |

Si `flags & 2`, preceden a geometría `8*N` bytes auxiliares, preservados en hex.
Hay 12 trazos de este tipo. Su semántica no está resuelta; no se aplica borrado.

Dimensión D = 3 si `flags & 1`; en otro caso D = 2. Se observan 23 trazos con
tercer canal, candidato a presión o anchura. Se conserva, pero el visor usa
grosor uniforme. No afirmar todavía que son muestras crudas del Apple Pencil.

- N ≤ 4: `N*D` float32 de coordenadas directas, sin cabecera de límites.
- N > 4: `2*D` float32 `[minX, extentX, minY, extentY, ...]`, seguidos de
  `N*D` uint16 cuantizados.
- Reconstrucción por dimensión: `min + q/65535 * extent`.
- Longitud = `56 + (8*N si flag 2) + (4*N*D si N≤4; 8*D+2*N*D si N>4)`.

El ajuste cubre estos archivos completos y coincide visualmente. No sustituye
confirmación de `StrokeDecoder.parse` por decompilación o instrumentación.
Ghidra ya respalda contenedor e índice; estas variantes nuevas proceden del
análisis del archivo y contraste con su exportación, sin análisis dinámico nuevo.

## Representación y límites

`tools/render_note.py` produce SVG directamente desde recursos y geometría de
`.noteful`. Transforma imágenes con centro, tamaño y rotación; interpreta líneas
simples con comandos `[0,1]`. Ordena elementos por candidatos de orden raw.
Usa anchura `2 * thickness_candidate`, extremos redondos y opacidad 0,45 para
resaltador como aproximaciones visuales, no constantes recuperadas del binario.
No reproduce curvas del motor, presión, borrado, visibilidad de capas ni todas
las figuras. Fondos PDF genéricos aún requieren soporte; los papeles de estas
muestras se reconstruyen desde configuración JSON.

El visor permite apertura por selector/arrastre, ocho ejemplos, navegación,
comparación del examen y exportación SVG. PDF incrustado daba panel negro en el
navegador integrado: comparación usa PNG de cada página renderizados con Poppler
y enlace al PDF original. Ninguno de estos píxeles entra en el SVG reconstruido.

Arranque: `HTTPServer.server_bind` consultaba `socket.getfqdn` y bloqueaba durante
decenas de segundos en este Mac, demostrado con traceback temporizado. Se evita
esa consulta usando enlace directo a dirección loopback numérica.

## Verificación

`python3 -m unittest discover -s tests -v` prueba contenedor, round-trip exacto
de ocho notas, truncamiento, offsets falsificados, tipos desconocidos, consumo
completo del examen, comandos de estilo, variantes float32/auxiliares y apertura
HTTP de todos los ejemplos tras dos entradas inválidas.

Prueba UI: botón Abrir → fixture inválida → mensaje visible → mismo botón →
examen original → 2.008 trazos/3 páginas. Comparación visual de las tres páginas,
imágenes adjuntas, colores y navegación. Evidencia resumida en `evidence/ui-check.md`.

Reproducir vistas: `python3 tools/build_examples.py`. Galería autónoma en
`examples/index.html`; manifiesto con conteos por página y advertencias en
`examples/manifest.json`. La escritura de notas modificadas todavía no se ha
validado importándolas en Noteful.app.
