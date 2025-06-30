! ==============================================================================
!   SPANISHMESSAGESEXT:  Mensajes adicionales en español para la librería Inform 6
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
!   Mensajes para acciones espaciales
! ==============================================================================

[ LanguageLMExt n x1 x2;
  DropUnder, DropBehind, DropInFront, DropNear:

  switch(n) {
    DropUnder:
        switch(x1) {
          1: print_ret "No puedes poner algo debajo de sí mismo.";
          2: print_ret "No tienes ", (the) x2, ".";
          3: print_ret "No puedes poner nada debajo de ti mismo.";
          4: print_ret "No puedes poner nada debajo de ", (the) x2, ".";
          5: print_ret "No puedes poner nada debajo de algo que no está en el suelo.";
          6: print_ret "Dejas ", (the) x1, " debajo ", (del) x2, ".";
        }
        
    DropBehind:
        switch(x1) {
          1: print_ret "No puedes poner algo detrás de sí mismo.";
          2: print_ret "No tienes ", (the) x2, ".";
          3: print_ret "No puedes poner nada detrás de ti mismo.";
          4: print_ret "No puedes poner nada detrás de ", (the) x2, ".";
          5: print_ret "No puedes poner nada detrás de algo que no está en el suelo.";
          6: print_ret "Dejas ", (the) x1, " detrás ", (del) x2, ".";
        }
        
    DropInFront:
        switch(x1) {
          1: print_ret "No puedes poner algo delante de sí mismo.";
          2: print_ret "No tienes ", (the) x2, ".";
          3: print_ret "No puedes poner nada delante de ti mismo.";
          4: print_ret "No puedes poner nada delante de ", (the) x2, ".";
          5: print_ret "No puedes poner nada delante de algo que no está en el suelo.";
          6: print_ret "Dejas ", (the) x1, " delante ", (del) x2, ".";
        }
        
    DropNear:
        switch(x1) {
          1: print_ret "No puedes poner algo cerca de sí mismo.";
          2: print_ret "No tienes ", (the) x2, ".";
          3: print_ret "No puedes poner nada cerca de ti mismo.";
          4: print_ret "No puedes poner nada cerca de algo que no está en el suelo.";
          5: print_ret "Dejas ", (the) x1, " cerca ", (del) x2, ".";
        }
  }
];

! ==============================================================================
!   Reemplazos de mensajes para acciones espaciales
! ==============================================================================

[ DropUnderSub;
    if (noun == second) return LanguageLMExt(##DropUnder, 1);
    if (parent(noun) ~= player) return LanguageLMExt(##DropUnder, 2, noun);
    if (second == player) return LanguageLMExt(##DropUnder, 3);
    if (second has animate) return LanguageLMExt(##DropUnder, 4, second);
    if (parent(second) ~= location) return LanguageLMExt(##DropUnder, 5);
    
    move noun to location;
    return LanguageLMExt(##DropUnder, 6, noun, second);
];

[ DropBehindSub;
    if (noun == second) return LanguageLMExt(##DropBehind, 1);
    if (parent(noun) ~= player) return LanguageLMExt(##DropBehind, 2, noun);
    if (second == player) return LanguageLMExt(##DropBehind, 3);
    if (second has animate) return LanguageLMExt(##DropBehind, 4, second);
    if (parent(second) ~= location) return LanguageLMExt(##DropBehind, 5);
    
    move noun to location;
    return LanguageLMExt(##DropBehind, 6, noun, second);
];

[ DropInFrontSub;
    if (noun == second) return LanguageLMExt(##DropInFront, 1);
    if (parent(noun) ~= player) return LanguageLMExt(##DropInFront, 2, noun);
    if (second == player) return LanguageLMExt(##DropInFront, 3);
    if (second has animate) return LanguageLMExt(##DropInFront, 4, second);
    if (parent(second) ~= location) return LanguageLMExt(##DropInFront, 5);
    
    move noun to location;
    return LanguageLMExt(##DropInFront, 6, noun, second);
];

[ DropNearSub;
    if (noun == second) return LanguageLMExt(##DropNear, 1);
    if (parent(noun) ~= player) return LanguageLMExt(##DropNear, 2, noun);
    if (second == player) return LanguageLMExt(##DropNear, 3);
    if (parent(second) ~= location) return LanguageLMExt(##DropNear, 4);
    
    move noun to location;
    return LanguageLMExt(##DropNear, 5, noun, second);
];

! ==============================================================================
!   Fin del archivo
! ==============================================================================