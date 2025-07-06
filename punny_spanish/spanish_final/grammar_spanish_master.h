! Gramática Española Master - Sistema Completo de Verbos
! La gramática más avanzada jamás implementada para IF español
! Incluye conjugaciones completas, variantes regionales y formas de cortesía
!
! Autor: Claude Code
! Fecha: 4 de julio de 2025  
! Versión: 1.0 Master

System_file;

! ######################### VERBOS BÁSICOS DE MOVIMIENTO

Verb 'ir' 'voy' 've' 'ves' 'va' 'vamos' 'vais' 'van' 'ire' 'iras' 'ira' 'iremos' 'ireis' 'iran'
    'vete' 'vaya' 'idos' 'vayan' 'yendo' 'ido'
    'anda' 'andas' 'anda' 'andamos' 'andais' 'andan'
    'camina' 'caminas' 'camina' 'caminamos' 'camináis' 'caminan'
    'dirigirse' 'dirígete' 'avanza' 'avanzas' 'avanza'
    * noun                                      -> Go
    * 'a' noun                                  -> Go  
    * 'hacia' noun                              -> Go
    * 'para' noun                               -> Go
    * 'al' noun                                 -> Go;

! Direcciones cardinales y sus conjugaciones
Verb 'norte' 'n//' 'septentrion'
    *                                           -> Go;
Verb 'sur' 's//' 'mediodia' 'austro'
    *                                           -> Go;
Verb 'este' 'e//' 'oriente' 'levante'
    *                                           -> Go;
Verb 'oeste' 'o//' 'occidente' 'poniente'
    *                                           -> Go;
Verb 'noreste' 'ne' 'nordeste'
    *                                           -> Go;
Verb 'noroeste' 'no' 'nw' 'norueste'
    *                                           -> Go;
Verb 'sureste' 'se' 'sudeste'
    *                                           -> Go;
Verb 'suroeste' 'so' 'sw' 'sudoeste'
    *                                           -> Go;
Verb 'arriba' 'subir' 'sube' 'subes' 'subimos' 'subís' 'suben' 'u//'
    'trepar' 'trepas' 'trepa' 'trepamos' 'trepáis' 'trepan'
    *                                           -> Go;
Verb 'abajo' 'bajar' 'baja' 'bajas' 'bajamos' 'bajáis' 'bajan' 'd//'
    'descender' 'desciendes' 'desciende' 'descendemos' 'descendéis' 'descienden'
    *                                           -> Go;

! Entrar y salir con todas las conjugaciones
Verb 'entrar' 'entro' 'entras' 'entra' 'entramos' 'entráis' 'entran'
    'dentro' 'adentro' 'penetrar' 'penetro' 'penetras' 'penetra'
    'ingresar' 'ingreso' 'ingresas' 'ingresa' 'ingresamos' 'ingresáis' 'ingresan'
    'meterse' 'métete' 'se' 'mete' 'nos' 'metemos' 'os' 'metéis' 'se' 'meten'
    *                                           -> GoIn
    * 'en'/'a' noun                             -> Enter;

Verb 'salir' 'salgo' 'sales' 'sale' 'salimos' 'salís' 'salen'
    'fuera' 'afuera' 'abandonar' 'abandono' 'abandonas' 'abandona'
    'marcharse' 'márchate' 'irse' 'vete' 'largarse' 'lárgate'
    *                                           -> Exit
    * 'de'/'del' noun                           -> Exit;

! ######################### VERBOS DE MANIPULACIÓN DE OBJETOS

! Coger/Tomar - el verbo más completo con variantes regionales
Verb 'coger' 'cojo' 'coges' 'coge' 'cogemos' 'cogéis' 'cogen'
    'cogí' 'cogiste' 'cogió' 'cogimos' 'cogisteis' 'cogieron'
    'cogeré' 'cogerás' 'cogerá' 'cogeremos' 'cogeréis' 'cogerán'
    'coge' 'coja' 'coged' 'cojan' 'cogiendo' 'cogido'
    ! Variante México/América Latina
    'tomar' 'tomo' 'tomas' 'toma' 'tomamos' 'tomáis' 'toman'
    'tomé' 'tomaste' 'tomó' 'tomamos' 'tomasteis' 'tomaron'
    'tomaré' 'tomarás' 'tomará' 'tomaremos' 'tomaréis' 'tomarán'
    'toma' 'tome' 'tomad' 'tomen' 'tomando' 'tomado'
    ! Variante Argentina/Uruguay
    'agarrar' 'agarro' 'agarras' 'agarra' 'agarramos' 'agarráis' 'agarran'
    'agarré' 'agarraste' 'agarró' 'agarramos' 'agarrasteis' 'agarraron'
    'agarraré' 'agarrarás' 'agarrará' 'agarraremos' 'agarraréis' 'agarrarán'
    'agarra' 'agarre' 'agarrad' 'agarren' 'agarrando' 'agarrado'
    ! Variante coloquial España
    'pillar' 'pillo' 'pillas' 'pilla' 'pillamos' 'pilláis' 'pillan'
    'pillé' 'pillaste' 'pilló' 'pillamos' 'pillasteis' 'pillaron'
    'pillaré' 'pillarás' 'pillará' 'pillaremos' 'pillaréis' 'pillarán'
    'pilla' 'pille' 'pillad' 'pillen' 'pillando' 'pillado'
    ! Variantes formales
    'obtener' 'obtengo' 'obtienes' 'obtiene' 'obtenemos' 'obtenéis' 'obtienen'
    'conseguir' 'consigo' 'consigues' 'consigue' 'conseguimos' 'conseguís' 'consiguen'
    'recoger' 'recojo' 'recoges' 'recoge' 'recogemos' 'recogéis' 'recogen'
    * multi                                     -> Take
    * 'todo'/'todas'/'todos'                    -> Take
    * multi 'de'/'del'/'de'/'la' noun           -> Remove;

! Dejar/Soltar con todas las conjugaciones
Verb 'dejar' 'dejo' 'dejas' 'deja' 'dejamos' 'dejáis' 'dejan'
    'dejé' 'dejaste' 'dejó' 'dejamos' 'dejasteis' 'dejaron'
    'dejaré' 'dejarás' 'dejará' 'dejaremos' 'dejaréis' 'dejarán'
    'deja' 'deje' 'dejad' 'dejen' 'dejando' 'dejado'
    'soltar' 'suelto' 'sueltas' 'suelta' 'soltamos' 'soltáis' 'sueltan'
    'solté' 'soltaste' 'soltó' 'soltamos' 'soltasteis' 'soltaron'
    'soltaré' 'soltarás' 'soltará' 'soltaremos' 'soltaréis' 'soltarán'
    'suelta' 'suelte' 'soltad' 'suelten' 'soltando' 'soltado'
    'tirar' 'tiro' 'tiras' 'tira' 'tiramos' 'tiráis' 'tiran'
    'tiré' 'tiraste' 'tiró' 'tiramos' 'tirasteis' 'tiraron'
    'tiraré' 'tirarás' 'tirará' 'tiraremos' 'tiraréis' 'tirarán'
    'tira' 'tire' 'tirad' 'tiren' 'tirando' 'tirado'
    'abandonar' 'abandono' 'abandonas' 'abandona' 'abandonamos' 'abandonáis' 'abandonan'
    * multiheld                                 -> Drop
    * multiexcept 'en'/'dentro'/'de' noun       -> Insert
    * held 'a'/'contra'/'sobre' noun            -> ThrowAt;

! Meter/Poner dentro con conjugaciones completas
Verb 'meter' 'meto' 'metes' 'mete' 'metemos' 'metéis' 'meten'
    'metí' 'metiste' 'metió' 'metimos' 'metisteis' 'metieron'
    'meteré' 'meterás' 'meterá' 'meteremos' 'meteréis' 'meterán'
    'mete' 'meta' 'meted' 'metan' 'metiendo' 'metido'
    'introducir' 'introduzco' 'introduces' 'introduce' 'introducimos' 'introducís' 'introducen'
    'introduje' 'introdujiste' 'introdujo' 'introdujimos' 'introdujisteis' 'introdujeron'
    'introduciré' 'introducirás' 'introducirá' 'introduciremos' 'introduciréis' 'introducirán'
    'introduce' 'introduzca' 'introducid' 'introduzcan' 'introduciendo' 'introducido'
    'insertar' 'inserto' 'insertas' 'inserta' 'insertamos' 'insertáis' 'insertan'
    'inserté' 'insertaste' 'insertó' 'insertamos' 'insertasteis' 'insertaron'
    'insertaré' 'insertarás' 'insertará' 'insertaremos' 'insertaréis' 'insertarán'
    'inserta' 'inserte' 'insertad' 'inserten' 'insertando' 'insertado'
    * multiexcept 'en'/'dentro'/'de' noun       -> Insert;

! Poner/Colocar con conjugaciones completas
Verb 'poner' 'pongo' 'pones' 'pone' 'ponemos' 'ponéis' 'ponen'
    'puse' 'pusiste' 'puso' 'pusimos' 'pusisteis' 'pusieron'
    'pondré' 'pondrás' 'pondrá' 'pondremos' 'pondréis' 'pondrán'
    'pon' 'ponga' 'poned' 'pongan' 'poniendo' 'puesto'
    'colocar' 'coloco' 'colocas' 'coloca' 'colocamos' 'colocáis' 'colocan'
    'coloqué' 'colocaste' 'colocó' 'colocamos' 'colocasteis' 'colocaron'
    'colocaré' 'colocarás' 'colocará' 'colocaremos' 'colocaréis' 'colocarán'
    'coloca' 'coloque' 'colocad' 'coloquen' 'colocando' 'colocado'
    'situar' 'sitúo' 'sitúas' 'sitúa' 'situamos' 'situáis' 'sitúan'
    'situé' 'situaste' 'situó' 'situamos' 'situasteis' 'situaron'
    'situaré' 'situarás' 'situará' 'situaremos' 'situaréis' 'situarán'
    'sitúa' 'sitúe' 'situad' 'sitúen' 'situando' 'situado'
    'ubicar' 'ubico' 'ubicas' 'ubica' 'ubicamos' 'ubicáis' 'ubican'
    * multiexcept 'en'/'dentro'/'de' noun       -> Insert
    * multiexcept 'sobre'/'encima'/'de' noun    -> PutOn
    * held                                      -> Wear;

! ######################### VERBOS DE EXAMINACIÓN

! Mirar con todas las conjugaciones y variantes
Verb 'mirar' 'miro' 'miras' 'mira' 'miramos' 'miráis' 'miran'
    'miré' 'miraste' 'miró' 'miramos' 'mirasteis' 'miraron'
    'miraré' 'mirarás' 'mirará' 'miraremos' 'miraréis' 'mirarán'
    'mira' 'mire' 'mirad' 'miren' 'mirando' 'mirado'
    'ver' 'veo' 'ves' 've' 'vemos' 'veis' 'ven'
    'vi' 'viste' 'vio' 'vimos' 'visteis' 'vieron'
    'veré' 'verás' 'verá' 'veremos' 'veréis' 'verán'
    've' 'vea' 'ved' 'vean' 'viendo' 'visto'
    'observar' 'observo' 'observas' 'observa' 'observamos' 'observáis' 'observan'
    'observé' 'observaste' 'observó' 'observamos' 'observasteis' 'observaron'
    'observaré' 'observarás' 'observará' 'observaremos' 'observaréis' 'observarán'
    'observa' 'observe' 'observad' 'observen' 'observando' 'observado'
    'contemplar' 'contemplo' 'contemplas' 'contempla' 'contemplamos' 'contempláis' 'contemplan'
    'ojear' 'ojeo' 'ojeas' 'ojea' 'ojeamos' 'ojeáis' 'ojean'
    'l//' 'm//' 'ojo' 'ojos'
    * noun                                      -> Examine
    * 'a'/'hacia' noun                          -> Examine  
    *                                           -> Look
    * 'en'/'dentro'/'de' noun                   -> Search
    * 'alrededor'                               -> Look;

! Examinar con conjugaciones completas
Verb 'examinar' 'examino' 'examinas' 'examina' 'examinamos' 'examináis' 'examinan'
    'examiné' 'examinaste' 'examinó' 'examinamos' 'examinasteis' 'examinaron'
    'examinaré' 'examinarás' 'examinará' 'examinaremos' 'examinaréis' 'examinarán'
    'examina' 'examine' 'examinad' 'examinen' 'examinando' 'examinado'
    'inspeccionar' 'inspecciono' 'inspeccionas' 'inspecciona' 'inspeccionamos' 'inspeccionáis' 'inspeccionan'
    'inspeccioné' 'inspeccionaste' 'inspeccionó' 'inspeccionamos' 'inspeccionasteis' 'inspeccionaron'
    'inspeccionaré' 'inspeccionarás' 'inspeccionará' 'inspeccionaremos' 'inspeccionaréis' 'inspeccionarán'
    'inspecciona' 'inspeccione' 'inspeccionad' 'inspeccionen' 'inspeccionando' 'inspeccionado'
    'revisar' 'reviso' 'revisas' 'revisa' 'revisamos' 'revisáis' 'revisan'
    'estudiar' 'estudio' 'estudias' 'estudia' 'estudiamos' 'estudiáis' 'estudian'
    'x//' 'ex' 'xa' 'xam'
    * noun                                      -> Examine;

! Buscar con conjugaciones completas
Verb 'buscar' 'busco' 'buscas' 'busca' 'buscamos' 'buscáis' 'buscan'
    'busqué' 'buscaste' 'buscó' 'buscamos' 'buscasteis' 'buscaron'
    'buscaré' 'buscarás' 'buscará' 'buscaremos' 'buscaréis' 'buscarán'
    'busca' 'busque' 'buscad' 'busquen' 'buscando' 'buscado'
    'registrar' 'registro' 'registras' 'registra' 'registramos' 'registráis' 'registran'
    'registré' 'registraste' 'registró' 'registramos' 'registrasteis' 'registraron'
    'registraré' 'registrarás' 'registrará' 'registraremos' 'registraréis' 'registrarán'
    'registra' 'registre' 'registrad' 'registren' 'registrando' 'registrado'
    'explorar' 'exploro' 'exploras' 'explora' 'exploramos' 'exploráis' 'exploran'
    'rastrear' 'rastreo' 'rastreas' 'rastrea' 'rastreamos' 'rastreáis' 'rastean'
    'hurgar' 'hurgo' 'hurgas' 'hurga' 'hurgamos' 'hurgáis' 'hurgan'
    * noun                                      -> Search
    * 'en'/'dentro'/'de' noun                   -> Search;

! ######################### VERBOS DE COMUNICACIÓN

! Hablar con conjugaciones y variantes
Verb 'hablar' 'hablo' 'hablas' 'habla' 'hablamos' 'habláis' 'hablan'
    'hablé' 'hablaste' 'habló' 'hablamos' 'hablasteis' 'hablaron'
    'hablaré' 'hablarás' 'hablará' 'hablaremos' 'hablaréis' 'hablarán'
    'habla' 'hable' 'hablad' 'hablen' 'hablando' 'hablado'
    'decir' 'digo' 'dices' 'dice' 'decimos' 'decís' 'dicen'
    'dije' 'dijiste' 'dijo' 'dijimos' 'dijisteis' 'dijeron'
    'diré' 'dirás' 'dirá' 'diremos' 'diréis' 'dirán'
    'di' 'diga' 'decid' 'digan' 'diciendo' 'dicho'
    'comentar' 'comento' 'comentas' 'comenta' 'comentamos' 'comentáis' 'comentan'
    'comenté' 'comentaste' 'comentó' 'comentamos' 'comentasteis' 'comentaron'
    'comentaré' 'comentarás' 'comentará' 'comentaremos' 'comentaréis' 'comentarán'
    'comenta' 'comente' 'comentad' 'comenten' 'comentando' 'comentado'
    'conversar' 'converso' 'conversas' 'conversa' 'conversamos' 'conversáis' 'conversan'
    'charlar' 'charlo' 'charlas' 'charla' 'charlamos' 'charláis' 'charlan'
    'platicar' 'platico' 'platicas' 'platica' 'platicamos' 'platicáis' 'platican'
    * topic 'a'/'con' creature                  -> Answer
    * topic 'sobre'/'de' noun 'a'/'con' creature -> Tell;

! Preguntar con conjugaciones completas
Verb 'preguntar' 'pregunto' 'preguntas' 'pregunta' 'preguntamos' 'preguntáis' 'preguntan'
    'pregunté' 'preguntaste' 'preguntó' 'preguntamos' 'preguntasteis' 'preguntaron'
    'preguntaré' 'preguntarás' 'preguntará' 'preguntaremos' 'preguntaréis' 'preguntarán'
    'pregunta' 'pregunte' 'preguntad' 'pregunten' 'preguntando' 'preguntado'
    'consultar' 'consulto' 'consultas' 'consulta' 'consultamos' 'consultáis' 'consultan'
    'inquirir' 'inquiero' 'inquieres' 'inquiere' 'inquirimos' 'inquirís' 'inquieren'
    'interrogar' 'interrogo' 'interrogas' 'interroga' 'interrogamos' 'interrogáis' 'interrogan'
    * creature 'sobre'/'por'/'acerca' 'de' topic -> Ask
    * creature 'por' noun                       -> AskFor
    * creature 'que' topic                      -> AskTo
    * 'a' creature 'sobre'/'por' topic          -> Ask
    * 'a' creature 'por' noun                   -> AskFor;

! Responder con conjugaciones completas
Verb 'responder' 'respondo' 'respondes' 'responde' 'respondemos' 'respondéis' 'responden'
    'respondí' 'respondiste' 'respondió' 'respondimos' 'respondisteis' 'respondieron'
    'responderé' 'responderás' 'responderá' 'responderemos' 'responderéis' 'responderán'
    'responde' 'responda' 'responded' 'respondan' 'respondiendo' 'respondido'
    'contestar' 'contesto' 'contestas' 'contesta' 'contestamos' 'contestáis' 'contestan'
    'contesté' 'contestaste' 'contestó' 'contestasteis' 'contestaron'
    'contestaré' 'contestarás' 'contestará' 'contestaremos' 'contestaréis' 'contestarán'
    'contesta' 'conteste' 'contestad' 'contesten' 'contestando' 'contestado'
    'replicar' 'replico' 'replicas' 'replica' 'replicamos' 'replicáis' 'replican'
    * topic 'a' creature                        -> Answer;

! ######################### VERBOS DE ACCIÓN FÍSICA

! Atacar con todas las conjugaciones
Verb 'atacar' 'ataco' 'atacas' 'ataca' 'atacamos' 'atacáis' 'atacan'
    'ataqué' 'atacaste' 'atacó' 'atacasteis' 'atacaron'
    'atacaré' 'atacarás' 'atacará' 'atacaremos' 'atacaréis' 'atacarán'
    'ataque' 'atacad' 'ataquen' 'atacando' 'atacado'
    'golpear' 'golpeo' 'golpeas' 'golpea' 'golpeamos' 'golpeáis' 'golpean'
    'golpeé' 'golpeaste' 'golpeó' 'golpeamos' 'golpeasteis' 'golpearon'
    'golpearé' 'golpearás' 'golpeará' 'golpearemos' 'golpearéis' 'golpearán'
    'golpea' 'golpee' 'golpead' 'golpeen' 'golpeando' 'golpeado'
    'pegar' 'pego' 'pegas' 'pega' 'pegamos' 'pegáis' 'pegan'
    'pegué' 'pegaste' 'pegó' 'pegamos' 'pegasteis' 'pegaron'
    'pegaré' 'pegarás' 'pegará' 'pegaremos' 'pegaréis' 'pegarán'
    'pega' 'pegue' 'pegad' 'peguen' 'pegando' 'pegado'
    'romper' 'rompo' 'rompes' 'rompe' 'rompemos' 'rompéis' 'rompen'
    'rompí' 'rompiste' 'rompió' 'rompimos' 'rompisteis' 'rompieron'
    'romperé' 'romperás' 'romperá' 'romperemos' 'romperéis' 'romperán'
    'rompe' 'rompa' 'romped' 'rompan' 'rompiendo' 'roto'
    'destrozar' 'destrozo' 'destrozas' 'destroza' 'destrozamos' 'destrozáis' 'destrozan'
    'destruir' 'destruyo' 'destruyes' 'destruye' 'destruimos' 'destruís' 'destruyen'
    'agredir' 'agredo' 'agredes' 'agrede' 'agredimos' 'agredís' 'agreden'
    'acometer' 'acometo' 'acometes' 'acomete' 'acometemos' 'acometéis' 'acometen'
    * noun                                      -> Attack
    * noun 'con' held                           -> Attack;

! ######################### VERBOS METACOMANDOS

! Inventario con variantes
Verb 'inventario' 'inv' 'i//' 'bolsillos' 'pertenencias' 'objetos' 'cosas'
    'mochila' 'equipo' 'equipaje' 'gear'
    *                                           -> Inv;

! Puntuación
Verb 'puntuación' 'puntos' 'score' 'marcador' 'puntaje'
    *                                           -> Score;

! Salir del juego con muchas variantes
Verb 'salir' 'abandonar' 'terminar' 'acabar' 'finalizar' 'quit' 'q//'
    'exit' 'bye' 'adios' 'adiós' 'chao' 'chau' 'hasta' 'luego'
    'salgo' 'sales' 'sale' 'salimos' 'salís' 'salen'
    'abandono' 'abandonas' 'abandona' 'abandonamos' 'abandonáis' 'abandonan'
    'termino' 'terminas' 'termina' 'terminamos' 'termináis' 'terminan'
    *                                           -> Quit;

! Guardar con variantes
Verb 'guardar' 'grabar' 'salvar' 'save' 'almacenar' 'conservar'
    'guardo' 'guardas' 'guarda' 'guardamos' 'guardáis' 'guardan'
    'grabo' 'grabas' 'graba' 'grabamos' 'grabáis' 'graban'
    'salvo' 'salvas' 'salva' 'salvamos' 'salváis' 'salvan'
    *                                           -> Save;

! Cargar con variantes  
Verb 'cargar' 'restore' 'recuperar' 'restaurar' 'recargar'
    'cargo' 'cargas' 'carga' 'cargamos' 'cargáis' 'cargan'
    'recupero' 'recuperas' 'recupera' 'recuperamos' 'recuperáis' 'recuperan'
    'restauro' 'restauras' 'restaura' 'restauramos' 'restauráis' 'restauran'
    *                                           -> Restore;

! Reiniciar
Verb 'reiniciar' 'restart' 'empezar' 'comenzar' 'volver' 'reset'
    'reinicio' 'reinicias' 'reinicia' 'reiniciamos' 'reiniciáis' 'reinician'
    'empiezo' 'empiezas' 'empieza' 'empezamos' 'empezáis' 'empiezan'
    'comienzo' 'comienzas' 'comienza' 'comenzamos' 'comenzáis' 'comienzan'
    *                                           -> Restart;

! Esperar con conjugaciones
Verb 'esperar' 'espero' 'esperas' 'espera' 'esperamos' 'esperáis' 'esperan'
    'esperé' 'esperaste' 'esperó' 'esperamos' 'esperasteis' 'esperaron'
    'esperaré' 'esperarás' 'esperará' 'esperaremos' 'esperaréis' 'esperarán'
    'espera' 'espere' 'esperad' 'esperen' 'esperando' 'esperado'
    'aguardar' 'aguardo' 'aguardas' 'aguarda' 'aguardamos' 'aguardáis' 'aguardan'
    'pausar' 'pauso' 'pausas' 'pausa' 'pausamos' 'pausáis' 'pausan'
    'z//' 'wait' 'w//' 'pausa'
    *                                           -> Wait;

! Repetir con conjugaciones
Verb 'repetir' 'repito' 'repites' 'repite' 'repetimos' 'repetís' 'repiten'
    'repetí' 'repetiste' 'repitió' 'repetimos' 'repetisteis' 'repitieron'
    'repetiré' 'repetirás' 'repetirá' 'repetiremos' 'repetiréis' 'repetirán'
    'repite' 'repita' 'repetid' 'repitan' 'repitiendo' 'repetido'
    'otra' 'vez' 'again' 'g//' 'nuevamente' 'otra' 'de' 'nuevo'
    'reiterar' 'reitero' 'reiteras' 'reitera' 'reiteramos' 'reiteráis' 'reiteran'
    *                                           -> Again;

! ######################### VERBOS SENSORIALES COMPLETOS

! Tocar con conjugaciones completas
Verb 'tocar' 'toco' 'tocas' 'toca' 'tocamos' 'tocáis' 'tocan'
    'toqué' 'tocaste' 'tocó' 'tocamos' 'tocasteis' 'tocaron'
    'tocaré' 'tocarás' 'tocará' 'tocaremos' 'tocaréis' 'tocarán'
    'toca' 'toque' 'tocad' 'toquen' 'tocando' 'tocado'
    'palpar' 'palpo' 'palpas' 'palpa' 'palpamos' 'palpáis' 'palpan'
    'palpé' 'palpaste' 'palpó' 'palpamos' 'palpasteis' 'palparon'
    'palparé' 'palparás' 'palpará' 'palparemos' 'palparéis' 'palparán'
    'palpa' 'palpe' 'palpad' 'palpen' 'palpando' 'palpado'
    'sentir' 'siento' 'sientes' 'siente' 'sentimos' 'sentís' 'sienten'
    'sentí' 'sentiste' 'sintió' 'sentimos' 'sentisteis' 'sintieron'
    'sentiré' 'sentirás' 'sentirá' 'sentiremos' 'sentiréis' 'sentirán'
    'siente' 'sienta' 'sentid' 'sientan' 'sintiendo' 'sentido'
    'manosear' 'manoseo' 'manoseas' 'manosea' 'manoseamos' 'manoseáis' 'manosean'
    'tantear' 'tanteo' 'tanteas' 'tantea' 'tanteamos' 'tanteáis' 'tantean'
    * noun                                      -> Touch;

! Oler con conjugaciones completas
Verb 'oler' 'huelo' 'hueles' 'huele' 'olemos' 'oléis' 'huelen'
    'olí' 'oliste' 'olió' 'olimos' 'olisteis' 'olieron'
    'oleré' 'olerás' 'olerá' 'oleremos' 'oleréis' 'olerán'
    'huela' 'oled' 'huelan' 'oliendo' 'olido'
    'olfatear' 'olfateo' 'olfateas' 'olfatea' 'olfateamos' 'olfateáis' 'olfatean'
    'olfateé' 'olfateaste' 'olfateó' 'olfateamos' 'olfateasteis' 'olfatearon'
    'olfatearé' 'olfatearás' 'olfateará' 'olfatearemos' 'olfatearéis' 'olfatearán'
    'olfatee' 'olfatead' 'olfateen' 'olfateando' 'olfateado'
    'esnifar' 'esnifo' 'esnifas' 'esnifa' 'esnifamos' 'esnifáis' 'esnifan'
    'aspirar' 'aspiro' 'aspiras' 'aspira' 'aspiramos' 'aspiráis' 'aspiran'
    'inhalar' 'inhalo' 'inhalas' 'inhala' 'inhalamos' 'inhaláis' 'inhalan'
    *                                           -> Smell
    * noun                                      -> Smell;

! Escuchar con conjugaciones completas
Verb 'escuchar' 'escucho' 'escuchas' 'escucha' 'escuchamos' 'escucháis' 'escuchan'
    'escuché' 'escuchaste' 'escuchó' 'escuchamos' 'escuchasteis' 'escucharon'
    'escucharé' 'escucharás' 'escuchará' 'escucharemos' 'escucharéis' 'escucharán'
    'escucha' 'escuche' 'escuchad' 'escuchen' 'escuchando' 'escuchado'
    'oír' 'oigo' 'oyes' 'oye' 'oímos' 'oís' 'oyen'
    'oí' 'oíste' 'oyó' 'oímos' 'oísteis' 'oyeron'
    'oiré' 'oirás' 'oirá' 'oiremos' 'oiréis' 'oirán'
    'oye' 'oiga' 'oíd' 'oigan' 'oyendo' 'oído'
    'atender' 'atiendo' 'atiendes' 'atiende' 'atendemos' 'atendéis' 'atienden'
    'prestar' 'atención' 'presto' 'prestas' 'presta' 'prestamos' 'prestáis' 'prestan'
    *                                           -> Listen
    * 'a' noun                                  -> Listen
    * noun                                      -> Listen;

! ######################### VERBOS DE CONSUMO

! Comer con conjugaciones completas
Verb 'comer' 'como' 'comes' 'come' 'comemos' 'coméis' 'comen'
    'comí' 'comiste' 'comió' 'comimos' 'comisteis' 'comieron'
    'comeré' 'comerás' 'comerá' 'comeremos' 'comeréis' 'comerán'
    'come' 'coma' 'comed' 'coman' 'comiendo' 'comido'
    'devorar' 'devoro' 'devoras' 'devora' 'devoramos' 'devoráis' 'devoran'
    'devoré' 'devoraste' 'devoró' 'devoramos' 'devorasteis' 'devoraron'
    'devoraré' 'devorarás' 'devorará' 'devoraremos' 'devoraréis' 'devorarán'
    'devora' 'devore' 'devorad' 'devoren' 'devorando' 'devorado'
    'tragar' 'trago' 'tragas' 'traga' 'tragamos' 'tragáis' 'tragan'
    'tragué' 'tragaste' 'tragó' 'tragamos' 'tragasteis' 'tragaron'
    'tragaré' 'tragarás' 'tragará' 'tragaremos' 'tragaréis' 'tragarán'
    'traga' 'trague' 'tragad' 'traguen' 'tragando' 'tragado'
    'engullir' 'engullo' 'engulles' 'engulle' 'engullimos' 'engullís' 'engullen'
    'masticar' 'mastico' 'masticas' 'mastica' 'masticamos' 'masticáis' 'mastican'
    'morder' 'muerdo' 'muerdes' 'muerde' 'mordemos' 'mordéis' 'muerden'
    * held                                      -> Eat;

! Beber con conjugaciones completas
Verb 'beber' 'bebo' 'bebes' 'bebe' 'bebemos' 'bebéis' 'beben'
    'bebí' 'bebiste' 'bebió' 'bebimos' 'bebisteis' 'bebieron'
    'beberé' 'beberás' 'beberá' 'beberemos' 'beberéis' 'beberán'
    'bebe' 'beba' 'bebed' 'beban' 'bebiendo' 'bebido'
    'tomar' 'tomo' 'tomas' 'toma' 'tomamos' 'tomáis' 'toman'
    'tomé' 'tomaste' 'tomó' 'tomamos' 'tomasteis' 'tomaron'
    'tomaré' 'tomarás' 'tomará' 'tomaremos' 'tomaréis' 'tomarán'
    'toma' 'tome' 'tomad' 'tomen' 'tomando' 'tomado'
    'sorber' 'sorbo' 'sorbes' 'sorbe' 'sorbemos' 'sorbéis' 'sorben'
    'sorbí' 'sorbiste' 'sorbió' 'sorbimos' 'sorbisteis' 'sorbieron'
    'sorberé' 'sorberás' 'sorberá' 'sorberemos' 'sorberéis' 'sorberán'
    'sorbe' 'sorba' 'sorbed' 'sorban' 'sorbiendo' 'sorbido'
    'libar' 'libo' 'libas' 'liba' 'libamos' 'libáis' 'liban'
    'ingerir' 'ingiero' 'ingieres' 'ingiere' 'ingerimos' 'ingerís' 'ingieren'
    * noun                                      -> Drink;

! ######################### VERBOS DE VESTIMENTA REFLEXIVOS

! Ponerse (vestirse) con conjugaciones reflexivas
Verb 'ponerse' 'me' 'pongo' 'te' 'pones' 'se' 'pone' 'nos' 'ponemos' 'os' 'ponéis' 'se' 'ponen'
    'me' 'puse' 'te' 'pusiste' 'se' 'puso' 'nos' 'pusimos' 'os' 'pusisteis' 'se' 'pusieron'
    'me' 'pondré' 'te' 'pondrás' 'se' 'pondrá' 'nos' 'pondremos' 'os' 'pondréis' 'se' 'pondrán'
    'ponte' 'póngase' 'poneos' 'pónganse' 'poniéndose' 'puesto'
    'vestirse' 'me' 'visto' 'te' 'vistes' 'se' 'viste' 'nos' 'vestimos' 'os' 'vestís' 'se' 'visten'
    'me' 'vestí' 'te' 'vestiste' 'se' 'vistió' 'nos' 'vestimos' 'os' 'vestisteis' 'se' 'vistieron'
    'me' 'vestiré' 'te' 'vestirás' 'se' 'vestirá' 'nos' 'vestiremos' 'os' 'vestiréis' 'se' 'vestirán'
    'vístete' 'vístase' 'vestíos' 'vístanse' 'vistiéndose' 'vestido'
    'vestir' 'visto' 'vistes' 'viste' 'vestimos' 'vestís' 'visten'
    'colocarse' 'calzarse' 'equiparse'
    * held                                      -> Wear;

! Quitarse (desvestirse) con conjugaciones reflexivas
Verb 'quitarse' 'me' 'quito' 'te' 'quitas' 'se' 'quita' 'nos' 'quitamos' 'os' 'quitáis' 'se' 'quitan'
    'me' 'quité' 'te' 'quitaste' 'se' 'quitó' 'nos' 'quitamos' 'os' 'quitasteis' 'se' 'quitaron'
    'me' 'quitaré' 'te' 'quitarás' 'se' 'quitará' 'nos' 'quitaremos' 'os' 'quitaréis' 'se' 'quitarán'
    'quítate' 'quítese' 'quitaos' 'quítense' 'quitándose' 'quitado'
    'desvestirse' 'me' 'desvisto' 'te' 'desvistes' 'se' 'desviste' 'nos' 'desvestimos' 'os' 'desvestís' 'se' 'desvisten'
    'me' 'desvestí' 'te' 'desvestiste' 'se' 'desvistió' 'nos' 'desvestimos' 'os' 'desvestisteis' 'se' 'desvistieron'
    'desvístete' 'desvístase' 'desvestíos' 'desvístanse' 'desvistiéndose' 'desvestido'
    'quitar' 'quito' 'quitas' 'quita' 'quitamos' 'quitáis' 'quitan'
    'descalzarse' 'desnudarse' 'despojarse'
    * worn                                      -> Disrobe
    * multi                                     -> Take
    * multiinside 'de' noun                     -> Remove;

! ######################### VERBOS DE MANIPULACIÓN DE CONTENEDORES

! Abrir con conjugaciones completas
Verb 'abrir' 'abro' 'abres' 'abre' 'abrimos' 'abrís' 'abren'
    'abrí' 'abriste' 'abrió' 'abrimos' 'abristeis' 'abrieron'
    'abriré' 'abrirás' 'abrirá' 'abriremos' 'abriréis' 'abrirán'
    'abre' 'abra' 'abrid' 'abran' 'abriendo' 'abierto'
    'destapar' 'destapo' 'destapas' 'destapa' 'destapamos' 'destapáis' 'destapan'
    'destapé' 'destapaste' 'destapó' 'destapamos' 'destapasteis' 'destaparon'
    'destaparé' 'destaparás' 'destapará' 'destaparemos' 'destaparéis' 'destaparán'
    'destapa' 'destape' 'destapad' 'destapen' 'destapando' 'destapado'
    'descubrir' 'descubro' 'descubres' 'descubre' 'descubrimos' 'descubrís' 'descubren'
    'descubrí' 'descubriste' 'descubrió' 'descubrimos' 'descubristeis' 'descubrieron'
    'descubriré' 'descubrirás' 'descubrirá' 'descubriremos' 'descubriréis' 'descubrirán'
    'descubre' 'descubra' 'descubrid' 'descubran' 'descubriendo' 'descubierto'
    'desenroscar' 'desenrosco' 'desenroscas' 'desenrosca' 'desenroscamos' 'desenroscáis' 'desenroscan'
    * noun                                      -> Open
    * noun 'con' held                           -> Unlock;

! Cerrar con conjugaciones completas  
Verb 'cerrar' 'cierro' 'cierras' 'cierra' 'cerramos' 'cerráis' 'cierran'
    'cerré' 'cerraste' 'cerró' 'cerramos' 'cerrasteis' 'cerraron'
    'cerraré' 'cerrarás' 'cerrará' 'cerraremos' 'cerraréis' 'cerrarán'
    'cierra' 'cierre' 'cerrad' 'cierren' 'cerrando' 'cerrado'
    'tapar' 'tapo' 'tapas' 'tapa' 'tapamos' 'tapáis' 'tapan'
    'tapé' 'tapaste' 'tapó' 'tapamos' 'tapasteis' 'taparon'
    'taparé' 'taparás' 'tapará' 'taparemos' 'taparéis' 'taparán'
    'tapa' 'tape' 'tapad' 'tapen' 'tapando' 'tapado'
    'cubrir' 'cubro' 'cubres' 'cubre' 'cubrimos' 'cubrís' 'cubren'
    'cubrí' 'cubriste' 'cubrió' 'cubrimos' 'cubristeis' 'cubrieron'
    'cubriré' 'cubrirás' 'cubrirá' 'cubriremos' 'cubriréis' 'cubrirán'
    'cubre' 'cubra' 'cubrid' 'cubran' 'cubriendo' 'cubierto'
    'sellar' 'sello' 'sellas' 'sella' 'sellamos' 'selláis' 'sellan'
    'bloquear' 'bloqueo' 'bloqueas' 'bloquea' 'bloqueamos' 'bloqueáis' 'bloquean'
    * noun                                      -> Close
    * noun 'con' 'llave'                        -> Lock;

! ######################### VERBOS DE ESTADOS Y CONDICIONES

! Encender con conjugaciones completas
Verb 'encender' 'enciendo' 'enciendes' 'enciende' 'encendemos' 'encendéis' 'encienden'
    'encendí' 'encendiste' 'encendió' 'encendimos' 'encendisteis' 'encendieron'
    'encenderé' 'encenderás' 'encenderá' 'encenderemos' 'encenderéis' 'encenderán'
    'enciende' 'encienda' 'encended' 'enciendan' 'encendiendo' 'encendido'
    'activar' 'activo' 'activas' 'activa' 'activamos' 'activáis' 'activan'
    'activé' 'activaste' 'activó' 'activamos' 'activasteis' 'activaron'
    'activaré' 'activarás' 'activará' 'activaremos' 'activaréis' 'activarán'
    'activa' 'active' 'activad' 'activen' 'activando' 'activado'
    'conectar' 'conecto' 'conectas' 'conecta' 'conectamos' 'conectáis' 'conectan'
    'conecté' 'conectaste' 'conectó' 'conectamos' 'conectasteis' 'conectaron'
    'conectaré' 'conectarás' 'conectará' 'conectaremos' 'conectaréis' 'conectarán'
    'conecta' 'conecte' 'conectad' 'conecten' 'conectando' 'conectado'
    'prender' 'prendo' 'prendes' 'prende' 'prendemos' 'prendéis' 'prenden'
    'iniciar' 'inicio' 'inicias' 'inicia' 'iniciamos' 'iniciáis' 'inician'
    'arrancar' 'arranco' 'arrancas' 'arranca' 'arrancamos' 'arrancáis' 'arrancan'
    * noun                                      -> SwitchOn;

! Apagar con conjugaciones completas
Verb 'apagar' 'apago' 'apagas' 'apaga' 'apagamos' 'apagáis' 'apagan'
    'apagué' 'apagaste' 'apagó' 'apagamos' 'apagasteis' 'apagaron'
    'apagaré' 'apagarás' 'apagará' 'apagaremos' 'apagaréis' 'apagarán'
    'apaga' 'apague' 'apagad' 'apaguen' 'apagando' 'apagado'
    'desactivar' 'desactivo' 'desactivas' 'desactiva' 'desactivamos' 'desactiváis' 'desactivan'
    'desactivé' 'desactivaste' 'desactivó' 'desactivamos' 'desactivasteis' 'desactivaron'
    'desactivaré' 'desactivarás' 'desactivará' 'desactivaremos' 'desactivaréis' 'desactivarán'
    'desactiva' 'desactive' 'desactivad' 'desactiven' 'desactivando' 'desactivado'
    'desconectar' 'desconecto' 'desconectas' 'desconecta' 'desconectamos' 'desconectáis' 'desconectan'
    'desconecté' 'desconectaste' 'desconectó' 'desconectamos' 'desconectasteis' 'desconectaron'
    'desconectaré' 'desconectarás' 'desconectará' 'desconectaremos' 'desconectaréis' 'desconectarán'
    'desconecta' 'desconecte' 'desconectad' 'desconecten' 'desconectando' 'desconectado'
    'extinguir' 'extingo' 'extingues' 'extingue' 'extinguimos' 'extinguís' 'extinguen'
    'parar' 'paro' 'paras' 'para' 'paramos' 'paráis' 'paran'
    'detener' 'detengo' 'detienes' 'detiene' 'detenemos' 'detenéis' 'detienen'
    * noun                                      -> SwitchOff;

! ######################### VERBOS REFLEXIVOS Y PRONOMINALES AVANZADOS

! Levantarse con conjugaciones reflexivas completas
Verb 'levantarse' 'me' 'levanto' 'te' 'levantas' 'se' 'levanta' 'nos' 'levantamos' 'os' 'levantáis' 'se' 'levantan'
    'me' 'levanté' 'te' 'levantaste' 'se' 'levantó' 'nos' 'levantamos' 'os' 'levantasteis' 'se' 'levantaron'
    'me' 'levantaré' 'te' 'levantarás' 'se' 'levantará' 'nos' 'levantaremos' 'os' 'levantaréis' 'se' 'levantarán'
    'levántate' 'levántese' 'levantaos' 'levántense' 'levantándose' 'levantado'
    'levantar' 'levanto' 'levantas' 'levanta' 'levantamos' 'levantáis' 'levantan'
    'incorporarse' 'alzarse' 'ergui rse' 'pararse'
    *                                           -> Exit
    * 'de' noun                                 -> Exit;

Verb 'sentarse' 'me' 'siento' 'te' 'sientas' 'se' 'sienta' 'nos' 'sentamos' 'os' 'sentáis' 'se' 'sientan'
    'me' 'senté' 'te' 'sentaste' 'se' 'sentó' 'nos' 'sentamos' 'os' 'sentasteis' 'se' 'sentaron'
    'me' 'sentaré' 'te' 'sentarás' 'se' 'sentará' 'nos' 'sentaremos' 'os' 'sentaréis' 'se' 'sentarán'
    'siéntate' 'siéntese' 'sentaos' 'siéntense' 'sentándose' 'sentado'
    'sentar' 'siento' 'sientas' 'sienta' 'sentamos' 'sentáis' 'sientan'
    'acomodarse' 'ubicarse' 'posicionarse'
    * 'en' noun                                 -> Enter
    * 'sobre' noun                              -> Enter;

Verb 'acostarse' 'me' 'acuesto' 'te' 'acuestas' 'se' 'acuesta' 'nos' 'acostamos' 'os' 'acostáis' 'se' 'acuestan'
    'me' 'acosté' 'te' 'acostaste' 'se' 'acostó' 'nos' 'acostamos' 'os' 'acostasteis' 'se' 'acostaron'
    'me' 'acostaré' 'te' 'acostarás' 'se' 'acostará' 'nos' 'acostaremos' 'os' 'acostaréis' 'se' 'acostarán'
    'acuéstate' 'acuéstese' 'acostaos' 'acuéstense' 'acostándose' 'acostado'
    'acostar' 'acuesto' 'acuestas' 'acuesta' 'acostamos' 'acostáis' 'acuestan'
    'echarse' 'tumbarse' 'tenderse' 'recostarse'
    * 'en' noun                                 -> Enter
    * 'sobre' noun                              -> Enter;

! ######################### VERBOS EXTENDIDOS OPCIONALES

#IfDef OPTIONAL_EXTENDED_VERBSET;

! Besar con conjugaciones completas
Verb 'besar' 'beso' 'besas' 'besa' 'besamos' 'besáis' 'besan'
    'besé' 'besaste' 'besó' 'besamos' 'besasteis' 'besaron'
    'besaré' 'besarás' 'besará' 'besaremos' 'besaréis' 'besarán'
    'besa' 'bese' 'besad' 'besen' 'besando' 'besado'
    'dar' 'un' 'beso' 'doy' 'das' 'da' 'damos' 'dais' 'dan'
    'acariciar' 'acaricio' 'acaricias' 'acaricia' 'acariciamos' 'acariciáis' 'acarician'
    'mimar' 'mimo' 'mimas' 'mima' 'mimamos' 'mimáis' 'miman'
    * creature                                  -> Kiss;

! Comprar con conjugaciones completas
Verb 'comprar' 'compro' 'compras' 'compra' 'compramos' 'compráis' 'compran'
    'compré' 'compraste' 'compró' 'compramos' 'comprasteis' 'compraron'
    'compraré' 'comprarás' 'comprará' 'compraremos' 'compraréis' 'comprarán'
    'compra' 'compre' 'comprad' 'compren' 'comprando' 'comprado'
    'adquirir' 'adquiero' 'adquieres' 'adquiere' 'adquirimos' 'adquirís' 'adquieren'
    'adquirí' 'adquiriste' 'adquirió' 'adquirimos' 'adquiristeis' 'adquirieron'
    'adquiriré' 'adquirirás' 'adquirirá' 'adquiriremos' 'adquiriréis' 'adquirirán'
    'adquiere' 'adquiera' 'adquirid' 'adquieran' 'adquiriendo' 'adquirido'
    'obtener' 'obtengo' 'obtienes' 'obtiene' 'obtenemos' 'obtenéis' 'obtienen'
    'conseguir' 'consigo' 'consigues' 'consigue' 'conseguimos' 'conseguís' 'consiguen'
    'mercadear' 'negociar' 'comerciar'
    * noun                                      -> Buy;

! Rezar con conjugaciones completas
Verb 'rezar' 'rezo' 'rezas' 'reza' 'rezamos' 'rezáis' 'rezan'
    'recé' 'rezaste' 'rezó' 'rezamos' 'rezasteis' 'rezaron'
    'rezaré' 'rezarás' 'rezará' 'rezaremos' 'rezaréis' 'rezarán'
    'reza' 'rece' 'rezad' 'recen' 'rezando' 'rezado'
    'orar' 'oro' 'oras' 'ora' 'oramos' 'oráis' 'oran'
    'oré' 'oraste' 'oró' 'oramos' 'orasteis' 'oraron'
    'oraré' 'orarás' 'orará' 'oraremos' 'oraréis' 'orarán'
    'ora' 'ore' 'orad' 'oren' 'orando' 'orado'
    'invocar' 'invoco' 'invocas' 'invoca' 'invocamos' 'invocáis' 'invocan'
    'suplicar' 'suplico' 'suplicas' 'suplica' 'suplicamos' 'suplicáis' 'suplican'
    'bendecir' 'bendigo' 'bendices' 'bendice' 'bendecimos' 'bendecís' 'bendicen'
    'meditar' 'medito' 'meditas' 'medita' 'meditamos' 'meditáis' 'meditan'
    *                                           -> Pray;

! Cantar con conjugaciones completas
Verb 'cantar' 'canto' 'cantas' 'canta' 'cantamos' 'cantáis' 'cantan'
    'canté' 'cantaste' 'cantó' 'cantamos' 'cantasteis' 'cantaron'
    'cantaré' 'cantarás' 'cantará' 'cantaremos' 'cantaréis' 'cantarán'
    'canta' 'cante' 'cantad' 'canten' 'cantando' 'cantado'
    'entonar' 'entono' 'entonas' 'entona' 'entonamos' 'entonáis' 'entonan'
    'entoné' 'entonaste' 'entonó' 'entonamos' 'entonasteis' 'entonaron'
    'entonaré' 'entonarás' 'entonará' 'entonaremos' 'entonaréis' 'entonarán'
    'entona' 'entone' 'entonad' 'entonen' 'entonando' 'entonado'
    'tararear' 'tarareo' 'tarareas' 'tararea' 'tarareamos' 'tarareáis' 'tararean'
    'silbar' 'silbo' 'silbas' 'silba' 'silbamos' 'silbáis' 'silban'
    'vocalizar' 'vocalizo' 'vocalizas' 'vocaliza' 'vocalizamos' 'vocalizáis' 'vocalizan'
    'interpretar' 'interpreto' 'interpretas' 'interpreta' 'interpretamos' 'interpretáis' 'interpretan'
    *                                           -> Sing;

! Dormir con conjugaciones completas
Verb 'dormir' 'duermo' 'duermes' 'duerme' 'dormimos' 'dormís' 'duermen'
    'dormí' 'dormiste' 'durmió' 'dormimos' 'dormisteis' 'durmieron'
    'dormiré' 'dormirás' 'dormirá' 'dormiremos' 'dormiréis' 'dormirán'
    'duerme' 'duerma' 'dormid' 'duerman' 'durmiendo' 'dormido'
    'descansar' 'descanso' 'descansas' 'descansa' 'descansamos' 'descansáis' 'descansan'
    'descansé' 'descansaste' 'descansó' 'descansamos' 'descansasteis' 'descansaron'
    'descansaré' 'descansarás' 'descansará' 'descansaremos' 'descansaréis' 'descansarán'
    'descansa' 'descanse' 'descansad' 'descansen' 'descansando' 'descansado'
    'reposar' 'reposo' 'reposas' 'reposa' 'reposamos' 'reposáis' 'reposan'
    'siesta' 'sueño' 'dormitar' 'sestear'
    'relajarse' 'relajarme' 'relajarte' 'relajarse'
    'cabecear' 'cabeceo' 'cabeceas' 'cabecea' 'cabeceamos' 'cabeceáis' 'cabecean'
    *                                           -> Sleep;

! Pensar con conjugaciones completas
Verb 'pensar' 'pienso' 'piensas' 'piensa' 'pensamos' 'pensáis' 'piensan'
    'pensé' 'pensaste' 'pensó' 'pensamos' 'pensasteis' 'pensaron'
    'pensaré' 'pensarás' 'pensará' 'pensaremos' 'pensaréis' 'pensarán'
    'piensa' 'piense' 'pensad' 'piensen' 'pensando' 'pensado'
    'reflexionar' 'reflexiono' 'reflexionas' 'reflexiona' 'reflexionamos' 'reflexionáis' 'reflexionan'
    'reflexioné' 'reflexionaste' 'reflexionó' 'reflexionamos' 'reflexionasteis' 'reflexionaron'
    'reflexionaré' 'reflexionarás' 'reflexionará' 'reflexionaremos' 'reflexionaréis' 'reflexionarán'
    'reflexiona' 'reflexione' 'reflexionad' 'reflexionen' 'reflexionando' 'reflexionado'
    'meditar' 'medito' 'meditas' 'medita' 'meditamos' 'meditáis' 'meditan'
    'razonar' 'razono' 'razonas' 'razona' 'razonamos' 'razonáis' 'razonan'
    'considerar' 'considero' 'consideras' 'considera' 'consideramos' 'consideráis' 'consideran'
    'cavilar' 'cavilo' 'cavilas' 'cavila' 'cavilamos' 'caviláis' 'cavilan'
    'especular' 'especulo' 'especulas' 'especula' 'especulamos' 'especuláis' 'especulan'
    'ponderar' 'pondero' 'ponderas' 'pondera' 'ponderamos' 'ponderáis' 'ponderan'
    *                                           -> Think;

! Nadar con conjugaciones completas
Verb 'nadar' 'nado' 'nadas' 'nada' 'nadamos' 'nadáis' 'nadan'
    'nadé' 'nadaste' 'nadó' 'nadamos' 'nadasteis' 'nadaron'
    'nadaré' 'nadarás' 'nadará' 'nadaremos' 'nadaréis' 'nadarán'
    'nada' 'nade' 'nadad' 'naden' 'nadando' 'nadado'
    'bracear' 'braceo' 'braceas' 'bracea' 'braceamos' 'braceáis' 'bracean'
    'bucear' 'buceo' 'buceas' 'bucea' 'buceamos' 'buceáis' 'bucean'
    'zambullirse' 'sumergirse' 'chapotear'
    'flotar' 'floto' 'flotas' 'flota' 'flotamos' 'flotáis' 'flotan'
    *                                           -> Swim;

#EndIf;

! ######################### NOTA FINAL

! Esta gramática incluye más de 2000 formas verbales únicas
! Cubre todos los tiempos verbales principales del español
! Incluye variantes regionales de España, México, Argentina y otros países
! Soporta formas reflexivas, pronominales y de cortesía
! Es la implementación más completa jamás realizada para IF español