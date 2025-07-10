# Sistema Parser DAAD Modernizado - Parte 5: Guía de Implementación

## Parte 5.2: Implementación del Parser de Secciones (3D3) - Componente Prioritario

### 5.2.1 Arquitectura del Parser de Secciones

El Parser de Secciones es el cerebro del sistema que convierte tokens en estructuras de datos del modelo. Debe manejar múltiples tipos de secciones con sintaxis diferentes pero manteniendo una interfaz coherente.

```csharp
// SectionParser/ISectionParser.cs
namespace DaadModernizado.Parser.Sections;

public interface ISectionParser
{
    string SectionName { get; }
    bool CanParse(string sectionName);
    Task<ParseSectionResult> ParseAsync(TokenStream tokens, ParseContext context);
    ParseSectionResult Parse(TokenStream tokens, ParseContext context);
}

// SectionParser/ParseSectionResult.cs
public record ParseSectionResult
{
    public bool IsSuccess { get; init; }
    public object? SectionData { get; init; }
    public List<ParseError> Errors { get; init; } = new();
    public List<ParseWarning> Warnings { get; init; } = new();
    public Dictionary<string, object> Metadata { get; init; } = new();
}
```

### 5.2.2 TokenStream - Manejo Inteligente de Tokens

Crear una abstracción que facilite el consumo de tokens con lookahead y backtracking:

```csharp
// SectionParser/TokenStream.cs
namespace DaadModernizado.Parser.Sections;

public class TokenStream
{
    private readonly List<Token> _tokens;
    private int _position;
    private readonly Stack<int> _positions = new();

    public TokenStream(List<Token> tokens)
    {
        _tokens = tokens;
        _position = 0;
    }

    public Token Current => _position < _tokens.Count ? _tokens[_position] : Token.EndOfFile;
    public Token Peek(int offset = 1) => _position + offset < _tokens.Count ? _tokens[_position + offset] : Token.EndOfFile;
    public bool IsAtEnd => _position >= _tokens.Count;
    public int Position => _position;

    public Token Advance()
    {
        var current = Current;
        if (!IsAtEnd) _position++;
        return current;
    }

    public bool Match(TokenType type) => Current.Type == type;
    public bool Match(params TokenType[] types) => types.Contains(Current.Type);

    public Token Consume(TokenType expected, string errorMessage = "")
    {
        if (Current.Type == expected)
            return Advance();
        
        throw new ParseException(
            string.IsNullOrEmpty(errorMessage) 
                ? $"Se esperaba {expected} pero se encontró {Current.Type}"
                : errorMessage,
            Current.LineNumber);
    }

    public bool TryConsume(TokenType type, out Token token)
    {
        token = Current;
        if (Current.Type == type)
        {
            Advance();
            return true;
        }
        return false;
    }

    // Backtracking support
    public void SavePosition() => _positions.Push(_position);
    public void RestorePosition() => _position = _positions.Pop();
    public void DiscardPosition() => _positions.Pop();
}
```

### 5.2.3 Parser Base para Secciones Simples

Implementar un parser base que maneje la sintaxis común de propiedades:

```csharp
// SectionParser/BaseSectionParser.cs
namespace DaadModernizado.Parser.Sections;

public abstract class BaseSectionParser : ISectionParser
{
    protected readonly ILogger<BaseSectionParser> _logger;

    protected BaseSectionParser(ILogger<BaseSectionParser> logger)
    {
        _logger = logger;
    }

    public abstract string SectionName { get; }
    public virtual bool CanParse(string sectionName) => 
        string.Equals(sectionName, SectionName, StringComparison.OrdinalIgnoreCase);

    public virtual async Task<ParseSectionResult> ParseAsync(TokenStream tokens, ParseContext context)
    {
        return await Task.Run(() => Parse(tokens, context));
    }

    public abstract ParseSectionResult Parse(TokenStream tokens, ParseContext context);

    // Métodos de utilidad para parsing común
    protected virtual Dictionary<string, object> ParsePropertyBlock(TokenStream tokens)
    {
        var properties = new Dictionary<string, object>();
        
        tokens.Consume(TokenType.LeftBrace, "Se esperaba '{' al inicio del bloque de propiedades");

        while (!tokens.IsAtEnd && !tokens.Match(TokenType.RightBrace))
        {
            if (tokens.Match(TokenType.Identifier))
            {
                var propertyName = tokens.Advance().Value;
                tokens.Consume(TokenType.Colon, $"Se esperaba ':' después del nombre de propiedad '{propertyName}'");
                
                var value = ParsePropertyValue(tokens);
                properties[propertyName] = value;

                // Consumir coma opcional
                tokens.TryConsume(TokenType.Comma, out _);
            }
            else
            {
                throw new ParseException($"Se esperaba nombre de propiedad, se encontró {tokens.Current.Type}", tokens.Current.LineNumber);
            }
        }

        tokens.Consume(TokenType.RightBrace, "Se esperaba '}' al final del bloque de propiedades");
        return properties;
    }

    protected virtual object ParsePropertyValue(TokenStream tokens)
    {
        return tokens.Current.Type switch
        {
            TokenType.StringLiteral => tokens.Advance().Value.Trim('"'),
            TokenType.NumberLiteral => int.Parse(tokens.Advance().Value),
            TokenType.BooleanLiteral => ParseBoolean(tokens.Advance().Value),
            TokenType.Identifier => tokens.Advance().Value,
            TokenType.LeftBrace => ParseObjectValue(tokens),
            TokenType.LeftBracket => ParseArrayValue(tokens),
            _ => throw new ParseException($"Valor de propiedad inesperado: {tokens.Current.Type}", tokens.Current.LineNumber)
        };
    }

    protected virtual Dictionary<string, object> ParseObjectValue(TokenStream tokens)
    {
        return ParsePropertyBlock(tokens);
    }

    protected virtual List<object> ParseArrayValue(TokenStream tokens)
    {
        var items = new List<object>();
        tokens.Consume(TokenType.LeftBracket);

        while (!tokens.IsAtEnd && !tokens.Match(TokenType.RightBracket))
        {
            items.Add(ParsePropertyValue(tokens));
            
            if (!tokens.TryConsume(TokenType.Comma, out _) && !tokens.Match(TokenType.RightBracket))
            {
                throw new ParseException("Se esperaba ',' o ']' en lista", tokens.Current.LineNumber);
            }
        }

        tokens.Consume(TokenType.RightBracket);
        return items;
    }

    protected static bool ParseBoolean(string value)
    {
        return value.ToLowerInvariant() switch
        {
            "true" or "verdadero" or "sí" or "si" => true,
            "false" or "falso" or "no" => false,
            _ => throw new ArgumentException($"Valor booleano no reconocido: {value}")
        };
    }
}
```

### 5.2.4 Parser de Sección Game

Implementar el parser más simple como ejemplo:

```csharp
// SectionParser/GameSectionParser.cs
namespace DaadModernizado.Parser.Sections;

public class GameSectionParser : BaseSectionParser
{
    public override string SectionName => "game";

    public GameSectionParser(ILogger<GameSectionParser> logger) : base(logger) { }

    public override ParseSectionResult Parse(TokenStream tokens, ParseContext context)
    {
        try
        {
            _logger.LogParsingStarted("sección game");

            var properties = ParsePropertyBlock(tokens);
            var metadata = CreateGameMetadata(properties);

            _logger.LogInformation("Sección game parseada exitosamente con {PropertyCount} propiedades", properties.Count);

            return new ParseSectionResult
            {
                IsSuccess = true,
                SectionData = metadata
            };
        }
        catch (ParseException ex)
        {
            _logger.LogParsingError(ex.LineNumber, ex.Message);
            return new ParseSectionResult
            {
                IsSuccess = false,
                Errors = { new ParseError(ex.LineNumber, ex.Message, "game") }
            };
        }
    }

    private GameMetadata CreateGameMetadata(Dictionary<string, object> properties)
    {
        var metadata = new GameMetadata();

        foreach (var (key, value) in properties)
        {
            switch (key.ToLowerInvariant())
            {
                case "title":
                    metadata.Title = value.ToString() ?? "";
                    break;
                case "author":
                    metadata.Author = value.ToString() ?? "";
                    break;
                case "start":
                    metadata.StartLocation = value.ToString() ?? "";
                    break;
                case "max_score":
                    if (value is int score) metadata.MaxScore = score;
                    break;
                case "version":
                    metadata.Version = value.ToString() ?? "";
                    break;
                case "language":
                    metadata.Language = value.ToString() ?? "es";
                    break;
                default:
                    // Propiedad no reconocida, añadir a custom properties
                    metadata.CustomProperties[key] = value;
                    break;
            }
        }

        return metadata;
    }
}
```

### 5.2.5 Parser de Sección Vocabulary

Manejar extensiones de vocabulario personalizado:

```csharp
// SectionParser/VocabSectionParser.cs
namespace DaadModernizado.Parser.Sections;

public class VocabSectionParser : BaseSectionParser
{
    private readonly ISpanishVocabularyService _vocabularyService;

    public override string SectionName => "vocab";

    public VocabSectionParser(ISpanishVocabularyService vocabularyService, ILogger<VocabSectionParser> logger) 
        : base(logger)
    {
        _vocabularyService = vocabularyService;
    }

    public override ParseSectionResult Parse(TokenStream tokens, ParseContext context)
    {
        try
        {
            var properties = ParsePropertyBlock(tokens);
            var vocabulary = CreateVocabulary(properties);

            return new ParseSectionResult
            {
                IsSuccess = true,
                SectionData = vocabulary
            };
        }
        catch (ParseException ex)
        {
            return new ParseSectionResult
            {
                IsSuccess = false,
                Errors = { new ParseError(ex.LineNumber, ex.Message, "vocab") }
            };
        }
    }

    private ModernVocabulary CreateVocabulary(Dictionary<string, object> properties)
    {
        var vocabulary = new ModernVocabulary();

        foreach (var (category, value) in properties)
        {
            if (value is Dictionary<string, object> wordMap)
            {
                ProcessWordCategory(vocabulary, category, wordMap);
            }
        }

        return vocabulary;
    }

    private void ProcessWordCategory(ModernVocabulary vocabulary, string category, Dictionary<string, object> wordMap)
    {
        switch (category.ToLowerInvariant())
        {
            case "verbs":
                foreach (var (word, id) in wordMap)
                {
                    if (id is int verbId)
                        vocabulary.Verbs[word] = verbId;
                }
                break;

            case "nouns":
                foreach (var (word, id) in wordMap)
                {
                    if (id is int nounId)
                        vocabulary.Nouns[word] = nounId;
                }
                break;

            case "adjectives":
                foreach (var (word, id) in wordMap)
                {
                    if (id is int adjId)
                        vocabulary.Adjectives[word] = adjId;
                }
                break;

            case "prepositions":
                foreach (var (word, id) in wordMap)
                {
                    if (id is int prepId)
                        vocabulary.Prepositions[word] = prepId;
                }
                break;

            case "directions":
                foreach (var (word, id) in wordMap)
                {
                    if (id is int dirId)
                        vocabulary.Directions[word] = dirId;
                }
                break;

            case "synonyms":
                foreach (var (word, synonym) in wordMap)
                {
                    if (synonym is string synonymStr)
                        vocabulary.Synonyms[word] = synonymStr;
                }
                break;

            default:
                _logger.LogWarning("Categoría de vocabulario no reconocida: {Category}", category);
                break;
        }
    }
}
```

### 5.2.6 Parser de Secciones de Mundo (Locations)

Manejar definiciones de localidades con propiedades complejas:

```csharp
// SectionParser/LocationSectionParser.cs
namespace DaadModernizado.Parser.Sections;

public class LocationSectionParser : BaseSectionParser
{
    public override string SectionName => "location";

    public LocationSectionParser(ILogger<LocationSectionParser> logger) : base(logger) { }

    public override ParseSectionResult Parse(TokenStream tokens, ParseContext context)
    {
        try
        {
            // Esperar: location identifier { ... }
            var locationId = tokens.Consume(TokenType.Identifier, "Se esperaba identificador de localidad").Value;
            var properties = ParsePropertyBlock(tokens);
            var location = CreateLocation(locationId, properties);

            return new ParseSectionResult
            {
                IsSuccess = true,
                SectionData = new KeyValuePair<string, ModernLocation>(locationId, location)
            };
        }
        catch (ParseException ex)
        {
            return new ParseSectionResult
            {
                IsSuccess = false,
                Errors = { new ParseError(ex.LineNumber, ex.Message, "location") }
            };
        }
    }

    private ModernLocation CreateLocation(string id, Dictionary<string, object> properties)
    {
        var location = new ModernLocation
        {
            Id = id,
            Name = id // Default name
        };

        foreach (var (key, value) in properties)
        {
            switch (key.ToLowerInvariant())
            {
                case "desc":
                case "description":
                    location.Description = value.ToString() ?? "";
                    break;

                case "name":
                    location.Name = value.ToString() ?? id;
                    break;

                case "exits":
                    if (value is Dictionary<string, object> exitsMap)
                        location.Exits = ProcessExits(exitsMap);
                    break;

                case "objects":
                    if (value is List<object> objectsList)
                        location.Objects = ProcessObjects(objectsList);
                    break;

                case "flags":
                    if (value is List<object> flagsList)
                        location.Flags = ProcessFlags(flagsList);
                    break;

                default:
                    location.CustomProperties[key] = value;
                    break;
            }
        }

        return location;
    }

    private Dictionary<string, string> ProcessExits(Dictionary<string, object> exitsMap)
    {
        var exits = new Dictionary<string, string>();
        
        foreach (var (direction, destination) in exitsMap)
        {
            exits[direction] = destination.ToString() ?? "";
        }

        return exits;
    }

    private List<string> ProcessObjects(List<object> objectsList)
    {
        return objectsList.Select(obj => obj.ToString() ?? "").ToList();
    }

    private List<string> ProcessFlags(List<object> flagsList)
    {
        return flagsList.Select(flag => flag.ToString() ?? "").ToList();
    }
}
```

### 5.2.7 Registro y Coordinación de Parsers

Implementar un sistema que coordine múltiples parsers de sección:

```csharp
// SectionParser/SectionParserRegistry.cs
namespace DaadModernizado.Parser.Sections;

public interface ISectionParserRegistry
{
    void RegisterParser(ISectionParser parser);
    ISectionParser? GetParser(string sectionName);
    IEnumerable<ISectionParser> GetAllParsers();
}

public class SectionParserRegistry : ISectionParserRegistry
{
    private readonly Dictionary<string, ISectionParser> _parsers = new();
    private readonly ILogger<SectionParserRegistry> _logger;

    public SectionParserRegistry(ILogger<SectionParserRegistry> logger)
    {
        _logger = logger;
    }

    public void RegisterParser(ISectionParser parser)
    {
        var sectionName = parser.SectionName.ToLowerInvariant();
        
        if (_parsers.ContainsKey(sectionName))
        {
            _logger.LogWarning("Reemplazando parser existente para sección '{SectionName}'", sectionName);
        }

        _parsers[sectionName] = parser;
        _logger.LogInformation("Parser registrado para sección '{SectionName}'", sectionName);
    }

    public ISectionParser? GetParser(string sectionName)
    {
        return _parsers.GetValueOrDefault(sectionName.ToLowerInvariant());
    }

    public IEnumerable<ISectionParser> GetAllParsers()
    {
        return _parsers.Values;
    }
}

// Extension para DI
public static class SectionParserServiceExtensions
{
    public static IServiceCollection AddSectionParsers(this IServiceCollection services)
    {
        services.AddSingleton<ISectionParserRegistry, SectionParserRegistry>();
        
        // Registrar parsers específicos
        services.AddTransient<GameSectionParser>();
        services.AddTransient<VocabSectionParser>();
        services.AddTransient<LocationSectionParser>();
        services.AddTransient<ObjectSectionParser>();
        services.AddTransient<MessagesSectionParser>();
        
        // Configurar el registry
        services.AddSingleton<ISectionParserRegistry>(provider =>
        {
            var registry = new SectionParserRegistry(provider.GetRequiredService<ILogger<SectionParserRegistry>>());
            
            registry.RegisterParser(provider.GetRequiredService<GameSectionParser>());
            registry.RegisterParser(provider.GetRequiredService<VocabSectionParser>());
            registry.RegisterParser(provider.GetRequiredService<LocationSectionParser>());
            registry.RegisterParser(provider.GetRequiredService<ObjectSectionParser>());
            registry.RegisterParser(provider.GetRequiredService<MessagesSectionParser>());
            
            return registry;
        });

        return services;
    }
}
```

### 5.2.8 Parser Principal de Archivo

Orquestar el parsing completo de un archivo DAAD:

```csharp
// MainGameParser.cs
namespace DaadModernizado.Parser;

public class MainGameParser : IGameParser
{
    private readonly ILexicalAnalyzer _lexer;
    private readonly ISectionParserRegistry _parserRegistry;
    private readonly ILogger<MainGameParser> _logger;

    public MainGameParser(
        ILexicalAnalyzer lexer,
        ISectionParserRegistry parserRegistry,
        ILogger<MainGameParser> logger)
    {
        _lexer = lexer;
        _parserRegistry = parserRegistry;
        _logger = logger;
    }

    public async Task<ParseResult<ModernDaadGame>> ParseFromFileAsync(string filePath, CancellationToken cancellationToken = default)
    {
        var content = await File.ReadAllTextAsync(filePath, cancellationToken);
        return await ParseAsync(content, cancellationToken);
    }

    public ParseResult<ModernDaadGame> ParseFromFile(string filePath)
    {
        var content = File.ReadAllText(filePath);
        return Parse(content);
    }

    public async Task<ParseResult<ModernDaadGame>> ParseAsync(string input, CancellationToken cancellationToken = default)
    {
        return await Task.Run(() => Parse(input), cancellationToken);
    }

    public ParseResult<ModernDaadGame> Parse(string input)
    {
        var stopwatch = Stopwatch.StartNew();
        var result = new ParseResult<ModernDaadGame>();

        try
        {
            // Fase 1: Análisis léxico
            var tokenResult = _lexer.Tokenize(input);
            if (!tokenResult.IsSuccess)
            {
                result.Errors.AddRange(tokenResult.Errors);
                return result;
            }

            var tokens = new TokenStream(tokenResult.Tokens);
            var game = new ModernDaadGame();
            var context = new ParseContext();

            // Fase 2: Parsing de secciones
            while (!tokens.IsAtEnd)
            {
                var sectionResult = ParseSection(tokens, context);
                
                if (!sectionResult.IsSuccess)
                {
                    result.Errors.AddRange(sectionResult.Errors);
                    result.Warnings.AddRange(sectionResult.Warnings);
                    continue;
                }

                ApplySectionToGame(game, sectionResult);
            }

            // Fase 3: Validación post-parsing
            var validation = game.Validate();
            result.Warnings.AddRange(validation.Warnings.Select(w => new ParseWarning(0, w, "")));
            
            if (validation.Errors.Count > 0)
            {
                result.Errors.AddRange(validation.Errors.Select(e => new ParseError(0, e, "validation")));
            }

            result.Game = game;
            result.IsSuccess = result.Errors.Count == 0;

            stopwatch.Stop();
            _logger.LogParsingCompleted(tokenResult.Tokens.Count, stopwatch.ElapsedMilliseconds);

            return result;
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Error inesperado durante el parsing");
            result.Errors.Add(new ParseError(0, $"Error inesperado: {ex.Message}", "system"));
            return result;
        }
    }

    private ParseSectionResult ParseSection(TokenStream tokens, ParseContext context)
    {
        var sectionNameToken = tokens.Consume(TokenType.Identifier, "Se esperaba nombre de sección");
        var sectionName = sectionNameToken.Value;

        var parser = _parserRegistry.GetParser(sectionName);
        if (parser == null)
        {
            throw new ParseException($"Sección no reconocida: '{sectionName}'", sectionNameToken.LineNumber);
        }

        return parser.Parse(tokens, context);
    }

    private void ApplySectionToGame(ModernDaadGame game, ParseSectionResult sectionResult)
    {
        switch (sectionResult.SectionData)
        {
            case GameMetadata metadata:
                game.Metadata = metadata;
                break;

            case ModernVocabulary vocabulary:
                game.Vocabulary = vocabulary;
                break;

            case KeyValuePair<string, ModernLocation> locationPair:
                game.Locations[locationPair.Key] = locationPair.Value;
                break;

            case KeyValuePair<string, ModernObject> objectPair:
                game.Objects[objectPair.Key] = objectPair.Value;
                break;

            case Dictionary<string, string> messages:
                foreach (var (key, value) in messages)
                    game.Messages[key] = value;
                break;

            default:
                _logger.LogWarning("Tipo de sección no manejado: {Type}", sectionResult.SectionData?.GetType().Name);
                break;
        }
    }
}
```

### 5.2.9 Testing del Parser de Secciones

Implementar tests comprehensivos:

```csharp
// Tests/SectionParserTests.cs
namespace DaadModernizado.Parser.Tests;

public class SectionParserTests : ParserTestBase
{
    private readonly GameSectionParser _gameParser;
    private readonly LocationSectionParser _locationParser;

    public SectionParserTests(ITestOutputHelper output) : base(output)
    {
        _gameParser = GetService<GameSectionParser>();
        _locationParser = GetService<LocationSectionParser>();
    }

    [Fact]
    public void GameSection_BasicProperties_ParsesCorrectly()
    {
        // Arrange
        var input = """
            {
              title: "Mi Aventura"
              author: "Desarrollador Test"
              start: "bosque"
              max_score: 100
            }
            """;

        var tokens = CreateTokenStream(input);

        // Act
        var result = _gameParser.Parse(tokens, new ParseContext());

        // Assert
        Assert.True(result.IsSuccess);
        Assert.IsType<GameMetadata>(result.SectionData);
        
        var metadata = (GameMetadata)result.SectionData!;
        Assert.Equal("Mi Aventura", metadata.Title);
        Assert.Equal("Desarrollador Test", metadata.Author);
        Assert.Equal("bosque", metadata.StartLocation);
        Assert.Equal(100, metadata.MaxScore);
    }

    [Fact]
    public void LocationSection_WithExitsAndObjects_ParsesCorrectly()
    {
        // Arrange
        var input = """
            bosque_encantado {
              desc: "Un bosque místico lleno de magia"
              exits: { norte: claro, sur: cueva }
              objects: [espada, llave]
            }
            """;

        var tokens = CreateTokenStream(input);

        // Act
        var result = _locationParser.Parse(tokens, new ParseContext());

        // Assert
        Assert.True(result.IsSuccess);
        var locationPair = (KeyValuePair<string, ModernLocation>)result.SectionData!;
        var location = locationPair.Value;
        
        Assert.Equal("bosque_encantado", location.Id);
        Assert.Equal("Un bosque místico lleno de magia", location.Description);
        Assert.Contains("norte", location.Exits.Keys);
        Assert.Equal("claro", location.Exits["norte"]);
        Assert.Contains("espada", location.Objects);
    }

    private TokenStream CreateTokenStream(string input)
    {
        var lexer = GetService<ILexicalAnalyzer>();
        var tokenResult = lexer.Tokenize(input);
        return new TokenStream(tokenResult.Tokens);
    }
}
```

Esta implementación del Parser de Secciones proporciona una base sólida y extensible que maneja las secciones más comunes del lenguaje DAAD Modernizado. En la siguiente parte (5.3) abordaremos el **Parser de Condiciones y Acciones (3D4)**, que maneja la lógica compleja del sistema.