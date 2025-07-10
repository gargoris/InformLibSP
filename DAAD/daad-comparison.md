# Comparativa: DAAD Original vs DAAD Modernizado

## Características generales

| Aspecto | DAAD Original (1989) | DAAD Modernizado (2024) |
|---------|----------------------|-------------------------|
| **Filosofía** | Sintaxis compacta y numérica | Mantiene compacidad pero con nombres descriptivos |
| **Estructura** | Secciones con prefijos (/CTL, /VOC, etc.) | Bloques declarativos con sintaxis de llaves |
| **Identificadores** | Números "mágicos" | Nombres descriptivos |
| **Validación** | Solo en tiempo de ejecución | Validación temprana en tiempo de compilación |
| **Compatibilidad** | - | Bidireccional (puede importar/exportar a DAAD clásico) |
| **Soporte a español** | Básico | Avanzado (sinónimos, filtrado de artículos, construcciones naturales) |

## Estructura y sintaxis básica

| Elemento | DAAD Original | DAAD Modernizado |
|----------|---------------|------------------|
| **Metadatos** | ```
/CTL
TITLE "Mi Aventura"
START 0
``` | ```
game {
  title: "Mi Aventura"
  author: "Desarrollador Moderno"
  start: bosque
  max_score: 100
}
``` |
| **Vocabulario** | ```
/VOC
mirar 0 1
coger 0 2
espada 1 50
``` | ```
vocab {
  verbs: { look: 1, take: 2, use: 4 }
  nouns: { sword: 50, key: 51 }
  directions: { north: 10, south: 11 }
}
``` |
| **Conexiones** | ```
/CON
0 norte 1
1 sur 0
``` | ```
location forest {
  exits: { north: clearing }
}
location clearing {
  exits: { south: forest }
}
``` |
| **Mensajes** | ```
/MTX
1 "No puedes hacer eso."
2 "¡Bien hecho!"
``` | ```
messages {
  cant_do: "¡No puedes hacer eso!"
  well_done: "¡Bien hecho!"
}
``` |

## Objetos y localidades

| Elemento | DAAD Original | DAAD Modernizado |
|----------|---------------|------------------|
| **Localidades** | Secciones numéricas con descripciones asociadas | ```
location forest {
  desc: "Estás en un bosque oscuro."
  exits: { north: clearing }
  objects: [key]
}
``` |
| **Objetos** | Atributos numéricos con banderas | ```
object sword {
  name: "espada"
  desc: "Una espada brillante"
  location: clearing
  weight: 5
  takeable: true
}
``` |

## Procesos y respuestas

| Elemento | DAAD Original | DAAD Modernizado |
|----------|---------------|------------------|
| **Respuestas** | ```
/PRO
*
1 50
PRESENT 50
MESSAGE 50
DONE
``` | ```
responses {
  on "look sword" {
    require: present(sword)
    do: {
      show_desc(sword)
      done
    }
  }
}
``` |
| **Procesos** | ```
/PRO 1
SET 5
LESS 2 10
MESSAGE 3
DONE
END
``` | ```
processes {
  auto victory_check {
    require: flag("door_opened")
    do: {
      message("well_done")
      end_game
    }
  }
}
``` |

## Características avanzadas

| Característica | DAAD Original | DAAD Modernizado |
|----------------|---------------|------------------|
| **Comentarios** | Limitados o inexistentes | ```
# Comentarios de línea
/* Comentarios
   multilinea */
``` |
| **Validación** | Manual (propenso a errores) | ```
location invalid_room {
  exits: { north: nonexistent_room }  # ERROR en tiempo de compilación
}
``` |
| **Tipos de datos** | Implícitos | ```
object broken_item {
  weight: "heavy"  # ERROR: weight debe ser número
}
``` |
| **Patrones múltiples** | Repetición de código | ```
on ["mirar espada", "examinar espada"] {
  require: present(sword)
  do: { ... }
}
``` |

## Transpilación bidireccional

| Dirección | Ejemplo |
|-----------|---------|
| **Moderno a Clásico** | ```
# Moderno
on "look sword" {
  require: present(sword)
  do: { show_desc(sword); done }
}
``` → ```
# DAAD Original
*
1 50
PRESENT 50
MESSAGE 50
DONE
``` |
| **Clásico a Moderno** | El sistema puede importar código DAAD clásico y convertirlo automáticamente a la sintaxis moderna |

## Ventajas del DAAD Modernizado

1. **Legibilidad**: Código autodocumentado con nombres descriptivos
2. **Mantenibilidad**: Cambios en la estructura no requieren renumerar todo
3. **Validación**: Errores detectados antes de la ejecución
4. **Herramientas**: Mejor soporte para IDEs (autocompletado, refactoring)
5. **Español nativo**: Soporte avanzado para construcciones naturales en español
6. **Colaboración**: Múltiples desarrolladores pueden trabajar sin conflictos
7. **Compatibilidad**: Bidireccional con el formato DAAD clásico
8. **Aprendizaje**: Curva de aprendizaje más suave para nuevos desarrolladores
