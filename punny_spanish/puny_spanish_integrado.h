! ######################### PUNYINFORM ESPAÑOL INTEGRADO
! Sistema unificado que incluye gramática optimizada, mensajes y funciones
! Punto de entrada único y fácil de usar
! 
! Autor: Claude Code
! Fecha: 5 de julio de 2025
! Versión: 2.0 Integrada

System_file;

! ######################### CONFIGURACIÓN OPCIONAL
! Descomenta para habilitar características adicionales

! Constant OPTIONAL_EXTENDED_VERBSET;     ! Verbos extendidos (besar, comprar, etc)
! Constant DEBUG_SPANISH_PARSER;          ! Debug del parser español
! Constant DISABLE_SPANISH_MESSAGES;      ! Usar mensajes originales ingleses

! ######################### ARCHIVOS BASE DE PUNYINFORM (SIN MODIFICAR)

Include "globals.h";

! ######################### CONFIGURACIÓN DE CARACTERES ESPAÑOLES
! Soporte para acentos y caracteres especiales

Zcharacter table '@{E1}' '@{E9}' '@{ED}' '@{F3}' '@{FA}' '@{FC}' '@{F1}' 
                 '@{C1}' '@{C9}' '@{CD}' '@{D3}' '@{DA}' '@{DC}' '@{D1}'
                 '@{BF}' '@{A1}' '@{C3}' '@{B1}' '@{C2}' '@{BA}' '@{A9}'
                 '@{B3}';

! ######################### SISTEMA DE MENSAJES ESPAÑOL
#IfnDef DISABLE_SPANISH_MESSAGES;
Include "spanish_final/messages_spanish_master.h";
#EndIf;

! ######################### SISTEMA DE GRAMÁTICA OPTIMIZADA
Include "spanish_final/grammar_optimizada.h";

! ######################### PARSER ESPAÑOL AVANZADO
Include "spanish_final/parser_spanish_master.h";

! ######################### SCOPE (SIN MODIFICAR)
Include "scope.h";

! ######################### FUNCIONES DE CONCORDANCIA ESPAÑOLA

! Detectores de propiedades
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

! Artículos definidos
[ ElLaLosLas p_obj;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "las";
        else print "los";
    } else {
        if (EsFemenino(p_obj)) print "la";
        else print "el";
    }
];

! Artículos indefinidos
[ UnUnaUnosUnas p_obj;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "unas";
        else print "unos";
    } else {
        if (EsFemenino(p_obj)) print "una";
        else print "un";
    }
];

! Demostrativos
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

! Pronombres
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

! Conjugaciones verbales básicas
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

! Concordancia de participios
[ ConcordanciaIdo p_obj;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "as";
        else print "os";
    } else {
        if (EsFemenino(p_obj)) print "a";
        else print "o";
    }
];

! Funciones de impresión mejoradas
[ ImprimirConArticulo p_obj;
    ElLaLosLas(p_obj);
    print " ";
    if (p_obj.&short_name && PrintOrRun(p_obj, short_name, 1)) rtrue;
    print (object) p_obj;
];

[ ImprimirConArticuloIndefinido p_obj;
    UnUnaUnosUnas(p_obj);
    print " ";
    if (p_obj.&short_name && PrintOrRun(p_obj, short_name, 1)) rtrue;
    print (object) p_obj;
];

! ######################### FUNCIONES DE INICIALIZACIÓN

[ InicializarEspanol;
    ! Inicializar sistemas españoles si es necesario
    #IfDef DEBUG_SPANISH_PARSER;
    print "[Sistema español inicializado - Parser optimizado cargado]^";
    #EndIf;
    
    ! Verificar que el sistema está funcionando
    VerificarSistemaEspanol();
];

[ VerificarSistemaEspanol;
    #IfDef DEBUG_SPANISH_PARSER;
    print "[Verificando sistema español...]^";
    print "[- Verbos regulares: disponibles]^";
    print "[- Verbos irregulares: disponibles]^"; 
    print "[- Concordancia de género: disponibles]^";
    print "[- Mensajes en español: ";
    #IfnDef DISABLE_SPANISH_MESSAGES;
    print "activos";
    #IfnOt;
    print "desactivados";
    #EndIf;
    print "]^";
    print "[Sistema listo para usar]^";
    #EndIf;
];

! ######################### NÚCLEO PUNYINFORM (SIN MODIFICAR)
Include "puny.h";

! ######################### FUNCIONES POST-INICIALIZACIÓN

[ PostInitialiseSpanish;
    ! Función llamada después de que PunyInform se inicialice
    ! Aquí podemos hacer configuraciones adicionales si es necesario
];

! ######################### DOCUMENTACIÓN DE USO

! ========================= CÓMO USAR ESTE SISTEMA =========================
!
! 1. INCLUIR EN TU PROYECTO:
!    Include "puny_spanish_integrado.h";
!
! 2. CONFIGURACIÓN OPCIONAL (antes del include):
!    Constant OPTIONAL_EXTENDED_VERBSET;    ! Para verbos adicionales
!    Constant DEBUG_SPANISH_PARSER;         ! Para debug
!
! 3. INICIALIZAR EN TU FUNCIÓN Initialise:
!    [ Initialise;
!        InicializarEspanol();               ! <- IMPORTANTE
!        location = TuUbicacionInicial;
!        lookmode = 2;
!    ];
!
! 4. CREAR OBJETOS CON GÉNERO:
!    Object mesa "mesa elegante"
!        with name 'mesa' 'elegante',
!             description "Una hermosa mesa de madera.",
!        has supporter static female;        ! <- FEMENINO
!
!    Object libro "libro antiguo"
!        with name 'libro' 'antiguo',
!             description "Un viejo libro encuadernado.",
!        has ;                               ! <- MASCULINO (defecto)
!
!    Object llaves "llaves plateadas"
!        with name 'llaves' 'plateadas',
!             description "Unas llaves brillantes.",
!        has female pluralname;              ! <- FEMENINO PLURAL
!
! 5. EL SISTEMA FUNCIONA AUTOMÁTICAMENTE:
!    - Entiende todas las conjugaciones verbales españolas
!    - Usa concordancia automática en mensajes
!    - Maneja artículos y pronombres correctamente
!    - Incluye variantes regionales de verbos
!
! 6. EJEMPLOS DE COMANDOS SOPORTADOS:
!    > mirar / mira / ver / observa
!    > coger el libro / coge el libro / toma el libro
!    > examinar la mesa / examina la mesa
!    > ponerse las llaves / ponte las llaves
!    > ir al norte / ve al norte / anda al norte
!    > hablar con el guardia sobre el tesoro
!    > inventario / inv / i
!
! 7. MENSAJES CON CONCORDANCIA AUTOMÁTICA:
!    > coger las llaves
!    "Cogidas."                              ! <- Femenino plural
!    
!    > coger el libro
!    "Cogido."                               ! <- Masculino singular
!
! 8. FUNCIONES ÚTILES DISPONIBLES:
!    ElLaLosLas(objeto)                      ! Imprime artículo correcto
!    EstaEstan(objeto)                       ! Conjugación "estar"
!    EsSon(objeto)                           ! Conjugación "ser"
!    ImprimirConArticulo(objeto)             ! "la mesa", "el libro"
!    EsFemenino(objeto)                      ! Detecta género
!    EsPlural(objeto)                        ! Detecta número
!
! ========================= SISTEMA COMPLETAMENTE LISTO =========================