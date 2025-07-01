! ==============================================================================
!   SPANISHGRAMMAR:  Gramática en español para la librería Inform 6
!
!   Basado en la librería Inform 6 -- Release 6.12.7 -- Serial number 240410
!
!   Copyright Graham Nelson 1993-2004 and David Griffith 2012-2024
!   Adaptación al español por Francisco Fuentes, 2025
!
!   This code is licensed under either the traditional Inform license as
!   described by the DM4 or the Artistic License version 2.0.
!
! ==============================================================================

System_file;

! ------------------------------------------------------------------------------
!   Parte I.   Verbos
! ------------------------------------------------------------------------------

Verb 'coge' 'toma' 'recoge'
    * noun                                          -> Take
    * 'a//' noun                                    -> Take
    * multi                                         -> Take
    * 'a//' multi                                   -> Take
    * 'todo' 'todos' 'todas'                        -> TakeAll
    * multiinside 'de' noun                         -> Remove
    * multiinside 'desde' noun                      -> Remove
    * 'a//' multiinside 'de' noun                   -> Remove
    * 'a//' multiinside 'desde' noun                -> Remove;

Verb 'quita' 'saca'
    * noun                                          -> Take
    * 'a//' noun                                    -> Take
    * multi                                         -> Take
    * 'a//' multi                                   -> Take
    * multiinside 'de' noun                         -> Remove
    * multiinside 'desde' noun                      -> Remove
    * 'a//' multiinside 'de' noun                   -> Remove
    * 'a//' multiinside 'desde' noun                -> Remove;

Verb 'deja' 'suelta' 'tira'
    * noun                                          -> Drop
    * 'a//' noun                                    -> Drop
    * multi                                         -> Drop
    * 'a//' multi                                   -> Drop
    * 'todo' 'todos' 'todas'                        -> DropAll
    * noun 'en' noun                                -> Insert
    * 'a//' noun 'en' noun                          -> Insert
    * noun 'dentro' 'de' noun                       -> Insert
    * 'a//' noun 'dentro' 'de' noun                 -> Insert
    * noun 'sobre' noun                             -> PutOn
    * 'a//' noun 'sobre' noun                       -> PutOn;

Verb 'pon' 'coloca'
    * noun                                          -> Drop
    * 'a//' noun                                    -> Drop
    * multi                                         -> Drop
    * 'a//' multi                                   -> Drop
    * noun 'en' noun                                -> Insert
    * 'a//' noun 'en' noun                          -> Insert
    * noun 'dentro' 'de' noun                       -> Insert
    * 'a//' noun 'dentro' 'de' noun                 -> Insert
    * noun 'sobre' noun                             -> PutOn
    * 'a//' noun 'sobre' noun                       -> PutOn;

Verb 'inserta'
    * noun 'en' noun                                -> Insert
    * 'a//' noun 'en' noun                          -> Insert
    * noun 'dentro' 'de' noun                       -> Insert
    * 'a//' noun 'dentro' 'de' noun                 -> Insert;

Verb 'inventario' 'i//'
    *                                               -> Inv
    * 'amplio' 'largo' 'completo'                   -> InvTall
    * 'corto' 'breve'                               -> InvWide;

Verb 'mira' 'l//' 'm//'
    *                                               -> Look
    * 'a//' noun                                    -> Examine
    * noun                                          -> Examine
    * 'en' noun                                     -> Search
    * 'dentro' 'de' noun                            -> Search
    * 'bajo' noun                                   -> LookUnder
    * 'debajo' 'de' noun                            -> LookUnder
    * 'a//' 'traves' 'de' noun                      -> Search
    * 'por' noun                                    -> Search;

Verb 'examina' 'x//' 'ex//' 'inspecciona' 'observa'
    * noun                                          -> Examine
    * 'a//' noun                                    -> Examine;

Verb 'lee'
    * noun                                          -> Examine
    * 'a//' noun                                    -> Examine;

Verb 'busca' 'registra'
    * 'en' noun                                     -> Search
    * 'dentro' 'de' noun                            -> Search
    * noun                                          -> Search;

Verb 'abre'
    * noun                                          -> Open
    * 'a//' noun                                    -> Open
    * noun 'con' held                               -> Unlock;

Verb 'cierra'
    * noun                                          -> Close
    * 'a//' noun                                    -> Close
    * noun 'con' held                               -> Lock;

Verb 'destapa' 'descubre'
    * noun                                          -> Open
    * 'a//' noun                                    -> Open;

Verb 'tapa' 'cubre'
    * noun                                          -> Close
    * 'a//' noun                                    -> Close;

Verb 'entra' 'metete'
    *                                               -> GoIn
    * 'en' noun                                     -> Enter
    * 'dentro' 'de' noun                            -> Enter
    * 'a//' noun                                    -> Enter;

Verb 'siéntate' 'sientate'
    * 'en' noun                                     -> Enter
    * 'sobre' noun                                  -> Enter;

Verb 'sal' 'fuera' 'afuera' 'salte'
    *                                               -> Exit
    * 'de' noun                                     -> GetOff
    * 'desde' noun                                  -> GetOff;

Verb 'bájate' 'bajate'
    * 'de' noun                                     -> GetOff
    * 'desde' noun                                  -> GetOff;

Verb 'vacia'
    * noun                                          -> Empty
    * 'a//' noun                                    -> Empty
    * noun 'en' noun                                -> EmptyT
    * 'a//' noun 'en' noun                          -> EmptyT
    * noun 'dentro' 'de' noun                       -> EmptyT
    * 'a//' noun 'dentro' 'de' noun                 -> EmptyT;

Verb 'transfiere'
    * noun 'a//' noun                               -> Transfer
    * 'a//' noun 'a//' noun                         -> Transfer;

Verb 'da' 'ofrece' 'alimenta'
    * noun 'a//' creature                           -> Give
    * 'a//' noun 'a//' creature                     -> Give
    * creature noun                                 -> Give reverse
    * 'a//' creature noun                           -> Give reverse
    * 'a//' creature 'a//' noun                     -> Give reverse;

Verb 'muestra' 'ensena' 'enseña'
    * noun 'a//' creature                           -> Show
    * 'a//' noun 'a//' creature                     -> Show
    * creature noun                                 -> Show reverse
    * 'a//' creature noun                           -> Show reverse
    * 'a//' creature 'a//' noun                     -> Show reverse;

Verb 've' 'camina' 'anda' 'corre' 'ir'
    *                                               -> VagueGo
    * noun                                          -> Go
    * 'a//' noun                                    -> Go
    * 'hacia' noun                                  -> Go
    * 'al' noun                                     -> Go
    * 'a//' 'el' noun                               -> Go
    * 'a//' 'la' noun                               -> Go
    * 'a//' 'los' noun                              -> Go
    * 'a//' 'las' noun                              -> Go
    * 'en' noun                                     -> Enter
    * 'dentro' 'de' noun                            -> Enter;

Verb 'empuja' 'mueve' 'desplaza'
    * noun                                          -> Push
    * 'a//' noun                                    -> Push
    * noun noun                                     -> PushDir
    * 'a//' noun noun                               -> PushDir
    * noun 'hacia' noun                             -> PushDir
    * 'a//' noun 'hacia' noun                       -> PushDir;

Verb 'gira' 'tuerce' 'retuerce'
    * noun                                          -> Turn
    * 'a//' noun                                    -> Turn;

Verb 'pulsa' 'presiona' 'aprieta'
    * noun                                          -> Push
    * 'a//' noun                                    -> Push;

Verb 'tira'
    * 'de' noun                                     -> Pull
    * noun                                          -> Pull
    * 'a//' noun                                    -> Pull;

Verb 'arrastra'
    * noun                                          -> Pull
    * 'a//' noun                                    -> Pull;

Verb 'gira'
    * noun                                          -> Turn
    * 'a//' noun                                    -> Turn;

Verb 'conecta' 'enchufa' 'enciende'
    * noun                                          -> SwitchOn
    * 'a//' noun                                    -> SwitchOn;

Verb 'desconecta' 'apaga'
    * noun                                          -> SwitchOff
    * 'a//' noun                                    -> SwitchOff;

Verb 'come' 'devora'
    * noun                                          -> Eat
    * 'a//' noun                                    -> Eat;

Verb 'bebe'
    * noun                                          -> Drink
    * 'a//' noun                                    -> Drink;

Verb 'huele' 'olfatea'
    *                                               -> Smell
    * noun                                          -> Smell
    * 'a//' noun                                    -> Smell;

Verb 'escucha'
    *                                               -> Listen
    * noun                                          -> Listen
    * 'a//' noun                                    -> Listen;

Verb 'prueba' 'saborea' 'paladea'
    * noun                                          -> Taste
    * 'a//' noun                                    -> Taste;

Verb 'toca' 'palpa'
    * noun                                          -> Touch
    * 'a//' noun                                    -> Touch;

Verb 'frota' 'limpia' 'pule' 'abrillanta'
    * noun                                          -> Rub
    * 'a//' noun                                    -> Rub;

Verb 'ata' 'une' 'enlaza'
    * noun                                          -> Tie
    * 'a//' noun                                    -> Tie
    * noun 'a//' noun                               -> Tie
    * 'a//' noun 'a//' noun                         -> Tie;

Verb 'quema' 'incendia' 'prende'
    * noun                                          -> Burn
    * 'a//' noun                                    -> Burn
    * noun 'con' held                               -> Burn
    * 'a//' noun 'con' held                         -> Burn;

Verb 'besa'
    * creature                                      -> Kiss
    * 'a//' creature                                -> Kiss;

Verb 'piensa'
    *                                               -> Think;

Verb 'huele'
    *                                               -> Smell
    * noun                                          -> Smell
    * 'a//' noun                                    -> Smell;

Verb 'escucha'
    *                                               -> Listen
    * noun                                          -> Listen
    * 'a//' noun                                    -> Listen;

Verb 'saborea'
    * noun                                          -> Taste
    * 'a//' noun                                    -> Taste;

Verb 'toca'
    * noun                                          -> Touch
    * 'a//' noun                                    -> Touch;

Verb 'di' 'grita' 'habla' 'canta'
    *                                               -> Say
    * topic                                         -> Say
    * topic 'a//' creature                          -> Tell
    * 'a//' creature topic                          -> Tell
    * creature topic                                -> Tell;

Verb 'pregunta'
    * creature 'sobre' 'acerca' topic               -> Ask
    * 'a//' creature 'sobre' 'acerca' topic         -> Ask
    * creature 'por' topic                          -> Ask
    * 'a//' creature 'por' topic                    -> Ask;

Verb 'responde' 'contesta'
    * creature topic                                -> Answer
    * 'a//' creature topic                          -> Answer
    * topic 'a//' creature                          -> Answer;

Verb 'cuenta' 'narra'
    * creature 'sobre' 'acerca' topic               -> Tell
    * 'a//' creature 'sobre' 'acerca' topic         -> Tell
    * creature topic                                -> Tell
    * 'a//' creature topic                          -> Tell;

Verb 'consulta'
    * creature 'sobre' 'acerca' topic               -> Ask
    * 'a//' creature 'sobre' 'acerca' topic         -> Ask
    * noun 'sobre' 'acerca' topic                   -> Consult
    * 'a//' noun 'sobre' 'acerca' topic             -> Consult;

Verb 'pide'
    * creature 'por' topic                          -> AskFor
    * 'a//' creature 'por' topic                    -> AskFor;

Verb 'espera' 'z//'
    *                                               -> Wait;

Verb 'duerme' 'descansa'
    *                                               -> Sleep;

Verb 'despierta' 'despiertate'
    *                                               -> Wake
    * creature                                      -> WakeOther
    * 'a//' creature                                -> WakeOther;

Verb 'besa'
    * creature                                      -> Kiss
    * 'a//' creature                                -> Kiss;

Verb 'agita' 'sacude' 'menea'
    * noun                                          -> Wave
    * 'a//' noun                                    -> Wave;

Verb 'saluda'
    *                                               -> WaveHands
    * creature                                      -> Wave
    * 'a//' creature                                -> Wave;

Verb 'lanza' 'arroja'
    * noun                                          -> Drop
    * 'a//' noun                                    -> Drop
    * held 'a//' noun                               -> ThrowAt
    * 'a//' held 'a//' noun                         -> ThrowAt
    * held 'contra' noun                            -> ThrowAt
    * 'a//' held 'contra' noun                      -> ThrowAt;

Verb 'ataca' 'mata' 'tortura' 'golpea'
    * creature                                      -> Attack
    * 'a//' creature                                -> Attack
    * creature 'con' held                           -> Attack
    * 'a//' creature 'con' held                     -> Attack;

Verb 'rompe' 'destruye' 'aplasta'
    * noun                                          -> Attack
    * 'a//' noun                                    -> Attack;

Verb 'trepa' 'escala'
    * noun                                          -> Climb
    * 'a//' noun                                    -> Climb
    * 'por' noun                                    -> Climb;

Verb 'sube'
    *                                               -> GoUp
    * noun                                          -> Climb
    * 'a//' noun                                    -> Climb
    * 'por' noun                                    -> Climb;

Verb 'baja'
    *                                               -> GoDown
    * noun                                          -> GetOff
    * 'de' noun                                     -> GetOff
    * 'desde' noun                                  -> GetOff
    * 'por' noun                                    -> Climb;

Verb 'salta'
    *                                               -> Jump
    * noun                                          -> JumpOver
    * 'a//' noun                                    -> JumpOver
    * 'sobre' noun                                  -> JumpOver
    * 'por' 'encima' 'de' noun                      -> JumpOver;

Verb 'busca'
    * topic 'en' noun                               -> Consult
    * topic 'dentro' 'de' noun                      -> Consult;

Verb 'nada'
    *                                               -> Swim;

Verb 'balanceate' 'balancéate'
    *                                               -> Swing
    * 'en' noun                                     -> Swing
    * 'sobre' noun                                  -> Swing;

Verb 'sopla'
    * noun                                          -> Blow
    * 'en' noun                                     -> Blow;

Verb 'reza' 'ora'
    *                                               -> Pray;

Verb 'despierta'
    *                                               -> Wake
    * creature                                      -> WakeOther
    * 'a//' creature                                -> WakeOther;

Verb 'besa'
    * creature                                      -> Kiss
    * 'a//' creature                                -> Kiss;

Verb 'piensa'
    *                                               -> Think;

Verb 'huele'
    *                                               -> Smell;

Verb 'escucha'
    *                                               -> Listen;

Verb 'saborea'
    * noun                                          -> Taste
    * 'a//' noun                                    -> Taste;

Verb 'toca'
    * noun                                          -> Touch
    * 'a//' noun                                    -> Touch;

Verb 'di' 'grita' 'habla' 'canta'
    *                                               -> Shout
    * topic                                         -> Say;

Verb 'puntua' 'puntuacion' 'puntuación'
    *                                               -> Score
    * 'total'                                       -> FullScore
    * 'completa'                                    -> FullScore;

Verb 'q//' 'termina' 'fin' 'acabar'
    *                                               -> Quit;

Verb 'guarda' 'salva'
    *                                               -> Save;

Verb 'recupera' 'carga' 'restaura'
    *                                               -> Restore;

Verb 'reinicia' 'reiniciar'
    *                                               -> Restart;

Verb 'verifica' 'verificar'
    *                                               -> Verify;

Verb 'version' 'versión'
    *                                               -> Version;

Verb 'script' 'transcripcion' 'transcripción'
    *                                               -> ScriptOn
    * 'on'                                          -> ScriptOn
    * 'off'                                         -> ScriptOff;

Verb 'superbreve' 'sb' 'corto'
    *                                               -> LMode3;

Verb 'breve' 'normal'
    *                                               -> LMode1;

Verb 'largo' 'verbose' 'verboso' 'detallado'
    *                                               -> LMode2;

Verb 'pronombres' 'p//'
    *                                               -> Pronouns;

Verb 'notify' 'notificar'
    * 'on'                                          -> NotifyOn
    * 'off'                                         -> NotifyOff;

Verb 'ayuda' 'info' 'informacion' 'información' 'about' 'acerca'
    *                                               -> Help;

Verb 'objetos'
    *                                               -> Objects;

Verb 'lugares'
    *                                               -> Places;

! ------------------------------------------------------------------------------
!   Parte II.   Extensiones y correcciones
! ------------------------------------------------------------------------------

! Verbos de dirección
Verb 'n//' 'norte'
    *                                               -> Go
    * noun                                          -> Go;

Verb 's//' 'sur'
    *                                               -> Go
    * noun                                          -> Go;

Verb 'e//' 'este'
    *                                               -> Go
    * noun                                          -> Go;

Verb 'o//' 'oeste'
    *                                               -> Go
    * noun                                          -> Go;

Verb 'ne' 'noreste'
    *                                               -> Go
    * noun                                          -> Go;

Verb 'no' 'noroeste'
    *                                               -> Go
    * noun                                          -> Go;

Verb 'se' 'sureste'
    *                                               -> Go
    * noun                                          -> Go;

Verb 'so' 'suroeste'
    *                                               -> Go
    * noun                                          -> Go;

Verb 'arriba' 'ar' 'sube'
    *                                               -> Go
    * noun                                          -> Go;

Verb 'abajo' 'ab' 'baja'
    *                                               -> Go
    * noun                                          -> Go;

Verb 'dentro' 'adentro'
    *                                               -> Go
    * noun                                          -> Go;

Verb 'fuera' 'afuera'
    *                                               -> Go
    * noun                                          -> Go;

! ==============================================================================