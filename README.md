<<<<<<< HEAD
# InformLibSP
Translation of inform 6 library to spanish based in INFSP and others
=======
# Librería en Español para Inform 6

Esta es una adaptación al español de la librería estándar de Inform 6, basada en la versión 6.12.7dev de la librería en inglés.

## Características

- Soporte completo para el idioma español, incluyendo acentos y caracteres especiales
- Gramática adaptada al español
- Verbos y comandos en español con soporte para verbos irregulares
- Soporte para diferentes dialectos (castellano y sudamericano)
- Rutinas de parser adaptadas para manejar correctamente el género y número en español

## Archivos

La librería consta de tres archivos principales:

1. `spanish.h` - Definiciones básicas del idioma español (artículos, pronombres, números, etc.)
2. `infspr.h` - Funciones de reemplazo para adaptar el parser al español
3. `spanishg.h` - Gramática española (verbos, comandos, etc.)

## Uso

Para usar esta librería en tus juegos de Inform 6, debes compilar con la opción `+language_name=spanish` y asegurarte de que estos archivos estén en el directorio de la librería.

### Ejemplo de uso

```inform
Constant Story "Mi Aventura";
Constant Headline "^Una aventura de ejemplo^";

Include "Parser";
Include "VerbLib";
Include "Grammar";

! Definición de objetos y lógica del juego aquí

Include "SpanishG";  ! Incluir la gramática en español
```

## Características específicas del español

### Género y número

En español, los objetos tienen género (masculino/femenino) y número (singular/plural). Para definir estos atributos:

```inform
Object mesa "mesa"
  with name 'mesa',
  has female;  ! Objeto femenino

Object libros "libros"
  with name 'libros',
  has pluralname;  ! Objeto plural
```

### Verbos irregulares

La librería incluye soporte para verbos irregulares en español, permitiendo que el parser reconozca diferentes formas verbales:

```inform
VerboIrregular "ir" with imperativo 'ir' 've' 'vaya' 'id' 'vayan',
                     presente 'voy' 'vas' 'va' 'vamos' 'vais' 'van',
                     pasado 'fui' 'fuiste' 'fue' 'fuimos' 'fuisteis' 'fueron',
                     futuro 'iré' 'irás' 'irá' 'iremos' 'iréis' 'irán';
```

Esto permite que el jugador pueda usar diferentes tiempos verbales en sus comandos, como "voy al norte" o "ve al norte".

### Dialectos

La librería soporta dos dialectos del español:

- **Castellano** (por defecto): Usa "coger" como verbo para tomar objetos
- **Sudamericano**: Evita el uso de "coger" (que puede tener connotaciones sexuales en algunos países)

Para cambiar el dialecto durante el juego, el jugador puede usar el comando:

```
> DIALECTO SUDAMERICANO
```

o

```
> DIALECTO CASTELLANO
```

### Acentos

Por defecto, la librería elimina los acentos de las palabras ingresadas por el jugador para facilitar la comprensión. Esto se puede desactivar con:

```
> ACENTOS ON
```

## Créditos

Esta librería es una adaptación de la librería estándar de Inform 6 (6.12.7dev) y está basada en el trabajo previo de INFSP y otros proyectos de traducción al español.

## Licencia

Esta librería está licenciada bajo los mismos términos que la librería estándar de Inform 6, ya sea bajo la licencia tradicional de Inform descrita en el DM4 o la Artistic License 2.0.
>>>>>>> master
