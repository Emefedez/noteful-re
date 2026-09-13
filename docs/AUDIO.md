# Audio: preservación y preparación del modelo

El binario analizado contiene `AudioSyncTime`, `beginAudioSync(recording:)`,
`endAudioSync()`, `audioPlayerSyncTimeDidChange`, `AudioRecordingFile` y servicios
AVAudioEngine/AVAudioRecorder. Es coherente con audio sincronizado con escritura,
pero esos nombres no establecen el formato de sus tiempos.

## Implementado

- Recursos identificados por firmas CAF, WAV, M4A/M4B, MP3 con ID3, FLAC y Ogg.
- Los recursos del índice tag 3 cuyo formato no se reconoce se conservan como
  binarios opacos. No se intenta interpretarlos como campos editables.
- Sesión Rust conserva el archivo original entero. `.nfedit` conserva esos bytes,
  incluidos audio, metadatos temporales y canales aún desconocidos.
- API `audio_bytes(id)` y panel web para reproducción independiente/descarga.
  Si el navegador no soporta el codec, queda disponible la descarga.
- No hay un techo fijo de MB para notas/proyectos ni un máximo global de puntos
  importados. Siguen las comprobaciones de offsets, estructura, profundidad y
  presupuestos proporcionales a los bytes de entrada. Memoria y direccionamiento
  de cada plataforma son límites técnicos; el navegador usa WASM32.

`tests/fixtures/audio-synthetic.noteful` añade un WAV generado de 0.25 segundos a
una nota vacía. Sirve para verificar recurso, reproducción y preservación exacta.
**No es una grabación exportada por Noteful ni prueba sincronización.** El navegador
leyó duración 0.25 s, readyState 4, sin error. Una prueba separada abre un recurso
binario de 65 MiB, superior al antiguo límite; no se guarda ese bloque en el repo.

## Pendiente para sincronizar

Se necesita establecer una relación explícita entre ID de grabación, escala de
tiempo del audio, intervalos de trazos y tiempos por muestra cuando existan.
Debe soportar varias grabaciones, pausas, cambios de página, edición y borrado.
No equiparar los relojes uint64 de cambios del documento con segundos de audio.
Tampoco atribuir tiempos al canal auxiliar de tinta sin evidencia.

El renderer futuro podrá filtrar la escena por tiempo usando esa relación;
la velocidad de reproducción y la posición del reproductor pertenecen a la GUI.
Los datos de sincronización originales seguirán separados de los trazos nuevos,
que actualmente no están asociados a una grabación.

Se intentó inspeccionar la app instalada y su biblioteca en modo lectura. macOS
rechazó captura de la app y lectura de su contenedor. No se cambiaron permisos,
no se grabó el micrófono ni se modificó la biblioteca. Hace falta una exportación
real con audio, o acceso concedido por el usuario, para validar esa parte.
