! ==============================================================================
! SPANISHLIBENTRY.H - Punto de entrada para SpanishLib con rutas corregidas
! ==============================================================================

System_file;

#Ifndef SPANISH_LIB_ENTRY_INCLUDED;
Constant SPANISH_LIB_ENTRY_INCLUDED;

! Configuración por defecto
#Ifndef SPANISH_MINIMAL;
    #Ifndef SPANISH_FULL_MESSAGES; Constant SPANISH_FULL_MESSAGES; #Endif;
    #Ifndef SPANISH_META_COMMANDS; Constant SPANISH_META_COMMANDS; #Endif;
    #Ifndef SPANISH_IRREGULAR_VERBS; Constant SPANISH_IRREGULAR_VERBS; #Endif;
    #Ifndef SPANISH_ADVANCED_PARSER; Constant SPANISH_ADVANCED_PARSER; #Endif;
#Endif;

! Incluir núcleo obligatorio
Include "SpanishLib/core/SpanishConstants.h";
Include "SpanishLib/core/SpanishCore.h";

! Parser avanzado opcional
#Ifdef SPANISH_ADVANCED_PARSER;
    Include "SpanishLib/core/SpanishParser1.h";
    Include "SpanishLib/core/SpanishParser2.h";
    Include "SpanishLib/core/SpanishParser3.h";
#Endif;

! Módulos core esenciales
Include "SpanishLib/core/SpanishGrammar.h";
Include "SpanishLib/core/SpanishVerbs.h";

! Recursos opcionales
#Ifdef SPANISH_FULL_MESSAGES;
    Include "SpanishLib/resources/SpanishMessages.h";
#Endif;

! Extensiones opcionales
#Ifdef SPANISH_IRREGULAR_VERBS;
    Include "SpanishLib/extensions/SpanishIrregularVerbs.h";
#Endif;

#Ifdef SPANISH_META_COMMANDS;
    Include "SpanishLib/extensions/SpanishMeta.h";
#Endif;

#Ifdef SPANISH_REGIONAL_VARIANTS;
    Include "SpanishLib/extensions/SpanishRegional.h";
#Endif;

Constant SPANISH_LIB_ENTRY_COMPLETE;

#Endif; ! SPANISH_LIB_ENTRY_INCLUDED