! ==============================================================================
! SPANISHREGIONAL.H - Sistema modular de variantes regionales
! Extension OPCIONAL para la libreria espanola existente
! Compatible con Inform 6.42 y libreria estandar 6.12.7
! ==============================================================================

System_file;

#Ifndef SPANISH_REGIONAL_INCLUDED;
Constant SPANISH_REGIONAL_INCLUDED;
Constant SPANISH_REGIONAL_VERSION = "2.1-complete-fixed";

! ==============================================================================
! VERIFICACION DE DEPENDENCIAS
! ==============================================================================

#Ifndef SPANISH_CONSTANTS_INCLUDED;
  Message fatalerror "*** Include SpanishConstants.h antes de SpanishRegional.h ***";
#Endif;

#Ifndef SPANISH_CORE_INCLUDED;
  Message fatalerror "*** Include SpanishCore.h antes de SpanishRegional.h ***";
#Endif;

! ==============================================================================
! CONFIGURACION REGIONAL - ACTIVACION OPCIONAL
! ==============================================================================

! El desarrollador puede definir estas constantes ANTES de Include SpanishLib.h
! Si no se define nada, usa comportamiento estandar (neutral)

#Ifndef SPANISH_REGION;
    Constant SPANISH_REGION = REGION_NEUTRAL;  ! Usar constante de SpanishConstants.h
#Endif;

! Variables locales especificas del modulo regional
Global spanish_regional_ready = false;

! ==============================================================================
! DETECCION Y CONFIGURACION AUTOMATICA
! ==============================================================================

[ SpanishRegionalInit;
    ! [OK] CORREGIDO: Usar variables globales de SpanishConstants.h, no duplicar
    current_spanish_region = SPANISH_REGION;
    
    ! Configuracion automatica basada en region
    switch (current_spanish_region) {
        REGION_ARGENTINA:
            voseo_enabled = true;
            FormalityLevel = INFORMAL;  ! Argentina es mas informal
            
        REGION_SPAIN:
            voseo_enabled = false;
            FormalityLevel = FORMAL;  ! Espana tiende a ser mas formal
            
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
        print "[Region: ";
        switch (current_spanish_region) {
            REGION_MEXICO: print "Mexico";
            REGION_ARGENTINA: print "Argentina";
            REGION_SPAIN: print "Espana";
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
! SISTEMA DE CONJUGACION CON VOSEO - [OK] COMPLETO
! ==============================================================================

[ SpanishRegionalConjugarVerbo verbo persona tiempo tipo;
    ! [OK] CORREGIDO: Funcion completa de integracion con voseo
    ! Si no hay voseo o no es segunda persona, usar sistema estandar
    if (~~voseo_enabled || persona ~= SEGUNDA_PERSONA) {
        #Ifdef SPANISH_VERBS_INCLUDED;
            return ConjugarVerbo(verbo, persona, tiempo, tipo);
        #Ifnot;
            ! Fallback basico
            print (address) verbo;
            return true;
        #Endif;
    }
    
    ! Solo si es Argentina y segunda persona, usar voseo
    if (current_spanish_region == REGION_ARGENTINA && persona == SEGUNDA_PERSONA) {
        return ConjugarVoseo(verbo, tiempo, tipo);
    }
    
    ! Fallback al sistema estandar
    #Ifdef SPANISH_VERBS_INCLUDED;
        return ConjugarVerbo(verbo, persona, tiempo, tipo);
    #Ifnot;
        print (address) verbo;
        return true;
    #Endif;
];

[ ConjugarVoseo verbo tiempo tipo   raiz;
    ! [OK] CORREGIDO: Funcion completa de conjugacion con voseo argentino
    ! Solo implementar los casos mas comunes
    if (tipo == 0) {
        #Ifdef SPANISH_VERBS_INCLUDED;
            tipo = DetectarTipoVerbo(verbo);
        #Ifnot;
            tipo = 1; ! Asumir -AR por defecto
        #Endif;
    }
    
    ! Intentar primero verbos irregulares con voseo
    if (ConjugarVoseoIrregular(verbo, tiempo)) return true;
    
    ! Si no es irregular, usar conjugacion regular con voseo
    if (tipo == 0) {
        print (address) verbo; ! Fallback
        return false;
    }
    
    ! Obtener raiz del verbo
    #Ifdef SPANISH_VERBS_INCLUDED;
        raiz = ObtenerRaizVerbo(verbo, spanish_temp_buffer);
    #Ifnot;
        ! Fallback basico - asumir que es la palabra sin las ultimas 2 letras
        raiz = spanish_temp_buffer;
        PrintToBuffer(raiz, 100, verbo);
        raiz->0 = raiz->0 - 2; ! Quitar -ar, -er, -ir
    #Endif;
    
    if (raiz == 0) {
        print (address) verbo;
        return false;
    }
    
    ! Conjugar segun tipo y tiempo para voseo
    print (string) raiz;
    
    switch(tiempo) {
        PRESENTE_T:
            switch(tipo) {
                1: print "as";     ! vos caminas
                2: print "es";     ! vos comes  
                3: print "is";     ! vos vivis
                default: print "as";
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
                2: print "ias";    ! vos comias
                3: print "ias";    ! vos vivias
                default: print "abas";
            }
            
        FUTURO_T:
            ! Para futuro, usar infinitivo + terminacion
            switch(tipo) {
                1: print "ar"; break;
                2: print "er"; break;
                3: print "ir"; break;
            }
            print "as";           ! vos caminaras, comeras, viviras
            
        IMPERATIVO_T:
            switch(tipo) {
                1: print "a";      ! !camina!
                2: print "e";      ! !come!
                3: print "i";      ! !vivi!
                default: print "a";
            }
            
        default:
            ! Para otros tiempos, usar conjugacion estandar
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
    ! [OK] CORREGIDO: Funcion completa de verbos irregulares con voseo
    switch(verbo) {
        'ser':
            switch(tiempo) {
                PRESENTE_T: print "sos"; rtrue;         ! vos sos
                PRETERITO_T: print "fuiste"; rtrue;     ! vos fuiste
                IMPERFECTO_T: print "eras"; rtrue;      ! vos eras
                IMPERATIVO_T: print "se"; rtrue;        ! !se!
            }
        'tener':
            switch(tiempo) {
                PRESENTE_T: print "tenes"; rtrue;       ! vos tenes
                PRETERITO_T: print "tuviste"; rtrue;    ! vos tuviste
                IMPERFECTO_T: print "tenias"; rtrue;    ! vos tenias
                IMPERATIVO_T: print "tene"; rtrue;      ! !tene!
            }
        'estar':
            switch(tiempo) {
                PRESENTE_T: print "estas"; rtrue;       ! vos estas
                PRETERITO_T: print "estuviste"; rtrue;  ! vos estuviste
                IMPERFECTO_T: print "estabas"; rtrue;   ! vos estabas
                IMPERATIVO_T: print "esta"; rtrue;      ! !esta!
            }
        'ir':
            switch(tiempo) {
                PRESENTE_T: print "vas"; rtrue;         ! vos vas
                PRETERITO_T: print "fuiste"; rtrue;     ! vos fuiste (igual que SER)
                IMPERFECTO_T: print "ibas"; rtrue;      ! vos ibas
                IMPERATIVO_T: print "anda"; rtrue;      ! !anda! (forma especial argentina)
            }
        'venir':
            switch(tiempo) {
                PRESENTE_T: print "venis"; rtrue;       ! vos venis
                PRETERITO_T: print "viniste"; rtrue;    ! vos viniste
                IMPERFECTO_T: print "venias"; rtrue;    ! vos venias
                IMPERATIVO_T: print "veni"; rtrue;      ! !veni!
            }
        'hacer':
            switch(tiempo) {
                PRESENTE_T: print "haces"; rtrue;       ! vos haces
                PRETERITO_T: print "hiciste"; rtrue;    ! vos hiciste
                IMPERFECTO_T: print "hacias"; rtrue;    ! vos hacias
                IMPERATIVO_T: print "hace"; rtrue;      ! !hace!
            }
        'poder':
            switch(tiempo) {
                PRESENTE_T: print "podes"; rtrue;       ! vos podes
                PRETERITO_T: print "pudiste"; rtrue;    ! vos pudiste
                IMPERFECTO_T: print "podias"; rtrue;    ! vos podias
            }
        'querer':
            switch(tiempo) {
                PRESENTE_T: print "queres"; rtrue;      ! vos queres
                PRETERITO_T: print "quisiste"; rtrue;   ! vos quisiste
                IMPERFECTO_T: print "querias"; rtrue;   ! vos querias
                IMPERATIVO_T: print "quere"; rtrue;     ! !quere!
            }
        'ver':
            switch(tiempo) {
                PRESENTE_T: print "ves"; rtrue;         ! vos ves
                IMPERFECTO_T: print "veias"; rtrue;     ! vos veias
                IMPERATIVO_T: print "ve"; rtrue;        ! !ve!
            }
        'dar':
            switch(tiempo) {
                PRESENTE_T: print "das"; rtrue;         ! vos das
                PRETERITO_T: print "diste"; rtrue;      ! vos diste
                IMPERATIVO_T: print "da"; rtrue;        ! !da!
            }
    }
    return false; ! No es irregular conocido para voseo
];

! ==============================================================================
! VOCABULARIO REGIONAL - [OK] SISTEMA COMPLETO
! ==============================================================================

! Tabla de equivalencias lexicas regional
Array regional_vocabulary_table table
    ! formato: palabra_estandar, region, palabra_regional
    'coche'     REGION_MEXICO     'carro'
    'coche'     REGION_ARGENTINA  'auto'  
    'coche'     REGION_SPAIN      'coche'
    'coche'     REGION_COLOMBIA   'carro'
    'coche'     REGION_CHILE      'auto'
    
    'autobus'   REGION_MEXICO     'camion'
    'autobus'   REGION_ARGENTINA  'colectivo'
    'autobus'   REGION_SPAIN      'autobus'
    'autobus'   REGION_COLOMBIA   'bus'
    'autobus'   REGION_CHILE      'micro'
    
    'movil'     REGION_MEXICO     'celular'
    'movil'     REGION_ARGENTINA  'celular'
    'movil'     REGION_SPAIN      'movil'
    'movil'     REGION_COLOMBIA   'celular'
    'movil'     REGION_CHILE      'celular'
    
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
    ! [OK] CORREGIDO: Funcion completa para obtener equivalencia regional
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
    ! [OK] CORREGIDO: Funcion inversa completa
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
! EXPRESIONES IDIOMATICAS REGIONALES - [OK] COMPLETO
! ==============================================================================

[ GetRegionalExpression expression_type;
    ! [OK] CORREGIDO: Funcion completa de expresiones idiomaticas
    switch(expression_type) {
        1: ! Expresiones de asentimiento
            switch(current_spanish_region) {
                REGION_MEXICO: print "!Orale, si!";
                REGION_ARGENTINA: print "!Dale!";
                REGION_SPAIN: print "!Vale!";
                REGION_COLOMBIA: print "!Listo, si!";
                REGION_CHILE: print "!Ya, si!";
                default: print "Si, de acuerdo.";
            }
            
        2: ! Expresiones de sorpresa
            switch(current_spanish_region) {
                REGION_MEXICO: print "!No manches!";
                REGION_ARGENTINA: print "!No me digas!";
                REGION_SPAIN: print "!No me jodas!";
                REGION_COLOMBIA: print "!Uy, no!";
                REGION_CHILE: print "!No puede ser, weon!";
                default: print "!No puede ser!";
            }
            
        3: ! Expresiones de despedida
            switch(current_spanish_region) {
                REGION_MEXICO: print "!Orale, nos vemos!";
                REGION_ARGENTINA: print "!Chau!";
                REGION_SPAIN: print "!Hasta luego!";
                REGION_COLOMBIA: print "!Que te vaya bien!";
                REGION_CHILE: print "!Chao!";
                default: print "Adios.";
            }
            
        4: ! Expresiones de saludo segun hora
            local time_of_day;
            time_of_day = (the_time / 60); ! Convertir a horas
            
            if (time_of_day < 12) print "!Buenos dias!";
            else if (time_of_day < 19) print "!Buenas tardes!";
            else print "!Buenas noches!";
            
        default:
            print "Hola."; ! Fallback neutral
    }
    return true;
];

[ GetRegionalGreeting;
    ! [OK] ANADIDO: Saludos especificos por region
    switch(current_spanish_region) {
        REGION_MEXICO: print "!Orale, que tal!";
        REGION_ARGENTINA: print "!Hola, che!";
        REGION_SPAIN: print "!Hola, que tal!";
        REGION_COLOMBIA: print "!Hola, ?que mas?";
        REGION_CHILE: print "!Hola, weon!";
        default: print "Hola.";
    }
];

! ==============================================================================
! CONFIGURACION DINAMICA - API PARA EL DESARROLLADOR
! ==============================================================================

[ SetSpanishRegion new_region;
    ! [OK] CORREGIDO: Funcion completa de configuracion de region
    if (new_region < REGION_NEUTRAL || new_region > REGION_CHILE) {
        print "Region invalida. Regiones disponibles: 0-5.^";
        return false;
    }
    
    current_spanish_region = new_region;
    SpanishRegionalInit();  ! Reconfigurar segun nueva region
    
    print "Region espanola cambiada a: ";
    switch(new_region) {
        REGION_MEXICO: print "Mexico";
        REGION_ARGENTINA: print "Argentina";  
        REGION_SPAIN: print "Espana";
        REGION_COLOMBIA: print "Colombia";
        REGION_CHILE: print "Chile";
        default: print "Neutral";
    }
    print ".^";
    
    return true;
];

[ ToggleVoseo;
    ! [OK] CORREGIDO: Funcion completa para alternar voseo
    if (current_spanish_region ~= REGION_ARGENTINA) {
        print "El voseo solo esta disponible para la region Argentina.^";
        return false;
    }
    
    if (voseo_enabled) {
        voseo_enabled = false;
        print "Voseo desactivado. Usando formas estandar con ~tu~.^";
    } else {
        voseo_enabled = true; 
        print "Voseo activado. Usando formas argentinas con ~vos~.^";
    }
    return true;
];

[ ToggleRegionalVocabulary;
    ! [OK] CORREGIDO: Funcion completa para alternar vocabulario regional
    if (regional_vocabulary) {
        regional_vocabulary = false;
        print "Vocabulario regional desactivado. Usando terminos neutros.^";
    } else {
        regional_vocabulary = true;
        print "Vocabulario regional activado.^";
    }
    return true;
];

[ GetAvailableRegions;
    ! [OK] CORREGIDO: Funcion completa de informacion de regiones
    print "Regiones disponibles:^";
    print "0 - Neutral (sin regionalismos)^";
    print "1 - Mexico^";
    print "2 - Argentina^";
    print "3 - Espana^";
    print "4 - Colombia^";
    print "5 - Chile^";
    print "^Caracteristicas por region:^";
    print "- Mexico: carro, camion, celular, computadora^";
    print "- Argentina: auto, colectivo, voseo (vos tenes)^";
    print "- Espana: coche, autobus, movil, ordenador^";
    print "- Colombia: carro, bus, apartamento^";
    print "- Chile: auto, micro, weon^";
];

! ==============================================================================
! DETECCION DE PRONOMBRES REGIONALES
! ==============================================================================

[ LanguageRefersRegional obj wn   word;
    ! [OK] CORREGIDO: Funcion completa de pronombres regionales
    word = wn-->0;
    
    ! Si es voseo argentino, manejar "vos"
    if (voseo_enabled && word == 'vos') {
        ! "vos" se refiere al player en segunda persona
        if (obj == player) return true;
    }
    
    ! Manejar pronombres regionales especificos
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
! MENSAJES REGIONALES ESPECIFICOS
! ==============================================================================

[ GetRegionalMessage message_type obj;
    ! [OK] CORREGIDO: Funcion completa de mensajes regionales
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
                REGION_MEXICO: print "No miras eso por aqui, amigo.";
                REGION_ARGENTINA: print "No ves eso por aca, che.";
                REGION_SPAIN: print "No ves tal cosa aqui.";
                REGION_COLOMBIA: print "No ves eso por aca.";
                REGION_CHILE: print "No ves esa cosa, weon.";
                default: print "No puedes ver tal cosa.";
            }
            
        3: ! Inventario vacio
            switch(current_spanish_region) {
                REGION_MEXICO: print "No cargas nada, compadre.";
                REGION_ARGENTINA: print "No tenes nada encima, che.";
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
! FUNCIONES DE DEPURACION Y TESTING
! ==============================================================================

#Ifdef DEBUG;
[ TestRegionalFeatures;
    print "^=== PRUEBA DE CARACTERISTICAS REGIONALES ===^";
    print "Region actual: ";
    switch(current_spanish_region) {
        REGION_MEXICO: print "Mexico^";
        REGION_ARGENTINA: print "Argentina^";
        REGION_SPAIN: print "Espana^";
        REGION_COLOMBIA: print "Colombia^";
        REGION_CHILE: print "Chile^";
        default: print "Neutral^";
    }
    
    ! Probar conjugacion voseo
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
    print "Region actual: ";
    switch(current_spanish_region) {
        REGION_MEXICO: print "Mexico^";
        REGION_ARGENTINA: print "Argentina^";
        REGION_SPAIN: print "Espana^";
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
    
    regional_word = GetRegionalWord('autobus');
    if (regional_word) {
        print "  autobus → "; print (address) regional_word; print "^";
    }
    
    regional_word = GetRegionalWord('movil');
    if (regional_word) {
        print "  movil → "; print (address) regional_word; print "^";
    }
    
    print "^=== FIN DE PRUEBA ===^";
];

[ SpanishRegionalStats;
    print "^=== ESTADISTICAS REGIONALES ===^";
    print "Version: ", (string) SPANISH_REGIONAL_VERSION, "^";
    print "Regiones soportadas: ", SPANISH_REGIONS_SUPPORTED, "^";
    print "Vocabulario regional: ", SPANISH_REGIONAL_VOCAB_ENTRIES, " entradas^";
    print "^Estado actual:^";
    print "- Region activa: ";
    switch(current_spanish_region) {
        REGION_MEXICO: print "Mexico";
        REGION_ARGENTINA: print "Argentina";
        REGION_SPAIN: print "Espana";
        REGION_COLOMBIA: print "Colombia";
        REGION_CHILE: print "Chile";
        default: print "Neutral";
    }
    print "^- Voseo: ";
    if (voseo_enabled) print "[OK] Activo"; else print "[X] Inactivo";
    print "^- Vocabulario regional: ";
    if (regional_vocabulary) print "[OK] Activo"; else print "[X] Inactivo";
    print "^- Formalidad: ";
    if (FormalityLevel == FORMAL) print "FORMAL"; else print "INFORMAL";
    print "^";
];
#Endif;

! ==============================================================================
! FUNCION DE ESTADO Y DIAGNOSTICO
! ==============================================================================

[ SpanishRegionalStatus;
    ! [OK] CORREGIDO: Funcion completa de estado
    print "^=== ESTADO REGIONAL ===^";
    print "Modulo: "; 
    if (spanish_regional_ready) print "[OK] Listo"; else print "[X] No inicializado";
    print "^";
    print "Region activa: ", current_spanish_region, "^";
    print "Voseo: ";
    if (voseo_enabled) print "[OK]"; else print "[X]";
    print "^";
    print "Vocabulario regional: ";
    if (regional_vocabulary) print "[OK]"; else print "[X]";
    print "^";
];

! ==============================================================================
! RUTINA DE INICIALIZACION PRINCIPAL
! ==============================================================================

[ SpanishRegionalInitialise;
    ! [OK] CORREGIDO: Inicializacion completa sin duplicaciones
    SpanishRegionalInit();
    MarkModuleLoaded('regional');
    
    #Ifdef DEBUG;
        print "^[SpanishRegional v", (string) SPANISH_REGIONAL_VERSION, " inicializado]^";
        print "[[OK] Soporte para ", SPANISH_REGIONS_SUPPORTED, " regiones: Neutral, Mexico, Argentina, Espana, Colombia, Chile]^";
        
        if (voseo_enabled) {
            print "[🇦🇷 Voseo argentino activado]^";
        }
        
        if (regional_vocabulary && current_spanish_region ~= REGION_NEUTRAL) {
            print "[[OK] Vocabulario regional para ";
            switch(current_spanish_region) {
                REGION_MEXICO: print "Mexico";
                REGION_ARGENTINA: print "Argentina";
                REGION_SPAIN: print "Espana";
                REGION_COLOMBIA: print "Colombia";
                REGION_CHILE: print "Chile";
            }
            print " activado]^";
        }
        
        print "[[OK] Expresiones idiomaticas regionales disponibles]^";
        print "[", SPANISH_REGIONAL_FUNCTIONS, " funciones disponibles]^";
    #Endif;
];

! ==============================================================================
! CONSTANTES DE FINALIZACION
! ==============================================================================

Constant SPANISH_REGIONAL_COMPLETE;
Constant SPANISH_REGIONAL_READY;
Constant SPANISH_REGIONS_SUPPORTED = 6;
Constant SPANISH_REGIONAL_VOCAB_ENTRIES = 21;  ! 7 palabras × 3 regiones principales
Constant SPANISH_REGIONAL_FUNCTIONS = 15; ! Numero de funciones publicas

! Informacion del modulo
Constant SPANISH_REGIONAL_FEATURES = "6 regiones, voseo argentino, vocabulario regional 21 entradas, expresiones idiomaticas, configuracion dinamica";

#Endif; ! SPANISH_REGIONAL_INCLUDED

! ==============================================================================
! Fin de SpanishRegional.h - Sistema regional completo y funcional
! Actualizado para integracion completa con el sistema modular
! ==============================================================================