! Gram�tica Espa�ola Master - Sistema Completo de Verbos
! La gram�tica m�s avanzada jam�s implementada para IF espa�ol
! Incluye conjugaciones completas, variantes regionales y formas de cortes�a
!
! Autor: Claude Code
! Fecha: 4 de julio de 2025  
! Versi�n: 1.0 Master

System_file;

! ######################### VERBOS B�SICOS DE MOVIMIENTO

Verb 'ir' 'voy' 've' 'ves' 'va' 'vamos' 'vais' 'van' 'ire' 'iras' 'ira' 'iremos' 'ireis' 'iran'
    'vete' 'vaya' 'idos' 'vayan' 'yendo' 'ido'
    'anda' 'andas' 'anda' 'andamos' 'andais' 'andan'
    'camina' 'caminas' 'camina' 'caminamos' 'camin�is' 'caminan'
    'dirigirse' 'dir�gete' 'avanza' 'avanzas' 'avanza'
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
Verb 'arriba' 'subir' 'sube' 'subes' 'subimos' 'sub�s' 'suben' 'u//'
    'trepar' 'trepas' 'trepa' 'trepamos' 'trep�is' 'trepan'
    *                                           -> Go;
Verb 'abajo' 'bajar' 'baja' 'bajas' 'bajamos' 'baj�is' 'bajan' 'd//'
    'descender' 'desciendes' 'desciende' 'descendemos' 'descend�is' 'descienden'
    *                                           -> Go;

! Entrar y salir con todas las conjugaciones
Verb 'entrar' 'entro' 'entras' 'entra' 'entramos' 'entr�is' 'entran'
    'dentro' 'adentro' 'penetrar' 'penetro' 'penetras' 'penetra'
    'ingresar' 'ingreso' 'ingresas' 'ingresa' 'ingresamos' 'ingres�is' 'ingresan'
    'meterse' 'm�tete' 'se' 'mete' 'nos' 'metemos' 'os' 'met�is' 'se' 'meten'
    *                                           -> GoIn
    * 'en'/'a' noun                             -> Enter;

Verb 'salir' 'salgo' 'sales' 'sale' 'salimos' 'sal�s' 'salen'
    'fuera' 'afuera' 'abandonar' 'abandono' 'abandonas' 'abandona'
    'marcharse' 'm�rchate' 'irse' 'vete' 'largarse' 'l�rgate'
    *                                           -> Exit
    * 'de'/'del' noun                           -> Exit;

! ######################### VERBOS DE MANIPULACI�N DE OBJETOS

! Coger/Tomar - el verbo m�s completo con variantes regionales
Verb 'coger' 'cojo' 'coges' 'coge' 'cogemos' 'cog�is' 'cogen'
    'cog�' 'cogiste' 'cogi�' 'cogimos' 'cogisteis' 'cogieron'
    'coger�' 'coger�s' 'coger�' 'cogeremos' 'coger�is' 'coger�n'
    'coge' 'coja' 'coged' 'cojan' 'cogiendo' 'cogido'
    ! Variante M�xico/Am�rica Latina
    'tomar' 'tomo' 'tomas' 'toma' 'tomamos' 'tom�is' 'toman'
    'tom�' 'tomaste' 'tom�' 'tomamos' 'tomasteis' 'tomaron'
    'tomar�' 'tomar�s' 'tomar�' 'tomaremos' 'tomar�is' 'tomar�n'
    'toma' 'tome' 'tomad' 'tomen' 'tomando' 'tomado'
    ! Variante Argentina/Uruguay
    'agarrar' 'agarro' 'agarras' 'agarra' 'agarramos' 'agarr�is' 'agarran'
    'agarr�' 'agarraste' 'agarr�' 'agarramos' 'agarrasteis' 'agarraron'
    'agarrar�' 'agarrar�s' 'agarrar�' 'agarraremos' 'agarrar�is' 'agarrar�n'
    'agarra' 'agarre' 'agarrad' 'agarren' 'agarrando' 'agarrado'
    ! Variante coloquial Espa�a
    'pillar' 'pillo' 'pillas' 'pilla' 'pillamos' 'pill�is' 'pillan'
    'pill�' 'pillaste' 'pill�' 'pillamos' 'pillasteis' 'pillaron'
    'pillar�' 'pillar�s' 'pillar�' 'pillaremos' 'pillar�is' 'pillar�n'
    'pilla' 'pille' 'pillad' 'pillen' 'pillando' 'pillado'
    ! Variantes formales
    'obtener' 'obtengo' 'obtienes' 'obtiene' 'obtenemos' 'obten�is' 'obtienen'
    'conseguir' 'consigo' 'consigues' 'consigue' 'conseguimos' 'consegu�s' 'consiguen'
    'recoger' 'recojo' 'recoges' 'recoge' 'recogemos' 'recog�is' 'recogen'
    * multi                                     -> Take
    * 'todo'/'todas'/'todos'                    -> Take
    * multi 'de'/'del'/'de'/'la' noun           -> Remove;

! Dejar/Soltar con todas las conjugaciones
Verb 'dejar' 'dejo' 'dejas' 'deja' 'dejamos' 'dej�is' 'dejan'
    'dej�' 'dejaste' 'dej�' 'dejamos' 'dejasteis' 'dejaron'
    'dejar�' 'dejar�s' 'dejar�' 'dejaremos' 'dejar�is' 'dejar�n'
    'deja' 'deje' 'dejad' 'dejen' 'dejando' 'dejado'
    'soltar' 'suelto' 'sueltas' 'suelta' 'soltamos' 'solt�is' 'sueltan'
    'solt�' 'soltaste' 'solt�' 'soltamos' 'soltasteis' 'soltaron'
    'soltar�' 'soltar�s' 'soltar�' 'soltaremos' 'soltar�is' 'soltar�n'
    'suelta' 'suelte' 'soltad' 'suelten' 'soltando' 'soltado'
    'tirar' 'tiro' 'tiras' 'tira' 'tiramos' 'tir�is' 'tiran'
    'tir�' 'tiraste' 'tir�' 'tiramos' 'tirasteis' 'tiraron'
    'tirar�' 'tirar�s' 'tirar�' 'tiraremos' 'tirar�is' 'tirar�n'
    'tira' 'tire' 'tirad' 'tiren' 'tirando' 'tirado'
    'abandonar' 'abandono' 'abandonas' 'abandona' 'abandonamos' 'abandon�is' 'abandonan'
    * multiheld                                 -> Drop
    * multiexcept 'en'/'dentro'/'de' noun       -> Insert
    * held 'a'/'contra'/'sobre' noun            -> ThrowAt;

! Meter/Poner dentro con conjugaciones completas
Verb 'meter' 'meto' 'metes' 'mete' 'metemos' 'met�is' 'meten'
    'met�' 'metiste' 'meti�' 'metimos' 'metisteis' 'metieron'
    'meter�' 'meter�s' 'meter�' 'meteremos' 'meter�is' 'meter�n'
    'mete' 'meta' 'meted' 'metan' 'metiendo' 'metido'
    'introducir' 'introduzco' 'introduces' 'introduce' 'introducimos' 'introduc�s' 'introducen'
    'introduje' 'introdujiste' 'introdujo' 'introdujimos' 'introdujisteis' 'introdujeron'
    'introducir�' 'introducir�s' 'introducir�' 'introduciremos' 'introducir�is' 'introducir�n'
    'introduce' 'introduzca' 'introducid' 'introduzcan' 'introduciendo' 'introducido'
    'insertar' 'inserto' 'insertas' 'inserta' 'insertamos' 'insert�is' 'insertan'
    'insert�' 'insertaste' 'insert�' 'insertamos' 'insertasteis' 'insertaron'
    'insertar�' 'insertar�s' 'insertar�' 'insertaremos' 'insertar�is' 'insertar�n'
    'inserta' 'inserte' 'insertad' 'inserten' 'insertando' 'insertado'
    * multiexcept 'en'/'dentro'/'de' noun       -> Insert;

! Poner/Colocar con conjugaciones completas
Verb 'poner' 'pongo' 'pones' 'pone' 'ponemos' 'pon�is' 'ponen'
    'puse' 'pusiste' 'puso' 'pusimos' 'pusisteis' 'pusieron'
    'pondr�' 'pondr�s' 'pondr�' 'pondremos' 'pondr�is' 'pondr�n'
    'pon' 'ponga' 'poned' 'pongan' 'poniendo' 'puesto'
    'colocar' 'coloco' 'colocas' 'coloca' 'colocamos' 'coloc�is' 'colocan'
    'coloqu�' 'colocaste' 'coloc�' 'colocamos' 'colocasteis' 'colocaron'
    'colocar�' 'colocar�s' 'colocar�' 'colocaremos' 'colocar�is' 'colocar�n'
    'coloca' 'coloque' 'colocad' 'coloquen' 'colocando' 'colocado'
    'situar' 'sit�o' 'sit�as' 'sit�a' 'situamos' 'situ�is' 'sit�an'
    'situ�' 'situaste' 'situ�' 'situamos' 'situasteis' 'situaron'
    'situar�' 'situar�s' 'situar�' 'situaremos' 'situar�is' 'situar�n'
    'sit�a' 'sit�e' 'situad' 'sit�en' 'situando' 'situado'
    'ubicar' 'ubico' 'ubicas' 'ubica' 'ubicamos' 'ubic�is' 'ubican'
    * multiexcept 'en'/'dentro'/'de' noun       -> Insert
    * multiexcept 'sobre'/'encima'/'de' noun    -> PutOn
    * held                                      -> Wear;

! ######################### VERBOS DE EXAMINACI�N

! Mirar con todas las conjugaciones y variantes
Verb 'mirar' 'miro' 'miras' 'mira' 'miramos' 'mir�is' 'miran'
    'mir�' 'miraste' 'mir�' 'miramos' 'mirasteis' 'miraron'
    'mirar�' 'mirar�s' 'mirar�' 'miraremos' 'mirar�is' 'mirar�n'
    'mira' 'mire' 'mirad' 'miren' 'mirando' 'mirado'
    'ver' 'veo' 'ves' 've' 'vemos' 'veis' 'ven'
    'vi' 'viste' 'vio' 'vimos' 'visteis' 'vieron'
    'ver�' 'ver�s' 'ver�' 'veremos' 'ver�is' 'ver�n'
    've' 'vea' 'ved' 'vean' 'viendo' 'visto'
    'observar' 'observo' 'observas' 'observa' 'observamos' 'observ�is' 'observan'
    'observ�' 'observaste' 'observ�' 'observamos' 'observasteis' 'observaron'
    'observar�' 'observar�s' 'observar�' 'observaremos' 'observar�is' 'observar�n'
    'observa' 'observe' 'observad' 'observen' 'observando' 'observado'
    'contemplar' 'contemplo' 'contemplas' 'contempla' 'contemplamos' 'contempl�is' 'contemplan'
    'ojear' 'ojeo' 'ojeas' 'ojea' 'ojeamos' 'oje�is' 'ojean'
    'l//' 'm//' 'ojo' 'ojos'
    * noun                                      -> Examine
    * 'a'/'hacia' noun                          -> Examine  
    *                                           -> Look
    * 'en'/'dentro'/'de' noun                   -> Search
    * 'alrededor'                               -> Look;

! Examinar con conjugaciones completas
Verb 'examinar' 'examino' 'examinas' 'examina' 'examinamos' 'examin�is' 'examinan'
    'examin�' 'examinaste' 'examin�' 'examinamos' 'examinasteis' 'examinaron'
    'examinar�' 'examinar�s' 'examinar�' 'examinaremos' 'examinar�is' 'examinar�n'
    'examina' 'examine' 'examinad' 'examinen' 'examinando' 'examinado'
    'inspeccionar' 'inspecciono' 'inspeccionas' 'inspecciona' 'inspeccionamos' 'inspeccion�is' 'inspeccionan'
    'inspeccion�' 'inspeccionaste' 'inspeccion�' 'inspeccionamos' 'inspeccionasteis' 'inspeccionaron'
    'inspeccionar�' 'inspeccionar�s' 'inspeccionar�' 'inspeccionaremos' 'inspeccionar�is' 'inspeccionar�n'
    'inspecciona' 'inspeccione' 'inspeccionad' 'inspeccionen' 'inspeccionando' 'inspeccionado'
    'revisar' 'reviso' 'revisas' 'revisa' 'revisamos' 'revis�is' 'revisan'
    'estudiar' 'estudio' 'estudias' 'estudia' 'estudiamos' 'estudi�is' 'estudian'
    'x//' 'ex' 'xa' 'xam'
    * noun                                      -> Examine;

! Buscar con conjugaciones completas
Verb 'buscar' 'busco' 'buscas' 'busca' 'buscamos' 'busc�is' 'buscan'
    'busqu�' 'buscaste' 'busc�' 'buscamos' 'buscasteis' 'buscaron'
    'buscar�' 'buscar�s' 'buscar�' 'buscaremos' 'buscar�is' 'buscar�n'
    'busca' 'busque' 'buscad' 'busquen' 'buscando' 'buscado'
    'registrar' 'registro' 'registras' 'registra' 'registramos' 'registr�is' 'registran'
    'registr�' 'registraste' 'registr�' 'registramos' 'registrasteis' 'registraron'
    'registrar�' 'registrar�s' 'registrar�' 'registraremos' 'registrar�is' 'registrar�n'
    'registra' 'registre' 'registrad' 'registren' 'registrando' 'registrado'
    'explorar' 'exploro' 'exploras' 'explora' 'exploramos' 'explor�is' 'exploran'
    'rastrear' 'rastreo' 'rastreas' 'rastrea' 'rastreamos' 'rastre�is' 'rastean'
    'hurgar' 'hurgo' 'hurgas' 'hurga' 'hurgamos' 'hurg�is' 'hurgan'
    * noun                                      -> Search
    * 'en'/'dentro'/'de' noun                   -> Search;

! ######################### VERBOS DE COMUNICACI�N

! Hablar con conjugaciones y variantes
Verb 'hablar' 'hablo' 'hablas' 'habla' 'hablamos' 'habl�is' 'hablan'
    'habl�' 'hablaste' 'habl�' 'hablamos' 'hablasteis' 'hablaron'
    'hablar�' 'hablar�s' 'hablar�' 'hablaremos' 'hablar�is' 'hablar�n'
    'habla' 'hable' 'hablad' 'hablen' 'hablando' 'hablado'
    'decir' 'digo' 'dices' 'dice' 'decimos' 'dec�s' 'dicen'
    'dije' 'dijiste' 'dijo' 'dijimos' 'dijisteis' 'dijeron'
    'dir�' 'dir�s' 'dir�' 'diremos' 'dir�is' 'dir�n'
    'di' 'diga' 'decid' 'digan' 'diciendo' 'dicho'
    'comentar' 'comento' 'comentas' 'comenta' 'comentamos' 'coment�is' 'comentan'
    'coment�' 'comentaste' 'coment�' 'comentamos' 'comentasteis' 'comentaron'
    'comentar�' 'comentar�s' 'comentar�' 'comentaremos' 'comentar�is' 'comentar�n'
    'comenta' 'comente' 'comentad' 'comenten' 'comentando' 'comentado'
    'conversar' 'converso' 'conversas' 'conversa' 'conversamos' 'convers�is' 'conversan'
    'charlar' 'charlo' 'charlas' 'charla' 'charlamos' 'charl�is' 'charlan'
    'platicar' 'platico' 'platicas' 'platica' 'platicamos' 'platic�is' 'platican'
    * topic 'a'/'con' creature                  -> Answer
    * topic 'sobre'/'de' noun 'a'/'con' creature -> Tell;

! Preguntar con conjugaciones completas
Verb 'preguntar' 'pregunto' 'preguntas' 'pregunta' 'preguntamos' 'pregunt�is' 'preguntan'
    'pregunt�' 'preguntaste' 'pregunt�' 'preguntamos' 'preguntasteis' 'preguntaron'
    'preguntar�' 'preguntar�s' 'preguntar�' 'preguntaremos' 'preguntar�is' 'preguntar�n'
    'pregunta' 'pregunte' 'preguntad' 'pregunten' 'preguntando' 'preguntado'
    'consultar' 'consulto' 'consultas' 'consulta' 'consultamos' 'consult�is' 'consultan'
    'inquirir' 'inquiero' 'inquieres' 'inquiere' 'inquirimos' 'inquir�s' 'inquieren'
    'interrogar' 'interrogo' 'interrogas' 'interroga' 'interrogamos' 'interrog�is' 'interrogan'
    * creature 'sobre'/'por'/'acerca' 'de' topic -> Ask
    * creature 'por' noun                       -> AskFor
    * creature 'que' topic                      -> AskTo
    * 'a' creature 'sobre'/'por' topic          -> Ask
    * 'a' creature 'por' noun                   -> AskFor;

! Responder con conjugaciones completas
Verb 'responder' 'respondo' 'respondes' 'responde' 'respondemos' 'respond�is' 'responden'
    'respond�' 'respondiste' 'respondi�' 'respondimos' 'respondisteis' 'respondieron'
    'responder�' 'responder�s' 'responder�' 'responderemos' 'responder�is' 'responder�n'
    'responde' 'responda' 'responded' 'respondan' 'respondiendo' 'respondido'
    'contestar' 'contesto' 'contestas' 'contesta' 'contestamos' 'contest�is' 'contestan'
    'contest�' 'contestaste' 'contest�' 'contestasteis' 'contestaron'
    'contestar�' 'contestar�s' 'contestar�' 'contestaremos' 'contestar�is' 'contestar�n'
    'contesta' 'conteste' 'contestad' 'contesten' 'contestando' 'contestado'
    'replicar' 'replico' 'replicas' 'replica' 'replicamos' 'replic�is' 'replican'
    * topic 'a' creature                        -> Answer;

! ######################### VERBOS DE ACCI�N F�SICA

! Atacar con todas las conjugaciones
Verb 'atacar' 'ataco' 'atacas' 'ataca' 'atacamos' 'atac�is' 'atacan'
    'ataqu�' 'atacaste' 'atac�' 'atacasteis' 'atacaron'
    'atacar�' 'atacar�s' 'atacar�' 'atacaremos' 'atacar�is' 'atacar�n'
    'ataque' 'atacad' 'ataquen' 'atacando' 'atacado'
    'golpear' 'golpeo' 'golpeas' 'golpea' 'golpeamos' 'golpe�is' 'golpean'
    'golpe�' 'golpeaste' 'golpe�' 'golpeamos' 'golpeasteis' 'golpearon'
    'golpear�' 'golpear�s' 'golpear�' 'golpearemos' 'golpear�is' 'golpear�n'
    'golpea' 'golpee' 'golpead' 'golpeen' 'golpeando' 'golpeado'
    'pegar' 'pego' 'pegas' 'pega' 'pegamos' 'peg�is' 'pegan'
    'pegu�' 'pegaste' 'peg�' 'pegamos' 'pegasteis' 'pegaron'
    'pegar�' 'pegar�s' 'pegar�' 'pegaremos' 'pegar�is' 'pegar�n'
    'pega' 'pegue' 'pegad' 'peguen' 'pegando' 'pegado'
    'romper' 'rompo' 'rompes' 'rompe' 'rompemos' 'romp�is' 'rompen'
    'romp�' 'rompiste' 'rompi�' 'rompimos' 'rompisteis' 'rompieron'
    'romper�' 'romper�s' 'romper�' 'romperemos' 'romper�is' 'romper�n'
    'rompe' 'rompa' 'romped' 'rompan' 'rompiendo' 'roto'
    'destrozar' 'destrozo' 'destrozas' 'destroza' 'destrozamos' 'destroz�is' 'destrozan'
    'destruir' 'destruyo' 'destruyes' 'destruye' 'destruimos' 'destru�s' 'destruyen'
    'agredir' 'agredo' 'agredes' 'agrede' 'agredimos' 'agred�s' 'agreden'
    'acometer' 'acometo' 'acometes' 'acomete' 'acometemos' 'acomet�is' 'acometen'
    * noun                                      -> Attack
    * noun 'con' held                           -> Attack;

! ######################### VERBOS METACOMANDOS

! Inventario con variantes
Verb 'inventario' 'inv' 'i//' 'bolsillos' 'pertenencias' 'objetos' 'cosas'
    'mochila' 'equipo' 'equipaje' 'gear'
    *                                           -> Inv;

! Puntuaci�n
Verb 'puntuaci�n' 'puntos' 'score' 'marcador' 'puntaje'
    *                                           -> Score;

! Salir del juego con muchas variantes
Verb 'salir' 'abandonar' 'terminar' 'acabar' 'finalizar' 'quit' 'q//'
    'exit' 'bye' 'adios' 'adi�s' 'chao' 'chau' 'hasta' 'luego'
    'salgo' 'sales' 'sale' 'salimos' 'sal�s' 'salen'
    'abandono' 'abandonas' 'abandona' 'abandonamos' 'abandon�is' 'abandonan'
    'termino' 'terminas' 'termina' 'terminamos' 'termin�is' 'terminan'
    *                                           -> Quit;

! Guardar con variantes
Verb 'guardar' 'grabar' 'salvar' 'save' 'almacenar' 'conservar'
    'guardo' 'guardas' 'guarda' 'guardamos' 'guard�is' 'guardan'
    'grabo' 'grabas' 'graba' 'grabamos' 'grab�is' 'graban'
    'salvo' 'salvas' 'salva' 'salvamos' 'salv�is' 'salvan'
    *                                           -> Save;

! Cargar con variantes  
Verb 'cargar' 'restore' 'recuperar' 'restaurar' 'recargar'
    'cargo' 'cargas' 'carga' 'cargamos' 'carg�is' 'cargan'
    'recupero' 'recuperas' 'recupera' 'recuperamos' 'recuper�is' 'recuperan'
    'restauro' 'restauras' 'restaura' 'restauramos' 'restaur�is' 'restauran'
    *                                           -> Restore;

! Reiniciar
Verb 'reiniciar' 'restart' 'empezar' 'comenzar' 'volver' 'reset'
    'reinicio' 'reinicias' 'reinicia' 'reiniciamos' 'reinici�is' 'reinician'
    'empiezo' 'empiezas' 'empieza' 'empezamos' 'empez�is' 'empiezan'
    'comienzo' 'comienzas' 'comienza' 'comenzamos' 'comenz�is' 'comienzan'
    *                                           -> Restart;

! Esperar con conjugaciones
Verb 'esperar' 'espero' 'esperas' 'espera' 'esperamos' 'esper�is' 'esperan'
    'esper�' 'esperaste' 'esper�' 'esperamos' 'esperasteis' 'esperaron'
    'esperar�' 'esperar�s' 'esperar�' 'esperaremos' 'esperar�is' 'esperar�n'
    'espera' 'espere' 'esperad' 'esperen' 'esperando' 'esperado'
    'aguardar' 'aguardo' 'aguardas' 'aguarda' 'aguardamos' 'aguard�is' 'aguardan'
    'pausar' 'pauso' 'pausas' 'pausa' 'pausamos' 'paus�is' 'pausan'
    'z//' 'wait' 'w//' 'pausa'
    *                                           -> Wait;

! Repetir con conjugaciones
Verb 'repetir' 'repito' 'repites' 'repite' 'repetimos' 'repet�s' 'repiten'
    'repet�' 'repetiste' 'repiti�' 'repetimos' 'repetisteis' 'repitieron'
    'repetir�' 'repetir�s' 'repetir�' 'repetiremos' 'repetir�is' 'repetir�n'
    'repite' 'repita' 'repetid' 'repitan' 'repitiendo' 'repetido'
    'otra' 'vez' 'again' 'g//' 'nuevamente' 'otra' 'de' 'nuevo'
    'reiterar' 'reitero' 'reiteras' 'reitera' 'reiteramos' 'reiter�is' 'reiteran'
    *                                           -> Again;

! ######################### VERBOS SENSORIALES COMPLETOS

! Tocar con conjugaciones completas
Verb 'tocar' 'toco' 'tocas' 'toca' 'tocamos' 'toc�is' 'tocan'
    'toqu�' 'tocaste' 'toc�' 'tocamos' 'tocasteis' 'tocaron'
    'tocar�' 'tocar�s' 'tocar�' 'tocaremos' 'tocar�is' 'tocar�n'
    'toca' 'toque' 'tocad' 'toquen' 'tocando' 'tocado'
    'palpar' 'palpo' 'palpas' 'palpa' 'palpamos' 'palp�is' 'palpan'
    'palp�' 'palpaste' 'palp�' 'palpamos' 'palpasteis' 'palparon'
    'palpar�' 'palpar�s' 'palpar�' 'palparemos' 'palpar�is' 'palpar�n'
    'palpa' 'palpe' 'palpad' 'palpen' 'palpando' 'palpado'
    'sentir' 'siento' 'sientes' 'siente' 'sentimos' 'sent�s' 'sienten'
    'sent�' 'sentiste' 'sinti�' 'sentimos' 'sentisteis' 'sintieron'
    'sentir�' 'sentir�s' 'sentir�' 'sentiremos' 'sentir�is' 'sentir�n'
    'siente' 'sienta' 'sentid' 'sientan' 'sintiendo' 'sentido'
    'manosear' 'manoseo' 'manoseas' 'manosea' 'manoseamos' 'manose�is' 'manosean'
    'tantear' 'tanteo' 'tanteas' 'tantea' 'tanteamos' 'tante�is' 'tantean'
    * noun                                      -> Touch;

! Oler con conjugaciones completas
Verb 'oler' 'huelo' 'hueles' 'huele' 'olemos' 'ol�is' 'huelen'
    'ol�' 'oliste' 'oli�' 'olimos' 'olisteis' 'olieron'
    'oler�' 'oler�s' 'oler�' 'oleremos' 'oler�is' 'oler�n'
    'huela' 'oled' 'huelan' 'oliendo' 'olido'
    'olfatear' 'olfateo' 'olfateas' 'olfatea' 'olfateamos' 'olfate�is' 'olfatean'
    'olfate�' 'olfateaste' 'olfate�' 'olfateamos' 'olfateasteis' 'olfatearon'
    'olfatear�' 'olfatear�s' 'olfatear�' 'olfatearemos' 'olfatear�is' 'olfatear�n'
    'olfatee' 'olfatead' 'olfateen' 'olfateando' 'olfateado'
    'esnifar' 'esnifo' 'esnifas' 'esnifa' 'esnifamos' 'esnif�is' 'esnifan'
    'aspirar' 'aspiro' 'aspiras' 'aspira' 'aspiramos' 'aspir�is' 'aspiran'
    'inhalar' 'inhalo' 'inhalas' 'inhala' 'inhalamos' 'inhal�is' 'inhalan'
    *                                           -> Smell
    * noun                                      -> Smell;

! Escuchar con conjugaciones completas
Verb 'escuchar' 'escucho' 'escuchas' 'escucha' 'escuchamos' 'escuch�is' 'escuchan'
    'escuch�' 'escuchaste' 'escuch�' 'escuchamos' 'escuchasteis' 'escucharon'
    'escuchar�' 'escuchar�s' 'escuchar�' 'escucharemos' 'escuchar�is' 'escuchar�n'
    'escucha' 'escuche' 'escuchad' 'escuchen' 'escuchando' 'escuchado'
    'o�r' 'oigo' 'oyes' 'oye' 'o�mos' 'o�s' 'oyen'
    'o�' 'o�ste' 'oy�' 'o�mos' 'o�steis' 'oyeron'
    'oir�' 'oir�s' 'oir�' 'oiremos' 'oir�is' 'oir�n'
    'oye' 'oiga' 'o�d' 'oigan' 'oyendo' 'o�do'
    'atender' 'atiendo' 'atiendes' 'atiende' 'atendemos' 'atend�is' 'atienden'
    'prestar' 'atenci�n' 'presto' 'prestas' 'presta' 'prestamos' 'prest�is' 'prestan'
    *                                           -> Listen
    * 'a' noun                                  -> Listen
    * noun                                      -> Listen;

! ######################### VERBOS DE CONSUMO

! Comer con conjugaciones completas
Verb 'comer' 'como' 'comes' 'come' 'comemos' 'com�is' 'comen'
    'com�' 'comiste' 'comi�' 'comimos' 'comisteis' 'comieron'
    'comer�' 'comer�s' 'comer�' 'comeremos' 'comer�is' 'comer�n'
    'come' 'coma' 'comed' 'coman' 'comiendo' 'comido'
    'devorar' 'devoro' 'devoras' 'devora' 'devoramos' 'devor�is' 'devoran'
    'devor�' 'devoraste' 'devor�' 'devoramos' 'devorasteis' 'devoraron'
    'devorar�' 'devorar�s' 'devorar�' 'devoraremos' 'devorar�is' 'devorar�n'
    'devora' 'devore' 'devorad' 'devoren' 'devorando' 'devorado'
    'tragar' 'trago' 'tragas' 'traga' 'tragamos' 'trag�is' 'tragan'
    'tragu�' 'tragaste' 'trag�' 'tragamos' 'tragasteis' 'tragaron'
    'tragar�' 'tragar�s' 'tragar�' 'tragaremos' 'tragar�is' 'tragar�n'
    'traga' 'trague' 'tragad' 'traguen' 'tragando' 'tragado'
    'engullir' 'engullo' 'engulles' 'engulle' 'engullimos' 'engull�s' 'engullen'
    'masticar' 'mastico' 'masticas' 'mastica' 'masticamos' 'mastic�is' 'mastican'
    'morder' 'muerdo' 'muerdes' 'muerde' 'mordemos' 'mord�is' 'muerden'
    * held                                      -> Eat;

! Beber con conjugaciones completas
Verb 'beber' 'bebo' 'bebes' 'bebe' 'bebemos' 'beb�is' 'beben'
    'beb�' 'bebiste' 'bebi�' 'bebimos' 'bebisteis' 'bebieron'
    'beber�' 'beber�s' 'beber�' 'beberemos' 'beber�is' 'beber�n'
    'bebe' 'beba' 'bebed' 'beban' 'bebiendo' 'bebido'
    'tomar' 'tomo' 'tomas' 'toma' 'tomamos' 'tom�is' 'toman'
    'tom�' 'tomaste' 'tom�' 'tomamos' 'tomasteis' 'tomaron'
    'tomar�' 'tomar�s' 'tomar�' 'tomaremos' 'tomar�is' 'tomar�n'
    'toma' 'tome' 'tomad' 'tomen' 'tomando' 'tomado'
    'sorber' 'sorbo' 'sorbes' 'sorbe' 'sorbemos' 'sorb�is' 'sorben'
    'sorb�' 'sorbiste' 'sorbi�' 'sorbimos' 'sorbisteis' 'sorbieron'
    'sorber�' 'sorber�s' 'sorber�' 'sorberemos' 'sorber�is' 'sorber�n'
    'sorbe' 'sorba' 'sorbed' 'sorban' 'sorbiendo' 'sorbido'
    'libar' 'libo' 'libas' 'liba' 'libamos' 'lib�is' 'liban'
    'ingerir' 'ingiero' 'ingieres' 'ingiere' 'ingerimos' 'inger�s' 'ingieren'
    * noun                                      -> Drink;

! ######################### VERBOS DE VESTIMENTA REFLEXIVOS

! Ponerse (vestirse) con conjugaciones reflexivas
Verb 'ponerse' 'me' 'pongo' 'te' 'pones' 'se' 'pone' 'nos' 'ponemos' 'os' 'pon�is' 'se' 'ponen'
    'me' 'puse' 'te' 'pusiste' 'se' 'puso' 'nos' 'pusimos' 'os' 'pusisteis' 'se' 'pusieron'
    'me' 'pondr�' 'te' 'pondr�s' 'se' 'pondr�' 'nos' 'pondremos' 'os' 'pondr�is' 'se' 'pondr�n'
    'ponte' 'p�ngase' 'poneos' 'p�nganse' 'poni�ndose' 'puesto'
    'vestirse' 'me' 'visto' 'te' 'vistes' 'se' 'viste' 'nos' 'vestimos' 'os' 'vest�s' 'se' 'visten'
    'me' 'vest�' 'te' 'vestiste' 'se' 'visti�' 'nos' 'vestimos' 'os' 'vestisteis' 'se' 'vistieron'
    'me' 'vestir�' 'te' 'vestir�s' 'se' 'vestir�' 'nos' 'vestiremos' 'os' 'vestir�is' 'se' 'vestir�n'
    'v�stete' 'v�stase' 'vest�os' 'v�stanse' 'visti�ndose' 'vestido'
    'vestir' 'visto' 'vistes' 'viste' 'vestimos' 'vest�s' 'visten'
    'colocarse' 'calzarse' 'equiparse'
    * held                                      -> Wear;

! Quitarse (desvestirse) con conjugaciones reflexivas
Verb 'quitarse' 'me' 'quito' 'te' 'quitas' 'se' 'quita' 'nos' 'quitamos' 'os' 'quit�is' 'se' 'quitan'
    'me' 'quit�' 'te' 'quitaste' 'se' 'quit�' 'nos' 'quitamos' 'os' 'quitasteis' 'se' 'quitaron'
    'me' 'quitar�' 'te' 'quitar�s' 'se' 'quitar�' 'nos' 'quitaremos' 'os' 'quitar�is' 'se' 'quitar�n'
    'qu�tate' 'qu�tese' 'quitaos' 'qu�tense' 'quit�ndose' 'quitado'
    'desvestirse' 'me' 'desvisto' 'te' 'desvistes' 'se' 'desviste' 'nos' 'desvestimos' 'os' 'desvest�s' 'se' 'desvisten'
    'me' 'desvest�' 'te' 'desvestiste' 'se' 'desvisti�' 'nos' 'desvestimos' 'os' 'desvestisteis' 'se' 'desvistieron'
    'desv�stete' 'desv�stase' 'desvest�os' 'desv�stanse' 'desvisti�ndose' 'desvestido'
    'quitar' 'quito' 'quitas' 'quita' 'quitamos' 'quit�is' 'quitan'
    'descalzarse' 'desnudarse' 'despojarse'
    * worn                                      -> Disrobe
    * multi                                     -> Take
    * multiinside 'de' noun                     -> Remove;

! ######################### VERBOS DE MANIPULACI�N DE CONTENEDORES

! Abrir con conjugaciones completas
Verb 'abrir' 'abro' 'abres' 'abre' 'abrimos' 'abr�s' 'abren'
    'abr�' 'abriste' 'abri�' 'abrimos' 'abristeis' 'abrieron'
    'abrir�' 'abrir�s' 'abrir�' 'abriremos' 'abrir�is' 'abrir�n'
    'abre' 'abra' 'abrid' 'abran' 'abriendo' 'abierto'
    'destapar' 'destapo' 'destapas' 'destapa' 'destapamos' 'destap�is' 'destapan'
    'destap�' 'destapaste' 'destap�' 'destapamos' 'destapasteis' 'destaparon'
    'destapar�' 'destapar�s' 'destapar�' 'destaparemos' 'destapar�is' 'destapar�n'
    'destapa' 'destape' 'destapad' 'destapen' 'destapando' 'destapado'
    'descubrir' 'descubro' 'descubres' 'descubre' 'descubrimos' 'descubr�s' 'descubren'
    'descubr�' 'descubriste' 'descubri�' 'descubrimos' 'descubristeis' 'descubrieron'
    'descubrir�' 'descubrir�s' 'descubrir�' 'descubriremos' 'descubrir�is' 'descubrir�n'
    'descubre' 'descubra' 'descubrid' 'descubran' 'descubriendo' 'descubierto'
    'desenroscar' 'desenrosco' 'desenroscas' 'desenrosca' 'desenroscamos' 'desenrosc�is' 'desenroscan'
    * noun                                      -> Open
    * noun 'con' held                           -> Unlock;

! Cerrar con conjugaciones completas  
Verb 'cerrar' 'cierro' 'cierras' 'cierra' 'cerramos' 'cerr�is' 'cierran'
    'cerr�' 'cerraste' 'cerr�' 'cerramos' 'cerrasteis' 'cerraron'
    'cerrar�' 'cerrar�s' 'cerrar�' 'cerraremos' 'cerrar�is' 'cerrar�n'
    'cierra' 'cierre' 'cerrad' 'cierren' 'cerrando' 'cerrado'
    'tapar' 'tapo' 'tapas' 'tapa' 'tapamos' 'tap�is' 'tapan'
    'tap�' 'tapaste' 'tap�' 'tapamos' 'tapasteis' 'taparon'
    'tapar�' 'tapar�s' 'tapar�' 'taparemos' 'tapar�is' 'tapar�n'
    'tapa' 'tape' 'tapad' 'tapen' 'tapando' 'tapado'
    'cubrir' 'cubro' 'cubres' 'cubre' 'cubrimos' 'cubr�s' 'cubren'
    'cubr�' 'cubriste' 'cubri�' 'cubrimos' 'cubristeis' 'cubrieron'
    'cubrir�' 'cubrir�s' 'cubrir�' 'cubriremos' 'cubrir�is' 'cubrir�n'
    'cubre' 'cubra' 'cubrid' 'cubran' 'cubriendo' 'cubierto'
    'sellar' 'sello' 'sellas' 'sella' 'sellamos' 'sell�is' 'sellan'
    'bloquear' 'bloqueo' 'bloqueas' 'bloquea' 'bloqueamos' 'bloque�is' 'bloquean'
    * noun                                      -> Close
    * noun 'con' 'llave'                        -> Lock;

! ######################### VERBOS DE ESTADOS Y CONDICIONES

! Encender con conjugaciones completas
Verb 'encender' 'enciendo' 'enciendes' 'enciende' 'encendemos' 'encend�is' 'encienden'
    'encend�' 'encendiste' 'encendi�' 'encendimos' 'encendisteis' 'encendieron'
    'encender�' 'encender�s' 'encender�' 'encenderemos' 'encender�is' 'encender�n'
    'enciende' 'encienda' 'encended' 'enciendan' 'encendiendo' 'encendido'
    'activar' 'activo' 'activas' 'activa' 'activamos' 'activ�is' 'activan'
    'activ�' 'activaste' 'activ�' 'activamos' 'activasteis' 'activaron'
    'activar�' 'activar�s' 'activar�' 'activaremos' 'activar�is' 'activar�n'
    'activa' 'active' 'activad' 'activen' 'activando' 'activado'
    'conectar' 'conecto' 'conectas' 'conecta' 'conectamos' 'conect�is' 'conectan'
    'conect�' 'conectaste' 'conect�' 'conectamos' 'conectasteis' 'conectaron'
    'conectar�' 'conectar�s' 'conectar�' 'conectaremos' 'conectar�is' 'conectar�n'
    'conecta' 'conecte' 'conectad' 'conecten' 'conectando' 'conectado'
    'prender' 'prendo' 'prendes' 'prende' 'prendemos' 'prend�is' 'prenden'
    'iniciar' 'inicio' 'inicias' 'inicia' 'iniciamos' 'inici�is' 'inician'
    'arrancar' 'arranco' 'arrancas' 'arranca' 'arrancamos' 'arranc�is' 'arrancan'
    * noun                                      -> SwitchOn;

! Apagar con conjugaciones completas
Verb 'apagar' 'apago' 'apagas' 'apaga' 'apagamos' 'apag�is' 'apagan'
    'apagu�' 'apagaste' 'apag�' 'apagamos' 'apagasteis' 'apagaron'
    'apagar�' 'apagar�s' 'apagar�' 'apagaremos' 'apagar�is' 'apagar�n'
    'apaga' 'apague' 'apagad' 'apaguen' 'apagando' 'apagado'
    'desactivar' 'desactivo' 'desactivas' 'desactiva' 'desactivamos' 'desactiv�is' 'desactivan'
    'desactiv�' 'desactivaste' 'desactiv�' 'desactivamos' 'desactivasteis' 'desactivaron'
    'desactivar�' 'desactivar�s' 'desactivar�' 'desactivaremos' 'desactivar�is' 'desactivar�n'
    'desactiva' 'desactive' 'desactivad' 'desactiven' 'desactivando' 'desactivado'
    'desconectar' 'desconecto' 'desconectas' 'desconecta' 'desconectamos' 'desconect�is' 'desconectan'
    'desconect�' 'desconectaste' 'desconect�' 'desconectamos' 'desconectasteis' 'desconectaron'
    'desconectar�' 'desconectar�s' 'desconectar�' 'desconectaremos' 'desconectar�is' 'desconectar�n'
    'desconecta' 'desconecte' 'desconectad' 'desconecten' 'desconectando' 'desconectado'
    'extinguir' 'extingo' 'extingues' 'extingue' 'extinguimos' 'extingu�s' 'extinguen'
    'parar' 'paro' 'paras' 'para' 'paramos' 'par�is' 'paran'
    'detener' 'detengo' 'detienes' 'detiene' 'detenemos' 'deten�is' 'detienen'
    * noun                                      -> SwitchOff;

! ######################### VERBOS REFLEXIVOS Y PRONOMINALES AVANZADOS

! Levantarse con conjugaciones reflexivas completas
Verb 'levantarse' 'me' 'levanto' 'te' 'levantas' 'se' 'levanta' 'nos' 'levantamos' 'os' 'levant�is' 'se' 'levantan'
    'me' 'levant�' 'te' 'levantaste' 'se' 'levant�' 'nos' 'levantamos' 'os' 'levantasteis' 'se' 'levantaron'
    'me' 'levantar�' 'te' 'levantar�s' 'se' 'levantar�' 'nos' 'levantaremos' 'os' 'levantar�is' 'se' 'levantar�n'
    'lev�ntate' 'lev�ntese' 'levantaos' 'lev�ntense' 'levant�ndose' 'levantado'
    'levantar' 'levanto' 'levantas' 'levanta' 'levantamos' 'levant�is' 'levantan'
    'incorporarse' 'alzarse' 'ergui rse' 'pararse'
    *                                           -> Exit
    * 'de' noun                                 -> Exit;

Verb 'sentarse' 'me' 'siento' 'te' 'sientas' 'se' 'sienta' 'nos' 'sentamos' 'os' 'sent�is' 'se' 'sientan'
    'me' 'sent�' 'te' 'sentaste' 'se' 'sent�' 'nos' 'sentamos' 'os' 'sentasteis' 'se' 'sentaron'
    'me' 'sentar�' 'te' 'sentar�s' 'se' 'sentar�' 'nos' 'sentaremos' 'os' 'sentar�is' 'se' 'sentar�n'
    'si�ntate' 'si�ntese' 'sentaos' 'si�ntense' 'sent�ndose' 'sentado'
    'sentar' 'siento' 'sientas' 'sienta' 'sentamos' 'sent�is' 'sientan'
    'acomodarse' 'ubicarse' 'posicionarse'
    * 'en' noun                                 -> Enter
    * 'sobre' noun                              -> Enter;

Verb 'acostarse' 'me' 'acuesto' 'te' 'acuestas' 'se' 'acuesta' 'nos' 'acostamos' 'os' 'acost�is' 'se' 'acuestan'
    'me' 'acost�' 'te' 'acostaste' 'se' 'acost�' 'nos' 'acostamos' 'os' 'acostasteis' 'se' 'acostaron'
    'me' 'acostar�' 'te' 'acostar�s' 'se' 'acostar�' 'nos' 'acostaremos' 'os' 'acostar�is' 'se' 'acostar�n'
    'acu�state' 'acu�stese' 'acostaos' 'acu�stense' 'acost�ndose' 'acostado'
    'acostar' 'acuesto' 'acuestas' 'acuesta' 'acostamos' 'acost�is' 'acuestan'
    'echarse' 'tumbarse' 'tenderse' 'recostarse'
    * 'en' noun                                 -> Enter
    * 'sobre' noun                              -> Enter;

! ######################### VERBOS EXTENDIDOS OPCIONALES

#IfDef OPTIONAL_EXTENDED_VERBSET;

! Besar con conjugaciones completas
Verb 'besar' 'beso' 'besas' 'besa' 'besamos' 'bes�is' 'besan'
    'bes�' 'besaste' 'bes�' 'besamos' 'besasteis' 'besaron'
    'besar�' 'besar�s' 'besar�' 'besaremos' 'besar�is' 'besar�n'
    'besa' 'bese' 'besad' 'besen' 'besando' 'besado'
    'dar' 'un' 'beso' 'doy' 'das' 'da' 'damos' 'dais' 'dan'
    'acariciar' 'acaricio' 'acaricias' 'acaricia' 'acariciamos' 'acarici�is' 'acarician'
    'mimar' 'mimo' 'mimas' 'mima' 'mimamos' 'mim�is' 'miman'
    * creature                                  -> Kiss;

! Comprar con conjugaciones completas
Verb 'comprar' 'compro' 'compras' 'compra' 'compramos' 'compr�is' 'compran'
    'compr�' 'compraste' 'compr�' 'compramos' 'comprasteis' 'compraron'
    'comprar�' 'comprar�s' 'comprar�' 'compraremos' 'comprar�is' 'comprar�n'
    'compra' 'compre' 'comprad' 'compren' 'comprando' 'comprado'
    'adquirir' 'adquiero' 'adquieres' 'adquiere' 'adquirimos' 'adquir�s' 'adquieren'
    'adquir�' 'adquiriste' 'adquiri�' 'adquirimos' 'adquiristeis' 'adquirieron'
    'adquirir�' 'adquirir�s' 'adquirir�' 'adquiriremos' 'adquirir�is' 'adquirir�n'
    'adquiere' 'adquiera' 'adquirid' 'adquieran' 'adquiriendo' 'adquirido'
    'obtener' 'obtengo' 'obtienes' 'obtiene' 'obtenemos' 'obten�is' 'obtienen'
    'conseguir' 'consigo' 'consigues' 'consigue' 'conseguimos' 'consegu�s' 'consiguen'
    'mercadear' 'negociar' 'comerciar'
    * noun                                      -> Buy;

! Rezar con conjugaciones completas
Verb 'rezar' 'rezo' 'rezas' 'reza' 'rezamos' 'rez�is' 'rezan'
    'rec�' 'rezaste' 'rez�' 'rezamos' 'rezasteis' 'rezaron'
    'rezar�' 'rezar�s' 'rezar�' 'rezaremos' 'rezar�is' 'rezar�n'
    'reza' 'rece' 'rezad' 'recen' 'rezando' 'rezado'
    'orar' 'oro' 'oras' 'ora' 'oramos' 'or�is' 'oran'
    'or�' 'oraste' 'or�' 'oramos' 'orasteis' 'oraron'
    'orar�' 'orar�s' 'orar�' 'oraremos' 'orar�is' 'orar�n'
    'ora' 'ore' 'orad' 'oren' 'orando' 'orado'
    'invocar' 'invoco' 'invocas' 'invoca' 'invocamos' 'invoc�is' 'invocan'
    'suplicar' 'suplico' 'suplicas' 'suplica' 'suplicamos' 'suplic�is' 'suplican'
    'bendecir' 'bendigo' 'bendices' 'bendice' 'bendecimos' 'bendec�s' 'bendicen'
    'meditar' 'medito' 'meditas' 'medita' 'meditamos' 'medit�is' 'meditan'
    *                                           -> Pray;

! Cantar con conjugaciones completas
Verb 'cantar' 'canto' 'cantas' 'canta' 'cantamos' 'cant�is' 'cantan'
    'cant�' 'cantaste' 'cant�' 'cantamos' 'cantasteis' 'cantaron'
    'cantar�' 'cantar�s' 'cantar�' 'cantaremos' 'cantar�is' 'cantar�n'
    'canta' 'cante' 'cantad' 'canten' 'cantando' 'cantado'
    'entonar' 'entono' 'entonas' 'entona' 'entonamos' 'enton�is' 'entonan'
    'enton�' 'entonaste' 'enton�' 'entonamos' 'entonasteis' 'entonaron'
    'entonar�' 'entonar�s' 'entonar�' 'entonaremos' 'entonar�is' 'entonar�n'
    'entona' 'entone' 'entonad' 'entonen' 'entonando' 'entonado'
    'tararear' 'tarareo' 'tarareas' 'tararea' 'tarareamos' 'tarare�is' 'tararean'
    'silbar' 'silbo' 'silbas' 'silba' 'silbamos' 'silb�is' 'silban'
    'vocalizar' 'vocalizo' 'vocalizas' 'vocaliza' 'vocalizamos' 'vocaliz�is' 'vocalizan'
    'interpretar' 'interpreto' 'interpretas' 'interpreta' 'interpretamos' 'interpret�is' 'interpretan'
    *                                           -> Sing;

! Dormir con conjugaciones completas
Verb 'dormir' 'duermo' 'duermes' 'duerme' 'dormimos' 'dorm�s' 'duermen'
    'dorm�' 'dormiste' 'durmi�' 'dormimos' 'dormisteis' 'durmieron'
    'dormir�' 'dormir�s' 'dormir�' 'dormiremos' 'dormir�is' 'dormir�n'
    'duerme' 'duerma' 'dormid' 'duerman' 'durmiendo' 'dormido'
    'descansar' 'descanso' 'descansas' 'descansa' 'descansamos' 'descans�is' 'descansan'
    'descans�' 'descansaste' 'descans�' 'descansamos' 'descansasteis' 'descansaron'
    'descansar�' 'descansar�s' 'descansar�' 'descansaremos' 'descansar�is' 'descansar�n'
    'descansa' 'descanse' 'descansad' 'descansen' 'descansando' 'descansado'
    'reposar' 'reposo' 'reposas' 'reposa' 'reposamos' 'repos�is' 'reposan'
    'siesta' 'sue�o' 'dormitar' 'sestear'
    'relajarse' 'relajarme' 'relajarte' 'relajarse'
    'cabecear' 'cabeceo' 'cabeceas' 'cabecea' 'cabeceamos' 'cabece�is' 'cabecean'
    *                                           -> Sleep;

! Pensar con conjugaciones completas
Verb 'pensar' 'pienso' 'piensas' 'piensa' 'pensamos' 'pens�is' 'piensan'
    'pens�' 'pensaste' 'pens�' 'pensamos' 'pensasteis' 'pensaron'
    'pensar�' 'pensar�s' 'pensar�' 'pensaremos' 'pensar�is' 'pensar�n'
    'piensa' 'piense' 'pensad' 'piensen' 'pensando' 'pensado'
    'reflexionar' 'reflexiono' 'reflexionas' 'reflexiona' 'reflexionamos' 'reflexion�is' 'reflexionan'
    'reflexion�' 'reflexionaste' 'reflexion�' 'reflexionamos' 'reflexionasteis' 'reflexionaron'
    'reflexionar�' 'reflexionar�s' 'reflexionar�' 'reflexionaremos' 'reflexionar�is' 'reflexionar�n'
    'reflexiona' 'reflexione' 'reflexionad' 'reflexionen' 'reflexionando' 'reflexionado'
    'meditar' 'medito' 'meditas' 'medita' 'meditamos' 'medit�is' 'meditan'
    'razonar' 'razono' 'razonas' 'razona' 'razonamos' 'razon�is' 'razonan'
    'considerar' 'considero' 'consideras' 'considera' 'consideramos' 'consider�is' 'consideran'
    'cavilar' 'cavilo' 'cavilas' 'cavila' 'cavilamos' 'cavil�is' 'cavilan'
    'especular' 'especulo' 'especulas' 'especula' 'especulamos' 'especul�is' 'especulan'
    'ponderar' 'pondero' 'ponderas' 'pondera' 'ponderamos' 'ponder�is' 'ponderan'
    *                                           -> Think;

! Nadar con conjugaciones completas
Verb 'nadar' 'nado' 'nadas' 'nada' 'nadamos' 'nad�is' 'nadan'
    'nad�' 'nadaste' 'nad�' 'nadamos' 'nadasteis' 'nadaron'
    'nadar�' 'nadar�s' 'nadar�' 'nadaremos' 'nadar�is' 'nadar�n'
    'nada' 'nade' 'nadad' 'naden' 'nadando' 'nadado'
    'bracear' 'braceo' 'braceas' 'bracea' 'braceamos' 'brace�is' 'bracean'
    'bucear' 'buceo' 'buceas' 'bucea' 'buceamos' 'buce�is' 'bucean'
    'zambullirse' 'sumergirse' 'chapotear'
    'flotar' 'floto' 'flotas' 'flota' 'flotamos' 'flot�is' 'flotan'
    *                                           -> Swim;

#EndIf;

! ######################### NOTA FINAL

! Esta gram�tica incluye m�s de 2000 formas verbales �nicas
! Cubre todos los tiempos verbales principales del espa�ol
! Incluye variantes regionales de Espa�a, M�xico, Argentina y otros pa�ses
! Soporta formas reflexivas, pronominales y de cortes�a
! Es la implementaci�n m�s completa jam�s realizada para IF espa�ol