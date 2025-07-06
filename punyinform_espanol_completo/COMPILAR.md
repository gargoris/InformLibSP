# Guía de Compilación - PunyInform Español

## 🚀 Compilación Rápida

### Comando básico:
```bash
inform -v5 +include_path=punyinform_espanol_completo tu_juego.inf
```

### Desde el directorio del proyecto:
```bash
cd punyinform_espanol_completo
inform -v5 +include_path=. ejemplos/basicos/ejemplo_minimo_funcionando.inf
```

## 📁 Rutas de Include

### Sistema Integrado (Recomendado):
```inform6
Include "core/sistema_integrado/puny_spanish_integrado.h";
```

### Sistema Optimizado:
```inform6
Include "core/sistema_optimizado/spanish_final/puny_spanish_master.h";
```

### Sistema Básico:
```inform6
Include "core/sistema_basico/spanish/puny_spanish.h";
```

## ⚙️ Configuración Opcional

### Antes del Include:
```inform6
Constant OPTIONAL_EXTENDED_VERBSET;     ! Verbos adicionales
Constant DEBUG_SPANISH_PARSER;          ! Debug del parser
! Constant DISABLE_SPANISH_MESSAGES;    ! Usar mensajes ingleses

Include "core/sistema_integrado/puny_spanish_integrado.h";
```

## 🔧 Solución de Problemas

### Error: "Can't find file"
- Verifica que el path del `+include_path` sea correcto
- Usa rutas absolutas si es necesario:
  ```bash
  inform -v5 +include_path=/ruta/completa/punyinform_espanol_completo tu_juego.inf
  ```

### Error: "No such constant"
- Asegúrate de que el sistema base de PunyInform esté disponible
- Los archivos `grammar.h`, `globals.h`, etc. deben estar en `core/`

### Advertencias de compilación
- Las advertencias sobre variables no usadas son normales
- Solo los ERRORES impiden la compilación exitosa

## ✅ Verificación Exitosa

Una compilación exitosa muestra:
```
Inform 6.42 for Linux
[warnings about unused variables - NORMAL]
Compiled with X warnings (but no ERRORS)
```

Y genera un archivo `.z5` o `.z8` listo para jugar.

## 🎮 Probar el Juego

### Intérpretes recomendados:
- **Frotz**: `frotz tu_juego.z5`
- **Gargoyle**: `gargoyle tu_juego.z5`  
- **Web**: Subir a ifdb.org o similar

### Comandos de prueba:
```
> mirar
> examinar mesa
> coger libro
> inventario
> ir al norte
```

## 📝 Ejemplos Incluidos

### Listos para compilar:
1. `ejemplos/basicos/ejemplo_minimo_funcionando.inf` ⭐ RECOMENDADO
2. `ejemplos/basicos/demo_espanol.inf`
3. `ejemplos/avanzados/ejemplo_espanol_completo.inf`

### Compilar ejemplo mínimo:
```bash
cd punyinform_espanol_completo
inform -v5 +include_path=. ejemplos/basicos/ejemplo_minimo_funcionando.inf
frotz ejemplo_minimo_funcionando.z5
```

## 🏗️ Para Desarrolladores

### Estructura de includes necesaria:
```
tu_proyecto/
├── tu_juego.inf
└── punyinform_espanol_completo/
    ├── core/
    │   ├── sistema_integrado/
    │   ├── grammar.h
    │   ├── globals.h
    │   └── ...
    └── ...
```

### Include en tu juego:
```inform6
Include "punyinform_espanol_completo/core/sistema_integrado/puny_spanish_integrado.h";
```

¡Listo para crear aventuras en español! 🎉