! ==============================================================================
!   LANGUAGE_CONFIG:  Configuración de idioma para Inform 6
!
!   Este archivo permite seleccionar el idioma de la librería sin conflictos
!   entre los archivos de definición de idioma.
!
! ==============================================================================

System_file;

#Ifndef LANGUAGE_CONFIG_INCLUDED;
Constant LANGUAGE_CONFIG_INCLUDED;

! Si se define SPANISH_LANGUAGE, se usará el idioma español
#Ifdef SPANISH_LANGUAGE;
    ! Evitar que se incluya english.h automáticamente
    #Ifndef LIBRARY_ENGLISH;
    Constant LIBRARY_ENGLISH;
    #Endif;
    
    ! Evitar que se incluya spanish.h automáticamente
    #Ifndef LIBRARY_SPANISH;
    Constant LIBRARY_SPANISH;
    #Endif;
#Endif;

#Endif; ! LANGUAGE_CONFIG_INCLUDED