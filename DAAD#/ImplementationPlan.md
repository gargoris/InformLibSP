# Plan de Implementación de CondActs Faltantes - DAAD#

## ✅ FASE 1 - COMPLETADA: CondActs Críticos Fundamentales

### Implementados en esta fase:
- **QUIT** (ID: 127) - Salir del juego con confirmación ✅
- **PARSE** (ID: 126) - Analizar entrada del jugador ✅
- **PROCESS** (ID: 125) - Llamar a sub-proceso ✅
- **DOALL** (ID: 124) - Ejecutar para todos los objetos ✅
- **SYSMESS** (ID: 123) - Mostrar mensaje del sistema ✅
- **EXTERN** (ID: 122) - Ejecutar código externo ✅
- **SAVE** (ID: 117) - Guardar estado del juego ✅
- **LOAD** (ID: 116) - Cargar estado del juego ✅
- **HASAT** (ID: 121) - Objeto tiene atributo ✅
- **HASNAT** (ID: 120) - Objeto NO tiene atributo ✅
- **PUTIN** (ID: 119) - Meter objeto en contenedor ✅
- **TAKEOUT** (ID: 118) - Sacar objeto de contenedor ✅

## 🔄 FASE 2: CondActs de Control de Flujo y Parser Avanzado

### A implementar próximamente:

#### Parser Avanzado
- **ADJECT1** (ID: 115) - Primer adjetivo
- **ADJECT2** (ID: 114) - Segundo adjetivo
- **ADVERB** (ID: 113) - Adverbio
- **PREP** (ID: 112) - Preposición
- **NOUN2** (ID: 111) - Segundo sustantivo

#### Comparaciones
- **NOTEQ** (ID: 110) - No igual
- **NOTSAME** (ID: 109) - No mismo
- **BIGGER** (ID: 108) - Mayor que
- **SMALLER** (ID: 107) - Menor que
- **ISNOTAT** (ID: 106) - Objeto NO en localización

#### Control de Procesos
- **ISDONE** (ID: 105) - Proceso terminó exitosamente
- **ISNDONE** (ID: 104) - Proceso terminó sin éxito
- **NOTDONE** (ID: 103) - Marcar proceso como no exitoso
- **SKIP** (ID: 102) - Saltar N CondActs

## 🔄 FASE 3: CondActs de Familia COPY

### Familia COPY (Críticos para manipulación de datos):
- **COPYFF** (ID: 101) - Copiar flag a flag
- **COPYOF** (ID: 100) - Copiar objeto a flag  
- **COPYFO** (ID: 99) - Copiar flag a objeto
- **COPYOO** (ID: 98) - Copiar objeto a objeto
- **COPYBF** (ID: 97) - Copiar byte a flag

## 🔄 FASE 4: Acciones Automáticas

### Auto-acciones (Importantes para UX):
- **AUTOG** (ID: 96) - Coger automático
- **AUTOD** (ID: 95) - Soltar automático
- **AUTOW** (ID: 94) - Vestir automático
- **AUTOR** (ID: 93) - Quitar automático
- **AUTOP** (ID: 92) - Meter automático
- **AUTOT** (ID: 91) - Sacar automático

## 🔄 FASE 5: Gestión de Objetos Avanzada

### Listas y manipulación:
- **LISTOBJ** (ID: 90) - Listar objetos presentes
- **LISTAT** (ID: 89) - Listar objetos en localización
- **WHATO** (ID: 88) - Buscar objeto por sustantivo
- **SETCO** (ID: 87) - Establecer objeto actual
- **WEIGH** (ID: 86) - Pesar objeto
- **WEIGHT** (ID: 85) - Peso total jugador
- **ABILITY** (ID: 84) - Configurar capacidades
- **SWAP** (ID: 83) - Intercambiar objetos
- **DROPALL** (ID: 82) - Soltar todo
- **PUTO** (ID: 81) - Mover objeto actual

## 🔄 FASE 6: Multimedia y Pantalla

### Multimedia:
- **BEEP** (ID: 80) - Sonido básico
- **PICTURE** (ID: 79) - Mostrar imagen
- **SFX** (ID: 78) - Efecto de sonido

### Ventanas y pantalla:
- **WINDOW** (ID: 77) - Seleccionar ventana
- **WINAT** (ID: 76) - Posicionar ventana
- **WINSIZE** (ID: 75) - Tamaño ventana
- **CENTRE** (ID: 74) - Centrar ventana
- **PAPER** (ID: 73) - Color fondo
- **INK** (ID: 72) - Color tinta
- **BORDER** (ID: 71) - Color borde

### Impresión avanzada:
- **DPRINT** (ID: 70) - Imprimir doble byte
- **PRINTAT** (ID: 69) - Imprimir en posición
- **TAB** (ID: 68) - Tabular
- **SPACE** (ID: 67) - Imprimir espacio
- **MES** (ID: 66) - Mensaje sin nueva línea

## 🔄 FASE 7: Utilidades y Sistema

### Utilidades:
- **ANYKEY** (ID: 65) - Esperar tecla
- **PAUSE** (ID: 64) - Pausa en frames
- **TIME** (ID: 63) - Configurar timeout
- **INPUT** (ID: 62) - Configurar entrada
- **INKEY** (ID: 61) - Tecla presionada

### Cálculos y flags:
- **ADD** (ID: 60) - Sumar flags
- **SUB** (ID: 59) - Restar flags
- **RANDOM** (ID: 58) - Número aleatorio

### Sistema:
- **MODE** (ID: 57) - Modo pantalla
- **RESET** (ID: 56) - Reiniciar objetos
- **EXIT** (ID: 55) - Salir a sistema
- **OK** (ID: 54) - Marcar OK
- **NEWTEXT** (ID: 53) - Limpiar buffer texto
- **DISPLAY** (ID: 52) - Mostrar pantalla
- **CALL** (ID: 51) - Llamar rutina
- **SYNONYM** (ID: 50) - Definir sinónimo

### Guardado avanzado:
- **RAMSAVE** (ID: 49) - Guardar en RAM
- **RAMLOAD** (ID: 48) - Cargar de RAM
- **SAVEAT** (ID: 47) - Guardar posición cursor
- **BACKAT** (ID: 46) - Restaurar posición cursor

### Otros:
- **GFX** (ID: 45) - Comando gráfico
- **MOUSE** (ID: 44) - Leer ratón
- **REDO** (ID: 43) - Rehacer comando
- **MOVE** (ID: 42) - Mover usando conexiones

## 📊 Estado Actual de Implementación

### ✅ Implementados en Fase 1: 12 CondActs
### 🔄 Pendientes Total: 31 CondActs restantes

### Prioridad de Implementación:
1. **🔴 Crítico** - Fase 2 (Parser y Control): 15 CondActs
2. **🟡 Importante** - Fase 3-4 (COPY y Auto): 11 CondActs  
3. **🟢 Útil** - Fase 5-7 (Multimedia y Utilidades): 5 CondActs

## 🎯 Próximos Pasos

1. **Inmediato**: Implementar Fase 2 (Parser Avanzado y Comparaciones)
2. **Corto plazo**: Completar Fase 3 (Familia COPY) 
3. **Medio plazo**: Fases 4-5 (Auto-acciones y Objetos)
4. **Largo plazo**: Fases 6-7 (Multimedia y Sistema)

## 📋 Archivos Creados

- `CriticalCondactsImplementation.cs` - Marco base y definiciones
- `CriticalCondactsSpecific.cs` - Implementaciones específicas de Fase 1
- `GameState.cs` - Estado del juego y estructuras de datos
- `ImplementationPlan.md` - Este plan de implementación

## 🔧 Uso

```csharp
// Inicializar el implementador
var gameState = new GameState();
gameState.Initialize();

var implementer = new CriticalCondactsImplementer(logger, gameState);

// Usar CondActs implementados
implementer.ExecuteQuit();
implementer.ExecuteParse();
implementer.ExecuteProcess(1);
// etc.
```

---

**Estado**: Fase 1 completada - CondActs críticos implementados
**Cobertura actual**: 94/125 (75%) vs 82/125 (66%) inicial
**Incremento**: +12 CondActs críticos funcionales
