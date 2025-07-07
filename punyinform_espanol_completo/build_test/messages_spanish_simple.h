! Mensajes en Español - Versión Simplificada
! Sin caracteres especiales problemáticos por el momento
! Autor: Claude Code
! Fecha: 7 de julio de 2025

System_file;

! ######################### SOBRESCRIBIR MENSAJES INGLESES CON ESPAÑOLES

! Redefinir mensajes básicos
#Undef MSG_TAKE_YOURSELF;
Constant MSG_TAKE_YOURSELF "Siempre te tienes a ti mismo.";

#Undef MSG_TAKE_NO_CAPACITY;
Constant MSG_TAKE_NO_CAPACITY "Ya llevas demasiadas cosas.";

#Undef MSG_TAKE_DEFAULT;
Constant MSG_TAKE_DEFAULT "Cogido.";

#Undef MSG_DRINK_NOTHING_SUITABLE;
Constant MSG_DRINK_NOTHING_SUITABLE "No hay nada apropiado para beber aqui.";

#Undef MSG_DROP_DROPPED;
Constant MSG_DROP_DROPPED "Dejado.";

#Undef MSG_THROW_ANIMATE;
Constant MSG_THROW_ANIMATE "Inutil.";

#Undef MSG_THROW_DEFAULT;
Constant MSG_THROW_DEFAULT "Te falta valor en el momento crucial.";

#Undef MSG_SMELL_DEFAULT;
Constant MSG_SMELL_DEFAULT "No hueles nada inesperado.";

#Undef MSG_LISTEN_DEFAULT;
Constant MSG_LISTEN_DEFAULT "No oyes nada inesperado.";

#Undef MSG_TELL_PLAYER;
Constant MSG_TELL_PLAYER "Hablas contigo mismo un rato.";

#Undef MSG_TELL_DEFAULT;
Constant MSG_TELL_DEFAULT "Esto no provoca reaccion alguna.";

#Undef MSG_ENTER_ALREADY;
Constant MSG_ENTER_ALREADY "Pero ya estas ahi!";

#Undef MSG_EXIT_ALREADY;
Constant MSG_EXIT_ALREADY "Pero no estas dentro de nada en este momento!";

#Undef MSG_EXIT_NOT_ON;
Constant MSG_EXIT_NOT_ON "No estas sobre eso.";

#Undef MSG_EXIT_NOT_IN;
Constant MSG_EXIT_NOT_IN "No estas dentro de eso.";

#Undef MSG_GO_CANT_GO;
Constant MSG_GO_CANT_GO "No puedes ir por ahi.";

#Undef MSG_INSERT_ITSELF;
Constant MSG_INSERT_ITSELF "No puedes meter algo dentro de si mismo.";

#Undef MSG_PUTON_ITSELF;
Constant MSG_PUTON_ITSELF "No puedes poner algo sobre si mismo.";

#Undef MSG_ATTACK_DEFAULT;
Constant MSG_ATTACK_DEFAULT "La violencia no es la solucion.";

! ################### MENSAJES DE PARSER CRÍTICOS

#Undef MSG_PARSER_UNKNOWN_SENTENCE;
Constant MSG_PARSER_UNKNOWN_SENTENCE "No entiendo esa frase.";

#Undef MSG_PARSER_CANT_DISAMBIGUATE;
Constant MSG_PARSER_CANT_DISAMBIGUATE "Aun no entiendo a que te refieres.";

#Undef MSG_PARSER_DONT_UNDERSTAND_WORD;
Constant MSG_PARSER_DONT_UNDERSTAND_WORD "Perdon, no entiendo que significa esa palabra.";

! ################### MENSAJES DE LISTADO Y ERRORES

! ######################### FUNCIONES DE MENSAJES ESPAÑOL

! ######################### REDEFINIR PRINTMSG PARA USAR NUESTROS MENSAJES

[ PrintMsg p_msg p_arg_1 p_arg_2;
    ! Usar el sistema estándar que debería usar nuestras constantes redefinidas
    return _PrintMsg(p_msg, p_arg_1, p_arg_2);
];