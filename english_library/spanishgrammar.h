! ==============================================================================
!   GRAMÁTICA ESPAÑOLA:  Entradas de tabla de gramática para la librería de verbos estándar.
!
!   Para uso con Inform 6 -- Release 6.12.7dev -- Serial number 240409
!
!   Copyright Graham Nelson 1993-2004 y David Griffith 2012-2024
!   Adaptación española 2024
!   Este código está licenciado bajo la licencia tradicional de Inform como
!   se describe en el DM4 o la Licencia Artística versión 2.0.
!
!   En tu archivo de juego, incluye tres archivos de librería en este orden:
!       Include "Parser";
!       Include "VerbLib";
!       Include "SpanishGrammar";
! ==============================================================================

System_file;

#Ifdef      LIBRARY_STAGE;
#Iffalse    LIBRARY_STAGE >= AFTER_GRAMMAR;  ! si no está ya incluido
#Iftrue     LIBRARY_STAGE == AFTER_VERBLIB;  ! si está bien incluirlo

! ------------------------------------------------------------------------------
!  Los "meta-verbos", comandos al juego más que en el juego, van primero:
! ------------------------------------------------------------------------------

Verb meta 'breve'
    *                                           -> LMode1;

Verb meta 'detallado' 'largo' 'verboso'
    *                                           -> LMode2;

Verb meta 'superbreve' 'corto'
    *                                           -> LMode3;

Verb meta 'normal'
    *                                           -> LModeNormal;

Verb meta 'notificar'
    *                                           -> NotifyOn
    * 'activar'                                 -> NotifyOn
    * 'desactivar'                              -> NotifyOff;

Verb meta 'pronombres' 'nombres'
    *                                           -> Pronouns;

Verb meta 'salir' 'q//' 'morir' 'terminar'
    *                                           -> Quit;

Verb meta 'grabar' 'grabaci@{F3}n'
    *                                           -> CommandsOn
    * 'activar'                                 -> CommandsOn
    * 'desactivar'                              -> CommandsOff;

Verb meta 'reproducir' 'replay'
    *                                           -> CommandsRead;

Verb meta 'reiniciar'
    *                                           -> Restart;

Verb meta 'cargar' 'restaurar'
    *                                           -> Restore;

Verb meta 'guardar'
    *                                           -> Save;

Verb meta 'puntuaci@{F3}n' 'puntos'
    *                                           -> Score;

Verb meta 'puntuaci@{F3}n' 'completa'
    *                                           -> FullScore
    * 'puntos'                                  -> FullScore;

Verb meta 'transcribir' 'transcripci@{F3}n'
    *                                           -> ScriptOn
    * 'activar'                                 -> ScriptOn
    * 'desactivar'                              -> ScriptOff;

Verb meta 'verificar'
    *                                           -> Verify;

Verb meta 'versi@{F3}n'
    *                                           -> Version;

#Ifndef NO_PLACES;
Verb meta 'objetos'
    *                                           -> Objects
    * 'alto'                                    -> ObjectsTall
    * 'ancho'                                   -> ObjectsWide;
Verb meta 'lugares'
    *                                           -> Places
    * 'alto'                                    -> PlacesTall
    * 'ancho'                                   -> PlacesWide;
#Endif; ! NO_PLACES

! ------------------------------------------------------------------------------
!  Gramática de depuración
! ------------------------------------------------------------------------------

#Ifdef DEBUG;
Verb meta 'acciones'
    *                                           -> ActionsOn
    * 'activar'                                 -> ActionsOn
    * 'desactivar'                              -> ActionsOff;

Verb meta 'cambios'
    *                                           -> ChangesOn
    * 'activar'                                 -> ChangesOn
    * 'desactivar'                              -> ChangesOff;

Verb meta 'iralugar'
    * anynumber                                 -> GoNear
    * noun                                      -> GoNear;

Verb meta 'ir'
    * anynumber                                 -> Goto;

Verb meta 'aleatorio'
    *                                           -> Predictable;

Verb meta 'rutinas' 'mensajes'
    *                                           -> RoutinesOn
    * 'activar'                                 -> RoutinesOn
    * 'detallado'                               -> RoutinesVerbose
    * 'desactivar'                              -> RoutinesOff;

Verb meta 'alcance'
    *                                           -> Scope
    * anynumber                                 -> Scope
    * noun                                      -> Scope;

Verb meta 'diccionario' 'dict'
    *                                           -> ShowDict
    * topic                                     -> ShowDict;

Verb meta 'objeto'
    *                                           -> ShowObj
    * anynumber                                 -> ShowObj
    * multi                                     -> ShowObj;

Verb meta 'verbo'
    * special                                   -> ShowVerb;

Verb meta 'temporizadores' 'demonios'
    *                                           -> TimersOn
    * 'activar'                                 -> TimersOn
    * 'desactivar'                              -> TimersOff;

Verb meta 'traza'
    *                                           -> TraceOn
    * number                                    -> TraceLevel
    * 'activar'                                 -> TraceOn
    * 'desactivar'                              -> TraceOff;

Verb meta 'abstracto'
    * anynumber 'a' anynumber                   -> XAbstract
    * noun 'a' noun                             -> XAbstract;

Verb meta 'robar'
    * anynumber                                 -> XPurloin
    * multi                                     -> XPurloin;

Verb meta 'arbol' '@{E1}rbol'
    *                                           -> XTree
    * anynumber                                 -> XTree
    * noun                                      -> XTree;

#Ifdef TARGET_GLULX;
Verb meta 'glklist'
    *                                           -> Glklist;
#Endif; ! TARGET_

#Endif; ! DEBUG

! ------------------------------------------------------------------------------
!  Y ahora los verbos del juego - ESPAÑOL COMPLETO
! ------------------------------------------------------------------------------

[ ADirection; if (noun in Compass) rtrue; rfalse; ];

! ==============================================================================
! VERBOS DE COMUNICACIÓN
! ==============================================================================

Verb 'responder' 'contestar' 'decir' 'gritar' 'hablar'
    * topic 'a' creature                        -> Answer;

Verb 'preguntar'
    * creature 'sobre' topic                    -> Ask
    * creature 'por' noun                       -> AskFor
    * creature 'que' topic                      -> AskTo
    * 'a' creature 'sobre' topic               -> Ask
    * 'a' creature 'por' noun                  -> AskFor
    * 'a' creature 'que' topic                 -> AskTo;

! ==============================================================================
! VERBOS DE VIOLENCIA Y DESTRUCCIÓN
! ==============================================================================

Verb 'atacar' 'golpear' 'pegar' 'romper' 'destruir'
     'luchar' 'matar' 'asesinar' 'dar' 'partir'
     'estrellar' 'torturar' 'destrozar' 'quebrar'
    * noun                                      -> Attack
    * 'a' noun                                  -> Attack
    * 'al' noun                                 -> Attack
    * noun 'con' noun                           -> Attack
    * 'a' noun 'con' noun                       -> Attack
    * 'al' noun 'con' noun                      -> Attack
    * 'a' noun 'con' 'el' noun                  -> Attack
    * 'a' noun 'con' 'la' noun                  -> Attack
    * 'al' noun 'con' 'el' noun                 -> Attack
    * 'al' noun 'con' 'la' noun                 -> Attack;

! ==============================================================================
! VERBOS DE ACCIÓN FÍSICA
! ==============================================================================

Verb 'soplar'
    * noun                                      -> Blow
    * 'a' noun                                  -> Blow
    * 'sobre' noun                              -> Blow;

Verb 'quemar' 'incendiar'
    * noun                                      -> Burn
    * noun 'con' noun                           -> Burn;

Verb 'comprar' 'adquirir'
    * noun                                      -> Buy;

Verb 'trepar' 'escalar' 'subir'
    * noun                                      -> Climb
    * 'a' noun                                  -> Climb
    * 'por' noun                                -> Climb
    * 'sobre' noun                              -> Climb;

! ==============================================================================
! VERBOS DE MANIPULACIÓN DE OBJETOS - CRÍTICOS PARA ESPAÑOL
! ==============================================================================

Verb 'cerrar' 'tapar'
    * noun                                      -> Close
    * 'el' noun                                 -> Close
    * 'la' noun                                 -> Close
    * 'los' noun                                -> Close
    * 'las' noun                                -> Close;

Verb 'consultar' 'buscar' 'revisar'
    * noun 'sobre' topic                        -> Consult
    * 'en' noun 'sobre' topic                   -> Consult
    * noun 'por' topic                          -> Consult;

Verb 'cortar' 'partir'
    * noun                                      -> Cut
    * noun 'con' noun                           -> Cut;

Verb 'cavar' 'excavar'
    * noun                                      -> Dig
    * noun 'con' noun                           -> Dig
    * 'en' noun                                 -> Dig;

Verb 'quitar' 'quitarse' 'desvestir'
    * noun                                      -> Disrobe
    * 'el' noun                                 -> Disrobe
    * 'la' noun                                 -> Disrobe
    * 'los' noun                                -> Disrobe
    * 'las' noun                                -> Disrobe
    * 'me' noun                                 -> Disrobe;

Verb 'beber' 'tomar'
    * noun                                      -> Drink
    * 'el' noun                                 -> Drink
    * 'la' noun                                 -> Drink;

! VERBO CRÍTICO: SOLTAR/DEJAR
Verb 'soltar' 'dejar' 'tirar' 'arrojar'
    * noun                                      -> Drop
    * 'el' noun                                 -> Drop
    * 'la' noun                                 -> Drop
    * 'los' noun                                -> Drop
    * 'las' noun                                -> Drop
    * noun 'en' noun                            -> Insert
    * noun 'sobre' noun                         -> PutOn
    * 'el' noun 'en' noun                       -> Insert
    * 'la' noun 'en' noun                       -> Insert
    * 'el' noun 'sobre' noun                    -> PutOn
    * 'la' noun 'sobre' noun                    -> PutOn;

Verb 'comer' 'devorar' 'tragar'
    * noun                                      -> Eat
    * 'el' noun                                 -> Eat
    * 'la' noun                                 -> Eat;

Verb 'vaciar' 'limpiar'
    * noun                                      -> EmptyT
    * noun 'en' noun                            -> EmptyT;

! VERBO CRÍTICO: ENTRAR
Verb 'entrar' 'subir' 'subirse' 'meterse'
    * noun                                      -> Enter
    * 'en' noun                                 -> Enter
    * 'a' noun                                  -> Enter
    * 'al' noun                                 -> Enter
    * 'sobre' noun                              -> Enter
    * 'dentro' 'de' noun                        -> Enter
    * 'encima' 'de' noun                        -> Enter;

! VERBO FUNDAMENTAL: EXAMINAR/MIRAR
Verb 'examinar' 'x//' 'mirar' 'm//' 'l//' 'ver' 'observar' 'inspeccionar'
    * noun                                      -> Examine
    * 'el' noun                                 -> Examine
    * 'la' noun                                 -> Examine
    * 'los' noun                                -> Examine
    * 'las' noun                                -> Examine
    * 'a' noun                                  -> Examine
    * 'al' noun                                 -> Examine
    * 'hacia' noun                              -> Examine
    * 'dentro' 'de' noun                        -> Search
    * 'en' noun                                 -> Search
    * 'bajo' noun                               -> LookUnder
    * 'debajo' 'de' noun                        -> LookUnder
    * 'encima' 'de' noun                        -> Search;

! Simple MIRAR para locaciones
Verb 'mirar' 'm//' 'l//'
    *                                           -> Look;

Verb 'salir' 'bajar' 'bajarse' 'irse'
    *                                           -> Exit
    * 'de' noun                                 -> Exit
    * 'del' noun                                -> Exit;

Verb 'llenar' 'rellenar'
    * noun                                      -> Fill
    * noun 'con' noun                           -> Fill
    * noun 'de' noun                            -> Fill;

Verb 'bajar' 'bajarse'
    * 'de' noun                                 -> GetOff
    * 'del' noun                                -> GetOff;

! VERBO CRÍTICO: DAR/ENTREGAR
Verb 'dar' 'entregar' 'ofrecer' 'pasar'
    * noun 'a' creature                         -> Give
    * 'el' noun 'a' creature                    -> Give
    * 'la' noun 'a' creature                    -> Give
    * noun 'al' creature                        -> Give
    * 'el' noun 'al' creature                   -> Give
    * 'la' noun 'al' creature                   -> Give;

! VERBOS DE MOVIMIENTO - FUNDAMENTALES
Verb 'ir' 'caminar' 'andar' 'marchar' 'dirigirse'
    * noun                                      -> Go
    * 'a' noun                                  -> Go
    * 'al' noun                                 -> Go
    * 'hacia' noun                              -> Go
    * 'por' noun                                -> Go
    * 'norte'                                   -> Go
    * 'sur'                                     -> Go
    * 'este'                                    -> Go
    * 'oeste'                                   -> Go
    * 'noreste'                                 -> Go
    * 'noroeste'                                -> Go
    * 'sureste'                                 -> Go
    * 'suroeste'                                -> Go
    * 'arriba'                                  -> Go
    * 'abajo'                                   -> Go
    * 'adentro'                                 -> Go
    * 'afuera'                                  -> Go
    * 'n//'                                     -> Go
    * 's//'                                     -> Go
    * 'e//'                                     -> Go
    * 'o//'                                     -> Go;

! Direcciones como verbos independientes
Verb 'norte' 'n//'
    *                                           -> Go;
Verb 'sur' 's//'
    *                                           -> Go;
Verb 'este' 'e//'
    *                                           -> Go;
Verb 'oeste' 'o//'
    *                                           -> Go;
Verb 'noreste' 'ne//'
    *                                           -> Go;
Verb 'noroeste' 'no//'
    *                                           -> Go;
Verb 'sureste' 'se//'
    *                                           -> Go;
Verb 'suroeste' 'so//'
    *                                           -> Go;
Verb 'arriba' 'subir'
    *                                           -> Go;
Verb 'abajo' 'bajar'
    *                                           -> Go;
Verb 'adentro' 'entrar'
    *                                           -> Go;
Verb 'afuera' 'salir'
    *                                           -> Go;

! VERBO CRÍTICO: METER/INSERTAR
Verb 'meter' 'insertar' 'poner' 'colocar' 'introducir'
    * noun 'en' noun                            -> Insert
    * 'el' noun 'en' noun                       -> Insert
    * 'la' noun 'en' noun                       -> Insert
    * noun 'dentro' 'de' noun                   -> Insert
    * 'el' noun 'dentro' 'de' noun              -> Insert
    * 'la' noun 'dentro' 'de' noun              -> Insert;

! VERBO FUNDAMENTAL: INVENTARIO
Verb 'inventario' 'i//' 'inv'
    *                                           -> Inv;

Verb 'saltar' 'brincar'
    *                                           -> Jump
    * 'sobre' noun                              -> JumpOver
    * 'por' 'encima' 'de' noun                  -> JumpOver
    * 'en' noun                                 -> JumpIn
    * 'dentro' 'de' noun                        -> JumpIn;

Verb 'besar' 'abrazar'
    * noun                                      -> Kiss
    * 'a' noun                                  -> Kiss
    * 'al' noun                                 -> Kiss;

Verb 'escuchar' 'o@{ED}r'
    *                                           -> Listen
    * noun                                      -> Listen
    * 'a' noun                                  -> Listen;

Verb 'bloquear' 'cerrar' 'trabar'
    * noun                                      -> Lock
    * noun 'con' noun                           -> Lock;

Verb 'mirar' 'buscar'
    * 'bajo' noun                               -> LookUnder
    * 'debajo' 'de' noun                        -> LookUnder;

Verb 'abrir' 'destapar'
    * noun                                      -> Open
    * 'el' noun                                 -> Open
    * 'la' noun                                 -> Open
    * noun 'con' noun                           -> Open;

Verb 'ordenar' 'mandar' 'decir'
    * creature 'que' topic                      -> Order
    * 'a' creature 'que' topic                  -> Order
    * 'al' creature 'que' topic                 -> Order;

Verb 'rezar' 'orar'
    *                                           -> Pray;

! VERBOS DE MANIPULACIÓN FÍSICA
Verb 'tirar' 'jalar' 'arrastrar'
    * noun                                      -> Pull
    * 'de' noun                                 -> Pull
    * 'del' noun                                -> Pull;

Verb 'empujar' 'presionar'
    * noun                                      -> Push
    * noun noun                                 -> PushDir
    * noun 'hacia' noun                         -> PushDir
    * noun 'a' noun                             -> PushDir
    * noun 'al' noun                            -> PushDir;

! VERBO CRÍTICO: PONER SOBRE
Verb 'poner'
    * noun 'sobre' noun                         -> PutOn
    * noun 'encima' 'de' noun                   -> PutOn
    * 'el' noun 'sobre' noun                    -> PutOn
    * 'la' noun 'sobre' noun                    -> PutOn
    * 'el' noun 'encima' 'de' noun              -> PutOn
    * 'la' noun 'encima' 'de' noun              -> PutOn;

Verb 'quitar' 'sacar'
    * noun 'de' noun                            -> Remove
    * noun 'del' noun                           -> Remove
    * 'el' noun 'de' noun                       -> Remove
    * 'la' noun 'de' noun                       -> Remove
    * 'el' noun 'del' noun                      -> Remove
    * 'la' noun 'del' noun                      -> Remove;

Verb 'frotar' 'restregar' 'limpiar'
    * noun                                      -> Rub
    * noun 'con' noun                           -> Rub;

Verb 'buscar' 'registrar' 'explorar'
    * noun                                      -> Search
    * 'en' noun                                 -> Search
    * 'dentro' 'de' noun                        -> Search;

Verb 'configurar' 'ajustar' 'establecer'
    * noun                                      -> Set
    * noun 'a' noun                             -> SetTo
    * noun 'en' noun                            -> SetTo;

Verb 'mostrar' 'enseñar'
    * noun 'a' creature                         -> Show
    * 'el' noun 'a' creature                    -> Show
    * 'la' noun 'a' creature                    -> Show
    * noun 'al' creature                        -> Show
    * 'el' noun 'al' creature                   -> Show
    * 'la' noun 'al' creature                   -> Show;

Verb 'cantar'
    *                                           -> Sing;

Verb 'dormir' 'descansar'
    *                                           -> Sleep;

Verb 'oler' 'olfatear'
    * noun                                      -> Smell
    * 'a' noun                                  -> Smell;

Verb 'disculparse' 'perd@{F3}n' 'perdona' 'lo' 'siento'
    *                                           -> Sorry;

Verb 'apretar' 'estrujar' 'oprimir'
    * noun                                      -> Squeeze;

Verb 'fuerte' 'maldici@{F3}n'
    *                                           -> Strong;

Verb 'nadar'
    *                                           -> Swim;

Verb 'balancear' 'mecer'
    * noun                                      -> Swing;

Verb 'apagar' 'desactivar'
    * noun                                      -> SwitchOff
    * 'el' noun                                 -> SwitchOff
    * 'la' noun                                 -> SwitchOff;

Verb 'encender' 'activar' 'prender'
    * noun                                      -> SwitchOn
    * 'el' noun                                 -> SwitchOn
    * 'la' noun                                 -> SwitchOn;

! VERBO FUNDAMENTAL: TOMAR/COGER - MUY IMPORTANTE EN ESPAÑOL
Verb 'tomar' 'coger' 'agarrar' 'llevar' 'pillar' 'recoger'
    * noun                                      -> Take
    * 'el' noun                                 -> Take
    * 'la' noun                                 -> Take
    * 'los' noun                                -> Take
    * 'las' noun                                -> Take
    * multi                                     -> Take;

Verb 'probar' 'degustar' 'saborear'
    * noun                                      -> Taste;

Verb 'contar' 'hablar' 'decir'
    * creature 'sobre' topic                    -> Tell
    * 'a' creature 'sobre' topic               -> Tell
    * 'al' creature 'sobre' topic              -> Tell;

Verb 'pensar'
    *                                           -> Think;

! VERBO CRÍTICO: LANZAR/TIRAR
Verb 'lanzar' 'tirar' 'arrojar'
    * noun 'a' noun                             -> ThrowAt
    * noun 'al' noun                            -> ThrowAt
    * noun 'hacia' noun                         -> ThrowAt
    * noun 'contra' noun                        -> ThrowAt
    * 'el' noun 'a' noun                        -> ThrowAt
    * 'la' noun 'a' noun                        -> ThrowAt
    * 'el' noun 'al' noun                       -> ThrowAt
    * 'la' noun 'al' noun                       -> ThrowAt
    * 'la' noun 'debajo' 'de' noun              -> ThrowAt
    * 'el' noun 'debajo' 'de' noun              -> ThrowAt;

Verb 'atar' 'amarrar'
    * noun                                      -> Tie
    * noun 'a' noun                             -> Tie
    * noun 'al' noun                            -> Tie;

Verb 'tocar' 'palpar' 'sentir'
    * noun                                      -> Touch;

Verb 'girar' 'rotar' 'dar' 'vuelta'
    * noun                                      -> Turn;

Verb 'desbloquear' 'abrir'
    * noun                                      -> Unlock
    * noun 'con' noun                           -> Unlock;

Verb 'esperar' 'z//'
    *                                           -> Wait;

Verb 'despertar' 'levantarse'
    *                                           -> Wake
    * noun                                      -> WakeOther
    * 'a' noun                                  -> WakeOther
    * 'al' noun                                 -> WakeOther;

Verb 'agitar' 'sacudir'
    * noun                                      -> Wave
    * noun 'a' noun                             -> Wave
    * noun 'hacia' noun                         -> Wave;

Verb 'usar' 'llevar' 'ponerse'
    * noun                                      -> Wear
    * 'el' noun                                 -> Wear
    * 'la' noun                                 -> Wear
    * 'los' noun                                -> Wear
    * 'las' noun                                -> Wear
    * 'me' noun                                 -> Wear;

! RESPUESTAS SIMPLES
Verb 'si' 's@{ED}' 's//'
    *                                           -> Yes;

Verb 'no' 'n//'
    *                                           -> No;

! ==============================================================================
! PATRONES COMPLEJOS ESPECÍFICOS DEL ESPAÑOL
! ==============================================================================

! Manejar frases como "ataca al soldado dormido con la espada brillante"
Verb 'atacar'
    * noun adjective 'con' noun adjective       -> Attack
    * 'al' noun adjective 'con' noun adjective  -> Attack
    * 'al' noun adjective 'con' 'la' noun adjective -> Attack
    * 'al' noun adjective 'con' 'el' noun adjective -> Attack;

! Manejar "lanza la piedra debajo de la mesa"
Verb 'lanzar'
    * noun 'debajo' 'de' noun                   -> ThrowAt
    * 'la' noun 'debajo' 'de' 'la' noun         -> ThrowAt
    * 'el' noun 'debajo' 'de' 'la' noun         -> ThrowAt
    * 'la' noun 'debajo' 'de' 'el' noun         -> ThrowAt;

! Manejar "coge la cantara y bébetela" - esto requiere procesamiento especial
Verb 'coger'
    * noun 'y' special                          -> Take;  ! special maneja casos complejos

! Preposiciones compuestas comunes en español
Verb 'mirar'
    * 'debajo' 'de' noun                        -> LookUnder
    * 'encima' 'de' noun                        -> Search
    * 'dentro' 'de' noun                        -> Search
    * 'detr@{E1}s' 'de' noun                    -> LookUnder
    * 'delante' 'de' noun                       -> Examine
    * 'al' 'lado' 'de' noun                     -> Examine
    * 'a' 'trav@{E9}s' 'de' noun                -> Examine;

Verb 'ir'
    * 'debajo' 'de' noun                        -> Go
    * 'encima' 'de' noun                        -> Go
    * 'dentro' 'de' noun                        -> Go
    * 'detr@{E1}s' 'de' noun                    -> Go
    * 'delante' 'de' noun                       -> Go
    * 'al' 'lado' 'de' noun                     -> Go
    * 'a' 'trav@{E9}s' 'de' noun                -> Go;

! Patrones con pronombres clíticos (simplificados)
Verb 'darse'
    * noun                                      -> Give;

Verb 'levantarse'
    *                                           -> Wake;

Verb 'irse'
    *                                           -> Exit
    * 'de' noun                                 -> Exit;

! ==============================================================================
! SOPORTE PARA FRASES IMPERATIVAS COMPLEJAS
! ==============================================================================

! "bébetela" se puede manejar con rutinas especiales de parsing
Verb 'beber'
    * noun                                      -> Drink
    * 'te' noun                                 -> Drink
    * 'se' noun                                 -> Drink;

! Otros imperativos reflexivos comunes
Verb 'quitarse'
    * noun                                      -> Disrobe;

Verb 'ponerse'
    * noun                                      -> Wear;

Verb 'llevarse'
    * noun                                      -> Take;

! ==============================================================================
! SINÓNIMOS ADICIONALES Y VARIANTES REGIONALES
! ==============================================================================

! Sinónimos para TOMAR (muy importante en español)
Verb 'pillar' 'recoger' 'alzar' 'levantar'
    * noun                                      -> Take;

! Sinónimos para MIRAR
Verb 'ojear' 'vistazo' 'echar' 'un' 'vistazo'
    * noun                                      -> Examine;

! Sinónimos para IR
Verb 'dirigirse' 'encaminarse' 'moverse'
    * 'a' noun                                  -> Go
    * 'hacia' noun                              -> Go;

! Variantes de DEJAR/SOLTAR
Verb 'abandonar' 'descartar'
    * noun                                      -> Drop;

! ==============================================================================
! GRAMMAR STAGE FINALIZACIÓN
! ==============================================================================

Constant LIBRARY_STAGE = AFTER_GRAMMAR;

#Endif; ! LIBRARY_STAGE check
#Endif; ! AFTER_GRAMMAR check

! ==============================================================================