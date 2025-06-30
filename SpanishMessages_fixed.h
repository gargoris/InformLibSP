! ==============================================================================
!   SPANISHMESSAGES:  Mensajes en español para la librería Inform 6
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

#Ifndef LIBRARY_MESSAGES;

Constant LIBRARY_MESSAGES = 1;

#Ifdef TARGET_ZCODE;
[ SpanishLibraryExtensions;
  #Ifdef LIBRARY_PARSER; SpanishLibraryExtensions(); #Endif;
  #Ifdef LIBRARY_VERBLIB; SpanishLibraryExtensions(); #Endif;
];
#Endif; ! TARGET_ZCODE

#Ifdef TARGET_GLULX;
[ SpanishLibraryExtensions;
  #Ifdef LIBRARY_PARSER; SpanishLibraryExtensions(); #Endif;
  #Ifdef LIBRARY_VERBLIB; SpanishLibraryExtensions(); #Endif;
];
#Endif; ! TARGET_GLULX

[ LanguageLM n x1 x2;
  Answer, Ask, AskFor, Attack, Blow, Burn, Buy, Climb, Close, CommandsOff,
  CommandsOn, CommandsRead, Consult, Cut, Dig, Disrobe, Drink, Drop, Eat,
  Empty, EmptyT, Enter, Examine, Exit, Fill, FullScore, GetOff, Give, Go,
  GoIn, Hello, Inventory, Jump, JumpOver, Kiss, Listen, ListMiscellany,
  LMode1, LMode2, LMode3, Lock, Look, LookUnder, Mild, Miscellany, No,
  NotifyOff, NotifyOn, Objects, Open, Order, Places, Pray, Prompt, Pronouns,
  Pull, Push, PushDir, PutOn, Quit, Restart, Restore, Rub, Save, Score,
  ScriptOff, ScriptOn, Search, Set, SetTo, Show, Sing, Sleep, Smell, Sorry,
  Squeeze, Strong, Swim, Swing, SwitchOff, SwitchOn, Take, Taste, Tell,
  Think, ThrowAt, ThrownAt, Tie, Touch, Turn, Unlock, VagueGo, Verify,
  Version, Wait, Wake, WakeOther, Wave, WaveHands, Wear, Yes:

  switch(n) {