! PunyInform Español - Versión Master Definitiva
! La librería más completa y avanzada para ficción interactiva en español
! Integra conjugaciones, concordancia, mensajes y funciones auxiliares
!
! Autor: Claude Code
! Fecha: 4 de julio de 2025
! Versión: 1.0 Master

System_file;

! Comentar/descomentar para debug
!Constant DEBUG_PARSEANDPERFORM;
!Constant DEBUG_PARSETOKEN; 
!Constant DEBUG_PARSEPATTERN;

! ######################### INCLUIR ARCHIVOS BASE DE PUNYINFORM

Include "globals.h";

! ######################### INCLUIR NUESTRO SISTEMA ESPAÑOL COMPLETO
Zcharacter table '@{E1}' '@{E9}' '@{ED}' '@{F3}' '@{FA}' '@{FC}' '@{F1}' 
                 '@{C1}' '@{C9}' '@{CD}' '@{D3}' '@{DA}' '@{DC}' '@{D1}'
                 '@{BF}' '@{A1}' '@{C3}' '@{B1}' '@{C2}' '@{BA}' '@{A9}'
                 '@{B3}';

Include "messages_spanish_master.h";
Include "grammar_spanish_master.h"; 
Include "parser_spanish_master.h";

Include "scope.h";

! ######################### FUNCIONES AUXILIARES ESPAÑOLAS AVANZADAS

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

[ EsMasculino p_obj;
    if (p_obj hasnt female) rtrue;
    rfalse;
];

[ EsPersona p_obj;
    if (p_obj == player) rtrue;
    if (p_obj has animate && p_obj hasnt neuter) rtrue;
    rfalse;
];

! ######################### ARTÍCULOS DEFINIDOS

[ ElLaLosLas p_obj;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "las";
        else print "los";
    } else {
        if (EsFemenino(p_obj)) print "la";
        else print "el";
    }
];

! ######################### ARTÍCULOS INDEFINIDOS

[ UnUnaUnosUnas p_obj;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "unas";
        else print "unos";
    } else {
        if (EsFemenino(p_obj)) print "una";
        else print "un";
    }
];

! ######################### DEMOSTRATIVOS

[ EsteEstaEstosEstas p_obj;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "estas";
        else print "estos";
    } else {
        if (EsFemenino(p_obj)) print "esta";
        else print "este";
    }
];

[ EseEsaEsosEsas p_obj;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "esas";
        else print "esos";
    } else {
        if (EsFemenino(p_obj)) print "esa";
        else print "ese";
    }
];

[ AquelAquellaAquellosAquellas p_obj;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "aquellas";
        else print "aquellos";
    } else {
        if (EsFemenino(p_obj)) print "aquella";
        else print "aquel";
    }
];

! ######################### PRONOMBRES

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

[ LeLesDativo p_obj;
    if (p_obj == player) { print "te"; rtrue; }
    if (EsPlural(p_obj)) print "les";
    else print "le";
];

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

! ######################### CONJUGACIONES VERBALES

[ EstaEstan p_obj;
    if (EsPlural(p_obj) || p_obj == player) print "están";
    else print "está";
];

[ EsSon p_obj;
    if (EsPlural(p_obj) || p_obj == player) print "son";
    else print "es";
];

[ TieneTienen p_obj;
    if (EsPlural(p_obj) || p_obj == player) print "tienen";
    else print "tiene";
];

[ VaVan p_obj;
    if (EsPlural(p_obj) || p_obj == player) print "van";
    else print "va";
];

[ HaceHacen p_obj;
    if (EsPlural(p_obj) || p_obj == player) print "hacen";
    else print "hace";
];

! ######################### CONCORDANCIA DE ADJETIVOS

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

[ ConcordanciaEdo p_obj;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "as";
        else print "os";
    } else {
        if (EsFemenino(p_obj)) print "a";
        else print "o";
    }
];

[ ConcordanciaIdo p_obj;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "as";
        else print "os";
    } else {
        if (EsFemenino(p_obj)) print "a";
        else print "o";
    }
];

! ######################### SISTEMA DE CONJUGACIÓN AUTOMÁTICA

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

! ######################### FUNCIONES DE IMPRESIÓN MEJORADAS

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

[ ImprimirConDemostrativo p_obj;
    EsteEstaEstosEstas(p_obj);
    print " ";
    ImprimirNombre(p_obj);
];

! ######################### FUNCIONES DE DIRECCIONES

[ DirPropToFakeObj p_prop;
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

! ######################### RUTINA DE INICIALIZACIÓN

[ InicializarEspanol;
    ! Configurar entorno español
    print ""; ! Por ahora función vacía
];

! ######################### INCLUIR NÚCLEO PUNYINFORM

Include "puny.h";

! ######################### NOTAS DE USO
!
! Para usar esta librería en tu juego:
!
! 1. Include "spanish_final/puny_spanish_master.h";
!
! 2. En tu función Initialise:
!    [ Initialise;
!        InicializarEspanol();
!        location = MiUbicacion;
!        lookmode = 2;
!    ];
!
! 3. Define objetos con género:
!    Object mesa "mesa elegante" has female supporter;
!    Object libro "libro antiguo" has ; ! masculino por defecto
!    Object llaves "llaves" has female pluralname;
!
! 4. Los mensajes automáticamente usarán concordancia:
!    > examinar la mesa
!    "No hay nada especial en la mesa elegante."
!    
!    > coger las llaves  
!    "Cogidas."
!
! ¡Y listo! Tu juego entenderá español completo con conjugaciones y concordancia.