! PunyInform Espanol - Version que SI compila
! Sistema minimo pero funcional en espanol
!
! Autor: Claude Code
! Fecha: 4 de julio de 2025
! Version: 1.0 FUNCIONA

System_file;

! ######################### INCLUIR SOLO LO NECESARIO
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

! ######################### FUNCIONES REQUERIDAS

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
            
        MSG_GIVE_DEFAULT:
            print (ElLaLosLas) second, " ", (object) second, " no parece ";
            if(EsFemenino(second)) print "interesada";
            else print "interesado";
            ".";
    }
    rfalse;
];

! ######################### INCLUIR ARCHIVOS EN ORDEN CORRECTO
Include "grammar.h";

! ######################### NUEVOS VERBOS ESPANOLES UNICOS

Verb 'coger'
    * multi -> Take;

Verb 'tomar' 
    * multi -> Take
    * noun -> Drink;

Verb 'agarrar'
    * multi -> Take;

Verb 'dejar'
    * multiheld -> Drop;

Verb 'soltar'
    * multiheld -> Drop;

Verb 'meter'
    * multiexcept 'en' noun -> Insert;

Verb 'poner'
    * multiexcept 'en' noun -> Insert
    * multiexcept 'sobre' noun -> PutOn;

Verb 'mirar'
    * noun -> Examine
    * -> Look;

Verb 'observar'
    * noun -> Examine;

Verb 'examinar'
    * noun -> Examine;

Verb 'buscar'
    * noun -> Search;

Verb 'hablar'
    * 'con' creature -> Tell;

Verb 'preguntar'
    * creature 'por' noun -> AskFor;

Verb 'abrir'
    * noun -> Open;

Verb 'cerrar'
    * noun -> Close;

Verb 'encender'
    * noun -> SwitchOn;

Verb 'apagar'
    * noun -> SwitchOff;

Verb 'tocar'
    * noun -> Touch;

Verb 'oler'
    * noun -> Smell;

Verb 'escuchar'
    * noun -> Listen;

Verb 'comer'
    * held -> Eat;

Verb 'beber'
    * noun -> Drink;

Verb 'ponerse'
    * held -> Wear;

Verb 'quitarse'
    * worn -> Disrobe;

! Direcciones en espanol
Verb 'norte' * -> Go;
Verb 'sur' * -> Go;
Verb 'este' * -> Go;  
Verb 'oeste' * -> Go;
Verb 'arriba' * -> Go;
Verb 'abajo' * -> Go;

Verb 'entrar'
    * -> GoIn
    * 'en' noun -> Enter;

Verb 'salida'
    * -> Exit;

Verb 'vamos'
    * noun -> Go;

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

! ######################### INCLUIR NUCLEO PUNYINFORM
Include "puny.h";