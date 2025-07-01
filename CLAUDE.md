# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

InformLibSP is a complete Spanish adaptation of the Inform 6 library (version 6.12.7) that provides comprehensive Spanish language support for interactive fiction games. This includes verb conjugation, gender/number agreement, spatial relationships, and fully translated system messages.

## Core Architecture

### Main Library Files
- **SpanishLib.h**: Main library file that orchestrates all Spanish language components
- **spanish.h**: Core Spanish language definitions 
- **SpanishMessages.h / SpanishMessagesExt.h**: System messages and extended spatial relationship messages
- **SpanishGrammar.h / SpanishGrammarExt.h**: Grammar definitions and spatial relationship extensions
- **SpanishVerbs.h**: Verb conjugation system with support for different tenses and persons
- **SpanishAdjectives.h**: Adjective agreement system for gender and number concordance
- **SpanishGender.h**: Gender and number utility functions (el/la/los/las, un/una, etc.)
- **SpanishAdverbs.h**: Spatial relationship and adverb handling system

### Configuration System
The library uses a modular configuration approach:
- **SPANISH_MINIMAL**: Loads only core functionality
- **SPANISH_FULL_MESSAGES**: Enables complete translated system messages
- **SPANISH_GRAMMAR**: Enables extended grammar for spatial relationships
- Default behavior loads all features if SPANISH_MINIMAL is not defined

### Key Language Features
- **Verb Conjugation**: Complete conjugation system with constants for tenses (TIEMPO_PRESENTE, TIEMPO_PRETERITO, etc.) and grammatical persons (PERSONA_YO, PERSONA_TU, etc.)
- **Gender/Number Agreement**: Automatic adjective and article agreement with object properties
- **Spatial Relationships**: Extended grammar for complex spatial commands (debajo de, encima de, cerca de, etc.)
- **Character Encoding**: Support for Spanish accented characters via Zcharacter table declarations

## Development Commands

### Compilation
```bash
# Compile an Inform 6 game
./inform6.exe -v8 filename.inf

# Compile with debug information
./inform6.exe -v8 -D filename.inf

# Compile targeting Glulx instead of Z-machine
./inform6.exe -G filename.inf
```

### Testing Examples
```bash
# Compile basic example
./inform6.exe -v8 ejemplo.inf

# Compile complete feature demonstration
./inform6.exe -v8 samples/EjemploCompleto.inf

# Compile accent handling example
./inform6.exe -v8 samples/EjemploAcentos.inf
```

## Code Structure Patterns

### Game Initialization Pattern
```inform6
[ Initialise;
    SpanishLibInitialise();           ! Initialize Spanish library
    SpanishLibShowConfiguration();    ! Optional: show loaded features
    location = StartingRoom;
];
```

### Character Encoding Declaration
All .inf files must start with Zcharacter table declaration before any includes:
```inform6
Zcharacter table + '@{E1}' '@{E9}' '@{ED}' '@{F3}' '@{FA}' '@{F1}' '@{DC}' '@{FC}' '@{BF}' '@{A1}';
```

### Library Include Order
```inform6
Include "Parser";
Include "VerbLib"; 
Include "SpanishLib";  ! Must come after Parser and VerbLib
```

### Verb Conjugation Usage
```inform6
ConjugarVerbo("hablar", TIEMPO_PRESENTE, PERSONA_EL);  ! Returns "habla"
ConjugarParaObjeto("brillar", objeto);                 ! Conjugates based on object properties
```

### Gender/Number Agreement Usage
```inform6
print (el) objeto, " ", (es) objeto, " ", (adj) "grande" objeto;  ! "El libro es grande"
print (esta_participio) "abierto" puerta;                        ! "La puerta está abierta"
```

### Spatial Relationships
```inform6
ImprimirRelacionEspacial(REL_DEBAJO, llaves, mesa);  ! "Las llaves están debajo de la mesa"
```

## Important Caveats

### Dictionary Alignment Issue
There's a known Inform 6 parser issue when the dictionary spans the $8000 mark. When using grammar properties that return negative values (typically for NPC command parsing), set `parser_one = true` before returning the negative value. This is documented in caveats.txt with a complete example.

### Character Encoding Requirements
Spanish accented characters must be explicitly declared in the Zcharacter table. Missing character declarations will cause compilation errors. See docs/CaracteresEspeciales.md for complete reference.

### Library Dependencies
SpanishLib.h must be included after Parser.h and VerbLib.h. The library performs environment verification and will generate fatal errors if included in wrong order.

## Common Development Workflows

### Adding New Spatial Relationships
1. Define new REL_ constant in SpanishAdverbs.h
2. Add corresponding grammar in SpanishGrammarExt.h
3. Implement message handling in SpanishMessagesExt.h
4. Test with spatial relationship functions

### Creating Game Objects with Proper Gender/Number
```inform6
Object -> libro "libro"
    with name 'libro',
         gender G_MASCULINO,
         number NUM_SINGULAR,
    has ...;
```

### Handling Complex Verb Conjugations
For irregular verbs, add entries to the verb tables in SpanishVerbs.h following the existing pattern for verbs like "ser", "estar", "tener".