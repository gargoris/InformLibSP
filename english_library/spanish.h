! ==============================================================================
!   SPANISH:  Definición de Idioma Español
!
!   Para uso con Inform 6 -- Release 6.12.7dev -- Serial number 240409
!
!   Copyright Graham Nelson 1993-2004 y David Griffith 2012-2024
!   Adaptación española 2024
!
!   Este código está licenciado bajo la licencia tradicional de Inform como
!   se describe en el DM4 o la Licencia Artística versión 2.0.
!
!   Este archivo es incluido automáticamente en tu juego por "parserm".
!   Estrictamente, "parserm" incluye el archivo nombrado en la variable "language__",
!   cuyo contenido puede ser definido por +language_name=XXX en el compilador (con
!   un default de "english").
!
!   Define la constante DIALECT_ES antes de incluir "Parser" para obtener
!   español de España.
! ==============================================================================

System_file;

#Ifndef LIBRARY_SPANISH;	! si este archivo ya está incluido,
				! no tratar de incluirlo otra vez.

! ------------------------------------------------------------------------------
!   Parte I.   Preliminares
! ------------------------------------------------------------------------------

Constant SpanishNaturalLanguage;    ! Necesario para mantener mecanismo de pronombres

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

Object Compass "br@{FA}jula" has concealed;

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

CompassDirection -> in_obj  with short_name "adentro", door_dir in_to,
                                 name 'adentro' 'dentro';
CompassDirection -> out_obj with short_name "afuera",  door_dir out_to,
                                 name 'afuera' 'fuera';

! ------------------------------------------------------------------------------
!   Parte II.   Vocabulario
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
Constant ME2__WD        = 'm@{ED}';
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
Constant THEN3__WD      = 'despu@{E9}s';

Constant NO1__WD        = 'n//';
Constant NO2__WD        = 'no';
Constant NO3__WD        = 'no';
Constant YES1__WD       = 's//';
Constant YES2__WD       = 's@{ED}';
Constant YES3__WD       = 's@{ED}';

Constant AMUSING__WD    = 'divertido';
Constant FULLSCORE1__WD = 'puntuaci@{F3}n';
Constant FULLSCORE2__WD = 'completa';
Constant QUIT1__WD      = 'q//';
Constant QUIT2__WD      = 'salir';
Constant RESTART__WD    = 'reiniciar';
Constant RESTORE__WD    = 'cargar';

Array LanguagePronouns table

  ! palabra     GNAs posibles                    conectado
  !             para seguir:                     a:
  !             a     i
  !             s  p  s  p
  !             mfnmfnmfnmfn

    'lo'      $$100000100000                    NULL      ! masculino singular
    'la'      $$010000010000                    NULL      ! femenino singular
    'los'     $$100000010000                    NULL      ! masculino plural
    'las'     $$010000001000                    NULL      ! femenino plural
    '@{E9}l'  $$100000100000                    NULL      ! él
    'ella'    $$010000010000                    NULL      ! ella
    'ellos'   $$100000010000                    NULL      ! ellos
    'ellas'   $$010000001000                    NULL      ! ellas
    'ello'    $$001000111000                    NULL      ! neutro (poco común)
    'le'      $$111000111000                    NULL      ! dativo
    'les'     $$000111000111                    NULL;     ! dativo plural

Array LanguageDescriptors table

  ! palabra     GNAs posibles   descriptor      conectado
  !             para seguir:    tipo:           a:
  !             a     i
  !             s  p  s  p
  !             mfnmfnmfnmfn

    'mi'      $$111111111111    POSSESS_PK      0         ! mi/mis
    'mis'     $$000111000111    POSSESS_PK      0
    'tu'      $$111111111111    POSSESS_PK      0         ! tu/tus
    'tus'     $$000111000111    POSSESS_PK      0
    'su'      $$111111111111    POSSESS_PK      0         ! su/sus
    'sus'     $$000111000111    POSSESS_PK      0
    'este'    $$100000100000    POSSESS_PK      0         ! este
    'esta'    $$010000100000    POSSESS_PK      0         ! esta
    'estos'   $$100000010000    POSSESS_PK      0         ! estos
    'estas'   $$010000010000    POSSESS_PK      0         ! estas
    'ese'     $$100000100000    POSSESS_PK      1         ! ese
    'esa'     $$010000100000    POSSESS_PK      1         ! esa
    'esos'    $$100000010000    POSSESS_PK      1         ! esos
    'esas'    $$010000010000    POSSESS_PK      1         ! esas
    'aquel'   $$100000100000    POSSESS_PK      2         ! aquel
    'aquella' $$010000100000    POSSESS_PK      2         ! aquella
    'aquellos' $$100000010000   POSSESS_PK      2         ! aquellos
    'aquellas' $$010000010000   POSSESS_PK      2         ! aquellas
    'el'      $$100000100000    DEFART_PK       NULL      ! el (masc sing)
    'la'      $$010000100000    DEFART_PK       NULL      ! la (fem sing)
    'los'     $$100000010000    DEFART_PK       NULL      ! los (masc plur)
    'las'     $$010000010000    DEFART_PK       NULL      ! las (fem plur)
    'un'      $$100000100000    INDEFART_PK     NULL      ! un (masc sing)
    'una'     $$010000100000    INDEFART_PK     NULL      ! una (fem sing)
    'unos'    $$100000010000    INDEFART_PK     NULL      ! unos (masc plur)
    'unas'    $$010000010000    INDEFART_PK     NULL      ! unas (fem plur)
    'algunos' $$100000010000    INDEFART_PK     NULL      ! algunos
    'algunas' $$010000010000    INDEFART_PK     NULL      ! algunas
    'encendido' $$111111111111  light           NULL      ! encendido/a
    'encendida' $$010000010000  light           NULL      ! encendida
    'iluminado' $$111111111111  light           NULL      ! iluminado/a
    'apagado'   $$111111111111  (-light)        NULL      ! apagado/a
    'apagada'   $$010000010000  (-light)        NULL;     ! apagada

Array LanguageNumbers table
    'cero' 0 'uno' 1 'dos' 2 'tres' 3 'cuatro' 4 'cinco' 5
    'seis' 6 'siete' 7 'ocho' 8 'nueve' 9 'diez' 10
    'once' 11 'doce' 12 'trece' 13 'catorce' 14 'quince' 15
    'diecis@{E9}is' 16 'diecisiete' 17 'dieciocho' 18 'diecinueve' 19 'veinte' 20
    'veintiuno' 21 'veintid@{F3}s' 22 'veintitr@{E9}s' 23 'veinticuatro' 24 'veinticinco' 25
    'treinta' 30 'cuarenta' 40 'cincuenta' 50 'sesenta' 60 'setenta' 70 
    'ochenta' 80 'noventa' 90 'cien' 100 'mil' 1000;

! ------------------------------------------------------------------------------
!   Parte III.   Traducción
! ------------------------------------------------------------------------------

[ LanguageToInformese buffer length pos;
    ! Procesar contracciones del español: del -> de el, al -> a el
    for (pos = 0: pos < length - 2: pos++) {
        ! Detectar "del" 
        if (buffer->pos == 'd' && buffer->(pos+1) == 'e' && buffer->(pos+2) == 'l' && 
            (pos + 3 >= length || buffer->(pos+3) == ' ')) {
            ! Reemplazar "del" por "de el"
            buffer->pos = 'd'; buffer->(pos+1) = 'e'; buffer->(pos+2) = ' ';
            ! Mover el resto hacia adelante para hacer espacio
            pos = pos + 3;
        }
        ! Detectar "al"
        if (buffer->pos == 'a' && buffer->(pos+1) == 'l' && 
            (pos + 2 >= length || buffer->(pos+2) == ' ')) {
            ! Reemplazar "al" por "a el"
            buffer->pos = 'a'; buffer->(pos+1) = ' '; buffer->(pos+2) = 'e';
            ! Mover el resto hacia adelante
            pos = pos + 3;
        }
    }
];

! ------------------------------------------------------------------------------
!   Parte IV.   Impresión
! ------------------------------------------------------------------------------

Constant LanguageAnimateGender   = male;     ! Por defecto, animados son masculinos
Constant LanguageInanimateGender = male;     ! Por defecto, inanimados son masculinos

Constant LanguageContractionForms = 4;      ! Español tiene cuatro:
                                            ! 0 = masculino singular (el)
                                            ! 1 = femenino singular (la)
                                            ! 2 = masculino plural (los)
                                            ! 3 = femenino plural (las)

[ LanguageContraction obj;
    ! Determinar el género y número del objeto para seleccionar el artículo correcto
    if (obj has female) {
        if (obj has pluralname) return 3;  ! las
        else return 1;                     ! la
    } else {
        if (obj has pluralname) return 2;  ! los
        else return 0;                     ! el
    }
];

Array LanguageArticles -->

 ! Forma 0 (el):      Forma 1 (la):      Forma 2 (los):     Forma 3 (las):
 ! Cdef  Def   Indef   Cdef  Def   Indef  Cdef  Def   Indef  Cdef  Def   Indef

   "El " "el " "un "   "La " "la " "una " "Los " "los " "unos " "Las " "las " "unas ";

                   !             a           i
                   !             s     p     s     p
                   !             m f n m f n m f n m f n

Array LanguageGNAsToArticles --> 0 1 0 2 3 2 0 1 0 2 3 2;

[ LanguageDirection d;
    switch (d) {
      n_to:    print "norte";
      s_to:    print "sur";
      e_to:    print "este";
      w_to:    print "oeste";
      ne_to:   print "noreste";
      nw_to:   print "noroeste";
      se_to:   print "sureste";
      sw_to:   print "suroeste";
      u_to:    print "arriba";
      d_to:    print "abajo";
      in_to:   print "adentro";
      out_to:  print "afuera";
      default: return RunTimeError(9,d);
    }
];

[ LanguageNumber n f;
    if (n == 0)    { print "cero"; rfalse; }
    if (n < 0)     { print "menos "; n = -n; }
    if (n >= 1000) { 
        print (LanguageNumber) n/1000, " mil"; 
        n = n%1000; 
        f = 1; 
        if (n == 0) rfalse;
        print " ";
    }
    if (n >= 100)  {
        if (f == 1) print " ";
        if (n >= 200) print (LanguageNumber) n/100, "cientos";
        else if (n >= 100) print "cien";
        n = n%100; 
        f = 1;
        if (n == 0) rfalse;
        print " ";
    }
    if (f == 1 && n > 0) print "y ";
    switch (n) {
      1:    print "uno";
      2:    print "dos";
      3:    print "tres";
      4:    print "cuatro";
      5:    print "cinco";
      6:    print "seis";
      7:    print "siete";
      8:    print "ocho";
      9:    print "nueve";
      10:   print "diez";
      11:   print "once";
      12:   print "doce";
      13:   print "trece";
      14:   print "catorce";
      15:   print "quince";
      16:   print "diecis@{E9}is";
      17:   print "diecisiete";
      18:   print "dieciocho";
      19:   print "diecinueve";
      20:   print "veinte";
      21 to 29: print "veinti"; LanguageNumber(n-20); 
      30 to 99: switch (n/10) {
        3:  print "treinta";
        4:  print "cuarenta";
        5:  print "cincuenta";
        6:  print "sesenta";
        7:  print "setenta";
        8:  print "ochenta";
        9:  print "noventa";
        }
        if (n%10 ~= 0) { print " y "; LanguageNumber(n%10); }
    }
];

[ LanguageTimeOfDay hours mins i;
    i = hours;
    if (i == 0) i = 12;
    if (i < 10) print " ";
    print i, ":", mins/10, mins%10;
    if (hours < 12) print " a.m."; else print " p.m.";
];

[ LanguageVerb i;
    switch (i) {
      'i//','inv','inventario':
               print "ver inventario";
      'l//','m//':   print "mirar";
      'x//','ex//':   print "examinar";
      'z//':   print "esperar";
! CompassDirection
      'n//':   print "norte";
      's//':   print "sur";
      'e//':   print "este";
      'o//':   print "oeste";
      'ne//':   print "noreste";
      'no//':   print "noroeste";
      'se//':   print "sureste";
      'so//':   print "suroeste";
      default: rfalse;
    }
    rtrue;
];

! ----------------------------------------------------------------------------
!  LanguageVerbIsDebugging es llamado por SearchScope. Debe devolver true
!  si la palabra w es un verbo de depuración que necesita todos los objetos en alcance.
! ----------------------------------------------------------------------------

#Ifdef DEBUG;
[ LanguageVerbIsDebugging w;
    if (w == 'robar' or 'arbol' or 'abstracto'
                     or 'iralugar' or 'alcance' or 'mostrarobjeto')
        rtrue;
    rfalse;
];
#Endif;

! ----------------------------------------------------------------------------
!  LanguageVerbLikesAdverb es llamado por PrintCommand cuando imprime un error UPTO_PE
!  o un mensaje de inferencia. Palabras que son verbos intransitivos, es decir,
!  que requieren un nombre de dirección como adverbio ('caminar oeste'), no un nombre
!  ('Solo te entendí hasta querer tocar /el/ suelo'), deben hacer que la rutina devuelva true.
! ----------------------------------------------------------------------------

[ LanguageVerbLikesAdverb w;
    if (w == 'mirar' or 'ir' or 'correr' or 'marchar' or 'l//' or 'empujar' or 'caminar')
        rtrue;
    rfalse;
];

! ----------------------------------------------------------------------------
!  LanguageVerbMayBeName es llamado por NounDomain cuando maneja la
!  respuesta del jugador a un prompt "¿Te refieres al palo corto o al palo
!  largo?" del parser. Si la respuesta es otro verbo (por ejemplo,
!  MIRAR) entonces el comando ambiguo anterior se descarta /a menos que/
!  sea una de estas palabras que podría ser tanto un verbo /como/ un
!  adjetivo en una propiedad 'name'.
! ----------------------------------------------------------------------------

[ LanguageVerbMayBeName w;
    if (w == 'largo' or 'corto' or 'normal'
                      or 'breve' or 'completo' or 'detallado')
        rtrue;
    rfalse;
];

! Constantes de texto para menús y interfaz
Constant NKEY__TX       = "N = siguiente tema";
Constant PKEY__TX       = "P = anterior";
Constant QKEY1__TX      = "  Q = continuar juego";
Constant QKEY2__TX      = "Q = men@{FA} anterior";
Constant RKEY__TX       = "ENTER = leer tema";

Constant NKEY1__KY      = 'N';
Constant NKEY2__KY      = 'n';
Constant PKEY1__KY      = 'P';
Constant PKEY2__KY      = 'p';
Constant QKEY1__KY      = 'Q';
Constant QKEY2__KY      = 'q';

Constant SCORE__TX      = "Puntuaci@{F3}n: ";
Constant MOVES__TX      = "Movimientos: ";
Constant TIME__TX       = "Tiempo: ";
Constant SCORE_S__TX    = "P: ";
Constant MOVES_S__TX    = "M: ";
Constant TIME_S__TX     = "T: ";
Constant CANTGO__TX     = "No puedes ir por ah@{ED}.";
Constant FORMER__TX     = "tu antiguo ser";
Constant MYFORMER__TX   = "mi antiguo ser";
Constant YOURSELF__TX   = "t@{FA} mismo";
Constant MYSELF__TX     = "yo mismo";
Constant YOU__TX        = "T@{FA}";
Constant DARKNESS__TX   = "Oscuridad";

Constant THOSET__TX     = "esas cosas";
Constant THAT__TX       = "eso";
Constant THE__TX        = "el/la";
Constant OR__TX         = " o ";
Constant NOTHING__TX    = "nada";
Constant IS__TX         = " es";
Constant ARE__TX        = " son";
Constant IS2__TX        = "es ";
Constant ARE2__TX       = "son ";
Constant WAS__TX        = " era";
Constant WERE__TX       = " eran";
Constant WAS2__TX       = "era ";
Constant WERE2__TX      = "eran ";
Constant AND__TX        = " y ";
Constant WHOM__TX       = "a qui@{E9}n ";
Constant WHICH__TX      = "cu@{E1}l ";
Constant COMMA__TX      = ", ";
Constant COLON__TX      = ":";

! Para EnterSub()
Constant STAND__TX	= 'estar';
Constant SIT__TX	= 'sentar';
Constant LIE__TX	= 'acostar';

Constant LIBERROR__TX   = "Error de librer@{ED}a ";
Constant TERP__TX       = "Int@{E9}rprete ";
Constant VER__TX        = "Versi@{F3}n ";
Constant STDTERP__TX    = "Int@{E9}rprete est@{E1}ndar ";
Constant TERPVER__TX	= "Versi@{F3}n del int@{E9}rprete ";
Constant LIBSER__TX	= "N@{FA}mero de serie de librer@{ED}a ";
Constant VM__TX		= "VM ";
Constant RELEASE__TX    = "Versi@{F3}n ";
Constant SERNUM__TX     = "N@{FA}mero de serie ";
Constant INFORMV__TX    = "Inform v";
Constant LIBRARYV__TX   = " Librer@{ED}a v";

! ----------------------------------------------------------------------------
! Información sobre pronombres nominativos versus acusativos...
! Considera la oración "Ella lo golpeó.".
! "Ella" está en caso nominativo. Aparece al comienzo de una oración.
! "lo" está en caso acusativo. No aparecerá al comienzo.
! ----------------------------------------------------------------------------

! Acusativo
[ ThatOrThose obj;
    if (obj == player) {
	if (player provides narrative_voice) {
	    if (player.narrative_voice == 1) { print "me"; return; }
	    if (player.narrative_voice == 3) { CDefart(player); return; }
	}
	print "te";
	return;
    }
    if (obj has pluralname) {
        if (obj has female) { print "esas"; return; }
        else { print "esos"; return; }
    }
    if (obj has female)           { print "esa"; return; }
    if (obj has male or animate)
        if (obj hasnt neuter)     { print "@{E9}l"; return; }
    print "eso";
];

! Acusativo
[ ItOrThem obj;
    if (obj == player) {
	if (player provides narrative_voice) {
	    if (player.narrative_voice == 1) { print "me"; return; }
	    if (player.narrative_voice == 3) { CDefart(player); return; }
	}
	print "te";
	return;
    }
    if (obj has pluralname) {
        if (obj has female) { print "las"; return; }
        else { print "los"; return; }
    }
    if (obj has female)           { print "la"; return; }
    if (obj has male or animate)
        if (obj hasnt neuter)     { print "lo"; return; }
    print "lo";
];

! Nominativo
[ CThatOrThose obj;
    if (obj == player) {
	if (player provides narrative_voice) {
	    if (player.narrative_voice == 1) { print "Yo"; return; }
	    if (player.narrative_voice == 3) { CDefart(player); return; }
	}
	print "T@{FA}";
	return;
    }
    if (obj has pluralname) {
        if (obj has female) { print "Esas"; return; }
        else { print "Esos"; return; }
    }
    if (obj has female)			{ print "Ella"; return; }
    if (obj has male or animate) {
        if (obj hasnt neuter)		{ print "@{C9}l"; return; }
    }
    print "Eso";
];

! Nominativo
[ CTheyreOrThats obj;
    if (obj == player) {
	if (player provides narrative_voice) {
	    if (player.narrative_voice == 1) { Tense("Estoy", "Estaba"); return; }
	    if (player.narrative_voice == 3) { CDefart(player); Tense(" est@{E1}", " estaba"); return; }
	}
	Tense("Est@{E1}s", "Estabas");
	return;
    }
    if (obj has pluralname)		{ Tense("Est@{E1}n", "Estaban"); return; }
    if (obj has female)			{ Tense("Est@{E1}", "Estaba"); return; }
    if (obj has male or animate) {
        if (obj hasnt neuter)		{ Tense("Est@{E1}", "Estaba"); return; }
    }
    Tense("Est@{E1}", "Estaba");
];

[ IsOrAre obj;
    if (player provides narrative_tense && player.narrative_tense == PAST_TENSE) {
        if (obj has pluralname) print "eran"; else print "era";
        return;
    }
    if (obj has pluralname) print "son"; else print "es";
    return;
];

[ nop x; x = x; ];      ! regla de impresión para absorber valor de retorno no deseado

! FUNCIONES DE SUJETO PARA NARRATIVA ESPAÑOLA
[ SubjectNotPlayer obj reportage nocaps v2 v3 past;
    if (past && player provides narrative_tense && player.narrative_tense == PAST_TENSE) {
        v2 = past;
        v3 = past;
    }
    if (reportage && actor ~= player) {
        L__M(##Miscellany, 60, actor);
        if (obj == actor) {
            print (theActor) obj, " ", (string) v3;
            return;
        }
        else
            if (obj has pluralname) {
                print (the) obj, " ", (string) v2;
                return;
            }
            else {print (the) obj, " ", (string) v3; return;}
    }
   else
        if (obj has pluralname) {
	    if (nocaps)
		print (the) obj;
	    else
		print (The) obj;
	    print " ", (string) v2;
	    return;
	}
        else {
	    if (nocaps)
		print (the) obj;
	    else
		print (The) obj;
	    print " ", (string) v3; return;
	}
];

[ CSubjectVoice obj v1 v2 v3 past;
    if (past && player provides narrative_tense && player.narrative_tense == PAST_TENSE) {
        v1 = past;
        v2 = past;
        v3 = past;
    } else {
        if (v2 == 0) v2 = v1;
        if (v3 == 0) v3 = v1;
    }
    if (obj ~= player) { print (string) v3; return; }

    if (player provides narrative_voice) switch (player.narrative_voice) {
      1:  print (string) v1; return;
      2:  ! No hacer nada.
      3:  print (string) v3; return;
      default: RunTimeError(16, player.narrative_voice);
    }

    print (string) v2; return;
];

[ CSubjectVerb obj reportage nocaps v1 v2 v3 past;
    if (past && player provides narrative_tense && player.narrative_tense == PAST_TENSE) {
        v1 = past;
        v2 = past;
        v3 = past;
    } else {
        if (v2 == 0) v2 = v1;
        if (v3 == 0) v3 = v1;
    }
    if (obj == player) {
        if (player provides narrative_voice) switch (player.narrative_voice) {
          1:  print "Yo ", (string) v1; return;
          2:  ! No hacer nada.
          3:  CDefart(player);
              print " ", (string) v3; return;
          default: RunTimeError(16, player.narrative_voice);
        }
        if (nocaps) { print "t@{FA} ", (string) v2; return; }
	print "T@{FA} ", (string) v2; return;
    }
    SubjectNotPlayer(obj, reportage, nocaps, v2, v3);
];

! Funciones auxiliares para conjugación española
[ CSubjectIs obj reportage nocaps;
    if (obj == player) {
        if (player provides narrative_voice) switch (player.narrative_voice) {
          1:  Tense("estoy", "estaba"); return;
          2:  ! No hacer nada.
          3:  CDefart(player);
              Tense(" est@{E1}", " estaba"); return;
          default: RunTimeError(16, player.narrative_voice);
        }
        if (nocaps) Tense("est@{E1}s", "estabas");
        else Tense("Est@{E1}s", "Estabas");
        return;
    }
    SubjectNotPlayer(obj, reportage, nocaps, "est@{E1}n", "est@{E1}", "estaba");
];

[ CSubjectIsnt obj reportage nocaps;
    if (obj == player) {
        if (player provides narrative_voice) switch (player.narrative_voice) {
          1:  Tense("no estoy", "no estaba"); return;
          2:  ! No hacer nada.
          3:  CDefart(player);
              Tense(" no est@{E1}", " no estaba"); return;
          default: RunTimeError(16, player.narrative_voice);
        }
        if (nocaps) Tense("no est@{E1}s", "no estabas");
        else Tense("No est@{E1}s", "No estabas");
	return;
    }
    SubjectNotPlayer(obj, reportage, nocaps, "no est@{E1}n", "no est@{E1}", "no estaba");
];

[ CSubjectHas obj reportage nocaps;
    if (obj == player) {
        if (player provides narrative_voice) switch (player.narrative_voice) {
          1:  Tense("tengo", "ten@{ED}a"); return;
          2:  ! No hacer nada.
          3:  CDefart(player);
              Tense(" tiene", " ten@{ED}a"); return;
          default: RunTimeError(16, player.narrative_voice);
        }
        if (nocaps) Tense("tienes", "ten@{ED}as");
        else Tense("Tienes", "Ten@{ED}as");
        return;
    }
    SubjectNotPlayer(obj, reportage, nocaps, "tienen", "tiene", "ten@{ED}a");
];

[ CSubjectWill obj reportage nocaps;
    if (obj == player) {
        if (player provides narrative_voice) switch (player.narrative_voice) {
          1:  Tense("voy a", "iba a"); return;
          2:  ! No hacer nada.
          3:  CDefart(player);
              Tense(" va a", " iba a"); return;
          default: RunTimeError(16, player.narrative_voice);
        }
        if (nocaps) Tense("vas a", "ibas a");
        else Tense("Vas a", "Ibas a");
        return;
    }
    SubjectNotPlayer(obj, reportage, nocaps, "van a", "va a", "iba a");
];

[ CSubjectCan obj reportage nocaps;
    CSubjectVerb(obj, reportage, nocaps, "puedo", "puedes", "puede", "pod@{ED}a");
];

[ CSubjectCant obj reportage nocaps;
    CSubjectVerb(obj, reportage, nocaps, "no puedo", "no puedes", "no puede", "no pod@{ED}a");
];

[ CSubjectDont obj reportage nocaps;
    CSubjectVerb(obj, reportage, nocaps, "no", "no", "no", "no");
];

[ OnesSelf obj;
    if (obj == player) {
        if (player provides narrative_voice) switch(player.narrative_voice) {
            1:  print (string) MYSELF__TX; return;
            2:  ! No hacer nada.
            3:  if (obj has female) {print "ella misma"; return;}
                print "@{E9}l mismo"; return;
          default: RunTimeError(16, player.narrative_voice);
        }
        print "ti mismo"; return;
    }
    if (obj has male) { print "@{E9}l mismo"; return; }
    if (obj has female) {print "ella misma"; return; }
    print "ello mismo"; return;
];

[ Possessive obj caps;
    if (obj == player) {
        if (player provides narrative_voice) switch(player.narrative_voice) {
          1:  if (caps) print "M"; else print "m"; print "i"; return;
          2:  ! No hacer nada.
          3:  CDefart(player);
              print " de"; return;
          default: RunTimeError(16, player.narrative_voice);
        }
        if (caps) print "T"; else print "t";
        print "u"; return;
    }
    if (obj has pluralname) {
      if (caps) print "S"; else print "s";
      print "u"; return;
    }
    if (obj has female) {
      if (caps) print "S"; else print "s";
      print "u"; return;
    }
    if (obj has male or animate) {
      if (obj hasnt neuter) {
        if (caps) print "S"; else print "s";
        print "u"; return;
      }
    }
    if (caps) print "S"; else { print "s"; }
    print "u"; return;
];

[ PossessiveCaps obj;
    Possessive(obj, true);
];

[ theActor obj;
    if (obj == player) {
        if (obj provides narrative_voice) {
            switch (obj.narrative_voice) {
              1:  print "yo"; return;
              2:  ! No hacer nada.
              3:  if (obj has neuter) { print "ello"; return; }
                  if (obj has female) { print "ella"; return; }
                  print "@{E9}l"; return;
              default: RunTimeError(16, player.narrative_voice);
            }
        }
        print "t@{FA}"; return;
    }
    if (obj has pluralname) {
        if (obj has female) { print "ellas"; return; }
        else { print "ellos"; return; }
    }
    if (obj has female)           { print "ella"; return; }
    if (obj has male or animate)
        if (obj hasnt neuter)     { print "@{E9}l"; return; }
                                    print "eso";
];

[ SupportObj obj s1 s2;
    if (obj has supporter)          print (string) s1;
    else                            print (string) s2;
];

[ PluralObj obj s1 s2 past;
    if (player provides narrative_tense && player.narrative_tense == PAST_TENSE) {
        print (string) past;
        return;
    }
    if (obj has pluralname)         print (string) s1;
    else                            print (string) s2;
];

! ----------------------------------------------------------------------------
! Tense es una función auxiliar para presentar el tiempo correcto de un
! verbo. El primer parámetro es el verbo en presente. El segundo
! parámetro es el verbo en pasado. Si el segundo parámetro se
! omite, entonces no se imprimirá nada si el tiempo apropiado es pasado.
! ----------------------------------------------------------------------------
[ Tense present past;
    if (player provides narrative_tense && player.narrative_tense == PAST_TENSE) {
        if (past == false) return;
        print (string) past;
    }
    else
        print (string) present;
];

[ DecideAgainst;
    CSubjectVerb(actor, false, false, "decido", "decides", "decide", "decidi@{F3}");
    print " que";
    Tense(" no es", " no era");
    " una buena idea.";
];

#Ifdef TARGET_ZCODE;

[ LowerCase c;    ! para ZSCII coincidiendo con ISO 8859-1
   switch (c) {
     'A' to 'Z':                            c = c + 32;
     202, 204, 212, 214, 221:               c--;
     217, 218:                              c = c - 2;
     158 to 160, 167, 168, 208 to 210:      c = c - 3;
     186 to 190, 196 to 200:                c = c - 5 ;
     175 to 180:                            c = c - 6;
   }
   return c;
];

[ UpperCase c;    ! para ZSCII coincidiendo con ISO 8859-1
   switch (c) {
     'a' to 'z':                            c = c - 32;
     201, 203, 211, 213, 220:               c++;
     215, 216:                              c = c + 2;
     155 to 157, 164, 165, 205 to 207:      c = c + 3;
     181 to 185, 191 to 195:                c = c + 5 ;
     169 to 174:                            c = c + 6;
   }
   return c;
];

#Ifnot; ! TARGET_GLULX

[ LowerCase c; return glk_char_to_lower(c); ];
[ UpperCase c; return glk_char_to_upper(c); ];

#Endif; ! TARGET_

! ==============================================================================
! FUNCIÓN PRINCIPAL DE MENSAJES DEL SISTEMA - LanguageLM
! Esta función maneja TODOS los mensajes del juego en español
! ==============================================================================

[ LanguageLM n x1 x2;
  Answer,Ask:
            print "No hay respuesta.";
! Ask:      ver Answer
  Attack:   print "La violencia no es la respuesta.";
  Blow:     CSubjectCant(actor,true);
            " soplar ", (thatorthose) x1, " @{FA}tilmente.";
  Burn: switch (n) {
        1:  print "Este acto peligroso ";
            Tense("lograr@{ED}a", "habr@{ED}a logrado");
            " poco.";
        2:  DecideAgainst();
    }
  Buy:      print "No hay nada en venta.";
  Climb: switch (n) {
        1:  print "Trepar ", (ThatOrThose) x1, " ";
            Tense("lograr@{ED}a", "habr@{ED}a logrado");
            " poco.";
        2:  DecideAgainst();
    }
  Close: switch (n) {
        1:  CSubjectIs(x1,true);
            print " no es algo que ", (theActor) actor;
            Tense(" pueda cerrar", " pudiera haber cerrado");
            ".";
        2:  CSubjectIs(x1,true); " ya est@{E1} cerrad", (o) x1, ".";
        3:  CSubjectVerb(actor,false,false,"cierro","cierras","cierra","cerr@{F3}");
            " ", (the) x1, ".";
        4:  "(primero cerrando ", (the) x1, ")";
    }
  CommandsOff: switch (n) {
        1: "[Grabaci@{F3}n de comandos desactivada.]";
        #Ifdef TARGET_GLULX;
        2: "[La grabaci@{F3}n de comandos ya est@{E1} desactivada.]";
        #Endif; ! TARGET_
    }
  CommandsOn: switch (n) {
        1: "[Grabaci@{F3}n de comandos activada.]";
        #Ifdef TARGET_GLULX;
        2: "[Los comandos se est@{E1}n reproduciendo actualmente.]";
        3: "[La grabaci@{F3}n de comandos ya est@{E1} activada.]";
        4: "[Fall@{F3} la grabaci@{F3}n de comandos.]";
        #Endif; ! TARGET_
    }
  CommandsRead: switch (n) {
        1: "[Reproduciendo comandos.]";
        #Ifdef TARGET_GLULX;
        2: "[Los comandos ya se est@{E1}n reproduciendo.]";
        3: "[Fall@{F3} la reproducci@{F3}n de comandos. La grabaci@{F3}n est@{E1} activada.]";
        4: "[Fall@{F3} la reproducci@{F3}n de comandos.]";
        5: "[Reproducci@{F3}n de comandos completada.]";
        #Endif; ! TARGET_
    }
  Consult:  CSubjectVerb(actor,true,false,"descubro","descubres","descubre","descubri@{F3}");
            print " nada de inter@{E9}s en ";
            if (x1 == player) { OnesSelf(x1); ".";}
            else print_ret (the) x1, ".";
  Cut: switch (n) {
        1:  print "Cortar ", (ThatOrThose) x1, " ";
            Tense("lograr@{ED}a", "habr@{ED}a logrado");
            " poco.";
        2:  DecideAgainst();
    }
  Dig:      print "Cavar no ";
            Tense("lograr@{ED}a", "habr@{ED}a logrado");
            " nada aqu@{ED}.";
  Disrobe: switch (n) {
        1:  CSubjectIsnt(actor,true); " llevando ", (ThatOrThose) x1, ".";
        2:  CSubjectVerb(actor,false,false,"me quito","te quitas","se quita", "se quit@{F3}");
            " ", (the) x1, ".";
        3:  "(primero quit@{E1}ndose ", (the) x1, ")";
        4: CSubjectVerb(actor,false,false, "necesito quitar", "necesitas quitar", "necesita quitar", "necesitaba quitar");
           " ", (the) noun, " primero.";
    }
  Drink:    print "No hay nada adecuado para beber aqu@{ED}.";
  Drop: switch (n) {
        1:  CSubjectIs(x1,true); " ya est@{E1} aqu@{ED}.";
        2:  CSubjectVerb(actor, false, false, "no tengo", "no tienes", "no tiene",
                         "no ten@{ED}a");
            " ", (the) x1, ".";
        3:  "Soltado.";
        4: CSubjectVerb(actor, false, false, "necesito sacar", "necesitas sacar", "necesita sacar", "necesitaba sacar");
           print " ", (the) x1, " ";
           if (x2 has container)
               print "de";
           else
               print "de";
           " ", (the) x2, " antes de soltarlo.";
    }
  Eat: switch (n) {
        1:  CSubjectIs(x1,true); " claramente no comestible.";
        2:  CSubjectVerb(actor,false,false,"como","comes","come", "comi@{F3}"); print " ", (the) x1;
                if (actor == player) ". No est@{E1} mal."; else ".";
    }
  EmptyT: switch (n) {
        1:  CSubjectCant(x1,true); " contener cosas.";
        2:  CSubjectIs(x1,true); " cerrad", (o) x1, ".";
        3:  CSubjectIs(x1,true); " ya est@{E1} vac@{ED}", (o) x1, ".";
        4:  print "Eso no ";
            Tense("vaciar@{ED}a", "habr@{ED}a vaciado");
            " nada.";
    }
  Enter: switch (n) {
        1:  print "Pero "; CSubjectIs(actor,true,true);
            " ya est@{E1} ", (nop) SupportObj(x1,"sobre ","en "), (the) x1, ".";
        2:  CSubjectIs(x1,true);
            print " no es algo en lo que ", (theActor) actor;
            Tense(" pueda ", " pudiera ");
            switch (x2) {
              'stand':  "pararse.";
              'sit':    "sentarse.";
              'lie':    "acostarse.";
              default:  "entrar.";
            }
        3:  CSubjectCant(actor,true);
            " entrar en ", (the) x1, " cerrad", (o) x1, ".";
        4:  CSubjectCan(actor,true);
            " solo entrar en algo que est@{E9} solo.";
        5:  CSubjectVerb(actor,false,false,"subo","subes","sube","subi@{F3}");
            SupportObj(x1," a"," en"); " ", (the) x1, ".";
        6:  "(bajando de ", (the) x1, ")";
        7:  if (x1 has supporter) "(subiendo a ", (the) x1, ")";
            if (x1 has container) "(entrando en ", (the) x1, ")";
                                  "(entrando en ", (the) x1, ")";
    }
  Examine: switch (n) {
        1:  "Oscuridad, sustantivo. Una ausencia de luz para ver.";
        2:  CSubjectVerb(actor,true,false,"veo","ves","ve","vi@{F3}");
            " nada especial sobre ", (the) x1, ".";
        3:  CSubjectIs(x1,true);
            Tense(" actualmente");
            print " ";
            if (x1 has on) "encendid", (o) x1, "."; else "apagad", (o) x1, ".";
    }
  Exit: switch (n) {
        1:  print "Pero ";
            CSubjectIsnt(actor,true,true);
            " dentro de nada en este momento.";
        2:  CSubjectCant(actor,false);
            " salir de ", (the) x1, " cerrad", (o) x1, ".";
        3:  CSubjectVerb(actor,false,false,"salgo","sales","sale", "sali@{F3}");
            print " ";
            SupportObj(x1,"de","de"); " ", (the) x1, ".";
        4:  CSubjectIsnt(actor,true);
            print " ";
            SupportObj(x1,"sobre","en"); " ", (the) x1, ".";
        5:  "(primero saliendo de ", (the) x1, ")";
        6:  CSubjectVerb(actor,false,false,"me levanto","te levantas","se levanta","se levant@{F3}"); ".";
    }
  Fill: switch (n) {
        1:  print "No hay nada obvio con qu@{E9} llenar ", (the) x1, ".";
        2:  print "Llenar ", (the) x1, " con ", (the) x2, " no ";
            Tense("tendr@{ED}a", "habr@{ED}a tenido");
            " sentido.";
    }
  FullScore: switch (n) {
        1:  if (deadflag) print "La puntuaci@{F3}n era "; else print "La puntuaci@{F3}n es ";
                "compuesta de la siguiente manera:^";
        2:  "encontrar varios objetos";
        3:  "visitar varios lugares";
        4:  print "total (de ", MAX_SCORE; ")";
    }
  GetOff:   print "Pero ";
            CSubjectIsnt(actor,true,true); " sobre ", (the) x1, " en este momento.";
  Give: switch (n) {
        1:  CSubjectIsnt(actor,true); " sosteniendo ", (the) x1, ".";
        2:  CSubjectVerb(actor,false,false,"hago malabares","haces malabares","hace malabares","hizo malabares");
            print " con ", (the) x1, " por un rato, pero ";
            CSubjectVoice(actor,"no logro","no logras","no logra","no logr@{F3}");
            " mucho.";
        3:  CSubjectDont(x1,true); " parece interesad", (o) x1, ".";
        4:  CSubjectVerb(actor,false,false,"entrego","entregas","entrega","entreg@{F3}");
            " ", (the) x1, ".";
    }
  Go: switch (n) {
        1:  CSubjectWill(actor,true);
            Tense(" tener", " haber tenido");
                " que bajar de ", (the) x1, " primero.";
        2:  CSubjectCant(actor,true); " ir por ah@{ED}.";
        3:  CSubjectIs  (actor,true); " incapaz de trepar ", (the) x1, ".";
        4:  CSubjectIs  (actor,true); " incapaz de descender por ", (the) x1, ".";
        5:  CSubjectCant(actor,true); " ya que ", (the) x1, " est@{E1} en el camino.";
        6:  CSubjectCant(actor,true); " ya que ", (the) x1, " no lleva a ninguna parte.";
        7:  CSubjectVerb(actor,false,false,"me voy","te vas","se va","se fue"); ".";
    }
  Insert: switch (n) {
        1:  CSubjectVerb(actor,true,false,"necesito","necesitas","necesita","necesitaba");
            print " estar sosteniendo ", (the) x1, " antes de poder";
            " ponerlo dentro de algo m@{E1}s.";
        2:  CSubjectCant(x1,true); " contener cosas.";
        3:  CSubjectIs  (x1,true); " cerrad", (o) x1, ".";
        4:  CSubjectWill(actor,true);
            Tense(" necesitar", " haber necesitado");
            " quitarlo primero.";
        5:  CSubjectCant(actor,true); " poner algo dentro de s@{ED} mismo.";
        6:  "(primero quitando ", (the) x1, ")";
        7:  print "No hay m@{E1}s espacio en ", (the) x1, ".";
        8:  "Hecho.";
        9:  CSubjectVerb(actor,false,false,"pongo","pones","pone","puso"); " ", (the) x1, " en ", (the) x2, ".";
    }
  Inv: switch (n) {
        1:  CSubjectIs  (actor,false); " no lleva nada.";
        2:  CSubjectIs  (actor,false); print " llevando";
        3:  ":";
        4:  ".";
    }
  Jump: CSubjectVerb(actor,false,false,"salto","saltas","salta","salt@{F3}"); " en el lugar, in@{FA}tilmente.";
  JumpIn: switch (n) {
        1: print "Saltar en ", (the) x1, " no ";
           Tense("lograr@{ED}a", "habr@{ED}a logrado");
           " nada aqu@{ED}.";
        2: DecideAgainst();
    }
  JumpOn: switch (n) {
        1: print "Saltar sobre ", (the) x1, " no ";
           Tense("lograr@{ED}a", "habr@{ED}a logrado");
           " nada aqu@{ED}.";
        2: DecideAgainst();
    }
  JumpOver: switch (n) {
        1: print "Saltar por encima de ", (the) x1, " no ";
           Tense("lograr@{ED}a", "habr@{ED}a logrado");
           " nada aqu@{ED}.";
        2:  DecideAgainst();
    }
  Kiss:     "Mant@{E9}n tu mente en el juego.";
  Listen:   CSubjectVerb(actor,true,false,"oigo","oyes","oye","oy@{F3}"); " nada inesperado.";
  ListMiscellany: switch (n) {
        1:  print " (dando luz)";
        2:  print " (que est@{E1} cerrad", (o) x1, ")";
        3:  print " (cerrad", (o) x1, " y dando luz)";
        4:  print " (que est@{E1} vac@{ED}", (o) x1, ")";
        5:  print " (vac@{ED}", (o) x1, " y dando luz)";
        6:  print " (que est@{E1} cerrad", (o) x1, " y vac@{ED}", (o) x1, ")";
        7:  print " (cerrad", (o) x1, ", vac@{ED}", (o) x1, " y dando luz)";
        8:  print " (dando luz y siendo llevad", (o) x1;
        9:  print " (dando luz";
        10: print " (siendo llevad", (o) x1;
        11: print " (que est@{E1} ";
        12: print "abiert", (o) x1;
        13: print "abiert", (o) x1, " pero vac@{ED}", (o) x1;
        14: print "cerrad", (o) x1;
        15: print "cerrad", (o) x1, " y bloqueado";
        16: print " y vac@{ED}", (o) x1;
        17: print " (que est@{E1} vac@{ED}", (o) x1, ")";
        18: print " que contiene ";
        19: print " (sobre ";
        20: print ", encima de ";
        21: print " (en ";
        22: print ", dentro de ";
    }
  LMode1:   print (string) Story, " est@{E1} ahora en su modo de impresi@{F3}n ";
            if (initial_lookmode == 1) print "normal ";
            "~breve~, que da descripciones largas de lugares nunca antes 
             visitados y descripciones cortas en otros casos.";
  LMode2:   print (string) Story, " est@{E1} ahora en su modo ";
            if (initial_lookmode ~= 1 or 3) print "normal ";
            "~detallado~, que siempre da descripciones largas de ubicaciones
             (incluso si has estado ah@{ED} antes).";
  LMode3:   print (string) Story, " est@{E1} ahora en su modo ";
            if (initial_lookmode == 3) print "normal ";
            "~superbreve~, que siempre da descripciones cortas de ubicaciones
             (incluso si no has estado ah@{ED} antes).";
  Lock: switch (n) {
        1:  CSubjectDont(x1,true);
            print " parece ser algo que ", (theActor) actor;
            Tense(" pueda", " pudiera");
            " bloquear.";
        2:  CSubjectIs  (x1,true); " bloqueado en este momento.";
        3:  CSubjectWill(actor,true); " primero tener que cerrar ", (the) x1, ".";
        4:  CSubjectDont(x1,true); " parece encajar en la cerradura.";
        5:  CSubjectVerb(actor,false,false,"bloqueo","bloqueas","bloquea","bloque@{F3}"); " ", (the) x1, ".";
    }
  Look: switch (n) {
        1:  print " (sobre ", (the) x1, ")";
        2:  print " (en ", (the) x1, ")";
        3:  print " (como ", (object) x1, ")";
        4:  print "^Sobre ", (the) x1;
            WriteListFrom(child(x1),
              ENGLISH_BIT+RECURSE_BIT+PARTINV_BIT+TERSE_BIT+CONCEAL_BIT+ISARE_BIT);
            ".";
        5,6:
            if (x1 ~= location) {
                if (x1 has supporter) print "^Sobre "; else print "^En ";
                print (the) x1, " ", (theActor) actor, " ";
                Tense("puede", "pod@{ED}a");
            }
            else { new_line; CSubjectCan(actor,false); }
            if (n == 5) print " tambi@{E9}n";
            print " ver ";
            WriteListFrom(child(x1),
              ENGLISH_BIT+RECURSE_BIT+PARTINV_BIT+TERSE_BIT+CONCEAL_BIT+WORKFLAG_BIT);
            if (x1 ~= location) "."; else " aqu@{ED}.";
        7:  CSubjectVerb(actor,true,false,"veo","ves","ve", "vi@{F3}"); " nada inesperado en esa direcci@{F3}n.";
    }
  LookUnder: switch (n) {
        1:  print "Pero est@{E1} oscuro.";
        2:  CSubjectVerb(actor,true,false,"encuentro","encuentras","encuentra", "encontr@{F3}"); " nada de inter@{E9}s.";
    }
  Mild:     "Efectivamente.";
  Miscellany: switch (n) {
        1:  "(considerando solo los primeros diecis@{E9}is objetos)^";
        2:  "Nada que hacer.";
        3:  print " "; CSubjectVerb(player, false, false, "he muerto", "has muerto", "ha muerto");
	    print " ";
        4:  print " "; CSubjectVerb(player, false, false, "he ganado", "has ganado", "ha ganado");
            print " ";
        5:  print "^@{BF}Te gustar@{ED}a REINICIAR, CARGAR una partida guardada";
            #Ifdef DEATH_MENTION_UNDO;
	    if (undo_flag ~= 0)
		print ", DESHACER tu @{FA}ltimo movimiento";
            #Endif;
            if (TASKS_PROVIDED == 0) print ", obtener la PUNTUACI@{D3}N COMPLETA de este juego";
            if (deadflag == 2 && AMUSING_PROVIDED == 0)
                print ", ver algunas sugerencias de cosas DIVERTIDAS que hacer";
            SerialComma(3); print " o SALIR?";
        6:  "[Tu int@{E9}rprete no proporciona ~deshacer~. @{A1}Lo siento!]";
            #Ifdef TARGET_ZCODE;
        7:  "~Deshacer~ fall@{F3}. [No todos los int@{E9}rpretes lo proporcionan.]";
            #Ifnot; ! TARGET_GLULX
        7:  "[No puedes ~deshacer~ m@{E1}s.]";
            #Endif; ! TARGET_
        8:  "Por favor, da una de las respuestas de arriba.";
        9:  print "^Ahora est@{E1} completamente oscuro aqu@{ED}.";
        10: "@{BF}Perd@{F3}n?";
        11: "[No puedes ~deshacer~ lo que no se ha hecho!]";
        12: "[No se puede ~deshacer~ dos veces seguidas. @{A1}Lo siento!]";
        13: "[Turno anterior deshecho.]";
        14: "Lo siento, eso no se puede corregir.";
        15: "No le des importancia.";
        16: "~Ups~ solo puede corregir una palabra.";
        17: print "Est@{E1} completamente oscuro, y ", (theActor) actor;
            Tense(" no puede", " no pod@{ED}a");
            " ver nada.";
        18: print "t@{FA} mismo";
        19: "Tan guap", (o) player, " como siempre.";
        20: "Para repetir un comando como ~rana, salta~, solo di ~otra vez~, no ~rana, otra vez~.";
        21: CSubjectCan(actor,true); " dif@{ED}cilmente repetir eso.";
        22: CSubjectCant(actor, true); " empezar con una coma.";
        23: CSubjectVerb(actor, true, false, "parece", "pareces", "parece", "parec@{ED}a");
            print " querer hablar con alguien, pero no ";
            Tense("puedo", "pod@{ED}a"); " ver con qui@{E9}n.";
        24: CSubjectCant(actor, true); " hablar con ", (the) x1, ".";
        25: "Para hablar con alguien, intenta ~alguien, hola~ o algo as@{ED}.";
        26: "(primero tomando ", (the) x1, ")";
        27: "No entend@{ED} esa oraci@{F3}n.";
        28: print "Solo te entend@{ED} hasta querer ";
        29: "No entend@{ED} ese n@{FA}mero.";
        30: CSubjectCant(actor,true); " ver tal cosa.";
        31: CSubjectVerb(actor, true, false, "parece", "pareces", "parece", "parec@{ED}a");
            " haber dicho muy poco.";
        32: CSubjectIsnt(actor); " sosteniendo eso.";
        33: "No puedes usar objetos m@{FA}ltiples con ese verbo.";
        34: "Solo puedes usar objetos m@{FA}ltiples una vez en una l@{ED}nea.";
        35: "No estoy seguro a qu@{E9} se refiere ~", (address) x1, "~.";
        36: "Exceptuaste algo que no estaba incluido de todos modos.";
        37: CSubjectCan(actor,true); " solo hacer eso a algo animado.";
            #Ifdef DIALECT_US;
        38: "Ese no es un verbo que reconozco.";
            #Ifnot;
        38: "Ese no es un verbo que reconozco.";
            #Endif;
        39: "Eso no es algo a lo que necesites referirte en el curso de este juego.";
        40: CSubjectCant(actor,true); " ver ~", (address) x1, "~ (", (the) x2, ") en este momento.";
        41: "No entend@{ED} c@{F3}mo termin@{F3} eso.";
        42: if (x1 == 0) print "Ninguno"; else print "Solo ", (number) x1;
            print " de esos ";
            if (x1 == 1) print "est@{E1}"; else print "est@{E1}n";
            " disponible.";
        43: "Nada que hacer.";
        44: print "No hay nada que ", (address) x1, ".";
        45: print "@{BF}A qui@{E9}n te refieres, ";
        46: print "@{BF}A cu@{E1}l te refieres, ";
        47: "Lo siento, solo puedes tener un art@{ED}culo aqu@{ED}. @{BF}Cu@{E1}l exactamente?";
        48: print "@{BF}A qui@{E9}n ";
            CSubjectVoice(player, "quiero", "quieres", "quiere", "quer@{ED}a");
            print " que ";
            if (x1 ~= player && x1 ~= nothing) print (the) x1, " ";
            PrintCommand(); "?";
        49: print "@{BF}Qu@{E9} ";
            CSubjectVoice(player, "quiero", "quieres", "quiere", "quer@{ED}a");
            print " que ";
            if (x1 ~= player && x1 ~= nothing) print (the) x1, " ";
            PrintCommand(); "?";
        50: print "La puntuaci@{F3}n acaba de ";
            if (x1 > 0) print "subir"; else { x1 = -x1; print "bajar"; }
            print " ", (number) x1, " punto";
            if (x1 > 1) print "s";
        51: "(Dado que algo dram@{E1}tico ha pasado, tu lista de comandos ha sido cortada.)";
        52: "^Teclea un n@{FA}mero del 1 al ", x1, ", 0 para mostrar de nuevo o presiona ENTER.";
        53: "^[Por favor presiona ESPACIO.]";
        54: "[Comentario registrado.]";
        55: "[Comentario NO registrado.]";
        56: ".";
        57: "?";
        58: "(primero tomando ", (the) x1, " de ", (the) x2, ")";
        59: "Tendr@{E1}s que ser m@{E1}s espec@{ED}fico.";
        60: print (The) x1, " observa que ";
    }
  No,Yes:   "Esa era una pregunta ret@{F3}rica.";
  NotifyOff:
            "Notificaci@{F3}n de puntuaci@{F3}n desactivada.";
  NotifyOn: "Notificaci@{F3}n de puntuaci@{F3}n activada.";
  Objects: switch (n) {
        1:  print (nop) CSubjectVerb(actor, false, false, "he manejado", "has manejado", "ha manejado");
        2:  CSubjectVerb(actor, false, false, "no he manejado", "no has manejado", "no ha manejado"); " nada.";
        3:  print " (llevado)";
        4:  print " (sostenido)";
        5:  print " (regalado)";
        6:  print " (en ", (name) x1, ")";
        7:  print " (en ", (the) x1, ")";
        8:  print " (dentro de ", (the) x1, ")";
        9:  print " (sobre ", (the) x1, ")";
        10: print " (perdido)";
    }
  Open: switch (n) {
        1:  CSubjectIs  (x1,true);
            print " no es algo que ", (theActor) actor;
            Tense(" pueda abrir", " pudiera haber abierto");
            ".";
        2:  CSubjectVerb(x1,true,false,"parece","pareces","parece","parec@{ED}a"); " estar bloqueado.";
        3:  CSubjectIs  (x1,true); " ya est@{E1} abiert", (o) x1, ".";
        4:  CSubjectVerb(actor,false,false,"abro","abres","abre","abri@{F3}"); print " ", (the) x1;
            Tense(", revelando ", " y revel@{F3} ");
                if (WriteListFrom(child(x1), ENGLISH_BIT+TERSE_BIT+CONCEAL_BIT) == 0) "nada.";
                ".";
        5:  CSubjectVerb(actor,false,false,"abro","abres","abre","abri@{F3}"); " ", (the) x1, ".";
        6:  "(primero abriendo ", (the) x1, ")";
    }
  Order:    CSubjectHas(x1,false); " mejores cosas que hacer.";
  Places: switch (n) {
        1:  print (nop) CSubjectVerb(actor, false, false, "he visitado", "has visitado", "ha visitado");
        2:  ".";
        3:  CSubjectVerb(actor, false, false, "no he visitado", "no has visitado", "no ha visitado"); " nada.";
    }
  Pray:     print "Nada pr@{E1}ctico ";
            Tense("resulta", "result@{F3}");
            " de la oraci@{F3}n de ", (Possessive) actor, ".";
  Prompt:   print "^>";
  Pronouns: switch (n) {
        1:  print "En este momento, ";
        2:  print "significa ";
        3:  print "no est@{E1} establecido";
        4:  "no se conocen pronombres en el juego.";
        5:  ".";
    }
  Pull,Push,Turn: switch (n) {
        1:  if (player provides narrative_voice && player.narrative_voice == 3) {
                print_ret (The) player, " no es probable que ayude a las cosas castig@{E1}ndose de esa manera.";
            } else {
                "Castigarte de esa manera no es probable que ayude a las cosas.";
            }
        2:  CSubjectIs  (x1,true); " fijo en su lugar.";
        3:  CSubjectIs  (actor,true); " incapaz.";
        4:  print "Nada obvio ";
            Tense("pasa", "pas@{F3}");
            ".";
        5:  print "Eso ";
            Tense("ser@{ED}a", "habr@{ED}a sido");
            " menos que cort@{E9}s.";
        6:  DecideAgainst();
    }
! Push: ver Pull
  PushDir: switch (n) {
        1:  print "Eso realmente no ";
            Tense("servir@{ED}a", "habr@{ED}a servido");
            " ning@{FA}n prop@{F3}sito.";
        2:  print "Esa ";
            Tense("no es", "no era");
            " una direcci@{F3}n.";
        3:  print "No por ah@{ED} ", (theActor) actor;
            Tense(" no puede", " no pod@{ED}a");
            ".";
    }
  PutOn: switch (n) {
        1:  CSubjectVerb(actor,true,false,"necesito","necesitas","necesita","necesitaba");
            print " estar sosteniendo ", (the) x1, " antes de poder";
            " ponerlo encima de algo m@{E1}s.";
        2:  CSubjectCant(actor,true,true); " poner algo encima de s@{ED} mismo.";
        3:  print "Poner cosas sobre ", (the) x1, " no";
            Tense(" lograr@{ED}a", " habr@{ED}a logrado");
            " nada.";
        4:  CSubjectVerb(actor,true,false,"me falta","te falta","le falta","le faltaba"); " la destreza.";
        5:  "(primero quitando ", (the) x1, ")";
        6:  print "No hay m@{E1}s espacio sobre ", (the) x1, ".";
        7:  "Hecho.";
        8:  CSubjectVerb(actor,false,false,"pongo","pones","pone","puso"); " ", (the) x1, " sobre ", (the) x2, ".";
    }
  Quit: switch (n) {
        1:  print "Por favor responde s@{ED} o no.";
        2:  print "@{BF}Est@{E1}s seguro de que quieres salir? ";
    }
  Remove: switch (n) {
        1:  CSubjectIs  (x1,true); " desafortunadamente cerrad", (o) x1, ".";
        2:  print "Pero ";
            CSubjectIsnt(x1,true,true); " ah@{ED} ahora.";
        3:  "Quitado.";
        4:  print "Pero ";
            CSubjectIsnt(x1,true,true); " en o sobre algo.";
    }
  Restart: switch (n) {
        1:  print "@{BF}Est@{E1}s seguro de que quieres reiniciar? ";
        2:  "Fall@{F3}.";
    }
  Restore: switch (n) {
        1:  "Cargar fall@{F3}.";
        2:  "Vale.";
    }
  Rub: switch (n) {
        1:  CSubjectVerb(actor,true,false,"logro","logras","logra","logr@{F3}");
            " nada con esto.";
        2:  DecideAgainst();
    }
  RunTimeError: print "** ";
	switch (n) {
	1:  print "Preposici@{F3}n no encontrada (esto no deber@{ED}a ocurrir)";
	2:  print "Valor de propiedad no es rutina o cadena: ~", (property) x2,
		"~ de ~", (name) x1, "~ (", x1, ")";
	3:  print "Entrada en lista de propiedades no es rutina o cadena: ~",
		(property) x2, "~ lista de ~", (name) x1, "~ (", x1, ")";
	4:  print "Demasiados temporizadores/demonios est@{E1}n activos simult@{E1}neamente.
		El l@{ED}mite es la constante de librer@{ED}a MAX_TIMERS
		(actualmente ", MAX_TIMERS, ") y deber@{ED}a incrementarse";
	5:  print "El objeto ~", (name) x1, "~ no tiene la propiedad ~", (property) x2, "~";
	7:  print "El objeto ~", (name) x1, "~ solo puede usarse como objeto jugador
		si tiene la propiedad ~number~";
	8:  print "Intento de tomar entrada aleatoria de un array de tabla vac@{ED}o";
	9:  print x1, " no es un n@{FA}mero de propiedad de direcci@{F3}n v@{E1}lido";
	10: print "El objeto-jugador est@{E1} fuera del @{E1}rbol de objetos";
	11: print "La habitaci@{F3}n ~", (name) x1, "~ no tiene la propiedad ~", (property) x2, "~";
	12: print "Se intent@{F3} establecer un pronombre no existente usando SetPronoun";
	13: print "Un token 'topic' solo puede ser seguido por una preposici@{F3}n";
	14: print "Se desbord@{F3} el l@{ED}mite del buffer de ", x1,
		" usando '@@64output_stream 3' ", (string) x2;
	15: print "LoopWithinObject roto porque el objeto ",
		(name) x1, " fue movido mientras el bucle pasaba a trav@{E9}s de @{E9}l.";
	16: print "Intento de usar narrative_voice ilegal de ", x1, ".";
	default:
	    print "(sin explicaci@{F3}n)";
    }
    print " **";
  Save: switch (n) {
        1:  "Guardar fall@{F3}.";
        2:  "Vale.";
    }
  Score: switch (n) {
        1:  if (deadflag) print "En ese juego puntuaste "; else print "Hasta ahora has puntuado ";
                print score, " de un posible ", MAX_SCORE, ", en ", turns, " turno";
                if (turns ~= 1) print "s";
                return;
        2:  "No hay puntuaci@{F3}n en esta historia.";
    }
  ScriptOff: switch (n) {
        1:  "La transcripci@{F3}n ya est@{E1} desactivada.";
        2:  "^Fin de la transcripci@{F3}n.";
        3:  "Intento de terminar transcripci@{F3}n fall@{F3}.";
    }
  ScriptOn: switch (n) {
        1:  "La transcripci@{F3}n ya est@{E1} activada.";
        2:  print "Inicio de una transcripci@{F3}n de"; VersionSub();
        3:  "Intento de comenzar transcripci@{F3}n fall@{F3}.";
    }
  Search: switch (n) {
        1:  print "Pero est@{E1} oscuro.";
        2:  print "No hay nada sobre ", (the) x1, ".";
        3:  print "Sobre ", (the) x1;
                WriteListFrom(child(x1), ENGLISH_BIT+TERSE_BIT+CONCEAL_BIT+ISARE_BIT);
                ".";
        4:  CSubjectVerb(actor,true,false,"encuentro","encuentras","encuentra","encontr@{F3}"); " nada de inter@{E9}s.";
        5:  CSubjectCant(actor,true); " ver dentro, ya que ", (the) x1, " est@{E1} cerrad", (o) x1, ".";
        6:  "", (The) x1, " est@{E1} vac@{ED}", (o) x1, ".";

        7:  print "En ", (the) x1;
                WriteListFrom(child(x1), ENGLISH_BIT+TERSE_BIT+CONCEAL_BIT+ISARE_BIT);
                ".";
    }
   ! "No," precedente no puede usarse para Set y SetTo
  Set:      CSubjectCant(actor,true); " configurar ", (ThatOrThose) x1, ".";
  SetTo:    CSubjectCant(actor,true); " configurar ", (ThatOrThose) x1, " a nada.";
  Show: switch (n) {
        1:  CSubjectIsnt(actor,true); " sosteniendo ", (the) x1, ".";
        2:  CSubjectIs  (x1,true); " poco impresiond", (o) x1, ".";
    }
  Sing:     print "El canto de ", (Possessive) actor, " es abominable.";
  Sleep:    CSubjectIsnt(actor,true); " sinti@{E9}ndose especialmente somnoliento.";
  Smell: switch (n) {
        1:  CSubjectVerb(actor,true,false,"huelo","hueles","huele","oli@{F3}"); " nada inesperado.";
        2:  DecideAgainst();
    }
            #Ifdef DIALECT_US;
  Sorry:    "Oh, no te disculpes.";
            #Ifnot;
  Sorry:    "Oh, no te disculpes.";
            #Endif;
  Squeeze: switch (n) {
        1:  DecideAgainst();
        2:  CSubjectVerb(actor,true,false,"logro","logras","logra","logr@{F3}"); " nada con esto.";
    }
  Strong:   print "Los verdaderos aventureros no usan tal lenguaje.";
  Swim:     print "No hay suficiente agua para nadar.";
  Swing:    print "No hay nada sensato para balancear aqu@{ED}.";
  SwitchOff: switch (n) {
        1:  CSubjectIs  (x1,true);
            print " no es algo que ", (theActor) actor, " ";
            Tense("pueda", "pudiera");
            " apagar.";
        2:  CSubjectIs  (x1,true); " ya est@{E1} apagad", (o) x1, ".";
        3:  CSubjectVerb(actor,false,false,"apago","apagas","apaga","apag@{F3}"); " ", (the) x1, ".";
    }
  SwitchOn: switch (n) {
        1:  CSubjectIs  (x1,true);
            print " no es algo que ", (theActor) actor, " ";
            Tense("pueda", "pudiera");
            " encender.";
        2:  CSubjectIs  (x1,true); " ya est@{E1} encendid", (o) x1, ".";
        3:  CSubjectVerb(actor,false,false,"enciendo","enciendes","enciende","encendi@{F3}"); " ", (the) x1, ".";
    }

  Take: switch (n) {
        1:  "Tomado.";
        2:  CSubjectIs  (actor,false); " siempre en posesi@{F3}n de s@{ED} mismo.";
        3:  print "No supongo que a ", (the) x1, " le ";
            Tense("importe", "hubiera importado");
            " eso.";
        4:  CSubjectWill(actor,true);
            print " tener que bajar de ", (the) x1, " primero.";
        5:  CSubjectVerb(actor,true,false,"ya tengo","ya tienes","ya tiene","ya ten@{ED}a"); " ", (ThatOrThose) x1, ".";
        6:  CSubjectVerb(x2,true,false,"parece","pareces","parece","parec@{ED}a"); " pertenecer a ", (the) x1, ".";
        7:  CSubjectVerb(x2,true,false,"parece","pareces","parece","parec@{ED}a"); " ser parte de ", (the) x1, ".";
        8:  CSubjectIs  (x1,true); " no disponible.";
        9:  CSubjectIs  (x1,true); " no abiert", (o) x1, ".";
        10: CSubjectIs  (x1,true); " dif@{ED}cilmente port@{E1}til.";
        11: CSubjectIs  (x1,true); " fijo en su lugar.";
        12: CSubjectIs  (actor,true); " llevando demasiadas cosas ya.";
        13: "(poniendo ", (the) x1, " en ", (the) x2, " para hacer espacio)";
    }
  Taste: switch (n) {
        1:  CSubjectVerb(actor,true,false,"saboreo","saboreas","saborea","sabore@{F3}"); " nada inesperado.";
        2:  DecideAgainst();
    }
  Tell: switch (n) {
        1:  CSubjectVerb(actor,false,false,"hablo","hablas","habla","habl@{F3}");
            " conmigo mismo por un rato.";
        2:  print "Esto no provoca reacci@{F3}n.";
    }
  Think:    "@{A1}Qu@{E9} buena idea!";
  ThrowAt: switch (n) {
        1:  "F@{FA}til.";
        2:  CSubjectVerb(actor,true,false,"me falta","te falta","le falta","le faltaba");
            print " el valor cuando ";
            Tense("llega", "lleg@{F3}");
            " el momento crucial.";
    }
  Tie: switch (n) {
        1:  CSubjectVerb(actor,true,false,"lograr@{ED}a","lograr@{ED}as","lograr@{ED}a","habr@{ED}a logrado");
            " nada con esto.";
        2:  DecideAgainst();
    }
  Touch: switch (n) {
        1:  DecideAgainst();
        2:  CSubjectVerb(actor,true,false,"siento","sientes","siente","sinti@{F3}"); " nada inesperado.";
        3:  print "Eso realmente no ";
            Tense("servir@{ED}a", "habr@{ED}a servido");
            " ning@{FA}n prop@{F3}sito.";
    }
! Turn: ver Pull.
  Unlock:  switch (n) {
        1:  CSubjectDont(x1,true);
            print " parece ser algo que ", (theActor) actor;
            Tense(" pueda desbloquear", " pudiera haber desbloqueado");
            ".";
        2:  CSubjectIs  (x1,true); " desbloqueado en este momento.";
        3:  CSubjectDont(x1,true); " parece encajar en la cerradura.";
        4:  CSubjectVerb(actor,false,false,"desbloqueo","desbloqueas","desbloquea","desbloque@{F3}"); " ", (the) x1, ".";
        5:  "(primero desbloqueando ", (the) x1, ")";
    }
  VagueGo:  CSubjectWill(actor);
            " tener que decir en qu@{E9} direcci@{F3}n de la br@{FA}jula ir.";
  Verify: switch (n) {
        1:  "El archivo del juego se ha verificado como intacto.";
        2:  "El archivo del juego no se verific@{F3} como intacto, y puede estar corrupto.";
    }
  Wait:     print "El tiempo pasa.";
  Wake:     print "La terrible verdad es que esto no es un sue@{F1}o.";
  WakeOther:print "Eso parece innecesario.";
  Wave: switch (n) {
        1:  print "Pero ";
            CSubjectIsnt(actor,true,true); " sosteniendo ", (ThatOrThose) x1, ".";
        2:  CSubjectVerb(actor,false,false,"me veo","te ves","se ve","se vi@{F3}");
            print " rid@{ED}culo agitando ", (the) x1;
            if (x2)
                " hacia ", (the) x2, ".";
            ".";
        3:  DecideAgainst();
    }
  WaveHands:
        CSubjectVerb(actor,false,false,"agito","agitas","agita","agit@{F3}");
        switch (n) {
        1: ! nada
        2: print " hacia ", (the) x1;
        }
        ", sinti@{E9}ndome tonto.";
  Wear: switch (n) {
        1:  CSubjectCant(actor,true); " llevar ", (ThatOrThose) x1, ".";
        2:  CSubjectIs  (actor,true); " no sosteniendo ", (ThatOrThose) x1, ".";
        3:  CSubjectIs  (actor,true); " ya llevando ", (ThatOrThose) x1, ".";
        4:  CSubjectVerb(actor,false,false,"me pongo","te pones","se pone","se puso"); " ", (the) x1, ".";
        5:  CSubjectVerb(actor, false, false, "necesito sacar", "necesitas sacar", "necesita sacar", "necesitaba sacar");
            print " ", (the) x1, " ";
            if (x2 has container)
                print "de";
            else
                print "de";
            " ", (the) x2, " antes de llevarlo.";
    }
! Yes:  ver No.
];

! Funciones auxiliares para concordancia de género
[ o obj;
    if (obj has female) print "a"; else print "o";
];

! ==============================================================================

Constant LIBRARY_SPANISH;       ! para verificación de dependencias.
#Endif;

! ==============================================================================