# InformLibSP Information

## Summary
InformLibSP is a complete adaptation of the Inform 6 library (version 6.12.7) to Spanish language. It provides advanced support for verb conjugation, gender and number agreement, and context-adapted messages. The library enables developers to create interactive fiction games in Spanish with natural language processing capabilities.

## Structure
- **Root Directory**: Contains main header files for Spanish language support
- **docs/**: Documentation for special characters handling in Spanish
- **samples/**: Example implementations including Elena.h (complex NPC example)

## Language & Runtime
**Language**: Inform 6
**Version**: Based on Inform 6 Library 6.12.7
**Library Version**: 6.12.7-1.1 (Spanish adaptation)

## Core Components
- **spanish.h**: Base Spanish language definitions
- **SpanishLib.h**: Main entry point for the Spanish library
- **SpanishMessages.h/SpanishMessagesExt.h**: System messages in Spanish
- **SpanishGrammar.h/SpanishGrammarExt.h**: Spanish grammar rules
- **SpanishVerbs.h**: Verb conjugation system
- **SpanishAdjectives.h**: Adjective agreement system
- **SpanishGender.h**: Gender and number handling
- **SpanishAdverbs.h**: Adverbs and spatial prepositions

## Features
- **Verb Conjugation System**: Support for regular and irregular verbs in different tenses
- **Adjective Agreement**: Automatic adaptation of adjectives according to gender and number
- **Gender and Number Utilities**: Tools for correctly handling articles, prepositions, and endings
- **Spatial Adverbs and Prepositions**: Handling of spatial relationships for complex phrases
- **Extended Grammar**: Support for spatial relationship commands

## Installation
```inform
! Include in your Inform 6 project
Include "Parser";
Include "VerbLib";
Include "SpanishLib";
```

## Usage
```inform
[ Initialise;
    SpanishLibInitialise();
    SpanishLibShowConfiguration(); ! Optional
    location = StartingRoom;
];
```

## Configuration Options
**Minimal Configuration**:
```inform
Constant SPANISH_MINIMAL;      ! Disable all features
Include "SpanishLib";
```

**Selective Features**:
```inform
Constant SPANISH_MINIMAL;      ! Disable all features
Constant SPANISH_FULL_MESSAGES; ! Enable full messages
Include "SpanishLib";
```

## Special Characters Support
Requires explicit declaration of Spanish characters:
```inform
Zcharacter table + '@{E1}' '@{E9}' '@{ED}' '@{F3}' '@{FA}' '@{F1}' '@{DC}' '@{FC}' '@{BF}' '@{A1}';  ! á é í ó ú ñ Ü ü ¿ ¡
```

## License
Available under either:
- The traditional Inform license as described by the DM4
- The Artistic License 2.0

## Credits
- Original Inform 6 Library: Graham Nelson (1993-2004) and David Griffith (2012-2024)
- Spanish adaptation: Francisco Fuentes (2025)