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

[ LanguageToInformese; 
    ! Función vacía - las contracciones se manejan en LanguageContraction
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

! Función auxiliar para compatibilidad con minúscula

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
! FUNCIONES DE INTERFAZ DE IDIOMA - VERSIÓN SIMPLIFICADA
! ==============================================================================

! Función completa de mensajes del sistema
[ LanguageLM n x1 x2;
    Answer,Ask: "No hay respuesta.";
    Attack:     "La violencia no es la respuesta a esto.";
    Blow:       CSubjectCant(actor,true);
                " soplar @{FA}tilmente ", (ThatOrThose) x1, ".";
    Burn: switch (n) {
        1:  print "Este acto peligroso ";
            Tense("lograr@{ED}a", "habr@{ED}a logrado");
            " poco.";
        2:  DecideAgainst();
    }
    Buy:        print "Nada ";
            Tense("est@{E1}", "estaba");
            " en venta.";
    Climb: switch (n) {
        1:  print "Trepar por ", (ThatOrThose) x1, " ";
            Tense("lograr@{ED}a", "habr@{ED}a logrado");
            " poco.";
        2:  DecideAgainst();
    }
    Close: switch (n) {
        1:  CSubjectIs(x1,true);
            print " no es algo que ", (theActor) actor;
            Tense(" puede cerrar", " podr@{ED}a haber cerrado");
            ".";
        2:  CSubjectIs(x1,true); " ya est@{E1} cerrad", (o) x1, ".";
        3:  CSubjectVerb(actor,false,false,"cierro","cierras","cierra","cerr@{F3}");
            " ", (the) x1, ".";
        4:  "(primero cerrando ", (the) x1, ")";
    }
    CommandsOff: switch (n) {
        1: "[Grabaci@{F3}n de comandos desactivada.]";
        #Ifdef TARGET_GLULX;
        2: "[La grabaci@{F3}n de comandos ya estaba desactivada.]";
        #Endif; ! TARGET_
    }
    CommandsOn: switch (n) {
        1: "[Grabaci@{F3}n de comandos activada.]";
        #Ifdef TARGET_GLULX;
        2: "[Los comandos se est@{E1}n reproduciendo actualmente.]";
        3: "[La grabaci@{F3}n de comandos ya estaba activada.]";
        4: "[La grabaci@{F3}n de comandos fall@{F3}.]";
        #Endif; ! TARGET_
    }
    CommandsRead: switch (n) {
        1: "[Reproduciendo comandos.]";
        #Ifdef TARGET_GLULX;
        2: "[Los comandos ya se est@{E1}n reproduciendo.]";
        3: "[La reproducci@{F3}n de comandos fall@{F3}. La grabaci@{F3}n est@{E1} activa.]";
        4: "[La reproducci@{F3}n de comandos fall@{F3}.]";
        5: "[Reproducci@{F3}n de comandos completada.]";
        #Endif; ! TARGET_
    }
    Consult:  CSubjectVerb(actor,true,false,"descubro","descubres","descubre","descubri@{F3}");
            print " nada interesante en ";
            if (x1 == player) { OnesSelf(x1); ".";}
            else print_ret (the) x1, ".";
    Cut: switch (n) {
        1:  print "Cortar ", (ThatOrThose) x1, " ";
            Tense("lograr@{ED}a", "habr@{ED}a logrado");
            " poco.";
        2:  DecideAgainst();
    }
    Dig:      print "Cavar ";
            Tense("lograr@{ED}a", "habr@{ED}a logrado");
            " nada aqu@{ED}.";
    Disrobe: switch (n) {
        1:  CSubjectIsnt(actor,true); " llevando ", (ThatOrThose) x1, ".";
        2:  CSubjectVerb(actor,false,false,"me quito","te quitas","se quita", "se quit@{F3}");
            " ", (the) x1, ".";
        3:  "(primero quit@{E1}ndose ", (the) x1, ")";
        4: CSubjectVerb(actor,false,false, "necesitar@{E9} quitar", 0, 0, "necesit@{F3} quitar");
           " ", (the) noun, " primero.";
    }
    Drink:    print "No hay";
            Tense("", " hab@{ED}a");
            " nada apropiado para beber aqu@{ED}.";
    Drop: switch (n) {
        1:  CSubjectIs(x1,true); " ya est@{E1} aqu@{ED}.";
        2:  CSubjectVerb(actor, false, false, "no tengo", "no tienes", "no tiene",
                         "no ten@{ED}a");
            " ", (the) x1, ".";
        3:  "Soltad", (o) x1, ".";
        4: CSubjectVerb(actor, false, false, "necesito tomar", "necesitas tomar", "necesita tomar", "necesit@{F3} tomar");
           print " ", (the) x1, " ";
           if (x2 has container)
               print "de";
           else
               print "de encima de";
           " ", (the) x2, " antes de soltar ", (ItOrThem) x1, ".";
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
            Tense(" puede ", " podr@{ED}a ");
            switch (x2) {
              'stand':  "pararse.";
              'sit':    "sentarse.";
              'lie':    "acostarse.";
              default:  "entrar.";
            }
        3:  CSubjectCant(actor,true);
            " entrar en ", (the) x1, " cerrad", (o) x1, ".";
        4:  CSubjectCan(actor,true);
            " s@{F3}lo entrar en algo que est@{E9} libre.";
        5:  CSubjectVerb(actor,false,false,"entro","entras","entra","entr@{F3}");
            SupportObj(x1," en"," en"); " ", (the) x1, ".";
        6:  "(saliendo ", (nop) SupportObj(x1,"de","de"), " ", (the) x1, ")";
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
            " en nada en este momento.";
        2:  CSubjectCant(actor,false);
            " salir de ", (the) x1, " cerrad", (o) x1, ".";
        3:  CSubjectVerb(actor,false,false,"salgo","sales","sale", "sali@{F3}");
            print " ";
            SupportObj(x1,"de","de"); " ", (the) x1, ".";
        4:  CSubjectIsnt(actor,true);
            print " ";
            SupportObj(x1,"en","en"); " ", (the) x1, ".";
        5:  "(primero saliendo ", (nop) SupportObj(x1,"de","de"),
              " ", (the) x1, ")";
        6:  CSubjectVerb(actor,false,false,"me pongo","te pones","se pone","se puso"); " de pie.";
    }
    Fill: switch (n) {
        1:  print "No hay ";
            Tense("", "hab@{ED}a");
            " nada obvio con lo que llenar ", (the) x1, ".";
        2:  print "Llenar ", (the) x1, " desde ", (the) x2, " no ";
            Tense("tendr@{ED}a", "habr@{ED}a tenido");
            " sentido.";
    }
    FullScore: switch (n) {
        1:  if (deadflag) print "La puntuaci@{F3}n fue "; else print "La puntuaci@{F3}n es ";
                "compuesta de la siguiente manera:^";
        2:  "encontrar varios objetos";
        3:  "visitar varios lugares";
        4:  print "total (de ", MAX_SCORE; ")";
    }
    GetOff:   print "Pero ";
            CSubjectIsnt(actor,true,true); " en ", (the) x1, " en este momento.";
    Give: switch (n) {
        1:  CSubjectIsnt(actor,true); " llevando ", (the) x1, ".";
        2:  CSubjectVerb(actor,false,false,"hago malabarismos","haces malabarismos","hace malabarismos","hizo malabarismos");
            print " con ", (the) x1, " un rato, pero ";
            CSubjectVoice(actor,"no logro","no logras","no logra","no logr@{F3}");
            " mucho.";
        3:  CSubjectDont(x1,true); " parecer interesad", (o) x1, ".";
        4:  CSubjectVerb(actor,false,false,"entrego","entregas","entrega","entreg@{F3}");
            " ", (the) x1, ".";
    }
    Go: switch (n) {
        1:  CSubjectWill(actor,true);
            Tense(" tener", " haber tenido");
                " que salir ", (nop) SupportObj(x1,"de","de"), " ", (the) x1, " primero.";
        2:  CSubjectCant(actor,true); " ir por ah@{ED}.";
        3:  CSubjectIs  (actor,true); " incapaz de trepar ", (the) x1, ".";
        4:  CSubjectIs  (actor,true); " incapaz de descender por ", (the) x1, ".";
        5:  CSubjectCant(actor,true); " porque ", (the) x1, " ", (IsOrAre) x1, " en el camino.";
        6:  CSubjectCant(actor,true); " porque ", (the) x1, " ", (nop) PluralObj(x1,"no lleva","no llevan","no llevaba"), " a ninguna parte.";
        7:  CSubjectVerb(actor,false,false,"me voy","te vas","se va","se fue"); ".";
    }
    Insert: switch (n) {
        1:  CSubjectVerb(actor,true,false,"necesito","necesitas","necesita","necesit@{F3}");
            print " estar llevando ", (the) x1, " antes de que ", (theActor) actor;
            Tense(" pueda", " pudiera");
            " meter ", (ItOrThem) x1, " en algo m@{E1}s.";
        2:  CSubjectCant(x1,true); " contener cosas.";
        3:  CSubjectIs  (x1,true); " cerrad", (o) x1, ".";
        4:  CSubjectVerb(actor,true,false,"necesito","necesitas","necesita","necesit@{F3}");
            print " quitar ", (the) x1, " primero.";
        5:  CSubjectCant(actor,true); " meter ", (ThatOrThose) x1, " dentro de s@{ED} mism", (o) x1, ".";
        6:  "(primero quit@{E1}ndose ", (the) x1, ")";
        7:  "No hay m@{E1}s espacio en ", (the) x1, ".";
        8:  "Hecho.";
        9:  CSubjectVerb(actor,false,false,"meto","metes","mete","meti@{F3}");
            " ", (the) x1, " en ", (the) x2, ".";
    }
    Inv: switch (n) {
        1:  CSubjectIs(actor,false); " cargando";
            if (x1 ~= 0) { print " "; WriteListFrom(x1, ENGLISH_BIT); }
            ".";
        2:  CSubjectIs(actor,false); " llevando";
            if (x1 ~= 0) { print " "; WriteListFrom(x1, ENGLISH_BIT); }
            ".";
        3:  CSubjectIs(actor,false); " vac@{ED}", (o) actor, ".";
    }
    Jump: switch (n) {
        1:  CSubjectVerb(actor,false,false,"salto","saltas","salta","salt@{F3}");
            " en el sitio.";
        2:  CSubjectVerb(actor,false,false,"obtengo","obtienes","obtiene","obtuvo");
            " poco saltando.";
        3:  DecideAgainst();
    }
    JumpIn: switch (n) {
        1:  print "Saltar en ", (the) x1, " no ";
            Tense("lograr@{ED}a", "habr@{ED}a logrado");
            " mucho.";
        2:  DecideAgainst();
    }
    JumpOn: switch (n) {
        1:  print "Saltar sobre ", (the) x1, " no ";
            Tense("lograr@{ED}a", "habr@{ED}a logrado");
            " mucho.";
        2:  DecideAgainst();
    }
    JumpOver: switch (n) {
        1:  CSubjectVerb(actor,false,false,"salto","saltas","salta","salt@{F3}");
            " sobre ", (the) x1, ".";
        2:  DecideAgainst();
    }
    Kiss:     "Mant@{E9}n tu mente en el juego.";
    Listen: switch (n) {
        1:  print "No ";
            Tense("escucho", "escuch@{E9}");
            " nada inesperado.";
        2:  print "No ";
            Tense("escucho", "escuch@{E9}");
            " nada particular desde ", (the) x1, ".";
    }
    ListMiscellany: switch (n) {
        1:  print " (iluminand", (o) x1, ")";
        2:  print " (que ", (IsOrAre) x1, " cerrad", (o) x1, ")";
        3:  print " (cerrad", (o) x1, " y bloqueaed", (o) x1, ")";
        4:  print " (que ", (IsOrAre) x1, " vac@{ED}", (o) x1, ")";
        5:  print " (vac@{ED}", (o) x1, " y abierto)";
        6:  print " (que ", (IsOrAre) x1, " abierto)";
        7:  print " (que ", (IsOrAre) x1, " abierto pero vac@{ED}", (o) x1, ")";
        8:  print " (iluminand", (o) x1, " y siendo llevad", (o) x1;
        9:  print " (siendo llevad", (o) x1;
        10: print " (";
        11: print " (en ", (the) x1;
        12: print " (en ", (the) x1;
        13: print " (dentro ", (the) x1;
        14: print " (dentro ", (the) x1;
        15: print " (sobre ", (the) x1;
        16: print " (sobre ", (the) x1;
        17: print " (trabajando)";
        18: print " (que ", (IsOrAre) x1, " cerrad", (o) x1, ")";
    }
    LMode1:   print " est@{E1} ahora en su modo ~breve~, que da descripciones largas";
                " de lugares nunca visitados y descripciones cortas de otros.";
    LMode2:   print " est@{E1} ahora en su modo ~detallado~, que da descripciones largas";
                " de lugares cada vez que los visitas.";
    LMode3:   print " est@{E1} ahora en su modo ~superbreve~, que da descripciones cortas";
                " de lugares cada vez que los visitas.";
    Lock: switch (n) {
        1:  CSubjectDont(x1,true);
            " parecer ser algo que pueda bloquearse.";
        2:  CSubjectIs(x1,true);
            " ya bloqueaed", (o) x1, ".";
        3:  "Primero tendr@{ED}as que cerrar ", (the) x1, ".";
        4:  CSubjectDont(x1,true);
            " parecer encajar en la cerradura.";
        5:  CSubjectVerb(actor,false,false,"bloqueo","bloqueas","bloquea","bloque@{F3}");
            " ", (the) x1, ".";
    }
    Look: switch (n) {
        1:  print " (en ", (the) x1, ")";
        2:  print " (en ", (the) x1, ")";
        3:  print " (como ", (object) x1, ")";
        4:  print "^En ", (the) x1, " ";
            CSubjectVerb(actor,true,false,"veo","ves","ve","vi@{F3}");
            " ";
            if (n == 5) print "tambi@{E9}n ";
            WriteListFrom(x2, ENGLISH_BIT);
            ".";
        5:  "No hay nada encima.";
        6:  print "En ", (the) x1, " ";
            CSubjectVerb(actor,true,false,"veo","ves","ve","vi@{F3}");
            " ";
            if (n == 7) print "tambi@{E9}n ";
            WriteListFrom(x2, ENGLISH_BIT);
            ".";
        7:  "No hay nada dentro.";
    }
    LookUnder: switch (n) {
        1:  print "Pero est@{E1} oscuro.";
        2:  CSubjectVerb(actor,true,false,"encuentro","encuentras","encuentra","encontr@{F3}");
            " nada de inter@{E9}s.";
    }
    Mild:     "Muy apropiado.";
    Miscellany: switch (n) {
        1:  "(considerando los primeros diecis@{E9}is objetos solamente)^";
        2:  "Nada que hacer!";
        3:  print " ";
            CSubjectVerb(player,true,false,"he","has","ha","hab@{ED}a");
            " muerto ";
        4:  print " ";
            CSubjectVerb(player,true,false,"he","has","ha","hab@{ED}a");
            " ganado ";
        5:  print "^@{BF}Te gustar@{ED}a REINICIAR, CARGAR un juego guardado";
            if (TASKS_PROVIDED == 0) print ", dar la PUNTUACI@{D3}N completa";
            if (deadflag == 2 && AMUSING_PROVIDED == 0) print ", ver algunas sugerencias DIVERTIDAS";
            " o SALIR?";
        6:  "[Tu int@{E9}rprete no puede ~deshacer~ acciones.]";
        7:  "~Deshacer~ fall@{F3}. [No todos los int@{E9}rpretes lo proporcionan.]";
        8:  "Por favor, da uno de los comandos anteriores.";
        9:  "^Ha oscurecido.";
        10: "Perd@{F3}n?";
        11: "[No puedes ~deshacer~ algo que no hiciste!]";
        12: "[No puedes ~deshacer~ dos veces seguidas. Perd@{F3}n!]";
        13: "[Acci@{F3}n anterior deshecha.]";
        14: "Perd@{F3}n, eso no puede corregirse.";
        15: "Piensa nada de eso.";
        16: "~Ups~ s@{F3}lo puede corregir una palabra.";
        17: "Est@{E1} demasiado oscuro para ver.";
        18: print (The) x1; " no puede ver nada importante en esa direcci@{F3}n.";
        19: print "Ese no es un verbo que reconozco.";
        20: "Eso es algo que no necesitas referir en este juego.";
        21: "No puedes ver ~", (address) x1, "~ (", (the) x1, ") en este momento.";
        22: "No entendiste esa oraci@{F3}n.";
        23: CSubjectCan(actor,false); " s@{F3}lo hacer eso con algo animado.";
        24: "Eso no es algo que puedas ", (address) x1, ".";
        25: "Eso no es algo que necesites referir en este juego.";
        26: "No puedes ver ~", (address) x1, "~ (", (the) x1, ") en este momento.";
        27: "No entendiste esa oraci@{F3}n.";
        28: print "No puedes ver ~", (address) x1, "~ en este momento.";
        29: "Eso no es algo que puedas ", (address) x1, ".";
        30: "Eso no es algo que necesites referir en este juego.";
        31: "No entendiste esa oraci@{F3}n.";
        32: "No puedes ver ~", (address) x1, "~ en este momento.";
        33: "No entendiste esa oraci@{F3}n.";
        34: "No puedes ver ~", (address) x1, "~ en este momento.";
        35: "No entendiste esa oraci@{F3}n.";
        36: "No puedes ver ~", (address) x1, "~ en este momento.";
        37: "No entendiste esa oraci@{F3}n.";
        38: "No puedes ver ~", (address) x1, "~ en este momento.";
        39: "Eso no es algo que puedas ", (address) x1, ".";
        40: "No puedes ver ~", (address) x1, "~ en este momento.";
        41: "No entendiste esa oraci@{F3}n.";
        42: "No puedes ver ~", (address) x1, "~ en este momento.";
        43: "No entendiste esa oraci@{F3}n.";
        44: "No hay suficientes de esos disponibles.";
        45: "Nada que hacer!";
        46: "Nada que ", (address) x1, "!";
        47: "Eso no es algo que puedas ", (address) x1, ".";
        48: "No puedes referirte a ", (the) x1, " de esa manera.";
        49: "No puedes referirte a ", (the) x1, " de esa manera.";
        50: "No entendiste esa oraci@{F3}n.";
        51: "No est@{E1} disponible.";
        52: print "No ";
            CSubjectVerb(actor,false,false,"tengo","tienes","tiene","ten@{ED}a");
            " nada que hacer.";
        53: CSubjectVerb(actor,false,false,"no puedo","no puedes","no puede","no pudo");
            " ", (address) x1, " ", (the) x2, " a ", (the) x1, ".";
        54: CSubjectVerb(actor,false,false,"no puedo","no puedes","no puede","no pudo");
            " ", (address) x1, " ", (the) x2, " a nadie m@{E1}s.";
        55: CSubjectVerb(actor,false,false,"no puedo","no puedes","no puede","no pudo");
            " ", (address) x1, " ", (the) x2, " con ", (the) x1, ".";
        56: CSubjectVerb(actor,false,false,"no puedo","no puedes","no puede","no pudo");
            " ", (address) x1, " ", (the) x2, " con nada m@{E1}s.";
        57: CSubjectVerb(actor,false,false,"no puedo","no puedes","no puede","no pudo");
            " ", (address) x1, " ", (the) x2, " con ", (the) x1, ".";
        58: "Debo haber entendido mal la oraci@{F3}n.";
        59: "No puedes hacer m@{FA}ltiples acciones con m@{FA}ltiples objetos.";
        60: "No puedes hacer eso a m@{FA}ltiples objetos.";
        61: "No est@{E1} claro a qu@{E9} te refieres.";
        62: "No est@{E1} claro a qu@{E9} te refieres.";
        63: CSubjectIs(actor,false); " llevando demasiadas cosas ya.";
        64: "Nunca has hecho eso.";
        65: "No puedes ", (address) x1, " algo que no est@{E1}s sosteniendo.";
        66: "No puedes ", (address) x1, " eso.";
        67: "No puedes ", (address) x1, " cosas que no est@{E1}n aqu@{ED}.";
        68: "No puedes ", (address) x1, " a personas.";
        69: "No puedes ", (address) x1, " el ", (name) x1, ".";
        70: "No est@{E1} claro qu@{E9} quieres que ", (the) x1, " haga.";
        71: "No puedes ", (address) x1, " ", (the) x1, " a ", (OnesSelf) x1, ".";
        72: "No puedes ", (address) x1, " ", (the) x1, " a nadie m@{E1}s.";
        73: "No puedes ", (address) x1, " ", (the) x1, " con ", (OnesSelf) x1, ".";
        74: "No puedes ", (address) x1, " ", (the) x1, " con nada m@{E1}s.";
        75: "No puedes ", (address) x1, " ", (the) x1, " con ", (the) x1, ".";
        76: "(Primero tomando ", (the) x1, ")";
        77: "No funciona.";
        78: "No puedes ", (address) x1, " lo que no est@{E1} abierto.";
        79: CSubjectIs(x1,false); " claramente no comestible.";
        80: "No puedes ", (address) x1, " lo que est@{E1} cerrado.";
        81: CSubjectIs(x1,false); " no muy apetitoso.";
        82: "No puedes ", (address) x1, " personas.";
        83: "No puedes ", (address) x1, " eso.";
        84: "Eso ya est@{E1} en ", (the) x1, ".";
        85: "No puedes ", (address) x1, " ", (the) x1, " dentro de ", (OnesSelf) x1, ".";
        86: "No puedes ", (address) x1, " ", (the) x1, " dentro de ", (the) x1, ".";
        87: "No puedes ", (address) x1, " personas.";
        88: "No puedes ", (address) x1, " eso.";
        89: "Eso ya est@{E1} en ", (the) x1, ".";
        90: "No puedes ", (address) x1, " ", (the) x1, " sobre ", (OnesSelf) x1, ".";
        91: "No puedes ", (address) x1, " ", (the) x1, " sobre ", (the) x1, ".";
        92: "No puedes ", (address) x1, " lo que no est@{E1}s sosteniendo.";
        93: "No puedes ", (address) x1, " eso.";
        94: "Eso ya est@{E1} aqu@{ED}.";
        95: "No puedes ", (address) x1, " ", (the) x1, " sobre ", (OnesSelf) x1, ".";
        96: "No puedes ", (address) x1, " ", (the) x1, " sobre ", (the) x1, ".";
        97: "No puedes ", (address) x1, " personas.";
        98: "No puedes ", (address) x1, " eso.";
        99: "Eso ya est@{E1} aqu@{ED}.";
        100: "No puedes ", (address) x1, " ", (the) x1, " de ", (OnesSelf) x1, ".";
        101: "No puedes ", (address) x1, " ", (the) x1, " de ", (the) x1, ".";
        102: "No puedes ", (address) x1, " personas.";
        103: "No puedes ", (address) x1, " eso.";
        104: "Eso ya est@{E1} aqu@{ED}.";
        105: "No puedes ", (address) x1, " ", (the) x1, " de ", (OnesSelf) x1, ".";
        106: "No puedes ", (address) x1, " ", (the) x1, " de ", (the) x1, ".";
        107: "No puedes ", (address) x1, " personas.";
        108: "No puedes ", (address) x1, " eso.";
        109: "Eso ya est@{E1} aqu@{ED}.";
        110: "No puedes ", (address) x1, " ", (the) x1, " de ", (OnesSelf) x1, ".";
        111: "No puedes ", (address) x1, " ", (the) x1, " de ", (the) x1, ".";
        112: "No puedes ", (address) x1, " personas.";
        113: "No puedes ", (address) x1, " eso.";
        114: "Eso ya est@{E1} aqu@{ED}.";
        115: "No puedes ", (address) x1, " ", (the) x1, " de ", (OnesSelf) x1, ".";
        116: "No puedes ", (address) x1, " ", (the) x1, " de ", (the) x1, ".";
        117: "No puedes ", (address) x1, " personas.";
        118: "No puedes ", (address) x1, " eso.";
        119: "Eso ya est@{E1} aqu@{ED}.";
        120: "No puedes ", (address) x1, " ", (the) x1, " de ", (OnesSelf) x1, ".";
        121: "No puedes ", (address) x1, " ", (the) x1, " de ", (the) x1, ".";
        122: "No puedes ", (address) x1, " personas.";
        123: "No puedes ", (address) x1, " eso.";
        124: "Eso ya est@{E1} aqu@{ED}.";
        125: "No puedes ", (address) x1, " ", (the) x1, " de ", (OnesSelf) x1, ".";
        126: "No puedes ", (address) x1, " ", (the) x1, " de ", (the) x1, ".";
        127: "No puedes ", (address) x1, " personas.";
        128: "No puedes ", (address) x1, " eso.";
        129: "Eso ya est@{E1} aqu@{ED}.";
        130: "No puedes ", (address) x1, " ", (the) x1, " de ", (OnesSelf) x1, ".";
        131: "No puedes ", (address) x1, " ", (the) x1, " de ", (the) x1, ".";
        132: "No puedes ", (address) x1, " personas.";
        133: "No puedes ", (address) x1, " eso.";
        134: "Eso ya est@{E1} aqu@{ED}.";
        135: "No puedes ", (address) x1, " ", (the) x1, " de ", (OnesSelf) x1, ".";
        136: "No puedes ", (address) x1, " ", (the) x1, " de ", (the) x1, ".";
        137: "No puedes ", (address) x1, " personas.";
        138: "No puedes ", (address) x1, " eso.";
        139: "Eso ya est@{E1} aqu@{ED}.";
        140: "No puedes ", (address) x1, " ", (the) x1, " de ", (OnesSelf) x1, ".";
        141: "No puedes ", (address) x1, " ", (the) x1, " de ", (the) x1, ".";
        142: "No puedes ", (address) x1, " personas.";
        143: "No puedes ", (address) x1, " eso.";
        144: "Eso ya est@{E1} aqu@{ED}.";
        145: "No puedes ", (address) x1, " ", (the) x1, " de ", (OnesSelf) x1, ".";
        146: "No puedes ", (address) x1, " ", (the) x1, " de ", (the) x1, ".";
        147: "No puedes ", (address) x1, " personas.";
        148: "No puedes ", (address) x1, " eso.";
        149: "Eso ya est@{E1} aqu@{ED}.";
        150: "No puedes ", (address) x1, " ", (the) x1, " de ", (OnesSelf) x1, ".";
        151: "No puedes ", (address) x1, " ", (the) x1, " de ", (the) x1, ".";
        152: "No puedes ", (address) x1, " personas.";
        153: "No puedes ", (address) x1, " eso.";
        154: "Eso ya est@{E1} aqu@{ED}.";
        155: "No puedes ", (address) x1, " ", (the) x1, " de ", (OnesSelf) x1, ".";
        156: "No puedes ", (address) x1, " ", (the) x1, " de ", (the) x1, ".";
    }
    Take: switch (n) {
        1:  "Tomad", (o) x1, ".";
        2:  CSubjectIs(actor,true); " siempre ", (nop) OnesSelf(actor), ".";
        3:  "No puedes tomar ", (the) x1, ".";
        4:  CSubjectVerb(actor,true,false,"tendr@{ED}a","tendr@{ED}as","tendr@{ED}a","habr@{ED}a tenido");
            " que salir ", (nop) SupportObj(x1,"de","de"), " ", (the) x1, " primero.";
        5:  CSubjectVerb(actor,true,false,"ya tengo","ya tienes","ya tiene","ya ten@{ED}a");
            " ", (the) x1, ".";
        6:  CSubjectIs(noun,true); " perteneciente a ", (the) x1, ".";
        7:  CSubjectIs(noun,true); " parte de ", (the) x1, ".";
        8:  CSubjectIs(x1,true); " no disponible.";
        9:  CSubjectIs(x1,true); " no abierto.";
        10: CSubjectIs(x1,true); " difícilmente portátil.";
        11: CSubjectIs(x1,true); " fijo en el lugar.";
        12: CSubjectIs(actor,true); " llevando demasiadas cosas ya.";
        13: "(poniendo ", (the) x1, " en ", (the) x2, " para hacer espacio)";
    }
    Taste:    CSubjectVerb(actor,true,false,"pruebo","pruebas","prueba","prob@{F3}");
            " nada inesperado.";
    Tell: switch (n) {
        1:  CSubjectVerb(actor,false,false,"hablo","hablas","habla","habl@{F3}");
            " con ", (OnesSelf) actor, " un rato.";
        2:  print "Esto no ";
            Tense("provoca", "provoc@{F3}");
            " reacci@{F3}n.";
    }
    Think:    "Qu@{E9} buena idea.";
    ThrowAt: switch (n) {
        1:  "F@{FA}til.";
        2:  CSubjectVerb(actor,false,false,"no tengo","no tienes","no tiene","no ten@{ED}a");
            " ", (the) x1, " cuando ", (nop) Tense("necesito", "necesit@{F3}");
            " ", (ItOrThem) x1, ".";
    }
    Tie:  CSubjectVerb(actor,true,false,"no lograr@{ED}a","no lograr@{ED}as","no lograr@{ED}a","no habr@{ED}a logrado");
        " nada haciendo eso.";
    Touch: switch (n) {
        1:  DecideAgainst();
        2:  CSubjectVerb(actor,true,false,"no siento","no sientes","no siente","no sinti@{F3}");
            " nada inesperado.";
        3:  CSubjectVerb(actor,true,false,"no puedo","no puedes","no puede","no pudo");
            " hacer eso.";
    }
    Turn: switch (n) {
        1:  CSubjectIs(x1,true);
            " fijo en el lugar.";
        2:  CSubjectVerb(actor,true,false,"no puedo","no puedes","no puede","no pudo");
            " girar eso.";
        3:  "Nada obvio pasa.";
        4:  CSubjectVerb(actor,false,false,"giro","giras","gira","gir@{F3}");
            " ", (the) x1, ".";
    }
    Wait:     "Pasa el tiempo.";
    WakeOther:"Eso no parece necesario.";
    Wake:     "El hecho terrible es que no está", (s) actor, " dormido.";
    WaveHands:"^";
    Wave: switch (n) {
        1:  print "Pero no ";
            CSubjectVerb(actor,false,false,"tengo","tienes","tiene","ten@{ED}a");
            " ", (the) x1, ".";
        2:  CSubjectVerb(actor,false,false,"me veo","te ves","se ve","se vi@{F3}");
            " ridícul", (o) actor, " agitando ", (the) x1, ".";
    }
    Wear: switch (n) {
        1:  CSubjectCant(actor,true); " usar ", (ThatOrThose) x1, "!";
        2:  CSubjectIs(actor,true); " no sosteniendo ", (ThatOrThose) x1, "!";
        3:  CSubjectIs(actor,true); " ya usando ", (ThatOrThose) x1, "!";
        4:  CSubjectVerb(actor,false,false,"me pongo","te pones","se pone","se puso");
            " ", (the) x1, ".";
    }
    ! MENSAJES CRÍTICOS PARA FUNCIONALIDAD BÁSICA
    
    ! Mensajes de lista y objetos visibles
    ListMiscellany: switch (n) {
        1:  print " (iluminand", (o) x1, ")";
        2:  print " (que ", (IsOrAre) x1, " cerrad", (o) x1, ")";
        3:  print " (cerrad", (o) x1, " y bloqueaed", (o) x1, ")";
        4:  print " (que ", (IsOrAre) x1, " vac@{ED}", (o) x1, ")";
        5:  print " (vac@{ED}", (o) x1, " y abierto)";
        6:  print " (que ", (IsOrAre) x1, " abierto)";
        7:  print " (que ", (IsOrAre) x1, " abierto pero vac@{ED}", (o) x1, ")";
        8:  print " (iluminand", (o) x1, " y siendo llevad", (o) x1;
        9:  print " (siendo llevad", (o) x1;
        10: print " (";
        11: print " (en ", (the) x1;
        12: print " (en ", (the) x1;
        13: print " (dentro ", (the) x1;
        14: print " (dentro ", (the) x1;
        15: print " (sobre ", (the) x1;
        16: print " (sobre ", (the) x1;
        17: print " (trabajando)";
        18: print " (que ", (IsOrAre) x1, " cerrad", (o) x1, ")";
    }
    
    default: print "[Mensaje ", action, ":", n, " no implementado]";
];

! Funciones auxiliares simplificadas para evitar errores de runtime
[ o obj; obj = obj; print "o"; ];  ! Usar terminación masculina por defecto
[ s obj; obj = obj; print ""; ];   ! Sin plurales complejos por ahora  
[ es obj; obj = obj; print "es"; ]; ! Usar singular por defecto
[ esta obj; obj = obj; print "est@{E1}"; ]; ! Usar singular por defecto

! LanguageDirection función duplicada eliminada - usar la del inicio del archivo

! LanguageNumber función duplicada eliminada - usar la del inicio del archivo

! LanguageContraction función duplicada eliminada - usar la del inicio del archivo

! ==============================================================================

Constant LIBRARY_SPANISH;       ! para verificación de dependencias.
#Endif;

! ==============================================================================