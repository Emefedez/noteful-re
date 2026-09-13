# Texto atribuido y fuentes

Muestra aportada: `samples/texto.noteful`, SHA-256
`b9d30b6f89bce4905ac61a9b802b1fb216aac22ffc8fa888a81045bf48ec673b`.
Son tres objetos tipo **2**. El contenido está en payload tag 4; colocación,
tamaño del objeto, rotación, opacidad y z siguen el esquema de las otras figuras.

| Texto literal | Fuente | Tamaño UI | Tamaño de página | Rasgo |
|---|---|---:|---:|---|
| `texto texto ` | Helvetica | 16 | 29.3333333333 | Normal |
| `Bocadillo` | Gill Sans / GillSans-Bold | 16 | 29.3333333333 | Negrita |
| `Hola` | Galvji / Galvji-Oblique | 12 | 22 | Cursiva |

El espacio final de `texto texto ` existe en el archivo. Cada bloque termina con
un fragmento U+200B usado como posición de escritura. No se dibuja ese marcador.
La relación observada es **unidades de página = puntos de UI × 11/6**. El SVG usa
el tamaño almacenado directamente: no vuelve a multiplicarlo.

## Estructura de contenido

| Tag | Valor |
|---|---|
| 1 | Reloj/identificador opaco uint64 |
| 2 | Array de fragmentos UTF-8 |
| 3 | Número de cambios de atributos por fragmento |
| 4 | Claves concatenadas de los cambios |
| 5 | Pool de strings de atributos |
| 6 | Pool de bool/u8 |
| 7 | Pool de colores estructurados |
| 8 | Pool de enteros uint64 |
| 9 | Pool de párrafos estructurados |
| 10 | Pool de números float64 |

Los pools tienen cursores independientes. Se aplican los cambios de cada
fragmento y el estilo resultante **se hereda al siguiente**. No son estilos
completos independientes. Los conteos y el consumo de pools se validan.

| Clave wire | Atributo | Pool |
|---:|---|---:|
| 1 | Descriptor de fuente antiguo (interpretación parcial) | 5 |
| 2 | Negrita | 6 |
| 3 | Cursiva | 6 |
| 4 | Estilo de subrayado, entero | 8 |
| 5 | Estilo de tachado, entero | 8 |
| 6 / 7 | Color de texto / fondo | 7 |
| 8 | Alineación de párrafo | 8 |
| 9 | Objeto de párrafo | 9 |
| 10 | Tamaño de fuente | 10 |
| 11 / 12 | Altura de línea / espaciado | 10 |
| 13 / 14 | Familia / nombre PostScript | 5 |

Contenido, tamaños, negrita, cursiva y nombres se contrastaron con la muestra y
la descripción del usuario. Subrayado/tachado se sustentan en análisis estático:
`evidence/ghidra-text/100a485ec.c` relaciona los atributos UIKit con casos internos
3/4 y un pool de enteros; `100a49e04.c` los vuelve a aplicar como
NSUnderlineStyleAttributeName / NSStrikethroughStyleAttributeName. La tabla
interna empieza en cero; los casos de fuente/tamaño coinciden con wire +1 en la
muestra. **No** se ha obtenido todavía una muestra real subrayada/tachada.
Pruebas sintéticas cubren ambas decoraciones, valores cero y herencia.

## Render y límites

Rust y Python generan texto SVG con `tspan`, preservación de espacios, saltos
explícitos, tamaño, peso, cursiva, subrayado/tachado y familias. El texto se escapa
como XML, nunca se interpreta como HTML. Un atributo desconocido no oculta las
palabras: deja estilos parciales y un diagnóstico.

Las familias se solicitan al navegador; hay fallback Arial/sans-serif. No se
redistribuyen fuentes de Apple. El aspecto exacto depende de fuentes instaladas,
shaping y métricas del destino. El panel Texto y fuentes muestra valores leídos,
no certifica qué fichero de fuente resolvió el navegador.

La línea base usa un posicionamiento aproximado (margen 5 horizontal y 8 vertical
más tamaño de fuente). No se afirma paridad tipográfica de píxeles. Saltos suaves,
justificación, listas, párrafos complejos y fondo de texto siguen pendientes.
Los estilos de decoración distintos de cero se muestran como línea simple.
El papel predefinido de esta nota omite parámetros de color/tipo en JSON; su
fondo completo queda pendiente. No se usan píxeles del thumbnail para el texto.

Pruebas: `tests/test_text.py`, `crates/noteful-core/tests/text.rs`, `web/test.mjs`.
El comparador de escenas ahora comprueba también caracteres dentro del SVG.
