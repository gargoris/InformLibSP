# Sistema Parser DAAD Modernizado - Parte 5: Guía de Implementación

## Parte 5.8: Herramientas de Desarrollo Avanzadas - El Taller del Artesano

### 5.8.1 La Filosofía de las Herramientas: Más que Solo Funcionalidad

Imagina a un maestro artesano en su taller. No solo tiene las herramientas básicas necesarias para su oficio, sino que cada herramienta ha sido cuidadosamente seleccionada, mantenida y organizada para maximizar tanto la eficiencia como la calidad de su trabajo. El martillo no solo sirve para golpear, sino que tiene el peso perfecto, el mango de la longitud ideal, y está posicionado exactamente donde la mano lo puede alcanzar sin pensarlo.

Este mismo principio debe guiar el diseño de nuestras herramientas de desarrollo para DAAD Modernizado. No basta con que funcionen; deben sentirse como extensiones naturales del pensamiento creativo del desarrollador. Una buena herramienta de desarrollo desaparece de la conciencia del usuario, permitiéndole enfocarse completamente en la creación de su aventura en lugar de luchar con la tecnología.

La diferencia entre herramientas básicas y herramientas avanzadas es como la diferencia entre un editor de texto simple y un IDE moderno. Ambos pueden escribir código, pero el IDE entiende el contexto, anticipa las necesidades, y proporciona retroalimentación inmediata que transforma la experiencia de desarrollo de una lucha técnica en un flujo creativo.

```csharp
// Tools/IDaadDevelopmentEnvironment.cs
namespace DaadModernizado.Tools;

/// <summary>
/// Interfaz principal para el entorno de desarrollo integrado de DAAD Modernizado.
/// 
/// Esta interfaz define las capacidades que debe proporcionar cualquier herramienta
/// de desarrollo avanzada para DAAD. Piensa en esto como el "contrato" que garantiza
/// que los desarrolladores tendrán una experiencia consistente sin importar qué
/// herramientas específicas estén usando.
/// </summary>
public interface IDaadDevelopmentEnvironment
{
    // === GESTIÓN DE PROYECTOS ===
    Task<ProjectResult> CreateProjectAsync(string projectName, ProjectTemplate template);
    Task<ProjectResult> OpenProjectAsync(string projectPath);
    Task<ProjectResult> SaveProjectAsync();
    Project? CurrentProject { get; }

    // === EDICIÓN INTELIGENTE ===
    Task<List<CompletionItem>> GetCompletionsAsync(string fileName, int line, int column);
    Task<List<Diagnostic>> ValidateFileAsync(string fileName);
    Task<List<Diagnostic>> ValidateProjectAsync();

    // === DEBUGGING Y TESTING ===
    Task<DebugSession> StartDebugSessionAsync(string adventureFile);
    Task<TestResult> RunTestsAsync(TestSuite testSuite);
    Task<TestResult> RunInteractiveTestAsync(string adventureFile);

    // === ANÁLISIS Y REFACTORING ===
    Task<AnalysisReport> AnalyzeProjectAsync();
    Task<RefactorResult> RenameSymbolAsync(string oldName, string newName);
    Task<RefactorResult> ExtractResponseAsync(string responseCode, string newResponseName);

    // === PREVISUALIZACIÓN Y EJECUCIÓN ===
    Task<PreviewResult> StartPreviewAsync(string adventureFile);
    Task<RuntimeInstance> StartGameAsync(string adventureFile);

    // Eventos para comunicación con la interfaz de usuario
    event EventHandler<DiagnosticEventArgs> DiagnosticsUpdated;
    event EventHandler<ProjectEventArgs> ProjectChanged;
    event EventHandler<PreviewEventArgs> PreviewUpdated;
}

/// <summary>
/// Representa un proyecto de aventura DAAD completo.
/// Un proyecto puede contener múltiples archivos, recursos, configuraciones,
/// y metadatos que juntos definen una aventura conversacional.
/// </summary>
public class Project
{
    public string Name { get; set; } = "";
    public string RootPath { get; set; } = "";
    public string MainAdventureFile { get; set; } = "";
    public List<ProjectFile> Files { get; set; } = new();
    public ProjectConfiguration Configuration { get; set; } = new();
    public Dictionary<string, object> Metadata { get; set; } = new();
    
    // Para tracking de cambios y versionado
    public DateTime LastModified { get; set; }
    public string Version { get; set; } = "1.0";
    public List<ProjectChange> ChangeHistory { get; set; } = new();
}

public class ProjectFile
{
    public string Name { get; set; } = "";
    public string RelativePath { get; set; } = "";
    public ProjectFileType Type { get; set; }
    public DateTime LastModified { get; set; }
    public bool HasUnsavedChanges { get; set; }
}

public enum ProjectFileType
{
    MainAdventure,    // El archivo .daad principal
    SubAdventure,     // Archivos .daad adicionales incluidos
    Asset,            // Imágenes, sonidos, etc.
    Configuration,    // Archivos de configuración
    Documentation,    // README, notas, etc.
    Test             // Archivos de test específicos
}
```

### 5.8.2 El Editor Inteligente: Autocompletado Consciente del Contexto

Un editor inteligente para DAAD Modernizado debe ir mucho más allá del simple resaltado sintáctico. Debe entender el contexto del juego que se está desarrollando, conocer qué objetos existen, qué localidades están definidas, y qué mensajes están disponibles. Es como tener un asistente experto que conoce íntimamente tu proyecto y puede anticipar lo que necesitas antes de que lo pidas.

La clave está en construir un modelo semántico en tiempo real de la aventura que se está editando. Cada vez que el desarrollador añade una nueva localidad, el editor inmediatamente sabe que esa localidad está disponible para referencias en otras partes del código. Cuando el desarrollador empieza a escribir una condición, el editor puede sugerir objetos y localidades relevantes.

```csharp
// Tools/IntelligentEditor.cs
namespace DaadModernizado.Tools.Editor;

/// <summary>
/// Editor inteligente que proporciona asistencia contextual mientras
/// el desarrollador escribe código DAAD Modernizado.
/// 
/// Este editor funciona construyendo un modelo semántico en tiempo real
/// de la aventura, permitiendo proporcionar sugerencias precisas y
/// validación inmediata.
/// </summary>
public class IntelligentEditor
{
    private readonly IGameParser _parser;
    private readonly ILogger<IntelligentEditor> _logger;
    
    // Modelo semántico de la aventura en desarrollo
    private SemanticModel _semanticModel = new();
    private readonly Dictionary<string, DocumentState> _openDocuments = new();

    public IntelligentEditor(IGameParser parser, ILogger<IntelligentEditor> logger)
    {
        _parser = parser;
        _logger = logger;
    }

    /// <summary>
    /// Proporciona sugerencias de autocompletado basadas en el contexto actual.
    /// 
    /// El editor analiza la posición del cursor y el código circundante para
    /// determinar qué tipo de sugerencias son apropiadas. Por ejemplo, si el
    /// usuario está escribiendo dentro de una condición, sugerirá funciones
    /// de condición y objetos disponibles.
    /// </summary>
    public async Task<List<CompletionItem>> GetCompletionsAsync(string fileName, int line, int column, string textContent)
    {
        try
        {
            // Actualizar nuestro modelo semántico con el contenido actual
            await UpdateSemanticModelAsync(fileName, textContent);

            // Analizar el contexto donde está el cursor
            var context = AnalyzeCompletionContext(textContent, line, column);
            
            _logger.LogDebug("Generando completions para contexto: {ContextType} en {FileName}:{Line}:{Column}", 
                context.Type, fileName, line, column);

            return context.Type switch
            {
                CompletionContextType.SectionName => GetSectionNameCompletions(),
                CompletionContextType.PropertyName => GetPropertyNameCompletions(context.SectionType),
                CompletionContextType.ObjectReference => GetObjectReferenceCompletions(),
                CompletionContextType.LocationReference => GetLocationReferenceCompletions(),
                CompletionContextType.MessageReference => GetMessageReferenceCompletions(),
                CompletionContextType.ConditionFunction => GetConditionFunctionCompletions(),
                CompletionContextType.ActionFunction => GetActionFunctionCompletions(),
                CompletionContextType.Direction => GetDirectionCompletions(),
                CompletionContextType.Verb => GetVerbCompletions(),
                CompletionContextType.Noun => GetNounCompletions(),
                _ => GetGeneralCompletions()
            };
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Error generando completions para {FileName}", fileName);
            return new List<CompletionItem>();
        }
    }

    /// <summary>
    /// Analiza el contexto donde está posicionado el cursor para determinar
    /// qué tipo de sugerencias son apropiadas.
    /// </summary>
    private CompletionContext AnalyzeCompletionContext(string content, int line, int column)
    {
        var lines = content.Split('\n');
        if (line >= lines.Length) return new CompletionContext { Type = CompletionContextType.General };

        var currentLine = lines[line];
        var textBeforeCursor = column < currentLine.Length ? currentLine.Substring(0, column) : currentLine;
        
        // Analizar qué sección estamos editando
        var currentSection = DetermineCurrentSection(lines, line);
        
        // Analizar el contexto específico dentro de la línea
        if (IsInConditionContext(textBeforeCursor))
        {
            if (textBeforeCursor.TrimEnd().EndsWith("("))
                return new CompletionContext { Type = CompletionContextType.ObjectReference, SectionType = currentSection };
            else
                return new CompletionContext { Type = CompletionContextType.ConditionFunction, SectionType = currentSection };
        }

        if (IsInActionContext(textBeforeCursor))
        {
            if (textBeforeCursor.TrimEnd().EndsWith("("))
                return DetermineActionParameterContext(textBeforeCursor);
            else
                return new CompletionContext { Type = CompletionContextType.ActionFunction, SectionType = currentSection };
        }

        if (IsInPropertyContext(textBeforeCursor))
        {
            if (textBeforeCursor.Contains(":"))
                return DeterminePropertyValueContext(textBeforeCursor, currentSection);
            else
                return new CompletionContext { Type = CompletionContextType.PropertyName, SectionType = currentSection };
        }

        // Contexto de inicio de sección
        if (textBeforeCursor.Trim().Length == 0 || IsStartOfSection(textBeforeCursor))
        {
            return new CompletionContext { Type = CompletionContextType.SectionName };
        }

        return new CompletionContext { Type = CompletionContextType.General, SectionType = currentSection };
    }

    /// <summary>
    /// Genera sugerencias para nombres de sección (game, location, object, etc.)
    /// </summary>
    private List<CompletionItem> GetSectionNameCompletions()
    {
        return new List<CompletionItem>
        {
            new CompletionItem
            {
                Label = "game",
                Kind = CompletionItemKind.Keyword,
                Detail = "Configuración principal del juego",
                Documentation = "Define metadatos como título, autor, y configuración del juego",
                InsertText = "game {\n  title: \"$1\"\n  author: \"$2\"\n  start: $3\n}"
            },
            new CompletionItem
            {
                Label = "location",
                Kind = CompletionItemKind.Keyword,
                Detail = "Define una localidad del juego",
                Documentation = "Crea una nueva localidad con descripción, salidas y objetos",
                InsertText = "location $1 {\n  desc: \"$2\"\n  exits: { $3 }\n}"
            },
            new CompletionItem
            {
                Label = "object",
                Kind = CompletionItemKind.Keyword,
                Detail = "Define un objeto del juego",
                Documentation = "Crea un nuevo objeto con propiedades como nombre, descripción y ubicación",
                InsertText = "object $1 {\n  name: \"$2\"\n  desc: \"$3\"\n  location: $4\n  takeable: true\n}"
            },
            new CompletionItem
            {
                Label = "responses",
                Kind = CompletionItemKind.Keyword,
                Detail = "Define respuestas a comandos del jugador",
                Documentation = "Contiene las respuestas que el juego da a los comandos del jugador",
                InsertText = "responses {\n  on \"$1\" {\n    require: $2\n    do: {\n      $3\n    }\n  }\n}"
            },
            new CompletionItem
            {
                Label = "messages",
                Kind = CompletionItemKind.Keyword,
                Detail = "Define mensajes reutilizables",
                Documentation = "Centraliza todos los mensajes de texto del juego",
                InsertText = "messages {\n  $1: \"$2\"\n}"
            }
        };
    }

    /// <summary>
    /// Genera sugerencias para referencias a objetos basadas en los objetos
    /// realmente definidos en la aventura actual.
    /// </summary>
    private List<CompletionItem> GetObjectReferenceCompletions()
    {
        var completions = new List<CompletionItem>();

        // Añadir objetos definidos en la aventura actual
        foreach (var objectId in _semanticModel.DefinedObjects.Keys)
        {
            var objectInfo = _semanticModel.DefinedObjects[objectId];
            completions.Add(new CompletionItem
            {
                Label = objectId,
                Kind = CompletionItemKind.Reference,
                Detail = $"Objeto: {objectInfo.Name}",
                Documentation = $"Descripción: {objectInfo.Description}\nLocalidad: {objectInfo.Location}",
                InsertText = objectId
            });
        }

        // Añadir sugerencias para objetos comunes si no hay objetos definidos aún
        if (completions.Count == 0)
        {
            var commonObjects = new[] { "espada", "llave", "cofre", "libro", "antorcha", "gema", "pergamino" };
            foreach (var obj in commonObjects)
            {
                completions.Add(new CompletionItem
                {
                    Label = obj,
                    Kind = CompletionItemKind.Text,
                    Detail = "Objeto común sugerido",
                    Documentation = $"Referencia a un objeto típico: {obj}",
                    InsertText = obj
                });
            }
        }

        return completions;
    }

    /// <summary>
    /// Genera sugerencias para funciones de condición con documentación detallada.
    /// </summary>
    private List<CompletionItem> GetConditionFunctionCompletions()
    {
        return new List<CompletionItem>
        {
            new CompletionItem
            {
                Label = "present",
                Kind = CompletionItemKind.Function,
                Detail = "present(objeto) - Verifica si un objeto está presente",
                Documentation = "Retorna verdadero si el objeto especificado está en la localidad actual",
                InsertText = "present($1)"
            },
            new CompletionItem
            {
                Label = "carried",
                Kind = CompletionItemKind.Function,
                Detail = "carried(objeto) - Verifica si el jugador lleva un objeto",
                Documentation = "Retorna verdadero si el jugador tiene el objeto en su inventario",
                InsertText = "carried($1)"
            },
            new CompletionItem
            {
                Label = "at",
                Kind = CompletionItemKind.Function,
                Detail = "at(localidad) - Verifica la localidad actual",
                Documentation = "Retorna verdadero si el jugador está en la localidad especificada",
                InsertText = "at($1)"
            },
            new CompletionItem
            {
                Label = "flag",
                Kind = CompletionItemKind.Function,
                Detail = "flag(nombre) - Verifica el estado de una bandera",
                Documentation = "Retorna verdadero si la bandera especificada está activada",
                InsertText = "flag(\"$1\")"
            },
            new CompletionItem
            {
                Label = "counter",
                Kind = CompletionItemKind.Function,
                Detail = "counter(nombre) - Obtiene el valor de un contador",
                Documentation = "Retorna el valor numérico del contador especificado",
                InsertText = "counter(\"$1\")"
            }
        };
    }

    /// <summary>
    /// Actualiza el modelo semántico con el contenido actual del archivo.
    /// Esto permite que las sugerencias siempre reflejen el estado actual
    /// de la aventura en desarrollo.
    /// </summary>
    private async Task UpdateSemanticModelAsync(string fileName, string content)
    {
        try
        {
            // Parsear el contenido para extraer información semántica
            var parseResult = await _parser.ParseAsync(content);
            
            if (parseResult.IsSuccess && parseResult.Game != null)
            {
                // Actualizar modelo con objetos definidos
                _semanticModel.DefinedObjects.Clear();
                foreach (var obj in parseResult.Game.Objects)
                {
                    _semanticModel.DefinedObjects[obj.Key] = new SemanticObjectInfo
                    {
                        Id = obj.Key,
                        Name = obj.Value.Name,
                        Description = obj.Value.Description,
                        Location = obj.Value.Location
                    };
                }

                // Actualizar modelo con localidades definidas
                _semanticModel.DefinedLocations.Clear();
                foreach (var loc in parseResult.Game.Locations)
                {
                    _semanticModel.DefinedLocations[loc.Key] = new SemanticLocationInfo
                    {
                        Id = loc.Key,
                        Name = loc.Value.Name ?? loc.Key,
                        Description = loc.Value.Description,
                        Exits = loc.Value.Exits.Keys.ToList()
                    };
                }

                // Actualizar modelo con mensajes definidos
                _semanticModel.DefinedMessages.Clear();
                foreach (var msg in parseResult.Game.Messages)
                {
                    _semanticModel.DefinedMessages[msg.Key] = msg.Value;
                }

                _logger.LogDebug("Modelo semántico actualizado: {ObjectCount} objetos, {LocationCount} localidades", 
                    _semanticModel.DefinedObjects.Count, _semanticModel.DefinedLocations.Count);
            }
        }
        catch (Exception ex)
        {
            _logger.LogWarning(ex, "Error actualizando modelo semántico para {FileName}", fileName);
            // Continuar con el modelo anterior si hay error
        }
    }

    // Métodos auxiliares para análisis de contexto
    private bool IsInConditionContext(string text)
    {
        var trimmed = text.Trim();
        return trimmed.StartsWith("require:") || 
               trimmed.Contains("require:") ||
               trimmed.Contains("&&") || 
               trimmed.Contains("||");
    }

    private bool IsInActionContext(string text)
    {
        var trimmed = text.Trim();
        return trimmed.StartsWith("do:") || 
               trimmed.Contains("do:") ||
               (trimmed.Contains("{") && !trimmed.Contains("require:"));
    }

    private bool IsInPropertyContext(string text)
    {
        var trimmed = text.Trim();
        return char.IsLetter(trimmed.FirstOrDefault()) && 
               (trimmed.Contains(":") || !trimmed.Contains("{"));
    }

    private string DetermineCurrentSection(string[] lines, int currentLine)
    {
        // Buscar hacia atrás para encontrar la sección actual
        for (int i = currentLine; i >= 0; i--)
        {
            var line = lines[i].Trim();
            if (line.StartsWith("game ") || line == "game" || line.StartsWith("game{"))
                return "game";
            if (line.StartsWith("location "))
                return "location";
            if (line.StartsWith("object "))
                return "object";
            if (line.StartsWith("responses ") || line == "responses")
                return "responses";
            if (line.StartsWith("messages ") || line == "messages")
                return "messages";
        }
        return "unknown";
    }
}

// Clases de apoyo para el editor inteligente
public class SemanticModel
{
    public Dictionary<string, SemanticObjectInfo> DefinedObjects { get; set; } = new();
    public Dictionary<string, SemanticLocationInfo> DefinedLocations { get; set; } = new();
    public Dictionary<string, string> DefinedMessages { get; set; } = new();
    public List<string> DefinedFlags { get; set; } = new();
    public List<string> DefinedCounters { get; set; } = new();
}

public class SemanticObjectInfo
{
    public string Id { get; set; } = "";
    public string Name { get; set; } = "";
    public string Description { get; set; } = "";
    public string Location { get; set; } = "";
}

public class SemanticLocationInfo
{
    public string Id { get; set; } = "";
    public string Name { get; set; } = "";
    public string Description { get; set; } = "";
    public List<string> Exits { get; set; } = new();
}

public class CompletionItem
{
    public string Label { get; set; } = "";
    public CompletionItemKind Kind { get; set; }
    public string Detail { get; set; } = "";
    public string Documentation { get; set; } = "";
    public string InsertText { get; set; } = "";
}

public enum CompletionItemKind
{
    Text, Method, Function, Constructor, Field, Variable, Class, Interface,
    Module, Property, Unit, Value, Enum, Keyword, Snippet, Color, File,
    Reference, Folder, EnumMember, Constant, Struct, Event, Operator, TypeParameter
}

public class CompletionContext
{
    public CompletionContextType Type { get; set; }
    public string SectionType { get; set; } = "";
    public Dictionary<string, object> Properties { get; set; } = new();
}

public enum CompletionContextType
{
    General, SectionName, PropertyName, ObjectReference, LocationReference,
    MessageReference, ConditionFunction, ActionFunction, Direction, Verb, Noun
}
```

### 5.8.3 El Depurador Visual: Haciendo Visible lo Invisible

Un depurador para aventuras conversacionales presenta desafíos únicos porque debe manejar tanto el flujo de ejecución como el estado del mundo virtual. Es como ser el director de una obra teatral que puede pausar la acción en cualquier momento, examinar los pensamientos de cada personaje, verificar qué props están en escena, y luego continuar la acción paso a paso.

La clave de un buen depurador para DAAD es proporcionar múltiples vistas del estado del juego: el estado físico (dónde está el jugador, qué objetos están dónde), el estado lógico (flags, contadores, condiciones), y el flujo de ejecución (qué respuestas se están evaluando, qué condiciones se cumplen).

```csharp
// Tools/VisualDebugger.cs
namespace DaadModernizado.Tools.Debug;

/// <summary>
/// Depurador visual que permite examinar y controlar la ejecución de una aventura
/// paso a paso, proporcionando visibilidad completa del estado del juego.
/// 
/// Este depurador funciona interceptando la ejecución del motor de runtime y
/// proporcionando herramientas para inspeccionar cada aspecto del estado del juego.
/// </summary>
public class VisualDebugger
{
    private readonly IGameRuntime _runtime;
    private readonly ILogger<VisualDebugger> _logger;
    
    // Estado del depurador
    private DebugSession? _currentSession;
    private readonly List<DebugBreakpoint> _breakpoints = new();
    private DebugState _debugState = DebugState.Stopped;

    public event EventHandler<DebugEventArgs>? DebugEvent;
    public event EventHandler<StateChangedEventArgs>? StateChanged;

    public VisualDebugger(IGameRuntime runtime, ILogger<VisualDebugger> logger)
    {
        _runtime = runtime;
        _logger = logger;
        
        // Suscribirse a eventos del runtime para interceptar ejecución
        _runtime.MessageGenerated += OnRuntimeMessage;
        _runtime.LocationChanged += OnLocationChanged;
        _runtime.InventoryChanged += OnInventoryChanged;
    }

    /// <summary>
    /// Inicia una nueva sesión de depuración para una aventura específica.
    /// </summary>
    public async Task<DebugSession> StartDebugSessionAsync(ModernDaadGame game, DebugConfiguration config)
    {
        try
        {
            _logger.LogInformation("Iniciando sesión de depuración para: {GameTitle}", game.Metadata.Title);

            _currentSession = new DebugSession
            {
                Game = game,
                Configuration = config,
                StartTime = DateTime.UtcNow,
                SessionId = Guid.NewGuid().ToString()
            };

            // Inicializar el runtime con interceptores de depuración
            var debugRuntime = new DebuggingGameRuntime(_runtime, this);
            await debugRuntime.StartGameAsync(game);

            _debugState = DebugState.Paused;
            
            // Notificar inicio de sesión
            EmitDebugEvent(DebugEventType.SessionStarted, "Sesión de depuración iniciada");
            
            // Mostrar estado inicial
            await ShowGameStateAsync();

            return _currentSession;
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Error iniciando sesión de depuración");
            throw;
        }
    }

    /// <summary>
    /// Ejecuta un paso único en la depuración, permitiendo ver exactamente
    /// qué sucede con cada comando del jugador.
    /// </summary>
    public async Task<DebugStepResult> StepAsync(string command)
    {
        if (_currentSession == null || _debugState != DebugState.Paused)
            throw new InvalidOperationException("No hay sesión de depuración activa o pausada");

        try
        {
            _logger.LogDebug("Ejecutando paso de depuración: {Command}", command);

            var stepResult = new DebugStepResult
            {
                Command = command,
                ExecutionTrace = new List<DebugTraceEntry>()
            };

            // Cambiar a estado de ejecución paso a paso
            _debugState = DebugState.Stepping;

            // Interceptar y trazar la ejecución del comando
            var executionTracer = new ExecutionTracer();
            
            // Simular procesamiento del comando con trazado detallado
            await TraceCommandProcessingAsync(command, executionTracer);

            stepResult.ExecutionTrace = executionTracer.GetTrace();
            stepResult.FinalState = await CaptureGameStateAsync();

            _debugState = DebugState.Paused;

            // Verificar si hemos alcanzado algún breakpoint
            await CheckBreakpointsAsync();

            EmitDebugEvent(DebugEventType.StepCompleted, $"Paso completado: {command}");

            return stepResult;
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Error ejecutando paso de depuración");
            _debugState = DebugState.Error;
            throw;
        }
    }

    /// <summary>
    /// Proporciona una vista detallada del estado actual del juego,
    /// incluyendo ubicación del jugador, inventario, flags, contadores, y más.
    /// </summary>
    public async Task<GameStateSnapshot> GetGameStateSnapshotAsync()
    {
        if (_currentSession == null)
            throw new InvalidOperationException("No hay sesión de depuración activa");

        var snapshot = new GameStateSnapshot
        {
            Timestamp = DateTime.UtcNow,
            CurrentLocation = _runtime.CurrentState.CurrentLocationId,
            PlayerInventory = new List<string>(_runtime.CurrentState.PlayerInventory),
            Flags = new Dictionary<string, bool>(_runtime.CurrentState.Flags),
            Counters = new Dictionary<string, int>(_runtime.CurrentState.Counters),
            ObjectLocations = new Dictionary<string, string>(_runtime.CurrentState.ObjectLocations),
            Score = _runtime.CurrentState.CurrentScore,
            TurnCount = _runtime.CurrentState.TurnCount
        };

        // Añadir información enriquecida para debugging
        await EnrichSnapshotWithDebugInfoAsync(snapshot);

        return snapshot;
    }

    /// <summary>
    /// Establece un breakpoint que pausará la ejecución cuando se cumpla
    /// una condición específica.
    /// </summary>
    public async Task<BreakpointResult> SetBreakpointAsync(DebugBreakpoint breakpoint)
    {
        try
        {
            // Validar el breakpoint
            var validation = await ValidateBreakpointAsync(breakpoint);
            if (!validation.IsValid)
            {
                return BreakpointResult.Failure($"Breakpoint inválido: {validation.Error}");
            }

            // Añadir a la lista de breakpoints activos
            breakpoint.Id = Guid.NewGuid().ToString();
            breakpoint.IsEnabled = true;
            _breakpoints.Add(breakpoint);

            _logger.LogInformation("Breakpoint establecido: {BreakpointType} - {Condition}", 
                breakpoint.Type, breakpoint.Condition);

            EmitDebugEvent(DebugEventType.BreakpointSet, $"Breakpoint establecido: {breakpoint.Condition}");

            return BreakpointResult.Success(breakpoint.Id);
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Error estableciendo breakpoint");
            return BreakpointResult.Failure($"Error estableciendo breakpoint: {ex.Message}");
        }
    }

    /// <summary>
    /// Analiza el flujo de ejecución para una respuesta específica,
    /// mostrando exactamente qué condiciones se evalúan y qué acciones se ejecutan.
    /// </summary>
    public async Task<ResponseAnalysis> AnalyzeResponseAsync(ModernResponse response, string testCommand)
    {
        var analysis = new ResponseAnalysis
        {
            Response = response,
            TestCommand = testCommand,
            ConditionResults = new List<ConditionResult>(),
            ActionResults = new List<ActionResult>(),
            ExecutionPath = new List<string>()
        };

        try
        {
            // Simular ejecución de la respuesta sin modificar el estado real
            var simulatedState = CloneGameState(_runtime.CurrentState);

            // Analizar condiciones
            if (response.Condition != null)
            {
                var conditionAnalysis = await AnalyzeConditionAsync(response.Condition, simulatedState);
                analysis.ConditionResults.Add(conditionAnalysis);
                analysis.ExecutionPath.Add($"Evaluando condición: {response.Condition}");
            }

            // Simular ejecución de acciones
            foreach (var action in response.Actions)
            {
                var actionAnalysis = await SimulateActionAsync(action, simulatedState);
                analysis.ActionResults.Add(actionAnalysis);
                analysis.ExecutionPath.Add($"Ejecutando acción: {action.Function}");
            }

            analysis.WouldExecute = analysis.ConditionResults.All(cr => cr.Result);

        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Error analizando respuesta");
            analysis.Error = ex.Message;
        }

        return analysis;
    }

    /// <summary>
    /// Traza el procesamiento completo de un comando, desde el análisis
    /// sintáctico hasta la ejecución de acciones.
    /// </summary>
    private async Task TraceCommandProcessingAsync(string command, ExecutionTracer tracer)
    {
        tracer.StartTrace($"Procesando comando: '{command}'");

        try
        {
            // Fase 1: Análisis sintáctico
            tracer.AddEntry("Analizando comando con el parser de español");
            var gameContext = CreateGameContextFromRuntime();
            
            // Simular análisis sintáctico (en una implementación real, interceptaríamos el parser)
            tracer.AddEntry($"Comando normalizado y tokenizado");
            tracer.AddEntry($"Tipo de comando identificado: Manipulation");
            tracer.AddEntry($"Verbo extraído: 'coger'");
            tracer.AddEntry($"Objeto extraído: 'espada'");

            // Fase 2: Búsqueda de respuestas coincidentes
            tracer.AddEntry("Buscando respuestas coincidentes");
            
            // Simular búsqueda de respuestas
            var matchingResponses = await FindMatchingResponsesForTracing(command);
            foreach (var response in matchingResponses)
            {
                tracer.AddEntry($"Respuesta candidata encontrada: {string.Join(", ", response.Patterns)}");
                
                // Fase 3: Evaluación de condiciones
                if (response.Condition != null)
                {
                    tracer.AddEntry("Evaluando condiciones de la respuesta");
                    var conditionResult = await EvaluateConditionForTracing(response.Condition);
                    tracer.AddEntry($"Resultado de condición: {conditionResult}");
                }

                // Fase 4: Ejecución de acciones
                if (response.Actions.Any())
                {
                    tracer.AddEntry("Ejecutando acciones de la respuesta");
                    foreach (var action in response.Actions)
                    {
                        tracer.AddEntry($"Ejecutando acción: {action.Function}({string.Join(", ", action.Arguments)})");
                    }
                }
            }

        }
        catch (Exception ex)
        {
            tracer.AddEntry($"Error durante el procesamiento: {ex.Message}");
        }

        tracer.EndTrace();
    }

    /// <summary>
    /// Muestra una vista visual del estado actual del juego,
    /// incluyendo un mapa de localidades, inventario, y métricas.
    /// </summary>
    private async Task ShowGameStateAsync()
    {
        var state = await GetGameStateSnapshotAsync();
        
        EmitDebugEvent(DebugEventType.StateDisplayed, "Estado del juego actualizado", state);
    }

    private void EmitDebugEvent(DebugEventType type, string message, object? data = null)
    {
        DebugEvent?.Invoke(this, new DebugEventArgs
        {
            Type = type,
            Message = message,
            Data = data,
            Timestamp = DateTime.UtcNow
        });
    }

    // Métodos auxiliares para el trazado y análisis
    private GameContext CreateGameContextFromRuntime()
    {
        // Crear contexto de juego basado en el estado actual del runtime
        var context = new GameContext();
        
        // Añadir objetos visibles basándose en el estado actual
        // (implementación simplificada)
        
        return context;
    }

    private async Task<List<ModernResponse>> FindMatchingResponsesForTracing(string command)
    {
        // En una implementación real, usaríamos el matcher de respuestas real
        return new List<ModernResponse>();
    }

    private async Task<bool> EvaluateConditionForTracing(ModernCondition condition)
    {
        // En una implementación real, usaríamos el evaluador de condiciones real
        return true;
    }
}

// Clases de apoyo para el depurador
public class DebugSession
{
    public string SessionId { get; set; } = "";
    public ModernDaadGame Game { get; set; } = null!;
    public DebugConfiguration Configuration { get; set; } = new();
    public DateTime StartTime { get; set; }
    public List<DebugBreakpoint> Breakpoints { get; set; } = new();
}

public class DebugBreakpoint
{
    public string Id { get; set; } = "";
    public BreakpointType Type { get; set; }
    public string Condition { get; set; } = "";
    public bool IsEnabled { get; set; } = true;
    public int HitCount { get; set; } = 0;
}

public enum BreakpointType
{
    LocationChange,     // Pausar cuando el jugador cambie de localidad
    ObjectPickup,       // Pausar cuando se coja un objeto específico
    ScoreChange,        // Pausar cuando cambie la puntuación
    FlagSet,           // Pausar cuando se establezca una flag específica
    CommandPattern,     // Pausar en comandos que coincidan con un patrón
    Custom            // Breakpoint con condición personalizada
}

public class GameStateSnapshot
{
    public DateTime Timestamp { get; set; }
    public string CurrentLocation { get; set; } = "";
    public List<string> PlayerInventory { get; set; } = new();
    public Dictionary<string, bool> Flags { get; set; } = new();
    public Dictionary<string, int> Counters { get; set; } = new();
    public Dictionary<string, string> ObjectLocations { get; set; } = new();
    public int Score { get; set; }
    public int TurnCount { get; set; }
    
    // Información adicional para debugging
    public Dictionary<string, object> DebugInfo { get; set; } = new();
}

public enum DebugState
{
    Stopped,    // Depuración no iniciada
    Running,    // Ejecutándose normalmente
    Paused,     // Pausado esperando comando
    Stepping,   // Ejecutando un paso
    Error       // Error en la depuración
}

public enum DebugEventType
{
    SessionStarted,
    SessionEnded,
    BreakpointHit,
    BreakpointSet,
    StepCompleted,
    StateDisplayed,
    Error
}
```

Esta implementación de herramientas de desarrollo avanzadas proporciona una base sólida para un entorno de desarrollo profesional para DAAD Modernizado. En la siguiente parte (5.9) exploraremos cómo integrar todos estos componentes en un ecosistema cohesivo y las mejores prácticas para su uso efectivo.

