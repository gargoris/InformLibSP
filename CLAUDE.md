# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is **InformLibSP** - a Spanish language library for Inform 6, providing complete Spanish language support for interactive fiction development. It's an adaptation of the standard Inform 6 library (version 6.12.7dev) that enables creating text adventures in Spanish while maintaining compatibility with the original English Inform 6 system.

## Core Architecture

The library consists of three main components:

1. **`spanish.h`** - Core Spanish language definitions (articles, pronouns, numbers, etc.)
2. **`infspr.h`** - Parser replacement functions adapted for Spanish language processing
3. **`spanishg.h`** - Spanish grammar definitions (verbs, commands, etc.)

These files work together to provide:
- Complete Spanish language support with accents and special characters
- Gender and number agreement (masculine/feminine, singular/plural)
- Irregular verb conjugation support
- Dialect support (Castilian vs. Latin American Spanish)
- Automatic accent removal for user input processing

## Compilation and Development

### Compiling Games

To compile games using this Spanish library, use:
```bash
inform6 +language_name=Spanish your_game.inf
```

The `+language_name=Spanish` flag is **essential** - it tells Inform 6 to use the Spanish language files instead of the default English ones.

### Game Structure

Inform 6 games using this library follow this include pattern:
```inform
Include "infspr";    ! Include Spanish parser functions first
! ... game objects and logic ...
Include "SpanishG";  ! Include Spanish grammar at the end
```

### Testing Games

Compiled games produce `.z5` or `.ulx` files that can be tested with:
- Z-machine interpreters for `.z5` files
- Glulx interpreters for `.ulx` files

## Key Language Features

### Gender and Number Attributes
Objects must be marked with appropriate gender and number:
```inform
Object mesa "mesa"
  with name 'mesa',
  has female;  ! Feminine object

Object libros "libros" 
  with name 'libros',
  has pluralname;  ! Plural object
```

### Dialect Support
The library supports two Spanish dialects:
- **Castilian** (default): Uses "coger" as the verb for taking objects
- **Latin American**: Avoids "coger" due to regional connotations

Players can switch dialects in-game with commands like `DIALECTO SUDAMERICANO` or `DIALECTO CASTELLANO`.

### Accent Handling
The library automatically removes accents from player input for easier parsing. This can be controlled with debug commands `ACENTOS ON/OFF`.

## File Organization

- **Root directory**: Main library files (`spanish.h`, `infspr.h`, `spanishg.h`)
- **`ejemplos/`**: Example games demonstrating library usage
- **`lib_corregida/`**: Corrected/updated library versions
- **`ejemplos/infsp6-master/`**: Original INFSP6 project files with documentation

## Development Notes

This library is based on the original INFSP (Inform in Spanish) project and maintains backward compatibility with the English Inform 6 system. The approach preserves the original Inform 6 parser core while providing comprehensive Spanish language support through language definition files.

When working with this codebase, always ensure the Spanish language files are properly included and the `+language_name=Spanish` compilation flag is used for any Spanish language games.