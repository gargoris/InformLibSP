! ==============================================================================
! SPANISHCHARACTERS.H - Configuracion de caracteres espanoles para Inform 6
! Solucion completa para acentos, n y caracteres especiales
! ==============================================================================

System_file;

#Ifndef SPANISH_CHARACTERS_INCLUDED;
Constant SPANISH_CHARACTERS_INCLUDED;

! ==============================================================================
! TABLA DE CARACTERES ESPANOLES
! ==============================================================================

! Declarar caracteres espanoles como parte de Zcharacter
! Esto debe ir ANTES de cualquier uso de estos caracteres

Zcharacter 'a';
Zcharacter 'e';
Zcharacter 'i';
Zcharacter 'o';
Zcharacter 'u';
Zcharacter 'n';
Zcharacter 'u';
Zcharacter 'o';
Zcharacter '?';
Zcharacter '!';
Zcharacter 'A';
Zcharacter 'E';
Zcharacter 'I';
Zcharacter 'O';
Zcharacter 'U';
Zcharacter 'N';
Zcharacter 'U';

! ==============================================================================
! MAPEO DE CARACTERES PARA ENTRADA
! ==============================================================================

! Funcion para normalizar caracteres de entrada
[ SpanishNormalizeChar ch;
    switch(ch) {
        'a': return 'a';
        'e': return 'e';
        'i': return 'i';
        'o': return 'o';
        'u': return 'u';
        'n': return 'n';  ! o mantener como n
        'u': return 'u';
        'A': return 'A';
        'E': return 'E';
        'I': return 'I';
        'O': return 'O';
        'U': return 'U';
        'N': return 'N';
        'U': return 'U';
        default: return ch;
    }
];

! Funcion para procesar buffer de entrada y normalizar
[ SpanishNormalizeBuffer buffer len   i ch;
    for (i = 0 : i < len : i++) {
        ch = buffer->i;
        buffer->i = SpanishNormalizeChar(ch);
    }
    return len;
];

! ==============================================================================
! SIMBOLOS ESPECIALES PARA INTERFACES
! ==============================================================================

! Definir constantes para simbolos que podemos usar de forma segura
Constant SPANISH_CHECK_MARK = "[OK]";     ! En lugar de [OK]
Constant SPANISH_WARNING = "[!]";         ! En lugar de [!]  
Constant SPANISH_ERROR = "[X]";           ! En lugar de [X]
Constant SPANISH_BULLET = "-";            ! En lugar de -

! ==============================================================================
! FUNCIONES DE UTILIDAD PARA CARACTERES
! ==============================================================================

! Verificar si un caracter es una vocal acentuada
[ SpanishIsAccentedVowel ch;
    switch(ch) {
        'a', 'e', 'i', 'o', 'u': return true;
        'A', 'E', 'I', 'O', 'U': return true;
        default: return false;
    }
];

! Obtener la vocal sin acento
[ SpanishRemoveAccent ch;
    switch(ch) {
        'a': return 'a';
        'e': return 'e';
        'i': return 'i';
        'o': return 'o';
        'u': return 'u';
        'A': return 'A';
        'E': return 'E';
        'I': return 'I';
        'O': return 'O';
        'U': return 'U';
        default: return ch;
    }
];

! Verificar si es consonante especial espanola
[ SpanishIsSpecialConsonant ch;
    if (ch == 'n' || ch == 'N' || ch == 'u' || ch == 'U') return true;
    return false;
];

! Variable global para controlar normalizacion - debe declararse antes de uso
Global spanish_normalize_input = true;  ! Por defecto, normalizar

! ==============================================================================
! INTEGRACION CON EL PARSER
! ==============================================================================

! Funcion para preparar entrada del jugador
[ SpanishPreprocessInput buffer parse len   i;
    ! Normalizar caracteres si esta habilitado
    if (spanish_normalize_input) {
        len = SpanishNormalizeBuffer(buffer, len);
    }
    
    return len;
];

! ==============================================================================
! FUNCIONES DE CONFIGURACION
! ==============================================================================

[ SpanishSetNormalization mode;
    spanish_normalize_input = mode;
    if (mode) {
        print "Normalizacion de acentos activada.^";
    } else {
        print "Normalizacion de acentos desactivada.^";
    }
];

[ SpanishCharacterInfo;
    print "^=== CONFIGURACION DE CARACTERES ESPANOLES ===^";
    print "Caracteres soportados:^";
    print "- Vocales acentuadas: a, e, i, o, u^";
    print "- Consonantes especiales: n, u^";
    print "- Signos de puntuacion: ?, !^";
    print "^Normalizacion: ";
    if (spanish_normalize_input) print "ACTIVADA"; else print "DESACTIVADA";
    print "^";
    print "^Uso: 'acentos on/off' para cambiar normalizacion^";
];

Constant SPANISH_CHARACTERS_COMPLETE;

#Endif; ! SPANISH_CHARACTERS_INCLUDED

! ==============================================================================
! Fin de SpanishCharacters.h
! ==============================================================================