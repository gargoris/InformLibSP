! ==============================================================================
! SPANISHCHARACTERSISO.H - Configuracion de caracteres espanoles usando ISO Latin-1
! Solucion completa usando codigos de caracteres validos para Inform 6
! ==============================================================================

System_file;

#Ifndef SPANISH_CHARACTERS_ISO_INCLUDED;
Constant SPANISH_CHARACTERS_ISO_INCLUDED;

! ==============================================================================
! TABLA DE CARACTERES ESPANOLES CON CODIGOS ISO LATIN-1
! ==============================================================================

! Inform 6 requiere codigos de caracteres especificos para caracteres no-ASCII
! Usamos los codigos ISO Latin-1 para caracteres espanoles

! Codigos de caracteres espanoles (ISO Latin-1)
Constant CHAR_a_acute = 225;    ! a
Constant CHAR_e_acute = 233;    ! e  
Constant CHAR_i_acute = 237;    ! i
Constant CHAR_o_acute = 243;    ! o
Constant CHAR_u_acute = 250;    ! u
Constant CHAR_n_tilde = 241;    ! n
Constant CHAR_u_diaeresis = 252; ! u
Constant CHAR_question_inverted = 191; ! ?
Constant CHAR_exclamation_inverted = 161; ! !

! Versiones mayusculas
Constant CHAR_A_acute = 193;    ! A
Constant CHAR_E_acute = 201;    ! E
Constant CHAR_I_acute = 205;    ! I
Constant CHAR_O_acute = 211;    ! O
Constant CHAR_U_acute = 218;    ! U
Constant CHAR_N_tilde = 209;    ! N
Constant CHAR_U_diaeresis = 220; ! U

! ==============================================================================
! DECLARACION DE CARACTERES PARA INFORM 6
! ==============================================================================

! Declarar que estos caracteres pueden ser usados
Zcharacter table_characters
  CHAR_a_acute CHAR_e_acute CHAR_i_acute CHAR_o_acute CHAR_u_acute
  CHAR_n_tilde CHAR_u_diaeresis CHAR_question_inverted CHAR_exclamation_inverted
  CHAR_A_acute CHAR_E_acute CHAR_I_acute CHAR_O_acute CHAR_U_acute 
  CHAR_N_tilde CHAR_U_diaeresis;

! ==============================================================================
! FUNCIONES DE UTILIDAD PARA CARACTERES
! ==============================================================================

! Convertir caracter acentuado a sin acento
[ SpanishRemoveAccent ch;
    switch(ch) {
        CHAR_a_acute: return 'a';
        CHAR_e_acute: return 'e';
        CHAR_i_acute: return 'i';
        CHAR_o_acute: return 'o';
        CHAR_u_acute: return 'u';
        CHAR_A_acute: return 'A';
        CHAR_E_acute: return 'E';
        CHAR_I_acute: return 'I';
        CHAR_O_acute: return 'O';
        CHAR_U_acute: return 'U';
        CHAR_n_tilde: return 'n';
        CHAR_N_tilde: return 'N';
        CHAR_u_diaeresis: return 'u';
        CHAR_U_diaeresis: return 'U';
        default: return ch;
    }
];

! Verificar si es vocal acentuada
[ SpanishIsAccentedVowel ch;
    switch(ch) {
        CHAR_a_acute, CHAR_e_acute, CHAR_i_acute, CHAR_o_acute, CHAR_u_acute: return true;
        CHAR_A_acute, CHAR_E_acute, CHAR_I_acute, CHAR_O_acute, CHAR_U_acute: return true;
        default: return false;
    }
];

! Verificar si es consonante especial
[ SpanishIsSpecialConsonant ch;
    switch(ch) {
        CHAR_n_tilde, CHAR_N_tilde, CHAR_u_diaeresis, CHAR_U_diaeresis: return true;
        default: return false;
    }
];

! ==============================================================================
! FUNCIONES DE IMPRESION SEGURA
! ==============================================================================

! Imprimir caracteres espanoles de forma segura
[ SpanishPrintChar ch;
    print (char) ch;
];

! Imprimir texto con acentos usando codigos
[ SpanishPrint str   i ch;
    for (i = 0 : i < str->0 : i++) {
        ch = str->(i+1);
        SpanishPrintChar(ch);
    }
];

! ==============================================================================
! MENSAJES CON CARACTERES SEGUROS
! ==============================================================================

! Versiones sin acentos para evitar problemas de compilacion
[ SpanishSafeMsg msg;
    switch(msg) {
        1: print "No puedes ir en esa direccion.";
        2: print "No ves nada especial.";
        3: print "Tomado.";
        4: print "No puedes tomar eso.";
        5: print "Soltado.";
        6: print "Ya tienes eso.";
        7: print "No entiendo esa orden.";
        8: print "No puedes hacer eso.";
        9: print "No hay nada aqui.";
        10: print "Eso no esta aqui.";
        11: print "Habitacion";
        12: print "nina"; ! nina
        13: print "nino"; ! nino  
        14: print "telefono"; ! telefono
        15: print "corazon"; ! corazon
        16: print "cancion"; ! cancion
        17: print "sillon"; ! sillon
        default: print "Mensaje ", msg;
    }
];

! ==============================================================================
! CONFIGURACION GLOBAL
! ==============================================================================

Global spanish_normalize_input = true;  ! Normalizar por defecto
Global spanish_use_accents = false;     ! No usar acentos en output por defecto

[ SpanishSetAccentMode mode;
    spanish_use_accents = mode;
    if (mode) {
        print "Modo de acentos ACTIVADO.^";
    } else {
        print "Modo de acentos DESACTIVADO (recomendado).^";
    }
];

[ SpanishSetNormalization mode;
    spanish_normalize_input = mode;
    if (mode) {
        print "Normalizacion de entrada ACTIVADA.^";
    } else {
        print "Normalizacion de entrada DESACTIVADA.^";
    }
];

[ SpanishCharacterInfo;
    print "^=== CONFIGURACION DE CARACTERES ESPANOLES ===^";
    print "Modo de acentos: ";
    if (spanish_use_accents) print "ACTIVADO"; else print "DESACTIVADO";
    print "^Normalizacion: ";
    if (spanish_normalize_input) print "ACTIVADA"; else print "DESACTIVADA";
    print "^";
    print "Caracteres soportados (solo entrada):^";
    print "- Vocales: a/A con acento^";
    print "- Consonantes: n con tilde^";
    print "- Signos: signos de interrogacion/exclamacion invertidos^";
    print "^Recomendacion: mantener acentos DESACTIVADOS para compatibilidad.^";
];

Constant SPANISH_CHARACTERS_ISO_COMPLETE;

#Endif; ! SPANISH_CHARACTERS_ISO_INCLUDED

! ==============================================================================
! Fin de SpanishCharactersISO.h
! ==============================================================================