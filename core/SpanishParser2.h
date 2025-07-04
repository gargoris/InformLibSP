! ==============================================================================
! SPANISHPARSER.H - PARTE 2: PROCESAMIENTO AVANZADO
! Preposiciones compuestas, contracciones y eliminacion de palabras superfluas
! Parte del sistema modular Spanish Library para Inform 6
! Compatible con Inform 6.42 y libreria estandar 6.12.7
! ==============================================================================

! Requiere que la Parte 1 ya este incluida
#Ifndef SPANISH_PARSER_PART1_COMPLETE;
  Message fatalerror "*** Include SpanishParser Parte 1 antes de Parte 2 ***";
#Endif;

! ==============================================================================
! PROCESAMIENTO DE PREPOSICIONES COMPUESTAS - EXPANDIDO
! ==============================================================================

[ SpanishProcessCompoundPrepositions   i j k l result;
    ! Procesa preposiciones compuestas espanolas complejas
    spanish_compound_prep_found = 0;
    result = 0;
    
    #Ifdef DEBUG;
        print "[PARSER] Iniciando procesamiento de preposiciones compuestas^";
    #Endif;
    
    ! Procesar de izquierda a derecha para evitar conflictos
    for (i = 0: i < parse->1 - 1: i++) {
        j = SpanishGetWordAt(i);
        k = SpanishGetWordAt(i+1);
        
        ! Preposiciones de dos palabras
        if (SpanishProcessTwoWordPrepositions(i, j, k)) {
            result++;
            #Ifdef DEBUG;
                SpanishDebugManipulation(6, i, j);
            #Endif;
            continue; ! i ya se ajusto automaticamente
        }
        
        ! Preposiciones de tres palabras (verificar que hay suficientes palabras)
        if (i < parse->1 - 2) {
            l = SpanishGetWordAt(i+2);
            if (SpanishProcessThreeWordPrepositions(i, j, k, l)) {
                result++;
                #Ifdef DEBUG;
                    SpanishDebugManipulation(6, i, j);
                #Endif;
                continue; ! i ya se ajusto automaticamente
            }
        }
    }
    
    spanish_compound_prep_found = result;
    
    #Ifdef DEBUG;
        if (result > 0) {
            print "[PARSER] Procesadas ", result, " preposiciones compuestas^";
        }
    #Endif;
    
    return result;
];

[ SpanishProcessTwoWordPrepositions pos word1 word2;
    ! Procesa preposiciones compuestas de dos palabras
    
    ! debajo de
    if (word1 == 'debajo' && word2 == 'de') {
        SpanishReplaceWord(pos, 'debajo_de', 'debajo_de');
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! encima de
    if (word1 == 'encima' && word2 == 'de') {
        SpanishReplaceWord(pos, 'encima_de', 'encima_de');
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! cerca de
    if (word1 == 'cerca' && word2 == 'de') {
        SpanishReplaceWord(pos, 'cerca_de', 'cerca_de');
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! lejos de
    if (word1 == 'lejos' && word2 == 'de') {
        SpanishReplaceWord(pos, 'lejos_de', 'lejos_de');
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! delante de
    if (word1 == 'delante' && word2 == 'de') {
        SpanishReplaceWord(pos, 'delante_de', 'delante_de');
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! detras de  
    if (word1 == 'detras' && word2 == 'de') {
        SpanishReplaceWord(pos, 'detras_de', 'detras_de');
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! dentro de
    if (word1 == 'dentro' && word2 == 'de') {
        SpanishReplaceWord(pos, 'dentro_de', 'dentro_de');
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! fuera de
    if (word1 == 'fuera' && word2 == 'de') {
        SpanishReplaceWord(pos, 'fuera_de', 'fuera_de');
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! a traves (primera parte - se completara en 3 palabras)
    if (word1 == 'a' && word2 == 'traves') {
        SpanishReplaceWord(pos, 'a_traves', 'a_traves');
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! alrededor de
    if (word1 == 'alrededor' && word2 == 'de') {
        SpanishReplaceWord(pos, 'alrededor_de', 'alrededor_de');
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! en frente (primera parte)
    if (word1 == 'en' && word2 == 'frente') {
        SpanishReplaceWord(pos, 'en_frente', 'en_frente');
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! por encima (primera parte)
    if (word1 == 'por' && word2 == 'encima') {
        SpanishReplaceWord(pos, 'por_encima', 'por_encima');
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! por debajo (primera parte)
    if (word1 == 'por' && word2 == 'debajo') {
        SpanishReplaceWord(pos, 'por_debajo', 'por_debajo');
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! en medio (primera parte)
    if (word1 == 'en' && word2 == 'medio') {
        SpanishReplaceWord(pos, 'en_medio', 'en_medio');
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! a causa (primera parte)
    if (word1 == 'a' && word2 == 'causa') {
        SpanishReplaceWord(pos, 'a_causa', 'a_causa');
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    return false;
];

[ SpanishProcessThreeWordPrepositions pos word1 word2 word3;
    ! Procesa preposiciones compuestas de tres palabras
    
    ! al lado de
    if (word1 == 'al' && word2 == 'lado' && word3 == 'de') {
        SpanishReplaceWord(pos, 'al_lado_de', 'al_lado_de');
        SpanishRemoveWord(pos+1);
        SpanishRemoveWord(pos+1); ! pos+1 porque ya removimos una
        return true;
    }
    
    ! a traves de (completar)
    if (word1 == 'a_traves' && word2 == 'de') {
        SpanishReplaceWord(pos, 'a_traves_de', 'a_traves_de');
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! en frente de (completar)
    if (word1 == 'en_frente' && word2 == 'de') {
        SpanishReplaceWord(pos, 'en_frente_de', 'en_frente_de');
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! por encima de (completar)
    if (word1 == 'por_encima' && word2 == 'de') {
        SpanishReplaceWord(pos, 'por_encima_de', 'por_encima_de');
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! por debajo de (completar)
    if (word1 == 'por_debajo' && word2 == 'de') {
        SpanishReplaceWord(pos, 'por_debajo_de', 'por_debajo_de');
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! en lugar de
    if (word1 == 'en' && word2 == 'lugar' && word3 == 'de') {
        SpanishReplaceWord(pos, 'en_lugar_de', 'en_lugar_de');
        SpanishRemoveWord(pos+1);
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! en vez de
    if (word1 == 'en' && word2 == 'vez' && word3 == 'de') {
        SpanishReplaceWord(pos, 'en_vez_de', 'en_vez_de');
        SpanishRemoveWord(pos+1);
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! en medio de (completar)
    if (word1 == 'en_medio' && word2 == 'de') {
        SpanishReplaceWord(pos, 'en_medio_de', 'en_medio_de');
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! a causa de (completar)
    if (word1 == 'a_causa' && word2 == 'de') {
        SpanishReplaceWord(pos, 'a_causa_de', 'a_causa_de');
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! a pesar de
    if (word1 == 'a' && word2 == 'pesar' && word3 == 'de') {
        SpanishReplaceWord(pos, 'a_pesar_de', 'a_pesar_de');
        SpanishRemoveWord(pos+1);
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    ! en contra de
    if (word1 == 'en' && word2 == 'contra' && word3 == 'de') {
        SpanishReplaceWord(pos, 'en_contra_de', 'en_contra_de');
        SpanishRemoveWord(pos+1);
        SpanishRemoveWord(pos+1);
        return true;
    }
    
    return false;
];

! ==============================================================================
! PROCESAMIENTO DE CONTRACCIONES - MEJORADO
! ==============================================================================

[ SpanishProcessContractions   i j result changed max_iterations;
    ! Procesa contracciones espanolas (del, al) de forma robusta
    spanish_contraction_processed = 0;
    result = 0;
    changed = true;
    max_iterations = 5; ! Prevenir loops infinitos
    
    #Ifdef DEBUG;
        print "[PARSER] Iniciando procesamiento de contracciones^";
    #Endif;
    
    ! Procesar multiples pasadas hasta que no haya cambios
    while (changed && max_iterations > 0) {
        changed = false;
        max_iterations--;
        
        for (i = 0: i < parse->1: i++) {
            j = SpanishGetWordAt(i);
            
            ! Procesar "del" = "de" + "el"
            if (j == 'del') {
                SpanishReplaceWord(i, 'de', 'de');
                SpanishInsertWord(i+1, 'el', 'el');
                result++;
                changed = true;
                #Ifdef DEBUG;
                    print "[PARSER] Contraccion: del -> de + el^";
                #Endif;
                i++; ! Saltar la palabra insertada
                continue;
            }
            
            ! Procesar "al" = "a" + "el"
            if (j == 'al') {
                SpanishReplaceWord(i, 'a', 'a');
                SpanishInsertWord(i+1, 'el', 'el');
                result++;
                changed = true;
                #Ifdef DEBUG;
                    print "[PARSER] Contraccion: al -> a + el^";
                #Endif;
                i++; ! Saltar la palabra insertada
                continue;
            }
            
            ! Contracciones pronominales
            if (j == 'conmigo') {
                SpanishReplaceWord(i, 'con', 'con');
                SpanishInsertWord(i+1, 'mi', 'mi');
                result++;
                changed = true;
                #Ifdef DEBUG;
                    print "[PARSER] Contraccion: conmigo -> con + mi^";
                #Endif;
                i++; ! Saltar la palabra insertada
                continue;
            }
            
            if (j == 'contigo') {
                SpanishReplaceWord(i, 'con', 'con');
                SpanishInsertWord(i+1, 'ti', 'ti');
                result++;
                changed = true;
                #Ifdef DEBUG;
                    print "[PARSER] Contraccion: contigo -> con + ti^";
                #Endif;
                i++; ! Saltar la palabra insertada
                continue;
            }
            
            if (j == 'consigo') {
                SpanishReplaceWord(i, 'con', 'con');
                SpanishInsertWord(i+1, 'si', 'si');
                result++;
                changed = true;
                #Ifdef DEBUG;
                    print "[PARSER] Contraccion: consigo -> con + si^";
                #Endif;
                i++; ! Saltar la palabra insertada
                continue;
            }
        }
    }
    
    spanish_contraction_processed = result;
    
    #Ifdef DEBUG;
        if (result > 0) {
            print "[PARSER] Procesadas ", result, " contracciones^";
        }
    #Endif;
    
    return result;
];

! ==============================================================================
! PROCESAMIENTO DE PALABRAS SUPERFLUAS - EXPANDIDO
! ==============================================================================

[ SpanishRemoveSuperfluousWords   i j removed;
    ! Elimina palabras que no aportan significado al comando
    removed = 0;
    
    #Ifdef DEBUG;
        print "[PARSER] Iniciando eliminacion de palabras superfluas^";
    #Endif;
    
    i = 0;
    while (i < parse->1) {
        j = SpanishGetWordAt(i);
        
        ! Eliminar "que" en contextos no relevantes
        if (j == 'que') {
            if (SpanishShouldRemoveQue(i)) {
                #Ifdef DEBUG;
                    print "[PARSER] Eliminando 'que' superfluo en posicion ", i, "^";
                #Endif;
                SpanishRemoveWord(i);
                removed++;
                continue; ! No incrementar i
            }
        }
        
        ! Eliminar muletillas y palabras de cortesia
        if (j == 'por_favor' or 'porfavor' or 'porfa' or 'please') {
            #Ifdef DEBUG;
                print "[PARSER] Eliminando muletilla de cortesia: ", (address) j, "^";
            #Endif;
            SpanishRemoveWord(i);
            removed++;
            continue;
        }
        
        if (j == 'gracias' or 'gracias.' or 'thanks' or 'thx') {
            #Ifdef DEBUG;
                print "[PARSER] Eliminando agradecimiento: ", (address) j, "^";
            #Endif;
            SpanishRemoveWord(i);
            removed++;
            continue;
        }
        
        ! Eliminar interjecciones comunes
        if (j == 'eh' or 'este' or 'bueno' or 'pues' or 'bien' or 'ah' or 'oh') {
            #Ifdef DEBUG;
                print "[PARSER] Eliminando interjeccion: ", (address) j, "^";
            #Endif;
            SpanishRemoveWord(i);
            removed++;
            continue;
        }
        
        ! Eliminar expresiones de inicio de frase
        if (j == 'mira' or 'oye' or 'escucha' or 'atiende') {
            if (SpanishShouldRemoveInterjection(i)) {
                #Ifdef DEBUG;
                    print "[PARSER] Eliminando expresion de inicio: ", (address) j, "^";
                #Endif;
                SpanishRemoveWord(i);
                removed++;
                continue;
            }
        }
        
        ! Eliminar articulos redundantes en algunos contextos
        if (j == 'el' or 'la' or 'los' or 'las') {
            if (SpanishShouldRemoveArticle(i)) {
                #Ifdef DEBUG;
                    print "[PARSER] Eliminando articulo redundante: ", (address) j, "^";
                #Endif;
                SpanishRemoveWord(i);
                removed++;
                continue;
            }
        }
        
        ! Eliminar preposiciones redundantes
        if (j == 'de' or 'en' or 'con' or 'para') {
            if (SpanishShouldRemovePreposition(i)) {
                #Ifdef DEBUG;
                    print "[PARSER] Eliminando preposicion redundante: ", (address) j, "^";
                #Endif;
                SpanishRemoveWord(i);
                removed++;
                continue;
            }
        }
        
        i++; ! Solo incrementar si no se elimino nada
    }
    
    spanish_words_removed = spanish_words_removed + removed;
    
    #Ifdef DEBUG;
        if (removed > 0) {
            print "[PARSER] Eliminadas ", removed, " palabras superfluas^";
        }
    #Endif;
    
    return removed;
];

[ SpanishShouldRemoveQue pos   prev_word next_word;
    ! Determina si "que" debe eliminarse segun el contexto
    if (pos == 0) return true; ! "Que" al inicio generalmente sobra
    
    prev_word = 0;
    next_word = 0;
    
    if (pos > 0) prev_word = SpanishGetWordAt(pos-1);
    if (pos < parse->1 - 1) next_word = SpanishGetWordAt(pos+1);
    
    ! No eliminar despues de verbos declarativos
    if (prev_word == 'preguntar' or 'decir' or 'saber' or 'esperar' or 'querer' 
                  or 'pedir' or 'creer' or 'pensar' or 'contar' or 'explicar'
                  or 'afirmar' or 'negar' or 'dudar' or 'suponer') {
        return false;
    }
    
    ! No eliminar en construcciones comparativas
    if (prev_word == 'mas' or 'menos' or 'mejor' or 'peor' or 'mayor' or 'menor') {
        return false;
    }
    
    ! No eliminar en construcciones temporales
    if (prev_word == 'antes' or 'despues' or 'mientras' or 'cuando') {
        return false;
    }
    
    ! En otros contextos, probablemente sobra
    return true;
];

[ SpanishShouldRemoveArticle pos   next_word prev_word;
    ! Determina si un articulo debe eliminarse
    if (pos >= parse->1 - 1) return false; ! No hay palabra siguiente
    
    next_word = SpanishGetWordAt(pos+1);
    prev_word = 0;
    if (pos > 0) prev_word = SpanishGetWordAt(pos-1);
    
    ! No eliminar si va seguido de nombre propio
    ! (Simplified check - 'has' only works with objects, not words)
    ! if (next_word has proper) return false;
    
    ! No eliminar en construcciones "todo el/la/los/las"
    if (prev_word == 'todo' or 'toda' or 'todos' or 'todas') return false;
    
    ! No eliminar despues de preposiciones importantes
    if (prev_word == 'hacia' or 'hasta' or 'desde' or 'contra') return false;
    
    ! En comandos muy cortos, mantener articulos
    if (parse->1 <= 3) return false;
    
    ! En general, mantener articulos (politica conservadora)
    return false;
];

[ SpanishShouldRemovePreposition pos   next_word prev_word;
    ! Determina si una preposicion debe eliminarse
    if (pos >= parse->1 - 1) return false; ! No hay palabra siguiente
    if (pos == 0) return false; ! Preposicion al inicio es importante
    
    next_word = SpanishGetWordAt(pos+1);
    prev_word = SpanishGetWordAt(pos-1);
    
    ! No eliminar preposiciones que conectan objetos importantes
    return false; ! Politica muy conservadora por ahora
];

[ SpanishShouldRemoveInterjection pos   next_word;
    ! Determina si una interjeccion de inicio debe eliminarse
    if (pos ~= 0) return false; ! Solo al inicio de frase
    if (parse->1 <= 2) return false; ! Frase muy corta
    
    ! Si hay un verbo despues, probablemente es interjeccion
    if (pos < parse->1 - 1) {
        next_word = SpanishGetWordAt(pos+1);
        if (SpanishIsVerbCandidate(pos+1)) return true;
    }
    
    return false;
];

! ==============================================================================
! RUTINAS DE ANALISIS DE CONTEXTO
! ==============================================================================

[ SpanishAnalyzeContext pos   prev_word next_word context;
    ! Analiza el contexto de una palabra para decidir procesamiento
    context = 0;
    prev_word = 0;
    next_word = 0;
    
    if (pos > 0) prev_word = SpanishGetWordAt(pos-1);
    if (pos < parse->1 - 1) next_word = SpanishGetWordAt(pos+1);
    
    ! Contexto de verbo
    if (SpanishIsVerbCandidate(pos-1)) context = context | 1;
    if (SpanishIsVerbCandidate(pos+1)) context = context | 2;
    
    ! Contexto de objeto
    if (SpanishIsObjectCandidate(pos-1)) context = context | 4;
    if (SpanishIsObjectCandidate(pos+1)) context = context | 8;
    
    ! Contexto de preposicion
    if (SpanishIsPreposition(prev_word)) context = context | 16;
    if (SpanishIsPreposition(next_word)) context = context | 32;
    
    return context;
];

[ SpanishGetWordImportance pos   word importance context;
    ! Determina la importancia de una palabra para el comando
    word = SpanishGetWordAt(pos);
    importance = 0;
    context = SpanishAnalyzeContext(pos);
    
    ! Importancia alta para verbos
    if (SpanishIsVerbCandidate(pos)) importance = importance + 10;
    
    ! Importancia alta para objetos
    if (SpanishIsObjectCandidate(pos)) importance = importance + 8;
    
    ! Importancia media para preposiciones
    if (SpanishIsPreposition(word)) importance = importance + 5;
    
    ! Importancia baja para articulos y muletillas
    if (SpanishIsArticle(word)) importance = importance + 2;
    if (word == 'que' or 'muy' or 'bastante') importance = importance + 1;
    
    ! Modificadores de contexto
    if (context & 1) importance = importance + 2; ! Despues de verbo
    if (context & 16) importance = inportance + 3; ! Despues de preposicion
    
    return importance;
];

! ==============================================================================
! CONSTANTES DE FINALIZACION PARTE 2
! ==============================================================================

Constant SPANISH_PARSER_PART2_COMPLETE;
Constant SPANISH_PARSER_ADVANCED_READY;

! Informacion de la Parte 2
Constant SPANISH_PARSER_PART2_FEATURES = "Preposiciones compuestas (20+), contracciones robustas, eliminacion inteligente";

! ==============================================================================
! Fin de SpanishParser.h - Parte 2: Procesamiento Avanzado
! ==============================================================================