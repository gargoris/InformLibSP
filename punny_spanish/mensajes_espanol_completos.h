! Mensajes Completos en Español para PunyInform
! Traducción exhaustiva con concordancia de género y número
! Mantiene compatibilidad total con el sistema original

System_file;

! ######################### MENSAJES SIMPLES TRADUCIDOS

#Ifndef MSG_TAKE_YOURSELF;
Constant MSG_TAKE_YOURSELF "Siempre te tienes a ti mismo.";
#EndIf;
#Ifndef MSG_TAKE_NO_CAPACITY;
Constant MSG_TAKE_NO_CAPACITY "Ya llevas demasiadas cosas.";
#EndIf;
#Ifndef MSG_TAKE_DEFAULT;
Constant MSG_TAKE_DEFAULT "Cogido.";
#EndIf;
#Ifndef MSG_DRINK_NOTHING_SUITABLE;
Constant MSG_DRINK_NOTHING_SUITABLE "No hay nada apropiado para beber aqui.";
#EndIf;
#Ifndef MSG_DROP_DROPPED;
Constant MSG_DROP_DROPPED "Dejado.";
#EndIf;
#Ifndef MSG_THROW_ANIMATE;
Constant MSG_THROW_ANIMATE "Inutil.";
#Endif;
#Ifndef MSG_THROW_DEFAULT;
Constant MSG_THROW_DEFAULT "Te falta valor en el momento crucial.";
#Endif;
#Ifndef MSG_SMELL_DEFAULT;
Constant MSG_SMELL_DEFAULT "No hueles nada inesperado.";
#Endif;
#Ifndef MSG_LISTEN_DEFAULT;
Constant MSG_LISTEN_DEFAULT "No oyes nada inesperado.";
#Endif;
#Ifndef MSG_TELL_PLAYER;
Constant MSG_TELL_PLAYER "Hablas contigo mismo durante un rato.";
#Endif;
#Ifndef MSG_TELL_DEFAULT;
Constant MSG_TELL_DEFAULT "Esto no provoca reaccion alguna.";
#Endif;
#Ifndef MSG_ENTER_ALREADY;
Constant MSG_ENTER_ALREADY "Pero ya estas ahi!";
#Endif;
#Ifndef MSG_EXIT_ALREADY;
Constant MSG_EXIT_ALREADY "Pero no estas dentro de nada en este momento!";
#Endif;
#Ifndef MSG_EXIT_NOT_ON;
Constant MSG_EXIT_NOT_ON "No estas sobre eso.";
#Endif;
#Ifndef MSG_EXIT_NOT_IN;
Constant MSG_EXIT_NOT_IN "No estas dentro de eso.";
#Endif;
#Ifndef MSG_INVENTORY_EMPTY;
Constant MSG_INVENTORY_EMPTY "No llevas nada.";
#Endif;
#Ifndef MSG_GO_CANT_GO;
Constant MSG_GO_CANT_GO "No puedes ir por ahi.";
#Endif;
#Ifndef MSG_SAVE_DEFAULT;
Constant MSG_SAVE_DEFAULT "Hecho.";
#Endif;
#Ifndef MSG_INSERT_ITSELF;
Constant MSG_INSERT_ITSELF "No puedes meter algo dentro de si mismo.";
#Endif;
#Ifndef MSG_PUTON_ITSELF;
Constant MSG_PUTON_ITSELF "No puedes poner algo sobre si mismo.";
#Endif;
#Ifndef MSG_ATTACK_DEFAULT;
Constant MSG_ATTACK_DEFAULT "La violencia no es la solucion.";
#Endif;
#Ifndef MSG_FILL_NO_WATER;
Constant MSG_FILL_NO_WATER "Pero no hay agua aqui para llevar.";
#EndIf;
#Ifndef MSG_DIG_NO_USE;
Constant MSG_DIG_NO_USE "Cavar no serviria de nada aqui.";
#EndIf;
#Ifndef MSG_WAIT_DEFAULT;
Constant MSG_WAIT_DEFAULT "No pasa nada.";
#EndIf;
#Ifndef MSG_TOUCH_DEFAULT;
Constant MSG_TOUCH_DEFAULT "No sientes nada inesperado.";
#EndIf;
#Ifndef MSG_PUSHDIR_DEFAULT;
Constant MSG_PUSHDIR_DEFAULT "Es eso lo mejor que se te ocurre?";
#EndIf;
#Ifndef MSG_JUMP;
Constant MSG_JUMP "Saltas en el sitio, inutilmente.";
#EndIf;
#Ifndef MSG_REMOVE_DEFAULT;
Constant MSG_REMOVE_DEFAULT "Quitado.";
#EndIf;
#Ifndef MSG_SEARCH_NOTHING_SPECIAL;
Constant MSG_SEARCH_NOTHING_SPECIAL "No encuentras nada especial.";
#EndIf;
#Ifndef MSG_OOPS_DEFAULT;
Constant MSG_OOPS_DEFAULT "No tiene importancia.";
#EndIf;

! Mensajes del parser en español
#Ifndef MSG_PARSER_ONLY_TO_ANIMATE;
Constant MSG_PARSER_ONLY_TO_ANIMATE "Solo puedes hacer eso con algo animado.";
#EndIf;
#Ifndef MSG_PARSER_NOT_MULTIPLE_VERB;
Constant MSG_PARSER_NOT_MULTIPLE_VERB "No puedes usar objetos multiples con ese verbo.";
#EndIf;
#Ifndef MSG_PARSER_NOT_MULTIPLE_DIRS;
Constant MSG_PARSER_NOT_MULTIPLE_DIRS "No puedes usar direcciones multiples.";
#EndIf;
#Ifndef MSG_PARSER_BAD_NUMBER;
Constant MSG_PARSER_BAD_NUMBER "No entendi ese numero.";
#EndIf;
#Ifndef MSG_PARSER_NO_INPUT;
Constant MSG_PARSER_NO_INPUT "Como dices?";
#EndIf;
#Ifndef MSG_PARSER_UNKNOWN_SENTENCE;
Constant MSG_PARSER_UNKNOWN_SENTENCE "No entiendo esa frase.";
#EndIf;
#Ifndef MSG_PARSER_UNKNOWN_VERB;
Constant MSG_PARSER_UNKNOWN_VERB "Ese no es un verbo que reconozca.";
#EndIf;
#Ifndef MSG_PARSER_CANT_DISAMBIGUATE;
Constant MSG_PARSER_CANT_DISAMBIGUATE "Sigo sin entender a que te refieres.";
#EndIf;
#Ifndef MSG_PARSER_UNKNOWN_PERSON;
Constant MSG_PARSER_UNKNOWN_PERSON "No veo a quien te refieres.";
#EndIf;
#Ifndef MSG_PARSER_NOSUCHTHING;
Constant MSG_PARSER_NOSUCHTHING "No puedes ver tal cosa.";
#EndIf;
#Ifndef MSG_PARSER_CANT_OOPS;
Constant MSG_PARSER_CANT_OOPS "Lo siento, eso no se puede corregir.";
#EndIf;
#Ifndef MSG_PARSER_COMPLEX_AGAIN;
Constant MSG_PARSER_COMPLEX_AGAIN "El comando 'otra vez' debe ir en una linea nueva.^";
#EndIf;
#Ifndef MSG_PARSER_NOTHING_TO_AGAIN;
Constant MSG_PARSER_NOTHING_TO_AGAIN "Dificilmente puedes repetir eso.";
#EndIf;
#Ifndef MSG_PARSER_BE_MORE_SPECIFIC;
Constant MSG_PARSER_BE_MORE_SPECIFIC "Necesitas ser mas especifico.";
#EndIf;
#Ifndef MSG_PARSER_NO_MULTIPLES_FOR_NPC;
Constant MSG_PARSER_NO_MULTIPLES_FOR_NPC "Solo puedes referirte a objetos individuales cuando hablas con otros.";
#EndIf;

! Mensajes de oscuridad
#IfnDef OPTIONAL_NO_DARKNESS;
#IfnDef MSG_NOW_DARK;
Constant MSG_NOW_DARK "^Ahora esta completamente oscuro aqui.";
#EndIf;
#EndIf;

! Mensajes de puntuacion completa
#IfDef OPTIONAL_FULL_SCORE;
#IfDef OPTIONAL_SCORED;
#Ifndef MSG_FULLSCORE_OBJECTS;
Constant MSG_FULLSCORE_OBJECTS "encontrando varios objetos";
#EndIf;
#Ifndef MSG_FULLSCORE_ROOMS;
Constant MSG_FULLSCORE_ROOMS "visitando varios lugares";
#EndIf;
#EndIf;
#Ifndef MSG_FULLSCORE_ACTIONS;
Constant MSG_FULLSCORE_ACTIONS "realizando acciones notables";
#EndIf;
#EndIf;

! Mensajes de deshacer
#IfDef OPTIONAL_PROVIDE_UNDO_FINAL;
#Ifndef MSG_UNDO_NOTHING_DONE;
Constant MSG_UNDO_NOTHING_DONE "[No puedes deshacer lo que no has hecho!]";
#EndIf;
#Ifndef MSG_UNDO_NOT_PROVIDED;
Constant MSG_UNDO_NOT_PROVIDED "[Tu interprete no proporciona la funcion de deshacer.]";
#EndIf;
#Ifndef MSG_UNDO_FAILED;
Constant MSG_UNDO_FAILED "Deshacer fallo.";
#EndIf;
#Ifndef MSG_UNDO_DONE;
Constant MSG_UNDO_DONE "Turno anterior deshecho.";
#EndIf;
#EndIf;

! Mensajes de comentarios
#Ifndef MSG_COMMENT_TRANSCRIPT;
Constant MSG_COMMENT_TRANSCRIPT "[Comentario grabado]^";
#EndIf;
#Ifndef MSG_COMMENT_NO_TRANSCRIPT;
#ifdef OPTIONAL_EXTENDED_METAVERBS;
Constant MSG_COMMENT_NO_TRANSCRIPT "[Comentario no grabado. Para grabar comentarios, inicia una transcripcion.]^";
#IfNot;
Constant MSG_COMMENT_NO_TRANSCRIPT "[Comentario no grabado. Este juego no soporta transcripciones.]^";
#EndIf;
#EndIf;

! Mensajes del conjunto extendido de verbos
#IfDef OPTIONAL_EXTENDED_VERBSET;
#Ifndef MSG_BURN_DEFAULT;
Constant MSG_BURN_DEFAULT "Este acto peligroso conseguiria poco.";
#EndIf;
#Ifndef MSG_BUY_DEFAULT;
Constant MSG_BUY_DEFAULT "No hay nada en venta.";
#EndIf;
#Ifndef MSG_EMPTY_WOULDNT_ACHIEVE;
Constant MSG_EMPTY_WOULDNT_ACHIEVE "Eso apenas vacia algo.";
#EndIf;
#Ifndef MSG_RHETORICAL_QUESTION;
Constant MSG_RHETORICAL_QUESTION "Esa fue una pregunta retorica.";
#EndIf;
#Ifndef MSG_PRAY_DEFAULT;
Constant MSG_PRAY_DEFAULT "Nada practico resulta de tu oracion.";
#EndIf;
#Ifndef MSG_SING_DEFAULT;
Constant MSG_SING_DEFAULT "Tu canto es abominable.";
#EndIf;
#Ifndef MSG_SLEEP_DEFAULT;
Constant MSG_SLEEP_DEFAULT "No te sientes especialmente somnoliento.";
#EndIf;
#Ifndef MSG_SORRY_DEFAULT;
Constant MSG_SORRY_DEFAULT "Oh, no te disculpes.";
#EndIf;
#Ifndef MSG_SQUEEZE_YOURSELF;
Constant MSG_SQUEEZE_YOURSELF "Manten las manos quietas.";
#EndIf;
#Ifndef MSG_SWIM_DEFAULT;
Constant MSG_SWIM_DEFAULT "No hay suficiente agua para nadar.";
#EndIf;
#Ifndef MSG_SWING_DEFAULT;
Constant MSG_SWING_DEFAULT "No hay nada sensato que columpiear aqui.";
#EndIf;
#Ifndef MSG_TASTE_DEFAULT;
Constant MSG_TASTE_DEFAULT "No saboreas nada inesperado.";
#EndIf;
#Ifndef MSG_THINK_DEFAULT;
Constant MSG_THINK_DEFAULT "Que buena idea.";
#EndIf;
#Ifndef MSG_WAVEHANDS_DEFAULT;
Constant MSG_WAVEHANDS_DEFAULT "Saludas con la mano, sintiendote tonto.";
#EndIf;
#Ifndef MSG_WAKE_DEFAULT;
Constant MSG_WAKE_DEFAULT "La terrible verdad es que esto no es un sueno.";
#Endif;
#Ifndef MSG_WAKEOTHER_DEFAULT;
Constant MSG_WAKEOTHER_DEFAULT "Eso parece innecesario.";
#Endif;
#Ifndef MSG_KISS_PLAYER;
Constant MSG_KISS_PLAYER "Si crees que eso te ayudara.";
#Endif;
#Ifndef MSG_KISS_DEFAULT;
Constant MSG_KISS_DEFAULT "Manten tu mente en el juego.";
#Endif;
#Ifndef MSG_MILD_DEFAULT;
Constant MSG_MILD_DEFAULT "Cierto.";
#EndIf;
#Ifndef MSG_STRONG_DEFAULT;
Constant MSG_STRONG_DEFAULT "Los verdaderos aventureros no usan tal lenguaje.";
#EndIf;
#EndIf;

! ######################### FUNCIONES AUXILIARES PARA ESPAÑOL

[ EsFemeninoMsg p_obj;
    if(p_obj has female) rtrue; 
    rfalse;
];

[ EsPluralMsg p_obj;
    if(p_obj has pluralname) rtrue; 
    rfalse;
];

[ EsAnimadoMsg p_obj;
    if(p_obj has animate) rtrue; 
    rfalse;
];

! Artículos con concordancia
[ ElLaLosLasMsg p_obj;
    if (EsPluralMsg(p_obj)) {
        if (EsFemeninoMsg(p_obj)) print "las"; else print "los";
    } else {
        if (EsFemeninoMsg(p_obj)) print "la"; else print "el";
    }
];

[ UnUnaUnosUnasMsg p_obj;
    if (EsPluralMsg(p_obj)) {
        if (EsFemeninoMsg(p_obj)) print "unas"; else print "unos";
    } else {
        if (EsFemeninoMsg(p_obj)) print "una"; else print "un";
    }
];

! Pronombres demostrativos
[ EsteEstaEstosEstasMsg p_obj;
    if (EsPluralMsg(p_obj)) {
        if (EsFemeninoMsg(p_obj)) print "estas"; else print "estos";
    } else {
        if (EsFemeninoMsg(p_obj)) print "esta"; else print "este";
    }
];

[ EseEsaEsosEsasMsg p_obj;
    if (EsPluralMsg(p_obj)) {
        if (EsFemeninoMsg(p_obj)) print "esas"; else print "esos";
    } else {
        if (EsFemeninoMsg(p_obj)) print "esa"; else print "ese";
    }
];

! Pronombres objeto
[ LoLaLosLasMsg p_obj;
    if (EsPluralMsg(p_obj)) {
        if (EsFemeninoMsg(p_obj)) print "las"; else print "los";
    } else {
        if (EsFemeninoMsg(p_obj)) print "la"; else print "lo";
    }
];

! Conjugación del verbo SER
[ EsSonMsg p_obj;
    if (EsPluralMsg(p_obj) || p_obj == player) print "son"; else print "es";
];

! Conjugación del verbo ESTAR
[ EstaEstanMsg p_obj;
    if (EsPluralMsg(p_obj)) print "estan"; else print "esta";
];

! Función para "Ello/Ellos/Ella/Ellas"
[ ElEllaEllosEllasMsg p_obj;
    if (p_obj == player) { print "tu"; rtrue; }
    if (EsPluralMsg(p_obj)) {
        if (EsFemeninoMsg(p_obj)) print "ellas"; else print "ellos";
    } else {
        if (EsAnimadoMsg(p_obj)) {
            if (EsFemeninoMsg(p_obj)) print "ella"; else print "el";
        } else {
            print "ello";
        }
    }
];

! Función para objetos como sujeto con mayúscula
[ ElEllaEsMsg p_obj;
    if (p_obj == player) { print "Tu"; return; }
    if (EsPluralMsg(p_obj)) {
        if (EsFemeninoMsg(p_obj)) print "Ellas"; else print "Ellos";
    } else {
        if (EsAnimadoMsg(p_obj)) {
            if (EsFemeninoMsg(p_obj)) print "Ella"; else print "El";
        } else {
            print "Eso";
        }
    }
    print " ";
    EsSonMsg(p_obj);
];

! Función para concordancia de participios
[ ParticipioConcordancia p_obj p_participio;
    ! p_participio debería ser la raíz sin terminación
    switch(p_participio) {
        'cogid': ! cogido/cogida/cogidos/cogidas
            if (EsPluralMsg(p_obj)) {
                if (EsFemeninoMsg(p_obj)) print "cogidas"; else print "cogidos";
            } else {
                if (EsFemeninoMsg(p_obj)) print "cogida"; else print "cogido";
            }
        'dejad': ! dejado/dejada/dejados/dejadas
            if (EsPluralMsg(p_obj)) {
                if (EsFemeninoMsg(p_obj)) print "dejadas"; else print "dejados";
            } else {
                if (EsFemeninoMsg(p_obj)) print "dejada"; else print "dejado";
            }
        'abiert': ! abierto/abierta/abiertos/abiertas
            if (EsPluralMsg(p_obj)) {
                if (EsFemeninoMsg(p_obj)) print "abiertas"; else print "abiertos";
            } else {
                if (EsFemeninoMsg(p_obj)) print "abierta"; else print "abierto";
            }
        'cerrad': ! cerrado/cerrada/cerrados/cerradas
            if (EsPluralMsg(p_obj)) {
                if (EsFemeninoMsg(p_obj)) print "cerradas"; else print "cerrados";
            } else {
                if (EsFemeninoMsg(p_obj)) print "cerrada"; else print "cerrado";
            }
        'vest': ! vestido/vestida (pero para "puesto")
            print "puest";
            if (EsPluralMsg(p_obj)) {
                if (EsFemeninoMsg(p_obj)) print "as"; else print "os";
            } else {
                if (EsFemeninoMsg(p_obj)) print "a"; else print "o";
            }
        default: ! Por defecto: hecho/hecha/hechos/hechas
            print "hech";
            if (EsPluralMsg(p_obj)) {
                if (EsFemeninoMsg(p_obj)) print "as"; else print "os";
            } else {
                if (EsFemeninoMsg(p_obj)) print "a"; else print "o";
            }
    }
];

! Equivalentes españoles de las funciones originales
[ EsoEsosMsg p_obj;
    if (EsPluralMsg(p_obj)) print "esos"; else print "eso";
];

[ EsEseEsaMsg p_obj;
    if (EsPluralMsg(p_obj)) {
        if (EsFemeninoMsg(p_obj)) print "esas"; else print "esos";
    } else {
        if (EsFemeninoMsg(p_obj)) print "esa"; else print "ese";
    }
];

! Función para "No lo/la/los/las + verbo"
[ NoLoLaMsg p_obj;
    print "No ";
    LoLaLosLasMsg(p_obj);
];

! ######################### MENSAJES COMPLEJOS CON MISMOS NÚMEROS

Default MSG_CLOSE_YOU_CANT = 2;
Default MSG_ENTER_YOU_CANT = 3;
Default MSG_EXAMINE_NOTHING_SPECIAL = 4;
Default MSG_TAKE_ANIMATE = 5;
Default MSG_TAKE_PLAYER_PARENT = 6;
Default MSG_EAT_ANIMATE = 7;
Default MSG_DROP_NOT_HOLDING = 8;
Default MSG_OPEN_DEFAULT = 9;
Default MSG_CLOSE_DEFAULT = 10;
Default MSG_LOOK_BEFORE_ROOMNAME = 11;
Default MSG_SHOW_NOT_HOLDING = 12;
Default MSG_SHOW_DEFAULT = 13;
Default MSG_GIVE_NOT_HOLDING = 14;
Default MSG_GIVE_DEFAULT = 15;
Default MSG_ASKFOR_DEFAULT = 16;
Default MSG_ASKTO_DEFAULT = 17;
Default MSG_ENTER_DEFAULT = 18;
Default MSG_EXIT_FIRST_LEAVE = 19;
Default MSG_ENTER_NOT_OPEN = 20;
Default MSG_EXIT_NOT_OPEN = 21;
Default MSG_EXIT_DEFAULT = 22;
Default MSG_INVENTORY_DEFAULT = 23;
Default MSG_GO_FIRST_LEAVE = 24;
Default MSG_GIVE_PLAYER = 25;
Default MSG_SAVE_FAILED = 26;
Default MSG_RESTORE_FAILED = 27;
Default MSG_RESTART_FAILED = 28;
Default MSG_INSERT_DEFAULT = 29;
Default MSG_INSERT_NOT_OPEN = 30;
Default MSG_ASK_DEFAULT = 31;
Default MSG_ANSWER_DEFAULT = 32;
Default MSG_RESTART_RESTORE_OR_QUIT = 33;
Default MSG_AREYOUSUREQUIT = 34;
Default MSG_WEAR_ALREADY_WORN = 35;
Default MSG_WEAR_NOT_CLOTHING = 36;
Default MSG_WEAR_NOT_HOLDING = 37;
Default MSG_WEAR_DEFAULT = 38;
Default MSG_INSERT_ALREADY = 39;
Default MSG_INSERT_NO_ROOM = 40;
Default MSG_PUTON_ALREADY = 41;
Default MSG_PUTON_NO_ROOM = 42;
Default MSG_PUTON_DEFAULT = 43;
Default MSG_GO_DOOR_CLOSED = 44;
Default MSG_SWITCH_ON_NOT_SWITCHABLE = 45;
Default MSG_SWITCH_OFF_NOT_SWITCHABLE = 46;
Default MSG_SWITCH_ON_ON = 47;
Default MSG_SWITCH_OFF_NOT_ON = 48;
Default MSG_SWITCH_ON_DEFAULT = 49;
Default MSG_SWITCH_OFF_DEFAULT = 50;
Default MSG_PUSH_STATIC = 51;
Default MSG_PULL_STATIC = 52;
Default MSG_TURN_STATIC = 53;
Default MSG_PUSH_SCENERY = 54;
Default MSG_PULL_SCENERY = 55;
Default MSG_TURN_SCENERY = 56;
Default MSG_PUSH_ANIMATE = 57;
Default MSG_PULL_ANIMATE = 58;
Default MSG_TURN_ANIMATE = 59;
Default MSG_TURN_DEFAULT = 60;
Default MSG_PUSH_DEFAULT = 61;
Default MSG_PULL_DEFAULT = 62;
Default MSG_YOU_HAVE_WON = 63;
Default MSG_YOU_HAVE_DIED = 64;
Default MSG_OPEN_YOU_CANT = 65;
Default MSG_PARSER_NOTHING_TO_VERB = 66;
Default MSG_TOUCHABLE_FOUND_CLOSED = 67;
Default MSG_CONSULT_NOTHING_INTERESTING = 68;
Default MSG_CUT_NO_USE = 69;
Default MSG_SACK_PUTTING = 70;
Default MSG_LOCK_NOT_A_LOCK = 71;
Default MSG_LOCK_ALREADY_LOCKED = 72;
Default MSG_LOCK_CLOSE_FIRST = 73;
Default MSG_LOCK_KEY_DOESNT_FIT = 74;
Default MSG_LOCK_DEFAULT = 75;
Default MSG_DISROBE_NOT_WEARING = 76;
Default MSG_DISROBE_DEFAULT = 77;
Default MSG_REMOVE_CLOSED = 78;
Default MSG_REMOVE_NOT_HERE = 79;
Default MSG_SEARCH_IN_IT_ISARE = 80;
Default MSG_SEARCH_ON_IT_ISARE = 81;
Default MSG_SEARCH_EMPTY = 82;
Default MSG_SEARCH_NOTHING_ON = 83;
Default MSG_SEARCH_CANT_SEE_CLOSED = 84;
Default MSG_EAT_DEFAULT = 85;
#Ifdef OPTIONAL_FULL_SCORE;
Default MSG_FULLSCORE_START = 86;
Default MSG_FULLSCORE_END = 87;
#Endif;
Default MSG_SCORE_DEFAULT = 88;
Default MSG_UNLOCK_NOT_A_LOCK = 89;
Default MSG_UNLOCK_ALREADY_UNLOCKED = 90;
Default MSG_UNLOCK_KEY_DOESNT_FIT = 91;
Default MSG_UNLOCK_DEFAULT = 92;
Default MSG_ENTER_BAD_LOCATION = 93;
Default MSG_PROMPT = 94;
#Ifndef OPTIONAL_NO_DARKNESS;
Default MSG_EXAMINE_DARK = 95;
Default MSG_SEARCH_DARK = 96;
#Endif;
Default MSG_EXAMINE_ONOFF = 97;
Default MSG_ORDERS_WONT = 98;
Default MSG_AUTO_TAKE = 99;
Default MSG_AUTO_DISROBE = 100;
Default MSG_PARSER_PARTIAL_MATCH = 101;
Default MSG_TAKE_BELONGS = 102;
Default MSG_TAKE_PART_OF = 103;
Default MSG_TAKE_NOT_AVAILABLE = 104;
Default MSG_PARSER_CONTAINER_ISNT_OPEN = 105;
Default MSG_PARSER_NOT_HOLDING = 106;
Default MSG_PARSER_CANT_TALK = 107;
Default MSG_WAVE_NOTHOLDING = 108;
Default MSG_JUMP_OVER = 109;
Default MSG_TIE_DEFAULT = 110;
Default MSG_CLOSE_NOT_OPEN = 111;
Default MSG_RUB_DEFAULT = 112;
Default MSG_SQUEEZE_DEFAULT = 113;
Default MSG_EXAMINE_CLOSED = 114;
Default MSG_EMPTY_IS_CLOSED = 115;
Default MSG_PARSER_NO_NEED_REFER_TO = 116;
Default MSG_PARSER_DONT_UNDERSTAND_WORD = 117;
Default MSG_INSERT_NOT_CONTAINER = 118;
Default MSG_TRANSFER_ALREADY = 119;
Default MSG_YES_OR_NO = 120;
Default MSG_RESTART_CONFIRM = 121;
#Ifndef NO_SCORE;
Default MSG_PARSER_NEW_SCORE = 122;
#Endif;
Default MSG_CLIMB_ANIMATE = 123;
Default MSG_CLIMB_DEFAULT = 124;
Default MSG_PARSER_BAD_PATTERN_PREFIX = 125;
Default MSG_PARSER_BAD_PATTERN_SUFFIX = 126;
Default MSG_TAKE_ALREADY_HAVE = 127;
Default MSG_SHOUT_DEFAULT = 128;
Default MSG_SHOUTAT_DEFAULT = 129;
Default MSG_INSERT_ANIMATE = 130;
Default MSG_PUTON_ANIMATE = 131;
Default MSG_LOOKMODE_NORMAL = 132;
Default MSG_LOOKMODE_LONG = 133;
Default MSG_LOOKMODE_SHORT = 134;
Default MSG_AUTO_TAKE_NOT_HELD = 135;
Default MSG_AUTO_DISROBE_WORN = 136;
Default MSG_TAKE_SCENERY = 137;
Default MSG_TAKE_STATIC = 138;
Default MSG_EAT_INEDIBLE = 139;
Default MSG_OPEN_ALREADY = 140;
Default MSG_OPEN_LOCKED = 141;
Default MSG_PUTON_NOT_SUPPORTER = 142;
Default MSG_PARSER_NO_IT = 143;
Default MSG_PARSER_CANT_SEE_IT = 144;
Default MSG_NOTIFY_ON = 145;
Default MSG_NOTIFY_OFF = 146;
Default MSG_ENTER_HELD = 147;

#IfDef OPTIONAL_EXTENDED_VERBSET;
Default MSG_BLOW_DEFAULT = 200;
Default MSG_WAVE_DEFAULT = 201;
Default MSG_EMPTY_ALREADY_EMPTY = 202;
Default MSG_SET_DEFAULT = 203;
Default MSG_SET_TO_DEFAULT = 204;
Default MSG_EMPTY_NOT_CONTAINER = 205;
#EndIf;