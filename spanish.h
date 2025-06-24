! ==============================================================================
!   SPANISH:  Language Definition File
!
!   Supplied for use with Inform 6 -- Release 6.12.7dev -- Serial number 240624
!
!   Copyright Graham Nelson 1993-2004 and David Griffith 2012-2024
!   Spanish adaptation by Gargoris (https://github.com/gargoris)
!
!   This code is licensed under either the traditional Inform license as
!   described by the DM4 or the Artistic License version 2.0.  See the
!   file COPYING in the distribution archive.
!
!   This file is automatically Included in your game file by "parserm".
!   Strictly, "parserm" includes the file named in the "language__" variable,
!   whose contents can be defined by+language_name=XXX compiler setting (with a
!   default of "english").
!
! ==============================================================================

System_file;
Message "^Incluyendo Spanish: Mensajes y rutinas de idioma [InformLibSP]";

#Ifndef LIBRARY_SPANISH;	! if this file is already included,
				! don't try to include it again.

! ------------------------------------------------------------------------------
!   Part I.   Preliminaries
! ------------------------------------------------------------------------------

Constant SpanishNaturalLanguage;    ! Needed to keep old pronouns mechanism

! Definición de caractéres "baratos". Esto permite que estas letras
! ocupen menos bits en la máquina Z. No funciona si se intenta la
! compilación por módulos (viejo método)

#ifdef TARGET_ZCODE;
  Zcharacter 'á';                    ! a con acento
  Zcharacter 'é';                    ! e con acento
  Zcharacter 'í';                    ! i con acento
  Zcharacter 'ó';                    ! o con acento
  Zcharacter 'ú';                    ! u con acento
  Zcharacter 'ñ';                    ! n con virguilla
  Zcharacter 'Ñ';                    ! N con virguilla
  Zcharacter 'ü';                    ! u con dieresis
  Zcharacter '¿';                    ! abrir interrogación
  Zcharacter '¡';                    ! abrir exclamación
#endif;

!----------------------------------------------
! CONSTANTES Y CLASES ESPECIFICAS
!----------------------------------------------

Constant G_MASCULINO = 1;
Constant G_FEMENINO  = 2;
Constant G_PLURAL    = 2;

Class VerboIrregular;

!------------------------------------
! Globales específicas
!------------------------------------

global PreguntaCualExactamente = 0;
! Esta variable se pone a 1 cuando se le pregunta al jugador ¿Cuál
! exactamente...? esto indica que puede ser necesario re-traducir la
! respuesta que el jugador dé, ya que puede que simplemente el jugador
! cambie de idea y en lugar de responder a nuestra pregunta introduzca
! un comando completamente nuevo.

global PreguntaSiNo = 0;
! Esta variable debe ponerse a 1 manualmente si queremos que el verbo
! 'no' sea accesible como respuesta (y no como punto cardinal). La
! variable sólo afecta a la siguiente respuesta del jugador y vuelve a
! hacerse cero automáticamente.

Global bandera_todo_vale;
Global quitacentos = 1;
Array  texto_impreso --> 52;

Global dialecto_sudamericano = 0;

!---------------------------------------------------------------------------
! Atributos y propiedades específicas
!---------------------------------------------------------------------------

Property additive adjectives;
Property gender 0;
Property imperativo alias name;
Property irrelevante alias name;
Property name_m alias name;
Property additive name_f;
Property additive name_fp;
Property additive name_mp;

#ifdef ADMITIR_COMANDO_SALIDAS;
  Property salidas;
#endif;

Attribute nombreusado; ! usado internamente cuando se matchea el objeto por el nombre usado

!================================================================
! Los puntos cardinales
!================================================================

Class   CompassDirection
  with  number 0, articles "El" "el" "",
        description [;
            if (location provides compass_look && location.compass_look(self)) rtrue;
            if (self.compass_look()) rtrue;
            L__M(##Look, 7, self);
        ],
        compass_look false,
        parse_name [; return -1; ]
  has   scenery;

Object Compass "brújula" has concealed female;

#Ifndef WITHOUT_DIRECTIONS;
  CompassDirection -> n_obj with short_name "norte",
    name 'n//' 'norte',
    door_dir n_to;

  CompassDirection -> s_obj with short_name "sur",
    name 's//' 'sur',
    door_dir s_to;

  CompassDirection -> e_obj with short_name "este",
    name 'e//' 'este',
    door_dir e_to;

  CompassDirection -> w_obj with short_name "oeste",
    name 'w//' 'o//' 'oeste',
    door_dir w_to;

  CompassDirection -> ne_obj with short_name "nordeste",
    name 'ne' 'nordeste' 'noreste',
    door_dir ne_to;

  CompassDirection -> nw_obj with short_name "noroeste",
    name 'no' 'nw' 'noroeste',
    door_dir nw_to;

  CompassDirection -> se_obj with short_name "sudeste",
    name 'se' 'sureste' 'sudeste',
    door_dir se_to;

  CompassDirection -> sw_obj with short_name "sudoeste",
    name 'so' 'sw' 'suroeste' 'sudoeste',
    door_dir sw_to;

  CompassDirection -> u_obj with short_name "arriba",
    name 'u//' 'arriba' 'ar' 'r//' 'sube' 'techo' 'cielo',
    door_dir u_to,
    has proper;

  CompassDirection -> d_obj with short_name "abajo",
    name 'd//' 'abajo' 'ab' 'b//' 'baja' 'piso' 'suelo',
    door_dir d_to,
    has proper;
#endif; ! WITHOUT_DIRECTIONS

CompassDirection -> in_obj with short_name "interior",
  door_dir in_to,
  name 'en' 'dentro' 'adentro';

CompassDirection -> out_obj with short_name "exterior",
  door_dir out_to,
  name 'fuera' 'afuera';

! ---------------------------------------------------------------------------
!   Parte II.   Vocabulario
! ---------------------------------------------------------------------------
Constant AGAIN1__WD = 'repetir';
Constant AGAIN2__WD = 're';
Constant AGAIN3__WD = 'g//';
Constant OOPS1__WD    = 'oops';
Constant OOPS2__WD    = 'epa';
Constant OOPS3__WD    = 'eepa';
Constant UNDO1__WD  = 'undo';
Constant UNDO2__WD  = 'deshacer';
Constant UNDO3__WD  = 'anular';

Constant ALL1__WD    = 'todos';
Constant ALL2__WD    = 'todas';
Constant ALL3__WD    = 'todo';
Constant ALL4__WD    = 'ambos';
Constant ALL5__WD    = 'ambas';
Constant AND1__WD       = 'y//';
Constant AND2__WD       = 'y//';
Constant AND3__WD       = 'e//';
Constant BUT1__WD   = 'excepto';
Constant BUT2__WD   = 'menos';
Constant BUT3__WD   = 'salvo';
Constant ME1__WD      = '-me';
Constant ME2__WD      = '-te';
Constant ME3__WD      = '-se';
Constant OF1__WD      = '.de';       ! no usados nunca, pues provocan
Constant OF2__WD      = '.de';       ! interferencia con la preposición "de"
Constant OF3__WD      = '.de';       ! usada por algunos verbos, como en
Constant OF4__WD      = '.de';       ! "saca objeto de la caja"
Constant OTHER1__WD    = 'otro';
Constant OTHER2__WD    = 'otra';
Constant OTHER3__WD    = 'otro';
Constant THEN1__WD = 'ydespues';
Constant DESPUES11_WD = 'despues';
Constant THEN2__WD = 'yluego';
Constant DESPUES21_WD = 'luego';
Constant THEN3__WD = 'yentonces';
Constant DESPUES31_WD = 'entonces';

Constant NO1__WD      = 'n//';
Constant NO2__WD      = 'no';
Constant NO3__WD      = 'no';
Constant YES1__WD      = 's//';
Constant YES2__WD      = 'si';
Constant YES3__WD      = 'sí';

Constant AMUSING__WD = 'curiosidades';
Constant FULLSCORE1__WD  = 'puntuacion';
Constant FULLSCORE2__WD  = 'punt';
Constant QUIT1__WD    = 'q//';
Constant QUIT2__WD    = 'terminar';
Constant RESTART__WD    = 'reiniciar';
Constant RESTORE__WD    = 'recuperar';

Array LanguagePronouns table

!   palabra  GNAs que pueden                conectado
!            seguirle:                      a:
!              a     i
!              s  p  s  p
!              mfnmfnmfnmfn

    '-lo'    $$101000100001                    NULL
    '-los'   $$000101000101                    NULL
    '-la'    $$010000010000                    NULL
    '-las'   $$000010000010                    NULL
    '-le'    $$110000110000                    NULL
    '-les'   $$000110000110                    NULL
    'él'     $$100000100000                    NULL
    'ella'   $$010000010000                    NULL
    'ellos'  $$000100000100                    NULL
    'ellas'  $$000010000010                    NULL;

Array LanguageDescriptors table

    !palabra  GNAs que pueden     tipo de   conectado
    !              seguirles:  descriptor:       con:
    !          a     i
    !          s  p  s  p
    !          mfnmfnmfnmfn

    'mi'     $$110110110110    POSSESS_PK      0
    'este'   $$100000100000    POSSESS_PK      0
    'estos'  $$000100000100    POSSESS_PK      0
    'esta'   $$010000010000    POSSESS_PK      0
    'estas'  $$000010000010    POSSESS_PK      0
    'ese'    $$100000100000    POSSESS_PK      1
    'esa'    $$010000010000    POSSESS_PK      1
    'esos'   $$000100000100    POSSESS_PK      1
    'esas'   $$000010000010    POSSESS_PK      1
    'su'     $$110000110000    POSSESS_PK      '-le'
    'sus'    $$000110000110    POSSESS_PK      '-le'
    'el'     $$100000100000    DEFART_PK       NULL
    'la'     $$010000010000    DEFART_PK       NULL
    'los'    $$000100000100    DEFART_PK       NULL
    'las'    $$000010000010    DEFART_PK       NULL
    'un'     $$100000100000    INDEFART_PK     NULL
    'una'    $$010000010000    INDEFART_PK     NULL
    'unos'   $$000100000100    INDEFART_PK     NULL
    'unas'   $$000010000010    INDEFART_PK     NULL
    'algún'  $$100000100000    INDEFART_PK     NULL
   'algunos' $$000100000100    INDEFART_PK     NULL
   'algunas' $$000010000010    INDEFART_PK     NULL
 'encendido' $$100000100000    light             NULL
 'encendida' $$010000010000    light             NULL
'encendidos' $$000100000100    light             NULL
'encendidas' $$000010000010    light             NULL
   'apagado' $$100000100000    (-light)          NULL
   'apagada' $$010000010000    (-light)          NULL
  'apagados' $$000100000100    (-light)          NULL
  'apagadas' $$000010000010    (-light)          NULL;

Array LanguageNumbers table
    'un' 1 'uno' 1 'una' 1 'dos' 2 'tres' 3 'cuatro' 4 'cinco' 5
    'seis' 6 'siete' 7 'ocho' 8 'nueve' 9 'diez' 10
    'once' 11 'doce' 12 'trece' 13 'catorce' 14 'quince' 15
    'dieciséis' 16 'diecisiete' 17 'dieciocho' 18 'diecinueve' 19
    'veinte' 20;

! ---------------------------------------------------------------------------
!   Parte III.   Traducción
! ---------------------------------------------------------------------------

! Función para procesar el texto del jugador y adaptarlo a la estructura
! que espera el parser. Esto incluye separar pronombres enclíticos,
! manejar contracciones, etc.
[ LanguageToInformese i j k l m;
    ! Separar pronombres enclíticos (como en "cógelo" -> "coge lo")
    ! y contracciones (como en "del" -> "de el")
    
    ! Primero buscamos verbos con pronombres enclíticos
    for (i=2: i<=(buffer->1): i++) {
        ! Buscar guiones o apóst"rofes
        if (buffer->i == '-' or "'") {
            ! Insertar un espacio después del guión o apóstrofe
            LTI_Insert(i+1, ' ');
            i++; ! Avanzar para no procesar el espacio recién insertado
        }
    }
    
    ! Procesar contracciones comunes en español
    for (i=2: i<=(buffer->1)-2: i++) {
        ! Detectar "del" -> "de el"
        if (i > 1 && buffer->i == 'd' && buffer->(i+1) == 'e' && buffer->(i+2) == 'l' &&
            (i+2 == (buffer->1) || buffer->(i+3) == ' ')) {
            buffer->(i+2) = ' ';
            LTI_Insert(i+3, 'e');
            LTI_Insert(i+4, 'l');
            i = i+4;
        }
        ! Detectar "al" -> "a el"
        else if (i > 1 && buffer->i == 'a' && buffer->(i+1) == 'l' &&
            (i+1 == (buffer->1) || buffer->(i+2) == ' ')) {
            buffer->(i+1) = ' ';
            LTI_Insert(i+2, 'e');
            LTI_Insert(i+3, 'l');
            i = i+3;
        }
    }
    
    ! Eliminar acentos si está activada la opción quitacentos
    if (quitacentos) {
        for (i=2: i<=(buffer->1): i++) {
            switch (buffer->i) {
                'á': buffer->i = 'a';
                'é': buffer->i = 'e';
                'í': buffer->i = 'i';
                'ó': buffer->i = 'o';
                'ú': buffer->i = 'u';
                'ü': buffer->i = 'u';
                'ñ': buffer->i = 'n';
                'Á': buffer->i = 'A';
                'É': buffer->i = 'E';
                'Í': buffer->i = 'I';
                'Ó': buffer->i = 'O';
                'Ú': buffer->i = 'U';
                'Ü': buffer->i = 'U';
                'Ñ': buffer->i = 'N';
            }
        }
    }
];

! Función auxiliar para insertar un carácter en el buffer
[ LTI_Insert pos ch   i;
    ! Comprobar que no nos salimos del buffer
    if (buffer->1 >= (buffer->0) - 1) return;
    
    ! Desplazar todo lo que hay a partir de pos
    for (i=buffer->1 + 1: i>=pos: i--)
        buffer->(i+1) = buffer->i;
    
    ! Insertar el nuevo carácter
    buffer->pos = ch;
    
    ! Incrementar la longitud del buffer
    buffer->1 = buffer->1 + 1;
];

! ------------------------------------------------------------------------------
!   Part IV.   Printing
! ------------------------------------------------------------------------------

Constant LanguageAnimateGender   = male;
Constant LanguageInanimateGender = male;

Constant LanguageContractionForms = 2;     ! Spanish has two:
                                           ! 0 = starting with a consonant
                                           ! 1 = starting with a vowel

[ LanguageContraction text;
    if (text->0 == 'a' or 'e' or 'i' or 'o' or 'u'
                or 'A' or 'E' or 'I' or 'O' or 'U') return 1;
    return 0;
];

Array LanguageArticles -->

 !   Contraction form 0:     Contraction form 1:
 !   Cdef   Def    Indef     Cdef   Def    Indef

     "El " "el " "un "      "El " "el " "un "          ! Articles 0 (male singular)
     "La " "la " "una "     "La " "la " "una "         ! Articles 1 (female singular)
     "Los " "los " "unos "  "Los " "los " "unos "      ! Articles 2 (male plural)
     "Las " "las " "unas "  "Las " "las " "unas ";     ! Articles 3 (female plural)

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
      ne_to:   print "nordeste";
      nw_to:   print "noroeste";
      se_to:   print "sudeste";
      sw_to:   print "sudoeste";
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
            if (n < 10) print "to "; else print "tos ";
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
      30:   print "treinta";
      31 to 39: print "treinta y ", (LanguageNumber) n-30;
      40:   print "cuarenta";
      41 to 49: print "cuarenta y ", (LanguageNumber) n-40;
      50:   print "cincuenta";
      51 to 59: print "cincuenta y ", (LanguageNumber) n-50;
      60:   print "sesenta";
      61 to 69: print "sesenta y ", (LanguageNumber) n-60;
      70:   print "setenta";
      71 to 79: print "setenta y ", (LanguageNumber) n-70;
      80:   print "ochenta";
      81 to 89: print "ochenta y ", (LanguageNumber) n-80;
      90:   print "noventa";
      91 to 99: print "noventa y ", (LanguageNumber) n-90;
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
      'i//','inv','inventory','inventario':
               print "hacer inventario";
      'l//':   print "mirar";
      'x//':   print "examinar";
      'z//':   print "esperar";
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
    if (w == 'purloin' or 'tree' or 'abstract' or 'xroba' or 'arboljuego' or 'xarbol' or 'xmueve'
                       or 'gonear' or 'scope' or 'showobj' or 'xobjeto' or 'alcance' or 'xir' or 'irdonde')
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
    if (w == 'look' or 'go' or 'push' or 'walk' or 'mirar' or 'ir' or 'empujar' or 'caminar')
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
    if (w == 'long' or 'short' or 'normal' or 'largo' or 'corto' or 'normal'
                    or 'brief' or 'full' or 'verbose' or 'breve' or 'completo' or 'verboso')
        rtrue;
    rfalse;
];

Constant NKEY__TX       = "N = siguiente tema";
Constant PKEY__TX       = "P = anterior";
Constant QKEY1__TX      = "  Q = volver al juego";
Constant QKEY2__TX      = "Q = menú anterior";
Constant RKEY__TX       = "RETURN = leer tema";

Constant NKEY1__KY      = 'N';
Constant NKEY2__KY      = 'n';
Constant PKEY1__KY      = 'P';
Constant PKEY2__KY      = 'p';
Constant QKEY1__KY      = 'Q';
Constant QKEY2__KY      = 'q';

Constant SCORE__TX      = "Puntuación: ";
Constant MOVES__TX      = "Movimientos: ";
Constant TIME__TX       = "Hora: ";
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
Constant IS__TX         = " está";
Constant ARE__TX        = " están";
Constant IS2__TX        = "está ";
Constant ARE2__TX       = "están ";
Constant WAS__TX        = " estaba";
Constant WERE__TX       = " estaban";
Constant WAS2__TX       = "estaba ";
Constant WERE2__TX      = "estaban ";
Constant AND__TX        = " y ";

! ==============================================================================

! Rutinas de ayuda para imprimir mensajes en español
[ EsOSon obj;
    if (obj has pluralname) print "son"; else print "es";
];

[ ElLaLosLas obj;
    if (obj has pluralname) {
        if (obj has female) print "las"; else print "los";
    } else {
        if (obj has female) print "la"; else print "el";
    }
];

[ ElLaLosLasCap obj;
    if (obj has pluralname) {
        if (obj has female) print "Las"; else print "Los";
    } else {
        if (obj has female) print "La"; else print "El";
    }
];

[ UnUnaUnosUnas obj;
    if (obj has pluralname) {
        if (obj has female) print "unas"; else print "unos";
    } else {
        if (obj has female) print "una"; else print "un";
    }
];

! Rutinas para reemplazar las funciones estándar del parser
! que necesitan adaptarse al español

! [Replace directives for Spanish-specific functions]
Replace DictionaryLookup;
Replace PrefaceByArticle;
Replace Identical;
Replace TryGivenObject;
Replace Indefart;
Replace BestGuess;
Replace NounDomain;

! Include replacement functions
Include "infspr";

#Endif; ! LIBRARY_SPANISH