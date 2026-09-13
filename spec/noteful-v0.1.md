# Especificación observada Noteful — revisión 0.1

Esta revisión versiona nuestro conocimiento, no una versión oficial de Noteful.
Corpus: ocho archivos originales `samples/*.noteful`; SHA-256 en evidencia/corpus.
Separar requisitos sintácticos de interpretaciones visuales contrastadas.

## Contenedor

Todos los números wire son big-endian. Magic inicial/final `AA BB CC DE`.
Tráiler de 16 bytes: magic, offset uint64 del índice, tamaño uint32 del índice.
`offset + tamaño = longitud_archivo - 16`.

Índice: tag 1 versión; tags 10/11/12 arrays de claves UTF-8, offsets uint64,
tamaños uint64. Igual longitud, claves únicas. Los bloques ordenados por offset
cubren exactamente `[4, offset_índice)`. Tamaños positivos, sin solapamientos.
Tag 4 identifica conjuntos editables. No inferir tinta por ausencia de prefijo.

Campos: uint16 tag + uint16 tipo. Base `tipo & 0xff`; flag 0x400 añade array con
count uint32; flag 0x800 añade reloj uint64 después del valor completo.

| Tipo base | Valor escalar |
|---|---|
| 1 | uint8 |
| 2, 0x13 | uint64, distinciones semánticas pendientes |
| 3 | float32 finito |
| 4, 0x20 | float64 finito |
| 0x11 | uint16 |
| 0x12, 0x14 | uint32 |
| 0x21 | Dos float64 |
| 5 | Longitud uint32 + UTF-8 |
| 6 | Longitud uint32 + blob |
| 7 | Longitud uint32 + secuencia anidada de campos |

Implementación Rust conserva variantes tipadas, offsets y tipo original. Rechaza
tags duplicados en cada secuencia, flags/tipos no soportados, longitudes inválidas,
UTF-8 inválido y no finitos. Es una política estricta del decoder observado.

## Tinta

Conjunto editable/tag 2: secuencia de comandos. F1 02 ocupa 44 bytes: comando,
RGBA en cuatro float64, herramienta uint16, ocho bytes opacos. Estilo persiste.
F1 01 ocupa cabecera de 56 bytes: comando, ID uint64, flags uint16, dos uint64
opacos, orden uint64, capa uint32, radio float64, uint32 opaco, N uint32.

`flags & 2`: canal auxiliar de `8*N` bytes antes de geometría. Semántica abierta.
D = 3 con `flags & 1`; D = 2 en otro caso. Geometría:

- N ≤ 4: N*D float32 directos.
- N > 4: 2*D float32 `[mínimo, extensión]` por dimensión, luego N*D uint16.
- Reconstrucción: `mínimo + q/65535 * extensión`.
- Tercera dimensión = radio por muestra, contrastada con extremos del PDF para
  23 trazos. No deducir presión del dispositivo a partir del radio.

Flags fuera de 0..3 o comandos desconocidos: conservar blob y producir error
del conjunto de tinta; nunca saltar bytes buscando siguiente firma. El contenedor
puede seguir inspeccionándose. `verify` demuestra round-trip, no semántica completa.

## Semántica y composición

Rutas de nota/página/capa: `docs/FORMAT.md`. Multipágina: `docs/EXAMEN.md`.
Figuras, opacidad y radios: `docs/RENDERING.md`; Multiply 0,5 para subrayador,
aplicado una vez por objeto/trazo. Son contratos del renderer futuro, no parte
del decoder binario. La fase Rust actual preserva esos campos para consumidor.

## Límites de implementación, no del formato

Archivo ≤64 MiB; profundidad anidada ≤40; presupuesto de 1.000.000 campos/valores
por bloque y 1.000.000 puntos por blob. No significa que Noteful imponga esos
límites. Los bloques se validan antes de decodificar; offsets usan aritmética
comprobada antes de convertirse a rangos en memoria. Tipos desconocidos no se
inventan ni normalizan.

## Criterios de conformidad de esta fase

1. Decodificar las ocho muestras sin error de tinta.
2. Reemitir campos e índice, preservando recursos y blobs: mismos bytes completos.
3. Coincidir con Python en datos emitidos y semántica. Tolerancia de cálculo de
   coordenadas: relativa 1e-13, absoluta 1e-10; datos binarios siempre exactos.
4. Con renderer Python compartido, producir mismos SVG byte a byte.
5. Rechazar casos negativos documentados sin panic.

El JSON de CLI es diagnóstico para Python/RE y puede contener uint64 mayores que
2^53. No es API estable de GUI JavaScript. Versionar una DTO distinta al crear
bindings. No usar SVG exportado como modelo editable de documento.
