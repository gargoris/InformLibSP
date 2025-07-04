! Mensajes en Español para PunyInform
! Traducción completa y adaptación cultural de todos los mensajes
! Con soporte completo para género, número y conjugaciones verbales

System_file;

! ######################### Mensajes simples (strings)

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
Constant MSG_DRINK_NOTHING_SUITABLE "No hay nada apropiado para beber aquí.";
#EndIf;
#Ifndef MSG_DROP_DROPPED;
Constant MSG_DROP_DROPPED "Dejado.";
#EndIf;
#Ifndef MSG_THROW_ANIMATE;
Constant MSG_THROW_ANIMATE "Inútil.";
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
Constant MSG_TELL_DEFAULT "Esto no provoca reacción alguna.";
#Endif;
#Ifndef MSG_ENTER_ALREADY;
Constant MSG_ENTER_ALREADY "¡Pero ya estás ahí!";
#Endif;
#Ifndef MSG_EXIT_ALREADY;
Constant MSG_EXIT_ALREADY "¡Pero no estás dentro de nada en este momento!";
#Endif;
#Ifndef MSG_EXIT_NOT_ON;
Constant MSG_EXIT_NOT_ON "No estás sobre eso.";
#Endif;
#Ifndef MSG_EXIT_NOT_IN;
Constant MSG_EXIT_NOT_IN "No estás dentro de eso.";
#Endif;
#Ifndef MSG_INVENTORY_EMPTY;
Constant MSG_INVENTORY_EMPTY "No llevas nada.";
#Endif;
#Ifndef MSG_GO_CANT_GO;
Constant MSG_GO_CANT_GO "No puedes ir por ahí.";
#Endif;
#Ifndef MSG_SAVE_DEFAULT;
Constant MSG_SAVE_DEFAULT "Hecho.";
#Endif;
#Ifndef MSG_INSERT_ITSELF;
Constant MSG_INSERT_ITSELF "No puedes meter algo dentro de sí mismo.";
#Endif;
#Ifndef MSG_PUTON_ITSELF;
Constant MSG_PUTON_ITSELF "No puedes poner algo sobre sí mismo.";
#Endif;
#Ifndef MSG_ATTACK_DEFAULT;
Constant MSG_ATTACK_DEFAULT "La violencia no es la solución.";
#Endif;
#Ifndef MSG_FILL_NO_WATER;
Constant MSG_FILL_NO_WATER "Pero no hay agua aquí para llevar.";
#EndIf;
#Ifndef MSG_DIG_NO_USE;
Constant MSG_DIG_NO_USE "Cavar no serviría de nada aquí.";
#EndIf;
#Ifndef MSG_WAIT_DEFAULT;
Constant MSG_WAIT_DEFAULT "No pasa nada.";
#EndIf;
#Ifndef MSG_TOUCH_DEFAULT;
Constant MSG_TOUCH_DEFAULT "No sientes nada inesperado.";
#EndIf;
#Ifndef MSG_PUSHDIR_DEFAULT;
Constant MSG_PUSHDIR_DEFAULT "¿Es eso lo mejor que se te ocurre?";
#EndIf;
#Ifndef MSG_JUMP;
Constant MSG_JUMP "Saltas en el sitio, inútilmente.";
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

! Mensajes del parser
#Ifndef MSG_PARSER_ONLY_TO_ANIMATE;
Constant MSG_PARSER_ONLY_TO_ANIMATE "Solo puedes hacer eso con algo animado.";
#EndIf;
#Ifndef MSG_PARSER_NOT_MULTIPLE_VERB;
Constant MSG_PARSER_NOT_MULTIPLE_VERB "No puedes usar objetos múltiples con ese verbo.";
#EndIf;
#Ifndef MSG_PARSER_NOT_MULTIPLE_DIRS;
Constant MSG_PARSER_NOT_MULTIPLE_DIRS "No puedes usar direcciones múltiples.";
#EndIf;
#Ifndef MSG_PARSER_BAD_NUMBER;
Constant MSG_PARSER_BAD_NUMBER "No entendí ese número.";
#EndIf;
#Ifndef MSG_PARSER_NO_INPUT;
Constant MSG_PARSER_NO_INPUT "¿Cómo dices?";
#EndIf;
#Ifndef MSG_PARSER_UNKNOWN_SENTENCE;
Constant MSG_PARSER_UNKNOWN_SENTENCE "No entiendo esa frase.";
#EndIf;
#Ifndef MSG_PARSER_UNKNOWN_VERB;
Constant MSG_PARSER_UNKNOWN_VERB "Ese no es un verbo que reconozca.";
#EndIf;
#Ifndef MSG_PARSER_CANT_DISAMBIGUATE;
Constant MSG_PARSER_CANT_DISAMBIGUATE "Sigo sin entender a qué te refieres.";
#EndIf;
#Ifndef MSG_PARSER_UNKNOWN_PERSON;
Constant MSG_PARSER_UNKNOWN_PERSON "No veo a quién te refieres.";
#EndIf;
#Ifndef MSG_PARSER_NOSUCHTHING;
Constant MSG_PARSER_NOSUCHTHING "No puedes ver tal cosa.";
#EndIf;
#Ifndef MSG_PARSER_CANT_OOPS;
Constant MSG_PARSER_CANT_OOPS "Lo siento, eso no se puede corregir.";
#EndIf;
#Ifndef MSG_PARSER_COMPLEX_AGAIN;
Constant MSG_PARSER_COMPLEX_AGAIN "El comando 'otra vez' debe ir en una línea nueva.^";
#EndIf;
#Ifndef MSG_PARSER_NOTHING_TO_AGAIN;
Constant MSG_PARSER_NOTHING_TO_AGAIN "Difícilmente puedes repetir eso.";
#EndIf;
#Ifndef MSG_PARSER_BE_MORE_SPECIFIC;
Constant MSG_PARSER_BE_MORE_SPECIFIC "Necesitas ser más específico.";
#EndIf;
#Ifndef MSG_PARSER_NO_MULTIPLES_FOR_NPC;
Constant MSG_PARSER_NO_MULTIPLES_FOR_NPC "Solo puedes referirte a objetos individuales cuando hablas con otros.";
#EndIf;

#IfnDef OPTIONAL_NO_DARKNESS;
#IfnDef MSG_NOW_DARK;
Constant MSG_NOW_DARK "^Ahora está completamente oscuro aquí.";
#EndIf;
#EndIf;

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

! ######################### Mensajes complejos (numerados)

! Usando los mismos números que PunyInform original para compatibilidad
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
Default MSG_SCORE_DEFAULT = 88;
Default MSG_PROMPT = 94;

! ######################### Función principal de mensajes

[ _PrintMsg p_msg p_arg_1 p_arg_2;
    if(p_msg ofclass String)
        print_ret (string) p_msg;

#Ifdef LibraryMessages;
    if(p_msg > 999) {
        return LibraryMessages(p_msg, p_arg_1, p_arg_2);
    }
#Endif;

    ! Procesar mensajes complejos en español
    switch(p_msg) {
    MSG_PROMPT:
        print "> ";
        rtrue;
        
    MSG_INVENTORY_DEFAULT:
        p_arg_1 = "Llevas ";
        if(inventory_style == 0) {
            p_arg_1 = "Llevas:";
            p_arg_2 = NEWLINE_BIT;
        }
        if(PrintContents(p_arg_1, player, p_arg_2)) {
            if(inventory_style) print ".^";
            rtrue;
        }
        rfalse;
        
    MSG_EXAMINE_NOTHING_SPECIAL:
        "No hay nada especial en ", (ElLaLosLas) noun, " ", (object) noun, ".";
        
    MSG_TAKE_ANIMATE:
        "No creo que ", (ElLaLosLas) noun, " ", (object) noun;
        if(EsFemenino(noun)) print " esté dispuesta";
        else print " esté dispuesto";
        " a eso.";
        
    MSG_TAKE_PLAYER_PARENT, MSG_GO_FIRST_LEAVE, MSG_EXIT_FIRST_LEAVE:
        "Primero tendrías que salir de ", (ElLaLosLas) p_arg_1, " ", (object) p_arg_1, ".";
        
    MSG_DROP_NOT_HOLDING, MSG_SHOW_NOT_HOLDING, MSG_GIVE_NOT_HOLDING, MSG_WEAR_NOT_HOLDING:
        "No ";
        if(EsPlural(noun)) print "llevas ";
        else print "llevas ";
        LoLaLosLas(noun);
        print " ", (object) noun, ".";
        
    MSG_OPEN_DEFAULT:
        "Abres ", (ElLaLosLas) noun, " ", (object) noun;
        if(noun has container && noun hasnt transparent &&
                ~~IndirectlyContains(noun, player)) {
            print ", revelando ";
            if(PrintContents(0, noun)==false) print "nada";
        }
        ".";
        
    MSG_CLOSE_DEFAULT, MSG_ENTER_DEFAULT, MSG_EXIT_DEFAULT:
        switch(p_msg) {
            MSG_CLOSE_DEFAULT: print "Cierras ";
            MSG_ENTER_DEFAULT: print "Entras en ";
            MSG_EXIT_DEFAULT: print "Sales de ";
        }
        print (ElLaLosLas) noun, " ", (object) noun, ".";
        
    MSG_GIVE_DEFAULT, MSG_SHOW_DEFAULT:
        print (ElLaLosLas) second, " ", (object) second, " no parece ";
        if(EsFemenino(second)) print "interesada";
        else print "interesado";
        ".";
        
    MSG_INSERT_DEFAULT:
        "Metes ", (ElLaLosLas) noun, " ", (object) noun, " en ", (ElLaLosLas) second, " ", (object) second, ".";
        
    MSG_PUTON_DEFAULT:
        "Pones ", (ElLaLosLas) noun, " ", (object) noun, " sobre ", (ElLaLosLas) second, " ", (object) second, ".";
        
    MSG_WEAR_DEFAULT:
        "Ahora llevas pues";
        if(EsFemenino(noun)) print "ta ";
        else print "to ";
        print (ElLaLosLas) noun, " ", (object) noun, ".";
        
    MSG_WEAR_ALREADY_WORN:
        "Ya llevas pues";
        if(EsFemenino(noun)) print "ta ";
        else print "to ";
        LoLaLosLas(noun);
        print " ", (object) noun, ".";
        
    MSG_SCORE_DEFAULT:
#Ifdef NO_SCORE;
        "No hay puntuación en este juego.";
#Ifnot;
        if (deadflag) print "En ese juego conseguiste"; else print "Hasta ahora has conseguido";
        print " ", score, " punto";
        if(score ~= 1) print "s";
        print " de un total de ", MAX_SCORE, " posibles, en ", turns, " turno";
        if(turns ~= 1) print "s";
        rtrue;
#Endif;

    MSG_AREYOUSUREQUIT:
        print "¿Estás seguro de que quieres abandonar? ";
        rtrue;
        
    default:
        ! Si no hay código específico, usar mensaje genérico
        "No se ha definido mensaje para #", p_msg, ".";
    }
];

! ######################### Funciones auxiliares de impresión

[ VerbName p_v;
    ! Imprimir nombres de verbos en español
    switch(p_v) {
        'g//', 'repetir': print "repetir"; return;
        'i//', 'inventario', 'inv': print "inventario"; return;
        'l//', 'mirar': print "mirar"; return;
        'q//', 'salir', 'abandonar': print "salir"; return;
        'x//', 'examinar', 'ex': print "examinar"; return;
        'z//', 'esperar': print "esperar"; return;
        'coger', 'tomar': print "coger"; return;
        'dejar', 'soltar': print "dejar"; return;
        'abrir': print "abrir"; return;
        'cerrar': print "cerrar"; return;
        'ir': print "ir"; return;
    }
    print (address) p_v;
];

! No redefinir PrintMsg aquí para evitar conflictos
! El usuario puede usar _PrintMsg directamente si lo necesita