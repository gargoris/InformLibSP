! ==============================================================================
! SPANISHPARSER.H - Parser Core para la librería española de Inform 6
! Compatible con Inform 6.42 y librería estándar 6.12.7
! 
! MÓDULO CORE: Funcionalidades esenciales de parsing en español
! Extraído del monolito Spanish-fase1.h siguiendo arquitectura modular
! ==============================================================================

System_file;

#Ifndef SPANISH_PARSER_INCLUDED;
Constant SPANISH_PARSER_INCLUDED;
Constant SPANISH_PARSER_VERSION = "1.0-core";

! Verificación de dependencias
#Ifdef LIBRARY_STAGE;
#Iffalse LIBRARY_STAGE >= AFTER_PARSER;
  Message fatalerror "*** Include Parser.h y VerbLib.h antes de SpanishParser.h ***";
#Endif;
#Endif;

! ==============================================================================
! CONSTANTES DE PARSING ESPAÑOL
! ==============================================================================

! Palabras especiales del parser español
Constant SPANISH_ALL1__WD   = 'todo';
Constant SPANISH_ALL2__WD   = 'todos';
Constant SPANISH_ALL3__WD   = 'todas';
Constant SPANISH_ALL4__WD   = 'cada';
Constant SPANISH_AND1__WD   = 'y';
Constant SPANISH_AND2__WD   = 'e';
Constant SPANISH_BUT1__WD   = 'menos';
Constant SPANISH_BUT2__WD   = 'excepto';
Constant SPANISH_BUT3__WD   = 'salvo';
Constant SPANISH_ME1__WD    = 'yo';
Constant SPANISH_ME2__WD    = 'mi';
Constant SPANISH_ME3__WD    = 'me';
Constant SPANISH_OF1__WD    = 'de';
Constant SPANISH_OF2__WD    = 'del';
Constant SPANISH_OF3__WD    = 'de_la';
Constant SPANISH_OF4__WD    = 'de_los';
Constant SPANISH_OTHER1__WD = 'otro';
Constant SPANISH_OTHER2__WD = 'otra';
Constant SPANISH_OTHER3__WD = 'otros';
Constant SPANISH_THEN1__WD  = 'luego';
Constant SPANISH_THEN2__WD  = 'después';
Constant SPANISH_THEN3__WD  = 'entonces';

! Constantes para tipos de preposiciones
Constant PREP_SIMPLE = 1;
Constant PREP_COMPOUND_START = 2;
Constant PREP_COMPOUND_MIDDLE = 3;
Constant PREP_COMPOUND_END = 4;

! Constantes para análisis sintáctico
Constant SPANISH_VERB_POSITION = 1;
Constant SPANISH_OBJECT_POSITION = 2;
Constant SPANISH_PREPOSITION_POSITION = 3;
Constant SPANISH_SECONDARY_OBJECT_POSITION = 4;

! ==============================================================================
! VARIABLES GLOBALES DE PARSING
! ==============================================================================

Global spanish_parse_stage = 0;
Global spanish_last_verb = 0;
Global spanish_compound_prep_found = 0;
Global spanish_contraction_processed = 0;
Global spanish_parse_errors = 0;

! Buffer para almacenar parsing intermedio
Array spanish_parse_buffer --> 64;
Array spanish_temp_parse --> 32;

! ==============================================================================
! RUTINAS DE MANIPULACIÓN DE PALABRAS
! ==============================================================================

[ SpanishRemoveWord pos   i;
    ! Elimina una palabra del buffer de parsing
    if (pos < 0 || pos >= parse->1) return false;
    
    for (i = pos: i < parse->1 - 1: i++) {
        parse-->(2*i+1) = parse-->(2*(i+1)+1);
        parse-->(2*i+2) = parse-->(2*(i+1)+2);
    }
    parse->1 = parse->1 - 1;
    return true;
];

[ SpanishInsertWord pos word dict_value   i;
    ! Inserta una palabra en el buffer de parsing
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
    ! Obtiene la palabra en una posición específica
    if (pos < 0 || pos >= parse->1) return 0;
    return parse-->(2*pos+1);
];

[ SpanishGetDictValueAt pos;
    ! Obtiene el valor de diccionario en una posición específica
    if (pos < 0 || pos >= parse->1) return 0;
    return parse-->(2*pos+2);
];

! ==============================================================================
! PROCESAMIENTO DE PREPOSICIONES COMPUESTAS
! ==============================================================================

[ SpanishProcessCompoundPrepositions   i j k l result;
    ! Procesa preposiciones compuestas españolas complejas
    spanish_compound_prep_found = 0;
    result = 0;
    
    for (i = 0: i < parse->1 - 1: i++) {
        j = SpanishGetWordAt(i);
        k = SpanishGetWordAt(i+1);
        
        ! Preposiciones de dos palabras
        if (SpanishProcessTwoWordPrepositions(i, j, k)) {
            result++;
            continue;
        }
        
        ! Preposiciones de tres palabras (al lado de, etc.)
        if (i < parse->1 - 2) {
            l = SpanishGetWordAt(i+2);
            if (SpanishProcessThreeWordPrepositions(i, j, k, l)) {
                result++;
                continue;
            }
        }
    }
    
    spanish_compound_prep_found = result;
    return result;
];

[ SpanishProcessTwoWordPrepositions pos word1 word2;
    ! Procesa preposiciones compuestas de dos palabras
    
    ! debajo de
    if (word1 == 'debajo' && word2 == 'de') {
        SpanishReplaceWord(pos, 'debajo_de', 1);
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! encima de
    if (word1 == 'encima' && word2 == 'de') {
        SpanishReplaceWord(pos, 'encima_de', 1);
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! cerca de
    if (word1 == 'cerca' && word2 == 'de') {
        SpanishReplaceWord(pos, 'cerca_de', 1);
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! lejos de
    if (word1 == 'lejos' && word2 == 'de') {
        SpanishReplaceWord(pos, 'lejos_de', 1);
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! delante de
    if (word1 == 'delante' && word2 == 'de') {
        SpanishReplaceWord(pos, 'delante_de', 1);
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! detrás de  
    if (word1 == 'detrás' && word2 == 'de') {
        SpanishReplaceWord(pos, 'detrás_de', 1);
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! dentro de
    if (word1 == 'dentro' && word2 == 'de') {
        SpanishReplaceWord(pos, 'dentro_de', 1);
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! fuera de
    if (word1 == 'fuera' && word2 == 'de') {
        SpanishReplaceWord(pos, 'fuera_de', 1);
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! a través de
    if (word1 == 'a' && word2 == 'través') {
        SpanishReplaceWord(pos, 'a_través', 1);
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! alrededor de
    if (word1 == 'alrededor' && word2 == 'de') {
        SpanishReplaceWord(pos, 'alrededor_de', 1);
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    return false;
];

[ SpanishProcessThreeWordPrepositions pos word1 word2 word3;
    ! Procesa preposiciones compuestas de tres palabras
    
    ! al lado de
    if (word1 == 'al' && word2 == 'lado' && word3 == 'de') {
        SpanishReplaceWord(pos, 'al_lado_de', 1);
        SpanishRemoveWord(pos+1);
        SpanishRemoveWord(pos+1); ! pos+1 porque ya removimos una
        return true;
    }
    
    ! a través de
    if (word1 == 'a_través' && word2 == 'de') {
        SpanishReplaceWord(pos, 'a_través_de', 1);
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! en frente de
    if (word1 == 'en' && word2 == 'frente' && word3 == 'de') {
        SpanishReplaceWord(pos, 'en_frente_de', 1);
        SpanishRemoveWord(pos+1);
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! por encima de
    if (word1 == 'por' && word2 == 'encima' && word3 == 'de') {
        SpanishReplaceWord(pos, 'por_encima_de', 1);
        SpanishRemoveWord(pos+1);
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! por debajo de
    if (word1 == 'por' && word2 == 'debajo' && word3 == 'de') {
        SpanishReplaceWord(pos, 'por_debajo_de', 1);
        SpanishRemoveWord(pos+1);
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    return false;
];

! ==============================================================================
! PROCESAMIENTO DE CONTRACCIONES
! ==============================================================================

[ SpanishProcessContractions   i j k result;
    ! Procesa contracciones españolas (del, al)
    spanish_contraction_processed = 0;
    result = 0;
    
    for (i = 0: i < parse->1: i++) {
        j = SpanishGetWordAt(i);
        
        ! Procesar "del" = "de" + "el"
        if (j == 'del') {
            SpanishReplaceWord(i, 'de', 1);
            SpanishInsertWord(i+1, 'el', 1);
            result++;
            i++; ! Saltar la palabra insertada
            continue;
        }
        
        ! Procesar "al" = "a" + "el"
        if (j == 'al') {
            SpanishReplaceWord(i, 'a', 1);
            SpanishInsertWord(i+1, 'el', 1);
            result++;
            i++; ! Saltar la palabra insertada
            continue;
        }
    }
    
    spanish_contraction_processed = result;
    return result;
];

! ==============================================================================
! PROCESAMIENTO DE PALABRAS SUPERFLUAS
! ==============================================================================

[ SpanishRemoveSuperfluousWords   i j k removed;
    ! Elimina palabras que no aportan significado al comando
    removed = 0;
    
    for (i = 0: i < parse->1: i++) {
        j = SpanishGetWordAt(i);
        
        ! Eliminar "que" en contextos no relevantes
        if (j == 'que') {
            if (SpanishShouldRemoveQue(i)) {
                SpanishRemoveWord(i);
                removed++;
                i--; ! Ajustar índice tras eliminación
                continue;
            }
        }
        
        ! Eliminar artículos innecesarios en ciertos contextos
        if (j == 'el' or 'la' or 'los' or 'las') {
            if (SpanishShouldRemoveArticle(i)) {
                SpanishRemoveWord(i);
                removed++;
                i--; ! Ajustar índice tras eliminación
                continue;
            }
        }
        
        ! Eliminar muletillas
        if (j == 'por_favor' or 'porfavor') {
            SpanishRemoveWord(i);
            removed++;
            i--; ! Ajustar índice tras eliminación
            continue;
        }
    }
    
    return removed;
];

[ SpanishShouldRemoveQue pos   prev_word;
    ! Determina si "que" debe eliminarse según el contexto
    if (pos == 0) return true; ! "Que" al inicio generalmente sobra
    
    prev_word = SpanishGetWordAt(pos-1);
    
    ! No eliminar después de verbos declarativos
    if (prev_word == 'preguntar' or 'decir' or 'saber' or 'esperar' or 'querer' 
                  or 'pedir' or 'creer' or 'pensar' or 'contar') {
        return false;
    }
    
    ! En otros contextos, probablemente sobra
    return true;
];

[ SpanishShouldRemoveArticle pos   next_word prev_word;
    ! Determina si un artículo debe eliminarse
    if (pos >= parse->1 - 1) return false; ! No hay palabra siguiente
    
    next_word = SpanishGetWordAt(pos+1);
    
    ! No eliminar si va seguido de nombre propio
    if (next_word has proper) return false;
    
    ! No eliminar en construcciones "todo el/la/los/las"
    if (pos > 0) {
        prev_word = SpanishGetWordAt(pos-1);
        if (prev_word == 'todo' or 'toda' or 'todos' or 'todas') return false;
    }
    
    ! En general, mantener artículos
    return false;
];

! ==============================================================================
! ANÁLISIS SINTÁCTICO ESPAÑOL
! ==============================================================================

[ SpanishAnalyzeSyntax   i verb_found obj_found prep_found;
    ! Analiza la estructura sintáctica del comando en español
    verb_found = false;
    obj_found = false;
    prep_found = false;
    
    for (i = 0: i < parse->1: i++) {
        ! Identificar verbo principal
        if (~~verb_found && SpanishIsVerbCandidate(i)) {
            spanish_last_verb = SpanishGetWordAt(i);
            verb_found = true;
            continue;
        }
        
        ! Identificar objetos
        if (verb_found && ~~prep_found && SpanishIsObjectCandidate(i)) {
            obj_found = true;
            continue;
        }
        
        ! Identificar preposiciones
        if (SpanishIsPrepositionCandidate(i)) {
            prep_found = true;
            continue;
        }
    }
    
    return (verb_found ? 1 : 0) + (obj_found ? 2 : 0) + (prep_found ? 4 : 0);
];

[ SpanishIsVerbCandidate pos   word;
    ! Determina si una palabra puede ser un verbo
    word = SpanishGetWordAt(pos);
    
    ! Usar la función existente del sistema principal
    return LanguageIsVerb(word);
];

[ SpanishIsObjectCandidate pos   word;
    ! Determina si una palabra puede ser un objeto
    word = SpanishGetWordAt(pos);
    
    ! Verificar si es una palabra reconocida en el diccionario
    if (word == 0) return false;
    
    ! Excluir preposiciones y artículos
    if (SpanishIsPreposition(word)) return false;
    if (SpanishIsArticle(word)) return false;
    
    return true;
];

[ SpanishIsPrepositionCandidate pos   word;
    ! Determina si una palabra es una preposición
    word = SpanishGetWordAt(pos);
    return SpanishIsPreposition(word);
];

[ SpanishIsPreposition word;
    ! Lista de preposiciones españolas
    if (word == 'a' or 'ante' or 'bajo' or 'con' or 'contra' or 'de' or 'desde' 
              or 'durante' or 'en' or 'entre' or 'hacia' or 'hasta' or 'mediante'
              or 'para' or 'por' or 'según' or 'sin' or 'sobre' or 'tras') return true;
              
    ! Preposiciones compuestas
    if (word == 'debajo_de' or 'encima_de' or 'cerca_de' or 'lejos_de' 
              or 'delante_de' or 'detrás_de' or 'dentro_de' or 'fuera_de'
              or 'al_lado_de' or 'a_través_de' or 'alrededor_de') return true;
              
    return false;
];

[ SpanishIsArticle word;
    ! Artículos españoles
    if (word == 'el' or 'la' or 'los' or 'las' or 'un' or 'una' or 'unos' or 'unas') return true;
    return false;
];

! ==============================================================================
! CORRECCIÓN AUTOMÁTICA DE ERRORES COMUNES
! ==============================================================================

[ SpanishAutoCorrectCommonErrors   i j corrections;
    ! Corrige errores comunes en comandos españoles
    corrections = 0;
    
    for (i = 0: i < parse->1: i++) {
        j = SpanishGetWordAt(i);
        
        ! Correcciones de ortografía comunes
        if (SpanishCorrectSpelling(i, j)) {
            corrections++;
            continue;
        }
        
        ! Correcciones de concordancia
        if (SpanishCorrectAgreement(i, j)) {
            corrections++;
            continue;
        }
    }
    
    return corrections;
];

[ SpanishCorrectSpelling pos word   corrected;
    ! Corrige errores ortográficos comunes
    corrected = 0;
    
    switch (word) {
        'cojer': ! Error común por "coger"
            SpanishReplaceWord(pos, 'coger', 1);
            corrected = 'coger';
        'aver': ! Error común por "a ver"
            SpanishReplaceWord(pos, 'a', 1);
            SpanishInsertWord(pos+1, 'ver', 1);
            corrected = 'a_ver';
        'haber': ! Confusión con "a ver"
            if (pos < parse->1 - 1 && SpanishGetWordAt(pos+1) ~= 'que') {
                SpanishReplaceWord(pos, 'a', 1);
                SpanishInsertWord(pos+1, 'ver', 1);
                corrected = 'a_ver';
            }
    }
    
    return corrected;
];

[ SpanishCorrectAgreement pos word;
    ! Corrige problemas de concordancia automáticamente
    ! Por ahora, implementación básica
    return 0;
];

! ==============================================================================
! VALIDACIÓN Y DEPURACIÓN
! ==============================================================================

[ SpanishValidateParsing   i errors;
    ! Valida que el parsing sea coherente
    errors = 0;
    spanish_parse_errors = 0;
    
    ! Verificar que no haya palabras nulas
    for (i = 0: i < parse->1: i++) {
        if (SpanishGetWordAt(i) == 0) {
            errors++;
        }
    }
    
    ! Verificar estructura básica del comando
    if (~~SpanishHasValidStructure()) {
        errors++;
    }
    
    spanish_parse_errors = errors;
    return errors;
];

[ SpanishHasValidStructure   i has_verb;
    ! Verifica que el comando tenga una estructura válida
    has_verb = false;
    
    for (i = 0: i < parse->1: i++) {
        if (SpanishIsVerbCandidate(i)) {
            has_verb = true;
            break;
        }
    }
    
    return has_verb;
];

#Ifdef DEBUG;
[ SpanishDebugParsing   i;
    ! Muestra información de depuración del parsing
    print "^[DEBUG] Parsing español:^";
    print "Palabras procesadas: ", parse->1, "^";
    print "Contracciones: ", spanish_contraction_processed, "^";
    print "Preposiciones compuestas: ", spanish_compound_prep_found, "^";
    print "Errores: ", spanish_parse_errors, "^";
    
    print "Buffer actual: ";
    for (i = 0: i < parse->1: i++) {
        print "'", (address) SpanishGetWordAt(i), "' ";
    }
    print "^";
];
#Endif;

! ==============================================================================
! RUTINA PRINCIPAL DE PROCESAMIENTO
! ==============================================================================

[ SpanishParserMain   stage1_result stage2_result stage3_result total_changes;
    ! Rutina principal que coordina todo el procesamiento
    spanish_parse_stage = 1;
    
    ! Etapa 1: Procesamiento de preposiciones compuestas
    stage1_result = SpanishProcessCompoundPrepositions();
    
    ! Etapa 2: Procesamiento de contracciones
    spanish_parse_stage = 2;
    stage2_result = SpanishProcessContractions();
    
    ! Etapa 3: Eliminación de palabras superfluas
    spanish_parse_stage = 3;
    stage3_result = SpanishRemoveSuperfluousWords();
    
    ! Etapa 4: Análisis sintáctico
    spanish_parse_stage = 4;
    SpanishAnalyzeSyntax();
    
    ! Etapa 5: Corrección automática
    spanish_parse_stage = 5;
    SpanishAutoCorrectCommonErrors();
    
    ! Etapa 6: Validación final
    spanish_parse_stage = 6;
    SpanishValidateParsing();
    
    total_changes = stage1_result + stage2_result + stage3_result;
    
    #Ifdef DEBUG;
        if (total_changes > 0) SpanishDebugParsing();
    #Endif;
    
    return total_changes;
];

! ==============================================================================
! RUTINAS DE INTEGRACIÓN CON SISTEMA PRINCIPAL
! ==============================================================================

[ SpanishParserInitialize;
    ! Inicialización del sistema de parsing
    spanish_parse_stage = 0;
    spanish_last_verb = 0;
    spanish_compound_prep_found = 0;
    spanish_contraction_processed = 0;
    spanish_parse_errors = 0;
    
    print "[Parser español inicializado: preposiciones compuestas, contracciones, corrección automática]^";
];

[ SpanishParserVersion;
    ! Información de versión
    print "SpanishParser.h v", (string) SPANISH_PARSER_VERSION;
    print " - Compatible con Inform 6.42+^";
];

! ==============================================================================
! CONSTANTES DE FINALIZACIÓN
! ==============================================================================

Constant SPANISH_PARSER_COMPLETE;
Constant SPANISH_CORE_FEATURES = "Preposiciones compuestas, contracciones, análisis sintáctico, corrección automática";

#Endif; ! SPANISH_PARSER_INCLUDED

! ==============================================================================
! Fin de SpanishParser.h - Núcleo de parsing avanzado en español
! ==============================================================================