! ==============================================================================
! SPANISHCORE.H - Núcleo coordinador del sistema modular español
! Sistema modular Spanish Library para Inform 6
! Compatible con Inform 6.42 y librería estándar 6.12.7
! ==============================================================================

System_file;

#Ifndef SPANISH_CORE_INCLUDED;
Constant SPANISH_CORE_INCLUDED;
Constant SPANISH_CORE_VERSION = "1.2-coordinator-fixed";

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
    
    #Ifdef DEBUG;
        print "^[SpanishCore: Coordinando módulos...]^";
    #Endif;
    
    ! Verificar que los módulos principales estén listos
    #Ifdef SPANISH_PARSER_INCLUDED;
        spanish_parser_ready = true;
        MarkModuleLoaded('parser');
        modules_ok++;
        #Ifdef DEBUG;
            print "[✅ Parser cargado]^";
        #Endif;
    #Ifnot;
        #Ifdef DEBUG;
            print "[⚠️ Parser básico solamente]^";
        #Endif;
    #Endif;
    
    #Ifdef SPANISH_VERBS_INCLUDED;
        spanish_verbs_ready = true;
        MarkModuleLoaded('verbs');
        modules_ok++;
        #Ifdef DEBUG;
            print "[✅ Verbos cargados]^";
        #Endif;
    #Ifnot;
        #Ifdef DEBUG;
            print "[❌ Sin sistema de verbos]^";
        #Endif;
    #Endif;
    
    #Ifdef SPANISH_GRAMMAR_INCLUDED;
        spanish_grammar_ready = true;
        MarkModuleLoaded('grammar');
        modules_ok++;
        #Ifdef DEBUG;
            print "[✅ Gramática cargada]^";
        #Endif;
    #Ifnot;
        #Ifdef DEBUG;
            print "[❌ Sin sistema de gramática]^";
        #Endif;
    #Endif;
    
    #Ifdef SPANISH_MESSAGES_COMPLETE;
        spanish_messages_ready = true;
        MarkModuleLoaded('messages');
        modules_ok++;
        #Ifdef DEBUG;
            print "[✅ Mensajes completos cargados]^";
        #Endif;
    #Endif;
    
    ! Marcar este módulo como cargado
    MarkModuleLoaded('core');
    
    #Ifdef DEBUG;
        print "[SpanishCore: ", modules_ok, " módulos principales coordinados]^";
    #Endif;
    
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

[ SpanishBasicParsing   i j k changes;
    ! ✅ CORREGIDO: Función completa de procesamiento mínimo
    ! Solo contracciones básicas para mantener funcionalidad mínima
    
    changes = 0;
    
    #Ifdef DEBUG;
        print "[CORE] Procesamiento básico: ", parse->1, " palabras^";
    #Endif;
    
    ! Solo procesar contracciones básicas
    for (i=0 : i<parse->1 : i++) {
        j = parse-->(2*i+1);
        
        ! Contracción DEL = DE + EL
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
            
            #Ifdef DEBUG;
                print "[CORE] Contracción procesada: del -> de el^";
            #Endif;
        }
        
        ! Contracción AL = A + EL
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
            
            #Ifdef DEBUG;
                print "[CORE] Contracción procesada: al -> a el^";
            #Endif;
        }
    }
    
    #Ifdef DEBUG;
        if (changes > 0) {
            print "[CORE] ", changes, " contracciones procesadas^";
        }
    #Endif;
    
    return changes;
];

! ==============================================================================
! RUTINAS DE COORDINACIÓN DE INICIALIZACIÓN
! ==============================================================================

[ SpanishCoreCallInitializers;
    ! ✅ CORREGIDO: Función completa para llamar inicializadores
    ! Llama a los inicializadores de todos los módulos en orden
    
    #Ifdef DEBUG;
        print "^[Inicializando módulos del sistema español...]^";
    #Endif;
    
    ! 1. Constantes (ya inicializadas)
    SpanishConstantsInit();
    
    ! 2. Parser (si está disponible)
    #Ifdef SPANISH_PARSER_INCLUDED;
        #Ifdef SPANISH_PARSER_PART3_COMPLETE;
            SpanishParserInitialize();
        #Endif;
    #Endif;
    
    ! 3. Gramática (si está disponible)
    #Ifdef SPANISH_GRAMMAR_INCLUDED;
        ! La gramática se inicializa automáticamente
        #Ifdef DEBUG;
            print "[SpanishGrammar cargado]^";
        #Endif;
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
        SpanishRegionalInit();
        MarkModuleLoaded('regional');
    #Endif;
    
    ! Marcar sistema como inicializado
    spanish_initialized = true;
    
    #Ifdef DEBUG;
        print "[Sistema español completamente inicializado]^";
    #Endif;
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
    
    print "Región: ";
    switch (current_spanish_region) {
        REGION_NEUTRAL: print "Neutral";
        REGION_MEXICO: print "México";
        REGION_ARGENTINA: print "Argentina";
        REGION_SPAIN: print "España";
        REGION_COLOMBIA: print "Colombia";
        REGION_CHILE: print "Chile";
        default: print "Desconocida";
    }
    print "^";
    
    print "Voseo: ";
    if (voseo_enabled) print "Activo"; else print "Inactivo";
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
    print "Estado del parser: Etapa ", spanish_parse_stage, "^";
];

! ==============================================================================
! RUTINAS DE EMERGENCIA Y FALLBACK
! ==============================================================================

[ SpanishEmergencyFallback;
    ! ✅ CORREGIDO: Función completa de rutinas de emergencia
    ! Rutinas básicas en caso de que otros módulos fallen
    
    print "^[MODO DE EMERGENCIA: Funcionalidad básica del español]^";
    print "[Solo contracciones y parsing mínimo disponibles]^";
    
    ! Configurar valores seguros
    FormalityLevel = INFORMAL;
    current_spanish_region = REGION_NEUTRAL;
    voseo_enabled = false;
    spanish_initialized = true;
    
    ! Marcar este módulo como cargado
    MarkModuleLoaded('core');
    
    ! Limpiar buffers
    spanish_buffer->0 = 0;
    if (spanish_temp_buffer) spanish_temp_buffer->0 = 0;
    
    #Ifdef DEBUG;
        print "[Modo de emergencia activado - funcionalidad limitada]^";
    #Endif;
    
    return true;
];

[ SpanishValidateSystem;
    ! ✅ CORREGIDO: Función completa de validación del sistema
    ! Verificar integridad del sistema
    local errors;
    errors = 0;
    
    #Ifdef DEBUG;
        print "^[Validando integridad del sistema español...]^";
    #Endif;
    
    ! Verificar constantes críticas
    if (PRESENTE_T == 0) {
        print "^[ERROR: Constantes de tiempo verbal no definidas]^";
        errors++;
    }
    
    if (MASCULINE == 0) {
        print "^[ERROR: Constantes de género no definidas]^";
        errors++;
    }
    
    ! Verificar arrays críticos (solo si están definidos)
    #Ifdef LIBRARY_STAGE;
    #Iffalse LIBRARY_STAGE >= AFTER_PARSER;
        ! Aún no se pueden verificar los arrays
    #Ifnot;
        if (LanguagePronouns-->0 == 0) {
            print "^[ERROR: Array de pronombres no inicializado]^";
            errors++;
        }
    #Endif;
    #Endif;
    
    ! Verificar variables centralizadas
    if (spanish_buffer == 0) {
        print "^[ERROR: Buffer principal no disponible]^";
        errors++;
    }
    
    ! Verificar inicialización de módulos críticos
    if (~~spanish_initialized) {
        print "^[ADVERTENCIA: Sistema no completamente inicializado]^";
    }
    
    if (errors > 0) {
        print "^[SISTEMA ESPAÑOL: ", errors, " errores detectados]^";
        print "[Recomendación: Usar SpanishEmergencyFallback()]^";
        return false;
    }
    
    #Ifdef DEBUG;
        print "[Validación completa: Sistema OK]^";
    #Endif;
    
    return true;
];

! ==============================================================================
! HOOKS PARA INTEGRACIÓN AUTOMÁTICA
! ==============================================================================

[ SpanishCoreProcessCommand;
    ! Hook para procesamiento de comandos
    ! Actualizar estadísticas de comando
    last_command_length = parse->1;
    
    ! Guardar comando para AGAIN si meta-comandos están disponibles
    #Ifdef SPANISH_META_INCLUDED;
        SpanishSaveCommand();
    #Endif;
    
    return false; ! Continuar procesamiento normal
];

[ SpanishCoreHandleError error_type;
    ! Hook para manejo de errores
    ! Delegar al sistema de meta-comandos si está disponible
    #Ifdef SPANISH_META_INCLUDED;
        return SpanishParseError(error_type, 0);
    #Ifnot;
        ! Manejo básico de errores
        switch(error_type) {
            STUCK_PE: print "No entendí esa instrucción.";
            CANTSEE_PE: print "No puedes ver tal cosa aquí.";
            VAGUE_PE: print "No está claro a qué te refieres.";
            VERB_PE: print "Ese no es un verbo que reconozca.";
            default: print "Error en el comando.";
        }
        return true;
    #Endif;
];

! ==============================================================================
! RUTINAS PRINCIPALES DE INICIALIZACIÓN
! ==============================================================================

[ SpanishCoreInit;
    ! ✅ AÑADIDO: Rutina principal de inicialización del core
    ! Inicialización principal del núcleo coordinador
    
    #Ifdef DEBUG;
        print "^[SpanishCore v", (string) SPANISH_CORE_VERSION, " iniciando...]^";
    #Endif;
    
    ! Verificar dependencias críticas
    if (~~SpanishValidateSystem()) {
        print "^[ERROR CRÍTICO: Sistema español no puede inicializarse]^";
        return SpanishEmergencyFallback();
    }
    
    ! Coordinar módulos
    SpanishCoreCoordinate();
    
    ! Llamar inicializadores
    SpanishCoreCallInitializers();
    
    ! Marcar como completo
    spanish_initialized = true;
    
    #Ifdef DEBUG;
        print "[SpanishCore inicializado correctamente]^";
        SpanishCoreStatus();
    #Endif;
    
    return true;
];

! ==============================================================================
! CONSTANTES DE FINALIZACIÓN
! ==============================================================================

Constant SPANISH_CORE_COMPLETE;
Constant SPANISH_COORDINATOR_READY;

! Información del módulo
Constant SPANISH_CORE_FEATURES = "Coordinación, inicialización, fallback, validación";
Constant SPANISH_CORE_FUNCTIONS = 10; ! Número de funciones públicas

#Endif; ! SPANISH_CORE_INCLUDED

! ==============================================================================
! Fin de SpanishCore.h - Núcleo coordinador limpio y sin duplicaciones
! ==============================================================================