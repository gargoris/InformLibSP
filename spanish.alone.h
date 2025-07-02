! spanish.h - Archivo puente para compatibilidad con el compilador
! Este archivo es cargado automáticamente por el flag +language_name=spanish
! y define las constantes básicas necesarias para el idioma español.

System_file;

! Definir tabla de caracteres para español
! Usamos códigos hexadecimales para evitar problemas de codificación
Zcharacter table + '@{E1}' '@{E9}' '@{ED}' '@{F3}' '@{FA}' '@{FC}' '@{F1}' 
               '@{C1}' '@{C9}' '@{CD}' '@{D3}' '@{DA}' '@{DC}' '@{D1}'
               '@{BF}' '@{A1}';

! Definir constantes básicas para el idioma español
#Ifndef SPANISH_H_INCLUDED;
Constant SPANISH_H_INCLUDED;

! Constantes requeridas por Parser.h
Constant LanguageContractionForms = 1;

! Constantes para mensajes del sistema
Constant Inventory = 1;
Constant Take = 2;
Constant Drop = 3;
Constant Throw = 4;
Constant PutOn = 5;
Constant Insert = 6;
Constant Remove = 7;
Constant PluralFound = 8;
Constant ListMiscellany = 9;
Constant Miscellany = 10;
Constant Prompt = 11;
Constant Open = 12;
Constant Close = 13;
Constant Lock = 14;
Constant Unlock = 15;
Constant SwitchOn = 16;
Constant SwitchOff = 17;
Constant Enter = 18;
Constant Exit = 19;
Constant EmptyT = 20;
Constant Give = 21;
Constant Show = 22;
Constant Wear = 23;
Constant Disrobe = 24;
Constant Eat = 25;
Constant Yes = 26;
Constant No = 27;
Constant Burn = 28;
Constant Wake = 29;
Constant WakeOther = 30;
Constant Consult = 31;
Constant Kiss = 32;
Constant Think = 33;
Constant Smell = 34;
Constant Listen = 35;
Constant Taste = 36;
Constant Touch = 37;
Constant Dig = 38;
Constant Cut = 39;
Constant Jump = 40;
Constant JumpOver = 41;
Constant Tie = 42;
Constant Drink = 43;
Constant Fill = 44;
Constant Sorry = 45;
Constant Strong = 46;
Constant Mild = 47;
Constant Attack = 48;
Constant Swim = 49;
Constant Swing = 50;
Constant Blow = 51;
Constant Pray = 52;
Constant Push = 53;
Constant PushDir = 54;
Constant Turn = 55;
Constant Squeeze = 56;
Constant WaveHands = 57;
Constant Wave = 58;
Constant Pull = 59;
Constant Set = 60;
Constant SetTo = 61;
Constant Search = 62;
Constant Tell = 63;
Constant Answer = 64;
Constant Buy = 65;
Constant Ask = 66;
Constant AskFor = 67;
Constant Sing = 68;
Constant Sleep = 69;
Constant Climb = 70;
Constant Wait = 71;
Constant Examine = 72;
Constant Read = 73;
Constant LMode1 = 74;
Constant LMode2 = 75;
Constant LMode3 = 76;
Constant Look = 77;
Constant Places = 78;
Constant Objects = 79;
Constant Score = 80;
Constant Quit = 81;
Constant Restart = 82;
Constant Restore = 83;
Constant Verify = 84;
Constant Save = 85;
Constant Script = 86;
Constant Noscript = 87;
Constant Version = 88;
Constant Again = 89;
Constant Undo = 90;
Constant Polish = 91;
Constant Pronouns = 92;
Constant NotifyOn = 93;
Constant NotifyOff = 94;
Constant Trace = 95;
Constant TraceLevel = 96;
Constant TraceOff = 97;
Constant CommandsOn = 98;
Constant CommandsOff = 99;
Constant CommandsRead = 100;
Constant Scope = 101;
Constant Superbrief = 102;
Constant Verbose = 103;
Constant Normal = 104;
Constant Predictable = 105;

! Constantes de texto requeridas
Constant DARKNESS__TX     = "Oscuridad";
Constant YOURSELF__TX     = "ti mismo";
Constant THE__TX          = "el";

! Definir arrays necesarios
Array LanguageGNAsToArticles --> 0 0 0 0 0 0 0 0 0 0 0 0;

! Implementación mejorada de LanguageLM para mensajes en español
[ LanguageLM n x1 x2;
    switch (n) {
        ! Mensajes básicos para Inventory
        Inventory: 
            switch (x1) {
                1: print "No llevas nada.^";
                2: print "Llevas";
                3: print "llevas";
                default: print "[Mensaje Inventory ", x1, "]";
            }
            rtrue;
        
        ! Mensajes básicos para Take
        Take:
            switch (x1) {
                1: print "Tomado.";
                2: print "Siempre te tienes a ti mismo.";
                5: print "Ya tienes eso.";
                9: print "Llevas demasiadas cosas ya.";
                10: print "(primero lo coges)^";
                default: print "[Mensaje Take ", x1, "]";
            }
            rtrue;
        
        ! Mensajes básicos para Drop
        Drop:
            switch (x1) {
                1: print "Eso ya est@{E1} aqu@{ED}.";
                2: print "No tienes eso.";
                4: print "Dejado.";
                default: print "[Mensaje Drop ", x1, "]";
            }
            rtrue;
        
        ! Mensajes básicos para Look
        Look:
            switch (x1) {
                3: print "Est@{E1} demasiado oscuro, no puedes ver nada.";
                default: print "[Mensaje Look ", x1, "]";
            }
            rtrue;
        
        ! Mensajes básicos para Examine
        Examine:
            switch (x1) {
                1: print "La oscuridad, sustantivo. Una ausencia de luz que ver o por la que ver.";
                2: print "No ves nada especial en eso.";
                default: print "[Mensaje Examine ", x1, "]";
            }
            rtrue;
        
        ! Mensajes básicos para Open/Close
        Open:
            switch (x1) {
                1: print "Eso no se puede abrir.";
                2: print "Est@{E1} cerrado con llave.";
                3: print "Ya est@{E1} abierto.";
                5: print "Abierto.";
                default: print "[Mensaje Open ", x1, "]";
            }
            rtrue;
        
        Close:
            switch (x1) {
                1: print "Eso no se puede cerrar.";
                2: print "Ya est@{E1} cerrado.";
                3: print "Cerrado.";
                default: print "[Mensaje Close ", x1, "]";
            }
            rtrue;
        
        ! Mensajes básicos para Enter
        Enter:
            switch (x1) {
                1: print "Ya est@{E1}s ah@{ED}.";
                2: print "No puedes entrar en eso.";
                3: print "Est@{E1} cerrado.";
                5: print "Entras.";
                default: print "[Mensaje Enter ", x1, "]";
            }
            rtrue;
        
        ! Mensajes básicos para Drink
        Drink:
            switch (x1) {
                1: print "Eso no parece potable.";
                2: print "Bebes. No est@{E1} mal.";
                default: print "[Mensaje Drink ", x1, "]";
            }
            rtrue;
            
        ! Mensajes básicos para Miscellany (varios)
        Miscellany:
            switch (x1) {
                1: print "(Encendiendo la luz)";
                2: print "(Apagando la luz)";
                3: print "Est@{E1} demasiado oscuro para ver algo.";
                4: print "No puedes hacer eso.";
                5: print "No puedes ver nada.";
                6: print "No tienes eso.";
                7: print "No puedes tener eso.";
                8: print "Ya tienes eso.";
                9: print "No puedes ir por ah@{ED}.";
                10: print "No puedes hacer eso.";
                11: print "No ves eso.";
                12: print "No puedes ver nada interesante.";
                13: print "(No puedes llevar m@{E1}s cosas)";
                14: print "(Est@{E1} demasiado oscuro)";
                15: print "Hecho.";
                16: print "No tienes nada que dejar.";
                17: print "No hay nada que hacer.";
                18: print "No hay nada que examinar.";
                19: print "No hay nada que tomar.";
                20: print "No hay nada que abrir.";
                21: print "No hay nada que cerrar.";
                22: print "No hay nada que desbloquear.";
                23: print "No hay nada que bloquear.";
                24: print "No hay nada que encender.";
                25: print "No hay nada que apagar.";
                26: print "No hay nada que comer.";
                27: print "No hay nada que beber.";
                28: print "No hay nada que ponerse.";
                29: print "No hay nada que quitarse.";
                30: print "No hay nada que buscar.";
                31: print "No hay nada que escuchar.";
                32: print "No hay nada que oler.";
                33: print "No hay nada que tocar.";
                34: print "No hay nada que cortar.";
                35: print "No hay nada que atar.";
                36: print "No hay nada que desatar.";
                37: print "No hay nada que empujar.";
                38: print "No hay nada que tirar.";
                39: print "No hay nada que girar.";
                40: print "No hay nada que apretar.";
                41: print "No hay nada que frotar.";
                42: print "No hay nada que lanzar.";
                43: print "No hay nada que atacar.";
                44: print "No hay nada que romper.";
                45: print "No hay nada que cavar.";
                46: print "No hay nada que quemar.";
                47: print "No hay nada que comprar.";
                48: print "No hay nada que cantar.";
                49: print "No hay nada que escalar.";
                50: print "No hay nada que soplar.";
                51: print "No hay nada que rezar.";
                52: print "No hay nada que despertar.";
                53: print "No hay nada que besar.";
                54: print "No hay nada que consultar.";
                55: print "No hay nada que saltar.";
                56: print "No hay nada que nadar.";
                57: print "No hay nada que balancear.";
                58: print "No hay nada que oler.";
                59: print "No hay nada que limpiar.";
                60: print "No hay nada que ajustar.";
                61: print "No hay nada que llenar.";
                62: print "No hay nada que vaciar.";
                63: print "No hay nada que agitar.";
                64: print "No hay nada que acariciar.";
                65: print "No hay nada que pulsar.";
                66: print "No hay nada que tirar.";
                67: print "No hay nada que arrastrar.";
                68: print "No hay nada que girar.";
                69: print "No hay nada que apretar.";
                70: print "No hay nada que frotar.";
                71: print "No hay nada que lanzar.";
                72: print "No hay nada que atacar.";
                73: print "No hay nada que romper.";
                74: print "No hay nada que cavar.";
                75: print "No hay nada que quemar.";
                76: print "No hay nada que comprar.";
                77: print "No hay nada que cantar.";
                78: print "No hay nada que escalar.";
                79: print "No hay nada que soplar.";
                80: print "No hay nada que rezar.";
                81: print "No hay nada que despertar.";
                82: print "No hay nada que besar.";
                83: print "No hay nada que consultar.";
                84: print "No hay nada que saltar.";
                85: print "No hay nada que nadar.";
                86: print "No hay nada que balancear.";
                87: print "No hay nada que oler.";
                88: print "No hay nada que limpiar.";
                89: print "No hay nada que ajustar.";
                90: print "No hay nada que llenar.";
                91: print "No hay nada que vaciar.";
                92: print "No hay nada que agitar.";
                93: print "No hay nada que acariciar.";
                94: print "No hay nada que pulsar.";
                default: print "[Mensaje Miscellany ", x1, "]";
            }
            rtrue;
        
        ! Mensajes por defecto
        default:
            print "[Mensaje ", n, " ", x1, "]";
            rtrue;
    }
];

#Endif;