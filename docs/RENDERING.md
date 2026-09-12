# Transparencia, figuras y grosor variable

Actualización: 2026-09-13. Análisis del contenedor y del PDF exportado aportado;
no se realizó nueva instrumentación de Noteful.app. Sustituye los límites de
representación descritos inicialmente en EXAMEN.md.

## Copia de seguridad anterior a estos cambios

Archivo completo: `../Noteful-RE-backups/Noteful-RE-20260912-190800.tar.gz`.
Incluye Ghidra, entorno de trabajo, muestras, código, ejemplos y evidencia.
4.415 archivos verificados contra el contenido del archivo comprimido;
162.836.122 bytes. SHA-256:
`211a56a1546f865216792978a5603e8de552a10a1607880eb00eeed5bb9c8377`.
El manifiesto se guarda junto a la copia, con sufijo `.tar.manifest.json`.

## Transparencia del subrayador sobre imágenes

El fallo concreto estaba en las formas de tipo 20: el renderer interpretaba
su geometría y color, pero omitía campos del objeto que controlan opacidad y
herramienta. Por eso el subrayado recto amarillo tapaba el texto de la fotografía.

Campos observados en el objeto, fuera del payload:

| Tag | Valor observado | Interpretación contrastada |
|---|---|---|
| 8 | 1.0 | Factor de opacidad del objeto |
| 9 | 0 / 1 | Dibujo normal / subrayador |

El PDF usa `/BM /Multiply` y `/ca 0.5` para rellenos, `/CA 0.5` para contornos.
Se conserva evidencia en `evidence/pdf-blend-states.json`. La forma de subrayado
de página 2 tiene grosor 28 y modo 1, y se coloca encima de una imagen JPEG.

Ahora formas y tinta comparten composición: Multiply con factor 0,5 para modo 1.
Alpha del color y del objeto se respetan. La composición se aplica una sola vez
por objeto/trazo, evitando oscurecer sus segmentos solapados. Se conserva el
orden raw de dibujo, de modo que la foto sirve como fondo real de la mezcla.
El factor de objeto distinto de 1 está probado mediante caso sintético; todas
las formas de esta muestra tienen factor 1. No se infieren otros modos de mezcla.

## Las doce figuras que faltaban

| Tipo raw | Forma | Cantidad nueva | Datos usados |
|---|---|---:|---|
| 3 | Rectángulo redondeado relleno | 1 | Tamaño, radio payload/20, relleno payload/5 |
| 6 | Elipse | 5 | Tamaño, contorno payload/7 |
| 12 | Polígono cerrado | 3 | Coordenadas y comandos payload/13 |
| 21 | Curva cúbica | 3 | Coordenadas y comandos payload/13 |

Comandos observados: 0 = mover (un punto), 1 = línea (un punto), 3 = curva cúbica
(tres puntos), 4 = cerrar (sin coordenadas). Cantidades y consumo se validan;
comandos desconocidos se rechazan explícitamente. No se presupone comando 2.

Transformación: centro, rotación y tamaño colocado; geometría en coordenadas
nativas, escalando también el contorno. Un eje nativo cero es válido para líneas.
La elipse y las curvas se corroboran con comandos del PDF. El rectángulo
amarillo recupera relleno y redondeo. Total del examen: 74/74 objetos representados.
Esto no afirma soporte de todos los tipos posibles del formato.

## El tercer canal contiene radios

En 23 trazos con `flags & 1`, el tercer valor por muestra se almacenaba antes
como `pressure_candidate`. No es presión normalizada: el primer valor coincide
con radio del círculo inicial dibujado en el PDF, tras convertir coordenadas por
factor 11/6. Se añade nombre `radii`; el alias anterior permanece por compatibilidad.

Validación independiente de 23 extremos iniciales:

- Error máximo del centro: 0,000128113 unidades internas.
- Error máximo del radio: 0,000071836 unidades internas.
- Círculos seleccionados por posición y circularidad, sin usar radio candidato
  para seleccionarlos. Evidencia: `evidence/variable-width-validation.json`.

El visor usa ahora radio por muestra, discos y tangentes externas entre discos,
componiendo todo el trazo una vez. Los extremos y el grosor variable quedan
representados. La interpolación entre muestras sigue siendo aproximada; no se
ha reproducido el suavizado exacto de curvas del motor de Noteful.

El primer experimento midió distancia al contorno más cercano y produjo errores
grandes: el lector de evidencia conservaba solo el último subcontorno del relleno
compuesto. Se abandonó esa métrica. Se conserva como experimento fallido en
`evidence/variable-width-outline-experiment.json`; no respalda el renderer.

## Reproducir comprobaciones

`python3 -m unittest discover -s tests -v`: 12 pruebas, sin dependencias externas.
Incluyen las ocho notas, figuras, subrayado encima de imagen, alpha y radios
contrastados con evidencia de círculos del PDF.

`python3 tools/validate_variable_width.py`: regenerar contraste geométrico; requiere
`pypdf` y `numpy` (disponibles en el runtime de desarrollo usado aquí).
`python3 tools/build_examples.py`: regenerar ocho ejemplos y diez SVG.

Pendiente: significado de canales auxiliares/borrado, interpolación exacta de tinta,
otros estilos y tipos de objeto, fondos PDF genéricos y escritura de archivos
modificados validada por importación real en Noteful. Visibilidad y orden entre
múltiples capas requieren corpus controlado; este examen solo tiene una capa.
