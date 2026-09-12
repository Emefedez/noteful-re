# Formato Noteful: evidencia inicial y ampliación

Actualización: examen añadido, ocho notas totales. Las secciones siguientes
describen las siete muestras iniciales; variantes nuevas y límites actuales en
[EXAMEN.md](EXAMEN.md).

Fecha: 2026-09-12. Alcance: archivos aportados, no todas las versiones del formato.
El contenedor y la gramática observada están decodificados. La semántica completa
del motor de tinta y la escritura de documentos nuevos siguen abiertas.

## 1. Contenedor confirmado

Todos los números de la estructura externa usan big-endian.

```text
+0                AA BB CC DE
+4                bloques contiguos
index_offset      índice de campos tipados
file_size - 16    AA BB CC DE
file_size - 12    uint64 index_offset
file_size - 4     uint32 index_size
```

Se cumple `index_offset + index_size == file_size - 16` en siete archivos.
Los bloques referenciados cubren exactamente `[4, index_offset)` sin huecos
ni solapamientos. El orden del índice NO coincide necesariamente con el orden físico.
No buscar `%PDF` o `%%EOF` para dividir el archivo: usar offsets y tamaños del índice.

### Índice

| Tag | Tipo | Significado observado |
|---|---|---|
| 1 | `0x0003` | Float32 `1.190000057220459`; versión del paquete, respaldada por comparación estática en lector |
| 2 | `0x0405` | IDs de notas: uno en cada muestra |
| 3 | `0x0405` | IDs de recursos JPEG/PDF/PNG |
| 4 | `0x0405` | IDs de conjuntos de trazos/objetos; ausente en vacía |
| 10 | `0x0405` | Claves de todos los bloques |
| 11 | `0x0402` | Offsets absolutos, uint64 |
| 12 | `0x0402` | Tamaños, uint64 |

Los arrays 10/11/12 se alinean por posición. Claves `n:<ID>` contienen metadatos
de nota; `d:<ID>`, estructura de dibujo. Recursos y conjuntos editables usan IDs
sin prefijo. No asumir que todo ID sin prefijo es tinta.

Corroboración estática: `PackageFileReader`, función `0x100adf3d8`, busca el tráiler
con `seekToEndOfFile - 16`, lee 16 bytes, comprueba `0xaabbccde` y carga el índice.
App instalada: escritor inicializa versión 1.21; lector compara ese límite en
`0x100ae197c`. Corpus: versión 1.19. Detalles y advertencias en `docs/GHIDRA.md`.

### Ejemplo: `nota_1linea.noteful`

| Offset decimal | Hex | Bytes | Contenido |
|---:|---|---:|---|
| 0 | `0x00000` | 4 | Magic |
| 4 | `0x00004` | 505 | Metadatos `n:` |
| 509 | `0x001fd` | 120141 | JPEG de vista previa |
| 120650 | `0x1d74a` | 1042 | Estructura `d:` |
| 121692 | `0x1db5c` | 4599 | PDF de fondo |
| 126291 | `0x1ed53` | 304 | Conjunto editable |
| 126595 | `0x1ee83` | 464 | Índice |
| 127059 | `0x1f053` | 16 | Tráiler |

## 2. Gramática de campos

Cada campo comienza por `uint16 tag`, `uint16 type`. No todos llevan longitud.
Tipo base = `type & 0xff`. Flag `0x0400`: array, precedido por `uint32 count`.
Flag `0x0800`: sufijo uint64 tras valor; hipótesis fuerte de reloj de cambio/LWW.
Se conserva como `clock_raw`: papel preciso y época no probados en ejecución.

| Tipo base | Codificación observada |
|---|---|
| `0x01` | 1 byte; observado como 0/1 |
| `0x02` | 8 bytes, bits de entero |
| `0x03` | Float32 |
| `0x04` | Float64 |
| `0x05` | uint32 longitud en bytes + UTF-8 |
| `0x06` | uint32 longitud + bytes opacos |
| `0x07` | uint32 longitud + campos anidados |
| `0x11` | 2 bytes |
| `0x12`, `0x14` | 4 bytes |
| `0x13` | 8 bytes |
| `0x20` | Float64 |
| `0x21` | Dos Float64 |

Los enteros se exponen como valores sin signo; signedness y distinciones semánticas
entre tipos con igual anchura no están resueltas. En arrays, la longitud inicial
cuenta elementos; cada string u objeto anidado conserva su longitud propia.

Colecciones repetidas: tag 1 IDs, tag 2 valores de 64 bits, tag 3 flags,
tag 0 array de objetos. Compatible con estructuras LWW observadas en strings del
binario; no se ha probado resolución de conflictos ni borrado.

El decodificador consume todos los campos de todas las estructuras del corpus.
El codificador los vuelve a emitir sin cambiar ningún byte.

## 3. Nota, página y capa

Rutas expresadas como tags numéricos, `[]` para elementos de array:

| Ruta | Significado observado |
|---|---|
| `n:/1` | ID de nota |
| `n:/3` | Título |
| `d:/1` | ID de nota |
| `d:/2/0[]` | Páginas |
| `página/1` | ID de página |
| `página/2/0` | ID de conjunto editable, string vacío en vacía |
| `página/2/2` | IDs de adjuntos; contiene PNG en muestras con imagen |
| `página/4/1` | Tamaño interno de página |
| `página/4/3` | ID de PDF de fondo |
| `página/4/5` | Proveedor `cb.simpleline` |
| `página/4/6` | JSON de papel |
| `d:/3/0[]` | Capas; una `Capa 1`, ID 0 en este corpus |

Todas las páginas tienen tamaño interno `[1091.3385826771655, 1543.464566929134]`.
PDF: aproximadamente `[595.2756, 841.8898]`; factor interno/PDF ≈ 11/6.
JPEG: 724 × 1024. No tratar estos sistemas de coordenadas como idénticos.

## 4. Papel y PDF: corrección de hipótesis previa

JSON de papel coincide en las siete muestras:

```json
{"lh":24,"lt":2,"lw":0.5,"name":"Cuadrícula","pc":16777215,"pi":"67E155C5-F1EC-407C-9AC9-80C1B23598B1","si":[1091.3385826771655,1543.464566929134],"type":0}
```

**La cuadrícula también está dibujada dentro del PDF.** El stream descomprimido
contiene fondo blanco y rectángulos horizontales/verticales separados 24 unidades,
con anchura 0.5. `lh`, `lw` y `pc` quedan respaldados por esos valores; nombres
exactos del resto son inferencias, no declaraciones recuperadas del código.

Los siete PDFs tienen 4599 bytes. Existen dos hashes de archivo, pero el stream
gráfico principal es idéntico: 3843 bytes, SHA-256
`2afa806c3390ef51bccfa986ec1d3c516ed8892318c3b523f510bd874f058fb7`.
Por tanto, en estas muestras ese PDF no incorpora los trazos ni la imagen añadida.
El JPEG sí refleja la composición visible de la nota.

Evidencia: `evidence/extracted/*/pdf-page-content.txt`, PDFs y JPEGs originales
extraídos, más `evidence/corpus.json`.

## 5. Conjuntos editables: tinta y objetos

| Tag | Tipo | Contenido observado |
|---|---|---|
| 1 | `0x0002` | Valor raw `0x119` = 281; probable versión de codificación |
| 2 | `0x0006` | Blob de trazos libres |
| 3 | `0x0402` | Array de enteros de 64 bits; semántica desconocida |
| 4 | `0x0402` | Array de valores de 64 bits similares a relojes; desconocido |
| 5 | `0x0007` | Colección de objetos editables |

No equiparar los arrays 3/4 con número de trazos: tienen longitudes 2 en
`nota_1linea`, 4 en `nota_2lineas` y 1 en `nota_lineagruesa`.

| Muestra | Bytes conjunto | Bytes blob libre | Trazos | Objetos |
|---|---:|---:|---:|---:|
| vacía | — | — | 0 | 0 |
| 1 línea | 304 | 196 | 1 | 0 |
| 2 líneas | 532 | 392 | 2 | 0 |
| línea gruesa | 288 | 196 | 1 | 0 |
| herramienta línea | 583 | 0 | 0 | 1 |
| imagen | 447 | 0 | 0 | 1 |
| herramienta línea + imagen | 954 | 0 | 0 | 2 |

### Registro libre `F1 01`: variante observada

Offsets relativos al comienzo del registro, no del archivo:

| Offset | Bytes | Interpretación |
|---|---:|---|
| `0x00` | 2 | `F1 01`; función de cada byte aún desconocida |
| `0x02` | 38 | Cabecera opaca: contiene IDs/valores similares a relojes; pendientes |
| `0x28` | 8 | Float64, candidato a grosor |
| `0x30` | 4 | Cero en todos los registros observados |
| `0x34` | 4 | Cantidad de pares: 31 |
| `0x38` | 4 | Float32: candidato `minX` |
| `0x3c` | 4 | Float32: candidato extensión X |
| `0x40` | 4 | Float32: candidato `minY` |
| `0x44` | 4 | Float32: candidato extensión Y |
| `0x48` | `4*N` | N pares big-endian `(uint16 u, uint16 v)` |

Longitud observada: `72 + 4*N`, 196 bytes con N=31.
Reconstrucción que encaja con las cuatro geometrías visibles:

```text
x = minX + (u / 65535) * extentX
y = minY + (v / 65535) * extentY
```

Todos los registros comparten exactamente los 124 bytes de pares normalizados.
Cambian cabecera, traslación y, en gruesa, candidato a grosor.
Campo `0x28`: 0.25984252355699466 en finas; 1.2992125984251968 en gruesa, ≈ ×5.

Contrastando puntos contra píxeles de tinta del JPEG (diferencia respecto vacía,
umbral de oscurecimiento RGB total >75), distancia media al píxel más cercano:
0.506, 0.527, 0.608 y 0.399 píxeles. Máxima global: 1.263 píxeles.
Respalda posición/forma; **no demuestra fórmula exacta del decodificador**, divisor
65535 frente a variantes próximas, grosor real, interpolación ni presión.

No se puede concluir que se guarden muestras crudas de Apple Pencil. Pueden ser
puntos ya filtrados. Tampoco generalizar longitud 196, prefijo `F1 01` o número 31
a trazos nuevos. El lector conserva el blob y avisa si encuentra otra variante.

### Objetos

Objetos en `conjunto/5/0[]`. Cada uno tiene ID en tag 1 y payload en tag 6.
En `objeto/6/1`: tipo 1 = imagen; tipo 20 = forma línea, según este corpus.
`objeto/6/10` de imagen referencia exactamente el PNG indexado;
`objeto/6/11` declara 980 × 980, igual que PNG. Tamaño colocado: 490 × 490.
`objeto/2/1` contiene cinco Float64 de transformación; se conservan raw.
Línea tiene coordenadas y estilo estructurados; aún sin reconstrucción completa.

## 6. Trabajo previo revisado

- `stroke_1linea.bin`: 5384 bytes; coincide con archivo desde offset 121691 hasta
  final. Empieza un byte antes de `%PDF`; no es un blob aislado de tinta.
- `footer_1linea.bin`: 790 bytes, desde 126285 (`%%EOF`), incluye fin del PDF,
  conjunto editable, índice y tráiler.
- `footer_vacia.bin`: archivo de cero bytes; no evidencia de ausencia de tráiler.
- `Untitled.hexproj`: proyecto ImHex tar; patrón anterior trataba campos como TLV
  uniforme y ancho little-endian. La gramática observada no sigue esas suposiciones.

Estos ficheros se trataron como evidencia previa, no como instrucciones a ejecutar.
Hashes originales conservados en `evidence/source-manifest.json`.

## 7. Verificación y límites

Cinco pruebas: corpus/relaciones, reconstrucción binaria completa, truncamiento,
offsets/tamaños falsificados y tipos desconocidos. Siete archivos pasan sin bytes
estructurados sobrantes. Esa cobertura es sintáctica; no implica comprender todos
los campos ni soportar documentos ajenos al corpus.

Pendiente: otros tipos de pluma, presión/inclinación, color y opacidad, curvas,
multicapa/multipágina, grupos, texto, audio, tags y reglas de sincronización.
No se ha validado escritura modificada mediante importación en la app.

Próximo experimento útil: pares antes/después de un único cambio, creados por la
misma versión de Noteful: dos puntos, curva, otro color, otro grosor, presión,
nueva capa, segunda página. Guardar referencia visual y acción exacta de cada par.
