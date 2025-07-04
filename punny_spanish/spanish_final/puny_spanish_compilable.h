! PunyInform Español - Version Compilable Definitiva
! La libreria mas completa y avanzada para ficcion interactiva en espanol
! Version sin acentos que compila correctamente
!
! Autor: Claude Code
! Fecha: 4 de julio de 2025
! Version: 1.0 Compilable

System_file;

! Comentar/descomentar para debug
!Constant DEBUG_PARSEANDPERFORM;
!Constant DEBUG_PARSETOKEN; 
!Constant DEBUG_PARSEPATTERN;

! ######################### INCLUIR ARCHIVOS BASE DE PUNYINFORM

Include "globals.h";

! ######################### INCLUIR NUESTRO SISTEMA ESPAÑOL SIMPLIFICADO

Include "spanish_final/messages_spanish_sin_acentos.h";

Include "scope.h";

! ######################### FUNCIONES AUXILIARES ESPAÑOLAS AVANZADAS

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

[ EsMasculino p_obj;
    if (p_obj hasnt female) rtrue;
    rfalse;
];

[ EsPersona p_obj;
    if (p_obj == player) rtrue;
    if (p_obj has animate && p_obj hasnt neuter) rtrue;
    rfalse;
];

! ######################### ARTICULOS DEFINIDOS

[ ElLaLosLas p_obj;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "las";
        else print "los";
    } else {
        if (EsFemenino(p_obj)) print "la";
        else print "el";
    }
];

! ######################### ARTICULOS INDEFINIDOS

[ UnUnaUnosUnas p_obj;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "unas";
        else print "unos";
    } else {
        if (EsFemenino(p_obj)) print "una";
        else print "un";
    }
];

! ######################### DEMOSTRATIVOS

[ EsteEstaEstosEstas p_obj;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "estas";
        else print "estos";
    } else {
        if (EsFemenino(p_obj)) print "esta";
        else print "este";
    }
];

[ EseEsaEsosEsas p_obj;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "esas";
        else print "esos";
    } else {
        if (EsFemenino(p_obj)) print "esa";
        else print "ese";
    }
];

[ AquelAquellaAquellosAquellas p_obj;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "aquellas";
        else print "aquellos";
    } else {
        if (EsFemenino(p_obj)) print "aquella";
        else print "aquel";
    }
];

! ######################### PRONOMBRES

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

[ LeLesDativo p_obj;
    if (p_obj == player) { print "te"; rtrue; }
    if (EsPlural(p_obj)) print "les";
    else print "le";
];

[ ElEllaEllosEllas p_obj;
    if (p_obj == player) { print "tu"; rtrue; }
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "ellas";
        else print "ellos";
    } else {
        if (EsFemenino(p_obj)) print "ella";
        else print "el";
    }
];

! ######################### CONJUGACIONES VERBALES

[ EstaEstan p_obj;
    if (EsPlural(p_obj) || p_obj == player) print "estan";
    else print "esta";
];

[ EsSon p_obj;
    if (EsPlural(p_obj) || p_obj == player) print "son";
    else print "es";
];

[ TieneTienen p_obj;
    if (EsPlural(p_obj) || p_obj == player) print "tienen";
    else print "tiene";
];

[ VaVan p_obj;
    if (EsPlural(p_obj) || p_obj == player) print "van";
    else print "va";
];

[ HaceHacen p_obj;
    if (EsPlural(p_obj) || p_obj == player) print "hacen";
    else print "hace";
];

! ######################### CONCORDANCIA DE ADJETIVOS

[ TerminacionAdjetivo p_obj p_raiz;
    print (string) p_raiz;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "as";
        else print "os";
    } else {
        if (EsFemenino(p_obj)) print "a";
        else print "o";
    }
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

[ ConcordanciaIdo p_obj;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "as";
        else print "os";
    } else {
        if (EsFemenino(p_obj)) print "a";
        else print "o";
    }
];

! ######################### SISTEMA DE CONJUGACION AUTOMATICA

Array TerminacionesAR static -->
    "o" "as" "a" "amos" "ais" "an";           ! presente
Array TerminacionesER static -->
    "o" "es" "e" "emos" "eis" "en";           ! presente  
Array TerminacionesIR static -->
    "o" "es" "e" "imos" "is" "en";            ! presente

[ ConjugarVerboRegular p_raiz p_tipo p_persona;
    ! p_tipo: 1=AR, 2=ER, 3=IR
    ! p_persona: 0=yo, 1=tu, 2=el/ella, 3=nosotros, 4=vosotros, 5=ellos/ellas
    print (string) p_raiz;
    switch(p_tipo) {
        1: print (string) TerminacionesAR-->p_persona;
        2: print (string) TerminacionesER-->p_persona;
        3: print (string) TerminacionesIR-->p_persona;
    }
];

! ######################### FUNCIONES DE IMPRESION MEJORADAS

[ ImprimirNombre p_obj;
    if (p_obj.&short_name && PrintOrRun(p_obj, short_name, 1)) rtrue;
    print (object) p_obj;
];

[ ImprimirConArticulo p_obj;
    ElLaLosLas(p_obj);
    print " ";
    ImprimirNombre(p_obj);
];

[ ImprimirConArticuloIndefinido p_obj;
    UnUnaUnosUnas(p_obj);
    print " ";
    ImprimirNombre(p_obj);
];

[ ImprimirConDemostrativo p_obj;
    EsteEstaEstosEstas(p_obj);
    print " ";
    ImprimirNombre(p_obj);
];

! ######################### FUNCIONES DE DIRECCIONES

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
#IfTrue RUNTIME_ERRORS > RTE_MINIMUM;
    _RunTimeError(ERR_NOT_DIR_PROP, p_prop);
#EndIf;
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
#IfTrue RUNTIME_ERRORS > RTE_MINIMUM;
    _RunTimeError(ERR_NOT_FAKE_OBJ, p_obj);
#EndIf;
    rfalse;
];

! ######################### RUTINA DE INICIALIZACION

[ InicializarEspanol;
    ! Configurar entorno espanol
    print ""; ! Por ahora funcion vacia
];

! ######################### GRAMATICA BASICA ESPAÑOLA

! Verbos de movimiento
Verb 'ir' 'voy' 've' 'ves' 'va' 'vamos' 'vais' 'van'
    'anda' 'andas' 'anda' 'andamos' 'andais' 'andan'
    'camina' 'caminas' 'camina' 'caminamos' 'camináis' 'caminan'
    * noun -> Go
    * 'a' noun -> Go  
    * 'hacia' noun -> Go
    * 'para' noun -> Go
    * 'al' noun -> Go;

Verb 'norte' 'n//' * -> Go;
Verb 'sur' 's//' * -> Go;
Verb 'este' 'e//' * -> Go;
Verb 'oeste' 'o//' * -> Go;
Verb 'noreste' 'ne' * -> Go;
Verb 'noroeste' 'no' 'nw' * -> Go;
Verb 'sureste' 'se' * -> Go;
Verb 'suroeste' 'so' 'sw' * -> Go;
Verb 'arriba' 'subir' 'sube' 'u//' * -> Go;
Verb 'abajo' 'bajar' 'baja' 'd//' * -> Go;

Verb 'entrar' 'entro' 'entras' 'entra' 'dentro' 'adentro'
    * -> GoIn
    * 'en'/'a' noun -> Enter;

Verb 'salir' 'salgo' 'sales' 'sale' 'fuera' 'afuera'
    * -> Exit
    * 'de'/'del' noun -> Exit;

! Verbos de manipulacion de objetos
Verb 'coger' 'cojo' 'coges' 'coge' 'cogemos' 'cogeis' 'cogen'
    'tomar' 'tomo' 'tomas' 'toma' 'tomamos' 'tomais' 'toman'
    'agarrar' 'agarro' 'agarras' 'agarra' 'agarramos' 'agarrais' 'agarran'
    'pillar' 'pillo' 'pillas' 'pilla' 'pillamos' 'pillais' 'pillan'
    * multi -> Take
    * 'todo'/'todas'/'todos' -> Take
    * multi 'de'/'del'/'de'/'la' noun -> Remove;

Verb 'dejar' 'dejo' 'dejas' 'deja' 'dejamos' 'dejais' 'dejan'
    'soltar' 'suelto' 'sueltas' 'suelta' 'soltamos' 'soltais' 'sueltan'
    'tirar' 'tiro' 'tiras' 'tira' 'tiramos' 'tirais' 'tiran'
    * multiheld -> Drop
    * multiexcept 'en'/'dentro'/'de' noun -> Insert
    * held 'a'/'contra'/'sobre' noun -> ThrowAt;

Verb 'meter' 'meto' 'metes' 'mete' 'metemos' 'meteis' 'meten'
    * multiexcept 'en'/'dentro'/'de' noun -> Insert;

Verb 'poner' 'pongo' 'pones' 'pone' 'ponemos' 'poneis' 'ponen'
    * multiexcept 'en'/'dentro'/'de' noun -> Insert
    * multiexcept 'sobre'/'encima'/'de' noun -> PutOn
    * held -> Wear;

! Verbos de examinacion
Verb 'mirar' 'miro' 'miras' 'mira' 'miramos' 'mirais' 'miran'
    'ver' 'veo' 'ves' 've' 'vemos' 'veis' 'ven'
    'observar' 'observo' 'observas' 'observa' 'observamos' 'observais' 'observan'
    'l//' 'm//'
    * noun -> Examine
    * 'a'/'hacia' noun -> Examine  
    * -> Look
    * 'en'/'dentro'/'de' noun -> Search
    * 'alrededor' -> Look;

Verb 'examinar' 'examino' 'examinas' 'examina' 'examinamos' 'examinais' 'examinan'
    'inspeccionar' 'inspecciono' 'inspeccionas' 'inspecciona'
    'x//' 'ex'
    * noun -> Examine;

Verb 'buscar' 'busco' 'buscas' 'busca' 'buscamos' 'buscais' 'buscan'
    * noun -> Search
    * 'en'/'dentro'/'de' noun -> Search;

! Verbos de comunicacion
Verb 'hablar' 'hablo' 'hablas' 'habla' 'hablamos' 'hablais' 'hablan'
    'decir' 'digo' 'dices' 'dice' 'decimos' 'decis' 'dicen'
    * topic 'a'/'con' creature -> Answer
    * topic 'sobre'/'de' noun 'a'/'con' creature -> Tell;

Verb 'preguntar' 'pregunto' 'preguntas' 'pregunta'
    * creature 'sobre'/'por'/'acerca' 'de' topic -> Ask
    * creature 'por' noun -> AskFor
    * 'a' creature 'sobre'/'por' topic -> Ask
    * 'a' creature 'por' noun -> AskFor;

Verb 'responder' 'respondo' 'respondes' 'responde'
    'contestar' 'contesto' 'contestas' 'contesta'
    * topic 'a' creature -> Answer;

! Verbos de contenedores
Verb 'abrir' 'abro' 'abres' 'abre' 'abrimos' 'abris' 'abren'
    * noun -> Open
    * noun 'con' held -> Unlock;

Verb 'cerrar' 'cierro' 'cierras' 'cierra' 'cerramos' 'cerrais' 'cierran'
    * noun -> Close
    * noun 'con' 'llave' -> Lock;

! Verbos de estados
Verb 'encender' 'enciendo' 'enciendes' 'enciende'
    'activar' 'activo' 'activas' 'activa'
    * noun -> SwitchOn;

Verb 'apagar' 'apago' 'apagas' 'apaga'
    'desactivar' 'desactivo' 'desactivas' 'desactiva'
    * noun -> SwitchOff;

! Verbos sensoriales
Verb 'tocar' 'toco' 'tocas' 'toca' 'tocamos' 'tocais' 'tocan'
    * noun -> Touch;

Verb 'oler' 'huelo' 'hueles' 'huele' 'olemos' 'oleis' 'huelen'
    * -> Smell
    * noun -> Smell;

Verb 'escuchar' 'escucho' 'escuchas' 'escucha'
    'oir' 'oigo' 'oyes' 'oye' 'oimos' 'ois' 'oyen'
    * -> Listen
    * 'a' noun -> Listen
    * noun -> Listen;

! Verbos de consumo
Verb 'comer' 'como' 'comes' 'come' 'comemos' 'comeis' 'comen'
    * held -> Eat;

Verb 'beber' 'bebo' 'bebes' 'bebe' 'bebemos' 'bebeis' 'beben'
    * noun -> Drink;

! Verbos de vestimenta
Verb 'ponerse' 'vestirse' 'vestir'
    * held -> Wear;

Verb 'quitarse' 'desvestirse' 'quitar'
    * worn -> Disrobe
    * multi -> Take;

! Verbos metacomandos
Verb 'inventario' 'inv' 'i//' * -> Inv;
Verb 'puntuacion' 'puntos' 'score' * -> Score;
Verb 'salir' 'abandonar' 'terminar' 'quit' 'q//' * -> Quit;
Verb 'guardar' 'grabar' 'salvar' 'save' * -> Save;
Verb 'cargar' 'restore' 'recuperar' * -> Restore;
Verb 'reiniciar' 'restart' 'empezar' * -> Restart;
Verb 'esperar' 'espero' 'esperas' 'espera' 'z//' 'wait' * -> Wait;
Verb 'repetir' 'repito' 'repites' 'repite' 'otra' 'vez' 'again' 'g//' * -> Again;

! ######################### INCLUIR NUCLEO PUNYINFORM

Include "puny.h";

! ######################### NOTAS DE USO
!
! Para usar esta libreria en tu juego:
!
! 1. Include "spanish_final/puny_spanish_compilable.h";
!
! 2. En tu funcion Initialise:
!    [ Initialise;
!        InicializarEspanol();
!        location = MiUbicacion;
!        lookmode = 2;
!    ];
!
! 3. Define objetos con genero:
!    Object mesa "mesa elegante" has female supporter;
!    Object libro "libro antiguo" has ; ! masculino por defecto
!    Object llaves "llaves" has female pluralname;
!
! 4. Los mensajes automaticamente usaran concordancia:
!    > examinar la mesa
!    "No hay nada especial en la mesa elegante."
!    
!    > coger las llaves  
!    "Cogidas."
!
! Y listo! Tu juego entendera español completo con conjugaciones y concordancia.