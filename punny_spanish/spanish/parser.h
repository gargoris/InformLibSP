! Parte de PunyInform: Parser adaptado para español
! Extensiones y adaptaciones específicas para el análisis sintáctico en español
! Compatible con la arquitectura original de PunyInform

System_file;

! Palabras clave en español que necesitan reconocimiento especial
Constant TODO_PALABRA_ES     = 'todo';
Constant EXCEPTO_PALABRA1_ES = 'excepto';
Constant EXCEPTO_PALABRA2_ES = 'menos';
Constant Y_PALABRA_ES        = 'y';
Constant ENTONCES_PALABRA_ES = 'entonces';
Constant COMA_PALABRA_ES     = 'coma,';

! Strings de objetos en español para el parser
#Ifndef ALGO_STR_ES;
Constant ALGO_STR_ES = "algo";
#Endif;
#Ifndef ALGUIEN_STR_ES;
Constant ALGUIEN_STR_ES = "alguien";
#Endif;
#Ifndef DIRECCION_STR_ES;
Constant DIRECCION_STR_ES = "(alguna dirección)";
#Endif;

! Redefinir las constantes de palabras especiales para usar versiones españolas
! cuando sea apropiado
#Ifdef USAR_PARSER_ESPANYOL;
#Ifndef ALL_WORD;
Constant ALL_WORD = TODO_PALABRA_ES;
#Endif;
#Ifndef EXCEPT_WORD1;
Constant EXCEPT_WORD1 = EXCEPTO_PALABRA1_ES;
#Endif;
#Ifndef EXCEPT_WORD2;
Constant EXCEPT_WORD2 = EXCEPTO_PALABRA2_ES;
#Endif;
#Ifndef AND_WORD;
Constant AND_WORD = Y_PALABRA_ES;
#Endif;
#EndIf;

! Array de direcciones en español
#IfDef OPTIONAL_FULL_DIRECTIONS;
Array _direcciones_dict_palabras_es static --> 
	'n//' 's//' 'e//' 'o//' 'ne' 'no' 'se' 'so' 'arriba' 'abajo' 'dentro' 'fuera'
	'norte' 'sur' 'este' 'oeste' 'noreste' 'noroeste' 'sureste' 'suroeste' 
	'arriba' 'abajo' 'dentro' 'fuera';

Array direccion_nombres_array_es static --> 
	"dirección" "norte" "sur" "este" "oeste" "noreste" "noroeste" 
	"sureste" "suroeste" "arriba" "abajo" "dentro" "fuera";
#IfNot;
Array _direcciones_dict_palabras_es static --> 
	'n//' 's//' 'e//' 'o//' 'arriba' 'abajo' 'dentro' 'fuera'
	'norte' 'sur' 'este' 'oeste' 'arriba' 'abajo' 'dentro' 'fuera';

Array direccion_nombres_array_es static --> 
	"dirección" "norte" "sur" "este" "oeste" "arriba" "abajo" "dentro" "fuera";
#EndIf;

! Función para respuestas Sí/No en español
[ SiONo n;
	for (::) {
		_ReadPlayerInput(true, true);
		n = parse -> 1;
		parse -> 1 = 0;
		if(n == 1) {
			! respuesta de una palabra
			n = parse --> 1;
			if(n == 'si' or 'sí' or 's//') rtrue;
			if(n == 'no' or 'n//') rfalse;
			if(n == 'vale' or 'bueno' or 'claro') rtrue;
		}
		PrintMsg(MSG_YES_OR_NO);
	}
];

! Función auxiliar para determinar si una palabra es un artículo español
[ EsArticuloEspanyol p_palabra;
	if(p_palabra == 'el' or 'la' or 'los' or 'las' or 
	              'un' or 'una' or 'unos' or 'unas') rtrue;
	rfalse;
];

! Función para saltar artículos en español durante el parsing
[ SaltarArticulosEspanyoles p_parse_pointer;
	while(EsArticuloEspanyol(p_parse_pointer --> 0)) {
		wn = wn + 1;
		p_parse_pointer = p_parse_pointer + 4;
		if(wn > num_words) return p_parse_pointer;
	}
	return p_parse_pointer;
];

! Extensión de la función para probar números escritos en español
#Ifdef OPTIONAL_ALLOW_WRITTEN_NUMBERS;
Array NumerosEspanyoles static table
	'uno' 1 'dos' 2 'tres' 3 'cuatro' 4 'cinco' 5
	'seis' 6 'siete' 7 'ocho' 8 'nueve' 9 'diez' 10
	'once' 11 'doce' 12 'trece' 13 'catorce' 14 'quince' 15
	'dieciséis' 16 'diecisiete' 17 'dieciocho' 18 'diecinueve' 19 'veinte' 20;

[ NumeroPalabraEspanyol p_o _i _n;
	! Intentar parsear "uno" hasta "veinte"
	_n = NumerosEspanyoles-->0;
#Ifv5;
	@log_shift _n (-1) -> _n; ! Dividir por 2
	@add NumerosEspanyoles 2 -> sp;
	@scan_table p_o sp _n $84 -> _i ?_encontrado;
	return 0;
._encontrado;
	return _i-->1;
#Ifnot;
	for(_i = 1 : _i <= _n : _i = _i + 2)
		if (p_o == NumerosEspanyoles-->_i) return NumerosEspanyoles-->(_i+1);
	return 0;
#Endif;
];
#Endif;

! Función extendida para manejar direcciones en español
[ DireccionEspanyola p_palabra;
	switch(p_palabra) {
		'norte', 'n//': return n_to;
		'sur', 's//': return s_to;
		'este', 'e//': return e_to;
		'oeste', 'o//': return w_to;
		'arriba', 'subir': return u_to;
		'abajo', 'bajar': return d_to;
		'dentro', 'adentro': return in_to;
		'fuera', 'afuera', 'salir': return out_to;
#IfDef OPTIONAL_FULL_DIRECTIONS;
		'noreste', 'ne': return ne_to;
		'noroeste', 'no': return nw_to;
		'sureste', 'se': return se_to;
		'suroeste', 'so': return sw_to;
#EndIf;
		default: return 0;
	}
];

! Función para imprimir patrones de sintaxis en español
[ _ImprimirSintaxisPatronEs p_pattern p_noun _num_preps _token _type _data;
	! Escribir qué patrón esperábamos, algo como:
	! "Creo que querías decir \"meter todo en algo\". Inténtalo de nuevo."
	PrintMsg(MSG_PARSER_BAD_PATTERN_PREFIX);
	print (verbname) verb_word;
	for(_token = p_pattern + 3: _token->0 ~= TT_END: _token = _token + 3) {
		_type = (_token -> 0) & $0f;
		_data = (_token + 1) --> 0;
		! comprobar si esta es una nueva lista de preposiciones
		if(_token->0 == TOKEN_FIRST_PREP or TOKEN_SINGLE_PREP) _num_preps = 0;
		if(_type == TT_PREPOSITION) {
			! solo escribir el primer elemento en una lista de preposiciones alternativas
			if(_num_preps == 0) print " ", (address) _data;
			++_num_preps;
		} else {
			print " ";
			if(p_noun == 0) {
				if(_type == TT_ROUTINE_FILTER && _data == ADirection) {
					print (string) DIRECCION_STR_ES;
				} else if(second == 0) {
					if(_type == TT_OBJECT && _token->2 == CREATURE_OBJECT) {
						print (string) ALGUIEN_STR_ES;
					} else {
						print (string) ALGO_STR_ES;
					}
				} else print (name) second;
			} else {
				if(noun ~= 0 && metaclass(noun) ~= ROUTINE) {
					p_noun = 0; ! evitar repetición
					if(parser_all_found) print "todo"; else print (name) noun;
				} else if(_type == TT_OBJECT && _token->2 == CREATURE_OBJECT) {
					print (string) ALGUIEN_STR_ES;
				} else {
					print (string) ALGO_STR_ES;
				}
			}
		}
	}
	PrintMsg(MSG_PARSER_BAD_PATTERN_SUFFIX);
];

! Función para preguntar cuál sustantivo en español
[ _PreguntarCualSustantivo p_num_matching_nouns _i;
	print "¿Te refieres a ";
	for(_i = 1 : _i <= p_num_matching_nouns : _i++) {
		if(_i > 1) {
			if(_i == p_num_matching_nouns) {
				print " o a ";
			} else {
				print ", a ";
			}
		}
		print (the) which_object --> _i;
	}
	print "?";
];

! Función para manejar formas reflexivas españolas
[ EsFormaReflexiva p_palabra;
	! Detectar si una palabra termina en -se (forma reflexiva)
	! Esto es una aproximación simple; un parser completo necesitaría
	! análisis morfológico más sofisticado
	if(p_palabra == 'levantarse' or 'sentarse' or 'acostarse' or 
	              'ponerse' or 'quitarse' or 'moverse' or 'irse') rtrue;
	rfalse;
];

! Función para reconocer formas imperativas españolas
[ EsImperativo p_palabra;
	! Reconocer formas imperativas comunes
	! Esta es una lista simplificada; un parser completo necesitaría
	! un análisis morfológico más exhaustivo
	if(p_palabra == 've' or 'ven' or 'coge' or 'toma' or 'deja' or 
	              'mira' or 'abre' or 'cierra' or 'entra' or 'sal') rtrue;
	rfalse;
];

! Función auxiliar para manejar concordancia de género en mensajes
[ ConcordanciaGenero p_obj p_masculino p_femenino;
	if(p_obj has female) print (string) p_femenino;
	else print (string) p_masculino;
];

! Función auxiliar para manejar concordancia de número en mensajes  
[ ConcordanciaNumero p_obj p_singular p_plural;
	if(p_obj has pluralname) print (string) p_plural;
	else print (string) p_singular;
];

! Funciones de utilidad para gramática española
[ EsMasculino p_obj;
	if(p_obj hasnt female) rtrue;
	rfalse;
];

[ EsFemenino p_obj;
	if(p_obj has female) rtrue;
	rfalse;
];

[ EsPlural p_obj;
	if(p_obj has pluralname) rtrue;
	rfalse;
];

[ EsSingular p_obj;
	if(p_obj hasnt pluralname) rtrue;
	rfalse;
];

! Extensión para reconocer patrones específicos del español
[ ReconocerPatronEspanyol p_input_words _i _palabra;
	! Buscar patrones específicos del español como:
	! - "al norte" (contracción de "a el norte")
	! - "del sur" (contracción de "de el sur")
	! - Construcciones con artículo + sustantivo
	
	for(_i = 1; _i <= p_input_words; _i++) {
		_palabra = parse-->(_i*2-1);
		
		! Manejar contracciones
		if(_palabra == 'al') {
			! "al" = "a" + "el"
			! Podríamos expandir esto internamente
			continue;
		}
		if(_palabra == 'del') {
			! "del" = "de" + "el"  
			! Podríamos expandir esto internamente
			continue;
		}
	}
	
	! Devolver el número de palabras procesadas
	return p_input_words;
];

! Include las funciones principales del parser original
! Las funciones específicas de español se pueden usar como extensiones