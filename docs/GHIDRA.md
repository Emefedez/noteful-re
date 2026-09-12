# Ghidra y Cerberus: estado reproducible

## Entorno

- Ghidra 12.1.2: `/opt/homebrew/Cellar/ghidra/12.1.2/bin/ghidraRun`.
- Skill Cerberus: `/Users/m1-max/.codex/skills/cerberus-re`.
- CLI instalada editable en `work/cerberus-venv/` para conservar acceso a sus scripts.
- Proyecto: `work/ghidra/projects/noteful/noteful.gpr`; programa `Noteful`.
- Binario: `/Applications/Noteful.app/Wrapper/Noteful.app/Noteful`.
- Noteful 1.4.36, build 200; ARM64; image base `0x100000000`.
- SHA-256: `edb8a4d5317b3a9d384a37acaef96c2026b22ac42876b2ca31066e53dfae84e0`.

Puente Python existente detectado:
`/Users/m1-max/Documents/GhidraMCP_Python/bridge_mcp_ghidra.py`, configurado para
`http://127.0.0.1:8089`. La conexión fue rechazada: proceso del puente activo no
equivale a servidor de Ghidra disponible. No hubo herramientas Ghidra callable en
esta sesión. Se utilizó Ghidra headless mediante Cerberus y después scripts locales.

Importación completa, guardada correctamente. Se omitieron reexports Mach-O.
No se modificó ni re-firmó la app; no hubo attach o validación dinámica.

## Hallazgos estáticos

Direcciones virtuales sin ASLR, correspondientes exclusivamente al hash anterior.
Nombres `FUN_...` son los de Ghidra; nombres semánticos de tabla son interpretaciones
apoyadas por campos de clase y operaciones del código.

| Dirección | Interpretación respaldada |
|---|---|
| `0x100991034` | Función que devuelve `0xaabbccde` |
| `0x100adf3d8` | Inicialización de `PackageFileReader`: `toc`, `url`, `handle`; seek al final menos 16, lectura de 16 bytes, comprobación de magic y carga del índice |
| `0x100ae186c` | Helper llamado para decodificar tráiler; usa `0x100ae1678` y callback `0x100ae20dc` |
| `0x100ae197c` | Lectura del índice desde campos; tag 1 como Float, compara límite `1.21` |
| `0x100ae2190` | Inicialización de `PackageFileWriter`: `toc`, `offset`, `footer`; footer magic y escritura inicial de bytes `AA BB CC DE` |

El escritor inicializa el índice con bits Float32 `0x3f9ae148` (≈1.21).
Las muestras usan `0x3f9851ec` (≈1.19). Hay diferencia de versión entre corpus
y app instalada. No confundir versión de paquete con `CFBundleShortVersionString`.

En ARM64 little-endian el escritor carga `0xdeccbbaa` antes de anexar cuatro bytes:
produce `AA BB CC DE` en archivo. Ese detalle no contradice big-endian del contenedor.

Pseudocódigo completo en `evidence/ghidra-targets/*.c`; búsquedas en
`evidence/ghidra-targets/string-targets.json`; instrucciones en
`evidence/magic-instructions.json`. No interpretar registros `unaff_x20`,
`unaff_x21` y variables descompiladas como firmas Swift exactas.

## Puntos concretos para continuar con tinta

| Evidencia | Dirección |
|---|---|
| String `StrokeDecoder.parse` | `0x100c5b130` |
| Referencia de datos a esa string | `0x100f81620` |
| Nombre `StrokeDecoder` | `0x100bc51c3` |
| Referencia relativa al nombre en descriptor | `0x100c9cfcc` |
| Nombre `StrokeEncoder` | `0x100bc51eb` |
| Referencia relativa al nombre en descriptor | `0x100c9d008` |

Ghidra no recuperó llamadas directas a esas strings mediante esta búsqueda.
No se afirma haber descompilado `StrokeDecoder.parse`. Continuación recomendada:
recuperar métodos desde metadatos Swift y confirmar lectura de `F1 01`, contador
en +0x34 y normalización de coordenadas. Tratar prefijo y los 38 bytes siguientes
como opacos hasta corroborarlo.

## Límites del análisis

Mach-O declara `LC_ENCRYPTION_INFO_64`: cryptid=1, cryptoff=0x4000,
cryptsize=0x1000. No se recuperó una imagen descifrada en ejecución. Hubo errores
del descompilador, incluido el área inicial, y excepciones de analizadores.
Los resultados seleccionados están fuera de ese intervalo, pero todas las
inferencias estáticas deben contrastarse antes de afirmar comportamiento runtime.

Importación registra 73 dependencias sin resolver y 52718 nombres que el script
`DemangleAllScript` no pudo demanglear. Muchos son etiquetas/propiedades; ese número
no equivale a 52718 funciones inválidas. Log íntegro en `work/ghidra/logs/noteful/`;
resumen en `evidence/ghidra-import.log`.

## Reproducir

Desde `/Users/m1-max/Documents/Noteful-RE`, para un proyecto nuevo (el importador
usa overwrite: cambiar nombre si interesa conservar el proyecto existente):

```sh
GHIDRA_INSTALL_DIR=/opt/homebrew/opt/ghidra/libexec \
GHIDRA_WORKSPACE=/Users/m1-max/Documents/Noteful-RE/work/ghidra \
work/cerberus-venv/bin/cerberus-re import analyze \
  /Applications/Noteful.app/Wrapper/Noteful.app/Noteful \
  noteful_nueva_importacion --skip-macho-reexports
```

Repetir solamente extracción estática, sin análisis global ni escritura del proyecto:

```sh
JAVA_HOME=/opt/homebrew/opt/openjdk@21/libexec/openjdk.jdk/Contents/Home \
/opt/homebrew/opt/ghidra/libexec/support/analyzeHeadless \
  work/ghidra/projects/noteful noteful -process Noteful -noanalysis -readOnly \
  -scriptPath /Users/m1-max/Documents/Noteful-RE/tools \
  -postScript NotefulTargets.java \
  /Users/m1-max/Documents/Noteful-RE/evidence/ghidra-targets
```

Puede abrirse el `.gpr` en interfaz gráfica de Ghidra cuando no haya operación
headless usando ese proyecto. No es necesario reinstalar Ghidra.
