! ==============================================================================
! SPANISHPARSER.H - PARTE 1: FUNDAMENTOS Y MANIPULACIÓN DE PALABRAS
! Sistema avanzado de parsing para español
! Parte del sistema modular Spanish Library para Inform 6
! Compatible con Inform 6.42 y librería estándar 6.12.7
! ==============================================================================

System_file;

#Ifndef SPANISH_PARSER_INCLUDED;
Constant SPANISH_PARSER_INCLUDED;
Constant SPANISH_PARSER_VERSION = "1.1-complete-part1";

! Verificación de dependencias
#Ifndef SPANISH_CONSTANTS_INCLUDED;
  Message fatalerror "*** Include SpanishConstants.h antes de SpanishParser.h ***";
#Endif;

#Ifndef SPANISH_CORE_INCLUDED;
  Message fatalerror "*** Include SpanishCore.h antes de SpanishParser.h ***";
#Endif;

#Ifdef LIBRARY_STAGE;
#Iffalse LIBRARY_STAGE >= AFTER_PARSER;
  Message fatalerror "*** Include Parser.h y VerbLib.h antes de SpanishParser.h ***";
#Endif;
#Endif;

! ==============================================================================
! VARIABLES LOCALES DE PARSING (NO GLOBALES - EVITAR DUPLICACIONES)
! ==============================================================================

! Estas variables ahora están centralizadas en SpanishConstants.h:
! - spanish_parse_stage
! - spanish_last_verb
! - spanish_parse_buffer
! - spanish_temp_parse

! Variables locales específicas del parser
Global spanish_compound_prep_found = 0;
Global spanish_contraction_processed = 0;
Global spanish_parse_errors = 0;
Global spanish_words_removed = 0;
Global spanish_corrections_made = 0;

! ==============================================================================
! RUTINAS DE MANIPULACIÓN DE PALABRAS - MEJORADAS
! ==============================================================================

[ SpanishRemoveWord pos   i;
    ! Elimina una palabra del buffer de parsing de forma segura
    if (pos < 0 || pos >= parse->1) return false;
    
    for (i = pos: i < parse->1 - 1: i++) {
        parse-->(2*i+1) = parse-->(2*(i+1)+1);
        parse-->(2*i+2) = parse-->(2*(i+1)+2);
    }
    parse->1 = parse->1 - 1;
    spanish_words_removed++;
    return true;
];

[ SpanishInsertWord pos word dict_value   i;
    ! Inserta una palabra en el buffer de parsing de forma segura
    if (pos < 0 || pos > parse->1) return false;
    if (parse->1 >= 30) return false; ! Límite de seguridad
    
    ! Mover palabras hacia la derecha
    for (i = parse->1: i > pos: i--) {
        parse-->(2*i+1) = parse-->(2*(i-1)+1);
        parse-->(2*i+2) = parse-->(2*(i-1)+2);
    }
    
    ! Insertar nueva palabra
    parse-->(2*pos+1) = word;
    parse-->(2*pos+2) = dict_value;
    parse->1 = parse->1 + 1;
    
    return true;
];

[ SpanishReplaceWord pos new_word new_dict_value;
    ! Reemplaza una palabra en el buffer de parsing
    if (pos < 0 || pos >= parse->1) return false;
    
    parse-->(2*pos+1) = new_word;
    parse-->(2*pos+2) = new_dict_value;
    return true;
];

[ SpanishGetWordAt pos;
    ! Obtiene la palabra en una posición específica de forma segura
    if (pos < 0 || pos >= parse->1) return 0;
    return parse-->(2*pos+1);
];

[ SpanishGetDictValueAt pos;
    ! Obtiene el valor de diccionario en una posición específica
    if (pos < 0 || pos >= parse->1) return 0;
    return parse-->(2*pos+2);
];

[ SpanishFindWord word   i;
    ! Encuentra la primera ocurrencia de una palabra en el buffer
    for (i = 0: i < parse->1: i++) {
        if (SpanishGetWordAt(i) == word) return i;
    }
    return -1;
];

[ SpanishFindWords word1 word2   i;
    ! Encuentra secuencia de dos palabras consecutivas
    for (i = 0: i < parse->1 - 1: i++) {
        if (SpanishGetWordAt(i) == word1 && SpanishGetWordAt(i+1) == word2) {
            return i;
        }
    }
    return -1;
];

[ SpanishFindThreeWords word1 word2 word3   i;
    ! Encuentra secuencia de tres palabras consecutivas
    for (i = 0: i < parse->1 - 2: i++) {
        if (SpanishGetWordAt(i) == word1 && 
            SpanishGetWordAt(i+1) == word2 && 
            SpanishGetWordAt(i+2) == word3) {
            return i;
        }
    }
    return -1;
];

! ==============================================================================
! FUNCIONES DE UTILIDAD PARA MANIPULACIÓN
! ==============================================================================

[ SpanishNormalizeParsing;
    ! Normaliza el buffer de parsing eliminando inconsistencias
    local i cleaned;
    cleaned = 0;
    
    ! Eliminar palabras duplicadas consecutivas
    i = 0;
    while (i < parse->1 - 1) {
        if (SpanishGetWordAt(i) == SpanishGetWordAt(i+1)) {
            SpanishRemoveWord(i+1);
            cleaned++;
        } else {
            i++;
        }
    }
    
    ! Eliminar espacios múltiples (representados como palabras vacías)
    i = 0;
    while (i < parse->1) {
        if (SpanishGetWordAt(i) == 0 || SpanishGetWordAt(i) == ' ') {
            SpanishRemoveWord(i);
            cleaned++;
        } else {
            i++;
        }
    }
    
    return cleaned;
];

[ SpanishExpandAbbreviations;
    ! Expande abreviaciones comunes
    local i word expansions;
    expansions = 0;
    
    for (i = 0: i < parse->1: i++) {
        word = SpanishGetWordAt(i);
        
        switch(word) {
            'inv', 'i': 
                SpanishReplaceWord(i, 'inventario', 'inventario');
                expansions++;
            'ex', 'x':
                SpanishReplaceWord(i, 'examinar', 'examinar');
                expansions++;
            'l':
                SpanishReplaceWord(i, 'mirar', 'mirar');
                expansions++;
            'n':
                SpanishReplaceWord(i, 'norte', 'norte');
                expansions++;
            's':
                SpanishReplaceWord(i, 'sur', 'sur');
                expansions++;
            'e':
                SpanishReplaceWord(i, 'este', 'este');
                expansions++;
            'o':
                SpanishReplaceWord(i, 'oeste', 'oeste');
                expansions++;
            'ne':
                SpanishReplaceWord(i, 'nordeste', 'nordeste');
                expansions++;
            'no':
                SpanishReplaceWord(i, 'noroeste', 'noroeste');
                expansions++;
            'se':
                SpanishReplaceWord(i, 'sudeste', 'sudeste');
                expansions++;
            'so':
                SpanishReplaceWord(i, 'sudoeste', 'sudoeste');
                expansions++;
            'g', 'r':
                SpanishReplaceWord(i, 'repetir', 'repetir');
                expansions++;
        }
    }
    
    return expansions;
];

[ SpanishReorderWords;
    ! Reordena palabras según patrones comunes del español
    ! Por ejemplo, "rojo el libro" -> "el libro rojo"
    local i temp_word temp_dict reorders;
    reorders = 0;
    
    ! Buscar patrones adj + art + sustantivo -> art + sustantivo + adj
    for (i = 0: i < parse->1 - 2: i++) {
        ! Si encontramos adjetivo + artículo + sustantivo
        if (SpanishIsAdjective(SpanishGetWordAt(i)) && 
            SpanishIsArticle(SpanishGetWordAt(i+1)) &&
            SpanishIsObjectCandidate(i+2)) {
            
            ! Intercambiar adjetivo y artículo
            temp_word = SpanishGetWordAt(i);
            temp_dict = SpanishGetDictValueAt(i);
            
            SpanishReplaceWord(i, SpanishGetWordAt(i+1), SpanishGetDictValueAt(i+1));
            SpanishReplaceWord(i+1, temp_word, temp_dict);
            
            reorders++;
        }
    }
    
    return reorders;
];

! ==============================================================================
! FUNCIONES DE CLASIFICACIÓN DE PALABRAS
! ==============================================================================

[ SpanishIsAdjective word;
    ! Determina si una palabra es un adjetivo común
    if (word == 'grande' or 'pequeño' or 'rojo' or 'azul' or 'verde' or 'amarillo') return true;
    if (word == 'bueno' or 'malo' or 'nuevo' or 'viejo' or 'joven' or 'alto' or 'bajo') return true;
    if (word == 'hermoso' or 'feo' or 'rápido' or 'lento' or 'fuerte' or 'débil') return true;
    if (word == 'caliente' or 'frío' or 'húmedo' or 'seco' or 'suave' or 'duro') return true;
    if (word == 'claro' or 'oscuro' or 'brillante' or 'opaco' or 'limpio' or 'sucio') return true;
    return false;
];

[ SpanishIsArticle word;
    ! Artículos españoles
    if (word == 'el' or 'la' or 'los' or 'las' or 'un' or 'una' or 'unos' or 'unas') return true;
    return false;
];

[ SpanishIsConjunction word;
    ! Conjunciones españolas
    if (word == 'y' or 'e' or 'o' or 'u' or 'pero' or 'mas' or 'sino' or 'aunque') return true;
    if (word == 'porque' or 'puesto' or 'dado' or 'mientras' or 'cuando' or 'si') return true;
    return false;
];

[ SpanishIsPreposition word;
    ! Lista extendida de preposiciones españolas
    if (word == 'a' or 'ante' or 'bajo' or 'con' or 'contra' or 'de' or 'desde' 
              or 'durante' or 'en' or 'entre' or 'hacia' or 'hasta' or 'mediante'
              or 'para' or 'por' or 'según' or 'sin' or 'sobre' or 'tras') return true;
              
    ! Preposiciones compuestas
    if (word == 'debajo_de' or 'encima_de' or 'cerca_de' or 'lejos_de' 
              or 'delante_de' or 'detrás_de' or 'dentro_de' or 'fuera_de'
              or 'al_lado_de' or 'a_través_de' or 'alrededor_de' or 'en_frente_de'
              or 'por_encima_de' or 'por_debajo_de' or 'en_lugar_de' or 'en_vez_de') return true;
              
    return false;
];

[ SpanishIsAdverb word;
    ! Adverbios comunes en español
    if (word == 'muy' or 'poco' or 'mucho' or 'bastante' or 'demasiado') return true;
    if (word == 'siempre' or 'nunca' or 'jamás' or 'ya' or 'todavía' or 'aún') return true;
    if (word == 'aquí' or 'ahí' or 'allí' or 'acá' or 'allá') return true;
    if (word == 'bien' or 'mal' or 'mejor' or 'peor' or 'así' or 'también') return true;
    if (word == 'sí' or 'no' or 'quizás' or 'tal_vez' or 'posiblemente') return true;
    return false;
];

[ SpanishIsPronoun word;
    ! Pronombres españoles
    if (word == 'yo' or 'tú' or 'él' or 'ella' or 'nosotros' or 'vosotros' or 'ellos' or 'ellas') return true;
    if (word == 'me' or 'te' or 'se' or 'nos' or 'os' or 'le' or 'la' or 'lo' or 'les' or 'las' or 'los') return true;
    if (word == 'mi' or 'tu' or 'su' or 'nuestro' or 'vuestro') return true;
    if (word == 'este' or 'esta' or 'esto' or 'ese' or 'esa' or 'eso' or 'aquel' or 'aquella' or 'aquello') return true;
    return false;
];

! ==============================================================================
! FUNCIONES DE VALIDACIÓN BÁSICA
! ==============================================================================

[ SpanishValidateBuffer;
    ! Valida la integridad básica del buffer de parsing
    local i errors;
    errors = 0;
    
    ! Verificar que el número de palabras sea válido
    if (parse->1 < 0 || parse->1 > 30) {
        errors++;
        #Ifdef DEBUG;
            print "[PARSER] Número inválido de palabras: ", parse->1, "^";
        #Endif;
    }
    
    ! Verificar que no haya palabras nulas en posiciones válidas
    for (i = 0: i < parse->1: i++) {
        if (SpanishGetWordAt(i) == 0) {
            errors++;
            #Ifdef DEBUG;
                print "[PARSER] Palabra nula en posición ", i, "^";
            #Endif;
        }
    }
    
    return errors;
];

[ SpanishCountWordsOfType type   i count;
    ! Cuenta palabras de un tipo específico en el buffer
    count = 0;
    
    for (i = 0: i < parse->1: i++) {
        switch(type) {
            1: ! Verbos
                if (SpanishIsVerbCandidate(i)) count++;
            2: ! Sustantivos/objetos
                if (SpanishIsObjectCandidate(i)) count++;
            3: ! Preposiciones
                if (SpanishIsPreposition(SpanishGetWordAt(i))) count++;
            4: ! Artículos
                if (SpanishIsArticle(SpanishGetWordAt(i))) count++;
            5: ! Adjetivos
                if (SpanishIsAdjective(SpanishGetWordAt(i))) count++;
        }
    }
    
    return count;
];

! ==============================================================================
! FUNCIONES DE ANÁLISIS PRELIMINAR
! ==============================================================================

[ SpanishAnalyzeWordPattern;
    ! Analiza el patrón general de palabras en el comando
    local pattern verbs objects preps articles;
    
    verbs = SpanishCountWordsOfType(1);
    objects = SpanishCountWordsOfType(2);
    preps = SpanishCountWordsOfType(3);
    articles = SpanishCountWordsOfType(4);
    
    ! Crear un código de patrón basado en la estructura
    pattern = verbs * 1000 + objects * 100 + preps * 10 + articles;
    
    #Ifdef DEBUG;
        print "[PARSER] Patrón detectado: ", pattern, " (V:", verbs, " O:", objects, " P:", preps, " A:", articles, ")^";
    #Endif;
    
    return pattern;
];

[ SpanishGetCommandComplexity;
    ! Determina la complejidad del comando basado en varios factores
    local complexity;
    complexity = 0;
    
    ! Complejidad por longitud
    if (parse->1 > 15) complexity += 5;
    else if (parse->1 > 10) complexity += 3;
    else if (parse->1 > 6) complexity += 2;
    else if (parse->1 > 3) complexity += 1;
    
    ! Complejidad por tipos de palabras
    complexity += SpanishCountWordsOfType(3); ! Preposiciones
    complexity += SpanishCountWordsOfType(1); ! Verbos adicionales
    
    ! Complejidad por procesamiento realizado
    complexity += spanish_compound_prep_found;
    complexity += spanish_contraction_processed;
    
    return complexity;
];

! ==============================================================================
! RUTINAS DE INICIALIZACIÓN Y DEPURACIÓN
! ==============================================================================

[ SpanishParserInitializePart1;
    ! Inicialización específica de la Parte 1
    spanish_compound_prep_found = 0;
    spanish_contraction_processed = 0;
    spanish_parse_errors = 0;
    spanish_words_removed = 0;
    spanish_corrections_made = 0;
    
    #Ifdef DEBUG;
        print "[SpanishParser Parte 1 v", (string) SPANISH_PARSER_VERSION, " inicializado]^";
        print "[Manipulación de palabras, normalización, expansión de abreviaciones]^";
    #Endif;
];

#Ifdef DEBUG;
[ SpanishDebugBuffer;
    ! Muestra el estado actual del buffer de parsing
    local i;
    
    print "^[DEBUG] Buffer de parsing:^";
    print "Palabras: ", parse->1, "^";
    print "Contenido: ";
    
    for (i = 0: i < parse->1: i++) {
        print "'", (address) SpanishGetWordAt(i), "'";
        if (i < parse->1 - 1) print " ";
    }
    print "^";
    
    print "Estadísticas:^";
    print "• Verbos: ", SpanishCountWordsOfType(1), "^";
    print "• Objetos: ", SpanishCountWordsOfType(2), "^";
    print "• Preposiciones: ", SpanishCountWordsOfType(3), "^";
    print "• Artículos: ", SpanishCountWordsOfType(4), "^";
    print "• Adjetivos: ", SpanishCountWordsOfType(5), "^";
    print "• Complejidad: ", SpanishGetCommandComplexity(), "^";
];

[ SpanishDebugManipulation operation pos word;
    ! Debug de operaciones de manipulación
    print "[PARSER] ";
    switch(operation) {
        1: print "Removiendo palabra en pos ", pos, ": '", (address) word, "'";
        2: print "Insertando palabra en pos ", pos, ": '", (address) word, "'";
        3: print "Reemplazando palabra en pos ", pos, ": '", (address) word, "'";
        4: print "Normalizando buffer";
        5: print "Expandiendo abreviaciones";
        6: print "Reordenando palabras";
    }
    print "^";
];
#Endif;

! ==============================================================================
! CONSTANTES DE FINALIZACIÓN PARTE 1
! ==============================================================================

Constant SPANISH_PARSER_PART1_COMPLETE;
Constant SPANISH_PARSER_MANIPULATION_READY;

! Información de la Parte 1
Constant SPANISH_PARSER_PART1_FEATURES = "Manipulación segura, normalización, expansión, clasificación, validación";

! ==============================================================================
! Fin de SpanishParser.h - Parte 1: Fundamentos y Manipulación
! ==============================================================================