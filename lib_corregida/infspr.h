! ==============================================================================
!   INFSPR:  Funciones de reemplazo para el parser en español (versión corregida)
!
!   Supplied for use with Inform 6 -- Release 6.12.7dev -- Serial number 240624
!
!   Copyright Graham Nelson 1993-2004 and David Griffith 2012-2024
!   Spanish adaptation by Gargoris (https://github.com/gargoris)
!   Corrections by AI Assistant
!
!   This code is licensed under either the traditional Inform license as
!   described by the DM4 or the Artistic License version 2.0.  See the
!   file COPYING in the distribution archive.
!
! ==============================================================================

System_file;

! Incluimos la librería estándar
Include "/usr/share/inform-stdlib/Parser";
Include "/usr/share/inform-stdlib/VerbLib";

! Definición de variables globales necesarias
Global quitacentos = 1;
Global PreguntaCualExactamente = 0;
Global PreguntaSiNo = 0;
Global dialecto_sudamericano = 0;
Global match_length = 0;
Global number_matched = 0;
Global match_from = 0;

! Definición de atributos específicos para español
Attribute female;    ! Femenino
Attribute male;      ! Masculino
Attribute plural;    ! Plural

! Definición de propiedades específicas para español
Property gender 0;   ! Género (1=masculino, 2=femenino)
Property name_f;     ! Nombre en femenino
Property name_m;     ! Nombre en masculino
Property name_mp;    ! Nombre en masculino plural
Property name_fp;    ! Nombre en femenino plural

! Constantes específicas para español
Constant G_MASCULINO = 1;
Constant G_FEMENINO  = 2;
Constant G_PLURAL    = 2;

! Clase para verbos irregulares
Class VerboIrregular
  with name;

! ------------------------------------------------------------------------------
! Reemplazo de DictionaryLookup para manejar palabras con acentos
! ------------------------------------------------------------------------------

[ DictionaryLookup texto longitud i j;
    ! Si está activada la opción quitacentos, convertimos los acentos
    ! antes de buscar en el diccionario
    if (quitacentos) {
        for (i=0: i<longitud: i++) {
            switch (texto->i) {
                'a': texto->i = 'a';
                'e': texto->i = 'e';
                'i': texto->i = 'i';
                'o': texto->i = 'o';
                'u': texto->i = 'u';
                'u': texto->i = 'u';
                'n': texto->i = 'n';
                'A': texto->i = 'A';
                'E': texto->i = 'E';
                'I': texto->i = 'I';
                'O': texto->i = 'O';
                'U': texto->i = 'U';
                'U': texto->i = 'U';
                'N': texto->i = 'N';
            }
        }
    }
    
    ! Llamar a la función original
    return VM_DictionaryLookup(texto, longitud);
];

! ------------------------------------------------------------------------------
! Reemplazo de PrefaceByArticle para manejar artículos en español
! ------------------------------------------------------------------------------

[ PrefaceByArticle o acode pluralform capitalise  i artform;
    if (o provides gender) {
        if (o.gender == G_FEMENINO) {
            if (pluralform) artform = "las ";
            else artform = "la ";
        }
        else {
            if (pluralform) artform = "los ";
            else artform = "el ";
        }
    }
    else {
        if (pluralform) artform = "los ";
        else artform = "el ";
    }
    
    if (capitalise) {
        if (artform->0 == 'l') artform->0 = 'L';
        if (artform->0 == 'e') artform->0 = 'E';
    }
    
    print (string) artform;
];

! ------------------------------------------------------------------------------
! Reemplazo de PrintShortName para manejar nombres en español
! ------------------------------------------------------------------------------

[ PrintShortName obj;
    if (obj provides short_name) {
        return PrintOrRun(obj, short_name, true);
    }
    
    print (object) obj;
    rtrue;
];

! ------------------------------------------------------------------------------
! Rutina para imprimir mensajes en español
! ------------------------------------------------------------------------------

[ SpanishMessage n x1 x2;
    switch(n) {
        1: print "No veo eso aqui.";
        2: print "No puedes hacer eso.";
        3: print "No puedes ir en esa direccion.";
        4: print "No puedes ver nada en especial.";
        5: print "No puedes hacer eso con ", (the) x1, ".";
        6: print "Llevas ", (the) x1, ".";
        7: print "Ya tienes ", (the) x1, ".";
        8: print "No tienes ", (the) x1, ".";
        9: print "Has tomado ", (the) x1, ".";
        10: print "Has dejado ", (the) x1, ".";
        11: print "Eso no es algo que puedas tomar.";
        12: print "No puedes dejar eso.";
        13: print "No puedes abrir ", (the) x1, ".";
        14: print "No puedes cerrar ", (the) x1, ".";
        15: print "Ya esta abierto.";
        16: print "Ya esta cerrado.";
        17: print "Has abierto ", (the) x1, ".";
        18: print "Has cerrado ", (the) x1, ".";
        19: print "No puedes entrar en ", (the) x1, ".";
        20: print "No puedes sentarte en ", (the) x1, ".";
        21: print "Te has sentado en ", (the) x1, ".";
        22: print "No puedes beber ", (the) x1, ".";
        23: print "Has bebido ", (the) x1, ".";
        24: print "No puedes examinar eso.";
        25: print "No ves nada especial en ", (the) x1, ".";
        26: print "Llevas:^";
        27: print "No llevas nada.";
        28: print "Has ganado.";
        29: print "Has muerto.";
        30: print "^Quieres volver a intentarlo? ";
        default: print "[Mensaje desconocido ", n, "]";
    }
];

! ------------------------------------------------------------------------------
! Reemplazo de la rutina de inicialización
! ------------------------------------------------------------------------------

[ Main i j;
    VM_Initialise();
    
    location = Initialise();
    
    while (~~deadflag) {
        VM_StatusLine();
        
        if (location ~= thedark) {
            if (location.description) PrintOrRun(location, description);
            else SpanishMessage(4);
        }
        else {
            SpanishMessage(4);
        }
        
        VM_Style(NORMAL_VMSTY);
        
        ! Procesar entrada del jugador
        VM_ReadCommand();
        
        ! Analizar y ejecutar el comando
        Parser();
        
        ! Actualizar estado del juego
        RunRoutines();
    }
    
    ! Mensaje final según el estado de deadflag
    if (deadflag == 1) SpanishMessage(29);
    if (deadflag == 2) SpanishMessage(28);
    
    ! Preguntar si quiere volver a jugar
    SpanishMessage(30);
    VM_ReadCommand();
    
    if (YesOrNo()) {
        deadflag = 0;
        VM_Restart();
    }
];

! ------------------------------------------------------------------------------
! Rutina para determinar si la respuesta es sí o no
! ------------------------------------------------------------------------------

[ YesOrNo i j;
    for (::) {
        i = VM_KeyChar();
        if (i == 'S' or 's' or 'Y' or 'y') return true;
        if (i == 'N' or 'n') return false;
    }
];

! ------------------------------------------------------------------------------
! Rutina para ejecutar rutinas pendientes
! ------------------------------------------------------------------------------

[ RunRoutines;
    ! Aquí iría el código para ejecutar rutinas pendientes
    ! como daemons, timers, etc.
];

! ------------------------------------------------------------------------------
! Incluimos la gramática en español
! ------------------------------------------------------------------------------

Include "/usr/share/inform-stdlib/Grammar";

! Verbos en español
Verb 'examina' 'examinar' 'ex' 'mira' 'mirar' 'm//'
    * noun                                -> Examine;

Verb 'inventario' 'inv' 'i//'
    *                                     -> Inv;

Verb 'coger' 'tomar' 'agarrar'
    * noun                                -> Take;

Verb 'dejar' 'soltar' 'tirar'
    * noun                                -> Drop;

Verb 'abrir'
    * noun                                -> Open;

Verb 'cerrar'
    * noun                                -> Close;

Verb 'entrar' 'entra' 'ir' 'vete' 've' 'caminar' 'camina'
    *                                     -> GoIn
    * 'en' 'hacia' noun                  -> Enter
    * 'en' 'hacia' 'el' noun             -> Enter
    * 'en' 'hacia' 'la' noun             -> Enter
    * 'en' 'hacia' 'los' noun            -> Enter
    * 'en' 'hacia' 'las' noun            -> Enter
    * 'hacia' 'norte'                    -> Go
    * 'hacia' 'sur'                      -> Go
    * 'hacia' 'este'                     -> Go
    * 'hacia' 'oeste'                    -> Go
    * 'hacia' 'arriba'                   -> Go
    * 'hacia' 'abajo'                    -> Go;

Verb 'sentarse' 'sentate' 'sientate'
    * 'en' noun                          -> Enter;

Verb 'beber' 'bebe'
    * noun                               -> Drink;

! Puntos cardinales en español
Verb 'n//' 'norte'
    *                                     -> Go, 1;

Verb 's//' 'sur'
    *                                     -> Go, 2;

Verb 'e//' 'este'
    *                                     -> Go, 3;

Verb 'o//' 'oeste'
    *                                     -> Go, 4;

Verb 'ne' 'nordeste' 'noreste'
    *                                     -> Go, 5;

Verb 'no' 'noroeste'
    *                                     -> Go, 6;

Verb 'se' 'sureste' 'sudeste'
    *                                     -> Go, 7;

Verb 'so' 'suroeste' 'sudoeste'
    *                                     -> Go, 8;

Verb 'arriba' 'sube' 'subir'
    *                                     -> Go, 9;

Verb 'abajo' 'baja' 'bajar'
    *                                     -> Go, 10;

Verb 'adentro' 'dentro' 'entrar'
    *                                     -> Go, 11;

Verb 'afuera' 'fuera' 'salir'
    *                                     -> Go, 12;