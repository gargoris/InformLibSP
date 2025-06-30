! ==============================================================================
!   SPANISHGENDER:  Funciones de género y número en español para Inform 6
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
!   Funciones auxiliares para manejar género y número en español
! ==============================================================================

! Funciones básicas de concordancia

! Imprime "es" o "son" según el número del objeto
[ es obj;
    if (obj has pluralname) print "son"; else print "es";
];

! Imprime "está" o "están" según el número del objeto
[ esta obj;
    if (obj has pluralname) print "están"; else print "está";
];

! Imprime "n" o nada según el número del objeto
[ n obj;
    if (obj has pluralname) print "n"; else print "";
];

! Imprime "s" o nada según el número del objeto
[ s obj;
    if (obj has pluralname) print "s"; else print "";
];

! Imprime "o" o "a" según el género del objeto
[ o obj;
    if (obj has female) print "a"; else print "o";
];

! Imprime "lo" o "la" según el género del objeto
[ lo obj;
    if (obj has female) print "la"; else print "lo";
];

! Imprime "el", "la", "los" o "las" según género y número
[ el obj;
    if (obj has female) {
        if (obj has pluralname) print "las";
        else print "la";
    } else {
        if (obj has pluralname) print "los";
        else print "el";
    }
];

! Imprime "un", "una", "unos" o "unas" según género y número
[ un obj;
    if (obj has female) {
        if (obj has pluralname) print "unas";
        else print "una";
    } else {
        if (obj has pluralname) print "unos";
        else print "un";
    }
];

! Imprime "te"
[ te;
    print "te";
];

! Funciones compuestas para frases preposicionales

! Imprime "del", "de la", "de los" o "de las" + nombre según género y número
[ del obj;
    if (obj has female) {
        if (obj has pluralname) print "de las ";
        else print "de la ";
    } else {
        if (obj has pluralname) print "de los ";
        else print "del ";
    }
    print (name) obj;
];

! Imprime "al", "a la", "a los" o "a las" + nombre según género y número
[ al obj;
    if (obj has female) {
        if (obj has pluralname) print "a las ";
        else print "a la ";
    } else {
        if (obj has pluralname) print "a los ";
        else print "al ";
    }
    print (name) obj;
];

! Imprime "en el", "en la", "en los" o "en las" + nombre según género y número
[ en_el obj;
    print "en ";
    if (obj has female) {
        if (obj has pluralname) print "las ";
        else print "la ";
    } else {
        if (obj has pluralname) print "los ";
        else print "el ";
    }
    print (name) obj;
];

! Imprime "por el", "por la", "por los" o "por las" + nombre según género y número
[ por_el obj;
    print "por ";
    if (obj has female) {
        if (obj has pluralname) print "las ";
        else print "la ";
    } else {
        if (obj has pluralname) print "los ";
        else print "el ";
    }
    print (name) obj;
];

! Imprime "sobre", "dentro", etc. según el tipo de objeto
[ contigo obj;
    if (obj has supporter) {
        print "sobre ";
        if (obj has female) {
            if (obj has pluralname) print "las ";
            else print "la ";
        } else {
            if (obj has pluralname) print "los ";
            else print "el ";
        }
        print (name) obj;
    } else {
        print "dentro ";
        if (obj has female) {
            if (obj has pluralname) print "de las ";
            else print "de la ";
        } else {
            if (obj has pluralname) print "de los ";
            else print "del ";
        }
        print (name) obj;
    }
];

! Funciones para participios y adjetivos comunes

! Imprime "abierto/a/os/as" según género y número
[ abierto obj;
    print "abiert";
    print (o) obj;
    print (s) obj;
];

! Imprime "cerrado/a/os/as" según género y número
[ cerrado obj;
    print "cerrad";
    print (o) obj;
    print (s) obj;
];

! Imprime "puesto/a/os/as" según género y número
[ puesto obj;
    print "puest";
    print (o) obj;
    print (s) obj;
];

! Imprime "vacío/a/os/as" según género y número
[ vacio obj;
    print "vací";
    print (o) obj;
    print (s) obj;
];

! Imprime "lleno/a/os/as" según género y número
[ lleno obj;
    print "llen";
    print (o) obj;
    print (s) obj;
];

! Imprime "bloqueado/a/os/as" según género y número
[ bloqueado obj;
    print "bloquead";
    print (o) obj;
    print (s) obj;
];

! Imprime "encendido/a/os/as" según género y número
[ encendido obj;
    print "encendid";
    print (o) obj;
    print (s) obj;
];

! Imprime "apagado/a/os/as" según género y número
[ apagado obj;
    print "apagad";
    print (o) obj;
    print (s) obj;
];

! Funciones para verbos comunes

! Imprime "está/están" + participio según género y número
[ esta_participio participio obj;
    if (obj has pluralname) print "están ";
    else print "está ";
    
    switch (participio) {
        'abierto': print (abierto) obj;
        'cerrado': print (cerrado) obj;
        'puesto': print (puesto) obj;
        'vacio': print (vacio) obj;
        'lleno': print (lleno) obj;
        'bloqueado': print (bloqueado) obj;
        'encendido': print (encendido) obj;
        'apagado': print (apagado) obj;
        default: print (string) participio;
    }
];

! Imprime "ha/han sido" + participio según género y número
[ ha_sido_participio participio obj;
    if (obj has pluralname) print "han sido ";
    else print "ha sido ";
    
    switch (participio) {
        'abierto': print (abierto) obj;
        'cerrado': print (cerrado) obj;
        'puesto': print (puesto) obj;
        'vacio': print (vacio) obj;
        'lleno': print (lleno) obj;
        'bloqueado': print (bloqueado) obj;
        'encendido': print (encendido) obj;
        'apagado': print (apagado) obj;
        default: print (string) participio;
    }
];

! Imprime "puede/pueden ser" + participio según género y número
[ puede_ser_participio participio obj;
    if (obj has pluralname) print "pueden ser ";
    else print "puede ser ";
    
    switch (participio) {
        'abierto': print (abierto) obj;
        'cerrado': print (cerrado) obj;
        'puesto': print (puesto) obj;
        'vacio': print (vacio) obj;
        'lleno': print (lleno) obj;
        'bloqueado': print (bloqueado) obj;
        'encendido': print (encendido) obj;
        'apagado': print (apagado) obj;
        default: print (string) participio;
    }
];

! ==============================================================================
!   Fin del archivo
! ==============================================================================