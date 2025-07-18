# Formato de Archivo DAAD# - Especificación Completa

## 📋 Guía Técnica del Formato de Archivo Fuente

### Versión: 3.0 | Especificación Completa DAAD#

---

## 📖 Índice

1. [Introducción](#introducción)
2. [Estructura General del Archivo](#estructura-general)
3. [Secciones del Archivo](#secciones-del-archivo)
4. [Sintaxis y Codificación](#sintaxis-y-codificación)
5. [Sección Game](#sección-game)
6. [Sección Vocabulary](#sección-vocabulary)
7. [Sección Messages](#sección-messages)
8. [Sección Locations](#sección-locations)
9. [Sección Objects](#sección-objects)
10. [Sección Responses](#sección-responses)
11. [Sección Processes](#sección-processes)
12. [Sección Flags](#sección-flags)
13. [Comentarios y Documentación](#comentarios-y-documentación)
14. [Ejemplo Completo](#ejemplo-completo)
15. [Validación y Errores](#validación-y-errores)

---

## 🚀 Introducción

Un archivo fuente DAAD# (extensión `.daad`) contiene toda la definición de una aventura conversacional. Este documento describe la sintaxis completa y la estructura del formato de archivo.

### Características del Formato

- **Basado en texto**: Archivo de texto plano UTF-8
- **Declarativo**: Define estado y comportamiento de la aventura
- **Estructurado**: Organizado en secciones claramente definidas
- **Extensible**: Soporte para comentarios y documentación
- **Compatible**: 100% compatible con DAAD clásico + extensiones modernas

---

## 🏗️ Estructura General del Archivo

### Formato Básico

```daad
// Comentarios opcionales al inicio del archivo
// Información del autor, versión, etc.

game {
    // Configuración general del juego
}

vocabulary {
    // Definición de palabras y sinónimos
}

messages {
    // Tabla de mensajes del sistema
}

locations {
    // Definición de ubicaciones/habitaciones
}

objects {
    // Definición de objetos del juego
}

responses {
    // Tabla de respuestas a comandos
}

processes {
    // Procesos y subrutinas adicionales
}

flags {
    // Definición inicial de variables
}
```

### Reglas Generales

1. **Orden**: Las secciones pueden aparecer en cualquier orden
2. **Obligatorias**: Solo `responses` es obligatoria
3. **Múltiples**: Se pueden repetir secciones (se concatenan)
4. **Espacios**: Los espacios en blanco son ignorados
5. **Codificación**: UTF-8 obligatorio para caracteres especiales

---

## 📝 Sintaxis y Codificación

### Caracteres Permitidos

```daad
// Identificadores: letras, números, guión bajo
mi_objeto_1
PuertaPrincipal
flag_energia

// Números: enteros positivos y negativos
42, -5, 0, 255

// Strings: entre comillas dobles
"Texto con espacios y acentos: café, niño"

// Comentarios: desde // hasta final de línea
// Este es un comentario de línea
```

### Delimitadores y Estructura

```daad
// Llaves para secciones y bloques
section_name {
    content
}

// Dos puntos para definiciones
item_name: {
    definition
}

// Punto y coma para separar CondActs
condact1; condact2; condact3

// Comas para listas
item1, item2, item3
```

### Palabras Reservadas

```daad
// Nombres de secciones
game, vocabulary, messages, locations, objects, responses, processes, flags

// CondActs (141 total)
at, present, carried, get, drop, goto, message, done, end, etc.

// Especificadores especiales
here, carried, worn, all, noun1, noun2, current, value

// Referencias
flag[], object[]
```

---

## 🎮 Sección Game

Define la configuración general del juego.

### Sintaxis

```daad
game {
    title: "Nombre del Juego"
    author: "Nombre del Autor"
    version: "1.0"
    
    // Configuración técnica
    max_objects: 255
    max_locations: 255
    max_flags: 256
    max_messages: 512
    
    // Ubicación inicial
    start_location: entrada
    
    // Configuración de juego
    darkness_word: "oscuridad"
    light_object: antorcha
    
    // Límites del jugador
    max_carried: 10
    max_worn: 5
    
    // Configuración de guardado
    save_slots: 10
    auto_save: true
    
    // Mensajes del sistema por defecto
    default_messages: {
        no_understand: "No entiendo."
        cant_do: "No puedes hacer eso."
        not_here: "No está aquí."
        already_have: "Ya lo tienes."
        not_have: "No lo tienes."
        cant_wear: "No puedes ponerte eso."
        cant_remove: "No puedes quitarte eso."
        cant_go: "No puedes ir en esa dirección."
        too_heavy: "Pesas demasiado."
        too_many: "Llevas demasiadas cosas."
        game_over: "Fin del juego."
        game_won: "¡Has ganado!"
    }
}
```

### Campos Opcionales

```daad
game {
    // Mínimo requerido
    title: "Mi Aventura"
    
    // Todo lo demás es opcional con valores por defecto
}
```

---

## 📚 Sección Vocabulary

Define todas las palabras que el parser puede reconocer.

### Sintaxis

```daad
vocabulary {
    // Verbos (tipos 1-20)
    verbs {
        1: coger, tomar, agarrar, llevarse
        2: soltar, dejar, tirar
        3: examinar, mirar, ver, observar
        4: ir, caminar, moverse
        5: inventario, inv, i
        // ... más verbos
    }
    
    // Sustantivos (tipos 21-100)
    nouns {
        21: llave, llavecita
        22: puerta, portón
        23: caja, cajón, cofre
        24: libro, tomo, manual
        // ... más sustantivos
    }
    
    // Adjetivos (tipos 101-150)
    adjectives {
        101: rojo, roja, rojas, rojos
        102: grande, grandes
        103: pequeño, pequeña, pequeños, pequeñas
        104: viejo, vieja, viejos, viejas
        // ... más adjetivos
    }
    
    // Preposiciones (tipos 151-170)
    prepositions {
        151: en, dentro, adentro
        152: sobre, encima
        153: bajo, debajo
        154: con, mediante
        // ... más preposiciones
    }
    
    // Adverbios (tipos 171-200)
    adverbs {
        171: rápidamente, rápido, velozmente
        172: lentamente, despacio
        173: cuidadosamente, con_cuidado
        174: silenciosamente, en_silencio
        // ... más adverbios
    }
    
    // Direcciones especiales (tipos 201-220)
    directions {
        201: norte, n
        202: sur, s
        203: este, e
        204: oeste, o
        205: noreste, ne
        206: noroeste, no
        207: sureste, se
        208: suroeste, so
        209: arriba, subir
        210: abajo, bajar
    }
}
```

### Reglas de Vocabulario

```daad
vocabulary {
    // Sinónimos: separados por comas
    verbs {
        1: coger, tomar, agarrar, llevarse, pillar
    }
    
    // Diferentes géneros y números
    adjectives {
        101: rojo, roja, rojos, rojas
    }
    
    // Palabras compuestas: con guión bajo
    nouns {
        25: llave_maestra, llave_dorada
    }
    
    // Abreviaciones comunes
    verbs {
        5: inventario, inv, i
    }
}
```

---

## 💬 Sección Messages

Define todos los mensajes de texto del juego.

### Sintaxis

```daad
messages {
    // Mensajes numerados
    1: "Bienvenido a la aventura."
    2: "Ves una habitación espaciosa con muebles antiguos."
    3: "La puerta está cerrada con llave."
    4: "¡Encuentras un tesoro brillante!"
    5: "No hay nada especial aquí."
    
    // Mensajes del sistema (números altos)
    100: "No entiendo esa palabra."
    101: "No puedes hacer eso."
    102: "No está aquí."
    103: "Ya lo tienes."
    104: "No lo tienes."
    105: "No puedes ponerte eso."
    
    // Mensajes largos con saltos de línea
    200: "Esta es una descripción muy larga que se extiende por múltiples líneas.\n\nPuede incluir párrafos separados y formateo especial como **negrita** o *cursiva*."
    
    // Mensajes con variables
    250: "Tienes %d puntos de experiencia."
    251: "Tu energía actual es %d de %d."
    252: "Has encontrado %s."
    
    // Mensajes condicionales
    300: {
        condition: "gt flag[nivel] 5"
        text: "Eres un aventurero experimentado."
        else: "Aún eres un novato."
    }
}
```

### Formateo de Mensajes

```daad
messages {
    // Escape de caracteres especiales
    1: "Dice: \"¡Hola mundo!\""
    2: "El camino se divide en dos.\nPuedes ir al norte o al este."
    3: "Temperatura: 25°C"
    
    // Variables embebidas
    10: "Puntuación: {flag[puntos]}"
    11: "Objeto encontrado: {object[current]}"
    12: "Ubicación actual: {location[current]}"
    
    // Formateo condicional
    20: {
        if: "gt flag[energia] 50"
        then: "Te sientes fuerte y lleno de energía."
        elsif: "gt flag[energia] 20"
        then: "Estás algo cansado pero puedes continuar."
        else: "Estás exhausto y necesitas descansar."
    }
}
```

---

## 🏠 Sección Locations

Define todas las ubicaciones/habitaciones del juego.

### Sintaxis

```daad
locations {
    // Definición básica
    entrada: {
        description: 1    // Mensaje #1
        short: "Entrada del castillo"
        
        // Conexiones direccionales
        north: gran_salon
        east: jardín
        west: torre_oeste
        
        // Conexiones especiales
        up: escaleras
        down: sótano
        
        // Propiedades
        dark: false
        visited: false
        
        // Objetos iniciales en esta ubicación
        objects: [llave_bronce, cartel_bienvenida]
        
        // Atributos especiales
        attributes: [interior, seguro]
        
        // Script al entrar
        on_enter: {
            first_time: {
                message 10
                set flag[primera_visita]
            }
            always: {
                process comprobar_entrada
            }
        }
        
        // Script al salir
        on_exit: {
            message 11
            clear flag[en_entrada]
        }
    }
    
    // Ubicación con múltiples descripciones
    biblioteca: {
        description: {
            default: 50
            dark: 51
            after_puzzle: 52
        }
        short: "Biblioteca antigua"
        
        // Conexiones condicionales
        connections: {
            south: entrada
            north: {
                condition: "carried llave_biblioteca"
                destination: sala_secreta
                failure_message: "La puerta está cerrada."
            }
        }
        
        // Límites especiales
        max_objects: 20
        light_level: 3
    }
    
    // Ubicación especial (exterior)
    jardín: {
        description: 60
        short: "Jardín del castillo"
        
        // Propiedades especiales
        outdoor: true
        weather_dependent: true
        
        // Diferentes conexiones según condiciones
        connections: {
            west: entrada
            east: {
                condition: "notat guardia"
                destination: huerto
                else: entrada
                failure_message: "El guardia te impide pasar."
            }
        }
    }
}
```

### Propiedades de Ubicaciones

```daad
locations {
    ubicacion_ejemplo: {
        // Obligatorio
        description: 1
        
        // Opcional con valores por defecto
        short: "Descripción corta"
        dark: false
        visited: false
        outdoor: false
        
        // Conexiones estándar
        north: destino_norte
        south: destino_sur
        east: destino_este
        west: destino_oeste
        northeast: destino_noreste
        northwest: destino_noroeste
        southeast: destino_sureste
        southwest: destino_suroeste
        up: destino_arriba
        down: destino_abajo
        
        // Conexiones personalizadas
        enter: destino_entrar
        exit: destino_salir
        
        // Objetos y configuración
        objects: [objeto1, objeto2]
        max_objects: 50
        light_level: 5
        
        // Eventos
        on_enter: { /* script */ }
        on_exit: { /* script */ }
        on_look: { /* script */ }
        
        // Atributos personalizados
        attributes: [attr1, attr2]
    }
}
```

---

## 📦 Sección Objects

Define todos los objetos del juego.

### Sintaxis

```daad
objects {
    // Objeto básico
    llave_dorada: {
        description: 100
        short: "llave dorada"
        
        // Ubicación inicial
        location: entrada
        
        // Propiedades básicas
        portable: true
        wearable: false
        container: false
        
        // Peso y tamaño
        weight: 1
        size: 1
        
        // Atributos (flags booleanos)
        attributes: [valioso, mágico]
        
        // Sinónimos adicionales
        aliases: [llave, llavecita]
    }
    
    // Objeto contenedor
    caja_tesoros: {
        description: 200
        short: "caja de tesoros"
        location: biblioteca
        
        // Propiedades de contenedor
        container: true
        max_contents: 10
        max_weight: 50
        
        // Estado inicial
        open: false
        locked: true
        
        // Contenido inicial
        contents: [monedas_oro, gema_azul]
        
        // Scripts
        on_open: {
            message 250
            set flag[caja_abierta]
        }
        
        on_close: {
            message 251
        }
        
        on_examine: {
            desc caja_tesoros
            eq flag[caja_abierta] 1; message "Está abierta."
            message "Está cerrada con llave."
        }
    }
    
    // Objeto wearable
    armadura_cuero: {
        description: 300
        short: "armadura de cuero"
        location: tienda_armas
        
        portable: true
        wearable: true
        
        // Propiedades especiales
        armor_value: 5
        durability: 100
        
        // Restricciones
        requires_strength: 10
        
        // Efectos al ponerse
        on_wear: {
            plus flag[defensa] 5
            message "Te sientes más protegido."
        }
        
        on_remove: {
            minus flag[defensa] 5
            message "Te sientes más vulnerable."
        }
    }
    
    // Objeto especial (luz)
    antorcha: {
        description: 400
        short: "antorcha encendida"
        location: entrada
        
        portable: true
        light_source: true
        light_duration: 100  // turnos
        
        // Estado
        lit: true
        fuel: 100
        
        // Comportamiento especial
        on_turn: {
            // Se ejecuta cada turno
            gt flag[fuel] 0; minus flag[fuel] 1
            eq flag[fuel] 0; clear flag[lit]; message "La antorcha se apaga."
        }
    }
    
    // Objeto inmóvil (parte del escenario)
    estatua_mármol: {
        description: 500
        short: "estatua de mármol"
        location: gran_salon
        
        portable: false
        fixed: true
        
        // Interacciones especiales
        on_examine: {
            message 501
            chance 10; message "Notas algo extraño en la base."
        }
        
        on_push: {
            hasnat estatua_mármol 1; set estatua_mármol; message "La estatua se mueve revelando un pasaje secreto."
            message "La estatua no se mueve más."
        }
    }
}
```

### Propiedades de Objetos

```daad
objects {
    objeto_completo: {
        // Identificación (obligatorio)
        description: 1
        short: "nombre corto"
        
        // Ubicación inicial
        location: habitacion_inicial    // ubicación específica
        location: carried              // inventario inicial
        location: worn                 // equipado inicial
        location: nowhere              // no existe inicialmente
        
        // Propiedades físicas
        portable: true/false           // ¿se puede coger?
        wearable: true/false          // ¿se puede llevar puesto?
        container: true/false         // ¿es contenedor?
        fixed: true/false             // ¿está fijo al escenario?
        
        // Contenedor (si container: true)
        max_contents: 10              // máximo objetos dentro
        max_weight: 50               // máximo peso total
        open: true/false             // ¿está abierto?
        locked: true/false           // ¿está cerrado con llave?
        transparent: true/false      // ¿se ve el contenido cerrado?
        
        // Física
        weight: 5                    // peso en unidades
        size: 3                      // tamaño en unidades
        bulk: 2                      // volumen ocupado
        
        // Luz
        light_source: true/false     // ¿da luz?
        light_duration: 100          // duración de la luz
        light_radius: 3              // alcance de la luz
        
        // Estados y atributos
        attributes: [attr1, attr2]   // atributos booleanos
        properties: {                // propiedades numéricas
            durability: 100
            value: 250
            magic_power: 15
        }
        
        // Contenido inicial (si es contenedor)
        contents: [obj1, obj2, obj3]
        
        // Sinónimos adicionales
        aliases: [alias1, alias2]
        
        // Scripts de eventos
        on_examine: { /* condacts */ }
        on_take: { /* condacts */ }
        on_drop: { /* condacts */ }
        on_wear: { /* condacts */ }
        on_remove: { /* condacts */ }
        on_open: { /* condacts */ }
        on_close: { /* condacts */ }
        on_turn: { /* condacts */ }    // cada turno
        on_destroy: { /* condacts */ }
        
        // Restricciones
        requires_strength: 10        // fuerza mínima para usar
        requires_skill: 5           // habilidad mínima
        requires_level: 3           // nivel mínimo
    }
}
```

---

## 🎯 Sección Responses

Define las respuestas a los comandos del jugador. Es la sección más importante.

### Sintaxis Básica

```daad
responses {
    // Patrón: secuencia de CondActs
    examinar llave: {
        present llave; desc llave; done
        message "No hay ninguna llave aquí."
    }
    
    // Patrón con comodín
    coger _: {
        present noun1; autog; done
        message "No puedes coger eso."
    }
    
    // Patrón complejo con múltiples palabras
    meter _ en _: {
        carried noun1; present noun2
        putin noun1 noun2; message "Hecho."
        done
        
        carried noun1; message "¿Meter dónde?"
        message "No tienes eso."
    }
}
```

### Patrones de Comandos Avanzados

```daad
responses {
    // Solo verbo
    inventario: {
        doall carried; print object[current]; newline
    }
    
    // Verbo + sustantivo
    examinar libro: {
        present libro; desc libro; done
        message "No hay ningún libro aquí."
    }
    
    // Verbo + comodín (cualquier sustantivo)
    examinar _: {
        present noun1; desc noun1; done
        message "No hay tal cosa aquí."
    }
    
    // Verbo + sustantivo + adjetivo
    examinar _ rojo: {
        present noun1; adject1 rojo; desc noun1; done
        present noun1; message "No es rojo."
        message "No está aquí."
    }
    
    // Verbo + sustantivo + preposición + sustantivo
    meter _ en _: {
        carried noun1; present noun2; noun2 caja
        putin noun1 noun2; message "Metido en la caja."; done
        
        carried noun1; present noun2
        message "No puedes meter eso ahí."; done
        
        carried noun1; message "¿Meter dónde?"; done
        message "No tienes eso."
    }
    
    // Con adverbios
    caminar rápidamente: {
        adverb rápidamente; minus flag[energia] 3
        goto salida; message "Caminas rápido hacia la salida."
    }
    
    // Múltiples comodines
    dar _ a _: {
        carried noun1; present noun2
        // lógica para dar objetos
    }
    
    // Patrones con múltiples adjetivos
    examinar _ rojo pequeño: {
        present noun1; adject1 rojo; adject2 pequeño
        desc noun1; done
        
        present noun1; message "No cumple esa descripción."
        message "No está aquí."
    }
}
```

### Condicionales y Flujo de Control

```daad
responses {
    abrir puerta: {
        // Verificaciones en secuencia
        present puerta; carried llave_dorada; hasnat puerta 1
        
        // Si llegamos aquí, todo es correcto
        clear puerta; message "Abres la puerta con la llave dorada."
        set flag[puerta_abierta]; done
        
        // Manejo de errores específicos
        present puerta; carried llave_dorada
        message "La puerta ya está abierta."; done
        
        present puerta
        message "Necesitas la llave dorada."; done
        
        message "No hay ninguna puerta aquí."
    }
    
    // Control de flujo con skip
    usar poción: {
        carried poción_vida; gt flag[energia] 80
        message "No necesitas la poción ahora."; done
        
        carried poción_vida; destroy poción_vida
        let flag[energia] 100; message "Te sientes completamente renovado."
        done
        
        message "No tienes poción de vida."
    }
    
    // Sistema de estados
    activar mecanismo: {
        present mecanismo
        
        // Estado 0: inactivo
        eq flag[estado_mecanismo] 0
        let flag[estado_mecanismo] 1
        message "El mecanismo comienza a funcionar."; done
        
        // Estado 1: funcionando
        eq flag[estado_mecanismo] 1
        let flag[estado_mecanismo] 2
        message "El mecanismo acelera su funcionamiento."; done
        
        // Estado 2: sobrecargado
        eq flag[estado_mecanismo] 2
        let flag[estado_mecanismo] 0
        message "El mecanismo se detiene por sobrecarga."; done
        
        message "No hay ningún mecanismo aquí."
    }
}
```

### Respuestas con Procesos

```daad
responses {
    // Llamar a proceso externo
    resolver puzzle: {
        present puzzle
        process tabla_puzzle
        isdone; message "¡Puzzle resuelto!"; plus flag[puzzles_resueltos] 1
        message "No puedes resolver el puzzle aún."
        done
        
        message "No hay ningún puzzle aquí."
    }
    
    // Bucles con doall
    listar todo: {
        message "=== OBJETOS AQUÍ ==="
        doall here; print "- "; print object[current]; newline
        
        message "=== INVENTARIO ==="
        doall carried; print "* "; print object[current]; newline
        
        message "=== EQUIPADO ==="
        doall worn; print "+ "; print object[current]; newline
    }
    
    // Sistema de combate
    atacar _: {
        present noun1; carried espada
        
        // Calcular daño aleatorio
        random 20; plus flag[value] 10  // 10-29 de daño
        
        // Aplicar daño
        copyof noun1 flag[enemy_hp]
        minus flag[enemy_hp] flag[value]
        copyfo flag[enemy_hp] noun1
        
        // Verificar si murió
        lt flag[enemy_hp] 1; destroy noun1
        message "¡Derrotas al enemigo!"; plus flag[experiencia] 50; done
        
        print "Haces "; print flag[value]; print " puntos de daño."
        newline; done
        
        present noun1; message "Necesitas un arma."
        message "No hay enemigos aquí."
    }
}
```

---

## ⚙️ Sección Processes

Define procesos y subrutinas adicionales que pueden ser llamados desde responses.

### Sintaxis

```daad
processes {
    // Proceso simple
    tabla_puzzle: {
        // Verificar si tiene las piezas correctas
        carried pieza_1; carried pieza_2; carried pieza_3
        
        // Resolver puzzle
        destroy pieza_1; destroy pieza_2; destroy pieza_3
        create llave_secreta
        message "Las piezas se combinan formando una llave secreta."
        done  // Marca como exitoso
        
        // Si llegamos aquí, falta alguna pieza
        message "Te faltan piezas para completar el puzzle."
        notdone  // Marca como fallido
    }
    
    // Proceso de combate avanzado
    combate_dragón: {
        // Verificar equipo
        worn armadura; carried espada_mágica
        
        // Primera fase
        message "Te enfrentas al dragón con tu equipo completo."
        chance 70; skip 3  // 70% de éxito
        message "El dragón te hiere gravemente."
        minus flag[energia] 50; notdone
        
        // Segunda fase - ataque especial
        message "Logras herir al dragón."
        chance 50; skip 3  // 50% de éxito en ataque especial
        message "Tu ataque especial falla."
        minus flag[energia] 20; notdone
        
        // Victoria
        message "¡Derrotas al dragón con un golpe épico!"
        plus flag[experiencia] 200
        create tesoro_dragón
        done
        
        // Fallo por equipo insuficiente
        message "No estás preparado para enfrentar al dragón."
        notdone
    }
    
    // Proceso de verificación de inventario
    verificar_ingredientes: {
        // Lista de ingredientes requeridos
        carried hierba_roja; carried agua_pura; carried cristal_poder
        
        // Todos presentes - crear poción
        destroy hierba_roja; destroy agua_pura; destroy cristal_poder
        create poción_suprema
        message "Mezclas los ingredientes creando una poción suprema."
        done
        
        // Verificar ingredientes específicos faltantes
        notcarr hierba_roja; message "Te falta hierba roja."
        notcarr agua_pura; message "Te falta agua pura."
        notcarr cristal_poder; message "Te falta un cristal de poder."
        notdone
    }
    
    // Proceso con múltiples salidas
    explorar_cofre: {
        present cofre_misterioso
        
        // Verificar si está abierto
        hasnat cofre_misterioso 1; message "El cofre está cerrado."; notdone
        
        // Cofre abierto - contenido aleatorio
        random 100
        
        // 30% tesoro valioso
        lt flag[value] 30; create gema_diamante
        message "¡Encuentras una gema de diamante!"; done
        
        // 50% tesoro normal
        lt flag[value] 80; create monedas_oro
        message "Encuentras una bolsa de monedas de oro."; done
        
        // 20% trampa
        message "¡El cofre tenía una trampa!"
        minus flag[energia] 30; notdone
        
        message "No hay ningún cofre aquí."
        notdone
    }
    
    // Proceso de guardado automático
    auto_guardar: {
        // Guardar en slot rotativo
        plus flag[slot_guardado] 1
        gt flag[slot_guardado] 5; let flag[slot_guardado] 1
        
        // Ejecutar guardado
        save flag[slot_guardado]
        print "Juego guardado automáticamente en slot "
        print flag[slot_guardado]; newline
        done
    }
}
```

### Tipos de Procesos

```daad
processes {
    // Proceso de verificación (retorna éxito/fallo)
    verificar_condiciones: {
        condición1; condición2; condición3
        done  // Éxito si todas las condiciones se cumplen
        notdone  // Fallo si alguna condición falla
    }
    
    // Proceso de acción (siempre ejecuta algo)
    ejecutar_efecto: {
        acción1; acción2; acción3
        // No necesita done/notdone explícito
    }
    
    // Proceso híbrido (verifica y actúa)
    resolver_acertijo: {
        // Verificar respuesta
        eq flag[respuesta_jugador] 42
        
        // Ejecutar recompensa
        plus flag[puntuación] 100
        create premio_especial
        message "¡Respuesta correcta!"
        done
        
        // Penalización por respuesta incorrecta
        minus flag[intentos] 1
        message "Respuesta incorrecta."
        notdone
    }
    
    // Proceso con parámetros implícitos
    procesar_objeto_actual: {
        // Usa noun1 como parámetro implícito
        present noun1; carried herramienta_especial
        
        // Diferentes acciones según el objeto
        same noun1 piedra_bruta; create gema_pulida; destroy noun1
        message "Pulidora terminada."; done
        
        same noun1 madera_tosca; create tabla_lisa; destroy noun1
        message "Lijado terminado."; done
        
        message "No puedes procesar ese objeto."
        notdone
    }
}
```

---

## 🏁 Sección Flags

Define el estado inicial de las variables del juego.

### Sintaxis

```daad
flags {
    // Flags simples (valor inicial)
    energia: 100
    puntuación: 0
    nivel: 1
    dinero: 50
    
    // Flags de estado booleano
    primera_vez: 1
    puerta_abierta: 0
    dragón_vivo: 1
    
    // Arrays de flags
    atributos: [10, 15, 12, 8, 14, 11]  // Fuerza, Destreza, etc.
    inventario_slots: [0, 0, 0, 0, 0]   // Slots de inventario especial
    
    // Configuración de juego
    dificultad: 2       // 1=Fácil, 2=Normal, 3=Difícil
    modo_debug: 0
    auto_save: 1
    
    // Contadores y estadísticas
    turnos_jugados: 0
    enemigos_derrotados: 0
    tesoros_encontrados: 0
    puzzles_resueltos: 0
    
    // Estados de objetos especiales
    antorcha_combustible: 100
    poción_vida_cantidad: 3
    llaves_encontradas: 0
    
    // Posiciones y referencias
    última_ubicación: 1
    objeto_en_mano: 0
    npc_hablando: 0
    
    // Configuración avanzada
    configuración: {
        volumen_música: 75
        volumen_efectos: 85
        velocidad_texto: 50
        mostrar_puntuación: 1
        confirmar_acciones: 0
    }
    
    // Tablas de datos
    tabla_experiencia: [0, 100, 250, 500, 1000, 2000, 4000, 8000]
    modificadores_combate: [0, 2, 5, 8, 12, 17, 23, 30]
    
    // Flags temporales (se resetean)
    temp: {
        cálculo_temporal: 0
        resultado_dado: 0
        valor_aleatorio: 0
        índice_bucle: 0
    }
}
```

### Tipos de Flags

```daad
flags {
    // Enteros simples
    flag_simple: 42
    
    // Booleanos (0 o 1)
    flag_booleano: 1
    
    // Negativos permitidos
    flag_negativo: -10
    
    // Arrays indexados
    atributos: {
        0: 15    // Fuerza
        1: 12    // Destreza  
        2: 14    // Inteligencia
        3: 10    // Resistencia
        4: 8     // Carisma
        5: 13    // Sabiduría
    }
    
    // Rangos especiales
    flags_sistema: {
        // Flags reservados del sistema
        value: 0         // Flag especial para valores temporales
        current: 0       // Flag especial para bucles
        random_seed: 42  // Semilla aleatoria
    }
    
    // Límites y rangos
    límites: {
        min_energia: 0
        max_energia: 100
        min_puntuación: 0
        max_objetos_inventario: 20
    }
}
```

---

## 💬 Comentarios y Documentación

### Tipos de Comentarios

```daad
// Comentario de línea simple
// Este comentario explica la siguiente línea

/* Comentario de bloque
   que puede ocupar múltiples líneas
   y es útil para documentación extensa */

/**
 * Comentario de documentación estilo JSDoc
 * @author Nombre del Autor
 * @version 1.0
 * @description Descripción del módulo
 */

responses {
    // Comando básico de movimiento
    ir norte: {
        at entrada; goto salon; message "Vas hacia el norte."  // Comentario inline
        message "No puedes ir al norte desde aquí."
    }
    
    /* Sistema de combate avanzado
       Implementa un sistema de combate por turnos
       con cálculo de daño basado en estadísticas */
    atacar _: {
        // Verificaciones previas
        present noun1; carried arma
        
        // TODO: Implementar sistema de críticos
        // FIXME: Balance de daño muy alto
        // NOTE: Considerar añadir resistencias elementales
        
        random 20; plus flag[value] 10
        message "Atacas al enemigo."
    }
}
```

### Documentación de Secciones

```daad
/**
 * AVENTURA: El Castillo Perdido
 * AUTOR: Juan Pérez
 * VERSIÓN: 2.1
 * FECHA: 2025-01-15
 * 
 * DESCRIPCIÓN:
 * Una aventura clásica de exploración y puzzles en un castillo misterioso.
 * El jugador debe encontrar tres llaves para acceder a la cámara del tesoro.
 * 
 * CARACTERÍSTICAS:
 * - Sistema de combate simple
 * - 15 ubicaciones interconectadas  
 * - 25 objetos únicos
 * - 5 puzzles principales
 * - Sistema de puntuación
 * 
 * NOTAS TÉCNICAS:
 * - Usa flags 0-50 para estado del juego
 * - Flags 51-99 para contadores y estadísticas
 * - Mensajes 1-199 para descripciones
 * - Mensajes 200-299 para diálogos
 * - Mensajes 300+ para sistema
 */

// ============================================
// CONFIGURACIÓN GENERAL DEL JUEGO
// ============================================
game {
    title: "El Castillo Perdido"
    author: "Juan Pérez"
    version: "2.1"
    max_objects: 50
    max_locations: 20
}

// ============================================
// VOCABULARIO PRINCIPAL
// ============================================
vocabulary {
    // Verbos de acción (1-20)
    verbs {
        1: coger, tomar, agarrar     // Coger objetos
        2: soltar, dejar, tirar      // Soltar objetos
        // ... más verbos documentados
    }
}

// ============================================
// MENSAJES DEL SISTEMA
// ============================================
messages {
    // Mensajes de bienvenida (1-10)
    1: "Bienvenido al Castillo Perdido"
    
    // Descripciones de ubicaciones (11-50)
    11: "Estás en la entrada del castillo..."
    
    // Descripciones de objetos (51-100)
    51: "Una llave dorada brilla en el suelo"
}
```

---

## 📋 Ejemplo Completo

### Archivo `castillo.daad` Completo

```daad
/**
 * EL CASTILLO PERDIDO
 * Una aventura de ejemplo completa
 * Demuestra todas las características de DAAD#
 */

// ============================================
// CONFIGURACIÓN GENERAL
// ============================================
game {
    title: "El Castillo Perdido"
    author: "Tutorial DAAD#"
    version: "1.0"
    start_location: entrada
    max_carried: 10
}

// ============================================
// VOCABULARIO
// ============================================
vocabulary {
    verbs {
        1: coger, tomar, agarrar
        2: soltar, dejar, tirar
        3: examinar, mirar, ver
        4: ir, caminar, moverse
        5: inventario, inv, i
        6: abrir
        7: cerrar
        8: usar, utilizar
    }
    
    nouns {
        21: llave, llavecita
        22: puerta, portón
        23: caja, cofre
        24: libro, tomo
        25: espada, sable
        26: escudo, broquel
    }
    
    adjectives {
        101: dorada, dorado, oro
        102: plateada, plateado, plata
        103: grande, grandes
        104: pequeña, pequeño, pequeños
    }
    
    prepositions {
        151: en, dentro
        152: con, mediante
    }
    
    directions {
        201: norte, n
        202: sur, s
        203: este, e
        204: oeste, o
    }
}

// ============================================
// MENSAJES
// ============================================
messages {
    // Bienvenida
    1: "¡Bienvenido al Castillo Perdido!"
    2: "Tu misión es encontrar el tesoro del castillo."
    
    // Ubicaciones
    10: "Estás en la entrada del castillo. Hay puertas al norte y al este."
    11: "Un gran salón con una escalera que sube al norte."
    12: "Una biblioteca llena de libros antiguos."
    13: "La cámara del tesoro. ¡Has ganado!"
    
    // Objetos
    20: "Una llave dorada brilla en el suelo."
    21: "Una espada afilada descansa contra la pared."
    22: "Un cofre cerrado con llave."
    23: "¡Un tesoro brillante de valor incalculable!"
    
    // Sistema
    100: "No entiendo esa palabra."
    101: "No puedes hacer eso."
    102: "No está aquí."
    103: "Ya lo tienes."
    104: "No lo tienes."
    
    // Victoria
    200: "¡FELICIDADES! Has encontrado el tesoro del castillo."
    201: "Tu aventura ha terminado exitosamente."
}

// ============================================
// UBICACIONES
// ============================================
locations {
    entrada: {
        description: 10
        short: "Entrada del castillo"
        north: gran_salon
        east: biblioteca
        objects: [llave_dorada]
    }
    
    gran_salon: {
        description: 11
        short: "Gran salón"
        south: entrada
        north: {
            condition: "carried llave_dorada"
            destination: camara_tesoro
            failure_message: "La puerta está cerrada con llave."
        }
        objects: [espada_hierro]
    }
    
    biblioteca: {
        description: 12
        short: "Biblioteca antigua"
        west: entrada
        objects: [libro_historia, cofre_pequeño]
    }
    
    camara_tesoro: {
        description: 13
        short: "Cámara del tesoro"
        south: gran_salon
        objects: [tesoro_real]
        
        on_enter: {
            message 200
            message 201
            plus flag[puntuacion] 1000
            end
        }
    }
}

// ============================================
// OBJETOS
// ============================================
objects {
    llave_dorada: {
        description: 20
        short: "llave dorada"
        location: entrada
        portable: true
        aliases: [llave]
    }
    
    espada_hierro: {
        description: 21
        short: "espada de hierro"
        location: gran_salon
        portable: true
        wearable: true
        aliases: [espada, sable]
    }
    
    libro_historia: {
        description: 24
        short: "libro de historia"
        location: biblioteca
        portable: true
        
        on_examine: {
            message "El libro cuenta la historia del castillo perdido."
            message "Menciona un tesoro escondido en la torre norte."
        }
    }
    
    cofre_pequeño: {
        description: 22
        short: "cofre pequeño"
        location: biblioteca
        container: true
        portable: false
        locked: true
        
        on_open: {
            hasnat cofre_pequeño 1; message "El cofre está cerrado con llave."
            clear cofre_pequeño
            message "Abres el cofre y encuentras una nota."
            create nota_secreta
        }
    }
    
    nota_secreta: {
        description: "Una nota con escritura misteriosa"
        short: "nota secreta"
        location: nowhere
        portable: true
        
        on_examine: {
            message "'La llave dorada abre el camino al tesoro.'"
        }
    }
    
    tesoro_real: {
        description: 23
        short: "tesoro real"
        location: camara_tesoro
        portable: true
        
        on_take: {
            message 200
            plus flag[puntuacion] 500
            end
        }
    }
}

// ============================================
// RESPUESTAS A COMANDOS
// ============================================
responses {
    // Comandos básicos de movimiento
    ir norte: {
        at entrada; goto gran_salon; done
        at gran_salon; carried llave_dorada; goto camara_tesoro; done
        at gran_salon; message "La puerta norte está cerrada con llave."
        at biblioteca; message "No puedes ir al norte."
        message "No puedes ir en esa dirección."
    }
    
    ir sur: {
        at gran_salon; goto entrada; done
        at camara_tesoro; goto gran_salon; done
        message "No puedes ir en esa dirección."
    }
    
    ir este: {
        at entrada; goto biblioteca; done
        message "No puedes ir en esa dirección."
    }
    
    ir oeste: {
        at biblioteca; goto entrada; done
        message "No puedes ir en esa dirección."
    }
    
    // Comandos de manipulación de objetos
    coger _: {
        present noun1; autog; done
        message 102  // "No está aquí."
    }
    
    soltar _: {
        carried noun1; autod; done
        message 104  // "No lo tienes."
    }
    
    examinar _: {
        present noun1; desc noun1; done
        carried noun1; desc noun1; done
        message 102  // "No está aquí."
    }
    
    // Comando de inventario
    inventario: {
        message "Llevas:"
        doall carried; print "- "; print object[current]; newline
    }
    
    // Comandos específicos
    abrir cofre: {
        present cofre_pequeño; autot cofre_pequeño; done
        message "No hay ningún cofre aquí."
    }
    
    abrir _: {
        present noun1; message "No puedes abrir eso."
        message 102  // "No está aquí."
    }
    
    usar llave: {
        carried llave_dorada; at gran_salon; goto camara_tesoro
        message "Usas la llave para abrir la puerta norte."
        done
        
        carried llave_dorada; message "No hay nada que abrir con la llave aquí."
        message "No tienes la llave."
    }
    
    // Comandos de ayuda
    ayuda: {
        message "Comandos disponibles:"
        message "- ir [dirección]"
        message "- coger [objeto]"
        message "- soltar [objeto]"
        message "- examinar [objeto]"
        message "- inventario"
        message "- abrir [objeto]"
        message "- usar [objeto]"
    }
    
    // Comando de puntuación
    puntuacion: {
        print "Puntuación actual: "
        print flag[puntuacion]
        newline
    }
}

// ============================================
// PROCESOS ADICIONALES
// ============================================
processes {
    proceso_victoria: {
        message 200
        message 201
        plus flag[puntuacion] 1000
        end
    }
    
    verificar_inventario: {
        // Verificar si el jugador tiene objetos clave
        carried llave_dorada; set flag[tiene_llave]
        carried espada_hierro; set flag[tiene_arma]
        done
    }
}

// ============================================
// ESTADO INICIAL DE FLAGS
// ============================================
flags {
    // Puntuación y estadísticas
    puntuacion: 0
    turnos: 0
    
    // Estados del juego
    primera_visita_salon: 1
    primera_visita_biblioteca: 1
    cofre_abierto: 0
    
    // Flags de objetos
    tiene_llave: 0
    tiene_arma: 0
    
    // Configuración
    modo_debug: 0
    mostrar_puntuacion: 1
}
```

---

## ✅ Validación y Errores

### Errores Comunes de Sintaxis

```daad
// ERROR: Sección sin llaves
responses
    comando: { ... }

// CORRECTO: Sección con llaves
responses {
    comando: { ... }
}

// ERROR: CondAct inexistente
responses {
    comando: {
        condact_inventado objeto
    }
}

// ERROR: Referencia de flag incorrecta
responses {
    comando: {
        eq flags[energia] 100  // Debe ser flag[energia]
    }
}

// ERROR: Objeto sin definir
responses {
    coger objeto_inexistente: {
        get objeto_inexistente  // Objeto no definido en objects
    }
}

// ERROR: Ubicación sin definir
responses {
    ir norte: {
        goto ubicacion_inexistente  // Ubicación no definida
    }
}
```

### Validaciones del Compilador

```daad
// ADVERTENCIA: Objeto inalcanzable
objects {
    objeto_perdido: {
        location: nowhere  // No hay forma de obtenerlo
        // Advertencia: objeto inalcanzable
    }
}

// ADVERTENCIA: Ubicación inalcanzable
locations {
    sala_secreta: {
        description: 1
        // No hay conexiones desde otras ubicaciones
        // Advertencia: ubicación inalcanzable
    }
}

// ADVERTENCIA: Mensaje sin usar
messages {
    999: "Este mensaje nunca se usa"
    // Advertencia: mensaje sin referencias
}

// ERROR: Referencia circular
locations {
    sala_a: {
        north: sala_b
    }
    sala_b: {
        north: sala_a
        // OK - no es circular
    }
}

// ERROR: Flag fuera de rango
flags {
    flag_invalido: 65536  // ERROR: máximo es 65535
}
```

### Mejores Prácticas

```daad
// BUENO: Nombres descriptivos
objects {
    llave_torre_norte: {
        description: 100
        short: "llave de la torre norte"
    }
}

// MALO: Nombres genéricos
objects {
    obj1: {
        description: 100
        short: "objeto"
    }
}

// BUENO: Comentarios explicativos
responses {
    // Sistema de combate básico - versión 1.2
    atacar _: {
        present noun1; carried arma  // Verificar objetivo y arma
        random 20; plus flag[value] 10  // Daño 10-29
        // ... resto del código
    }
}

// BUENO: Organización por funcionalidad
responses {
    // ========== COMANDOS DE MOVIMIENTO ==========
    ir norte: { ... }
    ir sur: { ... }
    
    // ========== COMANDOS DE OBJETOS ==========
    coger _: { ... }
    soltar _: { ... }
    
    // ========== COMANDOS ESPECIALES ==========
    usar _: { ... }
    abrir _: { ... }
}

// BUENO: Validación de estado
responses {
    abrir puerta: {
        // Verificar todas las condiciones primero
        present puerta; carried llave; hasnat puerta 1
        
        // Solo ejecutar acción si todo es correcto
        clear puerta; message "Abres la puerta."; done
        
        // Manejo explícito de errores
        present puerta; carried llave; message "Ya está abierta."
        present puerta; message "Necesitas una llave."
        message "No hay puerta aquí."
    }
}
```

---

## 📚 Resumen de Especificaciones

### Límites Técnicos

| Elemento | Límite | Notas |
|----------|--------|-------|
| Ubicaciones | 255 | IDs 0-254 |
| Objetos | 255 | IDs 0-254 |
| Mensajes | 65535 | IDs 0-65534 |
| Flags | 256 | IDs 0-255 |
| Vocabulario | 255 por tipo | Verbos, sustantivos, etc. |
| CondActs por respuesta | Sin límite | Limitado por memoria |
| Longitud de línea | 1024 caracteres | Recomendado < 120 |
| Tamaño de archivo | Sin límite | Limitado por memoria del sistema |

### Extensiones de Archivo

| Extensión | Propósito |
|-----------|-----------|
| `.daad` | Archivo fuente principal |
| `.daad.bak` | Respaldo automático |
| `.daad.tmp` | Archivo temporal de compilación |
| `.daadc` | Archivo compilado |
| `.daadh` | Archivo de inclusión (header) |

### Codificación y Formato

- **Codificación**: UTF-8 obligatorio
- **Saltos de línea**: LF (Unix) o CRLF (Windows)
- **Indentación**: Espacios o tabs (consistente)
- **Tamaño de tab**: 4 espacios recomendado

---

*Especificación de Formato DAAD# v3.0*  
*Documento técnico completo para desarrolladores*
