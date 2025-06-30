! ==============================================================================
!   SPANISHADJECTIVES:  Sistema de adjetivos en español para Inform 6
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

! Tipos de adjetivos según su terminación
Constant ADJ_O = 1;      ! Adjetivos que terminan en -o (cambian a -a, -os, -as)
Constant ADJ_E = 2;      ! Adjetivos que terminan en -e (solo cambian a -es en plural)
Constant ADJ_CONS = 3;   ! Adjetivos que terminan en consonante (solo cambian a -es en plural)
Constant ADJ_INVAR = 4;  ! Adjetivos invariables (no cambian)
Constant ADJ_IRREG = 5;  ! Adjetivos irregulares (requieren formas especiales)

! ==============================================================================
!   Parte II.   Funciones para determinar el tipo de adjetivo
! ==============================================================================

! Determina el tipo de adjetivo basado en su terminación
[ DeterminarTipoAdjetivo adjetivo;
    if (adjetivo->0 == 0) return 0;
    
    ! Obtener la longitud del adjetivo
    local len = adjetivo-->0;
    local ultima_letra = adjetivo->(len+1);
    
    ! Verificar terminación
    if (ultima_letra == 'o') return ADJ_O;
    if (ultima_letra == 'e') return ADJ_E;
    if (ultima_letra == 'a' or 'i' or 'u' or 'á' or 'é' or 'í' or 'ó' or 'ú') return ADJ_INVAR;
    
    ! Si termina en consonante
    return ADJ_CONS;
];

! ==============================================================================
!   Parte III.   Adjetivos irregulares
! ==============================================================================

! Tabla de adjetivos irregulares comunes
Array AdjetivosIrregulares table
    ! Masculino singular, Femenino singular, Masculino plural, Femenino plural
    "bueno"      "buena"      "buenos"     "buenas"
    "malo"       "mala"       "malos"      "malas"
    "grande"     "grande"     "grandes"    "grandes"
    "pequeño"    "pequeña"    "pequeños"   "pequeñas"
    "blanco"     "blanca"     "blancos"    "blancas"
    "negro"      "negra"      "negros"     "negras"
    "alto"       "alta"       "altos"      "altas"
    "bajo"       "baja"       "bajos"      "bajas"
    "viejo"      "vieja"      "viejos"     "viejas"
    "nuevo"      "nueva"      "nuevos"     "nuevas"
    "bonito"     "bonita"     "bonitos"    "bonitas"
    "feo"        "fea"        "feos"       "feas"
    "gordo"      "gorda"      "gordos"     "gordas"
    "delgado"    "delgada"    "delgados"   "delgadas"
    "rojo"       "roja"       "rojos"      "rojas"
    "azul"       "azul"       "azules"     "azules"
    "verde"      "verde"      "verdes"     "verdes"
    "amarillo"   "amarilla"   "amarillos"  "amarillas"
    "naranja"    "naranja"    "naranjas"   "naranjas"
    "morado"     "morada"     "morados"    "moradas"
    "rosa"       "rosa"       "rosas"      "rosas"
    "gris"       "gris"       "grises"     "grises"
    "marrón"     "marrón"     "marrones"   "marrones"
    "negro"      "negra"      "negros"     "negras"
    "blanco"     "blanca"     "blancos"    "blancas";

! Busca un adjetivo en la tabla de irregulares
[ BuscarAdjetivoIrregular adjetivo;
    local i;
    for (i=0: i<(AdjetivosIrregulares-->0)/4: i++) {
        if (CompararCadenas(adjetivo, AdjetivosIrregulares-->(i*4+1))) {
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

! ==============================================================================
!   Parte IV.   Funciones para concordar adjetivos
! ==============================================================================

! Concordar un adjetivo con un objeto según su género y número
[ ConcordarAdjetivo adjetivo obj;
    local es_plural = (obj has pluralname);
    local es_femenino = (obj has female);
    
    ! Verificar si es un adjetivo irregular
    local indice_irregular = BuscarAdjetivoIrregular(adjetivo);
    
    if (indice_irregular >= 0) {
        ! Es un adjetivo irregular, usar formas especiales
        if (es_femenino) {
            if (es_plural) {
                print (string) AdjetivosIrregulares-->(indice_irregular*4+4); ! Femenino plural
            } else {
                print (string) AdjetivosIrregulares-->(indice_irregular*4+2); ! Femenino singular
            }
        } else {
            if (es_plural) {
                print (string) AdjetivosIrregulares-->(indice_irregular*4+3); ! Masculino plural
            } else {
                print (string) AdjetivosIrregulares-->(indice_irregular*4+1); ! Masculino singular
            }
        }
        return true;
    }
    
    ! Es un adjetivo regular
    local tipo = DeterminarTipoAdjetivo(adjetivo);
    local len = adjetivo-->0;
    
    switch (tipo) {
        ADJ_O:
            if (es_femenino) {
                if (es_plural) {
                    ! Femenino plural: cambiar -o por -as
                    adjetivo->(len+1) = 0;
                    print (string) adjetivo, "as";
                } else {
                    ! Femenino singular: cambiar -o por -a
                    adjetivo->(len+1) = 0;
                    print (string) adjetivo, "a";
                }
            } else {
                if (es_plural) {
                    ! Masculino plural: cambiar -o por -os
                    adjetivo->(len+1) = 0;
                    print (string) adjetivo, "os";
                } else {
                    ! Masculino singular: mantener como está
                    print (string) adjetivo;
                }
            }
            
        ADJ_E, ADJ_CONS:
            if (es_plural) {
                ! Plural: añadir -es o -s según termine en consonante o vocal
                if (tipo == ADJ_E) {
                    print (string) adjetivo, "s";
                } else {
                    print (string) adjetivo, "es";
                }
            } else {
                ! Singular: mantener como está
                print (string) adjetivo;
            }
            
        ADJ_INVAR:
            ! Adjetivo invariable: mantener igual excepto en plural
            if (es_plural) {
                print (string) adjetivo, "s";
            } else {
                print (string) adjetivo;
            }
            
        default:
            print (string) adjetivo;
    }
    
    return true;
];

! ==============================================================================
!   Parte V.   Funciones de ayuda para mensajes
! ==============================================================================

! Función para imprimir un adjetivo concordado con un objeto
[ adj adjetivo obj;
    ConcordarAdjetivo(adjetivo, obj);
];

! Función para imprimir "está" + adjetivo concordado
[ esta_adj adjetivo obj;
    if (obj has pluralname) {
        print "están ";
    } else {
        print "está ";
    }
    ConcordarAdjetivo(adjetivo, obj);
];

! Función para imprimir "es" + adjetivo concordado
[ es_adj adjetivo obj;
    if (obj has pluralname) {
        print "son ";
    } else {
        print "es ";
    }
    ConcordarAdjetivo(adjetivo, obj);
];

! Función para imprimir "un/una/unos/unas" + adjetivo concordado
[ un_adj adjetivo obj;
    if (obj has female) {
        if (obj has pluralname) {
            print "unas ";
        } else {
            print "una ";
        }
    } else {
        if (obj has pluralname) {
            print "unos ";
        } else {
            print "un ";
        }
    }
    ConcordarAdjetivo(adjetivo, obj);
];

! Función para imprimir "el/la/los/las" + adjetivo concordado
[ el_adj adjetivo obj;
    if (obj has female) {
        if (obj has pluralname) {
            print "las ";
        } else {
            print "la ";
        }
    } else {
        if (obj has pluralname) {
            print "los ";
        } else {
            print "el ";
        }
    }
    ConcordarAdjetivo(adjetivo, obj);
];

! ==============================================================================
!   Fin del archivo
! ==============================================================================