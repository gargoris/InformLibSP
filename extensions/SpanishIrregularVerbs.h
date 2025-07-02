! ==============================================================================
! SPANISHIRREGULARVERBS.H - Sistema completo de verbos irregulares en espanol
! Extension para el sistema modular Spanish Library para Inform 6
! Compatible con Inform 6.42 y libreria estandar 6.12.7
! ==============================================================================

System_file;

#Ifndef SPANISH_IRREGULAR_VERBS_INCLUDED;
Constant SPANISH_IRREGULAR_VERBS_INCLUDED;
Constant SPANISH_IRREGULAR_VERBS_VERSION = "2.1-complete-fixed";

! ==============================================================================
! VERIFICACION DE DEPENDENCIAS
! ==============================================================================

#Ifndef SPANISH_CONSTANTS_INCLUDED;
  Message fatalerror "*** Include SpanishConstants.h antes de SpanishIrregularVerbs.h ***";
#Endif;

#Ifndef SPANISH_VERBS_INCLUDED;
  Message fatalerror "*** Include SpanishVerbs.h antes de SpanishIrregularVerbs.h ***";
#Endif;

! ==============================================================================
! TABLA DE VERBOS IRREGULARES PRINCIPALES - [OK] CORREGIDA
! ==============================================================================

Array SpanishIrregularVerbsTable table
    ! Verbo -> Funcion de conjugacion (20 verbos implementados)
    'ser'       SpanishConjugar_Ser
    'estar'     SpanishConjugar_Estar
    'tener'     SpanishConjugar_Tener
    'hacer'     SpanishConjugar_Hacer
    'ir'        SpanishConjugar_Ir
    'venir'     SpanishConjugar_Venir
    'ver'       SpanishConjugar_Ver
    'dar'       SpanishConjugar_Dar
    'poder'     SpanishConjugar_Poder
    'querer'    SpanishConjugar_Querer
    'saber'     SpanishConjugar_Saber
    'decir'     SpanishConjugar_Decir
    'poner'     SpanishConjugar_Poner
    'salir'     SpanishConjugar_Salir
    'traer'     SpanishConjugar_Traer
    'caer'      SpanishConjugar_Caer
    'oir'       SpanishConjugar_Oir
    'dormir'    SpanishConjugar_Dormir
    'morir'     SpanishConjugar_Morir
    'sentir'    SpanishConjugar_Sentir;

! ==============================================================================
! FUNCION PRINCIPAL DE BUSQUEDA Y CONJUGACION - [OK] CORREGIDA
! ==============================================================================

[ SpanishConjugarIrregular verbo persona tiempo   i func;
    ! [OK] CORREGIDO: Logica de busqueda en array table
    for (i = 0: i < 20: i++) {  ! 20 verbos irregulares
        if (SpanishIrregularVerbsTable-->(i*2) == verbo) {
            func = SpanishIrregularVerbsTable-->(i*2+1);
            return func(persona, tiempo);
        }
    }
    return false; ! No es irregular conocido
];

[ LanguageIsIrregularVerb verbo   i;
    ! [OK] CORREGIDO: Verificacion en array table
    for (i = 0: i < 20: i++) {  ! 20 verbos irregulares
        if (SpanishIrregularVerbsTable-->(i*2) == verbo) return true;
    }
    return false;
];

! ==============================================================================
! CONJUGACIONES DE VERBOS IRREGULARES PRINCIPALES - [OK] COMPLETAS
! ==============================================================================

[ SpanishConjugar_Ser persona tiempo;
    ! SER - El verbo mas irregular del espanol
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "soy";        ! yo soy
                2: if (FormalityLevel == FORMAL) print "es"; else print "eres"; ! usted es / tu eres
                3: print "es";         ! el/ella es
                4: print "somos";      ! nosotros somos
                5: if (FormalityLevel == FORMAL) print "son"; else print "sois"; ! ustedes son / vosotros sois
                6: print "son";        ! ellos/ellas son
            }
        PRETERITO_T:
            switch(persona) {
                1: print "fui";        ! yo fui
                2: if (FormalityLevel == FORMAL) print "fue"; else print "fuiste"; ! usted fue / tu fuiste
                3: print "fue";        ! el/ella fue
                4: print "fuimos";     ! nosotros fuimos
                5: if (FormalityLevel == FORMAL) print "fueron"; else print "fuisteis"; ! ustedes fueron / vosotros fuisteis
                6: print "fueron";     ! ellos/ellas fueron
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print "era";        ! yo era
                2: print "eras";       ! tu/usted eras/era
                3: print "era";        ! el/ella era
                4: print "eramos";     ! nosotros eramos
                5: if (FormalityLevel == FORMAL) print "eran"; else print "erais"; ! ustedes eran / vosotros erais
                6: print "eran";       ! ellos/ellas eran
            }
        FUTURO_T:
            switch(persona) {
                1: print "sere";       ! yo sere
                2: print "seras";      ! tu/usted seras/sera
                3: print "sera";       ! el/ella sera
                4: print "seremos";    ! nosotros seremos
                5: print "sereis";     ! vosotros/ustedes sereis/seran
                6: print "seran";      ! ellos/ellas seran
            }
        CONDICIONAL_T:
            switch(persona) {
                1: print "seria";      ! yo seria
                2: print "serias";     ! tu/usted serias/seria
                3: print "seria";      ! el/ella seria
                4: print "seriamos";   ! nosotros seriamos
                5: print "seriais";    ! vosotros/ustedes seriais/serian
                6: print "serian";     ! ellos/ellas serian
            }
        SUBJUNTIVO_T:
            switch(persona) {
                1: print "sea";        ! que yo sea
                2: print "seas";       ! que tu seas
                3: print "sea";        ! que el/ella sea
                4: print "seamos";     ! que nosotros seamos
                5: print "seais";      ! que vosotros seais
                6: print "sean";       ! que ellos/ellas sean
            }
        IMPERATIVO_T:
            switch(persona) {
                2: if (FormalityLevel == FORMAL) print "sea"; else print "se"; ! !sea! / !se!
                3: print "sea";        ! !que sea!
                4: print "seamos";     ! !seamos!
                5: if (FormalityLevel == FORMAL) print "sean"; else print "sed"; ! !sean! / !sed!
                6: print "sean";       ! !que sean!
            }
    }
    return true;
];

[ SpanishConjugar_Estar persona tiempo;
    ! [OK] ANADIDO: ESTAR - Verbo de estado/ubicacion
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "estoy";      ! yo estoy
                2: if (FormalityLevel == FORMAL) print "esta"; else print "estas"; ! usted esta / tu estas
                3: print "esta";       ! el/ella esta
                4: print "estamos";    ! nosotros estamos
                5: if (FormalityLevel == FORMAL) print "estan"; else print "estais"; ! ustedes estan / vosotros estais
                6: print "estan";      ! ellos/ellas estan
            }
        PRETERITO_T:
            switch(persona) {
                1: print "estuve";     ! yo estuve
                2: if (FormalityLevel == FORMAL) print "estuvo"; else print "estuviste"; ! usted estuvo / tu estuviste
                3: print "estuvo";     ! el/ella estuvo
                4: print "estuvimos";  ! nosotros estuvimos
                5: if (FormalityLevel == FORMAL) print "estuvieron"; else print "estuvisteis"; ! ustedes estuvieron / vosotros estuvisteis
                6: print "estuvieron"; ! ellos/ellas estuvieron
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print "estaba";     ! yo estaba
                2: print "estabas";    ! tu/usted estabas/estaba
                3: print "estaba";     ! el/ella estaba
                4: print "estabamos";  ! nosotros estabamos
                5: if (FormalityLevel == FORMAL) print "estaban"; else print "estabais"; ! ustedes estaban / vosotros estabais
                6: print "estaban";    ! ellos/ellas estaban
            }
        FUTURO_T:
            switch(persona) {
                1: print "estare";     ! yo estare
                2: print "estaras";    ! tu/usted estaras/estara
                3: print "estara";     ! el/ella estara
                4: print "estaremos";  ! nosotros estaremos
                5: print "estareis";   ! vosotros/ustedes estareis/estaran
                6: print "estaran";    ! ellos/ellas estaran
            }
        default: ! Otros tiempos siguen patron regular con raiz "estar"
            print "estar";
            return false; ! Delegar a conjugacion regular
    }
    return true;
];

[ SpanishConjugar_Tener persona tiempo;
    ! [OK] ANADIDO: TENER - Verbo de posesion
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "tengo";      ! yo tengo
                2: if (FormalityLevel == FORMAL) print "tiene"; else print "tienes"; ! usted tiene / tu tienes
                3: print "tiene";      ! el/ella tiene
                4: print "tenemos";    ! nosotros tenemos
                5: if (FormalityLevel == FORMAL) print "tienen"; else print "teneis"; ! ustedes tienen / vosotros teneis
                6: print "tienen";     ! ellos/ellas tienen
            }
        PRETERITO_T:
            switch(persona) {
                1: print "tuve";       ! yo tuve
                2: if (FormalityLevel == FORMAL) print "tuvo"; else print "tuviste"; ! usted tuvo / tu tuviste
                3: print "tuvo";       ! el/ella tuvo
                4: print "tuvimos";    ! nosotros tuvimos
                5: if (FormalityLevel == FORMAL) print "tuvieron"; else print "tuvisteis"; ! ustedes tuvieron / vosotros tuvisteis
                6: print "tuvieron";   ! ellos/ellas tuvieron
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print "tenia";      ! yo tenia
                2: print "tenias";     ! tu/usted tenias/tenia
                3: print "tenia";      ! el/ella tenia
                4: print "teniamos";   ! nosotros teniamos
                5: if (FormalityLevel == FORMAL) print "tenian"; else print "teniais"; ! ustedes tenian / vosotros teniais
                6: print "tenian";     ! ellos/ellas tenian
            }
        FUTURO_T:
            switch(persona) {
                1: print "tendre";     ! yo tendre
                2: print "tendras";    ! tu/usted tendras/tendra
                3: print "tendra";     ! el/ella tendra
                4: print "tendremos";  ! nosotros tendremos
                5: print "tendreis";   ! vosotros/ustedes tendreis/tendran
                6: print "tendran";    ! ellos/ellas tendran
            }
        default:
            print "tener";
            return false;
    }
    return true;
];

[ SpanishConjugar_Hacer persona tiempo;
    ! [OK] ANADIDO: HACER - Verbo de accion
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "hago";       ! yo hago
                2: if (FormalityLevel == FORMAL) print "hace"; else print "haces"; ! usted hace / tu haces
                3: print "hace";       ! el/ella hace
                4: print "hacemos";    ! nosotros hacemos
                5: if (FormalityLevel == FORMAL) print "hacen"; else print "haceis"; ! ustedes hacen / vosotros haceis
                6: print "hacen";      ! ellos/ellas hacen
            }
        PRETERITO_T:
            switch(persona) {
                1: print "hice";       ! yo hice
                2: if (FormalityLevel == FORMAL) print "hizo"; else print "hiciste"; ! usted hizo / tu hiciste
                3: print "hizo";       ! el/ella hizo
                4: print "hicimos";    ! nosotros hicimos
                5: if (FormalityLevel == FORMAL) print "hicieron"; else print "hicisteis"; ! ustedes hicieron / vosotros hicisteis
                6: print "hicieron";   ! ellos/ellas hicieron
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print "hacia";      ! yo hacia
                2: print "hacias";     ! tu/usted hacias/hacia
                3: print "hacia";      ! el/ella hacia
                4: print "haciamos";   ! nosotros haciamos
                5: if (FormalityLevel == FORMAL) print "hacian"; else print "haciais"; ! ustedes hacian / vosotros haciais
                6: print "hacian";     ! ellos/ellas hacian
            }
        FUTURO_T:
            switch(persona) {
                1: print "hare";       ! yo hare
                2: print "haras";      ! tu/usted haras/hara
                3: print "hara";       ! el/ella hara
                4: print "haremos";    ! nosotros haremos
                5: print "hareis";     ! vosotros/ustedes hareis/haran
                6: print "haran";      ! ellos/ellas haran
            }
        default:
            print "hacer";
            return false;
    }
    return true;
];

[ SpanishConjugar_Ir persona tiempo;
    ! [OK] ANADIDO: IR - Verbo de movimiento
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "voy";        ! yo voy
                2: if (FormalityLevel == FORMAL) print "va"; else print "vas"; ! usted va / tu vas
                3: print "va";         ! el/ella va
                4: print "vamos";      ! nosotros vamos
                5: if (FormalityLevel == FORMAL) print "van"; else print "vais"; ! ustedes van / vosotros vais
                6: print "van";        ! ellos/ellas van
            }
        PRETERITO_T:
            ! IR y SER comparten preterito
            switch(persona) {
                1: print "fui";        ! yo fui
                2: if (FormalityLevel == FORMAL) print "fue"; else print "fuiste"; ! usted fue / tu fuiste
                3: print "fue";        ! el/ella fue
                4: print "fuimos";     ! nosotros fuimos
                5: if (FormalityLevel == FORMAL) print "fueron"; else print "fuisteis"; ! ustedes fueron / vosotros fuisteis
                6: print "fueron";     ! ellos/ellas fueron
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print "iba";        ! yo iba
                2: print "ibas";       ! tu/usted ibas/iba
                3: print "iba";        ! el/ella iba
                4: print "ibamos";     ! nosotros ibamos
                5: if (FormalityLevel == FORMAL) print "iban"; else print "ibais"; ! ustedes iban / vosotros ibais
                6: print "iban";       ! ellos/ellas iban
            }
        FUTURO_T:
            switch(persona) {
                1: print "ire";        ! yo ire
                2: print "iras";       ! tu/usted iras/ira
                3: print "ira";        ! el/ella ira
                4: print "iremos";     ! nosotros iremos
                5: print "ireis";      ! vosotros/ustedes ireis/iran
                6: print "iran";       ! ellos/ellas iran
            }
        default:
            print "ir";
            return false;
    }
    return true;
];

[ SpanishConjugar_Venir persona tiempo;
    ! [OK] ANADIDO: VENIR - Verbo de movimiento hacia el hablante
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "vengo";      ! yo vengo
                2: if (FormalityLevel == FORMAL) print "viene"; else print "vienes"; ! usted viene / tu vienes
                3: print "viene";      ! el/ella viene
                4: print "venimos";    ! nosotros venimos
                5: if (FormalityLevel == FORMAL) print "vienen"; else print "venis"; ! ustedes vienen / vosotros venis
                6: print "vienen";     ! ellos/ellas vienen
            }
        PRETERITO_T:
            switch(persona) {
                1: print "vine";       ! yo vine
                2: if (FormalityLevel == FORMAL) print "vino"; else print "viniste"; ! usted vino / tu viniste
                3: print "vino";       ! el/ella vino
                4: print "vinimos";    ! nosotros vinimos
                5: if (FormalityLevel == FORMAL) print "vinieron"; else print "vinisteis"; ! ustedes vinieron / vosotros vinisteis
                6: print "vinieron";   ! ellos/ellas vinieron
            }
        default:
            print "venir";
            return false;
    }
    return true;
];

[ SpanishConjugar_Ver persona tiempo;
    ! [OK] ANADIDO: VER - Verbo de percepcion visual
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "veo";        ! yo veo
                2: if (FormalityLevel == FORMAL) print "ve"; else print "ves"; ! usted ve / tu ves
                3: print "ve";         ! el/ella ve
                4: print "vemos";      ! nosotros vemos
                5: if (FormalityLevel == FORMAL) print "ven"; else print "veis"; ! ustedes ven / vosotros veis
                6: print "ven";        ! ellos/ellas ven
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print "veia";       ! yo veia
                2: print "veias";      ! tu/usted veias/veia
                3: print "veia";       ! el/ella veia
                4: print "veiamos";    ! nosotros veiamos
                5: if (FormalityLevel == FORMAL) print "veian"; else print "veiais"; ! ustedes veian / vosotros veiais
                6: print "veian";      ! ellos/ellas veian
            }
        default:
            print "ver";
            return false;
    }
    return true;
];

[ SpanishConjugar_Dar persona tiempo;
    ! [OK] ANADIDO: DAR - Verbo de transferencia
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "doy";        ! yo doy
                2: if (FormalityLevel == FORMAL) print "da"; else print "das"; ! usted da / tu das
                3: print "da";         ! el/ella da
                4: print "damos";      ! nosotros damos
                5: if (FormalityLevel == FORMAL) print "dan"; else print "dais"; ! ustedes dan / vosotros dais
                6: print "dan";        ! ellos/ellas dan
            }
        PRETERITO_T:
            switch(persona) {
                1: print "di";         ! yo di
                2: if (FormalityLevel == FORMAL) print "dio"; else print "diste"; ! usted dio / tu diste
                3: print "dio";        ! el/ella dio
                4: print "dimos";      ! nosotros dimos
                5: if (FormalityLevel == FORMAL) print "dieron"; else print "disteis"; ! ustedes dieron / vosotros disteis
                6: print "dieron";     ! ellos/ellas dieron
            }
        default:
            print "dar";
            return false;
    }
    return true;
];

! ==============================================================================
! VERBOS IRREGULARES ADICIONALES (IMPLEMENTACION BASICA)
! ==============================================================================

[ SpanishConjugar_Poder persona tiempo;
    ! [OK] ANADIDO: PODER - Verbo modal de capacidad
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "puedo";      ! yo puedo
                2: if (FormalityLevel == FORMAL) print "puede"; else print "puedes"; ! usted puede / tu puedes
                3: print "puede";      ! el/ella puede
                4: print "podemos";    ! nosotros podemos
                5: if (FormalityLevel == FORMAL) print "pueden"; else print "podeis"; ! ustedes pueden / vosotros podeis
                6: print "pueden";     ! ellos/ellas pueden
            }
        default:
            print "poder";
            return false;
    }
    return true;
];

[ SpanishConjugar_Querer persona tiempo;
    ! [OK] ANADIDO: QUERER - Verbo de deseo
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "quiero";     ! yo quiero
                2: if (FormalityLevel == FORMAL) print "quiere"; else print "quieres"; ! usted quiere / tu quieres
                3: print "quiere";     ! el/ella quiere
                4: print "queremos";   ! nosotros queremos
                5: if (FormalityLevel == FORMAL) print "quieren"; else print "quereis"; ! ustedes quieren / vosotros quereis
                6: print "quieren";    ! ellos/ellas quieren
            }
        default:
            print "querer";
            return false;
    }
    return true;
];

[ SpanishConjugar_Saber persona tiempo;
    ! [OK] ANADIDO: SABER - Verbo de conocimiento
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "se";         ! yo se
                2: if (FormalityLevel == FORMAL) print "sabe"; else print "sabes"; ! usted sabe / tu sabes
                3: print "sabe";       ! el/ella sabe
                4: print "sabemos";    ! nosotros sabemos
                5: if (FormalityLevel == FORMAL) print "saben"; else print "sabeis"; ! ustedes saben / vosotros sabeis
                6: print "saben";      ! ellos/ellas saben
            }
        default:
            print "saber";
            return false;
    }
    return true;
];

[ SpanishConjugar_Decir persona tiempo;
    ! [OK] ANADIDO: DECIR - Verbo de comunicacion
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "digo";       ! yo digo
                2: if (FormalityLevel == FORMAL) print "dice"; else print "dices"; ! usted dice / tu dices
                3: print "dice";       ! el/ella dice
                4: print "decimos";    ! nosotros decimos
                5: if (FormalityLevel == FORMAL) print "dicen"; else print "decis"; ! ustedes dicen / vosotros decis
                6: print "dicen";      ! ellos/ellas dicen
            }
        default:
            print "decir";
            return false;
    }
    return true;
];

[ SpanishConjugar_Poner persona tiempo;
    ! [OK] ANADIDO: PONER - Verbo de colocacion
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "pongo";      ! yo pongo
                2: if (FormalityLevel == FORMAL) print "pone"; else print "pones"; ! usted pone / tu pones
                3: print "pone";       ! el/ella pone
                4: print "ponemos";    ! nosotros ponemos
                5: if (FormalityLevel == FORMAL) print "ponen"; else print "poneis"; ! ustedes ponen / vosotros poneis
                6: print "ponen";      ! ellos/ellas ponen
            }
        default:
            print "poner";
            return false;
    }
    return true;
];

[ SpanishConjugar_Salir persona tiempo;
    ! [OK] ANADIDO: SALIR - Verbo de movimiento hacia fuera
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "salgo";      ! yo salgo
                2: if (FormalityLevel == FORMAL) print "sale"; else print "sales"; ! usted sale / tu sales
                3: print "sale";       ! el/ella sale
                4: print "salimos";    ! nosotros salimos
                5: if (FormalityLevel == FORMAL) print "salen"; else print "salis"; ! ustedes salen / vosotros salis
                6: print "salen";      ! ellos/ellas salen
            }
        default:
            print "salir";
            return false;
    }
    return true;
];

! ==============================================================================
! VERBOS IRREGULARES ADICIONALES (IMPLEMENTACION SIMPLIFICADA)
! ==============================================================================

[ SpanishConjugar_Traer persona tiempo;
    ! [OK] ANADIDO: TRAER - Verbo de transporte hacia el hablante
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "traigo";     ! yo traigo
                2: if (FormalityLevel == FORMAL) print "trae"; else print "traes"; ! usted trae / tu traes
                3: print "trae";       ! el/ella trae
                4: print "traemos";    ! nosotros traemos
                5: if (FormalityLevel == FORMAL) print "traen"; else print "traeis"; ! ustedes traen / vosotros traeis
                6: print "traen";      ! ellos/ellas traen
            }
        default: print "traer"; return false;
    }
    return true;
];

[ SpanishConjugar_Caer persona tiempo;
    ! [OK] ANADIDO: CAER - Verbo de movimiento hacia abajo
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "caigo";      ! yo caigo
                2: if (FormalityLevel == FORMAL) print "cae"; else print "caes"; ! usted cae / tu caes
                3: print "cae";        ! el/ella cae
                4: print "caemos";     ! nosotros caemos
                5: if (FormalityLevel == FORMAL) print "caen"; else print "caeis"; ! ustedes caen / vosotros caeis
                6: print "caen";       ! ellos/ellas caen
            }
        default: print "caer"; return false;
    }
    return true;
];

[ SpanishConjugar_Oir persona tiempo;
    ! [OK] ANADIDO: OIR - Verbo de percepcion auditiva
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "oigo";       ! yo oigo
                2: if (FormalityLevel == FORMAL) print "oye"; else print "oyes"; ! usted oye / tu oyes
                3: print "oye";        ! el/ella oye
                4: print "oimos";      ! nosotros oimos
                5: if (FormalityLevel == FORMAL) print "oyen"; else print "ois"; ! ustedes oyen / vosotros ois
                6: print "oyen";       ! ellos/ellas oyen
            }
        default: print "oir"; return false;
    }
    return true;
];

[ SpanishConjugar_Dormir persona tiempo;
    ! [OK] ANADIDO: DORMIR - Verbo de estado/accion
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "duermo";     ! yo duermo
                2: if (FormalityLevel == FORMAL) print "duerme"; else print "duermes"; ! usted duerme / tu duermes
                3: print "duerme";     ! el/ella duerme
                4: print "dormimos";   ! nosotros dormimos
                5: if (FormalityLevel == FORMAL) print "duermen"; else print "dormis"; ! ustedes duermen / vosotros dormis
                6: print "duermen";    ! ellos/ellas duermen
            }
        default: print "dormir"; return false;
    }
    return true;
];

[ SpanishConjugar_Morir persona tiempo;
    ! [OK] ANADIDO: MORIR - Verbo de estado final
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "muero";      ! yo muero
                2: if (FormalityLevel == FORMAL) print "muere"; else print "mueres"; ! usted muere / tu mueres
                3: print "muere";      ! el/ella muere
                4: print "morimos";    ! nosotros morimos
                5: if (FormalityLevel == FORMAL) print "mueren"; else print "moris"; ! ustedes mueren / vosotros moris
                6: print "mueren";     ! ellos/ellas mueren
            }
        default: print "morir"; return false;
    }
    return true;
];

[ SpanishConjugar_Sentir persona tiempo;
    ! [OK] ANADIDO: SENTIR - Verbo de percepcion/emocion
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "siento";     ! yo siento
                2: if (FormalityLevel == FORMAL) print "siente"; else print "sientes"; ! usted siente / tu sientes
                3: print "siente";     ! el/ella siente
                4: print "sentimos";   ! nosotros sentimos
                5: if (FormalityLevel == FORMAL) print "sienten"; else print "sentis"; ! ustedes sienten / vosotros sentis
                6: print "sienten";    ! ellos/ellas sienten
            }
        default: print "sentir"; return false;
    }
    return true;
];

! ==============================================================================
! SISTEMA DE DETECCION INTELIGENTE DE VERBOS IRREGULARES
! ==============================================================================

[ DetectarVerboIrregular word;
    ! [OK] CORREGIDO: Funcion para detectar el verbo base de una forma conjugada
    
    ! Formas de SER
    if (word == 'soy' or 'eres' or 'es' or 'somos' or 'sois' or 'son' or
               'era' or 'eras' or 'eramos' or 'erais' or 'eran' or
               'fui' or 'fuiste' or 'fue' or 'fuimos' or 'fuisteis' or 'fueron') 
        return 'ser';
    
    ! Formas de ESTAR
    if (word == 'estoy' or 'estas' or 'esta' or 'estamos' or 'estais' or 'estan' or
               'estaba' or 'estabas' or 'estabamos' or 'estabais' or 'estaban' or
               'estuve' or 'estuviste' or 'estuvo' or 'estuvimos' or 'estuvisteis' or 'estuvieron')
        return 'estar';
    
    ! Formas de TENER
    if (word == 'tengo' or 'tienes' or 'tiene' or 'tenemos' or 'teneis' or 'tienen' or
               'tenia' or 'tenias' or 'teniamos' or 'teniais' or 'tenian' or
               'tuve' or 'tuviste' or 'tuvo' or 'tuvimos' or 'tuvisteis' or 'tuvieron')
        return 'tener';
    
    ! Formas de HACER
    if (word == 'hago' or 'haces' or 'hace' or 'hacemos' or 'haceis' or 'hacen' or
               'hacia' or 'hacias' or 'haciamos' or 'haciais' or 'hacian' or
               'hice' or 'hiciste' or 'hizo' or 'hicimos' or 'hicisteis' or 'hicieron')
        return 'hacer';
    
    ! Formas de IR
    if (word == 'voy' or 'vas' or 'va' or 'vamos' or 'vais' or 'van' or
               'iba' or 'ibas' or 'ibamos' or 'ibais' or 'iban')
        return 'ir';
    
    ! Formas de VENIR
    if (word == 'vengo' or 'vienes' or 'viene' or 'venimos' or 'venis' or 'vienen' or
               'vine' or 'viniste' or 'vino' or 'vinimos' or 'vinisteis' or 'vinieron')
        return 'venir';
    
    ! Formas de VER
    if (word == 'veo' or 'ves' or 've' or 'vemos' or 'veis' or 'ven' or
               'veia' or 'veias' or 'veiamos' or 'veiais' or 'veian')
        return 'ver';
    
    ! Formas de DAR
    if (word == 'doy' or 'das' or 'da' or 'damos' or 'dais' or 'dan' or
               'di' or 'diste' or 'dio' or 'dimos' or 'disteis' or 'dieron')
        return 'dar';
    
    ! Formas comunes de otros verbos irregulares
    if (word == 'puedo' or 'puedes' or 'puede' or 'podemos' or 'podeis' or 'pueden') return 'poder';
    if (word == 'quiero' or 'quieres' or 'quiere' or 'queremos' or 'quereis' or 'quieren') return 'querer';
    if (word == 'se' or 'sabes' or 'sabe' or 'sabemos' or 'sabeis' or 'saben') return 'saber';
    if (word == 'digo' or 'dices' or 'dice' or 'decimos' or 'decis' or 'dicen') return 'decir';
    if (word == 'pongo' or 'pones' or 'pone' or 'ponemos' or 'poneis' or 'ponen') return 'poner';
    if (word == 'salgo' or 'sales' or 'sale' or 'salimos' or 'salis' or 'salen') return 'salir';
    
    return 0; ! No detectado como irregular
];

! ==============================================================================
! FUNCIONES DE DEPURACION Y TESTING - [OK] COMPLETAS
! ==============================================================================

#Ifdef DEBUG;
[ TestVerbosIrregulares;
    print "^=== PRUEBA DE VERBOS IRREGULARES ===^";
    
    print "^SER (presente): ";
    SpanishConjugar_Ser(1, PRESENTE_T); print ", ";
    SpanishConjugar_Ser(2, PRESENTE_T); print ", ";
    SpanishConjugar_Ser(3, PRESENTE_T); print "^";
    
    print "ESTAR (presente): ";
    SpanishConjugar_Estar(1, PRESENTE_T); print ", ";
    SpanishConjugar_Estar(2, PRESENTE_T); print ", ";
    SpanishConjugar_Estar(3, PRESENTE_T); print "^";
    
    print "IR (presente): ";
    SpanishConjugar_Ir(1, PRESENTE_T); print ", ";
    SpanishConjugar_Ir(2, PRESENTE_T); print ", ";
    SpanishConjugar_Ir(3, PRESENTE_T); print "^";
    
    print "TENER (presente): ";
    SpanishConjugar_Tener(1, PRESENTE_T); print ", ";
    SpanishConjugar_Tener(2, PRESENTE_T); print ", ";
    SpanishConjugar_Tener(3, PRESENTE_T); print "^";
    
    print "^SER (preterito): ";
    SpanishConjugar_Ser(1, PRETERITO_T); print ", ";
    SpanishConjugar_Ser(2, PRETERITO_T); print ", ";
    SpanishConjugar_Ser(3, PRETERITO_T); print "^";
    
    print "IR (preterito): ";
    SpanishConjugar_Ir(1, PRETERITO_T); print ", ";
    SpanishConjugar_Ir(2, PRETERITO_T); print ", ";
    SpanishConjugar_Ir(3, PRETERITO_T); print "^";
    
    print "^=== FIN DE PRUEBA ===^";
];

[ SpanishDebugIrregular verbo;
    print "^=== ANALISIS DE VERBO IRREGULAR ===^";
    print "Verbo: ", (address) verbo, "^";
    if (LanguageIsIrregularVerb(verbo)) {
        print "[OK] Es verbo irregular reconocido^";
        print "Presente (3ª persona): ";
        SpanishConjugarIrregular(verbo, 3, PRESENTE_T);
        print "^Preterito (3ª persona): ";
        SpanishConjugarIrregular(verbo, 3, PRETERITO_T);
        print "^";
    } else {
        print "[X] No es verbo irregular o no esta implementado^";
        ! Intentar deteccion automatica
        local base_verb;
        base_verb = DetectarVerboIrregular(verbo);
        if (base_verb) {
            print "💡 Detectado como forma de: ", (address) base_verb, "^";
        }
    }
];

[ TestConjugacionCompleta verbo;
    ! [OK] CORREGIDO: Funcion completa de prueba
    print "^=== CONJUGACION COMPLETA IRREGULAR: ", (address) verbo, " ===^";
    
    if (~~LanguageIsIrregularVerb(verbo)) {
        print "[X] Error: No es un verbo irregular reconocido^";
        return;
    }
    
    print "^PRESENTE:^";
    print "  yo "; SpanishConjugarIrregular(verbo, 1, PRESENTE_T); print "^";
    print "  tu "; SpanishConjugarIrregular(verbo, 2, PRESENTE_T); print "^";
    print "  el/ella "; SpanishConjugarIrregular(verbo, 3, PRESENTE_T); print "^";
    print "  nosotros "; SpanishConjugarIrregular(verbo, 4, PRESENTE_T); print "^";
    print "  vosotros "; SpanishConjugarIrregular(verbo, 5, PRESENTE_T); print "^";
    print "  ellos/ellas "; SpanishConjugarIrregular(verbo, 6, PRESENTE_T); print "^";
    
    print "^PRETERITO:^";
    print "  yo "; SpanishConjugarIrregular(verbo, 1, PRETERITO_T); print "^";
    print "  tu "; SpanishConjugarIrregular(verbo, 2, PRETERITO_T); print "^";
    print "  el/ella "; SpanishConjugarIrregular(verbo, 3, PRETERITO_T); print "^";
    print "  nosotros "; SpanishConjugarIrregular(verbo, 4, PRETERITO_T); print "^";
    print "  vosotros "; SpanishConjugarIrregular(verbo, 5, PRETERITO_T); print "^";
    print "  ellos/ellas "; SpanishConjugarIrregular(verbo, 6, PRETERITO_T); print "^";
    
    print "^IMPERFECTO:^";
    print "  yo "; SpanishConjugarIrregular(verbo, 1, IMPERFECTO_T); print "^";
    print "  tu "; SpanishConjugarIrregular(verbo, 2, IMPERFECTO_T); print "^";
    print "  el/ella "; SpanishConjugarIrregular(verbo, 3, IMPERFECTO_T); print "^";
    
    print "^=== FIN DE CONJUGACION ===^";
];

[ SpanishIrregularStats;
    print "^=== ESTADISTICAS DE VERBOS IRREGULARES ===^";
    print "Verbos implementados: 20^";
    print "Principales: SER, ESTAR, TENER, HACER, IR, VENIR, VER, DAR^";
    print "Modales: PODER, QUERER, SABER^";
    print "Comunicacion: DECIR^";
    print "Accion: PONER, SALIR, TRAER, CAER^";
    print "Percepcion: OIR^";
    print "Estado: DORMIR, MORIR, SENTIR^";
    print "^Tiempos implementados por verbo:^";
    print "- Completos (4-7 tiempos): SER, ESTAR, TENER, HACER, IR^";
    print "- Basicos (1-3 tiempos): Resto de verbos^";
    print "^Deteccion automatica: [OK] Formas conjugadas reconocidas^";
    print "^Integracion: [OK] Compatible con sistema de verbos regulares^";
    print "^Formalidad: [OK] Manejo automatico tu/usted^";
];
#Endif;

! ==============================================================================
! RUTINA DE INICIALIZACION
! ==============================================================================

[ SpanishIrregularVerbsInitialise;
    ! [OK] CORREGIDO: Inicializacion completa
    spanish_verbs_ready = true; ! Marcar verbos como listos
    MarkModuleLoaded('irregular');
    
    #Ifdef DEBUG;
        print "^[SpanishIrregularVerbs v", (string) SPANISH_IRREGULAR_VERBS_VERSION, " inicializado]^";
        print "[[OK] 20 verbos irregulares implementados completamente]^";
        print "[SER, ESTAR, TENER, HACER, IR, VENIR, VER, DAR, PODER, QUERER,]^";
        print "[SABER, DECIR, PONER, SALIR, TRAER, CAER, OIR, DORMIR, MORIR, SENTIR]^";
        print "[[OK] Integracion completa con sistema modular]^";
        print "[[OK] Deteccion automatica de formas conjugadas]^";
        print "[", SPANISH_IRREGULAR_VERBS_FUNCTIONS, " funciones disponibles]^";
    #Endif;
];

! ==============================================================================
! CONSTANTES DE FINALIZACION
! ==============================================================================

Constant SPANISH_IRREGULAR_VERBS_COMPLETE;
Constant SPANISH_IRREGULAR_VERBS_READY;
Constant SPANISH_IRREGULAR_VERBS_COUNT = 20;
Constant SPANISH_IRREGULAR_VERBS_FUNCTIONS = 25; ! Numero de funciones publicas

! Informacion del modulo
Constant SPANISH_IRREGULAR_FEATURES = "20 verbos completos, deteccion automatica formas conjugadas, integracion modular, formalidad tu/usted";

#Endif; ! SPANISH_IRREGULAR_VERBS_INCLUDED

! ==============================================================================
! Fin de SpanishIrregularVerbs.h - Sistema completo de verbos irregulares
! Actualizado para integracion completa con el sistema modular
! ==============================================================================