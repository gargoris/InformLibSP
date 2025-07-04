! Gramática Española para PunyInform
! Sistema completo de verbos con conjugaciones, reflexivos y variantes regionales
! Incluye verbos regulares, irregulares y formas de cortesía

System_file;

! ######################### VERBOS BÁSICOS DE MOVIMIENTO

Verb 'ir' 'vete' 'anda' 'camina'
    * noun                                      -> Go
    * 'a' noun                                  -> Go  
    * 'hacia' noun                              -> Go
    * 'para' noun                               -> Go;

Verb 'norte' 'n//'
    *                                           -> Go;
Verb 'sur' 's//'  
    *                                           -> Go;
Verb 'este' 'e//'
    *                                           -> Go;
Verb 'oeste' 'o//'
    *                                           -> Go;
Verb 'noreste' 'ne'
    *                                           -> Go;
Verb 'noroeste' 'no' 'nw'
    *                                           -> Go;
Verb 'sureste' 'se'
    *                                           -> Go;
Verb 'suroeste' 'so' 'sw'
    *                                           -> Go;
Verb 'arriba' 'subir' 'sube' 'u//'
    *                                           -> Go;
Verb 'abajo' 'bajar' 'baja' 'd//'
    *                                           -> Go;
Verb 'entrar' 'dentro' 'adentro'
    *                                           -> GoIn
    * 'en'/'a' noun                             -> Enter;
Verb 'salir' 'fuera' 'afuera'
    *                                           -> Exit
    * 'de'/'del' noun                           -> Exit;

! ######################### VERBOS DE MANIPULACIÓN DE OBJETOS

! Coger/Tomar - con todas las variantes regionales
Verb 'coger' 'coge' 'cojo' 'coges' 'cogemos' 'cogéis' 'cogen'
    'tomar' 'toma' 'tomo' 'tomas' 'tomamos' 'tomáis' 'toman'
    'agarrar' 'agarra' 'agarro' 'agarras' 'agarramos' 'agarráis' 'agarran'
    'pillar' 'pilla' 'pillo' 'pillas' 'pillamos' 'pilláis' 'pillan'
    * multi                                     -> Take
    * 'todo'/'todas'/'todos'                    -> Take
    * multi 'de'/'del'/'de'/'la' noun           -> Remove;

! Dejar/Soltar 
Verb 'dejar' 'deja' 'dejo' 'dejas' 'dejamos' 'dejáis' 'dejan'
    'soltar' 'suelta' 'suelto' 'sueltas' 'soltamos' 'soltáis' 'sueltan'
    'tirar' 'tira' 'tiro' 'tiras' 'tiramos' 'tiráis' 'tiran'
    * multiheld                                 -> Drop
    * multiexcept 'en'/'dentro'/'de' noun       -> Insert
    * held 'a'/'contra'/'sobre' noun            -> ThrowAt;

! Meter/Poner dentro
Verb 'meter' 'mete' 'meto' 'metes' 'metemos' 'metéis' 'meten'
    'introducir' 'introduce' 'introduzco' 'introduces' 'introducimos' 'introducís' 'introducen'
    'insertar' 'inserta' 'inserto' 'insertas' 'insertamos' 'insertáis' 'insertan'
    * multiexcept 'en'/'dentro'/'de' noun       -> Insert;

! Poner/Colocar
Verb 'poner' 'pon' 'pongo' 'pones' 'ponemos' 'ponéis' 'ponen'
    'colocar' 'coloca' 'coloco' 'colocas' 'colocamos' 'colocáis' 'colocan'
    'situar' 'sitúa' 'sitúo' 'sitúas' 'situamos' 'situáis' 'sitúan'
    * multiexcept 'en'/'dentro'/'de' noun       -> Insert
    * multiexcept 'sobre'/'encima'/'de' noun    -> PutOn
    * 'en' held                                 -> Wear;

! ######################### VERBOS DE EXAMINACIÓN

! Mirar
Verb 'mirar' 'mira' 'miro' 'miras' 'miramos' 'miráis' 'miran'
    'ver' 've' 'veo' 'ves' 'vemos' 'veis' 'ven'
    'observar' 'observa' 'observo' 'observas' 'observamos' 'observáis' 'observan'
    'l//' 'm//'
    * noun                                      -> Examine
    * 'a'/'hacia' noun                          -> Examine  
    *                                           -> Look
    * 'en'/'dentro'/'de' noun                   -> Search
    * 'alrededor'                               -> Look;

! Examinar
Verb 'examinar' 'examina' 'examino' 'examinas' 'examinamos' 'examináis' 'examinan'
    'inspeccionar' 'inspecciona' 'inspecciono' 'inspeccionas' 'inspeccionamos' 'inspeccionáis' 'inspeccionan'
    'x//' 'ex'
    * noun                                      -> Examine;

! Buscar
Verb 'buscar' 'busca' 'busco' 'buscas' 'buscamos' 'buscáis' 'buscan'
    'registrar' 'registra' 'registro' 'registras' 'registramos' 'registráis' 'registran'
    * noun                                      -> Search
    * 'en'/'dentro'/'de' noun                   -> Search;

! ######################### VERBOS DE COMUNICACIÓN

! Hablar
Verb 'hablar' 'habla' 'hablo' 'hablas' 'hablamos' 'habláis' 'hablan'
    'decir' 'di' 'digo' 'dices' 'decimos' 'decís' 'dicen'
    'comentar' 'comenta' 'comento' 'comentas' 'comentamos' 'comentáis' 'comentan'
    * topic 'a'/'con' creature                  -> Answer
    * topic 'sobre'/'de' noun 'a'/'con' creature -> Tell;

! Preguntar
Verb 'preguntar' 'pregunta' 'pregunto' 'preguntas' 'preguntamos' 'preguntáis' 'preguntan'
    * creature 'sobre'/'por'/'acerca' 'de' topic -> Ask
    * creature 'por' noun                       -> AskFor
    * creature 'que' topic                      -> AskTo
    * 'a' creature 'sobre'/'por' topic          -> Ask
    * 'a' creature 'por' noun                   -> AskFor;

! Responder
Verb 'responder' 'responde' 'respondo' 'respondes' 'respondemos' 'respondéis' 'responden'
    'contestar' 'contesta' 'contesto' 'contestas' 'contestamos' 'contestáis' 'contestan'
    * topic 'a' creature                        -> Answer;

! ######################### VERBOS DE ACCIÓN FÍSICA

! Atacar
Verb 'atacar' 'ataca' 'ataco' 'atacas' 'atacamos' 'atacáis' 'atacan'
    'golpear' 'golpea' 'golpeo' 'golpeas' 'golpeamos' 'golpeáis' 'golpean'
    'pegar' 'pega' 'pego' 'pegas' 'pegamos' 'pegáis' 'pegan'
    'romper' 'rompe' 'rompo' 'rompes' 'rompemos' 'rompéis' 'rompen'
    'destrozar' 'destroza' 'destrozo' 'destrozas' 'destrozamos' 'destrozáis' 'destrozan'
    * noun                                      -> Attack
    * noun 'con' held                           -> Attack;

! Empujar
Verb 'empujar' 'empuja' 'empujo' 'empujas' 'empujamos' 'empujáis' 'empujan'
    'mover' 'mueve' 'muevo' 'mueves' 'movemos' 'movéis' 'mueven'
    'presionar' 'presiona' 'presiono' 'presionas' 'presionamos' 'presionáis' 'presionan'
    * noun                                      -> Push
    * noun noun=ADirection                      -> PushDir
    * noun 'hacia'/'a' noun                     -> Transfer;

! Tirar (halar)
Verb 'tirar' 'tira' 'tiro' 'tiras' 'tiramos' 'tiráis' 'tiran'
    'halar' 'hala' 'halo' 'halas' 'halamos' 'haláis' 'halan'
    'arrastrar' 'arrastra' 'arrastro' 'arrastras' 'arrastramos' 'arrastráis' 'arrastran'
    * noun                                      -> Pull;

! ######################### VERBOS DE MANIPULACIÓN DE CONTENEDORES

! Abrir
Verb 'abrir' 'abre' 'abro' 'abres' 'abrimos' 'abrís' 'abren'
    'destapar' 'destapa' 'destapo' 'destapas' 'destapamos' 'destapáis' 'destapan'
    * noun                                      -> Open
    * noun 'con' held                           -> Unlock;

! Cerrar  
Verb 'cerrar' 'cierra' 'cierro' 'cierras' 'cerramos' 'cerráis' 'cierran'
    'tapar' 'tapa' 'tapo' 'tapas' 'tapamos' 'tapáis' 'tapan'
    * noun                                      -> Close
    * noun 'con' 'llave'                        -> Lock;

! ######################### VERBOS DE ESTADOS Y CONDICIONES

! Encender
Verb 'encender' 'enciende' 'enciendo' 'enciendes' 'encendemos' 'encendéis' 'encienden'
    'activar' 'activa' 'activo' 'activas' 'activamos' 'activáis' 'activan'
    'conectar' 'conecta' 'conecto' 'conectas' 'conectamos' 'conectáis' 'conectan'
    * noun                                      -> SwitchOn;

! Apagar
Verb 'apagar' 'apaga' 'apago' 'apagas' 'apagamos' 'apagáis' 'apagan'
    'desactivar' 'desactiva' 'desactivo' 'desactivas' 'desactivamos' 'desactiváis' 'desactivan'
    'desconectar' 'desconecta' 'desconecto' 'desconectas' 'desconectamos' 'desconectáis' 'desconectan'
    * noun                                      -> SwitchOff;

! ######################### VERBOS SENSORIALES

! Tocar
Verb 'tocar' 'toca' 'toco' 'tocas' 'tocamos' 'tocáis' 'tocan'
    'palpar' 'palpa' 'palpo' 'palpas' 'palpamos' 'palpáis' 'palpan'
    'sentir' 'siente' 'siento' 'sientes' 'sentimos' 'sentís' 'sienten'
    * noun                                      -> Touch;

! Oler
Verb 'oler' 'huele' 'huelo' 'hueles' 'olemos' 'oléis' 'huelen'
    'olfatear' 'olfatea' 'olfateo' 'olfateas' 'olfateamos' 'olfateáis' 'olfatean'
    *                                           -> Smell
    * noun                                      -> Smell;

! Escuchar
Verb 'escuchar' 'escucha' 'escucho' 'escuchas' 'escuchamos' 'escucháis' 'escuchan'
    'oír' 'oye' 'oigo' 'oyes' 'oímos' 'oís' 'oyen'
    *                                           -> Listen
    * 'a' noun                                  -> Listen
    * noun                                      -> Listen;

! ######################### VERBOS DE CONSUMO

! Comer
Verb 'comer' 'come' 'como' 'comes' 'comemos' 'coméis' 'comen'
    'devorar' 'devora' 'devoro' 'devoras' 'devoramos' 'devoráis' 'devoran'
    'tragar' 'traga' 'trago' 'tragas' 'tragamos' 'tragáis' 'tragan'
    * held                                      -> Eat;

! Beber
Verb 'beber' 'bebe' 'bebo' 'bebes' 'bebemos' 'bebéis' 'beben'
    'tomar' 'toma' 'tomo' 'tomas' 'tomamos' 'tomáis' 'toman'
    * noun                                      -> Drink;

! ######################### VERBOS DE VESTIMENTA

! Ponerse (vestirse) - simplificado
Verb 'ponerse' 'vestirse' 'vestir'
    * held                                      -> Wear;

! Quitarse (desvestirse) - simplificado  
Verb 'quitarse' 'desvestirse' 'quitar'
    * worn                                      -> Disrobe
    * multi                                     -> Take
    * multiinside 'de' noun                     -> Remove;

! ######################### VERBOS METACOMANDOS

! Inventario
Verb 'inventario' 'inv' 'i//'
    *                                           -> Inv;

! Puntuación
Verb 'puntuación' 'puntos' 'score'
    *                                           -> Score;

! Salir del juego
Verb 'salir' 'abandonar' 'terminar' 'quit' 'q//'
    *                                           -> Quit;

! Guardar
Verb 'guardar' 'grabar' 'salvar' 'save'
    *                                           -> Save;

! Cargar
Verb 'cargar' 'restore' 'recuperar'
    *                                           -> Restore;

! Reiniciar
Verb 'reiniciar' 'restart' 'empezar'
    *                                           -> Restart;

! Esperar
Verb 'esperar' 'espera' 'espero' 'esperas' 'esperamos' 'esperáis' 'esperan'
    'z//' 'wait'
    *                                           -> Wait;

! Repetir
Verb 'repetir' 'repite' 'repito' 'repites' 'repetimos' 'repetís' 'repiten'
    'otra' 'vez' 'again' 'g//'
    *                                           -> Again;

! ######################### VERBOS REFLEXIVOS Y PRONOMINALES

! Simplificados por ahora - sin pronombres
Verb 'levantarse' 'levantar'
    *                                           -> Exit
    * 'de' noun                                 -> Exit;

Verb 'sentarse' 'sentar'
    * 'en' noun                                 -> Enter
    * 'sobre' noun                              -> Enter;

Verb 'acostarse' 'acostar'
    * 'en' noun                                 -> Enter
    * 'sobre' noun                              -> Enter;

! ######################### IMPLEMENTACIÓN DE ACCIONES

! Funcion simplificada - no usar noun=ADirection por ahora

! ######################### VERBOS EXTENDIDOS OPCIONALES

#IfDef OPTIONAL_EXTENDED_VERBSET;

! Besar
Verb 'besar' 'besa' 'beso' 'besas' 'besamos' 'besáis' 'besan'
    * creature                                  -> Kiss;

! Comprar
Verb 'comprar' 'compra' 'compro' 'compras' 'compramos' 'compráis' 'compran'
    * noun                                      -> Buy;

! Rezar
Verb 'rezar' 'reza' 'rezo' 'rezas' 'rezamos' 'rezáis' 'rezan'
    'orar' 'ora' 'oro' 'oras' 'oramos' 'oráis' 'oran'
    *                                           -> Pray;

! Cantar
Verb 'cantar' 'canta' 'canto' 'cantas' 'cantamos' 'cantáis' 'cantan'
    *                                           -> Sing;

! Dormir
Verb 'dormir' 'duerme' 'duermo' 'duermes' 'dormimos' 'dormís' 'duermen'
    'descansar' 'descansa' 'descanso' 'descansas' 'descansamos' 'descansáis' 'descansan'
    *                                           -> Sleep;

! Pensar
Verb 'pensar' 'piensa' 'pienso' 'piensas' 'pensamos' 'pensáis' 'piensan'
    *                                           -> Think;

! Nadar
Verb 'nadar' 'nada' 'nado' 'nadas' 'nadamos' 'nadáis' 'nadan'
    *                                           -> Swim;

#EndIf;