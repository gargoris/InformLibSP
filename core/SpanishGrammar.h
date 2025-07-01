! ==============================================================================
! SPANISHGRAMMAR.H - Sistema de gramatica espanola para Inform 6
! Sistema modular Spanish Library para Inform 6
! Compatible con Inform 6.42 y libreria estandar 6.12.7
! ==============================================================================

System_file;

#Ifndef SPANISH_GRAMMAR_INCLUDED;
Constant SPANISH_GRAMMAR_INCLUDED;
Constant SPANISH_GRAMMAR_VERSION = "1.2-complete-fixed";

! ==============================================================================
! VERIFICACION DE DEPENDENCIAS
! ==============================================================================

#Ifndef SPANISH_CONSTANTS_INCLUDED;
  Message fatalerror "*** Include SpanishConstants.h antes de SpanishGrammar.h ***";
#Endif;

#Ifdef LIBRARY_STAGE;
#Iffalse LIBRARY_STAGE >= AFTER_PARSER;
  Message fatalerror "*** Include Parser.h y VerbLib.h antes de SpanishGrammar.h ***";
#Endif;
#Endif;

! ==============================================================================
! FUNCIONES BASICAS DE GENERO Y NUMERO
! ==============================================================================

[ EsGeneroMasculino obj;
    ! [OK] CORREGIDO: Funcion critica que faltaba completamente
    ! Determina si un objeto es de genero masculino
    
    if (obj == nothing) return true; ! Por defecto masculino
    if (obj == player) return ~~(player has female); ! Depende del jugador
    
    ! Verificar atributo explicito
    if (obj has male) return true;
    if (obj has female) return false;
    
    ! Heuristica por terminacion del nombre (si esta disponible)
    if (obj provides name && obj.name ~= 0) {
        ! Por ahora, masculino por defecto
        ! Se puede expandir con analisis de terminaciones
        return true;
    }
    
    return true; ! Por defecto masculino
];

[ EsGeneroFemenino obj;
    ! [OK] ANADIDO: Funcion complementaria
    return ~~EsGeneroMasculino(obj);
];

[ EsPlural obj;
    ! Determina si un objeto es plural
    if (obj == nothing) return false;
    if (obj has pluralname) return true;
    if (obj has multitude) return true;
    return false;
];

[ EsAnimado obj;
    ! Determina si un objeto es animado
    if (obj == nothing) return false;
    if (obj == player) return true;
    if (obj has animate) return true;
    return false;
];

! ==============================================================================
! FUNCIONES DE IMPRESION DE NOMBRES - [OK] CONSOLIDADAS AQUI
! ==============================================================================

[ LanguagePrintShortName obj   aux;
    ! [OK] CORREGIDO: Funcion estandar de impresion de nombres sin recursion
    if (obj == 0) { print "(nada)"; rtrue; }
    if (obj == player) { print "tu"; rtrue; }
    
    ! Intentar usar short_name si esta disponible
    if (obj provides short_name && obj.short_name ~= 0) {
        if (metaclass(obj.short_name) == String) {
            print (string) obj.short_name;
            rtrue;
        }
        if (metaclass(obj.short_name) == Routine) {
            if (obj.short_name()) rtrue;
        }
    }
    
    ! Usar name property como fallback
    aux = obj.&name;
    if (aux ~= 0 && aux-->0 ~= 0) {
        print (address) aux-->0;
        rtrue;
    }
    
    ! Fallback final
    print "objeto";
    rtrue;
];

[ LanguagePrintName obj;
    ! [OK] ANADIDO: Funcion estandar de impresion de nombres largos
    if (obj == 0) { print "(nada)"; rtrue; }
    
    ! Usar LanguagePrintShortName como base
    return LanguagePrintShortName(obj);
];

[ PrintName obj;
    ! Alias para compatibilidad
    return LanguagePrintShortName(obj);
];

! ==============================================================================
! ARTICULOS Y DETERMINANTES - [OK] COMPLETOS
! ==============================================================================

[ ArticuloDefinido obj;
    ! Imprime articulo definido segun genero y numero
    if (EsPlural(obj)) {
        if (EsGeneroMasculino(obj)) print "los";
        else print "las";
    }
    else {
        if (EsGeneroMasculino(obj)) print "el";
        else print "la";
    }
];

[ ArticuloIndefinido obj;
    ! Imprime articulo indefinido segun genero y numero
    if (EsPlural(obj)) {
        if (EsGeneroMasculino(obj)) print "unos";
        else print "unas";
    }
    else {
        if (EsGeneroMasculino(obj)) print "un";
        else print "una";
    }
];

[ ArticuloDemostrativo obj distancia;
    ! distancia: 1=este/esta, 2=ese/esa, 3=aquel/aquella
    if (distancia == 0) distancia = 2; ! Por defecto "ese/esa"
    
    if (EsPlural(obj)) {
        switch(distancia) {
            1: if (EsGeneroMasculino(obj)) print "estos"; else print "estas";
            2: if (EsGeneroMasculino(obj)) print "esos"; else print "esas";
            3: if (EsGeneroMasculino(obj)) print "aquellos"; else print "aquellas";
        }
    }
    else {
        switch(distancia) {
            1: if (EsGeneroMasculino(obj)) print "este"; else print "esta";
            2: if (EsGeneroMasculino(obj)) print "ese"; else print "esa";
            3: if (EsGeneroMasculino(obj)) print "aquel"; else print "aquella";
        }
    }
];

[ ArticuloPosesivo persona obj;
    ! persona: 1=mi/mis, 2=tu/tus, 3=su/sus, etc.
    switch(persona) {
        1: if (EsPlural(obj)) print "mis"; else print "mi";
        2: if (EsPlural(obj)) print "tus"; else print "tu";
        3: if (EsPlural(obj)) print "sus"; else print "su";
        4: ! Nuestro/nuestra/nuestros/nuestras
           if (EsPlural(obj)) {
               if (EsGeneroMasculino(obj)) print "nuestros"; else print "nuestras";
           } else {
               if (EsGeneroMasculino(obj)) print "nuestro"; else print "nuestra";
           }
        5: ! Vuestro/vuestra/vuestros/vuestras
           if (EsPlural(obj)) {
               if (EsGeneroMasculino(obj)) print "vuestros"; else print "vuestras";
           } else {
               if (EsGeneroMasculino(obj)) print "vuestro"; else print "vuestra";
           }
        6: if (EsPlural(obj)) print "sus"; else print "su";
    }
];

! ==============================================================================
! CONTRACCIONES Y COMBINACIONES
! ==============================================================================

#Ifndef LanguageContraction;
[ LanguageContraction prep article;
    ! Manejo automatico de contracciones espanolas
    if (prep == 'de' && article == 'el') {
        print "del";
        return true;
    }
    if (prep == 'a' && article == 'el') {
        print "al";
        return true;
    }
    return false;
];
#Endif;

[ ImprimirPreposicionArticulo prep obj;
    ! Imprime preposicion + articulo con contracciones automaticas
    if (prep == 'de' && EsGeneroMasculino(obj) && ~~EsPlural(obj)) {
        print "del";
    }
    else if (prep == 'a' && EsGeneroMasculino(obj) && ~~EsPlural(obj)) {
        print "al";
    }
    else {
        print (address) prep, " ";
        ArticuloDefinido(obj);
    }
];

! ==============================================================================
! CONCORDANCIA DE ADJETIVOS
! ==============================================================================

[ ConcordarAdjetivo adj obj tipo   adj_str len last_char;
    ! [OK] CORREGIDO: Funcion completa de concordancia de adjetivos
    ! tipo: 0 = normal, 1 = invariable en genero, 2 = invariable total
    
    if (tipo == 2) {
        print (address) adj;
        return;
    }
    
    ! Convertir a string para analisis
    len = PrintToBuffer(spanish_temp_buffer, 100, adj);
    
    if (tipo == 1) {
        ! Adjetivos como "grande", "feliz", etc. - solo pluralizan
        print (address) adj;
        if (EsPlural(obj)) {
            last_char = spanish_temp_buffer->(len-1);
            if (last_char == 'z') print "ces"; ! feliz -> felices
            else print "s";
        }
        return;
    }
    
    ! Adjetivos normales - concordancia completa
    print (address) adj;
    
    last_char = spanish_temp_buffer->(len-1);
    
    ! Ajustar terminacion segun genero (solo si termina en -o y es femenino)
    if (last_char == 'o' && ~~EsGeneroMasculino(obj)) {
        print "a";
        last_char = 'a'; ! Actualizar para plural
    }
    
    ! Anadir plural si es necesario
    if (EsPlural(obj)) {
        if (last_char == 'z') {
            print "ces"; ! feliz -> felices
        } else {
            print "s";
        }
    }
];

! ==============================================================================
! PRONOMBRES - [OK] SISTEMA COMPLETO
! ==============================================================================

[ PronombrePersonal persona genero numero caso;
    ! [OK] CORREGIDO: Funcion completa de pronombres
    ! caso: 1=nominativo, 2=acusativo, 3=dativo
    ! genero y numero solo relevantes para 3a persona
    
    switch(persona) {
        1: switch(caso) {
               1: print "yo";
               2: print "me";
               3: print "me";
           }
        2: switch(caso) {
               1: if (FormalityLevel == FORMAL) print "usted"; else print "tu";
               2: if (FormalityLevel == FORMAL) print "le"; else print "te";
               3: if (FormalityLevel == FORMAL) print "le"; else print "te";
           }
        3: switch(caso) {
               1: if (numero == PLURAL) {
                      if (genero == FEMININE) print "ellas"; else print "ellos";
                  } else {
                      if (genero == FEMININE) print "ella"; else print "el";
                  }
               2: if (numero == PLURAL) {
                      if (genero == FEMININE) print "las"; else print "los";
                  } else {
                      if (genero == FEMININE) print "la"; else print "lo";
                  }
               3: if (numero == PLURAL) print "les"; else print "le";
           }
        4: switch(caso) {
               1: print "nosotros";
               2: print "nos";
               3: print "nos";
           }
        5: switch(caso) {
               1: if (FormalityLevel == FORMAL) print "ustedes"; else print "vosotros";
               2: if (FormalityLevel == FORMAL) print "les"; else print "os";
               3: if (FormalityLevel == FORMAL) print "les"; else print "os";
           }
        6: switch(caso) {
               1: if (genero == FEMININE) print "ellas"; else print "ellos";
               2: if (genero == FEMININE) print "las"; else print "los";
               3: print "les";
           }
    }
];

[ PronombreDemostrativo obj distancia;
    ! distancia: 1=esto/este, 2=eso/ese, 3=aquello/aquel
    if (distancia == 0) distancia = 2;
    
    if (EsAnimado(obj)) {
        ! Para personas, usar formas especificas
        ArticuloDemostrativo(obj, distancia);
    } else {
        ! Para cosas, usar formas neutras o concordadas
        if (EsPlural(obj)) {
            ArticuloDemostrativo(obj, distancia);
        } else {
            switch(distancia) {
                1: print "esto";
                2: print "eso";
                3: print "aquello";
            }
        }
    }
];

! ==============================================================================
! FUNCIONES DE IMPRESION CON ARTICULOS - [OK] INTEGRADAS
! ==============================================================================

[ LanguageA obj;
    ! Imprime articulo indefinido + objeto
    if (obj == nothing) { print "nada"; rtrue; }
    if (obj == player) { print "tu mismo"; rtrue; }
    
    ArticuloIndefinido(obj);
    print " ";
    LanguagePrintShortName(obj);
    rtrue;
];

[ LanguageThe obj;
    ! Imprime articulo definido + objeto
    if (obj == nothing) { print "nada"; rtrue; }
    if (obj == player) { print "tu"; rtrue; }
    
    ArticuloDefinido(obj);
    print " ";
    LanguagePrintShortName(obj);
    rtrue;
];

#Ifndef A;
[ A obj; return LanguageA(obj); ];
#Endif;
#Ifndef The;
[ The obj; return LanguageThe(obj); ];
#Endif;

! Compatibilidad con sintaxis estandar
#Ifndef a;
[ a obj; return LanguageA(obj); ];
#Endif;
#Ifndef the;
[ the obj; return LanguageThe(obj); ];
#Endif;

! ==============================================================================
! UTILIDADES DE IMPRESION CON CONCORDANCIA
! ==============================================================================

[ LanguageIsOrAre obj;
    if (obj has pluralname or multitude) print "son";
    else print "es";
];

[ LanguageTheyreOrThats obj;
    if (obj == player) { print "estas"; return; }
    if (obj has pluralname or multitude) print "estan";
    else print "esta";
];

#Ifndef LanguageAnimateGender;
[ LanguageAnimateGender person;
    ! Funcion para determinar genero de personas
    if (person has female) return FEMININE;
    if (person has male) return MASCULINE;
    return MASCULINE; ! Por defecto masculino
];
#Endif;

[ LanguageGenderNumber obj;
    ! Funcion que devuelve codigo de genero y numero
    ! 1 = masculino singular, 2 = femenino singular
    ! 3 = masculino plural, 4 = femenino plural
    if (EsPlural(obj)) {
        if (EsGeneroFemenino(obj)) return 4;
        return 3;
    } else {
        if (EsGeneroFemenino(obj)) return 2;
        return 1;
    }
];

! ==============================================================================
! NUMEROS Y CANTIDADES - [OK] IMPLEMENTADO
! ==============================================================================

[ EscribirNumero n;
    ! [OK] ANADIDO: Funcion para escribir numeros en espanol
    if (n == 0) { print "cero"; return; }
    if (n == 1) { print "uno"; return; }
    if (n == 2) { print "dos"; return; }
    if (n == 3) { print "tres"; return; }
    if (n == 4) { print "cuatro"; return; }
    if (n == 5) { print "cinco"; return; }
    if (n == 6) { print "seis"; return; }
    if (n == 7) { print "siete"; return; }
    if (n == 8) { print "ocho"; return; }
    if (n == 9) { print "nueve"; return; }
    if (n == 10) { print "diez"; return; }
    if (n == 11) { print "once"; return; }
    if (n == 12) { print "doce"; return; }
    if (n == 13) { print "trece"; return; }
    if (n == 14) { print "catorce"; return; }
    if (n == 15) { print "quince"; return; }
    if (n == 16) { print "dieciseis"; return; }
    if (n == 17) { print "diecisiete"; return; }
    if (n == 18) { print "dieciocho"; return; }
    if (n == 19) { print "diecinueve"; return; }
    if (n == 20) { print "veinte"; return; }
    
    ! Para numeros mayores, usar cifras
    print n;
];

#Ifndef LanguageNumber;
[ LanguageNumber n obj;
    ! Funcion estandar para numeros con concordancia
    if (n == 1) {
        if (obj == 0) print "uno";
        else if (EsGeneroMasculino(obj)) print "un";
        else print "una";
    } else {
        EscribirNumero(n);
    }
];

! ==============================================================================
! DIRECCIONES Y TIEMPO
! ==============================================================================

[ LanguageDirection dir;
    ! [OK] ANADIDO: Funcion para direcciones en espanol
    switch (dir) {
        n_to: print "norte";
        s_to: print "sur";
        e_to: print "este";
        w_to: print "oeste";
        ne_to: print "nordeste";
        nw_to: print "noroeste";
        se_to: print "sudeste";
        sw_to: print "sudoeste";
        u_to: print "arriba";
        d_to: print "abajo";
        in_to: print "adentro";
        out_to: print "afuera";
        default: print "direccion desconocida";
    }
];

[ LanguageTimeOfDay hours mins;
    ! [OK] ANADIDO: Funcion para tiempo en espanol
    if (hours == 0) print "medianoche";
    else if (hours == 12) print "mediodia";
    else {
        if (hours > 12) hours = hours - 12;
        EscribirNumero(hours);
        if (mins > 0) {
            print " y ";
            EscribirNumero(mins);
            if (mins == 1) print " minuto";
            else print " minutos";
        }
        if (hours == 1) print " de la ";
        else print " de las ";
        if (hours < 6 || hours > 20) print "noche";
        else if (hours < 12) print "manana";
        else if (hours < 19) print "tarde";
        else print "noche";
    }
];

! ==============================================================================
! INICIALIZACION Y FINALIZACION
! ==============================================================================

[ SpanishGrammarInitialise;
    ! [OK] CORREGIDO: Inicializacion completa del modulo
    ! Marcar que el modulo esta listo
    spanish_grammar_ready = true;
    MarkModuleLoaded('grammar');
    
    #Ifdef DEBUG;
        print "[SpanishGrammar v", (string) SPANISH_GRAMMAR_VERSION, " inicializado]^";
        print "[Funciones de impresion, articulos, pronombres y concordancia cargadas]^";
        print "[", SPANISH_GRAMMAR_FUNCTIONS, " funciones disponibles]^";
    #Endif;
];

! ==============================================================================
! CONSTANTES DE FINALIZACION
! ==============================================================================

! Estas constantes ya están definidas en SpanishConstants.h
! Constant SPANISH_GRAMMAR_COMPLETE;
! Constant SPANISH_GRAMMAR_READY;
Constant SPANISH_GRAMMAR_FUNCTIONS = 25; ! Numero de funciones publicas

! Informacion del modulo
Constant SPANISH_GRAMMAR_FEATURES = "Articulos, pronombres, concordancia, genero, numero, direcciones, tiempo";

#Endif; ! SPANISH_GRAMMAR_INCLUDED

! ==============================================================================
! Fin de SpanishGrammar.h - Sistema completo y consolidado de gramatica espanola
! ==============================================================================