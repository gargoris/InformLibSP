! ==============================================================================
!   SPANISH_CONFIG:  Configuración para usar español en Inform 6
!
!   Este archivo debe ser incluido ANTES de Parser.h para evitar conflictos
!   entre los archivos de definición de idioma.
!
! ==============================================================================

System_file;

! Definir que ya hemos incluido english.h para evitar que el parser lo incluya
#Ifndef LIBRARY_ENGLISH;
Constant LIBRARY_ENGLISH;
#Endif;

! Definir que ya hemos incluido spanish.h para evitar inclusiones duplicadas
#Ifndef LIBRARY_SPANISH;
Constant LIBRARY_SPANISH;
#Endif;

! Definir constantes necesarias que normalmente estarían en english.h
Constant EnglishNaturalLanguage;
Constant SpanishNaturalLanguage;

! Definir constantes de género
Constant LanguageAnimateGender = male;
Constant LanguageInanimateGender = neuter;
Constant LanguageContractionForms = 2;

! Definir constantes de texto necesarias para el parser
Constant DARKNESS__TX   = "Oscuridad";
Constant YOURSELF__TX   = "ti mismo";
Constant MYSELF__TX     = "mí mismo";
Constant YOU__TX        = "Tú";
Constant THE__TX        = "el";
Constant COMMA__TX      = ", ";
Constant AND__TX        = " y ";
Constant OR__TX         = " o ";
Constant NOTHING__TX    = "nada";
Constant IS__TX         = " es";
Constant ARE__TX        = " son";
Constant IS2__TX        = "es ";
Constant ARE2__TX       = "son ";
Constant WAS__TX        = " estaba";
Constant WERE__TX       = " estaban";
Constant WAS2__TX       = "estaba ";
Constant WERE2__TX      = "estaban ";
Constant IS3__TX        = " está";
Constant ARE3__TX       = " están";
Constant IS4__TX        = "está ";
Constant ARE4__TX       = "están ";
Constant HAS__TX        = " tiene";
Constant HAVE__TX       = " tienen";
Constant HAS2__TX       = "tiene ";
Constant HAVE2__TX      = "tienen ";
Constant HAS3__TX       = " ha";
Constant HAVE3__TX      = " han";
Constant HAS4__TX       = "ha ";
Constant HAVE4__TX      = "han ";
Constant THAT__TX       = "eso";
Constant THOSE__TX      = "esos";
Constant THOSET__TX     = "esas cosas";
Constant WHICH__TX      = "cuál";
Constant WHOM__TX       = "quién";

! Incluir el archivo de definición del lenguaje español
Include "spanish.h";