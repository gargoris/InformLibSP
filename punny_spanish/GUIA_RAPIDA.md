# 🚀 Guía Rápida - PunyInform Español Integrado

## ⚡ **Inicio Ultra-Rápido (2 pasos)**

### 1. Incluir el Sistema
```inform6
Include "puny_spanish_integrado.h";
```

### 2. Inicializar en tu juego
```inform6
[ Initialise;
    InicializarEspanol();  // ← IMPORTANTE: Solo esta línea
    location = TuUbicacion;
    lookmode = 2;
];
```

**¡YA ESTÁ!** Tu juego entiende español completo con conjugaciones y concordancia.

---

## 📚 **Versiones Disponibles (Elige Una)**

### 🌟 **RECOMENDADO: Sistema Integrado** - `puny_spanish_integrado.h`
✅ **Todo incluido** - Gramática optimizada + Mensajes + Funciones  
✅ **Fácil de usar** - Solo 1 include, 1 función de inicialización  
✅ **66% menos código** - Sin duplicados, máximo rendimiento  
✅ **100% funcional** - Todas las características

### 📖 **Alternativa: Sistema Original** - `spanish_final/puny_spanish_master.h`
✅ Funcionalidad completa  
❌ Más código duplicado  
❌ Más complejo de mantener

### ⚙️ **Avanzado: Componentes Separados**
- `spanish_final/grammar_optimizada.h` - Solo gramática optimizada
- `spanish_final/verbos_infinitivos.h` - Solo sistema de verbos
- `spanish_final/verbos_irregulares.h` - Solo verbos irregulares

---

## 🎯 **Configuración Opcional**

Añade ANTES del `Include` para personalizar:

```inform6
! Verbos adicionales (besar, comprar, rezar, etc.)
Constant OPTIONAL_EXTENDED_VERBSET;

! Ver información de debug del parser
Constant DEBUG_SPANISH_PARSER;

! Usar mensajes originales en inglés (solo gramática española)
Constant DISABLE_SPANISH_MESSAGES;

Include "puny_spanish_integrado.h";
```

---

## 👥 **Objetos con Género (Esencial)**

### Femenino
```inform6
Object mesa "mesa elegante"
    with name 'mesa' 'elegante',
    has supporter female;        // ← FEMENINO
```

### Masculino (por defecto)
```inform6
Object libro "libro antiguo"
    with name 'libro' 'antiguo',
    has ;                        // ← MASCULINO (defecto)
```

### Plural
```inform6
Object llaves "llaves plateadas"
    with name 'llaves' 'plateadas',
    has female pluralname;       // ← FEMENINO PLURAL
```

---

## 🎮 **Comandos Que Funcionan Automáticamente**

### Movimiento
```
ir al norte / ve al norte / anda al norte / camina al norte
entrar / entra / dentro / adentro
salir / sal / fuera / afuera
```

### Manipulación  
```
coger el libro / coge el libro / toma el libro / agarra el libro
dejar la mesa / deja la mesa / suelta la mesa / tira la mesa
meter libro en caja / mete libro en caja
poner llaves sobre mesa / pon llaves sobre mesa
```

### Examinación
```
mirar / mira / ver / observar / contemplar
examinar mesa / examina mesa / inspecciona mesa / revisa mesa
buscar en caja / busca en caja / registrar caja
```

### Comunicación
```
hablar con guardia / habla con guardia
preguntar a mago por llave / pregunta a mago por llave
responder "sí" / responde "sí" / contestar "no"
```

### Reflexivos
```
ponerse sombrero / ponte sombrero / vestirse sombrero
quitarse zapatos / quítate zapatos / desvestirse camisa
levantarse / levántate / sentarse en silla / acostarse en cama
```

### Metacomandos
```
inventario / inv / i / objetos / cosas
puntuación / puntos / score / puntaje
guardar / grabar / save / salvar
cargar / recuperar / restore
salir / quit / terminar / abandonar
```

---

## 🎯 **Mensajes Automáticos con Concordancia**

El sistema automáticamente usa el género y número correctos:

```
> coger las llaves
Cogidas.                    // ← Femenino plural

> coger el libro  
Cogido.                     // ← Masculino singular

> examinar la mesa
No hay nada especial en la mesa elegante.

> ponerse el sombrero
Te pones el sombrero elegante.
```

---

## 🔧 **Funciones Útiles Disponibles**

### Artículos y Concordancia
```inform6
ElLaLosLas(objeto);         // Imprime "el/la/los/las"
UnUnaUnosUnas(objeto);      // Imprime "un/una/unos/unas"
EsteEstaEstosEstas(objeto); // Imprime "este/esta/estos/estas"
```

### Conjugaciones
```inform6
EstaEstan(objeto);          // Imprime "está/están"
EsSon(objeto);              // Imprime "es/son"  
TieneTienen(objeto);        // Imprime "tiene/tienen"
```

### Detectores
```inform6
if (EsFemenino(objeto)) ...
if (EsPlural(objeto)) ...
if (EsAnimado(objeto)) ...
```

### Impresión
```inform6
ImprimirConArticulo(objeto);           // "la mesa", "el libro"
ImprimirConArticuloIndefinido(objeto); // "una mesa", "un libro"
```

---

## 📝 **Plantilla Mínima de Proyecto**

```inform6
Constant Story "^Mi Aventura^";
Constant Headline "^Un juego en español^";

! Configuración opcional
Constant OPTIONAL_EXTENDED_VERBSET;

! Sistema español integrado
Include "puny_spanish_integrado.h";

! Tu ubicación
Object Salon "salón"
    with description "Un salón elegante.",
    has light;

! Objetos con género  
Object -> mesa "mesa"
    with name 'mesa',
    has supporter female;

Object -> libro "libro"  
    with name 'libro',
    has ;

! Inicialización
[ Initialise;
    InicializarEspanol();
    location = Salon;
    lookmode = 2;
];
```

**Compilar:** `inform tuarchivo.inf tuarchivo.z5`

---

## ✅ **Verificar Que Funciona**

Después de compilar e iniciar tu juego, prueba:

```
> mirar
> examinar la mesa  
> coger el libro
> inventario
> poner libro sobre mesa
> ir al norte (si tienes otra habitación)
```

Si ves mensajes en español con concordancia correcta, **¡todo funciona!**

---

## 🆘 **Solución de Problemas**

### Error: "No such file"
- Verifica que `puny_spanish_integrado.h` esté en la misma carpeta
- O usa la ruta completa: `Include "ruta/puny_spanish_integrado.h";`

### Comandos no reconocidos
- Asegúrate de llamar `InicializarEspanol()` en `Initialise`
- Verifica que no hay errores de compilación

### Mensajes en inglés
- Verifica que NO tienes `Constant DISABLE_SPANISH_MESSAGES;`
- El sistema incluye mensajes españoles por defecto

### Concordancia incorrecta
- Verifica que los objetos tienen `has female` para femeninos
- Usa `has pluralname` para objetos en plural
- Los masculinos no necesitan atributos especiales

---

## 🎯 **Siguiente Paso**

1. **Copia** la plantilla mínima
2. **Añade** tus objetos y ubicaciones con género correcto
3. **Compila** y prueba
4. **¡Disfruta** tu juego en español completo!

Para ejemplos más avanzados, revisa `ejemplo_integrado.inf` que incluye todas las características del sistema.

**¡Tu aventura en español está lista! 🚀**