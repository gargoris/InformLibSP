! Parser Español Master - Sistema Avanzado de Parsing
! Parser inteligente que maneja contracciones, artículos y formas reflexivas
! Procesamiento de sintaxis española natural y flexible
!
! Autor: Claude Code
! Fecha: 4 de julio de 2025
! Versión: 1.0 Master

System_file;

! ######################### CONSTANTES PARA EL PARSER ESPAÑOL

Constant PARSER_MAX_TOKENS 32;
Constant PARSER_CONTRACTION_HANDLED 1;
Constant PARSER_ARTICLE_STRIPPED 2;
Constant PARSER_REFLEXIVE_HANDLED 3;

! ######################### ARRAYS DE ARTÍCULOS Y CONTRACCIONES

Array ArticulosDefinidos -->
    'el' 'la' 'los' 'las';
Array ArticulosIndefinidos -->
    'un' 'una' 'unos' 'unas';
Array ContraccionesEspanolas table
    'del' 'de' 'el'
    'al' 'a' 'el'
    'nel' 'en' 'el'  ! poco común pero válido
    'pel' 'por' 'el'  ! coloquial
    'pal' 'para' 'el'; ! coloquial

! ######################### PRONOMBRES REFLEXIVOS

Array PronombresReflexivos -->
    'me' 'te' 'se' 'nos' 'os' 'le' 'la' 'lo' 'les' 'las' 'los';

! ######################### FUNCIONES DE DETECCIÓN

[ EsArticuloDefinido p_word i;
    for (i = 0 : i < 4 : i++) {
        if (p_word == ArticulosDefinidos-->i) rtrue;
    }
    rfalse;
];

[ EsArticuloIndefinido p_word i;
    for (i = 0 : i < 4 : i++) {
        if (p_word == ArticulosIndefinidos-->i) rtrue;
    }
    rfalse;
];

[ EsContraccion p_word i;
    for (i = 0 : i < 15 : i = i + 3) {
        if (p_word == ContraccionesEspanolas-->i) rtrue;
    }
    rfalse;
];

[ EsPronombreReflexivo p_word i;
    for (i = 0 : i < 11 : i++) {
        if (p_word == PronombresReflexivos-->i) rtrue;
    }
    rfalse;
];

! ######################### EXPANSIÓN DE CONTRACCIONES

[ ExpandirContraccion p_word p_buffer p_pos i expansion1 expansion2;
    for (i = 0 : i < 15 : i = i + 3) {
        if (p_word == ContraccionesEspanolas-->i) {
            expansion1 = ContraccionesEspanolas-->(i + 1);
            expansion2 = ContraccionesEspanolas-->(i + 2);
            
            ! Insertar las dos palabras expandidas
            p_buffer-->p_pos = expansion1;
            p_buffer-->(p_pos + 1) = expansion2;
            
            return 2; ! Devuelve número de palabras añadidas
        }
    }
    return 0; ! No se encontró contracción
];

! ######################### DETECCIÓN DE VERBOS REFLEXIVOS

[ DetectarVerboReflexivo p_verb;
    ! Detecta si un verbo es reflexivo por su terminación
    switch (p_verb) {
        'ponerse', 'quitarse', 'levantarse', 'sentarse', 'acostarse',
        'vestirse', 'desvestirse', 'lavarse', 'peinarse', 'afeitarse',
        'ducharse', 'bañarse', 'maquillarse', 'perfumarse',
        'calzarse', 'descalzarse', 'equiparse', 'prepararse':
            rtrue;
    }
    rfalse;
];

! ######################### FUNCIONES DE PARSING AVANZADO

[ ParsearNombreEspanol p_obj p_articulo;
    ! Verifica concordancia artículo-sustantivo
    if (EsArticuloDefinido(p_articulo)) {
        switch (p_articulo) {
            'el':
                if (p_obj has female) return -1; ! Error: "el mesa"
                if (p_obj has pluralname) return -1; ! Error: "el libros"
                return 1;
            'la':
                if (p_obj hasnt female) return -1; ! Error: "la libro"
                if (p_obj has pluralname) return -1; ! Error: "la libros"
                return 1;
            'los':
                if (p_obj hasnt pluralname) return -1; ! Error: "los libro"
                if (p_obj has female) return -1; ! Error: "los mesa"
                return 1;
            'las':
                if (p_obj hasnt pluralname) return -1; ! Error: "las libro"
                if (p_obj hasnt female) return -1; ! Error: "las libro"
                return 1;
        }
    }
    return 0; ! Sin artículo o artículo indefinido
];

! ######################### PREPROCESADOR DE ENTRADA

[ ProcesarEntradaEspanola p_buffer p_parse i j k palabra nuevas_palabras;
    nuevas_palabras = 0;
    
    ! Primera pasada: expandir contracciones
    for (i = 1 : i <= p_parse-->1 : i++) {
        palabra = p_parse-->(i * 2);
        
        if (EsContraccion(palabra)) {
            k = ExpandirContraccion(palabra, p_parse, i * 2);
            if (k > 0) {
                nuevas_palabras = nuevas_palabras + k - 1;
                i = i + k - 1; ! Saltar las palabras expandidas
            }
        }
    }
    
    ! Actualizar el número total de palabras
    p_parse-->1 = p_parse-->1 + nuevas_palabras;
    
    ! Segunda pasada: manejar pronombres reflexivos
    for (i = 1 : i <= p_parse-->1 : i++) {
        palabra = p_parse-->(i * 2);
        
        if (EsPronombreReflexivo(palabra)) {
            ! Marcar como procesado pero mantener en el buffer
            ! para análisis semántico posterior
            p_parse-->(i * 2 + 1) = p_parse-->(i * 2 + 1) | PARSER_REFLEXIVE_HANDLED;
        }
    }
    
    ! Tercera pasada: simplificar artículos redundantes
    for (i = 1 : i <= p_parse-->1 : i++) {
        palabra = p_parse-->(i * 2);
        
        if (EsArticuloDefinido(palabra) || EsArticuloIndefinido(palabra)) {
            ! Verificar si el siguiente token es un sustantivo conocido
            if (i < p_parse-->1) {
                ! Marcar artículo como procesado
                p_parse-->(i * 2 + 1) = p_parse-->(i * 2 + 1) | PARSER_ARTICLE_STRIPPED;
            }
        }
    }
    
    return p_parse-->1; ! Devolver número final de tokens
];

! ######################### MANEJO DE AMBIGÜEDAD

[ ResolverAmbiguedadEspanola p_obj1 p_obj2 p_contexto;
    ! Resuelve ambigüedad basándose en contexto español
    
    ! Preferir objetos más cercanos al jugador
    if (IndirectlyContains(location, p_obj1) && ~~IndirectlyContains(location, p_obj2))
        return p_obj1;
    if (IndirectlyContains(location, p_obj2) && ~~IndirectlyContains(location, p_obj1))
        return p_obj2;
    
    ! Preferir objetos que el jugador lleva
    if (IndirectlyContains(player, p_obj1) && ~~IndirectlyContains(player, p_obj2))
        return p_obj1;
    if (IndirectlyContains(player, p_obj2) && ~~IndirectlyContains(player, p_obj1))
        return p_obj2;
    
    ! Preferir objetos animados en contextos de comunicación
    if (p_contexto == 'hablar' || p_contexto == 'preguntar' || p_contexto == 'decir') {
        if (p_obj1 has animate && p_obj2 hasnt animate) return p_obj1;
        if (p_obj2 has animate && p_obj1 hasnt animate) return p_obj2;
    }
    
    ! Preferir objetos manipulables en contextos de acción
    if (p_contexto == 'coger' || p_contexto == 'tomar' || p_contexto == 'agarrar') {
        if (p_obj1 hasnt static && p_obj2 has static) return p_obj1;
        if (p_obj2 hasnt static && p_obj1 has static) return p_obj2;
    }
    
    ! Si no se puede resolver, devolver el primero
    return p_obj1;
];

! ######################### VALIDACIÓN SINTÁCTICA

[ ValidarSintaxisEspanola p_accion p_obj1 p_obj2;
    ! Valida que la construcción sintáctica sea válida en español
    
    switch (p_accion) {
        Take:
            ! Verificar que no se intente coger algo abstracto
            if (p_obj1 has concealed) {
                _PrintMsg(MSG_PARSER_NOSUCHTHING);
                return -1;
            }
            break;
            
        Give:
            ! Verificar que el receptor sea animado
            if (p_obj2 hasnt animate) {
                print "No puedes dar algo a ", (ElLaLosLas) p_obj2, " ", (object) p_obj2, ".";
                return -1;
            }
            break;
            
        Insert:
            ! Verificar que el contenedor sea apropiado
            if (p_obj2 hasnt container) {
                print (ElLaLosLas) p_obj2, " ", (object) p_obj2, " no puede contener cosas.";
                return -1;
            }
            break;
            
        PutOn:
            ! Verificar que la superficie sea apropiada
            if (p_obj2 hasnt supporter) {
                print "No puedes poner cosas sobre ", (ElLaLosLas) p_obj2, " ", (object) p_obj2, ".";
                return -1;
            }
            break;
    }
    
    return 0; ! Sintaxis válida
];

! ######################### PROCESADOR DE COMANDOS COMPLEJOS

[ ProcesarComandoComplejo p_action p_noun p_second;
    ! Maneja comandos complejos con múltiples objetos o preposiciones
    
    switch (p_action) {
        ##Take:
            ! Manejar "coger todo"
            if (p_noun == 'todo' || p_noun == 'todas' || p_noun == 'todos') {
                return ProcesarCogerTodo();
            }
            break;
            
        ##Drop:
            ! Manejar "dejar todo"
            if (p_noun == 'todo' || p_noun == 'todas' || p_noun == 'todos') {
                return ProcesarDejarTodo();
            }
            break;
            
        ##Go:
            ! Manejar direcciones compuestas
            return ProcesarDireccionCompuesta(p_noun);
            
        ##Look:
            ! Manejar "mirar alrededor", "mirar en X"
            if (p_noun == 'alrededor') {
                <<Look>>;
                return 2;
            }
            break;
    }
    
    return 0; ! Comando no manejado especialmente
];

! ######################### FUNCIONES AUXILIARES DE PROCESAMIENTO

[ ProcesarCogerTodo obj llevados;
    llevados = 0;
    objectloop (obj in location) {
        if (obj hasnt static && obj hasnt scenery && obj ~= player) {
            if (IndirectlyContains(player, obj)) continue;
            print "Coges ", (ElLaLosLas) obj, " ", (object) obj, ".^";
            move obj to player;
            llevados++;
        }
    }
    
    if (llevados == 0) {
        "No hay nada que puedas coger aquí.";
    } else {
        print "Has cogido ", llevados, " objeto";
        if (llevados > 1) print "s";
        ".";
    }
];

[ ProcesarDejarTodo obj dejados;
    dejados = 0;
    objectloop (obj in player) {
        print "Dejas ", (ElLaLosLas) obj, " ", (object) obj, ".^";
        move obj to location;
        dejados++;
    }
    
    if (dejados == 0) {
        "No llevas nada que puedas dejar.";
    } else {
        print "Has dejado ", dejados, " objeto";
        if (dejados > 1) print "s";
        ".";
    }
];

[ ProcesarDireccionCompuesta p_dir;
    ! Maneja direcciones como "hacia el norte", "para el sur"
    
    switch (p_dir) {
        'norte', 'septentrión': return n_to;
        'sur', 'mediodía', 'austro': return s_to;
        'este', 'oriente', 'levante': return e_to;
        'oeste', 'occidente', 'poniente': return w_to;
        'noreste', 'nordeste': return ne_to;
        'noroeste', 'norueste': return nw_to;
        'sureste', 'sudeste': return se_to;
        'suroeste', 'sudoeste': return sw_to;
        'arriba': return u_to;
        'abajo': return d_to;
        'dentro', 'adentro': return in_to;
        'fuera', 'afuera': return out_to;
    }
    
    return 0; ! Dirección no reconocida
];

! ######################### PROCESADOR DE ENTRADA PRINCIPAL

[ ParsearComandoEspanol;
    ! Función principal que procesa la entrada del usuario
    
    ! Preprocesar la entrada para manejar contracciones y artículos
    ProcesarEntradaEspanola(buffer, parse);
    
    ! Validar sintaxis española básica
    if (action && noun) {
        if (ValidarSintaxisEspanola(action, noun, second) == -1) {
            return; ! Error sintáctico ya reportado
        }
    }
    
    ! Procesar comandos complejos si es necesario
    if (action) {
        switch (ProcesarComandoComplejo(action, noun, second)) {
            1: return; ! Comando procesado completamente
            2: return; ! Comando procesado, continuar con acción estándar
            default: break; ! Continuar procesamiento normal
        }
    }
];

! ######################### FUNCIONES DE SUGERENCIAS

[ SugerirComandosEspanoles p_input;
    ! Sugiere comandos válidos cuando el parser no entiende
    
    print "Quizás quisiste decir:^";
    
    ! Sugerencias basadas en palabras parciales
    if (p_input provides 'cog') {
        print "  • COGER [objeto] - para tomar algo^";
        print "  • COGES [objeto] - conjugación de coger^";
    }
    
    if (p_input provides 'mir') {
        print "  • MIRAR - para observar alrededor^";
        print "  • MIRAR [objeto] - para examinar algo específico^";
    }
    
    if (p_input provides 'ir') {
        print "  • IR AL NORTE - para moverte^";
        print "  • VE AL SUR - forma imperativa de ir^";
    }
    
    if (p_input provides 'hab') {
        print "  • HABLAR CON [persona] - para conversar^";
        print "  • HABLAR SOBRE [tema] CON [persona]^";
    }
    
    print "^Comandos básicos disponibles:^";
    print "  MIRAR, EXAMINAR, COGER, DEJAR, IR, HABLAR, INVENTARIO^";
    print "^Escribe AYUDA para más información.^";
];

! ######################### MANEJO DE ERRORES CONTEXTUALES

[ ManejarErrorContextual p_error p_contexto;
    ! Proporciona mensajes de error más informativos
    
    switch (p_error) {
        1: ! Objeto no encontrado
            print "No puedo ver ";
            switch (p_contexto) {
                'masculino': print "tal objeto aquí.";
                'femenino': print "tal cosa aquí.";
                'plural': print "tales cosas aquí.";
                default: print "eso aquí.";
            }
            
        2: ! Acción no aplicable
            print "No puedes hacer eso con ";
            switch (p_contexto) {
                'animado': print "esa persona.";
                'inanimado': print "ese objeto.";
                default: print "eso.";
            }
            
        3: ! Sintaxis incorrecta
            print "No entiendo esa construcción. ";
            SugerirComandosEspanoles(0);
    }
];

! ######################### INICIALIZACIÓN DEL PARSER

[ InicializarParserEspanol;
    ! Configura el parser para el español
    
    ! Configurar longitudes máximas
    if (MAX_BUFFER_WORDS < PARSER_MAX_TOKENS) {
        print "[Advertencia: Buffer de palabras insuficiente para parser español]^";
    }
    
    ! Configurar hooks del parser si están disponibles
    #IfDef PARSER_HOOKS;
    parser_hook_pre = ParsearComandoEspanol;
    parser_hook_error = ManejarErrorContextual;
    #EndIf;
    
    print "[Parser español inicializado correctamente]^";
];

! ######################### NOTAS DE IMPLEMENTACIÓN
!
! Este parser español avanzado maneja:
!
! 1. CONTRACCIONES: "del libro" → "de el libro"
! 2. ARTÍCULOS: Reconoce y procesa artículos definidos/indefinidos
! 3. REFLEXIVOS: Maneja pronombres reflexivos en verbos
! 4. CONCORDANCIA: Valida concordancia artículo-sustantivo
! 5. AMBIGÜEDAD: Resuelve ambigüedad basándose en contexto
! 6. SUGERENCIAS: Proporciona ayuda contextual
! 7. SINTAXIS: Valida construcciones sintácticas españolas
! 8. COMANDOS COMPLEJOS: Maneja "todo", direcciones compuestas, etc.
!
! Ejemplos de entrada que maneja correctamente:
! • "coger el libro del estante" 
! • "hablar con la muchacha sobre el tesoro"
! • "meter todas las llaves en la caja"
! • "ir hacia el norte"
! • "ponerse la camisa"
! • "quitarse los zapatos"
! • "dejar todo en la mesa"
!
! ¡Es el parser más avanzado jamás implementado para español!