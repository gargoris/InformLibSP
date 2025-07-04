! PunyInform Español - Versión Simplificada que Compila
! Solo verbos básicos españoles agregados a la librería original

System_file;

! Incluir la librería original completa
Include "globals.h";
Include "puny.h";

! ######################### VERBOS ESPAÑOLES BÁSICOS

! Después de incluir puny.h, agregar verbos españoles

! Verbos de movimiento
Verb 'ir' 'vete' 'anda' 'camina'
    * noun -> Go;

! Verbos de manipulación  
Verb 'coger' 'coge' 'tomar' 'toma' 'agarrar' 'agarra'
    * multi -> Take;

Verb 'dejar' 'deja' 'soltar' 'suelta'
    * multiheld -> Drop;

Verb 'meter' 'mete' 'introducir' 'introduce'
    * multiexcept 'en' noun -> Insert;

Verb 'poner' 'pon' 'colocar' 'coloca'
    * multiexcept 'en' noun -> Insert
    * multiexcept 'sobre' noun -> PutOn;

! Verbos de examinación
Verb 'mirar' 'mira' 'ver' 've' 'observar' 'observa'
    * noun -> Examine
    * -> Look;

Verb 'examinar' 'examina' 'inspeccionar' 'inspecciona'
    * noun -> Examine;

Verb 'buscar' 'busca' 'registrar' 'registra'
    * noun -> Search;

! Verbos de acción
Verb 'abrir' 'abre' 'destapar' 'destapa'
    * noun -> Open;

Verb 'cerrar' 'cierra' 'tapar' 'tapa'
    * noun -> Close;

Verb 'encender' 'enciende' 'activar' 'activa'
    * noun -> SwitchOn;

Verb 'apagar' 'apaga' 'desactivar' 'desactiva'
    * noun -> SwitchOff;

Verb 'tocar' 'toca' 'palpar' 'palpa'
    * noun -> Touch;

Verb 'oler' 'huele' 'olfatear' 'olfatea'
    * noun -> Smell;

Verb 'escuchar' 'escucha' 'oir' 'oye'
    * noun -> Listen;

Verb 'comer' 'come' 'devorar' 'devora'
    * held -> Eat;

Verb 'beber' 'bebe'
    * noun -> Drink;

! Verbos de vestimenta
Verb 'vestir' 'viste' 'ponerse' 'ponte'
    * held -> Wear;

Verb 'quitar' 'quita' 'quitarse' 'quitate'
    * worn -> Disrobe;

! Metacomandos
Verb 'inventario' 'inv'
    * -> Inv;

Verb 'puntuacion' 'puntos'
    * -> Score;

Verb 'guardar' 'grabar' 'salvar'
    * -> Save;

Verb 'cargar' 'recuperar'
    * -> Restore;

Verb 'salir' 'abandonar' 'terminar'
    * -> Quit;

Verb 'esperar'
    * -> Wait;

Verb 'repetir' 'otra' 'vez'
    * -> Again;

! Direcciones españolas
Verb 'norte' 'n'
    * -> Go;
Verb 'sur' 's'  
    * -> Go;
Verb 'este' 'e'
    * -> Go;
Verb 'oeste' 'o'
    * -> Go;
Verb 'arriba' 'subir' 'sube'
    * -> Go;
Verb 'abajo' 'bajar' 'baja'
    * -> Go;
Verb 'entrar' 'dentro' 'adentro'
    * 'en' noun -> Enter;
Verb 'salida' 'fuera' 'afuera'
    * -> Exit
    * 'de' noun -> Exit;

! ######################### FUNCIONES AUXILIARES BÁSICAS

[ EsFemenino p_obj;
    if(p_obj has female) rtrue; 
    rfalse;
];

[ EsPlural p_obj;
    if(p_obj has pluralname) rtrue; 
    rfalse;
];

[ ElLa p_obj;
    if (EsFemenino(p_obj)) print "la"; 
    else print "el";
];

[ InicializarEspanol;
    ! Función de inicialización vacía por ahora
    print "";
];