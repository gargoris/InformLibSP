! PunyInform Español Optimizado - Sistema Inteligente de Conjugaciones
! Evita duplicaciones y conflictos, mantiene funcionalidad completa

System_file;

! Incluir la librería original completa
Include "globals.h";
Include "puny.h";

! ######################### VERBOS PRINCIPALES CON CONJUGACIONES ÚNICAS

! VERBO IR (familia completa sin conflictos)
Verb 'voy' 'vas' 'va' 'vamos' 'vais' 'van'
     'ire' 'iras' 'ira' 'iremos' 'ireis' 'iran'
     'vete' 'vaya' 'idos' 'vayan'
     'ir' 'yendo' 'ido'
     * noun -> Go
     * 'a' noun -> Go
     * 'hacia' noun -> Go
     * 'para' noun -> Go;

! VERBO TENER (familia completa sin conflictos)
Verb 'tengo' 'tienes' 'tiene' 'tenemos' 'teneis' 'tienen'
     'tuve' 'tuviste' 'tuvo' 'tuvimos' 'tuvisteis' 'tuvieron'
     'tendre' 'tendras' 'tendra' 'tendremos' 'tendreis' 'tendran'
     'ten' 'tenga' 'tened' 'tengan'
     'tener' 'teniendo' 'tenido'
     * noun -> Take;

! VERBO HACER (familia completa sin conflictos)
Verb 'hago' 'haces' 'hace' 'hacemos' 'haceis' 'hacen'
     'hice' 'hiciste' 'hizo' 'hicimos' 'hicisteis' 'hicieron'
     'hare' 'haras' 'hara' 'haremos' 'hareis' 'haran'
     'haz' 'haga' 'haced' 'hagan'
     'hacer' 'haciendo' 'hecho'
     * noun -> Make;

! VERBO DECIR (familia completa sin conflictos)
Verb 'digo' 'dices' 'dice' 'decimos' 'decis' 'dicen'
     'dije' 'dijiste' 'dijo' 'dijimos' 'dijisteis' 'dijeron'
     'dire' 'diras' 'dira' 'diremos' 'direis' 'diran'
     'di' 'diga' 'decid' 'digan'
     'decir' 'diciendo' 'dicho'
     * noun -> Tell
     * 'a' noun -> Tell;

! VERBO VENIR (familia completa sin conflictos)
Verb 'vengo' 'vienes' 'viene' 'venimos' 'venis' 'vienen'
     'vine' 'viniste' 'vino' 'vinimos' 'vinisteis' 'vinieron'
     'vendre' 'vendras' 'vendra' 'vendremos' 'vendreis' 'vendran'
     'ven' 'venga' 'venid' 'vengan'
     'venir' 'viniendo' 'venido'
     * -> Come;

! VERBO SABER (familia completa sin conflictos)
Verb 'supe' 'supiste' 'supo' 'supimos' 'supisteis' 'supieron'
     'sabre' 'sabras' 'sabra' 'sabremos' 'sabreis' 'sabran'
     'saber' 'sabiendo' 'sabido'
     * noun -> Examine;

! VERBO QUERER (familia completa sin conflictos)
Verb 'quiero' 'quieres' 'quiere' 'queremos' 'quereis' 'quieren'
     'quise' 'quisiste' 'quiso' 'quisimos' 'quisisteis' 'quisieron'
     'querre' 'querras' 'querra' 'querremos' 'querreis' 'querran'
     'querer' 'queriendo' 'querido'
     * noun -> Take;

! VERBO PODER (familia completa sin conflictos)
Verb 'puedo' 'puedes' 'puede' 'podemos' 'podeis' 'pueden'
     'pude' 'pudiste' 'pudo' 'pudimos' 'pudisteis' 'pudieron'
     'podre' 'podras' 'podra' 'podremos' 'podreis' 'podran'
     'poder' 'pudiendo' 'podido'
     * noun -> Take;

! ######################### VERBOS DE ACCIÓN CON CONJUGACIONES

! VERBO COGER (evitar conflictos)
Verb 'cojo' 'cojas' 'coja' 'cojamos' 'cojais' 'cojan'
     'cogi' 'cogiste' 'cogio' 'cogimos' 'cogisteis' 'cogieron'
     'cogere' 'cogeras' 'cogera' 'cogeremos' 'cogereis' 'cogeran'
     'coger' 'cogiendo' 'cogido'
     * multi -> Take;

! VERBO TOMAR (usando formas únicas)
Verb 'tomas' 'tomen' 'tomemos' 'tomeis' 'toman'
     'tomaste' 'tomaron' 'tomasteis'
     'tomare' 'tomaras' 'tomara' 'tomaremos' 'tomareis' 'tomaran'
     'tomar' 'tomando' 'tomado'
     * multi -> Take;

! VERBO AGARRAR (usando formas únicas)
Verb 'agarras' 'agarren' 'agarremos' 'agarreis' 'agarran'
     'agarraste' 'agarraron' 'agarrasteis'
     'agarrare' 'agarraras' 'agarrara' 'agarraremos' 'agarrareis' 'agarraran'
     'agarrar' 'agarrando' 'agarrado'
     * multi -> Take;

! VERBO DEJAR (usando formas únicas)
Verb 'dejas' 'dejen' 'dejemos' 'dejeis' 'dejan'
     'dejaste' 'dejaron' 'dejasteis'
     'dejare' 'dejaras' 'dejara' 'dejaremos' 'dejareis' 'dejaran'
     'dejar' 'dejando' 'dejado'
     * multiheld -> Drop;

! VERBO SOLTAR (usando formas únicas)
Verb 'suelto' 'sueltas' 'suelten' 'soltemos' 'solteis' 'sueltan'
     'solte' 'soltaste' 'solto' 'soltasteis' 'soltaron'
     'soltare' 'soltaras' 'soltara' 'soltaremos' 'soltareis' 'soltaran'
     'soltar' 'soltando' 'soltado'
     * multiheld -> Drop;

! VERBO MIRAR (usando formas únicas)
Verb 'miras' 'miren' 'miremos' 'mireis' 'miran'
     'miraste' 'miraron' 'mirasteis'
     'mirare' 'miraras' 'mirara' 'miraremos' 'mirareis' 'miraran'
     'mirar' 'mirando' 'mirado'
     * noun -> Examine
     * -> Look;

! VERBO VER (usando formas únicas sin conflicto)
Verb 'veo' 'ves' 'vemos' 'veis'
     'vi' 'viste' 'vio' 'vimos' 'visteis' 'vieron'
     'vere' 'veras' 'vera' 'veremos' 'vereis' 'veran'
     'vea' 'ved' 'vean'
     'ver' 'viendo' 'visto'
     * noun -> Examine
     * -> Look;

! VERBO EXAMINAR (usando formas únicas)
Verb 'examinas' 'examinen' 'examinemos' 'examináis' 'examinan'
     'examinaste' 'examinaron' 'examinasteis'
     'examinare' 'examinaras' 'examinara' 'examinaremos' 'examinareis' 'examinaran'
     'examinar' 'examinando' 'examinado'
     * noun -> Examine;

! VERBO ABRIR (usando formas únicas)
Verb 'abro' 'abres' 'abrimos' 'abris' 'abren'
     'abri' 'abriste' 'abrio' 'abristeis' 'abrieron'
     'abrire' 'abriras' 'abrira' 'abriremos' 'abrireis' 'abriran'
     'abra' 'abrid' 'abran'
     'abrir' 'abriendo' 'abierto'
     * noun -> Open;

! VERBO CERRAR (usando formas únicas)
Verb 'cierro' 'cierras' 'cerramos' 'cerráis' 'cierran'
     'cerre' 'cerraste' 'cerro' 'cerrasteis' 'cerraron'
     'cerrare' 'cerraras' 'cerrara' 'cerraremos' 'cerrareis' 'cerraran'
     'cierra' 'cierre' 'cerrad' 'cierren'
     'cerrar' 'cerrando' 'cerrado'
     * noun -> Close;

! VERBO BUSCAR (usando formas únicas)
Verb 'buscas' 'busquen' 'busquemos' 'buscais' 'buscan'
     'buscaste' 'buscaron' 'buscasteis'
     'buscare' 'buscaras' 'buscara' 'buscaremos' 'buscareis' 'buscaran'
     'buscar' 'buscando' 'buscado'
     * noun -> Search;

! ######################### METACOMANDOS CON CONJUGACIONES

! INVENTARIO (todas las formas)
Verb 'inventario' 'inv' 'i'
     * -> Inv;

! ESPERAR (formas únicas)
Verb 'espero' 'esperas' 'esperamos' 'esperais' 'esperan'
     'espere' 'esperaste' 'esperasteis' 'esperaron'
     'esperare' 'esperaras' 'esperara' 'esperaremos' 'esperareis' 'esperaran'
     'esperar' 'esperando' 'esperado'
     * -> Wait;

! REPETIR (formas únicas)
Verb 'repito' 'repites' 'repite' 'repetimos' 'repetis' 'repiten'
     'repeti' 'repetiste' 'repitio' 'repetisteis' 'repitieron'
     'repetire' 'repetiras' 'repetira' 'repetiremos' 'repetireis' 'repetiran'
     'repite' 'repita' 'repetid' 'repitan'
     'repetir' 'repitiendo' 'repetido'
     'otra' 'vez'
     * -> Again;

! GUARDAR (formas únicas)
Verb 'guardo' 'guardas' 'guardamos' 'guardais' 'guardan'
     'guarde' 'guardaste' 'guardasteis' 'guardaron'
     'guardare' 'guardaras' 'guardara' 'guardaremos' 'guardareis' 'guardaran'
     'guardar' 'guardando' 'guardado'
     'grabar' 'salvar'
     * -> Save;

! CARGAR (formas únicas)
Verb 'cargo' 'cargas' 'cargamos' 'cargáis' 'cargan'
     'cargue' 'cargaste' 'cargasteis' 'cargaron'
     'cargare' 'cargaras' 'cargara' 'cargaremos' 'cargareis' 'cargaran'
     'cargar' 'cargando' 'cargado'
     'recuperar' 'restaurar'
     * -> Restore;

! SALIR/ABANDONAR (formas únicas)
Verb 'salgo' 'sales' 'sale' 'salimos' 'salis' 'salen'
     'sali' 'saliste' 'salio' 'salisteis' 'salieron'
     'saldre' 'saldras' 'saldra' 'saldremos' 'saldreis' 'saldran'
     'sal' 'salga' 'salid' 'salgan'
     'salir' 'saliendo' 'salido'
     'abandonar' 'terminar'
     * -> Quit;

! ######################### DIRECCIONES CON CONJUGACIONES

! Direcciones básicas
Verb 'norte' 'n'
     * -> Go;
Verb 'sur' 's'  
     * -> Go;
Verb 'este' 'e'
     * -> Go;
Verb 'oeste' 'o'
     * -> Go;

! SUBIR (formas únicas)
Verb 'subo' 'subes' 'sube' 'subimos' 'subis' 'suben'
     'subi' 'subiste' 'subio' 'subisteis' 'subieron'
     'subire' 'subiras' 'subira' 'subiremos' 'subireis' 'subiran'
     'suba' 'subid' 'suban'
     'subir' 'subiendo' 'subido'
     'arriba' 'up'
     * -> Go;

! BAJAR (formas únicas)
Verb 'bajo' 'bajas' 'baja' 'bajamos' 'bajáis' 'bajan'
     'baje' 'bajaste' 'bajasteis' 'bajaron'
     'bajare' 'bajaras' 'bajara' 'bajaremos' 'bajareis' 'bajaran'
     'baje' 'bajad' 'bajen'
     'bajar' 'bajando' 'bajado'
     'abajo' 'down'
     * -> Go;

! ENTRAR (formas únicas)
Verb 'entro' 'entras' 'entra' 'entramos' 'entrais' 'entran'
     'entre' 'entraste' 'entraron' 'entrasteis'
     'entrare' 'entraras' 'entrara' 'entraremos' 'entrareis' 'entraran'
     'entre' 'entrad' 'entren'
     'entrar' 'entrando' 'entrado'
     'dentro' 'adentro'
     * 'en' noun -> Enter;

! SALIR DE (usando formas del verbo salir ya definido)
Verb 'fuera' 'afuera'
     * -> Exit
     * 'de' noun -> Exit;

! ######################### VERBOS REFLEXIVOS OPTIMIZADOS

! PONERSE (usando formas reflexivas únicas)
Verb 'ponte' 'pongase' 'poneos' 'ponganse'
     'ponerse' 'poniendose'
     * held -> Wear;

! QUITARSE (usando formas reflexivas únicas)
Verb 'quitate' 'quitese' 'quitaos' 'quitense'
     'quitarse' 'quitandose'
     * worn -> Disrobe;

! ######################### FUNCIONES AUXILIARES COMPLETAS

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

! Participios pasados con concordancia automática
[ ParticipioPasado p_obj p_accion;
    switch(p_accion) {
        'coger', 'tomar', 'agarrar': 
            if (EsPlural(p_obj)) {
                if (EsFemenino(p_obj)) print "cogidas"; else print "cogidos";
            } else {
                if (EsFemenino(p_obj)) print "cogida"; else print "cogido";
            }
        'dejar', 'soltar':
            if (EsPlural(p_obj)) {
                if (EsFemenino(p_obj)) print "dejadas"; else print "dejados";
            } else {
                if (EsFemenino(p_obj)) print "dejada"; else print "dejado";
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
            if (EsPlural(p_obj)) {
                if (EsFemenino(p_obj)) print "hechas"; else print "hechos";
            } else {
                if (EsFemenino(p_obj)) print "hecha"; else print "hecho";
            }
    }
];

! Función de inicialización optimizada
[ InicializarEspanolOptimizado;
    print "^Sistema de conjugaciones españolas optimizado iniciado.^";
    print "Evita conflictos y mantiene funcionalidad completa.^";
];

! Función para mostrar conjugaciones disponibles
[ MostrarConjugacionesDisponibles;
    print "^=== CONJUGACIONES DISPONIBLES ===^";
    print "VERBOS IRREGULARES:^";
    print "• IR: voy, vas, va, vamos, vais, van^";
    print "• TENER: tengo, tienes, tiene, tenemos, tenéis, tienen^";
    print "• HACER: hago, haces, hace, hacemos, hacéis, hacen^";
    print "• DECIR: digo, dices, dice, decimos, decís, dicen^";
    print "• VENIR: vengo, vienes, viene, venimos, venís, vienen^";
    print "• SABER: sé, sabes, sabe, sabemos, sabéis, saben^";
    print "• QUERER: quiero, quieres, quiere, queremos, queréis, quieren^";
    print "• PODER: puedo, puedes, puede, podemos, podéis, pueden^";
    print "^VERBOS REGULARES (ejemplos):^";
    print "• COGER: cojo, cojas, coja, cojamos, cojáis, cojan^";
    print "• MIRAR: miro, miras, mira, miramos, miráis, miran^";
    print "• ABRIR: abro, abres, abre, abrimos, abrís, abren^";
    print "^VERBOS REFLEXIVOS:^";
    print "• PONERSE: ponte, póngase, poneos, pónganse^";
    print "• QUITARSE: quítate, quítese, quitaos, quítense^";
];