! ==============================================================================
!   SPANISHADVERBS:  Sistema de adverbios y preposiciones en español para Inform 6
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

! Tipos de adverbios
Constant ADV_LUGAR = 1;      ! Adverbios de lugar (aquí, allí, cerca, lejos...)
Constant ADV_TIEMPO = 2;     ! Adverbios de tiempo (ahora, después, pronto...)
Constant ADV_MODO = 3;       ! Adverbios de modo (bien, mal, rápido...)
Constant ADV_CANTIDAD = 4;   ! Adverbios de cantidad (mucho, poco, bastante...)
Constant ADV_AFIRMACION = 5; ! Adverbios de afirmación (sí, ciertamente...)
Constant ADV_NEGACION = 6;   ! Adverbios de negación (no, nunca, jamás...)
Constant ADV_DUDA = 7;       ! Adverbios de duda (quizás, tal vez, acaso...)

! Relaciones espaciales
Constant REL_DENTRO = 1;     ! dentro de
Constant REL_SOBRE = 2;      ! sobre, encima de
Constant REL_DEBAJO = 3;     ! debajo de, bajo
Constant REL_DETRAS = 4;     ! detrás de
Constant REL_DELANTE = 5;    ! delante de, frente a
Constant REL_CERCA = 6;      ! cerca de, junto a
Constant REL_LEJOS = 7;      ! lejos de
Constant REL_ENTRE = 8;      ! entre
Constant REL_ALREDEDOR = 9;  ! alrededor de
Constant REL_A_TRAVES = 10;  ! a través de
Constant REL_HACIA = 11;     ! hacia
Constant REL_DESDE = 12;     ! desde
Constant REL_HASTA = 13;     ! hasta
Constant REL_CONTRA = 14;    ! contra
Constant REL_SIN = 15;       ! sin
Constant REL_CON = 16;       ! con

! ==============================================================================
!   Parte II.   Tablas de adverbios
! ==============================================================================

! Tabla de adverbios de lugar
Array AdverbiosLugar table
    ! Adverbio      Tipo            Relación espacial
    "aquí"          ADV_LUGAR       0
    "allí"          ADV_LUGAR       0
    "acá"           ADV_LUGAR       0
    "allá"          ADV_LUGAR       0
    "cerca"         ADV_LUGAR       REL_CERCA
    "lejos"         ADV_LUGAR       REL_LEJOS
    "arriba"        ADV_LUGAR       REL_SOBRE
    "abajo"         ADV_LUGAR       REL_DEBAJO
    "dentro"        ADV_LUGAR       REL_DENTRO
    "fuera"         ADV_LUGAR       0
    "delante"       ADV_LUGAR       REL_DELANTE
    "detrás"        ADV_LUGAR       REL_DETRAS
    "enfrente"      ADV_LUGAR       REL_DELANTE
    "alrededor"     ADV_LUGAR       REL_ALREDEDOR
    "encima"        ADV_LUGAR       REL_SOBRE
    "debajo"        ADV_LUGAR       REL_DEBAJO;

! Tabla de preposiciones espaciales
Array PreposicionesEspaciales table
    ! Preposición   Relación espacial
    "en"            REL_DENTRO
    "sobre"         REL_SOBRE
    "bajo"          REL_DEBAJO
    "debajo de"     REL_DEBAJO
    "detrás de"     REL_DETRAS
    "delante de"    REL_DELANTE
    "frente a"      REL_DELANTE
    "cerca de"      REL_CERCA
    "junto a"       REL_CERCA
    "lejos de"      REL_LEJOS
    "entre"         REL_ENTRE
    "alrededor de"  REL_ALREDEDOR
    "a través de"   REL_A_TRAVES
    "hacia"         REL_HACIA
    "desde"         REL_DESDE
    "hasta"         REL_HASTA
    "contra"        REL_CONTRA
    "sin"           REL_SIN
    "con"           REL_CON;

! ==============================================================================
!   Parte III.   Funciones para buscar adverbios y preposiciones
! ==============================================================================

! Busca un adverbio en la tabla de adverbios de lugar
[ BuscarAdverbioLugar adverbio    i;
    for (i=0: i<(AdverbiosLugar-->0)/3: i++) {
        if (CompararCadenas(adverbio, AdverbiosLugar-->(i*3+1))) {
            return i;
        }
    }
    return -1;
];

! Busca una preposición en la tabla de preposiciones espaciales
[ BuscarPreposicionEspacial preposicion    i;
    for (i=0: i<(PreposicionesEspaciales-->0)/2: i++) {
        if (CompararCadenas(preposicion, PreposicionesEspaciales-->(i*2+1))) {
            return i;
        }
    }
    return -1;
];

! Compara dos cadenas
[ CompararCadenas cad1 cad2    i;
    if (cad1-->0 ~= cad2-->0) return false;
    
    for (i=0: i<cad1-->0: i++) {
        if (cad1->(i+2) ~= cad2->(i+2)) return false;
    }
    
    return true;
];

! Obtiene la relación espacial de un adverbio
[ ObtenerRelacionAdverbio adverbio    indice;
    indice = BuscarAdverbioLugar(adverbio);
    if (indice >= 0) {
        return AdverbiosLugar-->(indice*3+3);
    }
    return 0;
];

! Obtiene la relación espacial de una preposición
[ ObtenerRelacionPreposicion preposicion    indice;
    indice = BuscarPreposicionEspacial(preposicion);
    if (indice >= 0) {
        return PreposicionesEspaciales-->(indice*2+2);
    }
    return 0;
];

! ==============================================================================
!   Parte IV.   Funciones para imprimir relaciones espaciales
! ==============================================================================

! Imprime la relación espacial entre dos objetos
[ ImprimirRelacionEspacial relacion obj1 obj2;
    switch (relacion) {
        REL_DENTRO:
            print (el) obj1, " ", (esta) obj1, " dentro ";
            if (obj2 has female) {
                if (obj2 has pluralname) print "de las ";
                else print "de la ";
            } else {
                if (obj2 has pluralname) print "de los ";
                else print "del ";
            }
            print (name) obj2;
            
        REL_SOBRE:
            print (el) obj1, " ", (esta) obj1, " sobre ";
            if (obj2 has female) {
                if (obj2 has pluralname) print "las ";
                else print "la ";
            } else {
                if (obj2 has pluralname) print "los ";
                else print "el ";
            }
            print (name) obj2;
            
        REL_DEBAJO:
            print (el) obj1, " ", (esta) obj1, " debajo ";
            if (obj2 has female) {
                if (obj2 has pluralname) print "de las ";
                else print "de la ";
            } else {
                if (obj2 has pluralname) print "de los ";
                else print "del ";
            }
            print (name) obj2;
            
        REL_DETRAS:
            print (el) obj1, " ", (esta) obj1, " detrás ";
            if (obj2 has female) {
                if (obj2 has pluralname) print "de las ";
                else print "de la ";
            } else {
                if (obj2 has pluralname) print "de los ";
                else print "del ";
            }
            print (name) obj2;
            
        REL_DELANTE:
            print (el) obj1, " ", (esta) obj1, " delante ";
            if (obj2 has female) {
                if (obj2 has pluralname) print "de las ";
                else print "de la ";
            } else {
                if (obj2 has pluralname) print "de los ";
                else print "del ";
            }
            print (name) obj2;
            
        REL_CERCA:
            print (el) obj1, " ", (esta) obj1, " cerca ";
            if (obj2 has female) {
                if (obj2 has pluralname) print "de las ";
                else print "de la ";
            } else {
                if (obj2 has pluralname) print "de los ";
                else print "del ";
            }
            print (name) obj2;
            
        REL_LEJOS:
            print (el) obj1, " ", (esta) obj1, " lejos ";
            if (obj2 has female) {
                if (obj2 has pluralname) print "de las ";
                else print "de la ";
            } else {
                if (obj2 has pluralname) print "de los ";
                else print "del ";
            }
            print (name) obj2;
            
        REL_ENTRE:
            print (el) obj1, " ", (esta) obj1, " entre ";
            if (obj2 has female) {
                if (obj2 has pluralname) print "las ";
                else print "la ";
            } else {
                if (obj2 has pluralname) print "los ";
                else print "el ";
            }
            print (name) obj2;
            
        REL_ALREDEDOR:
            print (el) obj1, " ", (esta) obj1, " alrededor ";
            if (obj2 has female) {
                if (obj2 has pluralname) print "de las ";
                else print "de la ";
            } else {
                if (obj2 has pluralname) print "de los ";
                else print "del ";
            }
            print (name) obj2;
            
        REL_A_TRAVES:
            print (el) obj1, " ", (esta) obj1, " a través ";
            if (obj2 has female) {
                if (obj2 has pluralname) print "de las ";
                else print "de la ";
            } else {
                if (obj2 has pluralname) print "de los ";
                else print "del ";
            }
            print (name) obj2;
            
        REL_HACIA:
            print (el) obj1, " ", (esta) obj1, " hacia ";
            if (obj2 has female) {
                if (obj2 has pluralname) print "las ";
                else print "la ";
            } else {
                if (obj2 has pluralname) print "los ";
                else print "el ";
            }
            print (name) obj2;
            
        REL_DESDE:
            print (el) obj1, " ", (esta) obj1, " desde ";
            if (obj2 has female) {
                if (obj2 has pluralname) print "las ";
                else print "la ";
            } else {
                if (obj2 has pluralname) print "los ";
                else print "el ";
            }
            print (name) obj2;
            
        REL_HASTA:
            print (el) obj1, " ", (esta) obj1, " hasta ";
            if (obj2 has female) {
                if (obj2 has pluralname) print "las ";
                else print "la ";
            } else {
                if (obj2 has pluralname) print "los ";
                else print "el ";
            }
            print (name) obj2;
            
        REL_CONTRA:
            print (el) obj1, " ", (esta) obj1, " contra ";
            if (obj2 has female) {
                if (obj2 has pluralname) print "las ";
                else print "la ";
            } else {
                if (obj2 has pluralname) print "los ";
                else print "el ";
            }
            print (name) obj2;
            
        REL_SIN:
            print (el) obj1, " ", (esta) obj1, " sin ";
            if (obj2 has female) {
                if (obj2 has pluralname) print "las ";
                else print "la ";
            } else {
                if (obj2 has pluralname) print "los ";
                else print "el ";
            }
            print (name) obj2;
            
        REL_CON:
            print (el) obj1, " ", (esta) obj1, " con ";
            if (obj2 has female) {
                if (obj2 has pluralname) print "las ";
                else print "la ";
            } else {
                if (obj2 has pluralname) print "los ";
                else print "el ";
            }
            print (name) obj2;
            
        default:
            print (el) obj1, " ", (esta) obj1, " en relación con ";
            if (obj2 has female) {
                if (obj2 has pluralname) print "las ";
                else print "la ";
            } else {
                if (obj2 has pluralname) print "los ";
                else print "el ";
            }
            print (name) obj2;
    }
];

! ==============================================================================
!   Parte V.   Funciones para manejar frases preposicionales
! ==============================================================================

! Funciones para relaciones espaciales específicas

! Imprime "dentro de" + objeto
[ dentro_de obj;
    print "dentro ";
    if (obj has female) {
        if (obj has pluralname) print "de las ";
        else print "de la ";
    } else {
        if (obj has pluralname) print "de los ";
        else print "del ";
    }
    print (name) obj;
];

! Imprime "sobre" + objeto
[ sobre obj;
    print "sobre ";
    if (obj has female) {
        if (obj has pluralname) print "las ";
        else print "la ";
    } else {
        if (obj has pluralname) print "los ";
        else print "el ";
    }
    print (name) obj;
];

! Imprime "debajo de" + objeto
[ debajo_de obj;
    print "debajo ";
    if (obj has female) {
        if (obj has pluralname) print "de las ";
        else print "de la ";
    } else {
        if (obj has pluralname) print "de los ";
        else print "del ";
    }
    print (name) obj;
];

! Imprime "detrás de" + objeto
[ detras_de obj;
    print "detrás ";
    if (obj has female) {
        if (obj has pluralname) print "de las ";
        else print "de la ";
    } else {
        if (obj has pluralname) print "de los ";
        else print "del ";
    }
    print (name) obj;
];

! Imprime "delante de" + objeto
[ delante_de obj;
    print "delante ";
    if (obj has female) {
        if (obj has pluralname) print "de las ";
        else print "de la ";
    } else {
        if (obj has pluralname) print "de los ";
        else print "del ";
    }
    print (name) obj;
];

! Imprime "cerca de" + objeto
[ cerca_de obj;
    print "cerca ";
    if (obj has female) {
        if (obj has pluralname) print "de las ";
        else print "de la ";
    } else {
        if (obj has pluralname) print "de los ";
        else print "del ";
    }
    print (name) obj;
];

! Imprime "lejos de" + objeto
[ lejos_de obj;
    print "lejos ";
    if (obj has female) {
        if (obj has pluralname) print "de las ";
        else print "de la ";
    } else {
        if (obj has pluralname) print "de los ";
        else print "del ";
    }
    print (name) obj;
];

! Imprime "entre" + objeto
[ entre obj;
    print "entre ";
    if (obj has female) {
        if (obj has pluralname) print "las ";
        else print "la ";
    } else {
        if (obj has pluralname) print "los ";
        else print "el ";
    }
    print (name) obj;
];

! Imprime "alrededor de" + objeto
[ alrededor_de obj;
    print "alrededor ";
    if (obj has female) {
        if (obj has pluralname) print "de las ";
        else print "de la ";
    } else {
        if (obj has pluralname) print "de los ";
        else print "del ";
    }
    print (name) obj;
];

! Imprime "a través de" + objeto
[ a_traves_de obj;
    print "a través ";
    if (obj has female) {
        if (obj has pluralname) print "de las ";
        else print "de la ";
    } else {
        if (obj has pluralname) print "de los ";
        else print "del ";
    }
    print (name) obj;
];

! Imprime "hacia" + objeto
[ hacia obj;
    print "hacia ";
    if (obj has female) {
        if (obj has pluralname) print "las ";
        else print "la ";
    } else {
        if (obj has pluralname) print "los ";
        else print "el ";
    }
    print (name) obj;
];

! Imprime "desde" + objeto
[ desde obj;
    print "desde ";
    if (obj has female) {
        if (obj has pluralname) print "las ";
        else print "la ";
    } else {
        if (obj has pluralname) print "los ";
        else print "el ";
    }
    print (name) obj;
];

! Imprime "hasta" + objeto
[ hasta obj;
    print "hasta ";
    if (obj has female) {
        if (obj has pluralname) print "las ";
        else print "la ";
    } else {
        if (obj has pluralname) print "los ";
        else print "el ";
    }
    print (name) obj;
];

! Imprime "contra" + objeto
[ contra obj;
    print "contra ";
    if (obj has female) {
        if (obj has pluralname) print "las ";
        else print "la ";
    } else {
        if (obj has pluralname) print "los ";
        else print "el ";
    }
    print (name) obj;
];

! Imprime "sin" + objeto
[ sin obj;
    print "sin ";
    if (obj has female) {
        if (obj has pluralname) print "las ";
        else print "la ";
    } else {
        if (obj has pluralname) print "los ";
        else print "el ";
    }
    print (name) obj;
];

! Imprime "con" + objeto
[ con obj;
    print "con ";
    if (obj has female) {
        if (obj has pluralname) print "las ";
        else print "la ";
    } else {
        if (obj has pluralname) print "los ";
        else print "el ";
    }
    print (name) obj;
];

! ==============================================================================
!   Parte VI.   Funciones para manejar frases adverbiales
! ==============================================================================

! Imprime una frase adverbial con un adjetivo
[ adv_adj adverbio adjetivo obj;
    print (string) adverbio, " ";
    ConcordarAdjetivo(adjetivo, obj);
];

! Imprime una frase con verbo, adverbio y objeto
[ verbo_adv verbo adverbio obj;
    ConjugarParaObjeto(verbo, obj);
    print " ", (string) adverbio;
];

! Imprime una frase con verbo, objeto y adverbio
[ verbo_obj_adv verbo obj adverbio;
    ConjugarParaObjeto(verbo, obj);
    print " ", (el) obj, " ", (string) adverbio;
];

! Imprime una frase con verbo, objeto, adverbio y segundo objeto
[ verbo_obj_adv_obj2 verbo obj1 adverbio obj2 relacion;
    if (relacion == 0) {
        relacion = ObtenerRelacionAdverbio(adverbio);
    }
    
    ConjugarParaObjeto(verbo, obj1);
    print " ", (el) obj1, " ";
    
    switch (relacion) {
        REL_DENTRO: dentro_de(obj2);
        REL_SOBRE: sobre(obj2);
        REL_DEBAJO: debajo_de(obj2);
        REL_DETRAS: detras_de(obj2);
        REL_DELANTE: delante_de(obj2);
        REL_CERCA: cerca_de(obj2);
        REL_LEJOS: lejos_de(obj2);
        REL_ENTRE: entre(obj2);
        REL_ALREDEDOR: alrededor_de(obj2);
        REL_A_TRAVES: a_traves_de(obj2);
        REL_HACIA: hacia(obj2);
        REL_DESDE: desde(obj2);
        REL_HASTA: hasta(obj2);
        REL_CONTRA: contra(obj2);
        REL_SIN: sin(obj2);
        REL_CON: con(obj2);
        default:
            print (string) adverbio, " ";
            if (obj2 has female) {
                if (obj2 has pluralname) print "las ";
                else print "la ";
            } else {
                if (obj2 has pluralname) print "los ";
                else print "el ";
            }
            print (name) obj2;
    }
];

! ==============================================================================
!   Fin del archivo
! ==============================================================================