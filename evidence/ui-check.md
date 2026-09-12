# Verificación del visor — 2026-09-12

- Navegador integrado, servidor local `http://127.0.0.1:8765/`.
- Carga inicial: examen, 2.008 trazos, 3 páginas, 74 objetos.
- Página 1: título manuscrito, matrices, rojo, negro, azul y resaltadores.
- Página 2: imagen de Pregunta 2; 939 trazos; orden coincide con PDF.
- Página 3: imagen de Pregunta 1; 448 trazos; orden coincide con PDF.
- Referencia PDF incrustada inicialmente negra; reemplazada por PNG independientes
  con navegación sincronizada y enlace al PDF original.
- Botón Abrir con `tests/fixtures/invalid.noteful`: error visible de magic;
  lienzo anterior desaparece y navegación queda deshabilitada.
- Mismo selector con original Downloads/Examen wuolah.noteful: vuelve a cargar.
- Tinta y texto manuscrito reconstruidos proceden del binario; comparación muestra
  diferencias de grosor y figuras pendientes, sin afirmar identidad de píxeles.

- Guardar SVG produjo Downloads/Examen wuolah-1.svg (529.076 bytes), idéntico al
  SVG generado para página 1. El evento de descarga de automatización expiró,
  pero el archivo se guardó y su contenido fue verificado.

## Actualización 2026-09-13

- Triángulos, elipses, curvas y rectángulo resaltado visibles: 74 objetos del examen.
- Página 2: subrayado amarillo encima de fotografía deja texto legible.
- Comparación mantiene curvas de paréntesis y resaltado rectangular en posiciones
  coincidentes con PDF; quedan diferencias de interpolación de tinta.
- Pruebas ampliadas a 12, incluyendo radios de los 23 trazos variables.
