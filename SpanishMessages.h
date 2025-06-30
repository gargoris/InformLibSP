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

Constant LibraryMessages = 1;

#Ifdef TARGET_ZCODE;
[ LibraryExtensions;
  #Ifdef LIBRARY_PARSER; LibraryExtensions(); #Endif;
  #Ifdef LIBRARY_VERBLIB; LibraryExtensions(); #Endif;
];
#Endif; ! TARGET_ZCODE

#Ifdef TARGET_GLULX;
[ LibraryExtensions;
  #Ifdef LIBRARY_PARSER; LibraryExtensions(); #Endif;
  #Ifdef LIBRARY_VERBLIB; LibraryExtensions(); #Endif;
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
    Answer:
        switch(x1) {
          1: print_ret "No hay ninguna respuesta.";
        }

    Ask:
        switch(x1) {
          1: print_ret "No hay respuesta.";
          2: print_ret "No hay respuesta.";
        }

    AskFor:
        switch(x1) {
          1: print_ret "No puedes pedir eso.";
          2: print_ret "No hay respuesta.";
          3: print_ret "No hay respuesta.";
        }

    Attack:
        switch(x1) {
          1: print_ret "No tiene sentido atacar ", (the) x2, ".";
          2: print_ret "No estás en un estado combativo.";
          3: print_ret "No parece que atacar ", (the) x2, " vaya a servir de nada.";
        }

    Blow:
        switch(x1) {
          1: print_ret "No puedes soplar ", (the) x2, ".";
          2: print_ret "No conseguirás nada soplando ", (the) x2, ".";
          3: print_ret "No puedes soplar dentro de ", (the) x2, ".";
        }

    Burn:
        switch(x1) {
          1: print_ret "Este acto peligroso no conseguiría nada en cualquier caso.";
          2: print_ret "Este acto peligroso no conseguiría nada en cualquier caso.";
          3: print_ret "No puedes quemar ", (the) x2, ".";
        }

    Buy:
        switch(x1) {
          1: print_ret "No hay nada en venta.";
          2: print_ret "No ", (es) x2, " tuyo para comprar.";
        }

    Climb:
        switch(x1) {
          1: print_ret "No creo que ", (the) x2, " pueda", (n) x2, " ser escalado", (s) x2, ".";
          2: print_ret "No llegarías a ningún sitio.";
        }

    Close:
        switch(x1) {
          1: print_ret "No puedes cerrar ", (the) x2, ".";
          2: print_ret (The) x2, " ya está", (n) x2, " cerrad", (o) x2, ".";
          3: print_ret "Cierras ", (the) x2, ".";
          4: print_ret (The) x2, " se cierra.";
        }

    CommandsOff:
        switch(x1) {
          1: print_ret "Grabación de órdenes finalizada.";
          2: print_ret "Grabación de órdenes ya finalizada.";
          3: print_ret "Grabación de órdenes no iniciada.";
        }

    CommandsOn:
        switch(x1) {
          1: print_ret "Grabación de órdenes iniciada.";
          2: print_ret "Grabación de órdenes ya iniciada.";
          3: print_ret "Grabación de órdenes finalizada.";
          4: print_ret "Grabación de órdenes ya finalizada.";
        }

    CommandsRead:
        switch(x1) {
          1: print_ret "Reproducción de órdenes iniciada.";
          2: print_ret "Reproducción de órdenes ya iniciada.";
          3: print_ret "Reproducción de órdenes finalizada.";
          4: print_ret "Reproducción de órdenes ya finalizada.";
          5: print_ret "Intentando reproducir órdenes de un fichero inexistente.";
          6: print_ret "Reproducción de órdenes fallida.";
        }

    Consult:
        switch(x1) {
          1: print_ret "No descubres nada interesante en ", (the) x2, " sobre ese tema.";
        }

    Cut:
        switch(x1) {
          1: print_ret "Cortar ", (the) x2, " no serviría de nada.";
          2: print_ret "Cortar ", (the) x2, " con ", (the) x1, " no serviría de nada.";
        }

    Dig:
        switch(x1) {
          1: print_ret "Cavar no serviría de nada aquí.";
          2: print_ret "No tiene sentido cavar en ", (the) x2, ".";
          3: print_ret "No puedes cavar con ", (the) x2, ".";
        }

    Disrobe:
        switch(x1) {
          1: print_ret "No ", (es) x2, " algo que puedas quitarte.";
          2: print_ret "No llevas puesto ", (the) x2, ".";
          3: print_ret "Te quitas ", (the) x2, ".";
        }

    Drink:
        switch(x1) {
          1: print_ret "No hay nada adecuado para beber aquí.";
          2: print_ret "No puedes beber eso.";
          3: print_ret "Te bebes ", (the) x2, ". No está mal.";
        }

    Drop:
        switch(x1) {
          1: print_ret "No tienes ", (the) x2, ".";
          2: print_ret "No puedes dejar algo que llevas puesto.";
          3: print_ret "No hay espacio en ", (the) x2, " para dejar nada más.";
          4: print_ret "No puedes dejar nada en ", (the) x2, ".";
          5: print_ret "(primero ", (te) "bajas ", (del) x2, ")";
          6: print_ret "Dejado.";
          7: print_ret "Dejado.";
        }

    Eat:
        switch(x1) {
          1: print_ret (The) x2, " no ", (es) x2, " comestible.";
          2: print_ret "Te comes ", (the) x2, ". No está mal.";
        }

    Empty:
        switch(x1) {
          1: print_ret "No puedes vaciar ", (the) x2, ".";
          2: print_ret (The) x2, " ya está", (n) x2, " vací", (o) x2, ".";
          3: print_ret "No puedes vaciar algo sobre sí mismo.";
          4: print_ret "No puedes vaciar nada en ", (the) x2, ".";
        }

    EmptyT:
        switch(x1) {
          1: print_ret "No puedes vaciar ", (the) x2, ".";
        }

    Enter:
        switch(x1) {
          1: print_ret "Ya estás ", (contigo) x2, ".";
          2: print_ret "No puedes entrar en ", (the) x2, ".";
          3: print_ret "No puedes entrar en algo que está cerrado.";
          4: print_ret "No puedes entrar porque no estás en el suelo.";
          5: print_ret "Entras en ", (the) x2, ".";
          6: print_ret "Entras en ", (the) x2, ".";
          7: print_ret "(primero ", (te) "bajas ", (del) x1, ")";
        }

    Examine:
        switch(x1) {
          1: print_ret "Está demasiado oscuro. No puedes ver nada.";
          2: print_ret "No observas nada especial en ", (the) x2, ".";
          3: print_ret (The) x2, " está", (n) x2, " actualmente ";
             if (x2 has on) print "encendid"; else print "apagad";
             print (o) x2, ".";
          4: print_ret "Está demasiado oscuro para ver bien.";
        }

    Exit:
        switch(x1) {
          1: print_ret "No estás en ningún sitio del que debas salir.";
          2: print_ret "No puedes salir de algo cerrado.";
          3: print_ret "Sales ", (del) x2, ".";
          4: print_ret "No puedes salir porque ", (the) x1, " no tiene salida.";
          5: print_ret "(primero ", (te) "bajas ", (del) x1, ")";
          6: print_ret "(primero sales ", (del) x1, ")";
        }

    Fill:
        switch(x1) {
          1: print_ret "No puedes llenar eso.";
          2: print_ret "No hay agua disponible.";
          3: print_ret (The) x2, " no sirve", (n) x2, " para contener agua.";
        }

    FullScore:
        switch(x1) {
          1: if (deadflag) print "La puntuación fue "; else print "La puntuación es ";
             "de ", x2, " (de un total de ", x3, "), en ", turns, " turno";
             if (turns ~= 1) print "s";
          2: "Tu puntuación ha aumentado en ", x2, " punto";
             if (x2 ~= 1) print "s";
          3: "Tu puntuación ha disminuido en ", x2, " punto";
             if (x2 ~= 1) print "s";
        }

    GetOff:
        switch(x1) {
          1: print_ret "No estás ", (contigo) x2, ".";
          2: print_ret "Te bajas ", (del) x2, ".";
        }

    Give:
        switch(x1) {
          1: print_ret "No tienes ", (the) x2, ".";
          2: print_ret "No puedes darte cosas a ti mismo.";
          3: print_ret (The) x3, " no parece", (n) x3, " querer ", (the) x2, ".";
          4: print_ret "Le das ", (the) x2, " a ", (the) x3, ".";
        }

    Go:
        switch(x1) {
          1: print_ret "Tienes que indicar en qué dirección ir.";
          2: print_ret "No puedes ir por ahí.";
          3: print_ret "Estás ", (contigo) x2, ".";
          4: print_ret "No puedes ir porque ", (the) x2, " no lleva", (n) x2, " a ningún sitio.";
          5: print_ret "No puedes ir por ahí porque ", (the) x2, " está", (n) x2, " en el camino.";
          6: print_ret "No puedes ir por ahí porque ", (the) x2, " no está", (n) x2, " abierto", (s) x2, ".";
          7: print_ret "No puedes ir porque no estás en el suelo.";
        }

    GoIn:
        switch(x1) {
          1: print_ret "No puedes entrar en ", (the) x2, ".";
          2: print_ret "No puedes entrar en algo que está cerrado.";
          3: print_ret "Ya estás ", (contigo) x2, ".";
          4: print_ret "No puedes entrar porque no estás en el suelo.";
          5: print_ret "Entras en ", (the) x2, ".";
          6: print_ret "(primero ", (te) "bajas ", (del) x1, ")";
          7: print_ret "(primero sales ", (del) x1, ")";
        }

    Hello:
        switch(x1) {
          1: print_ret "No hay respuesta.";
        }

    Inventory:
        switch(x1) {
          1: print_ret "No llevas nada.";
          2: print_ret "Llevas:";
          3: print_ret "Llevas:";
          4: print_ret "  (puesto", (s) x1, ")";
          5: print_ret "  (iluminado y puesto)";
          6: print_ret "  (iluminado)";
          7: print_ret "  (puesto", (s) x1, " y ", (contigo) x1, ")";
          8: print_ret "  (", (contigo) x1, ")";
        }

    Jump:
        switch(x1) {
          1: print_ret "Saltas en el sitio, sin ningún resultado.";
        }

    JumpOver:
        switch(x1) {
          1: print_ret "Tendrás que encontrar otra forma de ir.";
          2: print_ret "No puedes saltar por encima de algo que no está en el suelo.";
        }

    Kiss:
        switch(x1) {
          1: print_ret "Guarda tus muestras de afecto.";
        }

    Listen:
        switch(x1) {
          1: print_ret "No escuchas nada fuera de lo común.";
        }

    ListMiscellany:
        switch(x1) {
          1: print " (iluminado", (s) x2, ")";
          2: print " (que ", (esta) x2, " cerrad", (o) x2, ")";
          3: print " (cerrad", (o) x2, " y vacío", (s) x2, ")";
          4: print " (cerrad", (o) x2, " y que ", (esta) x2, " ";
          5: print " (abierto", (s) x2, " y vacío", (s) x2, ")";
          6: print " (abierto", (s) x2, " pero vacío", (s) x2, ")";
          7: print " (abierto", (s) x2, " y que ", (esta) x2, " ";
          8: print " (que ", (esta) x2, " ";
          9: print " (iluminado", (s) x2, " y puesto", (s) x2, ")";
          10: print " (iluminado", (s) x2, " y que ", (esta) x2, " ";
          11: print " (que ", (esta) x2, " puesto", (s) x2, ")";
          12: print " (que ", (esta) x2, " ";
          13: print " (que ", (esta) x2, " ";
          14: print " (vacío", (s) x2, ")";
          15: print " (vacío", (s) x2, ")";
          16: print " (cerrad", (o) x2, ")";
          17: print " (cerrad", (o) x2, " y bloqueado", (s) x2, ")";
          18: print " (cerrad", (o) x2, " con llave)";
          19: print " (abierto", (s) x2, ")";
          20: print " (abierto", (s) x2, " y bloqueado", (s) x2, ")";
          21: print " (abierto", (s) x2, " con llave)";
          22: print " (bloqueado", (s) x2, ")";
          23: print " (bloqueado", (s) x2, " con llave)";
          24: print " (que ", (esta) x2, " vacío", (s) x2, ")";
          25: print " (que ", (esta) x2, " ";
          26: print " (que ", (esta) x2, " puesto", (s) x2, ")";
          27: print " (que ", (esta) x2, " ";
          28: print " (que ", (esta) x2, " ";
          29: print " (que ", (esta) x2, " ";
          30: print " (que ", (esta) x2, " ";
          31: print " (que ", (esta) x2, " ";
          32: print " (que ", (esta) x2, " ";
          33: print " (que ", (esta) x2, " ";
          34: print " (que ", (esta) x2, " ";
          35: print " (que ", (esta) x2, " ";
          36: print " (que ", (esta) x2, " ";
          37: print " (que ", (esta) x2, " ";
          38: print " (que ", (esta) x2, " ";
          39: print " (que ", (esta) x2, " ";
          40: print " (que ", (esta) x2, " ";
          41: print " (que ", (esta) x2, " ";
          42: print " (que ", (esta) x2, " ";
          43: print " (que ", (esta) x2, " ";
          44: print " (que ", (esta) x2, " ";
          45: print " (que ", (esta) x2, " ";
          46: print " (que ", (esta) x2, " ";
          47: print " (que ", (esta) x2, " ";
          48: print " (que ", (esta) x2, " ";
          49: print " (que ", (esta) x2, " ";
          50: print " (que ", (esta) x2, " ";
          51: print " (que ", (esta) x2, " ";
          52: print " (que ", (esta) x2, " ";
          53: print " (que ", (esta) x2, " ";
          54: print " (que ", (esta) x2, " ";
          55: print " (que ", (esta) x2, " ";
          56: print " (que ", (esta) x2, " ";
          57: print " (que ", (esta) x2, " ";
          58: print " (que ", (esta) x2, " ";
          59: print " (que ", (esta) x2, " ";
          60: print " (que ", (esta) x2, " ";
          61: print " (que ", (esta) x2, " ";
          62: print " (que ", (esta) x2, " ";
          63: print " (que ", (esta) x2, " ";
        }

    LMode1:
        switch(x1) {
          1: print_ret "Modo de descripciones normales.";
        }

    LMode2:
        switch(x1) {
          1: print_ret "Modo de descripciones detalladas.";
        }

    LMode3:
        switch(x1) {
          1: print_ret "Modo de descripciones breves.";
        }

    Lock:
        switch(x1) {
          1: print_ret "No puedes cerrar con llave ", (the) x2, ".";
          2: print_ret (The) x2, " ya está", (n) x2, " cerrad", (o) x2, " con llave.";
          3: print_ret "Primero tienes que cerrar ", (the) x2, ".";
          4: print_ret "No parece", (n) x2, " tener ningún tipo de cerradura.";
          5: print_ret "No tienes la llave correcta.";
          6: print_ret "Cierras ", (the) x2, " con llave.";
        }

    Look:
        switch(x1) {
          1: print " (en ", (the) x2, ")";
          2: print " (en ", (the) x2, ")";
          3: print " (como ", (the) x2, ")";
          4: print " (en ", (the) x2, ")";
          5: print_ret "No puedes ver nada. Está demasiado oscuro.";
          6: print_ret "No puedes ver gran cosa en ", (the) x2, ".";
          7: if (x2 has supporter) print " Sobre "; else print " En ";
             print (the) x2, " puedes ver ";
          8: print_ret "No puedes ver nada destacable en ", (the) x2, ".";
        }

    LookUnder:
        switch(x1) {
          1: print_ret "Pero está demasiado oscuro para ver algo.";
          2: print_ret "No ves nada especial debajo ", (del) x2, ".";
        }

    Mild:
        switch(x1) {
          1: print_ret "Bastante.";
        }

    Miscellany:
        switch(x1) {
          1: print_ret "(considerando sólo los objetos visibles)";
          2: print_ret "(considerando los objetos visibles)";
          3: print_ret "(considerando los objetos visibles)";
          4: print_ret "(considerando los objetos visibles)";
          5: print_ret "No hay nada que hacer.";
          6: print_ret "No has especificado suficiente.";
          7: print_ret "No has especificado eso.";
          8: print_ret "No puedes usar múltiples objetos con ese verbo.";
          9: print_ret "No puedes usar ese verbo con múltiples objetos.";
          10: print_ret "Sólo puedes usar múltiples objetos una vez en una acción.";
          11: print_ret "No puedo entender qué quieres decir con ", (address) x2, ".";
          12: print_ret "No puedes ver eso.";
          13: print_ret "No puedes ver eso.";
          14: print_ret "Eso no está disponible.";
          15: print_ret "No puedes ver ", (the) x2, " ahora mismo.";
          16: print_ret "No tienes ", (the) x2, ".";
          17: print_ret "No puedes usar múltiples objetos con ese verbo.";
          18: print_ret "No puedes usar ese verbo con múltiples objetos.";
          19: print_ret "No tienes ninguno de esos.";
          20: print_ret "No puedes usar eso.";
          21: print_ret "No puedes ver lo que hay que examinar.";
          22: print_ret "No puedes especificar objetos externos a lo que estás examinando.";
          23: print_ret "No puedes especificar objetos que están dentro de otros jugadores.";
          24: print_ret "Tienes que identificar un objeto.";
          25: print_ret "No entiendo a qué te refieres con ", (address) x2, ".";
          26: print_ret "Sólo puedes hacer eso con algo animado.";
          27: print_ret "No estoy seguro de a qué ", (the) x2, " te refieres.";
          28: print_ret "No estoy seguro de a qué te refieres con ", (address) x2, ".";
          29: print_ret "No estoy seguro de a qué te refieres con ", (address) x2, ".";
          30: print_ret "(Asumo que te refieres a ", (the) x2, ")";
          31: print_ret "(Asumo que te refieres a ", (the) x2, ")";
          32: print_ret "No puedes ver ", (the) x2, " ahora mismo.";
          33: print_ret "No puedes tocar ", (the) x2, " desde aquí.";
          34: print_ret "No tienes ", (the) x2, ".";
          35: print_ret "No puedes ver ", (the) x2, " ahora mismo.";
          36: print_ret "No tienes ", (the) x2, ".";
          37: print_ret "No puedes ver ", (the) x2, " ahora mismo.";
          38: print_ret "No tienes ", (the) x2, ".";
          39: print_ret "(primero coges ", (the) x2, ")";
          40: print_ret "No puedo ver lo que hay que examinar.";
          41: print_ret "No puedo ver lo que hay que examinar.";
          42: print_ret "No puedo ver lo que hay que examinar.";
          43: print_ret "No puedo ver lo que hay que examinar.";
          44: print_ret "No puedo ver lo que hay que examinar.";
          45: print_ret "No puedo ver lo que hay que examinar.";
          46: print_ret "No puedo ver lo que hay que examinar.";
          47: print_ret "No puedo ver lo que hay que examinar.";
          48: print_ret "No puedo ver lo que hay que examinar.";
          49: print_ret "No puedo ver lo que hay que examinar.";
          50: print_ret "No puedo ver lo que hay que examinar.";
          51: print_ret "No puedo ver lo que hay que examinar.";
          52: print_ret "No puedo ver lo que hay que examinar.";
          53: print_ret "No puedo ver lo que hay que examinar.";
          54: print_ret "No puedo ver lo que hay que examinar.";
          55: print_ret "No puedo ver lo que hay que examinar.";
          56: print_ret "No puedo ver lo que hay que examinar.";
          57: print_ret "No puedo ver lo que hay que examinar.";
          58: print_ret "No puedo ver lo que hay que examinar.";
          59: print_ret "No puedo ver lo que hay que examinar.";
          60: print_ret "No puedo ver lo que hay que examinar.";
          61: print_ret "No puedo ver lo que hay que examinar.";
          62: print_ret "No puedo ver lo que hay que examinar.";
          63: print_ret "No puedo ver lo que hay que examinar.";
        }

    No:
        switch(x1) {
          1: print_ret "Esa era una pregunta retórica.";
          2: print_ret "Has contestado negativamente.";
        }

    NotifyOff:
        switch(x1) {
          1: print_ret "Notificación de puntuación desactivada.";
        }

    NotifyOn:
        switch(x1) {
          1: print_ret "Notificación de puntuación activada.";
        }

    Objects:
        switch(x1) {
          1: print_ret "Objetos que has manejado:^";
          2: print_ret "Ninguno.";
          3: print_ret " (puesto", (s) x2, ")";
          4: print_ret " (en tu poder)";
          5: print_ret " (abandonado", (s) x2, ")";
          6: print_ret " (en ", (name) x3, ")";
          7: print_ret " (en ", (the) x3, ")";
          8: print_ret " (dentro ", (del) x3, ")";
          9: print_ret " (en ", (the) x3, ")";
          10: print_ret " (perdido", (s) x2, ")";
        }

    Open:
        switch(x1) {
          1: print_ret "No puedes abrir ", (the) x2, ".";
          2: print_ret (The) x2, " ya está", (n) x2, " abierto", (s) x2, ".";
          3: print_ret (The) x2, " está", (n) x2, " cerrado", (s) x2, " con llave.";
          4: print_ret "Abres ", (the) x2, ", descubriendo ";
          5: print_ret "Abres ", (the) x2, ".";
          6: print_ret (The) x2, " se abre.";
          7: print_ret "Está vacío.";
        }

    Order:
        switch(x1) {
          1: print_ret (The) x2, " tiene", (n) x2, " mejores cosas que hacer.";
        }

    Places:
        switch(x1) {
          1: print_ret "Has visitado: ";
          2: print_ret ".";
        }

    Pray:
        switch(x1) {
          1: print_ret "Tu plegaria no parece ser escuchada.";
        }

    Prompt:
        switch(x1) {
          1: print "^>";
          2: print "^>>";
        }

    Pronouns:
        switch(x1) {
          1: print_ret "En este momento, ";
          2: print_ret "significa ";
          3: print_ret "no está establecido";
          4: print_ret "significa múltiples objetos";
          5: print_ret "se refiere a algo fuera de alcance";
          6: print_ret "no se refiere a nada";
        }

    Pull:
        switch(x1) {
          1: print_ret "No está fijo", (s) x2, " en el sitio.";
          2: print_ret "Estás simplemente desperdiciando tu energía.";
          3: print_ret "No es algo que puedas mover.";
        }

    Push:
        switch(x1) {
          1: print_ret "No está fijo", (s) x2, " en el sitio.";
          2: print_ret "Estás simplemente desperdiciando tu energía.";
          3: print_ret "No es algo que puedas mover.";
        }

    PushDir:
        switch(x1) {
          1: print_ret "No es algo que puedas mover.";
          2: print_ret "No puedes ir en esa dirección.";
          3: print_ret "No puedes empujar ", (the) x2, " desde aquí.";
        }

    PutOn:
        switch(x1) {
          1: print_ret "Necesitas tener ", (the) x2, " para poder poner", (lo) x2, " en algo.";
          2: print_ret "No puedes poner algo sobre sí mismo.";
          3: print_ret "Poner cosas sobre ", (the) x2, " no serviría de nada.";
          4: print_ret "No tienes espacio en ", (the) x2, " para poner nada más.";
          5: print_ret "Hecho.";
          6: print_ret "Pones ", (the) x2, " sobre ", (the) x3, ".";
          7: print_ret "No tienes espacio en ", (the) x2, " para poner nada más.";
        }

    Quit:
        switch(x1) {
          1: print_ret "Por favor, responde sí o no.";
          2: print_ret "¿Estás seguro de que quieres terminar? ";
        }

    Restart:
        switch(x1) {
          1: print_ret "¿Estás seguro de que quieres reiniciar? ";
          2: print_ret "Error al reiniciar.";
        }

    Restore:
        switch(x1) {
          1: print_ret "Error al cargar.";
          2: print_ret "Ok.";
        }

    Rub:
        switch(x1) {
          1: print_ret "No conseguirás nada frotando ", (the) x2, ".";
        }

    Save:
        switch(x1) {
          1: print_ret "Error al guardar.";
          2: print_ret "Ok.";
        }

    Score:
        switch(x1) {
          1: if (deadflag) print "En ese juego conseguiste "; else print "Hasta ahora has conseguido ";
             print x2, " de un total de ", x3, ", en ", turns, " turno";
             if (turns ~= 1) print "s";
             return;
          2: print_ret "Tu puntuación ha aumentado en ", x2, " punto";
             if (x2 ~= 1) print "s";
          3: print_ret "Tu puntuación ha disminuido en ", x2, " punto";
             if (x2 ~= 1) print "s";
        }

    ScriptOff:
        switch(x1) {
          1: print_ret "Transcripción finalizada.";
          2: print_ret "Intento fallido de finalizar la transcripción.";
          3: print_ret "Transcripción ya finalizada.";
        }

    ScriptOn:
        switch(x1) {
          1: print_ret "Transcripción iniciada.";
          2: print_ret "Intento fallido de iniciar la transcripción.";
          3: print_ret "Transcripción ya iniciada.";
        }

    Search:
        switch(x1) {
          1: print_ret "Pero está demasiado oscuro para ver algo.";
          2: print_ret "No hay nada sobre ", (the) x2, ".";
          3: print_ret "En ", (the) x2, " puedes ver ";
          4: print_ret "No encuentras nada interesante.";
          5: print_ret "No puedes ver dentro ", (del) x2, " porque está", (n) x2, " cerrado", (s) x2, ".";
          6: print_ret (The) x2, " está", (n) x2, " vacío", (s) x2, ".";
          7: print_ret "En ", (the) x2, " puedes ver ";
        }

    Set:
        switch(x1) {
          1: print_ret "No, no puedes ajustar ", (the) x2, ".";
        }

    SetTo:
        switch(x1) {
          1: print_ret "No, no puedes ajustar ", (the) x2, " a nada.";
        }

    Show:
        switch(x1) {
          1: print_ret "No tienes ", (the) x2, ".";
          2: print_ret (The) x3, " no parece", (n) x3, " interesado", (s) x3, ".";
        }

    Sing:
        switch(x1) {
          1: print_ret "Cantas fatal.";
        }

    Sleep:
        switch(x1) {
          1: print_ret "No estás especialmente somnoliento.";
        }

    Smell:
        switch(x1) {
          1: print_ret "No hueles nada extraño.";
        }

    Sorry:
        switch(x1) {
          1: print_ret "No pasa nada.";
        }

    Squeeze:
        switch(x1) {
          1: print_ret "No tiene sentido apretar ", (the) x2, ".";
        }

    Strong:
        switch(x1) {
          1: print_ret "Los verdaderos aventureros no usan ese tipo de lenguaje.";
        }

    Swim:
        switch(x1) {
          1: print_ret "No hay agua suficiente para nadar.";
        }

    Swing:
        switch(x1) {
          1: print_ret "No es algo que puedas balancear.";
        }

    SwitchOff:
        switch(x1) {
          1: print_ret "No puedes apagar ", (the) x2, ".";
          2: print_ret (The) x2, " ya está", (n) x2, " apagado", (s) x2, ".";
          3: print_ret "Apagas ", (the) x2, ".";
          4: print_ret (The) x2, " se apaga.";
        }

    SwitchOn:
        switch(x1) {
          1: print_ret "No puedes encender ", (the) x2, ".";
          2: print_ret (The) x2, " ya está", (n) x2, " encendido", (s) x2, ".";
          3: print_ret "Enciendes ", (the) x2, ".";
          4: print_ret (The) x2, " se enciende.";
        }

    Take:
        switch(x1) {
          1: print_ret "Tomado.";
          2: print_ret "Ya tienes ", (the) x2, ".";
          3: print_ret (The) x2, " parece", (n) x2, " pertenecer a ", (the) x3, ".";
          4: print_ret (The) x2, " parece", (n) x2, " formar parte ", (del) x3, ".";
          5: print_ret "Ya tienes ", (the) x2, ".";
          6: print_ret "No parece", (n) x2, " ser algo que puedas llevarte.";
          7: print_ret (The) x2, " no está", (n) x2, " disponible", (s) x2, ".";
          8: print_ret (The) x2, " está", (n) x2, " fijo", (s) x2, " en el sitio.";
          9: print_ret "Estás llevando demasiadas cosas.";
          10: print_ret "No tienes espacio en ", (the) x2, " para poner nada más.";
          11: print_ret "No puedes quitarte ", (the) x2, ".";
          12: print_ret "No puedes coger ", (the) x2, ".";
          13: print_ret "(primero ", (te) "bajas ", (del) x3, ")";
          14: print_ret "Coges ", (the) x2, ".";
          15: print_ret "Recoges ", (the) x2, ".";
        }

    Taste:
        switch(x1) {
          1: print_ret "No saboreas nada inesperado.";
        }

    Tell:
        switch(x1) {
          1: print_ret "Hablas contigo mismo durante un rato.";
          2: print_ret "No parece que ", (the) x2, " esté", (n) x2, " interesado", (s) x2, ".";
        }

    Think:
        switch(x1) {
          1: print_ret "Qué buena idea.";
        }

    ThrowAt:
        switch(x1) {
          1: print_ret "No serviría de nada.";
          2: print_ret "En el último momento te echas atrás.";
        }

    ThrownAt:
        switch(x1) {
          1: print_ret "No tienes muy buena puntería.";
        }

    Tie:
        switch(x1) {
          1: print_ret "No puedes atar ", (the) x2, " a nada.";
        }

    Touch:
        switch(x1) {
          1: print_ret "No notas nada extraño al tacto.";
          2: print_ret "No creo que ", (al) x2, " le", (s) x2, " gustaría.";
        }

    Turn:
        switch(x1) {
          1: print_ret "No sucede nada.";
          2: print_ret "No es algo que puedas girar.";
        }

    Unlock:
        switch(x1) {
          1: print_ret "No puedes desbloquear ", (the) x2, ".";
          2: print_ret (The) x2, " ya tiene", (n) x2, " abierta la cerradura.";
          3: print_ret (The) x2, " no parece", (n) x2, " tener cerradura.";
          4: print_ret "No tienes la llave correcta.";
          5: print_ret "Desbloqueas ", (the) x2, ".";
        }

    VagueGo:
        switch(x1) {
          1: print_ret "Tienes que indicar en qué dirección ir.";
        }

    Verify:
        switch(x1) {
          1: print_ret "El fichero de juego ha verificado correctamente.";
          2: print_ret "El fichero de juego no ha verificado correctamente, y puede estar corrupto.";
        }

    Version:
        switch(x1) {
          1: print "Historia: ";
          2: print "Intérprete: ";
          3: print " / Librería: ";
        }

    Wait:
        switch(x1) {
          1: print_ret "Pasa el tiempo...";
        }

    Wake:
        switch(x1) {
          1: print_ret "No parece que estés dormido.";
        }

    WakeOther:
        switch(x1) {
          1: print_ret "No parece necesario hacer eso.";
        }

    Wave:
        switch(x1) {
          1: print_ret "No tienes ", (the) x2, ".";
          2: print_ret "Te sientes ridículo agitando ", (the) x2, ".";
        }

    WaveHands:
        switch(x1) {
          1: print_ret "Agitas tus manos.";
          2: print_ret "Estás demasiado ocupado para saludar.";
        }

    Wear:
        switch(x1) {
          1: print_ret "No puedes ponerte eso.";
          2: print_ret "No tienes ", (the) x2, ".";
          3: print_ret "Ya llevas puesto ", (the) x2, ".";
          4: print_ret "Te pones ", (the) x2, ".";
        }

    Yes:
        switch(x1) {
          1: print_ret "Esa era una pregunta retórica.";
          2: print_ret "Has contestado afirmativamente.";
        }
  }
];

! Funciones auxiliares para manejar género y número en español
[ es obj;
    if (obj has pluralname) print "son"; else print "es";
];

[ esta obj;
    if (obj has pluralname) print "están"; else print "está";
];

[ n obj;
    if (obj has pluralname) print "n"; else print "";
];

[ s obj;
    if (obj has pluralname) print "s"; else print "";
];

[ o obj;
    if (obj has female) print "a"; else print "o";
];

[ lo obj;
    if (obj has female) print "la"; else print "lo";
];

[ te;
    print "te";
];

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

#Endif;

! ==============================================================================! ==============================================================================
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

Constant LibraryMessages = 1;

#Ifdef TARGET_ZCODE;
[ LibraryExtensions;
  #Ifdef LIBRARY_PARSER; LibraryExtensions(); #Endif;
  #Ifdef LIBRARY_VERBLIB; LibraryExtensions(); #Endif;
];
#Endif; ! TARGET_ZCODE

#Ifdef TARGET_GLULX;
[ LibraryExtensions;
  #Ifdef LIBRARY_PARSER; LibraryExtensions(); #Endif;
  #Ifdef LIBRARY_VERBLIB; LibraryExtensions(); #Endif;
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
    Answer:
        switch(x1) {
          1: print_ret "No hay ninguna respuesta.";
        }

    Ask:
        switch(x1) {
          1: print_ret "No hay respuesta.";
          2: print_ret "No hay respuesta.";
        }

    AskFor:
        switch(x1) {
          1: print_ret "No puedes pedir eso.";
          2: print_ret "No hay respuesta.";
          3: print_ret "No hay respuesta.";
        }

    Attack:
        switch(x1) {
          1: print_ret "No tiene sentido atacar ", (the) x2, ".";
          2: print_ret "No estás en un estado combativo.";
          3: print_ret "No parece que atacar ", (the) x2, " vaya a servir de nada.";
        }

    Blow:
        switch(x1) {
          1: print_ret "No puedes soplar ", (the) x2, ".";
          2: print_ret "No conseguirás nada soplando ", (the) x2, ".";
          3: print_ret "No puedes soplar dentro de ", (the) x2, ".";
        }

    Burn:
        switch(x1) {
          1: print_ret "Este acto peligroso no conseguiría nada en cualquier caso.";
          2: print_ret "Este acto peligroso no conseguiría nada en cualquier caso.";
          3: print_ret "No puedes quemar ", (the) x2, ".";
        }

    Buy:
        switch(x1) {
          1: print_ret "No hay nada en venta.";
          2: print_ret "No ", (es) x2, " tuyo para comprar.";
        }

    Climb:
        switch(x1) {
          1: print_ret "No creo que ", (the) x2, " pueda", (n) x2, " ser escalado", (s) x2, ".";
          2: print_ret "No llegarías a ningún sitio.";
        }

    Close:
        switch(x1) {
          1: print_ret "No puedes cerrar ", (the) x2, ".";
          2: print_ret (The) x2, " ya está", (n) x2, " cerrad", (o) x2, ".";
          3: print_ret "Cierras ", (the) x2, ".";
          4: print_ret (The) x2, " se cierra.";
        }

    CommandsOff:
        switch(x1) {
          1: print_ret "Grabación de órdenes finalizada.";
          2: print_ret "Grabación de órdenes ya finalizada.";
          3: print_ret "Grabación de órdenes no iniciada.";
        }

    CommandsOn:
        switch(x1) {
          1: print_ret "Grabación de órdenes iniciada.";
          2: print_ret "Grabación de órdenes ya iniciada.";
          3: print_ret "Grabación de órdenes finalizada.";
          4: print_ret "Grabación de órdenes ya finalizada.";
        }

    CommandsRead:
        switch(x1) {
          1: print_ret "Reproducción de órdenes iniciada.";
          2: print_ret "Reproducción de órdenes ya iniciada.";
          3: print_ret "Reproducción de órdenes finalizada.";
          4: print_ret "Reproducción de órdenes ya finalizada.";
          5: print_ret "Intentando reproducir órdenes de un fichero inexistente.";
          6: print_ret "Reproducción de órdenes fallida.";
        }

    Consult:
        switch(x1) {
          1: print_ret "No descubres nada interesante en ", (the) x2, " sobre ese tema.";
        }

    Cut:
        switch(x1) {
          1: print_ret "Cortar ", (the) x2, " no serviría de nada.";
          2: print_ret "Cortar ", (the) x2, " con ", (the) x1, " no serviría de nada.";
        }

    Dig:
        switch(x1) {
          1: print_ret "Cavar no serviría de nada aquí.";
          2: print_ret "No tiene sentido cavar en ", (the) x2, ".";
          3: print_ret "No puedes cavar con ", (the) x2, ".";
        }

    Disrobe:
        switch(x1) {
          1: print_ret "No ", (es) x2, " algo que puedas quitarte.";
          2: print_ret "No llevas puesto ", (the) x2, ".";
          3: print_ret "Te quitas ", (the) x2, ".";
        }

    Drink:
        switch(x1) {
          1: print_ret "No hay nada adecuado para beber aquí.";
          2: print_ret "No puedes beber eso.";
          3: print_ret "Te bebes ", (the) x2, ". No está mal.";
        }

    Drop:
        switch(x1) {
          1: print_ret "No tienes ", (the) x2, ".";
          2: print_ret "No puedes dejar algo que llevas puesto.";
          3: print_ret "No hay espacio en ", (the) x2, " para dejar nada más.";
          4: print_ret "No puedes dejar nada en ", (the) x2, ".";
          5: print_ret "(primero ", (te) "bajas ", (del) x2, ")";
          6: print_ret "Dejado.";
          7: print_ret "Dejado.";
        }

    Eat:
        switch(x1) {
          1: print_ret (The) x2, " no ", (es) x2, " comestible.";
          2: print_ret "Te comes ", (the) x2, ". No está mal.";
        }

    Empty:
        switch(x1) {
          1: print_ret "No puedes vaciar ", (the) x2, ".";
          2: print_ret (The) x2, " ya está", (n) x2, " vací", (o) x2, ".";
          3: print_ret "No puedes vaciar algo sobre sí mismo.";
          4: print_ret "No puedes vaciar nada en ", (the) x2, ".";
        }

    EmptyT:
        switch(x1) {
          1: print_ret "No puedes vaciar ", (the) x2, ".";
        }

    Enter:
        switch(x1) {
          1: print_ret "Ya estás ", (contigo) x2, ".";
          2: print_ret "No puedes entrar en ", (the) x2, ".";
          3: print_ret "No puedes entrar en algo que está cerrado.";
          4: print_ret "No puedes entrar porque no estás en el suelo.";
          5: print_ret "Entras en ", (the) x2, ".";
          6: print_ret "Entras en ", (the) x2, ".";
          7: print_ret "(primero ", (te) "bajas ", (del) x1, ")";
        }

    Examine:
        switch(x1) {
          1: print_ret "Está demasiado oscuro. No puedes ver nada.";
          2: print_ret "No observas nada especial en ", (the) x2, ".";
          3: print_ret (The) x2, " está", (n) x2, " actualmente ";
             if (x2 has on) print "encendid"; else print "apagad";
             print (o) x2, ".";
          4: print_ret "Está demasiado oscuro para ver bien.";
        }

    Exit:
        switch(x1) {
          1: print_ret "No estás en ningún sitio del que debas salir.";
          2: print_ret "No puedes salir de algo cerrado.";
          3: print_ret "Sales ", (del) x2, ".";
          4: print_ret "No puedes salir porque ", (the) x1, " no tiene salida.";
          5: print_ret "(primero ", (te) "bajas ", (del) x1, ")";
          6: print_ret "(primero sales ", (del) x1, ")";
        }

    Fill:
        switch(x1) {
          1: print_ret "No puedes llenar eso.";
          2: print_ret "No hay agua disponible.";
          3: print_ret (The) x2, " no sirve", (n) x2, " para contener agua.";
        }

    FullScore:
        switch(x1) {
          1: if (deadflag) print "La puntuación fue "; else print "La puntuación es ";
             "de ", x2, " (de un total de ", x3, "), en ", turns, " turno";
             if (turns ~= 1) print "s";
          2: "Tu puntuación ha aumentado en ", x2, " punto";
             if (x2 ~= 1) print "s";
          3: "Tu puntuación ha disminuido en ", x2, " punto";
             if (x2 ~= 1) print "s";
        }

    GetOff:
        switch(x1) {
          1: print_ret "No estás ", (contigo) x2, ".";
          2: print_ret "Te bajas ", (del) x2, ".";
        }

    Give:
        switch(x1) {
          1: print_ret "No tienes ", (the) x2, ".";
          2: print_ret "No puedes darte cosas a ti mismo.";
          3: print_ret (The) x3, " no parece", (n) x3, " querer ", (the) x2, ".";
          4: print_ret "Le das ", (the) x2, " a ", (the) x3, ".";
        }

    Go:
        switch(x1) {
          1: print_ret "Tienes que indicar en qué dirección ir.";
          2: print_ret "No puedes ir por ahí.";
          3: print_ret "Estás ", (contigo) x2, ".";
          4: print_ret "No puedes ir porque ", (the) x2, " no lleva", (n) x2, " a ningún sitio.";
          5: print_ret "No puedes ir por ahí porque ", (the) x2, " está", (n) x2, " en el camino.";
          6: print_ret "No puedes ir por ahí porque ", (the) x2, " no está", (n) x2, " abierto", (s) x2, ".";
          7: print_ret "No puedes ir porque no estás en el suelo.";
        }

    GoIn:
        switch(x1) {
          1: print_ret "No puedes entrar en ", (the) x2, ".";
          2: print_ret "No puedes entrar en algo que está cerrado.";
          3: print_ret "Ya estás ", (contigo) x2, ".";
          4: print_ret "No puedes entrar porque no estás en el suelo.";
          5: print_ret "Entras en ", (the) x2, ".";
          6: print_ret "(primero ", (te) "bajas ", (del) x1, ")";
          7: print_ret "(primero sales ", (del) x1, ")";
        }

    Hello:
        switch(x1) {
          1: print_ret "No hay respuesta.";
        }

    Inventory:
        switch(x1) {
          1: print_ret "No llevas nada.";
          2: print_ret "Llevas:";
          3: print_ret "Llevas:";
          4: print_ret "  (puesto", (s) x1, ")";
          5: print_ret "  (iluminado y puesto)";
          6: print_ret "  (iluminado)";
          7: print_ret "  (puesto", (s) x1, " y ", (contigo) x1, ")";
          8: print_ret "  (", (contigo) x1, ")";
        }

    Jump:
        switch(x1) {
          1: print_ret "Saltas en el sitio, sin ningún resultado.";
        }

    JumpOver:
        switch(x1) {
          1: print_ret "Tendrás que encontrar otra forma de ir.";
          2: print_ret "No puedes saltar por encima de algo que no está en el suelo.";
        }

    Kiss:
        switch(x1) {
          1: print_ret "Guarda tus muestras de afecto.";
        }

    Listen:
        switch(x1) {
          1: print_ret "No escuchas nada fuera de lo común.";
        }

    ListMiscellany:
        switch(x1) {
          1: print " (iluminado", (s) x2, ")";
          2: print " (que ", (esta) x2, " cerrad", (o) x2, ")";
          3: print " (cerrad", (o) x2, " y vacío", (s) x2, ")";
          4: print " (cerrad", (o) x2, " y que ", (esta) x2, " ";
          5: print " (abierto", (s) x2, " y vacío", (s) x2, ")";
          6: print " (abierto", (s) x2, " pero vacío", (s) x2, ")";
          7: print " (abierto", (s) x2, " y que ", (esta) x2, " ";
          8: print " (que ", (esta) x2, " ";
          9: print " (iluminado", (s) x2, " y puesto", (s) x2, ")";
          10: print " (iluminado", (s) x2, " y que ", (esta) x2, " ";
          11: print " (que ", (esta) x2, " puesto", (s) x2, ")";
          12: print " (que ", (esta) x2, " ";
          13: print " (que ", (esta) x2, " ";
          14: print " (vacío", (s) x2, ")";
          15: print " (vacío", (s) x2, ")";
          16: print " (cerrad", (o) x2, ")";
          17: print " (cerrad", (o) x2, " y bloqueado", (s) x2, ")";
          18: print " (cerrad", (o) x2, " con llave)";
          19: print " (abierto", (s) x2, ")";
          20: print " (abierto", (s) x2, " y bloqueado", (s) x2, ")";
          21: print " (abierto", (s) x2, " con llave)";
          22: print " (bloqueado", (s) x2, ")";
          23: print " (bloqueado", (s) x2, " con llave)";
          24: print " (que ", (esta) x2, " vacío", (s) x2, ")";
          25: print " (que ", (esta) x2, " ";
          26: print " (que ", (esta) x2, " puesto", (s) x2, ")";
          27: print " (que ", (esta) x2, " ";
          28: print " (que ", (esta) x2, " ";
          29: print " (que ", (esta) x2, " ";
          30: print " (que ", (esta) x2, " ";
          31: print " (que ", (esta) x2, " ";
          32: print " (que ", (esta) x2, " ";
          33: print " (que ", (esta) x2, " ";
          34: print " (que ", (esta) x2, " ";
          35: print " (que ", (esta) x2, " ";
          36: print " (que ", (esta) x2, " ";
          37: print " (que ", (esta) x2, " ";
          38: print " (que ", (esta) x2, " ";
          39: print " (que ", (esta) x2, " ";
          40: print " (que ", (esta) x2, " ";
          41: print " (que ", (esta) x2, " ";
          42: print " (que ", (esta) x2, " ";
          43: print " (que ", (esta) x2, " ";
          44: print " (que ", (esta) x2, " ";
          45: print " (que ", (esta) x2, " ";
          46: print " (que ", (esta) x2, " ";
          47: print " (que ", (esta) x2, " ";
          48: print " (que ", (esta) x2, " ";
          49: print " (que ", (esta) x2, " ";
          50: print " (que ", (esta) x2, " ";
          51: print " (que ", (esta) x2, " ";
          52: print " (que ", (esta) x2, " ";
          53: print " (que ", (esta) x2, " ";
          54: print " (que ", (esta) x2, " ";
          55: print " (que ", (esta) x2, " ";
          56: print " (que ", (esta) x2, " ";
          57: print " (que ", (esta) x2, " ";
          58: print " (que ", (esta) x2, " ";
          59: print " (que ", (esta) x2, " ";
          60: print " (que ", (esta) x2, " ";
          61: print " (que ", (esta) x2, " ";
          62: print " (que ", (esta) x2, " ";
          63: print " (que ", (esta) x2, " ";
        }

    LMode1:
        switch(x1) {
          1: print_ret "Modo de descripciones normales.";
        }

    LMode2:
        switch(x1) {
          1: print_ret "Modo de descripciones detalladas.";
        }

    LMode3:
        switch(x1) {
          1: print_ret "Modo de descripciones breves.";
        }

    Lock:
        switch(x1) {
          1: print_ret "No puedes cerrar con llave ", (the) x2, ".";
          2: print_ret (The) x2, " ya está", (n) x2, " cerrad", (o) x2, " con llave.";
          3: print_ret "Primero tienes que cerrar ", (the) x2, ".";
          4: print_ret "No parece", (n) x2, " tener ningún tipo de cerradura.";
          5: print_ret "No tienes la llave correcta.";
          6: print_ret "Cierras ", (the) x2, " con llave.";
        }

    Look:
        switch(x1) {
          1: print " (en ", (the) x2, ")";
          2: print " (en ", (the) x2, ")";
          3: print " (como ", (the) x2, ")";
          4: print " (en ", (the) x2, ")";
          5: print_ret "No puedes ver nada. Está demasiado oscuro.";
          6: print_ret "No puedes ver gran cosa en ", (the) x2, ".";
          7: if (x2 has supporter) print " Sobre "; else print " En ";
             print (the) x2, " puedes ver ";
          8: print_ret "No puedes ver nada destacable en ", (the) x2, ".";
        }

    LookUnder:
        switch(x1) {
          1: print_ret "Pero está demasiado oscuro para ver algo.";
          2: print_ret "No ves nada especial debajo ", (del) x2, ".";
        }

    Mild:
        switch(x1) {
          1: print_ret "Bastante.";
        }

    Miscellany:
        switch(x1) {
          1: print_ret "(considerando sólo los objetos visibles)";
          2: print_ret "(considerando los objetos visibles)";
          3: print_ret "(considerando los objetos visibles)";
          4: print_ret "(considerando los objetos visibles)";
          5: print_ret "No hay nada que hacer.";
          6: print_ret "No has especificado suficiente.";
          7: print_ret "No has especificado eso.";
          8: print_ret "No puedes usar múltiples objetos con ese verbo.";
          9: print_ret "No puedes usar ese verbo con múltiples objetos.";
          10: print_ret "Sólo puedes usar múltiples objetos una vez en una acción.";
          11: print_ret "No puedo entender qué quieres decir con ", (address) x2, ".";
          12: print_ret "No puedes ver eso.";
          13: print_ret "No puedes ver eso.";
          14: print_ret "Eso no está disponible.";
          15: print_ret "No puedes ver ", (the) x2, " ahora mismo.";
          16: print_ret "No tienes ", (the) x2, ".";
          17: print_ret "No puedes usar múltiples objetos con ese verbo.";
          18: print_ret "No puedes usar ese verbo con múltiples objetos.";
          19: print_ret "No tienes ninguno de esos.";
          20: print_ret "No puedes usar eso.";
          21: print_ret "No puedes ver lo que hay que examinar.";
          22: print_ret "No puedes especificar objetos externos a lo que estás examinando.";
          23: print_ret "No puedes especificar objetos que están dentro de otros jugadores.";
          24: print_ret "Tienes que identificar un objeto.";
          25: print_ret "No entiendo a qué te refieres con ", (address) x2, ".";
          26: print_ret "Sólo puedes hacer eso con algo animado.";
          27: print_ret "No estoy seguro de a qué ", (the) x2, " te refieres.";
          28: print_ret "No estoy seguro de a qué te refieres con ", (address) x2, ".";
          29: print_ret "No estoy seguro de a qué te refieres con ", (address) x2, ".";
          30: print_ret "(Asumo que te refieres a ", (the) x2, ")";
          31: print_ret "(Asumo que te refieres a ", (the) x2, ")";
          32: print_ret "No puedes ver ", (the) x2, " ahora mismo.";
          33: print_ret "No puedes tocar ", (the) x2, " desde aquí.";
          34: print_ret "No tienes ", (the) x2, ".";
          35: print_ret "No puedes ver ", (the) x2, " ahora mismo.";
          36: print_ret "No tienes ", (the) x2, ".";
          37: print_ret "No puedes ver ", (the) x2, " ahora mismo.";
          38: print_ret "No tienes ", (the) x2, ".";
          39: print_ret "(primero coges ", (the) x2, ")";
          40: print_ret "No puedo ver lo que hay que examinar.";
          41: print_ret "No puedo ver lo que hay que examinar.";
          42: print_ret "No puedo ver lo que hay que examinar.";
          43: print_ret "No puedo ver lo que hay que examinar.";
          44: print_ret "No puedo ver lo que hay que examinar.";
          45: print_ret "No puedo ver lo que hay que examinar.";
          46: print_ret "No puedo ver lo que hay que examinar.";
          47: print_ret "No puedo ver lo que hay que examinar.";
          48: print_ret "No puedo ver lo que hay que examinar.";
          49: print_ret "No puedo ver lo que hay que examinar.";
          50: print_ret "No puedo ver lo que hay que examinar.";
          51: print_ret "No puedo ver lo que hay que examinar.";
          52: print_ret "No puedo ver lo que hay que examinar.";
          53: print_ret "No puedo ver lo que hay que examinar.";
          54: print_ret "No puedo ver lo que hay que examinar.";
          55: print_ret "No puedo ver lo que hay que examinar.";
          56: print_ret "No puedo ver lo que hay que examinar.";
          57: print_ret "No puedo ver lo que hay que examinar.";
          58: print_ret "No puedo ver lo que hay que examinar.";
          59: print_ret "No puedo ver lo que hay que examinar.";
          60: print_ret "No puedo ver lo que hay que examinar.";
          61: print_ret "No puedo ver lo que hay que examinar.";
          62: print_ret "No puedo ver lo que hay que examinar.";
          63: print_ret "No puedo ver lo que hay que examinar.";
        }

    No:
        switch(x1) {
          1: print_ret "Esa era una pregunta retórica.";
          2: print_ret "Has contestado negativamente.";
        }

    NotifyOff:
        switch(x1) {
          1: print_ret "Notificación de puntuación desactivada.";
        }

    NotifyOn:
        switch(x1) {
          1: print_ret "Notificación de puntuación activada.";
        }

    Objects:
        switch(x1) {
          1: print_ret "Objetos que has manejado:^";
          2: print_ret "Ninguno.";
          3: print_ret " (puesto", (s) x2, ")";
          4: print_ret " (en tu poder)";
          5: print_ret " (abandonado", (s) x2, ")";
          6: print_ret " (en ", (name) x3, ")";
          7: print_ret " (en ", (the) x3, ")";
          8: print_ret " (dentro ", (del) x3, ")";
          9: print_ret " (en ", (the) x3, ")";
          10: print_ret " (perdido", (s) x2, ")";
        }

    Open:
        switch(x1) {
          1: print_ret "No puedes abrir ", (the) x2, ".";
          2: print_ret (The) x2, " ya está", (n) x2, " abierto", (s) x2, ".";
          3: print_ret (The) x2, " está", (n) x2, " cerrado", (s) x2, " con llave.";
          4: print_ret "Abres ", (the) x2, ", descubriendo ";
          5: print_ret "Abres ", (the) x2, ".";
          6: print_ret (The) x2, " se abre.";
          7: print_ret "Está vacío.";
        }

    Order:
        switch(x1) {
          1: print_ret (The) x2, " tiene", (n) x2, " mejores cosas que hacer.";
        }

    Places:
        switch(x1) {
          1: print_ret "Has visitado: ";
          2: print_ret ".";
        }

    Pray:
        switch(x1) {
          1: print_ret "Tu plegaria no parece ser escuchada.";
        }

    Prompt:
        switch(x1) {
          1: print "^>";
          2: print "^>>";
        }

    Pronouns:
        switch(x1) {
          1: print_ret "En este momento, ";
          2: print_ret "significa ";
          3: print_ret "no está establecido";
          4: print_ret "significa múltiples objetos";
          5: print_ret "se refiere a algo fuera de alcance";
          6: print_ret "no se refiere a nada";
        }

    Pull:
        switch(x1) {
          1: print_ret "No está fijo", (s) x2, " en el sitio.";
          2: print_ret "Estás simplemente desperdiciando tu energía.";
          3: print_ret "No es algo que puedas mover.";
        }

    Push:
        switch(x1) {
          1: print_ret "No está fijo", (s) x2, " en el sitio.";
          2: print_ret "Estás simplemente desperdiciando tu energía.";
          3: print_ret "No es algo que puedas mover.";
        }

    PushDir:
        switch(x1) {
          1: print_ret "No es algo que puedas mover.";
          2: print_ret "No puedes ir en esa dirección.";
          3: print_ret "No puedes empujar ", (the) x2, " desde aquí.";
        }

    PutOn:
        switch(x1) {
          1: print_ret "Necesitas tener ", (the) x2, " para poder poner", (lo) x2, " en algo.";
          2: print_ret "No puedes poner algo sobre sí mismo.";
          3: print_ret "Poner cosas sobre ", (the) x2, " no serviría de nada.";
          4: print_ret "No tienes espacio en ", (the) x2, " para poner nada más.";
          5: print_ret "Hecho.";
          6: print_ret "Pones ", (the) x2, " sobre ", (the) x3, ".";
          7: print_ret "No tienes espacio en ", (the) x2, " para poner nada más.";
        }

    Quit:
        switch(x1) {
          1: print_ret "Por favor, responde sí o no.";
          2: print_ret "¿Estás seguro de que quieres terminar? ";
        }

    Restart:
        switch(x1) {
          1: print_ret "¿Estás seguro de que quieres reiniciar? ";
          2: print_ret "Error al reiniciar.";
        }

    Restore:
        switch(x1) {
          1: print_ret "Error al cargar.";
          2: print_ret "Ok.";
        }

    Rub:
        switch(x1) {
          1: print_ret "No conseguirás nada frotando ", (the) x2, ".";
        }

    Save:
        switch(x1) {
          1: print_ret "Error al guardar.";
          2: print_ret "Ok.";
        }

    Score:
        switch(x1) {
          1: if (deadflag) print "En ese juego conseguiste "; else print "Hasta ahora has conseguido ";
             print x2, " de un total de ", x3, ", en ", turns, " turno";
             if (turns ~= 1) print "s";
             return;
          2: print_ret "Tu puntuación ha aumentado en ", x2, " punto";
             if (x2 ~= 1) print "s";
          3: print_ret "Tu puntuación ha disminuido en ", x2, " punto";
             if (x2 ~= 1) print "s";
        }

    ScriptOff:
        switch(x1) {
          1: print_ret "Transcripción finalizada.";
          2: print_ret "Intento fallido de finalizar la transcripción.";
          3: print_ret "Transcripción ya finalizada.";
        }

    ScriptOn:
        switch(x1) {
          1: print_ret "Transcripción iniciada.";
          2: print_ret "Intento fallido de iniciar la transcripción.";
          3: print_ret "Transcripción ya iniciada.";
        }

    Search:
        switch(x1) {
          1: print_ret "Pero está demasiado oscuro para ver algo.";
          2: print_ret "No hay nada sobre ", (the) x2, ".";
          3: print_ret "En ", (the) x2, " puedes ver ";
          4: print_ret "No encuentras nada interesante.";
          5: print_ret "No puedes ver dentro ", (del) x2, " porque está", (n) x2, " cerrado", (s) x2, ".";
          6: print_ret (The) x2, " está", (n) x2, " vacío", (s) x2, ".";
          7: print_ret "En ", (the) x2, " puedes ver ";
        }

    Set:
        switch(x1) {
          1: print_ret "No, no puedes ajustar ", (the) x2, ".";
        }

    SetTo:
        switch(x1) {
          1: print_ret "No, no puedes ajustar ", (the) x2, " a nada.";
        }

    Show:
        switch(x1) {
          1: print_ret "No tienes ", (the) x2, ".";
          2: print_ret (The) x3, " no parece", (n) x3, " interesado", (s) x3, ".";
        }

    Sing:
        switch(x1) {
          1: print_ret "Cantas fatal.";
        }

    Sleep:
        switch(x1) {
          1: print_ret "No estás especialmente somnoliento.";
        }

    Smell:
        switch(x1) {
          1: print_ret "No hueles nada extraño.";
        }

    Sorry:
        switch(x1) {
          1: print_ret "No pasa nada.";
        }

    Squeeze:
        switch(x1) {
          1: print_ret "No tiene sentido apretar ", (the) x2, ".";
        }

    Strong:
        switch(x1) {
          1: print_ret "Los verdaderos aventureros no usan ese tipo de lenguaje.";
        }

    Swim:
        switch(x1) {
          1: print_ret "No hay agua suficiente para nadar.";
        }

    Swing:
        switch(x1) {
          1: print_ret "No es algo que puedas balancear.";
        }

    SwitchOff:
        switch(x1) {
          1: print_ret "No puedes apagar ", (the) x2, ".";
          2: print_ret (The) x2, " ya está", (n) x2, " apagado", (s) x2, ".";
          3: print_ret "Apagas ", (the) x2, ".";
          4: print_ret (The) x2, " se apaga.";
        }

    SwitchOn:
        switch(x1) {
          1: print_ret "No puedes encender ", (the) x2, ".";
          2: print_ret (The) x2, " ya está", (n) x2, " encendido", (s) x2, ".";
          3: print_ret "Enciendes ", (the) x2, ".";
          4: print_ret (The) x2, " se enciende.";
        }

    Take:
        switch(x1) {
          1: print_ret "Tomado.";
          2: print_ret "Ya tienes ", (the) x2, ".";
          3: print_ret (The) x2, " parece", (n) x2, " pertenecer a ", (the) x3, ".";
          4: print_ret (The) x2, " parece", (n) x2, " formar parte ", (del) x3, ".";
          5: print_ret "Ya tienes ", (the) x2, ".";
          6: print_ret "No parece", (n) x2, " ser algo que puedas llevarte.";
          7: print_ret (The) x2, " no está", (n) x2, " disponible", (s) x2, ".";
          8: print_ret (The) x2, " está", (n) x2, " fijo", (s) x2, " en el sitio.";
          9: print_ret "Estás llevando demasiadas cosas.";
          10: print_ret "No tienes espacio en ", (the) x2, " para poner nada más.";
          11: print_ret "No puedes quitarte ", (the) x2, ".";
          12: print_ret "No puedes coger ", (the) x2, ".";
          13: print_ret "(primero ", (te) "bajas ", (del) x3, ")";
          14: print_ret "Coges ", (the) x2, ".";
          15: print_ret "Recoges ", (the) x2, ".";
        }

    Taste:
        switch(x1) {
          1: print_ret "No saboreas nada inesperado.";
        }

    Tell:
        switch(x1) {
          1: print_ret "Hablas contigo mismo durante un rato.";
          2: print_ret "No parece que ", (the) x2, " esté", (n) x2, " interesado", (s) x2, ".";
        }

    Think:
        switch(x1) {
          1: print_ret "Qué buena idea.";
        }

    ThrowAt:
        switch(x1) {
          1: print_ret "No serviría de nada.";
          2: print_ret "En el último momento te echas atrás.";
        }

    ThrownAt:
        switch(x1) {
          1: print_ret "No tienes muy buena puntería.";
        }

    Tie:
        switch(x1) {
          1: print_ret "No puedes atar ", (the) x2, " a nada.";
        }

    Touch:
        switch(x1) {
          1: print_ret "No notas nada extraño al tacto.";
          2: print_ret "No creo que ", (al) x2, " le", (s) x2, " gustaría.";
        }

    Turn:
        switch(x1) {
          1: print_ret "No sucede nada.";
          2: print_ret "No es algo que puedas girar.";
        }

    Unlock:
        switch(x1) {
          1: print_ret "No puedes desbloquear ", (the) x2, ".";
          2: print_ret (The) x2, " ya tiene", (n) x2, " abierta la cerradura.";
          3: print_ret (The) x2, " no parece", (n) x2, " tener cerradura.";
          4: print_ret "No tienes la llave correcta.";
          5: print_ret "Desbloqueas ", (the) x2, ".";
        }

    VagueGo:
        switch(x1) {
          1: print_ret "Tienes que indicar en qué dirección ir.";
        }

    Verify:
        switch(x1) {
          1: print_ret "El fichero de juego ha verificado correctamente.";
          2: print_ret "El fichero de juego no ha verificado correctamente, y puede estar corrupto.";
        }

    Version:
        switch(x1) {
          1: print "Historia: ";
          2: print "Intérprete: ";
          3: print " / Librería: ";
        }

    Wait:
        switch(x1) {
          1: print_ret "Pasa el tiempo...";
        }

    Wake:
        switch(x1) {
          1: print_ret "No parece que estés dormido.";
        }

    WakeOther:
        switch(x1) {
          1: print_ret "No parece necesario hacer eso.";
        }

    Wave:
        switch(x1) {
          1: print_ret "No tienes ", (the) x2, ".";
          2: print_ret "Te sientes ridículo agitando ", (the) x2, ".";
        }

    WaveHands:
        switch(x1) {
          1: print_ret "Agitas tus manos.";
          2: print_ret "Estás demasiado ocupado para saludar.";
        }

    Wear:
        switch(x1) {
          1: print_ret "No puedes ponerte eso.";
          2: print_ret "No tienes ", (the) x2, ".";
          3: print_ret "Ya llevas puesto ", (the) x2, ".";
          4: print_ret "Te pones ", (the) x2, ".";
        }

    Yes:
        switch(x1) {
          1: print_ret "Esa era una pregunta retórica.";
          2: print_ret "Has contestado afirmativamente.";
        }
  }
];

! Funciones auxiliares para manejar género y número en español
[ es obj;
    if (obj has pluralname) print "son"; else print "es";
];

[ esta obj;
    if (obj has pluralname) print "están"; else print "está";
];

[ n obj;
    if (obj has pluralname) print "n"; else print "";
];

[ s obj;
    if (obj has pluralname) print "s"; else print "";
];

[ o obj;
    if (obj has female) print "a"; else print "o";
];

[ lo obj;
    if (obj has female) print "la"; else print "lo";
];

[ te;
    print "te";
];

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

#Endif;

! ==============================================================================