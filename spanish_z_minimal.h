! ==============================================================================
! SPANISH_Z_MINIMAL.H - Versión ultra-mínima para Z-machine
! ==============================================================================
! Esta versión está diseñada específicamente para el límite de 15 variables
! locales de la Z-machine, sacrificando funcionalidad por compatibilidad.
!
! USO: Include "spanish_z_minimal"; en lugar de usar +language_name=spanish
!
! LIMITACIONES:
! - Solo verbos básicos (sin conjugación completa)
! - Sin análisis sintáctico avanzado
! - Sin meta-comandos
! - Sin mensajes completos del sistema
! ==============================================================================

#Ifndef SPANISH_Z_MINIMAL_INCLUDED;
Constant SPANISH_Z_MINIMAL_INCLUDED;

! Forzar modo mínimo
Constant SPANISH_MINIMAL;
#Ifndef SPANISH_MINIMAL; Constant SPANISH_MINIMAL; #Endif;

! Desactivar todas las características avanzadas
#Ifdef SPANISH_FULL_MESSAGES; #Undef SPANISH_FULL_MESSAGES; #Endif;
#Ifdef SPANISH_META_COMMANDS; #Undef SPANISH_META_COMMANDS; #Endif;
#Ifdef SPANISH_IRREGULAR_VERBS; #Undef SPANISH_IRREGULAR_VERBS; #Endif;
#Ifdef SPANISH_REGIONAL_VARIANTS; #Undef SPANISH_REGIONAL_VARIANTS; #Endif;
#Ifdef SPANISH_ADVANCED_PARSER; #Undef SPANISH_ADVANCED_PARSER; #Endif;

! ==============================================================================
! CARACTERES BÁSICOS (sin Zcharacter - solo compatibilidad básica)
! ==============================================================================

! Buffer global compartido para reducir variables locales
Array spanish_minimal_buffer -> 32;

! ==============================================================================
! VERBOS BÁSICOS MÍNIMOS - Solo los más esenciales
! ==============================================================================

[ LanguageIsVerb word;
    ! Lista ultra-reducida de verbos - solo los más básicos
    if (word == 'tomar' or 'coger') return true;
    if (word == 'dejar' or 'soltar') return true;
    if (word == 'mirar' or 'ver') return true;
    if (word == 'examinar') return true;
    if (word == 'ir' or 'caminar') return true;
    if (word == 'abrir') return true;
    if (word == 'cerrar') return true;
    if (word == 'inventario') return true;
    
    return false; ! Sin detección por terminación para ahorrar variables
];

! ==============================================================================
! GRAMMAR MÍNIMA
! ==============================================================================

[ EsGeneroMasculino obj;
    if (obj has male) return true;
    if (obj has female) return false;
    return true; ! Por defecto masculino
];

[ EsPlural obj;
    return (obj has pluralname);
];

! ==============================================================================
! ARTÍCULOS ULTRA-SIMPLIFICADOS
! ==============================================================================

[ ImprimirArticuloDefinido obj;
    if (EsPlural(obj)) {
        print "los ";
        return;
    }
    if (EsGeneroMasculino(obj)) print "el ";
    else print "la ";
];

[ ImprimirArticuloIndefinido obj;
    if (EsPlural(obj)) {
        print "unos ";
        return;
    }
    if (EsGeneroMasculino(obj)) print "un ";
    else print "una ";
];

! ==============================================================================
! INTERFAZ MÍNIMA PARA COMPATIBILIDAD
! ==============================================================================

[ LanguagePronouns; ];

[ LanguageDescriptors; ];

[ LanguageNumbers n f;
    switch (n) {
        1: print "uno";
        2: print "dos";
        3: print "tres";
        4: print "cuatro";
        5: print "cinco";
        default: print n;
    }
];

[ LanguageLM n x1 x2;
    ! Mensajes ultra-básicos en español
    switch (n) {
        1: print "^"; ! Nuevo turno
        4: print "No he entendido esa frase.";
        5: print "Solo he entendido hasta: ";
        10: print "No he entendido nada.";
        16: print "No puedes verlo.";
        17: print "No puedes hacer eso.";
        default: print "OK.";
    }
];

! ==============================================================================
! STUB FUNCTIONS para evitar errores de compilación
! ==============================================================================

[ SpanishLibInitialise; 
    print "[Librería española Z-minimal activa]^";
];

[ SpanishBasicParsing; ];

[ LanguageToInformese; ];

[ LanguageInitialise; 
    SpanishLibInitialise();
];

#Endif; ! SPANISH_Z_MINIMAL_INCLUDED

! ==============================================================================
! MENSAJE INFORMATIVO
! ==============================================================================
Message "Spanish Z-minimal v1.0 - Optimizado para Z-machine";