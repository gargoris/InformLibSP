! ==============================================================================
! SPANISHCONSTANTS.H - Constantes centralizadas del sistema espanol
! Sistema modular Spanish Library para Inform 6
! Compatible con Inform 6.42 y libreria estandar 6.12.7
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
! CONSTANTES DE GENERO Y NUMERO
! ==============================================================================

Constant MASCULINE = 1;
Constant FEMININE = 2;
#Ifndef NEUTER;
Constant NEUTER = 3;
#Endif;

Constant SINGULAR = 1;
#Ifndef PLURAL;
Constant PLURAL = 2;
#Endif;

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

! Configuracion por defecto
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
! DIRECCIONES EN ESPANOL
! ==============================================================================

#Ifndef N_TO;
Constant N_TO     = "norte n";
#Endif;
#Ifndef S_TO;
Constant S_TO     = "sur s";
#Endif;
#Ifndef E_TO;
Constant E_TO     = "este e";
#Endif;
#Ifndef W_TO;
Constant W_TO     = "oeste o";
#Endif;
#Ifndef NE_TO;
Constant NE_TO    = "nordeste ne";
#Endif;
#Ifndef NW_TO;
Constant NW_TO    = "noroeste no";
#Endif;
#Ifndef SE_TO;
Constant SE_TO    = "sudeste se";
#Endif;
#Ifndef SW_TO;
Constant SW_TO    = "sudoeste so";
#Endif;
#Ifndef U_TO;
Constant U_TO     = "arriba subir";
#Endif;
#Ifndef D_TO;
Constant D_TO     = "abajo bajar";
#Endif;
#Ifndef IN_TO;
Constant IN_TO    = "dentro entrar";
#Endif;
#Ifndef OUT_TO;
Constant OUT_TO   = "fuera salir";
#Endif;

! ==============================================================================
! PALABRAS ESPECIALES DEL PARSER
! ==============================================================================

#Ifndef ALL1__WD;
Constant ALL1__WD   = 'todo';
#Endif;
#Ifndef ALL2__WD;
Constant ALL2__WD   = 'todos';
#Endif;
#Ifndef ALL3__WD;
Constant ALL3__WD   = 'todas';
#Endif;
#Ifndef ALL4__WD;
Constant ALL4__WD   = 'cada';
#Endif;
#Ifndef ALL5__WD;
Constant ALL5__WD   = 'ambos';
#Endif;
Constant ALL6__WD   = 'ambas';

#Ifndef AND1__WD;
Constant AND1__WD   = 'y';
#Endif;
#Ifndef AND2__WD;
Constant AND2__WD   = 'e';
#Endif;
#Ifndef AND3__WD;
Constant AND3__WD   = 'tambien';
#Endif;

#Ifndef BUT1__WD;
Constant BUT1__WD   = 'menos';
#Endif;
#Ifndef BUT2__WD;
Constant BUT2__WD   = 'excepto';
#Endif;
#Ifndef BUT3__WD;
Constant BUT3__WD   = 'salvo';
#Endif;
Constant BUT4__WD   = 'sino';

#Ifndef ME1__WD;
Constant ME1__WD    = 'yo';
#Endif;
#Ifndef ME2__WD;
Constant ME2__WD    = 'mi';
#Endif;
#Ifndef ME3__WD;
Constant ME3__WD    = 'me';
#Endif;
Constant ME4__WD    = 'mi';

#Ifndef OF1__WD;
Constant OF1__WD    = 'de';
#Endif;
#Ifndef OF2__WD;
Constant OF2__WD    = 'del';
#Endif;
#Ifndef OF3__WD;
Constant OF3__WD    = 'de_la';
#Endif;
#Ifndef OF4__WD;
Constant OF4__WD    = 'de_los';
#Endif;
Constant OF5__WD    = 'de_las';

#Ifndef OTHER1__WD;
Constant OTHER1__WD = 'otro';
#Endif;
#Ifndef OTHER2__WD;
Constant OTHER2__WD = 'otra';
#Endif;
#Ifndef OTHER3__WD;
Constant OTHER3__WD = 'otros';
#Endif;
Constant OTHER4__WD = 'otras';

#Ifndef THEN1__WD;
Constant THEN1__WD  = 'luego';
#Endif;
#Ifndef THEN2__WD;
Constant THEN2__WD  = 'despues';
#Endif;
#Ifndef THEN3__WD;
Constant THEN3__WD  = 'entonces';
#Endif;
Constant THEN4__WD  = 'y_luego';
Constant THEN5__WD  = 'y_despues';

! ==============================================================================
! VARIABLES GLOBALES CENTRALIZADAS - [OK] SIN DUPLICACIONES
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

! Marcadores de modulos cargados
Global SPANISH_CORE_LOADED = false;
Global SPANISH_PARSER_LOADED = false;
Global SPANISH_GRAMMAR_LOADED = false;
Global SPANISH_VERBS_LOADED = false;
Global SPANISH_MESSAGES_LOADED = false;
Global SPANISH_IRREGULAR_VERBS_LOADED = false;
Global SPANISH_META_LOADED = false;
Global SPANISH_REGIONAL_LOADED = false;

! ==============================================================================
! ARRAYS BASICOS COMPARTIDOS - [OK] CENTRALIZADOS
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
! ARRAYS LINGUISTICOS PRINCIPALES
! ==============================================================================

! [OK] CORREGIDO: Arrays con verificacion de compatibilidad
#Ifdef LIBRARY_STAGE;
#Iffalse LIBRARY_STAGE >= AFTER_PARSER;
  ! Los arrays se definiran despues del parser
#Ifnot;

#Ifndef LanguagePronouns;
Array LanguagePronouns table
    'me'       $$000001   0     
    'mi'       $$000001   0     
    'yo'       $$000001   0
    'te'       $$000010   0     
    'tu'       $$000010   0
    'usted'    $$000010   0
    'le'       $$000100   0     
    'la'       $$000100   0
    'lo'       $$000100   0
    'el'       $$000100   0
    'ella'     $$000100   0
    'nos'      $$001000   0     
    'nosotros' $$001000   0
    'nosotras' $$001000   0
    'os'       $$010000   0     
    'vosotros' $$010000   0 
    'vosotras' $$010000   0
    'ustedes'  $$010000   0
    'les'      $$100000   0     
    'las'      $$100000   0
    'los'      $$100000   0
    'ellos'    $$100000   0
    'ellas'    $$100000   0;
#Endif;

#Ifndef LanguageDescriptors;
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
#Endif;

#Ifndef LanguageNumbers;
Array LanguageNumbers table
    'uno' 1 'un' 1 'una' 1,
    'dos' 2, 'tres' 3, 'cuatro' 4, 'cinco' 5,
    'seis' 6, 'siete' 7, 'ocho' 8, 'nueve' 9, 'diez' 10,
    'once' 11, 'doce' 12, 'trece' 13, 'catorce' 14, 'quince' 15,
    'dieciseis' 16, 'diecisiete' 17, 'dieciocho' 18, 'diecinueve' 19, 'veinte' 20;
#Endif;

#Endif;
#Endif;

! ==============================================================================
! FUNCIONES BASICAS DE CONFIGURACION
! ==============================================================================

[ SpanishSetFormality level;
    ! [OK] CORREGIDO: Funcion completa de configuracion de formalidad
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
        print "[ERROR: Nivel de formalidad invalido: ", level, "]^";
    #Endif;
    
    return false;
];

[ SpanishSetRegion region;
    ! [OK] ANADIDO: Funcion de configuracion regional
    if (region >= REGION_NEUTRAL && region <= REGION_CHILE) {
        current_spanish_region = region;
        
        ! Configuracion automatica basada en region
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
            print "[Region cambiada a: ";
            switch (region) {
                REGION_NEUTRAL: print "NEUTRAL";
                REGION_MEXICO: print "MEXICO";
                REGION_ARGENTINA: print "ARGENTINA";
                REGION_SPAIN: print "ESPANA";
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
    ! [OK] ANADIDO: Obtener nivel de formalidad actual
    return FormalityLevel;
];

[ SpanishGetRegion;
    ! [OK] ANADIDO: Obtener region actual
    return current_spanish_region;
];

[ SpanishIsVoseoEnabled;
    ! [OK] ANADIDO: Verificar si el voseo esta activo
    return voseo_enabled;
];

[ SpanishToggleVoseo;
    ! [OK] ANADIDO: Alternar voseo manualmente
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
! SISTEMA DE TRACKING DE MODULOS
! ==============================================================================

[ MarkModuleLoaded module_name;
    ! [OK] ANADIDO: Marcar un modulo como cargado
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
    ! [OK] ANADIDO: Verificar si un modulo esta cargado
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
    ! [OK] ANADIDO: Mostrar estado de todos los modulos
    print "^=== ESTADO DE MODULOS SPANISH LIBRARY ===^";
    print "- Core: "; if (SPANISH_CORE_LOADED) print "[OK]"; else print "[X]"; print "^";
    print "- Parser: "; if (SPANISH_PARSER_LOADED) print "[OK]"; else print "[X]"; print "^";
    print "- Grammar: "; if (SPANISH_GRAMMAR_LOADED) print "[OK]"; else print "[X]"; print "^";
    print "- Verbs: "; if (SPANISH_VERBS_LOADED) print "[OK]"; else print "[X]"; print "^";
    print "- Messages: "; if (SPANISH_MESSAGES_LOADED) print "[OK]"; else print "[X]"; print "^";
    print "- Irregular Verbs: "; if (SPANISH_IRREGULAR_VERBS_LOADED) print "[OK]"; else print "[X]"; print "^";
    print "- Meta Commands: "; if (SPANISH_META_LOADED) print "[OK]"; else print "[X]"; print "^";
    print "- Regional: "; if (SPANISH_REGIONAL_LOADED) print "[OK]"; else print "[X]"; print "^";
    print "========================================^";
];

! ==============================================================================
! INICIALIZACION DE CONSTANTES
! ==============================================================================

[ SpanishConstantsInit;
    ! [OK] CORREGIDO: Inicializacion completa sin duplicaciones
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
    
    ! Limpiar marcadores de modulos
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
! CONSTANTES DE VERSION Y COMPATIBILIDAD
! ==============================================================================

Constant LIBRARY_SPANISH;
Constant SPANISH_MODULAR_SYSTEM;
Constant SPANISH_SYSTEM_VERSION = "1.2-modular-fixed";

! Marcar completitud del modulo
Constant SPANISH_CONSTANTS_COMPLETE;

#Endif; ! SPANISH_CONSTANTS_INCLUDED

! ==============================================================================
! Fin de SpanishConstants.h - Constantes centralizadas y corregidas
! ==============================================================================