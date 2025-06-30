# Librería en Español para Inform 6

Esta es una adaptación al español de la librería estándar de Inform 6 (versión 6.12.7).

## Características

- Traducción completa de todos los mensajes del sistema
- Soporte para gramática y conjugaciones en español
- Soporte completo para caracteres especiales del español (acentos, ñ, signos de interrogación/exclamación invertidos)
- Adaptación de la estructura de comandos a la sintaxis española

## Instalación

1. Copia todos los archivos de esta librería a tu directorio de trabajo de Inform 6.
2. En tu archivo principal de juego, incluye los archivos necesarios en este orden:

```inform
Include "Parser";
Include "VerbLib";
Include "SpanishLib";
```

## Uso

### Configuración básica

Para usar la librería en español, simplemente incluye `SpanishLib.h` después de incluir `Parser.h` y `VerbLib.h`:

```inform
Include "Parser";
Include "VerbLib";
Include "SpanishLib";

[ Initialise;
    SpanishLibInitialise();
    location = Sala_Inicial;
    "¡Bienvenido a tu aventura en español!";
];
```

### Configuración avanzada

Puedes personalizar la librería definiendo estas constantes antes de incluir `SpanishLib.h`:

- `SPANISH_MINIMAL`: Carga solo las características básicas
- `SPANISH_FULL_MESSAGES`: Carga todos los mensajes en español (activado por defecto)
- `SPANISH_GRAMMAR`: Carga la gramática en español (activado por defecto)

Ejemplo:

```inform
Constant SPANISH_MINIMAL;       ! Desactiva todas las características avanzadas
Constant SPANISH_FULL_MESSAGES; ! Pero activa los mensajes completos

Include "Parser";
Include "VerbLib";
Include "SpanishLib";
```

## Características del lenguaje español

### Género y número

La librería incluye funciones auxiliares para manejar el género y número en español:

- `es(obj)`: Imprime "es" o "son" según el número del objeto
- `esta(obj)`: Imprime "está" o "están" según el número del objeto
- `n(obj)`: Imprime "n" o nada según el número del objeto
- `s(obj)`: Imprime "s" o nada según el número del objeto
- `o(obj)`: Imprime "o" o "a" según el género del objeto
- `lo(obj)`: Imprime "lo" o "la" según el género del objeto
- `del(obj)`: Imprime "del", "de la", "de los" o "de las" según género y número
- `al(obj)`: Imprime "al", "a la", "a los" o "a las" según género y número

### Ejemplo de uso

```inform
Object mesa "mesa" has female;
Object sillas "sillas" has female pluralname;
Object libro "libro";

[ Prueba;
    print "La mesa ", (es) mesa, " bonita.^";
    print "Las sillas ", (estan) sillas, " colocada", (s) sillas, ".^";
    print "El libro ", (es) libro, " interesante.^";
    print "Mira ", (al) mesa, ".^";
    print "Coge ", (el) libro, ".^";
];
```

## Créditos

- Librería original Inform 6: Graham Nelson y David Griffith
- Adaptación al español: Francisco Fuentes (2025)

## Licencia

Esta librería está disponible bajo la licencia Artistic License 2.0, igual que la librería original de Inform 6.# Librería en Español para Inform 6

Esta es una adaptación al español de la librería estándar de Inform 6 (versión 6.12.7).

## Características

- Traducción completa de todos los mensajes del sistema
- Soporte para gramática y conjugaciones en español
- Soporte completo para caracteres especiales del español (acentos, ñ, signos de interrogación/exclamación invertidos)
- Adaptación de la estructura de comandos a la sintaxis española

## Instalación

1. Copia todos los archivos de esta librería a tu directorio de trabajo de Inform 6.
2. En tu archivo principal de juego, incluye los archivos necesarios en este orden:

```inform
Include "Parser";
Include "VerbLib";
Include "SpanishLib";
```

## Uso

### Configuración básica

Para usar la librería en español, simplemente incluye `SpanishLib.h` después de incluir `Parser.h` y `VerbLib.h`:

```inform
Include "Parser";
Include "VerbLib";
Include "SpanishLib";

[ Initialise;
    SpanishLibInitialise();
    location = Sala_Inicial;
    "¡Bienvenido a tu aventura en español!";
];
```

### Configuración avanzada

Puedes personalizar la librería definiendo estas constantes antes de incluir `SpanishLib.h`:

- `SPANISH_MINIMAL`: Carga solo las características básicas
- `SPANISH_FULL_MESSAGES`: Carga todos los mensajes en español (activado por defecto)
- `SPANISH_GRAMMAR`: Carga la gramática en español (activado por defecto)

Ejemplo:

```inform
Constant SPANISH_MINIMAL;       ! Desactiva todas las características avanzadas
Constant SPANISH_FULL_MESSAGES; ! Pero activa los mensajes completos

Include "Parser";
Include "VerbLib";
Include "SpanishLib";
```

## Características del lenguaje español

### Género y número

La librería incluye funciones auxiliares para manejar el género y número en español:

- `es(obj)`: Imprime "es" o "son" según el número del objeto
- `esta(obj)`: Imprime "está" o "están" según el número del objeto
- `n(obj)`: Imprime "n" o nada según el número del objeto
- `s(obj)`: Imprime "s" o nada según el número del objeto
- `o(obj)`: Imprime "o" o "a" según el género del objeto
- `lo(obj)`: Imprime "lo" o "la" según el género del objeto
- `del(obj)`: Imprime "del", "de la", "de los" o "de las" según género y número
- `al(obj)`: Imprime "al", "a la", "a los" o "a las" según género y número

### Ejemplo de uso

```inform
Object mesa "mesa" has female;
Object sillas "sillas" has female pluralname;
Object libro "libro";

[ Prueba;
    print "La mesa ", (es) mesa, " bonita.^";
    print "Las sillas ", (estan) sillas, " colocada", (s) sillas, ".^";
    print "El libro ", (es) libro, " interesante.^";
    print "Mira ", (al) mesa, ".^";
    print "Coge ", (el) libro, ".^";
];
```

## Créditos

- Librería original Inform 6: Graham Nelson y David Griffith
- Adaptación al español: Francisco Fuentes (2025)

## Licencia

Esta librería está disponible bajo la licencia Artistic License 2.0, igual que la librería original de Inform 6.