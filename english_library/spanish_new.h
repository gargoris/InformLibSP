! ==============================================================================
!   SPANISH:  Language Definition File - Versión Completa y Limpia
!
!   Supplied for use with Inform 6 -- Release 6.12.7dev -- Serial number 240409
!
!   Copyright Graham Nelson 1993-2004 and David Griffith 2012-2024
!   Spanish translation 2024
!
!   This code is licensed under either the traditional Inform license as
!   described by the DM4 or the Artistic License version 2.0.
! ==============================================================================

System_file;

#Ifndef LIBRARY_SPANISH;

! ------------------------------------------------------------------------------
!   Part I.   Preliminaries
! ------------------------------------------------------------------------------

Constant SpanishNaturalLanguage;

Class   CompassDirection
  with  number 0, article "el",
        description [;
            if (location provides compass_look && location.compass_look(self)) rtrue;
            if (self.compass_look()) rtrue;
            L__M(##Look, 7, self);
        ],
        compass_look false,
        parse_name [; return -1; ]
  has   scenery;

Object Compass "brújula" has concealed;

#Ifndef WITHOUT_DIRECTIONS;
CompassDirection -> n_obj  with short_name "norte",     door_dir n_to,
                                name 'n//' 'norte';
CompassDirection -> s_obj  with short_name "sur",      door_dir s_to,
                                name 's//' 'sur';
CompassDirection -> e_obj  with short_name "este",     door_dir e_to,
                                name 'e//' 'este';
CompassDirection -> w_obj  with short_name "oeste",    door_dir w_to,
                                name 'o//' 'oeste';
CompassDirection -> ne_obj with short_name "noreste",  door_dir ne_to,
                                name 'ne'  'noreste';
CompassDirection -> nw_obj with short_name "noroeste", door_dir nw_to,
                                name 'no'  'noroeste';
CompassDirection -> se_obj with short_name "sureste",  door_dir se_to,
                                name 'se'  'sureste';
CompassDirection -> sw_obj with short_name "suroeste", door_dir sw_to,
                                name 'so'  'suroeste';
CompassDirection -> u_obj  with short_name "arriba",   door_dir u_to,
                                name 'arr' 'arriba' 'subir' 'cielo' 'techo';
CompassDirection -> d_obj  with short_name "abajo",    door_dir d_to,
                                name 'ab' 'abajo' 'bajar' 'suelo' 'piso';
#Endif; ! WITHOUT_DIRECTIONS

CompassDirection -> in_obj  with short_name "dentro",  door_dir in_to,
                                 name 'dentro' 'adentro';
CompassDirection -> out_obj with short_name "fuera",   door_dir out_to,
                                 name 'fuera' 'afuera';

! ------------------------------------------------------------------------------
!   Part II.   Vocabulary
! ------------------------------------------------------------------------------

Constant AGAIN1__WD     = 'otra';
Constant AGAIN2__WD     = 'vez';
Constant AGAIN3__WD     = 'repetir';
Constant OOPS1__WD      = 'ups';
Constant OOPS2__WD      = 'uy';
Constant OOPS3__WD      = 'corregir';
Constant UNDO1__WD      = 'deshacer';
Constant UNDO2__WD      = 'undo';
Constant UNDO3__WD      = 'deshacer';

Constant ALL1__WD       = 'todo';
Constant ALL2__WD       = 'todos';
Constant ALL3__WD       = 'todas';
Constant ALL4__WD       = 'cada';
Constant ALL5__WD       = 'ambos';
Constant AND1__WD       = 'y';
Constant AND2__WD       = 'e';
Constant AND3__WD       = 'y';
Constant BUT1__WD       = 'pero';
Constant BUT2__WD       = 'excepto';
Constant BUT3__WD       = 'salvo';
Constant ME1__WD        = 'me';
Constant ME2__WD        = 'mi';
Constant ME3__WD        = 'conmigo';
Constant OF1__WD        = 'de';
Constant OF2__WD        = 'del';
Constant OF3__WD        = 'de';
Constant OF4__WD        = 'de';
Constant OTHER1__WD     = 'otro';
Constant OTHER2__WD     = 'otra';
Constant OTHER3__WD     = 'otros';
Constant THEN1__WD      = 'entonces';
Constant THEN2__WD      = 'luego';
Constant THEN3__WD      = 'después';

Constant NO1__WD        = 'no';
Constant NO2__WD        = 'no';
Constant NO3__WD        = 'no';
Constant YES1__WD       = 'sí';
Constant YES2__WD       = 'si';
Constant YES3__WD       = 'vale';

Constant INTERESTING__WD = 'interesante';
Constant AMUSING__WD     = 'divertido';
Constant FULLSCORE1__WD  = 'puntuación';
Constant FULLSCORE2__WD  = 'completa';
Constant QUIT1__WD       = 'salir';
Constant QUIT2__WD       = 'abandonar';
Constant RESTART__WD     = 'reiniciar';
Constant RESTORE__WD     = 'cargar';

! Additional constants required by parser
Constant LanguageContractionForms = 2;
Constant DARKNESS__TX = "oscuridad";
Constant YOURSELF__TX = "ti mismo";
Constant THE__TX = "el";
Constant COMMA__TX = ", ";
Constant AND__TX = " y ";
Constant OR__TX = " o ";
Constant NOTHING__TX = "nada";
Constant THOSET__TX = "esos";
Constant THAT__TX = "eso";
Constant MYSELF__TX = "yo mismo";
Constant TIME__TX = "tiempo";
Constant SCORE__TX = "puntuación";
Constant MOVES__TX = "movimientos";
Constant COLON__TX = ": ";
Constant CANTGO__TX = "No puedes ir por ahí.";
Constant FORMER__TX = "tu anterior";
Constant MYFORMER__TX = "mi anterior";
Constant RELEASE__TX = "Versión";
Constant SERNUM__TX = "/ Número de serie";
Constant INFORMV__TX = "/ Inform v";
Constant LIBRARYV__TX = " Librería v";
Constant STDTERP__TX = "Intérprete estándar";
Constant TERP__TX = "Intérprete";
Constant VER__TX = " versión ";
Constant LIBSER__TX = " S";
Constant LIBERROR__TX = "Error de la librería";
Constant IS__TX = " es";
Constant WAS__TX = " era";
Constant ARE__TX = " son";
Constant WERE__TX = " eran";
Constant IS2__TX = "es ";
Constant WAS2__TX = "era ";
Constant ARE2__TX = "son ";
Constant WERE2__TX = "eran ";
Constant WHOM__TX = "quién";
Constant WHICH__TX = "cuál";
Constant NKEY__TX = " N = siguiente tema";
Constant PKEY__TX = " P = tema anterior";
Constant QKEY1__TX = " Q = volver al juego";
Constant QKEY2__TX = " Q = menú anterior";
Constant RKEY__TX = " ENTER = leer tema";
Constant NKEY1__KY = 'N';
Constant NKEY2__KY = 'n';
Constant PKEY1__KY = 'P';
Constant PKEY2__KY = 'p';
Constant QKEY1__KY = 'Q';
Constant QKEY2__KY = 'q';
Constant STAND__TX = "pararte";
Constant SIT__TX = "sentarte";
Constant LIE__TX = "acostarte";

Array LanguagePronouns table

   ! word       possible GNAs                   connected
   !            to follow:                      to:
   !   a           a           i
   !   s     p     s     p     s    p
   !   mfnmfnmfnmfnmfnmfnmfnmfnmfnmfn

     'él'     $$100000100000                    NULL
     'ella'   $$010000010000                    NULL
     'eso'    $$001000001000                    NULL
     'ellos'  $$000100000100                    NULL
     'ellas'  $$000010000010                    NULL
     'esos'   $$000001000001                    NULL;

Array LanguageDescriptors table

     ! word       possible GNAs   descriptor type
     !            to follow:      

     'mi'       $$111111111111    POSSESS_PK
     'tu'       $$111111111111    POSSESS_PK
     'su'       $$111111111111    POSSESS_PK
     'el'       $$100000100000    DEFART_PK
     'la'       $$010000010000    DEFART_PK
     'los'      $$000100000100    DEFART_PK
     'las'      $$000010000010    DEFART_PK
     'un'       $$100000100000    INDEFART_PK
     'una'      $$010000010000    INDEFART_PK
     'unos'     $$000100000100    INDEFART_PK
     'unas'     $$000010000010    INDEFART_PK;

Array LanguageNumbers table
    'uno' 1 'dos' 2 'tres' 3 'cuatro' 4 'cinco' 5
    'seis' 6 'siete' 7 'ocho' 8 'nueve' 9 'diez' 10
    'once' 11 'doce' 12 'trece' 13 'catorce' 14 'quince' 15
    'dieciséis' 16 'diecisiete' 17 'dieciocho' 18 'diecinueve' 19 'veinte' 20;

Array LanguageArticles table

   !   Contraction form 0:     Contraction form 1:
   !   Cdef   Def    Indef     Cdef   Def    Indef
   !   masc   fem    neut      masc   fem    neut

       "el"   "la"   "un"      "al"   "la"   "un"
       "del"  "de la" "de un"  "del"  "de la" "de un";

! ------------------------------------------------------------------------------
!   Part III.   Translation
! ------------------------------------------------------------------------------

[ LanguageToInformese; ];

[ LanguageIsVerb buffer parse i;
    i = i; buffer = buffer; parse = parse;  ! Silence warnings
    return 0;
];

[ LanguageDoVerb; return 0; ];

Constant LanguageAnimateGender   = male;
Constant LanguageInanimateGender = male;

[ LanguageContraction text;
    if (text->0 == 'a' && text->1 == ' ' && text->2 == 'e' && text->3 == 'l') print "al";
    else if (text->0 == 'd' && text->1 == 'e' && text->2 == ' ' && text->3 == 'e' && text->4 == 'l') print "del";
    else print (string) text;
];

[ LanguageDirection d;
    switch (d) {
        n_to: print "norte";
        s_to: print "sur";
        e_to: print "este";
        w_to: print "oeste";
        ne_to: print "noreste";
        nw_to: print "noroeste";
        se_to: print "sureste";
        sw_to: print "suroeste";
        u_to: print "arriba";
        d_to: print "abajo";
        in_to: print "dentro";
        out_to: print "fuera";
        default: return RunTimeError(9, d);
    }
];

[ LanguageNumber n f;
    if (n == 0) { print "cero"; rfalse; }
    if (n < 0) { print "menos "; n = -n; }
    if (n >= 1000) { print (LanguageNumber) n/1000, " mil"; n = n%1000; f = 1; }
    if (n >= 100) {
        if (f == 1) print " ";
        if (n >= 200) print (LanguageNumber) n/100, "cientos";
        else print "cien";
        n = n%100; f = 1;
    }
    if (n >= 20) {
        if (f == 1) print " ";
        switch (n/10) {
            2: print "veinte";
            3: print "treinta";
            4: print "cuarenta";
            5: print "cincuenta";
            6: print "sesenta";
            7: print "setenta";
            8: print "ochenta";
            9: print "noventa";
        }
        if (n%10 ~= 0) print " y ", (LanguageNumber) n%10;
        rfalse;
    }
    switch (n) {
        10: print "diez";
        11: print "once";
        12: print "doce";
        13: print "trece";
        14: print "catorce";
        15: print "quince";
        16: print "dieciséis";
        17: print "diecisiete";
        18: print "dieciocho";
        19: print "diecinueve";
        1: print "uno";
        2: print "dos";
        3: print "tres";
        4: print "cuatro";
        5: print "cinco";
        6: print "seis";
        7: print "siete";
        8: print "ocho";
        9: print "nueve";
    }
];

[ LanguageTimeOfDay hours mins i;
    i = hours%12;
    if (i == 0) i = 12;
    if (i < 10) print " ";
    print i, ":";
    if (mins < 10) print "0";
    print mins;
    if ((hours >= 12) && (hours ~= 24)) print " pm";
    else print " am";
];

[ LanguageVerb i;
    i = i; ! Silence warning
    return 0;
];

[ LanguageVerbIsDebugging verb;
    if (verb == 'punonoff' or 'pronombres' or 'objetos' or 'lugares' or 'verbos' or 'acciones' or 'debug' or 'cmd' or 'rastrear') rtrue;
    rfalse;
];

[ LanguageVerbLikesAdverb verb;
    verb = verb; ! Silence warning
    return 0;
];

[ LanguageVerbMayBeName verb;
    verb = verb; ! Silence warning
    return 0;
];

[ LanguageInitialise; ];

[ LanguagePrintShortName obj;
    obj = obj; ! Silence warning
    return 0;
];

! Simple auxiliary functions without complex logic
[ ThatOrThose obj;
    if (obj has pluralname) print "esos"; else print "eso";
];

[ ItOrThem obj;
    if (obj has pluralname) print "los"; else "lo";
];

[ IsOrAre obj;
    if (obj has pluralname) print "son"; else print "es";
];

[ CDefart obj;
    if (obj has female) {
        if (obj has pluralname) print "las"; else print "la";
    } else {
        if (obj has pluralname) print "los"; else print "el";
    }
];

[ SupportObj obj prep1 prep2;
    obj = obj; prep2 = prep2; ! Silence warnings
    print (string) prep1;
];

[ Tense str1 str2;
    if (player provides narrative_tense && player.narrative_tense == PAST_TENSE)
        print (string) str2;
    else
        print (string) str1;
];

[ DecideAgainst;
    CSubjectCan(actor,true); print " hacer eso.";
];

[ CSubjectCan actor flag;
    actor = actor; flag = flag; ! Silence warnings
    print "Puedes";
];

[ CSubjectCant actor flag;
    actor = actor; flag = flag; ! Silence warnings
    print "No puedes";
];

[ CSubjectIs actor flag;
    actor = actor; flag = flag; ! Silence warnings
    print "Estás";
];

[ CSubjectIsnt actor flag;
    actor = actor; flag = flag; ! Silence warnings
    print "No estás";
];

[ CSubjectWill actor flag;
    actor = actor; flag = flag; ! Silence warnings
    print "Tendrás que";
];

[ CSubjectVerb actor flag1 flag2 str1 str2 str3 str4;
    actor = actor; flag1 = flag1; flag2 = flag2; str2 = str2; str3 = str3; str4 = str4; ! Silence warnings
    print (string) str1;
];

[ CSubjectVoice actor str1 str2 str3 str4;
    actor = actor; str2 = str2; str3 = str3; str4 = str4; ! Silence warnings
    print (string) str1;
];

[ CSubjectDont actor flag;
    actor = actor; flag = flag; ! Silence warnings
    print "No";
];

[ theActor actor;
    actor = actor; ! Silence warning
    print "tú";
];

[ OnesSelf actor;
    actor = actor; ! Silence warning
    print "a ti mismo";
];

[ PossessiveCaps actor;
    actor = actor; ! Silence warning
    print "Tu";
];

! ------------------------------------------------------------------------------
!   Part IV.   Printing
! ------------------------------------------------------------------------------

[ LanguageLM n x1 x2;
    Answer, Ask: "No hay respuesta.";
    Attack: "La violencia no es la respuesta a esto.";
    Blow: "No puedes soplar eso.";
    Burn: "Esta idea peligrosa no llevaría a nada.";
    Buy: "No hay nada en venta.";
    Climb: "No creo que puedas trepar por eso.";
    Close: switch (n) {
        1: "No es algo que puedas cerrar.";
        2: "Ya está cerrado.";
        3: "Cierras ", (the) x1, ".";
        4: "(primero cerrando ", (the) x1, ")";
    }
    CommandsOff: switch (n) {
        1: "La grabación de órdenes ya está desactivada.";
        #Ifdef TARGET_GLULX;
        2: "La grabación de órdenes se ha desactivado.";
        #Ifnot;
        2: "[La grabación de órdenes no está disponible.]";
        #Endif;
    }
    CommandsOn: switch (n) {
        1: "La grabación de órdenes ya está activada.";
        #Ifdef TARGET_GLULX;
        2: "La grabación de órdenes se ha activado.";
        #Ifnot;
        2: "[La grabación de órdenes no está disponible.]";
        #Endif;
    }
    CommandsRead: switch (n) {
        1: "La grabación de órdenes ya está activada.";
        #Ifdef TARGET_GLULX;
        2: "La grabación de órdenes se ha activado.";
        3: "La grabación de órdenes ha terminado.";
        #Ifnot;
        2: "[La grabación de órdenes no está disponible.]";
        #Endif;
    }
    Consult: "No descubres nada interesante en ", (the) x1, ".";
    Cut: "Cortar eso no serviría de nada.";
    Dig: "Excavar no llevaría a nada aquí.";
    Disrobe: switch (n) {
        1: "No llevas puesto eso.";
        2: "Te quitas ", (the) x1, ".";
    }
    Drink: "No hay nada adecuado para beber aquí.";
    Drop: switch (n) {
        1: "No llevas eso.";
        2: "No puedes soltarte a ti mismo.";
        3: "(primero te lo quitas)";
        4: "Soltado.";
    }
    Eat: switch (n) {
        1: "Es claramente incomestible.";
        2: "Te comes ", (the) x1, ". No está mal.";
    }
    Empty: switch (n) {
        1: "No puede contener cosas.";
        2: "Está cerrado.";
        3: "Ya está vacío.";
        4: "Eso no vaciaría nada.";
    }
    Enter: switch (n) {
        1: "Pero ya estás en ", (the) x1, ".";
        2: "No es algo donde puedas entrar.";
        3: "No puedes entrar en algo cerrado.";
        4: "Solo puedes entrar en algo que esté libre.";
        5: "Entras en ", (the) x1, ".";
        6: "(te bajas de ", (the) x1, ")";
        7: "(entras en ", (the) x1, ")";
    }
    Examine: switch (n) {
        1: "Oscuridad, sustantivo. Una ausencia de luz.";
        2: "No ves nada especial sobre ", (the) x1, ".";
        3: if (x1 has on) "Está encendido."; else "Está apagado.";
    }
    Exit: switch (n) {
        1: "Pero no estás en nada en este momento.";
        2: "No puedes salir de algo cerrado.";
        3: "Sales de ", (the) x1, ".";
        4: "Pero no estás en ", (the) x1, ".";
        5: "(primero te bajas de ", (the) x1, ")";
        6: "Te pones de pie.";
    }
    Fill: switch (n) {
        1: "No hay nada obvio con lo que llenar ", (the) x1, ".";
        2: "Llenar ", (the) x1, " desde ", (the) x2, " no tendría sentido.";
    }
    FullScore: switch (n) {
        1: if (deadflag) print "La puntuación era ";
           else print "La puntuación es ";
           "compuesta de la siguiente manera:^";
        2: "encontrar diversos objetos";
        3: "visitar varios lugares";
        4: print "total (de ", MAX_SCORE; ")";
    }
    GetOff: "Pero no estás encima de ", (the) x1, " en este momento.";
    Give: switch (n) {
        1: "No estás sosteniendo ", (the) x1, ".";
        2: "Juegas con ", (the) x1, " por un momento, pero no logras mucho.";
        3: "No parece interesado.";
        4: "Le das ", (the) x1, ".";
    }
    Go: switch (n) {
        1: "Tendrás que bajarte de ", (the) x1, " primero.";
        2: "No puedes ir por ahí.";
        3: "No puedes trepar por ", (the) x1, ".";
        4: "No puedes bajar por ", (the) x1, ".";
        5: "No puedes, ya que ", (the) x1, " está en el camino.";
        6: "No puedes, ya que ", (the) x1, " no lleva a ninguna parte.";
        7: "Te marchas.";
    }
    Insert: switch (n) {
        1: "Necesitas estar sosteniendo ", (the) x1, " antes de poder ponerlo en otra cosa.";
        2: "No puede contener cosas.";
        3: "Está cerrado.";
        4: "Tendrás que quitártelo primero.";
        5: "No puedes poner algo dentro de sí mismo.";
        6: "(primero te lo quitas)";
        7: "No hay más espacio en ", (the) x1, ".";
        8: "Hecho.";
        9: "Pones ", (the) x1, " en ", (the) x2, ".";
    }
    Inv: switch (n) {
        1: "No llevas nada.";
        2: "Llevas";
        3: ":";
        4: ".";
    }
    Jump: "Saltas en el sitio, inútilmente.";
    JumpIn: switch (n) {
        1: "Saltar en ", (the) x1, " no conseguiría nada aquí.";
        2: "No puedes saltar en eso.";
    }
    JumpOn: switch (n) {
        1: "Saltar sobre ", (the) x1, " no conseguiría nada aquí.";
        2: "No puedes saltar sobre eso.";
    }
    JumpOver: switch (n) {
        1: "Saltar sobre ", (the) x1, " no conseguiría nada aquí.";
        2: "No puedes saltar sobre eso.";
    }
    Kiss: "Mantén tu mente en el juego.";
    Listen: "No oyes nada inesperado.";
    ListMiscellany: switch (n) {
        1: print " (dando luz)";
        2: print " (que está cerrado)";
        3: print " (cerrado y dando luz)";
        4: print " (que está vacío)";
        5: print " (vacío y dando luz)";
        6: print " (que está cerrado y vacío)";
        7: print " (cerrado, vacío y dando luz)";
        8: print " (dando luz y puesto";
        9: print " (dando luz";
        10: print " (puesto";
        11: print " (que está ";
        12: print "abierto";
        13: print "abierto pero vacío";
        14: print "cerrado";
        15: print "cerrado y bloqueado";
        16: print " y vacío";
        17: print " (que está vacío)";
        18: print " que contiene ";
        19: print " (sobre ";
        20: print ", sobre ";
        21: print " (en ";
        22: print ", dentro de ";
    }
    LMode1: print (string) Story, " está ahora en su modo ~breve~, que da descripciones largas de lugares nunca antes visitados y descripciones cortas en otro caso.";
    LMode2: print (string) Story, " está ahora en su modo ~verboso~, que siempre da descripciones largas de lugares (incluso si ya has estado ahí antes).";
    LMode3: print (string) Story, " está ahora en su modo ~superbreve~, que siempre da descripciones cortas de lugares (incluso si no has estado ahí antes).";
    Lock: switch (n) {
        1: "No es algo que puedas cerrar con llave.";
        2: "Ya está cerrado con llave.";
        3: "Primero tendrás que cerrar ", (the) x1, ".";
        4: "No parece encajar en la cerradura.";
        5: "Cierras ", (the) x1, " con llave.";
    }
    Look: switch (n) {
        1: print " (sobre ", (the) x1, ")";
        2: print " (en ", (the) x1, ")";
        3: print " (como ", (object) x1, ")";
        4: print "^Sobre ", (the) x1;
            WriteListFrom(child(x1), ENGLISH_BIT+RECURSE_BIT+PARTINV_BIT+TERSE_BIT+CONCEAL_BIT+ISARE_BIT);
            ".";
        5,6:
            if (x1 ~= location) {
                if (x1 has supporter) print "^Sobre "; else print "^En ";
                print (the) x1, " puedes ";
            }
            else { new_line; print "Puedes "; }
            if (n == 5) print "también ";
            print "ver ";
            WriteListFrom(child(x1), ENGLISH_BIT+RECURSE_BIT+PARTINV_BIT+TERSE_BIT+CONCEAL_BIT+WORKFLAG_BIT);
            if (x1 ~= location) "."; else " aquí.";
        7: "No ves nada inesperado en esa dirección.";
    }
    LookUnder: switch (n) {
        1: "Pero está oscuro.";
        2: "No encuentras nada interesante.";
    }
    Mild: "Cierto.";
    Miscellany: switch (n) {
        1: "(considerando solo los primeros dieciséis objetos)^";
        2: "Nada que hacer.";
        3: print " Has muerto ";
        4: print " Has ganado ";
        5: print "^¿Te gustaría REINICIAR, CARGAR una partida guardada";
            #Ifdef DEATH_MENTION_UNDO;
            if (undo_flag ~= 0) print ", DESHACER tu último movimiento";
            #Endif;
            if (TASKS_PROVIDED == 0) print ", obtener la puntuación COMPLETA de esa partida";
            if (deadflag == 2 && AMUSING_PROVIDED == 0)
                print ", ver algunas sugerencias DIVERTIDAS";
            SerialComma(3); print " o SALIR?";
        6: "[Tu intérprete no proporciona ~deshacer~. ¡Lo siento!]";
            #Ifdef TARGET_ZCODE;
        7: "~Deshacer~ falló. [No todos los intérpretes lo proporcionan.]";
            #Ifnot; ! TARGET_GLULX
        7: "[No puedes ~deshacer~ más.]";
            #Endif; ! TARGET_
        8: "Por favor, da una de las respuestas anteriores.";
        9: "Está completamente oscuro aquí.";
        10: "¿Perdón?";
        11: "[No puedes ~deshacer~ lo que no se ha hecho!]";
        12: "[No puedes ~deshacer~ dos veces seguidas. ¡Lo siento!]";
        13: "[Movimiento anterior deshecho.]";
        14: "Lo siento, eso no se puede corregir.";
        15: "No pienses en ello.";
        16: "~Ups~ solo puede corregir una palabra.";
        17: "Está completamente oscuro, y no puedes ver nada.";
        18: print "ti mismo";
        19: "Así como hermoso como siempre.";
        20: "Para repetir un comando como ~rana, salta~, solo di ~otra vez~, no ~rana, otra vez~.";
        21: "Apenas puedes empezar una frase con una coma.";
        22: "Parece que quieres hablar con alguien, pero no puedo ver con quién.";
        23: "No puedes hablar con ", (the) x1, ".";
        24: "Para hablar con alguien, prueba ~persona, hola~ o algo parecido.";
        25: "No entiendo esa frase.";
        26: print "Solo entiendo unos ", MAX_UNDERSTOOD_LENGTH, " caracteres de esa frase.";
        27: "No entiendo esa frase.";
        28: "No conozco la palabra ~", (address) x1, "~.";
        29: "No conozco la palabra ~", (address) x1, "~.";
        30: "Parece que has dicho muy poco.";
        31: "No he entendido esa frase.";
        32: "No necesitas usar la palabra ~", (address) x1, "~ en este juego.";
        33: "No puedes usar múltiples objetos con ese verbo.";
        34: "Solo puedes usar múltiples objetos una vez en una línea.";
        35: "No estoy seguro de a qué te refieres con ~", (address) x1, "~.";
        36: "Has excluido algo, pero no estoy seguro de qué.";
        37: "Solo puedes hacer eso con algo animado.";
        38: "No puedes ver ~", (address) x1, "~ aquí.";
        39: "No puedes referirte a un objeto dos veces.";
        40: "No puedes ver ~", (address) x1, "~ aquí.";
        41: "No está claro qué pronombre se refiere a ~", (address) x1, "~.";
        42: "Excluiste algo que no estaba incluido de todos modos.";
        43: "Solo puedes hacer eso con algo que estés sosteniendo.";
        44: "No puedes hacer eso.";
        45: "No hay nada disponible para ese verbo.";
        46: "Ese verbo no puede tener un objeto indirecto.";
        47: "Solo puedes hacer eso con algo animado.";
        48: "No puedes ver ~", (address) x1, "~ aquí.";
        49: "Ese verbo no puede tener un objeto indirecto.";
        50: "Tu puntuación acaba de ";
        51: "bajar";
        52: "permanecer igual";
        53: "subir";
        54: print " por ", (number) x1, " punto";
        55: print " por ", (number) x1, " puntos";
        56: ".";
        57: "  ";
    }
    No, Yes: "Esa era una pregunta retórica.";
    NotifyOff: "Notificación de puntuación desactivada.";
    NotifyOn: "Notificación de puntuación activada.";
    Objects: switch (n) {
        1: "Objetos que has manejado:^";
        2: "Ninguno.";
        3: print "   (puesto)";
        4: print "   (sostenido)";
        5: print "   (dado)";
        6: print "   (en ", (name) x1, ")";
        7: print "   (en ", (the) x1, ")";
        8: print "   (dentro de ", (the) x1, ")";
        9: print "   (sobre ", (the) x1, ")";
        10: print "   (perdido)";
    }
    Open: switch (n) {
        1: "No es algo que puedas abrir.";
        2: "Parece estar cerrado con llave.";
        3: "Ya está abierto.";
        4: "Abres ", (the) x1, ", revelando ";
            WriteListFrom(child(x1), ENGLISH_BIT+TERSE_BIT+CONCEAL_BIT);
            ".";
        5: "Abres ", (the) x1, ".";
    }
    Order: "No puedes hacer eso.";
    Places: switch (n) {
        1: "Has visitado: ";
        2: ".";
    }
    Pray: "Nada práctico resulta de tu rezo.";
    Pronouns: switch (n) {
        1: "En este momento, ";
        2: "significa ";
        3: "está indefinido";
        4: "no hay pronombres conocidos por el juego.";
        5: ".";
    }
    Pull, Push, Turn: switch (n) {
        1: "Está fijado en su lugar.";
        2: "No puedes.";
        3: "No pasa nada.";
        4: "Eso no serviría de nada.";
    }
    PushDir: switch (n) {
        1: "No es obvio cómo el verbo ~", (address) x1, "~ se aplica a ~", (the) x2, "~.";
        2: "No es una dirección.";
        3: "No puedes empujar ", (the) x1, " en esa dirección.";
    }
    PutOn: switch (n) {
        1: "Necesitas estar sosteniendo ", (the) x1, " antes de poder ponerlo encima de algo más.";
        2: "No puedes poner algo encima de sí mismo.";
        3: "Poner cosas sobre ", (the) x1, " no conseguiría nada.";
        4: "Te falta destreza.";
        5: "(primero te lo quitas)";
        6: "No hay más espacio sobre ", (the) x1, ".";
        7: "Hecho.";
        8: "Pones ", (the) x1, " sobre ", (the) x2, ".";
    }
    Quit: switch (n) {
        1: "Por favor, responde sí o no.";
        2: "¿Estás seguro de que quieres salir? ";
    }
    Remove: switch (n) {
        1: "Desafortunadamente está cerrado.";
        2: "Pero no está ahí ahora.";
        3: "Quitado.";
        4: "Pero no está en o sobre nada.";
    }
    Restart: switch (n) {
        1: "¿Estás seguro de que quieres reiniciar? ";
        2: "Falló.";
    }
    Restore: switch (n) {
        1: "Restaurar falló.";
        2: "Ok.";
    }
    Rub: switch (n) {
        1: "No consigues nada con esto.";
        2: "No puedes hacer eso.";
    }
    Save: switch (n) {
        1: "Guardar falló.";
        2: "Ok.";
    }
    Score: switch (n) {
        1: if (deadflag) print "En ese juego obtuviste "; else print "Hasta ahora has obtenido ";
            print score, " de un posible ", MAX_SCORE, ", en ", turns, " turno";
            if (turns ~= 1) print "s";
            return;
        2: "No hay puntuación en esta historia.";
    }
    ScriptOff: switch (n) {
        1: "La transcripción ya está desactivada.";
        2: "^Fin de la transcripción.";
        3: "El intento de finalizar la transcripción falló.";
    }
    ScriptOn: switch (n) {
        1: "La transcripción ya está activada.";
        2: print "Inicio de una transcripción de"; VersionSub();
        3: "El intento de comenzar la transcripción falló.";
    }
    Search: switch (n) {
        1: "Pero está oscuro.";
        2: "No hay nada sobre ", (the) x1, ".";
        3: print "Sobre ", (the) x1;
            WriteListFrom(child(x1), ENGLISH_BIT+TERSE_BIT+CONCEAL_BIT+ISARE_BIT);
            ".";
        4: "No encuentras nada interesante.";
        5: "No puedes ver dentro, ya que ", (the) x1, " está cerrado.";
        6: "", (The) x1, " está vacío.";
        7: print "En ", (the) x1;
            WriteListFrom(child(x1), ENGLISH_BIT+TERSE_BIT+CONCEAL_BIT+ISARE_BIT);
            ".";
    }
    Set: "No puedes configurar eso.";
    SetTo: "No puedes configurar eso a nada.";
    Show: switch (n) {
        1: "No estás sosteniendo ", (the) x1, ".";
        2: "No está impresionado.";
    }
    Sing: "Tu canto es abominable.";
    Sleep: "No te sientes especialmente somnoliento.";
    Smell: switch (n) {
        1: "No hueles nada inesperado.";
        2: "No puedes hacer eso.";
    }
    Sorry: "Oh, no te disculpes.";
    Squeeze: switch (n) {
        1: "No puedes hacer eso.";
        2: "No consigues nada con esto.";
    }
    Strong: "Los verdaderos aventureros no usan ese lenguaje.";
    Swim: "No hay suficiente agua para nadar.";
    Swing: "No hay nada sensato que balancear aquí.";
    SwitchOff: switch (n) {
        1: "No es algo que puedas apagar.";
        2: "Ya está apagado.";
        3: "Apagas ", (the) x1, ".";
    }
    SwitchOn: switch (n) {
        1: "No es algo que puedas encender.";
        2: "Ya está encendido.";
        3: "Enciendes ", (the) x1, ".";
    }
    Take: switch (n) {
        1: "Tomado.";
        2: "Siempre te tienes a ti mismo.";
        3: "No creo que a ", (the) x1, " le importe eso.";
        4: "Tendrás que bajarte de ", (the) x1, " primero.";
        5: "Ya tienes eso.";
        6: "Parece pertenecer a ", (the) x1, ".";
        7: "Parece ser parte de ", (the) x1, ".";
        8: "No está disponible.";
        9: "No está abierto.";
        10: "Difícilmente es portátil.";
        11: "Está fijado en su lugar.";
        12: "Ya estás llevando demasiadas cosas.";
        13: "(poniendo ", (the) x1, " en ", (the) x2, " para hacer espacio)";
    }
    Taste: switch (n) {
        1: "No saboreas nada inesperado.";
        2: "No puedes hacer eso.";
    }
    Tell: switch (n) {
        1: "Hablas contigo mismo por un momento.";
        2: "Esto no provoca reacción.";
    }
    Think: "Qué buena idea.";
    ThrowAt: switch (n) {
        1: "Fútil.";
        2: "Te faltan agallas cuando llega el momento crucial.";
    }
    Tie: switch (n) {
        1: "No conseguirías nada con esto.";
        2: "No puedes hacer eso.";
    }
    Touch: switch (n) {
        1: "No puedes hacer eso.";
        2: "No sientes nada inesperado.";
        3: "Eso realmente no serviría de nada.";
    }
    Unlock: switch (n) {
        1: "No parece ser algo que puedas desbloquear.";
        2: "Está desbloqueado en este momento.";
        3: "No parece encajar en la cerradura.";
        4: "Desbloqueas ", (the) x1, ".";
        5: "(primero desbloqueando ", (the) x1, ")";
    }
    VagueGo: "Tendrás que decir en qué dirección de la brújula ir.";
    Verify: switch (n) {
        1: "El archivo del juego se ha verificado como intacto.";
        2: "El archivo del juego no se verificó como intacto y puede estar corrupto.";
    }
    Wait: "Pasa el tiempo.";
    Wake: "La terrible verdad es que esto no es un sueño.";
    WakeOther: "Eso parece innecesario.";
    Wave: switch (n) {
        1: "Pero no estás sosteniendo eso.";
        2: "Te ves ridículo agitando ", (the) x1, ".";
        3: "No puedes hacer eso.";
    }
    WaveHands: "Te ves ridículo agitando las manos.";
    Wear: switch (n) {
        1: "No puedes ponerte eso.";
        2: "No estás sosteniendo eso.";
        3: "Ya te lo tienes puesto.";
        4: "Te pones ", (the) x1, ".";
        5: "Necesitas quitarte ", (the) x1, " de ", (the) x2, " antes de ponértelo.";
    }
];

! ==============================================================================

Constant LIBRARY_SPANISH;
#Endif;

! ==============================================================================