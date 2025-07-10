# Sistema Parser DAAD Modernizado - Parte 5: Guía de Implementación

## Parte 5.4: Implementación del Transpilador a DAAD Clásico (3D5) - Componente Importante

### 5.4.1 Arquitectura del Transpilador

El transpilador debe convertir aventuras en formato DAAD Modernizado al formato clásico, manteniendo compatibilidad completa y generando código optimizado. Su arquitectura se basa en múltiples fases de transformación.

```csharp
// Transpiler/IClassicDaadTranspiler.cs
namespace DaadModernizado.Transpiler;

public interface IClassicDaadTranspiler
{
    Task<TranspileResult> TranspileAsync(ModernDaadGame game, TranspileOptions options, CancellationToken cancellationToken = default);
    TranspileResult Transpile(ModernDaadGame game, TranspileOptions options);
    ValidationResult ValidateCompatibility(ModernDaadGame game);
}

// Transpiler/TranspileResult.cs
public record TranspileResult
{
    public bool IsSuccess { get; init; }
    public string ClassicDaadCode { get; init; } = "";
    public Dictionary<string, int> IdentifierMapping { get; init; } = new();
    public List<string> Errors { get; init; } = new();
    public List<string> Warnings { get; init; } = new();
    public TranspileStatistics Statistics { get; init; } = new();
}

public record TranspileStatistics
{
    public int LocationsCount { get; init; }
    public int ObjectsCount { get; init; }
    public int MessagesCount { get; init; }
    public int ResponsesCount { get; init; }
    public int ProcessesCount { get; init; }
    public int VocabularySize { get; init; }
}

// Transpiler/TranspileOptions.cs
public class TranspileOptions
{
    public bool OptimizeCode { get; set; } = true;
    public bool IncludeComments { get; set; } = true;
    public bool ValidateTargetCompatibility { get; set; } = true;
    public DaadTarget TargetVersion { get; set; } = DaadTarget.Classic;
    public NumberingStrategy NumberingStrategy { get; set; } = NumberingStrategy.Automatic;
    public Dictionary<string, int> PresetNumbers { get; set; } = new();
}

public enum DaadTarget
{
    Classic,
    Enhanced,
    Portable
}

public enum NumberingStrategy
{
    Automatic,
    Sequential,
    Optimized,
    Manual
}
```

### 5.4.2 Sistema de Mapeo de Identificadores

Implementar un sistema robusto que convierta nombres descriptivos a números según las convenciones clásicas:

```csharp
// Transpiler/IdentifierMapper.cs
namespace DaadModernizado.Transpiler;

public class IdentifierMapper
{
    private readonly Dictionary<string, int> _locationMap = new();
    private readonly Dictionary<string, int> _objectMap = new();
    private readonly Dictionary<string, int> _messageMap = new();
    private readonly Dictionary<string, int> _verbMap = new();
    private readonly Dictionary<string, int> _nounMap = new();

    // Rangos estándar de DAAD clásico
    private const int LocationRangeStart = 0;
    private const int LocationRangeEnd = 99;
    private const int ObjectRangeStart = 50;
    private const int ObjectRangeEnd = 199;
    private const int MessageRangeStart = 0;
    private const int MessageRangeEnd = 255;
    private const int VerbRangeStart = 1;
    private const int VerbRangeEnd = 20;
    private const int NounRangeStart = 50;
    private const int NounRangeEnd = 200;

    public void BuildMappings(ModernDaadGame game, TranspileOptions options)
    {
        if (options.NumberingStrategy == NumberingStrategy.Manual)
        {
            ApplyPresetMappings(options.PresetNumbers);
        }

        BuildLocationMappings(game.Locations, options);
        BuildObjectMappings(game.Objects, options);
        BuildMessageMappings(game.Messages, options);
        BuildVocabularyMappings(game.Vocabulary, options);
    }

    private void BuildLocationMappings(Dictionary<string, ModernLocation> locations, TranspileOptions options)
    {
        var availableNumbers = GenerateAvailableNumbers(LocationRangeStart, LocationRangeEnd, _locationMap.Values);
        var numberQueue = new Queue<int>(availableNumbers);

        foreach (var (locationId, location) in locations.OrderBy(kvp => GetLocationPriority(kvp.Value)))
        {
            if (!_locationMap.ContainsKey(locationId))
            {
                if (numberQueue.Count == 0)
                    throw new TranspileException($"No hay números disponibles para la localidad '{locationId}'");
                
                _locationMap[locationId] = numberQueue.Dequeue();
            }
        }
    }

    private void BuildObjectMappings(Dictionary<string, ModernObject> objects, TranspileOptions options)
    {
        var availableNumbers = GenerateAvailableNumbers(ObjectRangeStart, ObjectRangeEnd, _objectMap.Values);
        var numberQueue = new Queue<int>(availableNumbers);

        foreach (var (objectId, obj) in objects.OrderBy(kvp => GetObjectPriority(kvp.Value)))
        {
            if (!_objectMap.ContainsKey(objectId))
            {
                if (numberQueue.Count == 0)
                    throw new TranspileException($"No hay números disponibles para el objeto '{objectId}'");
                
                _objectMap[objectId] = numberQueue.Dequeue();
            }
        }
    }

    private void BuildMessageMappings(Dictionary<string, string> messages, TranspileOptions options)
    {
        var availableNumbers = GenerateAvailableNumbers(MessageRangeStart, MessageRangeEnd, _messageMap.Values);
        var numberQueue = new Queue<int>(availableNumbers);

        foreach (var messageId in messages.Keys.OrderBy(id => id))
        {
            if (!_messageMap.ContainsKey(messageId))
            {
                if (numberQueue.Count == 0)
                    throw new TranspileException($"No hay números disponibles para el mensaje '{messageId}'");
                
                _messageMap[messageId] = numberQueue.Dequeue();
            }
        }
    }

    private void BuildVocabularyMappings(ModernVocabulary vocabulary, TranspileOptions options)
    {
        // Mapear verbos
        var availableVerbs = GenerateAvailableNumbers(VerbRangeStart, VerbRangeEnd, _verbMap.Values);
        var verbQueue = new Queue<int>(availableVerbs);

        foreach (var (verb, id) in vocabulary.Verbs.Where(kvp => !SpanishVocabularyLibrary.BaseVerbs.ContainsKey(kvp.Key)))
        {
            if (!_verbMap.ContainsKey(verb))
            {
                if (verbQueue.Count == 0)
                    throw new TranspileException($"No hay números disponibles para el verbo '{verb}'");
                
                _verbMap[verb] = verbQueue.Dequeue();
            }
        }

        // Mapear sustantivos
        var availableNouns = GenerateAvailableNumbers(NounRangeStart, NounRangeEnd, _nounMap.Values);
        var nounQueue = new Queue<int>(availableNouns);

        foreach (var (noun, id) in vocabulary.Nouns.Where(kvp => !SpanishVocabularyLibrary.BaseNouns.ContainsKey(kvp.Key)))
        {
            if (!_nounMap.ContainsKey(noun))
            {
                if (nounQueue.Count == 0)
                    throw new TranspileException($"No hay números disponibles para el sustantivo '{noun}'");
                
                _nounMap[noun] = nounQueue.Dequeue();
            }
        }
    }

    private static List<int> GenerateAvailableNumbers(int start, int end, IEnumerable<int> usedNumbers)
    {
        var used = new HashSet<int>(usedNumbers);
        return Enumerable.Range(start, end - start + 1).Where(n => !used.Contains(n)).ToList();
    }

    private static int GetLocationPriority(ModernLocation location)
    {
        // Priorizar localidad de inicio
        return location.IsStartLocation ? 0 : 1;
    }

    private static int GetObjectPriority(ModernObject obj)
    {
        // Priorizar objetos importantes o llevables
        return obj.IsTakeable ? 0 : 1;
    }

    private void ApplyPresetMappings(Dictionary<string, int> presets)
    {
        foreach (var (identifier, number) in presets)
        {
            // Determinar tipo por convención de nombre o rango numérico
            if (number >= LocationRangeStart && number <= LocationRangeEnd)
                _locationMap[identifier] = number;
            else if (number >= ObjectRangeStart && number <= ObjectRangeEnd)
                _objectMap[identifier] = number;
            else if (number >= MessageRangeStart && number <= MessageRangeEnd)
                _messageMap[identifier] = number;
        }
    }

    // Métodos de consulta
    public int GetLocationNumber(string locationId) => 
        _locationMap.TryGetValue(locationId, out var number) ? number : 
        throw new TranspileException($"Localidad no mapeada: '{locationId}'");

    public int GetObjectNumber(string objectId) => 
        _objectMap.TryGetValue(objectId, out var number) ? number : 
        throw new TranspileException($"Objeto no mapeado: '{objectId}'");

    public int GetMessageNumber(string messageId) => 
        _messageMap.TryGetValue(messageId, out var number) ? number : 
        throw new TranspileException($"Mensaje no mapeado: '{messageId}'");

    public Dictionary<string, int> GetAllMappings()
    {
        var allMappings = new Dictionary<string, int>();
        
        foreach (var (id, num) in _locationMap) allMappings[$"location:{id}"] = num;
        foreach (var (id, num) in _objectMap) allMappings[$"object:{id}"] = num;
        foreach (var (id, num) in _messageMap) allMappings[$"message:{id}"] = num;
        foreach (var (id, num) in _verbMap) allMappings[$"verb:{id}"] = num;
        foreach (var (id, num) in _nounMap) allMappings[$"noun:{id}"] = num;

        return allMappings;
    }
}
```

### 5.4.3 Generadores de Secciones Clásicas

Implementar generadores específicos para cada sección del formato clásico:

```csharp
// Transpiler/Generators/ClassicSectionGenerator.cs
namespace DaadModernizado.Transpiler.Generators;

public abstract class ClassicSectionGenerator
{
    protected readonly IdentifierMapper _mapper;
    protected readonly ILogger _logger;

    protected ClassicSectionGenerator(IdentifierMapper mapper, ILogger logger)
    {
        _mapper = mapper;
        _logger = logger;
    }

    public abstract string SectionName { get; }
    public abstract string Generate(ModernDaadGame game, TranspileOptions options);

    protected string GenerateComment(string comment)
    {
        return $"; {comment}";
    }

    protected string GenerateSectionHeader(string sectionName)
    {
        return $"/{sectionName.ToUpperInvariant()}";
    }
}

// Transpiler/Generators/ControlSectionGenerator.cs
public class ControlSectionGenerator : ClassicSectionGenerator
{
    public override string SectionName => "CTL";

    public ControlSectionGenerator(IdentifierMapper mapper, ILogger<ControlSectionGenerator> logger) 
        : base(mapper, logger) { }

    public override string Generate(ModernDaadGame game, TranspileOptions options)
    {
        var sb = new StringBuilder();
        
        sb.AppendLine(GenerateSectionHeader("CTL"));
        
        if (options.IncludeComments)
        {
            sb.AppendLine(GenerateComment("Sección de control generada automáticamente"));
            sb.AppendLine(GenerateComment($"Título: {game.Metadata.Title}"));
        }

        // TITLE
        if (!string.IsNullOrEmpty(game.Metadata.Title))
        {
            sb.AppendLine($"TITLE \"{game.Metadata.Title}\"");
        }

        // START
        if (!string.IsNullOrEmpty(game.Metadata.StartLocation))
        {
            var startLocationNumber = _mapper.GetLocationNumber(game.Metadata.StartLocation);
            sb.AppendLine($"START {startLocationNumber}");
        }

        // MAXSCORE
        if (game.Metadata.MaxScore > 0)
        {
            sb.AppendLine($"MAXSCORE {game.Metadata.MaxScore}");
        }

        // VERSION
        if (!string.IsNullOrEmpty(game.Metadata.Version))
        {
            sb.AppendLine($"VERSION \"{game.Metadata.Version}\"");
        }

        // AUTHOR
        if (!string.IsNullOrEmpty(game.Metadata.Author))
        {
            sb.AppendLine($"AUTHOR \"{game.Metadata.Author}\"");
        }

        return sb.ToString();
    }
}

// Transpiler/Generators/VocabularySectionGenerator.cs
public class VocabularySectionGenerator : ClassicSectionGenerator
{
    public override string SectionName => "VOC";

    public VocabularySectionGenerator(IdentifierMapper mapper, ILogger<VocabularySectionGenerator> logger) 
        : base(mapper, logger) { }

    public override string Generate(ModernDaadGame game, TranspileOptions options)
    {
        var sb = new StringBuilder();
        
        sb.AppendLine(GenerateSectionHeader("VOC"));
        
        if (options.IncludeComments)
        {
            sb.AppendLine(GenerateComment("Vocabulario personalizado"));
        }

        // Generar verbos personalizados
        foreach (var (verb, id) in game.Vocabulary.Verbs.Where(IsCustomWord))
        {
            sb.AppendLine($"{verb} {GetWordType("verb")} {id}");
        }

        // Generar sustantivos personalizados
        foreach (var (noun, id) in game.Vocabulary.Nouns.Where(IsCustomWord))
        {
            sb.AppendLine($"{noun} {GetWordType("noun")} {id}");
        }

        // Generar adjetivos personalizados
        foreach (var (adj, id) in game.Vocabulary.Adjectives.Where(IsCustomWord))
        {
            sb.AppendLine($"{adj} {GetWordType("adjective")} {id}");
        }

        // Generar preposiciones personalizadas
        foreach (var (prep, id) in game.Vocabulary.Prepositions.Where(IsCustomWord))
        {
            sb.AppendLine($"{prep} {GetWordType("preposition")} {id}");
        }

        return sb.ToString();
    }

    private static bool IsCustomWord(KeyValuePair<string, int> wordPair)
    {
        // Solo incluir palabras que no están en el vocabulario base
        return !SpanishVocabularyLibrary.BaseVerbs.ContainsKey(wordPair.Key) &&
               !SpanishVocabularyLibrary.BaseNouns.ContainsKey(wordPair.Key);
    }

    private static int GetWordType(string category)
    {
        return category.ToLowerInvariant() switch
        {
            "verb" => 0,
            "noun" => 1,
            "adjective" => 2,
            "preposition" => 3,
            "adverb" => 4,
            _ => 1 // Default a sustantivo
        };
    }
}

// Transpiler/Generators/ConnectionsSectionGenerator.cs
public class ConnectionsSectionGenerator : ClassicSectionGenerator
{
    public override string SectionName => "CON";

    public ConnectionsSectionGenerator(IdentifierMapper mapper, ILogger<ConnectionsSectionGenerator> logger) 
        : base(mapper, logger) { }

    public override string Generate(ModernDaadGame game, TranspileOptions options)
    {
        var sb = new StringBuilder();
        
        sb.AppendLine(GenerateSectionHeader("CON"));
        
        if (options.IncludeComments)
        {
            sb.AppendLine(GenerateComment("Conexiones entre localidades"));
        }

        foreach (var (locationId, location) in game.Locations.OrderBy(kvp => _mapper.GetLocationNumber(kvp.Key)))
        {
            var locationNumber = _mapper.GetLocationNumber(locationId);
            
            if (options.IncludeComments)
            {
                sb.AppendLine(GenerateComment($"Localidad: {location.Name ?? locationId}"));
            }

            foreach (var (direction, destination) in location.Exits)
            {
                var directionId = GetDirectionId(direction);
                var destinationNumber = _mapper.GetLocationNumber(destination);
                sb.AppendLine($"{locationNumber} {directionId} {destinationNumber}");
            }
        }

        return sb.ToString();
    }

    private static int GetDirectionId(string direction)
    {
        return direction.ToLowerInvariant() switch
        {
            "norte" or "north" or "n" => 10,
            "sur" or "south" or "s" => 11,
            "este" or "east" or "e" => 12,
            "oeste" or "west" or "o" or "w" => 13,
            "noreste" or "northeast" or "ne" => 14,
            "noroeste" or "northwest" or "nw" => 15,
            "sureste" or "southeast" or "se" => 16,
            "suroeste" or "southwest" or "sw" => 17,
            "arriba" or "up" or "u" => 18,
            "abajo" or "down" or "d" => 19,
            _ => throw new TranspileException($"Dirección no reconocida: '{direction}'")
        };
    }
}

// Transpiler/Generators/LocationTextSectionGenerator.cs
public class LocationTextSectionGenerator : ClassicSectionGenerator
{
    public override string SectionName => "LTX";

    public LocationTextSectionGenerator(IdentifierMapper mapper, ILogger<LocationTextSectionGenerator> logger) 
        : base(mapper, logger) { }

    public override string Generate(ModernDaadGame game, TranspileOptions options)
    {
        var sb = new StringBuilder();
        
        sb.AppendLine(GenerateSectionHeader("LTX"));
        
        if (options.IncludeComments)
        {
            sb.AppendLine(GenerateComment("Descripciones de localidades"));
        }

        foreach (var (locationId, location) in game.Locations.OrderBy(kvp => _mapper.GetLocationNumber(kvp.Key)))
        {
            var locationNumber = _mapper.GetLocationNumber(locationId);
            
            if (!string.IsNullOrEmpty(location.Description))
            {
                if (options.IncludeComments)
                {
                    sb.AppendLine(GenerateComment($"Localidad {locationNumber}: {location.Name ?? locationId}"));
                }
                
                sb.AppendLine($"{locationNumber} \"{EscapeText(location.Description)}\"");
            }
        }

        return sb.ToString();
    }

    private static string EscapeText(string text)
    {
        return text.Replace("\"", "\\\"").Replace("\n", "\\n").Replace("\r", "");
    }
}
```

### 5.4.4 Generador de Procesos (Lógica de Respuestas)

Convertir condiciones y acciones modernas al formato clásico:

```csharp
// Transpiler/Generators/ProcessSectionGenerator.cs
public class ProcessSectionGenerator : ClassicSectionGenerator
{
    public override string SectionName => "PRO";

    public ProcessSectionGenerator(IdentifierMapper mapper, ILogger<ProcessSectionGenerator> logger) 
        : base(mapper, logger) { }

    public override string Generate(ModernDaadGame game, TranspileOptions options)
    {
        var sb = new StringBuilder();
        
        sb.AppendLine(GenerateSectionHeader("PRO"));
        
        if (options.IncludeComments)
        {
            sb.AppendLine(GenerateComment("Procesos de respuesta"));
        }

        // Generar respuestas
        foreach (var response in game.Responses)
        {
            GenerateResponse(sb, response, options);
        }

        // Generar procesos automáticos
        foreach (var process in game.Processes)
        {
            GenerateProcess(sb, process, options);
        }

        return sb.ToString();
    }

    private void GenerateResponse(StringBuilder sb, ModernResponse response, TranspileOptions options)
    {
        if (options.IncludeComments)
        {
            sb.AppendLine(GenerateComment($"Respuesta: {string.Join(", ", response.Patterns)}"));
        }

        // Generar patrón de comando
        foreach (var pattern in response.Patterns)
        {
            var (verb, noun) = ParseCommandPattern(pattern);
            sb.AppendLine($"*");
            sb.AppendLine($"{verb} {noun}");

            // Generar condiciones
            if (response.Condition != null)
            {
                GenerateCondition(sb, response.Condition);
            }

            // Generar acciones
            foreach (var action in response.Actions)
            {
                GenerateAction(sb, action);
            }

            sb.AppendLine("DONE");
        }
    }

    private void GenerateProcess(StringBuilder sb, ModernProcess process, TranspileOptions options)
    {
        if (options.IncludeComments)
        {
            sb.AppendLine(GenerateComment($"Proceso: {process.Name}"));
        }

        // Los procesos automáticos usan patrón especial
        sb.AppendLine("_");

        // Generar condiciones del proceso
        if (process.Condition != null)
        {
            GenerateCondition(sb, process.Condition);
        }

        // Generar acciones del proceso
        foreach (var action in process.Actions)
        {
            GenerateAction(sb, action);
        }

        sb.AppendLine("DONE");
    }

    private void GenerateCondition(StringBuilder sb, ModernCondition condition)
    {
        switch (condition.Type)
        {
            case ConditionType.Simple:
                GenerateSimpleCondition(sb, condition);
                break;
            case ConditionType.Logical:
                GenerateLogicalCondition(sb, condition);
                break;
        }
    }

    private void GenerateSimpleCondition(StringBuilder sb, ModernCondition condition)
    {
        var classicFunction = ConvertConditionFunction(condition.Function);
        var args = ConvertConditionArguments(condition.Function, condition.Arguments);

        if (condition.IsNegated)
        {
            sb.AppendLine($"NOT{classicFunction} {string.Join(" ", args)}");
        }
        else
        {
            sb.AppendLine($"{classicFunction} {string.Join(" ", args)}");
        }
    }

    private void GenerateLogicalCondition(StringBuilder sb, ModernCondition condition)
    {
        // DAAD clásico no tiene operadores lógicos explícitos
        // Las condiciones múltiples se evalúan secuencialmente con AND implícito
        // Para OR necesitamos duplicar respuestas
        
        if (condition.Operator == "&&")
        {
            // AND: generar condiciones secuencialmente
            if (condition.Left != null)
                GenerateCondition(sb, condition.Left);
            if (condition.Right != null)
                GenerateCondition(sb, condition.Right);
        }
        else if (condition.Operator == "||")
        {
            // OR: esto requiere reestructuración compleja
            _logger.LogWarning("Operador OR en condiciones requiere reestructuración manual en DAAD clásico");
            // Por simplicidad, generamos solo la primera condición con advertencia
            if (condition.Left != null)
                GenerateCondition(sb, condition.Left);
        }
    }

    private void GenerateAction(StringBuilder sb, ModernAction action)
    {
        if (action.Function == "if")
        {
            // Estructuras de control no son directamente soportadas en DAAD clásico
            _logger.LogWarning("Estructura de control 'if' no soportada directamente en DAAD clásico");
            return;
        }

        var classicFunction = ConvertActionFunction(action.Function);
        var args = ConvertActionArguments(action.Function, action.Arguments);

        sb.AppendLine($"{classicFunction} {string.Join(" ", args)}");
    }

    private string ConvertConditionFunction(string modernFunction)
    {
        return modernFunction.ToLowerInvariant() switch
        {
            "present" => "PRESENT",
            "absent" => "ABSENT",
            "carried" => "CARRIED",
            "worn" => "WORN",
            "at" => "AT",
            "notat" => "NOTAT",
            "flag" => "FLAG",
            "counter" => "COUNTER",
            "chance" => "CHANCE",
            _ => modernFunction.ToUpperInvariant()
        };
    }

    private List<string> ConvertConditionArguments(string function, List<string> args)
    {
        var convertedArgs = new List<string>();

        foreach (var arg in args)
        {
            var converted = function.ToLowerInvariant() switch
            {
                "present" or "absent" or "carried" or "worn" => _mapper.GetObjectNumber(arg).ToString(),
                "at" or "notat" => _mapper.GetLocationNumber(arg).ToString(),
                _ => arg // Mantener como está para flags, counters, etc.
            };
            convertedArgs.Add(converted);
        }

        return convertedArgs;
    }

    private string ConvertActionFunction(string modernFunction)
    {
        return modernFunction.ToLowerInvariant() switch
        {
            "take" => "GET",
            "drop" => "DROP",
            "destroy" => "DESTROY",
            "create" => "CREATE",
            "goto" => "GOTO",
            "message" => "MESSAGE",
            "add_score" => "SCORE",
            "set_flag" => "SET",
            "clear_flag" => "CLEAR",
            "increment_counter" => "PLUS",
            "decrement_counter" => "MINUS",
            "set_counter" => "LET",
            "done" => "DONE",
            "end_game" => "END",
            "restart" => "RESTART",
            _ => modernFunction.ToUpperInvariant()
        };
    }

    private List<string> ConvertActionArguments(string function, List<string> args)
    {
        var convertedArgs = new List<string>();

        foreach (var arg in args)
        {
            var converted = function.ToLowerInvariant() switch
            {
                "take" or "drop" or "destroy" or "create" => _mapper.GetObjectNumber(arg).ToString(),
                "goto" => _mapper.GetLocationNumber(arg).ToString(),
                "message" => _mapper.GetMessageNumber(arg).ToString(),
                _ => arg
            };
            convertedArgs.Add(converted);
        }

        return convertedArgs;
    }

    private (int verb, int noun) ParseCommandPattern(string pattern)
    {
        // Parsear patrón como "verbo sustantivo" y convertir a números
        var words = pattern.Split(' ', StringSplitOptions.RemoveEmptyEntries);
        
        var verb = 1; // Default
        var noun = 50; // Default

        if (words.Length > 0 && SpanishVocabularyLibrary.BaseVerbs.TryGetValue(words[0], out var verbId))
        {
            verb = verbId;
        }

        if (words.Length > 1 && SpanishVocabularyLibrary.BaseNouns.TryGetValue(words[1], out var nounId))
        {
            noun = nounId;
        }

        return (verb, noun);
    }
}
```

### 5.4.5 Transpilador Principal

Orquestar todas las fases de transpilación:

```csharp
// Transpiler/ClassicDaadTranspiler.cs
namespace DaadModernizado.Transpiler;

public class ClassicDaadTranspiler : IClassicDaadTranspiler
{
    private readonly IdentifierMapper _mapper;
    private readonly List<ClassicSectionGenerator> _generators;
    private readonly ILogger<ClassicDaadTranspiler> _logger;

    public ClassicDaadTranspiler(ILogger<ClassicDaadTranspiler> logger)
    {
        _logger = logger;
        _mapper = new IdentifierMapper();
        _generators = new List<ClassicSectionGenerator>
        {
            new ControlSectionGenerator(_mapper, logger),
            new VocabularySectionGenerator(_mapper, logger),
            new ConnectionsSectionGenerator(_mapper, logger),
            new LocationTextSectionGenerator(_mapper, logger),
            new ObjectTextSectionGenerator(_mapper, logger),
            new MessageSectionGenerator(_mapper, logger),
            new ProcessSectionGenerator(_mapper, logger)
        };
    }

    public async Task<TranspileResult> TranspileAsync(ModernDaadGame game, TranspileOptions options, CancellationToken cancellationToken = default)
    {
        return await Task.Run(() => Transpile(game, options), cancellationToken);
    }

    public TranspileResult Transpile(ModernDaadGame game, TranspileOptions options)
    {
        var result = new TranspileResult();
        var stopwatch = Stopwatch.StartNew();

        try
        {
            _logger.LogInformation("Iniciando transpilación a DAAD clásico");

            // Fase 1: Validación de compatibilidad
            if (options.ValidateTargetCompatibility)
            {
                var compatibility = ValidateCompatibility(game);
                result.Warnings.AddRange(compatibility.Warnings);
                
                if (compatibility.Errors.Count > 0)
                {
                    result.Errors.AddRange(compatibility.Errors);
                    return result;
                }
            }

            // Fase 2: Construcción de mapeos
            _mapper.BuildMappings(game, options);
            result.IdentifierMapping = _mapper.GetAllMappings();

            // Fase 3: Generación de secciones
            var sections = new StringBuilder();
            
            foreach (var generator in _generators)
            {
                _logger.LogInformation("Generando sección {SectionName}", generator.SectionName);
                
                var sectionContent = generator.Generate(game, options);
                sections.AppendLine(sectionContent);
                sections.AppendLine(); // Línea en blanco entre secciones
            }

            // Fase 4: Optimización (si está habilitada)
            var finalCode = sections.ToString();
            if (options.OptimizeCode)
            {
                finalCode = OptimizeCode(finalCode);
            }

            result.ClassicDaadCode = finalCode;
            result.Statistics = GenerateStatistics(game);
            result.IsSuccess = true;

            stopwatch.Stop();
            _logger.LogInformation("Transpilación completada en {ElapsedMs}ms", stopwatch.ElapsedMilliseconds);

            return result;
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Error durante la transpilación");
            result.Errors.Add($"Error de transpilación: {ex.Message}");
            return result;
        }
    }

    public ValidationResult ValidateCompatibility(ModernDaadGame game)
    {
        var result = new ValidationResult();

        // Validar límites de DAAD clásico
        if (game.Locations.Count > 100)
        {
            result.Errors.Add($"Demasiadas localidades: {game.Locations.Count} (máximo 100)");
        }

        if (game.Objects.Count > 150)
        {
            result.Errors.Add($"Demasiados objetos: {game.Objects.Count} (máximo 150)");
        }

        if (game.Messages.Count > 256)
        {
            result.Errors.Add($"Demasiados mensajes: {game.Messages.Count} (máximo 256)");
        }

        // Validar características no soportadas
        foreach (var response in game.Responses)
        {
            if (response.Condition?.Type == ConditionType.Logical && response.Condition.Operator == "||")
            {
                result.Warnings.Add("Operadores OR en condiciones requieren reestructuración manual");
            }

            foreach (var action in response.Actions)
            {
                if (action.Function == "if" || action.Function == "while")
                {
                    result.Warnings.Add("Estructuras de control no son directamente soportadas en DAAD clásico");
                }
            }
        }

        // Validar vocabulario personalizado
        var customVerbs = game.Vocabulary.Verbs.Count(kvp => !SpanishVocabularyLibrary.BaseVerbs.ContainsKey(kvp.Key));
        var customNouns = game.Vocabulary.Nouns.Count(kvp => !SpanishVocabularyLibrary.BaseNouns.ContainsKey(kvp.Key));

        if (customVerbs > 20)
        {
            result.Warnings.Add($"Muchos verbos personalizados: {customVerbs} (recomendado máximo 20)");
        }

        if (customNouns > 150)
        {
            result.Warnings.Add($"Muchos sustantivos personalizados: {customNouns} (recomendado máximo 150)");
        }

        return result;
    }

    private string OptimizeCode(string code)
    {
        // Optimizaciones básicas del código generado
        var lines = code.Split('\n', StringSplitOptions.RemoveEmptyEntries);
        var optimizedLines = new List<string>();

        foreach (var line in lines)
        {
            var trimmed = line.Trim();
            
            // Eliminar líneas de comentario si no se requieren
            if (trimmed.StartsWith(";"))
                continue;

            // Eliminar líneas vacías redundantes
            if (string.IsNullOrWhiteSpace(trimmed))
                continue;

            optimizedLines.Add(trimmed);
        }

        return string.Join("\n", optimizedLines);
    }

    private TranspileStatistics GenerateStatistics(ModernDaadGame game)
    {
        return new TranspileStatistics
        {
            LocationsCount = game.Locations.Count,
            ObjectsCount = game.Objects.Count,
            MessagesCount = game.Messages.Count,
            ResponsesCount = game.Responses.Count,
            ProcessesCount = game.Processes.Count,
            VocabularySize = game.Vocabulary.Verbs.Count + game.Vocabulary.Nouns.Count
        };
    }
}

// Extensión para DI
public static class TranspilerServiceExtensions
{
    public static IServiceCollection AddClassicTranspiler(this IServiceCollection services)
    {
        services.AddTransient<IClassicDaadTranspiler, ClassicDaadTranspiler>();
        return services;
    }
}
```

### 5.4.6 Testing del Transpilador

Implementar tests comprehensivos para validar la transpilación:

```csharp
// Tests/TranspilerTests.cs
namespace DaadModernizado.Transpiler.Tests;

public class TranspilerTests : TestBase
{
    private readonly IClassicDaadTranspiler _transpiler;

    public TranspilerTests(ITestOutputHelper output) : base(output)
    {
        _transpiler = GetService<IClassicDaadTranspiler>();
    }

    [Fact]
    public void Transpile_BasicGame_GeneratesValidClassicCode()
    {
        // Arrange
        var game = CreateBasicTestGame();
        var options = new TranspileOptions
        {
            OptimizeCode = false,
            IncludeComments = true
        };

        // Act
        var result = _transpiler.Transpile(game, options);

        // Assert
        Assert.True(result.IsSuccess);
        Assert.NotEmpty(result.ClassicDaadCode);
        Assert.Contains("/CTL", result.ClassicDaadCode);
        Assert.Contains("/CON", result.ClassicDaadCode);
        Assert.Contains("/LTX", result.ClassicDaadCode);
        Assert.Contains("/PRO", result.ClassicDaadCode);
    }

    [Fact]
    public void Transpile_WithIdentifierMapping_CreatesCorrectMapping()
    {
        // Arrange
        var game = CreateTestGameWithNamedElements();
        var options = new TranspileOptions();

        // Act
        var result = _transpiler.Transpile(game, options);

        // Assert
        Assert.True(result.IsSuccess);
        Assert.NotEmpty(result.IdentifierMapping);
        Assert.Contains("location:bosque", result.IdentifierMapping.Keys);
        Assert.Contains("object:espada", result.IdentifierMapping.Keys);
    }

    [Fact]
    public void ValidateCompatibility_TooManyLocations_ReturnsError()
    {
        // Arrange
        var game = CreateGameWithTooManyLocations();

        // Act
        var result = _transpiler.ValidateCompatibility(game);

        // Assert
        Assert.NotEmpty(result.Errors);
        Assert.Contains("Demasiadas localidades", result.Errors[0]);
    }

    [Fact]
    public void Transpile_LogicalOrCondition_GeneratesWarning()
    {
        // Arrange
        var game = CreateGameWithOrCondition();
        var options = new TranspileOptions();

        // Act
        var result = _transpiler.Transpile(game, options);

        // Assert
        Assert.True(result.IsSuccess);
        Assert.NotEmpty(result.Warnings);
        Assert.Contains("Operadores OR", result.Warnings[0]);
    }

    private ModernDaadGame CreateBasicTestGame()
    {
        var game = new ModernDaadGame
        {
            Metadata = new GameMetadata
            {
                Title = "Juego de Prueba",
                Author = "Tester",
                StartLocation = "inicio"
            }
        };

        game.Locations["inicio"] = new ModernLocation
        {
            Id = "inicio",
            Name = "Habitación Inicial",
            Description = "Una habitación simple para pruebas."
        };

        return game;
    }

    private ModernDaadGame CreateTestGameWithNamedElements()
    {
        var game = CreateBasicTestGame();
        
        game.Locations["bosque"] = new ModernLocation
        {
            Id = "bosque",
            Name = "Bosque Encantado",
            Description = "Un bosque místico"
        };

        game.Objects["espada"] = new ModernObject
        {
            Id = "espada",
            Name = "Espada Brillante",
            Description = "Una espada que brilla con luz propia",
            Location = "bosque"
        };

        return game;
    }

    private ModernDaadGame CreateGameWithTooManyLocations()
    {
        var game = CreateBasicTestGame();
        
        // Crear más de 100 localidades
        for (int i = 0; i < 101; i++)
        {
            game.Locations[$"location_{i}"] = new ModernLocation
            {
                Id = $"location_{i}",
                Description = $"Localidad de prueba {i}"
            };
        }

        return game;
    }

    private ModernDaadGame CreateGameWithOrCondition()
    {
        var game = CreateTestGameWithNamedElements();
        
        game.Responses.Add(new ModernResponse
        {
            Patterns = ["mirar espada"],
            Condition = new ModernCondition
            {
                Type = ConditionType.Logical,
                Operator = "||",
                Left = CommonConditions.Present("espada"),
                Right = CommonConditions.Carried("espada")
            },
            Actions = [CommonActions.Message("Ves la espada")]
        });

        return game;
    }
}
```

Esta implementación del Transpilador a DAAD Clásico proporciona conversión completa con mapeo de identificadores, validación de compatibilidad, y optimización de código. En la siguiente parte (5.5) abordaremos el **Analizador Sintáctico Español (3D6)**, que maneja la comprensión de comandos del jugador en tiempo real.