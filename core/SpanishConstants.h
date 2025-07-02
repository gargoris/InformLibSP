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
! CONSTANTES REQUERIDAS POR EL PARSER DE INFORM
! ==============================================================================

! Contracciones en español (del, al)
Constant LanguageContractionForms = 2;

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

! Palabras para "todo/todos"
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

! Palabras para "sí/no"
#Ifndef YES1__WD;
Constant YES1__WD   = 'si';
#Endif;
#Ifndef YES2__WD;
Constant YES2__WD   = 'afirmativo';
#Endif;
#Ifndef YES3__WD;
Constant YES3__WD   = 'claro';
#Endif;

#Ifndef NO1__WD;
Constant NO1__WD    = 'no';
#Endif;
#Ifndef NO2__WD;
Constant NO2__WD    = 'negativo';
#Endif;
#Ifndef NO3__WD;
Constant NO3__WD    = 'nunca';
#Endif;

! Palabras para "deshacer/repetir"
#Ifndef UNDO1__WD;
Constant UNDO1__WD  = 'deshacer';
#Endif;
#Ifndef UNDO2__WD;
Constant UNDO2__WD  = 'undo';
#Endif;
#Ifndef UNDO3__WD;
Constant UNDO3__WD  = 'anular';
#Endif;

#Ifndef AGAIN1__WD;
Constant AGAIN1__WD = 'repetir';
#Endif;
#Ifndef AGAIN2__WD;
Constant AGAIN2__WD = 'again';
#Endif;
#Ifndef AGAIN3__WD;
Constant AGAIN3__WD = 'g//';
#Endif;

! Palabras para "oops"
#Ifndef OOPS1__WD;
Constant OOPS1__WD  = 'oops';
#Endif;
#Ifndef OOPS2__WD;
Constant OOPS2__WD  = 'uy';
#Endif;
#Ifndef OOPS3__WD;
Constant OOPS3__WD  = 'ay';
#Endif;

! Palabras para "salir/reiniciar/restaurar"
#Ifndef QUIT1__WD;
Constant QUIT1__WD  = 'salir';
#Endif;
#Ifndef QUIT2__WD;
Constant QUIT2__WD  = 'terminar';
#Endif;

#Ifndef RESTART__WD;
Constant RESTART__WD = 'reiniciar';
#Endif;

#Ifndef RESTORE__WD;
Constant RESTORE__WD = 'restaurar';
#Endif;

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
    ! Formato correcto: 'palabra' código_binario objeto_referido
    ! Primera persona singular
    'me'       $$000001   0     
    'mi'       $$000001   0     
    'yo'       $$000001   0
    ! Segunda persona singular
    'te'       $$000010   0     
    'tu'       $$000010   0
    'usted'    $$000010   0
    ! Tercera persona singular
    'le'       $$000100   0     
    'la'       $$000100   0
    'lo'       $$000100   0
    'el'       $$000100   0
    'ella'     $$000100   0
    ! Primera persona plural
    'nos'      $$001000   0     
    'nosotros' $$001000   0
    'nosotras' $$001000   0
    ! Segunda persona plural
    'os'       $$010000   0     
    'vosotros' $$010000   0 
    'vosotras' $$010000   0
    'ustedes'  $$010000   0
    ! Tercera persona plural
    'les'      $$100000   0     
    'las'      $$100000   0
    'los'      $$100000   0
    'ellos'    $$100000   0
    'ellas'    $$100000   0;
#Endif;

#Ifndef LanguageDescriptors;
Array LanguageDescriptors table
    ! Formato correcto: 'palabra' código_binario
    ! Primera persona singular
    'mi'       $$000001
    'mis'      $$000001
    ! Segunda persona singular
    'tu'       $$000010
    'tus'      $$000010
    ! Tercera persona singular/plural
    'su'       $$000100
    'sus'      $$000100
    ! Primera persona plural
    'nuestro'  $$001000
    'nuestra'  $$001000
    'nuestros' $$001000
    'nuestras' $$001000
    ! Segunda persona plural
    'vuestro'  $$010000
    'vuestra'  $$010000
    'vuestros' $$010000
    'vuestras' $$010000;
#Endif;

#Ifndef LanguageNumbers;
Array LanguageNumbers table
    ! Formato correcto: 'palabra' número ['palabra' número] ...
    ! Números del 1 al 20
    'uno' 1 'un' 1 'una' 1
    'dos' 2 'tres' 3 'cuatro' 4 'cinco' 5
    'seis' 6 'siete' 7 'ocho' 8 'nueve' 9 'diez' 10
    'once' 11 'doce' 12 'trece' 13 'catorce' 14 'quince' 15
    'dieciseis' 16 'diecisiete' 17 'dieciocho' 18 'diecinueve' 19 'veinte' 20;
#Endif;

#Endif;

! Definir array de artículos para géneros y números
#Ifndef LanguageGNAsToArticles;
Array LanguageGNAsToArticles --> 
    ! Singular   Plural
    "el "       "los "      ! Masculino
    "la "       "las "      ! Femenino
    "lo "       "los "      ! Neutro
    "un "       "unos "     ! Masculino indefinido
    "una "      "unas "     ! Femenino indefinido
    "un "       "unos ";    ! Neutro indefinido
#Endif;

! Definir array de artículos para objetos
#Ifndef LanguageArticles;
Array LanguageArticles -->
    ! Artículo definido
    "el " "la " "los " "las "
    ! Artículo indefinido
    "un " "una " "unos " "unas ";
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
! RUTINAS BÁSICAS PARA EL PARSER
! ==============================================================================

! Rutina para determinar si un verbo acepta adverbios
[ LanguageVerbLikesAdverb w;
    ! La mayoría de verbos en español aceptan adverbios
    return true;
];

! Rutina para determinar si un verbo puede ser un nombre
[ LanguageVerbMayBeName w;
    ! En español, algunos verbos pueden ser nombres
    ! Por ejemplo: "comer" (verbo) vs "el comer" (nombre)
    return false;
];

! Rutina para determinar el género de objetos inanimados
[ LanguageInanimateGender;
    ! En español, los objetos inanimados tienen género gramatical
    ! Por defecto, usamos masculino
    return MASCULINE;
];

! Rutina para analizar sustantivos
[ ParseNoun obj;
    ! Implementación básica
    return -1;
];

! Rutina para analizar números
[ ParseNumber;
    ! Implementación básica
    return -1;
];

! Rutina para determinar si un objeto está en el ámbito
[ InScope obj;
    ! Implementación básica
    rfalse;
];

! Rutina para elegir objetos
[ ChooseObjects obj code;
    ! Implementación básica
    return code;
];

! Rutina para imprimir verbos
[ PrintVerb verb;
    ! Implementación básica
    print (address) verb;
];

! Rutina para determinar si un objeto es "ese" o "esos"
[ ThatOrThose obj;
    ! En español, depende del número gramatical
    if (obj has pluralname) print "esos";
    else print "ese";
];

! Rutinas para eventos del juego
[ GamePreRoutine;
    ! Implementación básica
    rtrue;
];

[ GamePostRoutine;
    ! Implementación básica
    rtrue;
];

[ AfterPrompt;
    ! Implementación básica
    rtrue;
];

[ BeforeParsing;
    ! Implementación básica
    rtrue;
];

[ AfterLife;
    ! Implementación básica
    rtrue;
];

[ TimePasses;
    ! Implementación básica
    rtrue;
];

[ DeathMessage;
    ! Implementación básica
    rtrue;
];

[ Epilogue;
    ! Implementación básica
    rtrue;
];

[ AfterRestore;
    ! Implementación básica
    rtrue;
];

[ AfterSave;
    ! Implementación básica
    rtrue;
];

[ PrintRank;
    ! Implementación básica
    rtrue;
];

[ Amusing;
    ! Implementación básica
    rtrue;
];

[ ParserError error_code;
    ! Implementación básica
    rtrue;
];

[ ObjectDoesNotFit;
    ! Implementación básica
    rtrue;
];

! Rutina para convertir a mayúsculas
[ UpperCase c;
    switch (c) {
        'a': return 'A';
        'b': return 'B';
        'c': return 'C';
        'd': return 'D';
        'e': return 'E';
        'f': return 'F';
        'g': return 'G';
        'h': return 'H';
        'i': return 'I';
        'j': return 'J';
        'k': return 'K';
        'l': return 'L';
        'm': return 'M';
        'n': return 'N';
        'o': return 'O';
        'p': return 'P';
        'q': return 'Q';
        'r': return 'R';
        's': return 'S';
        't': return 'T';
        'u': return 'U';
        'v': return 'V';
        'w': return 'W';
        'x': return 'X';
        'y': return 'Y';
        'z': return 'Z';
        '@{E1}': return '@{C1}';  ! á -> Á
        '@{E9}': return '@{C9}';  ! é -> É
        '@{ED}': return '@{CD}';  ! í -> Í
        '@{F3}': return '@{D3}';  ! ó -> Ó
        '@{FA}': return '@{DA}';  ! ú -> Ú
        '@{F1}': return '@{D1}';  ! ñ -> Ñ
        '@{FC}': return '@{DC}';  ! ü -> Ü
        default: return c;
    }
];

! Rutina para convertir a minúsculas
[ LowerCase c;
    switch (c) {
        'A': return 'a';
        'B': return 'b';
        'C': return 'c';
        'D': return 'd';
        'E': return 'e';
        'F': return 'f';
        'G': return 'g';
        'H': return 'h';
        'I': return 'i';
        'J': return 'j';
        'K': return 'k';
        'L': return 'l';
        'M': return 'm';
        'N': return 'n';
        'O': return 'o';
        'P': return 'p';
        'Q': return 'q';
        'R': return 'r';
        'S': return 's';
        'T': return 't';
        'U': return 'u';
        'V': return 'v';
        'W': return 'w';
        'X': return 'x';
        'Y': return 'y';
        'Z': return 'z';
        '@{C1}': return '@{E1}';  ! Á -> á
        '@{C9}': return '@{E9}';  ! É -> é
        '@{CD}': return '@{ED}';  ! Í -> í
        '@{D3}': return '@{F3}';  ! Ó -> ó
        '@{DA}': return '@{FA}';  ! Ú -> ú
        '@{D1}': return '@{F1}';  ! Ñ -> ñ
        '@{DC}': return '@{FC}';  ! Ü -> ü
        default: return c;
    }
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
! CONSTANTES DE OBJETOS ESPECIALES
! ==============================================================================

! Objetos especiales para el parser
#Ifndef out_obj;
Constant out_obj = 1;
#Endif;
#Ifndef in_obj;
Constant in_obj = 2;
#Endif;
#Ifndef d_obj;
Constant d_obj = 3;
#Endif;

! ==============================================================================
! CONSTANTES DE TEXTO PARA EL PARSER
! ==============================================================================

! Constantes de texto básicas
#Ifndef DARKNESS__TX;
Constant DARKNESS__TX     = "Oscuridad";
#Endif;
#Ifndef YOURSELF__TX;
Constant YOURSELF__TX     = "ti mismo";
#Endif;
#Ifndef THE__TX;
Constant THE__TX          = "el";
#Endif;
#Ifndef NOTHING__TX;
Constant NOTHING__TX      = "nada";
#Endif;
#Ifndef MYSELF__TX;
Constant MYSELF__TX       = "yo mismo";
#Endif;
#Ifndef COMMA__TX;
Constant COMMA__TX        = ", ";
#Endif;
#Ifndef AND__TX;
Constant AND__TX          = " y ";
#Endif;
#Ifndef OR__TX;
Constant OR__TX           = " o ";
#Endif;
#Ifndef THAT__TX;
Constant THAT__TX         = "eso";
#Endif;
#Ifndef THOSET__TX;
Constant THOSET__TX       = "esos";
#Endif;
#Ifndef CANTGO__TX;
Constant CANTGO__TX       = "No puedes ir por ahí.";
#Endif;
#Ifndef IS__TX;
Constant IS__TX           = "es";
#Endif;
#Ifndef ARE__TX;
Constant ARE__TX          = "son";
#Endif;
#Ifndef WAS__TX;
Constant WAS__TX          = "era";
#Endif;
#Ifndef WERE__TX;
Constant WERE__TX         = "eran";
#Endif;
#Ifndef IS2__TX;
Constant IS2__TX          = "está";
#Endif;
#Ifndef ARE2__TX;
Constant ARE2__TX         = "están";
#Endif;
#Ifndef WAS2__TX;
Constant WAS2__TX         = "estaba";
#Endif;
#Ifndef WERE2__TX;
Constant WERE2__TX        = "estaban";
#Endif;

! Constantes para puntuación
#Ifndef COLON__TX;
Constant COLON__TX        = ": ";
#Endif;

! Constantes para mensajes de estado
#Ifndef TIME__TX;
Constant TIME__TX         = "Hora: ";
#Endif;
#Ifndef SCORE__TX;
Constant SCORE__TX        = "Puntuaci@{F3}n: ";
#Endif;
#Ifndef MOVES__TX;
Constant MOVES__TX        = "Movimientos: ";
#Endif;

! Constantes para versión
#Ifndef RELEASE__TX;
Constant RELEASE__TX      = "Versi@{F3}n ";
#Endif;
#Ifndef SERNUM__TX;
Constant SERNUM__TX       = "Serie ";
#Endif;
#Ifndef INFORMV__TX;
Constant INFORMV__TX      = "Inform v";
#Endif;
#Ifndef LIBRARYV__TX;
Constant LIBRARYV__TX     = "Librer@{ED}a v";
#Endif;

! Constantes para el intérprete
#Ifndef STDTERP__TX;
Constant STDTERP__TX      = "Int@{E9}rprete est@{E1}ndar";
#Endif;
#Ifndef TERP__TX;
Constant TERP__TX         = "Int@{E9}rprete ";
#Endif;
#Ifndef VER__TX;
Constant VER__TX          = "versi@{F3}n ";
#Endif;
#Ifndef LIBSER__TX;
Constant LIBSER__TX       = "N@{FA}mero de serie de la librer@{ED}a: ";
#Endif;
#Ifndef LIBERROR__TX;
Constant LIBERROR__TX     = "Error de librer@{ED}a: ";
#Endif;

! Constantes para teclas especiales
#Ifndef NKEY__TX;
Constant NKEY__TX         = "N = siguiente";
#Endif;
#Ifndef PKEY__TX;
Constant PKEY__TX         = "P = anterior";
#Endif;
#Ifndef RKEY__TX;
Constant RKEY__TX         = "R = restaurar";
#Endif;
#Ifndef QKEY1__TX;
Constant QKEY1__TX        = "Q = salir";
#Endif;
#Ifndef QKEY2__TX;
Constant QKEY2__TX        = "X = salir";
#Endif;

! Constantes para códigos de teclas
#Ifndef NKEY1__KY;
Constant NKEY1__KY        = 'N';
#Endif;
#Ifndef NKEY2__KY;
Constant NKEY2__KY        = 'n';
#Endif;
#Ifndef PKEY1__KY;
Constant PKEY1__KY        = 'P';
#Endif;
#Ifndef PKEY2__KY;
Constant PKEY2__KY        = 'p';
#Endif;
#Ifndef QKEY1__KY;
Constant QKEY1__KY        = 'Q';
#Endif;
#Ifndef QKEY2__KY;
Constant QKEY2__KY        = 'q';
#Endif;

! Constantes para posiciones
#Ifndef STAND__TX;
Constant STAND__TX        = "de pie";
#Endif;
#Ifndef SIT__TX;
Constant SIT__TX          = "sentado";
#Endif;

! Constantes para preguntas
#Ifndef WHOM__TX;
Constant WHOM__TX         = "qui@{E9}n";
#Endif;
#Ifndef WHICH__TX;
Constant WHICH__TX        = "cu@{E1}l";
#Endif;

! Constantes adicionales para el parser
#Ifndef FULLSCORE1__WD;
Constant FULLSCORE1__WD   = "puntuacion";
#Endif;
#Ifndef FULLSCORE2__WD;
Constant FULLSCORE2__WD   = "completa";
#Endif;
#Ifndef AMUSING__WD;
Constant AMUSING__WD      = "curiosidades";
#Endif;
#Ifndef MYFORMER__TX;
Constant MYFORMER__TX     = "mi anterior ";
#Endif;
#Ifndef FORMER__TX;
Constant FORMER__TX       = "el anterior ";
#Endif;
#Ifndef LIE__TX;
Constant LIE__TX          = "acostado";
#Endif;

! Constantes para objetos especiales
#Ifndef u_obj;
Constant u_obj = 4;
#Endif;

! Constantes para rutinas del juego
Constant Compass = 0;
Constant UnknownVerb = 0;
Constant Tense = 0;
Constant DarkToDark = 0;
Constant NewRoom = 0;
Constant LookRoutine = 0;

! Constantes para el parser español
Constant inportance = 0;
Constant multitude = 0;
Constant SpanishCoreInitialise = 0;

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