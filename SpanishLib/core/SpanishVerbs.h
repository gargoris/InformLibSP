! ==============================================================================
! SPANISHVERBS.H - Sistema completo de verbos y conjugaciones en español
! Parte del sistema modular Spanish Library para Inform 6
! Compatible con Inform 6.42 y librería estándar 6.12.7
! ==============================================================================

System_file;

#Ifndef SPANISH_VERBS_INCLUDED;
Constant SPANISH_VERBS_INCLUDED;
Constant SPANISH_VERBS_VERSION = "1.1-cleaned";

! Verificación de dependencias
#Ifndef SPANISH_CONSTANTS_INCLUDED;
  Message fatalerror "*** Include SpanishConstants.h antes de SpanishVerbs.h ***";
#Endif;

#Ifndef SPANISH_CORE_INCLUDED;
  Message fatalerror "*** Include SpanishCore.h antes de SpanishVerbs.h ***";
#Endif;

! ==============================================================================
! SISTEMA DE CONJUGACIÓN DE VERBOS REGULARES
! ==============================================================================

! Detectar el tipo de verbo según su terminación
[ DetectarTipoVerbo verbo;
    ! Esta función asume que 'verbo' es una string o dictionary word
    ! Devuelve: 1 = -AR, 2 = -ER, 3 = -IR, 0 = irregular o no reconocido
    
    local len;
    
    ! Si es dictionary word, convertir a string para análisis
    if (verbo < 256) return 0; ! No es string válida
    
    len = verbo->0;
    if (len < 2) return 0; ! Muy corto para ser verbo
    
    if (verbo->(len) == 'r') { ! Última letra es 'r'
        if (verbo->(len-1) == 'a') return 1; ! -AR
        if (verbo->(len-1) == 'e') return 2; ! -ER
        if (verbo->(len-1) == 'i') return 3; ! -IR
    }
    
    return 0; ! No reconocido como verbo regular
];

! Obtener la raíz de un verbo (sin -ar, -er, -ir)
[ ObtenerRaizVerbo verbo buffer   len i;
    len = verbo->0;
    if (len < 3) return 0;
    
    ! Copiar todo excepto las últimas 2 letras
    for (i = 0: i < len - 2: i++) {
        buffer->(i+1) = verbo->(i+1);
    }
    buffer->0 = len - 2;
    
    return buffer;
];

! ==============================================================================
! CONJUGACIONES DE VERBOS REGULARES - CORREGIDAS
! ==============================================================================

[ ConjugarAR raiz persona tiempo;
    ! raiz debe ser la raíz del verbo sin -ar
    switch(tiempo) {
        PRESENTE_T:
            print (string) raiz;
            switch(persona) {
                1: print "o";
                2: print "as";
                3: print "a";
                4: print "amos";
                5: print "áis";
                6: print "an";
            }
        PRETERITO_T:
            print (string) raiz;
            switch(persona) {
                1: print "é";
                2: print "aste";
                3: print "ó";
                4: print "amos";
                5: print "asteis";
                6: print "aron";
            }
        IMPERFECTO_T:
            print (string) raiz;
            switch(persona) {
                1: print "aba";
                2: print "abas";
                3: print "aba";
                4: print "ábamos";
                5: print "abais";
                6: print "aban";
            }
        FUTURO_T:
            print (string) raiz; print "ar";
            switch(persona) {
                1: print "é";
                2: print "ás";
                3: print "á";
                4: print "emos";
                5: print "éis";
                6: print "án";
            }
        CONDICIONAL_T:
            print (string) raiz; print "ar";
            switch(persona) {
                1: print "ía";
                2: print "ías";
                3: print "ía";
                4: print "íamos";
                5: print "íais";
                6: print "ían";
            }
        SUBJUNTIVO_T:
            print (string) raiz;
            switch(persona) {
                1: print "e";
                2: print "es";
                3: print "e";
                4: print "emos";
                5: print "éis";
                6: print "en";
            }
        IMPERATIVO_T:
            print (string) raiz;
            switch(persona) {
                2: print "a";
                3: print "e";
                4: print "emos";
                5: print "ad";
                6: print "en";
            }
    }
];

[ ConjugarER raiz persona tiempo;
    ! raiz debe ser la raíz del verbo sin -er
    switch(tiempo) {
        PRESENTE_T:
            print (string) raiz;
            switch(persona) {
                1: print "o";
                2: print "es";
                3: print "e";
                4: print "emos";
                5: print "éis";
                6: print "en";
            }
        PRETERITO_T:
            print (string) raiz;
            switch(persona) {
                1: print "í";
                2: print "iste";
                3: print "ió";
                4: print "imos";
                5: print "isteis";
                6: print "ieron";
            }
        IMPERFECTO_T:
            print (string) raiz;
            switch(persona) {
                1: print "ía";
                2: print "ías";
                3: print "ía";
                4: print "íamos";
                5: print "íais";
                6: print "ían";
            }
        FUTURO_T:
            print (string) raiz; print "er";
            switch(persona) {
                1: print "é";
                2: print "ás";
                3: print "á";
                4: print "emos";
                5: print "éis";
                6: print "án";
            }
        CONDICIONAL_T:
            print (string) raiz; print "er";
            switch(persona) {
                1: print "ía";
                2: print "ías";
                3: print "ía";
                4: print "íamos";
                5: print "íais";
                6: print "ían";
            }
        SUBJUNTIVO_T:
            print (string) raiz;
            switch(persona) {
                1: print "a";
                2: print "as";
                3: print "a";
                4: print "amos";
                5: print "áis";
                6: print "an";
            }
        IMPERATIVO_T:
            print (string) raiz;
            switch(persona) {
                2: print "e";
                3: print "a";
                4: print "amos";
                5: print "ed";
                6: print "an";
            }
    }
];

[ ConjugarIR raiz persona tiempo;
    ! raiz debe ser la raíz del verbo sin -ir
    switch(tiempo) {
        PRESENTE_T:
            print (string) raiz;
            switch(persona) {
                1: print "o";
                2: print "es";
                3: print "e";
                4: print "imos";
                5: print "ís";
                6: print "en";
            }
        PRETERITO_T:
            print (string) raiz;
            switch(persona) {
                1: print "í";
                2: print "iste";
                3: print "ió";
                4: print "imos";
                5: print "isteis";
                6: print "ieron";
            }
        IMPERFECTO_T:
            print (string) raiz;
            switch(persona) {
                1: print "ía";
                2: print "ías";
                3: print "ía";
                4: print "íamos";
                5: print "íais";
                6: print "ían";
            }
        FUTURO_T:
            print (string) raiz; print "ir";
            switch(persona) {
                1: print "é";
                2: print "ás";
                3: print "á";
                4: print "emos";
                5: print "éis";
                6: print "án";
            }
        CONDICIONAL_T:
            print (string) raiz; print "ir";
            switch(persona) {
                1: print "ía";
                2: print "ías";
                3: print "ía";
                4: print "íamos";
                5: print "íais";
                6: print "ían";
            }
        SUBJUNTIVO_T:
            print (string) raiz;
            switch(persona) {
                1: print "a";
                2: print "as";
                3: print "a";
                4: print "amos";
                5: print "áis";
                6: print "an";
            }
        IMPERATIVO_T:
            print (string) raiz;
            switch(persona) {
                2: print "e";
                3: print "a";
                4: print "amos";
                5: print "id";
                6: print "an";
            }
    }
];

! ==============================================================================
! SISTEMA PRINCIPAL DE CONJUGACIÓN - PREPARADO PARA IRREGULARES
! ==============================================================================

[ ConjugarVerbo_Regular verbo persona tiempo tipo   raiz_buffer;
    ! Función base para verbos regulares - preparada para ser extendida
    
    ! Si no se especifica tipo, detectarlo
    if (tipo == 0) tipo = DetectarTipoVerbo(verbo);
    
    ! Obtener raíz del verbo
    if (ObtenerRaizVerbo(verbo, raiz_buffer) == 0) {
        ! Si no se puede obtener raíz, imprimir infinitivo
        print (string) verbo;
        return false;
    }
    
    switch(tipo) {
        1: ConjugarAR(raiz_buffer, persona, tiempo);
        2: ConjugarER(raiz_buffer, persona, tiempo);
        3: ConjugarIR(raiz_buffer, persona, tiempo);
        default:
            ! No se puede conjugar, imprimir infinitivo
            print (string) verbo;
            return false;
    }
    return true;
];

[ ConjugarVerbo verbo persona tiempo tipo;
    ! Función principal que será extendida por SpanishIrregularVerbs.h
    ! Por ahora solo maneja verbos regulares
    
    #Ifdef SPANISH_IRREGULAR_VERBS_INCLUDED;
        ! Si hay módulo de irregulares, intentar primero con irregulares
        if (SpanishConjugarIrregular(verbo, persona, tiempo)) return true;
    #Endif;
    
    #Ifdef SPANISH_REGIONAL_INCLUDED;
        ! Si hay soporte regional y es voseo, usar conjugación especial
        if (voseo_enabled && persona == 2 && current_spanish_region == REGION_ARGENTINA) {
            if (ConjugarVoseo(verbo, tiempo, tipo)) return true;
        }
    #Endif;
    
    ! Fallback a conjugación regular
    return ConjugarVerbo_Regular(verbo, persona, tiempo, tipo);
];

! ==============================================================================
! DETECCIÓN DE VERBOS - EXPANDIDA Y ORGANIZADA
! ==============================================================================

[ LanguageIsVerb word;
    ! Verbos básicos de manipulación
    if (word == 'coger' or 'coja' or 'tomar' or 'tome' or 'agarrar' or 'agarre') rtrue;
    if (word == 'dejar' or 'deje' or 'soltar' or 'suelte' or 'abandonar' or 'abandone') rtrue;
    if (word == 'poner' or 'ponga' or 'pon' or 'colocar' or 'coloque' or 'coloca') rtrue;
    if (word == 'quitar' or 'quite' or 'quita' or 'sacar' or 'saque' or 'saca') rtrue;
    if (word == 'meter' or 'meta' or 'mete' or 'insertar' or 'inserte' or 'inserta') rtrue;
    
    ! Verbos de observación
    if (word == 'mirar' or 'mire' or 'ver' or 'vea' or 'observar' or 'observe') rtrue;
    if (word == 'examinar' or 'examine' or 'inspeccionar' or 'inspeccione') rtrue;
    if (word == 'buscar' or 'busque' or 'registrar' or 'registre' or 'revisar' or 'revise') rtrue;
    
    ! Verbos de movimiento
    if (word == 'ir' or 'vaya' or 've' or 'caminar' or 'camine' or 'andar' or 'ande') rtrue;
    if (word == 'venir' or 'venga' or 'ven' or 'llegar' or 'llegue' or 'llega') rtrue;
    if (word == 'correr' or 'corra' or 'corre' or 'trotar' or 'trote') rtrue;
    if (word == 'saltar' or 'salte' or 'salta' or 'brincar' or 'brinque') rtrue;
    if (word == 'subir' or 'suba' or 'sube' or 'trepar' or 'trepe') rtrue;
    if (word == 'bajar' or 'baje' or 'baja' or 'descender' or 'descienda') rtrue;
    if (word == 'entrar' or 'entre' or 'entra' or 'ingresar' or 'ingrese') rtrue;
    if (word == 'salir' or 'salga' or 'sal' or 'partir' or 'parta') rtrue;
    
    ! Verbos de interacción con objetos
    if (word == 'abrir' or 'abra' or 'abre' or 'cerrar' or 'cierre' or 'cierra') rtrue;
    if (word == 'encender' or 'encienda' or 'enciende' or 'apagar' or 'apague') rtrue;
    if (word == 'empujar' or 'empuje' or 'empuja' or 'tirar' or 'tire' or 'tira') rtrue;
    if (word == 'girar' or 'gire' or 'gira' or 'rotar' or 'rote' or 'voltear' or 'voltee') rtrue;
    if (word == 'romper' or 'rompa' or 'rompe' or 'quebrar' or 'quiebre') rtrue;
    
    ! Verbos de comunicación e interacción social
    if (word == 'dar' or 'dé' or 'da' or 'entregar' or 'entregue' or 'ofrecer' or 'ofrezca') rtrue;
    if (word == 'decir' or 'diga' or 'di' or 'hablar' or 'hable' or 'contar' or 'cuente') rtrue;
    if (word == 'preguntar' or 'pregunte' or 'consultar' or 'consulte') rtrue;
    if (word == 'responder' or 'responda' or 'contestar' or 'conteste') rtrue;
    if (word == 'mostrar' or 'muestre' or 'enseñar' or 'enseñe') rtrue;
    
    ! Verbos de los sentidos
    if (word == 'tocar' or 'toque' or 'toca' or 'palpar' or 'palpe' or 'sentir' or 'sienta') rtrue;
    if (word == 'oler' or 'huela' or 'huele' or 'olfatear' or 'olfatee') rtrue;
    if (word == 'escuchar' or 'escuche' or 'oir' or 'oiga' or 'oye') rtrue;
    if (word == 'probar' or 'pruebe' or 'prueba' or 'degustar' or 'deguste') rtrue;
    if (word == 'leer' or 'lea' or 'lee' or 'escribir' or 'escriba' or 'escribe') rtrue;
    
    ! Verbos de acciones físicas
    if (word == 'comer' or 'coma' or 'come' or 'beber' or 'beba' or 'bebe') rtrue;
    if (word == 'tragar' or 'trague' or 'traga' or 'masticar' or 'mastique') rtrue;
    if (word == 'llevar' or 'lleve' or 'lleva' or 'vestir' or 'vista' or 'viste') rtrue;
    if (word == 'ponerse' or 'póngase' or 'ponte' or 'quitarse' or 'quítese' or 'quítate') rtrue;
    if (word == 'atacar' or 'ataque' or 'golpear' or 'golpee' or 'pegar' or 'pegue') rtrue;
    if (word == 'cortar' or 'corte' or 'partir' or 'parta') rtrue;
    
    ! Verbos de estado
    if (word == 'dormir' or 'duerma' or 'duerme' or 'descansar' or 'descanse') rtrue;
    if (word == 'despertar' or 'despierte' or 'levantarse' or 'levántese') rtrue;
    if (word == 'esperar' or 'espere' or 'espera' or 'aguardar' or 'aguarde') rtrue;
    if (word == 'pensar' or 'piense' or 'piensa' or 'reflexionar' or 'reflexione') rtrue;
    if (word == 'recordar' or 'recuerde' or 'olvidar' or 'olvide') rtrue;
    
    ! Verbos de manipulación avanzada
    if (word == 'usar' or 'use' or 'usa' or 'utilizar' or 'utilice' or 'emplear' or 'emplee') rtrue;
    if (word == 'arreglar' or 'arregle' or 'reparar' or 'repare' or 'componer' or 'componga') rtrue;
    if (word == 'construir' or 'construya' or 'construye' or 'crear' or 'cree' or 'crea') rtrue;
    if (word == 'destruir' or 'destruya' or 'destruye' or 'demoler' or 'demuela') rtrue;
    
    ! Meta-comandos básicos
    if (word == 'inventario' or 'inv' or 'i') rtrue;
    if (word == 'guardar' or 'save' or 'salvar') rtrue;
    if (word == 'cargar' or 'restore' or 'recuperar') rtrue;
    if (word == 'reiniciar' or 'restart' or 'empezar') rtrue;
    if (word == 'salir' or 'quit' or 'terminar' or 'fin') rtrue;
    if (word == 'puntos' or 'score' or 'puntuación') rtrue;
    if (word == 'ayuda' or 'help' or 'socorro') rtrue;
    if (word == 'comandos' or 'commands' or 'verbos') rtrue;
    
    ! Meta-comandos avanzados (si están habilitados)
    #Ifdef SPANISH_META_INCLUDED;
        if (word == 'deshacer' or 'undo' or 'anular') rtrue;
        if (word == 'repetir' or 'again' or 'otra_vez' or 'r' or 'g') rtrue;
        if (word == 'corregir' or 'oops' or 'ups' or 'corrección') rtrue;
    #Endif;
    
    rfalse;
];

! ==============================================================================
! UTILIDADES DE VERBOS
! ==============================================================================

[ RequiereCambioRaiz verbo;
    ! Verbos que requieren cambio de raíz (para futura expansión)
    ! e->ie: pensar, querer, cerrar, etc.
    if (verbo == 'pensar' or 'querer' or 'cerrar' or 'empezar' or 'sentir') rtrue;
    
    ! o->ue: poder, dormir, volver, etc.
    if (verbo == 'poder' or 'dormir' or 'volver' or 'mover' or 'contar') rtrue;
    
    ! e->i: pedir, servir, seguir, etc.
    if (verbo == 'pedir' or 'servir' or 'seguir' or 'repetir' or 'vestir') rtrue;
    
    rfalse;
];

[ EsVerboReflexivo verbo;
    ! Detectar verbos reflexivos comunes
    if (verbo == 'levantarse' or 'acostarse' or 'vestirse' or 'quitarse') rtrue;
    if (verbo == 'lavarse' or 'peinarse' or 'ducharse' or 'bañarse') rtrue;
    if (verbo == 'sentarse' or 'pararse' or 'quedarse' or 'irse') rtrue;
    if (verbo == 'llamarse' or 'despertarse' or 'dormirse') rtrue;
    rfalse;
];

[ EsVerboImpersonal verbo;
    ! Verbos que se usan solo en tercera persona
    if (verbo == 'llover' or 'nevar' or 'granizar' or 'tronar') rtrue;
    if (verbo == 'haber' or 'hacer' or 'ser') rtrue; ! En construcciones impersonales
    rfalse;
];

! ==============================================================================
! FUNCIONES AUXILIARES PARA INTEGRACIÓN
! ==============================================================================

[ LanguageVerbIsDebugging word;
    ! Verbos de depuración en español
    if (word == 'punonoff' or 'puntosoff' or 'puntosOn') rtrue;
    if (word == 'routineoff' or 'rutinaoff' or 'rutinaon') rtrue;
    if (word == 'scopeoff' or 'alcanceoff' or 'alcanceon') rtrue;
    if (word == 'showobj' or 'mostrarobjeto') rtrue;
    if (word == 'showverb' or 'mostrarverbo') rtrue;
    if (word == 'showdict' or 'mostrardicc') rtrue;
    if (word == 'trace' or 'rastrear' or 'debug' or 'depurar') rtrue;
    rfalse;
];

[ LanguageVerbLikesAdverb word;
    ! Verbos que aceptan adverbios de modo naturalmente
    if (word == 'mirar' or 'ver' or 'observar' or 'examinar') rtrue;
    if (word == 'ir' or 'caminar' or 'andar' or 'correr') rtrue;
    if (word == 'buscar' or 'registrar' or 'revisar') rtrue;
    if (word == 'escuchar' or 'oir' or 'hablar' or 'decir') rtrue;
    if (word == 'pensar' or 'reflexionar' or 'recordar') rtrue;
    if (word == 'trabajar' or 'estudiar' or 'leer' or 'escribir') rtrue;
    rfalse;
];

[ LanguageVerbMayBeName word;
    ! Palabras que pueden ser confundidas con verbos pero son nombres
    if (word == 'agua' or 'fuego' or 'luz' or 'aire') rtrue;
    if (word == 'amor' or 'dolor' or 'calor' or 'color') rtrue;
    if (word == 'lugar' or 'hogar' or 'azúcar') rtrue;
    rfalse;
];

! ==============================================================================
! INFORMACIÓN DE VERBOS PARA AYUDA
! ==============================================================================

[ LanguageVerb i;
    ! Información de verbos para comandos de ayuda
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
        'g//','r//','again','repetir': print "repetir";
        'oops','ups','corrección': print "corrección";
        'undo','deshacer': print "deshacer";
        'tomar','coger': print "tomar";
        'dejar','soltar': print "dejar";
        'abrir': print "abrir";
        'cerrar': print "cerrar";
        'ir','caminar': print "ir";
        'entrar': print "entrar";
        'salir': print "salir";
        'dar': print "dar";
        'decir','hablar': print "decir";
        'usar': print "usar";
        default: rfalse;
    }
    rtrue;
];

! ==============================================================================
! RUTINAS DE INICIALIZACIÓN
! ==============================================================================

[ SpanishVerbsInitialise;
    ! Marcar que el módulo de verbos está listo
    spanish_verbs_ready = true;
    MarkModuleLoaded('verbs');
    
    #Ifdef DEBUG;
    print "[SpanishVerbs v", (string) SPANISH_VERBS_VERSION, " inicializado]^";
    print "[Conjugaciones AR/ER/IR, detección de verbos, integración con irregulares]^";
    #Endif;
];

! ==============================================================================
! DEPURACIÓN DE VERBOS
! ==============================================================================

#Ifdef DEBUG;
[ SpanishDebugVerb word;
    print "^=== ANÁLISIS DE VERBO ===^";
    print "Palabra: ", (address) word, "^";
    
    if (LanguageIsVerb(word)) {
        print "Estado: ✅ Reconocido como verbo válido^";
        
        ! Intentar detectar tipo
        local tipo;
        tipo = DetectarTipoVerbo(word);
        switch(tipo) {
            1: print "Tipo: Verbo regular -AR^";
            2: print "Tipo: Verbo regular -ER^";
            3: print "Tipo: Verbo regular -IR^";
            0: print "Tipo: Irregular, reflexivo o especial^";
        }
        
        ! Mostrar características especiales
        if (RequiereCambioRaiz(word)) print "• Requiere cambio de raíz^";
        if (EsVerboReflexivo(word)) print "• Verbo reflexivo^";
        if (EsVerboImpersonal(word)) print "• Verbo impersonal^";
        
        ! Probar conjugación básica
        if (tipo > 0) {
            print "Conjugación (presente): ";
            ConjugarVerbo(word, 1, PRESENTE_T, tipo); print ", ";
            ConjugarVerbo(word, 2, PRESENTE_T, tipo); print ", ";
            ConjugarVerbo(word, 3, PRESENTE_T, tipo); print "^";
        }
        
    } else {
        print "Estado: ❌ No reconocido como verbo^";
        print "Sugerencia: Agregar a LanguageIsVerb() si es necesario^";
    }
];

[ TestConjugacionCompleta verbo;
    print "^=== CONJUGACIÓN COMPLETA DE ", (string) verbo, " ===^";
    
    local tipo;
    tipo = DetectarTipoVerbo(verbo);
    
    if (tipo == 0) {
        print "No se puede conjugar automáticamente (irregular o no reconocido)^";
        return;
    }
    
    print "Presente: ";
    ConjugarVerbo(verbo, 1, PRESENTE_T, tipo); print ", ";
    ConjugarVerbo(verbo, 2, PRESENTE_T, tipo); print ", ";
    ConjugarVerbo(verbo, 3, PRESENTE_T, tipo); print "^";
    
    print "Pretérito: ";
    ConjugarVerbo(verbo, 1, PRETERITO_T, tipo); print ", ";
    ConjugarVerbo(verbo, 2, PRETERITO_T, tipo); print ", ";
    ConjugarVerbo(verbo, 3, PRETERITO_T, tipo); print "^";
    
    print "Imperfecto: ";
    ConjugarVerbo(verbo, 1, IMPERFECTO_T, tipo); print ", ";
    ConjugarVerbo(verbo, 2, IMPERFECTO_T, tipo); print ", ";
    ConjugarVerbo(verbo, 3, IMPERFECTO_T, tipo); print "^";
    
    print "Futuro: ";
    ConjugarVerbo(verbo, 1, FUTURO_T, tipo); print ", ";
    ConjugarVerbo(verbo, 2, FUTURO_T, tipo); print ", ";
    ConjugarVerbo(verbo, 3, FUTURO_T, tipo); print "^";
];

[ SpanishVerbStats;
    print "^=== ESTADÍSTICAS DE VERBOS ===^";
    print "Verbos regulares: AR, ER, IR^";
    print "Tiempos implementados: 7 (presente, pretérito, imperfecto, futuro, condicional, subjuntivo, imperativo)^";
    print "Personas: 6 (yo, tú/usted, él/ella, nosotros, vosotros/ustedes, ellos/ellas)^";
    
    #Ifdef SPANISH_IRREGULAR_VERBS_INCLUDED;
        print "Verbos irregulares: ✅ Módulo cargado^";
    #Ifnot;
        print "Verbos irregulares: ❌ Módulo no cargado^";
    #Endif;
    
    #Ifdef SPANISH_REGIONAL_INCLUDED;
        print "Soporte regional: ✅ Voseo disponible^";
    #Ifnot;
        print "Soporte regional: ❌ Solo español estándar^";
    #Endif;
    
    print "Detección de verbos: ~200 verbos comunes reconocidos^";
    print "Integración: Parser, gramática, meta-comandos^";
];
#Endif;

! ==============================================================================
! CONSTANTES DE FINALIZACIÓN
! ==============================================================================

Constant SPANISH_VERBS_COMPLETE;
Constant SPANISH_VERBS_READY;

! Información del módulo
Constant SPANISH_VERBS_FEATURES = "Conjugaciones regulares, detección expandida, integración modular";

#Endif; ! SPANISH_VERBS_INCLUDED

! ==============================================================================
! Fin de SpanishVerbs.h - Sistema completo y limpio de verbos en español
! ==============================================================================