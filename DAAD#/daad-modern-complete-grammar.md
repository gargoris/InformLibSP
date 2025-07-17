# Gramática DAAD Moderno Completa - Solo Español

## Estructura Principal del Programa

```ebnf
Programa ::= { DirectivaIncluir } [ SeccionJuego ] { Seccion }

DirectivaIncluir ::= "incluir" CadenaTexto

Seccion ::= SeccionJuego
          | SeccionVocabulario  
          | SeccionLocalidades
          | SeccionObjetos
          | SeccionNPCs
          | SeccionMensajes
          | SeccionRespuestas
          | SeccionProcesos
          | SeccionSintaxis
          | SeccionFlags
          | SeccionFinales
          | SeccionDepuracion
          | SeccionExtensiones
```

## Sección Juego (Configuración Principal)

```ebnf
SeccionJuego ::= "juego" "{" { PropiedadJuego } "}"

PropiedadJuego ::= "titulo:" CadenaTexto
                 | "autor:" CadenaTexto
                 | "version:" CadenaTexto
                 | "idioma:" CadenaTexto
                 | "localizacion_inicial:" Identificador
                 | "puntuacion_maxima:" Entero
                 | "limite_tiempo:" Entero
                 | "tiempo_inicial:" Entero
                 | "objetos_maximos:" Entero
                 | "longitud_palabra:" Entero
                 | "modo_depuracion:" Booleano
                 | "preservar_estado:" Booleano
                 | "descripcion:" CadenaTexto
                 | Identificador ":" Valor
```

## Sección Vocabulario Español

```ebnf
SeccionVocabulario ::= "vocabulario" "{" { CategoriaVocab } "}"

CategoriaVocab ::= TipoVocabulario ":" MapaVocabulario

TipoVocabulario ::= "verbos" | "sustantivos" | "adjetivos" | "adverbios"
                  | "preposiciones" | "conjunciones" | "direcciones" | "sistema"

MapaVocabulario ::= "{" { EntradaVocabulario } "}"

EntradaVocabulario ::= Entero "[" ListaCadenas "]" [ ClausulaSinonimos ]

ClausulaSinonimos ::= "sinonimos:" "[" ListaCadenas "]"
```

## Sección Flags Simbólicos

```ebnf
SeccionFlags ::= "flags" "{" { DefinicionFlag } "}"

DefinicionFlag ::= "flag" Identificador "=" Entero ";"
                 | "contador" Identificador "=" Entero ";"

AccesoFlag ::= NivelAcceso ":" Identificador

NivelAcceso ::= "solo_lectura" | "lectura_escritura" | "solo_sistema" | "solo_depuracion"
```

## Sección Localidades Avanzadas

```ebnf
SeccionLocalidades ::= "localidades" "{" { DefinicionLocalidad } "}"

DefinicionLocalidad ::= "localidad" Identificador "{" { PropiedadLocalidad } "}"

PropiedadLocalidad ::= "desc:" CadenaTexto
                     | "conexiones:" "{" { Conexion } "}"
                     | "objetos:" "[" ListaIdentificadores "]"
                     | "npcs:" "[" ListaIdentificadores "]"
                     | "nivel_luz:" Entero
                     | "visitas:" Entero
                     | "propiedades:" "{" { AsignacionPropiedad } "}"
                     | "al_entrar:" BloqueAccion
                     | "al_salir:" BloqueAccion
                     | "cada_turno:" BloqueAccion
                     | "primera_visita:" CadenaTexto
                     | Identificador ":" Valor

Conexion ::= Identificador ":" ( Identificador | ExpresionCondicional )

ExpresionCondicional ::= "si" "(" Condicion ")" "entonces" Identificador [ "sino" Identificador ]
```

## Sección Objetos Vestibles y Avanzados

```ebnf
SeccionObjetos ::= "objetos" "{" { DefinicionObjeto } "}"

DefinicionObjeto ::= "objeto" Identificador "{" { PropiedadObjeto } "}"

PropiedadObjeto ::= "nombre:" CadenaTexto
                  | "desc:" CadenaTexto
                  | "localizacion:" UbicacionObjeto
                  | "desc_vestido:" CadenaTexto
                  | "desc_examen:" CadenaTexto
                  | "propiedades:" "{" { AsignacionPropiedadObjeto } "}"
                  | "al_usar:" BloqueAccion
                  | "al_examinar:" BloqueAccion
                  | "al_vestir:" BloqueAccion
                  | "al_quitar:" BloqueAccion

UbicacionObjeto ::= Identificador | "inventario" | "ninguna_parte"

AsignacionPropiedadObjeto ::= PropiedadFisica ":" Valor

PropiedadFisica ::= "cogible" | "vestible" | "vestido_inicialmente" | "fuente_luz"
                  | "arma" | "armadura" | "magico" | "maldito" | "fragil"
                  | "abrible" | "bloqueable" | "contenedor" | "comestible" | "bebible"
                  | "peso" | "tamaño" | "valor" | "durabilidad" | "ranura_vestir"
                  | "daño" | "proteccion" | "nivel_encantamiento"
```

## Sección NPCs (Personajes No Jugadores)

```ebnf
SeccionNPCs ::= "npcs" "{" { DefinicionNPC } "}"

DefinicionNPC ::= "npc" Identificador "{" { PropiedadNPC } "}"

PropiedadNPC ::= "nombre:" CadenaTexto
               | "desc:" CadenaTexto
               | "localizacion:" Identificador
               | "comportamiento:" ComportamientoNPC
               | "estadisticas:" "{" { AsignacionEstadistica } "}"
               | "inventario:" "[" ListaIdentificadores "]"
               | "estado:" "{" { AsignacionEstado } "}"
               | "dialogo:" "{" { NodoDialogo } "}"
               | "cada_turno:" BloqueAccion
               | "al_hablar:" BloqueAccion
               | "al_atacar:" BloqueAccion

ComportamientoNPC ::= "estatico"
                    | "vagar" "[" ListaIdentificadores "]"
                    | "patrullar" "[" ListaIdentificadores "]"
                    | "seguir" Identificador
                    | "personalizado" CadenaTexto

AsignacionEstadistica ::= Identificador ":" Entero

AsignacionEstado ::= Identificador ":" Valor

NodoDialogo ::= Identificador ":" "{" { PropiedadDialogo } "}"

PropiedadDialogo ::= "texto:" CadenaTexto
                   | "condicion:" Condicion
                   | "al_entrar:" "[" ListaAcciones "]"
                   | "respuestas:" "{" { RespuestaDialogo } "}"

RespuestaDialogo ::= CadenaTexto ":" "{" { PropiedadRespuesta } "}"

PropiedadRespuesta ::= "texto_jugador:" CadenaTexto
                     | "respuesta_npc:" CadenaTexto
                     | "acciones:" "[" ListaAcciones "]"
                     | "siguiente_nodo:" CadenaTexto
```

## Sección Procesos Temporizados (Sistema PSI)

```ebnf
SeccionProcesos ::= "procesos" "{" { DefinicionProceso } "}"

DefinicionProceso ::= TipoProceso Identificador "{" { PropiedadProceso } "}"

TipoProceso ::= "inicial"
              | "cada_turno"
              | "auto"
              | "manejador_timeout"
              | "manejador_interrupcion" "(" Entero ")"
              | "proceso_usuario" "(" Entero ")"
              | "antes_accion_jugador"
              | "despues_accion_jugador"
              | "al_inicio_juego"
              | "al_fin_juego"
              | "periodico" "(" Entero ")"

PropiedadProceso ::= "prioridad:" Entero
                   | "configuracion_timeout:" ConfiguracionTimeout
                   | "mascara_interrupcion:" Entero
                   | "requiere:" Condicion
                   | "frecuencia:" Entero
                   | "hacer:" Accion

ConfiguracionTimeout ::= "{" 
    [ "duracion:" Entero ]
    [ "flags_control:" Entero ]
    [ "preservar_estado:" Booleano ]
    [ "restauracion_auto:" Booleano ]
"}"
```

## Sección Respuestas con Frases Complejas

```ebnf
SeccionRespuestas ::= "respuestas" "{" { DefinicionRespuesta } "}"

DefinicionRespuesta ::= "al" ListaPatrones [ ClausulaRequiere ] [ ClausulaPrioridad ] ClausulaHacer

ListaPatrones ::= PatronComando | "[" ListaCadenas "]" { ListaCadenas }

PatronComando ::= CadenaTexto
                | PatronSecuencial
                | PatronConObjetos
                | PatronComplejo

PatronSecuencial ::= CadenaTexto "y" "luego" CadenaTexto
                   | CadenaTexto "," CadenaTexto [ "," CadenaTexto ]*

PatronConObjetos ::= "usar" "A" "en" "B"
                   | "poner" "A" "sobre" "B"
                   | "hablar" "con" "A" "sobre" "B"
                   | "dar" "A" "a" "B"
                   | "tomar" "A" "de" "B"

PatronComplejo ::= CadenaTexto { OperadorPatron CadenaTexto }

OperadorPatron ::= "y" | "o" | "pero" | "entonces" | "despues"

ClausulaRequiere ::= "requiere:" Condicion

ClausulaPrioridad ::= "prioridad:" Entero

ClausulaHacer ::= "hacer:" Accion
```

## Sistema de Condiciones Avanzado

```ebnf
Condicion ::= CondicionOr

CondicionOr ::= CondicionY { ( "||" | "o" ) CondicionY }

CondicionY ::= CondicionNo { ( "&&" | "y" ) CondicionNo }

CondicionNo ::= [ "no" | "!" ] CondicionAtomica

CondicionAtomica ::= "(" Condicion ")"
                   | CondicionSimple

CondicionSimple ::= CondicionLocalizacion
                  | CondicionObjeto
                  | CondicionFlag
                  | CondicionContador
                  | CondicionJuego
                  | CondicionNPC
                  | CondicionTiempo
                  | CondicionAvanzada

CondicionLocalizacion ::= "en" "(" Identificador ")"

CondicionObjeto ::= "presente" "(" Identificador ")"
                  | "ausente" "(" Identificador ")"
                  | "llevado" "(" Identificador ")"
                  | "vestido" "(" Identificador ")"
                  | "no_vestido" "(" Identificador ")"

CondicionFlag ::= "cero" "(" Identificador ")"
                | "no_cero" "(" Identificador ")"
                | Identificador OperadorComparacion Entero

CondicionContador ::= "turnos" OperadorComparacion Entero
                    | "puntuacion" OperadorComparacion Entero
                    | "tiempo" OperadorComparacion Entero

CondicionJuego ::= "probabilidad" "(" Entero ")"
                 | "mismo" "(" Identificador ")"
                 | "esta_en" "(" Identificador "," Identificador ")"
                 | "es_mayor" "(" Identificador "," Identificador ")"
                 | "es_menor" "(" Identificador "," Identificador ")"

CondicionNPC ::= "npc_en" "(" Identificador "," Identificador ")"
               | "npc_hablando" "(" Identificador ")"
               | "npc_estado" "(" Identificador "," CadenaTexto ")"

CondicionTiempo ::= "timeout_activo" "(" ")"
                  | "interrupcion_activa" "(" Entero ")"
                  | "proceso_activo" "(" Entero ")"

CondicionAvanzada ::= "flag_cambio" "(" Identificador ")"
                    | "objeto_movido" "(" Identificador ")"
                    | "contador_ejecucion" "(" Entero OperadorComparacion Entero ")"
                    | Identificador "(" [ ListaArgumentos ] ")"

OperadorComparacion ::= "==" | "!=" | ">" | ">=" | "<" | "<="
```

## Sistema de Acciones Avanzado

```ebnf
Accion ::= BloqueAccion | AccionSimple

BloqueAccion ::= "{" ListaAcciones "}"

AccionSimple ::= AccionMovimiento
               | AccionObjeto
               | AccionVestible
               | AccionFlag
               | AccionContador
               | AccionJuego
               | AccionMensaje
               | AccionFlujo
               | AccionTemporal
               | AccionNPC
               | AccionCondicional
               | AccionAvanzada

AccionMovimiento ::= "ir_a" "(" Identificador ")"
                   | "mover" "(" Identificador ")"
                   | "teletransportar" "(" Identificador "," Identificador ")"

AccionObjeto ::= "coger" "(" Identificador ")"
               | "soltar" "(" Identificador ")"
               | "destruir" "(" Identificador ")"
               | "crear" "(" Identificador [ "," Identificador ] ")"
               | "intercambiar" "(" Identificador "," Identificador ")"
               | "colocar" "(" Identificador "," Identificador ")"

AccionVestible ::= "vestir" "(" Identificador ")"
                 | "quitar" "(" Identificador ")"

AccionFlag ::= "activar" "(" Identificador ")"
             | "desactivar" "(" Identificador ")"

AccionContador ::= "asignar" "(" Identificador "," Entero ")"
                 | "incrementar" "(" Identificador [ "," Entero ] ")"
                 | "decrementar" "(" Identificador [ "," Entero ] ")"

AccionJuego ::= "añadir_puntos" "(" Entero ")"
              | "quitar_puntos" "(" Entero ")"
              | "cambiar_tiempo" "(" Entero ")"
              | "guardar" "(" ")"
              | "cargar" "(" ")"
              | "guardar_ram" "(" Entero ")"
              | "cargar_ram" "(" Entero ")"
              | "reiniciar" "(" ")"
              | "salir" "(" ")"

AccionMensaje ::= "mensaje" "(" ( CadenaTexto | Identificador ) ")"
                | "imagen" "(" Entero ")"
                | "sonido" "(" [ Entero ] ")"

AccionFlujo ::= "terminar" "(" ")"
              | "fin" "(" ")"

AccionTemporal ::= "pausar" "(" Entero ")"
                 | "configurar_timeout" "(" ConfiguracionTimeout ")"
                 | "limpiar_timeout" "(" ")"
                 | "llamar_proceso" "(" Entero ")"
                 | "habilitar_interrupcion" "(" Entero ")"
                 | "deshabilitar_interrupcion" "(" ")"

AccionNPC ::= "mover_npc" "(" Identificador "," Identificador ")"
            | "npc_decir" "(" Identificador "," CadenaTexto ")"
            | "npc_accion" "(" Identificador "," CadenaTexto ")"
            | "cambiar_estado_npc" "(" Identificador "," CadenaTexto "," Valor ")"

AccionCondicional ::= "si" Condicion "{" ListaAcciones "}" [ "sino" "{" ListaAcciones "}" ]

AccionAvanzada ::= "copiar_objeto_objeto" "(" Identificador "," Identificador ")"
                 | "copiar_objeto_flag" "(" Identificador "," Identificador ")"
                 | "copiar_flag_objeto" "(" Identificador "," Identificador ")"
                 | "copiar_flag_flag" "(" Identificador "," Identificador ")"
                 | "externo" "(" Entero "," Entero ")"
                 | "para_todos" "(" Identificador "," BloqueAccion ")"
                 | "depurar" "(" CadenaTexto ")"
                 | "log" "(" CadenaTexto "," NivelLog ")"
                 | "breakpoint" "(" CadenaTexto ")"
                 | Identificador "(" [ ListaArgumentos ] ")"

NivelLog ::= "verboso" | "info" | "aviso" | "error"
```

## Sección Finales Múltiples

```ebnf
SeccionFinales ::= "finales" "{" { DefinicionFinal } "}"

DefinicionFinal ::= "final" Identificador "{" { PropiedadFinal } "}"

PropiedadFinal ::= "condicion:" Condicion
                 | "mensaje:" CadenaTexto
                 | "bonus_puntos:" Entero
                 | "penalizacion_puntos:" Entero
                 | "puntuacion:" Entero
```

## Sección Depuración Avanzada

```ebnf
SeccionDepuracion ::= "depuracion" "{" ConfiguracionDepuracion "}"

ConfiguracionDepuracion ::= 
    [ "log_verboso:" Booleano ]
    [ "paso_a_paso:" Booleano ]
    [ "breakpoints_habilitados:" Booleano ]
    [ "nivel_log:" NivelLog ]
    [ "archivo_salida:" CadenaTexto ]
    [ "monitorear_flags:" "[" ListaEnteros "]" ]
    [ "monitorear_objetos:" "[" ListaIdentificadores "]" ]
    [ "breakpoints:" "[" { BreakpointCondicional } "]" ]

BreakpointCondicional ::= "{" 
    "condicion:" Condicion
    "mensaje:" CadenaTexto
    "detener_ejecucion:" Booleano
"}"
```

## Sección Extensiones

```ebnf
SeccionExtensiones ::= "extensiones" "{" ConfiguracionExtensiones "}"

ConfiguracionExtensiones ::= 
    [ "cargar:" "[" ListaCadenas "]" ]
    [ "caracteristicas_experimentales:" "{" { CaracteristicaExperimental } "}" ]
    [ "sistemas_externos:" "{" { SistemaExterno } "}" ]

CaracteristicaExperimental ::= Identificador ":" Booleano

SistemaExterno ::= Identificador ":" CadenaTexto
```

## Tipos de Datos Básicos

```ebnf
Valor ::= CadenaTexto | Entero | Booleano | Identificador | Lista | Mapa

Lista ::= "[" [ ListaValores ] "]"

Mapa ::= "{" [ EntradasMapa ] "}"

EntradasMapa ::= EntradaMapa { "," EntradaMapa }

EntradaMapa ::= ( CadenaTexto | Identificador ) ":" Valor

ListaAcciones ::= Accion { ";" Accion }

ListaArgumentos ::= Valor { "," Valor }

ListaValores ::= Valor { "," Valor }

ListaCadenas ::= CadenaTexto { "," CadenaTexto }

ListaIdentificadores ::= Identificador { "," Identificador }

ListaEnteros ::= Entero { "," Entero }

Booleano ::= "verdadero" | "falso" | "sí" | "si" | "no"

CadenaTexto ::= '"' { Caracter - '"' | SecuenciaEscape } '"'

SecuenciaEscape ::= '\"' | '\\' | '\n' | '\t'

Entero ::= [ "-" ] Digito { Digito }

Identificador ::= Letra { Letra | Digito | "_" }

Caracter ::= Letra | Digito | Simbolo

Letra ::= "a".."z" | "A".."Z" | "á" | "é" | "í" | "ó" | "ú" | "ñ" | "ü" | "ç"

Digito ::= "0".."9"

Simbolo ::= " " | "!" | "@" | "#" | "$" | "%" | "^" | "&" | "*" | 
           "(" | ")" | "-" | "+" | "=" | "[" | "]" | "{" | "}" |
           "|" | "\" | ":" | ";" | "'" | "<" | ">" | "," | "." |
           "?" | "/" | "~" | "`"
```

## Comentarios y Espacios

```ebnf
Comentario ::= ComentarioLinea | ComentarioBloque

ComentarioLinea ::= "//" { Caracter - NuevaLinea } NuevaLinea

ComentarioBloque ::= "/*" { Caracter } "*/"

NuevaLinea ::= "\n" | "\r\n" | "\r"
```

Esta gramática incluye **todas las características avanzadas** identificadas en el contexto:

- ✅ NPCs con comportamientos complejos y diálogos
- ✅ Sistema PSI completo con procesos temporizados
- ✅ Frases complejas secuenciales y patrones avanzados
- ✅ Objetos vestibles y propiedades extendidas
- ✅ Flags simbólicos con nombres descriptivos
- ✅ Sistema de finales múltiples
- ✅ Depuración avanzada con breakpoints
- ✅ Extensiones y características experimentales
- ✅ Timeouts e interrupciones
- ✅ Condiciones y acciones avanzadas
- ✅ Soporte para includes modulares

¿Quieres que ahora genere la implementación completa con Pidgin?