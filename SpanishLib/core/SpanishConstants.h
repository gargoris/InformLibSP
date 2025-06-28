! ==============================================================================
! SPANISHCONSTANTS.H - Constantes centralizadas del sistema español
! Sistema modular Spanish Library para Inform 6
! Compatible con Inform 6.42 y librería estándar 6.12.7
! ==============================================================================

System_file;

#Ifndef SPANISH_CONSTANTS_INCLUDED;
Constant SPANISH_CONSTANTS_INCLUDED;
Constant SPANISH_CONSTANTS_VERSION = "1.2-centralized-fixed";

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
! CONSTANTES REGIONALES
! ==============================================================================

Constant REGION_NEUTRAL = 0;
Constant REGION_MEXICO = 1;
Constant REGION_ARGENTINA = 2;
Constant REGION_SPAIN = 3;
Constant REGION_COLOMBIA = 4;
Constant REGION_CHILE = 5;

#Ifndef SPANISH_REGION_DEFAULT;
    Constant SPANISH_REGION_DEFAULT = 0;     ! Neutral por defecto
#Endif;

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
! VARIABLES GLOBALES CENTRALIZADAS - ✅ SIN DUPLICACIONES
! ==============================================================================

! Variable principal de formalidad
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
Global current_spanish_region = SPANISH_REGION_DEFAULT;
Global voseo_enabled = false;
Global regional_vocabulary = true;

! Marcadores de módulos cargados
Global SPANISH_CORE_LOADED = false;
Global SPANISH_PARSER_LOADED = false;
Global SPANISH_GRAMMAR_LOADED = false;
Global SPANISH_VERBS_LOADED = false;
Global SPANISH_MESSAGES_LOADED = false;
Global SPANISH_IRREGULAR_VERBS_LOADED = false;
Global SPANISH_META_LOADED = false;
Global SPANISH_REGIONAL_LOADED = false;

! ==============================================================================
! ARRAYS BÁSICOS COMPARTIDOS - ✅ CENTRALIZADOS
! ==============================================================================

! Buffer principal del sistema
Array spanish_buffer -> 120;
Array spanish_temp_buffer -> 100;

! Buffers para comandos
Array last_command_buffer -> 120;
Array last_command_parse table 32;

! Buffers para parsing
Array spanish_parse_buffer --> 64;
Array spanish_temp_parse --> 32;

! ==============================================================================
! ARRAYS LINGÜÍSTICOS PRINCIPALES
! ==============================================================================

! ✅ CORREGIDO: Arrays con verificación de compatibilidad
#Ifdef LIBRARY_STAGE;
#Iffalse LIBRARY_STAGE >= AFTER_PARSER;
  ! Los arrays se definirán después del parser
#Ifnot;

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

#Endif;
#Endif;

! ==============================================================================
! FUNCIONES BÁSICAS DE CONFIGURACIÓN
! ==============================================================================

[ SpanishSetFormality level;
    ! ✅ CORREGIDO: Función completa de configuración de formalidad
    if (level == FORMAL || level == INFORMAL) {
        FormalityLevel = level;
        
        #Ifdef DEBUG;
            print "[Formalidad cambiada a: ";
            if (level == FORMAL) print "FORMAL";
            else print "INFORMAL";
            print "]^";
        #Endif;
        
        return true;
    }
    
    #Ifdef DEBUG;
        print "[ERROR: Nivel de formalidad inválido: ", level, "]^";
    #Endif;
    
    return false;
];

[ SpanishSetRegion region;
    ! ✅ AÑADIDO: Función de configuración regional
    if (region >= REGION_NEUTRAL && region <= REGION_CHILE) {
        current_spanish_region = region;
        
        ! Configuración automática basada en región
        switch (region) {
            REGION_ARGENTINA:
                voseo_enabled = true;
                FormalityLevel = INFORMAL;
            REGION_SPAIN:
                voseo_enabled = false;
                FormalityLevel = FORMAL;
            default:
                voseo_enabled = false;
                FormalityLevel = INFORMAL;
        }
        
        #Ifdef DEBUG;
            print "[Región cambiada a: ";
            switch (region) {
                REGION_NEUTRAL: print "NEUTRAL";
                REGION_MEXICO: print "MÉXICO";
                REGION_ARGENTINA: print "ARGENTINA";
                REGION_SPAIN: print "ESPAÑA";
                REGION_COLOMBIA: print "COLOMBIA";
                REGION_CHILE: print "CHILE";
            }
            print "]^";
        #Endif;
        
        return true;
    }
    
    return false;
];

[ SpanishGetFormality;
    ! ✅ AÑADIDO: Obtener nivel de formalidad actual
    return FormalityLevel;
];

[ SpanishGetRegion;
    ! ✅ AÑADIDO: Obtener región actual
    return current_spanish_region;
];

[ SpanishIsVoseoEnabled;
    ! ✅ AÑADIDO: Verificar si el voseo está activo
    return voseo_enabled;
];

[ SpanishToggleVoseo;
    ! ✅ AÑADIDO: Alternar voseo manualmente
    voseo_enabled = ~~voseo_enabled;
    
    #Ifdef DEBUG;
        print "[Voseo: ";
        if (voseo_enabled) print "ACTIVADO";
        else print "DESACTIVADO";
        print "]^";
    #Endif;
    
    return voseo_enabled;
];

! ==============================================================================
! SISTEMA DE TRACKING DE MÓDULOS
! ==============================================================================

[ MarkModuleLoaded module_name;
    ! ✅ AÑADIDO: Marcar un módulo como cargado
    switch (module_name) {
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

[ IsModuleLoaded module_name;
    ! ✅ AÑADIDO: Verificar si un módulo está cargado
    switch (module_name) {
        'core': return SPANISH_CORE_LOADED;
        'parser': return SPANISH_PARSER_LOADED;
        'grammar': return SPANISH_GRAMMAR_LOADED;
        'verbs': return SPANISH_VERBS_LOADED;
        'messages': return SPANISH_MESSAGES_LOADED;
        'irregular': return SPANISH_IRREGULAR_VERBS_LOADED;
        'meta': return SPANISH_META_LOADED;
        'regional': return SPANISH_REGIONAL_LOADED;
        default: return false;
    }
];

[ SpanishModuleStatus;
    ! ✅ AÑADIDO: Mostrar estado de todos los módulos
    print "^=== ESTADO DE MÓDULOS SPANISH LIBRARY ===^";
    print "• Core: "; if (SPANISH_CORE_LOADED) print "✅"; else print "❌"; print "^";
    print "• Parser: "; if (SPANISH_PARSER_LOADED) print "✅"; else print "❌"; print "^";
    print "• Grammar: "; if (SPANISH_GRAMMAR_LOADED) print "✅"; else print "❌"; print "^";
    print "• Verbs: "; if (SPANISH_VERBS_LOADED) print "✅"; else print "❌"; print "^";
    print "• Messages: "; if (SPANISH_MESSAGES_LOADED) print "✅"; else print "❌"; print "^";
    print "• Irregular Verbs: "; if (SPANISH_IRREGULAR_VERBS_LOADED) print "✅"; else print "❌"; print "^";
    print "• Meta Commands: "; if (SPANISH_META_LOADED) print "✅"; else print "❌"; print "^";
    print "• Regional: "; if (SPANISH_REGIONAL_LOADED) print "✅"; else print "❌"; print "^";
    print "========================================^";
];

! ==============================================================================
! INICIALIZACIÓN DE CONSTANTES
! ==============================================================================

[ SpanishConstantsInit;
    ! ✅ CORREGIDO: Inicialización completa sin duplicaciones
    FormalityLevel = SPANISH_FORMALITY_DEFAULT;
    current_spanish_region = SPANISH_REGION_DEFAULT;
    spanish_initialized = false;
    
    ! Limpiar arrays
    spanish_buffer->0 = 0;
    spanish_temp_buffer->0 = 0;
    last_command_buffer->0 = 0;
    
    ! Configurar sistema
    undo_disabled = false;
    again_enabled = true;
    oops_enabled = true;
    last_command_valid = false;
    voseo_enabled = false;
    regional_vocabulary = true;
    
    ! Limpiar marcadores de módulos
    SPANISH_CORE_LOADED = false;
    SPANISH_PARSER_LOADED = false;
    SPANISH_GRAMMAR_LOADED = false;
    SPANISH_VERBS_LOADED = false;
    SPANISH_MESSAGES_LOADED = false;
    SPANISH_IRREGULAR_VERBS_LOADED = false;
    SPANISH_META_LOADED = false;
    SPANISH_REGIONAL_LOADED = false;
    
    #Ifdef DEBUG;
        print "[SpanishConstants v", (string) SPANISH_CONSTANTS_VERSION, " inicializado]^";
    #Endif;
];

! ==============================================================================
! CONSTANTES DE VERSIÓN Y COMPATIBILIDAD
! ==============================================================================

Constant LIBRARY_SPANISH;
Constant SPANISH_MODULAR_SYSTEM;
Constant SPANISH_CONSTANTS_COMPLETE;
Constant SPANISH_SYSTEM_VERSION = "1.2-modular-fixed";

#Endif; ! SPANISH_CONSTANTS_INCLUDED

! ==============================================================================
! Fin de SpanishConstants.h - Constantes centralizadas y corregidas
! ==============================================================================