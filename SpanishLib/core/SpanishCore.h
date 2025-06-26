! ==============================================================================
! SPANISHCORE.H - Constantes y definiciones básicas del núcleo español
! Archivo coordinador del sistema modular Spanish Library para Inform 6
! Compatible con Inform 6.42 y librería estándar 6.12.7
! ==============================================================================

System_file;

#Ifndef SPANISH_CORE_INCLUDED;
Constant SPANISH_CORE_INCLUDED;

! ==============================================================================
! VERIFICACIÓN DE ENTORNO Y DEPENDENCIAS
! ==============================================================================

! Verificación de orden de includes
#Ifdef LIBRARY_STAGE;
#Iffalse LIBRARY_STAGE >= AFTER_PARSER;
  Message fatalerror "*** Include Parser.h y VerbLib.h antes de SpanishCore.h ***";
#Endif;
#Endif;

! ==============================================================================
! CONSTANTES BÁSICAS DEL IDIOMA ESPAÑOL
! ==============================================================================

! Artículos definidos
Constant DEFART_H = "el";        ! Masculino singular
Constant DEFART_F = "la";        ! Femenino singular
Constant DEFART_PL = "los/las";  ! Plural

! Artículos indefinidos
Constant INDEFART_H = "un";      ! Masculino singular
Constant INDEFART_F = "una";     ! Femenino singular
Constant INDEFART_PL = "unos/unas"; ! Plural

! ==============================================================================
! DIRECCIONES EN ESPAÑOL
! ==============================================================================

Constant N_TO     = "norte n";
Constant S_TO     = "sur s";
Constant E_TO     = "este e";
Constant W_TO     = "oeste o";
Constant NE_TO    = "nordeste ne";
Constant NW_TO    = "noroeste no";
Constant SE_TO    = "sudeste se";
Constant SW_TO    = "sudoeste so";
Constant U_TO     = "arriba subir";
Constant D_TO     = "abajo bajar";
Constant IN_TO    = "dentro entrar";
Constant OUT_TO   = "fuera salir";

! ==============================================================================
! PALABRAS ESPECIALES DEL PARSER
! ==============================================================================

! Formas de "todo"
Constant ALL1__WD   = 'todo';
Constant ALL2__WD   = 'todos';
Constant ALL3__WD   = 'todas';
Constant ALL4__WD   = 'cada';
Constant ALL5__WD   = 'ambos';
Constant ALL6__WD   = 'ambas';

! Conjunciones
Constant AND1__WD   = 'y';
Constant AND2__WD   = 'e';      ! Eufonía ante 'i'
Constant AND3__WD   = 'también';

! Excepciones
Constant BUT1__WD   = 'menos';
Constant BUT2__WD   = 'excepto';
Constant BUT3__WD   = 'salvo';
Constant BUT4__WD   = 'sino';

! Pronombres reflexivos y personales
Constant ME1__WD    = 'yo';
Constant ME2__WD    = 'mi';
Constant ME3__WD    = 'me';
Constant ME4__WD    = 'mí';    ! Con tilde

! Preposiciones y contracciones
Constant OF1__WD    = 'de';
Constant OF2__WD    = 'del';    ! Contracción
Constant OF3__WD    = 'de_la';
Constant OF4__WD    = 'de_los';
Constant OF5__WD    = 'de_las';

! Otros determinantes
Constant OTHER1__WD = 'otro';
Constant OTHER2__WD = 'otra';
Constant OTHER3__WD = 'otros';
Constant OTHER4__WD = 'otras';

! Conectores temporales
Constant THEN1__WD  = 'luego';
Constant THEN2__WD  = 'después';
Constant THEN3__WD  = 'entonces';
Constant THEN4__WD  = 'y_luego';
Constant THEN5__WD  = 'y_después';

! ==============================================================================
! VARIABLES GLOBALES DEL SISTEMA
! ==============================================================================

! Control de formalidad (0 = tú, 1 = usted)
Global FormalityLevel = 0;

! Control del último comando
Global last_command_length = 0;

! Buffer para procesamiento especial
Array spanish_buffer -> 120;

! Estado del sistema
Global spanish_initialized = false;

! ==============================================================================
! RUTINAS FUNDAMENTALES DE IMPRESIÓN
! ==============================================================================

[ LanguagePrintShortName obj aux;
    if (obj == 0) { print "(nada)"; rtrue; }
    
    ! Intentar con short_name_indef si existe
    if (indef_mode && obj.&short_name_indef ~= 0) {
        aux = obj.&short_name_indef;
        if (aux-->0 ~= 0) {
            print (string) aux-->0;
            rtrue;
        }
    }
    
    ! Usar short_name normal
    aux = obj.&short_name;
    if (aux ~= 0) {
        if (aux-->0 ~= 0) {
            print (string) aux-->0;
            rtrue;
        }
    }
    
    rfalse;
];

! ==============================================================================
! CONFIGURACIÓN DE CARACTERÍSTICAS OPCIONALES
! ==============================================================================

! Características disponibles (pueden ser activadas por el desarrollador)
! #Ifdef SPANISH_IRREGULAR_VERBS;    ! Verbos irregulares completos
! #Ifdef SPANISH_REGIONAL_VARIANTS;   ! Variantes regionales
! #Ifdef SPANISH_ADVANCED_GRAMMAR;    ! Gramática avanzada

! Configuración por defecto
#Ifndef SPANISH_FORMALITY_DEFAULT;
    Constant SPANISH_FORMALITY_DEFAULT = 0;  ! Informal por defecto
#Endif;

#Ifndef SPANISH_REGION_DEFAULT;
    Constant SPANISH_REGION_DEFAULT = 0;     ! 0 = neutro, 1 = España, 2 = Latinoamérica
#Endif;

! ==============================================================================
! MARCADORES DE COMPATIBILIDAD
! ==============================================================================

! Marcar que el sistema base está cargado
Constant LIBRARY_SPANISH;
Constant SPANISH_CORE_VERSION = "1.0";

! Compatibilidad con versiones anteriores
#Ifdef SPANISH_LEGACY_SUPPORT;
    Constant SPANISH_MONOLITHIC_COMPATIBLE;
#Endif;

! ==============================================================================
! INCLUSIÓN DE SUBMÓDULOS CORE
! ==============================================================================

! Orden crítico de inclusión
Include "SpanishParser";    ! Rutinas de parsing
Include "SpanishVerbs";     ! Sistema de verbos
Include "SpanishGrammar";   ! Utilidades gramaticales

! ==============================================================================
! RUTINA DE INICIALIZACIÓN DEL CORE
! ==============================================================================

[ SpanishCoreInitialise i;
    if (spanish_initialized) return;
    
    ! Establecer valores por defecto
    FormalityLevel = SPANISH_FORMALITY_DEFAULT;
    last_command_length = 0;
    
    ! Limpiar buffers
    for (i = 0: i < 120: i++) spanish_buffer->i = 0;
    
    ! Marcar como inicializado
    spanish_initialized = true;
    
    #Ifdef DEBUG;
    print "[SpanishCore inicializado - Parser, Verbos y Gramática cargados]^";
    #Endif;
];

! ==============================================================================
! INFORMACIÓN DEL SISTEMA
! ==============================================================================

[ SpanishCoreInfo;
    print "Spanish Library Core v", (string) SPANISH_CORE_VERSION, "^";
    print "Módulos cargados:^";
    print "  - Parser: Análisis sintáctico y preposiciones compuestas^";
    print "  - Verbos: Conjugación y detección de verbos^";
    print "  - Gramática: Género, número y concordancia^";
    
    #Ifdef SPANISH_IRREGULAR_VERBS;
    print "  - Verbos irregulares: ACTIVADO^";
    #Endif;
    
    #Ifdef SPANISH_REGIONAL_VARIANTS;
    print "  - Variantes regionales: ACTIVADO^";
    #Endif;
];

#Endif; ! SPANISH_CORE_INCLUDED

! ==============================================================================
! Fin de SpanishCore.h - Núcleo del sistema modular de español
! ==============================================================================