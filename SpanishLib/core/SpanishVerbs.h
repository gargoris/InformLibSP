! ==============================================================================
! SPANISHVERBS.H - Implementación de verbos y conjugaciones en español
! Parte del sistema modular Spanish Library para Inform 6
! Compatible con Inform 6.42 y librería estándar 6.12.7
! ==============================================================================

System_file;

#Ifndef SPANISH_VERBS_INCLUDED;
Constant SPANISH_VERBS_INCLUDED;

! Verificación de dependencias
#Ifndef SPANISH_CORE_INCLUDED;
  Message fatalerror "*** Include SpanishCore.h antes de SpanishVerbs.h ***";
#Endif;

! ==============================================================================
! CONSTANTES PARA TIEMPOS VERBALES
! ==============================================================================

Constant PRESENTE_T   = 1;
Constant PRETERITO_T  = 2;
Constant IMPERFECTO_T = 3;
Constant FUTURO_T     = 4;
Constant CONDICIONAL_T = 5;
Constant SUBJUNTIVO_T = 6;
Constant IMPERATIVO_T = 7;

! ==============================================================================
! SISTEMA DE CONJUGACIÓN DE VERBOS REGULARES
! ==============================================================================

! Conjugación de verbos terminados en -AR
[ ConjugarAR verbo persona tiempo;
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "tengo";
                2: print "tienes";
                3: print "tiene";
                4: print "tenemos";
                5: print "tenéis";
                6: print "tienen";
            }
        PRETERITO_T:
            switch(persona) {
                1: print "tuve";
                2: print "tuviste";
                3: print "tuvo";
                4: print "tuvimos";
                5: print "tuvisteis";
                6: print "tuvieron";
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print "tenía";
                2: print "tenías";
                3: print "tenía";
                4: print "teníamos";
                5: print "teníais";
                6: print "tenían";
            }
        FUTURO_T:
            switch(persona) {
                1: print "tendré";
                2: print "tendrás";
                3: print "tendrá";
                4: print "tendremos";
                5: print "tendréis";
                6: print "tendrán";
            }
        SUBJUNTIVO_T:
            switch(persona) {
                1: print "tenga";
                2: print "tengas";
                3: print "tenga";
                4: print "tengamos";
                5: print "tengáis";
                6: print "tengan";
            }
        IMPERATIVO_T:
            switch(persona) {
                2: print "ten";
                3: print "tenga";
                4: print "tengamos";
                5: print "tened";
                6: print "tengan";
            }
    }
];

! Conjugación del verbo HACER
[ ConjugarHacer persona tiempo;
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "hago";
                2: print "haces";
                3: print "hace";
                4: print "hacemos";
                5: print "hacéis";
                6: print "hacen";
            }
        PRETERITO_T:
            switch(persona) {
                1: print "hice";
                2: print "hiciste";
                3: print "hizo";
                4: print "hicimos";
                5: print "hicisteis";
                6: print "hicieron";
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print "hacía";
                2: print "hacías";
                3: print "hacía";
                4: print "hacíamos";
                5: print "hacíais";
                6: print "hacían";
            }
        FUTURO_T:
            switch(persona) {
                1: print "haré";
                2: print "harás";
                3: print "hará";
                4: print "haremos";
                5: print "haréis";
                6: print "harán";
            }
        SUBJUNTIVO_T:
            switch(persona) {
                1: print "haga";
                2: print "hagas";
                3: print "haga";
                4: print "hagamos";
                5: print "hagáis";
                6: print "hagan";
            }
        IMPERATIVO_T:
            switch(persona) {
                2: print "haz";
                3: print "haga";
                4: print "hagamos";
                5: print "haced";
                6: print "hagan";
            }
    }
];

#Endif; ! SPANISH_IRREGULAR_VERBS

! ==============================================================================
! DETECCIÓN Y CLASIFICACIÓN DE VERBOS
! ==============================================================================

[ LanguageIsVerb word;
    ! Verbos básicos de manipulación
    if (word == 'coger' or 'coja' or 'tomar' or 'tome' or 'agarrar' or 'agarre') rtrue;
    if (word == 'dejar' or 'deje' or 'soltar' or 'suelte' or 'abandonar' or 'abandone') rtrue;
    
    ! Verbos de observación
    if (word == 'mirar' or 'mire' or 'ver' or 'vea' or 'observar' or 'observe' or 'examinar' or 'examine') rtrue;
    
    ! Verbos de movimiento
    if (word == 'ir' or 'vaya' or 've' or 'caminar' or 'camine' or 'andar' or 'ande' or 'venir' or 'venga' or 'ven') rtrue;
    if (word == 'correr' or 'corra' or 'corre' or 'trotar' or 'trote' or 'trota') rtrue;
    if (word == 'saltar' or 'salte' or 'salta' or 'brincar' or 'brinque' or 'brinca') rtrue;
    if (word == 'nadar' or 'nade' or 'nada' or 'bucear' or 'bucee' or 'bucea') rtrue;
    if (word == 'volar' or 'vuele' or 'vuela' or 'flotar' or 'flote' or 'flota') rtrue;
    
    ! Verbos de interacción con objetos
    if (word == 'abrir' or 'abra' or 'abre' or 'cerrar' or 'cierre' or 'cierra') rtrue;
    if (word == 'encender' or 'encienda' or 'enciende' or 'apagar' or 'apague' or 'apaga') rtrue;
    if (word == 'poner' or 'ponga' or 'pon' or 'colocar' or 'coloque' or 'coloca' or 'meter' or 'meta' or 'mete') rtrue;
    if (word == 'quitar' or 'quite' or 'quita' or 'sacar' or 'saque' or 'saca' or 'remover' or 'remueva' or 'remueve') rtrue;
    if (word == 'romper' or 'rompa' or 'rompe' or 'quebrar' or 'quiebre' or 'quiebra' or 'destruir' or 'destruya' or 'destruye') rtrue;
    if (word == 'arreglar' or 'arregle' or 'arregla' or 'reparar' or 'repare' or 'repara' or 'componer' or 'componga' or 'compone') rtrue;
    
    ! Verbos de comunicación  
    if (word == 'dar' or 'dé' or 'da' or 'entregar' or 'entregue' or 'entrega' or 'ofrecer' or 'ofrezca' or 'ofrece') rtrue;
    if (word == 'decir' or 'diga' or 'di' or 'dice' or 'hablar' or 'hable' or 'habla' or 'contar' or 'cuente' or 'cuenta') rtrue;
    if (word == 'preguntar' or 'pregunte' or 'pregunta' or 'consultar' or 'consulte' or 'consulta') rtrue;
    if (word == 'gritar' or 'grite' or 'grita' or 'chillar' or 'chille' or 'chilla') rtrue;
    if (word == 'susurrar' or 'susurre' or 'susurra' or 'murmurar' or 'murmure' or 'murmura') rtrue;
    
    ! Verbos de los sentidos
    if (word == 'leer' or 'lea' or 'lee' or 'hojear' or 'hojee' or 'hojea') rtrue;
    if (word == 'escribir' or 'escriba' or 'escribe' or 'anotar' or 'anote' or 'anota') rtrue;
    if (word == 'tocar' or 'toque' or 'toca' or 'palpar' or 'palpe' or 'palpa' or 'sentir' or 'sienta' or 'siente') rtrue;
    if (word == 'oler' or 'huela' or 'huele' or 'olfatear' or 'olfatee' or 'olfatea') rtrue;
    if (word == 'escuchar' or 'escuche' or 'escucha' or 'oir' or 'oiga' or 'oye') rtrue;
    if (word == 'probar' or 'pruebe' or 'prueba' or 'degustar' or 'deguste' or 'degusta' or 'saborear' or 'saboree' or 'saborea') rtrue;
    
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
    if (word == 'recordar' or 'recuerde' or 'recuerda' or 'acordarse' or 'acuérdese' or 'acuérdate') rtrue;
    if (word == 'olvidar' or 'olvide' or 'olvida' or 'desatender' or 'desatienda' or 'desatiende') rtrue;
    
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
    
    ! Otros verbos útiles
    if (word == 'usar' or 'use' or 'usa' or 'utilizar' or 'utilice' or 'utiliza' or 'emplear' or 'emplee' or 'emplea') rtrue;
    if (word == 'activar' or 'active' or 'activa' or 'accionar' or 'accione' or 'acciona') rtrue;
    if (word == 'desactivar' or 'desactive' or 'desactiva' or 'detener' or 'detenga' or 'detén') rtrue;
    if (word == 'conectar' or 'conecte' or 'conecta' or 'enchufar' or 'enchufe' or 'enchufa') rtrue;
    if (word == 'desconectar' or 'desconecte' or 'desconecta' or 'desenchufar' or 'desenchufe' or 'desenchufa') rtrue;
    
    rfalse;
];

! ==============================================================================
! MANEJO INTELIGENTE DE CONJUGACIONES
! ==============================================================================

! Detectar el tipo de verbo según su terminación
[ DetectarTipoVerbo verbo;
    ! Esta función asume que 'verbo' es una string
    ! Devuelve: 1 = -AR, 2 = -ER, 3 = -IR, 0 = irregular o no reconocido
    
    if (verbo->0 < 2) return 0; ! Muy corto para ser verbo
    
    if (verbo->(verbo->0-1) == 'r') {
        if (verbo->(verbo->0-2) == 'a') return 1; ! -AR
        if (verbo->(verbo->0-2) == 'e') return 2; ! -ER
        if (verbo->(verbo->0-2) == 'i') return 3; ! -IR
    }
    
    return 0; ! No reconocido
];

! Conjugar cualquier verbo regular automáticamente
[ ConjugarVerbo verbo persona tiempo tipo;
    ! Si no se especifica tipo, detectarlo
    if (tipo == 0) tipo = DetectarTipoVerbo(verbo);
    
    switch(tipo) {
        1: ConjugarAR(verbo, persona, tiempo);
        2: ConjugarER(verbo, persona, tiempo);
        3: ConjugarIR(verbo, persona, tiempo);
        default:
            ! Intentar buscar en verbos irregulares
            #Ifdef SPANISH_IRREGULAR_VERBS;
                if (verbo == "ser") { ConjugarSer(persona, tiempo); rtrue; }
                if (verbo == "estar") { ConjugarEstar(persona, tiempo); rtrue; }
                if (verbo == "tener") { ConjugarTener(persona, tiempo); rtrue; }
                if (verbo == "hacer") { ConjugarHacer(persona, tiempo); rtrue; }
            #Endif;
            ! Si no es irregular conocido, imprimir infinitivo
            print (string) verbo;
    }
];

! ==============================================================================
! UTILIDADES DE VERBOS
! ==============================================================================

! Obtener la raíz de un verbo (sin -ar, -er, -ir)
[ ObtenerRaizVerbo verbo buffer   len;
    len = verbo->0;
    if (len < 3) return 0;
    
    ! Copiar todo excepto las últimas 2 letras
    for (len = 0: len < verbo->0 - 2: len++) {
        buffer->len = verbo->(len+1);
    }
    buffer->0 = len;
    
    return buffer;
];

! Verificar si un verbo requiere cambio de raíz
[ RequiereCambioRaiz verbo;
    ! e->ie: pensar, querer, cerrar, etc.
    if (verbo == "pensar" or "querer" or "cerrar" or "empezar" or "sentir") rtrue;
    
    ! o->ue: poder, dormir, volver, etc.
    if (verbo == "poder" or "dormir" or "volver" or "mover" or "contar") rtrue;
    
    ! e->i: pedir, servir, seguir, etc.
    if (verbo == "pedir" or "servir" or "seguir" or "repetir" or "vestir") rtrue;
    
    rfalse;
];

! ==============================================================================
! INFORMACIÓN DE VERBOS
! ==============================================================================

! Imprimir información sobre un verbo
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
        'g//','r//','again','repetir': print "repetir";
        'oops','ups','corrección': print "corrección";
        'undo','deshacer': print "deshacer";
        default: rfalse;
    }
    rtrue;
];

! ==============================================================================
! DEPURACIÓN DE VERBOS
! ==============================================================================

#Ifdef DEBUG;
[ SpanishDebugVerb word;
    print "Analizando verbo: ", (address) word, "^";
    if (LanguageIsVerb(word)) {
        print "Reconocido como verbo válido.^";
        
        ! Intentar detectar tipo
        if (word == 'mirar' or 'tomar' or 'dejar') print "Tipo: -AR^";
        else if (word == 'comer' or 'beber' or 'leer') print "Tipo: -ER^";
        else if (word == 'abrir' or 'vivir' or 'subir') print "Tipo: -IR^";
        else print "Tipo: Irregular o especial^";
    } else {
        print "No reconocido como verbo.^";
    }
];

[ TestConjugacion verbo;
    print "Conjugación de ", (string) verbo, ":^";
    print "Presente: ";
    ConjugarVerbo(verbo, 1, PRESENTE_T, 0); print ", ";
    ConjugarVerbo(verbo, 2, PRESENTE_T, 0); print ", ";
    ConjugarVerbo(verbo, 3, PRESENTE_T, 0); print "^";
    
    print "Pretérito: ";
    ConjugarVerbo(verbo, 1, PRETERITO_T, 0); print ", ";
    ConjugarVerbo(verbo, 2, PRETERITO_T, 0); print ", ";
    ConjugarVerbo(verbo, 3, PRETERITO_T, 0); print "^";
];
#Endif;

#Endif; ! SPANISH_VERBS_INCLUDED

! ==============================================================================
! Fin de SpanishVerbs.h - Sistema de verbos y conjugaciones en español
! ==============================================================================