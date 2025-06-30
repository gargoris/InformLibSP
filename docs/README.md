# Spanish Library para Inform 6

Sistema modular completo para desarrollar ficción interactiva en español con Inform 6.

## 🚀 Instalación Rápida

```inform6
! En tu archivo principal de Inform 6:
#Include "Parser.h"
#Include "VerbLib.h"
#Include "SpanishLib.h"   ← ¡Punto de entrada único!

! El resto de tu juego...
```

## 📁 Estructura del Sistema

```
SpanishLib/
├── SpanishLib.h              ← ARCHIVO PRINCIPAL (incluir este)
├── core/
│   ├── SpanishConstants.h    ← Constantes centralizadas
│   ├── SpanishCore.h         ← Coordinación del sistema
│   ├── SpanishParser.h       ← Análisis sintáctico avanzado
│   ├── SpanishVerbs.h        ← Conjugaciones y verbos
│   └── SpanishGrammar.h      ← Género, número, concordancia
├── extensions/
│   ├── SpanishIrregularVerbs.h ← Verbos irregulares (SER, ESTAR, etc.)
│   ├── SpanishMeta.h         ← Meta-comandos (UNDO, AGAIN, HELP)
│   └── SpanishRegional.h     ← Variantes regionales (voseo, etc.)
├── resources/
│   └── SpanishMessages.h     ← ~400 mensajes del sistema
└── docs/
    └── README.md             ← Este archivo
```

## ⚙️ Configuración

### Configuración Básica (Recomendada)

```inform6
! Antes de #Include "SpanishLib.h":
Constant SPANISH_FULL_MESSAGES;    ! Sistema completo de mensajes
Constant SPANISH_META_COMMANDS;    ! UNDO, AGAIN, HELP, etc.
Constant SPANISH_IRREGULAR_VERBS;  ! SER, ESTAR, TENER, etc.

#Include "SpanishLib.h"
```

### Configuración Mínima

```inform6
! Solo incluir SpanishLib.h sin constantes adicionales
! Proporciona funcionalidad básica
#Include "SpanishLib.h"
```

### Configuración Completa

```inform6
Constant SPANISH_FULL_MESSAGES;
Constant SPANISH_META_COMMANDS;
Constant SPANISH_IRREGULAR_VERBS;
Constant SPANISH_REGIONAL_VARIANTS; ! Variantes dialectales

#Include "SpanishLib.h"
```

## 🎯 Características Principales

### ✅ Núcleo Básico (Siempre Incluido)

- **Parser avanzado**: Preposiciones compuestas, contracciones (del/al)
- **Conjugaciones regulares**: Verbos -AR, -ER, -IR completos
- **Género y número**: Concordancia automática
- **Detección de verbos**: +100 verbos reconocidos

### 🚀 Extensiones Opcionales

#### Verbos Irregulares (`SPANISH_IRREGULAR_VERBS`)

```inform6
! Verbos implementados:
SER, ESTAR, TENER, HACER, IR, VENIR, VER, DAR, PODER,
QUERER, SABER, DECIR, PONER, SALIR, TRAER, CAER, OÍR,
DORMIR, MORIR, SENTIR
```

#### Meta-comandos (`SPANISH_META_COMMANDS`)

```inform6
! Comandos disponibles:
DESHACER/UNDO    - Deshacer última acción
REPETIR/AGAIN    - Repetir último comando
CORRECCIÓN/OOPS  - Corregir palabra mal escrita
AYUDA/HELP       - Sistema de ayuda integrado
COMANDOS         - Ver verbos disponibles
```

#### Mensajes Completos (`SPANISH_FULL_MESSAGES`)

- ~400 mensajes del sistema traducidos
- Concordancia automática de género/número
- Mensajes contextuales y naturales

#### Variantes Regionales (`SPANISH_REGIONAL_VARIANTS`)

- Voseo argentino ("vos tenés" vs "tú tienes")
- Vocabulario regional (coche/carro/auto)
- Configuración por país

## 🛠️ Uso Básico

### Configurar Género de Objetos

```inform6
Object mesa "mesa"
  with name 'mesa',
  has female;   ! Femenino: "la mesa"

Object libro "libro"
  with name 'libro',
  has male;     ! Masculino: "el libro" (por defecto)
```

### Usar Funciones de Gramática

```inform6
! En descripciones:
print "Ves "; ArticuloDefinido(obj); print " "; (name) obj;
! → "Ves la mesa" o "Ves el libro"

! Verificar género:
if (EsGeneroMasculino(obj)) print "masculino";
else print "femenino";
```

### Cambiar Nivel de Formalidad

```inform6
! En tiempo de ejecución:
SpanishSetFormality(FORMAL);   ! Cambiar a "usted"
SpanishSetFormality(INFORMAL); ! Cambiar a "tú"
```

## 🌍 Variantes Regionales

```inform6
! Configurar región (antes de #Include):
Constant SPANISH_REGION = REGION_ARGENTINA; ! o REGION_SPAIN, REGION_MEXICO

! O cambiar dinámicamente:
SetSpanishRegion(REGION_ARGENTINA);
! Activa automáticamente: voseo, vocabulario regional, etc.
```

## 🔧 Funciones Principales

### Parser y Análisis

```inform6
SpanishParserMain()           ! Procesamiento principal
SpanishProcessContractions()  ! del → de + el
```

### Conjugaciones

```inform6
ConjugarVerbo(verbo, persona, tiempo, tipo)
ConjugarAR(raiz, persona, tiempo)     ! Verbos -AR
ConjugarER(raiz, persona, tiempo)     ! Verbos -ER
ConjugarIR(raiz, persona, tiempo)     ! Verbos -IR
```

### Gramática

```inform6
EsGeneroMasculino(obj)        ! Verificar género
ArticuloDefinido(obj)         ! "el/la/los/las"
ArticuloIndefinido(obj)       ! "un/una/unos/unas"
SetSpanishGender(obj, gender) ! Establecer género
```

## 📊 Estadísticas del Sistema

| Característica           | Cobertura       |
| ------------------------ | --------------- |
| Verbos regulares         | 100% (AR/ER/IR) |
| Verbos irregulares       | 20 principales  |
| Mensajes del sistema     | ~400 mensajes   |
| Meta-comandos            | 13 comandos     |
| Preposiciones compuestas | 15+ formas      |
| Detección de verbos      | 100+ verbos     |

## 🐛 Depuración

```inform6
#Ifdef DEBUG;
  SpanishLibTest();           ! Prueba rápida del sistema
  SpanishDebugVerb('mirar');  ! Analizar verbo específico
  SpanishCoreStatus();        ! Estado del sistema
#Endif;
```

## 🆚 Migración desde Sistemas Anteriores

### Si usabas `Spanish.h` monolítico:

```inform6
! ANTES:
#Include "Spanish.h"

! AHORA:
#Include "SpanishLib.h"
! ¡El resto del código permanece igual!
```

### Si usabas módulos separados:

```inform6
! ANTES:
#Include "SpanishCore.h"
#Include "SpanishParser.h"
! ... etc

! AHORA:
#Include "SpanishLib.h"  ! ¡Incluye todo automáticamente!
```

## 📚 Ejemplos de Código

### Juego Básico

```inform6
#Include "Parser.h"
#Include "VerbLib.h"

! Configuración recomendada
Constant SPANISH_FULL_MESSAGES;
Constant SPANISH_META_COMMANDS;
Constant SPANISH_IRREGULAR_VERBS;

#Include "SpanishLib.h"

Object habitacion "Habitación"
  with description "Una habitación sencilla.",
  has light;

Object -> mesa "mesa"
  with name 'mesa',
       description "Una mesa de madera.",
  has female supporter;

Object -> libro "libro"
  with name 'libro',
       description "Un libro interesante.",
  has male;

[ Initialise;
  location = habitacion;
  print "¡Bienvenido al juego en español!^";
];
```

## 🔄 Historial de Versiones

- **v1.0** - Sistema modular completo
- **Limpieza** - Eliminación de duplicaciones
- **Correcciones** - Conjugaciones ER/IR completadas

## 🤝 Contribuir

1. Mantener compatibilidad con Inform 6.42+
2. Seguir estructura modular
3. Añadir tests para nuevas características
4. Documentar cambios

## 📄 Licencia

Compatible con la licencia de Inform 6 y la Standard Library.

---

**¿Problemas?** Verifica que includes están en orden: Parser.h → VerbLib.h → SpanishLib.h
