! ==============================================================================
!   SPANISHGRAMMAREXT:  Extensiones de gramática en español para Inform 6
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
!   Parte I.   Acciones para relaciones espaciales
! ==============================================================================

! Las implementaciones de estas acciones están en SpanishMessagesExt.h
! DropUnderSub: Acción para dejar algo debajo de otro objeto
! DropBehindSub: Acción para dejar algo detrás de otro objeto
! DropInFrontSub: Acción para dejar algo delante de otro objeto
! DropNearSub: Acción para dejar algo cerca de otro objeto

! ==============================================================================
!   Parte II.   Extensiones de gramática para verbos existentes
! ==============================================================================

Extend 'deja' 'suelta' 'tira'
    * noun 'sobre' noun                             -> PutOn
    * 'a//' noun 'sobre' noun                       -> PutOn
    * noun 'encima' 'de' noun                       -> PutOn
    * 'a//' noun 'encima' 'de' noun                 -> PutOn
    * noun 'debajo' 'de' noun                       -> DropUnder
    * 'a//' noun 'debajo' 'de' noun                 -> DropUnder
    * noun 'bajo' noun                              -> DropUnder
    * 'a//' noun 'bajo' noun                        -> DropUnder
    * noun 'detrás' 'de' noun                       -> DropBehind
    * 'a//' noun 'detrás' 'de' noun                 -> DropBehind
    * noun 'delante' 'de' noun                      -> DropInFront
    * 'a//' noun 'delante' 'de' noun                -> DropInFront
    * noun 'frente' 'a' noun                        -> DropInFront
    * 'a//' noun 'frente' 'a' noun                  -> DropInFront
    * noun 'cerca' 'de' noun                        -> DropNear
    * 'a//' noun 'cerca' 'de' noun                  -> DropNear
    * noun 'junto' 'a' noun                         -> DropNear
    * 'a//' noun 'junto' 'a' noun                   -> DropNear;

Extend 'pon' 'coloca' 'situa' 'sitúa'
    * noun 'debajo' 'de' noun                       -> DropUnder
    * 'a//' noun 'debajo' 'de' noun                 -> DropUnder
    * noun 'bajo' noun                              -> DropUnder
    * 'a//' noun 'bajo' noun                        -> DropUnder
    * noun 'detrás' 'de' noun                       -> DropBehind
    * 'a//' noun 'detrás' 'de' noun                 -> DropBehind
    * noun 'delante' 'de' noun                      -> DropInFront
    * 'a//' noun 'delante' 'de' noun                -> DropInFront
    * noun 'frente' 'a' noun                        -> DropInFront
    * 'a//' noun 'frente' 'a' noun                  -> DropInFront
    * noun 'cerca' 'de' noun                        -> DropNear
    * 'a//' noun 'cerca' 'de' noun                  -> DropNear
    * noun 'junto' 'a' noun                         -> DropNear
    * 'a//' noun 'junto' 'a' noun                   -> DropNear;

Extend 'mete' 'inserta' 'introduce'
    * noun 'debajo' 'de' noun                       -> DropUnder
    * 'a//' noun 'debajo' 'de' noun                 -> DropUnder
    * noun 'bajo' noun                              -> DropUnder
    * 'a//' noun 'bajo' noun                        -> DropUnder
    * noun 'detrás' 'de' noun                       -> DropBehind
    * 'a//' noun 'detrás' 'de' noun                 -> DropBehind;

! ==============================================================================
!   Parte III.   Nuevos verbos para relaciones espaciales
! ==============================================================================

Verb 'esconde'
    * noun                                          -> Drop
    * 'a//' noun                                    -> Drop
    * noun 'detrás' 'de' noun                       -> DropBehind
    * 'a//' noun 'detrás' 'de' noun                 -> DropBehind
    * noun 'debajo' 'de' noun                       -> DropUnder
    * 'a//' noun 'debajo' 'de' noun                 -> DropUnder;

Verb 'acerca'
    * noun 'a' noun                                 -> DropNear
    * 'a//' noun 'a' noun                           -> DropNear;

! ==============================================================================
!   Fin del archivo
! ==============================================================================