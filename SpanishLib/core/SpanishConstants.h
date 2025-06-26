! ==============================================================================
! SPANISHCONSTANTS.H - Constantes centralizadas del sistema español
! Todas las constantes del sistema Spanish Library en un solo lugar
! Compatible con Inform 6.42 y librería estándar 6.12.7
! ==============================================================================

System_file;

#Ifndef SPANISH_CONSTANTS_INCLUDED;
Constant SPANISH_CONSTANTS_INCLUDED;
Constant SPANISH_CONSTANTS_VERSION = "1.0-unified";

! ==============================================================================
! CONSTANTES DE VERSIÓN Y COMPATIBILIDAD
! ==============================================================================

Constant LanguageVersion = "6.12.7-es-modular-unified";
Constant LIBRARY_SPANISH;
Constant SPANISH_MODULAR_SYSTEM;

! ==============================================================================
! CONSTANTES DE TIEMPOS VERBALES
! ==============================================================================

Constant PRESENTE_T   = 1;
Constant PRETERITO_T  = 2;
Constant IMPERFECTO_T = 3;
Constant FUTURO_T     = 4;
Constant CONDICIONAL_T = 5;
Constant SUBJUNTIVO_T = 6;
Constant IMPERATIVO_T = 7;

! ==============================================================================
! CONSTANTES DE GÉNERO Y NÚMERO
! ==============================================================================

Constant MASCULINE = 1;
Constant FEMININE = 2;
Constant NEUTER = 3;

Constant SINGULAR = 1;
Constant PLURAL = 2;

! ==============================================================================
! CONSTANTES DE PERSONA GRAMATICAL
! ==============================================================================

Constant PRIMERA_PERSONA = 1;
Constant SEGUNDA_PERSONA = 2;
Constant TERCERA_PERSONA = 3;

! Formalidad
Constant INFORMAL = 0;
Constant FORMAL = 1;

! ==============================================================================
! ARTÍCULOS BÁSICOS
! ==============================================================================

Constant DEFART_H = "el";        ! Masculino singular
Constant DEFART_F = "la";        ! Femenino singular
Constant DEFART_PL = "los/las";  ! Plural

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
! CONSTANTES DE PARSING
! ==============================================================================

! Tipos de preposiciones
Constant PREP_SIMPLE = 1;
Constant PREP_COMPOUND_START = 2;
Constant PREP_COMPOUND_MIDDLE = 3;
Constant PREP_COMPOUND_END = 4;

! Posiciones sintácticas
Constant SPANISH_VERB_POSITION = 1;
Constant SPANISH_OBJECT_POSITION = 2;
Constant SPANISH_PREPOSITION_POSITION = 3;
Constant SPANISH_SECONDARY_OBJECT_POSITION = 4;

! ==============================================================================
! CONSTANTES DE META-COMANDOS
! ==============================================================================

Constant META_UNDO = 1;
Constant META_AGAIN = 2; 
Constant META_OOPS = 3;
Constant META_HELP = 4;
Constant META_COMMANDS = 5;
Constant META_SCRIPT_ON = 6;
Constant META_SCRIPT_OFF = 7;
Constant META_PRONOUNS = 8;
Constant META_NOTIFY_ON = 9;
Constant META_NOTIFY_OFF = 10;
Constant META_BRIEF = 11;
Constant META_VERBOSE = 12;
Constant META_SUPERBRIEF = 13;

! ==============================================================================
! CONSTANTES REGIONALES
! ==============================================================================

! Códigos de región
Constant REGION_NEUTRAL = 0;
Constant REGION_MEXICO = 1;
Constant REGION_ARGENTINA = 2;
Constant REGION_SPAIN = 3;
Constant REGION_COLOMBIA = 4;
Constant REGION_CHILE = 5;

! ==============================================================================
! CONFIGURACIÓN POR DEFECTO
! ==============================================================================

! Configuraciones que pueden ser sobreescritas por el desarrollador
#Ifndef SPANISH_FORMALITY_DEFAULT;
    Constant SPANISH_FORMALITY_DEFAULT = 0;  ! Informal por defecto
#Endif;

#Ifndef SPANISH_REGION_DEFAULT;
    Constant SPANISH_REGION_DEFAULT = 0;     ! Neutro por defecto
#Endif;

! ==============================================================================
! ARRAYS Y TABLAS BÁSICAS
! ==============================================================================

Array LanguagePronouns table
    'me'       $$000001   NULL     
    'mi'       $$000001   NULL     
    'yo'       $$000001   NULL
    'te'       $$000010   NULL     
    'tu'       $$000010   NULL
    'usted'    $$000010   NULL
    'le'       $$000100   NULL     
    'la'       $$000100   NULL
    'lo'       $$000100   NULL
    'el'       $$000100   NULL
    'ella'     $$000100   NULL
    'nos'      $$001000   NULL     
    'nosotros' $$001000   NULL
    'nosotras' $$001000   NULL
    'os'       $$010000   NULL     
    'vosotros' $$010000   NULL 
    'vosotras' $$010000   NULL
    'ustedes'  $$010000   NULL
    'les'      $$100000   NULL     
    'las'      $$100000   NULL
    'los'      $$100000   NULL
    'ellos'    $$100000   NULL
    'ellas'    $$100000   NULL;

Array LanguageDescriptors table
    'mi'       $$000001,
    'mis'      $$000001,
    'tu'       $$000010,
    'tus'      $$000010,
    'su'       $$000100,
    'sus'      $$000100,
    'nuestro'  $$001000,
    'nuestra'  $$001000,
    'nuestros' $$001000,
    'nuestras' $$001000,
    'vuestro'  $$010000,
    'vuestra'  $$010000,
    'vuestros' $$010000,
    'vuestras' $$010000;

Array LanguageNumbers table
    'uno' 1 'un' 1 'una' 1,
    'dos' 2, 'tres' 3, 'cuatro' 4, 'cinco' 5,
    'seis' 6, 'siete' 7, 'ocho' 8, 'nueve' 9, 'diez' 10,
    'once' 11, 'doce' 12, 'trece' 13, 'catorce' 14, 'quince' 15,
    'dieciséis' 16, 'diecisiete' 17, 'dieciocho' 18, 'diecinueve' 19, 'veinte' 20;

! ==============================================================================
! MARCADORES DE CARACTERÍSTICAS OPCIONALES
! ==============================================================================

! Estos se definen automáticamente según qué módulos se incluyan
! El desarrollador puede definirlos manualmente antes de incluir SpanishLib.h

! #Define SPANISH_IRREGULAR_VERBS     ! Activa verbos irregulares
! #Define SPANISH_META_COMMANDS       ! Activa meta-comandos avanzados  
! #Define SPANISH_REGIONAL_VARIANTS   ! Activa variantes regionales
! #Define SPANISH_FULL_MESSAGES       ! Activa sistema completo de mensajes
! #Define SPANISH_HELP_SYSTEM         ! Activa sistema de ayuda integrado

! ==============================================================================
! INFORMACIÓN DE DEPURACIÓN
! ==============================================================================

#Ifdef DEBUG;
Constant SPANISH_DEBUG_INFO = "Spanish Library - Sistema Modular Unificado";
Constant SPANISH_BUILD_DATE = "2024-12-unified";
Constant SPANISH_TARGET_VERSION = "6.12.7";
#Endif;

#Endif; ! SPANISH_CONSTANTS_INCLUDED

! ==============================================================================
! Fin de SpanishConstants.h - Constantes centralizadas del sistema español
! ==============================================================================