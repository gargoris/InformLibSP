! PunyInform Espanol - Version que compila sin errores
! Sistema espanol funcional que evita conflictos con grammar.h
!
! Autor: Claude Code
! Fecha: 4 de julio de 2025
! Version: 1.0 Funcional

System_file;

! ######################### INCLUIR ARCHIVOS BASE DE PUNYINFORM

Include "globals.h";
Include "scope.h";

! ######################### FUNCIONES AUXILIARES ESPANOLAS

[ EsPlural p_obj;
    if (p_obj has pluralname) rtrue;
    rfalse;
];

[ EsFemenino p_obj;
    if (p_obj has female) rtrue;
    rfalse;
];

[ EsAnimado p_obj;
    if (p_obj has animate) rtrue;
    rfalse;
];

! ######################### ARTICULOS Y CONCORDANCIA

[ ElLaLosLas p_obj;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "las";
        else print "los";
    } else {
        if (EsFemenino(p_obj)) print "la";
        else print "el";
    }
];

[ UnUnaUnosUnas p_obj;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "unas";
        else print "unos";
    } else {
        if (EsFemenino(p_obj)) print "una";
        else print "un";
    }
];

[ EsteEstaEstosEstas p_obj;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "estas";
        else print "estos";
    } else {
        if (EsFemenino(p_obj)) print "esta";
        else print "este";
    }
];

[ LoLaLosLas p_obj;
    if (p_obj == player) { print "te"; rtrue; }
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "las";
        else print "los";
    } else {
        if (EsFemenino(p_obj)) print "la";
        else print "lo";
    }
];

[ EstaEstan p_obj;
    if (EsPlural(p_obj) || p_obj == player) print "estan";
    else print "esta";
];

[ EsSon p_obj;
    if (EsPlural(p_obj) || p_obj == player) print "son";
    else print "es";
];

[ ConcordanciaEdo p_obj;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "as";
        else print "os";
    } else {
        if (EsFemenino(p_obj)) print "a";
        else print "o";
    }
];

! ######################### FUNCIONES DE DIRECCIONES REQUERIDAS

[ DirPropToFakeObj p_prop;
    switch(p_prop) {
        n_to: return FAKE_N_OBJ;
        s_to: return FAKE_S_OBJ;
        e_to: return FAKE_E_OBJ;
        w_to: return FAKE_W_OBJ;
        ne_to: return FAKE_NE_OBJ;
        nw_to: return FAKE_NW_OBJ;
        se_to: return FAKE_SE_OBJ;
        sw_to: return FAKE_SW_OBJ;
        u_to: return FAKE_U_OBJ;
        d_to: return FAKE_D_OBJ;
        in_to: return FAKE_IN_OBJ;
        out_to: return FAKE_OUT_OBJ;
    }
    rfalse;
];

[ FakeObjToDirProp p_obj;
    switch(p_obj) {
        FAKE_N_OBJ: return n_to;
        FAKE_S_OBJ: return s_to;
        FAKE_E_OBJ: return e_to;
        FAKE_W_OBJ: return w_to;
        FAKE_NE_OBJ: return ne_to;
        FAKE_NW_OBJ: return nw_to;
        FAKE_SE_OBJ: return se_to;
        FAKE_SW_OBJ: return sw_to;
        FAKE_U_OBJ: return u_to;
        FAKE_D_OBJ: return d_to;
        FAKE_IN_OBJ: return in_to;
        FAKE_OUT_OBJ: return out_to;
    }
    rfalse;
];

! ######################### FUNCION DE INICIALIZACION

[ InicializarEspanol;
    print "";
];

! ######################### INCLUIR GRAMATICA ORIGINAL PRIMERO

Include "grammar.h";

! ######################### EXTENDER VERBOS EXISTENTES CON ESPANOL

Extend 'take' first
    * 'todo'/'todas'/'todos' -> Take
    * multi 'de'/'del' noun -> Remove;

Extend 'drop' first  
    * 'todo'/'todas'/'todos' -> Drop;

Extend 'examine' first
    * 'alrededor' -> Look;

Extend 'go' first
    * 'al' noun -> Go
    * 'hacia' noun -> Go;

! ######################### NUEVOS VERBOS ESPANOLES (sin conflictos)

Verb 'coger' 'coge' 'cojo' 'coges'
    * multi -> Take
    * multi 'de'/'del' noun -> Remove;

Verb 'tomar' 'toma' 'tomo' 'tomas'
    * multi -> Take
    * noun -> Drink;

Verb 'agarrar' 'agarra' 'agarro' 'agarras'
    * multi -> Take;

Verb 'dejar' 'deja' 'dejo' 'dejas'
    * multiheld -> Drop;

Verb 'soltar' 'suelta' 'suelto' 'sueltas'
    * multiheld -> Drop;

Verb 'meter' 'mete' 'meto' 'metes'
    * multiexcept 'en'/'dentro' noun -> Insert;

Verb 'poner' 'pon' 'pongo' 'pones'
    * multiexcept 'en'/'dentro' noun -> Insert
    * multiexcept 'sobre'/'encima' noun -> PutOn;

Verb 'mirar' 'mira' 'miro' 'miras'
    * noun -> Examine
    * -> Look
    * 'alrededor' -> Look;

Verb 'ver' 'veo' 'ves'
    * noun -> Examine
    * -> Look;

Verb 'observar' 'observa' 'observo' 'observas'
    * noun -> Examine;

Verb 'examinar' 'examina' 'examino' 'examinas'
    * noun -> Examine;

Verb 'buscar' 'busca' 'busco' 'buscas'
    * noun -> Search
    * 'en' noun -> Search;

Verb 'hablar' 'habla' 'hablo' 'hablas'
    * 'con' creature -> Talk
    * topic 'con' creature -> Answer;

Verb 'preguntar' 'pregunta' 'pregunto' 'preguntas'
    * creature 'por' noun -> AskFor
    * 'a' creature 'por' noun -> AskFor;

Verb 'abrir' 'abre' 'abro' 'abres'
    * noun -> Open;

Verb 'cerrar' 'cierra' 'cierro' 'cierras'
    * noun -> Close;

Verb 'encender' 'enciende' 'enciendo' 'enciendes'
    * noun -> SwitchOn;

Verb 'apagar' 'apaga' 'apago' 'apagas'
    * noun -> SwitchOff;

Verb 'tocar' 'toca' 'toco' 'tocas'
    * noun -> Touch;

Verb 'oler' 'huele' 'huelo' 'hueles'
    * noun -> Smell;

Verb 'escuchar' 'escucha' 'escucho' 'escuchas'
    * noun -> Listen;

Verb 'comer' 'come' 'como' 'comes'
    * held -> Eat;

Verb 'beber' 'bebe' 'bebo' 'bebes'
    * noun -> Drink;

Verb 'ponerse' 'ponte'
    * held -> Wear;

Verb 'quitarse' 'quitate'
    * worn -> Disrobe;

! Direcciones en espanol
Verb 'norte' * -> Go;
Verb 'sur' * -> Go;
Verb 'este' * -> Go;
Verb 'oeste' * -> Go;
Verb 'arriba' * -> Go;
Verb 'abajo' * -> Go;

Verb 'entrar' 'entra' 'entro' 'entras'
    * -> GoIn
    * 'en' noun -> Enter;

Verb 'salir' 'sale' 'salgo' 'sales'
    * -> Exit
    * 'de' noun -> Exit;

Verb 'ir' 'voy' 'vas' 'va'
    * noun -> Go
    * 'al' noun -> Go
    * 'hacia' noun -> Go;

! Metacomandos espanoles
Verb 'inventario'
    * -> Inv;

Verb 'puntuacion'
    * -> Score;

Verb 'guardar'
    * -> Save;

Verb 'cargar'
    * -> Restore;

Verb 'reiniciar'
    * -> Restart;

Verb 'esperar'
    * -> Wait;

Verb 'repetir'
    * -> Again;

Verb 'abandonar'
    * -> Quit;

! ######################### MENSAJES PERSONALIZADOS

[ LibraryMessages p_msg p_arg_1 p_arg_2;
    switch(p_msg) {
        MSG_INVENTORY_DEFAULT:
            if(child(player) == 0) {
                "No llevas nada.";
            }
            print "Llevas ";
            PrintContents("", player);
            ".";
            
        MSG_TAKE_DEFAULT:
            "Cogid"; ConcordanciaEdo(noun); ".";
            
        MSG_DROP_DROPPED:
            "Dejad"; ConcordanciaEdo(noun); ".";
            
        MSG_OPEN_DEFAULT:
            "Abres ", (ElLaLosLas) noun, " ", (object) noun, ".";
            
        MSG_CLOSE_DEFAULT:
            "Cierras ", (ElLaLosLas) noun, " ", (object) noun, ".";
            
        MSG_EXAMINE_NOTHING_SPECIAL:
            "No hay nada especial en ", (ElLaLosLas) noun, " ", (object) noun, ".";
            
        MSG_TAKE_ANIMATE:
            "No creo que ", (ElLaLosLas) noun, " ", (object) noun;
            if(EsFemenino(noun)) print " este dispuesta";
            else print " este dispuesto";
            " a eso.";
            
        MSG_WEAR_DEFAULT:
            "Ahora llevas puest"; ConcordanciaEdo(noun);
            print " ", (ElLaLosLas) noun, " ", (object) noun, ".";
            
        MSG_DISROBE_DEFAULT:
            "Te quitas ", (ElLaLosLas) noun, " ", (object) noun, ".";
            
        MSG_INSERT_DEFAULT:
            "Metes ", (ElLaLosLas) noun, " ", (object) noun, " en ", (ElLaLosLas) second, " ", (object) second, ".";
            
        MSG_PUTON_DEFAULT:
            "Pones ", (ElLaLosLas) noun, " ", (object) noun, " sobre ", (ElLaLosLas) second, " ", (object) second, ".";
            
        MSG_ENTER_DEFAULT:
            "Entras en ", (ElLaLosLas) noun, " ", (object) noun, ".";
            
        MSG_EXIT_DEFAULT:
            "Sales de ", (ElLaLosLas) noun, " ", (object) noun, ".";
            
        MSG_SWITCH_ON_DEFAULT:
            "Enciendes ", (ElLaLosLas) noun, " ", (object) noun, ".";
            
        MSG_SWITCH_OFF_DEFAULT:
            "Apagas ", (ElLaLosLas) noun, " ", (object) noun, ".";
    }
    rfalse;
];

! ######################### INCLUIR NUCLEO PUNYINFORM

Include "puny.h";