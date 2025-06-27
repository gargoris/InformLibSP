! ==============================================================================
! SPANISHCONSTANTS.H - Constantes centralizadas del sistema español
! Sistema modular Spanish Library para Inform 6
! Compatible con Inform 6.42 y librería estándar 6.12.7
! ==============================================================================

System_file;

#Ifndef SPANISH_CONSTANTS_INCLUDED;
Constant SPANISH_CONSTANTS_INCLUDED;
Constant SPANISH_CONSTANTS_VERSION = "1.1-centralized-fixed";

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

! ==============================================================================
! CONSTANTES DE FORMALIDAD
! ==============================================================================

Constant INFORMAL = 0;
Constant FORMAL = 1;

! Configuración por defecto
#Ifndef SPANISH_FORMALITY_DEFAULT;
    Constant SPANISH_FORMALITY_DEFAULT = 0;  ! Informal por defecto
#Endif;

! ==============================================================================
! VARIABLES GLOBALES CENTRALIZADAS
! ==============================================================================

! Variable principal de formalidad (antes estaba duplicada)
Global FormalityLevel = SPANISH_FORMALITY_DEFAULT;

! Variables de estado del sistema
Global spanish_initialized = false;
Global spanish_parser_ready = false;
Global spanish_verbs_ready = false;
Global spanish_grammar_ready = false;
Global spanish_messages_ready = false;

! Variables para comandos
Global last_command_length = 0;
Global spanish_parse_stage = 0;
Global spanish_last_verb = 0;

! Variables para meta-comandos
Global undo_disabled = false;
Global again_enabled = true;
Global oops_enabled = true;
Global last_command_valid = false;
Global oops_word = 0;
Global oops_position = 0;

! Variables regionales
#Ifndef SPANISH_REGION_DEFAULT;
    Constant SPANISH_REGION_DEFAULT = 0;     ! Neutral por defecto
#Endif;

Global current_spanish_region = SPANISH_REGION_DEFAULT;
Global voseo_enabled = false;
Global regional_vocabulary = true;

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

Constant ALL1__WD   = 'todo';
Constant ALL2__WD   = 'todos';
Constant ALL3__WD   = 'todas';
Constant ALL4__WD   = 'cada';
Constant ALL5__WD   = 'ambos';
Constant ALL6__WD   = 'ambas';

Constant AND1__WD   = 'y';
Constant AND2__WD   = 'e';
Constant AND3__WD   = 'también';

Constant BUT1__WD   = 'menos';
Constant BUT2__WD   = 'excepto';
Constant BUT3__WD   = 'salvo';
Constant BUT4__WD   = 'sino';

Constant ME1__WD    = 'yo';
Constant ME2__WD    = 'mi';
Constant ME3__WD    = 'me';
Constant ME4__WD    = 'mí';

Constant OF1__WD    = 'de';
Constant OF2__WD    = 'del';
Constant OF3__WD    = 'de_la';
Constant OF4__WD    = 'de_los';
Constant OF5__WD    = 'de_las';

Constant OTHER1__WD = 'otro';
Constant OTHER2__WD = 'otra';
Constant OTHER3__WD = 'otros';
Constant OTHER4__WD = 'otras';

Constant THEN1__WD  = 'luego';
Constant THEN2__WD  = 'después';
Constant THEN3__WD  = 'entonces';
Constant THEN4__WD  = 'y_luego';
Constant THEN5__WD  = 'y_después';

! ==============================================================================
! CONSTANTES DE PARSING
! ==============================================================================

Constant PREP_SIMPLE = 1;
Constant PREP_COMPOUND_START = 2;
Constant PREP_COMPOUND_MIDDLE = 3;
Constant PREP_COMPOUND_END = 4;

Constant SPANISH_VERB_POSITION = 1;
Constant SPANISH_OBJECT_POSITION = 2;
Constant SPANISH_PREPOSITION_POSITION = 3;
Constant SPANISH_SECONDARY_OBJECT_POSITION = 4;

! ==============================================================================
! CONSTANTES REGIONALES
! ==============================================================================

Constant REGION_NEUTRAL = 0;
Constant REGION_MEXICO = 1;
Constant REGION_ARGENTINA = 2;
Constant REGION_SPAIN = 3;
Constant REGION_COLOMBIA = 4;
Constant REGION_CHILE = 5;

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
! ARRAYS BÁSICOS COMPARTIDOS - CENTRALIZADOS
! ==============================================================================

! Buffer principal del sistema
Array spanish_buffer -> 120;

! Buffers para comandos
Array last_command_buffer -> 120;
Array last_command_parse table 32;

! Buffers para parsing
Array spanish_parse_buffer --> 64;
Array spanish_temp_parse --> 32;

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
! CONSTANTES DE VERSIÓN Y COMPATIBILIDAD
! ==============================================================================

Constant LIBRARY_SPANISH;
Constant SPANISH_MODULAR_SYSTEM;
Constant SPANISH_CONSTANTS_COMPLETE;
Constant SPANISH_SYSTEM_VERSION = "1.1-modular-fixed";

! Marcadores de módulos disponibles (se activan cuando se cargan)
Global SPANISH_CORE_LOADED = false;
Global SPANISH_PARSER_LOADED = false;
Global SPANISH_GRAMMAR_LOADED = false;
Global SPANISH_VERBS_LOADED = false;
Global SPANISH_MESSAGES_LOADED = false;
Global SPANISH_IRREGULAR_VERBS_LOADED = false;
Global SPANISH_META_LOADED = false;
Global SPANISH_REGIONAL_LOADED = false;

! ==============================================================================
! FUNCIONES BÁSICAS DE CONFIGURACIÓN
! ==============================================================================

[ SpanishSetFormality level;
    ! Cambiar nivel de formalidad dinámicamente
    if (level == FORMAL || level == INFORMAL) {
        FormalityLevel = level;
        return true;
    }
    return false;
];

[ SpanishGetFormality;
    return FormalityLevel;
];

[ SpanishToggleFormality;
    if (FormalityLevel == FORMAL) {
        return SpanishSetFormality(INFORMAL);
    } else {
        return SpanishSetFormality(FORMAL);
    }
];

! ==============================================================================
! FUNCIONES DE ESTADO DEL SISTEMA
! ==============================================================================

[ SpanishSystemStatus;
    print "^=== ESTADO DEL SISTEMA ESPAÑOL ===^";
    print "Versión: ", (string) SPANISH_SYSTEM_VERSION, "^";
    
    print "Módulos cargados:^";
    print "• Core: "; if (SPANISH_CORE_LOADED) print "✅"; else print "❌"; print "^";
    print "• Parser: "; if (SPANISH_PARSER_LOADED) print "✅"; else print "❌"; print "^";
    print "• Grammar: "; if (SPANISH_GRAMMAR_LOADED) print "✅"; else print "❌"; print "^";
    print "• Verbs: "; if (SPANISH_VERBS_LOADED) print "✅"; else print "❌"; print "^";
    print "• Messages: "; if (SPANISH_MESSAGES_LOADED) print "✅"; else print "❌"; print "^";
    print "• Irregular Verbs: "; if (SPANISH_IRREGULAR_VERBS_LOADED) print "✅"; else print "❌"; print "^";
    print "• Meta Commands: "; if (SPANISH_META_LOADED) print "✅"; else print "❌"; print "^";
    print "• Regional: "; if (SPANISH_REGIONAL_LOADED) print "✅"; else print "❌"; print "^";
    
    print "^Configuración:^";
    print "• Formalidad: ";
    if (FormalityLevel == FORMAL) print "Formal (usted)"; else print "Informal (tú)";
    print "^• Región: ";
    switch(current_spanish_region) {
        REGION_MEXICO: print "México";
        REGION_ARGENTINA: print "Argentina";
        REGION_SPAIN: print "España";
        default: print "Neutral";
    }
    print "^• Voseo: ";
    if (voseo_enabled) print "Sí"; else print "No";
    print "^";
];

[ MarkModuleLoaded module_name;
    switch(module_name) {
        'core': SPANISH_CORE_LOADED = true;
        'parser': SPANISH_PARSER_LOADED = true;
        'grammar': SPANISH_GRAMMAR_LOADED = true;
        'verbs': SPANISH_VERBS_LOADED = true;
        'messages': SPANISH_MESSAGES_LOADED = true;
        'irregular': SPANISH_IRREGULAR_VERBS_LOADED = true;
        'meta': SPANISH_META_LOADED = true;
        'regional': SPANISH_REGIONAL_LOADED = true;
    }
];

! ==============================================================================
! INICIALIZACIÓN DE CONSTANTES
! ==============================================================================

[ SpanishConstantsInit;
    ! Inicializar valores por defecto
    FormalityLevel = SPANISH_FORMALITY_DEFAULT;
    current_spanish_region = SPANISH_REGION_DEFAULT;
    spanish_initialized = false;
    
    ! Limpiar arrays
    spanish_buffer->0 = 0;
    last_command_buffer->0 = 0;
    
    ! Configurar sistema
    undo_disabled = false;
    again_enabled = true;
    oops_enabled = true;
    last_command_valid = false;
    voseo_enabled = false;
    regional_vocabulary = true;
    
    #Ifdef DEBUG;
    print "[SpanishConstants v", (string) SPANISH_CONSTANTS_VERSION, " inicializado]^";
    #Endif;
];

#Endif; ! SPANISH_CONSTANTS_INCLUDED

! ==============================================================================
! Fin de SpanishConstants.h - Constantes centralizadas y corregidas
! ==============================================================================