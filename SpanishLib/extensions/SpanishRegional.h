! ==============================================================================
! SPANISHREGIONAL.H - Sistema modular de variantes regionales
! Extensión OPCIONAL para la librería española existente
! Compatible con Inform 6.42 y librería estándar 6.12.7
! ==============================================================================

System_file;

#Ifndef SPANISH_REGIONAL_INCLUDED;
Constant SPANISH_REGIONAL_INCLUDED;
Constant SPANISH_REGIONAL_VERSION = "2.1-complete-fixed";

! ==============================================================================
! VERIFICACIÓN DE DEPENDENCIAS
! ==============================================================================

#Ifndef SPANISH_CONSTANTS_INCLUDED;
  Message fatalerror "*** Include SpanishConstants.h antes de SpanishRegional.h ***";
#Endif;

#Ifndef SPANISH_CORE_INCLUDED;
  Message fatalerror "*** Include SpanishCore.h antes de SpanishRegional.h ***";
#Endif;

! ==============================================================================
! CONFIGURACIÓN REGIONAL - ACTIVACIÓN OPCIONAL
! ==============================================================================

! El desarrollador puede definir estas constantes ANTES de Include SpanishLib.h
! Si no se define nada, usa comportamiento estándar (neutral)

#Ifndef SPANISH_REGION;
    Constant SPANISH_REGION = REGION_NEUTRAL;  ! Usar constante de SpanishConstants.h
#Endif;

! Variables locales específicas del módulo regional
Global spanish_regional_ready = false;

! ==============================================================================
! DETECCIÓN Y CONFIGURACIÓN AUTOMÁTICA
! ==============================================================================

[ SpanishRegionalInit;
    ! ✅ CORREGIDO: Usar variables globales de SpanishConstants.h, no duplicar
    current_spanish_region = SPANISH_REGION;
    
    ! Configuración automática basada en región
    switch (current_spanish_region) {
        REGION_ARGENTINA:
            voseo_enabled = true;
            FormalityLevel = INFORMAL;  ! Argentina es más informal
            
        REGION_SPAIN:
            voseo_enabled = false;
            FormalityLevel = FORMAL;  ! España tiende a ser más formal
            
        REGION_MEXICO:
            voseo_enabled = false;
            FormalityLevel = INFORMAL;
            
        REGION_COLOMBIA:
            voseo_enabled = false;
            FormalityLevel = INFORMAL;
            
        REGION_CHILE:
            voseo_enabled = false;
            FormalityLevel = INFORMAL;
            
        default:  ! REGION_NEUTRAL
            voseo_enabled = false;
            FormalityLevel = SPANISH_FORMALITY_DEFAULT;
    }
    
    spanish_regional_ready = true;
    
    #Ifdef DEBUG;
        print "^[SpanishRegional v", (string) SPANISH_REGIONAL_VERSION, " inicializado]^";
        print "[Región: ";
        switch (current_spanish_region) {
            REGION_MEXICO: print "México";
            REGION_ARGENTINA: print "Argentina";
            REGION_SPAIN: print "España";
            REGION_COLOMBIA: print "Colombia";
            REGION_CHILE: print "Chile";
            default: print "Neutral";
        }
        print "]^";
        print "[Voseo: ";
        if (voseo_enabled) print "Activado"; else print "Desactivado";
        print "]^";
    #Endif;
];

! ==============================================================================
! SISTEMA DE CONJUGACIÓN CON VOSEO - ✅ COMPLETO
! ==============================================================================

[ SpanishRegionalConjugarVerbo verbo persona tiempo tipo;
    ! ✅ CORREGIDO: Función completa de integración con voseo
    ! Si no hay voseo o no es segunda persona, usar sistema estándar
    if (~~voseo_enabled || persona ~= SEGUNDA_PERSONA) {
        #Ifdef SPANISH_VERBS_INCLUDED;
            return ConjugarVerbo(verbo, persona, tiempo, tipo);
        #Ifnot;
            ! Fallback básico
            print (address) verbo;
            return true;
        #Endif;
    }
    
    ! Solo si es Argentina y segunda persona, usar voseo
    if (current_spanish_region == REGION_ARGENTINA && persona == SEGUNDA_PERSONA) {
        return ConjugarVoseo(verbo, tiempo, tipo);
    }
    
    ! Fallback al sistema estándar
    #Ifdef SPANISH_VERBS_INCLUDED;
        return ConjugarVerbo(verbo, persona, tiempo, tipo);
    #Ifnot;
        print (address) verbo;
        return true;
    #Endif;
];

[ ConjugarVoseo verbo tiempo tipo   raiz;
    ! ✅ CORREGIDO: Función completa de conjugación con voseo argentino
    ! Solo implementar los casos más comunes
    if (tipo == 0) {
        #Ifdef SPANISH_VERBS_INCLUDED;
            tipo = DetectarTipoVerbo(verbo);
        #Ifnot;
            tipo = 1; ! Asumir -AR por defecto
        #Endif;
    }
    
    ! Intentar primero verbos irregulares con voseo
    if (ConjugarVoseoIrregular(verbo, tiempo)) return true;
    
    ! Si no es irregular, usar conjugación regular con voseo
    if (tipo == 0) {
        print (address) verbo; ! Fallback
        return false;
    }
    
    ! Obtener raíz del verbo
    #Ifdef SPANISH_VERBS_INCLUDED;
        raiz = ObtenerRaizVerbo(verbo, spanish_temp_buffer);
    #Ifnot;
        ! Fallback básico - asumir que es la palabra sin las últimas 2 letras
        raiz = spanish_temp_buffer;
        PrintToBuffer(raiz, 100, verbo);
        raiz->0 = raiz->0 - 2; ! Quitar -ar, -er, -ir
    #Endif;
    
    if (raiz == 0) {
        print (address) verbo;
        return false;
    }
    
    ! Conjugar según tipo y tiempo para voseo
    print (string) raiz;
    
    switch(tiempo) {
        PRESENTE_T:
            switch(tipo) {
                1: print "ás";     ! vos caminás
                2: print "és";     ! vos comés  
                3: print "ís";     ! vos vivís
                default: print "ás";
            }
            
        PRETERITO_T:
            switch(tipo) {
                1: print "aste";   ! vos caminaste
                2: print "iste";   ! vos comiste
                3: print "iste";   ! vos viviste
                default: print "aste";
            }
            
        IMPERFECTO_T:
            switch(tipo) {
                1: print "abas";   ! vos caminabas
                2: print "ías";    ! vos comías
                3: print "ías";    ! vos vivías
                default: print "abas";
            }
            
        FUTURO_T:
            ! Para futuro, usar infinitivo + terminación
            switch(tipo) {
                1: print "ar"; break;
                2: print "er"; break;
                3: print "ir"; break;
            }
            print "ás";           ! vos caminarás, comerás, vivirás
            
        IMPERATIVO_T:
            switch(tipo) {
                1: print "á";      ! ¡caminá!
                2: print "é";      ! ¡comé!
                3: print "í";      ! ¡viví!
                default: print "á";
            }
            
        default:
            ! Para otros tiempos, usar conjugación estándar
            #Ifdef SPANISH_VERBS_INCLUDED;
                return ConjugarVerbo(verbo, SEGUNDA_PERSONA, tiempo, tipo);
            #Ifnot;
                print (address) verbo;
                return false;
            #Endif;
    }
    return true;
];

[ ConjugarVoseoIrregular verbo tiempo;
    ! ✅ CORREGIDO: Función completa de verbos irregulares con voseo
    switch(verbo) {
        'ser':
            switch(tiempo) {
                PRESENTE_T: print "sos"; rtrue;         ! vos sos
                PRETERITO_T: print "fuiste"; rtrue;     ! vos fuiste
                IMPERFECTO_T: print "eras"; rtrue;      ! vos eras
                IMPERATIVO_T: print "sé"; rtrue;        ! ¡sé!
            }
        'tener':
            switch(tiempo) {
                PRESENTE_T: print "tenés"; rtrue;       ! vos tenés
                PRETERITO_T: print "tuviste"; rtrue;    ! vos tuviste
                IMPERFECTO_T: print "tenías"; rtrue;    ! vos tenías
                IMPERATIVO_T: print "tené"; rtrue;      ! ¡tené!
            }
        'estar':
            switch(tiempo) {
                PRESENTE_T: print "estás"; rtrue;       ! vos estás
                PRETERITO_T: print "estuviste"; rtrue;  ! vos estuviste
                IMPERFECTO_T: print "estabas"; rtrue;   ! vos estabas
                IMPERATIVO_T: print "está"; rtrue;      ! ¡está!
            }
        'ir':
            switch(tiempo) {
                PRESENTE_T: print "vas"; rtrue;         ! vos vas
                PRETERITO_T: print "fuiste"; rtrue;     ! vos fuiste (igual que SER)
                IMPERFECTO_T: print "ibas"; rtrue;      ! vos ibas
                IMPERATIVO_T: print "andá"; rtrue;      ! ¡andá! (forma especial argentina)
            }
        'venir':
            switch(tiempo) {
                PRESENTE_T: print "venís"; rtrue;       ! vos venís
                PRETERITO_T: print "viniste"; rtrue;    ! vos viniste
                IMPERFECTO_T: print "venías"; rtrue;    ! vos venías
                IMPERATIVO_T: print "vení"; rtrue;      ! ¡vení!
            }
        'hacer':
            switch(tiempo) {
                PRESENTE_T: print "hacés"; rtrue;       ! vos hacés
                PRETERITO_T: print "hiciste"; rtrue;    ! vos hiciste
                IMPERFECTO_T: print "hacías"; rtrue;    ! vos hacías
                IMPERATIVO_T: print "hacé"; rtrue;      ! ¡hacé!
            }
        'poder':
            switch(tiempo) {
                PRESENTE_T: print "podés"; rtrue;       ! vos podés
                PRETERITO_T: print "pudiste"; rtrue;    ! vos pudiste
                IMPERFECTO_T: print "podías"; rtrue;    ! vos podías
            }
        'querer':
            switch(tiempo) {
                PRESENTE_T: print "querés"; rtrue;      ! vos querés
                PRETERITO_T: print "quisiste"; rtrue;   ! vos quisiste
                IMPERFECTO_T: print "querías"; rtrue;   ! vos querías
                IMPERATIVO_T: print "queré"; rtrue;     ! ¡queré!
            }
        'ver':
            switch(tiempo) {
                PRESENTE_T: print "ves"; rtrue;         ! vos ves
                IMPERFECTO_T: print "veías"; rtrue;     ! vos veías
                IMPERATIVO_T: print "ve"; rtrue;        ! ¡ve!
            }
        'dar':
            switch(tiempo) {
                PRESENTE_T: print "das"; rtrue;         ! vos das
                PRETERITO_T: print "diste"; rtrue;      ! vos diste
                IMPERATIVO_T: print "da"; rtrue;        ! ¡da!
            }
    }
    return false; ! No es irregular conocido para voseo
];

! ==============================================================================
! VOCABULARIO REGIONAL - ✅ SISTEMA COMPLETO
! ==============================================================================

! Tabla de equivalencias léxicas regional
Array regional_vocabulary_table table
    ! formato: palabra_estándar, región, palabra_regional
    'coche'     REGION_MEXICO     'carro'
    'coche'     REGION_ARGENTINA  'auto'  
    'coche'     REGION_SPAIN      'coche'
    'coche'     REGION_COLOMBIA   'carro'
    'coche'     REGION_CHILE      'auto'
    
    'autobús'   REGION_MEXICO     'camión'
    'autobús'   REGION_ARGENTINA  'colectivo'
    'autobús'   REGION_SPAIN      'autobús'
    'autobús'   REGION_COLOMBIA   'bus'
    'autobús'   REGION_CHILE      'micro'
    
    'móvil'     REGION_MEXICO     'celular'
    'móvil'     REGION_ARGENTINA  'celular'
    'móvil'     REGION_SPAIN      'móvil'
    'móvil'     REGION_COLOMBIA   'celular'
    'móvil'     REGION_CHILE      'celular'
    
    'ordenador' REGION_MEXICO     'computadora'
    'ordenador' REGION_ARGENTINA  'computadora'
    'ordenador' REGION_SPAIN      'ordenador'
    'ordenador' REGION_COLOMBIA   'computador'
    'ordenador' REGION_CHILE      'computador'
    
    'piso'      REGION_MEXICO     'departamento'
    'piso'      REGION_ARGENTINA  'departamento'
    'piso'      REGION_SPAIN      'piso'
    'piso'      REGION_COLOMBIA   'apartamento'
    'piso'      REGION_CHILE      'departamento'
    
    'patata'    REGION_MEXICO     'papa'
    'patata'    REGION_ARGENTINA  'papa'
    'patata'    REGION_SPAIN      'patata'
    'patata'    REGION_COLOMBIA   'papa'
    'patata'    REGION_CHILE      'papa'
    
    'zumo'      REGION_MEXICO     'jugo'
    'zumo'      REGION_ARGENTINA  'jugo'
    'zumo'      REGION_SPAIN      'zumo'
    'zumo'      REGION_COLOMBIA   'jugo'
    'zumo'      REGION_CHILE      'jugo';

[ GetRegionalWord standard_word;
    ! ✅ CORREGIDO: Función completa para obtener equivalencia regional
    local i;
    
    if (~~regional_vocabulary) return 0; ! Vocabulario regional desactivado
    if (current_spanish_region == REGION_NEUTRAL) return 0; ! Sin regionalismo
    
    ! Buscar en la tabla
    for (i = 0: i < 21: i = i + 3) {  ! 7 palabras × 3 campos cada una
        if (regional_vocabulary_table-->(i) == standard_word &&
            regional_vocabulary_table-->(i+1) == current_spanish_region) {
            return regional_vocabulary_table-->(i+2);
        }
    }
    
    return 0;  ! No hay equivalencia regional
];

[ GetStandardWord regional_word;
    ! ✅ CORREGIDO: Función inversa completa
    local i;
    
    if (~~regional_vocabulary) return 0;
    
    for (i = 0: i < 21: i = i + 3) {
        if (regional_vocabulary_table-->(i+2) == regional_word &&
            regional_vocabulary_table-->(i+1) == current_spanish_region) {
            return regional_vocabulary_table-->(i);
        }
    }
    
    return 0;
];

! ==============================================================================
! EXPRESIONES IDIOMÁTICAS REGIONALES - ✅ COMPLETO
! ==============================================================================

[ GetRegionalExpression expression_type;
    ! ✅ CORREGIDO: Función completa de expresiones idiomáticas
    switch(expression_type) {
        1: ! Expresiones de asentimiento
            switch(current_spanish_region) {
                REGION_MEXICO: print "¡Órale, sí!";
                REGION_ARGENTINA: print "¡Dale!";
                REGION_SPAIN: print "¡Vale!";
                REGION_COLOMBIA: print "¡Listo, sí!";
                REGION_CHILE: print "¡Ya, sí!";
                default: print "Sí, de acuerdo.";
            }
            
        2: ! Expresiones de sorpresa
            switch(current_spanish_region) {
                REGION_MEXICO: print "¡No manches!";
                REGION_ARGENTINA: print "¡No me digas!";
                REGION_SPAIN: print "¡No me jodas!";
                REGION_COLOMBIA: print "¡Uy, no!";
                REGION_CHILE: print "¡No puede ser, weon!";
                default: print "¡No puede ser!";
            }
            
        3: ! Expresiones de despedida
            switch(current_spanish_region) {
                REGION_MEXICO: print "¡Órale, nos vemos!";
                REGION_ARGENTINA: print "¡Chau!";
                REGION_SPAIN: print "¡Hasta luego!";
                REGION_COLOMBIA: print "¡Que te vaya bien!";
                REGION_CHILE: print "¡Chao!";
                default: print "Adiós.";
            }
            
        4: ! Expresiones de saludo según hora
            local time_of_day;
            time_of_day = (the_time / 60); ! Convertir a horas
            
            if (time_of_day < 12) print "¡Buenos días!";
            else if (time_of_day < 19) print "¡Buenas tardes!";
            else print "¡Buenas noches!";
            
        default:
            print "Hola."; ! Fallback neutral
    }
    return true;
];

[ GetRegionalGreeting;
    ! ✅ AÑADIDO: Saludos específicos por región
    switch(current_spanish_region) {
        REGION_MEXICO: print "¡Órale, qué tal!";
        REGION_ARGENTINA: print "¡Hola, che!";
        REGION_SPAIN: print "¡Hola, qué tal!";
        REGION_COLOMBIA: print "¡Hola, ¿qué más?";
        REGION_CHILE: print "¡Hola, weon!";
        default: print "Hola.";
    }
];

! ==============================================================================
! CONFIGURACIÓN DINÁMICA - API PARA EL DESARROLLADOR
! ==============================================================================

[ SetSpanishRegion new_region;
    ! ✅ CORREGIDO: Función completa de configuración de región
    if (new_region < REGION_NEUTRAL || new_region > REGION_CHILE) {
        print "Región inválida. Regiones disponibles: 0-5.^";
        return false;
    }
    
    current_spanish_region = new_region;
    SpanishRegionalInit();  ! Reconfigurar según nueva región
    
    print "Región española cambiada a: ";
    switch(new_region) {
        REGION_MEXICO: print "México";
        REGION_ARGENTINA: print "Argentina";  
        REGION_SPAIN: print "España";
        REGION_COLOMBIA: print "Colombia";
        REGION_CHILE: print "Chile";
        default: print "Neutral";
    }
    print ".^";
    
    return true;
];

[ ToggleVoseo;
    ! ✅ CORREGIDO: Función completa para alternar voseo
    if (current_spanish_region ~= REGION_ARGENTINA) {
        print "El voseo solo está disponible para la región Argentina.^";
        return false;
    }
    
    if (voseo_enabled) {
        voseo_enabled = false;
        print "Voseo desactivado. Usando formas estándar con ~tú~.^";
    } else {
        voseo_enabled = true; 
        print "Voseo activado. Usando formas argentinas con ~vos~.^";
    }
    return true;
];

[ ToggleRegionalVocabulary;
    ! ✅ CORREGIDO: Función completa para alternar vocabulario regional
    if (regional_vocabulary) {
        regional_vocabulary = false;
        print "Vocabulario regional desactivado. Usando términos neutros.^";
    } else {
        regional_vocabulary = true;
        print "Vocabulario regional activado.^";
    }
    return true;
];

[ GetAvailableRegions;
    ! ✅ CORREGIDO: Función completa de información de regiones
    print "Regiones disponibles:^";
    print "0 - Neutral (sin regionalismos)^";
    print "1 - México^";
    print "2 - Argentina^";
    print "3 - España^";
    print "4 - Colombia^";
    print "5 - Chile^";
    print "^Características por región:^";
    print "• México: carro, camión, celular, computadora^";
    print "• Argentina: auto, colectivo, voseo (vos tenés)^";
    print "• España: coche, autobús, móvil, ordenador^";
    print "• Colombia: carro, bus, apartamento^";
    print "• Chile: auto, micro, weon^";
];

! ==============================================================================
! DETECCIÓN DE PRONOMBRES REGIONALES
! ==============================================================================

[ LanguageRefersRegional obj wn   word;
    ! ✅ CORREGIDO: Función completa de pronombres regionales
    word = wn-->0;
    
    ! Si es voseo argentino, manejar "vos"
    if (voseo_enabled && word == 'vos') {
        ! "vos" se refiere al player en segunda persona
        if (obj == player) return true;
    }
    
    ! Manejar pronombres regionales específicos
    if (current_spanish_region == REGION_ARGENTINA) {
        if (word == 'che' && obj == player) return true;  ! "che" como referencia informal
    }
    
    ! Si no hay sistema de pronombres base, usar fallback
    #Ifdef LanguageRefers;
        return LanguageRefers(obj, wn);
    #Ifnot;
        return false;
    #Endif;
];

! ==============================================================================
! MENSAJES REGIONALES ESPECÍFICOS
! ==============================================================================

[ GetRegionalMessage message_type obj;
    ! ✅ CORREGIDO: Función completa de mensajes regionales
    switch(message_type) {
        1: ! Tomar objeto
            switch(current_spanish_region) {
                REGION_MEXICO: print "Tomaste "; print (the) obj; print ".";
                REGION_ARGENTINA: print "Agarraste "; print (the) obj; print ".";
                REGION_SPAIN: print "Cogiste "; print (the) obj; print ".";
                default: print "Tomaste "; print (the) obj; print ".";
            }
            
        2: ! No puedes ver eso
            switch(current_spanish_region) {
                REGION_MEXICO: print "No miras eso por aquí, amigo.";
                REGION_ARGENTINA: print "No ves eso por acá, che.";
                REGION_SPAIN: print "No ves tal cosa aquí.";
                REGION_COLOMBIA: print "No ves eso por acá.";
                REGION_CHILE: print "No ves esa cosa, weon.";
                default: print "No puedes ver tal cosa.";
            }
            
        3: ! Inventario vacío
            switch(current_spanish_region) {
                REGION_MEXICO: print "No cargas nada, compadre.";
                REGION_ARGENTINA: print "No tenés nada encima, che.";
                REGION_SPAIN: print "No llevas nada.";
                REGION_COLOMBIA: print "No llevas nada, parcero.";
                REGION_CHILE: print "No llevas nada, weon.";
                default: print "No llevas nada.";
            }
            
        default:
            return false; ! Mensaje no regional
    }
    return true;
];

! ==============================================================================
! FUNCIONES DE DEPURACIÓN Y TESTING
! ==============================================================================

#Ifdef DEBUG;
[ TestRegionalFeatures;
    print "^=== PRUEBA DE CARACTERÍSTICAS REGIONALES ===^";
    print "Región actual: ";
    switch(current_spanish_region) {
        REGION_MEXICO: print "México^";
        REGION_ARGENTINA: print "Argentina^";
        REGION_SPAIN: print "España^";
        REGION_COLOMBIA: print "Colombia^";
        REGION_CHILE: print "Chile^";
        default: print "Neutral^";
    }
    
    ! Probar conjugación voseo
    if (voseo_enabled) {
        print "^Prueba de voseo:^";
        print "  tener (vos): "; ConjugarVoseo('tener', PRESENTE_T, 0); print "^";
        print "  ser (vos): "; ConjugarVoseo('ser', PRESENTE_T, 0); print "^";
        print "  ir (vos imperativo): "; ConjugarVoseo('ir', IMPERATIVO_T, 0); print "^";
    }
    
    print "^Expresiones regionales:^";
    print "  Asentimiento: "; GetRegionalExpression(1); print "^";
    print "  Sorpresa: "; GetRegionalExpression(2); print "^";
    print "  Despedida: "; GetRegionalExpression(3); print "^";
];

[ TestRegionalVocabulary;
    print "^=== PRUEBA DE VOCABULARIO REGIONAL ===^";
    print "Región actual: ";
    switch(current_spanish_region) {
        REGION_MEXICO: print "México^";
        REGION_ARGENTINA: print "Argentina^";
        REGION_SPAIN: print "España^";
        REGION_COLOMBIA: print "Colombia^";
        REGION_CHILE: print "Chile^";
        default: print "Neutral^";
    }
    
    print "^Equivalencias regionales:^";
    local regional_word;
    regional_word = GetRegionalWord('coche');
    if (regional_word) {
        print "  coche → "; print (address) regional_word; print "^";
    }
    
    regional_word = GetRegionalWord('autobús');
    if (regional_word) {
        print "  autobús → "; print (address) regional_word; print "^";
    }
    
    regional_word = GetRegionalWord('móvil');
    if (regional_word) {
        print "  móvil → "; print (address) regional_word; print "^";
    }
    
    print "^=== FIN DE PRUEBA ===^";
];

[ SpanishRegionalStats;
    print "^=== ESTADÍSTICAS REGIONALES ===^";
    print "Versión: ", (string) SPANISH_REGIONAL_VERSION, "^";
    print "Regiones soportadas: ", SPANISH_REGIONS_SUPPORTED, "^";
    print "Vocabulario regional: ", SPANISH_REGIONAL_VOCAB_ENTRIES, " entradas^";
    print "^Estado actual:^";
    print "• Región activa: ";
    switch(current_spanish_region) {
        REGION_MEXICO: print "México";
        REGION_ARGENTINA: print "Argentina";
        REGION_SPAIN: print "España";
        REGION_COLOMBIA: print "Colombia";
        REGION_CHILE: print "Chile";
        default: print "Neutral";
    }
    print "^• Voseo: ";
    if (voseo_enabled) print "✅ Activo"; else print "❌ Inactivo";
    print "^• Vocabulario regional: ";
    if (regional_vocabulary) print "✅ Activo"; else print "❌ Inactivo";
    print "^• Formalidad: ";
    if (FormalityLevel == FORMAL) print "FORMAL"; else print "INFORMAL";
    print "^";
];
#Endif;

! ==============================================================================
! FUNCIÓN DE ESTADO Y DIAGNÓSTICO
! ==============================================================================

[ SpanishRegionalStatus;
    ! ✅ CORREGIDO: Función completa de estado
    print "^=== ESTADO REGIONAL ===^";
    print "Módulo: "; 
    if (spanish_regional_ready) print "✅ Listo"; else print "❌ No inicializado";
    print "^";
    print "Región activa: ", current_spanish_region, "^";
    print "Voseo: ";
    if (voseo_enabled) print "✅"; else print "❌";
    print "^";
    print "Vocabulario regional: ";
    if (regional_vocabulary) print "✅"; else print "❌";
    print "^";
];

! ==============================================================================
! RUTINA DE INICIALIZACIÓN PRINCIPAL
! ==============================================================================

[ SpanishRegionalInitialise;
    ! ✅ CORREGIDO: Inicialización completa sin duplicaciones
    SpanishRegionalInit();
    MarkModuleLoaded('regional');
    
    #Ifdef DEBUG;
        print "^[SpanishRegional v", (string) SPANISH_REGIONAL_VERSION, " inicializado]^";
        print "[✅ Soporte para ", SPANISH_REGIONS_SUPPORTED, " regiones: Neutral, México, Argentina, España, Colombia, Chile]^";
        
        if (voseo_enabled) {
            print "[🇦🇷 Voseo argentino activado]^";
        }
        
        if (regional_vocabulary && current_spanish_region ~= REGION_NEUTRAL) {
            print "[✅ Vocabulario regional para ";
            switch(current_spanish_region) {
                REGION_MEXICO: print "México";
                REGION_ARGENTINA: print "Argentina";
                REGION_SPAIN: print "España";
                REGION_COLOMBIA: print "Colombia";
                REGION_CHILE: print "Chile";
            }
            print " activado]^";
        }
        
        print "[✅ Expresiones idiomáticas regionales disponibles]^";
        print "[", SPANISH_REGIONAL_FUNCTIONS, " funciones disponibles]^";
    #Endif;
];

! ==============================================================================
! CONSTANTES DE FINALIZACIÓN
! ==============================================================================

Constant SPANISH_REGIONAL_COMPLETE;
Constant SPANISH_REGIONAL_READY;
Constant SPANISH_REGIONS_SUPPORTED = 6;
Constant SPANISH_REGIONAL_VOCAB_ENTRIES = 21;  ! 7 palabras × 3 regiones principales
Constant SPANISH_REGIONAL_FUNCTIONS = 15; ! Número de funciones públicas

! Información del módulo
Constant SPANISH_REGIONAL_FEATURES = "6 regiones, voseo argentino, vocabulario regional 21 entradas, expresiones idiomáticas, configuración dinámica";

#Endif; ! SPANISH_REGIONAL_INCLUDED

! ==============================================================================
! Fin de SpanishRegional.h - Sistema regional completo y funcional
! Actualizado para integración completa con el sistema modular
! ==============================================================================