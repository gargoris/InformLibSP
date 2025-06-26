! ==============================================================================
! SPANISHREGIONAL.H - Sistema modular de variantes regionales
! Extensión OPCIONAL para la librería española existente
! Implementación con cambios mínimos - compatibilidad total hacia atrás
! ==============================================================================

System_file;

#Ifndef SPANISH_REGIONAL_INCLUDED;
Constant SPANISH_REGIONAL_INCLUDED;
Constant SPANISH_REGIONAL_VERSION = "1.0-minimal";

! Verificación de dependencias
#Ifndef SPANISH_LIB_INCLUDED;
  Message fatalerror "*** Include Spanish.h antes de SpanishRegional.h ***";
#Endif;

! ==============================================================================
! CONFIGURACIÓN REGIONAL - ACTIVACIÓN OPCIONAL
! ==============================================================================

! El desarrollador puede definir estas constantes ANTES de Include Spanish.h
! Si no se define nada, usa comportamiento estándar (neutral)

#Ifndef SPANISH_REGION;
    Constant SPANISH_REGION = 0;  ! 0=neutral, 1=México, 2=Argentina, 3=España
#Endif;

#Ifndef SPANISH_FORMALITY_DEFAULT;
    #If SPANISH_REGION == 3;        ! España - más formal
        Constant SPANISH_FORMALITY_DEFAULT = 1;
    #Ifnot;
        Constant SPANISH_FORMALITY_DEFAULT = 0;  ! Latinoamérica - más informal
    #Endif;
#Endif;

! ==============================================================================
! CONSTANTES REGIONALES
! ==============================================================================

! Códigos de región
Constant REGION_NEUTRAL = 0;
Constant REGION_MEXICO = 1;
Constant REGION_ARGENTINA = 2;
Constant REGION_SPAIN = 3;
Constant REGION_COLOMBIA = 4;
Constant REGION_CHILE = 5;

! Variables globales para configuración dinámica
Global current_spanish_region = SPANISH_REGION;
Global voseo_enabled = false;
Global regional_vocabulary = true;

! ==============================================================================
! DETECCIÓN Y CONFIGURACIÓN AUTOMÁTICA
! ==============================================================================

[ SpanishRegionalInit;
    current_spanish_region = SPANISH_REGION;
    
    ! Configuración automática basada en región
    switch (current_spanish_region) {
        REGION_ARGENTINA:
            voseo_enabled = true;
            FormalityLevel = 0;  ! Argentina es más informal
            
        REGION_SPAIN:
            voseo_enabled = false;
            FormalityLevel = 1;  ! España tiende a ser más formal
            
        REGION_MEXICO:
            voseo_enabled = false;
            FormalityLevel = 0;
            
        default:  ! NEUTRAL
            voseo_enabled = false;
            FormalityLevel = SPANISH_FORMALITY_DEFAULT;
    }
    
    #Ifdef DEBUG;
    print "[SpanishRegional inicializado - Región: ";
    switch (current_spanish_region) {
        REGION_MEXICO: print "México";
        REGION_ARGENTINA: print "Argentina";
        REGION_SPAIN: print "España";
        default: print "Neutral";
    }
    print "]^";
    #Endif;
];

! ==============================================================================
! OVERRIDE MÍNIMO DEL SISTEMA DE CONJUGACIÓN EXISTENTE
! ==============================================================================

! Mantenemos las funciones originales y añadimos un wrapper regional
Replace ConjugarVerbo ConjugarVerbo_Original;

[ ConjugarVerbo verbo persona tiempo tipo;
    ! Si no hay voseo, usar el sistema original
    if (~~voseo_enabled || persona ~= 2) {
        return ConjugarVerbo_Original(verbo, persona, tiempo, tipo);
    }
    
    ! Solo si es Argentina y segunda persona, usar voseo
    if (current_spanish_region == REGION_ARGENTINA && persona == 2) {
        return ConjugarVoseo(verbo, tiempo, tipo);
    }
    
    ! Fallback al sistema original
    return ConjugarVerbo_Original(verbo, persona, tiempo, tipo);
];

! ==============================================================================
! SISTEMA DE VOSEO ARGENTINO (MÍNIMO)
! ==============================================================================

[ ConjugarVoseo verbo tiempo tipo;
    ! Solo implementar los casos más comunes
    if (tipo == 0) tipo = DetectarTipoVerbo(verbo);
    
    switch(tiempo) {
        PRESENTE_T:
            switch(tipo) {
                1: print (string) verbo, "ás";     ! caminar -> caminás
                2: print (string) verbo, "és";     ! comer -> comés  
                3: print (string) verbo, "ís";     ! vivir -> vivís
                default: 
                    ! Para irregulares, usar formas conocidas
                    if (verbo == "ser") { print "sos"; rtrue; }
                    if (verbo == "tener") { print "tenés"; rtrue; }
                    if (verbo == "estar") { print "estás"; rtrue; }
                    ! Fallback a forma estándar
                    return ConjugarVerbo_Original(verbo, 2, tiempo, tipo);
            }
        default:
            ! Para otros tiempos, usar conjugación estándar
            return ConjugarVerbo_Original(verbo, 2, tiempo, tipo);
    }
    rtrue;
];

! ==============================================================================
! VOCABULARIO REGIONAL - SISTEMA DE LOOKUP SIMPLE
! ==============================================================================

! Tabla de equivalencias léxicas básicas
Array regional_vocabulary_table table
    ! Palabra_estándar, Región, Palabra_regional
    'computadora'   REGION_SPAIN      'ordenador'
    'coche'         REGION_MEXICO     'carro'
    'coche'         REGION_ARGENTINA  'auto'
    'autobús'       REGION_MEXICO     'camión'
    'patata'        REGION_MEXICO     'papa'
    'zumo'          REGION_MEXICO     'jugo'
    'gafas'         REGION_MEXICO     'lentes'
    'móvil'         REGION_MEXICO     'celular'
    'piso'          REGION_MEXICO     'departamento'
    'vale'          REGION_MEXICO     'órale'
    'coger'         REGION_MEXICO     'tomar';  ! Importante para México

! Función para obtener equivalencia regional
[ GetRegionalWord standard_word;
    local i;
    
    if (~~regional_vocabulary) return 0;  ! Vocabulario regional desactivado
    
    ! Buscar en la tabla
    for (i = 0: i < regional_vocabulary_table-->0: i = i + 3) {
        if (regional_vocabulary_table-->(i+1) == standard_word &&
            regional_vocabulary_table-->(i+2) == current_spanish_region) {
            return regional_vocabulary_table-->(i+3);
        }
    }
    
    return 0;  ! No hay equivalencia regional
];

! ==============================================================================
! MENSAJES REGIONALES - OVERRIDE MÍNIMO
! ==============================================================================

! Solo overrideamos LanguageLM si hay mensajes específicos importantes
#Ifdef SPANISH_REGIONAL_MESSAGES;

Replace LanguageLM LanguageLM_Original;

[ LanguageLM n x1 x2;
    ! Primero intentar mensaje regional
    if (GetRegionalMessage(n, x1, x2)) rtrue;
    
    ! Fallback al sistema original
    return LanguageLM_Original(n, x1, x2);
];

[ GetRegionalMessage n x1 x2;
    ! Solo algunos mensajes clave que varían por región
    
    if (current_spanish_region == REGION_MEXICO) {
        switch(n) {
            Take:
                switch(x1) {
                    1: print "Tomado."; rtrue;  ! México prefiere "tomar"
                }
            Miscellany:
                switch(x1) {
                    26: print "Esa palabra no la entiendo."; rtrue;  ! Más mexicano
                }
        }
    }
    
    if (current_spanish_region == REGION_ARGENTINA) {
        switch(n) {
            Take:
                switch(x1) {
                    1: print "Agarrado."; rtrue;  ! Argentina prefiere "agarrar"
                }
        }
    }
    
    rfalse;  ! No hay mensaje regional específico
];

#Endif;

! ==============================================================================
! DETECCIÓN DE PRONOMBRES REGIONALES
! ==============================================================================

! Override mínimo del sistema de pronombres para voseo
Replace LanguageRefers LanguageRefers_Original;

[ LanguageRefers obj wn   word;
    word = wn-->0;
    
    ! Si es voseo argentino, manejar "vos"
    if (voseo_enabled && word == 'vos') {
        ! "vos" se refiere al player en segunda persona
        if (obj == player) rtrue;
    }
    
    ! Fallback al sistema original
    return LanguageRefers_Original(obj, wn);
];

! ==============================================================================
! EXPRESIONES IDIOMÁTICAS REGIONALES
! ==============================================================================

[ GetRegionalExpression expression_type;
    ! Expresiones de asentimiento
    if (expression_type == 1) {  ! "Sí, de acuerdo"
        switch(current_spanish_region) {
            REGION_MEXICO: print "¡Órale, sí!";
            REGION_ARGENTINA: print "¡Dale!";
            REGION_SPAIN: print "¡Vale!";
            default: print "Sí, de acuerdo.";
        }
        rtrue;
    }
    
    ! Expresiones de sorpresa
    if (expression_type == 2) {
        switch(current_spanish_region) {
            REGION_MEXICO: print "¡No manches!";
            REGION_ARGENTINA: print "¡No me digas!";
            REGION_SPAIN: print "¡No me jodas!";
            default: print "¡No puede ser!";
        }
        rtrue;
    }
    
    rfalse;
];

! ==============================================================================
! CONFIGURACIÓN DINÁMICA - API PARA EL DESARROLLADOR
! ==============================================================================

[ SetSpanishRegion new_region;
    current_spanish_region = new_region;
    SpanishRegionalInit();  ! Reconfigurar según nueva región
    
    print "Región española cambiada a: ";
    switch(new_region) {
        REGION_MEXICO: print "México";
        REGION_ARGENTINA: print "Argentina";  
        REGION_SPAIN: print "España";
        default: print "Neutral";
    }
    print ".^";
];

[ ToggleVoseo;
    if (voseo_enabled) {
        voseo_enabled = false;
        print "Voseo desactivado.^";
    } else {
        voseo_enabled = true; 
        print "Voseo activado.^";
    }
];

[ ToggleRegionalVocabulary;
    if (regional_vocabulary) {
        regional_vocabulary = false;
        print "Vocabulario regional desactivado.^";
    } else {
        regional_vocabulary = true;
        print "Vocabulario regional activado.^";
    }
];

! ==============================================================================
! COMANDOS DE DEPURACIÓN REGIONALES
! ==============================================================================

#Ifdef DEBUG;

[ RegionalDebugCommand;
    print "^=== CONFIGURACIÓN REGIONAL ACTUAL ===^";
    print "Región: ";
    switch(current_spanish_region) {
        REGION_MEXICO: print "México";
        REGION_ARGENTINA: print "Argentina";
        REGION_SPAIN: print "España";
        default: print "Neutral";
    }
    print "^";
    
    print "Voseo: ";
    if (voseo_enabled) print "Activado"; else print "Desactivado";
    print "^";
    
    print "Vocabulario regional: ";
    if (regional_vocabulary) print "Activado"; else print "Desactivado";
    print "^";
    
    print "Nivel de formalidad: ";
    if (FormalityLevel) print "Formal (usted)"; else print "Informal (tú)";
    print "^";
    
    ! Probar conjugación voseo
    if (voseo_enabled) {
        print "^Prueba de voseo:^";
        print "  tener (vos): "; ConjugarVoseo("tener", PRESENTE_T, 0); print "^";
        print "  ser (vos): "; ConjugarVoseo("ser", PRESENTE_T, 0); print "^";
    }
];

#Endif;

! ==============================================================================
! INTEGRACIÓN CON EL SISTEMA PRINCIPAL
! ==============================================================================

! Auto-inicialización cuando se carga este módulo
[ SpanishRegionalAutoInit;
    SpanishRegionalInit();
];

! Llamar auto-inicialización al cargar (si está definido el hook)
#Ifdef SPANISH_AFTER_INIT_HOOK;
    SpanishRegionalAutoInit();
#Endif;

#Endif; ! SPANISH_REGIONAL_INCLUDED

! ==============================================================================
! Fin de SpanishRegional.h - Sistema regional mínimo y opcional
! ==============================================================================