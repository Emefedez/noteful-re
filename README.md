# Noteful RE

Lector y visor experimental `.noteful`, validado con ocho notas aportadas.
Trabajo realizado en esta carpeta; archivos originales de Downloads conservados.

## Abrir una nota

Doble clic en **Abrir Noteful.command**. Abre navegador y carga el examen.
Usa **Abrir archivo .noteful**, arrastra un archivo o elige uno de los ocho ejemplos.
Flechas cambian de página; **Comparar con PDF del examen** muestra referencia
independiente. **Guardar SVG** exporta la reconstrucción de la página actual.

También puedes abrir `examples/index.html` directamente: ocho vistas HTML y diez
páginas SVG, sin servidor. Estas vistas estáticas no cargan archivos nuevos.

```sh
python3 tools/noteful.py  # abre visor
python3 tools/noteful.py "samples/Examen wuolah.noteful" --view
python3 tools/viewer.py --file "/ruta/nota.noteful"
```

Requiere Python 3.10 o posterior. Servidor limitado a `127.0.0.1`; ningún archivo
sale del equipo. Ctrl+C en Terminal cierra servidor. No modifica los originales.

## Resultados

- Magic `AA BB CC DE`; índice situado por tráiler de 16 bytes.
- Extracción exacta de bloques JPEG, PDF, PNG y estructuras editables.
- Decodificación recursiva de campos, arrays y sufijos de 64 bits asociados a cambios.
- Relaciones nota → página → fondo / conjunto editable / adjuntos; capas recuperadas.
- Examen: 2.008 trazos en tres páginas (621 / 939 / 448), colores y herramientas.
- Comandos `F1 01` de geometría y `F1 02` de estilo; puntos float32 o cuantizados.
- Radio por punto recuperado en 23 trazos; canal auxiliar en 12 aún sin resolver.
- Subrayador sobre fotografías: Multiply al 50%, como el PDF exportado.
- Figuras: elipses, polígonos, curvas cúbicas y rectángulos redondeados.
- Herramienta línea e imagen son objetos distintos de los trazos libres.
- Ocho archivos reconstruidos byte a byte; doce pruebas automáticas pasan.

Ver [especificación y límites](docs/FORMAT.md), [evidencia comparativa](evidence/corpus.json)
y [estado de Ghidra](docs/GHIDRA.md).

## Uso

Python 3, sin dependencias para lector y pruebas. Ejecutar desde esta carpeta:

```sh
python3 tools/noteful.py samples/nota_1linea.noteful
python3 tools/noteful.py samples/nota_1linea.noteful --extract work/mi-extraccion
python3 tools/analyze_corpus.py
python3 -m unittest discover -s tests -v
file -m docs/noteful.magic samples/nota_1linea.noteful
```

`--extract` exige una carpeta nueva. Produce bloques sin alterar, `index.bin`,
`manifest.json` con offsets absolutos y resumen semántico. Los blobs originales de
tinta se guardan aparte. Las siete extracciones ya están en `evidence/extracted/`.

`encode_fields()` permite reconstruir los campos observados. No se presenta como
editor general: todavía no se ha importado un archivo modificado en Noteful.
El visor representa los 74 objetos y los 2.008 trazos del examen, con grosor
variable y subrayadores transparentes. Interpolación de tinta todavía aproximada.
Fondos PDF genéricos, otros tipos de figura y semántica de borrado pendientes.
Los antiguos `freehand-provisional.svg` son evidencia histórica en negro.
`examples/` contiene la reconstrucción actual con color y páginas separadas.

## Organización

- `samples/`: copias de ocho notas y PDF exportado del examen.
- `examples/`: galería estática, SVG por página y referencia rasterizada del PDF.
- `viewer/`: interfaz local.
- `tools/`: lector, codificador de campos, comparación y scripts de análisis.
- `tests/`: corpus, relaciones, reconstrucción y entradas inválidas.
- `docs/`: formato, identificación libmagic y estado de Ghidra.
- `evidence/`: hashes, offsets, extracciones, comparaciones y resultados estáticos.
- `work/`: entorno Cerberus y proyecto Ghidra; material intermedio.

Regenerar ejemplos: `python3 tools/build_examples.py`. Referencias PNG creadas con
Poppler desde el PDF aportado; no se usan para reconstruir tinta. Hashes en
`evidence/exam-source-manifest.json`. Detalles nuevos: `docs/EXAMEN.md`.

Actualización de transparencia, figuras, radios y copia completa de seguridad:
[RENDERING.md](docs/RENDERING.md).
