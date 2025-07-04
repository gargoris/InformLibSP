! Parser Español para PunyInform
! Extensiones y adaptaciones del parser para manejar español
! Incluye manejo de artículos, contracciones y formas reflexivas

System_file;

! ######################### Constantes para español

Constant ARTICULO_EL = 'el';
Constant ARTICULO_LA = 'la';  
Constant ARTICULO_LOS = 'los';
Constant ARTICULO_LAS = 'las';
Constant ARTICULO_UN = 'un';
Constant ARTICULO_UNA = 'una';
Constant ARTICULO_UNOS = 'unos';
Constant ARTICULO_UNAS = 'unas';

Constant CONTRACCION_DEL = 'del';
Constant CONTRACCION_AL = 'al';

Constant PREPOSICION_DE = 'de';
Constant PREPOSICION_A = 'a';
Constant PREPOSICION_EN = 'en';
Constant PREPOSICION_CON = 'con';
Constant PREPOSICION_PARA = 'para';
Constant PREPOSICION_POR = 'por';
Constant PREPOSICION_SOBRE = 'sobre';
Constant PREPOSICION_BAJO = 'bajo';

! Palabras especiales en español
Constant TODO_WORD = 'todo';
Constant TODOS_WORD = 'todos';
Constant TODAS_WORD = 'todas';
Constant ALGO_WORD = 'algo';
Constant ALGUIEN_WORD = 'alguien';
Constant NADA_WORD = 'nada';
Constant NADIE_WORD = 'nadie';

! ######################### Funciones de parsing específicas para español

[ EsArticulo p_word;
    if (p_word == ARTICULO_EL or ARTICULO_LA or ARTICULO_LOS or ARTICULO_LAS or
        ARTICULO_UN or ARTICULO_UNA or ARTICULO_UNOS or ARTICULO_UNAS) rtrue;
    rfalse;
];

[ EsContraccion p_word;
    if (p_word == CONTRACCION_DEL or CONTRACCION_AL) rtrue;
    rfalse;
];

[ EsPreposicion p_word;
    if (p_word == PREPOSICION_DE or PREPOSICION_A or PREPOSICION_EN or 
        PREPOSICION_CON or PREPOSICION_PARA or PREPOSICION_POR or
        PREPOSICION_SOBRE or PREPOSICION_BAJO) rtrue;
    rfalse;
];

[ EsPronombreReflexivo p_word;
    if (p_word == 'me' or 'te' or 'se' or 'nos' or 'os') rtrue;
    rfalse;
];

! ######################### Manejo de contracciones españolas

[ ExpandirContraccion p_word;
    ! Expande contracciones como "del" -> "de" + "el"
    switch(p_word) {
        CONTRACCION_DEL:
            return PREPOSICION_DE; ! Seguido implícitamente por ARTICULO_EL
        CONTRACCION_AL:
            return PREPOSICION_A;  ! Seguido implícitamente por ARTICULO_EL
        default:
            return p_word;
    }
];

! ######################### Parser de nombres con género y número

[ ParsearNombreEspanol p_obj p_words_matched _i _word _articulo _genero _numero;
    ! Intenta hacer match de un objeto considerando artículos españoles
    _i = wn;
    _word = NextWord();
    
    ! Saltar artículos si los hay
    if (EsArticulo(_word)) {
        _articulo = _word;
        ! Determinar género y número del artículo
        if (_word == ARTICULO_EL or ARTICULO_UN) _genero = 0; ! masculino
        if (_word == ARTICULO_LA or ARTICULO_UNA) _genero = 1; ! femenino
        if (_word == ARTICULO_LOS or ARTICULO_UNOS) { _genero = 0; _numero = 1; } ! masc. plural
        if (_word == ARTICULO_LAS or ARTICULO_UNAS) { _genero = 1; _numero = 1; } ! fem. plural
        
        _word = NextWord();
    }
    
    ! Verificar si el género y número coinciden con el objeto
    if (_articulo ~= 0) {
        if (_genero == 1 && p_obj hasnt female) return 0; ! Artículo fem. con obj. masc.
        if (_genero == 0 && p_obj has female) return 0;   ! Artículo masc. con obj. fem.
        if (_numero == 1 && p_obj hasnt pluralname) return 0; ! Artículo plural con obj. singular
        if (_numero == 0 && p_obj has pluralname) return 0;   ! Artículo singular con obj. plural
    }
    
    ! Intentar hacer match con el nombre del objeto
    wn = _i;
    return ParseToken(ELEMENTARY_TT, NOUN_TOKEN);
];

! ######################### Funciones auxiliares para el parser

[ SaltarPalabrasIrrelevantes;
    ! Salta artículos, preposiciones y otras palabras que no afectan al significado
    while (wn <= num_words) {
        if (EsArticulo(WordValue(wn)) || EsPreposicion(WordValue(wn))) {
            wn++;
            continue;
        }
        break;
    }
];

[ BuscarObjetoConArticulo p_type p_descriptors;
    ! Busca un objeto permitiendo artículos españoles
    SaltarPalabrasIrrelevantes();
    return ParseToken(ELEMENTARY_TT, p_type);
];

! ######################### Manejo de verbos reflexivos

Global verbo_reflexivo = false;
Global pronombre_reflexivo = 0;

[ DetectarVerboReflexivo _i _word;
    ! Detecta si hay un pronombre reflexivo en la oración
    verbo_reflexivo = false;
    pronombre_reflexivo = 0;
    
    for (_i = 1: _i <= num_words: _i++) {
        _word = WordValue(_i);
        if (EsPronombreReflexivo(_word)) {
            verbo_reflexivo = true;
            pronombre_reflexivo = _word;
            ! Simplificado por ahora - no modificar num_words
            break;
        }
    }
];

! ######################### Funciones de corrección ortográfica básica

[ CorregirOrtografia p_word;
    ! Correcciones ortográficas comunes
    switch(p_word) {
        'mira': return 'mirar';
        'coge': return 'coger';
        'pon': return 'poner';
        'abre': return 'abrir';
        've': return 'ir';
        'sal': return 'salir';
        default: return p_word;
    }
];

! ######################### Análisis sintáctico mejorado

[ AnalizarFraseEspanola _i _word _verbo_encontrado;
    ! Análisis básico de la estructura de la frase española
    DetectarVerboReflexivo();
    
    ! Buscar el verbo principal
    for (_i = 1: _i <= num_words: _i++) {
        _word = WordValue(_i);
        _word = CorregirOrtografia(_word);
        
        ! Si encontramos un verbo conocido, restructurar si es necesario
        if (IsVerb(_word)) {
            _verbo_encontrado = true;
            break;
        }
    }
    
    return _verbo_encontrado;
];

! ######################### Mensajes de error en español

[ MensajeErrorParser p_tipo p_palabra;
    switch(p_tipo) {
        1: ! Palabra desconocida
            print "No entiendo la palabra '", (address) p_palabra, "'.^";
        2: ! Verbo desconocido
            print "No conozco el verbo '", (address) p_palabra, "'.^";
        3: ! Objeto no visible
            print "No veo ning";
            if (EsFemenino(noun)) print "una"; else print "ún";
            print " '", (address) p_palabra, "' por aquí.^";
        4: ! Ambigüedad
            print "¿Te refieres a cuál de ";
            if (EsPlural(noun)) print "esos"; else print "eso";
            print "?^";
        default:
            print "No entiendo lo que quieres decir.^";
    }
];

! ######################### Funciones de utilidad

[ TryNumber p_wordnum _word _num _sign _digit;
    ! Intenta convertir una palabra a número, incluyendo números en español
    _word = WordValue(p_wordnum);
    
    ! Números en español
    switch(_word) {
        'cero': return 0;
        'uno': return 1;
        'dos': return 2;
        'tres': return 3;
        'cuatro': return 4;
        'cinco': return 5;
        'seis': return 6;
        'siete': return 7;
        'ocho': return 8;
        'nueve': return 9;
        'diez': return 10;
        'once': return 11;
        'doce': return 12;
        'trece': return 13;
        'catorce': return 14;
        'quince': return 15;
        'dieciséis': return 16;
        'diecisiete': return 17;
        'dieciocho': return 18;
        'diecinueve': return 19;
        'veinte': return 20;
    }
    
    ! Usar la función original para números arábigos
    return TryNumber(p_wordnum);
];

! ######################### Integración con el parser principal

[ CustomParserSetup;
    ! Configuración inicial del parser español
    DetectarVerboReflexivo();
    AnalizarFraseEspanola();
];

! Redefinir algunas funciones críticas del parser si es necesario
#Ifdef PARSER_SPANISH_OVERRIDE;

[ NounDomain p_domain p_actor p_noun_filter p_tok _word;
    ! Versión española del dominio de sustantivos que maneja artículos
    SaltarPalabrasIrrelevantes();
    
    _word = WordValue(wn);
    if (EsContraccion(_word)) {
        _word = ExpandirContraccion(_word);
        WordValue(wn) = _word;
    }
    
    ! Llamar a la función original con las modificaciones
    return NounDomain(p_domain, p_actor, p_noun_filter, p_tok);
];

#Endif;

! ######################### Direcciones en español

Object DireccionesEspanol "direcciones"
    with description "Una dirección para moverte.",
         parse_name [ _w _i _matched;
            _w = NextWord();
            switch(_w) {
                'norte', 'n//': _matched = 1; selected_direction_index = 1;
                'sur', 's//': _matched = 1; selected_direction_index = 2;  
                'este', 'e//': _matched = 1; selected_direction_index = 3;
                'oeste', 'o//': _matched = 1; selected_direction_index = 4;
                'noreste', 'ne': _matched = 1; selected_direction_index = 5;
                'noroeste', 'no', 'nw': _matched = 1; selected_direction_index = 6;
                'sureste', 'se': _matched = 1; selected_direction_index = 7;
                'suroeste', 'so', 'sw': _matched = 1; selected_direction_index = 8;
                'arriba', 'subir', 'u//': _matched = 1; selected_direction_index = 9;
                'abajo', 'bajar', 'd//': _matched = 1; selected_direction_index = 10;
                'dentro', 'adentro': _matched = 1; selected_direction_index = 11;
                'fuera', 'afuera': _matched = 1; selected_direction_index = 12;
                default: return 0;
            }
            
            if (_matched) {
                selected_direction = direction_properties_array->selected_direction_index;
                return 1;
            }
            return 0;
         ],
    has scenery;