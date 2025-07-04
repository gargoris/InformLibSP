! ######################### PunyInform Español
! 
! Biblioteca estándar PunyInform adaptada al español
! Para crear ficción interactiva en español usando Inform 6
! Compatible con computadoras de 8-bit como la Commodore 64
!
! Basado en PunyInform por Johan Berntsson y otros contribuidores
! Adaptación al español creada con Claude Code
!
! Para usar esta biblioteca, include este archivo en lugar de puny.h:
! Include "spanish/puny_spanish.h";

System_file;

! Definir que estamos usando el parser español
Constant USAR_PARSER_ESPANYOL;

! Información de versión
Constant PUNYINFORM_SPANISH_VERSION = "1.0";

! Primero incluir las definiciones base de PunyInform
Include "globals.h";

! Luego incluir las extensiones españolas
Include "spanish/parser.h";
Include "spanish/messages.h";

! Redefinir algunas constantes para el español antes de incluir puny.h
#Undef SOMETHING_STR;
#Undef SOMEONE_STR;
#Undef SOMEDIRECTION_STR;
Constant SOMETHING_STR = ALGO_STR_ES;
Constant SOMEONE_STR = ALGUIEN_STR_ES;
Constant SOMEDIRECTION_STR = DIRECCION_STR_ES;

! Incluir la implementación principal de PunyInform
! NOTA: puny.h ya incluye scope.h, no lo incluimos por separado
Include "puny.h";

! Incluir la gramática española AL FINAL para que sobrescriba la inglesa
Include "spanish/grammar.h";

! Objeto Directions extendido para español
Object DireccionesEs "direcciones"
	with
		description "Una mirada en esa dirección no revela nada nuevo.",
		short_name [;
			print (string) direccion_nombres_array_es-->selected_direction_index;
			rtrue;
		],
#IfV5;
		parse_name [_parse _i _w _arr;
#IfNot;
		parse_name [_parse _i _w;
#EndIf;
#IfV5;
			@log_shift wn 2 -> _parse; ! Multiplicar por 4
			_parse = parse + _parse - 2;

			_w = _parse-->0;
			_arr = _direcciones_dict_palabras_es;
			if(normal_directions_enabled) {
				@scan_table _w _arr (DIRECTION_COUNT * 2) -> _i ?_palabra_encontrada;
				if(_w == 'suelo' or 'piso') {
					selected_direction_index = DIRECTION_COUNT - 2;
					jump _encontrada_y_direccion_fijada;
				}
			}
			
			! sin coincidencia
			return 0;
._palabra_encontrada;
			_i = _i - _arr;
			@log_shift _i (-1) -> _i; ! Dividir por 2
			selected_direction_index = (_i % DIRECTION_COUNT) + 1;
._encontrada_y_direccion_fijada;
			selected_direction = direction_properties_array -> selected_direction_index;
			return 1;
#IfNot;
			! Esto es V3
			_parse = parse+4*wn-2;
			_w = _parse-->0;

			if(normal_directions_enabled) {
				@je _w 'fuera' ?_encontrada_fuera;
				@je _w 'dentro' 'adentro' ?_encontrada_dentro;
				@je _w 'abajo' 'bajar' ?_encontrada_abajo;
				@je _w 'suelo' 'piso' ?_encontrada_abajo;
				@je _w 'arriba' 'subir' ?_encontrada_arriba;
#Ifdef OPTIONAL_FULL_DIRECTIONS;
				@je _w 'se' 'sureste' ?_encontrada_se;
				@je _w 'so' 'suroeste' ?_encontrada_so;
				@je _w 'ne' 'noreste' ?_encontrada_ne;
				@je _w 'no' 'noroeste' ?_encontrada_no;
#Endif;
				@je _w 'e//' 'este' ?_encontrada_e;
				@je _w 'o//' 'oeste' ?_encontrada_o;
				@je _w 's//' 'sur' ?_encontrada_s;
				@je _w 'n//' 'norte' ?_encontrada_n;
			}

      		! No se encontró dirección
			return 0;

._encontrada_fuera; @inc _i;
._encontrada_dentro; @inc _i;
._encontrada_abajo; @inc _i;
._encontrada_arriba; @inc _i;
#Ifdef OPTIONAL_FULL_DIRECTIONS;
._encontrada_so; @inc _i;
._encontrada_se; @inc _i;
._encontrada_no; @inc _i;
._encontrada_ne; @inc _i;
#Endif;
._encontrada_o; @inc _i;
._encontrada_e; @inc _i;
._encontrada_s; @inc _i;
._encontrada_n; @inc _i;

			selected_direction_index = _i;
			selected_direction = direction_properties_array -> selected_direction_index;
			return 1;
#EndIf;
		],
has scenery
#Ifdef OPTIONAL_REACTIVE_PARSE_NAME;
		reactive
#Endif;
;

! Función principal de inicialización para juegos en español
[ InicializarEspanyol;
	! Configurar el idioma
	print "^[PunyInform Español v", (string) PUNYINFORM_SPANISH_VERSION;
	print " basado en PunyInform v", PUNYINFORM_MAJOR_VERSION, ".", PUNYINFORM_MINOR_VERSION;
	if(PUNYINFORM_PATCH_VERSION) print ".", PUNYINFORM_PATCH_VERSION;
	print "]^";
	
	! Configurar direcciones
	normal_directions_enabled = true;
	
	! Reemplazar la función YesOrNo con la versión española
	YesOrNo = SiONo;
];

! Función para imprimir el banner en español
[ BannerEspanyol _i;
	new_line;
#IfDef Story;
	#IfV5;
		style bold;
	#EndIf;
		print (string) Story;
	#IfV5;
		style roman;
	#EndIf;
	#IfDef Headline;
		print (string) Headline;
	#IfNot;
		new_line;
	#EndIf;
#EndIf;
	print "Versión ", (0-->1) & $03ff, " / Número de serie ";
	for (_i = 18:_i < 24: _i++) print (char) 0->_i;
	print " / Inform v";
	inversion;
	print " PunyInform Español v", (string) PUNYINFORM_SPANISH_VERSION;
	print " (basado en PunyInform v", PUNYINFORM_MAJOR_VERSION, ".", PUNYINFORM_MINOR_VERSION;
	if(PUNYINFORM_PATCH_VERSION) print ".", PUNYINFORM_PATCH_VERSION;
	print ")";
	_i = 0;
#IfDef STRICT_MODE;
	#IfV5;
	print " S";
	_i = 1;
	#EndIf;
#EndIf;
#IfDef DEBUG;
	if(_i == 0) print " ";
	print "D";
	_i = 1;
#EndIf;
#IfTrue RUNTIME_ERRORS > 0;
	if(_i == 0) print " ";
	print "R";
#EndIf;
	new_line;
];

! Redefinir la función Banner para usar la versión española
#Undef Banner;
[ Banner; BannerEspanyol(); ];

! Comentarios de documentación:
!
! CÓMO USAR ESTA BIBLIOTECA:
!
! 1. Include "spanish/puny_spanish.h"; al principio de tu juego
! 2. Llama a InicializarEspanyol() en tu función Initialise
! 3. Define tus objetos usando has female para objetos femeninos
! 4. Los verbos ya están definidos en español en grammar.h
!
! EJEMPLOS DE COMANDOS QUE FUNCIONARÁN:
!
! > coger la llave
! > examinar el cofre  
! > abrir la puerta con la llave
! > ir al norte
! > meter las monedas en la bolsa
! > inventario
! > mirar
!
! CARACTERÍSTICAS ESPECIALES:
!
! - Soporte para género (masculino/femenino) con "has female"
! - Soporte para número (singular/plural) con "has pluralname"  
! - Artículos correctos (el/la/los/las, un/una/unos/unas)
! - Preposiciones españolas (a, de, en, con, por, para, etc.)
! - Direcciones en español (norte, sur, este, oeste, arriba, abajo, etc.)
! - Mensajes completamente traducidos al español
! - Comandos meta en español (inventario, guardar, cargar, etc.)
!
! Para más información, consulta el archivo CLAUDE.md