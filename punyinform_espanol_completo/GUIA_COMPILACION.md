# Guía de Compilación - PunyInform Español

## 🎯 **Guía Rápida para Compilar**

### ✅ **Método Recomendado: Directorio build_test**

**Estado:** ✅ **PROBADO Y FUNCIONAL**  
**Fecha:** 7 de julio de 2025  
**Resultado:** Archivo `.z5` jugable generado exitosamente  

#### **1. Ubicación del Sistema Funcional:**
```
punyinform_espanol_completo/build_test/
├── ejemplo_master_completo.inf          # ✅ Ejemplo principal
├── ejemplo_master_completo.z5           # ✅ Archivo compilado (68KB)
├── puny_spanish_integrado.h             # ✅ Sistema integrado
└── [archivos de soporte]                # ✅ Todas las dependencias
```

#### **2. Comando de Compilación:**
```bash
# Desde el directorio build_test/
/ruta/al/inform ejemplo_master_completo.inf

# Ejemplo con ruta específica:
/mnt/c/Users/TuUsuario/inform/InformLibSP/inform ejemplo_master_completo.inf
```

#### **3. Resultado Esperado:**
```
✅ Compilación exitosa
✅ Archivo generado: ejemplo_master_completo.z5 (68KB)
✅ 6 warnings menores (no críticos)
✅ Juego completamente funcional en español
```

---

## 🔧 **Especificaciones Técnicas**

### **Archivos Requeridos (Ya incluidos en build_test/):**
- `puny_spanish_integrado.h` - Sistema español integrado
- `grammar_optimizada.h` - Gramática española optimizada
- `parser_spanish_master.h` - Parser español avanzado
- `verbos_infinitivos.h` - Sistema de conjugaciones
- `verbos_irregulares.h` - Verbos irregulares
- `puny_sin_grammar.h` - PunyInform base modificado
- `globals.h`, `messages.h`, `scope.h`, `parser.h` - Archivos base

### **Correcciones Aplicadas:**
1. ✅ **Atributos declarados** - `Attribute male;` añadido
2. ✅ **Sintaxis corregida** - Direcciones sin `->` 
3. ✅ **Rutinas añadidas** - 8 rutinas españolas implementadas
4. ✅ **Caracteres especiales** - Tabla Zcharacter expandida
5. ✅ **Conflictos resueltos** - Rutinas reorganizadas

### **Características del Juego Compilado:**
- **Conjugaciones verbales completas** en español
- **Concordancia automática** de género y número
- **Soporte completo** para caracteres españoles (ñ, á, é, í, ó, ú, ¿, ¡)
- **Rutinas de acción** personalizadas en español
- **Ejemplo jugable** con múltiples objetos y funcionalidades

---

## 🚀 **Crear Tu Propio Juego**

### **Plantilla Básica:**
```inform6
! Tu juego en español
Zcharacter table 
    '@{E1}' '@{E9}' '@{ED}' '@{F3}' '@{FA}'    ! á é í ó ú
    '@{C1}' '@{C9}' '@{CD}' '@{D3}' '@{DA}'    ! Á É Í Ó Ú
    '@{F1}' '@{D1}'                            ! ñ Ñ
    '@{BF}' '@{A1}'                            ! ¿ ¡
;

Constant Story "^Tu Aventura en Español^";
Constant Headline "^Un juego usando PunyInform Español^";

! Incluir el sistema español
Include "puny_spanish_integrado.h";

! Tu ubicación inicial
Object SalaInicial "sala principal"
    with description "Una sala donde comienza la aventura.",
    has light;

! Función de inicialización
[ Initialise;
    InicializarEspanol();
    print "^^¡Bienvenido a tu aventura en español!^^";
    location = SalaInicial;
    lookmode = 2;
];
```

### **Compilar Tu Juego:**
```bash
# Desde el directorio build_test/
/ruta/al/inform tu_juego.inf
```

---

## 🐛 **Solución de Problemas**

### **Problema: "Couldn't open source file"**
**Solución:** Usar el directorio `build_test/` que tiene todas las dependencias

### **Problema: "Expected name of attribute but found male"**
**Solución:** Ya corregido en `puny_spanish_integrado.h`

### **Problema: "Character can only be used if declared in advance"**
**Solución:** Usar la tabla Zcharacter expandida del ejemplo

### **Problema: Rutinas duplicadas (DrinkSub, SmellSub, etc.)**
**Solución:** Ya corregido - rutinas reorganizadas y renombradas

---

## 📊 **Verificación de Éxito**

### **Indicadores de Compilación Exitosa:**
```
✅ Archivo .z5 generado
✅ Tamaño aproximado: 60-70KB
✅ Máximo 6 warnings (no críticos)
✅ Sin errores fatales
✅ Texto "Compiled successfully" al final
```

### **Prueba Rápida del Juego:**
```
> mirar
Sala principal
Una sala donde comienza la aventura.

> inventario
No llevas nada en este momento.

> examinar mesa
(Si hay una mesa en tu juego)
```

---

## 🎮 **Ejecutar el Juego**

### **Interpretes Recomendados:**
- **Frotz** (Linux/Mac/Windows)
- **Gargoyle** (Multiplataforma)
- **Lectrote** (Electron-based)
- **WinFrotz** (Windows)

### **Comando de Ejecución:**
```bash
# Ejemplo con Frotz
frotz ejemplo_master_completo.z5

# O simplemente hacer doble clic en el archivo .z5
```

---

## 📚 **Recursos Adicionales**

### **Documentación:**
- `CLAUDE.md` - Documentación completa del proyecto
- `ANALISIS_DEPENDENCIAS.md` - Estructura del sistema
- `PLAN_ACCION_ERRORES.md` - Registro de correcciones

### **Ejemplos:**
- `ejemplo_master_completo.inf` - Ejemplo completo funcional
- Otros ejemplos en `/ejemplos/basicos/` y `/ejemplos/avanzados/`

### **Soporte:**
- Revisar logs de compilación para errores específicos
- Consultar documentación de PunyInform original
- Verificar que el compilador Inform 6 esté actualizado

---

*Guía actualizada el 7 de julio de 2025 - Claude Code*  
**Estado: ✅ VERIFICADO Y FUNCIONAL**