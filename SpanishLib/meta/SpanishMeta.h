! ==============================================================================
! SPANISHMETA.H - Sistema de Meta-comandos para la librería española de Inform 6
! Compatible con Inform 6.42 y librería estándar 6.12.7
! 
! FASE 3: Meta-comandos completos (UNDO, AGAIN, OOPS, etc.)
! Implementación modular que extiende el sistema principal Spanish.h
! ==============================================================================

System_file;

#Ifndef SPANISH_META_INCLUDED;
Constant SPANISH_META_INCLUDED;
Constant SPANISH_META_VERSION = "3.0-metacommands";

! Verificación de dependencias
#Ifndef SPANISH_MESSAGES_COMPLETE;
  Message fatalerror "*** Include Spanish.h antes de SpanishMeta.h ***";
#Endif;

! ==============================================================================
! VARIABLES GLOBALES PARA META-COMANDOS
! ==============================================================================

Global undo_disabled = false;
Global again_enabled = true;
Global oops_enabled = true;
Global last_command_valid = false;
Global oops_word = 0;
Global oops_position = 0;

! Buffer para el último comando ejecutado
Array last_command_buffer -> 120;
Array last_command_parse table 32;

! Variables para sistema de ayuda
Global help_context = 0;
Global commands_shown = false;

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
! IMPLEMENTACIÓN DE OOPS/CORRECCIÓN EN ESPAÑOL
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
! SISTEMA DE AYUDA INTEGRADO EN ESPAÑOL
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
    print "Este es un juego de ficción interactiva. Puedes usar comandos en español natural.^";
    print "^Comandos básicos:^";
    print "• MIRAR / EXAMINAR [objeto] - observar algo^";
    print "• TOMAR / COGER [objeto] - tomar algo^";
    print "• IR [dirección] - moverte (norte, sur, este, oeste, etc.)^";
    print "• INVENTARIO / I - ver qué llevas^";
    print "^Meta-comandos:^";
    print "• GUARDAR - guardar tu progreso^";
    print "• CARGAR - cargar una partida guardada^";
    print "• DESHACER - deshacer la última acción^";
    print "• REPETIR - repetir el último comando^";
    print "• AYUDA [tema] - obtener ayuda específica^";
    print "• SALIR - terminar el juego^";
    print "^Para ayuda específica, usa: AYUDA COMANDOS, AYUDA NAVEGACION, etc.^";
];

[ SpanishHelpCommands;
    print "^=== COMANDOS DISPONIBLES ===^";
    print "^Movimiento:^";
    print "• IR, CAMINAR, ENTRAR, SALIR, SUBIR, BAJAR^";
    print "• NORTE/N, SUR/S, ESTE/E, OESTE/O^";
    print "• NORDESTE/NE, NOROESTE/NO, SUDESTE/SE, SUDOESTE/SO^";
    print "• ARRIBA, ABAJO, ADENTRO, AFUERA^";
    print "^Manipulación:^";
    print "• TOMAR, COGER, DEJAR, SOLTAR^";
    print "• PONER [objeto] EN/SOBRE [lugar]^";
    print "• METER [objeto] EN [contenedor]^";
    print "• SACAR [objeto] DE [contenedor]^";
    print "^Observación:^";
    print "• MIRAR, EXAMINAR, VER, OBSERVAR^";
    print "• BUSCAR, REGISTRAR, REVISAR^";
    print "• ESCUCHAR, OLER, TOCAR, PROBAR^";
    print "^Interacción:^";
    print "• ABRIR, CERRAR, ENCENDER, APAGAR^";
    print "• EMPUJAR, TIRAR, GIRAR^";
    print "• ATACAR, GOLPEAR (si es necesario)^";
    print "^Usa AYUDA META para ver meta-comandos del sistema.^";
    commands_shown = true;
];

[ SpanishHelpNavigation;
    print "^=== NAVEGACIÓN ===^";
    print "Puedes moverte usando direcciones:^";
    print "• Básicas: NORTE (N), SUR (S), ESTE (E), OESTE (O)^";
    print "• Diagonales: NORDESTE (NE), NOROESTE (NO), SUDESTE (SE), SUDOESTE (SO)^";
    print "• Verticales: ARRIBA, ABAJO, SUBIR, BAJAR^";
    print "• Entradas: ENTRAR, ADENTRO, SALIR, AFUERA^";
    print "^También puedes usar:^";
    print "• IR AL NORTE (más natural)^";
    print "• CAMINAR HACIA EL SUR^";
    print "• ENTRAR EN LA CASA^";
    print "• SALIR DEL EDIFICIO^";
    print "^Si hay puertas, usa ABRIR PUERTA antes de pasar por ella.^";
];

[ SpanishHelpObjects;
    print "^=== MANIPULACIÓN DE OBJETOS ===^";
    print "^Tomar y dejar:^";
    print "• TOMAR/COGER [objeto] - tomar algo^";
    print "• DEJAR/SOLTAR [objeto] - soltar algo^";
    print "^Poner objetos:^";
    print "• PONER [objeto] EN [lugar] - colocar dentro^";
    print "• PONER [objeto] SOBRE [superficie] - colocar encima^";
    print "^Objetos múltiples:^";
    print "• TOMAR TODO - tomar todo lo disponible^";
    print "• DEJAR TODO - soltar todo lo que llevas^";
    print "• TOMAR TODO EXCEPTO [objeto] - tomar todo menos algo específico^";
    print "^Usar objetos:^";
    print "• USAR [objeto] - usar algo^";
    print "• ATACAR [enemigo] CON [arma] - usar un objeto como herramienta^";
    print "^Examinar:^";
    print "• EXAMINAR/MIRAR [objeto] - descripción detallada^";
    print "• BUSCAR EN [contenedor] - ver qué hay dentro^";
];

[ SpanishHelpMeta;
    print "^=== META-COMANDOS DEL SISTEMA ===^";
    print "^Comandos de partida:^";
    print "• GUARDAR/SAVE - guardar tu progreso^";
    print "• CARGAR/RESTORE - cargar partida guardada^";
    print "• REINICIAR/RESTART - empezar de nuevo^";
    print "• SALIR/QUIT - terminar el juego^";
    print "^Comandos de revisión:^";
    print "• DESHACER/UNDO - deshacer último comando^";
    print "• REPETIR/AGAIN/R - repetir último comando^";
    print "• CORRECCIÓN/OOPS [palabra] - corregir palabra mal escrita^";
    print "^Información:^";
    print "• INVENTARIO/I - ver qué llevas^";
    print "• PUNTOS/SCORE - ver tu puntuación^";
    print "• AYUDA [tema] - obtener ayuda^";
    print "• COMANDOS - ver esta lista^";
    print "^Modo de juego:^";
    print "• DETALLADO/VERBOSE - descripciones completas^";
    print "• BREVE/BRIEF - descripciones cortas^";
    print "• MÍNIMO/SUPERBRIEF - solo nombres de lugares^";
];

! ==============================================================================
! RUTINAS DE CONFIGURACIÓN Y MODO DE JUEGO
! ==============================================================================

[ SpanishNotifyOn;
    notify_mode = true;
    print "Notificación de puntuación activada.";
    rtrue;
];

[ SpanishNotifyOff;
    notify_mode = false;
    print "Notificación de puntuación desactivada.";
    rtrue;
];

[ SpanishBrief;
    lookmode = 1;
    print "El juego está ahora en modo breve, que da descripciones largas ";
    print "de lugares solo la primera vez que los visitas.";
    rtrue;
];

[ SpanishVerbose;
    lookmode = 2;
    print "El juego está ahora en modo detallado, que siempre da ";
    print "descripciones largas de lugares (a menos que hayas estado ahí recientemente).";
    rtrue;
];

[ SpanishSuperBrief;
    lookmode = 3;
    print "El juego está ahora en modo súper-breve, que siempre da ";
    print "descripciones cortas de lugares.";
    rtrue;
];

! ==============================================================================
! SISTEMA DE PRONOMBRES EN ESPAÑOL
! ==============================================================================

[ SpanishPronouns i obj;
    print "En este momento, los pronombres se refieren a:^";
    
    ! Pronombres de objeto directo
    if (PronounValue('le')) {
        obj = PronounValue('le');
        print "~le~ se refiere a "; print (the) obj; print "^";
    }
    if (PronounValue('la')) {
        obj = PronounValue('la');
        print "~la~ se refiere a "; print (the) obj; print "^";
    }
    if (PronounValue('lo')) {
        obj = PronounValue('lo');
        print "~lo~ se refiere a "; print (the) obj; print "^";
    }
    if (PronounValue('los')) {
        obj = PronounValue('los');
        print "~los~ se refiere a "; print (the) obj; print "^";
    }
    if (PronounValue('las')) {
        obj = PronounValue('las');
        print "~las~ se refiere a "; print (the) obj; print "^";
    }
    
    ! Verificar si no hay pronombres definidos
    if (PronounValue('le') == nothing && PronounValue('la') == nothing && 
        PronounValue('lo') == nothing && PronounValue('los') == nothing && 
        PronounValue('las') == nothing) {
        print "Ningún pronombre está definido en este momento.";
    }
    rtrue;
];

! ==============================================================================
! RUTINAS DE INTEGRACIÓN CON PARSER PRINCIPAL
! ==============================================================================

[ SpanishMetaParser word1 word2;
    ! Manejo de meta-comandos en español
    ! Esta función debe ser llamada desde el parser principal
    
    if (word1 == 'deshacer' or 'undo' or 'anular') {
        return SpanishUndo();
    }
    
    if (word1 == 'repetir' or 'again' or 'r' or 'g' or 'otra_vez') {
        return SpanishAgain();
    }
    
    if (word1 == 'corrección' or 'corregir' or 'oops' or 'ups') {
        return SpanishOops(word2);
    }
    
    if (word1 == 'ayuda' or 'help' or 'socorro') {
        return SpanishHelp(word2);
    }
    
    if (word1 == 'comandos' or 'commands' or 'verbos') {
        return SpanishHelpCommands();
    }
    
    if (word1 == 'pronombres' or 'pronouns') {
        return SpanishPronouns();
    }
    
    if (word1 == 'notificar_si' or 'notify_on') {
        return SpanishNotifyOn();
    }
    
    if (word1 == 'notificar_no' or 'notify_off') {
        return SpanishNotifyOff();
    }
    
    if (word1 == 'detallado' or 'verbose') {
        return SpanishVerbose();
    }
    
    if (word1 == 'breve' or 'brief') {
        return SpanishBrief();
    }
    
    if (word1 == 'mínimo' or 'superbrief') {
        return SpanishSuperBrief();
    }
    
    ! No es un meta-comando reconocido
    return false;
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
! RUTINAS DE INICIALIZACIÓN 
! ==============================================================================

[ SpanishMetaInitialise;
    ! Inicializar sistema de meta-comandos
    undo_disabled = false;
    again_enabled = true;
    oops_enabled = true;
    last_command_valid = false;
    commands_shown = false;
    help_context = 0;
    
    ! Limpiar buffers
    SpanishClearCommand();
    
    print "^[Sistema de meta-comandos en español inicializado]^";
    print "[✅ DESHACER, REPETIR, CORRECCIÓN disponibles]^";
    print "[✅ Sistema de ayuda integrado: AYUDA, COMANDOS]^";
    print "[✅ Configuración: DETALLADO, BREVE, NOTIFICAR]^";
    print "^[Usa AYUDA para empezar o COMANDOS para ver qué puedes hacer]^";
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
Constant SPANISH_COVERAGE_ESTIMATED = 85; ! % de cobertura con meta-comandos

#Endif; ! SPANISH_META_INCLUDED

! ==============================================================================
! Fin de SpanishMeta.h - Sistema completo de meta-comandos en español
! ==============================================================================