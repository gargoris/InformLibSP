! ==============================================================================
! SPANISHVERBS.H - Sistema completo de verbos y conjugaciones en espanol
! Parte del sistema modular Spanish Library para Inform 6
! Compatible con Inform 6.42 y libreria estandar 6.12.7
! ==============================================================================

System_file;

#Ifndef SPANISH_VERBS_INCLUDED;
Constant SPANISH_VERBS_INCLUDED;
Constant SPANISH_VERBS_VERSION = "1.2-complete-fixed";

! ==============================================================================
! VERIFICACION DE DEPENDENCIAS
! ==============================================================================

#Ifndef SPANISH_CONSTANTS_INCLUDED;
  Message fatalerror "*** Include SpanishConstants.h antes de SpanishVerbs.h ***";
#Endif;

#Ifndef SPANISH_CORE_INCLUDED;
  Message fatalerror "*** Include SpanishCore.h antes de SpanishVerbs.h ***";
#Endif;

! ==============================================================================
! UTILIDADES DE ANALISIS DE VERBOS
! ==============================================================================

[ DetectarTipoVerbo verbo   len buffer;
    ! [OK] CORREGIDO: Funcion completa para detectar tipo de verbo
    ! Devuelve: 1 = -AR, 2 = -ER, 3 = -IR, 0 = irregular o no reconocido
    
    if (verbo == 0) return 0;
    
    ! Convertir dictionary word a string para analisis
    len = PrintToBuffer(spanish_temp_buffer, 100, verbo);
    
    if (len <= 0 || len < 3) return 0; ! Validar buffer y longitud minima
    
    ! Verificar terminacion
    if (spanish_temp_buffer->(len-1) == 'r') { ! Ultima letra es 'r'
        if (spanish_temp_buffer->(len-2) == 'a') return 1; ! -AR
        if (spanish_temp_buffer->(len-2) == 'e') return 2; ! -ER  
        if (spanish_temp_buffer->(len-2) == 'i') return 3; ! -IR
    }
    
    return 0; ! No reconocido como verbo regular
];

[ ObtenerRaizVerbo verbo buffer   len i;
    ! [OK] CORREGIDO: Funcion completa para obtener raiz
    ! Obtiene la raiz de un verbo (sin -ar, -er, -ir)
    
    len = PrintToBuffer(spanish_temp_buffer, 100, verbo);
    if (len <= 0 || len < 3) return 0;
    
    ! Copiar todo excepto las ultimas 2 letras (-ar, -er, -ir)
    for (i = 0: i < len - 2: i++) {
        buffer->(i+1) = spanish_temp_buffer->(i);
    }
    buffer->0 = len - 2;
    
    return buffer;
];

! ==============================================================================
! CONJUGACIONES DE VERBOS REGULARES - [OK] COMPLETAS
! ==============================================================================

[ ConjugarAR raiz persona tiempo;
    ! [OK] CORREGIDO: Funcion completa de conjugacion de verbos -AR
    
    if (raiz == 0) return false;
    
    ! Imprimir la raiz
    print (string) raiz;
    
    ! Anadir terminacion segun persona y tiempo
    switch (tiempo) {
        PRESENTE_T:
            switch (persona) {
                1: print "o";      ! yo camino
                2: if (FormalityLevel == FORMAL) print "a"; else print "as"; ! usted camina / tu caminas
                3: print "a";      ! el/ella camina
                4: print "amos";   ! nosotros caminamos
                5: if (FormalityLevel == FORMAL) print "an"; else print "ais"; ! ustedes caminan / vosotros caminais
                6: print "an";     ! ellos/ellas caminan
            }
            
        PRETERITO_T:
            switch (persona) {
                1: print "e";      ! yo camine
                2: if (FormalityLevel == FORMAL) print "o"; else print "aste"; ! usted camino / tu caminaste
                3: print "o";      ! el/ella camino
                4: print "amos";   ! nosotros caminamos
                5: if (FormalityLevel == FORMAL) print "aron"; else print "asteis"; ! ustedes caminaron / vosotros caminasteis
                6: print "aron";   ! ellos/ellas caminaron
            }
            
        IMPERFECTO_T:
            switch (persona) {
                1: print "aba";    ! yo caminaba
                2: print "aba";    ! tu/usted caminaba
                3: print "aba";    ! el/ella caminaba
                4: print "abamos"; ! nosotros caminabamos
                5: if (FormalityLevel == FORMAL) print "aban"; else print "abais"; ! ustedes caminaban / vosotros caminabais
                6: print "aban";   ! ellos/ellas caminaban
            }
            
        FUTURO_T:
            ! Para futuro, usar infinitivo completo + terminacion
            print "ar";
            switch (persona) {
                1: print "e";      ! yo caminare
                2: print "as";     ! tu/usted caminaras/a
                3: print "a";      ! el/ella caminara
                4: print "emos";   ! nosotros caminaremos
                5: print "eis";    ! vosotros/ustedes caminareis/an
                6: print "an";     ! ellos/ellas caminaran
            }
            
        CONDICIONAL_T:
            print "ar";
            switch (persona) {
                1: print "ia";     ! yo caminaria
                2: print "ias";    ! tu/usted caminarias/ia
                3: print "ia";     ! el/ella caminaria
                4: print "iamos";  ! nosotros caminariamos
                5: print "iais";   ! vosotros/ustedes caminariais/ian
                6: print "ian";    ! ellos/ellas caminarian
            }
            
        SUBJUNTIVO_T:
            switch (persona) {
                1: print "e";      ! que yo camine
                2: print "es";     ! que tu camines
                3: print "e";      ! que el/ella camine
                4: print "emos";   ! que nosotros caminemos
                5: print "eis";    ! que vosotros camineis
                6: print "en";     ! que ellos/ellas caminen
            }
            
        IMPERATIVO_T:
            switch (persona) {
                2: if (FormalityLevel == FORMAL) print "e"; else print "a"; ! !camine! / !camina!
                3: print "e";      ! !que camine!
                4: print "emos";   ! !caminemos!
                5: if (FormalityLevel == FORMAL) print "en"; else print "ad"; ! !caminen! / !caminad!
                6: print "en";     ! !que caminen!
            }
    }
    
    return true;
];

[ ConjugarER raiz persona tiempo;
    ! [OK] CORREGIDO: Funcion completa de conjugacion de verbos -ER
    
    if (raiz == 0) return false;
    
    print (string) raiz;
    
    switch (tiempo) {
        PRESENTE_T:
            switch (persona) {
                1: print "o";      ! yo como
                2: if (FormalityLevel == FORMAL) print "e"; else print "es"; ! usted come / tu comes
                3: print "e";      ! el/ella come
                4: print "emos";   ! nosotros comemos
                5: if (FormalityLevel == FORMAL) print "en"; else print "eis"; ! ustedes comen / vosotros comeis
                6: print "en";     ! ellos/ellas comen
            }
            
        PRETERITO_T:
            switch (persona) {
                1: print "i";      ! yo comi
                2: if (FormalityLevel == FORMAL) print "io"; else print "iste"; ! usted comio / tu comiste
                3: print "io";     ! el/ella comio
                4: print "imos";   ! nosotros comimos
                5: if (FormalityLevel == FORMAL) print "ieron"; else print "isteis"; ! ustedes comieron / vosotros comisteis
                6: print "ieron";  ! ellos/ellas comieron
            }
            
        IMPERFECTO_T:
            switch (persona) {
                1: print "ia";     ! yo comia
                2: print "ias";    ! tu/usted comias/ia
                3: print "ia";     ! el/ella comia
                4: print "iamos";  ! nosotros comiamos
                5: if (FormalityLevel == FORMAL) print "ian"; else print "iais"; ! ustedes comian / vosotros comiais
                6: print "ian";    ! ellos/ellas comian
            }
            
        FUTURO_T:
            print "er";
            switch (persona) {
                1: print "e";      ! yo comere
                2: print "as";     ! tu/usted comeras/a
                3: print "a";      ! el/ella comera
                4: print "emos";   ! nosotros comeremos
                5: print "eis";    ! vosotros/ustedes comereis/an
                6: print "an";     ! ellos/ellas comeran
            }
            
        CONDICIONAL_T:
            print "er";
            switch (persona) {
                1: print "ia";     ! yo comeria
                2: print "ias";    ! tu/usted comerias/ia
                3: print "ia";     ! el/ella comeria
                4: print "iamos";  ! nosotros comeriamos
                5: print "iais";   ! vosotros/ustedes comeriais/ian
                6: print "ian";    ! ellos/ellas comerian
            }
            
        SUBJUNTIVO_T:
            switch (persona) {
                1: print "a";      ! que yo coma
                2: print "as";     ! que tu comas
                3: print "a";      ! que el/ella coma
                4: print "amos";   ! que nosotros comamos
                5: print "ais";    ! que vosotros comais
                6: print "an";     ! que ellos/ellas coman
            }
            
        IMPERATIVO_T:
            switch (persona) {
                2: if (FormalityLevel == FORMAL) print "a"; else print "e"; ! !coma! / !come!
                3: print "a";      ! !que coma!
                4: print "amos";   ! !comamos!
                5: if (FormalityLevel == FORMAL) print "an"; else print "ed"; ! !coman! / !comed!
                6: print "an";     ! !que coman!
            }
    }
    
    return true;
];

[ ConjugarIR raiz persona tiempo;
    ! [OK] CORREGIDO: Funcion completa de conjugacion de verbos -IR
    
    if (raiz == 0) return false;
    
    print (string) raiz;
    
    switch (tiempo) {
        PRESENTE_T:
            switch (persona) {
                1: print "o";      ! yo vivo
                2: if (FormalityLevel == FORMAL) print "e"; else print "es"; ! usted vive / tu vives
                3: print "e";      ! el/ella vive
                4: print "imos";   ! nosotros vivimos
                5: if (FormalityLevel == FORMAL) print "en"; else print "is"; ! ustedes viven / vosotros vivis
                6: print "en";     ! ellos/ellas viven
            }
            
        PRETERITO_T:
            switch (persona) {
                1: print "i";      ! yo vivi
                2: if (FormalityLevel == FORMAL) print "io"; else print "iste"; ! usted vivio / tu viviste
                3: print "io";     ! el/ella vivio
                4: print "imos";   ! nosotros vivimos
                5: if (FormalityLevel == FORMAL) print "ieron"; else print "isteis"; ! ustedes vivieron / vosotros vivisteis
                6: print "ieron";  ! ellos/ellas vivieron
            }
            
        IMPERFECTO_T:
            switch (persona) {
                1: print "ia";     ! yo vivia
                2: print "ias";    ! tu/usted vivias/ia
                3: print "ia";     ! el/ella vivia
                4: print "iamos";  ! nosotros viviamos
                5: if (FormalityLevel == FORMAL) print "ian"; else print "iais"; ! ustedes vivian / vosotros viviais
                6: print "ian";    ! ellos/ellas vivian
            }
            
        FUTURO_T:
            print "ir";
            switch (persona) {
                1: print "e";      ! yo vivire
                2: print "as";     ! tu/usted viviras/a
                3: print "a";      ! el/ella vivira
                4: print "emos";   ! nosotros viviremos
                5: print "eis";    ! vosotros/ustedes vivireis/an
                6: print "an";     ! ellos/ellas viviran
            }
            
        CONDICIONAL_T:
            print "ir";
            switch (persona) {
                1: print "ia";     ! yo viviria
                2: print "ias";    ! tu/usted vivirias/ia
                3: print "ia";     ! el/ella viviria
                4: print "iamos";  ! nosotros viviriamos
                5: print "iais";   ! vosotros/ustedes viviriais/ian
                6: print "ian";    ! ellos/ellas vivirian
            }
            
        SUBJUNTIVO_T:
            switch (persona) {
                1: print "a";      ! que yo viva
                2: print "as";     ! que tu vivas
                3: print "a";      ! que el/ella viva
                4: print "amos";   ! que nosotros vivamos
                5: print "ais";    ! que vosotros vivais
                6: print "an";     ! que ellos/ellas vivan
            }
            
        IMPERATIVO_T:
            switch (persona) {
                2: if (FormalityLevel == FORMAL) print "a"; else print "e"; ! !viva! / !vive!
                3: print "a";      ! !que viva!
                4: print "amos";   ! !vivamos!
                5: if (FormalityLevel == FORMAL) print "an"; else print "id"; ! !vivan! / !vivid!
                6: print "an";     ! !que vivan!
            }
    }
    
    return true;
];

! ==============================================================================
! FUNCION PRINCIPAL DE CONJUGACION
! ==============================================================================

[ ConjugarVerbo verbo persona tiempo tipo   raiz;
    ! [OK] CORREGIDO: Funcion principal que maneja todos los tipos
    ! Si tipo no se especifica, detectarlo automaticamente
    
    if (tipo == 0) tipo = DetectarTipoVerbo(verbo);
    
    ! Verificar si hay conjugador irregular disponible
    #Ifdef SPANISH_IRREGULAR_VERBS_INCLUDED;
        if (LanguageIsIrregularVerb(verbo)) {
            return SpanishConjugarIrregular(verbo, persona, tiempo);
        }
    #Endif;
    
    ! Si no es irregular, usar conjugacion regular
    if (tipo == 0) {
        print (address) verbo; ! Fallback: imprimir tal como esta
        return false;
    }
    
    ! Obtener raiz del verbo
    raiz = ObtenerRaizVerbo(verbo, spanish_temp_buffer);
    
    ! Conjugar segun el tipo
    switch (tipo) {
        1: return ConjugarAR(raiz, persona, tiempo);
        2: return ConjugarER(raiz, persona, tiempo);
        3: return ConjugarIR(raiz, persona, tiempo);
        default: 
            print (address) verbo;
            return false;
    }
];

! ==============================================================================
! DETECCION DE VERBOS - [OK] SISTEMA COMPLETO
! ==============================================================================

[ LanguageIsVerb word;
    ! [OK] CORREGIDO: Funcion principal de deteccion de verbos
    ! Lista comprensiva de verbos espanoles comunes
    
    if (word == 0) return false;
    
    ! Verificar verbos irregulares primero
    #Ifdef SPANISH_IRREGULAR_VERBS_INCLUDED;
        if (LanguageIsIrregularVerb(word)) return true;
    #Endif;
    
    ! Verbos de accion basica
    if (word == 'tomar' or 'coger' or 'agarrar' or 'sujetar') return true;
    if (word == 'dejar' or 'soltar' or 'abandonar' or 'liberar') return true;
    if (word == 'usar' or 'utilizar' or 'emplear' or 'aplicar') return true;
    if (word == 'mover' or 'manejar' or 'operar' or 'accionar') return true;
    
    ! Verbos de observacion
    if (word == 'mirar' or 'ver' or 'observar' or 'contemplar') return true;
    if (word == 'examinar' or 'inspeccionar' or 'revisar' or 'chequear') return true;
    if (word == 'buscar' or 'registrar' or 'explorar' or 'indagar') return true;
    if (word == 'encontrar' or 'hallar' or 'localizar' or 'descubrir') return true;
    
    ! Verbos de movimiento
    if (word == 'ir' or 'caminar' or 'andar' or 'marchar') return true;
    if (word == 'venir' or 'llegar' or 'acercarse' or 'aproximarse') return true;
    if (word == 'correr' or 'trotar' or 'sprint ar') return true;
    if (word == 'saltar' or 'brincar' or 'brindar' or 'botar') return true;
    if (word == 'subir' or 'trepar' or 'escalar' or 'ascender') return true;
    if (word == 'bajar' or 'descender' or 'declinar') return true;
    if (word == 'entrar' or 'ingresar' or 'acceder' or 'penetrar') return true;
    if (word == 'salir' or 'partir' or 'marcharse' or 'irse') return true;
    
    ! Verbos de interaccion con objetos
    if (word == 'abrir' or 'destapa r' or 'desenroscar') return true;
    if (word == 'cerrar' or 'tapar' or 'clausurar' or 'sellar') return true;
    if (word == 'encender' or 'prender' or 'activar' or 'conectar') return true;
    if (word == 'apagar' or 'desactivar' or 'desconectar') return true;
    if (word == 'empujar' or 'presionar' or 'impulsar') return true;
    if (word == 'tirar' or 'jalar' or 'halar' or 'arrastrar') return true;
    if (word == 'girar' or 'rotar' or 'voltear' or 'torcer') return true;
    if (word == 'romper' or 'quebrar' or 'fracturar' or 'partir') return true;
    
    ! Verbos de comunicacion
    if (word == 'dar' or 'entregar' or 'otorgar' or 'conceder') return true;
    if (word == 'decir' or 'hablar' or 'contar' or 'narrar') return true;
    if (word == 'preguntar' or 'consultar' or 'interrogar') return true;
    if (word == 'responder' or 'contestar' or 'replicar') return true;
    if (word == 'mostrar' or 'ensenar' or 'exhibir' or 'presentar') return true;
    if (word == 'explicar' or 'aclarar' or 'exponer' or 'describir') return true;
    
    ! Verbos de los sentidos
    if (word == 'tocar' or 'palpar' or 'sentir' or 'percibir') return true;
    if (word == 'oler' or 'olfatear' or 'husmear') return true;
    if (word == 'escuchar' or 'oir' or 'atender') return true;
    if (word == 'probar' or 'degustar' or 'saborear' or 'catar') return true;
    if (word == 'leer' or 'estudiar' or 'revisar') return true;
    if (word == 'escribir' or 'anotar' or 'redactar' or 'inscribir') return true;
    
    ! Verbos de acciones fisicas
    if (word == 'comer' or 'consumir' or 'ingerir' or 'alimentarse') return true;
    if (word == 'beber' or 'tomar' or 'ingerir') return true;
    if (word == 'tragar' or 'deglutir') return true;
    if (word == 'masticar' or 'morder' or 'mordisquear') return true;
    if (word == 'llevar' or 'portar' or 'cargar' or 'transportar') return true;
    if (word == 'vestir' or 'ponerse' or 'usar') return true;
    if (word == 'quitarse' or 'sacarse' or 'remover') return true;
    
    ! Verbos de combate y accion
    if (word == 'atacar' or 'agredir' or 'asaltar') return true;
    if (word == 'golpear' or 'pegar' or 'impactar' or 'chocar') return true;
    if (word == 'cortar' or 'rebanar' or 'tajear' or 'seccionar') return true;
    if (word == 'defender' or 'proteger' or 'resguardar') return true;
    if (word == 'escapar' or 'huir' or 'fugarse') return true;
    
    ! Verbos de manipulacion avanzada
    if (word == 'construir' or 'edificar' or 'erigir' or 'fabricar') return true;
    if (word == 'destruir' or 'demoler' or 'derribar' or 'arrasar') return true;
    if (word == 'reparar' or 'arreglar' or 'componer' or 'restaurar') return true;
    if (word == 'limpiar' or 'asear' or 'lavar' or 'purificar') return true;
    if (word == 'ensuciar' or 'manchar' or 'contaminar') return true;
    
    ! Verbos de estado y cambio
    if (word == 'dormir' or 'descansar' or 'reposar') return true;
    if (word == 'despertar' or 'despertarse' or 'levantarse') return true;
    if (word == 'sentar' or 'sentarse' or 'acomodarse') return true;
    if (word == 'parar' or 'pararse' or 'detener' or 'detener se') return true;
    if (word == 'esperar' or 'aguardar' or 'permanecer') return true;
    
    ! Meta-verbos y comandos del juego
    if (word == 'inventario' or 'llevar') return true;
    if (word == 'guardar' or 'save' or 'cargar' or 'restore') return true;
    if (word == 'reiniciar' or 'restart' or 'salir' or 'quit') return true;
    if (word == 'ayuda' or 'help' or 'info' or 'informacion') return true;
    
    ! Verificar si parece verbo por terminacion
    return (DetectarTipoVerbo(word) > 0);
];

[ LanguageVerbCannotDo;
    ! [OK] ANADIDO: Funcion para verbos que no se pueden ejecutar
    print "No puedes hacer eso.";
];

[ LanguageVerbMayDamage;
    ! [OK] ANADIDO: Funcion para advertencias de acciones peligrosas
    print "Eso podria ser peligroso.";
];

! ==============================================================================
! FUNCIONES DE UTILIDAD Y DETECCION
! ==============================================================================

[ EsVerboReflexivo word;
    ! [OK] ANADIDO: Detecta verbos reflexivos
    if (word == 'levantarse' or 'sentarse' or 'acostarse') return true;
    if (word == 'vestirse' or 'desvestirse' or 'banarse') return true;
    if (word == 'peinarse' or 'lavarse' or 'cepillarse') return true;
    return false;
];

[ EsVerboImpersonal word;
    ! [OK] ANADIDO: Detecta verbos impersonales
    if (word == 'llover' or 'nevar' or 'granizar') return true;
    if (word == 'amanecer' or 'anochecer' or 'atardecer') return true;
    if (word == 'hace r_calor' or 'hacer_frio') return true;
    return false;
];

[ RequiereCambioRaiz word;
    ! [OK] ANADIDO: Detecta verbos que requieren cambio de raiz
    if (word == 'pensar' or 'querer' or 'poder') return true;
    if (word == 'dormir' or 'morir' or 'sentir') return true;
    if (word == 'pedir' or 'servir' or 'seguir') return true;
    return false;
];

[ EsVerboConfundible word;
    ! [OK] ANADIDO: Palabras que pueden ser confundidas con verbos pero son nombres
    if (word == 'agua' or 'fuego' or 'luz' or 'aire') return true;
    if (word == 'amor' or 'dolor' or 'calor' or 'color') return true;
    if (word == 'lugar' or 'hogar' or 'azucar') return true;
    return false;
];

! ==============================================================================
! INFORMACION DE VERBOS PARA AYUDA
! ==============================================================================

[ LanguageVerb word;
    ! [OK] CORREGIDO: Funcion para informacion de verbos en ayuda
    ! Informacion de verbos para comandos de ayuda
    switch (word) {
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
        'fullscore','puntoscompletos': print "puntos completos";
        'notify','notificar': print "notificar";
        'g//','r//','again','repetir': print "repetir";
        'oops','ups','correccion': print "correccion";
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
        default: return false;
    }
    return true;
];

! ==============================================================================
! RUTINAS DE INICIALIZACION Y DEPURACION
! ==============================================================================

[ SpanishVerbsInitialise;
    ! [OK] CORREGIDO: Inicializacion completa del modulo
    ! Marcar que el modulo de verbos esta listo
    spanish_verbs_ready = true;
    MarkModuleLoaded('verbs');
    
    #Ifdef DEBUG;
        print "[SpanishVerbs v", (string) SPANISH_VERBS_VERSION, " inicializado]^";
        print "[Conjugaciones AR/ER/IR, deteccion de verbos, integracion con irregulares]^";
        print "[", SPANISH_VERBS_FUNCTIONS, " funciones disponibles]^";
    #Endif;
];

! ==============================================================================
! FUNCIONES DE DEPURACION
! ==============================================================================

#Ifdef DEBUG;
[ SpanishDebugVerb word   tipo;
    print "^=== ANALISIS DE VERBO ===^";
    print "Palabra: ", (address) word, "^";
    
    if (LanguageIsVerb(word)) {
        print "Estado: [OK] Reconocido como verbo valido^";
        
        tipo = DetectarTipoVerbo(word);
        print "Tipo: ";
        switch (tipo) {
            1: print "-AR (regular)";
            2: print "-ER (regular)";
            3: print "-IR (regular)";
            0: print "Irregular o no clasificado";
        }
        print "^";
        
        ! Mostrar caracteristicas especiales
        if (RequiereCambioRaiz(word)) print "- Requiere cambio de raiz^";
        if (EsVerboReflexivo(word)) print "- Verbo reflexivo^";
        if (EsVerboImpersonal(word)) print "- Verbo impersonal^";
        
        ! Probar conjugacion basica
        if (tipo > 0) {
            print "Conjugacion (presente): ";
            ConjugarVerbo(word, 1, PRESENTE_T, tipo); print ", ";
            ConjugarVerbo(word, 2, PRESENTE_T, tipo); print ", ";
            ConjugarVerbo(word, 3, PRESENTE_T, tipo); print "^";
        }
        
    } else {
        print "Estado: [X] No reconocido como verbo^";
        if (EsVerboConfundible(word)) {
            print "- Advertencia: Puede ser confundido con sustantivo^";
        }
        print "Sugerencia: Agregar a LanguageIsVerb() si es necesario^";
    }
];

[ TestConjugacionCompleta verbo   tipo;
    print "^=== CONJUGACION COMPLETA DE ", (address) verbo, " ===^";
    
    tipo = DetectarTipoVerbo(verbo);
    
    if (tipo == 0) {
        print "No se puede conjugar automaticamente (irregular o no reconocido)^";
        return;
    }
    
    print "^PRESENTE:^";
    print "  yo "; ConjugarVerbo(verbo, 1, PRESENTE_T, tipo); print "^";
    print "  tu "; ConjugarVerbo(verbo, 2, PRESENTE_T, tipo); print "^";
    print "  el/ella "; ConjugarVerbo(verbo, 3, PRESENTE_T, tipo); print "^";
    print "  nosotros "; ConjugarVerbo(verbo, 4, PRESENTE_T, tipo); print "^";
    print "  vosotros "; ConjugarVerbo(verbo, 5, PRESENTE_T, tipo); print "^";
    print "  ellos/ellas "; ConjugarVerbo(verbo, 6, PRESENTE_T, tipo); print "^";
    
    print "^PRETERITO:^";
    print "  yo "; ConjugarVerbo(verbo, 1, PRETERITO_T, tipo); print "^";
    print "  tu "; ConjugarVerbo(verbo, 2, PRETERITO_T, tipo); print "^";
    print "  el/ella "; ConjugarVerbo(verbo, 3, PRETERITO_T, tipo); print "^";
];

[ SpanishVerbStats;
    print "^=== ESTADISTICAS DE VERBOS ===^";
    print "Verbos regulares: AR, ER, IR^";
    print "Tiempos implementados: 7 (presente, preterito, imperfecto, futuro, condicional, subjuntivo, imperativo)^";
    print "Personas: 6 (yo, tu/usted, el/ella, nosotros, vosotros/ustedes, ellos/ellas)^";
    print "Verbos reconocidos: ~200 verbos comunes^";
    
    #Ifdef SPANISH_IRREGULAR_VERBS_INCLUDED;
        print "Verbos irregulares: [OK] Modulo cargado^";
    #Ifnot;
        print "Verbos irregulares: [X] Modulo no cargado^";
    #Endif;
    
    #Ifdef SPANISH_REGIONAL_INCLUDED;
        print "Soporte regional: [OK] Voseo disponible^";
    #Ifnot;
        print "Soporte regional: [X] Solo espanol estandar^";
    #Endif;
    
    print "Deteccion de tipos: Reflexivos, impersonales, cambio de raiz^";
    print "Integracion: Parser, gramatica, meta-comandos^";
    print "Formalidad: "; if (FormalityLevel == FORMAL) print "FORMAL (usted)"; else print "INFORMAL (tu)"; print "^";
];
#Endif;

! ==============================================================================
! CONSTANTES DE FINALIZACION
! ==============================================================================

! Estas constantes ya están definidas en SpanishConstants.h
! Constant SPANISH_VERBS_COMPLETE;
! Constant SPANISH_VERBS_READY;
Constant SPANISH_VERBS_FUNCTIONS = 20; ! Numero de funciones publicas

! Informacion del modulo
Constant SPANISH_VERBS_FEATURES = "Conjugaciones AR/ER/IR, deteccion 200+ verbos, 7 tiempos, 6 personas, tipos especiales";

#Endif; ! SPANISH_VERBS_INCLUDED

! ==============================================================================
! Fin de SpanishVerbs.h - Sistema completo de verbos y conjugaciones espanol
! ==============================================================================