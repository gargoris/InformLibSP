! PunyInform en Español: Una librería completa para ficción interactiva en español
! Basada en PunyInform pero completamente adaptada para el idioma español
! Diseñada para interpretar español en toda su extensión verbal, adjetival y adverbial

! Comentar/descomentar para restringir mensajes de debug por defecto
!Constant DEBUG_PARSEANDPERFORM;
!Constant DEBUG_PARSETOKEN;
!Constant DEBUG_PARSEPATTERN;
!Constant DEBUG_PARSENOUNPHRASE;
!Constant DEBUG_GETNEXTNOUN;
!Constant DEBUG_SCOPE;

System_file;

! Incluir archivos base de PunyInform (sin modificar)
Include "globals.h";

! Incluir nuestros archivos españoles
Include "spanish/messages_spanish.h";
Include "spanish/grammar_spanish.h";
Include "spanish/parser_spanish.h";

! Incluir scope.h sin modificaciones (manejo de ámbito)
Include "scope.h";

! ######################### Funciones auxiliares españolas

[ EsPlural p_obj;
    if (p_obj has pluralname) rtrue;
    rfalse;
];

[ EsFemenino p_obj;
    if (p_obj has female) rtrue;
    rfalse;
];

[ EsAnimado p_obj;
    if (p_obj has animate) rtrue;
    rfalse;
];

! Artículos definidos: el, la, los, las
[ ElLaLosLas p_obj;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "las";
        else print "los";
    } else {
        if (EsFemenino(p_obj)) print "la";
        else print "el";
    }
];

! Artículos indefinidos: un, una, unos, unas
[ UnUnaUnosUnas p_obj;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "unas";
        else print "unos";
    } else {
        if (EsFemenino(p_obj)) print "una";
        else print "un";
    }
];

! Demostrativos: este/esta/estos/estas
[ EsteEstaEstosEstas p_obj;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "estas";
        else print "estos";
    } else {
        if (EsFemenino(p_obj)) print "esta";
        else print "este";
    }
];

! Demostrativos: ese/esa/esos/esas  
[ EseEsaEsosEsas p_obj;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "esas";
        else print "esos";
    } else {
        if (EsFemenino(p_obj)) print "esa";
        else print "ese";
    }
];

! Pronombres: lo/la/los/las
[ LoLaLosLas p_obj;
    if (p_obj == player) { print "te"; rtrue; }
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "las";
        else print "los";
    } else {
        if (EsFemenino(p_obj)) print "la";
        else print "lo";
    }
];

! Pronombres sujeto: él/ella/ellos/ellas
[ ElEllaEllosEllas p_obj;
    if (p_obj == player) { print "tú"; rtrue; }
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "ellas";
        else print "ellos";
    } else {
        if (EsFemenino(p_obj)) print "ella";
        else print "él";
    }
];

! Conjugación del verbo "estar": está/están
[ EstaEstan p_obj;
    if (EsPlural(p_obj) || p_obj == player) print "están";
    else print "está";
];

! Conjugación del verbo "ser": es/son
[ EsSon p_obj;
    if (EsPlural(p_obj) || p_obj == player) print "son";
    else print "es";
];

! Terminaciones de género para adjetivos: -o/-a/-os/-as
[ TerminacionAdjetivo p_obj p_raiz;
    print (string) p_raiz;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "as";
        else print "os";
    } else {
        if (EsFemenino(p_obj)) print "a";
        else print "o";
    }
];

! ######################### Funciones de impresión mejoradas

[ ImprimirNombre p_obj;
    if (p_obj.&short_name && PrintOrRun(p_obj, short_name, 1)) rtrue;
    print (object) p_obj;
];

[ ImprimirConArticulo p_obj;
    ElLaLosLas(p_obj);
    print " ";
    ImprimirNombre(p_obj);
];

[ ImprimirConArticuloIndefinido p_obj;
    UnUnaUnosUnas(p_obj);
    print " ";
    ImprimirNombre(p_obj);
];

! ######################### Sistema de conjugación verbal

! Terminaciones verbales regulares
Array TerminacionesAR static -->
    "o" "as" "a" "amos" "áis" "an";           ! presente
Array TerminacionesER static -->
    "o" "es" "e" "emos" "éis" "en";           ! presente
Array TerminacionesIR static -->
    "o" "es" "e" "imos" "ís" "en";            ! presente

[ ConjugarVerboRegular p_raiz p_tipo p_persona;
    ! p_tipo: 1=AR, 2=ER, 3=IR
    ! p_persona: 0=yo, 1=tú, 2=él/ella, 3=nosotros, 4=vosotros, 5=ellos/ellas
    print (string) p_raiz;
    switch(p_tipo) {
        1: print (string) TerminacionesAR-->p_persona;
        2: print (string) TerminacionesER-->p_persona;
        3: print (string) TerminacionesIR-->p_persona;
    }
];

! ######################### Rutina principal de inicialización

[ InicializarEspanol;
    ! Las constantes ya están definidas en globals.h
    ! Solo configurar si es necesario
    print ""; ! Funcion vacia por ahora
];

! ######################### Rutinas de conversión de objetos direccionales

[ DirPropToFakeObj p_prop;
    ! Convierte una propiedad direccional a objeto falso
    switch(p_prop) {
        n_to: return FAKE_N_OBJ;
        s_to: return FAKE_S_OBJ;
        e_to: return FAKE_E_OBJ;
        w_to: return FAKE_W_OBJ;
        ne_to: return FAKE_NE_OBJ;
        nw_to: return FAKE_NW_OBJ;
        se_to: return FAKE_SE_OBJ;
        sw_to: return FAKE_SW_OBJ;
        u_to: return FAKE_U_OBJ;
        d_to: return FAKE_D_OBJ;
        in_to: return FAKE_IN_OBJ;
        out_to: return FAKE_OUT_OBJ;
    }
#IfTrue RUNTIME_ERRORS > RTE_MINIMUM;
    _RunTimeError(ERR_NOT_DIR_PROP, p_prop);
#EndIf;
    rfalse;
];

[ FakeObjToDirProp p_obj;
    ! Convierte un objeto falso a propiedad direccional
    switch(p_obj) {
        FAKE_N_OBJ: return n_to;
        FAKE_S_OBJ: return s_to;
        FAKE_E_OBJ: return e_to;
        FAKE_W_OBJ: return w_to;
        FAKE_NE_OBJ: return ne_to;
        FAKE_NW_OBJ: return nw_to;
        FAKE_SE_OBJ: return se_to;
        FAKE_SW_OBJ: return sw_to;
        FAKE_U_OBJ: return u_to;
        FAKE_D_OBJ: return d_to;
        FAKE_IN_OBJ: return in_to;
        FAKE_OUT_OBJ: return out_to;
    }
#IfTrue RUNTIME_ERRORS > RTE_MINIMUM;
    _RunTimeError(ERR_NOT_FAKE_OBJ, p_obj);
#EndIf;
    rfalse;
];

! ######################### Incluir el resto del núcleo de PunyInform

Include "puny.h";

! El juego debe definir su propia función Initialise que llame a InicializarEspanol()
! No definir Initialise aquí para evitar conflictos