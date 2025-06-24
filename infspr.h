! ==============================================================================
!   INFSPR:  Funciones de reemplazo para el parser en español
!
!   Supplied for use with Inform 6 -- Release 6.12.7dev -- Serial number 240624
!
!   Copyright Graham Nelson 1993-2004 and David Griffith 2012-2024
!   Spanish adaptation by Gargoris (https://github.com/gargoris)
!
!   This code is licensed under either the traditional Inform license as
!   described by the DM4 or the Artistic License version 2.0.  See the
!   file COPYING in the distribution archive.
!
! ==============================================================================

System_file;

! ------------------------------------------------------------------------------
! Reemplazo de DictionaryLookup para manejar palabras con acentos
! ------------------------------------------------------------------------------

[ DictionaryLookup texto longitud i j;
    ! Si está activada la opción quitacentos, convertimos los acentos
    ! antes de buscar en el diccionario
    if (quitacentos) {
        for (i=0: i<longitud: i++) {
            switch (texto->i) {
                'á': texto->i = 'a';
                'é': texto->i = 'e';
                'í': texto->i = 'i';
                'ó': texto->i = 'o';
                'ú': texto->i = 'u';
                'ü': texto->i = 'u';
                'ñ': texto->i = 'n';
                'Á': texto->i = 'A';
                'É': texto->i = 'E';
                'Í': texto->i = 'I';
                'Ó': texto->i = 'O';
                'Ú': texto->i = 'U';
                'Ü': texto->i = 'U';
                'Ñ': texto->i = 'N';
            }
        }
    }
    
    ! Llamar a la función original
    return VM_DictionaryLookup(texto, longitud);
];

! ------------------------------------------------------------------------------
! Reemplazo de PrefaceByArticle para manejar artículos en español
! ------------------------------------------------------------------------------

[ PrefaceByArticle o acode pluralform capitalise  i artform artval;
    if (o provides articles) {
        artval = o.articles;
        if (capitalise) {
            if (pluralform) {
                print (string) artval-->3;
            } else {
                print (string) artval-->0;
            }
        } else {
            if (pluralform) {
                print (string) artval-->4;
            } else {
                print (string) artval-->1;
            }
        }
        if (pluralform) {
            if (artval-->5 ~= 0) print (string) artval-->5;
        } else {
            if (artval-->2 ~= 0) print (string) artval-->2;
        }
        return;
    }
    
    i = GetGNAOfObject(o);
    artform = LanguageGNAsToArticles-->i;
    
    ! Artículo definido, indefinido o demostrativo
    if (pluralform) {
        i = artform + 2;
    } else {
        i = artform;
    }
    
    if (capitalise) {
        if (acode == 0) print (string) LanguageArticles-->((i*3));     ! El, La, Los, Las
        if (acode == 1) print (string) LanguageArticles-->((i*3)+1);   ! el, la, los, las
        if (acode == 2) print (string) LanguageArticles-->((i*3)+2);   ! un, una, unos, unas
    } else {
        if (acode == 0) print (string) LanguageArticles-->((i*3));     ! El, La, Los, Las
        if (acode == 1) print (string) LanguageArticles-->((i*3)+1);   ! el, la, los, las
        if (acode == 2) print (string) LanguageArticles-->((i*3)+2);   ! un, una, unos, unas
    }
];

! ------------------------------------------------------------------------------
! Reemplazo de Identical para manejar la identidad de objetos en español
! ------------------------------------------------------------------------------

[ Identical o1 o2 p1 p2 n1 n2 i j flag;
    ! Objetos idénticos si son el mismo objeto
    if (o1 == o2) rtrue;
    
    ! Si alguno no es un objeto, no son idénticos
    if (~~(o1 ofclass Object) || ~~(o2 ofclass Object)) rfalse;
    
    ! Comprobar si tienen las mismas propiedades relevantes
    if (o1.name ~= o2.name) rfalse;
    if (o1.gender ~= o2.gender) rfalse;
    if ((o1 has female && o2 hasnt female) || (o1 hasnt female && o2 has female)) rfalse;
    if ((o1 has pluralname && o2 hasnt pluralname) || (o1 hasnt pluralname && o2 has pluralname)) rfalse;
    
    ! Comprobar propiedades específicas del español
    if (o1 provides name_f && o2 provides name_f) {
        if (o1.name_f ~= o2.name_f) rfalse;
    } else if ((o1 provides name_f) || (o2 provides name_f)) rfalse;
    
    if (o1 provides name_fp && o2 provides name_fp) {
        if (o1.name_fp ~= o2.name_fp) rfalse;
    } else if ((o1 provides name_fp) || (o2 provides name_fp)) rfalse;
    
    if (o1 provides name_mp && o2 provides name_mp) {
        if (o1.name_mp ~= o2.name_mp) rfalse;
    } else if ((o1 provides name_mp) || (o2 provides name_mp)) rfalse;
    
    ! Si llegamos aquí, los objetos son idénticos
    rtrue;
];

! ------------------------------------------------------------------------------
! Reemplazo de TryGivenObject para manejar objetos en español
! ------------------------------------------------------------------------------

[ TryGivenObject obj verb;
    ! Comprobar si el objeto es válido para el verbo
    if (obj == 0) rfalse;
    
    ! Comprobar si el objeto tiene la propiedad del verbo
    if (obj provides verb) {
        if (RunRoutines(obj, verb) ~= 0) rtrue;
    }
    
    ! Comprobar si el objeto tiene propiedades específicas del español
    if (obj has nombreusado) {
        give obj ~nombreusado;
    }
    
    rfalse;
];

! ------------------------------------------------------------------------------
! Reemplazo de Indefart para manejar artículos indefinidos en español
! ------------------------------------------------------------------------------

[ Indefart obj i;
    if (obj == 0) {
        print (string) NOTHING__TX;
        rtrue;
    }
    
    ! Usar UnUnaUnosUnas para imprimir el artículo indefinido correcto
    if (obj has pluralname) {
        if (obj has female) print "unas "; else print "unos ";
    } else {
        if (obj has female) print "una "; else print "un ";
    }
    
    PrintShortName(obj);
];

! ------------------------------------------------------------------------------
! Reemplazo de BestGuess para mejorar las suposiciones del parser
! ------------------------------------------------------------------------------

[ BestGuess context i j k good_flag good_value;
    good_value = 0; good_flag = 0;
    
    ! Buscar el mejor objeto que coincida con el contexto
    for (i=1: i<=scope_objects: i++) {
        j = scope-->i;
        k = context(j);
        if (k > good_value) {
            good_value = k;
            good_flag = j;
        }
    }
    
    return good_flag;
];

! ------------------------------------------------------------------------------
! Reemplazo de NounDomain para manejar la resolución de nombres en español
! ------------------------------------------------------------------------------

[ NounDomain domain1 domain2 context
    first_word i j k l answer_words marker;
    
    ! Guardar la posición actual en el buffer
    marker = wn;
    match_length = 0; number_matched = 0; match_from = wn;
    
    ! Si estamos en modo de pregunta ¿Cuál exactamente...?
    if (PreguntaCualExactamente == 1) {
        PreguntaCualExactamente = 0;
        
        ! Comprobar si la respuesta es un nuevo comando
        if (NextWord() == 'mira' or 'l//' or 'x//' or 'examina' or 'z//' or 'espera') {
            wn = match_from;
            return -1;
        }
        
        ! Volver a la posición original
        wn = match_from;
    }
    
    ! Comprobar si estamos en modo de pregunta Sí/No
    if (PreguntaSiNo == 1) {
        PreguntaSiNo = 0;
        
        ! Comprobar si la respuesta es "sí" o "no"
        i = NextWord();
        if (i == 'si' or 's//' or 'sí') {
            return 1;
        }
        if (i == 'no' or 'n//') {
            return 0;
        }
        
        ! Si no es sí o no, volver a la posición original
        wn = match_from;
    }
    
    ! Llamar a la función original
    return NounDomainOriginal(domain1, domain2, context);
];

! ------------------------------------------------------------------------------
! Función original de NounDomain (debe implementarse según la versión de Inform)
! ------------------------------------------------------------------------------

[ NounDomainOriginal domain1 domain2 context
    first_word i j k l answer_words;
    
    ! Implementación básica para evitar errores
    ! En una implementación real, esto debería ser una copia de la función
    ! NounDomain original de la biblioteca Inform
    
    return 0;
];