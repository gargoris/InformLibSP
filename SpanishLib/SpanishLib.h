! ==============================================================================
! SPANISHLIB.H - Librería Española Completa para Inform 6
! Punto de entrada único del sistema modular
! ==============================================================================

System_file;

#Ifndef SPANISH_LIB_MAIN_INCLUDED;
Constant SPANISH_LIB_MAIN_INCLUDED;

! Núcleo obligatorio
#Include "core/SpanishConstants.h"
#Include "core/SpanishCore.h"

! Extensiones opcionales automáticas
#Ifdef SPANISH_IRREGULAR_VERBS;
    #Include "extensions/SpanishIrregularVerbs.h"
#Endif;

#Ifdef SPANISH_META_COMMANDS;
    #Include "extensions/SpanishMeta.h"
#Endif;

#Ifdef SPANISH_REGIONAL_VARIANTS;
    #Include "extensions/SpanishRegional.h"
#Endif;

! Inicialización automática
[ SpanishLibInitialise;
    SpanishCoreInitialise();
    
    #Ifdef SPANISH_IRREGULAR_VERBS;
        SpanishIrregularVerbsInitialise();
    #Endif;
    
    #Ifdef SPANISH_META_COMMANDS;
        SpanishMetaInitialise();
    #Endif;
    
    print "^[Spanish Library v6.12.7-modular lista para usar]^";
];

#Endif;