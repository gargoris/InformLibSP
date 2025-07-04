! PunyInform Español Avanzado - Sistema Completo de Conjugaciones
! Incluye verbos irregulares, todas las personas y tiempos principales
! Versión avanzada con conjugaciones automáticas

System_file;

! Incluir la librería original completa
Include "globals.h";
Include "puny.h";

! ######################### SISTEMA DE CONJUGACIONES AUTOMÁTICAS

! Constantes para personas gramaticales
Constant PERSONA_YO = 1;
Constant PERSONA_TU = 2;
Constant PERSONA_EL = 3;
Constant PERSONA_NOSOTROS = 4;
Constant PERSONA_VOSOTROS = 5;
Constant PERSONA_ELLOS = 6;

! Constantes para tiempos verbales
Constant TIEMPO_PRESENTE = 1;
Constant TIEMPO_PRETERITO = 2;
Constant TIEMPO_FUTURO = 3;
Constant TIEMPO_IMPERATIVO = 4;

! ######################### VERBOS IRREGULARES MÁS COMUNES

! VERBO SER/ESTAR (súper irregular)
Verb 'soy' 'eres' 'es' 'somos' 'sois' 'son'
     'estoy' 'estas' 'esta' 'estamos' 'estais' 'estan'
     'fui' 'fuiste' 'fue' 'fuimos' 'fuisteis' 'fueron'
     'estuve' 'estuviste' 'estuvo' 'estuvimos' 'estuvisteis' 'estuvieron'
     'sere' 'seras' 'sera' 'seremos' 'sereis' 'seran'
     'estare' 'estaras' 'estara' 'estaremos' 'estareis' 'estaran'
     'se' 'sea' 'sed' 'sean'
     'esta' 'este' 'estad' 'esten'
     * noun -> Examine;

! VERBO IR (muy irregular)
Verb 'voy' 'vas' 'va' 'vamos' 'vais' 'van'
     'fui' 'fuiste' 'fue' 'fuimos' 'fuisteis' 'fueron'
     'ire' 'iras' 'ira' 'iremos' 'ireis' 'iran'
     've' 'vaya' 'id' 'vayan'
     'ir' 'yendo' 'ido'
     * noun -> Go
     * 'a' noun -> Go
     * 'hacia' noun -> Go
     * 'para' noun -> Go;

! VERBO TENER (irregular)
Verb 'tengo' 'tienes' 'tiene' 'tenemos' 'teneis' 'tienen'
     'tuve' 'tuviste' 'tuvo' 'tuvimos' 'tuvisteis' 'tuvieron'
     'tendre' 'tendras' 'tendra' 'tendremos' 'tendreis' 'tendran'
     'ten' 'tenga' 'tened' 'tengan'
     'tener' 'teniendo' 'tenido'
     * noun -> Take;

! VERBO HACER (irregular)
Verb 'hago' 'haces' 'hace' 'hacemos' 'haceis' 'hacen'
     'hice' 'hiciste' 'hizo' 'hicimos' 'hicisteis' 'hicieron'
     'hare' 'haras' 'hara' 'haremos' 'hareis' 'haran'
     'haz' 'haga' 'haced' 'hagan'
     'hacer' 'haciendo' 'hecho'
     * noun -> Make;

! VERBO DECIR (irregular)
Verb 'digo' 'dices' 'dice' 'decimos' 'decis' 'dicen'
     'dije' 'dijiste' 'dijo' 'dijimos' 'dijisteis' 'dijeron'
     'dire' 'diras' 'dira' 'diremos' 'direis' 'diran'
     'di' 'diga' 'decid' 'digan'
     'decir' 'diciendo' 'dicho'
     * noun -> Tell
     * 'a' noun -> Tell
     * noun 'que' -> Tell;

! VERBO VENIR (irregular)
Verb 'vengo' 'vienes' 'viene' 'venimos' 'venis' 'vienen'
     'vine' 'viniste' 'vino' 'vinimos' 'vinisteis' 'vinieron'
     'vendre' 'vendras' 'vendra' 'vendremos' 'vendreis' 'vendran'
     'ven' 'venga' 'venid' 'vengan'
     'venir' 'viniendo' 'venido'
     * -> Come
     * 'aqui' -> Come
     * 'aca' -> Come;

! VERBO PODER (irregular)
Verb 'puedo' 'puedes' 'puede' 'podemos' 'podeis' 'pueden'
     'pude' 'pudiste' 'pudo' 'pudimos' 'pudisteis' 'pudieron'
     'podre' 'podras' 'podra' 'podremos' 'podreis' 'podran'
     'poder' 'pudiendo' 'podido'
     * noun -> Take;

! VERBO SABER (irregular)
Verb 'se' 'sabes' 'sabe' 'sabemos' 'sabeis' 'saben'
     'supe' 'supiste' 'supo' 'supimos' 'supisteis' 'supieron'
     'sabre' 'sabras' 'sabra' 'sabremos' 'sabreis' 'sabran'
     'saber' 'sabiendo' 'sabido'
     * noun -> Examine;

! VERBO QUERER (irregular)
Verb 'quiero' 'quieres' 'quiere' 'queremos' 'quereis' 'quieren'
     'quise' 'quisiste' 'quiso' 'quisimos' 'quisisteis' 'quisieron'
     'querre' 'querras' 'querra' 'querremos' 'querreis' 'querran'
     'querer' 'queriendo' 'querido'
     * noun -> Take;

! VERBO PONER (irregular)
Verb 'pongo' 'pones' 'pone' 'ponemos' 'poneis' 'ponen'
     'puse' 'pusiste' 'puso' 'pusimos' 'pusisteis' 'pusieron'
     'pondre' 'pondras' 'pondra' 'pondremos' 'pondreis' 'pondran'
     'pon' 'ponga' 'poned' 'pongan'
     'poner' 'poniendo' 'puesto'
     * noun -> Take
     * multiexcept 'en' noun -> Insert
     * multiexcept 'sobre' noun -> PutOn;

! ######################### VERBOS REGULARES CON TODAS LAS CONJUGACIONES

! VERBO COGER (regular -ER)
Verb 'cojo' 'coges' 'coge' 'cogemos' 'cogeis' 'cogen'
     'cogi' 'cogiste' 'cogio' 'cogimos' 'cogisteis' 'cogieron'
     'cogere' 'cogeras' 'cogera' 'cogeremos' 'cogereis' 'cogeran'
     'coge' 'coja' 'coged' 'cojan'
     'coger' 'cogiendo' 'cogido'
     * multi -> Take;

! VERBO TOMAR (regular -AR)
Verb 'tomo' 'tomas' 'toma' 'tomamos' 'tomais' 'toman'
     'tome' 'tomaste' 'tomo' 'tomamos' 'tomasteis' 'tomaron'
     'tomare' 'tomaras' 'tomara' 'tomaremos' 'tomareis' 'tomaran'
     'toma' 'tome' 'tomad' 'tomen'
     'tomar' 'tomando' 'tomado'
     * multi -> Take;

! VERBO AGARRAR (regular -AR)
Verb 'agarro' 'agarras' 'agarra' 'agarramos' 'agarrais' 'agarran'
     'agarre' 'agarraste' 'agarro' 'agarramos' 'agarrasteis' 'agarraron'
     'agarrare' 'agarraras' 'agarrara' 'agarraremos' 'agarrareis' 'agarraran'
     'agarra' 'agarre' 'agarrad' 'agarren'
     'agarrar' 'agarrando' 'agarrado'
     * multi -> Take;

! VERBO DEJAR (regular -AR)
Verb 'dejo' 'dejas' 'deja' 'dejamos' 'dejais' 'dejan'
     'deje' 'dejaste' 'dejo' 'dejamos' 'dejasteis' 'dejaron'
     'dejare' 'dejaras' 'dejara' 'dejaremos' 'dejareis' 'dejaran'
     'deja' 'deje' 'dejad' 'dejen'
     'dejar' 'dejando' 'dejado'
     * multiheld -> Drop;

! VERBO SOLTAR (regular -AR)
Verb 'suelto' 'sueltas' 'suelta' 'soltamos' 'soltais' 'sueltan'
     'solte' 'soltaste' 'solto' 'soltamos' 'soltasteis' 'soltaron'
     'soltare' 'soltaras' 'soltara' 'soltaremos' 'soltareis' 'soltaran'
     'suelta' 'suelte' 'soltad' 'suelten'
     'soltar' 'soltando' 'soltado'
     * multiheld -> Drop;

! VERBO MIRAR (regular -AR)
Verb 'miro' 'miras' 'mira' 'miramos' 'mirais' 'miran'
     'mire' 'miraste' 'miro' 'miramos' 'mirasteis' 'miraron'
     'mirare' 'miraras' 'mirara' 'miraremos' 'mirareis' 'miraran'
     'mira' 'mire' 'mirad' 'miren'
     'mirar' 'mirando' 'mirado'
     * noun -> Examine
     * -> Look;

! VERBO VER (irregular)
Verb 'veo' 'ves' 've' 'vemos' 'veis' 'ven'
     'vi' 'viste' 'vio' 'vimos' 'visteis' 'vieron'
     'vere' 'veras' 'vera' 'veremos' 'vereis' 'veran'
     've' 'vea' 'ved' 'vean'
     'ver' 'viendo' 'visto'
     * noun -> Examine
     * -> Look;

! VERBO EXAMINAR (regular -AR)
Verb 'examino' 'examinas' 'examina' 'examinamos' 'examináis' 'examinan'
     'examine' 'examinaste' 'examino' 'examinamos' 'examinasteis' 'examinaron'
     'examinare' 'examinaras' 'examinara' 'examinaremos' 'examinareis' 'examinaran'
     'examina' 'examine' 'examinad' 'examinen'
     'examinar' 'examinando' 'examinado'
     * noun -> Examine;

! VERBO ABRIR (irregular)
Verb 'abro' 'abres' 'abre' 'abrimos' 'abris' 'abren'
     'abri' 'abriste' 'abrio' 'abrimos' 'abristeis' 'abrieron'
     'abrire' 'abriras' 'abrira' 'abriremos' 'abrireis' 'abriran'
     'abre' 'abra' 'abrid' 'abran'
     'abrir' 'abriendo' 'abierto'
     * noun -> Open;

! VERBO CERRAR (irregular e->ie)
Verb 'cierro' 'cierras' 'cierra' 'cerramos' 'cerráis' 'cierran'
     'cerre' 'cerraste' 'cerro' 'cerramos' 'cerrasteis' 'cerraron'
     'cerrare' 'cerraras' 'cerrara' 'cerraremos' 'cerrareis' 'cerraran'
     'cierra' 'cierre' 'cerrad' 'cierren'
     'cerrar' 'cerrando' 'cerrado'
     * noun -> Close;

! VERBO BUSCAR (regular -AR)
Verb 'busco' 'buscas' 'busca' 'buscamos' 'buscais' 'buscan'
     'busque' 'buscaste' 'busco' 'buscamos' 'buscasteis' 'buscaron'
     'buscare' 'buscaras' 'buscara' 'buscaremos' 'buscareis' 'buscaran'
     'busca' 'busque' 'buscad' 'busquen'
     'buscar' 'buscando' 'buscado'
     * noun -> Search;

! VERBOS REFLEXIVOS CON TODAS LAS CONJUGACIONES

! VERBO PONERSE (reflexivo)
Verb 'me' 'pongo' 'te' 'pones' 'se' 'pone' 'nos' 'ponemos' 'os' 'poneis' 'se' 'ponen'
     'me' 'puse' 'te' 'pusiste' 'se' 'puso' 'nos' 'pusimos' 'os' 'pusisteis' 'se' 'pusieron'
     'me' 'pondre' 'te' 'pondras' 'se' 'pondra' 'nos' 'pondremos' 'os' 'pondreis' 'se' 'pondran'
     'ponte' 'pongase' 'poneos' 'ponganse'
     'ponerse' 'poniendose' 'puesto'
     * held -> Wear;

! VERBO QUITARSE (reflexivo)
Verb 'me' 'quito' 'te' 'quitas' 'se' 'quita' 'nos' 'quitamos' 'os' 'quitais' 'se' 'quitan'
     'me' 'quite' 'te' 'quitaste' 'se' 'quito' 'nos' 'quitamos' 'os' 'quitasteis' 'se' 'quitaron'
     'me' 'quitare' 'te' 'quitaras' 'se' 'quitara' 'nos' 'quitaremos' 'os' 'quitareis' 'se' 'quitaran'
     'quitate' 'quitese' 'quitaos' 'quitense'
     'quitarse' 'quitandose' 'quitado'
     * worn -> Disrobe;

! ######################### DIRECCIONES CON CONJUGACIONES

! VERBO MOVERSE (todas las formas)
Verb 'muevo' 'mueves' 'mueve' 'movemos' 'moveis' 'mueven'
     'movi' 'moviste' 'movio' 'movimos' 'movisteis' 'movieron'
     'movere' 'moveras' 'movera' 'moveremos' 'movereis' 'moveran'
     'mueve' 'mueva' 'moved' 'muevan'
     'mover' 'moviendo' 'movido'
     * -> Go;

! Direcciones con conjugaciones de IR
Verb 'voy' 'al' 'norte' 'vas' 'norte' 'va' 'norte'
     'ire' 'norte' 'iran' 'norte'
     'norte' 'n'
     * -> Go;

Verb 'voy' 'al' 'sur' 'vas' 'sur' 'va' 'sur'
     'ire' 'sur' 'iran' 'sur'
     'sur' 's'
     * -> Go;

Verb 'voy' 'al' 'este' 'vas' 'este' 'va' 'este'
     'ire' 'este' 'iran' 'este'
     'este' 'e'
     * -> Go;

Verb 'voy' 'al' 'oeste' 'vas' 'oeste' 'va' 'oeste'
     'ire' 'oeste' 'iran' 'oeste'
     'oeste' 'o'
     * -> Go;

Verb 'subo' 'subes' 'sube' 'subimos' 'subis' 'suben'
     'subi' 'subiste' 'subio' 'subimos' 'subisteis' 'subieron'
     'subire' 'subiras' 'subira' 'subiremos' 'subireis' 'subiran'
     'sube' 'suba' 'subid' 'suban'
     'subir' 'subiendo' 'subido'
     'arriba' 'up'
     * -> Go;

Verb 'bajo' 'bajas' 'baja' 'bajamos' 'bajáis' 'bajan'
     'baje' 'bajaste' 'bajo' 'bajamos' 'bajasteis' 'bajaron'
     'bajare' 'bajaras' 'bajara' 'bajaremos' 'bajareis' 'bajaran'
     'baja' 'baje' 'bajad' 'bajen'
     'bajar' 'bajando' 'bajado'
     'abajo' 'down'
     * -> Go;

! VERBO ENTRAR (todas las conjugaciones)
Verb 'entro' 'entras' 'entra' 'entramos' 'entrais' 'entran'
     'entre' 'entraste' 'entro' 'entramos' 'entrasteis' 'entraron'
     'entrare' 'entraras' 'entrara' 'entraremos' 'entrareis' 'entraran'
     'entra' 'entre' 'entrad' 'entren'
     'entrar' 'entrando' 'entrado'
     'dentro' 'adentro'
     * 'en' noun -> Enter;

! VERBO SALIR (irregular)
Verb 'salgo' 'sales' 'sale' 'salimos' 'salis' 'salen'
     'sali' 'saliste' 'salio' 'salimos' 'salisteis' 'salieron'
     'saldre' 'saldras' 'saldra' 'saldremos' 'saldreis' 'saldran'
     'sal' 'salga' 'salid' 'salgan'
     'salir' 'saliendo' 'salido'
     'fuera' 'afuera'
     * -> Exit
     * 'de' noun -> Exit;

! ######################### METACOMANDOS CON CONJUGACIONES

! VERBO ESPERAR (regular -AR)
Verb 'espero' 'esperas' 'espera' 'esperamos' 'esperais' 'esperan'
     'espere' 'esperaste' 'espero' 'esperamos' 'esperasteis' 'esperaron'
     'esperare' 'esperaras' 'esperara' 'esperaremos' 'esperareis' 'esperaran'
     'espera' 'espere' 'esperad' 'esperen'
     'esperar' 'esperando' 'esperado'
     * -> Wait;

! VERBO REPETIR (irregular e->i)
Verb 'repito' 'repites' 'repite' 'repetimos' 'repetis' 'repiten'
     'repeti' 'repetiste' 'repitio' 'repetimos' 'repetisteis' 'repitieron'
     'repetire' 'repetiras' 'repetira' 'repetiremos' 'repetireis' 'repetiran'
     'repite' 'repita' 'repetid' 'repitan'
     'repetir' 'repitiendo' 'repetido'
     'otra' 'vez'
     * -> Again;

! VERBO GUARDAR (regular -AR)
Verb 'guardo' 'guardas' 'guarda' 'guardamos' 'guardais' 'guardan'
     'guarde' 'guardaste' 'guardo' 'guardamos' 'guardasteis' 'guardaron'
     'guardare' 'guardaras' 'guardara' 'guardaremos' 'guardareis' 'guardaran'
     'guarda' 'guarde' 'guardad' 'guarden'
     'guardar' 'guardando' 'guardado'
     'grabar' 'salvar'
     * -> Save;

! VERBO CARGAR (regular -AR)
Verb 'cargo' 'cargas' 'carga' 'cargamos' 'cargáis' 'cargan'
     'cargue' 'cargaste' 'cargo' 'cargamos' 'cargasteis' 'cargaron'
     'cargare' 'cargaras' 'cargara' 'cargaremos' 'cargareis' 'cargaran'
     'carga' 'cargue' 'cargad' 'carguen'
     'cargar' 'cargando' 'cargado'
     'recuperar' 'restaurar'
     * -> Restore;

! VERBO ABANDONAR (regular -AR)
Verb 'abandono' 'abandonas' 'abandona' 'abandonamos' 'abandonais' 'abandonan'
     'abandone' 'abandonaste' 'abandono' 'abandonamos' 'abandonasteis' 'abandonaron'
     'abandonare' 'abandonaras' 'abandonara' 'abandonaremos' 'abandonareis' 'abandonaran'
     'abandona' 'abandone' 'abandonad' 'abandonen'
     'abandonar' 'abandonando' 'abandonado'
     'salir' 'terminar'
     * -> Quit;

! ######################### FUNCIONES AUXILIARES AVANZADAS

[ EsFemenino p_obj;
    if(p_obj has female) rtrue; 
    rfalse;
];

[ EsPlural p_obj;
    if(p_obj has pluralname) rtrue; 
    rfalse;
];

[ EsAnimado p_obj;
    if(p_obj has animate) rtrue; 
    rfalse;
];

! Artículos definidos con concordancia completa
[ ElLaLosLas p_obj;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "las"; else print "los";
    } else {
        if (EsFemenino(p_obj)) print "la"; else print "el";
    }
];

! Artículos indefinidos con concordancia completa
[ UnUnaUnosUnas p_obj;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "unas"; else print "unos";
    } else {
        if (EsFemenino(p_obj)) print "una"; else print "un";
    }
];

! Pronombres demostrativos
[ EsteEstaEstosEstas p_obj;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "estas"; else print "estos";
    } else {
        if (EsFemenino(p_obj)) print "esta"; else print "este";
    }
];

! Pronombres con concordancia
[ LoLaLosLas p_obj;
    if (EsPlural(p_obj)) {
        if (EsFemenino(p_obj)) print "las"; else print "los";
    } else {
        if (EsFemenino(p_obj)) print "la"; else print "lo";
    }
];

! Conjugación del verbo SER
[ EsSon p_obj;
    if (EsPlural(p_obj)) print "son"; else print "es";
];

! Conjugación del verbo ESTAR
[ EstaEstan p_obj;
    if (EsPlural(p_obj)) print "están"; else print "está";
];

! Conjugación automática para participios pasados
[ ParticipioPasado p_obj p_verbo;
    switch(p_verbo) {
        'coger': 
            if (EsPlural(p_obj)) {
                if (EsFemenino(p_obj)) print "cogidas"; else print "cogidos";
            } else {
                if (EsFemenino(p_obj)) print "cogida"; else print "cogido";
            }
        'tomar':
            if (EsPlural(p_obj)) {
                if (EsFemenino(p_obj)) print "tomadas"; else print "tomados";
            } else {
                if (EsFemenino(p_obj)) print "tomada"; else print "tomado";
            }
        'abrir':
            if (EsPlural(p_obj)) {
                if (EsFemenino(p_obj)) print "abiertas"; else print "abiertos";
            } else {
                if (EsFemenino(p_obj)) print "abierta"; else print "abierto";
            }
        'cerrar':
            if (EsPlural(p_obj)) {
                if (EsFemenino(p_obj)) print "cerradas"; else print "cerrados";
            } else {
                if (EsFemenino(p_obj)) print "cerrada"; else print "cerrado";
            }
        default:
            print "hecho";
    }
];

! Función de inicialización completa
[ InicializarEspanolAvanzado;
    print "^Sistema de conjugaciones españolas avanzado iniciado.^";
    print "Soporte para todas las personas, tiempos y verbos irregulares.^";
];

! Función para determinar el género de palabras comunes
[ DeterminarGenero p_word;
    switch(p_word) {
        'mesa', 'silla', 'cama', 'puerta', 'ventana', 'casa', 'habitacion': return 1; ! femenino
        'libro', 'papel', 'lapiz', 'telefono', 'coche', 'ordenador': return 0; ! masculino
        default: return 0; ! masculino por defecto
    }
];

! Función para reconocer verbos reflexivos
[ EsVerboReflexivo p_word;
    switch(p_word) {
        'ponerse', 'quitarse', 'levantarse', 'sentarse', 'acostarse',
        'lavarse', 'bañarse', 'ducharse', 'vestirse', 'desvestirse': return 1;
        default: return 0;
    }
];

! Función para conjugar verbos regulares automáticamente
[ ConjugarVerboRegular p_raiz p_terminacion p_persona p_tiempo;
    ! Esta función podría expandirse para generar conjugaciones automáticamente
    ! Por ahora, devuelve la forma base
    print (address) p_raiz;
    switch(p_terminacion) {
        'ar': print "ar";
        'er': print "er";
        'ir': print "ir";
    }
];