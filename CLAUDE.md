# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is **InformLibSP** - a Spanish language library for Inform 6, providing complete Spanish language support for interactive fiction development. It's an adaptation of the standard Inform 6 library (version 6.12.7dev) that enables creating text adventures in Spanish while maintaining compatibility with the original English Inform 6 system.

The project has evolved into a **dual architecture**:

1. **Legacy System** (root directory): Original INFSP6-based files for backward compatibility
2. **Modern Modular System** (`SpanishLib/`): New design with single entry point and optional features

## Core Architecture

### Modern Modular System (`SpanishLib/`)

Single entry point with optional features:

1. **`SpanishLib.h`** - Main entry point that orchestrates all modules
2. **`core/`** - Essential components (Constants, Core, Parser, Verbs, Grammar)
3. **`extensions/`** - Optional features (IrregularVerbs, Meta-commands, Regional variants)
4. **`resources/`** - Message system (~400 translated messages)

Both systems provide:

- Complete Spanish language support with accents and special characters
- Gender and number agreement (masculine/feminine, singular/plural)
- Irregular verb conjugation support
- Dialect support (Castilian vs. Latin American Spanish)
- Automatic accent removal for user input processing

## Compilation and Development

### Essential Compilation Command

To compile games using this Spanish library, use:

```bash
inform6 +language_name=Spanish your_game.inf
```

The `+language_name=Spanish` flag is **essential** - it tells Inform 6 to use Spanish language files instead of default English ones.

### Development Testing Workflow

Test changes using example games:

```bash
# Compile and test a simple example
cd ejemplos
inform6 +language_name=Spanish rioja_simple.inf

# Test with Z-machine interpreter
inform6 +language_name=Spanish simple.inf
```

Example games in `ejemplos/` serve as integration tests for library functionality.

### Game Structure Patterns

#### Legacy System

```inform
Include "infspr";    ! Include Spanish parser functions first
! ... game objects and logic ...
Include "SpanishG";  ! Include Spanish grammar at the end
```

#### Modern System

```inform
Include "Parser";
Include "VerbLib";

! Optional feature configuration
Constant SPANISH_FULL_MESSAGES;
Constant SPANISH_META_COMMANDS;
Constant SPANISH_IRREGULAR_VERBS;

Include "SpanishLib";  ! Single include for everything
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

- **Root directory**: Legacy library files (`spanish.h`, `infspr.h`, `spanishg.h`)
- **`SpanishLib/`**: Modern modular system with single entry point
- **`ejemplos/`**: Example games serving as integration tests
- **`lib_corregida/`**: Corrected/updated library versions
- **`made_with_claude/`**: Examples created during development
- **`ejemplos/infsp6-master/`**: Original INFSP6 project files with documentation

### Critical Include Dependencies

**Modern system**: `Parser.h` → `VerbLib.h` → `SpanishLib.h` (order matters)
**Legacy system**: `infspr.h` first, `SpanishG.h` last

## Development Notes

This library is based on the original INFSP (Inform in Spanish) project and maintains backward compatibility with the English Inform 6 system. The approach preserves the original Inform 6 parser core while providing comprehensive Spanish language support through language definition files.

### Key Development Principles

- **Dual compatibility**: Both legacy and modern systems must remain functional
- **Include order critical**: Wrong order causes compilation failures
- **Example-driven testing**: Use `ejemplos/` games to verify changes
- **Modular design**: Modern system uses optional feature constants for clean builds

### When Working on This Codebase

1. **Always use** `+language_name=Spanish` compilation flag
2. **Test changes** using example games in `ejemplos/`
3. **Maintain compatibility** between legacy and modern systems
4. **Verify include order** when modifying headers
5. **Use SpanishLib.h** for new development (modern system preferred)
