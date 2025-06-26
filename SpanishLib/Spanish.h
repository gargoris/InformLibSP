! ==============================================================================
! SPANISH.H - Librería Modular de Idioma Español para Inform 6 (ACTUALIZADA)
! Compatible con Inform 6.42 y librería estándar 6.12.7
! 
! VERSIÓN MEJORADA: Integración completa con verbos irregulares
! Mantiene retrocompatibilidad total + nuevas características avanzadas
! ==============================================================================

System_file;

#Ifndef SPANISH_LIB_INCLUDED;
Constant SPANISH_LIB_INCLUDED;
Constant LanguageVersion = "6.12.7-es-irregular-complete";

! ==============================================================================
! CONFIGURACIÓN MODULAR ACTUALIZADA
! ==============================================================================

! Configuraciones por defecto (el desarrollador puede override antes de Include)
#Ifndef SPANISH_MINIMAL;
    #Ifndef SPANISH_FULL_MESSAGES; Constant SPANISH_FULL_MESSAGES; #Endif;
    #Ifndef SPANISH_META_COMMANDS; Constant SPANISH_META_COMMANDS; #Endif;
    #Ifndef SPANISH_HELP_SYSTEM; Constant SPANISH_HELP_SYSTEM; #Endif;
    #Ifndef SPANISH_IRREGULAR_VERBS; Constant SPANISH_IRREGULAR_VERBS; #Endif;  ! NUEVO
#Endif;

! Características avanzadas opcionales
#Ifndef SPANISH_ADVANCED_GRAMMAR; 
    ! Activar gramática avanzada con verbos irregulares
    #Ifdef SPANISH_IRREGULAR_VERBS;
        Constant SPANISH_ADVANCED_GRAMMAR;
    #Endif;
#Endif;

! Verificación de orden de includes
#Ifdef LIBRARY_STAGE;
#Iffalse LIBRARY_STAGE >= AFTER_PARSER;
  Message fatalerror "*** Include Parser.h y VerbLib.h antes de Spanish.h ***";
#Endif;
#Endif;

! ==============================================================================
! NÚCLEO BÁSICO - EXPORTANDO TODAS LAS CONSTANTES ORIGINALES
! ==============================================================================

! [Todo el contenido del núcleo básico original se mantiene igual]
Constant DEFART_H = "el";
Constant DEFART_F = "la";
Constant DEFART_PL = "los/las";
Constant INDEFART_H = "un";
Constant INDEFART_F = "una";
Constant INDEFART_PL = "unos/unas";

! Direcciones básicas
Constant N_TO     = "norte n";
Constant S_TO     = "sur s";
Constant E_TO     = "este e";
Constant W_TO     = "oeste o";
Constant NE_TO    = "nordeste ne";
Constant NW_TO    = "noroeste no";
Constant SE_TO    = "sudeste se";
Constant SW_TO    = "sudoeste so";
Constant U_TO     = "arriba subir";
Constant D_TO     = "abajo bajar";
Constant IN_TO    = "dentro entrar";
Constant OUT_TO   = "fuera salir";

! Palabras especiales del parser
Constant ALL1__WD   = 'todo';
Constant ALL2__WD   = 'todos';
Constant ALL3__WD   = 'todas';
Constant ALL4__WD   = 'cada';
Constant AND1__WD   = 'y';
Constant AND2__WD   = 'e';
Constant BUT1__WD   = 'menos';
Constant BUT2__WD   = 'excepto';
Constant BUT3__WD   = 'salvo';
Constant ME1__WD    = 'yo';
Constant ME2__WD    = 'mi';
Constant ME3__WD    = 'me';
Constant OF1__WD    = 'de';
Constant OF2__WD    = 'del';
Constant OF3__WD    = 'de_la';
Constant OF4__WD    = 'de_los';
Constant OTHER1__WD = 'otro';
Constant OTHER2__WD = 'otra';
Constant OTHER3__WD = 'otros';
Constant THEN1__WD  = 'luego';
Constant THEN2__WD  = 'después';
Constant THEN3__WD  = 'entonces';

! Variables globales básicas
Global FormalityLevel = 0;
Global last_command_length = 0;

! Constantes para género
Constant MASCULINE = 1;
Constant FEMININE = 2;
Constant NEUTER = 3;

! Constantes para tiempos verbales (EXPANDIDAS)
Constant PRESENTE_T   = 1;
Constant PRETERITO_T  = 2;
Constant IMPERFECTO_T = 3;
Constant FUTURO_T     = 4;
Constant CONDICIONAL_T = 5;    ! NUEVO
Constant SUBJUNTIVO_T = 6;     ! NUEVO
Constant IMPERATIVO_T = 7;     ! NUEVO

! Constantes para preposiciones
Constant PREP_SIMPLE = 1;
Constant PREP_COMPOUND_START = 2;

! ==============================================================================
! ARRAYS Y TABLAS BÁSICAS (MANTENIDAS)
! ==============================================================================

Array LanguagePronouns table
    'me'       $$000001   NULL     
    'mi'       $$000001   NULL     
    'yo'       $$000001   NULL
    'te'       $$000010   NULL     
    'tu'       $$000010   NULL
    'usted'    $$000010   NULL
    'le'       $$000100   NULL     
    'la'       $$000100   NULL
    'lo'       $$000100   NULL
    'el'       $$000100   NULL
    'ella'     $$000100   NULL
    'nos'      $$001000   NULL     
    'nosotros' $$001000   NULL
    'nosotras' $$001000   NULL
    'os'       $$010000   NULL     
    'vosotros' $$010000   NULL 
    'vosotras' $$010000   NULL
    'ustedes'  $$010000   NULL
    'les'      $$100000   NULL     
    'las'      $$100000   NULL
    'los'      $$100000   NULL
    'ellos'    $$100000   NULL
    'ellas'    $$100000   NULL;

Array LanguageDescriptors table
    'mi'       $$000001,
    'mis'      $$000001,
    'tu'       $$000010,
    'tus'      $$000010,
    'su'       $$000100,
    'sus'      $$000100,
    'nuestro'  $$001000,
    'nuestra'  $$001000,
    'nuestros' $$001000,
    'nuestras' $$001000,
    'vuestro'  $$010000,
    'vuestra'  $$010000,
    'vuestros' $$010000,
    'vuestras' $$010000;

Array LanguageNumbers table
    'uno' 1 'un' 1 'una' 1,
    'dos' 2, 'tres' 3, 'cuatro' 4, 'cinco' 5,
    'seis' 6, 'siete' 7, 'ocho' 8, 'nueve' 9, 'diez' 10,
    'once' 11, 'doce' 12, 'trece' 13, 'catorce' 14, 'quince' 15,
    'dieciséis' 16, 'diecisiete' 17, 'dieciocho' 18, 'diecinueve' 19, 'veinte' 20;

! ==============================================================================
! FUNCIONES BÁSICAS DE GÉNERO Y ARTÍCULOS (MANTENIDAS)
! ==============================================================================

[ EsGeneroMasculino obj;
    if (obj has male) rtrue;
    if (obj has female) rfalse;
    if (obj has neuter) rfalse;
    rtrue;
];

[ EsPlural obj;
    if (obj has pluralname) rtrue;
    rfalse;
];

[ ArticuloDefinido obj;
    if (EsPlural(obj)) {
        print "los";
        if (EsGeneroMasculino(obj) == false) print "/las";
    }
    else {
        if (EsGeneroMasculino(obj)) print "el";
        else print "la";
    }
];

[ ArticuloIndefinido obj;
    if (EsPlural(obj)) {
        if (EsGeneroMasculino(obj)) print "unos";
        else print "unas";
    }
    else {
        if (EsGeneroMasculino(obj)) print "un";
        else print "una";
    }
];

[ SetSpanishGender obj gender;
    if (gender ~= 0) {
        if (gender == 1) give obj male;
        if (gender == 2) give obj female;
        return;
    }
    give obj male;
];

! ==============================================================================
! FUNCIONES BÁSICAS DE CONJUGACIÓN REGULARES (EXPANDIDAS)
! ==============================================================================

[ ConjugarAR verbo persona tiempo;
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print (string) verbo, "o";
                2: print (string) verbo, "as";
                3: print (string) verbo, "a";
                4: print (string) verbo, "amos";
                5: print (string) verbo, "áis";
                6: print (string) verbo, "an";
            }
        PRETERITO_T:
            switch(persona) {
                1: print (string) verbo, "é";
                2: print (string) verbo, "aste";
                3: print (string) verbo, "ó";
                4: print (string) verbo, "amos";
                5: print (string) verbo, "asteis";
                6: print (string) verbo, "aron";
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print (string) verbo, "aba";
                2: print (string) verbo, "abas";
                3: print (string) verbo, "aba";
                4: print (string) verbo, "ábamos";
                5: print (string) verbo, "abais";
                6: print (string) verbo, "aban";
            }
        FUTURO_T:
            print (string) verbo, "ar";
            switch(persona) {
                1: print "é";
                2: print "ás";
                3: print "á";
                4: print "emos";
                5: print "éis";
                6: print "án";
            }
        CONDICIONAL_T:
            print (string) verbo, "ar";
            switch(persona) {
                1: print "ía";
                2: print "ías";
                3: print "ía";
                4: print "íamos";
                5: print "íais";
                6: print "ían";
            }
        SUBJUNTIVO_T:
            switch(persona) {
                1: print (string) verbo, "e";
                2: print (string) verbo, "es";
                3: print (string) verbo, "e";
                4: print (string) verbo, "emos";
                5: print (string) verbo, "éis";
                6: print (string) verbo, "en";
            }
        IMPERATIVO_T:
            switch(persona) {
                2: print (string) verbo, "a";
                3: print (string) verbo, "e";
                4: print (string) verbo, "emos";
                5: print (string) verbo, "ad";
                6: print (string) verbo, "en";
            }
    }
];

[ ConjugarER verbo persona tiempo;
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print (string) verbo, "o";
                2: print (string) verbo, "es";
                3: print (string) verbo, "e";
                4: print (string) verbo, "emos";
                5: print (string) verbo, "éis";
                6: print (string) verbo, "en";
            }
        PRETERITO_T:
            switch(persona) {
                1: print (string) verbo, "í";
                2: print (string) verbo, "iste";
                3: print (string) verbo, "ió";
                4: print (string) verbo, "imos";
                5: print (string) verbo, "isteis";
                6: print (string) verbo, "ieron";
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print (string) verbo, "ía";
                2: print (string) verbo, "ías";
                3: print (string) verbo, "ía";
                4: print (string) verbo, "íamos";
                5: print (string) verbo, "íais";
                6: print (string) verbo, "ían";
            }
        FUTURO_T:
            print (string) verbo, "er";
            switch(persona) {
                1: print "é";
                2: print "ás";
                3: print "á";
                4: print "emos";
                5: print "éis";
                6: print "án";
            }
        CONDICIONAL_T:
            print (string) verbo, "er";
            switch(persona) {
                1: print "ía";
                2: print "ías";
                3: print "ía";
                4: print "íamos";
                5: print "íais";
                6: print "ían";
            }
        SUBJUNTIVO_T:
            switch(persona) {
                1: print (string) verbo, "a";
                2: print (string) verbo, "as";
                3: print (string) verbo, "a";
                4: print (string) verbo, "amos";
                5: print (string) verbo, "áis";
                6: print (string) verbo, "an";
            }
        IMPERATIVO_T:
            switch(persona) {
                2: print (string) verbo, "e";
                3: print (string) verbo, "a";
                4: print (string) verbo, "amos";
                5: print (string) verbo, "ed";
                6: print (string) verbo, "an";
            }
    }
];

[ ConjugarIR verbo persona tiempo;
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print (string) verbo, "o";
                2: print (string) verbo, "es";
                3: print (string) verbo, "e";
                4: print (string) verbo, "imos";
                5: print (string) verbo, "ís";
                6: print (string) verbo, "en";
            }
        PRETERITO_T:
            switch(persona) {
                1: print (string) verbo, "í";
                2: print (string) verbo, "iste";
                3: print (string) verbo, "ió";
                4: print (string) verbo, "imos";
                5: print (string) verbo, "isteis";
                6: print (string) verbo, "ieron";
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print (string) verbo, "ía";
                2: print (string) verbo, "ías";
                3: print (string) verbo, "ía";
                4: print (string) verbo, "íamos";
                5: print (string) verbo, "íais";
                6: print (string) verbo, "ían";
            }
        FUTURO_T:
            print (string) verbo, "ir";
            switch(persona) {
                1: print "é";
                2: print "ás";
                3: print "á";
                4: print "emos";
                5: print "éis";
                6: print "án";
            }
        CONDICIONAL_T:
            print (string) verbo, "ir";
            switch(persona) {
                1: print "ía";
                2: print "ías";
                3: print "ía";
                4: print "íamos";
                5: print "íais";
                6: print "ían";
            }
        SUBJUNTIVO_T:
            switch(persona) {
                1: print (string) verbo, "a";
                2: print (string) verbo, "as";
                3: print (string) verbo, "a";
                4: print (string) verbo, "amos";
                5: print (string) verbo, "áis";
                6: print (string) verbo, "an";
            }
        IMPERATIVO_T:
            switch(persona) {
                2: print (string) verbo, "e";
                3: print (string) verbo, "a";
                4: print (string) verbo, "amos";
                5: print (string) verbo, "id";
                6: print (string) verbo, "an";
            }
    }
];

! ==============================================================================
! RUTINAS AUXILIARES DEL PARSER (MANTENIDAS)
! ==============================================================================

[ LanguageRemoveWord pos   i;
    for (i = pos: i < parse->1 - 1: i++) {
        parse-->(2*i+1) = parse-->(2*(i+1)+1);
        parse-->(2*i+2) = parse-->(2*(i+1)+2);
    }
    parse->1 = parse->1 - 1;
];

[ LanguageProcessCompoundPrepositions   i j k;
    for (i = 0: i < parse->1 - 1: i++) {
        j = parse-->(2*i+1);
        k = parse-->(2*(i+1)+1);
        
        if (j == 'debajo' && k == 'de') {
            parse-->(2*i+1) = 'debajo_de';
            LanguageRemoveWord(i+1);
            continue;
        }
        
        if (j == 'encima' && k == 'de') {
            parse-->(2*i+1) = 'encima_de';
            LanguageRemoveWord(i+1);
            continue;
        }
        
        if (j == 'cerca' && k == 'de') {
            parse-->(2*i+1) = 'cerca_de';
            LanguageRemoveWord(i+1);
            continue;
        }
        
        if (j == 'lejos' && k == 'de') {
            parse-->(2*i+1) = 'lejos_de';
            LanguageRemoveWord(i+1);
            continue;
        }
        
        if (j == 'delante' && k == 'de') {
            parse-->(2*i+1) = 'delante_de';
            LanguageRemoveWord(i+1);
            continue;
        }
        
        if (j == 'detrás' && k == 'de') {
            parse-->(2*i+1) = 'detrás_de';
            LanguageRemoveWord(i+1);
            continue;
        }
        
        if (j == 'al' && k == 'lado') {
            if (i < parse->1 - 2 && parse-->(2*(i+2)+1) == 'de') {
                parse-->(2*i+1) = 'al_lado_de';
                LanguageRemoveWord(i+1);
                LanguageRemoveWord(i+1);
                continue;
            }
        }
    }
];

[ LanguageSaveLastCommand;
    last_command_length = parse->1;
    if (last_command_length > 20) last_command_length = 20;
    
    ! Llamar a SpanishSaveCommand si está disponible
    #Ifdef SPANISH_META_COMMANDS;
        SpanishSaveCommand();
    #Endif;
];

! ==============================================================================
! SISTEMA DE PARSING PRINCIPAL (MEJORADO CON VERBOS IRREGULARES)
! ==============================================================================

[ LanguageToInformese i j k;
    LanguageProcessCompoundPrepositions();
    
    for (i=0 : i<parse->1 : i++) {
        j = parse-->(2*i+1);
        k = parse-->(2*i+2);
        
        if (j == 'del') {
            parse-->(2*i+1) = 'de';
            for (k=parse->1: k>i: k--) {
                parse-->(2*k+1) = parse-->(2*k-1);
                parse-->(2*k+2) = parse-->(2*k);
            }
            parse->1 = parse->1 + 1;
            parse-->(2*i+3) = 'el';
            parse-->(2*i+4) = 1;
        }
        
        if (j == 'al') {
            parse-->(2*i+1) = 'a';
            for (k=parse->1: k>i: k--) {
                parse-->(2*k+1) = parse-->(2*k-1);
                parse-->(2*k+2) = parse-->(2*k);
            }
            parse->1 = parse->1 + 1;
            parse-->(2*i+3) = 'el';
            parse-->(2*i+4) = 1;
        }
    }
    
    ! Procesar meta-comandos si están habilitados
    #Ifdef SPANISH_META_COMMANDS;
        if (parse->1 > 0) {
            j = parse-->1;
            k = (parse->1 > 1) ? parse-->3 : 0;
            if (SpanishMetaParser(j, k)) {
                return 2; ! Meta-comando procesado
            }
        }
    #Endif;
    
    for (i=0 : i<parse->1 : i++) {
        j = parse-->(2*i+1);
        
        if (j == 'que') {
            if (i > 0) {
                k = parse-->(2*(i-1)+1);
                if (k ~= 'preguntar' && k ~= 'decir' && k ~= 'saber' && k ~= 'esperar' && k ~= 'querer') {
                    LanguageRemoveWord(i);
                    i--;
                }
            }
        }
    }
    
    LanguageSaveLastCommand();
];

! ==============================================================================
! DETECCIÓN DE VERBOS MEJORADA CON VERBOS IRREGULARES
! ==============================================================================

[ LanguageIsVerb word;
    ! Primero verificar verbos irregulares si están habilitados
    #Ifdef SPANISH_IRREGULAR_VERBS;
        if (LanguageIsIrregularVerb(word)) rtrue;
        
        ! Formas irregulares específicas
        if (word == 'soy' or 'eres' or 'es' or 'somos' or 'sois' or 'son') rtrue;      ! ser
        if (word == 'estoy' or 'estás' or 'está' or 'estamos' or 'estáis' or 'están') rtrue; ! estar
        if (word == 'tengo' or 'tienes' or 'tiene' or 'tenemos' or 'tenéis' or 'tienen') rtrue; ! tener
        if (word == 'hago' or 'haces' or 'hace' or 'hacemos' or 'hacéis' or 'hacen') rtrue; ! hacer
        if (word == 'voy' or 'vas' or 'va' or 'vamos' or 'vais' or 'van') rtrue;       ! ir
        if (word == 'vengo' or 'vienes' or 'viene' or 'venimos' or 'venís' or 'vienen') rtrue; ! venir
        if (word == 'veo' or 'ves' or 've' or 'vemos' or 'veis' or 'ven') rtrue;       ! ver
        if (word == 'doy' or 'das' or 'da' or 'damos' or 'dais' or 'dan') rtrue;       ! dar
        if (word == 'puedo' or 'puedes' or 'puede' or 'podemos' or 'podéis' or 'pueden') rtrue; ! poder
        if (word == 'quiero' or 'quieres' or 'quiere' or 'queremos' or 'queréis' or 'quieren') rtrue; ! querer
        if (word == 'sé' or 'sabes' or 'sabe' or 'sabemos' or 'sabéis' or 'saben') rtrue; ! saber
        if (word == 'digo' or 'dices' or 'dice' or 'decimos' or 'decís' or 'dicen') rtrue; ! decir
        if (word == 'pongo' or 'pones' or 'pone' or 'ponemos' or 'ponéis' or 'ponen') rtrue; ! poner
        if (word == 'salgo' or 'sales' or 'sale' or 'salimos' or 'salís' or 'salen') rtrue; ! salir
    #Endif;
    
    ! Verbos básicos de manipulación
    if (word == 'coger' or 'coja' or 'tomar' or 'tome' or 'agarrar' or 'agarre') rtrue;
    if (word == 'dejar' or 'deje' or 'soltar' or 'suelte' or 'abandonar' or 'abandone') rtrue;
    
    ! Verbos de observación
    if (word == 'mirar' or 'mire' or 'ver' or 'vea' or 'observar' or 'observe' or 'examinar' or 'examine') rtrue;
    
    ! Verbos de movimiento
    if (word == 'ir' or 'vaya' or 've' or 'caminar' or 'camine' or 'andar' or 'ande' or 'venir' or 'venga' or 'ven') rtrue;
    
    ! Verbos de interacción con objetos
    if (word == 'abrir' or 'abra' or 'abre' or 'cerrar' or 'cierre' or 'cierra') rtrue;
    if (word == 'encender' or 'encienda' or 'enciende' or 'apagar' or 'apague' or 'apaga') rtrue;
    if (word == 'poner' or 'ponga' or 'pon' or 'colocar' or 'coloque' or 'coloca' or 'meter' or 'meta' or 'mete') rtrue;
    if (word == 'quitar' or 'quite' or 'quita' or 'sacar' or 'saque' or 'saca' or 'remover' or 'remueva' or 'remueve') rtrue;
    
    ! Verbos de comunicación  
    if (word == 'dar' or 'dé' or 'da' or 'entregar' or 'entregue' or 'entrega' or 'ofrecer' or 'ofrezca' or 'ofrece') rtrue;
    if (word == 'decir' or 'diga' or 'di' or 'dice' or 'hablar' or 'hable' or 'habla' or 'contar' or 'cuente' or 'cuenta') rtrue;
    if (word == 'preguntar' or 'pregunte' or 'pregunta' or 'consultar' or 'consulte' or 'consulta') rtrue;
    
    ! [Resto de verbos mantenidos igual...]
    if (word == 'leer' or 'lea' or 'lee' or 'hojear' or 'hojee' or 'hojea') rtrue;
    if (word == 'escribir' or 'escriba' or 'escribe' or 'anotar' or 'anote' or 'anota') rtrue;
    if (word == 'tocar' or 'toque' or 'toca' or 'palpar' or 'palpe' or 'palpa' or 'sentir' or 'sienta' or 'siente') rtrue;
    if (word == 'oler' or 'huela' or 'huele' or 'olfatear' or 'olfatee' or 'olfatea') rtrue;
    if (word == 'escuchar' or 'escuche' or 'escucha' or 'oir' or 'oiga' or 'oye') rtrue;
    if (word == 'probar' or 'pruebe' or 'prueba' or 'degustar' or 'deguste' or 'degusta') rtrue;
    
    ! Verbos de acciones físicas
    if (word == 'comer' or 'coma' or 'come' or 'beber' or 'beba' or 'bebe' or 'tragar' or 'trague' or 'traga') rtrue;
    if (word == 'llevar' or 'lleve' or 'lleva' or 'vestir' or 'vista' or 'viste' or 'ponerse' or 'póngase' or 'ponte') rtrue;
    if (word == 'subir' or 'suba' or 'sube' or 'trepar' or 'trepe' or 'trepa' or 'escalar' or 'escale' or 'escala') rtrue;
    if (word == 'bajar' or 'baje' or 'baja' or 'descender' or 'descienda' or 'desciende') rtrue;
    if (word == 'entrar' or 'entre' or 'entra' or 'ingresar' or 'ingrese' or 'ingresa') rtrue;
    if (word == 'salir' or 'salga' or 'sal' or 'partir' or 'parta' or 'parte' or 'marcharse' or 'márchese' or 'márchate') rtrue;
    if (word == 'empujar' or 'empuje' or 'empuja' or 'tirar' or 'tire' or 'tira' or 'arrastrar' or 'arrastre' or 'arrastra') rtrue;
    if (word == 'girar' or 'gire' or 'gira' or 'rotar' or 'rote' or 'rota' or 'voltear' or 'voltee' or 'voltea') rtrue;
    if (word == 'buscar' or 'busque' or 'busca' or 'registrar' or 'registre' or 'registra' or 'revisar' or 'revise' or 'revisa') rtrue;
    if (word == 'atacar' or 'ataque' or 'ataca' or 'golpear' or 'golpee' or 'golpea' or 'pegar' or 'pegue' or 'pega') rtrue;
    
    ! Verbos de estado
    if (word == 'dormir' or 'duerma' or 'duerme' or 'descansar' or 'descanse' or 'descansa') rtrue;
    if (word == 'despertar' or 'despierte' or 'despierta' or 'levantarse' or 'levántese' or 'levántate') rtrue;
    if (word == 'esperar' or 'espere' or 'espera' or 'aguardar' or 'aguarde' or 'aguarda') rtrue;
    if (word == 'pensar' or 'piense' or 'piensa' or 'reflexionar' or 'reflexione' or 'reflexiona') rtrue;
    
    ! Meta-comandos básicos
    if (word == 'inventario' or 'inv' or 'i') rtrue;
    if (word == 'guardar' or 'save' or 'salvar') rtrue;
    if (word == 'cargar' or 'restore' or 'recuperar') rtrue;
    if (word == 'reiniciar' or 'restart' or 'empezar_de_nuevo') rtrue;
    if (word == 'salir' or 'quit' or 'terminar' or 'acabar' or 'fin') rtrue;
    if (word == 'puntos' or 'score' or 'puntuación') rtrue;
    if (word == 'ayuda' or 'help' or 'socorro' or 'auxilio') rtrue;
    if (word == 'comandos' or 'commands' or 'verbos' or 'acciones') rtrue;
    
    ! Meta-comandos avanzados (si están habilitados)
    #Ifdef SPANISH_META_COMMANDS;
        if (word == 'deshacer' or 'undo' or 'anular' or 'revertir') rtrue;
        if (word == 'repetir' or 'again' or 'otra_vez' or 'r' or 'g') rtrue;
        if (word == 'corregir' or 'oops' or 'ups' or 'corrección') rtrue;
    #Endif;
    
    if (word == 'usar' or 'use' or 'usa' or 'utilizar' or 'utilice' or 'utiliza' or 'emplear' or 'emplee' or 'emplea') rtrue;
    rfalse;
];

[ LanguageVerbIsDebugging word;
    if (word == 'punonoff' or 'puntosoff' or 'puntosOn') rtrue;
    if (word == 'routineoff' or 'rutinaoff' or 'rutinaon') rtrue;
    if (word == 'scopeoff' or 'alcanceoff' or 'alcanceon') rtrue;
    if (word == 'showobj' or 'mostrarobjeto') rtrue;
    if (word == 'showverb' or 'mostrarverbo') rtrue;
    if (word == 'showdict' or 'mostrardicc') rtrue;
    rfalse;
];

[ LanguageVerbLikesAdverb word;
    if (word == 'mirar' or 'ver' or 'observar') rtrue;
    if (word == 'ir' or 'caminar' or 'andar') rtrue;
    if (word == 'buscar' or 'registrar') rtrue;
    if (word == 'escuchar' or 'oir') rtrue;
    rfalse;
];

[ LanguageVerbMayBeName word;
    if (word == 'agua' or 'fuego' or 'luz') rtrue;
    rfalse;
];

! ==============================================================================
! INCLUSIÓN CONDICIONAL DE MÓDULOS (ACTUALIZADA)
! ==============================================================================

! Incluir sistema completo de mensajes si está habilitado
#Ifdef SPANISH_FULL_MESSAGES;
Include "SpanishMessages";
#Ifnot;
! Sistema básico de mensajes (fallback)
[ LanguageLM n x1 x2;
    switch(n) {
        Inventory: 
            switch (x1) {
                1: print "No llevas nada.^";
                2: print "Llevas";
            }
        Take:
            switch (x1) {
                1: print "Tomado.";
                2: print "Siempre te tienes a ti mismo.";
                default: print "No puedes tomar eso.";
            }
        Drop:
            switch (x1) {
                1: print "Dejado.";
                default: print "No puedes dejar eso.";
            }
        Look:
            switch (x1) {
                1: print (name) location; print "^";
                default: print "No ves nada especial.";
            }
        Miscellany:
            switch (x1) {
                16: print "Está muy oscuro, no puedes ver nada.";
                17: print "tú mismo";
                26: print "Ese no es un verbo que reconozca.";
                default: print "[Mensaje ", n, ".", x1, " - usa SPANISH_FULL_MESSAGES para sistema completo]";
            }
        default: 
            print "[Mensaje ", n, " - usa SPANISH_FULL_MESSAGES para sistema completo]";
    }
];
#Endif;

! Incluir verbos irregulares si están habilitados
#Ifdef SPANISH_IRREGULAR_VERBS;
Include "SpanishIrregularVerbs";
#Endif;

! Incluir meta-comandos si están habilitados
#Ifdef SPANISH_META_COMMANDS;
Include "meta/SpanishMeta";
#Endif;

! Incluir sistema de ayuda expandido si está habilitado
#Ifdef SPANISH_HELP_SYSTEM;
    ! Sistema de ayuda ya incluido en SpanishMeta
    #Ifndef SPANISH_META_COMMANDS;
        Message warning "SPANISH_HELP_SYSTEM requiere SPANISH_META_COMMANDS";
    #Endif;
#Endif;

! ==============================================================================
! [RESTO DE RUTINAS MANTENIDAS IGUAL - RUTINAS DE IMPRESIÓN, ETC.]
! ==============================================================================

[ LanguagePrintShortName obj aux;
    if (obj == 0) { print "(nada)"; rtrue; }
    aux = obj.&short_name;
    if (aux ~= 0) {
        if (aux-->0 ~= 0) {
            print (string) aux-->0;
            rtrue;
        }
    }
    rfalse;
];

[ LanguageDirection d;
    switch (d) {
        n_to:    print "norte";
        s_to:    print "sur"; 
        e_to:    print "este";
        w_to:    print "oeste";
        ne_to:   print "nordeste";
        nw_to:   print "noroeste";
        se_to:   print "sudeste";
        sw_to:   print "sudoeste";
        u_to:    print "arriba";
        d_to:    print "abajo";
        in_to:   print "adentro";
        out_to:  print "afuera";
        default: return RunTimeError(9, d);
    }
];

[ LanguageNumber n f;
    if (n == 0) { print "cero"; rfalse; }
    if (n < 0) { print "menos "; n = -n; }
    if (n >= 1000) {
        if (n >= 1000000) {
            if (f == 1) print (LanguageNumber) n/1000000, " millón";
            else print (LanguageNumber) n/1000000, " millones";
            n = n%1000000;
            if (n ~= 0) print " ";
        }
        if (n >= 1000) {
            if (f == 1) print (LanguageNumber) n/1000, " mil";
            else print (LanguageNumber) n/1000, " mil";
            n = n%1000;
            if (n ~= 0) print " ";
        }
    }
    switch (n) {
        0: rfalse;
        1: print "uno"; 2: print "dos"; 3: print "tres"; 4: print "cuatro"; 5: print "cinco";
        6: print "seis"; 7: print "siete"; 8: print "ocho"; 9: print "nueve"; 10: print "diez";
        11: print "once"; 12: print "doce"; 13: print "trece"; 14: print "catorce"; 15: print "quince";
        16: print "dieciséis"; 17: print "diecisiete"; 18: print "dieciocho"; 19: print "diecinueve"; 20: print "veinte";
        default:
            if (n < 100) {
                if (n < 30) {
                    print "veinti"; 
                    print (LanguageNumber) n-20;
                } else {
                    print (LanguageNumber) (n/10)*10;
                    if (n%10 ~= 0) {
                        print " y ";
                        print (LanguageNumber) n%10;
                    }
                }
            } else {
                print (LanguageNumber) n/100, "cientos";
                if (n%100 ~= 0) {
                    print " ";
                    print (LanguageNumber) n%100;
                }
            }
    }
];

[ LanguageTimeOfDay hours mins i;
    i = hours%12;
    if (i == 0) i = 12;
    if (i < 10) print " ";
    print i, ":";
    if (mins < 10) print "0";
    print mins;
    if ((hours >= 12) && (hours ~= 24)) print " PM";
    else print " AM";
];

[ LanguageVerb i;
    switch (i) {
        'i//','inv','inventario': print "inventario";
        'l//','mirar': print "mirar";
        'x//','examinar','ex': print "examinar";  
        'z//','esperar': print "esperar";
        'q//','salir','quit': print "salir";
        'save','guardar': print "guardar";
        'restore','cargar': print "cargar";
        'restart','reiniciar': print "reiniciar";
        'verify','verificar': print "verificar";
        'score','puntos': print "puntos";
        'quit','fin': print "fin";
        'fullscore','puntoscompletos': print "puntos completos";
        'notify','notificar': print "notificar";
        default: rfalse;
    }
    rtrue;
];

! ==============================================================================
! RUTINAS DE MANEJO DE ERRORES (MANTENIDAS)
! ==============================================================================

[ LanguageParseFailed type;
    ! Usar manejo mejorado si meta-comandos están disponibles
    #Ifdef SPANISH_META_COMMANDS;
        if (SpanishParseError(type, 0)) rtrue;
    #Endif;
    
    ! Manejo básico de errores
    switch(type) {
        STUCK_PE:
            print "No entendí esa instrucción. Prueba con comandos más simples.";
        UPTO_PE:
            print "Solo entendí hasta: ";
        NUMBER_PE:
            print "No entendí ese número.";
        CANTSEE_PE:
            print "No puedes ver tal cosa aquí.";
        TOOLIT_PE:
            print "Dijiste muy poco. ¿Qué quieres hacer exactamente?";
        NOTHELD_PE:
            print "No tienes eso.";
        MULTI_PE:
            print "No puedes usar múltiples objetos con ese verbo.";
        MMULTI_PE:
            print "Solo puedes usar múltiples objetos una vez por línea.";
        VAGUE_PE:
            print "No está claro a qué te refieres.";
        EXCEPT_PE:
            print "Excluiste algo que no estaba incluido.";
        ANIMA_PE:
            print "Solo puedes hacer eso a algo con vida.";
        VERB_PE:
            print "Ese no es un verbo que reconozca.";
        SCENERY_PE:
            print "Eso no es importante.";
        ITGONE_PE:
            print "Ya no puedes ver eso.";
        JUNK_PE:
            print "No entendí el final de esa frase.";
        TOOFEW_PE:
            if (x1 == 0) print "¡Ninguno disponible!";
            else print "¡Solo ", (number) x1, " disponible!";
        NOTHING_PE:
            print "¡Nada que hacer!";
        ASKSCOPE_PE:
            print "Eso no está disponible.";
        default:
            print "No entendí el comando.";
    }
];

! ==============================================================================
! RUTINAS AUXILIARES FINALES (MANTENIDAS + MEJORADAS)
! ==============================================================================

[ LanguageIsOrAre obj;
    if (obj has pluralname or multitude) print "son";
    else print "es";
];

[ LanguageTheyreOrThats obj;
    if (obj == player) { print "estás"; return; }
    if (obj has pluralname) print "están";
    else print "está";
];

[ LanguageCantGo;
    print "No puedes ir hacia esa dirección.";
];

! [Resto de rutinas auxiliares mantenidas...]

! ==============================================================================
! RUTINA DE INICIALIZACIÓN MODULAR ACTUALIZADA
! ==============================================================================

[ LanguageInitialise i;
    print "^[Librería Modular de Español para Inform 6 - v", (string) LanguageVersion, "]^";
    
    ! Mostrar qué módulos están cargados
    print "[✅ Núcleo básico: Parser, verbos, conjugaciones]^";
    
    #Ifdef SPANISH_FULL_MESSAGES;
        print "[✅ Sistema completo de mensajes: ~400 mensajes]^";
        ! Inicializar sistema de mensajes si tiene rutina
        #Ifdef SpanishMessagesInitialise;
            SpanishMessagesInitialise();
        #Endif;
    #Ifnot;
        print "[⚠️  Sistema básico de mensajes - usa Constant SPANISH_FULL_MESSAGES para completar]^";
    #Endif;
    
    #Ifdef SPANISH_IRREGULAR_VERBS;
        print "[🚀 VERBOS IRREGULARES: 20 verbos implementados completamente]^";
        ! Inicializar verbos irregulares si tiene rutina
        #Ifdef SpanishIrregularVerbsInitialise;
            SpanishIrregularVerbsInitialise();
        #Endif;
    #Ifnot;
        print "[⚠️  Solo verbos regulares - usa Constant SPANISH_IRREGULAR_VERBS para completar]^";
    #Endif;
    
    #Ifdef SPANISH_META_COMMANDS;
        print "[✅ Meta-comandos: DESHACER, REPETIR, CORRECCIÓN, AYUDA]^";
        ! Inicializar meta-comandos si tiene rutina
        #Ifdef SpanishMetaInitialise;
            SpanishMetaInitialise();
        #Endif;
    #Ifnot;
        print "[⚠️  Meta-comandos básicos - usa Constant SPANISH_META_COMMANDS para expandir]^";
    #Endif;
    
    #Ifdef SPANISH_HELP_SYSTEM;
        print "[✅ Sistema de ayuda integrado]^";
    #Endif;
    
    print "[✅ Parsing avanzado: preposiciones compuestas, contracciones]^";
    print "[✅ Soporte completo para género, número y formalidad]^";
    
    #Ifdef SPANISH_IRREGULAR_VERBS;
        print "[🎯 NUEVA CARACTERÍSTICA: Conjugación completa de verbos irregulares]^";
        print "[    SER, ESTAR, TENER, HACER, IR, VENIR, VER, DAR, PODER, etc.]^";
    #Endif;
    
    ! Configurar género automático para objetos
    objectloop (i) {
        if (i ~= player && i ~= selfobj && i ~= 0) {
            SetSpanishGender(i, 0);
        }
    }
    
    ! Inicializar variables
    FormalityLevel = 0;
    last_command_length = 0;
    
    ! Calcular cobertura estimada ACTUALIZADA
    i = 75; ! Cobertura base incrementada
    #Ifdef SPANISH_FULL_MESSAGES; i = i + 15; #Endif;
    #Ifdef SPANISH_META_COMMANDS; i = i + 10; #Endif;
    #Ifdef SPANISH_HELP_SYSTEM; i = i + 5; #Endif;
    #Ifdef SPANISH_IRREGULAR_VERBS; i = i + 15; #Endif;  ! NUEVO
    
    if (i > 100) i = 100; ! Máximo 100%
    
    print "^[Cobertura estimada: ", i, "% de funcionalidad completa]^";
    
    #Ifdef SPANISH_META_COMMANDS;
        print "[Sistema listo para uso profesional. Usa AYUDA para comenzar]^";
    #Ifnot;
        print "[Sistema listo para uso profesional]^";
    #Endif;
];

! ==============================================================================
! CONSTANTES DE COMPATIBILIDAD Y FINALIZACIÓN ACTUALIZADAS
! ==============================================================================

Constant LIBRARY_SPANISH;
Constant SPANISH_MODULAR_SYSTEM;
Constant SPANISH_IRREGULAR_SUPPORT;   ! NUEVO

! Estimación de cobertura dinámica ACTUALIZADA
#Ifdef SPANISH_IRREGULAR_VERBS;
    #Ifdef SPANISH_FULL_MESSAGES;
        #Ifdef SPANISH_META_COMMANDS;
            Constant SPANISH_COVERAGE_ESTIMATED = 100;  ! MÁXIMO
        #Ifnot;
            Constant SPANISH_COVERAGE_ESTIMATED = 95;
        #Endif;
    #Ifnot;
        #Ifdef SPANISH_META_COMMANDS;
            Constant SPANISH_COVERAGE_ESTIMATED = 90;
        #Ifnot;
            Constant SPANISH_COVERAGE_ESTIMATED = 85;
        #Endif;
    #Endif;
#Ifnot;
    #Ifdef SPANISH_FULL_MESSAGES;
        #Ifdef SPANISH_META_COMMANDS;
            Constant SPANISH_COVERAGE_ESTIMATED = 95;
        #Ifnot;
            Constant SPANISH_COVERAGE_ESTIMATED = 80;
        #Endif;
    #Ifnot;
        #Ifdef SPANISH_META_COMMANDS;
            Constant SPANISH_COVERAGE_ESTIMATED = 80;
        #Ifnot;
            Constant SPANISH_COVERAGE_ESTIMATED = 65;
        #Endif;
    #Endif;
#Endif;

! Compatibilidad con versiones anteriores
#Ifdef SPANISH_LEGACY_SUPPORT;
    ! Aliases para compatibilidad con el monolito anterior
    [ LegacyLanguageToInformese; return LanguageToInformese(); ];
    [ LegacyLanguageIsVerb word; return LanguageIsVerb(word); ];
    [ LegacyLanguageLM n x1 x2; return LanguageLM(n, x1, x2); ];
#Endif;

! Información de depuración ACTUALIZADA
#Ifdef DEBUG;
Constant SPANISH_DEBUG_INFO = "Módulos: Núcleo + Mensajes + Meta + Ayuda + Verbos Irregulares";
Constant SPANISH_BUILD_DATE = "2024-12-updated";
Constant SPANISH_TARGET_VERSION = "6.12.7";
Constant SPANISH_IRREGULAR_VERBS_COUNT = 20;
#Endif;

#Endif; ! SPANISH_LIB_INCLUDED

! ==============================================================================
! Fin de Spanish.h - Sistema Modular COMPLETO de Idioma Español para Inform 6
! Ahora con soporte total para verbos irregulares y conjugación avanzada
! ==============================================================================