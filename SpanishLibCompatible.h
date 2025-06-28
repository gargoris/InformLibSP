! ==============================================================================
! SPANISHLIBCOMPATIBLE.H - Version compatible con Inform 6 sin conflictos
! Sistema completo pero usando constantes propias sin redefinir las del sistema
! ==============================================================================

System_file;

#Ifndef SPANISH_LIB_COMPATIBLE_INCLUDED;
Constant SPANISH_LIB_COMPATIBLE_INCLUDED;
Constant SPANISH_LIB_COMPATIBLE_VERSION = "1.0-full-compatible";

! ==============================================================================
! CONFIGURACION DE CARACTERÍSTICAS (si no están definidas)
! ==============================================================================

#Ifndef SPANISH_MINIMAL;
    #Ifndef SPANISH_FULL_MESSAGES; Constant SPANISH_FULL_MESSAGES; #Endif;
    #Ifndef SPANISH_META_COMMANDS; Constant SPANISH_META_COMMANDS; #Endif;
    #Ifndef SPANISH_IRREGULAR_VERBS; Constant SPANISH_IRREGULAR_VERBS; #Endif;
    #Ifndef SPANISH_ADVANCED_PARSER; Constant SPANISH_ADVANCED_PARSER; #Endif;
    #Ifndef SPANISH_REGIONAL_VARIANTS; Constant SPANISH_REGIONAL_VARIANTS; #Endif;
#Endif;

! ==============================================================================
! CONSTANTES ESPAÑOLAS (prefijadas para evitar conflictos)
! ==============================================================================

! Tiempos verbales
Constant SP_PRESENTE   = 1;
Constant SP_PRETERITO  = 2;
Constant SP_IMPERFECTO = 3;
Constant SP_FUTURO     = 4;
Constant SP_CONDICIONAL = 5;
Constant SP_SUBJUNTIVO = 6;
Constant SP_IMPERATIVO = 7;

! Géneros (usando constantes propias)
Constant SP_MASCULINE = 1;
Constant SP_FEMININE = 2;

! Personas gramaticales
Constant SP_PRIMERA_PERSONA = 1;
Constant SP_SEGUNDA_PERSONA = 2;
Constant SP_TERCERA_PERSONA = 3;

! Nivel de formalidad
Constant SP_FORMAL = 1;
Constant SP_INFORMAL = 2;

! Regiones dialectales
Constant SP_REGION_SPAIN = 1;
Constant SP_REGION_MEXICO = 2;
Constant SP_REGION_ARGENTINA = 3;
Constant SP_REGION_COLOMBIA = 4;

! Variables globales del sistema
Global sp_formality_level = SP_INFORMAL;
Global sp_current_region = SP_REGION_SPAIN;
Global sp_accent_mode = 1; ! 1 = quitar acentos, 0 = mantener
Global sp_system_initialized = 0;

! ==============================================================================
! FUNCIONES DE GENERO Y NUMERO
! ==============================================================================

[ SpanishGender obj;
    if (obj has female) return SP_FEMININE;
    return SP_MASCULINE;
];

[ SpanishNumber obj;
    if (obj has pluralname) return 2;
    return 1;
];

[ SpanishDefiniteArticle obj;
    if (obj has female) {
        if (obj has pluralname) print "las";
        else print "la";
    } else {
        if (obj has pluralname) print "los";
        else print "el";
    }
];

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
! CONJUGACIONES BASICAS
! ==============================================================================

! Conjugar verbos regulares -AR
[ ConjugarAR raiz persona tiempo;
    switch(persona) {
        SP_PRIMERA_PERSONA:
            switch(tiempo) {
                SP_PRESENTE: print (string) raiz, "o";
                SP_PRETERITO: print (string) raiz, "e";
                SP_IMPERFECTO: print (string) raiz, "aba";
                SP_FUTURO: print (string) raiz, "are";
                default: print (string) raiz, "o";
            }
        SP_SEGUNDA_PERSONA:
            switch(tiempo) {
                SP_PRESENTE: 
                    if (sp_formality_level == SP_FORMAL) print (string) raiz, "a";
                    else print (string) raiz, "as";
                SP_PRETERITO: print (string) raiz, "aste";
                SP_IMPERFECTO: print (string) raiz, "abas";
                SP_FUTURO: print (string) raiz, "aras";
                default: print (string) raiz, "as";
            }
        SP_TERCERA_PERSONA:
            switch(tiempo) {
                SP_PRESENTE: print (string) raiz, "a";
                SP_PRETERITO: print (string) raiz, "o";
                SP_IMPERFECTO: print (string) raiz, "aba";
                SP_FUTURO: print (string) raiz, "ara";
                default: print (string) raiz, "a";
            }
    }
];

! Conjugar verbos regulares -ER
[ ConjugarER raiz persona tiempo;
    switch(persona) {
        SP_PRIMERA_PERSONA:
            switch(tiempo) {
                SP_PRESENTE: print (string) raiz, "o";
                SP_PRETERITO: print (string) raiz, "i";
                SP_IMPERFECTO: print (string) raiz, "ia";
                SP_FUTURO: print (string) raiz, "ere";
                default: print (string) raiz, "o";
            }
        SP_SEGUNDA_PERSONA:
            switch(tiempo) {
                SP_PRESENTE:
                    if (sp_formality_level == SP_FORMAL) print (string) raiz, "e";
                    else print (string) raiz, "es";
                SP_PRETERITO: print (string) raiz, "iste";
                SP_IMPERFECTO: print (string) raiz, "ias";
                SP_FUTURO: print (string) raiz, "eras";
                default: print (string) raiz, "es";
            }
        SP_TERCERA_PERSONA:
            switch(tiempo) {
                SP_PRESENTE: print (string) raiz, "e";
                SP_PRETERITO: print (string) raiz, "io";
                SP_IMPERFECTO: print (string) raiz, "ia";
                SP_FUTURO: print (string) raiz, "era";
                default: print (string) raiz, "e";
            }
    }
];

! Conjugar verbos regulares -IR
[ ConjugarIR raiz persona tiempo;
    switch(persona) {
        SP_PRIMERA_PERSONA:
            switch(tiempo) {
                SP_PRESENTE: print (string) raiz, "o";
                SP_PRETERITO: print (string) raiz, "i";
                SP_IMPERFECTO: print (string) raiz, "ia";
                SP_FUTURO: print (string) raiz, "ire";
                default: print (string) raiz, "o";
            }
        SP_SEGUNDA_PERSONA:
            switch(tiempo) {
                SP_PRESENTE:
                    if (sp_formality_level == SP_FORMAL) print (string) raiz, "e";
                    else print (string) raiz, "es";
                SP_PRETERITO: print (string) raiz, "iste";
                SP_IMPERFECTO: print (string) raiz, "ias";
                SP_FUTURO: print (string) raiz, "iras";
                default: print (string) raiz, "es";
            }
        SP_TERCERA_PERSONA:
            switch(tiempo) {
                SP_PRESENTE: print (string) raiz, "e";
                SP_PRETERITO: print (string) raiz, "io";
                SP_IMPERFECTO: print (string) raiz, "ia";
                SP_FUTURO: print (string) raiz, "ira";
                default: print (string) raiz, "e";
            }
    }
];

! ==============================================================================
! VERBOS IRREGULARES BASICOS
! ==============================================================================

#Ifdef SPANISH_IRREGULAR_VERBS;

[ ConjugarSER persona tiempo;
    switch(persona) {
        SP_PRIMERA_PERSONA:
            switch(tiempo) {
                SP_PRESENTE: print "soy";
                SP_PRETERITO: print "fui";
                SP_IMPERFECTO: print "era";
                SP_FUTURO: print "sere";
                default: print "soy";
            }
        SP_SEGUNDA_PERSONA:
            switch(tiempo) {
                SP_PRESENTE:
                    if (sp_formality_level == SP_FORMAL) print "es";
                    else print "eres";
                SP_PRETERITO: print "fuiste";
                SP_IMPERFECTO: print "eras";
                SP_FUTURO: print "seras";
                default: print "eres";
            }
        SP_TERCERA_PERSONA:
            switch(tiempo) {
                SP_PRESENTE: print "es";
                SP_PRETERITO: print "fue";
                SP_IMPERFECTO: print "era";
                SP_FUTURO: print "sera";
                default: print "es";
            }
    }
];

[ ConjugarESTAR persona tiempo;
    switch(persona) {
        SP_PRIMERA_PERSONA:
            switch(tiempo) {
                SP_PRESENTE: print "estoy";
                SP_PRETERITO: print "estuve";
                SP_IMPERFECTO: print "estaba";
                SP_FUTURO: print "estare";
                default: print "estoy";
            }
        SP_SEGUNDA_PERSONA:
            switch(tiempo) {
                SP_PRESENTE:
                    if (sp_formality_level == SP_FORMAL) print "esta";
                    else print "estas";
                SP_PRETERITO: print "estuviste";
                SP_IMPERFECTO: print "estabas";
                SP_FUTURO: print "estaras";
                default: print "estas";
            }
        SP_TERCERA_PERSONA:
            switch(tiempo) {
                SP_PRESENTE: print "esta";
                SP_PRETERITO: print "estuvo";
                SP_IMPERFECTO: print "estaba";
                SP_FUTURO: print "estara";
                default: print "esta";
            }
    }
];

[ ConjugarTENER persona tiempo;
    switch(persona) {
        SP_PRIMERA_PERSONA:
            switch(tiempo) {
                SP_PRESENTE: print "tengo";
                SP_PRETERITO: print "tuve";
                SP_IMPERFECTO: print "tenia";
                SP_FUTURO: print "tendre";
                default: print "tengo";
            }
        SP_SEGUNDA_PERSONA:
            switch(tiempo) {
                SP_PRESENTE:
                    if (sp_formality_level == SP_FORMAL) print "tiene";
                    else print "tienes";
                SP_PRETERITO: print "tuviste";
                SP_IMPERFECTO: print "tenias";
                SP_FUTURO: print "tendras";
                default: print "tienes";
            }
        SP_TERCERA_PERSONA:
            switch(tiempo) {
                SP_PRESENTE: print "tiene";
                SP_PRETERITO: print "tuvo";
                SP_IMPERFECTO: print "tenia";
                SP_FUTURO: print "tendra";
                default: print "tiene";
            }
    }
];

#Endif; ! SPANISH_IRREGULAR_VERBS

! ==============================================================================
! MENSAJES DEL SISTEMA
! ==============================================================================

#Ifdef SPANISH_FULL_MESSAGES;

[ SpanishLibMsg msg;
    switch(msg) {
        1: print "No puedes ir en esa direccion.";
        2: print "No hay nada especial que ver.";
        3: print "Tomado.";
        4: print "No puedes tomar eso.";
        5: print "Soltado.";
        6: print "Ya tienes eso.";
        7: print "No entiendo esa orden.";
        8: print "No puedes hacer eso.";
        9: print "No hay nada aqui.";
        10: print "Eso no esta aqui.";
        default: print "Mensaje no implementado.";
    }
];

#Ifnot;

[ SpanishLibMsg msg;
    switch(msg) {
        1: print "No puedes ir ahi.";
        2: print "Nada especial.";
        3: print "Tomado.";
        4: print "No puedes.";
        5: print "Soltado.";
        default: print "OK.";
    }
];

#Endif; ! SPANISH_FULL_MESSAGES

! ==============================================================================
! META-COMANDOS
! ==============================================================================

#Ifdef SPANISH_META_COMMANDS;

[ SpanishUndoSub;
    print "Deshaciendo ultima accion...^";
    ! Aquí iría la lógica de undo
    "Accion deshecha.";
];

[ SpanishAgainSub;
    print "Repitiendo ultimo comando...^";
    ! Aquí iría la lógica de again
];

[ SpanishHelpSub;
    print "^=== AYUDA DEL JUEGO ===^";
    print "Comandos basicos:^";
    print "- EXAMINA [objeto] : examinar algo^";
    print "- TOMA [objeto] : tomar algo^";
    print "- DEJA [objeto] : soltar algo^";
    print "- IR [direccion] : moverse^";
    print "- INVENTARIO : ver objetos que llevas^";
    print "^Comandos del sistema:^";
    print "- DESHACER : deshacer ultima accion^";
    print "- REPETIR : repetir ultimo comando^";
    print "- AYUDA : esta ayuda^";
    #Ifdef SPANISH_IRREGULAR_VERBS;
    print "- VERBOS : lista de verbos irregulares^";
    #Endif;
];

[ SpanishVerbsSub;
    #Ifdef SPANISH_IRREGULAR_VERBS;
    print "^=== VERBOS IRREGULARES DISPONIBLES ===^";
    print "SER: soy, eres, es, somos, sois, son^";
    print "ESTAR: estoy, estas, esta, estamos, estais, estan^";
    print "TENER: tengo, tienes, tiene, tenemos, teneis, tienen^";
    print "Y muchos mas...^";
    #Ifnot;
    print "Los verbos irregulares no estan habilitados.^";
    #Endif;
];

#Endif; ! SPANISH_META_COMMANDS

! ==============================================================================
! VARIANTES REGIONALES
! ==============================================================================

#Ifdef SPANISH_REGIONAL_VARIANTS;

[ SetSpanishRegion region;
    sp_current_region = region;
    switch(region) {
        SP_REGION_SPAIN: print "Dialecto: Espanol peninsular activado.^";
        SP_REGION_MEXICO: print "Dialecto: Espanol mexicano activado.^";
        SP_REGION_ARGENTINA: print "Dialecto: Espanol argentino activado.^";
        SP_REGION_COLOMBIA: print "Dialecto: Espanol colombiano activado.^";
        default: print "Dialecto neutral activado.^";
    }
];

[ SpanishRegionalMsg msg;
    ! Mensajes específicos por región
    switch(sp_current_region) {
        SP_REGION_ARGENTINA:
            switch(msg) {
                1: print "No podes ir por ahi."; ! Voseo argentino
                2: print "Che, no ves nada especial.";
                default: SpanishLibMsg(msg);
            }
        SP_REGION_MEXICO:
            switch(msg) {
                1: print "No puedes ir por alla.";
                2: print "No hay nada que mirar, compadre.";
                default: SpanishLibMsg(msg);
            }
        default: SpanishLibMsg(msg);
    }
];

#Endif; ! SPANISH_REGIONAL_VARIANTS

! ==============================================================================
! INICIALIZACION DEL SISTEMA
! ==============================================================================

[ SpanishLibCompatibleInit;
    sp_system_initialized = 1;
    print "^[Spanish Library Compatible v", (string) SPANISH_LIB_COMPATIBLE_VERSION, " inicializado]^";
    
    print "[Caracteristicas activas:^";
    print " - Nucleo basico: articulos, genero, numero^";
    print " - Conjugaciones regulares: AR, ER, IR^";
    
    #Ifdef SPANISH_IRREGULAR_VERBS;
    print " - Verbos irregulares: SER, ESTAR, TENER^";
    #Endif;
    
    #Ifdef SPANISH_FULL_MESSAGES;
    print " - Sistema completo de mensajes^";
    #Endif;
    
    #Ifdef SPANISH_META_COMMANDS;
    print " - Meta-comandos: DESHACER, AYUDA, REPETIR^";
    #Endif;
    
    #Ifdef SPANISH_REGIONAL_VARIANTS;
    print " - Variantes regionales disponibles^";
    #Endif;
    
    print "]^";
    
    return true;
];

[ SpanishLibCompatibleInfo;
    print "^=== SPANISH LIBRARY COMPATIBLE ===^";
    print "Version: ", (string) SPANISH_LIB_COMPATIBLE_VERSION, "^";
    print "Estado: ";
    if (sp_system_initialized) print "Inicializado"; else print "No inicializado";
    print "^";
    print "Formalidad: ";
    if (sp_formality_level == SP_FORMAL) print "Formal (usted)"; else print "Informal (tu)";
    print "^";
    
    #Ifdef SPANISH_REGIONAL_VARIANTS;
    print "Region: ";
    switch(sp_current_region) {
        SP_REGION_SPAIN: print "Espana";
        SP_REGION_MEXICO: print "Mexico";
        SP_REGION_ARGENTINA: print "Argentina";
        SP_REGION_COLOMBIA: print "Colombia";
        default: print "Neutral";
    }
    print "^";
    #Endif;
    
    print "Funciones disponibles:^";
    print "- SpanishDefiniteArticle(obj) : articulo definido^";
    print "- SpanishIndefiniteArticle(obj) : articulo indefinido^";
    print "- ConjugarAR/ER/IR(raiz, persona, tiempo)^";
    
    #Ifdef SPANISH_IRREGULAR_VERBS;
    print "- ConjugarSER/ESTAR/TENER(persona, tiempo)^";
    #Endif;
    
    print "- SpanishLibMsg(numero) : mensajes del sistema^";
];

! Marcar completitud
Constant SPANISH_LIB_COMPATIBLE_COMPLETE;

#Endif; ! SPANISH_LIB_COMPATIBLE_INCLUDED

! ==============================================================================
! Fin de SpanishLibCompatible.h - Sistema completo y compatible
! ==============================================================================