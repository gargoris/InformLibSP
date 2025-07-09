# Análisis Completo de PunyInform para Conversión al Español

## Resumen Ejecutivo

PunyInform es una biblioteca alternativa a Inform 6 optimizada para crear aventuras textuales compactas y eficientes, especialmente diseñada para computadoras de 8 bits. [GitHub +3](https://github.com/johanberntsson/PunyInform?& w2 == 'de') return 'under';
    if(w1 == 'encima' && w2 == 'de') return 'on';
    if(w1 == 'delante' && w2 == 'de') return 'in_front_of';
    if(w1 == 'detrás' && w2 == 'de') return 'behind';
    if(w1 == 'al' && w2 == 'lado' && NextWord() == 'de') return 'beside';
    
    wn = wn - 2; // Retroceder si no se encontró patrón
    return 0;
];

// Gramática extendida para expresiones adverbiales
Verb 'poner' 'pon' 'ponen' 'ponga' 'pongan'
    * noun 'en' noun                           -> Insert
    * noun 'sobre' noun                        -> PutOn
    * noun 'debajo' 'de' noun                  -> SpanishPutUnder
    * noun 'encima' 'de' noun                  -> PutOn
    * noun 'dentro' 'de' noun                  -> Insert;
```

### 2.4 Sistema de Direcciones Españolas

```inform6
// Sistema de direcciones básicas
Object Directions "dirección"
    with name 'norte' 'n' 'sur' 's' 'este' 'e' 'oeste' 'o'
              'noreste' 'ne' 'noroeste' 'no' 'sureste' 'se' 'suroeste' 'so'
              'arriba' 'subir' 'abajo' 'bajar' 'adentro' 'dentro' 'afuera' 'fuera';

// Sistema de direcciones marítimas españolas
#Ifdef OPTIONAL_SHIP_DIRECTIONS_SPANISH;
Object Directions "dirección"
    with name 'proa' 'pr' 'popa' 'po' 'babor' 'ba' 'estribor' 'es';
#Endif;

// Variables de control
Global spanish_directions_enabled = true;
Global ship_directions_spanish_enabled = false;
```

## 3. SISTEMA DE MENSAJES ESPAÑOL

### 3.1 Estructura de Mensajes

**Tipos de Mensajes:**
- **Estáticos**: Strings simples como "Tomado."
- **Complejos**: Requieren lógica de género/número/concordancia

**Categorías Principales:**
1. **Mensajes del parser** (50+ mensajes)
2. **Mensajes de acciones** (80+ mensajes)
3. **Mensajes de error** (40+ mensajes)
4. **Mensajes del sistema** (30+ mensajes)
5. **Mensajes de debug** (20+ mensajes)

### 3.2 Implementación para Español

**Archivo messages_es.h propuesto:**

```inform6
// Mensajes estáticos simples
Constant MSG_LOOK_DEFAULT_AGAIN "Otra vez";
Constant MSG_WAIT_DEFAULT "Pasa el tiempo...";
Constant MSG_SAVE_DEFAULT "Guardado completado.";
Constant MSG_SAVE_FAILED "Error al guardar.";
Constant MSG_RESTORE_FAILED "Error al restaurar.";

// Mensajes complejos (requieren LibraryMessages)
Constant MSG_TAKE_DEFAULT = 2001;
Constant MSG_DROP_DEFAULT = 2002;
Constant MSG_TAKE_PART_OF = 2003;
Constant MSG_SEARCH_IN_IT_ISARE = 2004;
Constant MSG_PUT_ON_SUPPORTER = 2005;
```

**Sistema LibraryMessages para Español:**

```inform6
[ LibraryMessages p_msg p_arg_1 p_arg_2;
    switch(p_msg) {
        MSG_TAKE_DEFAULT:
            if(p_arg_1 has feminine) {
                if(p_arg_1 has pluralname) print "Tomadas.";
                else print "Tomada.";
            } else {
                if(p_arg_1 has pluralname) print "Tomados.";
                else print "Tomado.";
            }
            
        MSG_SEARCH_IN_IT_ISARE:
            print (The) p_arg_1;
            if(p_arg_1 has pluralname) print " contienen ";
            else print " contiene ";
            WriteListFrom(child(p_arg_1), ENGLISH_BIT);
            print ".";
            
        MSG_PUT_ON_SUPPORTER:
            print "Pones ", (the) p_arg_1, " sobre ", (the) p_arg_2, ".";
    }
];
```

### 3.3 Rutinas de Soporte

```inform6
// Rutina para artículos definidos
[ ArticuloDefinido obj;
    if(obj has pluralname) {
        if(obj has feminine) print "las ";
        else print "los ";
    } else {
        if(obj has feminine) print "la ";
        else print "el ";
    }
];

// Rutina para artículos indefinidos
[ ArticuloIndefinido obj;
    if(obj has pluralname) {
        if(obj has feminine) print "unas ";
        else print "unos ";
    } else {
        if(obj has feminine) print "una ";
        else print "un ";
    }
];
```

## 4. FUNCIONES CLAVE PARA LOCALIZACIÓN

### 4.1 Funciones de Parsing Principal

**_ParseNounPhrase** (Análisis de frases nominales)
```inform6
[ _ParseNounPhrase noun_wordnum descriptor_wn;
    // Versión española que maneja géneros
    if(CheckGenderAgreement(noun_wordnum, descriptor_wn) == false)
        return -1;
    
    // Manejo de artículos españoles
    if(NextWord() == 'el' or 'la' or 'los' or 'las')
        article_found = true;
    
    // Procesamiento de concordancia
    return ProcessSpanishNoun(noun_wordnum);
];
```

**Sistema de Desambiguación Español:**
```inform6
[ SpanishDisambiguation obj_list count;
    local i, chosen_obj;
    
    print "¿Te refieres a ";
    for(i = 0: i < count: i++) {
        if(i > 0) {
            if(i == count - 1) print " o ";
            else print ", ";
        }
        print (the) obj_list->i;
    }
    print "?";
    
    chosen_obj = GetUserChoice();
    return chosen_obj;
];
```

### 4.2 Sistema de Conjugaciones

```inform6
// Sistema de conjugación verbal
[ ConjugarVerbo verbo persona numero tiempo;
    switch(verbo) {
        'tomar':
            switch(persona) {
                1: // yo
                    if(numero == SING) return "tomo";
                    else return "tomamos";
                2: // tú
                    if(numero == SING) return "tomas";
                    else return "tomáis";
                3: // él/ella
                    if(numero == SING) return "toma";
                    else return "toman";
            }
        'ver':
            switch(persona) {
                1: if(numero == SING) return "veo"; else return "vemos";
                2: if(numero == SING) return "ves"; else return "veis";
                3: if(numero == SING) return "ve"; else return "ven";
            }
    }
    return verbo; // fallback
];
```

### 4.3 Sistema de Objetos con Género

```inform6
// Clase base para objetos españoles
Class ObjetoEspanol
    with gender MASC,
         number SING,
         articulo_def "el",
         articulo_indef "un",
         before [;
             // Validaciones de género automáticas
             Take:
                 if(self has feminine) {
                     if(self has pluralname) print "Tomadas.";
                     else print "Tomada.";
                 } else {
                     if(self has pluralname) print "Tomados.";
                     else print "Tomado.";
                 }
                 return true;
         ];
```

## 5. ESTRUCTURA PARA CONVERSIÓN AL ESPAÑOL

### 5.1 Archivos que Necesitan Modificación

**Modificaciones Completas:**
- `messages.h` → `mensajes_es.h`
- `grammar.h` → `gramatica_es.h`
- Secciones específicas de `puny.h`

**Nuevos Archivos Necesarios:**
- `generos_es.h` - Sistema de géneros gramaticales
- `conjugaciones_es.h` - Tabla de conjugaciones verbales
- `articulos_es.h` - Manejo de artículos españoles
- `preposiciones_es.h` - Sistema de preposiciones compuestas

### 5.2 Estructura de Directorios Propuesta

```
lib/
├── core/
│   ├── globals.h
│   ├── puny.h (modificado)
│   └── messages.h (inglés)
├── español/
│   ├── mensajes_es.h
│   ├── gramatica_es.h
│   ├── generos_es.h
│   ├── conjugaciones_es.h
│   └── articulos_es.h
├── extensions/
│   ├── ext_waittime.h
│   ├── ext_talk_menu.h
│   └── ext_cheap_scenery.h
└── localized_extensions/
    ├── ext_waittime_es.h
    ├── ext_talk_menu_es.h
    └── ext_cheap_scenery_es.h
```

### 5.3 Approach para Implementar Géneros

**Arquitectura de Géneros:**
```inform6
Constant MASC = 1;
Constant FEM = 2;
Constant NEUT = 3;
Constant SING = 1;
Constant PLUR = 2;

// Integración con objetos existentes
Object Mesa "mesa"
    with name 'mesa' 'mueble',
         gender FEM,
         number SING,
         description "Una mesa de madera maciza.",
         before [;
             Take:
                 if(self has feminine) print "Tomada.";
                 else print "Tomado.";
         ];
```

**Sistema de Validación de Concordancia:**
```inform6
[ CheckGenderAgreement adj noun;
    local adj_gender, noun_gender;
    
    adj_gender = GetAdjectiveGender(adj);
    noun_gender = GetNounGender(noun);
    
    if(adj_gender != 0 && noun_gender != 0) {
        if(adj_gender != noun_gender) {
            print "La concordancia no es correcta.";
            return false;
        }
    }
    return true;
];
```

## 6. RECOMENDACIONES ESPECÍFICAS

### 6.1 Cronograma de Implementación

**Fase 1 (2-3 semanas): Infraestructura**
- Crear sistema de géneros y números
- Implementar artículos básicos
- Modificar parser para manejo básico de español

**Fase 2 (3-4 semanas): Gramática**
- Sistema de conjugación verbal
- Concordancia adjetival
- Implementar preposiciones compuestas

**Fase 3 (2-3 semanas): Mensajes**
- Traducir y adaptar todos los mensajes
- Implementar LibraryMessages completo
- Pruebas de concordancia

**Fase 4 (1-2 semanas): Optimización**
- Optimizar para memoria limitada
- Pruebas en plataformas z3
- Documentación completa

### 6.2 Consideraciones de Rendimiento

**Impacto en Memoria:**
- Nuevas propiedades: +2KB
- Tablas de conjugación: +3KB
- Mensajes en español: +1KB
- **Total estimado**: +6KB

**Optimizaciones Sugeridas:**
```inform6
// Compresión de conjugaciones
Array ConjugacionesCompactas table
    'ar' 'o' 'as' 'a' 'amos' 'áis' 'an'
    'er' 'o' 'es' 'e' 'emos' 'éis' 'en'
    'ir' 'o' 'es' 'e' 'imos' 'ís' 'en';

// Abbreviations españolas
Abbreviate "que" "con" "una" "para" "desde" "hasta" "muy" "más";
```

### 6.3 Manejo de Expresiones Adverbiales Complejas

**Sistema de Expresiones Espaciales:**
```inform6
[ ParseSpanishSpatialExpression;
    local w1, w2, w3;
    
    w1 = NextWord();
    w2 = NextWord();
    w3 = NextWord();
    
    // "al lado de" = beside
    if(w1 == 'al' && w2 == 'lado' && w3 == 'de') return 'beside';
    
    // "en frente de" = in_front_of
    if(w1 == 'en' && w2 == 'frente' && w3 == 'de') return 'in_front_of';
    
    // "a través de" = through
    if(w1 == 'a' && w2 == 'través' && w3 == 'de') return 'through';
    
    wn = wn - 3; // Retroceder si no se encontró patrón
    return 0;
];
```

**Integración con Gramática:**
```inform6
Verb 'buscar' 'busca' 'buscan' 'busque' 'busquen'
    * noun                                     -> Search
    * 'en' noun                               -> Search
    * 'dentro' 'de' noun                      -> Search
    * 'debajo' 'de' noun                      -> SearchUnder
    * 'detrás' 'de' noun                      -> SearchBehind;
```

## 7. GUÍA DE IMPLEMENTACIÓN TÉCNICA

### 7.1 Pasos para Desarrolladores

1. **Configuración inicial:**
```inform6
// Incluir archivos españoles
#Include "lib/español/generos_es.h"
#Include "lib/español/conjugaciones_es.h"
#Include "lib/español/mensajes_es.h"
```

2. **Definir objetos con género:**
```inform6
Object Libro "libro" habitacion
    with name 'libro' 'tomo' 'volumen',
         gender MASC,
         description "Un libro interesante.",
    has readable;
```

3. **Implementar acciones con concordancia:**
```inform6
[ TakeSub;
    if(ImplicitGrabIfNotHeld(noun)) return;
    
    // Mensaje con concordancia
    if(noun has feminine) {
        if(noun has pluralname) print "Tomadas.";
        else print "Tomada.";
    } else {
        if(noun has pluralname) print "Tomados.";
        else print "Tomado.";
    }
];
```

### 7.2 Ejemplo de Juego Completo

```inform6
!% -v3 -e
Constant Story "Mi Primera Aventura Española";
Constant Headline "Un ejemplo de PunyInform en español";

! Incluir archivos españoles
#Include "lib/español/generos_es.h"
#Include "lib/globals.h"
#Include "lib/español/mensajes_es.h"
#Include "lib/español/gramatica_es.h"
#Include "lib/puny.h"

! Habitación principal
Object Habitacion "habitación"
    with description "Una habitación sencilla. Hay una mesa aquí.",
         n_to Pasillo,
    has light;

! Objeto con género femenino
Object -> Mesa "mesa"
    with name 'mesa' 'mueble',
         gender FEM,
         description "Una mesa de madera.",
    has supporter feminine;

! Objeto con género masculino
Object -> Libro "libro"
    with name 'libro' 'tomo',
         gender MASC,
         description "Un libro interesante.",
    has readable;

[ Initialise;
    location = Habitacion;
    print "¡Bienvenido a tu primera aventura en español!";
];
```

## 8. CONCLUSIONES

### 8.1 Viabilidad del Proyecto

La conversión de PunyInform al español es **técnicamente viable** y **altamente recomendable**. La arquitectura modular de la biblioteca facilita la implementación de los cambios necesarios sin comprometer la eficiencia característica del sistema. [GitHub](https://github.com/johanberntsson/PunyInform