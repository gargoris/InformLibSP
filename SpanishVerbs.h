! ==============================================================================
!   SPANISHVERBS:  Sistema de conjugación de verbos en español para Inform 6
!
!   Basado en la librería Inform 6 -- Release 6.12.7 -- Serial number 240410
!
!   Copyright Graham Nelson 1993-2004 and David Griffith 2012-2024
!   Adaptación al español por Francisco Fuentes, 2025
!
!   This code is licensed under either the traditional Inform license as
!   described by the DM4 or the Artistic License version 2.0.
!
! ==============================================================================

System_file;

! ==============================================================================
!   Parte I.   Constantes y definiciones
! ==============================================================================

! Tiempos verbales
Constant TIEMPO_PRESENTE = 1;
Constant TIEMPO_PRETERITO = 2;
Constant TIEMPO_IMPERFECTO = 3;
Constant TIEMPO_FUTURO = 4;
Constant TIEMPO_CONDICIONAL = 5;
Constant TIEMPO_SUBJUNTIVO = 6;
Constant TIEMPO_IMPERATIVO = 7;

! Personas gramaticales
Constant PERSONA_YO = 1;
Constant PERSONA_TU = 2;
Constant PERSONA_USTED = 3;
Constant PERSONA_EL = 4;
Constant PERSONA_ELLA = 5;
Constant PERSONA_NOSOTROS = 6;
Constant PERSONA_VOSOTROS = 7;
Constant PERSONA_USTEDES = 8;
Constant PERSONA_ELLOS = 9;
Constant PERSONA_ELLAS = 10;

! Tipos de conjugación
Constant CONJ_AR = 1;
Constant CONJ_ER = 2;
Constant CONJ_IR = 3;
Constant CONJ_IRREGULAR = 4;

! ==============================================================================
!   Parte II.   Conjugación de verbos regulares
! ==============================================================================

! Determina el tipo de conjugación basado en la terminación del verbo
[ DeterminarConjugacion verbo;
    if (verbo->0 == 0) return 0;
    
    ! Obtener la longitud del verbo
    local len = verbo-->0;
    
    ! Verificar terminación
    if (len >= 2) {
        if (verbo->(len-1) == 'r' && verbo->(len) == 0) {
            if (verbo->(len-2) == 'a') return CONJ_AR;
            if (verbo->(len-2) == 'e') return CONJ_ER;
            if (verbo->(len-2) == 'i') return CONJ_IR;
        }
    }
    
    return 0;
];

! Obtiene la raíz del verbo (sin la terminación -ar, -er, -ir)
[ ObtenerRaizVerbo verbo destino;
    if (verbo->0 == 0) return 0;
    
    local len = verbo-->0;
    local i;
    
    ! Copiar todo excepto los últimos 2 caracteres
    for (i=0: i<len-2: i++) {
        destino->(i+2) = verbo->(i+2);
    }
    destino->(i+2) = 0;
    destino-->0 = len-2;
    
    return 1;
];

! Conjugar un verbo regular en presente
[ ConjugarVerboRegularPresente raiz tipo persona;
    switch (tipo) {
        CONJ_AR:
            switch (persona) {
                PERSONA_YO: print (string) raiz, "o";
                PERSONA_TU: print (string) raiz, "as";
                PERSONA_USTED, PERSONA_EL, PERSONA_ELLA: print (string) raiz, "a";
                PERSONA_NOSOTROS: print (string) raiz, "amos";
                PERSONA_VOSOTROS: print (string) raiz, "áis";
                PERSONA_USTEDES, PERSONA_ELLOS, PERSONA_ELLAS: print (string) raiz, "an";
                default: print (string) raiz, "ar";
            }
        
        CONJ_ER:
            switch (persona) {
                PERSONA_YO: print (string) raiz, "o";
                PERSONA_TU: print (string) raiz, "es";
                PERSONA_USTED, PERSONA_EL, PERSONA_ELLA: print (string) raiz, "e";
                PERSONA_NOSOTROS: print (string) raiz, "emos";
                PERSONA_VOSOTROS: print (string) raiz, "éis";
                PERSONA_USTEDES, PERSONA_ELLOS, PERSONA_ELLAS: print (string) raiz, "en";
                default: print (string) raiz, "er";
            }
        
        CONJ_IR:
            switch (persona) {
                PERSONA_YO: print (string) raiz, "o";
                PERSONA_TU: print (string) raiz, "es";
                PERSONA_USTED, PERSONA_EL, PERSONA_ELLA: print (string) raiz, "e";
                PERSONA_NOSOTROS: print (string) raiz, "imos";
                PERSONA_VOSOTROS: print (string) raiz, "ís";
                PERSONA_USTEDES, PERSONA_ELLOS, PERSONA_ELLAS: print (string) raiz, "en";
                default: print (string) raiz, "ir";
            }
            
        default:
            print (string) raiz, "??";
    }
];

! Conjugar un verbo regular en pretérito
[ ConjugarVerboRegularPreterito raiz tipo persona;
    switch (tipo) {
        CONJ_AR:
            switch (persona) {
                PERSONA_YO: print (string) raiz, "é";
                PERSONA_TU: print (string) raiz, "aste";
                PERSONA_USTED, PERSONA_EL, PERSONA_ELLA: print (string) raiz, "ó";
                PERSONA_NOSOTROS: print (string) raiz, "amos";
                PERSONA_VOSOTROS: print (string) raiz, "asteis";
                PERSONA_USTEDES, PERSONA_ELLOS, PERSONA_ELLAS: print (string) raiz, "aron";
                default: print (string) raiz, "ar";
            }
        
        CONJ_ER, CONJ_IR:
            switch (persona) {
                PERSONA_YO: print (string) raiz, "í";
                PERSONA_TU: print (string) raiz, "iste";
                PERSONA_USTED, PERSONA_EL, PERSONA_ELLA: print (string) raiz, "ió";
                PERSONA_NOSOTROS: print (string) raiz, "imos";
                PERSONA_VOSOTROS: print (string) raiz, "isteis";
                PERSONA_USTEDES, PERSONA_ELLOS, PERSONA_ELLAS: print (string) raiz, "ieron";
                default: print (string) raiz, tipo == CONJ_ER ? "er" : "ir";
            }
            
        default:
            print (string) raiz, "??";
    }
];

! Conjugar un verbo regular en imperfecto
[ ConjugarVerboRegularImperfecto raiz tipo persona;
    switch (tipo) {
        CONJ_AR:
            switch (persona) {
                PERSONA_YO: print (string) raiz, "aba";
                PERSONA_TU: print (string) raiz, "abas";
                PERSONA_USTED, PERSONA_EL, PERSONA_ELLA: print (string) raiz, "aba";
                PERSONA_NOSOTROS: print (string) raiz, "ábamos";
                PERSONA_VOSOTROS: print (string) raiz, "abais";
                PERSONA_USTEDES, PERSONA_ELLOS, PERSONA_ELLAS: print (string) raiz, "aban";
                default: print (string) raiz, "ar";
            }
        
        CONJ_ER, CONJ_IR:
            switch (persona) {
                PERSONA_YO: print (string) raiz, "ía";
                PERSONA_TU: print (string) raiz, "ías";
                PERSONA_USTED, PERSONA_EL, PERSONA_ELLA: print (string) raiz, "ía";
                PERSONA_NOSOTROS: print (string) raiz, "íamos";
                PERSONA_VOSOTROS: print (string) raiz, "íais";
                PERSONA_USTEDES, PERSONA_ELLOS, PERSONA_ELLAS: print (string) raiz, "ían";
                default: print (string) raiz, tipo == CONJ_ER ? "er" : "ir";
            }
            
        default:
            print (string) raiz, "??";
    }
];

! Conjugar un verbo regular en futuro
[ ConjugarVerboRegularFuturo verbo persona;
    ! El futuro se forma con el infinitivo completo + terminaciones
    switch (persona) {
        PERSONA_YO: print (string) verbo, "é";
        PERSONA_TU: print (string) verbo, "ás";
        PERSONA_USTED, PERSONA_EL, PERSONA_ELLA: print (string) verbo, "á";
        PERSONA_NOSOTROS: print (string) verbo, "emos";
        PERSONA_VOSOTROS: print (string) verbo, "éis";
        PERSONA_USTEDES, PERSONA_ELLOS, PERSONA_ELLAS: print (string) verbo, "án";
        default: print (string) verbo;
    }
];

! Conjugar un verbo regular en condicional
[ ConjugarVerboRegularCondicional verbo persona;
    ! El condicional se forma con el infinitivo completo + terminaciones
    switch (persona) {
        PERSONA_YO: print (string) verbo, "ía";
        PERSONA_TU: print (string) verbo, "ías";
        PERSONA_USTED, PERSONA_EL, PERSONA_ELLA: print (string) verbo, "ía";
        PERSONA_NOSOTROS: print (string) verbo, "íamos";
        PERSONA_VOSOTROS: print (string) verbo, "íais";
        PERSONA_USTEDES, PERSONA_ELLOS, PERSONA_ELLAS: print (string) verbo, "ían";
        default: print (string) verbo;
    }
];

! Conjugar un verbo regular en subjuntivo presente
[ ConjugarVerboRegularSubjuntivo raiz tipo persona;
    switch (tipo) {
        CONJ_AR:
            switch (persona) {
                PERSONA_YO: print (string) raiz, "e";
                PERSONA_TU: print (string) raiz, "es";
                PERSONA_USTED, PERSONA_EL, PERSONA_ELLA: print (string) raiz, "e";
                PERSONA_NOSOTROS: print (string) raiz, "emos";
                PERSONA_VOSOTROS: print (string) raiz, "éis";
                PERSONA_USTEDES, PERSONA_ELLOS, PERSONA_ELLAS: print (string) raiz, "en";
                default: print (string) raiz, "ar";
            }
        
        CONJ_ER, CONJ_IR:
            switch (persona) {
                PERSONA_YO: print (string) raiz, "a";
                PERSONA_TU: print (string) raiz, "as";
                PERSONA_USTED, PERSONA_EL, PERSONA_ELLA: print (string) raiz, "a";
                PERSONA_NOSOTROS: print (string) raiz, "amos";
                PERSONA_VOSOTROS: print (string) raiz, "áis";
                PERSONA_USTEDES, PERSONA_ELLOS, PERSONA_ELLAS: print (string) raiz, "an";
                default: print (string) raiz, tipo == CONJ_ER ? "er" : "ir";
            }
            
        default:
            print (string) raiz, "??";
    }
];

! Conjugar un verbo regular en imperativo
[ ConjugarVerboRegularImperativo raiz tipo persona;
    switch (tipo) {
        CONJ_AR:
            switch (persona) {
                PERSONA_TU: print (string) raiz, "a";
                PERSONA_USTED: print (string) raiz, "e";
                PERSONA_NOSOTROS: print (string) raiz, "emos";
                PERSONA_VOSOTROS: print (string) raiz, "ad";
                PERSONA_USTEDES: print (string) raiz, "en";
                default: print (string) raiz, "ar";
            }
        
        CONJ_ER:
            switch (persona) {
                PERSONA_TU: print (string) raiz, "e";
                PERSONA_USTED: print (string) raiz, "a";
                PERSONA_NOSOTROS: print (string) raiz, "amos";
                PERSONA_VOSOTROS: print (string) raiz, "ed";
                PERSONA_USTEDES: print (string) raiz, "an";
                default: print (string) raiz, "er";
            }
            
        CONJ_IR:
            switch (persona) {
                PERSONA_TU: print (string) raiz, "e";
                PERSONA_USTED: print (string) raiz, "a";
                PERSONA_NOSOTROS: print (string) raiz, "amos";
                PERSONA_VOSOTROS: print (string) raiz, "id";
                PERSONA_USTEDES: print (string) raiz, "an";
                default: print (string) raiz, "ir";
            }
            
        default:
            print (string) raiz, "??";
    }
];

! ==============================================================================
!   Parte III.   Verbos irregulares
! ==============================================================================

! Tabla de verbos irregulares comunes
Array VerbosIrregulares table
    ! Infinitivo  Presente (yo)  Presente (él)  Pretérito (yo)  Pretérito (él)  Futuro (yo)  Participio
    "ser"         "soy"          "es"           "fui"           "fue"           "seré"       "sido"
    "estar"       "estoy"        "está"         "estuve"        "estuvo"        "estaré"     "estado"
    "ir"          "voy"          "va"           "fui"           "fue"           "iré"        "ido"
    "haber"       "he"           "ha"           "hube"          "hubo"          "habré"      "habido"
    "tener"       "tengo"        "tiene"        "tuve"          "tuvo"          "tendré"     "tenido"
    "hacer"       "hago"         "hace"         "hice"          "hizo"          "haré"       "hecho"
    "poder"       "puedo"        "puede"        "pude"          "pudo"          "podré"      "podido"
    "decir"       "digo"         "dice"         "dije"          "dijo"          "diré"       "dicho"
    "ver"         "veo"          "ve"           "vi"            "vio"           "veré"       "visto"
    "dar"         "doy"          "da"           "di"            "dio"           "daré"       "dado"
    "saber"       "sé"           "sabe"         "supe"          "supo"          "sabré"      "sabido"
    "querer"      "quiero"       "quiere"       "quise"         "quiso"         "querré"     "querido"
    "poner"       "pongo"        "pone"         "puse"          "puso"          "pondré"     "puesto"
    "venir"       "vengo"        "viene"        "vine"          "vino"          "vendré"     "venido"
    "salir"       "salgo"        "sale"         "salí"          "salió"         "saldré"     "salido"
    "traer"       "traigo"       "trae"         "traje"         "trajo"         "traeré"     "traído";

! Busca un verbo en la tabla de irregulares
[ BuscarVerboIrregular verbo;
    local i;
    for (i=0: i<(VerbosIrregulares-->0)/7: i++) {
        if (CompararCadenas(verbo, VerbosIrregulares-->(i*7+1))) {
            return i;
        }
    }
    return -1;
];

! Compara dos cadenas
[ CompararCadenas cad1 cad2;
    local i;
    if (cad1-->0 ~= cad2-->0) return false;
    
    for (i=0: i<cad1-->0: i++) {
        if (cad1->(i+2) ~= cad2->(i+2)) return false;
    }
    
    return true;
];

! Conjugar un verbo irregular en presente
[ ConjugarVerboIrregularPresente indice persona;
    if (indice < 0) return false;
    
    switch (persona) {
        PERSONA_YO: 
            print (string) VerbosIrregulares-->(indice*7+2);
            
        PERSONA_TU:
            ! Derivar tú de él (reglas generales)
            local el_form = VerbosIrregulares-->(indice*7+3);
            local len = el_form-->0;
            
            if (el_form->(len+1) == 'e') {
                ! Si termina en 'e', cambiar a 'es'
                print (string) el_form, "s";
            } else {
                ! Si termina en otra vocal, añadir 's'
                print (string) el_form, "s";
            }
            
        PERSONA_USTED, PERSONA_EL, PERSONA_ELLA:
            print (string) VerbosIrregulares-->(indice*7+3);
            
        PERSONA_NOSOTROS:
            ! Derivar nosotros del infinitivo (más regular)
            local inf = VerbosIrregulares-->(indice*7+1);
            local len = inf-->0;
            local tipo = DeterminarConjugacion(inf);
            
            if (tipo == CONJ_AR) {
                ! Quitar 'ar' y añadir 'amos'
                inf->(len) = 0;
                inf->(len-1) = 0;
                print (string) inf, "amos";
            } else {
                ! Quitar 'er'/'ir' y añadir 'emos'/'imos'
                inf->(len) = 0;
                inf->(len-1) = 0;
                if (tipo == CONJ_ER) {
                    print (string) inf, "emos";
                } else {
                    print (string) inf, "imos";
                }
            }
            
        PERSONA_VOSOTROS:
            ! Derivar vosotros del infinitivo
            local inf = VerbosIrregulares-->(indice*7+1);
            local len = inf-->0;
            local tipo = DeterminarConjugacion(inf);
            
            if (tipo == CONJ_AR) {
                ! Quitar 'ar' y añadir 'áis'
                inf->(len) = 0;
                inf->(len-1) = 0;
                print (string) inf, "áis";
            } else if (tipo == CONJ_ER) {
                ! Quitar 'er' y añadir 'éis'
                inf->(len) = 0;
                inf->(len-1) = 0;
                print (string) inf, "éis";
            } else {
                ! Quitar 'ir' y añadir 'ís'
                inf->(len) = 0;
                inf->(len-1) = 0;
                print (string) inf, "ís";
            }
            
        PERSONA_USTEDES, PERSONA_ELLOS, PERSONA_ELLAS:
            ! Derivar ellos de él
            local el_form = VerbosIrregulares-->(indice*7+3);
            local len = el_form-->0;
            
            if (el_form->(len+1) == 'e') {
                ! Si termina en 'e', cambiar a 'en'
                print (string) el_form, "n";
            } else {
                ! Si termina en otra vocal, añadir 'n'
                print (string) el_form, "n";
            }
            
        default:
            print (string) VerbosIrregulares-->(indice*7+1);
    }
    
    return true;
];

! Conjugar un verbo irregular en pretérito
[ ConjugarVerboIrregularPreterito indice persona;
    if (indice < 0) return false;
    
    switch (persona) {
        PERSONA_YO: 
            print (string) VerbosIrregulares-->(indice*7+4);
            
        PERSONA_TU:
            ! Derivar tú de yo en pretérito (reglas generales)
            local yo_form = VerbosIrregulares-->(indice*7+4);
            local len = yo_form-->0;
            
            ! Quitar última letra y añadir 'ste'
            yo_form->(len+1) = 0;
            print (string) yo_form, "ste";
            
        PERSONA_USTED, PERSONA_EL, PERSONA_ELLA:
            print (string) VerbosIrregulares-->(indice*7+5);
            
        PERSONA_NOSOTROS:
            ! Derivar nosotros de él en pretérito
            local el_form = VerbosIrregulares-->(indice*7+5);
            local len = el_form-->0;
            
            ! Quitar última letra y añadir 'mos'
            el_form->(len+1) = 0;
            print (string) el_form, "mos";
            
        PERSONA_VOSOTROS:
            ! Derivar vosotros de él en pretérito
            local el_form = VerbosIrregulares-->(indice*7+5);
            local len = el_form-->0;
            
            ! Quitar última letra y añadir 'steis'
            el_form->(len+1) = 0;
            print (string) el_form, "steis";
            
        PERSONA_USTEDES, PERSONA_ELLOS, PERSONA_ELLAS:
            ! Derivar ellos de él en pretérito
            local el_form = VerbosIrregulares-->(indice*7+5);
            local len = el_form-->0;
            
            ! Quitar última letra y añadir 'ron'
            el_form->(len+1) = 0;
            print (string) el_form, "ron";
            
        default:
            print (string) VerbosIrregulares-->(indice*7+1);
    }
    
    return true;
];

! Conjugar un verbo irregular en futuro
[ ConjugarVerboIrregularFuturo indice persona;
    if (indice < 0) return false;
    
    switch (persona) {
        PERSONA_YO: 
            print (string) VerbosIrregulares-->(indice*7+6);
            
        PERSONA_TU:
            ! Derivar tú de yo en futuro
            local yo_form = VerbosIrregulares-->(indice*7+6);
            local len = yo_form-->0;
            
            ! Quitar última letra y añadir 'ás'
            yo_form->(len+1) = 0;
            print (string) yo_form, "ás";
            
        PERSONA_USTED, PERSONA_EL, PERSONA_ELLA:
            ! Derivar él de yo en futuro
            local yo_form = VerbosIrregulares-->(indice*7+6);
            local len = yo_form-->0;
            
            ! Quitar última letra y añadir 'á'
            yo_form->(len+1) = 0;
            print (string) yo_form, "á";
            
        PERSONA_NOSOTROS:
            ! Derivar nosotros de yo en futuro
            local yo_form = VerbosIrregulares-->(indice*7+6);
            local len = yo_form-->0;
            
            ! Quitar última letra y añadir 'emos'
            yo_form->(len+1) = 0;
            print (string) yo_form, "emos";
            
        PERSONA_VOSOTROS:
            ! Derivar vosotros de yo en futuro
            local yo_form = VerbosIrregulares-->(indice*7+6);
            local len = yo_form-->0;
            
            ! Quitar última letra y añadir 'éis'
            yo_form->(len+1) = 0;
            print (string) yo_form, "éis";
            
        PERSONA_USTEDES, PERSONA_ELLOS, PERSONA_ELLAS:
            ! Derivar ellos de yo en futuro
            local yo_form = VerbosIrregulares-->(indice*7+6);
            local len = yo_form-->0;
            
            ! Quitar última letra y añadir 'án'
            yo_form->(len+1) = 0;
            print (string) yo_form, "án";
            
        default:
            print (string) VerbosIrregulares-->(indice*7+1);
    }
    
    return true;
];

! ==============================================================================
!   Parte IV.   Interfaz principal de conjugación
! ==============================================================================

! Función principal para conjugar verbos
[ ConjugarVerbo verbo tiempo persona;
    ! Verificar si es un verbo irregular
    local indice_irregular = BuscarVerboIrregular(verbo);
    
    if (indice_irregular >= 0) {
        ! Es un verbo irregular, usar conjugaciones especiales
        switch (tiempo) {
            TIEMPO_PRESENTE:
                return ConjugarVerboIrregularPresente(indice_irregular, persona);
                
            TIEMPO_PRETERITO:
                return ConjugarVerboIrregularPreterito(indice_irregular, persona);
                
            TIEMPO_FUTURO:
                return ConjugarVerboIrregularFuturo(indice_irregular, persona);
                
            default:
                ! Para otros tiempos, usar conjugación regular como fallback
                print "[Conjugación irregular no disponible para este tiempo] ";
        }
    }
    
    ! Es un verbo regular o no tenemos la conjugación irregular para este tiempo
    local tipo_conj = DeterminarConjugacion(verbo);
    
    if (tipo_conj == 0) {
        print (string) verbo;
        return false;
    }
    
    ! Obtener la raíz del verbo
    local raiz = CreateArray(verbo-->0);
    ObtenerRaizVerbo(verbo, raiz);
    
    ! Conjugar según el tiempo verbal
    switch (tiempo) {
        TIEMPO_PRESENTE:
            ConjugarVerboRegularPresente(raiz, tipo_conj, persona);
            
        TIEMPO_PRETERITO:
            ConjugarVerboRegularPreterito(raiz, tipo_conj, persona);
            
        TIEMPO_IMPERFECTO:
            ConjugarVerboRegularImperfecto(raiz, tipo_conj, persona);
            
        TIEMPO_FUTURO:
            ConjugarVerboRegularFuturo(verbo, persona);
            
        TIEMPO_CONDICIONAL:
            ConjugarVerboRegularCondicional(verbo, persona);
            
        TIEMPO_SUBJUNTIVO:
            ConjugarVerboRegularSubjuntivo(raiz, tipo_conj, persona);
            
        TIEMPO_IMPERATIVO:
            ConjugarVerboRegularImperativo(raiz, tipo_conj, persona);
            
        default:
            print (string) verbo;
    }
    
    return true;
];

! Función auxiliar para crear un array temporal
[ CreateArray size;
    return VM_AllocateMemory(size + 4);
];

! ==============================================================================
!   Parte V.   Funciones de ayuda para mensajes
! ==============================================================================

! Conjugar un verbo en tercera persona según el género y número del objeto
[ ConjugarParaObjeto verbo obj;
    local persona;
    
    if (obj has pluralname) {
        if (obj has female) {
            persona = PERSONA_ELLAS;
        } else {
            persona = PERSONA_ELLOS;
        }
    } else {
        if (obj has female) {
            persona = PERSONA_ELLA;
        } else {
            persona = PERSONA_EL;
        }
    }
    
    return ConjugarVerbo(verbo, TIEMPO_PRESENTE, persona);
];

! Conjugar un verbo en pasado para un objeto
[ ConjugarPasadoParaObjeto verbo obj;
    local persona;
    
    if (obj has pluralname) {
        if (obj has female) {
            persona = PERSONA_ELLAS;
        } else {
            persona = PERSONA_ELLOS;
        }
    } else {
        if (obj has female) {
            persona = PERSONA_ELLA;
        } else {
            persona = PERSONA_EL;
        }
    }
    
    return ConjugarVerbo(verbo, TIEMPO_PRETERITO, persona);
];

! ==============================================================================
!   Fin del archivo
! ==============================================================================