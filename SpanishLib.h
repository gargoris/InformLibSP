! ==============================================================================
!   SPANISHLIB:  Librería en español para Inform 6
!
!   Basado en la librería Inform 6 -- Release 6.12.7 -- Serial number 240410
!
!   Copyright Graham Nelson 1993-2004 and David Griffith 2012-2024
!   Adaptación al español por Francisco Fuentes, 2025
!
!   This code is licensed under either the traditional Inform license as
!   described by the DM4 or the Artistic License version 2.0.
!
! ==============================================================================

System_file;

#Ifndef SPANISH_LIB_INCLUDED;
Constant SPANISH_LIB_INCLUDED;
Constant SPANISH_LIB_VERSION = "6.12.7-1.0";

! ==============================================================================
!   VERIFICACIÓN DE ENTORNO
! ==============================================================================

#Ifdef LIBRARY_STAGE;
#Iffalse LIBRARY_STAGE >= AFTER_PARSER;
  Message fatalerror "*** Incluye Parser.h y VerbLib.h antes de SpanishLib.h ***";
#Endif;
#Endif;

! ==============================================================================
!   CONFIGURACIÓN DE CARACTERÍSTICAS
! ==============================================================================

! El usuario puede definir estas constantes ANTES de incluir SpanishLib.h
! para activar características específicas:

! Si no está definido SPANISH_MINIMAL, cargar características completas
#Ifndef SPANISH_MINIMAL;
    #Ifndef SPANISH_FULL_MESSAGES; Constant SPANISH_FULL_MESSAGES; #Endif;
    #Ifndef SPANISH_GRAMMAR; Constant SPANISH_GRAMMAR; #Endif;
#Endif;

! ==============================================================================
!   NÚCLEO OBLIGATORIO
! ==============================================================================

! Incluir el archivo de definición del lenguaje español
Include "spanish.h";

! Incluir mensajes en español
#Ifdef SPANISH_FULL_MESSAGES;
    Include "SpanishMessages.h";
#Endif;

! Incluir gramática en español
#Ifdef SPANISH_GRAMMAR;
    Include "SpanishGrammar.h";
#Endif;

! ==============================================================================
!   RUTINA PRINCIPAL DE INICIALIZACIÓN
! ==============================================================================

[ SpanishLibInitialise;
    print "^[Librería en español v", (string) SPANISH_LIB_VERSION, " inicializando...]^";
    
    ! Inicializar el lenguaje
    LanguageInitialise();
    
    print "^[Librería en español lista para usar]^";
    return true;
];

! ==============================================================================
!   INFORMACIÓN DE CONFIGURACIÓN
! ==============================================================================

[ SpanishLibShowConfiguration;
    print "^[===== CONFIGURACIÓN CARGADA =====]^";
    print "[[OK] Núcleo: Definición del lenguaje español]^";
    
    #Ifdef SPANISH_FULL_MESSAGES;
        print "[[OK] Mensajes: Mensajes del sistema en español]^";
    #Ifnot;
        print "[ℹ️  Mensajes: Usando mensajes básicos]^";
    #Endif;
    
    #Ifdef SPANISH_GRAMMAR;
        print "[[OK] Gramática: Verbos y comandos en español]^";
    #Ifnot;
        print "[ℹ️  Gramática: Usando gramática básica]^";
    #Endif;
    
    print "[==============================]^";
];

! ==============================================================================
!   FIN DE LA LIBRERÍA
! ==============================================================================

#Endif; ! SPANISH_LIB_INCLUDED

! ==============================================================================! ==============================================================================
!   SPANISHLIB:  Librería en español para Inform 6
!
!   Basado en la librería Inform 6 -- Release 6.12.7 -- Serial number 240410
!
!   Copyright Graham Nelson 1993-2004 and David Griffith 2012-2024
!   Adaptación al español por Francisco Fuentes, 2025
!
!   This code is licensed under either the traditional Inform license as
!   described by the DM4 or the Artistic License version 2.0.
!
! ==============================================================================

System_file;

#Ifndef SPANISH_LIB_INCLUDED;
Constant SPANISH_LIB_INCLUDED;
Constant SPANISH_LIB_VERSION = "6.12.7-1.0";

! ==============================================================================
!   VERIFICACIÓN DE ENTORNO
! ==============================================================================

#Ifdef LIBRARY_STAGE;
#Iffalse LIBRARY_STAGE >= AFTER_PARSER;
  Message fatalerror "*** Incluye Parser.h y VerbLib.h antes de SpanishLib.h ***";
#Endif;
#Endif;

! ==============================================================================
!   CONFIGURACIÓN DE CARACTERÍSTICAS
! ==============================================================================

! El usuario puede definir estas constantes ANTES de incluir SpanishLib.h
! para activar características específicas:

! Si no está definido SPANISH_MINIMAL, cargar características completas
#Ifndef SPANISH_MINIMAL;
    #Ifndef SPANISH_FULL_MESSAGES; Constant SPANISH_FULL_MESSAGES; #Endif;
    #Ifndef SPANISH_GRAMMAR; Constant SPANISH_GRAMMAR; #Endif;
#Endif;

! ==============================================================================
!   NÚCLEO OBLIGATORIO
! ==============================================================================

! Incluir el archivo de definición del lenguaje español
Include "spanish.h";

! Incluir mensajes en español
#Ifdef SPANISH_FULL_MESSAGES;
    Include "SpanishMessages.h";
#Endif;

! Incluir gramática en español
#Ifdef SPANISH_GRAMMAR;
    Include "SpanishGrammar.h";
#Endif;

! ==============================================================================
!   RUTINA PRINCIPAL DE INICIALIZACIÓN
! ==============================================================================

[ SpanishLibInitialise;
    print "^[Librería en español v", (string) SPANISH_LIB_VERSION, " inicializando...]^";
    
    ! Inicializar el lenguaje
    LanguageInitialise();
    
    print "^[Librería en español lista para usar]^";
    return true;
];

! ==============================================================================
!   INFORMACIÓN DE CONFIGURACIÓN
! ==============================================================================

[ SpanishLibShowConfiguration;
    print "^[===== CONFIGURACIÓN CARGADA =====]^";
    print "[[OK] Núcleo: Definición del lenguaje español]^";
    
    #Ifdef SPANISH_FULL_MESSAGES;
        print "[[OK] Mensajes: Mensajes del sistema en español]^";
    #Ifnot;
        print "[ℹ️  Mensajes: Usando mensajes básicos]^";
    #Endif;
    
    #Ifdef SPANISH_GRAMMAR;
        print "[[OK] Gramática: Verbos y comandos en español]^";
    #Ifnot;
        print "[ℹ️  Gramática: Usando gramática básica]^";
    #Endif;
    
    print "[==============================]^";
];

! ==============================================================================
!   FIN DE LA LIBRERÍA
! ==============================================================================

#Endif; ! SPANISH_LIB_INCLUDED

! ==============================================================================