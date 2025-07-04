! ######################### Gramática Española + Acciones
! Traducción y adaptación al español de PunyInform
! Soporte para verbos regulares e irregulares españoles

! ---------------------
! Verbos base españoles
! ---------------------

! NOTA: Se mantiene la estructura original de PunyInform
! pero adaptada para la gramática española

Verb 'responder' 'contestar' 'decir' 'hablar'
	* topic 'a' creature                        -> Answer;

Verb 'preguntar'
	* creature 'sobre' topic                    -> Ask
	* 'a' creature 'sobre' topic                -> Ask
	* creature 'por' noun                       -> AskFor
	* 'a' creature 'por' noun                   -> AskFor
	* 'a' creature topic                        -> AskTo
	* 'que' creature topic                      -> AskTo;

Verb 'atacar' 'romper' 'golpear' 'pegar' 'partir'
		'luchar' 'pelear' 'matar' 'asesinar' 'destruir'
		'destrozar' 'quebrar' 'machacar'
	* noun                                      -> Attack
	* noun 'con' held                           -> Attack;

Verb 'escalar' 'trepar' 'subir'
	* noun                                      -> Climb
	* 'por' noun                                -> Climb
	* 'a' noun                                  -> Enter
	* 'en' noun                                 -> Enter
	* 'sobre' noun                              -> Enter
	* 'de' noun                                 -> Exit
	* 'desde' noun                              -> Exit;

Verb 'cerrar' 'tapar'
	* noun                                      -> Close
	* noun 'con' held                           -> Close;

Verb 'cortar' 'partir' 'trocear'
	* noun                                      -> Cut
	* noun 'con' held                           -> Attack;

Verb 'cavar' 'excavar'
	* noun                                      -> Dig
	* noun 'con' held                           -> Dig;

Verb 'beber' 'tomar'
	* noun                                      -> Drink;

Verb 'soltar' 'tirar' 'arrojar' 'lanzar'
	* multiheld                                 -> Drop
	* multiexcept 'en' noun                     -> Insert
	* multiexcept 'dentro' 'de' noun            -> Insert
	* multiexcept 'sobre' noun                  -> PutOn
	* held 'a' noun                             -> ThrowAt
	* held 'contra' noun                        -> ThrowAt;

Verb 'comer' 'comerse'
	* held                                      -> Eat;

#IfDef OPTIONAL_EXTENDED_VERBSET;
Verb 'entrar' 'meterse'
	*                                           -> GoIn
	* 'en' noun                                 -> Enter
	* noun                                      -> Enter;
#IfNot;
Verb 'entrar' 'meterse'
	* 'en' noun                                 -> Enter
	* noun                                      -> Enter;
#Endif;

Verb 'examinar' 'mirar' 'observar' 'ver' 'x//' 'm//'
	* noun                                      -> Examine
	* 'a' noun                                  -> Examine;

Verb 'salir' 'marcharse' 'irse'
	*                                           -> Exit
	* 'de' noun                                 -> Exit
	* noun                                      -> Exit;

Verb 'llenar' 'rellenar'
	* noun                                      -> Fill;

Verb 'coger' 'agarrar' 'tomar'
	* 'de' noun                                 -> Exit
	* multi                                     -> Take
	* 'en' noun                                 -> Enter
	* 'sobre' noun                              -> Enter
	* multiinside 'de' noun                     -> Remove;

Verb 'dar' 'entregar' 'ofrecer' 'pagar'
	* held 'a' creature                         -> Give
	* creature held                             -> Give reverse
	* held creature                             -> Give reverse;

[ ADireccion;
	if (noun == Directions) rtrue;
	rfalse;
];

Verb 'ir' 'dirigirse' 'caminar' 'andar'
	* noun=ADireccion                           -> Go
	* 'al' noun=ADireccion                      -> Go
	* 'hacia' noun=ADireccion                   -> Go
	* noun                                      -> Enter;

Verb 'meter' 'poner' 'colocar' 'insertar'
	* multiexcept 'en' noun                     -> Insert
	* multiexcept 'dentro' 'de' noun            -> Insert;

#Ifdef OPTIONAL_FLEXIBLE_INVENTORY;
Verb 'inventario' 'inv' 'i//'
	* -> Inv
	* 'alto'/'ancho' -> Inv;
#Ifnot;
Verb 'inventario' 'inv' 'i//'
	* -> Inv;
#Endif;

Verb 'saltar'
	*                                           -> Jump
	* 'sobre' noun                              -> JumpOver
	* 'en' noun                                 -> Enter
	* 'dentro' 'de' noun                        -> Enter
	* 'de' noun                                 -> Exit
	* 'desde' noun                              -> Exit;

Verb 'escuchar' 'oir'
	*                                           -> Listen
	* 'a' noun                                  -> Listen
	* noun                                      -> Listen;

Verb 'cerrar' 'bloquear'
	* noun 'con' held                           -> Lock;

Verb 'mirar' 'ver' 'observar' 'l//'
	* noun                                      -> Examine
	* 'a' noun                                  -> Examine
	*                                           -> Look
	* 'en' noun                                 -> Search
	* 'dentro' 'de' noun                        -> Search;

Verb 'abrir' 'destapar' 'desenvolver'
	* noun                                      -> Open
	* noun 'con' held                           -> Unlock;

Verb 'recoger'
	* multi                                     -> Take;

Verb 'tirar' 'jalar' 'arrastrar'
	* noun                                      -> Pull;

Verb 'empujar' 'mover' 'presionar' 'pulsar'
	* noun                                      -> Push
	* noun noun=ADireccion                      -> PushDir
	* noun 'hacia' noun=ADireccion              -> PushDir
	* noun 'a' noun                             -> Transfer;

Verb 'poner' 'colocar' 'situar'
	* multiexcept 'en' noun                     -> Insert
	* multiexcept 'dentro' 'de' noun            -> Insert
	* multiexcept 'sobre' noun                  -> PutOn
	* multiexcept 'encima' 'de' noun            -> PutOn
	* held                                      -> Wear;

Verb 'leer'
	* noun                                      -> Examine
	* 'sobre' topic 'en' noun                   -> Consult reverse
	* topic 'en' noun                           -> Consult reverse;

Verb 'quitar' 'sacar' 'extraer'
	* worn                                      -> Disrobe
	* multi                                     -> Take
	* multiinside 'de' noun                     -> Remove;

Verb 'frotar' 'limpiar' 'pulir' 'fregar'
	* noun                                      -> Rub;

Verb 'buscar' 'registrar'
	* noun                                      -> Search
	* 'en' noun                                 -> Search;

Verb 'quitarse' 'desnudarse'
	* held                                      -> Disrobe;

Verb 'gritar' 'chillar' 'vociferar'
	* topic 'a' creature                        -> Answer
	* 'a' noun                                  -> ShoutAt
	* topic                                     -> Shout
	*                                           -> Shout;

Verb 'mostrar' 'enseñar' 'presentar'
	* creature held                             -> Show reverse
	* held 'a' creature                         -> Show;

Verb 'sentarse' 'acostarse'
	* 'en' noun                                 -> Enter
	* 'sobre' noun                              -> Enter;

Verb 'oler' 'olfatear'
	*                                           -> Smell
	* noun                                      -> Smell;

Verb 'levantarse' 'pararse'
	*                                           -> Exit
	* 'de' noun                                 -> Exit
	* 'sobre' noun                              -> Enter;

Verb 'encender' 'prender'
	* noun                                      -> SwitchOn;

Verb 'apagar'
	* noun                                      -> SwitchOff;

Verb 'llevar' 'portar'
	* multi                                     -> Take
	* multiinside 'de' noun                     -> Remove
	* 'inventario'                              -> Inv;

Verb 'decir' 'contar'
	* creature 'sobre' topic                    -> Tell
	* 'a' creature 'sobre' topic                -> Tell
	* 'a' creature topic                        -> AskTo;

Verb 'atar' 'amarrar' 'sujetar'
	* noun                                      -> Tie
	* noun 'a' noun                             -> Tie
	* noun 'con' noun                           -> Tie;

Verb 'tocar' 'palpar'
	* noun                                      -> Touch;

Verb 'girar' 'rotar' 'torcer'
	* noun                                      -> Turn;

Verb 'desbloquear' 'destrancar'
	* noun 'con' held                           -> Unlock;

Verb 'esperar' 'z//'
	*                                           -> Wait;

Verb 'vestir' 'ponerse' 'llevar'
	* held                                      -> Wear;

! ---------------------
! Verbos meta españoles  
! ---------------------

Verb meta 'otra' 'vez' 'repetir' 'g//'
	*                                           -> Again;

Verb meta 'breve' 'normal'
	*                                           -> LookModeNormal;

#Ifdef OPTIONAL_FULL_SCORE;
Verb meta 'puntuacion' 'completa'
	*                                           -> FullScore
	* 'completa'                                -> FullScore;
#Endif;

#Ifndef NO_SCORE;
Verb meta 'avisos'
	*                                           -> NotifyOn
	* 'si'                                      -> NotifyOn
	* 'no'                                      -> NotifyOff;
#Endif;

Verb meta 'ups' 'uy'
	*                                           -> Oops
	* special                                   -> OopsCorrection;

Verb meta 'reiniciar' 'empezar'
	*                                           -> Restart;

Verb meta 'cargar' 'restaurar'
	*                                           -> Restore;

Verb meta 'guardar' 'salvar'
	*                                           -> Save;

Verb meta 'puntos' 'puntuacion'
	*                                           -> Score;

Verb meta 'superbreve' 'corto'
	*                                           -> LookModeShort;

Verb meta 'detallado' 'largo'
	*                                           -> LookModeLong;

Verb meta 'version'
	*                                           -> Version;

Verb meta 'salir' 'terminar' 'q//'
	*                                           -> Quit;

! ---------------------
! Verbos extendidos españoles
! ---------------------

#IfDef OPTIONAL_EXTENDED_VERBSET;

Verb 'soplar'
	* held                                      -> Blow;

Verb 'maldicion' 'diablos' 'rayos'
	*                                           -> Mild
	* topic                                     -> Mild;

Verb 'quemar' 'encender'
	* noun                                      -> Burn
	* noun 'con' held                           -> Burn;

Verb 'comprar' 'adquirir'
	* noun                                      -> Buy;

Verb 'consultar'
	* noun 'sobre' topic                        -> Consult
	* noun 'acerca' 'de' topic                  -> Consult;

Verb 'vaciar'
	* noun                                      -> Empty
	* noun 'en' noun                            -> EmptyT
	* noun 'sobre' noun                         -> EmptyT;

Verb 'dentro' 'adentro'
	*                                           -> GoIn;

Verb 'besar' 'abrazar'
	* creature                                  -> Kiss;

Verb 'no'
	*                                           -> No;

Verb 'pelar' 'quitar'
	* noun                                      -> Take;

Verb 'rezar' 'orar'
	*                                           -> Pray;

Verb 'forzar' 'hacer' 'palanca'
	* noun 'con' held                           -> Unlock
	* noun 'con' held                           -> Unlock;

Verb 'ajustar' 'configurar'
	* noun                                      -> Set
	* noun 'a' special                          -> SetTo;

Verb 'mierda' 'joder' 'carajo'
	*                                           -> Strong
	* topic                                     -> Strong;

Verb 'cantar'
	*                                           -> Sing;

Verb 'dormir' 'descansar'
	*                                           -> Sleep;

Verb 'perdon' 'disculpa'
	*                                           -> Sorry;

Verb 'apretar' 'estrujar' 'comprimir'
	* noun                                      -> Squeeze;

Verb 'nadar' 'bucear'
	*                                           -> Swim;

Verb 'balancear' 'columpiar'
	* noun                                      -> Swing
	* 'en' noun                                 -> Swing;

Verb 'probar' 'saborear'
	* noun                                      -> Taste;

Verb 'pensar' 'reflexionar'
	*                                           -> Think;

Verb 'transferir' 'pasar'
	* noun 'a' noun                             -> Transfer;

Verb 'despertar' 'levantarse'
	*                                           -> Wake
	* creature                                  -> WakeOther;

Verb 'agitar' 'mover'
	*                                           -> WaveHands
	* noun                                      -> Wave;

Verb 'si' 'claro' 'vale'
	*                                           -> Yes;

#EndIf;

! ---------------------
! Direcciones españolas
! ---------------------

! El objeto Directions se mantiene igual, pero se añade soporte 
! para palabras españolas en el parser

! Las implementaciones de las acciones se mantienen iguales
! ya que la lógica no cambia, solo los comandos de entrada