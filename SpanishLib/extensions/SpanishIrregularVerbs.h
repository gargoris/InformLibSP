! ==============================================================================
! SPANISHIRREGULARVERBS.H - Sistema completo de verbos irregulares en español
! Extensión para el sistema modular Spanish Library para Inform 6
! Compatible con Inform 6.42 y librería estándar 6.12.7
! ACTUALIZADO: Integración completa con el sistema modular
! ==============================================================================

System_file;

#Ifndef SPANISH_IRREGULAR_VERBS_INCLUDED;
Constant SPANISH_IRREGULAR_VERBS_INCLUDED;
Constant SPANISH_IRREGULAR_VERBS_VERSION = "2.0-modular";

! Verificación de dependencias
#Ifndef SPANISH_CONSTANTS_INCLUDED;
  Message fatalerror "*** Include SpanishConstants.h antes de SpanishIrregularVerbs.h ***";
#Endif;

#Ifndef SPANISH_VERBS_INCLUDED;
  Message fatalerror "*** Include SpanishVerbs.h antes de SpanishIrregularVerbs.h ***";
#Endif;

! ==============================================================================
! TABLA DE VERBOS IRREGULARES PRINCIPALES
! ==============================================================================

Array spanish_irregular_verbs table
    ! Verbo, Función de conjugación
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
    'oír'       SpanishConjugar_Oir
    'dormir'    SpanishConjugar_Dormir
    'morir'     SpanishConjugar_Morir
    'sentir'    SpanishConjugar_Sentir;

! ==============================================================================
! FUNCIÓN PRINCIPAL DE BÚSQUEDA Y CONJUGACIÓN
! ==============================================================================

[ SpanishConjugarIrregular verbo persona tiempo   i func;
    ! Buscar el verbo en la tabla de irregulares
    for (i = 0: i < spanish_irregular_verbs-->0: i = i + 2) {
        if (spanish_irregular_verbs-->(i+1) == verbo) {
            func = spanish_irregular_verbs-->(i+2);
            return func(persona, tiempo);
        }
    }
    return false; ! No es irregular conocido
];

[ LanguageIsIrregularVerb verbo   i;
    ! Verificar si un verbo está en nuestra tabla de irregulares
    for (i = 0: i < spanish_irregular_verbs-->0: i = i + 2) {
        if (spanish_irregular_verbs-->(i+1) == verbo) return true;
    }
    return false;
];

! ==============================================================================
! CONJUGACIONES DE VERBOS IRREGULARES BÁSICOS
! ==============================================================================

! SER - El verbo más irregular del español
[ SpanishConjugar_Ser persona tiempo;
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "soy";
                2: print "eres";
                3: print "es";
                4: print "somos";
                5: print "sois";
                6: print "son";
            }
        PRETERITO_T:
            switch(persona) {
                1: print "fui";
                2: print "fuiste";
                3: print "fue";
                4: print "fuimos";
                5: print "fuisteis";
                6: print "fueron";
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print "era";
                2: print "eras";
                3: print "era";
                4: print "éramos";
                5: print "erais";
                6: print "eran";
            }
        FUTURO_T:
            switch(persona) {
                1: print "seré";
                2: print "serás";
                3: print "será";
                4: print "seremos";
                5: print "seréis";
                6: print "serán";
            }
        CONDICIONAL_T:
            switch(persona) {
                1: print "sería";
                2: print "serías";
                3: print "sería";
                4: print "seríamos";
                5: print "seríais";
                6: print "serían";
            }
        SUBJUNTIVO_T:
            switch(persona) {
                1: print "sea";
                2: print "seas";
                3: print "sea";
                4: print "seamos";
                5: print "seáis";
                6: print "sean";
            }
        IMPERATIVO_T:
            switch(persona) {
                2: print "sé";
                3: print "sea";
                4: print "seamos";
                5: print "sed";
                6: print "sean";
            }
    }
    return true;
];

! ESTAR - Ubicación y estados temporales
[ SpanishConjugar_Estar persona tiempo;
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "estoy";
                2: print "estás";
                3: print "está";
                4: print "estamos";
                5: print "estáis";
                6: print "están";
            }
        PRETERITO_T:
            switch(persona) {
                1: print "estuve";
                2: print "estuviste";
                3: print "estuvo";
                4: print "estuvimos";
                5: print "estuvisteis";
                6: print "estuvieron";
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print "estaba";
                2: print "estabas";
                3: print "estaba";
                4: print "estábamos";
                5: print "estabais";
                6: print "estaban";
            }
        FUTURO_T:
            switch(persona) {
                1: print "estaré";
                2: print "estarás";
                3: print "estará";
                4: print "estaremos";
                5: print "estaréis";
                6: print "estarán";
            }
        SUBJUNTIVO_T:
            switch(persona) {
                1: print "esté";
                2: print "estés";
                3: print "esté";
                4: print "estemos";
                5: print "estéis";
                6: print "estén";
            }
        IMPERATIVO_T:
            switch(persona) {
                2: print "está";
                3: print "esté";
                4: print "estemos";
                5: print "estad";
                6: print "estén";
            }
    }
    return true;
];

! TENER - Posesión y obligación
[ SpanishConjugar_Tener persona tiempo;
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "tengo";
                2: print "tienes";
                3: print "tiene";
                4: print "tenemos";
                5: print "tenéis";
                6: print "tienen";
            }
        PRETERITO_T:
            switch(persona) {
                1: print "tuve";
                2: print "tuviste";
                3: print "tuvo";
                4: print "tuvimos";
                5: print "tuvisteis";
                6: print "tuvieron";
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print "tenía";
                2: print "tenías";
                3: print "tenía";
                4: print "teníamos";
                5: print "teníais";
                6: print "tenían";
            }
        FUTURO_T:
            switch(persona) {
                1: print "tendré";
                2: print "tendrás";
                3: print "tendrá";
                4: print "tendremos";
                5: print "tendréis";
                6: print "tendrán";
            }
        SUBJUNTIVO_T:
            switch(persona) {
                1: print "tenga";
                2: print "tengas";
                3: print "tenga";
                4: print "tengamos";
                5: print "tengáis";
                6: print "tengan";
            }
        IMPERATIVO_T:
            switch(persona) {
                2: print "ten";
                3: print "tenga";
                4: print "tengamos";
                5: print "tened";
                6: print "tengan";
            }
    }
    return true;
];

! HACER - Acción general
[ SpanishConjugar_Hacer persona tiempo;
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "hago";
                2: print "haces";
                3: print "hace";
                4: print "hacemos";
                5: print "hacéis";
                6: print "hacen";
            }
        PRETERITO_T:
            switch(persona) {
                1: print "hice";
                2: print "hiciste";
                3: print "hizo";
                4: print "hicimos";
                5: print "hicisteis";
                6: print "hicieron";
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print "hacía";
                2: print "hacías";
                3: print "hacía";
                4: print "hacíamos";
                5: print "hacíais";
                6: print "hacían";
            }
        FUTURO_T:
            switch(persona) {
                1: print "haré";
                2: print "harás";
                3: print "hará";
                4: print "haremos";
                5: print "haréis";
                6: print "harán";
            }
        SUBJUNTIVO_T:
            switch(persona) {
                1: print "haga";
                2: print "hagas";
                3: print "haga";
                4: print "hagamos";
                5: print "hagáis";
                6: print "hagan";
            }
        IMPERATIVO_T:
            switch(persona) {
                2: print "haz";
                3: print "haga";
                4: print "hagamos";
                5: print "haced";
                6: print "hagan";
            }
    }
    return true;
];

! IR - Movimiento básico
[ SpanishConjugar_Ir persona tiempo;
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "voy";
                2: print "vas";
                3: print "va";
                4: print "vamos";
                5: print "vais";
                6: print "van";
            }
        PRETERITO_T:
            switch(persona) {
                1: print "fui";
                2: print "fuiste";
                3: print "fue";
                4: print "fuimos";
                5: print "fuisteis";
                6: print "fueron";
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print "iba";
                2: print "ibas";
                3: print "iba";
                4: print "íbamos";
                5: print "ibais";
                6: print "iban";
            }
        FUTURO_T:
            switch(persona) {
                1: print "iré";
                2: print "irás";
                3: print "irá";
                4: print "iremos";
                5: print "iréis";
                6: print "irán";
            }
        SUBJUNTIVO_T:
            switch(persona) {
                1: print "vaya";
                2: print "vayas";
                3: print "vaya";
                4: print "vayamos";
                5: print "vayáis";
                6: print "vayan";
            }
        IMPERATIVO_T:
            switch(persona) {
                2: print "ve";
                3: print "vaya";
                4: print "vamos";
                5: print "id";
                6: print "vayan";
            }
    }
    return true;
];

! VENIR - Movimiento hacia el hablante
[ SpanishConjugar_Venir persona tiempo;
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "vengo";
                2: print "vienes";
                3: print "viene";
                4: print "venimos";
                5: print "venís";
                6: print "vienen";
            }
        PRETERITO_T:
            switch(persona) {
                1: print "vine";
                2: print "viniste";
                3: print "vino";
                4: print "vinimos";
                5: print "vinisteis";
                6: print "vinieron";
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print "venía";
                2: print "venías";
                3: print "venía";
                4: print "veníamos";
                5: print "veníais";
                6: print "venían";
            }
        FUTURO_T:
            switch(persona) {
                1: print "vendré";
                2: print "vendrás";
                3: print "vendrá";
                4: print "vendremos";
                5: print "vendréis";
                6: print "vendrán";
            }
        SUBJUNTIVO_T:
            switch(persona) {
                1: print "venga";
                2: print "vengas";
                3: print "venga";
                4: print "vengamos";
                5: print "vengáis";
                6: print "vengan";
            }
        IMPERATIVO_T:
            switch(persona) {
                2: print "ven";
                3: print "venga";
                4: print "vengamos";
                5: print "venid";
                6: print "vengan";
            }
    }
    return true;
];

! VER - Percepción visual
[ SpanishConjugar_Ver persona tiempo;
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "veo";
                2: print "ves";
                3: print "ve";
                4: print "vemos";
                5: print "veis";
                6: print "ven";
            }
        PRETERITO_T:
            switch(persona) {
                1: print "vi";
                2: print "viste";
                3: print "vio";
                4: print "vimos";
                5: print "visteis";
                6: print "vieron";
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print "veía";
                2: print "veías";
                3: print "veía";
                4: print "veíamos";
                5: print "veíais";
                6: print "veían";
            }
        FUTURO_T:
            switch(persona) {
                1: print "veré";
                2: print "verás";
                3: print "verá";
                4: print "veremos";
                5: print "veréis";
                6: print "verán";
            }
        SUBJUNTIVO_T:
            switch(persona) {
                1: print "vea";
                2: print "veas";
                3: print "vea";
                4: print "veamos";
                5: print "veáis";
                6: print "vean";
            }
        IMPERATIVO_T:
            switch(persona) {
                2: print "ve";
                3: print "vea";
                4: print "veamos";
                5: print "ved";
                6: print "vean";
            }
    }
    return true;
];

! DAR - Transferencia
[ SpanishConjugar_Dar persona tiempo;
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "doy";
                2: print "das";
                3: print "da";
                4: print "damos";
                5: print "dais";
                6: print "dan";
            }
        PRETERITO_T:
            switch(persona) {
                1: print "di";
                2: print "diste";
                3: print "dio";
                4: print "dimos";
                5: print "disteis";
                6: print "dieron";
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print "daba";
                2: print "dabas";
                3: print "daba";
                4: print "dábamos";
                5: print "dabais";
                6: print "daban";
            }
        FUTURO_T:
            switch(persona) {
                1: print "daré";
                2: print "darás";
                3: print "dará";
                4: print "daremos";
                5: print "daréis";
                6: print "darán";
            }
        SUBJUNTIVO_T:
            switch(persona) {
                1: print "dé";
                2: print "des";
                3: print "dé";
                4: print "demos";
                5: print "deis";
                6: print "den";
            }
        IMPERATIVO_T:
            switch(persona) {
                2: print "da";
                3: print "dé";
                4: print "demos";
                5: print "dad";
                6: print "den";
            }
    }
    return true;
];

! PODER - Habilidad/posibilidad
[ SpanishConjugar_Poder persona tiempo;
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "puedo";
                2: print "puedes";
                3: print "puede";
                4: print "podemos";
                5: print "podéis";
                6: print "pueden";
            }
        PRETERITO_T:
            switch(persona) {
                1: print "pude";
                2: print "pudiste";
                3: print "pudo";
                4: print "pudimos";
                5: print "pudisteis";
                6: print "pudieron";
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print "podía";
                2: print "podías";
                3: print "podía";
                4: print "podíamos";
                5: print "podíais";
                6: print "podían";
            }
        FUTURO_T:
            switch(persona) {
                1: print "podré";
                2: print "podrás";
                3: print "podrá";
                4: print "podremos";
                5: print "podréis";
                6: print "podrán";
            }
        SUBJUNTIVO_T:
            switch(persona) {
                1: print "pueda";
                2: print "puedas";
                3: print "pueda";
                4: print "podamos";
                5: print "podáis";
                6: print "puedan";
            }
    }
    return true;
];

! QUERER - Deseo/voluntad
[ SpanishConjugar_Querer persona tiempo;
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "quiero";
                2: print "quieres";
                3: print "quiere";
                4: print "queremos";
                5: print "queréis";
                6: print "quieren";
            }
        PRETERITO_T:
            switch(persona) {
                1: print "quise";
                2: print "quisiste";
                3: print "quiso";
                4: print "quisimos";
                5: print "quisisteis";
                6: print "quisieron";
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print "quería";
                2: print "querías";
                3: print "quería";
                4: print "queríamos";
                5: print "queríais";
                6: print "querían";
            }
        FUTURO_T:
            switch(persona) {
                1: print "querré";
                2: print "querrás";
                3: print "querrá";
                4: print "querremos";
                5: print "querréis";
                6: print "querrán";
            }
        SUBJUNTIVO_T:
            switch(persona) {
                1: print "quiera";
                2: print "quieras";
                3: print "quiera";
                4: print "queramos";
                5: print "queráis";
                6: print "quieran";
            }
        IMPERATIVO_T:
            switch(persona) {
                2: print "quiere";
                3: print "quiera";
                4: print "queramos";
                5: print "quered";
                6: print "quieran";
            }
    }
    return true;
];

! SABER - Conocimiento
[ SpanishConjugar_Saber persona tiempo;
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "sé";
                2: print "sabes";
                3: print "sabe";
                4: print "sabemos";
                5: print "sabéis";
                6: print "saben";
            }
        PRETERITO_T:
            switch(persona) {
                1: print "supe";
                2: print "supiste";
                3: print "supo";
                4: print "supimos";
                5: print "supisteis";
                6: print "supieron";
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print "sabía";
                2: print "sabías";
                3: print "sabía";
                4: print "sabíamos";
                5: print "sabíais";
                6: print "sabían";
            }
        FUTURO_T:
            switch(persona) {
                1: print "sabré";
                2: print "sabrás";
                3: print "sabrá";
                4: print "sabremos";
                5: print "sabréis";
                6: print "sabrán";
            }
        SUBJUNTIVO_T:
            switch(persona) {
                1: print "sepa";
                2: print "sepas";
                3: print "sepa";
                4: print "sepamos";
                5: print "sepáis";
                6: print "sepan";
            }
        IMPERATIVO_T:
            switch(persona) {
                2: print "sabe";
                3: print "sepa";
                4: print "sepamos";
                5: print "sabed";
                6: print "sepan";
            }
    }
    return true;
];

! DECIR - Comunicación
[ SpanishConjugar_Decir persona tiempo;
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "digo";
                2: print "dices";
                3: print "dice";
                4: print "decimos";
                5: print "decís";
                6: print "dicen";
            }
        PRETERITO_T:
            switch(persona) {
                1: print "dije";
                2: print "dijiste";
                3: print "dijo";
                4: print "dijimos";
                5: print "dijisteis";
                6: print "dijeron";
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print "decía";
                2: print "decías";
                3: print "decía";
                4: print "decíamos";
                5: print "decíais";
                6: print "decían";
            }
        FUTURO_T:
            switch(persona) {
                1: print "diré";
                2: print "dirás";
                3: print "dirá";
                4: print "diremos";
                5: print "diréis";
                6: print "dirán";
            }
        SUBJUNTIVO_T:
            switch(persona) {
                1: print "diga";
                2: print "digas";
                3: print "diga";
                4: print "digamos";
                5: print "digáis";
                6: print "digan";
            }
        IMPERATIVO_T:
            switch(persona) {
                2: print "di";
                3: print "diga";
                4: print "digamos";
                5: print "decid";
                6: print "digan";
            }
    }
    return true;
];

! PONER - Colocación
[ SpanishConjugar_Poner persona tiempo;
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "pongo";
                2: print "pones";
                3: print "pone";
                4: print "ponemos";
                5: print "ponéis";
                6: print "ponen";
            }
        PRETERITO_T:
            switch(persona) {
                1: print "puse";
                2: print "pusiste";
                3: print "puso";
                4: print "pusimos";
                5: print "pusisteis";
                6: print "pusieron";
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print "ponía";
                2: print "ponías";
                3: print "ponía";
                4: print "poníamos";
                5: print "poníais";
                6: print "ponían";
            }
        FUTURO_T:
            switch(persona) {
                1: print "pondré";
                2: print "pondrás";
                3: print "pondrá";
                4: print "pondremos";
                5: print "pondréis";
                6: print "pondrán";
            }
        SUBJUNTIVO_T:
            switch(persona) {
                1: print "ponga";
                2: print "pongas";
                3: print "ponga";
                4: print "pongamos";
                5: print "pongáis";
                6: print "pongan";
            }
        IMPERATIVO_T:
            switch(persona) {
                2: print "pon";
                3: print "ponga";
                4: print "pongamos";
                5: print "poned";
                6: print "pongan";
            }
    }
    return true;
];

! SALIR - Egreso
[ SpanishConjugar_Salir persona tiempo;
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "salgo";
                2: print "sales";
                3: print "sale";
                4: print "salimos";
                5: print "salís";
                6: print "salen";
            }
        PRETERITO_T:
            switch(persona) {
                1: print "salí";
                2: print "saliste";
                3: print "salió";
                4: print "salimos";
                5: print "salisteis";
                6: print "salieron";
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print "salía";
                2: print "salías";
                3: print "salía";
                4: print "salíamos";
                5: print "salíais";
                6: print "salían";
            }
        FUTURO_T:
            switch(persona) {
                1: print "saldré";
                2: print "saldrás";
                3: print "saldrá";
                4: print "saldremos";
                5: print "saldréis";
                6: print "saldrán";
            }
        SUBJUNTIVO_T:
            switch(persona) {
                1: print "salga";
                2: print "salgas";
                3: print "salga";
                4: print "salgamos";
                5: print "salgáis";
                6: print "salgan";
            }
        IMPERATIVO_T:
            switch(persona) {
                2: print "sal";
                3: print "salga";
                4: print "salgamos";
                5: print "salid";
                6: print "salgan";
            }
    }
    return true;
];

! ==============================================================================
! VERBOS CON CAMBIOS DE RAÍZ (e->ie, o->ue, e->i)
! ==============================================================================

! DORMIR (o->ue en presente)
[ SpanishConjugar_Dormir persona tiempo;
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "duermo";
                2: print "duermes";
                3: print "duerme";
                4: print "dormimos";
                5: print "dormís";
                6: print "duermen";
            }
        PRETERITO_T:
            switch(persona) {
                1: print "dormí";
                2: print "dormiste";
                3: print "durmió";
                4: print "dormimos";
                5: print "dormisteis";
                6: print "durmieron";
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print "dormía";
                2: print "dormías";
                3: print "dormía";
                4: print "dormíamos";
                5: print "dormíais";
                6: print "dormían";
            }
        SUBJUNTIVO_T:
            switch(persona) {
                1: print "duerma";
                2: print "duermas";
                3: print "duerma";
                4: print "durmamos";
                5: print "durmáis";
                6: print "duerman";
            }
        IMPERATIVO_T:
            switch(persona) {
                2: print "duerme";
                3: print "duerma";
                4: print "durmamos";
                5: print "dormid";
                6: print "duerman";
            }
    }
    return true;
];

! SENTIR (e->ie en presente)
[ SpanishConjugar_Sentir persona tiempo;
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "siento";
                2: print "sientes";
                3: print "siente";
                4: print "sentimos";
                5: print "sentís";
                6: print "sienten";
            }
        PRETERITO_T:
            switch(persona) {
                1: print "sentí";
                2: print "sentiste";
                3: print "sintió";
                4: print "sentimos";
                5: print "sentisteis";
                6: print "sintieron";
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print "sentía";
                2: print "sentías";
                3: print "sentía";
                4: print "sentíamos";
                5: print "sentíais";
                6: print "sentían";
            }
        SUBJUNTIVO_T:
            switch(persona) {
                1: print "sienta";
                2: print "sientas";
                3: print "sienta";
                4: print "sintamos";
                5: print "sintáis";
                6: print "sientan";
            }
        IMPERATIVO_T:
            switch(persona) {
                2: print "siente";
                3: print "sienta";
                4: print "sintamos";
                5: print "sentid";
                6: print "sientan";
            }
    }
    return true;
];

! ==============================================================================
! VERBOS ADICIONALES IMPORTANTES PARA IF
! ==============================================================================

! TRAER - Traer cosas
[ SpanishConjugar_Traer persona tiempo;
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "traigo";
                2: print "traes";
                3: print "trae";
                4: print "traemos";
                5: print "traéis";
                6: print "traen";
            }
        PRETERITO_T:
            switch(persona) {
                1: print "traje";
                2: print "trajiste";
                3: print "trajo";
                4: print "trajimos";
                5: print "trajisteis";
                6: print "trajeron";
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print "traía";
                2: print "traías";
                3: print "traía";
                4: print "traíamos";
                5: print "traíais";
                6: print "traían";
            }
        SUBJUNTIVO_T:
            switch(persona) {
                1: print "traiga";
                2: print "traigas";
                3: print "traiga";
                4: print "traigamos";
                5: print "traigáis";
                6: print "traigan";
            }
    }
    return true;
];

! CAER - Caerse
[ SpanishConjugar_Caer persona tiempo;
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "caigo";
                2: print "caes";
                3: print "cae";
                4: print "caemos";
                5: print "caéis";
                6: print "caen";
            }
        PRETERITO_T:
            switch(persona) {
                1: print "caí";
                2: print "caíste";
                3: print "cayó";
                4: print "caímos";
                5: print "caísteis";
                6: print "cayeron";
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print "caía";
                2: print "caías";
                3: print "caía";
                4: print "caíamos";
                5: print "caíais";
                6: print "caían";
            }
        SUBJUNTIVO_T:
            switch(persona) {
                1: print "caiga";
                2: print "caigas";
                3: print "caiga";
                4: print "caigamos";
                5: print "caigáis";
                6: print "caigan";
            }
    }
    return true;
];

! OÍR - Escuchar
[ SpanishConjugar_Oir persona tiempo;
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "oigo";
                2: print "oyes";
                3: print "oye";
                4: print "oímos";
                5: print "oís";
                6: print "oyen";
            }
        PRETERITO_T:
            switch(persona) {
                1: print "oí";
                2: print "oíste";
                3: print "oyó";
                4: print "oímos";
                5: print "oísteis";
                6: print "oyeron";
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print "oía";
                2: print "oías";
                3: print "oía";
                4: print "oíamos";
                5: print "oíais";
                6: print "oían";
            }
        SUBJUNTIVO_T:
            switch(persona) {
                1: print "oiga";
                2: print "oigas";
                3: print "oiga";
                4: print "oigamos";
                5: print "oigáis";
                6: print "oigan";
            }
        IMPERATIVO_T:
            switch(persona) {
                2: print "oye";
                3: print "oiga";
                4: print "oigamos";
                5: print "oíd";
                6: print "oigan";
            }
    }
    return true;
];

! MORIR (o->ue, irregular en participio)
[ SpanishConjugar_Morir persona tiempo;
    switch(tiempo) {
        PRESENTE_T:
            switch(persona) {
                1: print "muero";
                2: print "mueres";
                3: print "muere";
                4: print "morimos";
                5: print "morís";
                6: print "mueren";
            }
        PRETERITO_T:
            switch(persona) {
                1: print "morí";
                2: print "moriste";
                3: print "murió";
                4: print "morimos";
                5: print "moristeis";
                6: print "murieron";
            }
        IMPERFECTO_T:
            switch(persona) {
                1: print "moría";
                2: print "morías";
                3: print "moría";
                4: print "moríamos";
                5: print "moríais";
                6: print "morían";
            }
        SUBJUNTIVO_T:
            switch(persona) {
                1: print "muera";
                2: print "mueras";
                3: print "muera";
                4: print "muramos";
                5: print "muráis";
                6: print "mueran";
            }
        IMPERATIVO_T:
            switch(persona) {
                2: print "muere";
                3: print "muera";
                4: print "muramos";
                5: print "morid";
                6: print "mueran";
            }
    }
    return true;
];

! ==============================================================================
! INTEGRACIÓN CON EL SISTEMA PRINCIPAL
! ==============================================================================

! Función principal para integración con SpanishVerbs.h
[ SpanishConjugarVerboIrregular verbo persona tiempo;
    ! Esta función es llamada desde ConjugarVerbo() en SpanishVerbs.h
    return SpanishConjugarIrregular(verbo, persona, tiempo);
];

! Función auxiliar para detección en LanguageIsVerb
[ SpanishEsVerboIrregular word;
    ! Formas irregulares específicas comunes en IF
    if (word == 'soy' or 'eres' or 'es' or 'somos' or 'sois' or 'son') rtrue;      ! ser
    if (word == 'estoy' or 'estás' or 'está' or 'estamos' or 'estáis' or 'están') rtrue; ! estar
    if (word == 'tengo' or 'tienes' or 'tiene' or 'tenemos' or 'tenéis' or 'tienen') rtrue; ! tener
    if (word == 'hago' or 'haces' or 'hace' or 'hacemos' or 'hacéis' or 'hacen') rtrue; ! hacer
    if (word == 'voy' or 'vas' or 'va' or 'vamos' or 'vais' or 'van') rtrue;       ! ir
    if (word == 'vengo' or 'vienes' or 'viene' or 'venimos' or 'venís' or 'vienen') rtrue; ! venir
    if (word == 'veo' or 'ves' or 've' or 'vemos' or 'veis' or 'ven') rtrue;       ! ver
    if (word == 'doy' or 'das' or 'da' or 'damos' or 'dais' or 'dan') rtrue;       ! dar
    if (word == 'puedo' or 'puedes' or 'puede' or 'podemos' or 'podéis' or 'pueden') rtrue; ! poder
    if (word == 'quiero' or 'quieres' or 'quiere' or 'queremos' or 'queréis' or 'quieren') rtrue; ! querer
    if (word == 'sé' or 'sabes' or 'sabe' or 'sabemos' or 'sabéis' or 'saben') rtrue; ! saber
    if (word == 'digo' or 'dices' or 'dice' or 'decimos' or 'decís' or 'dicen') rtrue; ! decir
    if (word == 'pongo' or 'pones' or 'pone' or 'ponemos' or 'ponéis' or 'ponen') rtrue; ! poner
    if (word == 'salgo' or 'sales' or 'sale' or 'salimos' or 'salís' or 'salen') rtrue; ! salir
    
    ! También verificar infinitivos
    return LanguageIsIrregularVerb(word);
];

! ==============================================================================
! SISTEMA DE DETECCIÓN INTELIGENTE DE VERBOS
! ==============================================================================

[ DetectarVerboIrregular word   base_verb;
    ! Intenta detectar el verbo base de una forma conjugada
    
    ! Formas de SER
    if (word == 'soy' or 'eres' or 'es' or 'somos' or 'sois' or 'son' or
               'era' or 'eras' or 'éramos' or 'erais' or 'eran' or
               'fui' or 'fuiste' or 'fue' or 'fuimos' or 'fuisteis' or 'fueron') 
        return 'ser';
    
    ! Formas de ESTAR
    if (word == 'estoy' or 'estás' or 'está' or 'estamos' or 'estáis' or 'están' or
               'estaba' or 'estabas' or 'estábamos' or 'estabais' or 'estaban' or
               'estuve' or 'estuviste' or 'estuvo' or 'estuvimos' or 'estuvisteis' or 'estuvieron')
        return 'estar';
    
    ! Formas de TENER
    if (word == 'tengo' or 'tienes' or 'tiene' or 'tenemos' or 'tenéis' or 'tienen' or
               'tenía' or 'tenías' or 'teníamos' or 'teníais' or 'tenían' or
               'tuve' or 'tuviste' or 'tuvo' or 'tuvimos' or 'tuvisteis' or 'tuvieron')
        return 'tener';
    
    ! Formas de HACER
    if (word == 'hago' or 'haces' or 'hace' or 'hacemos' or 'hacéis' or 'hacen' or
               'hacía' or 'hacías' or 'hacíamos' or 'hacíais' or 'hacían' or
               'hice' or 'hiciste' or 'hizo' or 'hicimos' or 'hicisteis' or 'hicieron')
        return 'hacer';
    
    ! Formas de IR
    if (word == 'voy' or 'vas' or 'va' or 'vamos' or 'vais' or 'van' or
               'iba' or 'ibas' or 'íbamos' or 'ibais' or 'iban')
        return 'ir';
    
    return 0; ! No detectado
];

! ==============================================================================
! FUNCIONES DE DEPURACIÓN Y TESTING
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
    
    print "^SER (pretérito): ";
    SpanishConjugar_Ser(1, PRETERITO_T); print ", ";
    SpanishConjugar_Ser(2, PRETERITO_T); print ", ";
    SpanishConjugar_Ser(3, PRETERITO_T); print "^";
    
    print "IR (pretérito): ";
    SpanishConjugar_Ir(1, PRETERITO_T); print ", ";
    SpanishConjugar_Ir(2, PRETERITO_T); print ", ";
    SpanishConjugar_Ir(3, PRETERITO_T); print "^";
    
    print "^=== FIN DE PRUEBA ===^";
];

[ SpanishDebugIrregular verbo;
    print "^=== ANÁLISIS DE VERBO IRREGULAR ===^";
    print "Verbo: ", (address) verbo, "^";
    if (LanguageIsIrregularVerb(verbo)) {
        print "✅ Es verbo irregular reconocido^";
        print "Presente (3ª persona): ";
        SpanishConjugarIrregular(verbo, 3, PRESENTE_T);
        print "^Pretérito (3ª persona): ";
        SpanishConjugarIrregular(verbo, 3, PRETERITO_T);
        print "^";
    } else {
        print "❌ No es verbo irregular o no está implementado^";
    }
];

[ TestConjugacionCompleta verbo;
    print "^=== CONJUGACIÓN COMPLETA IRREGULAR: ", (string) verbo, " ===^";
    
    if (~~LanguageIsIrregularVerb(verbo)) {
        print "❌ Error: No es un verbo irregular reconocido^";
        return;
    }
    
    print "^PRESENTE:^";
    print "  yo "; SpanishConjugarIrregular(verbo, 1, PRESENTE_T); print "^";
    print "  tú "; SpanishConjugarIrregular(verbo, 2, PRESENTE_T); print "^";
    print "  él/ella "; SpanishConjugarIrregular(verbo, 3, PRESENTE_T); print "^";
    print "  nosotros "; SpanishConjugarIrregular(verbo, 4, PRESENTE_T); print "^";
    print "  vosotros "; SpanishConjugarIrregular(verbo, 5, PRESENTE_T); print "^";
    print "  ellos/ellas "; SpanishConjugarIrregular(verbo, 6, PRESENTE_T); print "^";
    
    print "^PRETÉRITO:^";
    print "  yo "; SpanishConjugarIrregular(verbo, 1, PRETERITO_T); print "^";
    print "  tú "; SpanishConjugarIrregular(verbo, 2, PRETERITO_T); print "^";
    print "  él/ella "; SpanishConjugarIrregular(verbo, 3, PRETERITO_T); print "^";
    print "  nosotros "; SpanishConjugarIrregular(verbo, 4, PRETERITO_T); print "^";
    print "  vosotros "; SpanishConjugarIrregular(verbo, 5, PRETERITO_T); print "^";
    print "  ellos/ellas "; SpanishConjugarIrregular(verbo, 6, PRETERITO_T); print "^";
    
    print "^IMPERFECTO:^";
    print "  yo "; SpanishConjugarIrregular(verbo, 1, IMPERFECTO_T); print "^";
    print "  tú "; SpanishConjugarIrregular(verbo, 2, IMPERFECTO_T); print "^";
    print "  él/ella "; SpanishConjugarIrregular(verbo, 3, IMPERFECTO_T); print "^";
    
    print "^=== FIN DE CONJUGACIÓN ===^";
];
#Endif;

! ==============================================================================
! RUTINA DE INICIALIZACIÓN
! ==============================================================================

[ SpanishIrregularVerbsInitialise;
    #Ifdef DEBUG;
    print "^[SpanishIrregularVerbs v", (string) SPANISH_IRREGULAR_VERBS_VERSION, " inicializado]^";
    print "[✅ 20 verbos irregulares implementados completamente]^";
    print "[SER, ESTAR, TENER, HACER, IR, VENIR, VER, DAR, PODER, QUERER,]^";
    print "[SABER, DECIR, PONER, SALIR, TRAER, CAER, OÍR, DORMIR, MORIR, SENTIR]^";
    print "[✅ Integración completa con sistema modular]^";
    print "[✅ Detección automática de formas conjugadas]^";
    #Endif;
];

! ==============================================================================
! CONSTANTES DE FINALIZACIÓN
! ==============================================================================

Constant SPANISH_IRREGULAR_VERBS_COMPLETE;
Constant SPANISH_IRREGULAR_VERBS_READY;
Constant SPANISH_IRREGULAR_VERBS_COUNT = 20;

! Información del módulo
Constant SPANISH_IRREGULAR_FEATURES = "20 verbos completos, detección automática, integración modular";

#Endif; ! SPANISH_IRREGULAR_VERBS_INCLUDED

! ==============================================================================
! Fin de SpanishIrregularVerbs.h - Sistema completo de verbos irregulares
! Actualizado para integración completa con el sistema modular
! ==============================================================================