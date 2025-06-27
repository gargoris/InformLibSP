! ==============================================================================
! SPANISHREGIONAL.H - Sistema modular de variantes regionales
! Extensión OPCIONAL para la librería española existente
! ACTUALIZADO: Integración completa con el sistema modular
! ==============================================================================

System_file;

#Ifndef SPANISH_REGIONAL_INCLUDED;
Constant SPANISH_REGIONAL_INCLUDED;
Constant SPANISH_REGIONAL_VERSION = "2.0-modular";

! Verificación de dependencias
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

#Ifndef SPANISH_FORMALITY_DEFAULT;
    #If SPANISH_REGION == REGION_SPAIN;        ! España - más formal
        Constant SPANISH_FORMALITY_DEFAULT = FORMAL;
    #Ifnot;
        Constant SPANISH_FORMALITY_DEFAULT = INFORMAL;  ! Latinoamérica - más informal
    #Endif;
#Endif;

! ==============================================================================
! VARIABLES GLOBALES REGIONALES
! ==============================================================================

! Variables globales para configuración dinámica
Global current_spanish_region = SPANISH_REGION;
Global voseo_enabled = false;
Global regional_vocabulary = true;
Global spanish_regional_ready = false;

! ==============================================================================
! DETECCIÓN Y CONFIGURACIÓN AUTOMÁTICA
! ==============================================================================

[ SpanishRegionalInit;
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
! SISTEMA DE CONJUGACIÓN CON VOSEO (INTEGRADO)
! ==============================================================================

! Integración segura con el sistema de verbos existente
[ SpanishRegionalConjugarVerbo verbo persona tiempo tipo;
    ! Si no hay voseo o no es segunda persona, usar sistema estándar
    if (~~voseo_enabled || persona ~= SEGUNDA_PERSONA) {
        #Ifdef SPANISH_VERBS_INCLUDED;
            return ConjugarVerbo(verbo, persona, tiempo, tipo);
        #Ifnot;
            ! Fallback básico
            print (string) verbo;
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
        print (string) verbo;
        return true;
    #Endif;
];

! ==============================================================================
! SISTEMA DE VOSEO ARGENTINO (MEJORADO)
! ==============================================================================

[ ConjugarVoseo verbo tiempo tipo;
    ! Solo implementar los casos más comunes
    if (tipo == 0) {
        #Ifdef SPANISH_VERBS_INCLUDED;
            tipo = DetectarTipoVerbo(verbo);
        #Ifnot;
            tipo = 1; ! Asumir -AR por defecto
        #Endif;
    }
    
    ! Verificar si es verbo irregular con voseo especial
    if (ConjugarVoseoIrregular(verbo, tiempo)) return true;
    
    switch(tiempo) {
        PRESENTE_T:
            switch(tipo) {
                1: print (string) verbo, "ás";     ! caminar -> caminás
                2: print (string) verbo, "és";     ! comer -> comés  
                3: print (string) verbo, "ís";     ! vivir -> vivís
                default: 
                    print (string) verbo;
                    return false;
            }
        PRETERITO_T:
            ! En pretérito, el voseo es igual al tú estándar
            switch(tipo) {
                1: print (string) verbo, "aste";   ! caminaste
                2: print (string) verbo, "iste";   ! comiste
                3: print (string) verbo, "iste";   ! viviste
                default:
                    print (string) verbo;
                    return false;
            }
        IMPERATIVO_T:
            switch(tipo) {
                1: print (string) verbo, "á";      ! ¡caminá!
                2: print (string) verbo, "é";      ! ¡comé!
                3: print (string) verbo, "í";      ! ¡viví!
                default:
                    print (string) verbo;
                    return false;
            }
        default:
            ! Para otros tiempos, usar conjugación estándar
            #Ifdef SPANISH_VERBS_INCLUDED;
                return ConjugarVerbo(verbo, SEGUNDA_PERSONA, tiempo, tipo);
            #Ifnot;
                print (string) verbo;
                return false;
            #Endif;
    }
    return true;
];

[ ConjugarVoseoIrregular verbo tiempo;
    ! Verbos irregulares específicos con voseo
    switch(verbo) {
        'ser':
            switch(tiempo) {
                PRESENTE_T: print "sos"; rtrue;
                PRETERITO_T: print "fuiste"; rtrue;
                IMPERATIVO_T: print "sé"; rtrue;
            }
        'tener':
            switch(tiempo) {
                PRESENTE_T: print "tenés"; rtrue;
                PRETERITO_T: print "tuviste"; rtrue;
                IMPERATIVO_T: print "tené"; rtrue;
            }
        'estar':
            switch(tiempo) {
                PRESENTE_T: print "estás"; rtrue;
                PRETERITO_T: print "estuviste"; rtrue;
                IMPERATIVO_T: print "está"; rtrue;
            }
        'ir':
            switch(tiempo) {
                PRESENTE_T: print "vas"; rtrue;
                PRETERITO_T: print "fuiste"; rtrue;
                IMPERATIVO_T: print "andá"; rtrue;  ! Forma especial argentina
            }
        'venir':
            switch(tiempo) {
                PRESENTE_T: print "venís"; rtrue;
                PRETERITO_T: print "viniste"; rtrue;
                IMPERATIVO_T: print "vení"; rtrue;
            }
        'hacer':
            switch(tiempo) {
                PRESENTE_T: print "hacés"; rtrue;
                PRETERITO_T: print "hiciste"; rtrue;
                IMPERATIVO_T: print "hacé"; rtrue;
            }
        'poder':
            switch(tiempo) {
                PRESENTE_T: print "podés"; rtrue;
                PRETERITO_T: print "pudiste"; rtrue;
            }
        'querer':
            switch(tiempo) {
                PRESENTE_T: print "querés"; rtrue;
                PRETERITO_T: print "quisiste"; rtrue;
                IMPERATIVO_T: print "queré"; rtrue;
            }
    }
    rfalse; ! No es irregular conocido para voseo
];

! ==============================================================================
! VOCABULARIO REGIONAL - SISTEMA DE LOOKUP MEJORADO
! ==============================================================================

! Tabla de equivalencias léxicas expandida
Array regional_vocabulary_table table
    ! Palabra_estándar, Región, Palabra_regional
    'computadora'   REGION_SPAIN      'ordenador'
    'coche'         REGION_MEXICO     'carro'
    'coche'         REGION_ARGENTINA  'auto'
    'autobús'       REGION_MEXICO     'camión'
    'autobús'       REGION_ARGENTINA  'colectivo'
    'patata'        REGION_MEXICO     'papa'
    'zumo'          REGION_MEXICO     'jugo'
    'gafas'         REGION_MEXICO     'lentes'
    'móvil'         REGION_MEXICO     'celular'
    'móvil'         REGION_ARGENTINA  'celular'
    'piso'          REGION_MEXICO     'departamento'
    'piso'          REGION_ARGENTINA  'departamento'
    'vale'          REGION_MEXICO     'órale'
    'coger'         REGION_MEXICO     'tomar'      ! Importante para México
    'conducir'      REGION_MEXICO     'manejar'
    'conducir'      REGION_ARGENTINA  'manejar'
    'aparcar'       REGION_MEXICO     'estacionar'
    'aparcar'       REGION_ARGENTINA  'estacionar'
    'enfadado'      REGION_MEXICO     'enojado'
    'enfadado'      REGION_ARGENTINA  'enojado'
    'dinero'        REGION_ARGENTINA  'plata'
    'trabajo'       REGION_ARGENTINA  'laburo'
    'chico'         REGION_ARGENTINA  'pibe'
    'casa'          REGION_ARGENTINA  'rancho'      ! En contexto rural
    'niño'          REGION_MEXICO     'chamaco'
    'niño'          REGION_ARGENTINA  'chico'
    'bonito'        REGION_ARGENTINA  'lindo'
    'muy'           REGION_ARGENTINA  're'          ! "re bueno"
    'ahora'         REGION_ARGENTINA  'ahora'       ! Sin cambio, pero pronunciación
    'llevar'        REGION_ARGENTINA  'llevar'      ! Sin cambio
    'bolígrafo'     REGION_ARGENTINA  'birome'
    'jersey'        REGION_MEXICO     'suéter'
    'jersey'        REGION_ARGENTINA  'pullover';

! Función mejorada para obtener equivalencia regional
[ GetRegionalWord standard_word;
    local i;
    
    if (~~regional_vocabulary) return 0;  ! Vocabulario regional desactivado
    if (current_spanish_region == REGION_NEUTRAL) return 0; ! Sin regionalismo
    
    ! Buscar en la tabla
    for (i = 0: i < regional_vocabulary_table-->0: i = i + 3) {
        if (regional_vocabulary_table-->(i+1) == standard_word &&
            regional_vocabulary_table-->(i+2) == current_spanish_region) {
            return regional_vocabulary_table-->(i+3);
        }
    }
    
    return 0;  ! No hay equivalencia regional
];

[ GetStandardWord regional_word;
    ! Función inversa: de palabra regional a estándar
    local i;
    
    if (~~regional_vocabulary) return 0;
    
    for (i = 0: i < regional_vocabulary_table-->0: i = i + 3) {
        if (regional_vocabulary_table-->(i+3) == regional_word &&
            regional_vocabulary_table-->(i+2) == current_spanish_region) {
            return regional_vocabulary_table-->(i+1);
        }
    }
    
    return 0;
];

! ==============================================================================
! DETECCIÓN DE PRONOMBRES REGIONALES
! ==============================================================================

! Integración mejorada con el sistema de pronombres
[ LanguageRefersRegional obj wn   word;
    word = wn-->0;
    
    ! Si es voseo argentino, manejar "vos"
    if (voseo_enabled && word == 'vos') {
        ! "vos" se refiere al player en segunda persona
        if (obj == player) rtrue;
    }
    
    ! Manejar pronombres regionales específicos
    if (current_spanish_region == REGION_ARGENTINA) {
        if (word == 'che' && obj == player) rtrue;  ! "che" como referencia informal
    }
    
    ! Si no hay sistema de pronombres base, usar fallback
    #Ifdef LanguageRefers;
        return LanguageRefers(obj, wn);
    #Ifnot;
        rfalse;
    #Endif;
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
            REGION_COLOMBIA: print "¡Listo, sí!";
            REGION_CHILE: print "¡Ya, sí!";
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
            REGION_COLOMBIA: print "¡Uy, no!";
            REGION_CHILE: print "¡No puede ser, weon!";
            default: print "¡No puede ser!";
        }
        rtrue;
    }
    
    ! Expresiones de despedida
    if (expression_type == 3) {
        switch(current_spanish_region) {
            REGION_MEXICO: print "¡Nos vemos, amigo!";
            REGION_ARGENTINA: print "¡Chau, che!";
            REGION_SPAIN: print "¡Hasta luego!";
            REGION_COLOMBIA: print "¡Hasta la vista!";
            REGION_CHILE: print "¡Chao, weon!";
            default: print "¡Adiós!";
        }
        rtrue;
    }
    
    rfalse;
];

[ GetRegionalGreeting time_of_day;
    ! Saludos según región y hora
    switch(current_spanish_region) {
        REGION_MEXICO:
            if (time_of_day < 12) print "¡Buenos días, amigo!";
            else if (time_of_day < 19) print "¡Buenas tardes!";
            else print "¡Buenas noches!";
            
        REGION_ARGENTINA:
            if (time_of_day < 12) print "¡Buen día, che!";
            else if (time_of_day < 19) print "¡Buenas tardes!";
            else print "¡Buenas noches!";
            
        REGION_SPAIN:
            if (time_of_day < 12) print "¡Buenos días!";
            else if (time_of_day < 19) print "¡Buenas tardes!";
            else print "¡Buenas noches!";
            
        REGION_COLOMBIA:
            if (time_of_day < 12) print "¡Buenos días, parcero!";
            else if (time_of_day < 19) print "¡Buenas tardes!";
            else print "¡Buenas noches!";
            
        REGION_CHILE:
            if (time_of_day < 12) print "¡Buenos días, weon!";
            else if (time_of_day < 19) print "¡Buenas tardes!";
            else print "¡Buenas noches!";
            
        default:
            if (time_of_day < 12) print "¡Buenos días!";
            else if (time_of_day < 19) print "¡Buenas tardes!";
            else print "¡Buenas noches!";
    }
];

! ==============================================================================
! CONFIGURACIÓN DINÁMICA - API PARA EL DESARROLLADOR
! ==============================================================================

[ SetSpanishRegion new_region;
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
    print "Regiones disponibles:^";
    print "0 - Neutral (sin regionalismos)^";
    print "1 - México^";
    print "2 - Argentina^";
    print "3 - España^";
    print "4 - Colombia^";
    print "5 - Chile^";
];

! ==============================================================================
! MENSAJES REGIONALES ESPECÍFICOS
! ==============================================================================

[ GetRegionalMessage message_type obj;
    ! Mensajes que varían según la región
    switch(message_type) {
        1: ! Tomar objeto
            switch(current_spanish_region) {
                REGION_MEXICO: print "Tomaste "; print (the) obj; print ".";
                REGION_ARGENTINA: print "Agarraste "; print (the) obj; print ".";
                REGION_SPAIN: print "Cogiste "; print (the) obj; print ".";
                default: print "Tomaste "; print (the) obj; print ".";
            }
            rtrue;
            
        2: ! No puedes ver eso
            switch(current_spanish_region) {
                REGION_MEXICO: print "No miras eso por aquí, amigo.";
                REGION_ARGENTINA: print "No ves eso por acá, che.";
                REGION_SPAIN: print "No ves tal cosa aquí.";
                REGION_COLOMBIA: print "No se ve eso por acá, parcero.";
                REGION_CHILE: print "No ves eso acá, weon.";
                default: print "No puedes ver eso aquí.";
            }
            rtrue;
            
        3: ! Despedida del juego
            switch(current_spanish_region) {
                REGION_MEXICO: print "¡Hasta la vista, amigo!";
                REGION_ARGENTINA: print "¡Chau, che! ¡Que andes bien!";
                REGION_SPAIN: print "¡Hasta pronto!";
                REGION_COLOMBIA: print "¡Nos vemos, parcero!";
                REGION_CHILE: print "¡Chao, nos vemos!";
                default: print "¡Hasta pronto!";
            }
            rtrue;
    }
    
    rfalse; ! No hay mensaje regional específico
];

! ==============================================================================
! COMANDOS DE DEPURACIÓN REGIONALES
! ==============================================================================

#Ifdef DEBUG;

[ RegionalDebugCommand;
    print "^=== CONFIGURACIÓN REGIONAL ACTUAL ===^";
    print "Versión: ", (string) SPANISH_REGIONAL_VERSION, "^";
    print "Región: ";
    switch(current_spanish_region) {
        REGION_MEXICO: print "México";
        REGION_ARGENTINA: print "Argentina";
        REGION_SPAIN: print "España";
        REGION_COLOMBIA: print "Colombia";
        REGION_CHILE: print "Chile";
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
    if (FormalityLevel) print "Formal (usted)"; else print "Informal (tú/vos)";
    print "^";
    
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
        default: print "Neutral^";
    }
    
    print "^Equivalencias regionales:^";
    if (GetRegionalWord('coche')) {
        print "  coche → "; print (address) GetRegionalWord('coche'); print "^";
    }
    if (GetRegionalWord('autobús')) {
        print "  autobús → "; print (address) GetRegionalWord('autobús'); print "^";
    }
    if (GetRegionalWord('móvil')) {
        print "  móvil → "; print (address) GetRegionalWord('móvil'); print "^";
    }
    
    print "^=== FIN DE PRUEBA ===^";
];

#Endif;

! ==============================================================================
! INTEGRACIÓN CON EL SISTEMA PRINCIPAL
! ==============================================================================

! Auto-inicialización cuando se carga este módulo
[ SpanishRegionalAutoInit;
    SpanishRegionalInit();
];

! Función de estado para otros módulos
[ SpanishRegionalStatus;
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
    SpanishRegionalInit();
    
    print "^[SpanishRegional v", (string) SPANISH_REGIONAL_VERSION, " inicializado]^";
    print "[✅ Soporte para 6 regiones: Neutral, México, Argentina, España, Colombia, Chile]^";
    
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
];

! ==============================================================================
! CONSTANTES DE FINALIZACIÓN
! ==============================================================================

Constant SPANISH_REGIONAL_COMPLETE;
Constant SPANISH_REGIONAL_READY;
Constant SPANISH_REGIONS_SUPPORTED = 6;
Constant SPANISH_REGIONAL_VOCAB_ENTRIES = 20;

! Información del módulo
Constant SPANISH_REGIONAL_FEATURES = "6 regiones, voseo argentino, vocabulario regional, expresiones idiomáticas";

#Endif; ! SPANISH_REGIONAL_INCLUDED

! ==============================================================================
! Fin de SpanishRegional.h - Sistema regional mínimo y completo
! Actualizado para integración completa con el sistema modular
! ==============================================================================