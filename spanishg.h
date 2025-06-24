! ==============================================================================
!   SPANISHG:  Grammar Spanish File
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
! ==============================================================================

System_file;
Message "^Incluyendo SpanishG: Gramática española [InformLibSP]";

! ==============================================================================
!   Rutinas de utilidad y configuración
! ==============================================================================

#ifdef DEBUG;
  [ ActivarAcentosSub;
    quitacentos = 0;
    "Los acentos no serán eliminados del comando recibido.";
  ];

  [ DesactivarAcentosSub;
    quitacentos = 1;
    "Los acentos serán eliminados del comando recibido, pero sólo en
      las palabras que de otro modo no serían comprendidas.";
  ];
#endif; ! DEBUG

! Elección del dialecto (afecta a la interpretación del
! verbo COGER únicamente)

[ DialectoSub;
  print "Actualmente estás jugando en el dialecto ";
  if (dialecto_sudamericano)
    print "sudamericano";
  else
    print "castellano";
  ". Puedes elegir dialecto usando el comando DIALECTO SUDAMERICANO \
    o bien DIALECTO CASTELLANO.";
];

[ DialectoSudSub;
  dialecto_sudamericano = 2;
  "Elegido dialecto SUDAMERICANO.";
];

[ DialectoCastSub;
  dialecto_sudamericano = 0;
  "Elegido dialecto CASTELLANO.";
];

! ==============================================================================
!   Rutinas auxiliares para acciones comunes
! ==============================================================================

[ SubirSub;
  <<Go u_obj>>;
];

[ BajarSub p;
  p=parent(player);
  if ((p~=location) && (p has supporter))
     if (noun~=nothing) <<GetOff noun>>;
     else <<GetOff p>>;
  if (noun==nothing)  <<Go d_obj>>;
  if (noun has door) <<Enter noun>>;
  L__M(##Enter,2,noun);
];

[ QuitarSub;
    if (second) <<Remove noun second>>;
    if (noun in player) <<Disrobe noun>>;
    <<Take noun>>;
];

#ifdef ADMITIR_COMANDO_SALIDAS;
  [ SalidasSub i flag flag2 j loc;
    print "Salidas visibles:";
    if (location == thedark)
      loc = real_location;
    else
      loc = location;
    
    objectloop(i in compass) {
      j = loc.(i.door_dir);
      if (j ~= 0) {
        if (j has door) {
          if (j has open || j has transparent) {
            flag = true;
            flag2 = true;
          }
        }
        else {
          flag = true;
          flag2 = true;
        }
      }
      if (flag) {
        if (flag2) print " ", (name) i;
        else print " (", (name) i, " - cerrada)";
      }
      flag = false;
      flag2 = false;
    }
    if (loc provides salidas) {
      print " ", (string) loc.salidas;
    }
    "";
  ];
#endif; ! ADMITIR_COMANDO_SALIDAS

! ==============================================================================
!   Definición de verbos y gramática
! ==============================================================================

! ----------------------------------------------------------------------------
! Verbos de movimiento
! ----------------------------------------------------------------------------

Verb 'ir' 'voy' 'vas' 'va' 'vamos' 'vais' 'van'
  *                                   -> VagueGo
  * 'a//' noun                        -> Go
  * 'hacia' noun                      -> Go
  * noun                              -> Enter;
VerboIrregular "ir" with imperativo 'ir' 've' 'vaya' 'id' 'vayan',
                     presente 'voy' 'vas' 'va' 'vamos' 'vais' 'van',
                     pasado 'fui' 'fuiste' 'fue' 'fuimos' 'fuisteis' 'fueron',
                     futuro 'iré' 'irás' 'irá' 'iremos' 'iréis' 'irán';

Verb 'n//' 'norte'
  *                                   -> Go;
VerboIrregular "ir al norte" with imperativo 'n//' 'norte';

Verb 's//' 'sur'
  *                                   -> Go;
VerboIrregular "ir al sur" with imperativo 's//' 'sur';

Verb 'e//' 'este'
  *                                   -> Go;
VerboIrregular "ir al este" with imperativo 'e//' 'este';

Verb 'o//' 'oeste' 'w//'
  *                                   -> Go;
VerboIrregular "ir al oeste" with imperativo 'o//' 'oeste' 'w//';

Verb 'ne' 'nordeste' 'noreste'
  *                                   -> Go;
VerboIrregular "ir al nordeste" with imperativo 'ne' 'nordeste' 'noreste';

Verb 'no' 'noroeste' 'nw'
  *                                   -> Go;
VerboIrregular "ir al noroeste" with imperativo 'no' 'noroeste' 'nw';

Verb 'se' 'sudeste' 'sureste'
  *                                   -> Go;
VerboIrregular "ir al sudeste" with imperativo 'se' 'sudeste' 'sureste';

Verb 'so' 'sudoeste' 'suroeste' 'sw'
  *                                   -> Go;
VerboIrregular "ir al sudoeste" with imperativo 'so' 'sudoeste' 'suroeste' 'sw';

Verb 'arriba' 'sube' 'subir' 'u//' 'ar' 'r//' 'subo' 'subes' 'subimos' 'subís' 'suben'
  *                                   -> Go
  * noun                              -> Enter;
VerboIrregular "subir" with imperativo 'arriba' 'sube' 'subir' 'u//' 'ar' 'r//',
                        presente 'subo' 'subes' 'sube' 'subimos' 'subís' 'suben';

Verb 'abajo' 'baja' 'bajar' 'd//' 'ab' 'b//' 'bajo' 'bajas' 'bajamos' 'bajáis' 'bajan'
  *                                   -> Go
  * noun                              -> Enter;
VerboIrregular "bajar" with imperativo 'abajo' 'baja' 'bajar' 'd//' 'ab' 'b//',
                        presente 'bajo' 'bajas' 'baja' 'bajamos' 'bajáis' 'bajan';

Verb 'entra' 'entrar' 'adentro' 'dentro' 'entro' 'entras' 'entramos' 'entráis' 'entran'
  *                                   -> GoIn
  * 'en//' / 'por' noun              -> Enter;
VerboIrregular "entrar" with imperativo 'entra' 'entrar' 'adentro' 'dentro',
                         presente 'entro' 'entras' 'entra' 'entramos' 'entráis' 'entran';

Verb 'sal' 'salir' 'afuera' 'fuera' 'salgo' 'sales' 'sale' 'salimos' 'salís' 'salen'
  *                                   -> Exit
  * 'de' noun                         -> GetOff
  * 'por' noun                        -> Exit;
VerboIrregular "salir" with imperativo 'sal' 'salir' 'afuera' 'fuera',
                        presente 'salgo' 'sales' 'sale' 'salimos' 'salís' 'salen';

! ----------------------------------------------------------------------------
! Verbos de manipulación
! ----------------------------------------------------------------------------

Verb 'coge' 'toma' 'recoge' 'atrapa' 'captura' 'cojo' 'coges' 'coge' 'cogemos' 'cogéis' 'cogen'
  * multi                             -> Take
  * 'a//' creature                    -> Take;
VerboIrregular "coger" with imperativo 'coge' 'toma' 'recoge' 'atrapa' 'captura',
                        presente 'cojo' 'coges' 'coge' 'cogemos' 'cogéis' 'cogen';

Verb 'agarra' 'sostiene' 'sujeta' 'agarro' 'agarras' 'agarra' 'agarramos' 'agarráis' 'agarran'
  * multi                             -> Take;
VerboIrregular "agarrar" with imperativo 'agarra' 'sostiene' 'sujeta',
                          presente 'agarro' 'agarras' 'agarra' 'agarramos' 'agarráis' 'agarran';

Verb 'deja' 'suelta' 'libera' 'abandona' 'dejo' 'dejas' 'deja' 'dejamos' 'dejáis' 'dejan'
  * multiheld                         -> Drop
  * 'a//' creature                    -> Release
  * multiheld 'en//' noun             -> Insert
  * multiheld 'sobre' noun            -> PutOn;
VerboIrregular "dejar" with imperativo 'deja' 'suelta' 'libera' 'abandona',
                        presente 'dejo' 'dejas' 'deja' 'dejamos' 'dejáis' 'dejan';

Verb 'mete' 'pon' 'coloca' 'inserta' 'introduce' 'meto' 'metes' 'mete' 'metemos' 'metéis' 'meten'
  * multiexcept 'en//' noun           -> Insert
  * multiexcept 'dentro' 'de' noun    -> Insert
  * multiexcept 'sobre' noun          -> PutOn
  * multiexcept 'encima' 'de' noun    -> PutOn
  * 'a//' creature 'en//' noun        -> Insert
  * 'a//' creature 'sobre' noun       -> PutOn;
VerboIrregular "meter" with imperativo 'mete' 'pon' 'coloca' 'inserta' 'introduce',
                        presente 'meto' 'metes' 'mete' 'metemos' 'metéis' 'meten';

Verb 'quita' 'saca' 'extrae' 'quito' 'quitas' 'quita' 'quitamos' 'quitáis' 'quitan'
  * multi                             -> Take
  * multi 'de' noun                   -> Remove
  * 'a//' creature 'de' noun          -> Remove;
VerboIrregular "quitar" with imperativo 'quita' 'saca' 'extrae',
                         presente 'quito' 'quitas' 'quita' 'quitamos' 'quitáis' 'quitan';

Verb 'vacia' 'vacío' 'vacías' 'vacía' 'vaciamos' 'vaciáis' 'vacían'
  * noun                              -> Empty
  * noun 'en//' noun                  -> EmptyT
  * noun 'sobre' noun                 -> EmptyT;
VerboIrregular "vaciar" with imperativo 'vacia',
                         presente 'vacío' 'vacías' 'vacía' 'vaciamos' 'vaciáis' 'vacían';

Verb 'transfiere' 'mueve' 'cambia' 'desplaza' 'transfiero' 'transfieres' 'transfiere' 'transferimos' 'transferís' 'transfieren'
  * noun 'a//' noun                   -> Transfer;
VerboIrregular "transferir" with imperativo 'transfiere' 'mueve' 'cambia' 'desplaza',
                            presente 'transfiero' 'transfieres' 'transfiere' 'transferimos' 'transferís' 'transfieren';

! ----------------------------------------------------------------------------
! Verbos de examen
! ----------------------------------------------------------------------------

Verb 'examina' 'x//' 'ex' 'mira' 'l//' 'observa' 'contempla' 'examino' 'examinas' 'examina' 'examinamos' 'examináis' 'examinan'
  *                                   -> Look
  * 'a//' / 'hacia' noun              -> Examine;
VerboIrregular "examinar" with imperativo 'examina' 'x//' 'ex' 'mira' 'l//' 'observa' 'contempla',
                          presente 'examino' 'examinas' 'examina' 'examinamos' 'examináis' 'examinan';

Verb 'lee' 'ojea' 'leo' 'lees' 'lee' 'leemos' 'leéis' 'leen'
  * noun                              -> Examine;
VerboIrregular "leer" with imperativo 'lee' 'ojea',
                      presente 'leo' 'lees' 'lee' 'leemos' 'leéis' 'leen';

Verb 'consulta' 'consulto' 'consultas' 'consulta' 'consultamos' 'consultáis' 'consultan'
  * noun                              -> Consult
  * noun 'sobre' topic                -> Consult
  * noun 'acerca' 'de' topic          -> Consult;
VerboIrregular "consultar" with imperativo 'consulta',
                           presente 'consulto' 'consultas' 'consulta' 'consultamos' 'consultáis' 'consultan';

Verb 'busca' 'rebusca' 'busco' 'buscas' 'busca' 'buscamos' 'buscáis' 'buscan'
  * 'en//' noun                       -> Search
  * 'dentro' 'de' noun                -> Search
  * topic 'en//' noun                 -> Consult;
VerboIrregular "buscar" with imperativo 'busca' 'rebusca',
                        presente 'busco' 'buscas' 'busca' 'buscamos' 'buscáis' 'buscan';

! ----------------------------------------------------------------------------
! Verbos de interacción con objetos
! ----------------------------------------------------------------------------

Verb 'abre' 'destapa' 'abro' 'abres' 'abre' 'abrimos' 'abrís' 'abren'
  * noun                              -> Open
  * noun 'con' held                   -> Unlock;
VerboIrregular "abrir" with imperativo 'abre' 'destapa',
                       presente 'abro' 'abres' 'abre' 'abrimos' 'abrís' 'abren';

Verb 'cierra' 'tapa' 'cierro' 'cierras' 'cierra' 'cerramos' 'cerráis' 'cierran'
  * noun                              -> Close
  * noun 'con' held                   -> Lock;
VerboIrregular "cerrar" with imperativo 'cierra' 'tapa',
                        presente 'cierro' 'cierras' 'cierra' 'cerramos' 'cerráis' 'cierran';

Verb 'bloquea' 'traba' 'bloqueo' 'bloqueas' 'bloquea' 'bloqueamos' 'bloqueáis' 'bloquean'
  * noun                              -> Lock
  * noun 'con' held                   -> Lock;
VerboIrregular "bloquear" with imperativo 'bloquea' 'traba',
                          presente 'bloqueo' 'bloqueas' 'bloquea' 'bloqueamos' 'bloqueáis' 'bloquean';

Verb 'desbloquea' 'destraba' 'desbloqueo' 'desbloqueas' 'desbloquea' 'desbloqueamos' 'desbloqueáis' 'desbloquean'
  * noun                              -> Unlock
  * noun 'con' held                   -> Unlock;
VerboIrregular "desbloquear" with imperativo 'desbloquea' 'destraba',
                              presente 'desbloqueo' 'desbloqueas' 'desbloquea' 'desbloqueamos' 'desbloqueáis' 'desbloquean';

Verb 'enciende' 'prende' 'enciendo' 'enciendes' 'enciende' 'encendemos' 'encendéis' 'encienden'
  * noun                              -> SwitchOn;
VerboIrregular "encender" with imperativo 'enciende' 'prende',
                          presente 'enciendo' 'enciendes' 'enciende' 'encendemos' 'encendéis' 'encienden';

Verb 'apaga' 'apago' 'apagas' 'apaga' 'apagamos' 'apagáis' 'apagan'
  * noun                              -> SwitchOff;
VerboIrregular "apagar" with imperativo 'apaga',
                        presente 'apago' 'apagas' 'apaga' 'apagamos' 'apagáis' 'apagan';

Verb 'empuja' 'mueve' 'desplaza' 'arrastra' 'empujo' 'empujas' 'empuja' 'empujamos' 'empujáis' 'empujan'
  * noun                              -> Push
  * noun noun                         -> PushDir;
VerboIrregular "empujar" with imperativo 'empuja' 'mueve' 'desplaza' 'arrastra',
                          presente 'empujo' 'empujas' 'empuja' 'empujamos' 'empujáis' 'empujan';

Verb 'gira' 'atornilla' 'desatornilla' 'giro' 'giras' 'gira' 'giramos' 'giráis' 'giran'
  * noun                              -> Turn;
VerboIrregular "girar" with imperativo 'gira' 'atornilla' 'desatornilla',
                        presente 'giro' 'giras' 'gira' 'giramos' 'giráis' 'giran';

Verb 'pulsa' 'presiona' 'aprieta' 'oprime' 'pulso' 'pulsas' 'pulsa' 'pulsamos' 'pulsáis' 'pulsan'
  * noun                              -> Push;
VerboIrregular "pulsar" with imperativo 'pulsa' 'presiona' 'aprieta' 'oprime',
                        presente 'pulso' 'pulsas' 'pulsa' 'pulsamos' 'pulsáis' 'pulsan';

Verb 'tira' 'tiro' 'tiras' 'tira' 'tiramos' 'tiráis' 'tiran'
  * 'de' noun                         -> Pull;
VerboIrregular "tirar" with imperativo 'tira',
                       presente 'tiro' 'tiras' 'tira' 'tiramos' 'tiráis' 'tiran';

! ----------------------------------------------------------------------------
! Verbos de interacción con personajes
! ----------------------------------------------------------------------------

Verb 'habla' 'conversa' 'platica' 'hablo' 'hablas' 'habla' 'hablamos' 'habláis' 'hablan'
  * 'con' creature                    -> Talk;
VerboIrregular "hablar" with imperativo 'habla' 'conversa' 'platica',
                        presente 'hablo' 'hablas' 'habla' 'hablamos' 'habláis' 'hablan';

Verb 'pregunta' 'pregunto' 'preguntas' 'pregunta' 'preguntamos' 'preguntáis' 'preguntan'
  * creature 'sobre' / 'por' / 'acerca' topic -> Ask
  * creature 'sobre' / 'por' / 'acerca' 'de' topic -> Ask;
VerboIrregular "preguntar" with imperativo 'pregunta',
                           presente 'pregunto' 'preguntas' 'pregunta' 'preguntamos' 'preguntáis' 'preguntan';

Verb 'cuenta' 'di' 'dile' 'cuento' 'cuentas' 'cuenta' 'contamos' 'contáis' 'cuentan'
  * creature 'sobre' / 'acerca' 'de' topic -> Tell
  * creature topic                    -> Tell;
VerboIrregular "contar" with imperativo 'cuenta' 'di' 'dile',
                        presente 'cuento' 'cuentas' 'cuenta' 'contamos' 'contáis' 'cuentan';

Verb 'responde' 'contesta' 'respondo' 'respondes' 'responde' 'respondemos' 'respondéis' 'responden'
  * creature topic                    -> Answer
  * topic 'a//' creature              -> Answer;
VerboIrregular "responder" with imperativo 'responde' 'contesta',
                           presente 'respondo' 'respondes' 'responde' 'respondemos' 'respondéis' 'responden';

Verb 'da' 'dale' 'regala' 'ofrece' 'doy' 'das' 'da' 'damos' 'dais' 'dan'
  * held 'a//' creature               -> Give
  * creature held                     -> Give;
VerboIrregular "dar" with imperativo 'da' 'dale' 'regala' 'ofrece',
                     presente 'doy' 'das' 'da' 'damos' 'dais' 'dan';

Verb 'muestra' 'ensena' 'enseña' 'muestro' 'muestras' 'muestra' 'mostramos' 'mostráis' 'muestran'
  * held 'a//' creature               -> Show
  * creature held                     -> Show;
VerboIrregular "mostrar" with imperativo 'muestra' 'ensena' 'enseña',
                         presente 'muestro' 'muestras' 'muestra' 'mostramos' 'mostráis' 'muestran';

! ----------------------------------------------------------------------------
! Verbos de percepción sensorial
! ----------------------------------------------------------------------------

Verb 'huele' 'olfatea' 'huelo' 'hueles' 'huele' 'olemos' 'oléis' 'huelen'
  *                                   -> Smell
  * noun                              -> Smell;
VerboIrregular "oler" with imperativo 'huele' 'olfatea',
                      presente 'huelo' 'hueles' 'huele' 'olemos' 'oléis' 'huelen';

Verb 'escucha' 'oye' 'escucho' 'escuchas' 'escucha' 'escuchamos' 'escucháis' 'escuchan'
  *                                   -> Listen
  * noun                              -> Listen;
VerboIrregular "escuchar" with imperativo 'escucha' 'oye',
                          presente 'escucho' 'escuchas' 'escucha' 'escuchamos' 'escucháis' 'escuchan';

Verb 'saborea' 'paladea' 'prueba' 'lame' 'chupa' 'saboreo' 'saboreas' 'saborea' 'saboreamos' 'saboreáis' 'saborean'
  * noun                              -> Taste;
VerboIrregular "saborear" with imperativo 'saborea' 'paladea' 'prueba' 'lame' 'chupa',
                          presente 'saboreo' 'saboreas' 'saborea' 'saboreamos' 'saboreáis' 'saborean';

Verb 'toca' 'palpa' 'acaricia' 'toco' 'tocas' 'toca' 'tocamos' 'tocáis' 'tocan'
  * noun                              -> Touch;
VerboIrregular "tocar" with imperativo 'toca' 'palpa' 'acaricia',
                       presente 'toco' 'tocas' 'toca' 'tocamos' 'tocáis' 'tocan';

Verb 'frota' 'limpia' 'pule' 'abrillanta' 'friega' 'froto' 'frotas' 'frota' 'frotamos' 'frotáis' 'frotan'
  * noun                              -> Rub;
VerboIrregular "frotar" with imperativo 'frota' 'limpia' 'pule' 'abrillanta' 'friega',
                        presente 'froto' 'frotas' 'frota' 'frotamos' 'frotáis' 'frotan';

Verb 'ata' 'liga' 'amarra' 'ato' 'atas' 'ata' 'atamos' 'atáis' 'atan'
  * noun                              -> Tie
  * noun 'a//' noun                   -> Tie;
VerboIrregular "atar" with imperativo 'ata' 'liga' 'amarra',
                      presente 'ato' 'atas' 'ata' 'atamos' 'atáis' 'atan';

Verb 'quema' 'prende' 'incendia' 'inflama' 'quemo' 'quemas' 'quema' 'quemamos' 'quemáis' 'queman'
  * noun                              -> Burn;
VerboIrregular "quemar" with imperativo 'quema' 'prende' 'incendia' 'inflama',
                        presente 'quemo' 'quemas' 'quema' 'quemamos' 'quemáis' 'queman';

Verb 'bebe' 'traga' 'bebo' 'bebes' 'bebe' 'bebemos' 'bebéis' 'beben'
  * noun                              -> Drink;
VerboIrregular "beber" with imperativo 'bebe' 'traga',
                       presente 'bebo' 'bebes' 'bebe' 'bebemos' 'bebéis' 'beben';

Verb 'llena' 'lleno' 'llenas' 'llena' 'llenamos' 'llenáis' 'llenan'
  * noun                              -> Fill;
VerboIrregular "llenar" with imperativo 'llena',
                        presente 'lleno' 'llenas' 'llena' 'llenamos' 'llenáis' 'llenan';

! ----------------------------------------------------------------------------
! Verbos de acciones personales
! ----------------------------------------------------------------------------

Verb 'inventario' 'i//' 'inv'
  *                                   -> Inv;
VerboIrregular "mostrar inventario" with imperativo 'inventario' 'i//' 'inv';

Verb 'espera' 'z//' 'espero' 'esperas' 'espera' 'esperamos' 'esperáis' 'esperan'
  *                                   -> Wait;
VerboIrregular "esperar" with imperativo 'espera' 'z//',
                         presente 'espero' 'esperas' 'espera' 'esperamos' 'esperáis' 'esperan';

Verb 'duerme' 'descansa' 'duermo' 'duermes' 'duerme' 'dormimos' 'dormís' 'duermen'
  *                                   -> Sleep;
VerboIrregular "dormir" with imperativo 'duerme' 'descansa',
                        presente 'duermo' 'duermes' 'duerme' 'dormimos' 'dormís' 'duermen';

Verb 'despierta' 'despertate' 'espabila' 'espabilate' 'despierto' 'despiertas' 'despierta' 'despertamos' 'despertáis' 'despiertan'
  *                                   -> Wake
  * creature                          -> WakeOther;
VerboIrregular "despertar" with imperativo 'despierta' 'despertate' 'espabila' 'espabilate',
                           presente 'despierto' 'despiertas' 'despierta' 'despertamos' 'despertáis' 'despiertan';

Verb 'vistete' 'ponte' 'me visto' 'te vistes' 'se viste' 'nos vestimos' 'os vestís' 'se visten'
  * held                              -> Wear;
VerboIrregular "vestirse" with imperativo 'vistete' 'ponte',
                          presente 'me visto' 'te vistes' 'se viste' 'nos vestimos' 'os vestís' 'se visten';

Verb 'quitarse' 'quitate' 'sacate' 'me quito' 'te quitas' 'se quita' 'nos quitamos' 'os quitáis' 'se quitan'
  * held                              -> Disrobe;
VerboIrregular "quitarse" with imperativo 'quitarse' 'quitate' 'sacate',
                          presente 'me quito' 'te quitas' 'se quita' 'nos quitamos' 'os quitáis' 'se quitan';

Verb 'besa' 'abraza' 'beso' 'besas' 'besa' 'besamos' 'besáis' 'besan'
  * creature                          -> Kiss;
VerboIrregular "besar" with imperativo 'besa' 'abraza',
                       presente 'beso' 'besas' 'besa' 'besamos' 'besáis' 'besan';

Verb 'piensa' 'pienso' 'piensas' 'piensa' 'pensamos' 'pensáis' 'piensan'
  *                                   -> Think;
VerboIrregular "pensar" with imperativo 'piensa',
                        presente 'pienso' 'piensas' 'piensa' 'pensamos' 'pensáis' 'piensan';

Verb 'salta' 'brinca' 'salto' 'saltas' 'salta' 'saltamos' 'saltáis' 'saltan'
  *                                   -> Jump
  * 'sobre' noun                      -> JumpOver;
VerboIrregular "saltar" with imperativo 'salta' 'brinca',
                        presente 'salto' 'saltas' 'salta' 'saltamos' 'saltáis' 'saltan';

Verb 'nada' 'nado' 'nadas' 'nada' 'nadamos' 'nadáis' 'nadan'
  *                                   -> Swim;
VerboIrregular "nadar" with imperativo 'nada',
                       presente 'nado' 'nadas' 'nada' 'nadamos' 'nadáis' 'nadan';

Verb 'balanceate' 'columpiate' 'mecete' 'me balanceo' 'te balanceas' 'se balancea' 'nos balanceamos' 'os balanceáis' 'se balancean'
  *                                   -> Swing
  * 'en//' noun                       -> Swing;
VerboIrregular "balancearse" with imperativo 'balanceate' 'columpiate' 'mecete',
                              presente 'me balanceo' 'te balanceas' 'se balancea' 'nos balanceamos' 'os balanceáis' 'se balancean';

Verb 'sopla' 'soplo' 'soplas' 'sopla' 'soplamos' 'sopláis' 'soplan'
  * noun                              -> Blow;
VerboIrregular "soplar" with imperativo 'sopla',
                        presente 'soplo' 'soplas' 'sopla' 'soplamos' 'sopláis' 'soplan';

Verb 'reza' 'ora' 'rezo' 'rezas' 'reza' 'rezamos' 'rezáis' 'rezan'
  *                                   -> Pray;
VerboIrregular "rezar" with imperativo 'reza' 'ora',
                       presente 'rezo' 'rezas' 'reza' 'rezamos' 'rezáis' 'rezan';

Verb 'rompe' 'destruye' 'aplasta' 'golpea' 'patea' 'rompo' 'rompes' 'rompe' 'rompemos' 'rompéis' 'rompen'
  * noun                              -> Attack;
VerboIrregular "romper" with imperativo 'rompe' 'destruye' 'aplasta' 'golpea' 'patea',
                        presente 'rompo' 'rompes' 'rompe' 'rompemos' 'rompéis' 'rompen';

Verb 'ataca' 'mata' 'asesina' 'tortura' 'ataco' 'atacas' 'ataca' 'atacamos' 'atacáis' 'atacan'
  * creature                          -> Attack;
VerboIrregular "atacar" with imperativo 'ataca' 'mata' 'asesina' 'tortura',
                         presente 'ataco' 'atacas' 'ataca' 'atacamos' 'atacáis' 'atacan';

Verb 'trepa' 'escala' 'trepo' 'trepas' 'trepa' 'trepamos' 'trepáis' 'trepan'
  * noun                              -> Climb;
VerboIrregular "trepar" with imperativo 'trepa' 'escala',
                        presente 'trepo' 'trepas' 'trepa' 'trepamos' 'trepáis' 'trepan';

! ----------------------------------------------------------------------------
! Verbos de meta-comandos
! ----------------------------------------------------------------------------

Verb 'puntuacion' 'punt' 'puntos'
  *                                   -> Score;
VerboIrregular "mostrar puntuación" with imperativo 'puntuacion' 'punt' 'puntos';

Verb 'version' 'ver'
  *                                   -> Version;
VerboIrregular "mostrar versión" with imperativo 'version' 'ver';

Verb 'q//' 'terminar' 'fin' 'acabar' 'abandonar'
  *                                   -> Quit;
VerboIrregular "terminar el juego" with imperativo 'q//' 'terminar' 'fin' 'acabar' 'abandonar';

Verb 'reiniciar' 'reinicia'
  *                                   -> Restart;
VerboIrregular "reiniciar el juego" with imperativo 'reiniciar' 'reinicia';

Verb 'recuperar' 'restaurar' 'cargar'
  *                                   -> Restore;
VerboIrregular "recuperar un juego guardado" with imperativo 'recuperar' 'restaurar' 'cargar';

Verb 'guardar' 'salvar'
  *                                   -> Save;
VerboIrregular "guardar el juego" with imperativo 'guardar' 'salvar';

Verb 'script' 'transcripcion'
  *                                   -> ScriptOn
  * 'on'                              -> ScriptOn
  * 'off'                             -> ScriptOff;
VerboIrregular "activar/desactivar transcripción" with imperativo 'script' 'transcripcion';

Verb 'dialecto'
  *                                   -> Dialecto
  * 'sudamericano'                    -> DialectoSud
  * 'castellano'                      -> DialectoCast;
VerboIrregular "cambiar dialecto" with imperativo 'dialecto';

Verb 'g//' 'repetir' 're'
  *                                   -> Again;
VerboIrregular "repetir el comando anterior" with imperativo 'g//' 'repetir' 're';

Verb 'oops' 'epa' 'eepa'
  *                                   -> Oops
  * special                           -> OopsCorrection;
VerboIrregular "corregir un error" with imperativo 'oops' 'epa' 'eepa';

#ifdef ADMITIR_COMANDO_SALIDAS;
  Verb 'salidas'
    *                                 -> Salidas;
  VerboIrregular "mostrar las salidas visibles" with imperativo 'salidas';
#endif;

#ifdef DEBUG;
  Verb meta 'acentos'
    * 'on'                            -> ActivarAcentos
    * 'off'                           -> DesactivarAcentos;
#endif;

! ----------------------------------------------------------------------------
!  Final del fichero de gramática
! ----------------------------------------------------------------------------