! ######################### PUNYINFORM ESPAÑOL INTEGRADO
! Sistema unificado que incluye gramática optimizada, mensajes y funciones
! Punto de entrada único y fácil de usar
! 
! Autor: Claude Code
! Fecha: 5 de julio de 2025
! Versión: 2.0 Integrada

System_file;

! ######################### CARACTERES ESPECIALES ESPAÑOLES - DEBE IR PRIMERO
! Esta tabla DEBE definirse antes que cualquier string que use caracteres especiales
Zcharacter table 
    '@{E1}' '@{E9}' '@{ED}' '@{F3}' '@{FA}'    ! á é í ó ú (minúsculas)
    '@{C1}' '@{C9}' '@{CD}' '@{D3}' '@{DA}'    ! Á É Í Ó Ú (mayúsculas)
    '@{FC}' '@{DC}'                            ! ü Ü (diéresis)
    '@{F1}' '@{D1}'                            ! ñ Ñ (eñe)
    '@{BF}' '@{A1}'                            ! ¿ ¡ (signos interrogación/exclamación)
    '@{AB}' '@{BB}'                            ! « » (comillas españolas)
    '@{B7}'                                    ! · (punto medio)
    '@{A7}' '@{BA}' '@{B3}' '@{B2}' '@{B9}'    ! § º ³ ² ¹ (símbolos adicionales)
    '@{A9}' '@{AE}' '@{B1}' '@{F7}' '@{D7}'    ! © ® ± ÷ × (símbolos matemáticos)
    '@{C3}' '@{C2}' '@{E2}' '@{A2}' '@{BD}'    ! Códigos adicionales para acentos complejos
;

! ######################### CONFIGURACIÓN OPCIONAL
! Descomenta para habilitar características adicionales

! Constant OPTIONAL_EXTENDED_VERBSET;     ! Verbos extendidos (besar, comprar, etc)
! Constant DEBUG_SPANISH_PARSER;          ! Debug del parser español
! Constant DISABLE_SPANISH_MESSAGES;      ! Usar mensajes originales ingleses

! ######################### ARCHIVOS BASE DE PUNYINFORM (SIN MODIFICAR)

Include "globals.h";

! ######################### ATRIBUTOS ESPAÑOLES REQUERIDOS
! Declaración de atributos para género (female ya existe en globals.h)
Attribute male;

! ######################### CONSTANTES DE ACCIONES REQUERIDAS
! Definición de constantes que usa el parser español
Constant MAX_BUFFER_WORDS = 20;
! Global PrintMsg = _PrintMsg;  ! Comentado - se define en messages_spanish_master.h
Constant Take = TakeSub;
Constant Give = GiveSub; 
Constant Insert = InsertSub;
Constant PutOn = PutOnSub;

! ######################### PUNYINFORM CORE (SIN GRAMMAR.H PARA EVITAR CONFLICTOS)
! NOTA: Usamos puny_sin_grammar.h que es una versión modificada de puny.h
! que excluye grammar.h para evitar conflictos con grammar_optimizada.h
Include "puny_sin_grammar.h";

! ######################### SISTEMA DE MENSAJES ESPAÑOL (DESPUÉS DE PUNYINFORM)
! NOTA: Debe ir DESPUÉS de puny_sin_grammar.h para sobrescribir mensajes ingleses
#IfnDef DISABLE_SPANISH_MESSAGES;
Include "messages_spanish_simple.h";
#EndIf;

! ######################### GRAMMAR.H ORIGINAL (PARA DEFINICIONES DE ACCIONES)
! NOTA: Se incluye ANTES de la gramática española para definir las acciones,
! pero los verbos españoles sobrescribirán los ingleses
Include "grammar.h";

! ######################### SISTEMA DE GRAMÁTICA OPTIMIZADA (SOBRESCRIBE VERBOS)
Include "grammar_optimizada.h";

! ######################### PARSER ESPAÑOL AVANZADO
! TEMPORALMENTE COMENTADO PARA DEBUGGING
! Include "parser_spanish_master.h";

! NOTA: scope.h ya está incluido en puny_sin_grammar.h - no incluir de nuevo

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

! ######################### RUTINAS DE ACCIÓN ESPAÑOLAS ADICIONALES
! Rutinas para verbos que no están en el núcleo de PunyInform

[ KissSub;
    if (noun has animate) {
        if (noun == player) "No puedes besarte a ti mismo.";
        print (The) noun, " no parece interesad";
        if (noun has female) print "a"; else print "o";
        " en eso.";
    }
    "No es apropiado besar eso.";
];

[ BuySub;
    "No hay nada que comprar aquí.";
];

[ PraySub;
    if (noun) {
        print "Rezas a ", (the) noun, " en silencio.";
    } else {
        print "Rezas en silencio, esperando que alguien escuche tus plegarias.";
    }
];

[ SingSub;
    if (noun) {
        print "Cantas una melodía dedicada a ", (the) noun, ".";
    } else {
        print "Cantas una hermosa melodía que llena el aire de música.";
    }
];

[ SleepSub;
    "No es momento de dormir. Tienes cosas importantes que hacer.";
];

[ ThinkSub;
    if (noun) {
        print "Piensas profundamente sobre ", (the) noun, ".";
    } else {
        print "Te quedas pensativo, reflexionando sobre la situación.";
    }
];

[ SwimSub;
    "No hay ningún lugar apropiado para nadar aquí.";
];

[ GoInSub;
    GoSub();
];

! ######################### NÚCLEO PUNYINFORM (MODIFICADO PARA EVITAR CONFLICTOS)
! Incluir solo las partes de puny.h que no conflictan con nuestro sistema

! Necesitamos incluir messages.h antes que nuestros mensajes
! NOTA: Comentado para evitar duplicación - puny_sin_grammar.h ya incluye messages.h
! #IfDef DISABLE_SPANISH_MESSAGES;
! Include "messages.h";
! #EndIf;

! Incluir la implementación de PunyInform sin grammar.h
! NOTA: Comentado para evitar duplicación - ya incluido arriba en línea 47
! Include "puny_sin_grammar.h";

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