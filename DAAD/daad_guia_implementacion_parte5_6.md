# Sistema Parser DAAD Modernizado - Parte 5: Guía de Implementación

## Parte 5.6: Testing, Integración y Herramientas de Soporte - Completando el Ecosistema

### 5.6.1 La Importancia del Testing en Sistemas de Lenguaje

Antes de sumergirnos en el código específico, es crucial entender por qué el testing es especialmente crítico en un sistema como DAAD Modernizado. Imagina que estás construyendo un puente: no solo necesitas que las vigas individuales sean sólidas, sino que toda la estructura funcione en conjunto bajo diferentes condiciones climáticas y cargas de tráfico.

En nuestro caso, no estamos construyendo un puente físico, sino un puente lingüístico entre la intención humana expresada en español natural y la lógica computacional. Este puente debe soportar la creatividad infinita del lenguaje humano, las variaciones dialectales del español, y la complejidad narrativa de las aventuras conversacionales.

El testing en sistemas de procesamiento de lenguaje natural presenta desafíos únicos. A diferencia de una función matemática que para una entrada específica siempre debe producir la misma salida, nuestro sistema debe manejar múltiples formas correctas de expresar la misma idea, detectar errores humanos comunes, y gracefully degradar cuando se encuentra con entrada inesperada.

```csharp
// Testing/DaadTestingFramework.cs
namespace DaadModernizado.Testing;

/// <summary>
/// Framework especializado para testing de sistemas de aventuras conversacionales.
/// Proporciona utilidades específicas para testing de DSLs y procesamiento de español.
/// </summary>
public class DaadTestingFramework
{
    private readonly IServiceProvider _serviceProvider;
    private readonly ILogger<DaadTestingFramework> _logger;

    public DaadTestingFramework(IServiceProvider serviceProvider, ILogger<DaadTestingFramework> logger)
    {
        _serviceProvider = serviceProvider;
        _logger = logger;
    }

    /// <summary>
    /// Crear un juego de prueba con una estructura básica pero completa.
    /// Esto nos permite testing de funcionalidades sin tener que construir
    /// manualmente estructuras complejas en cada test.
    /// </summary>
    public ModernDaadGame CreateTestGame(string scenario = "basic")
    {
        return scenario.ToLowerInvariant() switch
        {
            "empty" => CreateEmptyGame(),
            "basic" => CreateBasicTestGame(),
            "complex" => CreateComplexTestGame(),
            "spanish" => CreateSpanishFocusedGame(),
            _ => throw new ArgumentException($"Escenario de prueba desconocido: {scenario}")
        };
    }

    /// <summary>
    /// Validar que un juego parseado tiene la estructura esperada.
    /// Esto es especialmente útil para testing de regresión.
    /// </summary>
    public TestValidationResult ValidateGameStructure(ModernDaadGame game, GameExpectations expectations)
    {
        var result = new TestValidationResult();

        // Validar metadatos básicos
        if (expectations.ExpectedTitle != null && game.Metadata.Title != expectations.ExpectedTitle)
        {
            result.Errors.Add($"Título esperado: '{expectations.ExpectedTitle}', encontrado: '{game.Metadata.Title}'");
        }

        // Validar número de localidades
        if (expectations.ExpectedLocationCount.HasValue && 
            game.Locations.Count != expectations.ExpectedLocationCount.Value)
        {
            result.Errors.Add($"Localidades esperadas: {expectations.ExpectedLocationCount}, encontradas: {game.Locations.Count}");
        }

        // Validar existencia de localidades específicas
        foreach (var expectedLocation in expectations.ExpectedLocations)
        {
            if (!game.Locations.ContainsKey(expectedLocation))
            {
                result.Errors.Add($"Localidad esperada no encontrada: '{expectedLocation}'");
            }
        }

        // Validar objetos
        foreach (var expectedObject in expectations.ExpectedObjects)
        {
            if (!game.Objects.ContainsKey(expectedObject))
            {
                result.Errors.Add($"Objeto esperado no encontrado: '{expectedObject}'");
            }
        }

        // Validar respuestas
        if (expectations.ExpectedResponseCount.HasValue &&
            game.Responses.Count != expectations.ExpectedResponseCount.Value)
        {
            result.Errors.Add($"Respuestas esperadas: {expectations.ExpectedResponseCount}, encontradas: {game.Responses.Count}");
        }

        result.IsValid = result.Errors.Count == 0;
        return result;
    }

    private ModernDaadGame CreateBasicTestGame()
    {
        var game = new ModernDaadGame
        {
            Metadata = new GameMetadata
            {
                Title = "Aventura de Prueba",
                Author = "Framework de Testing",
                StartLocation = "habitacion_inicial",
                MaxScore = 100,
                Version = "1.0"
            }
        };

        // Crear localidades interconectadas
        game.Locations["habitacion_inicial"] = new ModernLocation
        {
            Id = "habitacion_inicial",
            Name = "Habitación Inicial",
            Description = "Una habitación simple con una puerta al norte.",
            Exits = new Dictionary<string, string> { ["norte"] = "pasillo" }
        };

        game.Locations["pasillo"] = new ModernLocation
        {
            Id = "pasillo",
            Name = "Pasillo",
            Description = "Un pasillo largo con puertas a ambos lados.",
            Exits = new Dictionary<string, string> 
            { 
                ["sur"] = "habitacion_inicial",
                ["este"] = "biblioteca"
            }
        };

        game.Locations["biblioteca"] = new ModernLocation
        {
            Id = "biblioteca",
            Name = "Biblioteca",
            Description = "Una biblioteca llena de libros antiguos.",
            Exits = new Dictionary<string, string> { ["oeste"] = "pasillo" },
            Objects = ["libro_magico", "llave_dorada"]
        };

        // Crear objetos de prueba
        game.Objects["libro_magico"] = new ModernObject
        {
            Id = "libro_magico",
            Name = "libro mágico",
            Description = "Un libro que brilla con una luz tenue.",
            Location = "biblioteca",
            IsTakeable = true,
            Weight = 2
        };

        game.Objects["llave_dorada"] = new ModernObject
        {
            Id = "llave_dorada", 
            Name = "llave dorada",
            Description = "Una pequeña llave de oro brillante.",
            Location = "biblioteca",
            IsTakeable = true,
            Weight = 1
        };

        // Crear algunos mensajes
        game.Messages["bienvenida"] = "¡Bienvenido a la aventura de prueba!";
        game.Messages["no_puedes"] = "No puedes hacer eso.";
        game.Messages["bien_hecho"] = "¡Bien hecho!";

        // Crear respuestas básicas
        game.Responses.Add(new ModernResponse
        {
            Patterns = ["mirar libro", "examinar libro"],
            Condition = CommonConditions.Present("libro_magico"),
            Actions = [CommonActions.Message("El libro contiene conocimientos arcanos.")]
        });

        return game;
    }

    private ModernDaadGame CreateSpanishFocusedGame()
    {
        // Juego específicamente diseñado para testing de características del español
        var game = CreateBasicTestGame();

        // Añadir objetos con nombres que testen características específicas del español
        game.Objects["espada_brillante"] = new ModernObject
        {
            Id = "espada_brillante",
            Name = "espada brillante",
            Description = "Una espada que destella a la luz.",
            Location = "biblioteca",
            IsTakeable = true
        };

        // Respuestas que testen sinónimos y variaciones
        game.Responses.Add(new ModernResponse
        {
            Patterns = ["coger espada", "tomar espada", "agarrar espada"],
            Condition = CommonConditions.Present("espada_brillante"),
            Actions = [CommonActions.Take("espada_brillante"), CommonActions.Message("Coges la espada brillante.")]
        });

        // Respuestas que testen preposiciones complejas
        game.Responses.Add(new ModernResponse
        {
            Patterns = ["usar llave en puerta"],
            Condition = CommonConditions.And(
                CommonConditions.Carried("llave_dorada"),
                CommonConditions.Present("puerta_secreta")
            ),
            Actions = [CommonActions.Message("La llave encaja perfectamente.")]
        });

        return game;
    }
}

// Clases de apoyo para expectations en testing
public record GameExpectations
{
    public string? ExpectedTitle { get; init; }
    public int? ExpectedLocationCount { get; init; }
    public int? ExpectedObjectCount { get; init; }
    public int? ExpectedResponseCount { get; init; }
    public List<string> ExpectedLocations { get; init; } = new();
    public List<string> ExpectedObjects { get; init; } = new();
    public List<string> ExpectedMessages { get; init; } = new();
}

public record TestValidationResult
{
    public bool IsValid { get; set; }
    public List<string> Errors { get; init; } = new();
    public List<string> Warnings { get; init; } = new();
}
```

### 5.6.2 Testing del Parser Principal - Casos Comprehensivos

El testing del parser principal debe cubrir no solo casos de éxito, sino también casos de error elegante, recuperación, y edge cases que pueden aparecer en aventuras reales.

```csharp
// Tests/Integration/MainParserIntegrationTests.cs
namespace DaadModernizado.Tests.Integration;

/// <summary>
/// Tests de integración que verifican que todo el pipeline de parsing funciona
/// correctamente desde entrada de texto hasta juego completo.
/// </summary>
public class MainParserIntegrationTests : TestBase
{
    private readonly IGameParser _parser;
    private readonly DaadTestingFramework _testFramework;

    public MainParserIntegrationTests(ITestOutputHelper output) : base(output)
    {
        _parser = GetService<IGameParser>();
        _testFramework = GetService<DaadTestingFramework>();
    }

    [Fact]
    public async Task ParseCompleteGame_ValidInput_ProducesWorkingGame()
    {
        // Arrange - Crear un archivo de aventura completo pero simple
        var gameSource = """
            game {
              title: "Mi Primera Aventura"
              author: "Desarrollador Novato"  
              start: inicio
              max_score: 50
            }

            vocab {
              nouns: { cristal: 60, pergamino: 61 }
            }

            location inicio {
              desc: "Estás en una habitación circular con una puerta al norte."
              exits: { norte: salon }
              objects: [cristal]
            }

            location salon {
              desc: "Un gran salón con tapices en las paredes."
              exits: { sur: inicio }
              objects: [pergamino]
            }

            object cristal {
              name: "cristal mágico"
              desc: "Un cristal que pulsa con luz azul"
              location: inicio
              takeable: true
            }

            object pergamino {
              name: "pergamino antiguo"
              desc: "Un pergamino con runas extrañas"
              location: salon
              takeable: true
            }

            messages {
              saludo: "¡Bienvenido, aventurero!"
              despedida: "Gracias por jugar"
            }

            responses {
              on "mirar cristal" {
                require: present(cristal)
                do: {
                  message("El cristal brilla intensamente")
                  add_score(5)
                }
              }
              
              on ["coger cristal", "tomar cristal"] {
                require: present(cristal) && !carried(cristal)
                do: {
                  take(cristal)
                  message("Coges el cristal. Sientes su poder.")
                  add_score(10)
                }
              }
            }
            """;

        // Act - Parsear el juego completo
        var result = await _parser.ParseAsync(gameSource);

        // Assert - Verificar estructura completa
        Assert.True(result.IsSuccess, $"Parsing falló: {string.Join(", ", result.Errors.Select(e => e.Message))}");
        Assert.NotNull(result.Game);

        var game = result.Game!;
        
        // Validar usando nuestro framework de testing
        var expectations = new GameExpectations
        {
            ExpectedTitle = "Mi Primera Aventura",
            ExpectedLocationCount = 2,
            ExpectedObjectCount = 2,
            ExpectedResponseCount = 2,
            ExpectedLocations = ["inicio", "salon"],
            ExpectedObjects = ["cristal", "pergamino"]
        };

        var validation = _testFramework.ValidateGameStructure(game, expectations);
        Assert.True(validation.IsValid, $"Validación falló: {string.Join(", ", validation.Errors)}");

        // Verificar que las conexiones están correctas
        Assert.Equal("salon", game.Locations["inicio"].Exits["norte"]);
        Assert.Equal("inicio", game.Locations["salon"].Exits["sur"]);

        // Verificar que los objetos están en las localidades correctas
        Assert.Contains("cristal", game.Locations["inicio"].Objects);
        Assert.Contains("pergamino", game.Locations["salon"].Objects);
    }

    [Theory]
    [InlineData("", "Entrada vacía debe manejar gracefully")]
    [InlineData("   \n\t   ", "Solo espacios en blanco")]
    [InlineData("game { title: }", "Valor de propiedad faltante")]
    [InlineData("unknown_section { }", "Sección no reconocida")]
    public async Task ParseInvalidInput_HandlesGracefully(string input, string description)
    {
        // Act
        var result = await _parser.ParseAsync(input);

        // Assert
        // Para entrada inválida, esperamos que falle gracefully
        // (no lance excepciones) y proporcione errores útiles
        Assert.False(result.IsSuccess, $"Debería fallar para: {description}");
        Assert.NotEmpty(result.Errors);
        
        // Los errores deben ser informativos, no genéricos
        foreach (var error in result.Errors)
        {
            Assert.False(string.IsNullOrWhiteSpace(error.Message));
            Assert.True(error.LineNumber >= 0);
        }
    }

    [Fact]
    public async Task ParseGameWithReferences_ResolvesCorrectly()
    {
        // Test específico para verificar que las referencias entre secciones se resuelven
        var gameSource = """
            game {
              title: "Test de Referencias"
              start: entrada
            }

            location entrada {
              desc: "La entrada principal"
              exits: { norte: tesoro }
            }

            location tesoro {
              desc: "El cuarto del tesoro"
              exits: { sur: entrada }
              objects: [moneda_oro]
            }

            object moneda_oro {
              name: "moneda de oro"
              desc: "Una moneda brillante"
              location: tesoro
              takeable: true
            }

            responses {
              on "coger moneda" {
                require: present(moneda_oro) && at(tesoro)
                do: {
                  take(moneda_oro)
                  message("victoria")
                }
              }
            }

            messages {
              victoria: "¡Has encontrado el tesoro!"
            }
            """;

        // Act
        var result = await _parser.ParseAsync(gameSource);

        // Assert
        Assert.True(result.IsSuccess);
        
        var game = result.Game!;
        
        // Verificar que las referencias se resolvieron correctamente
        var response = game.Responses.First();
        
        // La respuesta debería referenciar los objetos y localidades correctos
        Assert.Contains("moneda_oro", response.Condition!.ToString());
        Assert.Contains("tesoro", response.Condition.ToString());
        
        // El mensaje referenciado debería existir
        Assert.True(game.Messages.ContainsKey("victoria"));
    }

    [Fact]
    public async Task ParseGame_WithWarnings_ReportsButContinues()
    {
        // Aventura que debería generar warnings pero aún ser parseable
        var gameSource = """
            game {
              title: "Aventura con Warnings"
              start: lugar_inalcanzable  // Warning: localidad start no existe aún
            }

            location inicio {
              desc: "Inicio real"
              exits: { norte: lugar_inexistente }  // Warning: destino no existe
            }

            object objeto_huerfano {
              name: "objeto sin hogar"
              location: lugar_fantasma  // Warning: localidad no existe
              takeable: true
            }

            responses {
              on "usar objeto_inexistente" {
                require: present(objeto_inexistente)  // Warning: objeto no existe
                do: { message("imposible") }
              }
            }
            """;

        // Act
        var result = await _parser.ParseAsync(gameSource);

        // Assert
        // Debería parsear pero con warnings
        Assert.True(result.IsSuccess);
        Assert.NotEmpty(result.Warnings);
        
        // Verificar que los warnings sean específicos y útiles
        var warningMessages = result.Warnings.Select(w => w.Message.ToLowerInvariant()).ToList();
        
        Assert.Contains(warningMessages, msg => msg.Contains("start") && msg.Contains("lugar_inalcanzable"));
        Assert.Contains(warningMessages, msg => msg.Contains("destino") && msg.Contains("lugar_inexistente"));
    }
}
```

### 5.6.3 Testing Específico del Procesamiento de Español

El testing del analizador sintáctico español requiere un enfoque especial que considere la riqueza y variabilidad del idioma español.

```csharp
// Tests/Spanish/SpanishSyntaxAnalyzerTests.cs
namespace DaadModernizado.Tests.Spanish;

/// <summary>
/// Tests específicos para el procesamiento de comandos en español natural.
/// Estos tests son críticos porque validan la interfaz principal del usuario.
/// </summary>
public class SpanishSyntaxAnalyzerTests : TestBase
{
    private readonly ISpanishSyntaxAnalyzer _analyzer;
    private readonly GameContext _gameContext;

    public SpanishSyntaxAnalyzerTests(ITestOutputHelper output) : base(output)
    {
        _analyzer = GetService<ISpanishSyntaxAnalyzer>();
        _gameContext = CreateTestGameContext();
    }

    /// <summary>
    /// Test que verifica que diferentes formas de expresar la misma idea
    /// se interpretan correctamente.
    /// </summary>
    [Theory]
    [InlineData("mirar espada", "mirar", "espada", CommandType.Examination)]
    [InlineData("examinar la espada", "examinar", "espada", CommandType.Examination)]
    [InlineData("ver espada brillante", "ver", "espada", CommandType.Examination)]
    [InlineData("observar cuidadosamente la espada", "observar", "espada", CommandType.Examination)]
    public void ParseCommand_ExaminationVariations_ParsesCorrectly(
        string input, string expectedVerb, string expectedObject, CommandType expectedType)
    {
        // Act
        var result = _analyzer.ParseCommand(input, _gameContext);

        // Assert
        Assert.True(result.IsSuccess, $"Falló parsing de '{input}': {string.Join(", ", result.Errors)}");
        Assert.NotNull(result.Command);
        
        var command = result.Command!;
        Assert.Equal(expectedType, command.Type);
        Assert.Equal(expectedVerb, command.Verb);
        Assert.Equal(expectedObject, command.DirectObject);
    }

    /// <summary>
    /// Test de sinónimos automáticos - característica clave del sistema español.
    /// </summary>
    [Theory]
    [InlineData("coger espada", "tomar espada")]
    [InlineData("agarrar llave", "coger llave")]
    [InlineData("recoger moneda", "tomar moneda")]
    public void ParseCommand_Synonyms_ProduceSameResult(string input1, string input2)
    {
        // Act
        var result1 = _analyzer.ParseCommand(input1, _gameContext);
        var result2 = _analyzer.ParseCommand(input2, _gameContext);

        // Assert
        Assert.True(result1.IsSuccess && result2.IsSuccess);
        
        // Los comandos sinónimos deberían producir la misma estructura semántica
        Assert.Equal(result1.Command!.Type, result2.Command!.Type);
        Assert.Equal(result1.Command.DirectObject, result2.Command.DirectObject);
        
        // Los verbos pueden ser diferentes, pero deberían mapearse al mismo concepto
        var verb1Canonical = GetCanonicalVerb(result1.Command.Verb);
        var verb2Canonical = GetCanonicalVerb(result2.Command.Verb);
        Assert.Equal(verb1Canonical, verb2Canonical);
    }

    /// <summary>
    /// Test de comandos complejos con preposiciones - construcción típica del español.
    /// </summary>
    [Theory]
    [InlineData("usar llave en puerta", "usar", "llave", "en", "puerta")]
    [InlineData("poner libro sobre mesa", "poner", "libro", "sobre", "mesa")]
    [InlineData("dar moneda a comerciante", "dar", "moneda", "a", "comerciante")]
    [InlineData("hablar con el mago", "hablar", "", "con", "mago")]
    public void ParseCommand_ComplexWithPrepositions_ParsesCorrectly(
        string input, string expectedVerb, string expectedDirect, 
        string expectedPrep, string expectedIndirect)
    {
        // Act
        var result = _analyzer.ParseCommand(input, _gameContext);

        // Assert
        Assert.True(result.IsSuccess, $"Parsing falló para '{input}'");
        
        var command = result.Command!;
        Assert.Equal(CommandType.Complex, command.Type);
        Assert.Equal(expectedVerb, command.Verb);
        Assert.Equal(expectedDirect, command.DirectObject);
        Assert.Equal(expectedPrep, command.Preposition);
        Assert.Equal(expectedIndirect, command.IndirectObject);
    }

    /// <summary>
    /// Test de resolución de pronombres - característica avanzada del español.
    /// </summary>
    [Fact]
    public void ParseCommand_WithPronouns_ResolvesContext()
    {
        // Arrange - Simular contexto conversacional
        _gameContext.AddRecentMention("espada", Gender.Feminine);
        _gameContext.AddRecentMention("escudo", Gender.Masculine);

        // Act - Usar pronombres que deberían resolverse
        var result1 = _analyzer.ParseCommand("cógela", _gameContext);  // debería referirse a "espada"
        var result2 = _analyzer.ParseCommand("cógelo", _gameContext);  // debería referirse a "escudo"

        // Assert
        Assert.True(result1.IsSuccess);
        Assert.True(result2.IsSuccess);
        
        // Verificar que los pronombres se resolvieron correctamente
        Assert.Equal("espada", result1.Command!.DirectObject);
        Assert.Equal("escudo", result2.Command!.DirectObject);
        
        // Verificar que se registró la resolución
        Assert.Contains("la", result1.Command.ResolvedReferences.Keys);
        Assert.Contains("lo", result2.Command.ResolvedReferences.Keys);
    }

    /// <summary>
    /// Test de manejo de errores y sugerencias - UX crítico.
    /// </summary>
    [Theory]
    [InlineData("mira", "¿Quisiste decir 'mirar'?")]
    [InlineData("cogre espada", "coger espada")]
    [InlineData("ir nortr", "ir norte")]
    public void ParseCommand_WithTypos_ProvidesSuggestions(string input, string expectedSuggestion)
    {
        // Act
        var result = _analyzer.ParseCommand(input, _gameContext);

        // Assert
        // Puede o no parsear exitosamente, pero debe proporcionar sugerencias útiles
        Assert.NotEmpty(result.Suggestions);
        
        var suggestions = string.Join(" ", result.Suggestions);
        Assert.Contains(expectedSuggestion, suggestions, StringComparison.OrdinalIgnoreCase);
    }

    /// <summary>
    /// Test de comandos direccionales - patrón común en aventuras.
    /// </summary>
    [Theory]
    [InlineData("norte", CommandType.Movement, "norte")]
    [InlineData("ir al norte", CommandType.Movement, "norte")]
    [InlineData("caminar hacia el sur", CommandType.Movement, "sur")]
    [InlineData("subir", CommandType.Movement, "arriba")]
    [InlineData("bajar las escaleras", CommandType.Movement, "abajo")]
    public void ParseCommand_Directions_ParsesCorrectly(
        string input, CommandType expectedType, string expectedDirection)
    {
        // Act
        var result = _analyzer.ParseCommand(input, _gameContext);

        // Assert
        Assert.True(result.IsSuccess);
        Assert.Equal(expectedType, result.Command!.Type);
        Assert.Equal(expectedDirection, result.Command.Direction);
    }

    /// <summary>
    /// Test de comandos con artículos y modificadores - manejo natural del español.
    /// </summary>
    [Theory]
    [InlineData("mirar la espada brillante")]
    [InlineData("examinar el libro muy antiguo")]
    [InlineData("coger esa llave pequeña")]
    public void ParseCommand_WithArticlesAndModifiers_FiltersCorrectly(string input)
    {
        // Act
        var result = _analyzer.ParseCommand(input, _gameContext);

        // Assert
        Assert.True(result.IsSuccess);
        
        // Los artículos deberían haberse filtrado, pero los modificadores importantes preservados
        var command = result.Command!;
        Assert.False(string.IsNullOrEmpty(command.DirectObject));
        
        // El objeto directo no debería contener artículos
        Assert.DoesNotContain("la", command.DirectObject);
        Assert.DoesNotContain("el", command.DirectObject);
        Assert.DoesNotContain("esa", command.DirectObject);
    }

    /// <summary>
    /// Test de performance - importante para UX responsiva.
    /// </summary>
    [Fact]
    public void ParseCommand_Performance_CompletesQuickly()
    {
        // Arrange
        var complexInput = "examinar cuidadosamente la espada brillante que está sobre la mesa";
        var stopwatch = Stopwatch.StartNew();

        // Act
        var result = _analyzer.ParseCommand(complexInput, _gameContext);
        stopwatch.Stop();

        // Assert
        Assert.True(result.IsSuccess);
        
        // El parsing debería completarse en menos de 100ms para UX fluida
        Assert.True(stopwatch.ElapsedMilliseconds < 100, 
            $"Parsing tomó {stopwatch.ElapsedMilliseconds}ms, demasiado lento para UX fluida");
    }

    private GameContext CreateTestGameContext()
    {
        var context = new GameContext();
        
        // Añadir objetos de prueba con propiedades gramaticales
        context.AddObject(new GameObject 
        { 
            Id = "espada", 
            Name = "espada brillante",
            Gender = Gender.Feminine,
            IsVisible = true,
            IsPresent = true
        });
        
        context.AddObject(new GameObject 
        { 
            Id = "escudo", 
            Name = "escudo de hierro",
            Gender = Gender.Masculine,
            IsVisible = true,
            IsPresent = true
        });

        context.AddObject(new GameObject 
        { 
            Id = "llave", 
            Name = "llave dorada",
            Gender = Gender.Feminine,
            IsVisible = true,
            IsPresent = true
        });

        return context;
    }

    private string GetCanonicalVerb(string verb)
    {
        // Mapeo de sinónimos a formas canónicas para testing
        var synonymMap = new Dictionary<string, string>
        {
            ["coger"] = "take",
            ["tomar"] = "take", 
            ["agarrar"] = "take",
            ["mirar"] = "look",
            ["examinar"] = "look",
            ["ver"] = "look"
        };

        return synonymMap.GetValueOrDefault(verb, verb);
    }
}
```

### 5.6.4 Testing de Compatibilidad con DAAD Clásico

Una parte crítica del testing es verificar que el transpilador produce código DAAD clásico correcto y que las aventuras transpiladas funcionan como se espera.

```csharp
// Tests/Transpiler/ClassicCompatibilityTests.cs
namespace DaadModernizado.Tests.Transpiler;

/// <summary>
/// Tests que verifican la compatibilidad completa con DAAD clásico.
/// Estos tests son especialmente importantes porque validan que no estamos
/// rompiendo el ecosistema existente.
/// </summary>
public class ClassicCompatibilityTests : TestBase
{
    private readonly IClassicDaadTranspiler _transpiler;
    private readonly IGameParser _parser;

    public ClassicCompatibilityTests(ITestOutputHelper output) : base(output)
    {
        _transpiler = GetService<IClassicDaadTranspiler>();
        _parser = GetService<IGameParser>();
    }

    [Fact]
    public async Task TranspileBasicGame_ProducesValidClassicFormat()
    {
        // Arrange - Crear juego moderno simple
        var modernSource = """
            game {
              title: "Prueba Transpilación"
              start: inicio
              max_score: 10
            }

            location inicio {
              desc: "Una habitación simple"
              exits: { norte: final }
            }

            location final {
              desc: "El final del juego"
              exits: { sur: inicio }
            }

            object tesoro {
              name: "tesoro brillante"
              desc: "Un tesoro que brilla"
              location: final
              takeable: true
            }

            responses {
              on "coger tesoro" {
                require: present(tesoro)
                do: {
                  take(tesoro)
                  add_score(10)
                  end_game
                }
              }
            }
            """;

        // Act - Parsear y transpilar
        var parseResult = await _parser.ParseAsync(modernSource);
        Assert.True(parseResult.IsSuccess);

        var transpileResult = _transpiler.Transpile(parseResult.Game!, new TranspileOptions());

        // Assert - Verificar formato clásico
        Assert.True(transpileResult.IsSuccess);
        
        var classicCode = transpileResult.ClassicDaadCode;
        
        // Verificar que contiene todas las secciones esperadas
        Assert.Contains("/CTL", classicCode);
        Assert.Contains("/CON", classicCode);
        Assert.Contains("/LTX", classicCode);
        Assert.Contains("/PRO", classicCode);
        
        // Verificar estructura específica
        Assert.Contains("TITLE \"Prueba Transpilación\"", classicCode);
        Assert.Contains("START 0", classicCode);  // inicio debería ser localidad 0
        Assert.Contains("MAXSCORE 10", classicCode);
        
        // Verificar conexiones
        Assert.Contains("0 10 1", classicCode);  // inicio norte final
        Assert.Contains("1 11 0", classicCode);  // final sur inicio
        
        // Verificar proceso de respuesta
        Assert.Contains("PRESENT", classicCode);
        Assert.Contains("GET", classicCode);
        Assert.Contains("SCORE 10", classicCode);
        Assert.Contains("END", classicCode);
    }

    [Fact]
    public void TranspileGame_WithIdentifierMapping_ProducesConsistentNumbers()
    {
        // Arrange
        var game = CreateGameWithManyElements();
        var options = new TranspileOptions 
        { 
            NumberingStrategy = NumberingStrategy.Optimized 
        };

        // Act - Transpilar múltiples veces
        var result1 = _transpiler.Transpile(game, options);
        var result2 = _transpiler.Transpile(game, options);

        // Assert - Los mapeos deberían ser determinísticos
        Assert.True(result1.IsSuccess && result2.IsSuccess);
        Assert.Equal(result1.IdentifierMapping, result2.IdentifierMapping);
        Assert.Equal(result1.ClassicDaadCode, result2.ClassicDaadCode);
    }

    [Fact]
    public void ValidateCompatibility_WithUnsupportedFeatures_ReportsWarnings()
    {
        // Arrange - Juego con características modernas no soportadas en clásico
        var gameWithModernFeatures = new ModernDaadGame
        {
            Metadata = new GameMetadata { Title = "Test Moderno" }
        };

        // Añadir respuesta con lógica OR (no soportada directamente)
        gameWithModernFeatures.Responses.Add(new ModernResponse
        {
            Patterns = ["test"],
            Condition = new ModernCondition
            {
                Type = ConditionType.Logical,
                Operator = "||",
                Left = CommonConditions.Present("objeto1"),
                Right = CommonConditions.Present("objeto2")
            }
        });

        // Act
        var validation = _transpiler.ValidateCompatibility(gameWithModernFeatures);

        // Assert
        Assert.NotEmpty(validation.Warnings);
        Assert.Contains(validation.Warnings, w => w.Contains("OR"));
    }

    [Fact]
    public void TranspileGame_WithPresetNumbers_RespectsMapping()
    {
        // Arrange
        var game = CreateSimpleGame();
        var options = new TranspileOptions
        {
            NumberingStrategy = NumberingStrategy.Manual,
            PresetNumbers = new Dictionary<string, int>
            {
                ["location:inicio"] = 5,
                ["object:espada"] = 100
            }
        };

        // Act
        var result = _transpiler.Transpile(game, options);

        // Assert
        Assert.True(result.IsSuccess);
        
        // Verificar que se usaron los números predefinidos
        Assert.Equal(5, result.IdentifierMapping["location:inicio"]);
        Assert.Equal(100, result.IdentifierMapping["object:espada"]);
        
        // Verificar que aparecen en el código generado
        Assert.Contains("START 5", result.ClassicDaadCode);
        Assert.Contains("PRESENT 100", result.ClassicDaadCode);
    }

    /// <summary>
    /// Test crucial: verificar que un juego DAAD clásico puede "round-trip"
    /// (clásico → moderno → clásico) sin pérdida de funcionalidad.
    /// </summary>
    [Fact]
    public void RoundTripTranspilation_PreservesGameBehavior()
    {
        // Este test es conceptual - en una implementación completa necesitaríamos
        // también un parser que pueda leer DAAD clásico
        
        // Arrange - Simular código DAAD clásico conocido
        var originalClassicBehavior = new ExpectedGameBehavior
        {
            StartLocation = 0,
            MaxScore = 100,
            LocationConnections = new Dictionary<(int from, int direction), int>
            {
                [(0, 10)] = 1,  // norte
                [(1, 11)] = 0   // sur
            },
            ObjectInitialLocations = new Dictionary<int, int>
            {
                [50] = 1  // objeto 50 en localidad 1
            }
        };

        // Para una implementación completa, aquí haríamos:
        // 1. Parsear DAAD clásico → ModernDaadGame
        // 2. Transpilar ModernDaadGame → DAAD clásico
        // 3. Verificar que el comportamiento es equivalente

        // Por ahora, verificamos que nuestro transpilador produce salida consistente
        var modernGame = CreateEquivalentModernGame();
        var transpileResult = _transpiler.Transpile(modernGame, new TranspileOptions());
        
        Assert.True(transpileResult.IsSuccess);
        VerifyBehaviorPreserved(transpileResult.ClassicDaadCode, originalClassicBehavior);
    }

    private void VerifyBehaviorPreserved(string classicCode, ExpectedGameBehavior expected)
    {
        // Verificar que elementos clave están presentes en el código transpilado
        Assert.Contains($"START {expected.StartLocation}", classicCode);
        Assert.Contains($"MAXSCORE {expected.MaxScore}", classicCode);
        
        foreach (var connection in expected.LocationConnections)
        {
            var (from, direction) = connection.Key;
            var to = connection.Value;
            Assert.Contains($"{from} {direction} {to}", classicCode);
        }
    }

    private ModernDaadGame CreateGameWithManyElements()
    {
        var game = new ModernDaadGame
        {
            Metadata = new GameMetadata { Title = "Juego Grande", StartLocation = "zona1" }
        };

        // Crear muchas localidades para testear mapeo de IDs
        for (int i = 1; i <= 10; i++)
        {
            game.Locations[$"zona{i}"] = new ModernLocation
            {
                Id = $"zona{i}",
                Description = $"Zona de prueba {i}"
            };
        }

        // Crear muchos objetos
        for (int i = 1; i <= 20; i++)
        {
            game.Objects[$"objeto{i}"] = new ModernObject
            {
                Id = $"objeto{i}",
                Name = $"objeto {i}",
                Location = $"zona{(i % 10) + 1}"
            };
        }

        return game;
    }

    private ModernDaadGame CreateSimpleGame()
    {
        var game = new ModernDaadGame
        {
            Metadata = new GameMetadata { Title = "Simple", StartLocation = "inicio" }
        };

        game.Locations["inicio"] = new ModernLocation
        {
            Id = "inicio",
            Description = "Inicio"
        };

        game.Objects["espada"] = new ModernObject
        {
            Id = "espada",
            Name = "espada",
            Location = "inicio"
        };

        return game;
    }

    private ModernDaadGame CreateEquivalentModernGame()
    {
        // Crear juego moderno equivalente al comportamiento clásico esperado
        var game = new ModernDaadGame
        {
            Metadata = new GameMetadata 
            { 
                Title = "Equivalente", 
                StartLocation = "loc0",
                MaxScore = 100
            }
        };

        game.Locations["loc0"] = new ModernLocation
        {
            Id = "loc0",
            Description = "Localidad 0",
            Exits = new Dictionary<string, string> { ["norte"] = "loc1" }
        };

        game.Locations["loc1"] = new ModernLocation
        {
            Id = "loc1", 
            Description = "Localidad 1",
            Exits = new Dictionary<string, string> { ["sur"] = "loc0" },
            Objects = ["obj50"]
        };

        game.Objects["obj50"] = new ModernObject
        {
            Id = "obj50",
            Name = "objeto 50",
            Location = "loc1"
        };

        return game;
    }
}

// Clases de apoyo para testing de comportamiento
public record ExpectedGameBehavior
{
    public int StartLocation { get; init; }
    public int MaxScore { get; init; }
    public Dictionary<(int from, int direction), int> LocationConnections { get; init; } = new();
    public Dictionary<int, int> ObjectInitialLocations { get; init; } = new();
}
```

### 5.6.5 Herramientas de Desarrollo y CLI

Para completar el ecosistema, necesitamos herramientas que faciliten el desarrollo y uso del sistema por parte de los creadores de aventuras.

```csharp
// Tools/DaadCli.cs
namespace DaadModernizado.Tools;

/// <summary>
/// Interfaz de línea de comandos para el sistema DAAD Modernizado.
/// Proporciona acceso a todas las funcionalidades principales desde terminal.
/// </summary>
public class DaadCli
{
    private readonly IServiceProvider _serviceProvider;
    private readonly ILogger<DaadCli> _logger;

    public DaadCli(IServiceProvider serviceProvider)
    {
        _serviceProvider = serviceProvider;
        _logger = serviceProvider.GetRequiredService<ILogger<DaadCli>>();
    }

    public async Task<int> RunAsync(string[] args)
    {
        try
        {
            var command = args.Length > 0 ? args[0].ToLowerInvariant() : "help";
            
            return command switch
            {
                "parse" => await ParseCommand(args[1..]),
                "transpile" => await TranspileCommand(args[1..]),
                "validate" => await ValidateCommand(args[1..]),
                "test" => await TestCommand(args[1..]),
                "new" => await NewProjectCommand(args[1..]),
                "help" => ShowHelp(),
                _ => ShowError($"Comando desconocido: {command}")
            };
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Error ejecutando comando CLI");
            Console.WriteLine($"Error: {ex.Message}");
            return 1;
        }
    }

    private async Task<int> ParseCommand(string[] args)
    {
        if (args.Length == 0)
            return ShowError("Uso: daad parse <archivo.daad> [--output=archivo.json]");

        var inputFile = args[0];
        var outputFile = GetOption(args, "--output") ?? 
                        Path.ChangeExtension(inputFile, ".json");

        Console.WriteLine($"Parseando '{inputFile}'...");

        var parser = _serviceProvider.GetRequiredService<IGameParser>();
        var result = await parser.ParseFromFileAsync(inputFile);

        if (result.IsSuccess)
        {
            Console.WriteLine("✅ Parsing exitoso!");
            
            // Guardar resultado como JSON para debugging/inspección
            var json = JsonSerializer.Serialize(result.Game, new JsonSerializerOptions 
            { 
                WriteIndented = true,
                PropertyNamingPolicy = JsonNamingPolicy.CamelCase
            });
            
            await File.WriteAllTextAsync(outputFile, json);
            Console.WriteLine($"Resultado guardado en: {outputFile}");

            // Mostrar estadísticas
            ShowParseStatistics(result);
            
            return 0;
        }
        else
        {
            Console.WriteLine("❌ Parsing falló:");
            foreach (var error in result.Errors)
            {
                Console.WriteLine($"  Línea {error.LineNumber}: {error.Message}");
            }

            if (result.Warnings.Count > 0)
            {
                Console.WriteLine("\n⚠️ Advertencias:");
                foreach (var warning in result.Warnings)
                {
                    Console.WriteLine($"  Línea {warning.LineNumber}: {warning.Message}");
                }
            }

            return 1;
        }
    }

    private async Task<int> TranspileCommand(string[] args)
    {
        if (args.Length == 0)
            return ShowError("Uso: daad transpile <archivo.daad> [--output=archivo.ddb] [--optimize]");

        var inputFile = args[0];
        var outputFile = GetOption(args, "--output") ?? 
                        Path.ChangeExtension(inputFile, ".ddb");
        var optimize = args.Contains("--optimize");

        Console.WriteLine($"Transpilando '{inputFile}' a DAAD clásico...");

        // Primero parsear
        var parser = _serviceProvider.GetRequiredService<IGameParser>();
        var parseResult = await parser.ParseFromFileAsync(inputFile);

        if (!parseResult.IsSuccess)
        {
            Console.WriteLine("❌ Error de parsing, no se puede transpilar:");
            foreach (var error in parseResult.Errors)
            {
                Console.WriteLine($"  {error.Message}");
            }
            return 1;
        }

        // Luego transpilar
        var transpiler = _serviceProvider.GetRequiredService<IClassicDaadTranspiler>();
        var options = new TranspileOptions
        {
            OptimizeCode = optimize,
            IncludeComments = true
        };

        var transpileResult = transpiler.Transpile(parseResult.Game!, options);

        if (transpileResult.IsSuccess)
        {
            await File.WriteAllTextAsync(outputFile, transpileResult.ClassicDaadCode);
            Console.WriteLine($"✅ Transpilación exitosa: {outputFile}");
            
            // Mostrar estadísticas
            ShowTranspileStatistics(transpileResult);
            
            return 0;
        }
        else
        {
            Console.WriteLine("❌ Transpilación falló:");
            foreach (var error in transpileResult.Errors)
            {
                Console.WriteLine($"  {error}");
            }
            return 1;
        }
    }

    private async Task<int> ValidateCommand(string[] args)
    {
        if (args.Length == 0)
            return ShowError("Uso: daad validate <archivo.daad>");

        var inputFile = args[0];
        Console.WriteLine($"Validando '{inputFile}'...");

        var parser = _serviceProvider.GetRequiredService<IGameParser>();
        var result = await parser.ParseFromFileAsync(inputFile);

        var hasErrors = false;

        // Errores de parsing
        if (result.Errors.Count > 0)
        {
            Console.WriteLine("❌ Errores de sintaxis:");
            foreach (var error in result.Errors)
            {
                Console.WriteLine($"  Línea {error.LineNumber}: {error.Message}");
            }
            hasErrors = true;
        }

        // Validación semántica
        if (result.IsSuccess && result.Game != null)
        {
            var validation = result.Game.Validate();
            
            if (validation.Errors.Count > 0)
            {
                Console.WriteLine("❌ Errores semánticos:");
                foreach (var error in validation.Errors)
                {
                    Console.WriteLine($"  {error}");
                }
                hasErrors = true;
            }

            if (validation.Warnings.Count > 0)
            {
                Console.WriteLine("⚠️ Advertencias:");
                foreach (var warning in validation.Warnings)
                {
                    Console.WriteLine($"  {warning}");
                }
            }
        }

        if (!hasErrors)
        {
            Console.WriteLine("✅ Validación exitosa - no se encontraron errores");
            return 0;
        }

        return 1;
    }

    private async Task<int> TestCommand(string[] args)
    {
        Console.WriteLine("Ejecutando tests de comandos en español...");

        if (args.Length == 0)
            return ShowError("Uso: daad test <archivo.daad> [--interactive]");

        var inputFile = args[0];
        var interactive = args.Contains("--interactive");

        // Cargar y parsear el juego
        var parser = _serviceProvider.GetRequiredService<IGameParser>();
        var result = await parser.ParseFromFileAsync(inputFile);

        if (!result.IsSuccess)
        {
            Console.WriteLine("❌ No se puede testear - error de parsing");
            return 1;
        }

        var analyzer = _serviceProvider.GetRequiredService<ISpanishSyntaxAnalyzer>();
        var gameContext = CreateGameContextFromGame(result.Game!);

        if (interactive)
        {
            return await RunInteractiveTest(analyzer, gameContext);
        }
        else
        {
            return RunAutomaticTests(analyzer, gameContext);
        }
    }

    private async Task<int> RunInteractiveTest(ISpanishSyntaxAnalyzer analyzer, GameContext context)
    {
        Console.WriteLine("🎮 Modo interactivo - prueba comandos en español:");
        Console.WriteLine("Escribe comandos para probar (escribe 'salir' para terminar)");
        Console.WriteLine();

        while (true)
        {
            Console.Write("> ");
            var input = Console.ReadLine();
            
            if (string.IsNullOrEmpty(input) || input.ToLowerInvariant() == "salir")
                break;

            var result = analyzer.ParseCommand(input, context);
            
            if (result.IsSuccess)
            {
                Console.WriteLine($"✅ Comando interpretado:");
                Console.WriteLine($"   Tipo: {result.Command!.Type}");
                Console.WriteLine($"   Verbo: {result.Command.Verb}");
                Console.WriteLine($"   Objeto: {result.Command.DirectObject}");
                Console.WriteLine($"   Confianza: {result.ConfidenceScore:F2}");
            }
            else
            {
                Console.WriteLine($"❌ No se pudo interpretar:");
                foreach (var error in result.Errors)
                {
                    Console.WriteLine($"   {error}");
                }
                
                if (result.Suggestions.Count > 0)
                {
                    Console.WriteLine("💡 Sugerencias:");
                    foreach (var suggestion in result.Suggestions)
                    {
                        Console.WriteLine($"   {suggestion}");
                    }
                }
            }
            Console.WriteLine();
        }

        return 0;
    }

    private async Task<int> NewProjectCommand(string[] args)
    {
        if (args.Length == 0)
            return ShowError("Uso: daad new <nombre-proyecto>");

        var projectName = args[0];
        var projectDir = Path.Combine(Directory.GetCurrentDirectory(), projectName);

        if (Directory.Exists(projectDir))
        {
            return ShowError($"El directorio '{projectName}' ya existe");
        }

        Console.WriteLine($"Creando nuevo proyecto: {projectName}");
        
        Directory.CreateDirectory(projectDir);

        // Crear archivo principal de la aventura
        var mainFile = Path.Combine(projectDir, $"{projectName}.daad");
        var templateContent = GenerateProjectTemplate(projectName);
        await File.WriteAllTextAsync(mainFile, templateContent);

        // Crear README
        var readmeFile = Path.Combine(projectDir, "README.md");
        var readmeContent = GenerateReadmeTemplate(projectName);
        await File.WriteAllTextAsync(readmeFile, readmeContent);

        Console.WriteLine($"✅ Proyecto creado en: {projectDir}");
        Console.WriteLine($"📝 Archivo principal: {mainFile}");
        Console.WriteLine($"🚀 Para empezar: cd {projectName} && daad parse {projectName}.daad");

        return 0;
    }

    private string GenerateProjectTemplate(string projectName)
    {
        return $"""
            # Aventura: {projectName}
            # Creada con DAAD Modernizado

            game {{
              title: "{projectName}"
              author: "Tu Nombre"
              start: inicio
              max_score: 100
              version: "1.0"
            }}

            # Localidades de tu aventura
            location inicio {{
              desc: "Te encuentras en el punto de partida de tu aventura."
              exits: {{ norte: salon }}
              objects: [llave_misteriosa]
            }}

            location salon {{
              desc: "Un elegante salón con muebles antiguos."
              exits: {{ sur: inicio }}
            }}

            # Objetos del juego
            object llave_misteriosa {{
              name: "llave misteriosa"
              desc: "Una llave antigua con grabados extraños."
              location: inicio
              takeable: true
              weight: 1
            }}

            # Mensajes del juego
            messages {{
              bienvenida: "¡Bienvenido a {projectName}!"
              victoria: "¡Has completado la aventura!"
              derrota: "¡La aventura ha terminado!"
            }}

            # Respuestas a comandos del jugador
            responses {{
              on "mirar llave" {{
                require: present(llave_misteriosa)
                do: {{
                  message("La llave brilla débilmente bajo la luz.")
                }}
              }}

              on ["coger llave", "tomar llave"] {{
                require: present(llave_misteriosa) && !carried(llave_misteriosa)
                do: {{
                  take(llave_misteriosa)
                  message("Coges la llave misteriosa.")
                  add_score(10)
                }}
              }}
            }}
            """;
    }

    private string GenerateReadmeTemplate(string projectName)
    {
        return $"""
            # {projectName}

            Una aventura conversacional creada con DAAD Modernizado.

            ## Desarrollo

            Para trabajar en esta aventura:

            ```bash
            # Parsear y validar
            daad parse {projectName}.daad

            # Probar comandos interactivamente
            daad test {projectName}.daad --interactive

            # Transpilar a DAAD clásico
            daad transpile {projectName}.daad

            # Validar código
            daad validate {projectName}.daad
            ```

            ## Estructura del Proyecto

            - `{projectName}.daad` - Archivo principal de la aventura
            - `README.md` - Este archivo

            ## Documentación

            Consulta la documentación de DAAD Modernizado para más información sobre:
            - Sintaxis del lenguaje
            - Comandos disponibles
            - Mejores prácticas para aventuras
            """;
    }

    // Métodos auxiliares
    private string? GetOption(string[] args, string optionName)
    {
        var option = args.FirstOrDefault(arg => arg.StartsWith($"{optionName}="));
        return option?.Substring(optionName.Length + 1);
    }

    private int ShowError(string message)
    {
        Console.WriteLine($"❌ {message}");
        return 1;
    }

    private int ShowHelp()
    {
        Console.WriteLine("""
            DAAD Modernizado - Sistema de Aventuras Conversacionales

            Uso: daad <comando> [opciones]

            Comandos:
              parse <archivo>     Parsear archivo DAAD modernizado
              transpile <archivo> Transpilar a DAAD clásico  
              validate <archivo>  Validar sintaxis y semántica
              test <archivo>      Probar analizador de español
              new <proyecto>      Crear nuevo proyecto
              help               Mostrar esta ayuda

            Ejemplos:
              daad new mi-aventura
              daad parse mi-aventura.daad
              daad test mi-aventura.daad --interactive
              daad transpile mi-aventura.daad --optimize

            Para más información: https://github.com/daad-modernizado
            """);
        return 0;
    }

    private void ShowParseStatistics(ParseResult<ModernDaadGame> result)
    {
        var game = result.Game!;
        Console.WriteLine($"""
            📊 Estadísticas:
              Localidades: {game.Locations.Count}
              Objetos: {game.Objects.Count}
              Mensajes: {game.Messages.Count}
              Respuestas: {game.Responses.Count}
              Procesos: {game.Processes.Count}
            """);
    }

    private void ShowTranspileStatistics(TranspileResult result)
    {
        var stats = result.Statistics;
        Console.WriteLine($"""
            📊 Estadísticas de transpilación:
              Localidades: {stats.LocationsCount}
              Objetos: {stats.ObjectsCount}
              Mensajes: {stats.MessagesCount}
              Respuestas: {stats.ResponsesCount}
              Vocabulario: {stats.VocabularySize} palabras
            """);
    }

    private GameContext CreateGameContextFromGame(ModernDaadGame game)
    {
        var context = new GameContext();
        
        foreach (var obj in game.Objects.Values)
        {
            context.AddObject(new GameObject
            {
                Id = obj.Id,
                Name = obj.Name,
                IsVisible = true,
                IsPresent = !string.IsNullOrEmpty(obj.Location)
            });
        }

        return context;
    }

    private int RunAutomaticTests(ISpanishSyntaxAnalyzer analyzer, GameContext context)
    {
        // Tests automáticos básicos
        var testCommands = new[]
        {
            "mirar",
            "inventario", 
            "norte",
            "coger todo",
            "usar llave en puerta"
        };

        var passCount = 0;
        
        Console.WriteLine("Ejecutando tests automáticos...");
        
        foreach (var command in testCommands)
        {
            var result = analyzer.ParseCommand(command, context);
            var status = result.IsSuccess ? "✅" : "❌";
            Console.WriteLine($"{status} '{command}' - Confianza: {result.ConfidenceScore:F2}");
            
            if (result.IsSuccess) passCount++;
        }

        Console.WriteLine($"\nResultado: {passCount}/{testCommands.Length} tests pasaron");
        return passCount == testCommands.Length ? 0 : 1;
    }
}
```

Con esta implementación completamos los componentes fundamentales del sistema DAAD Modernizado. Hemos cubierto desde la arquitectura base hasta las herramientas de desarrollo, proporcionando un framework robusto para crear aventuras conversacionales modernas mientras mantenemos compatibilidad con el ecosistema DAAD clásico.

La clave del éxito en este proyecto radica en entender que no estamos simplemente construyendo un compilador, sino creando un puente entre la rica tradición de las aventuras conversacionales en español y las posibilidades que ofrecen las herramientas de desarrollo modernas. Cada componente ha sido diseñado pensando tanto en la expresividad del español como en la usabilidad para desarrolladores contemporáneos.

