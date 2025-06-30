! ==============================================================================
!   SPANISH:  Language Definition File
!
!   Basado en la librería Inform 6 -- Release 6.12.7 -- Serial number 240410
!
!   Copyright Graham Nelson 1993-2004 and David Griffith 2012-2024
!   Adaptación al español por Francisco Fuentes, 2025
!
!   This code is licensed under either the traditional Inform license as
!   described by the DM4 or the Artistic License version 2.0.  See the
!   file COPYING in the distribution archive.
!
!   Este archivo es incluido automáticamente en tu juego por "parserm".
!   Estrictamente, "parserm" incluye el archivo nombrado en la variable "language__",
!   cuyo contenido puede ser definido por el ajuste del compilador +language_name=XXX
!   (con un valor predeterminado de "english").
!
! ==============================================================================

System_file;

#Ifndef LIBRARY_SPANISH;	! if this file is already included,
				! don't try to include it again.

! ------------------------------------------------------------------------------
!   Part I.   Preliminaries
! ------------------------------------------------------------------------------

Constant SpanishNaturalLanguage;    ! Needed to keep old pronouns mechanism

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
CompassDirection -> s_obj  with short_name "sur",     door_dir s_to,
                                name 's//' 'sur';
CompassDirection -> e_obj  with short_name "este",      door_dir e_to,
                                name 'e//' 'este';
CompassDirection -> w_obj  with short_name "oeste",      door_dir w_to,
                                name 'o//' 'oeste';
CompassDirection -> ne_obj with short_name "noreste", door_dir ne_to,
                                name 'ne'  'noreste';
CompassDirection -> nw_obj with short_name "noroeste", door_dir nw_to,
                                name 'no'  'noroeste';
CompassDirection -> se_obj with short_name "sureste", door_dir se_to,
                                name 'se'  'sureste';
CompassDirection -> sw_obj with short_name "suroeste", door_dir sw_to,
                                name 'so'  'suroeste';
CompassDirection -> u_obj  with short_name "arriba",  door_dir u_to,
                                name 'arr' 'arriba' 'techo' 'cielo';
CompassDirection -> d_obj  with short_name "suelo",    door_dir d_to,
                                name 'ab' 'abajo' 'suelo' 'tierra';
#Endif; ! WITHOUT_DIRECTIONS

CompassDirection -> in_obj  with short_name "dentro",  door_dir in_to;
CompassDirection -> out_obj with short_name "fuera", door_dir out_to;

! ------------------------------------------------------------------------------
!   Part II.   Vocabulary
! ------------------------------------------------------------------------------

Constant AGAIN1__WD     = 'repetir';
Constant AGAIN2__WD     = 'r//';
Constant AGAIN3__WD     = 'otra';
Constant OOPS1__WD      = 'uy';
Constant OOPS2__WD      = 'u//';
Constant OOPS3__WD      = 'ups';
Constant UNDO1__WD      = 'deshacer';
Constant UNDO2__WD      = 'anular';
Constant UNDO3__WD      = 'undo';

Constant ALL1__WD       = 'todo';
Constant ALL2__WD       = 'todos';
Constant ALL3__WD       = 'todas';
Constant ALL4__WD       = 'cada';
Constant ALL5__WD       = 'ambos';
Constant AND1__WD       = 'y//';
Constant AND2__WD       = 'y//';
Constant AND3__WD       = 'e//';
Constant BUT1__WD       = 'pero';
Constant BUT2__WD       = 'excepto';
Constant BUT3__WD       = 'salvo';
Constant ME1__WD        = 'me';
Constant ME2__WD        = 'yo';
Constant ME3__WD        = 'mi';
Constant OF1__WD        = 'de';
Constant OF2__WD        = 'del';
Constant OF3__WD        = 'de';
Constant OF4__WD        = 'del';
Constant OTHER1__WD     = 'otro';
Constant OTHER2__WD     = 'otra';
Constant OTHER3__WD     = 'otros';
Constant THEN1__WD      = 'entonces';
Constant THEN2__WD      = 'luego';
Constant THEN3__WD      = 'despues';

Constant NO1__WD        = 'n//';
Constant NO2__WD        = 'no';
Constant NO3__WD        = 'no';
Constant YES1__WD       = 's//';
Constant YES2__WD       = 'si';
Constant YES3__WD       = 'afirmativo';

Constant AMUSING__WD    = 'curiosidades';
Constant FULLSCORE1__WD = 'puntuacion';
Constant FULLSCORE2__WD = 'completa';
Constant QUIT1__WD      = 'q//';
Constant QUIT2__WD      = 'terminar';
Constant RESTART__WD    = 'reiniciar';
Constant RESTORE__WD    = 'recuperar';

Array LanguagePronouns table

  ! word        possible GNAs                   connected
  !             to follow:                      to:
  !             a     i
  !             s  p  s  p
  !             mfnmfnmfnmfn

    'lo'      $$100000100000                    NULL
    'la'      $$010000010000                    NULL
    'le'      $$110000110000                    NULL
    'los'     $$100000100000                    NULL
    'las'     $$010000010000                    NULL
    'les'     $$110000110000                    NULL
    'ello'    $$001000001000                    NULL
    'ellos'   $$100000100000                    NULL
    'ellas'   $$010000010000                    NULL;

Array LanguageDescriptors table

  ! word        possible GNAs   descriptor      connected
  !             to follow:      type:           to:
  !             a     i
  !             s  p  s  p
  !             mfnmfnmfnmfn

    'mi'      $$111111111111    POSSESS_PK      0
    'mis'     $$000111000111    POSSESS_PK      0
    'este'    $$100000100000    POSSESS_PK      0
    'esta'    $$010000010000    POSSESS_PK      0
    'estos'   $$100000100000    POSSESS_PK      0
    'estas'   $$010000010000    POSSESS_PK      0
    'ese'     $$100000100000    POSSESS_PK      1
    'esa'     $$010000010000    POSSESS_PK      1
    'esos'    $$100000100000    POSSESS_PK      1
    'esas'    $$010000010000    POSSESS_PK      1
    'su'      $$111111111111    POSSESS_PK      'le'
    'sus'     $$111111111111    POSSESS_PK      'les'
    'el'      $$100000100000    DEFART_PK       NULL
    'la'      $$010000010000    DEFART_PK       NULL
    'los'     $$100000100000    DEFART_PK       NULL
    'las'     $$010000010000    DEFART_PK       NULL
    'un'      $$100000100000    INDEFART_PK     NULL
    'una'     $$010000010000    INDEFART_PK     NULL
    'unos'    $$100000100000    INDEFART_PK     NULL
    'unas'    $$010000010000    INDEFART_PK     NULL
    'algun'   $$100000100000    INDEFART_PK     NULL
    'alguna'  $$010000010000    INDEFART_PK     NULL
    'algunos' $$100000100000    INDEFART_PK     NULL
    'algunas' $$010000010000    INDEFART_PK     NULL
    'encendido' $$100000100000  light           NULL
    'encendida' $$010000010000  light           NULL
    'apagado'   $$100000100000  (-light)        NULL
    'apagada'   $$010000010000  (-light)        NULL;

Array LanguageNumbers table
    'uno' 1 'dos' 2 'tres' 3 'cuatro' 4 'cinco' 5
    'seis' 6 'siete' 7 'ocho' 8 'nueve' 9 'diez' 10
    'once' 11 'doce' 12 'trece' 13 'catorce' 14 'quince' 15
    'dieciseis' 16 'diecisiete' 17 'dieciocho' 18 'diecinueve' 19 'veinte' 20;

! ------------------------------------------------------------------------------
!   Part III.   Translation
! ------------------------------------------------------------------------------

[ LanguageToInformese;
];

! ------------------------------------------------------------------------------
!   Part IV.   Printing
! ------------------------------------------------------------------------------

Constant LanguageAnimateGender   = male;
Constant LanguageInanimateGender = neuter;

Constant LanguageContractionForms = 2;     ! Spanish has two:
                                           ! 0 = masculine
                                           ! 1 = feminine

[ LanguageContraction text;
    if (text->0 == 'a' or 'e' or 'i' or 'o' or 'u'
                or 'A' or 'E' or 'I' or 'O' or 'U') return 1;
    return 0;
];

Array LanguageArticles -->

 !   Contraction form 0:     Contraction form 1:
 !   Cdef   Def    Indef     Cdef   Def    Indef

     "El " "el " "un "      "La " "la " "una "          ! Articles 0
     "Los " "los " "unos "   "Las " "las " "unas ";       ! Articles 1

                   !             a           i
                   !             s     p     s     p
                   !             m f n m f n m f n m f n

Array LanguageGNAsToArticles --> 0 1 0 0 1 0 0 1 0 0 1 0;

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
      in_to:   print "dentro";
      out_to:  print "fuera";
      default: return RunTimeError(9,d);
    }
];

[ LanguageNumber n f;
    if (n == 0)    { print "cero"; rfalse; }
    if (n < 0)     { print "menos "; n = -n; }
    if (n >= 1000) { print (LanguageNumber) n/1000, " mil"; n = n%1000; f = 1; }
    if (n >= 100)  {
        if (f == 1) print " ";
        switch (n/100) {
          1: print "cien";
          2: print "doscientos";
          3: print "trescientos";
          4: print "cuatrocientos";
          5: print "quinientos";
          6: print "seiscientos";
          7: print "setecientos";
          8: print "ochocientos";
          9: print "novecientos";
        }
        n = n%100;
        if (n ~= 0) {
            if (n < 10) print "to "; else print " ";
        }
        f = 1;
    }
    if (n == 0) rfalse;
    
    if (f == 1) print " ";
    
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
      16:   print "dieciséis";
      17:   print "diecisiete";
      18:   print "dieciocho";
      19:   print "diecinueve";
      20:   print "veinte";
      21:   print "veintiuno";
      22:   print "veintidós";
      23:   print "veintitrés";
      24:   print "veinticuatro";
      25:   print "veinticinco";
      26:   print "veintiséis";
      27:   print "veintisiete";
      28:   print "veintiocho";
      29:   print "veintinueve";
      30 to 99: switch (n/10) {
        3:  print "treinta";
        4:  print "cuarenta";
        5:  print "cincuenta";
        6:  print "sesenta";
        7:  print "setenta";
        8:  print "ochenta";
        9:  print "noventa";
        }
        if (n%10 ~= 0) print " y ", (LanguageNumber) n%10;
    }
];

[ LanguageTimeOfDay hours mins i;
    i = hours%12;
    if (i == 0) i = 12;
    if (i < 10) print " ";
    print i, ":", mins/10, mins%10;
    if ((hours/12) > 0) print " pm"; else print " am";
];

[ LanguageVerb i;
    switch (i) {
      'i//','inv','inventario':
               print "hacer inventario";
      'l//':   print "mirar";
      'x//':   print "examinar";
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
!  LanguageVerbIsDebugging is called by SearchScope.  It should return true
!  if word w is a debugging verb which needs all objects to be in scope.
! ----------------------------------------------------------------------------

#Ifdef DEBUG;
[ LanguageVerbIsDebugging w;
    if (w == 'purloin' or 'tree' or 'abstract'
                       or 'gonear' or 'scope' or 'showobj')
        rtrue;
    rfalse;
];
#Endif;

! ----------------------------------------------------------------------------
!  LanguageVerbLikesAdverb is called by PrintCommand when printing an UPTO_PE
!  error or an inference message.  Words which are intransitive verbs, i.e.,
!  which require a direction name as an adverb ('walk west'), not a noun
!  ('I only understood you as far as wanting to touch /the/ ground'), should
!  cause the routine to return true.
! ----------------------------------------------------------------------------

[ LanguageVerbLikesAdverb w;
    if (w == 'mirar' or 'ir' or 'correr' or 'salir' or 'l//' or 'empujar' or 'caminar')
        rtrue;
    rfalse;
];

! ----------------------------------------------------------------------------
!  LanguageVerbMayBeName is called by NounDomain when dealing with the
!  player's reply to a "Which do you mean, the short stick or the long
!  stick?" prompt from the parser. If the reply is another verb (for example,
!  LOOK) then then previous ambiguous command is discarded /unless/
!  it is one of these words which could be both a verb /and/ an
!  adjective in a 'name' property.
! ----------------------------------------------------------------------------

[ LanguageVerbMayBeName w;
    if (w == 'largo' or 'corto' or 'normal'
                    or 'breve' or 'completo' or 'detallado')
        rtrue;
    rfalse;
];

Constant NKEY__TX       = "N = siguiente tema";
Constant PKEY__TX       = "P = anterior";
Constant QKEY1__TX      = "  Q = continuar juego";
Constant QKEY2__TX      = "Q = menú anterior";
Constant RKEY__TX       = "RETURN = leer tema";

Constant NKEY1__KY      = 'N';
Constant NKEY2__KY      = 'n';
Constant PKEY1__KY      = 'P';
Constant PKEY2__KY      = 'p';
Constant QKEY1__KY      = 'Q';
Constant QKEY2__KY      = 'q';

Constant SCORE__TX      = "Puntuación: ";
Constant MOVES__TX      = "Turnos: ";
Constant TIME__TX       = "Hora: ";
Constant SCORE_S__TX    = "P: ";
Constant MOVES_S__TX    = "T: ";
Constant TIME_S__TX     = "H: ";
Constant CANTGO__TX     = "No puedes ir por ahí.";
Constant FORMER__TX     = "tu antiguo yo";
Constant MYFORMER__TX   = "mi antiguo yo";
Constant YOURSELF__TX   = "ti mismo";
Constant MYSELF__TX     = "mí mismo";
Constant YOU__TX        = "Tú";
Constant DARKNESS__TX   = "Oscuridad";

Constant THOSET__TX     = "esas cosas";
Constant THAT__TX       = "eso";
Constant OR__TX         = " o ";
Constant NOTHING__TX    = "nada";
Constant IS__TX         = " es";
Constant ARE__TX        = " son";
Constant IS2__TX        = "es ";
Constant ARE2__TX       = "son ";
Constant IS3__TX        = "es";
Constant ARE3__TX       = "son";
Constant IS4__TX        = "está";
Constant ARE4__TX       = "están";
Constant IS5__TX        = "está ";
Constant ARE5__TX       = "están ";
Constant WHOM__TX       = "quien";

! Nuevas constantes para español
Constant PARTICULA_TE   = "te";
Constant PARTICULA_ME   = "me";
Constant PARTICULA_SE   = "se";
Constant PARTICULA_NOS  = "nos";
Constant PARTICULA_OS   = "os";
Constant PARTICULA_LES  = "les";

! ------------------------------------------------------------------------------
!   Part V.   Grammar
! ------------------------------------------------------------------------------

[ LanguageInitialise;
    LanguageVerb = 'verb';
    LanguageGNAsToArticles-->0 = 0;
    LanguageGNAsToArticles-->3 = 1;
];

! ------------------------------------------------------------------------------

Constant LIBRARY_SPANISH;      ! for dependency checking.

#Endif;

! ==============================================================================! ==============================================================================
!   SPANISH:  Language Definition File
!
!   Basado en la librería Inform 6 -- Release 6.12.7 -- Serial number 240410
!
!   Copyright Graham Nelson 1993-2004 and David Griffith 2012-2024
!   Adaptación al español por Francisco Fuentes, 2025
!
!   This code is licensed under either the traditional Inform license as
!   described by the DM4 or the Artistic License version 2.0.  See the
!   file COPYING in the distribution archive.
!
!   Este archivo es incluido automáticamente en tu juego por "parserm".
!   Estrictamente, "parserm" incluye el archivo nombrado en la variable "language__",
!   cuyo contenido puede ser definido por el ajuste del compilador +language_name=XXX
!   (con un valor predeterminado de "english").
!
! ==============================================================================

System_file;

#Ifndef LIBRARY_SPANISH;	! if this file is already included,
				! don't try to include it again.

! ------------------------------------------------------------------------------
!   Part I.   Preliminaries
! ------------------------------------------------------------------------------

Constant SpanishNaturalLanguage;    ! Needed to keep old pronouns mechanism

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
CompassDirection -> s_obj  with short_name "sur",     door_dir s_to,
                                name 's//' 'sur';
CompassDirection -> e_obj  with short_name "este",      door_dir e_to,
                                name 'e//' 'este';
CompassDirection -> w_obj  with short_name "oeste",      door_dir w_to,
                                name 'o//' 'oeste';
CompassDirection -> ne_obj with short_name "noreste", door_dir ne_to,
                                name 'ne'  'noreste';
CompassDirection -> nw_obj with short_name "noroeste", door_dir nw_to,
                                name 'no'  'noroeste';
CompassDirection -> se_obj with short_name "sureste", door_dir se_to,
                                name 'se'  'sureste';
CompassDirection -> sw_obj with short_name "suroeste", door_dir sw_to,
                                name 'so'  'suroeste';
CompassDirection -> u_obj  with short_name "arriba",  door_dir u_to,
                                name 'arr' 'arriba' 'techo' 'cielo';
CompassDirection -> d_obj  with short_name "suelo",    door_dir d_to,
                                name 'ab' 'abajo' 'suelo' 'tierra';
#Endif; ! WITHOUT_DIRECTIONS

CompassDirection -> in_obj  with short_name "dentro",  door_dir in_to;
CompassDirection -> out_obj with short_name "fuera", door_dir out_to;

! ------------------------------------------------------------------------------
!   Part II.   Vocabulary
! ------------------------------------------------------------------------------

Constant AGAIN1__WD     = 'repetir';
Constant AGAIN2__WD     = 'r//';
Constant AGAIN3__WD     = 'otra';
Constant OOPS1__WD      = 'uy';
Constant OOPS2__WD      = 'u//';
Constant OOPS3__WD      = 'ups';
Constant UNDO1__WD      = 'deshacer';
Constant UNDO2__WD      = 'anular';
Constant UNDO3__WD      = 'undo';

Constant ALL1__WD       = 'todo';
Constant ALL2__WD       = 'todos';
Constant ALL3__WD       = 'todas';
Constant ALL4__WD       = 'cada';
Constant ALL5__WD       = 'ambos';
Constant AND1__WD       = 'y//';
Constant AND2__WD       = 'y//';
Constant AND3__WD       = 'e//';
Constant BUT1__WD       = 'pero';
Constant BUT2__WD       = 'excepto';
Constant BUT3__WD       = 'salvo';
Constant ME1__WD        = 'me';
Constant ME2__WD        = 'yo';
Constant ME3__WD        = 'mi';
Constant OF1__WD        = 'de';
Constant OF2__WD        = 'del';
Constant OF3__WD        = 'de';
Constant OF4__WD        = 'del';
Constant OTHER1__WD     = 'otro';
Constant OTHER2__WD     = 'otra';
Constant OTHER3__WD     = 'otros';
Constant THEN1__WD      = 'entonces';
Constant THEN2__WD      = 'luego';
Constant THEN3__WD      = 'despues';

Constant NO1__WD        = 'n//';
Constant NO2__WD        = 'no';
Constant NO3__WD        = 'no';
Constant YES1__WD       = 's//';
Constant YES2__WD       = 'si';
Constant YES3__WD       = 'afirmativo';

Constant AMUSING__WD    = 'curiosidades';
Constant FULLSCORE1__WD = 'puntuacion';
Constant FULLSCORE2__WD = 'completa';
Constant QUIT1__WD      = 'q//';
Constant QUIT2__WD      = 'terminar';
Constant RESTART__WD    = 'reiniciar';
Constant RESTORE__WD    = 'recuperar';

Array LanguagePronouns table

  ! word        possible GNAs                   connected
  !             to follow:                      to:
  !             a     i
  !             s  p  s  p
  !             mfnmfnmfnmfn

    'lo'      $$100000100000                    NULL
    'la'      $$010000010000                    NULL
    'le'      $$110000110000                    NULL
    'los'     $$100000100000                    NULL
    'las'     $$010000010000                    NULL
    'les'     $$110000110000                    NULL
    'ello'    $$001000001000                    NULL
    'ellos'   $$100000100000                    NULL
    'ellas'   $$010000010000                    NULL;

Array LanguageDescriptors table

  ! word        possible GNAs   descriptor      connected
  !             to follow:      type:           to:
  !             a     i
  !             s  p  s  p
  !             mfnmfnmfnmfn

    'mi'      $$111111111111    POSSESS_PK      0
    'mis'     $$000111000111    POSSESS_PK      0
    'este'    $$100000100000    POSSESS_PK      0
    'esta'    $$010000010000    POSSESS_PK      0
    'estos'   $$100000100000    POSSESS_PK      0
    'estas'   $$010000010000    POSSESS_PK      0
    'ese'     $$100000100000    POSSESS_PK      1
    'esa'     $$010000010000    POSSESS_PK      1
    'esos'    $$100000100000    POSSESS_PK      1
    'esas'    $$010000010000    POSSESS_PK      1
    'su'      $$111111111111    POSSESS_PK      'le'
    'sus'     $$111111111111    POSSESS_PK      'les'
    'el'      $$100000100000    DEFART_PK       NULL
    'la'      $$010000010000    DEFART_PK       NULL
    'los'     $$100000100000    DEFART_PK       NULL
    'las'     $$010000010000    DEFART_PK       NULL
    'un'      $$100000100000    INDEFART_PK     NULL
    'una'     $$010000010000    INDEFART_PK     NULL
    'unos'    $$100000100000    INDEFART_PK     NULL
    'unas'    $$010000010000    INDEFART_PK     NULL
    'algun'   $$100000100000    INDEFART_PK     NULL
    'alguna'  $$010000010000    INDEFART_PK     NULL
    'algunos' $$100000100000    INDEFART_PK     NULL
    'algunas' $$010000010000    INDEFART_PK     NULL
    'encendido' $$100000100000  light           NULL
    'encendida' $$010000010000  light           NULL
    'apagado'   $$100000100000  (-light)        NULL
    'apagada'   $$010000010000  (-light)        NULL;

Array LanguageNumbers table
    'uno' 1 'dos' 2 'tres' 3 'cuatro' 4 'cinco' 5
    'seis' 6 'siete' 7 'ocho' 8 'nueve' 9 'diez' 10
    'once' 11 'doce' 12 'trece' 13 'catorce' 14 'quince' 15
    'dieciseis' 16 'diecisiete' 17 'dieciocho' 18 'diecinueve' 19 'veinte' 20;

! ------------------------------------------------------------------------------
!   Part III.   Translation
! ------------------------------------------------------------------------------

[ LanguageToInformese;
];

! ------------------------------------------------------------------------------
!   Part IV.   Printing
! ------------------------------------------------------------------------------

Constant LanguageAnimateGender   = male;
Constant LanguageInanimateGender = neuter;

Constant LanguageContractionForms = 2;     ! Spanish has two:
                                           ! 0 = masculine
                                           ! 1 = feminine

[ LanguageContraction text;
    if (text->0 == 'a' or 'e' or 'i' or 'o' or 'u'
                or 'A' or 'E' or 'I' or 'O' or 'U') return 1;
    return 0;
];

Array LanguageArticles -->

 !   Contraction form 0:     Contraction form 1:
 !   Cdef   Def    Indef     Cdef   Def    Indef

     "El " "el " "un "      "La " "la " "una "          ! Articles 0
     "Los " "los " "unos "   "Las " "las " "unas ";       ! Articles 1

                   !             a           i
                   !             s     p     s     p
                   !             m f n m f n m f n m f n

Array LanguageGNAsToArticles --> 0 1 0 0 1 0 0 1 0 0 1 0;

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
      in_to:   print "dentro";
      out_to:  print "fuera";
      default: return RunTimeError(9,d);
    }
];

[ LanguageNumber n f;
    if (n == 0)    { print "cero"; rfalse; }
    if (n < 0)     { print "menos "; n = -n; }
    if (n >= 1000) { print (LanguageNumber) n/1000, " mil"; n = n%1000; f = 1; }
    if (n >= 100)  {
        if (f == 1) print " ";
        switch (n/100) {
          1: print "cien";
          2: print "doscientos";
          3: print "trescientos";
          4: print "cuatrocientos";
          5: print "quinientos";
          6: print "seiscientos";
          7: print "setecientos";
          8: print "ochocientos";
          9: print "novecientos";
        }
        n = n%100;
        if (n ~= 0) {
            if (n < 10) print "to "; else print " ";
        }
        f = 1;
    }
    if (n == 0) rfalse;
    
    if (f == 1) print " ";
    
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
      16:   print "dieciséis";
      17:   print "diecisiete";
      18:   print "dieciocho";
      19:   print "diecinueve";
      20:   print "veinte";
      21:   print "veintiuno";
      22:   print "veintidós";
      23:   print "veintitrés";
      24:   print "veinticuatro";
      25:   print "veinticinco";
      26:   print "veintiséis";
      27:   print "veintisiete";
      28:   print "veintiocho";
      29:   print "veintinueve";
      30 to 99: switch (n/10) {
        3:  print "treinta";
        4:  print "cuarenta";
        5:  print "cincuenta";
        6:  print "sesenta";
        7:  print "setenta";
        8:  print "ochenta";
        9:  print "noventa";
        }
        if (n%10 ~= 0) print " y ", (LanguageNumber) n%10;
    }
];

[ LanguageTimeOfDay hours mins i;
    i = hours%12;
    if (i == 0) i = 12;
    if (i < 10) print " ";
    print i, ":", mins/10, mins%10;
    if ((hours/12) > 0) print " pm"; else print " am";
];

[ LanguageVerb i;
    switch (i) {
      'i//','inv','inventario':
               print "hacer inventario";
      'l//':   print "mirar";
      'x//':   print "examinar";
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
!  LanguageVerbIsDebugging is called by SearchScope.  It should return true
!  if word w is a debugging verb which needs all objects to be in scope.
! ----------------------------------------------------------------------------

#Ifdef DEBUG;
[ LanguageVerbIsDebugging w;
    if (w == 'purloin' or 'tree' or 'abstract'
                       or 'gonear' or 'scope' or 'showobj')
        rtrue;
    rfalse;
];
#Endif;

! ----------------------------------------------------------------------------
!  LanguageVerbLikesAdverb is called by PrintCommand when printing an UPTO_PE
!  error or an inference message.  Words which are intransitive verbs, i.e.,
!  which require a direction name as an adverb ('walk west'), not a noun
!  ('I only understood you as far as wanting to touch /the/ ground'), should
!  cause the routine to return true.
! ----------------------------------------------------------------------------

[ LanguageVerbLikesAdverb w;
    if (w == 'mirar' or 'ir' or 'correr' or 'salir' or 'l//' or 'empujar' or 'caminar')
        rtrue;
    rfalse;
];

! ----------------------------------------------------------------------------
!  LanguageVerbMayBeName is called by NounDomain when dealing with the
!  player's reply to a "Which do you mean, the short stick or the long
!  stick?" prompt from the parser. If the reply is another verb (for example,
!  LOOK) then then previous ambiguous command is discarded /unless/
!  it is one of these words which could be both a verb /and/ an
!  adjective in a 'name' property.
! ----------------------------------------------------------------------------

[ LanguageVerbMayBeName w;
    if (w == 'largo' or 'corto' or 'normal'
                    or 'breve' or 'completo' or 'detallado')
        rtrue;
    rfalse;
];

Constant NKEY__TX       = "N = siguiente tema";
Constant PKEY__TX       = "P = anterior";
Constant QKEY1__TX      = "  Q = continuar juego";
Constant QKEY2__TX      = "Q = menú anterior";
Constant RKEY__TX       = "RETURN = leer tema";

Constant NKEY1__KY      = 'N';
Constant NKEY2__KY      = 'n';
Constant PKEY1__KY      = 'P';
Constant PKEY2__KY      = 'p';
Constant QKEY1__KY      = 'Q';
Constant QKEY2__KY      = 'q';

Constant SCORE__TX      = "Puntuación: ";
Constant MOVES__TX      = "Turnos: ";
Constant TIME__TX       = "Hora: ";
Constant SCORE_S__TX    = "P: ";
Constant MOVES_S__TX    = "T: ";
Constant TIME_S__TX     = "H: ";
Constant CANTGO__TX     = "No puedes ir por ahí.";
Constant FORMER__TX     = "tu antiguo yo";
Constant MYFORMER__TX   = "mi antiguo yo";
Constant YOURSELF__TX   = "ti mismo";
Constant MYSELF__TX     = "mí mismo";
Constant YOU__TX        = "Tú";
Constant DARKNESS__TX   = "Oscuridad";

Constant THOSET__TX     = "esas cosas";
Constant THAT__TX       = "eso";
Constant OR__TX         = " o ";
Constant NOTHING__TX    = "nada";
Constant IS__TX         = " es";
Constant ARE__TX        = " son";
Constant IS2__TX        = "es ";
Constant ARE2__TX       = "son ";
Constant IS3__TX        = "es";
Constant ARE3__TX       = "son";
Constant IS4__TX        = "está";
Constant ARE4__TX       = "están";
Constant IS5__TX        = "está ";
Constant ARE5__TX       = "están ";
Constant WHOM__TX       = "quien";

! Nuevas constantes para español
Constant PARTICULA_TE   = "te";
Constant PARTICULA_ME   = "me";
Constant PARTICULA_SE   = "se";
Constant PARTICULA_NOS  = "nos";
Constant PARTICULA_OS   = "os";
Constant PARTICULA_LES  = "les";

! ------------------------------------------------------------------------------
!   Part V.   Grammar
! ------------------------------------------------------------------------------

[ LanguageInitialise;
    LanguageVerb = 'verb';
    LanguageGNAsToArticles-->0 = 0;
    LanguageGNAsToArticles-->3 = 1;
];

! ------------------------------------------------------------------------------

Constant LIBRARY_SPANISH;      ! for dependency checking.

#Endif;

! ==============================================================================