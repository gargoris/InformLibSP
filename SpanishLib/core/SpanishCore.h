! ==============================================================================
! SPANISHCORE.H - Núcleo coordinador del sistema modular español
! Sistema modular Spanish Library para Inform 6
! Compatible con Inform 6.42 y librería estándar 6.12.7
! ==============================================================================

System_file;

#Ifndef SPANISH_CORE_INCLUDED;
Constant SPANISH_CORE_INCLUDED;
Constant SPANISH_CORE_VERSION = "1.1-coordinator-only";

! ==============================================================================
! VERIFICACIÓN DE DEPENDENCIAS
! ==============================================================================

#Ifndef SPANISH_CONSTANTS_INCLUDED;
  Message fatalerror "*** Include SpanishConstants.h antes de SpanishCore.h ***";
#Endif;

#Ifdef LIBRARY_STAGE;
#Iffalse LIBRARY_STAGE >= AFTER_PARSER;
  Message fatalerror "*** Include Parser.h y VerbLib.h antes de SpanishCore.h ***";
#Endif;
#Endif;

! ==============================================================================
! RUTINAS DE COORDINACIÓN ENTRE MÓDULOS
! ==============================================================================

[ SpanishCoreCoordinate;
    ! Coordina la inicialización de todos los módulos
    ! Se llama después de que todos los módulos estén cargados
    
    local modules_ok;
    modules_ok = 0;
    
    ! Verificar que los módulos principales estén listos
    #Ifdef SPANISH_PARSER_INCLUDED;
        spanish_parser_ready = true;
        MarkModuleLoaded('parser');
        modules_ok++;
    #Ifnot;
        print "^[ADVERTENCIA: SpanishParser.h no está cargado]^";
    #Endif;
    
    #Ifdef SPANISH_VERBS_INCLUDED;
        spanish_verbs_ready = true;
        MarkModuleLoaded('verbs');
        modules_ok++;
    #Ifnot;
        print "^[ADVERTENCIA: SpanishVerbs.h no está cargado]^";
    #Endif;
    
    #Ifdef SPANISH_GRAMMAR_INCLUDED;
        spanish_grammar_ready = true;
        MarkModuleLoaded('grammar');
        modules_ok++;
    #Ifnot;
        print "^[ADVERTENCIA: SpanishGrammar.h no está cargado]^";
    #Endif;
    
    #Ifdef SPANISH_MESSAGES_COMPLETE;
        spanish_messages_ready = true;
        MarkModuleLoaded('messages');
        modules_ok++;
    #Endif;
    
    ! Marcar este módulo como cargado
    MarkModuleLoaded('core');
    
    return modules_ok;
];

! ==============================================================================
! INTEGRACIÓN CON EL PARSER PRINCIPAL
! ==============================================================================

[ LanguageToInformese;
    ! Esta función coordina el procesamiento pero la lógica real
    ! está en SpanishParser.h para evitar duplicaciones
    
    #Ifdef SPANISH_PARSER_INCLUDED;
        return SpanishParserMain();
    #Ifnot;
        ! Procesamiento básico si no hay parser avanzado
        return SpanishBasicParsing();
    #Endif;
];

[ SpanishBasicParsing   i j k;
    ! Procesamiento mínimo si SpanishParser.h no está disponible
    ! Solo contracciones básicas para mantener funcionalidad mínima
    
    local changes;
    changes = 0;
    
    ! Solo procesar contracciones básicas
    for (i=0 : i<parse->1 : i++) {
        j = parse-->(2*i+1);
        
        if (j == 'del') {
            parse-->(2*i+1) = 'de';
            ! Insertar 'el' después
            for (k=parse->1: k>i: k--) {
                parse-->(2*k+1) = parse-->(2*k-1);
                parse-->(2*k+2) = parse-->(2*k);
            }
            parse->1 = parse->1 + 1;
            parse-->(2*i+3) = 'el';
            parse-->(2*i+4) = 1;
            changes++;
        }
        
        if (j == 'al') {
            parse-->(2*i+1) = 'a';
            ! Insertar 'el' después
            for (k=parse->1: k>i: k--) {
                parse-->(2*k+1) = parse-->(2*k-1);
                parse-->(2*k+2) = parse-->(2*k);
            }
            parse->1 = parse->1 + 1;
            parse-->(2*i+3) = 'el';
            parse-->(2*i+4) = 1;
            changes++;
        }
    }
    
    return changes;
];

! ==============================================================================
! RUTINAS DE ESTADO Y MONITOREO
! ==============================================================================

[ SpanishCoreStatus;
    print "^=== ESTADO DEL NÚCLEO ESPAÑOL ===^";
    print "Versión del núcleo: ", (string) SPANISH_CORE_VERSION, "^";
    print "Inicializado: ";
    if (spanish_initialized) print "Sí"; else print "No";
    print "^";
    
    print "Formalidad: ";
    if (FormalityLevel == FORMAL) print "Formal (usted)";
    else print "Informal (tú)";
    print "^";
    
    print "^Módulos coordinados:^";
    print "• Parser: ";
    if (spanish_parser_ready) print "✅"; else print "❌";
    print "^• Verbos: ";
    if (spanish_verbs_ready) print "✅"; else print "❌";
    print "^• Gramática: ";
    if (spanish_grammar_ready) print "✅"; else print "❌";
    print "^• Mensajes: ";
    if (spanish_messages_ready) print "✅"; else print "❌";
    print "^";
    
    print "Último comando: ", last_command_length, " palabras^";
];

! ==============================================================================
! RUTINAS DE EMERGENCIA Y FALLBACK
! ==============================================================================

[ SpanishEmergencyFallback;
    ! Rutinas básicas en caso de que otros módulos fallen
    print "^[MODO DE EMERGENCIA: Funcionalidad básica del español]^";
    print "[Solo contracciones y parsing mínimo disponibles]^";
    
    ! Configurar valores seguros
    FormalityLevel = INFORMAL;
    spanish_initialized = true;
    MarkModuleLoaded('core');
    
    return true;
];

[ SpanishValidateSystem;
    ! Verificar integridad del sistema
    local errors;
    errors = 0;
    
    ! Verificar constantes críticas
    if (PRESENTE_T == 0) {
        print "^[ERROR: Constantes de tiempo verbal no definidas]^";
        errors++;
    }
    
    if (MASCULINE == 0) {
        print "^[ERROR: Constantes de género no definidas]^";
        errors++;
    }
    
    ! Verificar arrays críticos
    if (LanguagePronouns-->0 == 0) {
        print "^[ERROR: Array de pronombres no inicializado]^";
        errors++;
    }
    
    ! Verificar variables centralizadas
    if (spanish_buffer == 0) {
        print "^[ERROR: Buffer principal no disponible]^";
        errors++;
    }
    
    if (errors > 0) {
        print "^[SISTEMA ESPAÑOL: ", errors, " errores detectados]^";
        return false;
    }
    
    return true;
];

! ==============================================================================
! RUTINAS DE COORDINACIÓN DE INICIALIZACIÓN
! ==============================================================================

[ SpanishCoreCallInitializers;
    ! Llama a los inicializadores de todos los módulos en orden
    
    print "^[Inicializando módulos del sistema español...]^";
    
    ! 1. Constantes (ya inicializadas)
    SpanishConstantsInit();
    
    ! 2. Parser (si está disponible)
    #Ifdef SPANISH_PARSER_INCLUDED;
        SpanishParserInitialize();
    #Endif;
    
    ! 3. Gramática (si está disponible)
    #Ifdef SPANISH_GRAMMAR_INCLUDED;
        ! La gramática se inicializa automáticamente
        print "[SpanishGrammar cargado]^";
    #Endif;
    
    ! 4. Verbos (si está disponible)
    #Ifdef SPANISH_VERBS_INCLUDED;
        SpanishVerbsInitialise();
    #Endif;
    
    ! 5. Mensajes (si está disponible)
    #Ifdef SPANISH_MESSAGES_COMPLETE;
        SpanishMessagesInitialise();
    #Endif;
    
    ! 6. Verbos irregulares (si está disponible)
    #Ifdef SPANISH_IRREGULAR_VERBS_INCLUDED;
        SpanishIrregularVerbsInitialise();
        MarkModuleLoaded('irregular');
    #Endif;
    
    ! 7. Meta-comandos (si está disponible)
    #Ifdef SPANISH_META_INCLUDED;
        SpanishMetaInitialise();
        MarkModuleLoaded('meta');
    #Endif;
    
    ! 8. Regional (si está disponible)
    #Ifdef SPANISH_REGIONAL_INCLUDED;
        SpanishRegionalAutoInit();
        MarkModuleLoaded('regional');
    #Endif;
    
    print "^[Inicialización de módulos completada]^";
];

! ==============================================================================
! RUTINA PRINCIPAL DE INICIALIZACIÓN
! ==============================================================================

[ SpanishCoreInitialise   i modules_loaded;
    if (spanish_initialized) return;
    
    print "^[SpanishCore v", (string) SPANISH_CORE_VERSION, " inicializando...]^";
    
    ! Validar sistema antes de inicializar
    if (~~SpanishValidateSystem()) {
        print "^[ACTIVANDO MODO DE EMERGENCIA]^";
        return SpanishEmergencyFallback();
    }
    
    ! Limpiar buffers del sistema
    for (i = 0: i < 120: i++) spanish_buffer->i = 0;
    
    ! Coordinar con otros módulos
    modules_loaded = SpanishCoreCoordinate();
    
    ! Llamar inicializadores de todos los módulos
    SpanishCoreCallInitializers();
    
    ! Establecer que ya estamos inicializados
    spanish_initialized = true;
    
    print "^[SpanishCore inicializado correctamente - ";
    print modules_loaded, " módulos principales detectados]^";
    print "[Coordinación activa para: Parser, Gramática, Verbos, Mensajes]^";
];

! ==============================================================================
! RUTINAS DE INFORMACIÓN DEL SISTEMA
! ==============================================================================

[ SpanishCoreInfo;
    print "^=== SPANISH CORE PARA INFORM 6 ===^";
    print "Versión: ", (string) SPANISH_CORE_VERSION, "^";
    print "Función: Coordinación y núcleo básico^";
    print "^Responsabilidades:^";
    print "• Coordinación entre módulos^";
    print "• Inicialización centralizada^";
    print "• Procesamiento básico fallback^";
    print "• Validación de integridad del sistema^";
    print "• Gestión de estado global^";
    print "^Este módulo NO contiene:^";
    print "• Funciones de gramática (ver SpanishGrammar.h)^";
    print "• Conjugaciones (ver SpanishVerbs.h)^";
    print "• Parsing avanzado (ver SpanishParser.h)^";
    print "• Variables globales (ver SpanishConstants.h)^";
    print "^Para funcionalidad completa, incluye todos los módulos.^";
];

! ==============================================================================
! HOOKS PARA INTEGRACIÓN AUTOMÁTICA
! ==============================================================================

! Hook para procesamiento de comandos
[ SpanishCoreProcessCommand;
    ! Actualizar estadísticas de comando
    last_command_length = parse->1;
    
    ! Guardar comando para AGAIN si meta-comandos están disponibles
    #Ifdef SPANISH_META_INCLUDED;
        SpanishSaveCommand();
    #Endif;
    
    return false; ! Continuar procesamiento normal
];

! Hook para manejo de errores
[ SpanishCoreHandleError error_type;
    ! Delegar al sistema de meta-comandos si está disponible
    #Ifdef SPANISH_META_INCLUDED;
        return SpanishParseError(error_type, 0);
    #Ifnot;
        ! Manejo básico de errores
        switch(error_type) {
            1: print "No entendí esa instrucción.";
            2: print "No puedes ver tal cosa aquí.";
            3: print "No está claro a qué te refieres.";
            default: print "Error en el comando.";
        }
        return true;
    #Endif;
];

! ==============================================================================
! CONSTANTES DE FINALIZACIÓN
! ==============================================================================

Constant SPANISH_CORE_COMPLETE;
Constant SPANISH_COORDINATOR_READY;

! Información del módulo
Constant SPANISH_CORE_FEATURES = "Coordinación, inicialización, fallback, validación";

#Endif; ! SPANISH_CORE_INCLUDED

! ==============================================================================
! Fin de SpanishCore.h - Núcleo coordinador limpio y sin duplicaciones
! ==============================================================================