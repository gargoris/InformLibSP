# DAAD CondActs Reference Manual

## Tabla de Contenidos

### Condiciones (Conditions)
- [Condiciones de LocalizaciÃ³n](#condiciones-de-localizaciÃ³n)
- [Condiciones de Objetos](#condiciones-de-objetos)
- [Condiciones de Flags](#condiciones-de-flags)
- [Condiciones de Sentencia LÃ³gica](#condiciones-de-sentencia-lÃ³gica)
- [Condiciones de Estado](#condiciones-de-estado)
- [Condiciones de InteracciÃ³n](#condiciones-de-interacciÃ³n)

### Acciones (Actions)
- [Acciones de ManipulaciÃ³n de Objetos](#acciones-de-manipulaciÃ³n-de-objetos)
- [Acciones AutomÃ¡ticas de Objetos](#acciones-automÃ¡ticas-de-objetos)
- [Acciones de Flags](#acciones-de-flags)
- [Acciones de Movimiento](#acciones-de-movimiento)
- [Acciones de Pantalla](#acciones-de-pantalla)
- [Acciones de Entrada/Salida](#acciones-de-entrada-salida)
- [Acciones de ImpresiÃ³n](#acciones-de-impresiÃ³n)
- [Acciones de Listas](#acciones-de-listas)
- [Acciones de Guardado](#acciones-de-guardado)
- [Acciones de Control](#acciones-de-control)
- [Acciones de Llamadas](#acciones-de-llamadas)
- [Acciones de GrÃ¡ficos](#acciones-de-grÃ¡ficos)
- [Acciones de FinalizaciÃ³n](#acciones-de-finalizaciÃ³n)

---

## IntroducciÃ³n

DAAD (DiseÃ±ador de Aventuras de Aventuras AD) es un sistema de programaciÃ³n diseÃ±ado especÃ­ficamente para crear aventuras de texto. Este documento contiene una referencia completa de todos los CondActs (Conditions and Actions) disponibles en DAAD, basado en el manual tÃ©cnico original de la versiÃ³n 2.1.

### Conceptos BÃ¡sicos

**ParÃ¡metros comunes:**
- `locno.` = nÃºmero de localizaciÃ³n vÃ¡lido
- `locno+` = nÃºmero de localizaciÃ³n vÃ¡lido o: 252 ("not-created"), 253 ("WORN"), 254 ("CARRIED"), 255 ("HERE")
- `mesno.` = nÃºmero de mensaje vÃ¡lido
- `sysno.` = nÃºmero de mensaje del sistema
- `flagno.` = cualquier flag (0-255)
- `objno.` = nÃºmero de objeto vÃ¡lido
- `value` = valor de 0 a 255
- `word` = palabra del vocabulario o "_" para palabra nula

**IndirecciÃ³n:**
Muchos CondActs permiten indirecciÃ³n en su primer parÃ¡metro usando corchetes `[]`. Por ejemplo, `MESSAGE [100]` imprimirÃ¡ el mensaje cuyo nÃºmero estÃ¡ almacenado en la Flag 100.

---

## Condiciones de LocalizaciÃ³n

### AT (ID: 0) (ID: 0) locno\. (ID: 0)
**DescripciÃ³n:** Verifica si el jugador estÃ¡ en la localizaciÃ³n especificada.
**Uso:** Control de presencia del jugador en ubicaciones especÃ­ficas.
**Ejemplo:**
```
AT 5    ; Â¿El jugador estÃ¡ en la localizaciÃ³n 5?
```

### NOTAT (ID: 1) (ID: 1) locno\. (ID: 1)
**DescripciÃ³n:** Verifica si el jugador NO estÃ¡ en la localizaciÃ³n especificada.
**Uso:** Control negativo de presencia del jugador.
**Ejemplo:**
```
NOTAT 0    ; Â¿El jugador NO estÃ¡ en la localizaciÃ³n 0?
```

### ATGT (ID: 2) locno.
**DescripciÃ³n:** Verifica si la localizaciÃ³n actual es mayor que la especificada.
**Uso:** Control de rangos de localizaciones.
**Ejemplo:**
```
ATGT 10    ; Â¿La localizaciÃ³n actual es mayor que 10?
```

### ATLT (ID: 3) locno.
**DescripciÃ³n:** Verifica si la localizaciÃ³n actual es menor que la especificada.
**Uso:** Control de rangos de localizaciones.
**Ejemplo:**
```
ATLT 20    ; Â¿La localizaciÃ³n actual es menor que 20?
```

---

## Condiciones de Objetos

### PRESENT (ID: 4) objno.
**DescripciÃ³n:** Verifica si el objeto estÃ¡ presente (llevado, vestido o en la localizaciÃ³n actual).
**Uso:** Control general de disponibilidad de objetos.
**Ejemplo:**
```
PRESENT 1    ; Â¿El objeto 1 estÃ¡ presente?
MESSAGE 10   ; "Veo la espada aquÃ­"
```

### ABSENT (ID: 5) objno.
**DescripciÃ³n:** Verifica si el objeto NO estÃ¡ presente.
**Uso:** Control negativo de disponibilidad de objetos.
**Ejemplo:**
```
ABSENT 1     ; Â¿El objeto 1 NO estÃ¡ presente?
MESSAGE 11   ; "No veo la espada por aquÃ­"
```

### WORN (ID: 6) objno.
**DescripciÃ³n:** Verifica si el objeto estÃ¡ siendo vestido.
**Uso:** Control de estado de vestimenta.
**Ejemplo:**
```
WORN 5       ; Â¿El objeto 5 estÃ¡ siendo vestido?
MESSAGE 12   ; "Llevo puesto el casco"
```

### NOTWORN (ID: 7) objno.
**DescripciÃ³n:** Verifica si el objeto NO estÃ¡ siendo vestido.
**Uso:** Control negativo de estado de vestimenta.
**Ejemplo:**
```
NOTWORN 5    ; Â¿El objeto 5 NO estÃ¡ siendo vestido?
MESSAGE 13   ; "No llevo puesto el casco"
```

### CARRIED (ID: 8) objno.
**DescripciÃ³n:** Verifica si el objeto estÃ¡ siendo llevado.
**Uso:** Control de inventario del jugador.
**Ejemplo:**
```
CARRIED 2    ; Â¿El objeto 2 estÃ¡ siendo llevado?
MESSAGE 14   ; "Tengo la llave en mis manos"
```

### NOTCARR (ID: 9) objno.
**DescripciÃ³n:** Verifica si el objeto NO estÃ¡ siendo llevado.
**Uso:** Control negativo de inventario.
**Ejemplo:**
```
NOTCARR 2    ; Â¿El objeto 2 NO estÃ¡ siendo llevado?
MESSAGE 15   ; "No tengo la llave"
```

### ISAT (ID: 55) (ID: 55) objno\. locno+
**DescripciÃ³n:** Verifica si el objeto estÃ¡ en la localizaciÃ³n especificada.
**Uso:** Control de posiciÃ³n especÃ­fica de objetos.
**Ejemplo:**
```
ISAT 3 10    ; Â¿El objeto 3 estÃ¡ en la localizaciÃ³n 10?
MESSAGE 16   ; "El tesoro estÃ¡ en la cueva"
```

### ISNOTAT (ID: 88) (ID: 88) objno\. locno+
**DescripciÃ³n:** Verifica si el objeto NO estÃ¡ en la localizaciÃ³n especificada.
**Uso:** Control negativo de posiciÃ³n de objetos.
**Ejemplo:**
```
ISNOTAT 3 10 ; Â¿El objeto 3 NO estÃ¡ en la localizaciÃ³n 10?
MESSAGE 17   ; "El tesoro no estÃ¡ en la cueva"
```

---

## Condiciones de Flags

### ZERO (ID: 11) flagno.
**DescripciÃ³n:** Verifica si la flag estÃ¡ en cero.
**Uso:** Control de estado inicial o reseteo.
**Ejemplo:**
```
ZERO 30      ; Â¿La flag 30 estÃ¡ en cero?
MESSAGE 18   ; "La puntuaciÃ³n es cero"
```

### NOTZERO (ID: 12) flagno.
**DescripciÃ³n:** Verifica si la flag NO estÃ¡ en cero.
**Uso:** Control de estado activo.
**Ejemplo:**
```
NOTZERO 30   ; Â¿La flag 30 NO estÃ¡ en cero?
PRINT 30     ; Mostrar la puntuaciÃ³n
```

### EQ (ID: 13) (ID: 13) flagno\. value
**DescripciÃ³n:** Verifica si la flag es igual al valor especificado.
**Uso:** Control de valor especÃ­fico.
**Ejemplo:**
```
EQ 30 100    ; Â¿La flag 30 es igual a 100?
MESSAGE 19   ; "Â¡PuntuaciÃ³n perfecta!"
```

### NOTEQ (ID: 79) (ID: 79) flagno\. value
**DescripciÃ³n:** Verifica si la flag NO es igual al valor especificado.
**Uso:** Control de valor diferente.
**Ejemplo:**
```
NOTEQ 30 0   ; Â¿La flag 30 NO es igual a 0?
MESSAGE 20   ; "Tienes algunos puntos"
```

### GT (ID: 14) (ID: 14) flagno\. value
**DescripciÃ³n:** Verifica si la flag es mayor que el valor especificado.
**Uso:** Control de umbral superior.
**Ejemplo:**
```
GT 30 50     ; Â¿La flag 30 es mayor que 50?
MESSAGE 21   ; "Â¡Buen progreso!"
```

### LT (ID: 15) (ID: 15) flagno\. value
**DescripciÃ³n:** Verifica si la flag es menor que el valor especificado.
**Uso:** Control de umbral inferior.
**Ejemplo:**
```
LT 1 4       ; Â¿Llevas menos de 4 objetos?
MESSAGE 22   ; "Puedes llevar mÃ¡s cosas"
```

### SAME (ID: 76) flagno1 flagno2
**DescripciÃ³n:** Verifica si dos flags tienen el mismo valor.
**Uso:** ComparaciÃ³n entre flags.
**Ejemplo:**
```
SAME 30 31   ; Â¿Las flags 30 y 31 tienen el mismo valor?
MESSAGE 23   ; "Los valores coinciden"
```

### NOTSAME (ID: 80) flagno1 flagno2
**DescripciÃ³n:** Verifica si dos flags NO tienen el mismo valor.
**Uso:** ComparaciÃ³n negativa entre flags.
**Ejemplo:**
```
NOTSAME 30 31 ; Â¿Las flags 30 y 31 NO tienen el mismo valor?
MESSAGE 24    ; "Los valores son diferentes"
```

### BIGGER (ID: 112) flagno1 flagno2
**DescripciÃ³n:** Verifica si la primera flag es mayor que la segunda.
**Uso:** ComparaciÃ³n de magnitud entre flags.
**Ejemplo:**
```
BIGGER 30 31  ; Â¿La flag 30 es mayor que la flag 31?
MESSAGE 25    ; "El primer valor es mayor"
```

### SMALLER (ID: 113) flagno1 flagno2
**DescripciÃ³n:** Verifica si la primera flag es menor que la segunda.
**Uso:** ComparaciÃ³n de magnitud inversa entre flags.
**Ejemplo:**
```
SMALLER 30 31 ; Â¿La flag 30 es menor que la flag 31?
MESSAGE 26    ; "El primer valor es menor"
```

---

## Condiciones de Sentencia LÃ³gica

### ADJECT1 (ID: 16) word
**DescripciÃ³n:** Verifica si el primer adjetivo de la sentencia lÃ³gica es la palabra especificada.
**Uso:** Control de modificadores especÃ­ficos.
**Ejemplo:**
```
ADJECT1 ROJA  ; Â¿El primer adjetivo es "ROJA"?
MESSAGE 27    ; "Te refieres a la pelota roja"
```

### ADVERB (ID: 17) word
**DescripciÃ³n:** Verifica si el adverbio de la sentencia lÃ³gica es la palabra especificada.
**Uso:** Control de modificadores de acciÃ³n.
**Ejemplo:**
```
ADVERB RAPIDAMENTE ; Â¿El adverbio es "RAPIDAMENTE"?
MESSAGE 28         ; "Lo haces con prisa"
```

### PREP (ID: 68) word
**DescripciÃ³n:** Verifica si la preposiciÃ³n de la sentencia lÃ³gica es la palabra especificada.
**Uso:** Control de relaciones espaciales o de acciÃ³n.
**Ejemplo:**
```
PREP CON     ; Â¿La preposiciÃ³n es "CON"?
MESSAGE 29   ; "Necesitas especificar con quÃ©"
```

### NOUN2 (ID: 69) word
**DescripciÃ³n:** Verifica si el segundo sustantivo de la sentencia lÃ³gica es la palabra especificada.
**Uso:** Control de objeto indirecto.
**Ejemplo:**
```
NOUN2 CAJA   ; Â¿El segundo sustantivo es "CAJA"?
MESSAGE 30   ; "Lo pones en la caja"
```

### ADJECT2 (ID: 70) word
**DescripciÃ³n:** Verifica si el segundo adjetivo de la sentencia lÃ³gica es la palabra especificada.
**Uso:** Control de modificadores del objeto indirecto.
**Ejemplo:**
```
ADJECT2 GRANDE ; Â¿El segundo adjetivo es "GRANDE"?
MESSAGE 31     ; "Te refieres a la caja grande"
```

---

## Condiciones de Estado

### CHANCE (ID: 10) percent
**DescripciÃ³n:** CondiciÃ³n aleatoria que se cumple con el porcentaje especificado.
**Uso:** Eventos aleatorios y variabilidad en el juego.
**Ejemplo:**
```
CHANCE 30    ; 30% de probabilidad
MESSAGE 32   ; "Â¡Un rayo ilumina el cielo!"
```

### ISDONE
**DescripciÃ³n:** Verifica si la Ãºltima tabla procesada terminÃ³ ejecutando al menos una acciÃ³n.
**Uso:** Control de Ã©xito/fallo de subprocesos.
**Ejemplo:**
```
PROCESS 5    ; Llamar subproceso
ISDONE       ; Â¿El subproceso tuvo Ã©xito?
MESSAGE 33   ; "La acciÃ³n se completÃ³"
```

### ISNDONE
**DescripciÃ³n:** Verifica si la Ãºltima tabla procesada terminÃ³ sin hacer nada o con NOTDONE.
**Uso:** Control de fallo de subprocesos.
**Ejemplo:**
```
PROCESS 5    ; Llamar subproceso
ISNDONE      ; Â¿El subproceso fallÃ³?
MESSAGE 34   ; "La acciÃ³n no se pudo completar"
```

### HASAT (ID: 58) value
**DescripciÃ³n:** Verifica si el atributo especificado estÃ¡ activado.
**Uso:** Control de atributos de objetos y sistema.
**Ejemplo:**
```
HASAT WEARABLE ; Â¿El objeto actual es vestible?
MESSAGE 35     ; "Puedes vestirte con esto"
```

### HASNAT (ID: 59) value
**DescripciÃ³n:** Verifica si el atributo especificado NO estÃ¡ activado.
**Uso:** Control negativo de atributos.
**Ejemplo:**
```
HASNAT CONTAINER ; Â¿El objeto actual NO es contenedor?
MESSAGE 36       ; "No puedes meter cosas ahÃ­"
```

---

## Condiciones de InteracciÃ³n

### INKEY
**DescripciÃ³n:** Verifica si el jugador estÃ¡ presionando una tecla.
**Uso:** Control de entrada directa del teclado.
**Ejemplo:**
```
INKEY        ; Â¿Se estÃ¡ presionando una tecla?
MESSAGE 37   ; "Tecla presionada"
```

### QUIT
**DescripciÃ³n:** Pregunta al jugador si estÃ¡ seguro de querer salir.
**Uso:** ConfirmaciÃ³n de salida del juego.
**Ejemplo:**
```
QUIT         ; Â¿EstÃ¡ seguro de salir?
END          ; Salir del juego
```

---

## Acciones de ManipulaciÃ³n de Objetos

### GET (ID: 40) objno.
**DescripciÃ³n:** Intenta tomar el objeto especificado.
**Uso:** Recoger objetos del entorno.
**Comportamiento:** Verifica peso, lÃ­mites de objetos, disponibilidad.
**Ejemplo:**
```
GET 1        ; Tomar objeto 1
DONE         ; Terminar entrada
```

### DROP (ID: 41) objno.
**DescripciÃ³n:** Intenta soltar el objeto especificado.
**Uso:** Dejar objetos en la localizaciÃ³n actual.
**Comportamiento:** Verifica si se tiene el objeto, si estÃ¡ vestido.
**Ejemplo:**
```
DROP 1       ; Soltar objeto 1
DONE         ; Terminar entrada
```

### WEAR (ID: 42) objno.
**DescripciÃ³n:** Intenta vestir el objeto especificado.
**Uso:** Ponerse objetos vestibles.
**Comportamiento:** Verifica si es vestible, si se lleva.
**Ejemplo:**
```
WEAR 5       ; Vestir objeto 5 (casco)
DONE         ; Terminar entrada
```

### REMOVE (ID: 39) objno.
**DescripciÃ³n:** Intenta quitar el objeto especificado.
**Uso:** Quitarse objetos vestidos.
**Comportamiento:** Verifica si estÃ¡ vestido, lÃ­mites de objetos.
**Ejemplo:**
```
REMOVE 5     ; Quitar objeto 5
DONE         ; Terminar entrada
```

### CREATE (ID: 44) objno.
**DescripciÃ³n:** Crea el objeto en la localizaciÃ³n actual.
**Uso:** Hacer aparecer objetos dinÃ¡micamente.
**Comportamiento:** Coloca el objeto en la localizaciÃ³n actual.
**Ejemplo:**
```
CREATE 10    ; Crear objeto 10 aquÃ­
MESSAGE 38   ; "Â¡Aparece un objeto mÃ¡gico!"
```

### DESTROY (ID: 43) objno.
**DescripciÃ³n:** Destruye el objeto (lo hace desaparecer).
**Uso:** Eliminar objetos del juego.
**Comportamiento:** Marca el objeto como no creado.
**Ejemplo:**
```
DESTROY 10   ; Destruir objeto 10
MESSAGE 39   ; "El objeto se desvanece"
```

### SWAP (ID: 45) objno1 objno2
**DescripciÃ³n:** Intercambia las posiciones de dos objetos.
**Uso:** Intercambio de posiciones de objetos.
**Comportamiento:** Los objetos intercambian ubicaciones.
**Ejemplo:**
```
SWAP 1 2     ; Intercambiar posiciones de objetos 1 y 2
MESSAGE 40   ; "Los objetos cambian de lugar"
```

### PLACE (ID: 46) (ID: 46) objno\. locno+
**DescripciÃ³n:** Coloca el objeto en la localizaciÃ³n especificada.
**Uso:** Mover objetos a ubicaciones especÃ­ficas.
**Comportamiento:** Ajusta contadores de objetos llevados.
**Ejemplo:**
```
PLACE 1 5    ; Colocar objeto 1 en localizaciÃ³n 5
MESSAGE 41   ; "El objeto aparece en la cueva"
```

### PUTO (ID: 102) locno+
**DescripciÃ³n:** Coloca el objeto actual en la localizaciÃ³n especificada.
**Uso:** Mover el objeto referenciado actualmente.
**Comportamiento:** Usa el objeto en flag 51.
**Ejemplo:**
```
PUTO 254     ; Colocar objeto actual en inventario (CARRIED)
MESSAGE 42   ; "Ahora lo llevas"
```

### PUTIN (ID: 90) (ID: 90) objno\. locno.
**DescripciÃ³n:** Intenta meter el objeto en el contenedor especificado.
**Uso:** Almacenar objetos en contenedores.
**Comportamiento:** Verifica si se tiene el objeto, si estÃ¡ vestido.
**Ejemplo:**
```
PUTIN 1 10   ; Meter objeto 1 en contenedor 10
MESSAGE 43   ; "Lo metes en la caja"
```

### TAKEOUT (ID: 91) (ID: 91) objno\. locno.
**DescripciÃ³n:** Intenta sacar el objeto del contenedor especificado.
**Uso:** Extraer objetos de contenedores.
**Comportamiento:** Verifica lÃ­mites de peso y cantidad.
**Ejemplo:**
```
TAKEOUT 1 10 ; Sacar objeto 1 del contenedor 10
MESSAGE 44   ; "Lo sacas de la caja"
```

### DROPALL
**DescripciÃ³n:** Suelta todos los objetos llevados y vestidos.
**Uso:** Soltar todo el inventario de una vez.
**Comportamiento:** Coloca todos los objetos en la localizaciÃ³n actual.
**Ejemplo:**
```
DROPALL      ; Soltar todo
MESSAGE 45   ; "Sueltas todo lo que llevas"
```

### COPYOO (ID: 121) objno1 objno2
**DescripciÃ³n:** Copia la posiciÃ³n del primer objeto al segundo.
**Uso:** Sincronizar posiciones de objetos.
**Comportamiento:** El segundo objeto va donde estÃ¡ el primero.
**Ejemplo:**
```
COPYOO 1 2   ; Copiar posiciÃ³n del objeto 1 al 2
MESSAGE 46   ; "Los objetos se reÃºnen"
```

### RESET
**DescripciÃ³n:** Coloca todos los objetos en sus posiciones iniciales.
**Uso:** Reiniciar estado de objetos.
**Comportamiento:** Restaura el estado inicial de todos los objetos.
**Ejemplo:**
```
RESET        ; Reiniciar posiciones de objetos
MESSAGE 47   ; "Todo vuelve a su lugar original"
```

---

## Acciones AutomÃ¡ticas de Objetos

### AUTOG
**DescripciÃ³n:** VersiÃ³n automÃ¡tica de GET. Busca el objeto por nombre.
**Uso:** Tomar objetos por nombre del vocabulario.
**Comportamiento:** Busca el objeto por prioridad: aquÃ­, llevado, vestido.
**Ejemplo:**
```
COGER ESPADA
AUTOG        ; Tomar la espada automÃ¡ticamente
DONE
```

### AUTOD
**DescripciÃ³n:** VersiÃ³n automÃ¡tica de DROP. Busca el objeto por nombre.
**Uso:** Soltar objetos por nombre del vocabulario.
**Comportamiento:** Busca el objeto por prioridad: llevado, vestido, aquÃ­.
**Ejemplo:**
```
SOLTAR ESPADA
AUTOD        ; Soltar la espada automÃ¡ticamente
DONE
```

### AUTOW
**DescripciÃ³n:** VersiÃ³n automÃ¡tica de WEAR. Busca el objeto por nombre.
**Uso:** Vestir objetos por nombre del vocabulario.
**Comportamiento:** Busca el objeto por prioridad: llevado, vestido, aquÃ­.
**Ejemplo:**
```
VESTIR CASCO
AUTOW        ; Vestir el casco automÃ¡ticamente
DONE
```

### AUTOR
**DescripciÃ³n:** VersiÃ³n automÃ¡tica de REMOVE. Busca el objeto por nombre.
**Uso:** Quitar objetos por nombre del vocabulario.
**Comportamiento:** Busca el objeto por prioridad: vestido, llevado, aquÃ­.
**Ejemplo:**
```
QUITAR CASCO
AUTOR        ; Quitar el casco automÃ¡ticamente
DONE
```

### AUTOP (ID: 104) locno.
**DescripciÃ³n:** VersiÃ³n automÃ¡tica de PUTIN. Busca el objeto por nombre.
**Uso:** Meter objetos en contenedores por nombre.
**Comportamiento:** Busca el objeto por prioridad: llevado, vestido, aquÃ­.
**Ejemplo:**
```
METER LLAVE CAJA
AUTOP 10     ; Meter la llave en la caja (objeto 10)
DONE
```

### AUTOT (ID: 105) locno.
**DescripciÃ³n:** VersiÃ³n automÃ¡tica de TAKEOUT. Busca el objeto por nombre.
**Uso:** Sacar objetos de contenedores por nombre.
**Comportamiento:** Busca en el contenedor primero.
**Ejemplo:**
```
SACAR LLAVE CAJA
AUTOT 10     ; Sacar la llave de la caja (objeto 10)
DONE
```

### COPYOF (ID: 119) (ID: 119) objno\. flagno.
**DescripciÃ³n:** Copia la posiciÃ³n del objeto a una flag.
**Uso:** Guardar posiciÃ³n de objeto para procesamiento.
**Comportamiento:** La flag recibe la localizaciÃ³n del objeto.
**Ejemplo:**
```
COPYOF 1 100 ; Copiar posiciÃ³n del objeto 1 a flag 100
PRINT 100    ; Mostrar la posiciÃ³n
```

### COPYFO (ID: 123) (ID: 123) flagno\. objno.
**DescripciÃ³n:** Copia el valor de una flag a la posiciÃ³n del objeto.
**Uso:** Mover objeto a posiciÃ³n calculada.
**Comportamiento:** El objeto va a la localizaciÃ³n indicada en la flag.
**Ejemplo:**
```
COPYFO 100 1 ; Mover objeto 1 a posiciÃ³n almacenada en flag 100
MESSAGE 48   ; "El objeto se mueve"
```

### WHATO
**DescripciÃ³n:** Busca el objeto por nombre y lo hace el objeto actual.
**Uso:** Identificar objeto por nombre para acciones posteriores.
**Comportamiento:** Establece el objeto en las flags 51, 54-57.
**Ejemplo:**
```
WHATO        ; Identificar objeto por nombre
PRINT 51     ; Mostrar nÃºmero del objeto identificado
```

### SETCO (ID: 56) objno.
**DescripciÃ³n:** Establece el objeto actual.
**Uso:** Cambiar el objeto de referencia.
**Comportamiento:** Establece el objeto en las flags correspondientes.
**Ejemplo:**
```
SETCO 5      ; Establecer objeto 5 como actual
MESSAGE 49   ; "Ahora trabajas con el casco"
```

### WEIGH (ID: 89) (ID: 89) objno\. flagno.
**DescripciÃ³n:** Calcula el peso total del objeto y lo guarda en una flag.
**Uso:** Determinar peso de objetos y contenedores.
**Comportamiento:** Incluye peso de contenidos si es contenedor.
**Ejemplo:**
```
WEIGH 10 100 ; Calcular peso del objeto 10 y guardarlo en flag 100
PRINT 100    ; Mostrar el peso
```

---

## Acciones de Flags

### SET (ID: 47) flagno.
**DescripciÃ³n:** Establece la flag al valor mÃ¡ximo (255).
**Uso:** Activar flags booleanas.
**Comportamiento:** Flag = 255.
**Ejemplo:**
```
SET 100      ; Activar flag 100
MESSAGE 50   ; "FunciÃ³n activada"
```

### CLEAR (ID: 48) flagno.
**DescripciÃ³n:** Establece la flag a cero.
**Uso:** Desactivar flags o reiniciar valores.
**Comportamiento:** Flag = 0.
**Ejemplo:**
```
CLEAR 100    ; Desactivar flag 100
MESSAGE 51   ; "FunciÃ³n desactivada"
```

### LET (ID: 51) (ID: 51) flagno\. value
**DescripciÃ³n:** Establece la flag al valor especificado.
**Uso:** Asignar valores especÃ­ficos a flags.
**Comportamiento:** Flag = value.
**Ejemplo:**
```
LET 30 100   ; Establecer puntuaciÃ³n a 100
MESSAGE 52   ; "Â¡PuntuaciÃ³n mÃ¡xima!"
```

### PLUS (ID: 49) (ID: 49) flagno\. value
**DescripciÃ³n:** Suma el valor a la flag.
**Uso:** Incrementar valores de flags.
**Comportamiento:** Flag = Flag + value (mÃ¡ximo 255).
**Ejemplo:**
```
PLUS 30 10   ; Sumar 10 puntos
MESSAGE 53   ; "Â¡Ganas 10 puntos!"
```

### MINUS (ID: 50) (ID: 50) flagno\. value
**DescripciÃ³n:** Resta el valor de la flag.
**Uso:** Decrementar valores de flags.
**Comportamiento:** Flag = Flag - value (mÃ­nimo 0).
**Ejemplo:**
```
MINUS 30 5   ; Restar 5 puntos
MESSAGE 54   ; "Pierdes 5 puntos"
```

### ADD (ID: 71) flagno1 flagno2
**DescripciÃ³n:** Suma el valor de la primera flag a la segunda.
**Uso:** Operaciones aritmÃ©ticas entre flags.
**Comportamiento:** Flag2 = Flag2 + Flag1 (mÃ¡ximo 255).
**Ejemplo:**
```
ADD 31 30    ; Sumar flag 31 a flag 30
MESSAGE 55   ; "Valores combinados"
```

### SUB (ID: 72) flagno1 flagno2
**DescripciÃ³n:** Resta el valor de la primera flag de la segunda.
**Uso:** Operaciones aritmÃ©ticas entre flags.
**Comportamiento:** Flag2 = Flag2 - Flag1 (mÃ­nimo 0).
**Ejemplo:**
```
SUB 31 30    ; Restar flag 31 de flag 30
MESSAGE 56   ; "Valores restados"
```

### COPYFF (ID: 125) flagno1 flagno2
**DescripciÃ³n:** Copia el valor de la primera flag a la segunda.
**Uso:** Duplicar valores de flags.
**Comportamiento:** Flag2 = Flag1.
**Ejemplo:**
```
COPYFF 30 31 ; Copiar puntuaciÃ³n a respaldo
MESSAGE 57   ; "PuntuaciÃ³n guardada"
```

### COPYBF (ID: 126) flagno1 flagno2
**DescripciÃ³n:** Copia el valor de la segunda flag a la primera.
**Uso:** Copia inversa para usar con indirecciÃ³n.
**Comportamiento:** Flag1 = Flag2.
**Ejemplo:**
```
COPYBF 30 31 ; Copiar de flag 31 a flag 30
MESSAGE 58   ; "Valor restaurado"
```

### RANDOM (ID: 95) flagno.
**DescripciÃ³n:** Genera un nÃºmero aleatorio (1-100) en la flag.
**Uso:** Generar valores aleatorios para decisiones.
**Comportamiento:** Flag = random(1, 100).
**Ejemplo:**
```
RANDOM 100   ; Generar nÃºmero aleatorio
GT 100 50    ; Â¿Mayor que 50?
MESSAGE 59   ; "Â¡Tienes suerte!"
```

### MOVE (ID: 106) flagno.
**DescripciÃ³n:** Usa el verbo actual para mover desde la localizaciÃ³n en la flag.
**Uso:** Movimiento de PSIs o jugador programÃ¡tico.
**Comportamiento:** Consulta tabla de conexiones.
**Ejemplo:**
```
MOVE 38      ; Intentar mover jugador
MESSAGE 60   ; "Te mueves"
```

---

## Acciones de Movimiento

### GOTO (ID: 37) locno.
**DescripciÃ³n:** Mueve el jugador a la localizaciÃ³n especificada.
**Uso:** Teletransporte o movimiento directo.
**Comportamiento:** Establece flag 38 al valor de localizaciÃ³n.
**Ejemplo:**
```
GOTO 10      ; Ir a localizaciÃ³n 10
DESC 10      ; Describir nueva localizaciÃ³n
```

### WEIGHT (ID: 94) flagno.
**DescripciÃ³n:** Calcula el peso total de objetos llevados y vestidos.
**Uso:** Control de lÃ­mites de peso.
**Comportamiento:** Incluye peso de contenidos de contenedores.
**Ejemplo:**
```
WEIGHT 100   ; Calcular peso llevado
GT 100 50    ; Â¿Peso mayor que 50?
MESSAGE 61   ; "Llevas demasiado peso"
```

### ABILITY (ID: 93) value1 value2
**DescripciÃ³n:** Establece lÃ­mites de objetos y peso del jugador.
**Uso:** Configurar capacidades del jugador.
**Comportamiento:** Flag 37 = value1, Flag 52 = value2.
**Ejemplo:**
```
ABILITY 6 75 ; MÃ¡ximo 6 objetos, peso 75
MESSAGE 62   ; "Te sientes mÃ¡s fuerte"
```

---

## Acciones de Pantalla

### MODE (ID: 81) option
**DescripciÃ³n:** Cambia el modo de operaciÃ³n de la ventana actual.
**Uso:** Control de visualizaciÃ³n de texto.
**Comportamiento:** Opciones: 1=conjunto superior, 2=sin "More...".
**Ejemplo:**
```
MODE 3       ; Conjunto superior + sin "More..."
MESSAGE 63   ; "Modo especial activado"
```

### INPUT (ID: 96) stream option
**DescripciÃ³n:** Establece el flujo de entrada y opciones.
**Uso:** Control de entrada de texto.
**Comportamiento:** Opciones: 1=limpiar, 2=reimprimir, 4=recordar.
**Ejemplo:**
```
INPUT 0 1    ; Entrada del flujo actual, limpiar despuÃ©s
MESSAGE 64   ; "Entrada configurada"
```

### TIME (ID: 83) duration option
**DescripciÃ³n:** Establece timeout para entrada de texto.
**Uso:** Control de tiempo lÃ­mite.
**Comportamiento:** DuraciÃ³n en segundos, opciones para diferentes situaciones.
**Ejemplo:**
```
TIME 30 7    ; 30 segundos, todas las situaciones
MESSAGE 65   ; "Tiempo lÃ­mite establecido"
```

### WINDOW (ID: 78) window
**DescripciÃ³n:** Selecciona la ventana activa (0-7).
**Uso:** Control de ventanas mÃºltiples.
**Comportamiento:** Cambia flujo de salida.
**Ejemplo:**
```
WINDOW 1     ; Cambiar a ventana 1
MESSAGE 66   ; "Mensaje en ventana 1"
```

### WINAT (ID: 82) line col
**DescripciÃ³n:** Posiciona la ventana actual en lÃ­nea y columna.
**Uso:** Control de posicionamiento de ventanas.
**Comportamiento:** Ajusta posiciÃ³n con recorte.
**Ejemplo:**
```
WINAT 5 10   ; Posicionar ventana en lÃ­nea 5, columna 10
MESSAGE 67   ; "Ventana reposicionada"
```

### WINSIZE (ID: 107) height width
**DescripciÃ³n:** Establece el tamaÃ±o de la ventana actual.
**Uso:** Control de dimensiones de ventanas.
**Comportamiento:** Ajusta tamaÃ±o con recorte.
**Ejemplo:**
```
WINSIZE 10 40 ; Ventana de 10 lÃ­neas por 40 columnas
MESSAGE 68    ; "Ventana redimensionada"
```

### CENTRE
**DescripciÃ³n:** Centra la ventana actual para el ancho de pantalla.
**Uso:** AlineaciÃ³n automÃ¡tica de ventanas.
**Comportamiento:** Solo afecta posiciÃ³n horizontal.
**Ejemplo:**
```
CENTRE       ; Centrar ventana
MESSAGE 69   ; "Ventana centrada"
```

### CLS
**DescripciÃ³n:** Limpia la ventana actual.
**Uso:** Limpiar pantalla o ventana especÃ­fica.
**Comportamiento:** Borra contenido de ventana.
**Ejemplo:**
```
CLS          ; Limpiar ventana
MESSAGE 70   ; "Pantalla limpia"
```

### SAVEAT
**DescripciÃ³n:** Guarda la posiciÃ³n actual de impresiÃ³n.
**Uso:** Mantener posiciÃ³n para restaurar despuÃ©s.
**Comportamiento:** Guarda posiciÃ³n en pila interna.
**Ejemplo:**
```
SAVEAT       ; Guardar posiciÃ³n
WINDOW 2     ; Cambiar a otra ventana
MESSAGE 71   ; "Mensaje temporal"
BACKAT       ; Restaurar posiciÃ³n
```

### BACKAT
**DescripciÃ³n:** Restaura la posiciÃ³n de impresiÃ³n guardada.
**Uso:** Volver a posiciÃ³n anterior.
**Comportamiento:** Restaura posiciÃ³n desde pila.
**Ejemplo:**
```
BACKAT       ; Restaurar posiciÃ³n
MESSAGE 72   ; "De vuelta a la posiciÃ³n original"
```

### PAPER (ID: 65) colour
**DescripciÃ³n:** Establece el color de fondo.
**Uso:** Control de colores de fondo.
**Comportamiento:** Usa tabla de colores especÃ­fica de mÃ¡quina.
**Ejemplo:**
```
PAPER 4      ; Color de fondo 4
MESSAGE 73   ; "Fondo cambiado"
```

### INK (ID: 66) colour
**DescripciÃ³n:** Establece el color de tinta (texto).
**Uso:** Control de colores de texto.
**Comportamiento:** Usa tabla de colores especÃ­fica de mÃ¡quina.
**Ejemplo:**
```
INK 2        ; Color de tinta 2
MESSAGE 74   ; "Texto en color"
```

### BORDER (ID: 67) colour
**DescripciÃ³n:** Establece el color del borde de pantalla.
**Uso:** Control de borde de pantalla.
**Comportamiento:** EspecÃ­fico de mÃ¡quina.
**Ejemplo:**
```
BORDER 1     ; Borde color 1
MESSAGE 75   ; "Borde cambiado"
```

### BEEP (ID: 64) value1 value2
**DescripciÃ³n:** Produce un sonido o pitido.
**Uso:** Efectos sonoros simples.
**Comportamiento:** Genera audio usando altavoz del sistema. Los parÃ¡metros controlan frecuencia y duraciÃ³n (especÃ­fico de mÃ¡quina).
**Ejemplo:**
```
BEEP 100 50  ; Pitido con frecuencia 100, duraciÃ³n 50
MESSAGE 76   ; "Â¡Sonido emitido!"
```

### PRINTAT (ID: 99) line col
**DescripciÃ³n:** Establece la posiciÃ³n de impresiÃ³n en la ventana.
**Uso:** Control de posiciÃ³n de cursor.
**Comportamiento:** Si estÃ¡ fuera de ventana, va a esquina superior izquierda.
**Ejemplo:**
```
PRINTAT 5 10 ; PosiciÃ³n lÃ­nea 5, columna 10
MESSAGE 76   ; "Mensaje en posiciÃ³n especÃ­fica"
```

### TAB (ID: 118) col
**DescripciÃ³n:** Mueve el cursor a la columna especificada.
**Uso:** AlineaciÃ³n horizontal de texto.
**Comportamiento:** En la lÃ­nea actual.
**Ejemplo:**
```
TAB 20       ; Ir a columna 20
MESSAGE 77   ; "Texto tabulado"
```

### SPACE
**DescripciÃ³n:** Imprime un espacio.
**Uso:** Espaciado manual de texto.
**Comportamiento:** MÃ¡s corto que un mensaje con espacio.
**Ejemplo:**
```
MESSAGE 78   ; "Palabra"
SPACE        ; Espacio
MESSAGE 79   ; "Otra palabra"
```

### NEWLINE
**DescripciÃ³n:** Imprime retorno de carro y avance de lÃ­nea.
**Uso:** Salto de lÃ­nea manual.
**Comportamiento:** Nueva lÃ­nea.
**Ejemplo:**
```
MESSAGE 80   ; "Primera lÃ­nea"
NEWLINE      ; Nueva lÃ­nea
MESSAGE 81   ; "Segunda lÃ­nea"
```

---

## Acciones de Entrada/Salida

### MES (ID: 77) mesno.
**DescripciÃ³n:** Imprime el mensaje especificado.
**Uso:** Mostrar texto sin salto de lÃ­nea.
**Comportamiento:** Solo imprime el mensaje.
**Ejemplo:**
```
MES 10       ; Imprimir mensaje 10
SPACE        ; Espacio
MES 11       ; Imprimir mensaje 11
```

### MESSAGE (ID: 38) mesno.
**DescripciÃ³n:** Imprime el mensaje especificado y salta de lÃ­nea.
**Uso:** Mostrar texto con salto de lÃ­nea.
**Comportamiento:** Imprime mensaje + NEWLINE.
**Ejemplo:**
```
MESSAGE 82   ; "Â¡Hola mundo!"
MESSAGE 83   ; "Segunda lÃ­nea"
```

### SYSMESS (ID: 54) sysno.
**DescripciÃ³n:** Imprime el mensaje del sistema especificado.
**Uso:** Mostrar mensajes estÃ¡ndar del sistema.
**Comportamiento:** Mensajes predefinidos del intÃ©rprete.
**Ejemplo:**
```
SYSMESS 8    ; "No puedo hacer eso"
DONE
```

### DESC (ID: 19) locno.
**DescripciÃ³n:** Imprime la descripciÃ³n de la localizaciÃ³n sin salto de lÃ­nea.
**Uso:** Mostrar texto de localizaciÃ³n.
**Comportamiento:** Solo el texto descriptivo.
**Ejemplo:**
```
DESC 38      ; Describir localizaciÃ³n actual
NEWLINE      ; Saltar lÃ­nea
LISTOBJ      ; Listar objetos presentes
```

---

## Acciones de ImpresiÃ³n

### PRINT (ID: 53) flagno.
**DescripciÃ³n:** Imprime el valor decimal de la flag.
**Uso:** Mostrar valores numÃ©ricos.
**Comportamiento:** Sin espacios adicionales.
**Ejemplo:**
```
MES 84       ; "PuntuaciÃ³n: "
PRINT 30     ; Mostrar valor de flag 30
MESSAGE 85   ; " puntos"
```

### DPRINT (ID: 27) flagno.
**DescripciÃ³n:** Imprime un nÃºmero de dos bytes (flag y flag+1).
**Uso:** Mostrar valores grandes (0-65535).
**Comportamiento:** (flag+1) * 256 + flag.
**Ejemplo:**
```
MES 86       ; "Valor grande: "
DPRINT 100   ; Mostrar valor de flags 100-101
NEWLINE
```

---

## Acciones de Listas

### LISTOBJ
**DescripciÃ³n:** Lista los objetos presentes en la localizaciÃ³n actual.
**Uso:** Mostrar objetos disponibles.
**Comportamiento:** Si hay objetos, imprime SM1 + lista.
**Ejemplo:**
```
DESC 38      ; Describir localizaciÃ³n
LISTOBJ      ; Listar objetos presentes
```

### LISTAT (ID: 74) locno+
**DescripciÃ³n:** Lista los objetos en la localizaciÃ³n especificada.
**Uso:** Mostrar contenido de contenedores o localizaciones.
**Comportamiento:** Si no hay objetos, imprime SM53 ("nothing").
**Ejemplo:**
```
MES 87       ; "En la caja hay: "
LISTAT 10    ; Listar objetos en contenedor 10
```

---

## Acciones de Guardado

### SAVE (ID: 25) opt
**DescripciÃ³n:** Guarda el estado actual del juego.
**Uso:** Sistema de guardado.
**Comportamiento:** opt: 0=normal, 1=cinta, 2=disco.
**Ejemplo:**
```
SAVE 2       ; Guardar en disco
MESSAGE 88   ; "Juego guardado"
```

### LOAD (ID: 26) opt
**DescripciÃ³n:** Carga un estado guardado del juego.
**Uso:** Sistema de carga.
**Comportamiento:** opt: 0=normal, 1=cinta, 2=disco.
**Ejemplo:**
```
LOAD 2       ; Cargar desde disco
MESSAGE 89   ; "Juego cargado"
```

### RAMSAVE
**DescripciÃ³n:** Guarda el estado del juego en memoria.
**Uso:** Guardado temporal en RAM.
**Comportamiento:** VolÃ¡til, se pierde al apagar.
**Ejemplo:**
```
RAMSAVE      ; Guardar en memoria
MESSAGE 90   ; "Estado guardado en memoria"
```

### RAMLOAD (ID: 63) flagno.
**DescripciÃ³n:** Carga el estado guardado en memoria.
**Uso:** Restaurar estado temporal.
**Comportamiento:** ParÃ¡metro especifica Ãºltima flag a cargar.
**Ejemplo:**
```
RAMLOAD 254  ; Cargar estado de memoria
MESSAGE 91   ; "Estado restaurado"
```

---

## Acciones de Control

### ANYKEY
**DescripciÃ³n:** Espera que se presione cualquier tecla.
**Uso:** Pausar el juego esperando entrada.
**Comportamiento:** Imprime SM16 y espera tecla.
**Ejemplo:**
```
MESSAGE 92   ; "Â¡Evento importante!"
ANYKEY       ; Esperar tecla
```

### PAUSE (ID: 35) value
**DescripciÃ³n:** Pausa durante el tiempo especificado.
**Uso:** Pausas automÃ¡ticas.
**Comportamiento:** value/50 segundos (0 = 256/50 segundos).
**Ejemplo:**
```
PAUSE 100    ; Pausar 2 segundos
MESSAGE 93   ; "DespuÃ©s de la pausa"
```

### PARSE (ID: 73) n
**DescripciÃ³n:** Analiza entrada del jugador.
**Uso:** Control del analizador sintÃ¡ctico.
**Comportamiento:** n: 0=lÃ­nea principal, 1=cadena entrecomillada.
**Ejemplo:**
```
PARSE 0      ; Analizar entrada principal
MESSAGE 94   ; "Entrada procesada"
```

### NEWTEXT
**DescripciÃ³n:** Fuerza la pÃ©rdida de frases restantes en lÃ­nea de entrada.
**Uso:** Cancelar entrada mÃºltiple tras errores.
**Comportamiento:** Limpia buffer de entrada.
**Ejemplo:**
```
NEWTEXT      ; Cancelar entrada restante
MESSAGE 95   ; "Entrada cancelada"
```

### SYNONYM (ID: 36) verb noun
**DescripciÃ³n:** Sustituye verbo y sustantivo en sentencia lÃ³gica.
**Uso:** Normalizar entrada del jugador.
**Comportamiento:** Reemplaza palabras en sentencia actual.
**Ejemplo:**
```
SYNONYM ENCENDER ANTORCHA ; Normalizar comando
MESSAGE 96 ; "Enciendes la antorcha"
```

### PROCESS (ID: 75) procno.
**DescripciÃ³n:** Llama a la tabla de proceso especificada.
**Uso:** Llamadas a subrutinas.
**Comportamiento:** Llamada verdadera con retorno.
**Ejemplo:**
```
PROCESS 5    ; Llamar proceso 5
MESSAGE 97   ; "Proceso completado"
```

### REDO
**DescripciÃ³n:** Reinicia la tabla actual.
**Uso:** Bucles y repeticiones.
**Comportamiento:** Vuelve al inicio de la tabla.
**Ejemplo:**
```
REDO         ; Reiniciar tabla actual
```

### DOALL (ID: 85) locno+
**DescripciÃ³n:** Implementa comandos tipo "ALL".
**Uso:** Ejecutar acciÃ³n en todos los objetos.
**Comportamiento:** Itera sobre objetos en localizaciÃ³n.
**Ejemplo:**
```
COGER TODO
DOALL 255    ; Coger todo en localizaciÃ³n actual
AUTOG        ; Coger cada objeto
```

### SKIP (ID: 116) distance
**DescripciÃ³n:** Salta a otra entrada en la tabla.
**Uso:** Control de flujo y saltos.
**Comportamiento:** distance: -128 a 128, o etiqueta local.
**Ejemplo:**
```
SKIP 2       ; Saltar 2 entradas adelante
MESSAGE 98   ; "Esta lÃ­nea se salta"
MESSAGE 99   ; "Esta tambiÃ©n"
MESSAGE 100  ; "Esta se ejecuta"
```

---

## Acciones de Llamadas

### EXTERN (ID: 61) value
**DescripciÃ³n:** Llama a rutina externa con parÃ¡metro.
**Uso:** Extensiones en ensamblador.
**Comportamiento:** DirecciÃ³n establecida por enlazado.
**Ejemplo:**
```
EXTERN 5     ; Llamar rutina externa con parÃ¡metro 5
MESSAGE 101  ; "Rutina externa ejecutada"
```

### CALL (ID: 101) address
**DescripciÃ³n:** Ejecuta cÃ³digo en direcciÃ³n especificada.
**Uso:** Llamadas a cÃ³digo mÃ¡quina.
**Comportamiento:** Salta a direcciÃ³n de memoria.
**Ejemplo:**
```
CALL 32768   ; Ejecutar cÃ³digo en direcciÃ³n 32768
MESSAGE 102  ; "CÃ³digo ejecutado"
```

### SFX (ID: 18) value1 value2
**DescripciÃ³n:** AcciÃ³n para efectos de sonido.
**Uso:** Reproducir sonidos.
**Comportamiento:** Escribe value1 en registro value2 del chip de sonido.
**Ejemplo:**
```
SFX 128 1    ; Efecto de sonido
MESSAGE 103  ; "Â¡Sonido reproducido!"
```

### GFX (ID: 87) value1 value2
**DescripciÃ³n:** AcciÃ³n para extensiones grÃ¡ficas.
**Uso:** Control grÃ¡fico avanzado.
**Comportamiento:** En 16-bit controla cambio de pantallas.
**Ejemplo:**
```
GFX 1 0      ; Cambiar modo grÃ¡fico
MESSAGE 104  ; "Modo grÃ¡fico cambiado"
```

---

## Acciones de GrÃ¡ficos

### PICTURE (ID: 84) picno
**DescripciÃ³n:** Carga la imagen especificada en el buffer.
**Uso:** Preparar imÃ¡genes para mostrar.
**Comportamiento:** Si no existe la imagen, salta a siguiente entrada.
**Ejemplo:**
```
PICTURE 5    ; Cargar imagen 5
DISPLAY 0    ; Mostrar imagen
```

### DISPLAY (ID: 28) value
**DescripciÃ³n:** Muestra la imagen buffered o limpia Ã¡rea.
**Uso:** Mostrar grÃ¡ficos en pantalla.
**Comportamiento:** value=0 muestra imagen, value!=0 limpia Ã¡rea.
**Ejemplo:**
```
DISPLAY 0    ; Mostrar imagen cargada
MESSAGE 105  ; "Imagen mostrada"
```

### MOUSE (ID: 86) option
**DescripciÃ³n:** Manejo bÃ¡sico de ratÃ³n (en preparaciÃ³n).
**Uso:** Control de ratÃ³n (sistema experimental).
**Comportamiento:** Esqueleto para sistema futuro.
**Ejemplo:**
```
MOUSE 1      ; Activar soporte de ratÃ³n
MESSAGE 106  ; "RatÃ³n activado"
```

---

## Acciones de FinalizaciÃ³n

### RESTART
**DescripciÃ³n:** Reinicia completamente el juego.
**Uso:** Reiniciar aventura.
**Comportamiento:** Cancela DOALL y subprocesos, va a proceso 0.
**Ejemplo:**
```
RESTART      ; Reiniciar juego
```

### END
**DescripciÃ³n:** Termina el juego preguntando si quiere jugar otra vez.
**Uso:** Final del juego.
**Comportamiento:** Pregunta si quiere jugar de nuevo.
**Ejemplo:**
```
MESSAGE 107  ; "Â¡Has ganado!"
END          ; Terminar juego
```

### EXIT (ID: 110) value
**DescripciÃ³n:** Sale del juego o reinicia.
**Uso:** Salida controlada.
**Comportamiento:** value=0 sale, value!=0 reinicia.
**Ejemplo:**
```
EXIT 0       ; Salir al sistema operativo
```

### DONE
**DescripciÃ³n:** Termina la tabla actual marcando que se ejecutÃ³ una acciÃ³n.
**Uso:** Finalizar entrada exitosamente.
**Comportamiento:** Retorna con flag "hecho".
**Ejemplo:**
```
GET 1        ; Coger objeto
DONE         ; Terminar entrada exitosamente
```

### NOTDONE
**DescripciÃ³n:** Termina la tabla actual marcando que NO se ejecutÃ³ acciÃ³n.
**Uso:** Finalizar entrada sin Ã©xito.
**Comportamiento:** Retorna con flag "no hecho".
**Ejemplo:**
```
NOTDONE      ; Terminar sin ejecutar acciÃ³n
```

### OK
**DescripciÃ³n:** Imprime "OK" y termina la entrada.
**Uso:** Respuesta afirmativa simple.
**Comportamiento:** Imprime SM15 + DONE.
**Ejemplo:**
```
OK           ; Responder "OK" y terminar
```

---

## Flags del Sistema

### Flags Importantes
- **Flag 0**: Indica si el juego estÃ¡ oscuro (usado con objeto 0)
- **Flag 1**: Cantidad de objetos que lleva el jugador
- **Flag 29**: Flags de grÃ¡ficos y opciones de pantalla
- **Flag 30**: PuntuaciÃ³n (por convenciÃ³n)
- **Flag 33**: Verbo de la sentencia lÃ³gica actual
- **Flag 34**: Primer sustantivo de la sentencia lÃ³gica
- **Flag 37**: MÃ¡ximo nÃºmero de objetos que puede llevar
- **Flag 38**: LocalizaciÃ³n actual del jugador
- **Flag 51**: Objeto actualmente referenciado
- **Flag 52**: Fuerza del jugador (peso mÃ¡ximo)

### Ejemplo de Uso de Flags del Sistema
```
; Comprobar si el jugador puede llevar mÃ¡s objetos
LT 1 37      ; Â¿Lleva menos del mÃ¡ximo?
GET 1        ; Coger objeto
DONE

; Si no puede llevar mÃ¡s
MESSAGE 108  ; "No puedes llevar mÃ¡s cosas"
DONE
```

---

## Ejemplos Avanzados

### Sistema de PuntuaciÃ³n
```
; Proceso para dar puntos por primera vez
PROCESS 10   ; Proceso de puntuaciÃ³n
ZERO 64      ; Â¿Es la primera vez? (flag 64 = marcador)
PLUS 30 50   ; Sumar 50 puntos
SET 64       ; Marcar como hecho
MESSAGE 109  ; "Â¡Ganas 50 puntos!"
DONE

; No dar puntos si ya se hizo
MESSAGE 110  ; "Ya hiciste esto antes"
DONE
```

### Sistema de Inventario Inteligente
```
; Comando INVENTARIO mejorado
INVENTARIO _
ZERO 1       ; Â¿No llevas nada?
MESSAGE 111  ; "No llevas nada"
DONE

; Mostrar objetos llevados
MESSAGE 112  ; "Llevas:"
LISTAT 254   ; Listar objetos llevados
DONE
```

### Sistema de Contenedores
```
; Comando ABRIR CAJA
ABRIR CAJA
PRESENT 10   ; Â¿EstÃ¡ presente la caja?
HASAT CONTAINER ; Â¿Es realmente un contenedor?
MESSAGE 113  ; "Abres la caja. Dentro hay:"
LISTAT 10    ; Mostrar contenido
DONE

; Error si no es contenedor
MESSAGE 114  ; "No puedes abrir eso"
DONE
```

### Sistema de Movimiento Condicional
```
; Movimiento al norte con condiciones
NORTE _
AT 5         ; Â¿EstÃ¡s en localizaciÃ³n 5?
ZERO 65      ; Â¿La puerta estÃ¡ cerrada? (flag 65)
MESSAGE 115  ; "La puerta estÃ¡ cerrada"
DONE

; Movimiento exitoso
GOTO 6       ; Ir al norte
DESC 6       ; Describir nueva localizaciÃ³n
DONE
```

---

## Notas Importantes

1. **IndirecciÃ³n**: Muchos CondActs permiten indirecciÃ³n en su primer parÃ¡metro usando `[]`.
2. **Salida de Tablas**: Los CondActs de salida (DONE, NOTDONE, etc.) terminan el procesamiento de la tabla actual.
3. **Mensajes del Sistema**: Los mensajes del sistema (SM) estÃ¡n predefinidos y pueden variar segÃºn el idioma.
4. **LÃ­mites**: Los valores de flags estÃ¡n limitados a 0-255.
5. **Objetos Especiales**: El objeto 0 se considera fuente de luz por defecto.

---

## Convenciones de ProgramaciÃ³n

### Estructura TÃ­pica de Proceso 0
```
; Proceso principal
_  _  PARSE 0     ; Analizar entrada
      PROCESS 1  ; Procesar comandos
      REDO       ; Repetir bucle

; Si no se procesa nada
_  _  SYSMESS 8  ; "No puedo hacer eso"
      REDO       ; Repetir bucle
```

### Manejo de Errores
```
; Verificar condiciones antes de actuar
COGER _
WHATO        ; Identificar objeto
PRESENT 51   ; Â¿EstÃ¡ presente?
AUTOG        ; Coger automÃ¡ticamente
DONE

; Error si no estÃ¡ presente
MESSAGE 116  ; "No veo eso aquÃ­"
DONE
```

### Uso de Subprocesos
```
; Llamada a subproceso con verificaciÃ³n
PROCESS 5    ; Llamar subproceso
ISDONE       ; Â¿Tuvo Ã©xito?
MESSAGE 117  ; "AcciÃ³n completada"
DONE

; Manejo de fallo
MESSAGE 118  ; "No se pudo completar"
DONE
```

---

Este documento proporciona una referencia completa de todos los CondActs disponibles en DAAD. Cada CondAct incluye su descripciÃ³n, uso tÃ­pico, comportamiento detallado y ejemplos prÃ¡cticos de implementaciÃ³n.

