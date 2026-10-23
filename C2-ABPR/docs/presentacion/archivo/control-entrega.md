# Control de entrega — C2 ABPr

Estado revisado el 23 de octubre de 2026. La captura de Teams indica vencimiento el 16 de octubre a las 17:30 y permite varias entregas; no se ha confirmado una prórroga ni una entrega previa.

## 1. Archivos para la exposición

| Uso | Archivo |
|---|---|
| Presentación, 12 páginas principales y 3 anexos | [PDF](presentacion-c2.pdf) · [PowerPoint editable](presentacion-c2.pptx) |
| Reparto y explicación por página | [Guion de exposición](guion-exposicion.pdf) |
| Video del diseño mecánico | [MP4](../video/medidor-animado.mp4) |
| Informe requerido en Markdown | [README del proyecto](../../README.md) |
| Esquemático ampliable | [Medidor](../../hardware/medidor-energia.pdf) · [Banco](../../hardware/banco-pruebas.pdf) |
| Nuevos resultados de simulación | [Xyce y ngspice](../../simulacion/xyce/resultados.txt) |

La diapositiva 8 del PowerPoint incluye el video; también se entrega el MP4 separado para abrirlo desde VLC u otro reproductor.

Duración propuesta: unos 12 minutos, incluido el video. Reparto provisional: David, páginas 1–4; Jose, 5–8; Leo, 9–12. Cada integrante debe poder explicar también las conexiones y cálculos de los otros bloques.

## 2. Cobertura de la rúbrica documental

Fuente: [material del curso, sección 1.1.9.3](https://nemog3762.gitlab.io/material/compiled/Sistemas%20embebidos%201.html), consultado el 23 de octubre de 2026.

| Requisito | Evidencia | Estado |
|---|---|---|
| Título, objetivo general y tres específicos | README, encabezado y sección 2 | Incluidos |
| Problema alineado con el primer avance | Sección 3; cambio de tres a dos pinzas explicado | Incluido; cotejar con la entrega C1 enviada |
| Estado del arte y marco teórico | Secciones 4 y 5, con referencias | Incluidos |
| Introducción y materiales | Secciones 1 y 6 | Incluidos; lista prevista, no inventario comprado |
| Desarrollo técnico y figuras justificables | Sección 7, fuentes KiCad, FreeCAD y Python | Incluido; protección todavía bajo revisión |
| Metodología, cronograma y dificultades | Sección 8 | Incluidos; estado físico pendiente de confirmar |
| Formato y numeración | Títulos, tablas e ilustraciones del README; tipografía uniforme en PDF/PPTX | Revisados automáticamente |
| Entrega por repositorio GitHub/GitLab | Remoto configurado: davixcky/sistemas-embebidos-1 | Carpeta C2-ABPR sin seguimiento al revisar; publicación no acreditada |

## 3. Requisitos físicos que los archivos no pueden acreditar

La rúbrica exige gabinete terminado, placa fabricada y mayormente soldada, ensamble con microcontrolador y prueba de resistencia superada. El README todavía registra compra, gabinete y montaje en curso; las pruebas permanecen pendientes.

- [ ] Confirmar y llevar el gabinete real y el ensamble.
- [ ] Confirmar qué componentes están soldados y cuáles faltan.
- [ ] Resolver con el docente si la placa perforada satisface el requisito de PCB fabricada; no hay autorización documentada.
- [ ] Registrar resultados reales de las pruebas; no llenar la tabla con valores de simulación.
- [ ] Resolver la fijación: el CAD contiene postes, pero la placa perforada no tiene los agujeros M3 libres previstos.
- [ ] Revisar el margen del clamp de entrada antes de cerrar el diseño.

El video muestra geometría del diseño. No demuestra fabricación, encendido, aislamiento, precisión ni ejecución del firmware.

## 4. Revisión técnica que debe mencionarse

La comparación nueva ejecutó 24 casos en cada solver. Los voltajes coinciden dentro de 10 µV, usando los mismos modelos. Los casos nominales funcionan dentro del rango planteado. Con CH2 a 100 A y 15 °C, el modelo predice −0,334 a 3,627 V: el clamp supera los límites usados en el proyecto. El modelo térmico no está validado por fabricante; el hallazgo exige margen y comprobación, no permite afirmar que se observó ese voltaje en una placa real.

La fuente de 4,75 V no cumple el criterio de entrada del regulador. El PTC se representa con resistencia fija: no se ha simulado su disparo. No se ha validado la alimentación simultánea por USB y fuente externa.

## 5. Antes de salir

- [ ] Abrir el PDF y el MP4 en el computador que se usará; llevar una copia local.
- [ ] Ensayar una vez el reparto de tres integrantes. Usar las notas como apoyo, no leerlas completas.
- [ ] Llevar esquemáticos PDF y la lista de materiales para preguntas.
- [ ] Mostrar la plataforma con el rótulo de datos simulados; tener la captura como respaldo.
- [ ] Revisar el enlace remoto después de publicar; un archivo local no constituye una entrega.
- [ ] Confirmar la fecha y el mecanismo de entrega en Teams.

No se han publicado archivos ni enviado mensajes al docente desde esta preparación.
