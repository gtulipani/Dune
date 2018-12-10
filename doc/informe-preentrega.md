# Informe preentrega

Este informe está hecho a partir del commit `87540a1d5`

## Generales

* **Informe**: El informe (el del trabajo, no esta devolución) tiene que estar divido en 3: *informe técnico*, *informe general del proyecto* y *manual de usuario*.
El informe entregado es una mezcla entre el general y el técnico, ampliar un poco el general (describir funcionalidad lograda, faltante, aspectos del tp que quieran resaltar, aspectos que mejorarían si tuvieran más tiempo, etc), y ampliar el técnico, mostrando más la relación entre las clases, como interactúan los distintos objetos entre sí, cómo se sincronizan, etc.

No es necesario usar UML, pueden hacer diagramas más informales para explicar temas más complejos como la sincronización de eventos mediante un diagrama de secuencias, o la comunicación entre aplicaciones mediante diagramas de componentes

El manual de usuario es para el usuario que quiera jugar al juego. Debería explicar cómo se instala, cómo se inicia, cómo crear partidas, cómo se juega, requerimientos, etc.

* **Instalador**: El script está incompleto, no instala los sprites ni otras carpetas.

* Darle un cierre al editor, como para tener algo con qué crear mapas.

### Código compartido

* Agregar comentarios al código

* ¿Es necesario usar move semantics en los eventos?

### Servidor

* Agregar un `-h, --help`

* Atacar un edificio utiliza el 100% de la cpu.

* Cuando las unidades se matan entre sí, termina con segmentation fault.

* Deshardcodear mapa y unidades en initializePlayers. Deshardcodear cantidad de jugadores (para eso está la configuración, debería soportar más de 2 jugadores)

### Cliente

* Strings y picturables pasan por copia

* El cliente inicia y no se renderiza nada en la pantalla, no hay feedback de que está esperando otro jugador.

* ¿No hay renderización hasta que no haya un evento que actualiza el modelo?

* No puedo colocar edificios ni unidades nuevas

* Tarda en responder, le falta fluidez
