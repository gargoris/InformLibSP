# InformLibSP - Librería en Español para Inform 6

Una adaptación completa de la librería Inform 6 (versión 6.12.7) al idioma español, con soporte avanzado para conjugación verbal, concordancia de género y número, y mensajes adaptados al contexto.

## Características principales

- **Mensajes del sistema en español**: Todos los mensajes del sistema han sido traducidos al español.
- **Gramática española**: Verbos y comandos adaptados a la estructura gramatical del español.
- **Sistema de conjugación verbal**: Soporte para verbos regulares e irregulares en diferentes tiempos verbales.
- **Sistema de concordancia de adjetivos**: Adaptación automática de adjetivos según el género y número.
- **Funciones auxiliares de género y número**: Herramientas para manejar correctamente artículos, preposiciones y terminaciones.
- **Sistema de adverbios y preposiciones espaciales**: Manejo de relaciones espaciales para frases complejas.

## Instalación

1. Descarga los archivos de la librería
2. Colócalos en el directorio de tu proyecto o en el directorio de librerías de Inform
3. Incluye la librería en tu juego:

```inform
Include "Parser";
Include "VerbLib";
Include "SpanishLib";
```

## Uso básico

### Configuración

La librería se configura automáticamente con todas las características habilitadas. Si deseas una versión más ligera, puedes definir `SPANISH_MINIMAL` antes de incluir SpanishLib:

```inform
Constant SPANISH_MINIMAL;
Include "SpanishLib";
```

Para habilitar características específicas:

```inform
Constant SPANISH_MINIMAL;      ! Desactiva todas las características
Constant SPANISH_FULL_MESSAGES; ! Activa mensajes completos
Include "SpanishLib";
```

### Inicialización

Para inicializar la librería, llama a `SpanishLibInitialise()` en tu rutina `Initialise`:

```inform
[ Initialise;
    SpanishLibInitialise();
    location = MiHabitacionInicial;
];
```

Para ver la configuración cargada:

```inform
[ Initialise;
    SpanishLibInitialise();
    SpanishLibShowConfiguration();
    location = MiHabitacionInicial;
];
```

## Sistema de conjugación verbal

La librería incluye un sistema completo para conjugar verbos en español:

### Constantes de tiempo verbal

```inform
TIEMPO_PRESENTE
TIEMPO_PRETERITO
TIEMPO_IMPERFECTO
TIEMPO_FUTURO
TIEMPO_CONDICIONAL
TIEMPO_SUBJUNTIVO
TIEMPO_IMPERATIVO
```

### Constantes de persona gramatical

```inform
PERSONA_YO
PERSONA_TU
PERSONA_USTED
PERSONA_EL
PERSONA_ELLA
PERSONA_NOSOTROS
PERSONA_VOSOTROS
PERSONA_USTEDES
PERSONA_ELLOS
PERSONA_ELLAS
```

### Funciones de conjugación

- `ConjugarVerbo(verbo, tiempo, persona)`: Conjuga cualquier verbo en el tiempo y persona indicados
- `ConjugarParaObjeto(verbo, obj)`: Conjuga un verbo en presente según el género y número del objeto
- `ConjugarPasadoParaObjeto(verbo, obj)`: Conjuga un verbo en pretérito según el género y número del objeto

### Ejemplo de uso

```inform
print "El libro ";
ConjugarParaObjeto("brillar", libro);
print " en la oscuridad.";  ! Imprime: "El libro brilla en la oscuridad."

print "Las llaves ";
ConjugarParaObjeto("abrir", llaves);
print " la puerta.";  ! Imprime: "Las llaves abren la puerta."
```

## Sistema de concordancia de adjetivos

La librería incluye funciones para adaptar adjetivos al género y número de los objetos:

### Funciones principales

- `ConcordarAdjetivo(adjetivo, obj)`: Adapta un adjetivo al género y número del objeto
- `adj(adjetivo, obj)`: Versión abreviada de ConcordarAdjetivo
- `esta_adj(adjetivo, obj)`: Imprime "está/están" + adjetivo concordado
- `es_adj(adjetivo, obj)`: Imprime "es/son" + adjetivo concordado
- `un_adj(adjetivo, obj)`: Imprime "un/una/unos/unas" + adjetivo concordado
- `el_adj(adjetivo, obj)`: Imprime "el/la/los/las" + adjetivo concordado

### Ejemplo de uso

```inform
print "El libro ", (es_adj) "viejo" libro, ".";  ! Imprime: "El libro es viejo."
print "La mesa ", (es_adj) "viejo" mesa, ".";    ! Imprime: "La mesa es vieja."
print "Los libros ", (es_adj) "viejo" libros, "."; ! Imprime: "Los libros son viejos."
print "Las llaves ", (es_adj) "viejo" llaves, "."; ! Imprime: "Las llaves son viejas."
```

## Género y número

La librería incluye funciones auxiliares para manejar el género y número en español:

### Funciones básicas

- `es(obj)`: Imprime "es" o "son" según el número del objeto
- `esta(obj)`: Imprime "está" o "están" según el número del objeto
- `n(obj)`: Imprime "n" o nada según el número del objeto
- `s(obj)`: Imprime "s" o nada según el número del objeto
- `o(obj)`: Imprime "o" o "a" según el género del objeto
- `lo(obj)`: Imprime "lo" o "la" según el género del objeto
- `el(obj)`: Imprime "el", "la", "los" o "las" según género y número
- `un(obj)`: Imprime "un", "una", "unos" o "unas" según género y número
- `del(obj)`: Imprime "del", "de la", "de los" o "de las" según género y número
- `al(obj)`: Imprime "al", "a la", "a los" o "a las" según género y número
- `en_el(obj)`: Imprime "en el", "en la", "en los" o "en las" según género y número
- `por_el(obj)`: Imprime "por el", "por la", "por los" o "por las" según género y número

### Funciones para participios

- `abierto(obj)`: Imprime "abierto/a/os/as" según género y número
- `cerrado(obj)`: Imprime "cerrado/a/os/as" según género y número
- `puesto(obj)`: Imprime "puesto/a/os/as" según género y número
- `vacio(obj)`: Imprime "vacío/a/os/as" según género y número
- `lleno(obj)`: Imprime "lleno/a/os/as" según género y número
- `bloqueado(obj)`: Imprime "bloqueado/a/os/as" según género y número
- `encendido(obj)`: Imprime "encendido/a/os/as" según género y número
- `apagado(obj)`: Imprime "apagado/a/os/as" según género y número

### Funciones compuestas

- `esta_participio(participio, obj)`: Imprime "está/están" + participio concordado
- `ha_sido_participio(participio, obj)`: Imprime "ha/han sido" + participio concordado
- `puede_ser_participio(participio, obj)`: Imprime "puede/pueden ser" + participio concordado

### Ejemplo de uso

```inform
print "El libro ", (es) libro, " interesante.";  ! Imprime: "El libro es interesante."
print "Las llaves ", (esta) llaves, " sobre la mesa.";  ! Imprime: "Las llaves están sobre la mesa."
print "El libro ", (esta_participio) "abierto" libro, ".";  ! Imprime: "El libro está abierto."
print "Las puertas ", (esta_participio) "cerrado" puertas, ".";  ! Imprime: "Las puertas están cerradas."
```

## Adverbios y preposiciones espaciales

La librería incluye un sistema para manejar adverbios y preposiciones espaciales:

### Constantes de relaciones espaciales

```inform
REL_DENTRO      ! dentro de
REL_SOBRE       ! sobre, encima de
REL_DEBAJO      ! debajo de, bajo
REL_DETRAS      ! detrás de
REL_DELANTE     ! delante de, frente a
REL_CERCA       ! cerca de, junto a
REL_LEJOS       ! lejos de
REL_ENTRE       ! entre
REL_ALREDEDOR   ! alrededor de
REL_A_TRAVES    ! a través de
REL_HACIA       ! hacia
REL_DESDE       ! desde
REL_HASTA       ! hasta
REL_CONTRA      ! contra
REL_SIN         ! sin
REL_CON         ! con
```

### Funciones para relaciones espaciales

- `dentro_de(obj)`: Imprime "dentro de" + objeto
- `sobre(obj)`: Imprime "sobre" + objeto
- `debajo_de(obj)`: Imprime "debajo de" + objeto
- `detras_de(obj)`: Imprime "detrás de" + objeto
- `delante_de(obj)`: Imprime "delante de" + objeto
- `cerca_de(obj)`: Imprime "cerca de" + objeto
- `lejos_de(obj)`: Imprime "lejos de" + objeto
- `entre(obj)`: Imprime "entre" + objeto
- `alrededor_de(obj)`: Imprime "alrededor de" + objeto
- `a_traves_de(obj)`: Imprime "a través de" + objeto
- `hacia(obj)`: Imprime "hacia" + objeto
- `desde(obj)`: Imprime "desde" + objeto
- `hasta(obj)`: Imprime "hasta" + objeto
- `contra(obj)`: Imprime "contra" + objeto
- `sin(obj)`: Imprime "sin" + objeto
- `con(obj)`: Imprime "con" + objeto

### Funciones para frases complejas

- `adv_adj(adverbio, adjetivo, obj)`: Imprime adverbio + adjetivo concordado
- `verbo_adv(verbo, adverbio, obj)`: Imprime verbo conjugado + adverbio
- `verbo_obj_adv(verbo, obj, adverbio)`: Imprime verbo conjugado + objeto + adverbio
- `verbo_obj_adv_obj2(verbo, obj1, adverbio, obj2, relacion)`: Imprime frases complejas con dos objetos y una relación espacial
- `ImprimirRelacionEspacial(relacion, obj1, obj2)`: Imprime una relación espacial completa entre dos objetos

### Ejemplo de uso

```inform
print "El libro está ";
dentro_de(mesa);
print ".";  ! Imprime: "El libro está dentro de la mesa."

print "La lámpara está ";
sobre(mesa);
print ".";  ! Imprime: "La lámpara está sobre la mesa."

verbo_obj_adv_obj2("poner", libro, "dentro", mesa, REL_DENTRO);
print ".";  ! Imprime: "Pone el libro dentro de la mesa."

ImprimirRelacionEspacial(REL_DEBAJO, llaves, mesa);
print ".";  ! Imprime: "Las llaves están debajo de la mesa."
```

## Mensajes adicionales para relaciones espaciales

La librería incluye mensajes adicionales para las nuevas acciones espaciales:

### Mensajes para acciones espaciales

- Mensajes para `DropUnder`: Dejar algo debajo de otro objeto
- Mensajes para `DropBehind`: Dejar algo detrás de otro objeto
- Mensajes para `DropInFront`: Dejar algo delante de otro objeto
- Mensajes para `DropNear`: Dejar algo cerca de otro objeto

### Función de mensajes extendida

```inform
LanguageLMExt(accion, numero, objeto1, objeto2)
```

Esta función maneja los mensajes para las nuevas acciones espaciales, siguiendo el mismo patrón que la función `LanguageLM` estándar de Inform.

## Extensiones de gramática para relaciones espaciales

La librería incluye extensiones de gramática para manejar comandos con relaciones espaciales:

### Nuevas acciones

- `DropUnder`: Dejar algo debajo de otro objeto
- `DropBehind`: Dejar algo detrás de otro objeto
- `DropInFront`: Dejar algo delante de otro objeto
- `DropNear`: Dejar algo cerca de otro objeto

### Extensiones de verbos existentes

Los verbos como 'deja', 'pon', 'coloca', 'mete', etc. han sido extendidos para soportar frases como:

- "deja el libro sobre la mesa"
- "pon la lámpara encima de la mesa"
- "coloca las llaves debajo de la alfombra"
- "deja el vaso detrás del jarrón"
- "pon la silla delante del escritorio"
- "coloca el cuadro cerca de la ventana"
- "deja la planta junto a la puerta"

### Nuevos verbos

- `esconde`: Para esconder objetos detrás o debajo de otros
- `acerca`: Para acercar objetos a otros

### Ejemplo de uso

```inform
! En la rutina de inicialización
[ Initialise;
    ! Configuración estándar...
    
    ! Mensajes personalizados para acciones espaciales
    DropUnderSub.description = "Dejas el objeto debajo de otro.";
    DropBehindSub.description = "Escondes el objeto detrás de otro.";
    DropInFrontSub.description = "Colocas el objeto delante de otro.";
    DropNearSub.description = "Acercas el objeto a otro.";
];
```

## Ejemplos

La librería incluye varios ejemplos que demuestran su uso:

- `samples/EjemploCompleto.inf`: Demostración completa de todas las características
- `samples/Elena.h`: Ejemplo de NPC con personalidad compleja

## Licencia

Esta librería está disponible bajo la licencia tradicional de Inform como se describe en el DM4 o la Artistic License 2.0.

## Créditos

- Librería original Inform 6: Graham Nelson (1993-2004) y David Griffith (2012-2024)
- Adaptación al español: Francisco Fuentes (2025)