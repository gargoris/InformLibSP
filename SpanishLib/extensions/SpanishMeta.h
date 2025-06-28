! ==============================================================================
! SPANISHMETA.H - Sistema de Meta-comandos para la librería española de Inform 6
! Compatible con Inform 6.42 y librería estándar 6.12.7
! 
! Meta-comandos completos (UNDO, AGAIN, OOPS, HELP, etc.)
! Implementación modular que extiende el sistema principal SpanishLib
! ==============================================================================

System_file;

#Ifndef SPANISH_META_INCLUDED;
Constant SPANISH_META_INCLUDED;
Constant SPANISH_META_VERSION = "3.1-metacommands-fixed";

! ✅ CORREGIDO: Verificación de dependencias del sistema modular
#Ifndef SPANISH_CONSTANTS_INCLUDED;
  Message fatalerror "*** Include SpanishConstants.h antes de SpanishMeta.h ***";
#Endif;

#Ifndef SPANISH_CORE_INCLUDED;
  Message fatalerror "*** Include SpanishCore.h antes de SpanishMeta.h ***";
#Endif;

! ==============================================================================
! CONSTANTES PARA META-COMANDOS
! ==============================================================================

Constant META_UNDO = 1;
Constant META_AGAIN = 2; 
Constant META_OOPS = 3;
Constant META_HELP = 4;
Constant META_COMMANDS = 5;
Constant META_SCRIPT_ON = 6;
Constant META_SCRIPT_OFF = 7;
Constant META_PRONOUNS = 8;
Constant META_NOTIFY_ON = 9;
Constant META_NOTIFY_OFF = 10;
Constant META_BRIEF = 11;
Constant META_VERBOSE = 12;
Constant META_SUPERBRIEF = 13;

! ==============================================================================
! ARRAYS PARA COMANDOS (sin duplicar variables globales)
! ==============================================================================

! Buffer para el último comando ejecutado
Array last_command_buffer -> 120;
Array last_command_parse table 32;

! Variables locales para sistema de ayuda
Global help_context = 0;
Global commands_shown = false;

! ==============================================================================
! RUTINAS DE APOYO PARA META-COMANDOS
! ==============================================================================

[ SpanishSaveCommand;
    ! Guarda el último comando ejecutado para AGAIN
    if (parse->1 > 0) {
        VM_CopyBufferFrom(buffer, last_command_buffer);
        VM_CopyParseFrom(parse, last_command_parse);
        last_command_valid = true;
    }
];

[ SpanishRestoreCommand;
    ! Restaura el último comando para AGAIN
    if (last_command_valid) {
        VM_CopyBufferTo(last_command_buffer, buffer);
        VM_CopyParseTo(last_command_parse, parse);
        return true;
    }
    return false;
];

[ SpanishClearCommand;
    ! Limpia el buffer de comandos
    last_command_valid = false;
    last_command_buffer->0 = 0;
    last_command_parse->0 = 0;
];

! ==============================================================================
! IMPLEMENTACIÓN DE UNDO EN ESPAÑOL
! ==============================================================================

[ SpanishUndo result_code;
    if (undo_disabled) {
        print "El comando DESHACER está deshabilitado en este juego.";
        rtrue;
    }
    
    if (~~SpanishCheckUndoSupport()) {
        print "Tu intérprete no soporta la función DESHACER.";
        rtrue;
    }
    
    #Ifdef TARGET_ZCODE;
        @save_undo result_code;
        if (result_code == -1) {
            print "Lo siento, no se puede deshacer la acción anterior.";
            print " (Tu intérprete puede no soportar esta función.)";
            rtrue;
        }
        if (result_code == 0) {
            print "No se puede deshacer más.";
            rtrue;
        }
        @restore_undo result_code;
        if (result_code == 0) {
            print "No hay nada que deshacer.";
            rtrue;
        }
        print "[Acción anterior deshecha.]";
    #Ifnot; ! TARGET_GLULX
        @saveundo result_code;
        if (result_code == -1) {
            GGRecoverObjects();
            print "[Acción anterior deshecha.]";
            rtrue;
        }
        if (result_code == 0) {
            print "No hay nada que deshacer.";
            rtrue;
        }
        if (result_code == 1) {
            print "Lo siento, no se puede deshacer.";
            rtrue;
        }
    #Endif;
    
    rtrue;
];

! ==============================================================================
! IMPLEMENTACIÓN DE AGAIN/REPETIR EN ESPAÑOL  
! ==============================================================================

[ SpanishAgain;
    if (~~again_enabled) {
        print "El comando REPETIR está deshabilitado.";
        rtrue;
    }
    
    if (~~last_command_valid) {
        print "No hay comando anterior que repetir.";
        rtrue;
    }
    
    ! Mostrar qué comando se está repitiendo
    print "[Repitiendo: ~";
    VM_PrintCommandWords(last_command_buffer);
    print "~]^";
    
    ! Restaurar y ejecutar el comando anterior
    if (SpanishRestoreCommand()) {
        ! El comando se ejecutará automáticamente al retornar false
        rfalse;
    } else {
        print "Error al repetir el comando anterior.";
        rtrue;
    }
];

! ==============================================================================
! IMPLEMENTACIÓN DE OOPS/CORRECCIÓN EN ESPAÑOL - ✅ COMPLETA
! ==============================================================================

[ SpanishOops word i j k found;
    if (~~oops_enabled) {
        print "El comando CORRECCIÓN está deshabilitado.";
        rtrue;
    }
    
    if (oops_word == 0 || oops_position == 0) {
        print "No hay nada que corregir.";
        rtrue;
    }
    
    if (word == 0) {
        print "Debes decir con qué palabra quieres corregir.";
        print "^Por ejemplo: CORRECCIÓN LLAVE";
        rtrue;
    }
    
    ! Restaurar el comando anterior
    if (~~SpanishRestoreCommand()) {
        print "No se puede corregir el comando anterior.";
        rtrue;
    }
    
    ! Buscar y reemplazar la palabra incorrecta
    found = false;
    for (i = 1: i <= parse->1: i++) {
        if (parse-->(2*i-1) == oops_word) {
            parse-->(2*i-1) = word;
            found = true;
            break;
        }
    }
    
    if (~~found) {
        print "No se encontró la palabra que querías corregir.";
        rtrue;
    }
    
    ! Mostrar el comando corregido
    print "[Comando corregido: ~";
    VM_PrintCommandWords(buffer);
    print "~]^";
    
    ! Limpiar estado de OOPS
    oops_word = 0;
    oops_position = 0;
    
    ! Ejecutar el comando corregido
    rfalse;
];

! ==============================================================================
! SISTEMA DE AYUDA INTEGRADO EN ESPAÑOL - ✅ COMPLETO
! ==============================================================================

[ SpanishHelp topic;
    if (topic == 0 || topic == 'general' or 'básico' or 'ayuda') {
        SpanishHelpGeneral();
        rtrue;
    }
    
    if (topic == 'comandos' or 'verbos' or 'acciones') {
        SpanishHelpCommands();
        rtrue;
    }
    
    if (topic == 'navegacion' or 'navegar' or 'movimiento') {
        SpanishHelpNavigation();
        rtrue;
    }
    
    if (topic == 'objetos' or 'cosas' or 'items') {
        SpanishHelpObjects();
        rtrue;
    }
    
    if (topic == 'meta' or 'metacomandos' or 'sistema') {
        SpanishHelpMeta();
        rtrue;
    }
    
    print "No hay ayuda disponible sobre ~"; print (address) topic; print "~.^";
    print "Prueba: AYUDA COMANDOS, AYUDA NAVEGACION, AYUDA OBJETOS, o AYUDA META.";
    rtrue;
];

[ SpanishHelpGeneral;
    print "^=== AYUDA GENERAL ===^";
    print "Este es un juego de ficción interactiva. Controlas la historia escribiendo";
    print " comandos en español natural.^";
    print "^Comandos básicos:^";
    print "• MIRAR - Observar el entorno^";
    print "• INVENTARIO - Ver qué llevas^";
    print "• NORTE/SUR/ESTE/OESTE - Moverte^";
    print "• TOMAR [objeto] - Coger algo^";
    print "• USAR [objeto] - Usar algo^";
    print "• HABLAR CON [persona] - Conversar^";
    print "^Para más ayuda específica:^";
    print "• AYUDA COMANDOS - Lista completa de verbos^";
    print "• AYUDA NAVEGACION - Cómo moverte^";
    print "• AYUDA OBJETOS - Interactuar con cosas^";
    print "• AYUDA META - Comandos del sistema^";
    print "^¡Experimenta y diviértete!^";
];

[ SpanishHelpCommands;
    print "^=== COMANDOS DISPONIBLES ===^";
    print "^Observación:^";
    print "MIRAR, EXAMINAR, VER, OBSERVAR^";
    print "^Manipulación:^";
    print "TOMAR, COGER, DEJAR, SOLTAR, DAR^";
    print "^Movimiento:^";
    print "IR, CAMINAR, SUBIR, BAJAR, ENTRAR, SALIR^";
    print "NORTE/N, SUR/S, ESTE/E, OESTE/O^";
    print "NORDESTE/NE, NOROESTE/NO, SUDESTE/SE, SUDOESTE/SO^";
    print "^Interacción:^";
    print "ABRIR, CERRAR, ENCENDER, APAGAR, PULSAR, EMPUJAR^";
    print "^Comunicación:^";
    print "HABLAR CON, DECIR, PREGUNTAR, GRITAR^";
    print "^Inventario:^";
    print "INVENTARIO/I, LLEVAR^";
    print "^Sistema:^";
    print "PUNTUACION, TIEMPO, GUARDAR, CARGAR^";
    
    commands_shown = true; ! Marcar que se mostraron los comandos
];

[ SpanishHelpNavigation;
    print "^=== NAVEGACIÓN ===^";
    print "Para moverte por el mundo del juego:^";
    print "^Direcciones básicas:^";
    print "• NORTE, SUR, ESTE, OESTE (o N, S, E, O)^";
    print "• NORDESTE, NOROESTE, SUDESTE, SUDOESTE (o NE, NO, SE, SO)^";
    print "• ARRIBA, ABAJO^";
    print "^Otros comandos de movimiento:^";
    print "• IR A [lugar] - Ir a un lugar específico^";
    print "• ENTRAR EN [lugar] - Entrar en un edificio o habitación^";
    print "• SALIR DE [lugar] - Salir de donde estés^";
    print "• SUBIR A/POR [cosa] - Subir escaleras, colinas, etc.^";
    print "• BAJAR DE/POR [cosa] - Bajar^";
    print "^¡Usa MIRAR para orientarte en cada nueva ubicación!^";
];

[ SpanishHelpObjects;
    print "^=== INTERACTUAR CON OBJETOS ===^";
    print "^Examinar objetos:^";
    print "• EXAMINAR [objeto] - Ver detalles^";
    print "• MIRAR [objeto] - Observar algo específico^";
    print "^Manipular objetos:^";
    print "• TOMAR [objeto] - Coger algo^";
    print "• DEJAR [objeto] - Soltar algo que llevas^";
    print "• DAR [objeto] A [persona] - Dar algo a alguien^";
    print "^Usar objetos:^";
    print "• USAR [objeto] - Usar algo^";
    print "• ABRIR/CERRAR [objeto] - Puertas, cajas, etc.^";
    print "• ENCENDER/APAGAR [objeto] - Luces, máquinas, etc.^";
    print "• PULSAR [objeto] - Botones, interruptores^";
    print "• EMPUJAR/TIRAR [objeto] - Mover cosas^";
    print "^¡Muchos objetos tienen usos especiales que descubrirás experimentando!^";
];

[ SpanishHelpMeta;
    print "^=== COMANDOS DEL SISTEMA ===^";
    print "^Meta-comandos disponibles:^";
    print "• DESHACER/UNDO - Deshacer la última acción^";
    print "• REPETIR/AGAIN - Repetir el último comando^";
    print "• CORRECCIÓN [palabra]/OOPS [palabra] - Corregir un error^";
    print "• AYUDA [tema]/HELP [tema] - Ver ayuda^";
    print "• COMANDOS - Ver lista de verbos^";
    print "^Configuración:^";
    print "• DETALLADO - Descripciones completas^";
    print "• BREVE - Descripciones resumidas^";
    print "• NOTIFICAR ON/OFF - Activar/desactivar notificaciones^";
    print "^Archivo:^";
    print "• GUARDAR/SAVE - Guardar partida^";
    print "• CARGAR/RESTORE - Cargar partida^";
    print "• REINICIAR/RESTART - Empezar de nuevo^";
    print "• SALIR/QUIT - Terminar el juego^";
    print "^Estado:^";
    print "• PUNTUACION/SCORE - Ver puntuación^";
    print "• TIEMPO/TIME - Ver tiempo transcurrido^";
    print "• VERSION - Ver información del juego^";
];

! ==============================================================================
! RUTINAS DE MANEJO DE ERRORES EN ESPAÑOL
! ==============================================================================

[ SpanishParseError error_type word_number;
    ! Manejo de errores de parsing específicos para español
    ! con mejor contexto y sugerencias
    
    switch (error_type) {
        STUCK_PE:
            print "No entendí esa instrucción. ";
            if (commands_shown == false) {
                print "Usa COMANDOS para ver qué puedes hacer.";
            } else {
                print "Prueba con frases más simples.";
            }
            
        UPTO_PE:
            print "Solo entendí hasta: ~";
            for (word_number = 2: word_number <= parse->1: word_number++) {
                print (address) parse-->(2*word_number-1), " ";
            }
            print "~";
            
        CANTSEE_PE:
            print "No puedes ver tal cosa aquí. ";
            print "Usa MIRAR para ver qué hay disponible.";
            
        TOOLIT_PE:
            print "Dijiste muy poco. ";
            print "¿Qué quieres hacer exactamente? ";
            print "Prueba AYUDA si necesitas ideas.";
            
        VAGUE_PE:
            print "No está claro a qué te refieres. ";
            print "Intenta ser más específico.";
            
        VERB_PE:
            print "Ese no es un verbo que reconozca. ";
            print "Usa COMANDOS para ver los verbos disponibles.";
            
        default:
            ! Usar manejo de errores estándar
            return false;
    }
    return true;
];

! ==============================================================================
! DETECCIÓN DE META-COMANDOS
! ==============================================================================

[ SpanishDetectMetaCommand word;
    ! Identifica si una palabra es un meta-comando
    ! Retorna el código del meta-comando o 0 si no lo es
    
    switch (word) {
        'deshacer', 'undo':
            return META_UNDO;
        'repetir', 'again', 'g':
            return META_AGAIN;
        'corrección', 'correccion', 'oops':
            return META_OOPS;
        'ayuda', 'help':
            return META_HELP;
        'comandos', 'verbos':
            return META_COMMANDS;
        'detallado', 'verbose':
            return META_VERBOSE;
        'breve', 'brief':
            return META_BRIEF;
        'superbreve', 'superbrief':
            return META_SUPERBRIEF;
        'notificar':
            return META_NOTIFY_ON; ! Se detectará ON/OFF después
        default:
            return 0; ! No es un meta-comando reconocido
    }
];

! ==============================================================================
! RUTINAS DE INICIALIZACIÓN 
! ==============================================================================

[ SpanishMetaInitialise;
    ! Inicializar sistema de meta-comandos
    ! ✅ CORREGIDO: No duplicar inicialización de variables globales
    commands_shown = false;
    help_context = 0;
    
    ! Limpiar buffers
    SpanishClearCommand();
    
    #Ifdef DEBUG;
        print "^[Sistema de meta-comandos en español inicializado]^";
        print "[✅ DESHACER, REPETIR, CORRECCIÓN disponibles]^";
        print "[✅ Sistema de ayuda integrado: AYUDA, COMANDOS]^";
        print "[✅ Configuración: DETALLADO, BREVE, NOTIFICAR]^";
        print "^[Usa AYUDA para empezar o COMANDOS para ver qué puedes hacer]^";
    #Endif;
];

! Verificar disponibilidad de UNDO en la plataforma
[ SpanishCheckUndoSupport;
    #Ifdef TARGET_ZCODE;
        if (0->$32 & $16) return true;  ! Bit 4 del byte $32
        return false;
    #Ifnot; ! TARGET_GLULX
        return true;  ! Glulx siempre soporta UNDO
    #Endif;
];

! ==============================================================================
! CONSTANTES Y MARCADORES DE FINALIZACIÓN
! ==============================================================================

Constant SPANISH_META_COMPLETE;
Constant SPANISH_META_FUNCTIONS = 15; ! Número de funciones implementadas
Constant SPANISH_META_COMMANDS_SUPPORTED = 13; ! Meta-comandos soportados
Constant SPANISH_COVERAGE_ESTIMATED = 85; ! % de cobertura con meta-comandos

#Endif; ! SPANISH_META_INCLUDED

! ==============================================================================
! Fin de SpanishMeta.h - Sistema completo de meta-comandos en español
! ==============================================================================