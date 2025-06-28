! ==============================================================================
! SPANISHCORE.H - Nucleo coordinador del sistema modular espanol
! Sistema modular Spanish Library para Inform 6
! Compatible con Inform 6.42 y libreria estandar 6.12.7
! ==============================================================================

System_file;

#Ifndef SPANISH_CORE_INCLUDED;
Constant SPANISH_CORE_INCLUDED;
Constant SPANISH_CORE_VERSION = "1.2-coordinator-fixed";

! ==============================================================================
! VERIFICACION DE DEPENDENCIAS
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
! RUTINAS DE COORDINACION ENTRE MODULOS
! ==============================================================================

[ SpanishCoreCoordinate   modules_ok;
    ! Coordina la inicializacion de todos los modulos
    ! Se llama despues de que todos los modulos esten cargados
    
    modules_ok = 0;
    
    #Ifdef DEBUG;
        print "^[SpanishCore: Coordinando modulos...]^";
    #Endif;
    
    ! Verificar que los modulos principales esten listos
    #Ifdef SPANISH_PARSER_INCLUDED;
        spanish_parser_ready = true;
        MarkModuleLoaded('parser');
        modules_ok++;
        #Ifdef DEBUG;
            print "[[OK] Parser cargado]^";
        #Endif;
    #Ifnot;
        #Ifdef DEBUG;
            print "[[!] Parser basico solamente]^";
        #Endif;
    #Endif;
    
    #Ifdef SPANISH_VERBS_INCLUDED;
        spanish_verbs_ready = true;
        MarkModuleLoaded('verbs');
        modules_ok++;
        #Ifdef DEBUG;
            print "[[OK] Verbos cargados]^";
        #Endif;
    #Ifnot;
        #Ifdef DEBUG;
            print "[[X] Sin sistema de verbos]^";
        #Endif;
    #Endif;
    
    #Ifdef SPANISH_GRAMMAR_INCLUDED;
        spanish_grammar_ready = true;
        MarkModuleLoaded('grammar');
        modules_ok++;
        #Ifdef DEBUG;
            print "[[OK] Gramatica cargada]^";
        #Endif;
    #Ifnot;
        #Ifdef DEBUG;
            print "[[X] Sin sistema de gramatica]^";
        #Endif;
    #Endif;
    
    #Ifdef SPANISH_MESSAGES_COMPLETE;
        spanish_messages_ready = true;
        MarkModuleLoaded('messages');
        modules_ok++;
        #Ifdef DEBUG;
            print "[[OK] Mensajes completos cargados]^";
        #Endif;
    #Endif;
    
    ! Marcar este modulo como cargado
    MarkModuleLoaded('core');
    
    #Ifdef DEBUG;
        print "[SpanishCore: ", modules_ok, " modulos principales coordinados]^";
    #Endif;
    
    return modules_ok;
];

! ==============================================================================
! INTEGRACION CON EL PARSER PRINCIPAL
! ==============================================================================

#Ifndef LanguageToInformese;
[ LanguageToInformese;
    ! Esta funcion coordina el procesamiento pero la logica real
    ! esta en SpanishParser.h para evitar duplicaciones
    
    #Ifdef SPANISH_PARSER_INCLUDED;
        return SpanishParserMain();
    #Ifnot;
        ! Procesamiento basico si no hay parser avanzado
        return SpanishBasicParsing();
    #Endif;
];
#Endif;

[ SpanishBasicParsing   i j k changes;
    ! [OK] CORREGIDO: Funcion completa de procesamiento minimo
    ! Solo contracciones basicas para mantener funcionalidad minima
    
    changes = 0;
    
    #Ifdef DEBUG;
        print "[CORE] Procesamiento basico: ", parse->1, " palabras^";
    #Endif;
    
    ! Solo procesar contracciones basicas
    for (i=0 : i<parse->1 : i++) {
        j = parse-->(2*i+1);
        
        ! Contraccion DEL = DE + EL
        if (j == 'del') {
            parse-->(2*i+1) = 'de';
            ! Insertar 'el' despues
            for (k=parse->1: k>i: k--) {
                parse-->(2*k+1) = parse-->(2*k-1);
                parse-->(2*k+2) = parse-->(2*k);
            }
            parse->1 = parse->1 + 1;
            parse-->(2*i+3) = 'el';
            parse-->(2*i+4) = 1;
            changes++;
            
            #Ifdef DEBUG;
                print "[CORE] Contraccion procesada: del -> de el^";
            #Endif;
        }
        
        ! Contraccion AL = A + EL
        if (j == 'al') {
            parse-->(2*i+1) = 'a';
            ! Insertar 'el' despues
            for (k=parse->1: k>i: k--) {
                parse-->(2*k+1) = parse-->(2*k-1);
                parse-->(2*k+2) = parse-->(2*k);
            }
            parse->1 = parse->1 + 1;
            parse-->(2*i+3) = 'el';
            parse-->(2*i+4) = 1;
            changes++;
            
            #Ifdef DEBUG;
                print "[CORE] Contraccion procesada: al -> a el^";
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
! RUTINAS DE COORDINACION DE INICIALIZACION
! ==============================================================================

[ SpanishCoreCallInitializers;
    ! [OK] CORREGIDO: Funcion completa para llamar inicializadores
    ! Llama a los inicializadores de todos los modulos en orden
    
    #Ifdef DEBUG;
        print "^[Inicializando modulos del sistema espanol...]^";
    #Endif;
    
    ! 1. Constantes (ya inicializadas)
    SpanishConstantsInit();
    
    ! 2. Parser (si esta disponible)
    #Ifdef SPANISH_PARSER_INCLUDED;
        #Ifdef SPANISH_PARSER_PART3_COMPLETE;
            SpanishParserInitialize();
        #Endif;
    #Endif;
    
    ! 3. Gramatica (si esta disponible)
    #Ifdef SPANISH_GRAMMAR_INCLUDED;
        ! La gramatica se inicializa automaticamente
        #Ifdef DEBUG;
            print "[SpanishGrammar cargado]^";
        #Endif;
    #Endif;
    
    ! 4. Verbos (si esta disponible)
    #Ifdef SPANISH_VERBS_INCLUDED;
        SpanishVerbsInitialise();
    #Endif;
    
    ! 5. Mensajes (si esta disponible)
    #Ifdef SPANISH_MESSAGES_COMPLETE;
        SpanishMessagesInitialise();
    #Endif;
    
    ! 6. Verbos irregulares (si esta disponible)
    #Ifdef SPANISH_IRREGULAR_VERBS_INCLUDED;
        SpanishIrregularVerbsInitialise();
        MarkModuleLoaded('irregular');
    #Endif;
    
    ! 7. Meta-comandos (si esta disponible)
    #Ifdef SPANISH_META_INCLUDED;
        SpanishMetaInitialise();
        MarkModuleLoaded('meta');
    #Endif;
    
    ! 8. Regional (si esta disponible)
    #Ifdef SPANISH_REGIONAL_INCLUDED;
        SpanishRegionalInit();
        MarkModuleLoaded('regional');
    #Endif;
    
    ! Marcar sistema como inicializado
    spanish_initialized = true;
    
    #Ifdef DEBUG;
        print "[Sistema espanol completamente inicializado]^";
    #Endif;
];

! ==============================================================================
! RUTINAS DE ESTADO Y MONITOREO
! ==============================================================================

[ SpanishCoreStatus;
    print "^=== ESTADO DEL NUCLEO ESPANOL ===^";
    print "Version del nucleo: ", (string) SPANISH_CORE_VERSION, "^";
    print "Inicializado: ";
    if (spanish_initialized) print "Si"; else print "No";
    print "^";
    
    print "Formalidad: ";
    if (FormalityLevel == FORMAL) print "Formal (usted)";
    else print "Informal (tu)";
    print "^";
    
    print "Region: ";
    switch (current_spanish_region) {
        REGION_NEUTRAL: print "Neutral";
        REGION_MEXICO: print "Mexico";
        REGION_ARGENTINA: print "Argentina";
        REGION_SPAIN: print "Espana";
        REGION_COLOMBIA: print "Colombia";
        REGION_CHILE: print "Chile";
        default: print "Desconocida";
    }
    print "^";
    
    print "Voseo: ";
    if (voseo_enabled) print "Activo"; else print "Inactivo";
    print "^";
    
    print "^Modulos coordinados:^";
    print "- Parser: ";
    if (spanish_parser_ready) print "[OK]"; else print "[X]";
    print "^- Verbos: ";
    if (spanish_verbs_ready) print "[OK]"; else print "[X]";
    print "^- Gramatica: ";
    if (spanish_grammar_ready) print "[OK]"; else print "[X]";
    print "^- Mensajes: ";
    if (spanish_messages_ready) print "[OK]"; else print "[X]";
    print "^";
    
    print "Ultimo comando: ", last_command_length, " palabras^";
    print "Estado del parser: Etapa ", spanish_parse_stage, "^";
];

! ==============================================================================
! RUTINAS DE EMERGENCIA Y FALLBACK
! ==============================================================================

[ SpanishEmergencyFallback;
    ! [OK] CORREGIDO: Funcion completa de rutinas de emergencia
    ! Rutinas basicas en caso de que otros modulos fallen
    
    print "^[MODO DE EMERGENCIA: Funcionalidad basica del espanol]^";
    print "[Solo contracciones y parsing minimo disponibles]^";
    
    ! Configurar valores seguros
    FormalityLevel = INFORMAL;
    current_spanish_region = REGION_NEUTRAL;
    voseo_enabled = false;
    spanish_initialized = true;
    
    ! Marcar este modulo como cargado
    MarkModuleLoaded('core');
    
    ! Limpiar buffers
    spanish_buffer->0 = 0;
    if (spanish_temp_buffer) spanish_temp_buffer->0 = 0;
    
    #Ifdef DEBUG;
        print "[Modo de emergencia activado - funcionalidad limitada]^";
    #Endif;
    
    return true;
];

[ SpanishValidateSystem   errors;
    ! [OK] CORREGIDO: Funcion completa de validacion del sistema
    ! Verificar integridad del sistema
    errors = 0;
    
    #Ifdef DEBUG;
        print "^[Validando integridad del sistema espanol...]^";
    #Endif;
    
    ! Verificar constantes criticas
    if (PRESENTE_T == 0) {
        print "^[ERROR: Constantes de tiempo verbal no definidas]^";
        errors++;
    }
    
    if (MASCULINE == 0) {
        print "^[ERROR: Constantes de genero no definidas]^";
        errors++;
    }
    
    ! Verificar arrays criticos (solo si estan definidos)
    #Ifdef LIBRARY_STAGE;
    #Iffalse LIBRARY_STAGE >= AFTER_PARSER;
        ! Aun no se pueden verificar los arrays
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
    
    ! Verificar inicializacion de modulos criticos
    if (~~spanish_initialized) {
        print "^[ADVERTENCIA: Sistema no completamente inicializado]^";
    }
    
    if (errors > 0) {
        print "^[SISTEMA ESPANOL: ", errors, " errores detectados]^";
        print "[Recomendacion: Usar SpanishEmergencyFallback()]^";
        return false;
    }
    
    #Ifdef DEBUG;
        print "[Validacion completa: Sistema OK]^";
    #Endif;
    
    return true;
];

! ==============================================================================
! HOOKS PARA INTEGRACION AUTOMATICA
! ==============================================================================

[ SpanishCoreProcessCommand;
    ! Hook para procesamiento de comandos
    ! Actualizar estadisticas de comando
    last_command_length = parse->1;
    
    ! Guardar comando para AGAIN si meta-comandos estan disponibles
    #Ifdef SPANISH_META_INCLUDED;
        SpanishSaveCommand();
    #Endif;
    
    return false; ! Continuar procesamiento normal
];

[ SpanishCoreHandleError error_type;
    ! Hook para manejo de errores
    ! Delegar al sistema de meta-comandos si esta disponible
    #Ifdef SPANISH_META_INCLUDED;
        return SpanishParseError(error_type, 0);
    #Ifnot;
        ! Manejo basico de errores
        switch(error_type) {
            STUCK_PE: print "No entendi esa instruccion.";
            CANTSEE_PE: print "No puedes ver tal cosa aqui.";
            VAGUE_PE: print "No esta claro a que te refieres.";
            VERB_PE: print "Ese no es un verbo que reconozca.";
            default: print "Error en el comando.";
        }
        return true;
    #Endif;
];

! ==============================================================================
! RUTINAS PRINCIPALES DE INICIALIZACION
! ==============================================================================

[ SpanishCoreInit;
    ! [OK] ANADIDO: Rutina principal de inicializacion del core
    ! Inicializacion principal del nucleo coordinador
    
    #Ifdef DEBUG;
        print "^[SpanishCore v", (string) SPANISH_CORE_VERSION, " iniciando...]^";
    #Endif;
    
    ! Verificar dependencias criticas
    if (~~SpanishValidateSystem()) {
        print "^[ERROR CRITICO: Sistema espanol no puede inicializarse]^";
        return SpanishEmergencyFallback();
    }
    
    ! Coordinar modulos
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
! CONSTANTES DE FINALIZACION
! ==============================================================================

Constant SPANISH_CORE_COMPLETE;
Constant SPANISH_COORDINATOR_READY;

! Informacion del modulo
Constant SPANISH_CORE_FEATURES = "Coordinacion, inicializacion, fallback, validacion";
Constant SPANISH_CORE_FUNCTIONS = 10; ! Numero de funciones publicas

! Marcar completitud del modulo (ya definido en linea 452)

#Endif; ! SPANISH_CORE_INCLUDED

! ==============================================================================
! Fin de SpanishCore.h - Nucleo coordinador limpio y sin duplicaciones
! ==============================================================================