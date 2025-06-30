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
  Answer: switch(x1) {
    1: print_ret "No hay ninguna respuesta.";
  }
  
  Ask: switch(x1) {
    1: print_ret "No hay respuesta.";
    2: print_ret "No hay respuesta.";
  }
  
  AskFor: switch(x1) {
    1: print_ret "No puedes pedir eso.";
    2: print_ret "No hay respuesta.";
    3: print_ret "No hay respuesta.";
  }
  
  Attack: switch(x1) {
    1: print_ret "No tiene sentido atacar ", (the) x2, ".";
    2: print_ret "No estás en un estado combativo.";
    3: print_ret "No parece que atacar ", (the) x2, " vaya a servir de nada.";
  }
  
  Blow: switch(x1) {
    1: print_ret "No puedes soplar ", (the) x2, ".";
    2: print_ret "No conseguirás nada soplando ", (the) x2, ".";
    3: print_ret "No puedes soplar dentro de ", (the) x2, ".";
  }
  
  Burn: switch(x1) {
    1: print_ret "Este acto peligroso no conseguiría nada en cualquier caso.";
    2: print_ret "Este acto peligroso no conseguiría nada en cualquier caso.";
    3: print_ret "No puedes quemar ", (the) x2, ".";
  }
  
  Buy: switch(x1) {
    1: print_ret "No hay nada en venta.";
    2: print_ret "No ", (es) x2, " tuyo para comprar.";
  }
  
  Climb: switch(x1) {
    1: print_ret "No creo que ", (the) x2, " pueda", (n) x2, " ser escalado", (s) x2, ".";
    2: print_ret "No llegarías a ningún sitio.";
  }
  
  Close: switch(x1) {
    1: print_ret "No ", (es) x1, " algo que puedas cerrar.";
    2: print_ret "Ya está", (n) x1, " cerrado", (s) x1, ".";
    3: print_ret "Primero tendrías que ", (coge) x1, ".";
    4: print_ret "Cierras ", (the) x1, ".";
  }
  
  CommandsOff: switch (x1) {
    1: "[Grabación de órdenes finalizada.]";
    #Ifdef TARGET_GLULX;
    2: "[Grabación de órdenes ya estaba finalizada.]";
    #Endif; ! TARGET_
  }
  
  CommandsOn: switch (x1) {
    1: "[Grabación de órdenes activada.]";
    #Ifdef TARGET_GLULX;
    2: "[Órdenes grabándose en la tabla.]";
    3: "[Grabación de órdenes ya estaba activada.]";
    4: "[Grabación de órdenes falló.]";
    #Endif; ! TARGET_
  }
  
  CommandsRead: switch (x1) {
    1: "[Reproduciendo órdenes.]";
    #Ifdef TARGET_GLULX;
    2: "[Las órdenes ya están siendo reproducidas.]";
    3: "[Reproducción de órdenes finalizada.]";
    4: "[Reproducción de órdenes ya estaba finalizada.]";
    5: "[Reproducción de órdenes falló: no hay órdenes grabadas.]";
    6: "[Reproducción de órdenes falló.]";
    #Endif; ! TARGET_
  }
  
  Consult: switch (x1) {
    1: print "No descubres nada interesante en ";
       switch (x2) {
         0: print "eso.";
         1: print "ellos.";
         2: print "él.";
         3: print "ella.";
       }
       new_line;
       rtrue;
  }
  
  Cut: switch (x1) {
    1: print_ret "Cortando ", (the) x2, " no conseguirás gran cosa.";
    2: print_ret "No ", (es) x2, " algo que puedas cortar.";
  }
  
  Dig: switch (x1) {
    1: print_ret "No tiene sentido excavar en ", (the) x2, ".";
    2: print_ret "No ", (es) x2, " un lugar adecuado para excavar.";
  }
  
  Disrobe: switch (x1) {
    1: print_ret "No ", (te) "estás poniendo ", (the) x1, ".";
    2: print_ret (Te) "quitas ", (the) x1, ".";
  }
  
  Drink: switch (x1) {
    1: print_ret "Eso no parece potable.";
    2: print_ret "No hay nada que beber aquí.";
  }
  
  Drop: switch (x1) {
    1: print_ret "Para hacer eso, antes tienes que ", (coge) x1, ".";
    2: print_ret "No puedes dejar algo que forma parte de ti.";
    3: print_ret "No puedes dejar algo que está fijo en el sitio o que forma parte de algo.";
    4: print_ret "(Primero ", (te) "quitas ", (the) x1, ")";
    5: print_ret "Dejado.";
  }
  
  Eat: switch (x1) {
    1: print_ret "Eso no parece comestible.";
    2: print_ret (Te) "comes ", (the) x1, ". No está mal.";
  }
  
  EmptyT: switch (x1) {
    1: print_ret "No puedes vaciar ", (the) x1, ".";
    2: print_ret (The) x1, " ya está", (n) x1, " vacío", (s) x1, ".";
    3: print_ret (The) x1, " no puede", (n) x1, " contener cosas.";
    4: print_ret "No puedes vaciar algo sobre sí mismo.";
  }
  
  Empty: switch (x1) {
    1: print_ret "No puedes vaciar ", (the) x1, ".";
    2: print_ret (The) x1, " ya está", (n) x1, " vacío", (s) x1, ".";
    3: print_ret (The) x1, " no puede", (n) x1, " contener cosas.";
    4: print_ret "No puedes vaciar algo sobre sí mismo.";
  }
  
  Enter: switch (x1) {
    1: print "Pero ya estás ";
       if (x2 has supporter) print "sobre "; else print "en ";
       print_ret (the) x2, ".";
    2: switch (n) {
       1: print_ret "No puedes entrar en ", (the) x2, ".";
       2: print_ret "No puedes subir a ", (the) x2, ".";
       3: print_ret "No puedes meterte en ", (the) x2, ".";
       }
    3: print_ret "Tienes que ", (salte) "primero.";
    4: print_ret "No puedes entrar en algo que está ", (contigo), ".";
    5: print_ret "No puedes entrar en algo que está sobre ", (contigo), ".";
    6: print_ret "No puedes entrar en algo que está dentro de ", (contigo), ".";
    7: switch (n) {
       1: print_ret (Te) "metes en ", (the) x2, ".";
       2: print_ret (Te) "subes a ", (the) x2, ".";
       3: print_ret (Te) "metes en ", (the) x2, ".";
       }
  }
  
  Examine: switch (x1) {
    1: print_ret "Está demasiado oscuro. No puedes ver nada.";
    2: print_ret "No observas nada especial en ", (the) x1, ".";
    3: print_ret (The) x1, " está", (n) x1, " apagado", (s) x1, ".";
  }
  
  Exit: switch (x1) {
    1: print_ret "No estás en ningún sitio del que debas salir.";
    2: print_ret "No puedes salir de ", (the) x1, ".";
    3: print_ret (Te) "bajas de ", (the) x1, ".";
    4: print_ret (Te) "sales de ", (the) x1, ".";
  }
  
  Fill: switch (x1) {
    1: print_ret "No puedes llenar eso.";
    2: print_ret "Eso no puede contener líquidos.";
    3: print_ret (The) x1, " ya está", (n) x1, " lleno", (s) x1, ".";
    4: print_ret "No puedes llenar algo con sí mismo.";
    5: print_ret "No tienes nada con lo que llenar ", (the) x1, ".";
  }
  
  FullScore: switch (x1) {
    1: if (deadflag) print "La puntuación fue "; else print "La puntuación es ";
       "de ", score, " puntos de un total de ", MAX_SCORE,
       ", en ", turns, " turno";
       if (turns ~= 1) print "s";
       if (deadflag) print "."; else print ", hasta el momento.";
    2: "Ese modo de puntuación no está disponible.";
  }
  
  GetOff: print_ret (Te) "bajas de ", (the) x1, ".";
  
  Give: switch (x1) {
    1: print_ret "No tienes ", (the) x1, ".";
    2: print_ret (The) x1, " no está", (n) x1, " interesado", (s) x1, ".";
    3: print_ret "Mantienes ", (the) x1, " para ti.";
  }
  
  Go: switch (x1) {
    1: print_ret "Tienes que especificar en qué dirección ir.";
    2: print_ret "No puedes ir por ahí.";
    3: print_ret "Estás en ", (name) x2, ".";
    4: print_ret "No puedes ir porque ", (the) x2, " no lleva", (n) x2, " a ningún sitio.";
    5: print_ret "No puedes ir porque ", (the) x2, " está", (n) x2, " cerrad", (o) x2, ".";
    6: print_ret "No puedes, ya que ", (the) x2, " está", (n) x2, " en el camino.";
    7: print_ret "No puedes ir por ahí.";
  }
  
  GoIn: print_ret "No ves ninguna entrada obvia.";
  
  Hello: print_ret "No hay respuesta.";
  
  Inventory: switch (x1) {
    1: print_ret "No llevas nada.";
    2: print "Llevas";
    3: print ":^";
    4: print ".^";
  }
  
  Jump: print_ret "Saltas en el sitio, sin ningún resultado.";
  
  JumpOver,Tie:
    print_ret "No conseguirías nada así.";
  
  Kiss: print_ret "Mantente centrado.";
  
  Listen: print_ret "No escuchas nada fuera de lo común.";
  
  ListMiscellany: switch (x1) {
    1: print " (encendid", (o) x2, ")";
    2: print " (que está", (n) x2, " cerrad", (o) x2, ")";
    3: print " (cerrad", (o) x2, " y encendid", (o) x2, ")";
    4: print " (que está", (n) x2, " vacío", (s) x2, ")";
    5: print " (vacío", (s) x2, " y encendid", (o) x2, ")";
    6: print " (que está", (n) x2, " cerrad", (o) x2, " y vacío", (s) x2, ")";
    7: print " (cerrad", (o) x2, ", vacío", (s) x2, " y encendid", (o) x2, ")";
    8: print " (encendid", (o) x2, " y llevad", (o) x2, " puest", (o) x2;
    9: print " (encendid", (o) x2;
    10: print " (llevad", (o) x2, " puest", (o) x2;
    11: print " (que está", (n) x2, " ";
    12: print " (que ";
    13: print " (";
    14: print ", ";
    15: print " y ";
    16: print " (sobre ";
    17: print ", sobre ";
    18: print " (en ";
    19: print ", en ";
    20: print " (dentro de ";
    21: print ", dentro de ";
    22: print " (";
    23: print ")";
  }
  
  LMode1: print_ret " está ahora en modo ";
  LMode2: print_ret " está ahora en modo ";
  LMode3: print_ret " está ahora en modo ";
  
  Lock: switch (x1) {
    1: print_ret "No parece", (n) x1, " tener ningún tipo de cerrojo.";
    2: print_ret (The) x1, " ya está", (n) x1, " cerrad", (o) x1, " con llave.";
    3: print_ret "Primero tendrías que cerrar ", (the) x1, ".";
    4: print_ret "Eso no encaja con la cerradura.";
    5: print_ret (Te) "cierras ", (the) x1, " con llave.";
  }
  
  Look: switch (x1) {
    1: print " (sobre ", (the) x2, ")";
    2: print " (en ", (the) x2, ")";
    3: print " (dentro de ", (the) x2, ")";
    4: print " (como ", (object) x2, ")";
    5: print "^No ves nada especial en esa dirección.";
    6: print "Está demasiado oscuro. No puedes ver nada.";
    7: print "^", (The) x2;
    8: print "^En ", (the) x1;
    9: print "^Sobre ", (the) x1;
    10: print "^No puedes ver lo que hay dentro ", (del) x1, " porque está", (n) x1, " cerrad", (o) x1, ".";
    11: print "^";
    12: print "^No hay nada sobre ", (the) x1, ".";
    13: print "^No hay nada dentro ", (del) x1, ".";
    14: print "^En este lugar hay:";
    15: print "^";
    16: print "^Está demasiado oscuro para ver algo.";
  }
  
  LookUnder: switch (x1) {
    1: print_ret "Pero está demasiado oscuro para ver algo.";
    2: print_ret "No ves nada especial debajo ", (del) x1, ".";
  }
  
  Mild: print_ret "Bastante.";
  
  Miscellany: switch (x1) {
    1: print "^¡No ha ocurrido nada!^";
    2: print "^No lo entiendo.^";
    3: print "^¡Has muerto!^";
    4: print "^Has ganado^";
    5: print "^¿Quieres reiniciar el juego? ";
    6: print "^¿Quieres restaurar una partida guardada? ";
    7: print "^¿Estás seguro? ";
    8: print "^Por favor, responde sí o no.^";
    9: print "^Por favor, da una de las respuestas anteriores.^";
    10: print "^Para repetir un comando como ~norte~, escribe ~repetir~, no ~repetir norte~.^";
    11: print "^No puedes deshacer algo que no has hecho.^";
    12: print "^No puedes deshacer más.^";
    13: print "^Acción desecha.^";
    14: print "^Perdón.^";
    15: print "^Está demasiado oscuro para ver algo.^";
    16: print "^Creo que debes hablarme más claramente.^";
    17: print "^No puedes hablar con ", (the) x2, ".^";
    18: print "^Para hablar con alguien intenta ~alguien, hola~ o algo así.^";
    19: if (x2 has female) print "^No tienes por qué usar la palabra ~ella~: puedes simplemente dar órdenes.^";
        else               print "^No tienes por qué usar la palabra ~él~: puedes simplemente dar órdenes.^";
    20: print "^Para ver lo que tienes, escribe ~inventario~.^";
    21: print "^No has especificado suficiente información.^";
    22: print "^No has especificado un objeto.^";
    23: print "^No puedes especificar más de un objeto con ese verbo.^";
    24: print "^No puedes usar múltiples objetos con ese verbo.^";
    25: print "^Sólo puedes usar múltiples objetos una vez en una acción.^";
    26: print "^Sólo entendí lo que querías hacer con ", (the) x2, ".^";
    27: print "^No entiendo a qué te refieres con ~", (address) x2, "~.^";
    28: print "^No entendí esa frase.^";
    29: print "^No veo eso, que yo sepa.^";
    30: print "^No puedes ver ~", (address) x2, "~ (", (the) x3, ") en este momento.^";
    31: print "^No puedes ver ~", (address) x2, "~ (", (the) x3, ") en este momento.^";
    32: print "^No tienes ~", (address) x2, "~ (", (the) x3, ").^";
    33: print "^No puedes usar el artículo ~", (address) x2, "~ con ese verbo.^";
    34: print "^Sólo puedes hacer eso con seres animados.^";
    35: print "^No tengo claro a qué ~", (address) x2, "~ te refieres.^";
    36: print "^Has usado la palabra ~", (address) x2, "~ en un contexto que no entiendo.^";
    37: print "^Ese comando sólo tiene sentido cuando le hablas a alguien.^";
    38: print "^No puedes hablar con ", (the) x2, ".^";
    39: print "^Para hablar con alguien intenta ~alguien, hola~ o algo así.^";
    40: print "^Para responder a alguien intenta ~respuesta, hola~.^";
    41: print "^Para hacer una pregunta a alguien intenta ~alguien, ¿dónde está oro?~ o algo así.^";
    42: print "^No tienes por qué referirte a objetos que no son importantes.^";
    43: print "^No entiendo ese número.^";
    44: print "^No puedes ver lo que hay dentro ", (del) x2, " porque está", (n) x2, " cerrad", (o) x2, ".^";
    45: print "^No puedes ver lo que hay dentro ", (del) x2, " porque está", (n) x2, " cerrad", (o) x2, ".^";
    46: print "^No está disponible.^";
    47: print "^Está demasiado oscuro.^";
    48: print "^", (The) x2, " no está", (n) x2, " disponible", (s) x2, ".^";
    49: print "^No está disponible.^";
    50: print "^No está disponible.^";
    51: print "^No está disponible.^";
    52: print "^No está disponible.^";
    53: print "^No está disponible.^";
    54: print "^No está disponible.^";
    55: print "^No está disponible.^";
    56: print "^Te refieres a ", (the) x2, "?^";
    57: print "^No puedo ayudarte con eso.^";
    58: print "^No puedo ver lo que hay dentro a menos que mires dentro o busques.^";
    59: print "^No puedes ver lo que hay dentro ", (del) x2, ".^";
    60: print "^No está disponible.^";
    61: print "^No está disponible.^";
    62: print "^No está disponible.^";
    63: print "^No está disponible.^";
  }
  
  No: print_ret "De acuerdo.";
  
  NotifyOff: print_ret "[Notificación de puntuación desactivada.]";
  
  NotifyOn: print_ret "[Notificación de puntuación activada.]";
  
  Objects: switch (x1) {
    1: print "Objetos que has manejado:^";
    2: print "Ninguno.";
    3: print " (puesto)";
    4: print " (dentro de ", (name) x2, ")";
    5: print " (en ", (name) x2, ")";
    6: print " (sobre ", (name) x2, ")";
    7: print " (perdido)";
  }
  
  Open: switch (x1) {
    1: print_ret "No puedes abrir ", (the) x1, ".";
    2: print_ret (The) x1, " ya está", (n) x1, " abierto", (s) x1, ".";
    3: print_ret (The) x1, " está", (n) x1, " cerrado", (s) x1, " con llave.";
    4: print_ret "Abres ", (the) x1, ", descubriendo ";
    5: print_ret "Abres ", (the) x1, ".";
    6: print_ret (The) x1, " se abre.";
  }
  
  Order: print_ret (The) x1, " tiene", (n) x1, " mejores cosas que hacer.";
  
  Places: switch (x1) {
    1: print "Has visitado: ";
    2: print ".^";
  }
  
  Pray: print_ret "No ocurre nada obvio.";
  
  Prompt: print "^>";
  
  Pronouns: switch (x1) {
    1: print "En este momento, ";
    2: print "significa ";
    3: print "no está definido";
    4: print "él: ";
    5: print "ella: ";
    6: print "ello: ";
    7: print "ellos: ";
    8: print "todo: ";
    9: print ".^";
  }
  
  Pull,Push,Turn: switch (x1) {
    1: print_ret "Está fijo en el sitio.";
    2: print_ret "No ", (es) x1, " algo que puedas mover.";
    3: print_ret "No ocurre nada, aparentemente.";
  }
  
  PushDir: switch (x1) {
    1: print_ret "No es una dirección en la que puedas empujar ", (the) x2, ".";
    2: print_ret "No puedes empujar ", (the) x2, " en esa dirección.";
    3: print_ret "No puedes empujar ", (the) x2, " desde aquí.";
  }
  
  PutOn: switch (x1) {
    1: print_ret "Necesitas tener ", (the) x1, " para poder poner", (lo) x1, " sobre algo.";
    2: print_ret "No puedes poner algo sobre sí mismo.";
    3: print_ret "Poner cosas sobre ", (the) x1, " no serviría de nada.";
    4: print_ret "No tienes ", (the) x1, ".";
    5: print_ret "No puedes poner ", (the) x1, " sobre ", (the) x2, " porque ", (the) x1, " está", (n) x1, " ";
       switch (n) {
         1: "cerrad", (o) x1, ".";
         2: "encendid", (o) x1, ".";
         3: "cerrad", (o) x1, " y encendid", (o) x1, ".";
       }
    6: print_ret "No hay sitio en ", (the) x2, " para poner nada más.";
    7: print_ret "Hecho.";
    8: print_ret "Colocas ", (the) x1, " sobre ", (the) x2, ".";
  }
  
  Quit: switch (x1) {
    1: print "Por favor, responde sí o no.";
    2: print "¿Estás seguro de que quieres abandonar el juego? ";
  }
  
  Remove: switch (x1) {
    1: print_ret "No está ahí ahora.";
    2: print_ret "No está", (n) x1, " dentro ", (del) x2, ".";
    3: print_ret (The) x1, " está", (n) x1, " cerrad", (o) x1, ".";
    4: print_ret "Sacas ", (the) x1, " ", (del) x2, ".";
  }
  
  Restart: switch (x1) {
    1: print "¿Estás seguro de que quieres reiniciar el juego? ";
    2: print "Error al reiniciar.^";
  }
  
  Restore: switch (x1) {
    1: print "Error al restaurar.^";
    2: print "Ok.^";
  }
  
  Rub: print_ret "No consigues nada frotando ", (the) x1, ".";
  
  Save: switch (x1) {
    1: print "Error al guardar.^";
    2: print "Ok.^";
  }
  
  Score: switch (x1) {
    1: if (deadflag) print "En este juego tu puntuación fue "; else print "En este juego tu puntuación es ";
       print score, " de un máximo de ", MAX_SCORE, ", en ", turns, " turno";
       if (turns ~= 1) print "s";
       return;
    2: print "Tu puntuación ha aumentado en ", x2, " punto";
       if (x2 ~= 1) print "s";
       return;
    3: print "Tu puntuación ha disminuido en ", x2, " punto";
       if (x2 ~= 1) print "s";
       return;
  }
  
  ScriptOff: switch (x1) {
    1: print_ret "Transcripción finalizada.";
    2: print_ret "Intento fallido de finalizar la transcripción.";
    3: print_ret "La transcripción ya estaba finalizada.";
  }
  
  ScriptOn: switch (x1) {
    1: print_ret "Iniciando transcripción de...";
    2: print_ret "Intento fallido de iniciar transcripción.";
    3: print_ret "La transcripción ya estaba iniciada.";
  }
  
  Search: switch (x1) {
    1: print_ret "Pero está demasiado oscuro para ver algo.";
    2: print_ret "No hay nada sobre ", (the) x1, ".";
    3: print_ret "En ", (the) x1, " ves ";
    4: print_ret "No encuentras nada interesante.";
    5: print_ret "No puedes ver dentro ", (del) x1, " porque está", (n) x1, " cerrad", (o) x1, ".";
    6: print_ret (The) x1, " está", (n) x1, " vacío", (s) x1, ".";
    7: print_ret "En ", (the) x1, " ves ";
  }
  
  Set: print_ret "No, no puedes ajustar ", (the) x1, ".";
  
  SetTo: print_ret "No, no puedes ajustar ", (the) x1, " a nada.";
  
  Show: switch (x1) {
    1: print_ret "No tienes ", (the) x1, ".";
    2: print_ret (The) x2, " no muestra", (n) x2, " ningún interés.";
  }
  
  Sing: print_ret "Cantas fatal.";
  
  Sleep: print_ret "No estás especialmente somnoliento.";
  
  Smell: print_ret "No hueles nada extraño.";
  
  Sorry: print_ret "Oh, no es necesario que te disculpes.";
  
  Squeeze: switch (x1) {
    1: print_ret "Guarda las manos para ti.";
    2: print_ret "No consigues nada haciendo eso.";
  }
  
  Strong: print_ret "Los verdaderos aventureros no usan ese tipo de lenguaje.";
  
  Swim: print_ret "No hay agua suficiente en la que nadar.";
  
  Swing: print_ret "No es algo que puedas balancear.";
  
  SwitchOff: switch (x1) {
    1: print_ret "No es algo que puedas apagar.";
    2: print_ret (The) x1, " ya está", (n) x1, " apagad", (o) x1, ".";
    3: print_ret "Apagas ", (the) x1, ".";
  }
  
  SwitchOn: switch (x1) {
    1: print_ret "No es algo que puedas encender.";
    2: print_ret (The) x1, " ya está", (n) x1, " encendid", (o) x1, ".";
    3: print_ret "Enciendes ", (the) x1, ".";
  }
  
  Take: switch (x1) {
    1: print_ret "Tomado.";
    2: print_ret "Ya tienes ", (the) x1, ".";
    3: print_ret (The) x1, " parece", (n) x1, " pertenecer ", (al) x2, ".";
    4: print_ret (The) x1, " está", (n) x1, " fij", (o) x1, " en el sitio.";
    5: print_ret "Ya tienes ", (the) x1, ".";
    6: print_ret "Eso parece ser parte ", (del) x1, ".";
    7: print_ret "No es algo que puedas llevarte.";
    8: print_ret (The) x1, " no está", (n) x1, " disponible", (s) x1, ".";
    9: print_ret (The) x1, " no está", (n) x1, " disponible", (s) x1, ".";
    10: print_ret "Tendrías que ", (coge) x1, " primero.";
    11: print_ret "Tendrías que quitarte ", (the) x1, " primero.";
    12: print_ret "Tendrías que salir ", (del) x1, " primero.";
    13: print_ret "No puedes coger ", (the) x1, ".";
  }
  
  Taste: print_ret "No saboreas nada inesperado.";
  
  Tell: switch (x1) {
    1: print_ret "Hablas ", (contigo), " mismo.";
    2: print_ret "No provocas ninguna reacción.";
  }
  
  Think: print_ret "Vaya idea más interesante.";
  
  ThrowAt: switch (x1) {
    1: print_ret "No serviría de nada.";
    2: print_ret "En el último momento te echas atrás.";
  }
  
  ThrownAt: switch (x1) {
    1: print_ret "No puedes hacer eso.";
    2: print_ret (The) x1, " no", (es) x1, " un proyectil.";
  }
  
  Tie: print_ret "No puedes atar ", (the) x1, " a nada.";
  
  Touch: switch (x1) {
    1: print_ret "Guarda las manos para ti.";
    2: print_ret "No notas nada extraño al tacto.";
    3: print_ret "No creo que ", (al) x1, " le", (s) x1, " guste.";
  }
  
  Turn: switch (x1) {
    1: print_ret "No ocurre nada.";
    2: print_ret "No es algo que puedas girar.";
  }
  
  Unlock: switch (x1) {
    1: print_ret "No parece", (n) x1, " tener cerradura.";
    2: print_ret (The) x1, " ya tiene", (n) x1, " abierta la cerradura.";
    3: print_ret "Eso no encaja con la cerradura.";
    4: print_ret "Quitas el cerrojo ", (al) x1, ".";
  }
  
  VagueGo: print_ret "Tienes que especificar en qué dirección ir.";
  
  Verify: switch (x1) {
    1: print_ret "El fichero de juego ha verificado correctamente.";
    2: print_ret "El fichero de juego no ha verificado correctamente, y puede estar corrupto (aunque a veces esto falla).";
  }
  
  Version: print_ret "Librería ", (string) LibRelease, " / Inform v", (string) NI_BUILD_COUNT, " (Español)";
  
  Wait: print_ret "Pasa el tiempo...";
  
  Wake: print_ret "La cruda realidad es que esto no es un sueño.";
  
  WakeOther: print_ret "No parece necesario hacer eso.";
  
  Wave: switch (x1) {
    1: print_ret "No tienes ", (the) x1, ".";
    2: print_ret (Te) "sientes ridículo agitando ", (the) x1, ".";
  }
  
  WaveHands: print_ret (Te) "sientes ridículo agitando las manos.";
  
  Wear: switch (x1) {
    1: print_ret "No puedes ponerte eso.";
    2: print_ret "No tienes ", (the) x1, ".";
    3: print_ret "Ya ", (te) "estás vistiendo ", (the) x1, ".";
    4: print_ret (Te) "pones ", (the) x1, ".";
  }
  
  Yes: print_ret "De acuerdo.";
];

[ LanguageDirection d;
    switch (d) {
      n_to:    print "norte";
      s_to:    print "sur";
      e_to:    print "este";
      w_to:    print "oeste";
      ne_to:   print "noreste";
      nw_to:   print "noroeste";
      se_to:   print "sureste";
      sw_to:   print "suroeste";
      u_to:    print "arriba";
      d_to:    print "abajo";
      in_to:   print "dentro";
      out_to:  print "fuera";
      default: return RunTimeError(9,d);
    }
];

[ LanguageNumber n f;
    if (n == 0)    { print "cero"; rfalse; }
    if (n < 0)     { print "menos "; n = -n; }
    if (n >= 1000) { print (LanguageNumber) n/1000, " mil"; n = n%1000; f = 1; }
    if (n >= 100)  {
        if (f == 1) print " ";
        switch (n/100) {
          1: print "cien";
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
        if (n ~= 0) {
            if (n < 10) print "to "; else print " ";
        }
        f = 1;
    }
    if (n == 0) rfalse;
    
    if (f == 1) print " ";
    
    switch (n) {
      1:    print "uno";
      2:    print "dos";
      3:    print "tres";
      4:    print "cuatro";
      5:    print "cinco";
      6:    print "seis";
      7:    print "siete";
      8:    print "ocho";
      9:    print "nueve";
      10:   print "diez";
      11:   print "once";
      12:   print "doce";
      13:   print "trece";
      14:   print "catorce";
      15:   print "quince";
      16:   print "dieciséis";
      17:   print "diecisiete";
      18:   print "dieciocho";
      19:   print "diecinueve";
      20:   print "veinte";
      21:   print "veintiuno";
      22:   print "veintidós";
      23:   print "veintitrés";
      24:   print "veinticuatro";
      25:   print "veinticinco";
      26:   print "veintiséis";
      27:   print "veintisiete";
      28:   print "veintiocho";
      29:   print "veintinueve";
      30 to 99: switch (n/10) {
        3:  print "treinta";
        4:  print "cuarenta";
        5:  print "cincuenta";
        6:  print "sesenta";
        7:  print "setenta";
        8:  print "ochenta";
        9:  print "noventa";
        }
        if (n%10 ~= 0) print " y ", (LanguageNumber) n%10;
    }
];

[ LanguageTimeOfDay hours mins i;
    i = hours%12;
    if (i == 0) i = 12;
    if (i < 10) print " ";
    print i, ":", mins/10, mins%10;
    if ((hours/12) > 0) print " pm"; else print " am";
];

[ LanguageVerb i;
    switch (i) {
      'i//','inv','inventario':
               print "hacer inventario";
      'l//':   print "mirar";
      'x//':   print "examinar";
      'z//':   print "esperar";
! CompassDirection
      'n//':   print "norte";
      's//':   print "sur";
      'e//':   print "este";
      'o//':   print "oeste";
      'ne//':   print "noreste";
      'no//':   print "noroeste";
      'se//':   print "sureste";
      'so//':   print "suroeste";
      default: rfalse;
    }
    rtrue;
];

#Ifdef DEBUG;
[ LanguageVerbIsDebugging w;
    if (w == 'purloin' or 'tree' or 'abstract'
                       or 'gonear' or 'scope' or 'showobj')
        rtrue;
    rfalse;
];
#Endif;

[ LanguageVerbLikesAdverb w;
    if (w == 'mirar' or 'ir' or 'correr' or 'salir' or 'l//' or 'empujar' or 'caminar')
        rtrue;
    rfalse;
];

[ LanguageVerbMayBeName w;
    if (w == 'examinar' or 'x//' or 'mirar' or 'l//' or 'consultar')
        rtrue;
    rfalse;
];

[ es obj;
    if (obj has pluralname) print "son"; else print "es";
];

[ n obj;
    if (obj has female) print "a"; else print "o";
];

[ s obj;
    if (obj has pluralname) print "s"; else print "";
];

[ o obj;
    if (obj has female) print "a"; else print "o";
];

[ lo obj;
    if (obj has female) {
        if (obj has pluralname) print "las"; else print "la";
    } else {
        if (obj has pluralname) print "los"; else print "lo";
    }
];

[ al obj;
    if (obj has female) {
        if (obj has pluralname) print "a las"; else print "a la";
    } else {
        if (obj has pluralname) print "a los"; else print "al";
    }
];

[ del obj;
    if (obj has female) {
        if (obj has pluralname) print "de las"; else print "de la";
    } else {
        if (obj has pluralname) print "de los"; else print "del";
    }
];

[ coge obj;
    if (obj has female) {
        if (obj has pluralname) print "cogerlas"; else print "cogerla";
    } else {
        if (obj has pluralname) print "cogerlos"; else print "cogerlo";
    }
];

[ salte;
    if (actor == player) print "salir"; else print "salga";
];

[ te;
    if (actor == player) print "te"; else print "se";
];

[ Te;
    if (actor == player) print "Te"; else print "Se";
];

[ contigo;
    if (actor == player) print "contigo"; else print "con sí mismo";
];

[ conmigo;
    if (actor == player) print "conmigo"; else print "consigo";
];

[ The obj;
    if (obj has proper) {
        print (name) obj;
        return;
    }
    if (obj has female) {
        if (obj has pluralname) print "Las "; else print "La ";
    } else {
        if (obj has pluralname) print "Los "; else print "El ";
    }
    print (name) obj;
];

[ the obj;
    if (obj has proper) {
        print (name) obj;
        return;
    }
    if (obj has female) {
        if (obj has pluralname) print "las "; else print "la ";
    } else {
        if (obj has pluralname) print "los "; else print "el ";
    }
    print (name) obj;
];

[ ThatorThose obj;
    if (obj has pluralname) {
        print "esos ";
        if (obj has female) print "objetos"; else print "objetos";
    } else {
        print "ese ";
        if (obj has female) print "objeto"; else print "objeto";
    }
];

[ thatorthose obj;
    if (obj has pluralname) {
        print "esos ";
        if (obj has female) print "objetos"; else print "objetos";
    } else {
        print "ese ";
        if (obj has female) print "objeto"; else print "objeto";
    }
];

[ ItorThem obj;
    if (obj has pluralname) {
        if (obj has female) print "Ellas"; else print "Ellos";
    } else {
        if (obj has female) print "Ella"; else print "Él";
    }
];

[ itorthem obj;
    if (obj has pluralname) {
        if (obj has female) print "ellas"; else print "ellos";
    } else {
        if (obj has female) print "ella"; else print "él";
    }
];

[ InsideorOn obj;
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

#Endif;

! ==============================================================================