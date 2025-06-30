# Manejo de caracteres especiales en español para Inform 6

Este documento explica cómo manejar correctamente los caracteres acentuados y especiales del español en juegos desarrollados con Inform 6.

## Tabla de caracteres Zcharacter

Para usar caracteres acentuados y especiales en Inform 6, es necesario declararlos explícitamente mediante la directiva `Zcharacter table`. Esta directiva debe colocarse **antes** de incluir cualquier archivo de la librería.

### Ejemplo básico

```inform
! Definir la tabla de caracteres para soportar acentos y caracteres especiales
Zcharacter table + '@{E1}' '@{E9}' '@{ED}' '@{F3}' '@{FA}' '@{F1}' '@{DC}' '@{FC}' '@{BF}' '@{A1}';  ! á é í ó ú ñ Ü ü ¿ ¡

! Incluir la librería estándar
Include "Parser";
Include "VerbLib";

! Incluir la librería en español
Include "SpanishLib";
```

## Tabla de códigos hexadecimales para caracteres especiales

| Carácter | Código Hex | Secuencia Inform |
|----------|------------|------------------|
| á        | E1         | `@{E1}`          |
| é        | E9         | `@{E9}`          |
| í        | ED         | `@{ED}`          |
| ó        | F3         | `@{F3}`          |
| ú        | FA         | `@{FA}`          |
| ñ        | F1         | `@{F1}`          |
| Á        | C1         | `@{C1}`          |
| É        | C9         | `@{C9}`          |
| Í        | CD         | `@{CD}`          |
| Ó        | D3         | `@{D3}`          |
| Ú        | DA         | `@{DA}`          |
| Ñ        | D1         | `@{D1}`          |
| ü        | FC         | `@{FC}`          |
| Ü        | DC         | `@{DC}`          |
| ¿        | BF         | `@{BF}`          |
| ¡        | A1         | `@{A1}`          |

## Recomendaciones

### 1. Declaración completa

Para asegurar la compatibilidad con todos los caracteres especiales del español, se recomienda incluir la siguiente declaración al inicio de tu juego:

```inform
Zcharacter table + '@{E1}' '@{E9}' '@{ED}' '@{F3}' '@{FA}' '@{F1}' '@{C1}' '@{C9}' '@{CD}' '@{D3}' '@{DA}' '@{D1}' '@{FC}' '@{DC}' '@{BF}' '@{A1}';
```

### 2. Alternativa sin acentos

Si prefieres evitar problemas con los caracteres acentuados, puedes optar por no usarlos en tu código. En ese caso, simplifica los textos eliminando acentos y caracteres especiales:

```inform
Constant Story "EJEMPLO DE LIBRERIA ESPANOLA";
Constant Headline "^Un ejemplo completo de las caracteristicas de la libreria en espanol.^";
```

### 3. Uso en strings

Cuando necesites usar caracteres acentuados dentro de strings, puedes hacerlo directamente si ya has declarado la tabla de caracteres:

```inform
print "¡Hola! ¿Cómo estás?";
```

O usar secuencias de escape si prefieres evitar problemas de codificación:

```inform
print "@{A1}Hola! @{BF}C@{F3}mo est@{E1}s?";
```

## Solución de problemas

Si encuentras errores como:

```
Error: Character can only be used if declared in advance as part of 'Zcharacter table': (ISO Latin1) $XX
```

Significa que estás usando un carácter que no has declarado en la tabla Zcharacter. Añade el carácter a la declaración o elimina/reemplaza el carácter en tu código.

## Compatibilidad con intérpretes

La mayoría de los intérpretes modernos de Z-machine y Glulx soportan correctamente los caracteres del español cuando están declarados adecuadamente. Sin embargo, algunos intérpretes antiguos pueden tener problemas. Si desarrollas para una plataforma específica, es recomendable probar la compatibilidad de caracteres.

## Más información

Para información más detallada sobre el manejo de caracteres en Inform 6, consulta:

- [DM4: The Inform Designer's Manual, 4th Edition](https://inform-fiction.org/manual/html/index.html)
- [Sección 2.5: Character Sets](https://inform-fiction.org/manual/html/s2.html#s2.5)