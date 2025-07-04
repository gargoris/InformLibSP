# Plan de Traducción de PunyInform al Español

## Análisis de la Estructura de PunyInform

Después de analizar la librería PunyInform, he identificado los siguientes componentes clave que necesitan traducción/adaptación al español:

### Archivos Principales Analizados:

1. **puny.h** - Archivo principal que incluye la librería completa
2. **grammar.h** - Define verbos y patrones gramaticales
3. **messages.h** - Contiene todos los mensajes mostrados al jugador  
4. **parser.h** - Lógica del parser y análisis de comandos
5. **globals.h** - Constantes y variables globales

## Plan de Trabajo

### Fase 1: Estructura Base Española

1. **Crear directorio `spanish/`** ✅
2. **Archivo `spanish/grammar.h`** - Verbos españoles con conjugaciones
3. **Archivo `spanish/messages.h`** - Mensajes localizados
4. **Archivo `spanish/parser.h`** - Adaptaciones específicas del parser
5. **Archivo `spanish/puny_spanish.h`** - Archivo principal que incluye todo

### Fase 2: Adaptación Lingüística

#### Verbos Regulares e Irregulares
- Implementar conjugaciones verbales españolas
- Soporte para infinitivo, imperativo y formas reflexivas
- Verbos regulares (-ar, -er, -ir)
- Verbos irregulares comunes (ser, estar, ir, tener, etc.)

#### Artículos y Concordancia
- Artículos definidos: el, la, los, las
- Artículos indefinidos: un, una, unos, unas
- Concordancia de género y número

#### Preposiciones
- Adaptación de preposiciones españolas (a, de, en, con, por, para, etc.)

### Fase 3: Características Específicas del Español

#### Direcciones
- Norte, sur, este, oeste
- Arriba, abajo, dentro, fuera
- Formas cortas: n, s, e, o, arriba, abajo

#### Comandos Meta
- Ayuda, inventario, mirar, examinar
- Cargar, guardar, reiniciar, salir

#### Mensajes del Sistema
- Traducción completa de todos los mensajes
- Adaptación cultural apropiada

## Ejemplos de Uso Esperados

### Verbos Básicos
```
> coger la llave
> examinar el cofre
> abrir la puerta con la llave
> ir al norte
> hablar con el mercader
```

### Comandos con Objetos Múltiples
```
> coger todo
> coger todo excepto la espada
> meter las monedas en la bolsa
```

### Comandos Meta
```
> inventario
> mirar
> ayuda
> guardar
```

## Arquitectura Técnica

### Integración con PunyInform Original
- Mantenimiento de compatibilidad con el núcleo de PunyInform
- Uso del sistema de mensajes existente
- Extensión del parser para manejar gramática española

### Constantes y Configuración
- Definición de palabras clave en español
- Arrays de direcciones en español
- Configuración de género y número gramatical

### Manejo de Caracteres Especiales
- Soporte para acentos (á, é, í, ó, ú)
- Soporte para ñ
- Consideración de limitaciones en sistemas retro

## Próximos Pasos

1. Implementar `spanish/grammar.h` con verbos básicos
2. Crear `spanish/messages.h` con mensajes traducidos
3. Adaptar `spanish/parser.h` para gramática española
4. Crear archivo principal `spanish/puny_spanish.h`
5. Crear ejemplo de juego de prueba
6. Documentación de uso

## Objetivos de Compatibilidad

- Funcionar en sistemas de 8-bit (Commodore 64, etc.)
- Mantener el tamaño pequeño característico de PunyInform
- Compatibilidad con Inform 6.36+
- Soporte tanto para Z-machine v3 como v5

## Consideraciones Culturales

- Adaptación de expresiones idiomáticas
- Uso de formalidades apropiadas (tú/usted)
- Mensajes de error claros en español natural
- Terminología de ficción interactiva en español