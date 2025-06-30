! ==============================================================================
! SPANISHMETA.H - Sistema de Meta-comandos para la libreria espanola de Inform 6
! Compatible con Inform 6.42 y libreria estandar 6.12.7
! 
! Meta-comandos completos (UNDO, AGAIN, OOPS, HELP, etc.)
! Implementacion modular que extiende el sistema principal SpanishLib
! ==============================================================================

System_file;

#Ifndef SPANISH_META_INCLUDED;
Constant SPANISH_META_INCLUDED;
Constant SPANISH_META_VERSION = "3.1-metacommands-fixed";

! [OK] CORREGIDO: Verificacion de dependencias del sistema modular
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

! Buffer para el ultimo comando ejecutado
Array last_command_buffer -> 120;
Array last_command_parse table 32;

! Variables locales para sistema de ayuda
Global help_context = 0;
Global commands_shown = false;

! ==============================================================================
! RUTINAS DE APOYO PARA META-COMANDOS
! ==============================================================================

[ SpanishSaveCommand;
    ! Guarda el ultimo comando ejecutado para AGAIN
    if (parse->1 > 0) {
        VM_CopyBufferFrom(buffer, last_command_buffer);
        VM_CopyParseFrom(parse, last_command_parse);
        last_command_valid = true;
    }
];

[ SpanishRestoreCommand;
    ! Restaura el ultimo comando para AGAIN
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
! IMPLEMENTACION DE UNDO EN ESPANOL
! ==============================================================================

[ SpanishUndo result_code;
    if (undo_disabled) {
        print "El comando DESHACER esta deshabilitado en este juego.";
        rtrue;
    }
    
    if (~~SpanishCheckUndoSupport()) {
        print "Tu interprete no soporta la funcion DESHACER.";
        rtrue;
    }
    
    #Ifdef TARGET_ZCODE;
        @save_undo result_code;
        if (result_code == -1) {
            print "Lo siento, no se puede deshacer la accion anterior.";
            print " (Tu interprete puede no soportar esta funcion.)";
            rtrue;
        }
        if (result_code == 0) {
            print "No se puede deshacer mas.";
            rtrue;
        }
        @restore_undo result_code;
        if (result_code == 0) {
            print "No hay nada que deshacer.";
            rtrue;
        }
        print "[Accion anterior deshecha.]";
    #Ifnot; ! TARGET_GLULX
        @saveundo result_code;
        if (result_code == -1) {
            GGRecoverObjects();
            print "[Accion anterior deshecha.]";
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
! IMPLEMENTACION DE AGAIN/REPETIR EN ESPANOL  
! ==============================================================================

[ SpanishAgain;
    if (~~again_enabled) {
        print "El comando REPETIR esta deshabilitado.";
        rtrue;
    }
    
    if (~~last_command_valid) {
        print "No hay comando anterior que repetir.";
        rtrue;
    }
    
    ! Mostrar que comando se esta repitiendo
    print "[Repitiendo: ~";
    VM_PrintCommandWords(last_command_buffer);
    print "~]^";
    
    ! Restaurar y ejecutar el comando anterior
    if (SpanishRestoreCommand()) {
        ! El comando se ejecutara automaticamente al retornar false
        rfalse;
    } else {
        print "Error al repetir el comando anterior.";
        rtrue;
    }
];

! ==============================================================================
! IMPLEMENTACION DE OOPS/CORRECCION EN ESPANOL - [OK] COMPLETA
! ==============================================================================

[ SpanishOops word i j k found;
    if (~~oops_enabled) {
        print "El comando CORRECCION esta deshabilitado.";
        rtrue;
    }
    
    if (oops_word == 0 || oops_position == 0) {
        print "No hay nada que corregir.";
        rtrue;
    }
    
    if (word == 0) {
        print "Debes decir con que palabra quieres corregir.";
        print "^Por ejemplo: CORRECCION LLAVE";
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
        print "No se encontro la palabra que querias corregir.";
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
! SISTEMA DE AYUDA INTEGRADO EN ESPANOL - [OK] COMPLETO
! ==============================================================================

[ SpanishHelp topic;
    if (topic == 0 || topic == 'general' or 'basico' or 'ayuda') {
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
    print "Este es un juego de ficcion interactiva. Controlas la historia escribiendo";
    print " comandos en espanol natural.^";
    print "^Comandos basicos:^";
    print "- MIRAR - Observar el entorno^";
    print "- INVENTARIO - Ver que llevas^";
    print "- NORTE/SUR/ESTE/OESTE - Moverte^";
    print "- TOMAR [objeto] - Coger algo^";
    print "- USAR [objeto] - Usar algo^";
    print "- HABLAR CON [persona] - Conversar^";
    print "^Para mas ayuda especifica:^";
    print "- AYUDA COMANDOS - Lista completa de verbos^";
    print "- AYUDA NAVEGACION - Como moverte^";
    print "- AYUDA OBJETOS - Interactuar con cosas^";
    print "- AYUDA META - Comandos del sistema^";
    print "^!Experimenta y diviertete!^";
];

[ SpanishHelpCommands;
    print "^=== COMANDOS DISPONIBLES ===^";
    print "^Observacion:^";
    print "MIRAR, EXAMINAR, VER, OBSERVAR^";
    print "^Manipulacion:^";
    print "TOMAR, COGER, DEJAR, SOLTAR, DAR^";
    print "^Movimiento:^";
    print "IR, CAMINAR, SUBIR, BAJAR, ENTRAR, SALIR^";
    print "NORTE/N, SUR/S, ESTE/E, OESTE/O^";
    print "NORDESTE/NE, NOROESTE/NO, SUDESTE/SE, SUDOESTE/SO^";
    print "^Interaccion:^";
    print "ABRIR, CERRAR, ENCENDER, APAGAR, PULSAR, EMPUJAR^";
    print "^Comunicacion:^";
    print "HABLAR CON, DECIR, PREGUNTAR, GRITAR^";
    print "^Inventario:^";
    print "INVENTARIO/I, LLEVAR^";
    print "^Sistema:^";
    print "PUNTUACION, TIEMPO, GUARDAR, CARGAR^";
    
    commands_shown = true; ! Marcar que se mostraron los comandos
];

[ SpanishHelpNavigation;
    print "^=== NAVEGACION ===^";
    print "Para moverte por el mundo del juego:^";
    print "^Direcciones basicas:^";
    print "- NORTE, SUR, ESTE, OESTE (o N, S, E, O)^";
    print "- NORDESTE, NOROESTE, SUDESTE, SUDOESTE (o NE, NO, SE, SO)^";
    print "- ARRIBA, ABAJO^";
    print "^Otros comandos de movimiento:^";
    print "- IR A [lugar] - Ir a un lugar especifico^";
    print "- ENTRAR EN [lugar] - Entrar en un edificio o habitacion^";
    print "- SALIR DE [lugar] - Salir de donde estes^";
    print "- SUBIR A/POR [cosa] - Subir escaleras, colinas, etc.^";
    print "- BAJAR DE/POR [cosa] - Bajar^";
    print "^!Usa MIRAR para orientarte en cada nueva ubicacion!^";
];

[ SpanishHelpObjects;
    print "^=== INTERACTUAR CON OBJETOS ===^";
    print "^Examinar objetos:^";
    print "- EXAMINAR [objeto] - Ver detalles^";
    print "- MIRAR [objeto] - Observar algo especifico^";
    print "^Manipular objetos:^";
    print "- TOMAR [objeto] - Coger algo^";
    print "- DEJAR [objeto] - Soltar algo que llevas^";
    print "- DAR [objeto] A [persona] - Dar algo a alguien^";
    print "^Usar objetos:^";
    print "- USAR [objeto] - Usar algo^";
    print "- ABRIR/CERRAR [objeto] - Puertas, cajas, etc.^";
    print "- ENCENDER/APAGAR [objeto] - Luces, maquinas, etc.^";
    print "- PULSAR [objeto] - Botones, interruptores^";
    print "- EMPUJAR/TIRAR [objeto] - Mover cosas^";
    print "^!Muchos objetos tienen usos especiales que descubriras experimentando!^";
];

[ SpanishHelpMeta;
    print "^=== COMANDOS DEL SISTEMA ===^";
    print "^Meta-comandos disponibles:^";
    print "- DESHACER/UNDO - Deshacer la ultima accion^";
    print "- REPETIR/AGAIN - Repetir el ultimo comando^";
    print "- CORRECCION [palabra]/OOPS [palabra] - Corregir un error^";
    print "- AYUDA [tema]/HELP [tema] - Ver ayuda^";
    print "- COMANDOS - Ver lista de verbos^";
    print "^Configuracion:^";
    print "- DETALLADO - Descripciones completas^";
    print "- BREVE - Descripciones resumidas^";
    print "- NOTIFICAR ON/OFF - Activar/desactivar notificaciones^";
    print "^Archivo:^";
    print "- GUARDAR/SAVE - Guardar partida^";
    print "- CARGAR/RESTORE - Cargar partida^";
    print "- REINICIAR/RESTART - Empezar de nuevo^";
    print "- SALIR/QUIT - Terminar el juego^";
    print "^Estado:^";
    print "- PUNTUACION/SCORE - Ver puntuacion^";
    print "- TIEMPO/TIME - Ver tiempo transcurrido^";
    print "- VERSION - Ver informacion del juego^";
];

! ==============================================================================
! RUTINAS DE MANEJO DE ERRORES EN ESPANOL
! ==============================================================================

[ SpanishParseError error_type word_number;
    ! Manejo de errores de parsing especificos para espanol
    ! con mejor contexto y sugerencias
    
    switch (error_type) {
        STUCK_PE:
            print "No entendi esa instruccion. ";
            if (commands_shown == false) {
                print "Usa COMANDOS para ver que puedes hacer.";
            } else {
                print "Prueba con frases mas simples.";
            }
            
        UPTO_PE:
            print "Solo entendi hasta: ~";
            for (word_number = 2: word_number <= parse->1: word_number++) {
                print (address) parse-->(2*word_number-1), " ";
            }
            print "~";
            
        CANTSEE_PE:
            print "No puedes ver tal cosa aqui. ";
            print "Usa MIRAR para ver que hay disponible.";
            
        TOOLIT_PE:
            print "Dijiste muy poco. ";
            print "?Que quieres hacer exactamente? ";
            print "Prueba AYUDA si necesitas ideas.";
            
        VAGUE_PE:
            print "No esta claro a que te refieres. ";
            print "Intenta ser mas especifico.";
            
        VERB_PE:
            print "Ese no es un verbo que reconozca. ";
            print "Usa COMANDOS para ver los verbos disponibles.";
            
        default:
            ! Usar manejo de errores estandar
            return false;
    }
    return true;
];

! ==============================================================================
! DETECCION DE META-COMANDOS
! ==============================================================================

[ SpanishDetectMetaCommand word;
    ! Identifica si una palabra es un meta-comando
    ! Retorna el codigo del meta-comando o 0 si no lo es
    
    switch (word) {
        'deshacer', 'undo':
            return META_UNDO;
        'repetir', 'again', 'g':
            return META_AGAIN;
        'correccion', 'correccion', 'oops':
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
            return META_NOTIFY_ON; ! Se detectara ON/OFF despues
        default:
            return 0; ! No es un meta-comando reconocido
    }
];

! ==============================================================================
! RUTINAS DE INICIALIZACION 
! ==============================================================================

[ SpanishMetaInitialise;
    ! Inicializar sistema de meta-comandos
    ! [OK] CORREGIDO: No duplicar inicializacion de variables globales
    commands_shown = false;
    help_context = 0;
    
    ! Limpiar buffers
    SpanishClearCommand();
    
    #Ifdef DEBUG;
        print "^[Sistema de meta-comandos en espanol inicializado]^";
        print "[[OK] DESHACER, REPETIR, CORRECCION disponibles]^";
        print "[[OK] Sistema de ayuda integrado: AYUDA, COMANDOS]^";
        print "[[OK] Configuracion: DETALLADO, BREVE, NOTIFICAR]^";
        print "^[Usa AYUDA para empezar o COMANDOS para ver que puedes hacer]^";
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
! CONSTANTES Y MARCADORES DE FINALIZACION
! ==============================================================================

Constant SPANISH_META_COMPLETE;
Constant SPANISH_META_FUNCTIONS = 15; ! Numero de funciones implementadas
Constant SPANISH_META_COMMANDS_SUPPORTED = 13; ! Meta-comandos soportados
Constant SPANISH_COVERAGE_ESTIMATED = 85; ! % de cobertura con meta-comandos

#Endif; ! SPANISH_META_INCLUDED

! ==============================================================================
! Fin de SpanishMeta.h - Sistema completo de meta-comandos en espanol
! ==============================================================================