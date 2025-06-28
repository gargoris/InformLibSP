! ==============================================================================
! SPANISHLIBSIMPLE.H - Versión simplificada sin conflictos
! ==============================================================================

System_file;

#Ifndef SPANISH_LIB_SIMPLE_INCLUDED;
Constant SPANISH_LIB_SIMPLE_INCLUDED;
Constant SPANISH_LIB_SIMPLE_VERSION = "1.0-compatible";

! ==============================================================================
! CONSTANTES ESPAÑOLAS ÚNICAS (sin conflictos con Inform 6)
! ==============================================================================

! Tiempos verbales específicos del español
Constant SPANISH_PRESENTE_T   = 1;
Constant SPANISH_PRETERITO_T  = 2;
Constant SPANISH_IMPERFECTO_T = 3;
Constant SPANISH_FUTURO_T     = 4;
Constant SPANISH_CONDICIONAL_T = 5;
Constant SPANISH_SUBJUNTIVO_T = 6;
Constant SPANISH_IMPERATIVO_T = 7;

! Géneros gramaticales
Constant SPANISH_MASCULINE = 1;
Constant SPANISH_FEMININE = 2;

! Personas gramaticales
Constant SPANISH_PRIMERA_PERSONA = 1;
Constant SPANISH_SEGUNDA_PERSONA = 2;
Constant SPANISH_TERCERA_PERSONA = 3;

! Números gramaticales (usar las constantes existentes de Inform)
! SINGULAR ya existe en Inform 6
! PLURAL ya existe como propiedad en Inform 6

! ==============================================================================
! FUNCIONES BÁSICAS DE GRAMÁTICA ESPAÑOLA
! ==============================================================================

! Determinar género de un objeto
[ SpanishGender obj;
    if (obj has female) return SPANISH_FEMININE;
    return SPANISH_MASCULINE;
];

! Determinar número de un objeto  
[ SpanishNumber obj;
    if (obj has pluralname) return 2; ! plural
    return 1; ! singular
];

! Artículo definido básico
[ SpanishDefiniteArticle obj;
    if (obj has female) {
        if (obj has pluralname) print "las";
        else print "la";
    } else {
        if (obj has pluralname) print "los";
        else print "el";
    }
];

! Artículo indefinido básico
[ SpanishIndefiniteArticle obj;
    if (obj has female) {
        if (obj has pluralname) print "unas";
        else print "una";
    } else {
        if (obj has pluralname) print "unos";
        else print "un";
    }
];

! ==============================================================================
! MENSAJES BÁSICOS EN ESPAÑOL
! ==============================================================================

[ SpanishLookMsg;
    print "No ves nada especial.";
];

[ SpanishTakeMsg;
    print "Tomado.";
];

[ SpanishDropMsg;
    print "Soltado.";
];

! ==============================================================================
! FUNCIONES DE INICIALIZACIÓN
! ==============================================================================

[ SpanishLibSimpleInit;
    print "^[SpanishLib Simple v", (string) SPANISH_LIB_SIMPLE_VERSION, " inicializado]^";
    return true;
];

! Información del sistema
[ SpanishLibSimpleInfo;
    print "^=== SPANISH LIB SIMPLE ===^";
    print "Version: ", (string) SPANISH_LIB_SIMPLE_VERSION, "^";
    print "Caracteristicas:^";
    print "- Articulos definidos e indefinidos^";
    print "- Genero y numero automatico^";
    print "- Mensajes basicos en espanol^";
    print "- Compatible con Inform 6.42^";
];

! Marcar completitud
Constant SPANISH_LIB_SIMPLE_COMPLETE;

#Endif; ! SPANISH_LIB_SIMPLE_INCLUDED

! ==============================================================================
! Fin de SpanishLibSimple.h
! ==============================================================================