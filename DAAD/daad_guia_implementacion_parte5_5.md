# Sistema Parser DAAD Modernizado - Parte 5: Guía de Implementación

## Parte 5.5: Implementación del Analizador Sintáctico Español (3D6) - Componente Importante

### 5.5.1 Filosofía y Desafíos del Procesamiento de Español Natural

El Analizador Sintáctico Español representa el punto donde nuestro trabajo técnico se convierte en experiencia humana. A diferencia de otros componentes que procesan código escrito por desarrolladores que están dispuestos a aprender sintaxis específica, este componente debe entender a usuarios finales que esperan escribir español natural y ser comprendidos inmediatamente.

Piensa en este componente como un traductor universal que debe entender no solo las palabras que escribe el jugador, sino también sus intenciones, el contexto del juego, y las múltiples formas en que el español permite expresar la misma idea. Es como tener una conversación donde una persona habla de manera formal y la otra responde de manera coloquial, pero ambas se entienden perfectamente.

```csharp
// Spanish/ISpanishSyntaxAnalyzer.cs
namespace DaadModernizado.Spanish;

public interface ISpanishSyntaxAnalyzer
{
    Task<CommandParseResult> ParseCommandAsync(string userInput, GameContext context, CancellationToken cancellationToken = default);
    CommandParseResult ParseCommand(string userInput, GameContext context);
    List<string> SuggestAlternatives(string userInput, GameContext context);
    bool IsValidCommand(string userInput, GameContext context);
}

// Spanish/CommandParseResult.cs
public record CommandParseResult
{
    public bool IsSuccess { get; init; }
    public ParsedCommand? Command { get; init; }
    public List<string> Errors { get; init; } = new();
    public List<string> Suggestions { get; init; } = new();
    public float ConfidenceScore { get; init; } // 0.0 a 1.0
    public Dictionary<string, object> DebugInfo { get; init; } = new();
}

// Spanish/ParsedCommand.cs
public record ParsedCommand
{
    public CommandType Type { get; init; }
    public string Verb { get; init; } = "";
    public string DirectObject { get; init; } = "";
    public string IndirectObject { get; init; } = "";
    public string Preposition { get; init; } = "";
    public string Direction { get; init; } = "";
    public List<string> Adjectives { get; init; } = new();
    public string OriginalInput { get; init; } = "";
    public Dictionary<string, string> ResolvedReferences { get; init; } = new();
}

public enum CommandType
{
    Movement,      // ir norte, norte
    Examination,   // mirar espada, examinar cofre
    Manipulation,  // coger llave, usar espada
    Communication, // hablar con mago, preguntar sobre tesoro
    System,        // inventario, puntuación, guardar
    Complex        // usar llave en puerta, poner libro sobre mesa
}
```

### 5.5.2 Arquitectura del Pipeline de Procesamiento

El analizador utiliza un pipeline de múltiples etapas que procesa gradualmente el texto del usuario, desde la normalización básica hasta la resolución semántica completa. Cada etapa tiene una responsabilidad específica y puede operar independientemente, lo que facilita el testing y la optimización individual.

```csharp
// Spanish/SpanishSyntaxAnalyzer.cs
namespace DaadModernizado.Spanish;

public class SpanishSyntaxAnalyzer : ISpanishSyntaxAnalyzer
{
    private readonly ISpanishVocabularyService _vocabulary;
    private readonly ILogger<SpanishSyntaxAnalyzer> _logger;
    private readonly SpanishNormalizer _normalizer;
    private readonly CommandClassifier _classifier;
    private readonly ReferenceResolver _referenceResolver;
    private readonly AmbiguityResolver _ambiguityResolver;

    public SpanishSyntaxAnalyzer(
        ISpanishVocabularyService vocabulary,
        ILogger<SpanishSyntaxAnalyzer> logger)
    {
        _vocabulary = vocabulary;
        _logger = logger;
        
        // Inicializar componentes del pipeline
        // Cada uno se especializa en una tarea específica del procesamiento
        _normalizer = new SpanishNormalizer(vocabulary, logger);
        _classifier = new CommandClassifier(vocabulary, logger);
        _referenceResolver = new ReferenceResolver(logger);
        _ambiguityResolver = new AmbiguityResolver(vocabulary, logger);
    }

    public async Task<CommandParseResult> ParseCommandAsync(string userInput, GameContext context, CancellationToken cancellationToken = default)
    {
        return await Task.Run(() => ParseCommand(userInput, context), cancellationToken);
    }

    public CommandParseResult ParseCommand(string userInput, GameContext context)
    {
        var stopwatch = Stopwatch.StartNew();
        
        try
        {
            _logger.LogInformation("Procesando comando: '{UserInput}'", userInput);

            // Fase 1: Normalización del texto de entrada
            // Corregir errores comunes, normalizar acentos, filtrar palabras vacías
            var normalizedInput = _normalizer.Normalize(userInput);
            _logger.LogDebug("Texto normalizado: '{NormalizedInput}'", normalizedInput);

            // Fase 2: Tokenización inteligente para español
            // Separar palabras considerando contracciones y clíticos
            var tokens = _normalizer.Tokenize(normalizedInput);
            _logger.LogDebug("Tokens: [{Tokens}]", string.Join(", ", tokens));

            // Fase 3: Clasificación del comando
            // Determinar tipo de comando y extraer componentes básicos
            var classification = _classifier.ClassifyCommand(tokens, context);
            _logger.LogDebug("Clasificación: {CommandType}", classification.Type);

            // Fase 4: Resolución de referencias
            // Convertir "la espada", "eso", "él" a objetos específicos del juego
            var resolvedCommand = _referenceResolver.ResolveReferences(classification, context);

            // Fase 5: Resolución de ambigüedades
            // Manejar casos donde múltiples interpretaciones son posibles
            var finalCommand = _ambiguityResolver.ResolveAmbiguities(resolvedCommand, context);

            // Calcular puntuación de confianza basada en qué tan bien se resolvió el comando
            var confidence = CalculateConfidence(finalCommand, tokens.Count);

            stopwatch.Stop();
            _logger.LogInformation("Comando procesado en {ElapsedMs}ms con confianza {Confidence:F2}", 
                stopwatch.ElapsedMilliseconds, confidence);

            return new CommandParseResult
            {
                IsSuccess = true,
                Command = finalCommand,
                ConfidenceScore = confidence,
                DebugInfo = new Dictionary<string, object>
                {
                    ["original_input"] = userInput,
                    ["normalized_input"] = normalizedInput,
                    ["tokens"] = tokens,
                    ["processing_time_ms"] = stopwatch.ElapsedMilliseconds
                }
            };
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Error procesando comando: '{UserInput}'", userInput);
            
            return new CommandParseResult
            {
                IsSuccess = false,
                Errors = { $"Error procesando comando: {ex.Message}" },
                Suggestions = SuggestAlternatives(userInput, context)
            };
        }
    }

    // Calcular qué tan seguro estamos de haber interpretado correctamente el comando
    private float CalculateConfidence(ParsedCommand command, int tokenCount)
    {
        float confidence = 0.5f; // Base confidence
        
        // Aumentar confianza si reconocimos el verbo principal
        if (!string.IsNullOrEmpty(command.Verb))
            confidence += 0.3f;
        
        // Aumentar si resolvimos referencias de objetos
        if (!string.IsNullOrEmpty(command.DirectObject))
            confidence += 0.2f;
        
        // Reducir si quedaron muchos tokens sin procesar
        var processedTokens = CountProcessedTokens(command);
        var processingRatio = (float)processedTokens / tokenCount;
        confidence *= processingRatio;

        return Math.Min(1.0f, confidence);
    }

    private int CountProcessedTokens(ParsedCommand command)
    {
        var count = 0;
        if (!string.IsNullOrEmpty(command.Verb)) count++;
        if (!string.IsNullOrEmpty(command.DirectObject)) count++;
        if (!string.IsNullOrEmpty(command.IndirectObject)) count++;
        if (!string.IsNullOrEmpty(command.Preposition)) count++;
        if (!string.IsNullOrEmpty(command.Direction)) count++;
        return count;
    }
}
```

### 5.5.3 Normalizador de Español - Limpieza Inteligente

El normalizador maneja las peculiaridades del español que pueden confundir a un parser simple. Su trabajo es convertir la entrada variada del usuario en una forma canónica que el resto del sistema puede procesar de manera consistente.

```csharp
// Spanish/SpanishNormalizer.cs
namespace DaadModernizado.Spanish;

public class SpanishNormalizer
{
    private readonly ISpanishVocabularyService _vocabulary;
    private readonly ILogger _logger;
    
    // Palabras que no aportan significado semántico y pueden eliminarse
    private static readonly HashSet<string> StopWords = new(StringComparer.OrdinalIgnoreCase)
    {
        "el", "la", "los", "las", "un", "una", "unos", "unas",
        "al", "del", // contracciones
        "y", "o", "pero", "que", "se", "me", "te", "le", "lo", "la",
        "por", "para", "como", "muy", "más", "menos", "bien", "mal"
    };

    // Contracciones comunes en español que deben expandirse
    private static readonly Dictionary<string, string[]> Contractions = new(StringComparer.OrdinalIgnoreCase)
    {
        ["al"] = ["a", "el"],
        ["del"] = ["de", "el"],
        ["conmigo"] = ["con", "mí"],
        ["contigo"] = ["con", "ti"],
        ["consigo"] = ["con", "sí"]
    };

    public SpanishNormalizer(ISpanishVocabularyService vocabulary, ILogger logger)
    {
        _vocabulary = vocabulary;
        _logger = logger;
    }

    public string Normalize(string input)
    {
        if (string.IsNullOrWhiteSpace(input))
            return "";

        var text = input.Trim();
        
        // Paso 1: Convertir a minúsculas para consistencia
        text = text.ToLowerInvariant();
        
        // Paso 2: Normalizar acentos y caracteres especiales
        text = NormalizeAccents(text);
        
        // Paso 3: Limpiar puntuación innecesaria
        text = CleanPunctuation(text);
        
        // Paso 4: Normalizar espacios múltiples
        text = NormalizeWhitespace(text);

        _logger.LogDebug("Normalizado '{Original}' → '{Normalized}'", input, text);
        
        return text;
    }

    public List<string> Tokenize(string normalizedInput)
    {
        if (string.IsNullOrWhiteSpace(normalizedInput))
            return new List<string>();

        var words = normalizedInput.Split(' ', StringSplitOptions.RemoveEmptyEntries);
        var tokens = new List<string>();

        foreach (var word in words)
        {
            // Expandir contracciones antes de procesar
            if (Contractions.TryGetValue(word, out var expanded))
            {
                tokens.AddRange(expanded);
                _logger.LogDebug("Expandiendo contracción '{Word}' → [{Expanded}]", 
                    word, string.Join(", ", expanded));
            }
            else
            {
                tokens.Add(word);
            }
        }

        // Filtrar palabras vacías pero conservar información sobre su posición
        // Esto es importante para mantener el contexto sintáctico
        var filteredTokens = new List<string>();
        for (int i = 0; i < tokens.Count; i++)
        {
            var token = tokens[i];
            
            if (!StopWords.Contains(token))
            {
                filteredTokens.Add(token);
            }
            else
            {
                // Algunas palabras vacías pueden ser importantes en ciertos contextos
                // Por ejemplo, "en" en "poner libro en mesa"
                if (IsContextuallyImportant(token, tokens, i))
                {
                    filteredTokens.Add(token);
                    _logger.LogDebug("Preservando palabra vacía contextualmente importante: '{Token}'", token);
                }
            }
        }

        return filteredTokens;
    }

    private string NormalizeAccents(string text)
    {
        // Mapeo de caracteres acentuados a sus versiones básicas
        // Mantenemos ñ porque es distintiva en español
        return text
            .Replace("á", "a").Replace("à", "a")
            .Replace("é", "e").Replace("è", "e")
            .Replace("í", "i").Replace("ì", "i")
            .Replace("ó", "o").Replace("ò", "o")
            .Replace("ú", "u").Replace("ù", "u")
            .Replace("ü", "u");
    }

    private string CleanPunctuation(string text)
    {
        // Eliminar puntuación que no aporta significado
        // Pero conservar apóstrofes que pueden indicar contracciones
        var cleaned = new StringBuilder();
        
        foreach (char c in text)
        {
            if (char.IsLetterOrDigit(c) || char.IsWhiteSpace(c) || c == 'ñ' || c == '\'')
            {
                cleaned.Append(c);
            }
            else if (char.IsPunctuation(c))
            {
                // Convertir puntuación a espacios para separar palabras
                cleaned.Append(' ');
            }
        }
        
        return cleaned.ToString();
    }

    private string NormalizeWhitespace(string text)
    {
        // Reducir múltiples espacios a uno solo
        return System.Text.RegularExpressions.Regex.Replace(text, @"\s+", " ").Trim();
    }

    private bool IsContextuallyImportant(string token, List<string> allTokens, int position)
    {
        // Preposiciones son importantes cuando conectan objetos
        var prepositions = new HashSet<string> { "en", "con", "de", "sobre", "bajo", "dentro" };
        
        if (prepositions.Contains(token))
        {
            // Es importante si está entre dos sustantivos potenciales
            var hasPreviousNoun = position > 0 && CouldBeNoun(allTokens[position - 1]);
            var hasFollowingNoun = position < allTokens.Count - 1 && CouldBeNoun(allTokens[position + 1]);
            
            return hasPreviousNoun && hasFollowingNoun;
        }

        return false;
    }

    private bool CouldBeNoun(string word)
    {
        // Verificar si una palabra podría ser un sustantivo
        // Esto incluye tanto palabras del vocabulario como identificadores de objetos del juego
        return _vocabulary.IsNoun(word) || 
               char.IsLetter(word[0]); // Identificadores de objetos suelen empezar con letra
    }
}
```

### 5.5.4 Clasificador de Comandos - Reconocimiento de Patrones

El clasificador determina qué tipo de acción quiere realizar el jugador basándose en los patrones típicos del español para aventuras conversacionales.

```csharp
// Spanish/CommandClassifier.cs
namespace DaadModernizado.Spanish;

public class CommandClassifier
{
    private readonly ISpanishVocabularyService _vocabulary;
    private readonly ILogger _logger;

    // Patrones comunes para diferentes tipos de comandos
    private static readonly Dictionary<CommandType, List<string[]>> CommandPatterns = new()
    {
        [CommandType.Movement] = new List<string[]>
        {
            new[] { "ir", "norte" },     // ir norte
            new[] { "norte" },           // norte
            new[] { "caminar", "sur" },  // caminar sur
            new[] { "subir" },           // subir
            new[] { "bajar" }            // bajar
        },
        
        [CommandType.Examination] = new List<string[]>
        {
            new[] { "mirar", "*" },      // mirar objeto
            new[] { "examinar", "*" },   // examinar objeto
            new[] { "ver", "*" },        // ver objeto
            new[] { "leer", "*" }        // leer objeto
        },
        
        [CommandType.Manipulation] = new List<string[]>
        {
            new[] { "coger", "*" },      // coger objeto
            new[] { "tomar", "*" },      // tomar objeto
            new[] { "dejar", "*" },      // dejar objeto
            new[] { "usar", "*" },       // usar objeto
            new[] { "abrir", "*" },      // abrir objeto
            new[] { "cerrar", "*" }      // cerrar objeto
        },
        
        [CommandType.Complex] = new List<string[]>
        {
            new[] { "usar", "*", "en", "*" },        // usar llave en puerta
            new[] { "poner", "*", "sobre", "*" },    // poner libro sobre mesa
            new[] { "dar", "*", "a", "*" },          // dar moneda a comerciante
            new[] { "hablar", "con", "*" }           // hablar con personaje
        },
        
        [CommandType.System] = new List<string[]>
        {
            new[] { "inventario" },
            new[] { "puntuacion" },
            new[] { "guardar" },
            new[] { "cargar" },
            new[] { "ayuda" }
        }
    };

    public CommandClassifier(ISpanishVocabularyService vocabulary, ILogger logger)
    {
        _vocabulary = vocabulary;
        _logger = logger;
    }

    public ParsedCommand ClassifyCommand(List<string> tokens, GameContext context)
    {
        if (tokens.Count == 0)
        {
            return new ParsedCommand { Type = CommandType.System };
        }

        // Intentar cada tipo de comando en orden de especificidad
        // Los patrones más específicos (Complex) se prueban primero
        foreach (var commandType in new[] { CommandType.Complex, CommandType.System, 
                                          CommandType.Movement, CommandType.Examination, 
                                          CommandType.Manipulation })
        {
            var result = TryMatchCommandType(tokens, commandType, context);
            if (result != null)
            {
                _logger.LogDebug("Comando clasificado como {CommandType}", commandType);
                return result;
            }
        }

        // Si no coincide con ningún patrón conocido, intentar clasificación heurística
        return ClassifyByHeuristics(tokens, context);
    }

    private ParsedCommand? TryMatchCommandType(List<string> tokens, CommandType commandType, GameContext context)
    {
        if (!CommandPatterns.TryGetValue(commandType, out var patterns))
            return null;

        foreach (var pattern in patterns)
        {
            var match = MatchPattern(tokens, pattern, context);
            if (match != null)
            {
                match.Type = commandType;
                return match;
            }
        }

        return null;
    }

    private ParsedCommand? MatchPattern(List<string> tokens, string[] pattern, GameContext context)
    {
        if (tokens.Count < pattern.Length - pattern.Count(p => p == "*"))
        {
            return null; // No hay suficientes tokens
        }

        var command = new ParsedCommand { OriginalInput = string.Join(" ", tokens) };
        int tokenIndex = 0;
        int patternIndex = 0;

        while (patternIndex < pattern.Length && tokenIndex < tokens.Count)
        {
            var patternElement = pattern[patternIndex];
            var token = tokens[tokenIndex];

            if (patternElement == "*")
            {
                // Comodín - capturar el siguiente token como parte del comando
                var role = DetermineTokenRole(patternIndex, pattern);
                AssignTokenToCommand(command, token, role);
                tokenIndex++;
            }
            else if (IsTokenMatch(token, patternElement))
            {
                // Coincidencia exacta o por sinónimo
                var role = DetermineTokenRole(patternIndex, pattern);
                AssignTokenToCommand(command, ResolveToken(token, patternElement), role);
                tokenIndex++;
            }
            else
            {
                return null; // No coincide el patrón
            }

            patternIndex++;
        }

        // Verificar que hemos procesado todo el patrón
        if (patternIndex == pattern.Length)
        {
            return command;
        }

        return null;
    }

    private bool IsTokenMatch(string token, string patternElement)
    {
        if (string.Equals(token, patternElement, StringComparison.OrdinalIgnoreCase))
            return true;

        // Verificar sinónimos
        var normalizedPattern = _vocabulary.NormalizeWord(patternElement);
        var normalizedToken = _vocabulary.NormalizeWord(token);
        
        return string.Equals(normalizedToken, normalizedPattern, StringComparison.OrdinalIgnoreCase);
    }

    private string DetermineTokenRole(int patternIndex, string[] pattern)
    {
        // Determinar qué rol tiene este token en el comando basándose en su posición
        if (patternIndex == 0)
            return "verb";
        
        if (pattern[patternIndex] == "*")
        {
            // Determinar rol basándose en el contexto
            if (patternIndex == 1)
                return "direct_object";
            
            // Si hay una preposición antes, es objeto indirecto
            if (patternIndex > 0 && IsPreposition(pattern[patternIndex - 1]))
                return "indirect_object";
                
            return "direct_object";
        }

        if (IsPreposition(pattern[patternIndex]))
            return "preposition";

        if (IsDirection(pattern[patternIndex]))
            return "direction";

        return "unknown";
    }

    private void AssignTokenToCommand(ParsedCommand command, string token, string role)
    {
        switch (role)
        {
            case "verb":
                command.Verb = token;
                break;
            case "direct_object":
                command.DirectObject = token;
                break;
            case "indirect_object":
                command.IndirectObject = token;
                break;
            case "preposition":
                command.Preposition = token;
                break;
            case "direction":
                command.Direction = token;
                break;
        }
    }

    private string ResolveToken(string token, string patternElement)
    {
        // Si el token coincide por sinónimo, devolver la forma canónica
        return _vocabulary.GetCanonicalForm(token) ?? token;
    }

    private bool IsPreposition(string word)
    {
        var prepositions = new HashSet<string> { "en", "con", "de", "a", "sobre", "bajo", "dentro", "fuera" };
        return prepositions.Contains(word.ToLowerInvariant());
    }

    private bool IsDirection(string word)
    {
        var directions = new HashSet<string> { "norte", "sur", "este", "oeste", "arriba", "abajo" };
        return directions.Contains(word.ToLowerInvariant());
    }

    private ParsedCommand ClassifyByHeuristics(List<string> tokens, GameContext context)
    {
        // Clasificación heurística cuando no coincide ningún patrón específico
        var command = new ParsedCommand 
        { 
            Type = CommandType.Examination, // Default conservador
            OriginalInput = string.Join(" ", tokens)
        };

        // Si el primer token es un verbo conocido, usarlo
        if (tokens.Count > 0 && _vocabulary.IsVerb(tokens[0]))
        {
            command.Verb = _vocabulary.GetCanonicalForm(tokens[0]) ?? tokens[0];
            
            // Si hay más tokens, asumir que son objetos
            if (tokens.Count > 1)
            {
                command.DirectObject = tokens[1];
            }
        }
        else if (tokens.Count > 0)
        {
            // Si no empieza con verbo, podría ser un comando de dirección
            if (IsDirection(tokens[0]))
            {
                command.Type = CommandType.Movement;
                command.Direction = tokens[0];
            }
        }

        _logger.LogDebug("Clasificación heurística aplicada: {CommandType}", command.Type);
        return command;
    }
}
```

### 5.5.5 Resolución de Referencias - Entendiendo el Contexto

El resolvedor de referencias maneja los pronombres, referencias implícitas y la deixis (palabras como "esto", "eso", "aquí") que son comunes en el español conversacional.

```csharp
// Spanish/ReferenceResolver.cs
namespace DaadModernizado.Spanish;

public class ReferenceResolver
{
    private readonly ILogger _logger;
    
    // Pronombres que pueden referirse a objetos del juego
    private static readonly Dictionary<string, ObjectReference> ObjectPronouns = new(StringComparer.OrdinalIgnoreCase)
    {
        ["lo"] = new ObjectReference { Gender = Gender.Masculine, Number = Number.Singular },
        ["la"] = new ObjectReference { Gender = Gender.Feminine, Number = Number.Singular },
        ["los"] = new ObjectReference { Gender = Gender.Masculine, Number = Number.Plural },
        ["las"] = new ObjectReference { Gender = Gender.Feminine, Number = Number.Plural },
        ["eso"] = new ObjectReference { Gender = Gender.Neutral, Number = Number.Singular },
        ["esto"] = new ObjectReference { Gender = Gender.Neutral, Number = Number.Singular },
        ["aquello"] = new ObjectReference { Gender = Gender.Neutral, Number = Number.Singular }
    };

    public ReferenceResolver(ILogger logger)
    {
        _logger = logger;
    }

    public ParsedCommand ResolveReferences(ParsedCommand command, GameContext context)
    {
        var resolvedCommand = command with { }; // Crear copia

        // Resolver referencias en objeto directo
        if (!string.IsNullOrEmpty(command.DirectObject))
        {
            var resolved = ResolveObjectReference(command.DirectObject, context);
            if (resolved != null)
            {
                resolvedCommand.DirectObject = resolved;
                resolvedCommand.ResolvedReferences[command.DirectObject] = resolved;
                _logger.LogDebug("Resuelto '{Original}' → '{Resolved}'", command.DirectObject, resolved);
            }
        }

        // Resolver referencias en objeto indirecto
        if (!string.IsNullOrEmpty(command.IndirectObject))
        {
            var resolved = ResolveObjectReference(command.IndirectObject, context);
            if (resolved != null)
            {
                resolvedCommand.IndirectObject = resolved;
                resolvedCommand.ResolvedReferences[command.IndirectObject] = resolved;
            }
        }

        return resolvedCommand;
    }

    private string? ResolveObjectReference(string reference, GameContext context)
    {
        // Caso 1: El nombre ya es específico (no es un pronombre)
        if (!ObjectPronouns.ContainsKey(reference) && !IsVagueReference(reference))
        {
            // Verificar si existe un objeto con este nombre exacto o similar
            var exactMatch = context.FindObjectByName(reference);
            if (exactMatch != null)
                return exactMatch.Id;

            // Buscar coincidencias parciales o por sinónimos
            var partialMatch = context.FindObjectBySimilarName(reference);
            if (partialMatch != null)
            {
                _logger.LogDebug("Coincidencia parcial: '{Reference}' → '{ObjectId}'", reference, partialMatch.Id);
                return partialMatch.Id;
            }

            return null; // No se pudo resolver
        }

        // Caso 2: Es un pronombre que necesita ser resuelto por contexto
        if (ObjectPronouns.TryGetValue(reference, out var pronounInfo))
        {
            return ResolvePronouns(pronounInfo, context);
        }

        // Caso 3: Es una referencia vaga como "cosa", "objeto"
        if (IsVagueReference(reference))
        {
            return ResolveVagueReference(reference, context);
        }

        return null;
    }

    private string? ResolvePronouns(ObjectReference pronounInfo, GameContext context)
    {
        // Buscar en el contexto conversacional objetos que coincidan en género y número
        var candidates = context.GetRecentlyMentionedObjects()
            .Where(obj => MatchesGenderAndNumber(obj, pronounInfo))
            .ToList();

        if (candidates.Count == 1)
        {
            _logger.LogDebug("Pronombre resuelto a objeto único: {ObjectId}", candidates[0].Id);
            return candidates[0].Id;
        }

        if (candidates.Count > 1)
        {
            // Múltiples candidatos - usar heurísticas para desambiguar
            var mostRecent = candidates.OrderByDescending(obj => obj.LastMentionTime).First();
            _logger.LogDebug("Pronombre resuelto a objeto más reciente: {ObjectId}", mostRecent.Id);
            return mostRecent.Id;
        }

        // No se pudo resolver
        _logger.LogWarning("No se pudo resolver pronombre con género {Gender}, número {Number}", 
            pronounInfo.Gender, pronounInfo.Number);
        return null;
    }

    private string? ResolveVagueReference(string reference, GameContext context)
    {
        // Referencias vagas como "cosa", "objeto", "eso de ahí"
        var vagueTerms = new HashSet<string> { "cosa", "objeto", "elemento", "item" };
        
        if (vagueTerms.Contains(reference.ToLowerInvariant()))
        {
            // Buscar el objeto más recientemente mencionado o más prominente
            var recentObjects = context.GetRecentlyMentionedObjects();
            if (recentObjects.Any())
            {
                var mostRecent = recentObjects.First();
                _logger.LogDebug("Referencia vaga '{Reference}' resuelta a: {ObjectId}", reference, mostRecent.Id);
                return mostRecent.Id;
            }
        }

        return null;
    }

    private bool MatchesGenderAndNumber(GameObject obj, ObjectReference pronounInfo)
    {
        // En un sistema completo, los objetos tendrían información gramatical
        // Por ahora, usamos heurísticas basadas en terminaciones comunes
        
        if (pronounInfo.Gender == Gender.Neutral)
            return true; // "esto", "eso" pueden referirse a cualquier cosa

        var objGender = InferGender(obj.Name);
        var objNumber = InferNumber(obj.Name);

        return (pronounInfo.Gender == Gender.Masculine && objGender == Gender.Masculine) ||
               (pronounInfo.Gender == Gender.Feminine && objGender == Gender.Feminine);
    }

    private Gender InferGender(string objectName)
    {
        // Heurísticas basadas en terminaciones comunes en español
        var lowerName = objectName.ToLowerInvariant();
        
        if (lowerName.EndsWith("a") || lowerName.EndsWith("cion") || lowerName.EndsWith("sion"))
            return Gender.Feminine;
        
        if (lowerName.EndsWith("o") || lowerName.EndsWith("or") || lowerName.EndsWith("al"))
            return Gender.Masculine;

        return Gender.Masculine; // Default conservador
    }

    private Number InferNumber(string objectName)
    {
        var lowerName = objectName.ToLowerInvariant();
        
        if (lowerName.EndsWith("s") && !lowerName.EndsWith("as") && !lowerName.EndsWith("os"))
            return Number.Plural;
        
        return Number.Singular;
    }

    private bool IsVagueReference(string reference)
    {
        var vagueTerms = new HashSet<string> { "cosa", "objeto", "elemento", "item", "ello", "aquello" };
        return vagueTerms.Contains(reference.ToLowerInvariant());
    }
}

// Clases de apoyo para información gramatical
public record ObjectReference
{
    public Gender Gender { get; init; }
    public Number Number { get; init; }
}

public enum Gender { Masculine, Feminine, Neutral }
public enum Number { Singular, Plural }
```

### 5.5.6 Sistema de Sugerencias Inteligentes

Cuando el sistema no puede entender un comando, proporciona sugerencias útiles basadas en el contexto del juego y comandos similares.

```csharp
// Spanish/SpanishSyntaxAnalyzer.cs (continuación - método SuggestAlternatives)
public List<string> SuggestAlternatives(string userInput, GameContext context)
{
    var suggestions = new List<string>();
    
    if (string.IsNullOrWhiteSpace(userInput))
        return suggestions;

    var normalizedInput = _normalizer.Normalize(userInput);
    var tokens = _normalizer.Tokenize(normalizedInput);

    // Estrategia 1: Sugerir correcciones ortográficas
    suggestions.AddRange(SuggestSpellingCorrections(tokens, context));

    // Estrategia 2: Sugerir comandos con objetos visibles
    suggestions.AddRange(SuggestVisibleObjectCommands(tokens, context));

    // Estrategia 3: Sugerir direcciones válidas
    suggestions.AddRange(SuggestValidDirections(tokens, context));

    // Estrategia 4: Sugerir comandos comunes
    suggestions.AddRange(SuggestCommonCommands(context));

    // Limitar y priorizar sugerencias
    return suggestions.Distinct().Take(5).ToList();
}

private List<string> SuggestSpellingCorrections(List<string> tokens, GameContext context)
{
    var suggestions = new List<string>();

    foreach (var token in tokens)
    {
        // Buscar palabras similares en el vocabulario
        var similarWords = _vocabulary.FindSimilarWords(token, maxDistance: 2);
        
        foreach (var similar in similarWords.Take(2)) // Máximo 2 por palabra
        {
            var correctedCommand = string.Join(" ", tokens.Select(t => t == token ? similar : t));
            suggestions.Add($"¿Quisiste decir '{correctedCommand}'?");
        }
    }

    return suggestions;
}

private List<string> SuggestVisibleObjectCommands(List<string> tokens, GameContext context)
{
    var suggestions = new List<string>();
    var visibleObjects = context.GetVisibleObjects();

    // Si mencionaron un objeto que no existe, sugerir objetos similares visibles
    foreach (var token in tokens)
    {
        var similarObjects = visibleObjects
            .Where(obj => CalculateStringSimilarity(token, obj.Name) > 0.6)
            .Take(2);

        foreach (var obj in similarObjects)
        {
            suggestions.Add($"mirar {obj.Name}");
            suggestions.Add($"coger {obj.Name}");
        }
    }

    return suggestions;
}

private List<string> SuggestValidDirections(List<string> tokens, GameContext context)
{
    var suggestions = new List<string>();
    
    // Si parece que intentaron moverse pero la dirección no es válida
    if (tokens.Any(t => t.StartsWith("ir") || IsAlmostDirection(t)))
    {
        var availableExits = context.GetAvailableExits();
        foreach (var exit in availableExits.Take(3))
        {
            suggestions.Add(exit);
        }
    }

    return suggestions;
}

private List<string> SuggestCommonCommands(GameContext context)
{
    return new List<string>
    {
        "mirar",
        "inventario",
        "ayuda"
    };
}

private bool IsAlmostDirection(string token)
{
    var almostDirections = new Dictionary<string, string>
    {
        ["nort"] = "norte",
        ["sur"] = "sur", 
        ["est"] = "este",
        ["oest"] = "oeste"
    };

    return almostDirections.Keys.Any(key => 
        CalculateStringSimilarity(token, key) > 0.7);
}

private double CalculateStringSimilarity(string s1, string s2)
{
    // Implementación simplificada de distancia de Levenshtein normalizada
    if (string.IsNullOrEmpty(s1) || string.IsNullOrEmpty(s2))
        return 0;

    var distance = CalculateLevenshteinDistance(s1, s2);
    var maxLength = Math.Max(s1.Length, s2.Length);
    
    return 1.0 - (double)distance / maxLength;
}

private int CalculateLevenshteinDistance(string s1, string s2)
{
    var matrix = new int[s1.Length + 1, s2.Length + 1];

    for (int i = 0; i <= s1.Length; i++)
        matrix[i, 0] = i;
    
    for (int j = 0; j <= s2.Length; j++)
        matrix[0, j] = j;

    for (int i = 1; i <= s1.Length; i++)
    {
        for (int j = 1; j <= s2.Length; j++)
        {
            var cost = s1[i - 1] == s2[j - 1] ? 0 : 1;
            
            matrix[i, j] = Math.Min(
                Math.Min(matrix[i - 1, j] + 1, matrix[i, j - 1] + 1),
                matrix[i - 1, j - 1] + cost);
        }
    }

    return matrix[s1.Length, s2.Length];
}
```

Esta implementación del Analizador Sintáctico Español proporciona procesamiento robusto y tolerante de comandos en español natural, con resolución de referencias, manejo de ambigüedades y sugerencias inteligentes. En la siguiente parte (5.6) abordaremos los **Componentes de Soporte y Testing**, que completan la infraestructura necesaria para el desarrollo y mantenimiento del sistema.

