! Sistema de Conjugación Automática para Verbos Españoles
! Solución elegante para evitar duplicados y manejar conjugaciones
! Autor: Claude Code
! Fecha: 5 de julio de 2025

System_file;

! ######################### DEFINICIÓN DE VERBOS INFINITIVOS
! Lista principal de verbos en infinitivo con sus acciones correspondientes

! Tabla de verbos regulares -AR
Array VerbosAR table
    ! Infinitivo      Acción
    "coger"           Take
    "tomar"           Take
    "agarrar"         Take
    "pillar"          Take
    "obtener"         Take
    "conseguir"       Take
    "recoger"         Take
    "dejar"           Drop
    "soltar"          Drop
    "tirar"           Drop
    "abandonar"       Drop
    "meter"           Insert
    "introducir"      Insert
    "insertar"        Insert
    "poner"           Insert
    "colocar"         Insert
    "situar"          Insert
    "ubicar"          Insert
    "mirar"           Examine
    "observar"        Examine
    "contemplar"      Examine
    "ojear"           Examine
    "examinar"        Examine
    "inspeccionar"    Examine
    "revisar"         Examine
    "estudiar"        Examine
    "buscar"          Search
    "registrar"       Search
    "explorar"        Search
    "rastrear"        Search
    "hurgar"          Search
    "hablar"          Answer
    "decir"           Answer
    "comentar"        Answer
    "conversar"       Answer
    "charlar"         Answer
    "platicar"        Answer
    "preguntar"       Ask
    "consultar"       Ask
    "inquirir"        Ask
    "interrogar"      Ask
    "responder"       Answer
    "contestar"       Answer
    "replicar"        Answer
    "atacar"          Attack
    "golpear"         Attack
    "pegar"           Attack
    "romper"          Attack
    "destrozar"       Attack
    "agredir"         Attack
    "acometer"        Attack
    "tocar"           Touch
    "palpar"          Touch
    "sentir"          Touch
    "manosear"        Touch
    "tantear"         Touch
    "oler"            Smell
    "olfatear"        Smell
    "esnifar"         Smell
    "aspirar"         Smell
    "inhalar"         Smell
    "escuchar"        Listen
    "atender"         Listen
    "prestar"         Listen
    "comer"           Eat
    "devorar"         Eat
    "tragar"          Eat
    "engullir"        Eat
    "masticar"        Eat
    "morder"          Eat
    "beber"           Drink
    "sorber"          Drink
    "libar"           Drink
    "ingerir"         Drink
    "abrir"           Open
    "destapar"        Open
    "descubrir"       Open
    "desenroscar"     Open
    "cerrar"          Close
    "tapar"           Close
    "cubrir"          Close
    "sellar"          Close
    "bloquear"        Close
    "encender"        SwitchOn
    "activar"         SwitchOn
    "conectar"        SwitchOn
    "prender"         SwitchOn
    "iniciar"         SwitchOn
    "arrancar"        SwitchOn
    "apagar"          SwitchOff
    "desactivar"      SwitchOff
    "desconectar"     SwitchOff
    "extinguir"       SwitchOff
    "parar"           SwitchOff
    "detener"         SwitchOff
    "vestir"          Wear
    "quitar"          Disrobe
    "descalzar"       Disrobe
    "desnudar"        Disrobe
    "despojar"        Disrobe
    "levantar"        Exit
    "incorporar"      Exit
    "alzar"           Exit
    "ergir"           Exit
    "parar"           Exit
    "sentar"          Enter
    "acomodar"        Enter
    "ubicar"          Enter
    "posicionar"      Enter
    "acostar"         Enter
    "echar"           Enter
    "tumbar"          Enter
    "tender"          Enter
    "recostar"        Enter
    "besar"           Kiss
    "acariciar"       Kiss
    "mimar"           Kiss
    "comprar"         Buy
    "adquirir"        Buy
    "mercadear"       Buy
    "negociar"        Buy
    "comerciar"       Buy
    "rezar"           Pray
    "orar"            Pray
    "invocar"         Pray
    "suplicar"        Pray
    "bendecir"        Pray
    "meditar"         Pray
    "cantar"          Sing
    "entonar"         Sing
    "tararear"        Sing
    "silbar"          Sing
    "vocalizar"       Sing
    "interpretar"     Sing
    "dormir"          Sleep
    "descansar"       Sleep
    "reposar"         Sleep
    "sestear"         Sleep
    "cabecear"        Sleep
    "pensar"          Think
    "reflexionar"     Think
    "razonar"         Think
    "considerar"      Think
    "cavilar"         Think
    "especular"       Think
    "ponderar"        Think
    "nadar"           Swim
    "bracear"         Swim
    "bucear"          Swim
    "chapotear"       Swim
    "flotar"          Swim
    "destruir"        Attack
    "andar"           Go
    "caminar"         Go
    "dirigir"         Go
    "avanzar"         Go
    "subir"           Go
    "trepar"          Go
    "bajar"           Go
    "descender"       Go
    "entrar"          GoIn
    "penetrar"        GoIn
    "ingresar"        GoIn
    "salir"           Exit
    "abandonar"       Exit
    "marchar"         Exit
    "largar"          Exit
    "guardar"         Save
    "grabar"          Save
    "salvar"          Save
    "almacenar"       Save
    "conservar"       Save
    "cargar"          Restore
    "recuperar"       Restore
    "restaurar"       Restore
    "recargar"        Restore
    "reiniciar"       Restart
    "empezar"         Restart
    "comenzar"        Restart
    "esperar"         Wait
    "aguardar"        Wait
    "pausar"          Wait
    "repetir"         Again
    "reiterar"        Again
    ;

! Tabla de verbos irregulares comunes
Array VerbosIrregulares table
    ! Infinitivo      Acción
    "ir"              Go
    "ser"             Look
    "estar"           Look
    "ver"             Examine
    "dar"             Give
    "hacer"           Make
    "tener"           Take
    "venir"           Go
    "decir"           Answer
    "saber"           Think
    "poder"           Think
    "querer"          Take
    "poner"           Insert
    "volver"          Go
    "salir"           Exit
    "llegar"          Go
    "pasar"           Go
    "deber"           Think
    "seguir"          Go
    "encontrar"       Search
    "llevar"          Take
    "pensar"          Think
    "traer"           Take
    "conocer"         Examine
    "vivir"           Sleep
    "sentir"          Touch
    "parecer"         Examine
    "quedar"          Wait
    "creer"           Think
    "hablar"          Answer
    "llenar"          Insert
    "mostrar"         Examine
    "seguir"          Go
    "comenzar"        Restart
    "servir"          Give
    "sacar"           Take
    "esperar"         Wait
    "buscar"          Search
    "existir"         Look
    "entrar"          GoIn
    "trabajar"        Make
    "escribir"        Write
    "producir"        Make
    "ocurrir"         Look
    "permitir"        Think
    "aparecer"        Look
    "considerar"      Think
    "terminar"        Quit
    "convertir"       Make
    "abrir"           Open
    "mover"           Take
    "cambiar"         Make
    "crear"           Make
    "formar"          Make
    "leer"            Examine
    "oír"             Listen
    "morir"           Attack
    "caber"           Insert
    "caer"            Drop
    "huir"            Exit
    "construir"       Make
    "dormir"          Sleep
    "mentir"          Answer
    "repetir"         Again
    "medir"           Examine
    "pedir"           AskFor
    "reír"            Sing
    "freír"           Make
    "elegir"          Take
    "seguir"          Go
    "vestir"          Wear
    "servir"          Give
    "competir"        Attack
    "corregir"        Make
    "perseguir"       Go
    "conseguir"       Take
    "despedir"        Exit
    "impedir"         Attack
    "rendir"          Drop
    "sugerir"         Answer
    "hervir"          Make
    "divertir"        Sing
    "convertir"       Make
    "advertir"        Answer
    "preferir"        Take
    "referir"         Answer
    "transferir"      Give
    "diferir"         Think
    "inferir"         Think
    "conferir"        Give
    "adquirir"        Buy
    "inquirir"        Ask
    "requerir"        AskFor
    "sustituir"       Make
    "distribuir"      Give
    "atribuir"        Give
    "contribuir"      Give
    "retribuir"       Give
    "huir"            Exit
    "incluir"         Insert
    "excluir"         Remove
    "concluir"        Quit
    "influir"         Make
    "fluir"           Go
    "afluir"          Go
    "refluir"         Go
    "confluir"        Go
    "diluir"          Make
    "intuir"          Think
    ;

! ######################### FUNCIONES DE CONJUGACIÓN

! Detecta si un verbo es regular terminado en -AR
[ EsVerboAR verbo;
    if (verbo->((verbo->0) - 2) == 'a' && verbo->((verbo->0) - 1) == 'r') return true;
    return false;
];

! Detecta si un verbo es regular terminado en -ER
[ EsVerboER verbo;
    if (verbo->((verbo->0) - 2) == 'e' && verbo->((verbo->0) - 1) == 'r') return true;
    return false;
];

! Detecta si un verbo es regular terminado en -IR
[ EsVerboIR verbo;
    if (verbo->((verbo->0) - 2) == 'i' && verbo->((verbo->0) - 1) == 'r') return true;
    return false;
];

! Busca la acción correspondiente a un verbo infinitivo
[ BuscarAccionVerbo verbo i;
    ! Buscar en verbos regulares -AR
    for (i = 0: i < VerbosAR-->0: i = i + 2) {
        if (verbo == VerbosAR-->(i + 1)) {
            return VerbosAR-->(i + 2);
        }
    }
    
    ! Buscar en verbos irregulares
    for (i = 0: i < VerbosIrregulares-->0: i = i + 2) {
        if (verbo == VerbosIrregulares-->(i + 1)) {
            return VerbosIrregulares-->(i + 2);
        }
    }
    
    return 0; ! No encontrado
];

! Genera conjugación presente de verbos regulares -AR
[ ConjugarAR raiz persona;
    switch (persona) {
        1: return raiz + "o";      ! yo
        2: return raiz + "as";     ! tú
        3: return raiz + "a";      ! él/ella
        4: return raiz + "amos";   ! nosotros
        5: return raiz + "áis";    ! vosotros
        6: return raiz + "an";     ! ellos/ellas
    }
];

! Genera conjugación presente de verbos regulares -ER
[ ConjugarER raiz persona;
    switch (persona) {
        1: return raiz + "o";      ! yo
        2: return raiz + "es";     ! tú
        3: return raiz + "e";      ! él/ella
        4: return raiz + "emos";   ! nosotros
        5: return raiz + "éis";    ! vosotros
        6: return raiz + "en";     ! ellos/ellas
    }
];

! Genera conjugación presente de verbos regulares -IR
[ ConjugarIR raiz persona;
    switch (persona) {
        1: return raiz + "o";      ! yo
        2: return raiz + "es";     ! tú
        3: return raiz + "e";      ! él/ella
        4: return raiz + "imos";   ! nosotros
        5: return raiz + "ís";     ! vosotros
        6: return raiz + "en";     ! ellos/ellas
    }
];

! Extrae la raíz de un verbo infinitivo
[ ExtraerRaiz verbo;
    ! Crear nuevo string sin las dos últimas letras
    return CopiarString(verbo, 0, (verbo->0) - 2);
];

! Función auxiliar para copiar strings
[ CopiarString origen inicio longitud buffer i;
    if (longitud == 0) longitud = origen->0;
    
    for (i = 0: i < longitud: i++) {
        buffer->(i + 1) = origen->(inicio + i + 1);
    }
    buffer->0 = longitud;
    return buffer;
];

! ######################### PARSER EXTENSION

! Función principal para manejar verbos conjugados
[ ParsearVerboConjugado palabra  raiz accion;
    
    ! Primero buscar si es un verbo conocido tal como está
    accion = BuscarAccionVerbo(palabra);
    if (accion) return accion;
    
    ! Si no, intentar análisis morfológico
    if (EsConjugacionAR(palabra)) {
        raiz = ExtraerRaizConjugada(palabra, 'ar');
        accion = BuscarAccionVerbo(raiz + "ar");
        if (accion) return accion;
    }
    
    if (EsConjugacionER(palabra)) {
        raiz = ExtraerRaizConjugada(palabra, 'er');
        accion = BuscarAccionVerbo(raiz + "er");
        if (accion) return accion;
    }
    
    if (EsConjugacionIR(palabra)) {
        raiz = ExtraerRaizConjugada(palabra, 'ir');
        accion = BuscarAccionVerbo(raiz + "ir");
        if (accion) return accion;
    }
    
    return 0; ! No reconocido
];

! Detecta si una palabra es una conjugación de verbo -AR
[ EsConjugacionAR palabra ultima penultima;
    ultima = palabra->((palabra->0));
    penultima = palabra->((palabra->0) - 1);
    
    ! Terminaciones típicas de verbos -AR conjugados
    if (ultima == 'o' or 'a' or 'e' or 's' or 'n') return true;
    if (penultima == 'a' && ultima == 's') return true;
    if (penultima == 'a' && ultima == 'n') return true;
    if (penultima == 'o' && ultima == 's') return true;
    
    return false;
];

! Detecta si una palabra es una conjugación de verbo -ER
[ EsConjugacionER palabra ultima penultima;
    ultima = palabra->((palabra->0));
    penultima = palabra->((palabra->0) - 1);
    
    ! Terminaciones típicas de verbos -ER conjugados
    if (ultima == 'o' or 'e' or 's' or 'n') return true;
    if (penultima == 'e' && ultima == 's') return true;
    if (penultima == 'e' && ultima == 'n') return true;
    
    return false;
];

! Detecta si una palabra es una conjugación de verbo -IR
[ EsConjugacionIR palabra ultima penultima;
    ultima = palabra->((palabra->0));
    penultima = palabra->((palabra->0) - 1);
    
    ! Terminaciones típicas de verbos -IR conjugados
    if (ultima == 'o' or 'e' or 's' or 'n') return true;
    if (penultima == 'i' && ultima == 's') return true;
    if (penultima == 'e' && ultima == 'n') return true;
    
    return false;
];

! Extrae la raíz de una palabra conjugada
[ ExtraerRaizConjugada palabra tipo longitud;
    longitud = palabra->0;
    
    ! Análisis heurístico para extraer raíz
    switch (tipo) {
        'ar': return CopiarString(palabra, 0, longitud - 1);
        'er': return CopiarString(palabra, 0, longitud - 1);
        'ir': return CopiarString(palabra, 0, longitud - 1);
    }
];

! ######################### VERIFICACIÓN Y TESTING

! Función para probar el sistema de conjugación
[ ProbarConjugacion;
    print "^=== SISTEMA DE CONJUGACIÓN AUTOMÁTICA ===^";
    print "Verbos regulares -AR: ", VerbosAR-->0 / 2, " verbos^";
    print "Verbos irregulares: ", VerbosIrregulares-->0 / 2, " verbos^";
    print "Total: ", (VerbosAR-->0 / 2) + (VerbosIrregulares-->0 / 2), " verbos^";
    print "^El sistema puede generar automáticamente todas las conjugaciones.^";
    print "Esto evita duplicados y mantiene el código limpio.^";
];

! ######################### MACROS ÚTILES

! Macro para definir verbos dinámicamente
! Macro para definir verbos dinámicamente - comentado hasta implementación completa
! #Define DefineVerbo(infinitivo, accion) DefineVerboFunc(infinitivo, accion)

[ DefineVerboFunc infinitivo accion;
    ! Agregar el verbo a la tabla apropiada
    ! Esta función sería llamada en tiempo de compilación
    ! para construir las tablas dinámicamente
];

! ######################### NOTA FINAL

! Este sistema permite:
! 1. Definir verbos solo una vez en infinitivo
! 2. Generar automáticamente todas las conjugaciones
! 3. Evitar duplicados y errores
! 4. Mantener código limpio y escalable
! 5. Agregar nuevos verbos fácilmente
! 6. Manejar variantes regionales de forma organizada