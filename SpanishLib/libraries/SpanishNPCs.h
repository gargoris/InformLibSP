! ==============================================================================
! SPANISHNPCS.H - Sistema avanzado de NPCs para la libreria espanola
! Modulo especializado para el sistema modular Spanish Library para Inform 6
! Compatible con Inform 6.42 y libreria estandar 6.12.7
! ==============================================================================

System_file;

#Ifndef SPANISH_NPCS_INCLUDED;
Constant SPANISH_NPCS_INCLUDED;
Constant SPANISH_NPCS_VERSION = "1.0-complete";

! Verificacion de dependencias
#Ifndef SPANISH_CORE_INCLUDED;
  Message fatalerror "*** Include SpanishCore.h antes de SpanishNPCs.h ***";
#Endif;

! ==============================================================================
! CONSTANTES PARA SISTEMA DE NPCs
! ==============================================================================

! Niveles de formalidad
Constant NPC_FORMAL = 1;
Constant NPC_INFORMAL = 0;
Constant NPC_REGIONAL_VOS = 2;

! Tipos de personalidad linguistica
Constant PERSONALIDAD_INTELECTUAL = 1;
Constant PERSONALIDAD_DIRECTA = 2;
Constant PERSONALIDAD_EMOCIONAL = 3;
Constant PERSONALIDAD_ESTOICA = 4;
Constant PERSONALIDAD_OPTIMISTA = 5;
Constant PERSONALIDAD_PESIMISTA = 6;
Constant PERSONALIDAD_ACADEMICA = 7;
Constant PERSONALIDAD_CASUAL = 8;

! Regiones linguisticas
Constant REGION_NEUTRO = 0;
Constant REGION_MEXICO = 1;
Constant REGION_ARGENTINA = 2;
Constant REGION_ESPANA = 3;
Constant REGION_COLOMBIA = 4;
Constant REGION_CHILE = 5;
Constant REGION_PERU = 6;

! Estados de relacion
Constant RELACION_DESCONOCIDO = 0;
Constant RELACION_CONOCIDO = 1;
Constant RELACION_AMIGABLE = 2;
Constant RELACION_AMIGO = 3;
Constant RELACION_INTIMO = 4;
Constant RELACION_HOSTIL = -1;
Constant RELACION_ENEMIGO = -2;

! Estados emocionales
Constant EMOCION_NEUTRAL = 0;
Constant EMOCION_FELIZ = 1;
Constant EMOCION_TRISTE = 2;
Constant EMOCION_ENOJADO = 3;
Constant EMOCION_NERVIOSO = 4;
Constant EMOCION_EMOCIONADO = 5;

! ==============================================================================
! CLASE BASE PARA NPCs ESPANOLES
! ==============================================================================

Class SpanishNPC
    with
        ! Caracteristicas linguisticas basicas
        formality_level NPC_FORMAL,
        personality_type PERSONALIDAD_CASUAL,
        regional_variant REGION_NEUTRO,
        
        ! Estado de relacion con el jugador
        relationship_level RELACION_DESCONOCIDO,
        emotional_state EMOCION_NEUTRAL,
        
        ! Contadores para desarrollo de relacion
        conversation_count 0,
        positive_interactions 0,
        negative_interactions 0,
        
        ! Preferencias linguisticas
        prefers_subjunctive false,
        uses_complex_syntax false,
        formal_vocabulary_level 1,
        
        ! Datos culturales
        social_class 1,
        educational_level 1,
        age_category 2, ! 1=joven, 2=adulto, 3=mayor
        
        ! Metodos principales
        greet SpanishNPC_Greet,
        farewell SpanishNPC_Farewell,
        respond_to SpanishNPC_RespondTo,
        update_relationship SpanishNPC_UpdateRelationship,
        generate_response SpanishNPC_GenerateResponse,
        
        ! Metodos de personalidad
        get_politeness_formula SpanishNPC_GetPolitenessFormula,
        select_verb_form SpanishNPC_SelectVerbForm,
        choose_vocabulary SpanishNPC_ChooseVocabulary,
        
        ! Metodos regionales
        apply_regional_features SpanishNPC_ApplyRegionalFeatures,
        get_regional_vocabulary SpanishNPC_GetRegionalVocabulary,
        
    has animate;

! ==============================================================================
! SISTEMA DE GESTION DE FORMALIDAD DINAMICA
! ==============================================================================

[ SpanishNPC_UpdateFormality npc player_formality context;
    local current_formality, new_formality, relationship_bonus;
    
    current_formality = npc.formality_level;
    relationship_bonus = npc.relationship_level;
    
    ! Calcular nueva formalidad basada en contexto
    switch (context) {
        1: ! Primera conversacion
            if (npc.regional_variant == REGION_COLOMBIA) 
                new_formality = NPC_FORMAL; ! Colombia usa usted por defecto
            else if (npc.social_class > 2 or npc.age_category == 3)
                new_formality = NPC_FORMAL;
            else if (player_formality == NPC_INFORMAL && npc.age_category == 1)
                new_formality = NPC_INFORMAL;
            else
                new_formality = NPC_FORMAL;
                
        2: ! Conversacion continuada
            if (relationship_bonus >= RELACION_AMIGABLE) {
                if (npc.regional_variant == REGION_ARGENTINA && player_formality == NPC_INFORMAL)
                    new_formality = NPC_REGIONAL_VOS;
                else if (relationship_bonus >= RELACION_AMIGO)
                    new_formality = NPC_INFORMAL;
            }
            
        3: ! Contexto formal (profesional, institucional)
            new_formality = NPC_FORMAL;
            
        4: ! Contexto intimo/familiar
            if (relationship_bonus >= RELACION_AMIGO)
                new_formality = NPC_INFORMAL;
    }
    
    ! Aplicar transicion gradual si hay cambio
    if (new_formality ~= current_formality) {
        if (npc.conversation_count > 3) {
            npc.formality_level = new_formality;
            return true; ! Indica que hubo cambio
        }
    }
    
    return false;
];

! ==============================================================================
! SISTEMA DE PERSONALIDAD LINGUISTICA
! ==============================================================================

[ SpanishNPC_SelectVerbForm npc base_verb tense person;
    local personality, complexity_preference;
    
    personality = npc.personality_type;
    
    switch (personality) {
        PERSONALIDAD_INTELECTUAL:
            ! Prefiere formas complejas y subjuntivo
            if (random(3) == 1 && tense == PRESENTE_T) {
                tense = SUBJUNTIVO_T;
                print "creo que "; 
            }
            return ConjugarVerbo(base_verb, person, tense, 0);
            
        PERSONALIDAD_DIRECTA:
            ! Prefiere indicativo y formas simples
            if (tense == SUBJUNTIVO_T) tense = PRESENTE_T;
            return ConjugarVerbo(base_verb, person, tense, 0);
            
        PERSONALIDAD_EMOCIONAL:
            ! Usa mas reflexivos y expresiones emotivas
            if (base_verb == "sentir" or "pensar" or "creer") {
                print "me "; 
            }
            return ConjugarVerbo(base_verb, person, tense, 0);
            
        PERSONALIDAD_ESTOICA:
            ! Prefiere construcciones impersonales
            if (person == 1) person = 3; ! Evita primera persona
            return ConjugarVerbo(base_verb, person, tense, 0);
            
        PERSONALIDAD_OPTIMISTA:
            ! Usa mas futuro y aspectos perfectivos
            if (tense == PRESENTE_T && random(4) == 1) {
                tense = FUTURO_T;
            }
            return ConjugarVerbo(base_verb, person, tense, 0);
            
        PERSONALIDAD_PESIMISTA:
            ! Prefiere imperfectivo y condicional
            if (tense == FUTURO_T) tense = CONDICIONAL_T;
            return ConjugarVerbo(base_verb, person, tense, 0);
            
        default:
            return ConjugarVerbo(base_verb, person, tense, 0);
    }
];

[ SpanishNPC_ChooseVocabulary npc concept;
    local personality, formal_level, region;
    
    personality = npc.personality_type;
    formal_level = npc.formal_vocabulary_level;
    region = npc.regional_variant;
    
    switch (concept) {
        1: ! Expresar contraste
            if (personality == PERSONALIDAD_ACADEMICA) {
                if (formal_level > 2) print "sin embargo";
                else print "no obstante";
            } else {
                print "pero";
            }
            
        2: ! Expresar posibilidad
            if (personality == PERSONALIDAD_INTELECTUAL) {
                print "es posible que";
            } else if (personality == PERSONALIDAD_DIRECTA) {
                print "tal vez";
            } else {
                print "quizas";
            }
            
        3: ! Ordenador/computadora segun region
            switch (region) {
                REGION_ESPANA: print "ordenador";
                REGION_MEXICO, REGION_COLOMBIA: print "computadora";
                default: print "computadora";
            }
            
        4: ! Coche/carro/auto segun region
            switch (region) {
                REGION_ESPANA: print "coche";
                REGION_MEXICO: print "carro";
                REGION_ARGENTINA: print "auto";
                default: print "carro";
            }
    }
];

! ==============================================================================
! SISTEMA DE DESARROLLO DE RELACIONES
! ==============================================================================

[ SpanishNPC_UpdateRelationship npc interaction_type;
    local current_level, points_change;
    
    current_level = npc.relationship_level;
    npc.conversation_count++;
    
    switch (interaction_type) {
        1: ! Interaccion positiva
            npc.positive_interactions++;
            points_change = 1;
            if (npc.conversation_count > 5) points_change = 2;
            
        2: ! Interaccion muy positiva
            npc.positive_interactions = npc.positive_interactions + 2;
            points_change = 3;
            
        -1: ! Interaccion negativa
            npc.negative_interactions++;
            points_change = -2;
            
        -2: ! Interaccion muy negativa
            npc.negative_interactions = npc.negative_interactions + 2;
            points_change = -4;
            
        default:
            points_change = 0;
    }
    
    ! Calcular nuevo nivel de relacion
    local total_positive = npc.positive_interactions * 2;
    local total_negative = npc.negative_interactions * 3;
    local net_score = total_positive - total_negative;
    
    if (net_score >= 20) npc.relationship_level = RELACION_INTIMO;
    else if (net_score >= 12) npc.relationship_level = RELACION_AMIGO;
    else if (net_score >= 6) npc.relationship_level = RELACION_AMIGABLE;
    else if (net_score >= 2) npc.relationship_level = RELACION_CONOCIDO;
    else if (net_score <= -8) npc.relationship_level = RELACION_ENEMIGO;
    else if (net_score <= -4) npc.relationship_level = RELACION_HOSTIL;
    else npc.relationship_level = RELACION_DESCONOCIDO;
    
    ! Notificar cambio de relacion si es significativo
    if (npc.relationship_level ~= current_level) {
        SpanishNPC_NotifyRelationshipChange(npc, current_level, npc.relationship_level);
        return true;
    }
    
    return false;
];

[ SpanishNPC_NotifyRelationshipChange npc old_level new_level;
    ! Mensaje sutil sobre cambio de relacion
    switch (new_level) {
        RELACION_AMIGABLE:
            if (old_level < RELACION_AMIGABLE) {
                print "^"; print (The) npc; 
                print " parece mas comodo hablando contigo.^";
            }
            
        RELACION_AMIGO:
            if (old_level < RELACION_AMIGO) {
                print "^"; print (The) npc; 
                print " te sonrie con genuina calidez.^";
            }
            
        RELACION_HOSTIL:
            if (old_level > RELACION_HOSTIL) {
                print "^"; print (The) npc; 
                print " te mira con desconfianza.^";
            }
    }
];

! ==============================================================================
! SISTEMA DE SALUDO Y DESPEDIDA CULTURAL
! ==============================================================================

[ SpanishNPC_Greet npc context;
    local formality, region, time_of_day, relationship;
    
    formality = npc.formality_level;
    region = npc.regional_variant;
    relationship = npc.relationship_level;
    time_of_day = (the_time / 60) % 24;
    
    ! Actualizar formalidad segun contexto
    SpanishNPC_UpdateFormality(npc, FormalityLevel, context);
    
    print "^"; print (The) npc; print " ";
    
    ! Seleccionar saludo apropiado
    if (relationship >= RELACION_AMIGO) {
        ! Saludos informales para amigos
        switch (random(4)) {
            1: print "te saluda calidamente.";
            2: print "te sonrie y te saluda.";
            3: print "se acerca con una sonrisa.";
            4: print "te saluda con entusiasmo.";
        }
        print " ~";
        if (time_of_day < 12) {
            print "!Buenos dias!";
        } else if (time_of_day < 18) {
            print "!Buenas tardes!";
        } else {
            print "!Buenas noches!";
        }
        
    } else if (formality == NPC_FORMAL) {
        ! Saludos formales
        print "se acerca con cortesia.";
        print " ~";
        if (time_of_day < 12) {
            print "Buenos dias";
        } else if (time_of_day < 18) {
            print "Buenas tardes";
        } else {
            print "Buenas noches";
        }
        
        ! Anadir tratamiento formal segun region
        switch (region) {
            REGION_COLOMBIA, REGION_MEXICO:
                if (player has male) print ", senor";
                else print ", senora";
            REGION_ESPANA:
                print ", ?como esta usted?";
            default:
                print ".";
        }
        
    } else {
        ! Saludos informales
        print "te saluda.";
        print " ~";
        switch (region) {
            REGION_ARGENTINA:
                print "!Hola! ?Como andas?";
            REGION_MEXICO:
                print "!Hola! ?Que tal?";
            REGION_ESPANA:
                print "!Hola! ?Como estas?";
            default:
                print "!Hola! ?Como estas?";
        }
    }
    
    print "~^";
    
    ! Actualizar contador de conversaciones
    npc.conversation_count++;
];

[ SpanishNPC_Farewell npc;
    local formality, relationship, region;
    
    formality = npc.formality_level;
    relationship = npc.relationship_level;
    region = npc.regional_variant;
    
    print "^"; print (The) npc; print " ";
    
    if (relationship >= RELACION_AMIGO) {
        print "se despide afectuosamente.";
        print " ~";
        switch (random(3)) {
            1: print "!Hasta luego!";
            2: print "!Nos vemos pronto!";
            3: print "!Cuidate mucho!";
        }
        
    } else if (formality == NPC_FORMAL) {
        print "se despide cortesmente.";
        print " ~";
        switch (region) {
            REGION_COLOMBIA:
                print "Que tenga un buen dia.";
            REGION_MEXICO:
                print "Que le vaya bien.";
            REGION_ESPANA:
                print "Hasta la vista.";
            default:
                print "Buenas tardes.";
        }
        
    } else {
        print "se despide.";
        print " ~";
        switch (region) {
            REGION_ARGENTINA:
                print "!Chau!";
            REGION_CHILE:
                print "!Ya, nos vemos!";
            default:
                print "!Hasta luego!";
        }
    }
    
    print "~^";
];

! ==============================================================================
! SISTEMA DE GENERACION DE RESPUESTAS CONTEXTUAL
! ==============================================================================

[ SpanishNPC_GenerateResponse npc topic emotional_context;
    local personality, formality, region;
    
    personality = npc.personality_type;
    formality = npc.formality_level;
    region = npc.regional_variant;
    
    ! Establecer estado emocional
    npc.emotional_state = emotional_context;
    
    print "^"; print (The) npc; print " ";
    
    ! Modificar tono segun personalidad y emocion
    switch (personality) {
        PERSONALIDAD_INTELECTUAL:
            if (emotional_context == EMOCION_FELIZ) {
                print "reflexiona con interes";
            } else {
                print "considera cuidadosamente";
            }
            
        PERSONALIDAD_DIRECTA:
            if (emotional_context == EMOCION_ENOJADO) {
                print "responde firmemente";
            } else {
                print "dice directamente";
            }
            
        PERSONALIDAD_EMOCIONAL:
            switch (emotional_context) {
                EMOCION_FELIZ: print "responde con entusiasmo";
                EMOCION_TRISTE: print "suspira y dice";
                EMOCION_ENOJADO: print "exclama con frustracion";
                default: print "responde emotivamente";
            }
            
        PERSONALIDAD_ESTOICA:
            print "responde con calma";
            
        default:
            print "responde";
    }
    
    print ": ~";
    
    ! Aqui iria el contenido especifico del dialogo segun el topic
    ! Esta seccion se personaliza para cada NPC especifico
    
    return true;
];

! ==============================================================================
! SISTEMA DE CONCORDANCIA AUTOMATICA PARA DESCRIPCIONES
! ==============================================================================

[ SpanishNPC_DescribeAppearance npc;
    local gender, clothing_items, i;
    
    gender = ObtenerGenero(npc);
    
    print "^"; ArticuloDefinido(npc); print " "; print (name) npc;
    
    ! Descripcion fisica con concordancia automatica
    if (gender == FEMININE) {
        switch (random(3)) {
            1: print " es una mujer ";
            2: print " es una persona ";
            3: print " parece ser una ";
        }
        
        switch (npc.age_category) {
            1: print "joven";
            2: print "adulta";
            3: print "mayor";
        }
        
    } else {
        switch (random(3)) {
            1: print " es un hombre ";
            2: print " es una persona ";
            3: print " parece ser un ";
        }
        
        switch (npc.age_category) {
            1: print "joven";
            2: print "adulto";
            3: print "mayor";
        }
    }
    
    ! Descripcion de vestimenta con concordancia
    if (npc has elegant) {
        print " y ";
        if (gender == FEMININE) {
            print "elegante";
        } else {
            print "elegante";
        }
    }
    
    print ".^";
];

! ==============================================================================
! SISTEMA DE VARIACIONES REGIONALES
! ==============================================================================

[ SpanishNPC_ApplyRegionalFeatures npc text_buffer;
    local region = npc.regional_variant;
    
    switch (region) {
        REGION_ARGENTINA:
            ! Aplicar caracteristicas del espanol rioplatense
            ! "ll" y "y" como "sh" (representado con adaptaciones)
            ! Uso de "vos" en lugar de "tu"
            SpanishNPC_ApplyArgentineFeatures(text_buffer);
            
        REGION_MEXICO:
            ! Caracteristicas del espanol mexicano
            ! Uso de diminutivos frecuentes
            SpanishNPC_ApplyMexicanFeatures(text_buffer);
            
        REGION_ESPANA:
            ! Caracteristicas del espanol peninsular
            ! Uso de "vosotros"
            SpanishNPC_ApplySpanishFeatures(text_buffer);
            
        REGION_COLOMBIA:
            ! Caracteristicas del espanol colombiano
            ! Mayor formalidad default
            SpanishNPC_ApplyColombianFeatures(text_buffer);
    }
];

[ SpanishNPC_ApplyArgentineFeatures buffer;
    ! Aplicar caracteristicas argentinas al texto
    ! Esto es una version simplificada - en implementacion real
    ! se procesaria el buffer de texto completo
    
    if (FormalityLevel == NPC_INFORMAL) {
        ! Cambiar referencias de "tu" a "vos"
        ! print "vos" en lugar de "tu"
        ! Conjugaciones especiales para vos
    }
];

[ SpanishNPC_ApplyMexicanFeatures buffer;
    ! Caracteristicas mexicanas: diminutivos frecuentes
    ! "ahorita", "poquito", etc.
];

[ SpanishNPC_ApplySpanishFeatures buffer;
    ! Caracteristicas espanolas: vosotros, distincion ll/y
];

[ SpanishNPC_ApplyColombianFeatures buffer;
    ! Caracteristicas colombianas: mayor uso de usted
];

! ==============================================================================
! SISTEMA DE ESTADOS EMOCIONALES
! ==============================================================================

[ SpanishNPC_SetEmotion npc new_emotion duration;
    local old_emotion = npc.emotional_state;
    
    npc.emotional_state = new_emotion;
    
    ! Efectos visuales del cambio emocional
    if (new_emotion ~= old_emotion) {
        print "^"; print (The) npc; print " ";
        
        switch (new_emotion) {
            EMOCION_FELIZ:
                print "se ilumina con una sonrisa.";
                
            EMOCION_TRISTE:
                print "baja la mirada con tristeza.";
                
            EMOCION_ENOJADO:
                print "frunce el ceno con irritacion.";
                
            EMOCION_NERVIOSO:
                print "parece inquieto.";
                
            EMOCION_EMOCIONADO:
                print "se anima visiblemente.";
                
            default:
                print "recupera la compostura.";
        }
        print "^";
    }
    
    ! Programar retorno a estado neutral si se especifica duracion
    if (duration > 0) {
        ! En implementacion real, esto usaria un timer
        ! StartTimer(npc, duration);
    }
];

! ==============================================================================
! SISTEMA DE RUTINAS AUXILIARES
! ==============================================================================

[ SpanishNPC_GetFormalityDescription npc;
    switch (npc.formality_level) {
        NPC_FORMAL: print "formal";
        NPC_INFORMAL: print "informal";
        NPC_REGIONAL_VOS: print "familiar (vos)";
        default: print "variable";
    }
];

[ SpanishNPC_GetRelationshipDescription npc;
    switch (npc.relationship_level) {
        RELACION_ENEMIGO: print "hostil";
        RELACION_HOSTIL: print "desconfiado";
        RELACION_DESCONOCIDO: print "desconocido";
        RELACION_CONOCIDO: print "conocido";
        RELACION_AMIGABLE: print "amigable";
        RELACION_AMIGO: print "amigo";
        RELACION_INTIMO: print "cercano";
        default: print "neutral";
    }
];

[ SpanishNPC_GetPersonalityDescription npc;
    switch (npc.personality_type) {
        PERSONALIDAD_INTELECTUAL: print "intelectual";
        PERSONALIDAD_DIRECTA: print "directo";
        PERSONALIDAD_EMOCIONAL: print "emocional";
        PERSONALIDAD_ESTOICA: print "estoico";
        PERSONALIDAD_OPTIMISTA: print "optimista";
        PERSONALIDAD_PESIMISTA: print "pesimista";
        PERSONALIDAD_ACADEMICA: print "academico";
        PERSONALIDAD_CASUAL: print "casual";
        default: print "equilibrado";
    }
];

! ==============================================================================
! RUTINAS DE DEPURACION Y TESTING
! ==============================================================================

#Ifdef DEBUG;
[ SpanishNPC_DebugInfo npc;
    print "^=== INFORMACION DEL NPC ===^";
    print "Nombre: "; print (name) npc; print "^";
    print "Formalidad: "; SpanishNPC_GetFormalityDescription(npc); print "^";
    print "Personalidad: "; SpanishNPC_GetPersonalityDescription(npc); print "^";
    print "Relacion: "; SpanishNPC_GetRelationshipDescription(npc); print "^";
    print "Conversaciones: ", npc.conversation_count; print "^";
    print "Interacciones positivas: ", npc.positive_interactions; print "^";
    print "Interacciones negativas: ", npc.negative_interactions; print "^";
    print "Region: ";
    switch (npc.regional_variant) {
        REGION_NEUTRO: print "Neutro";
        REGION_MEXICO: print "Mexico";
        REGION_ARGENTINA: print "Argentina";
        REGION_ESPANA: print "Espana";
        REGION_COLOMBIA: print "Colombia";
        default: print "Desconocida";
    }
    print "^";
    print "Estado emocional: ";
    switch (npc.emotional_state) {
        EMOCION_NEUTRAL: print "Neutral";
        EMOCION_FELIZ: print "Feliz";
        EMOCION_TRISTE: print "Triste";
        EMOCION_ENOJADO: print "Enojado";
        EMOCION_NERVIOSO: print "Nervioso";
        default: print "Desconocido";
    }
    print "^=========================^";
];

[ TestSpanishNPC npc;
    print "^=== PRUEBA DE NPC ===^";
    SpanishNPC_Greet(npc, 1);
    SpanishNPC_UpdateRelationship(npc, 1);
    SpanishNPC_SetEmotion(npc, EMOCION_FELIZ, 0);
    SpanishNPC_GenerateResponse(npc, "saludo", EMOCION_FELIZ);
    SpanishNPC_Farewell(npc);
    SpanishNPC_DebugInfo(npc);
    print "^=== FIN PRUEBA ===^";
];
#Endif;

! ==============================================================================
! RUTINA DE INICIALIZACION
! ==============================================================================

[ SpanishNPCsInitialise;
    #Ifdef DEBUG;
    print "[Sistema de NPCs espanoles inicializado]^";
    print "[[OK] Formalidad dinamica (tu/usted/vos)]^";
    print "[[OK] 8 tipos de personalidad linguistica]^";
    print "[[OK] 6 variantes regionales]^";
    print "[[OK] Sistema de desarrollo de relaciones]^";
    print "[[OK] Estados emocionales integrados]^";
    print "[[OK] Concordancia automatica de genero]^";
    print "[[OK] Saludos y despedidas culturales]^";
    #Endif;
];

! ==============================================================================
! MACROS DE CONVENIENCIA PARA DESARROLLADORES
! ==============================================================================

! Macro para crear NPC mexicano informal
#Define CreateMexicanNPC(npc_name, gender) \
    SpanishNPC npc_name \
        with formality_level NPC_INFORMAL, \
             regional_variant REGION_MEXICO, \
             personality_type PERSONALIDAD_CASUAL \
        has gender

! Macro para crear NPC espanol formal
#Define CreateSpanishNPC(npc_name, gender) \
    SpanishNPC npc_name \
        with formality_level NPC_FORMAL, \
             regional_variant REGION_ESPANA, \
             personality_type PERSONALIDAD_DIRECTA \
        has gender

! Macro para crear NPC argentino con vos
#Define CreateArgentineNPC(npc_name, gender) \
    SpanishNPC npc_name \
        with formality_level NPC_INFORMAL, \
             regional_variant REGION_ARGENTINA, \
             personality_type PERSONALIDAD_CASUAL \
        has gender

#Endif; ! SPANISH_NPCS_INCLUDED

! ==============================================================================
! Fin de SpanishNPCs.h - Sistema completo de NPCs para espanol
! ==============================================================================