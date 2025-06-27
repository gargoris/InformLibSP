! ==============================================================================
! SPANISHGRAMMAR.H - Sistema completo de gramática y impresión para español
! Parte del sistema modular Spanish Library para Inform 6
! Compatible con Inform 6.42 y librería estándar 6.12.7
! ==============================================================================

System_file;

#Ifndef SPANISH_GRAMMAR_INCLUDED;
Constant SPANISH_GRAMMAR_INCLUDED;
Constant SPANISH_GRAMMAR_VERSION = "1.1-consolidated";

! Verificación de dependencias
#Ifndef SPANISH_CONSTANTS_INCLUDED;
  Message fatalerror "*** Include SpanishConstants.h antes de SpanishGrammar.h ***";
#Endif;

#Ifndef SPANISH_CORE_INCLUDED;
  Message fatalerror "*** Include SpanishCore.h antes de SpanishGrammar.h ***";
#Endif;

! ==============================================================================
! FUNCIONES DE GÉNERO Y NÚMERO - CENTRALIZADAS
! ==============================================================================

[ EsGeneroMasculino obj;
    if (obj has male) rtrue;
    if (obj has female) rfalse;
    if (obj has neuter) rfalse;
    rtrue; ! Por defecto masculino
];

[ EsPlural obj;
    if (obj has pluralname) rtrue;
    rfalse;
];

[ ObtenerGenero obj;
    if (obj has female) return FEMININE;
    if (obj has neuter) return NEUTER;
    return MASCULINE;
];

[ ObtenerNumero obj;
    if (obj has pluralname) return PLURAL;
    return SINGULAR;
];

[ SetSpanishGender obj gender;
    if (gender ~= 0) {
        if (gender == MASCULINE) give obj male;
        if (gender == FEMININE) give obj female;
        if (gender == NEUTER) give obj neuter;
        return;
    }
    give obj male; ! Por defecto masculino
];

! ==============================================================================
! FUNCIONES DE IMPRESIÓN PRINCIPALES - CONSOLIDADAS
! ==============================================================================

[ LanguagePrintShortName obj aux;
    ! FUNCIÓN PRINCIPAL DE IMPRESIÓN - ahora solo aquí
    if (obj == 0) { print "(nada)"; rtrue; }
    
    ! Intentar con short_name_indef si existe y estamos en modo indefinido
    if (indef_mode && obj.&short_name_indef ~= 0) {
        aux = obj.&short_name_indef;
        if (aux-->0 ~= 0) {
            print (string) aux-->0;
            rtrue;
        }
    }
    
    ! Usar short_name normal
    aux = obj.&short_name;
    if (aux ~= 0) {
        if (aux-->0 ~= 0) {
            print (string) aux-->0;
            rtrue;
        }
    }
    
    rfalse;
];

[ LanguagePrintName obj aux;
    ! Función estándar de impresión de nombres
    if (obj == 0) { print "(nada)"; rtrue; }
    
    aux = obj.&name;
    if (aux ~= 0) {
        if (aux-->0 ~= 0) {
            print (string) aux-->0;
            rtrue;
        }
    }
    
    ! Fallback a short_name
    return LanguagePrintShortName(obj);
];

[ PrintName obj;
    ! Alias para compatibilidad
    return LanguagePrintName(obj);
];

! ==============================================================================
! ARTÍCULOS Y DETERMINANTES - EXPANDIDOS
! ==============================================================================

[ ArticuloDefinido obj;
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

[ LanguageContraction prep article;
    ! Manejo automático de contracciones españolas
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

[ ImprimirPreposicionArticulo prep obj;
    ! Imprime preposición + artículo con contracciones automáticas
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

[ ConcordarAdjetivo adj obj tipo;
    ! tipo: 0 = normal, 1 = invariable en género, 2 = invariable total
    
    if (tipo == 2) {
        print (string) adj;
        return;
    }
    
    if (tipo == 1) {
        ! Adjetivos como "grande", "feliz", etc.
        print (string) adj;
        if (EsPlural(obj)) print "s";
        return;
    }
    
    ! Adjetivos normales terminados en -o/-a
    print (string) adj;
    
    ! Ajustar terminación según género
    if (~~EsGeneroMasculino(obj)) {
        ! Si termina en -o, cambiar a -a
        if (adj->(adj->0) == 'o') {
            print "a";
        }
    }
    
    ! Añadir plural si es necesario
    if (EsPlural(obj)) {
        if (adj->(adj->0) == 'z') {
            print "ces"; ! feliz -> felices
        } else {
            print "s";
        }
    }
];

! ==============================================================================
! PRONOMBRES
! ==============================================================================

[ PronombrePersonal persona genero numero caso;
    ! caso: 1=nominativo, 2=acusativo, 3=dativo
    ! genero y numero solo relevantes para 3a persona
    
    switch(persona) {
        1: switch(caso) {
               1: print "yo";
               2: print "me";
               3: print "me";
           }
        2: switch(caso) {
               1: if (FormalityLevel) print "usted"; else print "tú";
               2: if (FormalityLevel) print "le"; else print "te";
               3: if (FormalityLevel) print "le"; else print "te";
           }
        3: switch(caso) {
               1: if (numero == PLURAL) {
                      if (genero == FEMININE) print "ellas"; else print "ellos";
                  } else {
                      if (genero == FEMININE) print "ella"; else print "él";
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
               1: if (FormalityLevel) print "ustedes"; else print "vosotros";
               2: if (FormalityLevel) print "les"; else print "os";
               3: if (FormalityLevel) print "les"; else print "os";
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
    
    if (obj has animate) {
        ! Para personas, usar formas específicas
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
! FUNCIONES DE IMPRESIÓN CON ARTÍCULOS - INTEGRADAS
! ==============================================================================

[ LanguageA obj   aux;
    ! Imprime artículo indefinido + objeto
    if (obj == nothing) { print "nada"; rtrue; }
    if (obj == player) { print "tú mismo"; rtrue; }
    
    ArticuloIndefinido(obj);
    print " ";
    LanguagePrintShortName(obj);
    rtrue;
];

[ LanguageThe obj   aux;
    ! Imprime artículo definido + objeto
    if (obj == nothing) { print "nada"; rtrue; }
    if (obj == player) { print "tú"; rtrue; }
    
    ArticuloDefinido(obj);
    print " ";
    LanguagePrintShortName(obj);
    rtrue;
];

[ A obj; return LanguageA(obj); ];
[ The obj; return LanguageThe(obj); ];

! Compatibilidad con sintaxis estándar
[ a obj; return LanguageA(obj); ];
[ the obj; return LanguageThe(obj); ];

! ==============================================================================
! UTILIDADES DE IMPRESIÓN CON CONCORDANCIA
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

[ LanguageAnimateGender person;
    ! Función para determinar género de personas
    if (person has female) return FEMININE;
    if (person has male) return MASCULINE;
    return MASCULINE; ! Por defecto masculino
];

[ LanguageGenderNumber obj;
    ! Función que devuelve código de género y número
    ! 1 = masculino singular, 2 = femenino singular
    ! 3 = masculino plural, 4 = femenino plural
    if (obj has pluralname) {
        if (obj has female) return 4;
        return 3;
    } else {
        if (obj has female) return 2;
        return 1;
    }
];

! ==============================================================================
! NÚMEROS Y CANTIDADES
! ==============================================================================

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
            if (n/1000 == 1) print "mil";
            else print (LanguageNumber) n/1000, " mil";
            n = n%1000;
            if (n ~= 0) print " ";
        }
    }
    if (n >= 100) {
        switch(n/100) {
            1: if (n == 100) print "cien"; else print "ciento";
            2: print "doscientos";
            3: print "trescientos";
            4: print "cuatrocientos";
            5: print "quinientos";
            6: print "seiscientos";
            7: print "setecientos";
            8: print "ochocientos";
            9: print "novecientos";
        }
        n = n%100;
        if (n ~= 0) print " ";
    }
    switch (n) {
        0: rfalse;
        1: if (f == 1) print "una"; else print "uno";
        2: print "dos"; 3: print "tres"; 4: print "cuatro"; 5: print "cinco";
        6: print "seis"; 7: print "siete"; 8: print "ocho"; 9: print "nueve"; 10: print "diez";
        11: print "once"; 12: print "doce"; 13: print "trece"; 14: print "catorce"; 15: print "quince";
        16: print "dieciséis"; 17: print "diecisiete"; 18: print "dieciocho"; 19: print "diecinueve"; 20: print "veinte";
        21: print "veintiuno"; 22: print "veintidós"; 23: print "veintitrés"; 24: print "veinticuatro";
        25: print "veinticinco"; 26: print "veintiséis"; 27: print "veintisiete"; 28: print "veintiocho";
        29: print "veintinueve";
        30: print "treinta"; 40: print "cuarenta"; 50: print "cincuenta";
        60: print "sesenta"; 70: print "setenta"; 80: print "ochenta"; 90: print "noventa";
        default:
            print (LanguageNumber) (n/10)*10;
            print " y ";
            print (LanguageNumber) n%10;
    }
];

[ LanguageTimeOfDay hours mins i;
    i = hours%12;
    if (i == 0) i = 12;
    if (i == 1) print "Es la una";
    else { print "Son las "; print (LanguageNumber) i; }
    
    if (mins ~= 0) {
        if (mins == 15) print " y cuarto";
        else if (mins == 30) print " y media";
        else if (mins == 45) { 
            print " menos cuarto"; 
            if (hours%12 == 11) print " del mediodía";
            else if (hours == 23) print " de la noche";
        }
        else {
            print " y ";
            print (LanguageNumber) mins;
            if (mins == 1) print " minuto"; else print " minutos";
        }
    }
    
    if (hours == 0 && mins == 0) print " de la medianoche";
    else if (hours < 12) print " de la mañana";
    else if (hours == 12 && mins == 0) print " del mediodía";
    else if (hours < 19) print " de la tarde";
    else print " de la noche";
];

! ==============================================================================
! DIRECCIONES
! ==============================================================================

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

[ DireccionOpuesta d;
    switch (d) {
        n_to:  return s_to;
        s_to:  return n_to;
        e_to:  return w_to;
        w_to:  return e_to;
        ne_to: return sw_to;
        nw_to: return se_to;
        se_to: return nw_to;
        sw_to: return ne_to;
        u_to:  return d_to;
        d_to:  return u_to;
        in_to: return out_to;
        out_to: return in_to;
    }
    return 0;
];

! ==============================================================================
! UTILIDADES GRAMATICALES ADICIONALES
! ==============================================================================

[ LanguageCantGo;
    print "No puedes ir hacia esa dirección.";
];

[ EsVocal char;
    if (char == 'a' or 'e' or 'i' or 'o' or 'u' or 
                 'á' or 'é' or 'í' or 'ó' or 'ú') rtrue;
    rfalse;
];

[ RequiereEufonia palabra1 palabra2;
    ! Determina si se necesita eufonía (y->e, o->u)
    if (palabra1 == 'y' && palabra2->1 == 'i') rtrue;
    if (palabra1 == 'o' && palabra2->1 == 'o') rtrue;
    rfalse;
];

[ ImprimirListaY obj1 obj2;
    print (name) obj1;
    if (RequiereEufonia('y', obj2.&name-->0)) 
        print " e ";
    else 
        print " y ";
    print (name) obj2;
];

[ ImprimirListaO obj1 obj2;
    print (name) obj1;
    if (RequiereEufonia('o', obj2.&name-->0)) 
        print " u ";
    else 
        print " o ";
    print (name) obj2;
];

! ==============================================================================
! FORMACIÓN DE PLURALES
! ==============================================================================

[ FormarPlural palabra buffer;
    ! Copia la palabra al buffer y añade la terminación plural apropiada
    ! Asume que buffer tiene espacio suficiente
    
    local i len ultima penultima;
    
    len = palabra->0;
    for (i = 0: i < len: i++) {
        buffer->(i+1) = palabra->(i+1);
    }
    
    ultima = palabra->len;
    if (len > 1) penultima = palabra->(len-1);
    
    ! Reglas de formación de plurales en español
    if (ultima == 'z') {
        ! -z -> -ces (lápiz -> lápices)
        buffer->len = 'c';
        buffer->(len+1) = 'e';
        buffer->(len+2) = 's';
        buffer->0 = len + 2;
    }
    else if (ultima == 's' && ~~EsVocal(penultima)) {
        ! Palabras terminadas en -s precedida de consonante no cambian
        buffer->0 = len;
    }
    else if (EsVocal(ultima)) {
        ! Vocal -> vocal + s
        buffer->(len+1) = 's';
        buffer->0 = len + 1;
    }
    else {
        ! Consonante (excepto -s, -z) -> consonante + es
        buffer->(len+1) = 'e';
        buffer->(len+2) = 's';
        buffer->0 = len + 2;
    }
    
    return buffer;
];

! ==============================================================================
! FUNCIONES DE INTEGRACIÓN CON SISTEMA PRINCIPAL
! ==============================================================================

[ LanguageRefers obj wn   word pronoun_class;
    ! Sistema de pronombres integrado con voseo
    word = wn-->0;
    
    #Ifdef SPANISH_REGIONAL_INCLUDED;
        ! Si es voseo argentino, manejar "vos"
        if (voseo_enabled && word == 'vos') {
            if (obj == player) rtrue;
        }
    #Endif;
    
    ! Verificar pronombres estándar
    if (word == 'el' or 'ella' or 'ello') {
        if (obj has animate && ~~(obj has pluralname)) rtrue;
    }
    
    if (word == 'ellos' or 'ellas') {
        if (obj has animate && obj has pluralname) rtrue;
    }
    
    if (word == 'lo' or 'la') {
        if (~~(obj has animate) && ~~(obj has pluralname)) rtrue;
    }
    
    if (word == 'los' or 'las') {
        if (~~(obj has animate) && obj has pluralname) rtrue;
    }
    
    ! Verificar en tabla de pronombres
    pronoun_class = PronounValue(word);
    if (pronoun_class ~= 0) {
        if (obj == pronoun_class) rtrue;
    }
    
    rfalse;
];

! ==============================================================================
! DEPURACIÓN GRAMATICAL
! ==============================================================================

#Ifdef DEBUG;
[ SpanishDebugGender obj;
    print "Objeto: ", (name) obj;
    print " - Género: ";
    if (obj has male) print "masculino";
    else if (obj has female) print "femenino";
    else print "neutro";
    
    print " - Número: ";
    if (obj has pluralname) print "plural";
    else print "singular";
    
    print " - Artículo: ";
    ArticuloDefinido(obj);
    print "^";
];

[ TestConcordancia obj adj;
    print "Prueba de concordancia:^";
    print "  "; ArticuloDefinido(obj); print " "; (name) obj; 
    print " "; ConcordarAdjetivo(adj, obj, 0); print "^";
    
    print "  "; ArticuloIndefinido(obj); print " "; (name) obj;
    print " "; ConcordarAdjetivo(adj, obj, 0); print "^";
    
    print "  "; ArticuloDemostrativo(obj, 1); print " "; (name) obj; print "^";
    print "  "; ArticuloPosesivo(1, obj); print " "; (name) obj; print "^";
];
#Endif;

! ==============================================================================
! INICIALIZACIÓN Y FINALIZACIÓN
! ==============================================================================

[ SpanishGrammarInitialise;
    ! Marcar que el módulo está listo
    spanish_grammar_ready = true;
    MarkModuleLoaded('grammar');
    
    #Ifdef DEBUG;
        print "[SpanishGrammar v", (string) SPANISH_GRAMMAR_VERSION, " inicializado]^";
        print "[Funciones de impresión, artículos, pronombres y concordancia cargadas]^";
    #Endif;
];

! Constantes de finalización
Constant SPANISH_GRAMMAR_COMPLETE;
Constant SPANISH_GRAMMAR_READY;

#Endif; ! SPANISH_GRAMMAR_INCLUDED

! ==============================================================================
! Fin de SpanishGrammar.h - Sistema completo y consolidado de gramática española
! ==============================================================================