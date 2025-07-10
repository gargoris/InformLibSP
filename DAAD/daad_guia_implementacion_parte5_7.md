# Sistema Parser DAAD Modernizado - Parte 5: Guía de Implementación

## Parte 5.7: Motor de Ejecución Básico - Dando Vida a las Aventuras

### 5.7.1 Entendiendo el Corazón del Sistema: El Motor de Ejecución

Imagina que has construido cuidadosamente el plano arquitectónico de una casa extraordinaria. Has diseñado cada habitación, planificado cada conexión, especificado cada detalle. Pero hasta que no construyas la casa y alguien pueda habitarla, seguirá siendo solo un conjunto de líneas en papel. Esto es exactamente lo que representa el Motor de Ejecución en nuestro sistema DAAD Modernizado.

Hasta ahora hemos construido las herramientas para crear aventuras: podemos parsear el código del desarrollador, validar su consistencia, transpilarlo a formatos clásicos, e incluso entender comandos en español natural. Pero todo esto sirve para crear una representación estática de una aventura. El Motor de Ejecución es lo que transforma esa representación en una experiencia viva y dinámica.

Piensa en el motor como el director de una obra teatral compleja. Debe mantener un seguimiento constante de dónde está cada actor (el jugador), qué props están en escena (objetos del juego), qué escenas están disponibles (localidades), y cómo responder cuando los actores improvisan (comandos del jugador). Más aún, debe hacer todo esto de manera que la experiencia se sienta natural y fluida para el usuario.

```csharp
// Runtime/IGameRuntime.cs
namespace DaadModernizado.Runtime;

/// <summary>
/// El motor de ejecución principal que mantiene el estado del juego
/// y procesa las acciones del jugador en tiempo real.
/// 
/// Este es el corazón palpitante de toda aventura DAAD Modernizada.
/// Transforma la representación estática del juego en una experiencia
/// interactiva y dinámica.
/// </summary>
public interface IGameRuntime
{
    // Estado del juego
    GameState CurrentState { get; }
    bool IsGameActive { get; }
    
    // Gestión del ciclo de vida
    Task<RuntimeResult> StartGameAsync(ModernDaadGame game, CancellationToken cancellationToken = default);
    Task<RuntimeResult> ProcessCommandAsync(string userInput, CancellationToken cancellationToken = default);
    Task<RuntimeResult> SaveGameAsync(string saveSlot, CancellationToken cancellationToken = default);
    Task<RuntimeResult> LoadGameAsync(string saveSlot, CancellationToken cancellationToken = default);
    
    // Eventos para la interfaz de usuario
    event EventHandler<GameMessageEventArgs> MessageGenerated;
    event EventHandler<LocationChangedEventArgs> LocationChanged;
    event EventHandler<InventoryChangedEventArgs> InventoryChanged;
    event EventHandler<ScoreChangedEventArgs> ScoreChanged;
    event EventHandler<GameEndedEventArgs> GameEnded;
}

/// <summary>
/// Representa el estado completo del juego en un momento específico.
/// Esto incluye todo lo necesario para restaurar exactamente la experiencia
/// del jugador: su ubicación, inventario, progreso, y el estado del mundo.
/// </summary>
public class GameState
{
    public string CurrentLocationId { get; set; } = "";
    public List<string> PlayerInventory { get; set; } = new();
    public Dictionary<string, bool> Flags { get; set; } = new();
    public Dictionary<string, int> Counters { get; set; } = new();
    public Dictionary<string, string> ObjectLocations { get; set; } = new();
    public int CurrentScore { get; set; }
    public int TurnCount { get; set; }
    public DateTime GameStartTime { get; set; }
    public TimeSpan PlayTime { get; set; }
    
    // Para debugging y análisis
    public List<string> CommandHistory { get; set; } = new();
    public Dictionary<string, object> CustomState { get; set; } = new();
}
```

### 5.7.2 La Arquitectura del Motor: Simplificando la Complejidad

El motor de ejecución debe manejar una complejidad considerable, pero podemos organizarla de manera que cada componente tenga una responsabilidad clara y bien definida. Piensa en esto como una cocina profesional donde cada chef tiene su estación específica, pero todos trabajan en coordinación para crear una experiencia culinaria excepcional.

La clave está en separar las preocupaciones: el motor principal orquesta la experiencia general, mientras que componentes especializados manejan aspectos específicos como el procesamiento de comandos, la gestión del estado, y la ejecución de lógica de juego.

```csharp
// Runtime/GameRuntime.cs
namespace DaadModernizado.Runtime;

/// <summary>
/// Implementación principal del motor de ejecución.
/// 
/// Esta clase actúa como el director de orquesta, coordinando todos
/// los aspectos de la experiencia de juego en tiempo real.
/// </summary>
public class GameRuntime : IGameRuntime
{
    private readonly ISpanishSyntaxAnalyzer _commandAnalyzer;
    private readonly ILogger<GameRuntime> _logger;
    
    // Componentes especializados del motor
    private readonly StateManager _stateManager;
    private readonly ActionExecutor _actionExecutor;
    private readonly ResponseMatcher _responseMatcher;
    private readonly ProcessRunner _processRunner;
    
    // Estado actual del juego
    private ModernDaadGame _game = null!;
    private GameState _currentState = new();
    private bool _isGameActive = false;

    public GameState CurrentState => _currentState;
    public bool IsGameActive => _isGameActive;

    // Eventos para comunicación con la interfaz de usuario
    public event EventHandler<GameMessageEventArgs>? MessageGenerated;
    public event EventHandler<LocationChangedEventArgs>? LocationChanged;
    public event EventHandler<InventoryChangedEventArgs>? InventoryChanged;
    public event EventHandler<ScoreChangedEventArgs>? ScoreChanged;
    public event EventHandler<GameEndedEventArgs>? GameEnded;

    public GameRuntime(
        ISpanishSyntaxAnalyzer commandAnalyzer,
        ILogger<GameRuntime> logger)
    {
        _commandAnalyzer = commandAnalyzer;
        _logger = logger;
        
        // Inicializar componentes especializados
        // Cada uno se encarga de un aspecto específico del motor
        _stateManager = new StateManager(logger);
        _actionExecutor = new ActionExecutor(this, logger);
        _responseMatcher = new ResponseMatcher(logger);
        _processRunner = new ProcessRunner(this, logger);
    }

    public async Task<RuntimeResult> StartGameAsync(ModernDaadGame game, CancellationToken cancellationToken = default)
    {
        try
        {
            _logger.LogInformation("Iniciando nueva partida: {GameTitle}", game.Metadata.Title);

            _game = game;
            
            // Inicializar estado del juego
            _currentState = await InitializeGameStateAsync(game);
            _isGameActive = true;

            // Mostrar mensaje de bienvenida si existe
            if (game.Messages.TryGetValue("bienvenida", out var welcomeMessage))
            {
                EmitMessage(welcomeMessage);
            }

            // Mostrar descripción de la localidad inicial
            await ShowCurrentLocationAsync();

            // Ejecutar procesos automáticos iniciales
            await _processRunner.RunAutoProcessesAsync();

            _logger.LogInformation("Partida iniciada exitosamente en localidad: {StartLocation}", 
                _currentState.CurrentLocationId);

            return RuntimeResult.Success("Juego iniciado exitosamente");
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Error iniciando partida");
            return RuntimeResult.Failure($"Error iniciando partida: {ex.Message}");
        }
    }

    public async Task<RuntimeResult> ProcessCommandAsync(string userInput, CancellationToken cancellationToken = default)
    {
        if (!_isGameActive)
            return RuntimeResult.Failure("No hay partida activa");

        try
        {
            _logger.LogDebug("Procesando comando: '{UserInput}'", userInput);

            // Incrementar contador de turnos
            _currentState.TurnCount++;
            _currentState.CommandHistory.Add(userInput);

            // Crear contexto de juego para el analizador de comandos
            var gameContext = CreateGameContext();

            // Analizar el comando del usuario usando nuestro analizador de español
            var parseResult = await _commandAnalyzer.ParseCommandAsync(userInput, gameContext, cancellationToken);

            if (!parseResult.IsSuccess)
            {
                // Si no entendimos el comando, proporcionar ayuda útil
                var suggestions = string.Join(", ", parseResult.Suggestions);
                var errorMessage = $"No entiendo '{userInput}'.";
                
                if (!string.IsNullOrEmpty(suggestions))
                    errorMessage += $" ¿Quisiste decir: {suggestions}?";

                EmitMessage(errorMessage);
                return RuntimeResult.Success("Comando no reconocido, sugerencias proporcionadas");
            }

            // Buscar respuesta apropiada para el comando parseado
            var response = await _responseMatcher.FindMatchingResponseAsync(parseResult.Command!, _game.Responses);

            if (response != null)
            {
                // Ejecutar la respuesta encontrada
                await ExecuteResponseAsync(response);
            }
            else
            {
                // No hay respuesta específica, usar comportamiento por defecto
                await ExecuteDefaultBehaviorAsync(parseResult.Command!);
            }

            // Ejecutar procesos automáticos después del comando
            await _processRunner.RunTurnProcessesAsync();

            return RuntimeResult.Success("Comando procesado exitosamente");
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Error procesando comando: '{UserInput}'", userInput);
            EmitMessage("Ocurrió un error interno. Por favor, intenta de nuevo.");
            return RuntimeResult.Failure($"Error procesando comando: {ex.Message}");
        }
    }

    /// <summary>
    /// Inicializa el estado del juego basándose en la definición de la aventura.
    /// Esto incluye colocar objetos en sus localidades iniciales, establecer
    /// flags y contadores por defecto, y posicionar al jugador.
    /// </summary>
    private async Task<GameState> InitializeGameStateAsync(ModernDaadGame game)
    {
        var state = new GameState
        {
            CurrentLocationId = game.Metadata.StartLocation,
            GameStartTime = DateTime.UtcNow,
            PlayTime = TimeSpan.Zero
        };

        // Colocar objetos en sus localidades iniciales
        foreach (var gameObject in game.Objects.Values)
        {
            if (!string.IsNullOrEmpty(gameObject.Location))
            {
                if (gameObject.Location.Equals("inventory", StringComparison.OrdinalIgnoreCase))
                {
                    // El objeto comienza en el inventario del jugador
                    state.PlayerInventory.Add(gameObject.Id);
                }
                else
                {
                    // El objeto comienza en una localidad específica
                    state.ObjectLocations[gameObject.Id] = gameObject.Location;
                }
            }
            else
            {
                // Objeto sin localización específica, colocarlo en "nowhere"
                state.ObjectLocations[gameObject.Id] = "nowhere";
            }
        }

        // Inicializar flags y contadores definidos en el juego
        foreach (var flagName in ExtractFlagNames(game))
        {
            state.Flags[flagName] = false;
        }

        foreach (var counterName in ExtractCounterNames(game))
        {
            state.Counters[counterName] = 0;
        }

        _logger.LogDebug("Estado inicial creado: {LocationCount} localidades, {ObjectCount} objetos", 
            game.Locations.Count, game.Objects.Count);

        return state;
    }

    /// <summary>
    /// Muestra la descripción de la localidad actual al jugador.
    /// Esto incluye la descripción principal, objetos visibles, y salidas disponibles.
    /// </summary>
    private async Task ShowCurrentLocationAsync()
    {
        if (!_game.Locations.TryGetValue(_currentState.CurrentLocationId, out var location))
        {
            EmitMessage($"Error: localidad '{_currentState.CurrentLocationId}' no encontrada.");
            return;
        }

        // Mostrar descripción principal de la localidad
        EmitMessage(location.Description);

        // Mostrar objetos visibles en la localidad
        var objectsHere = GetObjectsInLocation(_currentState.CurrentLocationId);
        if (objectsHere.Any())
        {
            var objectDescriptions = objectsHere
                .Where(objId => _game.Objects.ContainsKey(objId))
                .Select(objId => _game.Objects[objId].Name)
                .ToList();

            if (objectDescriptions.Any())
            {
                var objectList = string.Join(", ", objectDescriptions);
                EmitMessage($"Aquí puedes ver: {objectList}.");
            }
        }

        // Mostrar salidas disponibles de manera natural
        if (location.Exits.Any())
        {
            var exitList = string.Join(", ", location.Exits.Keys);
            EmitMessage($"Puedes ir hacia: {exitList}.");
        }
    }

    private GameContext CreateGameContext()
    {
        var context = new GameContext();

        // Añadir objetos visibles (en la localidad actual e inventario)
        var visibleObjects = GetObjectsInLocation(_currentState.CurrentLocationId)
            .Concat(_currentState.PlayerInventory);

        foreach (var objectId in visibleObjects)
        {
            if (_game.Objects.TryGetValue(objectId, out var gameObject))
            {
                context.AddObject(new GameObject
                {
                    Id = objectId,
                    Name = gameObject.Name,
                    IsVisible = true,
                    IsPresent = true,
                    IsCarried = _currentState.PlayerInventory.Contains(objectId)
                });
            }
        }

        // Añadir salidas disponibles
        if (_game.Locations.TryGetValue(_currentState.CurrentLocationId, out var currentLocation))
        {
            foreach (var exit in currentLocation.Exits.Keys)
            {
                context.AddAvailableExit(exit);
            }
        }

        return context;
    }

    private void EmitMessage(string message)
    {
        MessageGenerated?.Invoke(this, new GameMessageEventArgs(message));
    }

    private List<string> GetObjectsInLocation(string locationId)
    {
        return _currentState.ObjectLocations
            .Where(kvp => kvp.Value == locationId)
            .Select(kvp => kvp.Key)
            .ToList();
    }

    // Métodos auxiliares para extraer información del juego
    private HashSet<string> ExtractFlagNames(ModernDaadGame game)
    {
        var flagNames = new HashSet<string>();
        
        // Buscar referencias a flags en respuestas y procesos
        foreach (var response in game.Responses)
        {
            ExtractFlagNamesFromCondition(response.Condition, flagNames);
            ExtractFlagNamesFromActions(response.Actions, flagNames);
        }

        foreach (var process in game.Processes)
        {
            ExtractFlagNamesFromCondition(process.Condition, flagNames);
            ExtractFlagNamesFromActions(process.Actions, flagNames);
        }

        return flagNames;
    }

    private HashSet<string> ExtractCounterNames(ModernDaadGame game)
    {
        var counterNames = new HashSet<string>();
        
        // Similar al método anterior, pero buscando contadores
        foreach (var response in game.Responses)
        {
            ExtractCounterNamesFromCondition(response.Condition, counterNames);
            ExtractCounterNamesFromActions(response.Actions, counterNames);
        }

        foreach (var process in game.Processes)
        {
            ExtractCounterNamesFromCondition(process.Condition, counterNames);
            ExtractCounterNamesFromActions(process.Actions, counterNames);
        }

        return counterNames;
    }

    private void ExtractFlagNamesFromCondition(ModernCondition? condition, HashSet<string> flagNames)
    {
        if (condition == null) return;

        if (condition.Type == ConditionType.Simple && condition.Function == "flag")
        {
            if (condition.Arguments.Count > 0)
                flagNames.Add(condition.Arguments[0]);
        }
        else if (condition.Type == ConditionType.Logical)
        {
            ExtractFlagNamesFromCondition(condition.Left, flagNames);
            ExtractFlagNamesFromCondition(condition.Right, flagNames);
        }
    }

    private void ExtractFlagNamesFromActions(List<ModernAction> actions, HashSet<string> flagNames)
    {
        foreach (var action in actions)
        {
            if ((action.Function == "set_flag" || action.Function == "clear_flag") && action.Arguments.Count > 0)
            {
                flagNames.Add(action.Arguments[0]);
            }
        }
    }

    private void ExtractCounterNamesFromCondition(ModernCondition? condition, HashSet<string> counterNames)
    {
        if (condition == null) return;

        if (condition.Type == ConditionType.Simple && condition.Function == "counter")
        {
            if (condition.Arguments.Count > 0)
                counterNames.Add(condition.Arguments[0]);
        }
        else if (condition.Type == ConditionType.Logical)
        {
            ExtractCounterNamesFromCondition(condition.Left, counterNames);
            ExtractCounterNamesFromCondition(condition.Right, counterNames);
        }
    }

    private void ExtractCounterNamesFromActions(List<ModernAction> actions, HashSet<string> counterNames)
    {
        foreach (var action in actions)
        {
            if ((action.Function == "increment_counter" || action.Function == "decrement_counter" || 
                 action.Function == "set_counter") && action.Arguments.Count > 0)
            {
                counterNames.Add(action.Arguments[0]);
            }
        }
    }
}

// Clases de eventos para comunicación con la interfaz de usuario
public class GameMessageEventArgs : EventArgs
{
    public string Message { get; }
    public DateTime Timestamp { get; }

    public GameMessageEventArgs(string message)
    {
        Message = message;
        Timestamp = DateTime.UtcNow;
    }
}

public class LocationChangedEventArgs : EventArgs
{
    public string OldLocationId { get; }
    public string NewLocationId { get; }

    public LocationChangedEventArgs(string oldLocationId, string newLocationId)
    {
        OldLocationId = oldLocationId;
        NewLocationId = newLocationId;
    }
}

public class RuntimeResult
{
    public bool IsSuccess { get; init; }
    public string Message { get; init; } = "";
    public Exception? Exception { get; init; }

    public static RuntimeResult Success(string message = "") => 
        new() { IsSuccess = true, Message = message };

    public static RuntimeResult Failure(string message) => 
        new() { IsSuccess = false, Message = message };

    public static RuntimeResult Failure(Exception exception) => 
        new() { IsSuccess = false, Message = exception.Message, Exception = exception };
}
```

### 5.7.3 El Ejecutor de Acciones: Transformando Intenciones en Cambios

El ejecutor de acciones es donde las intenciones abstractas del desarrollador se convierten en cambios concretos en el estado del juego. Piensa en él como el técnico de efectos especiales en una producción teatral: cuando el director dice "que aparezca humo", el técnico sabe exactamente qué botones presionar y qué mecanismos activar para hacer que suceda la magia.

Cada acción en DAAD Modernizado representa una transformación específica del estado del mundo. "Take" mueve un objeto del mundo al inventario del jugador. "Goto" cambia la localización actual. "Message" comunica información al jugador. El ejecutor debe manejar estas transformaciones de manera consistente y predecible.

```csharp
// Runtime/ActionExecutor.cs
namespace DaadModernizado.Runtime;

/// <summary>
/// Ejecuta acciones específicas del juego, transformando el estado del mundo
/// según las instrucciones del desarrollador de la aventura.
/// 
/// Cada método corresponde a una acción específica disponible en el lenguaje DAAD.
/// </summary>
public class ActionExecutor
{
    private readonly GameRuntime _runtime;
    private readonly ILogger<ActionExecutor> _logger;

    public ActionExecutor(GameRuntime runtime, ILogger<ActionExecutor> logger)
    {
        _runtime = runtime;
        _logger = logger;
    }

    /// <summary>
    /// Ejecuta una acción específica basándose en su tipo y argumentos.
    /// Este es el punto de entrada principal para toda ejecución de acciones.
    /// </summary>
    public async Task<ActionResult> ExecuteActionAsync(ModernAction action, GameState state, ModernDaadGame game)
    {
        try
        {
            _logger.LogDebug("Ejecutando acción: {ActionFunction} con argumentos: [{Arguments}]", 
                action.Function, string.Join(", ", action.Arguments));

            // Despachar a la implementación específica según el tipo de acción
            var result = action.Function.ToLowerInvariant() switch
            {
                // Acciones de manipulación de objetos
                "take" => await ExecuteTakeAsync(action.Arguments, state, game),
                "drop" => await ExecuteDropAsync(action.Arguments, state, game),
                "destroy" => await ExecuteDestroyAsync(action.Arguments, state, game),
                "create" => await ExecuteCreateAsync(action.Arguments, state, game),

                // Acciones de movimiento
                "goto" => await ExecuteGotoAsync(action.Arguments, state, game),
                "place" => await ExecutePlaceAsync(action.Arguments, state, game),

                // Acciones de comunicación
                "message" => await ExecuteMessageAsync(action.Arguments, state, game),

                // Acciones de puntuación
                "add_score" => await ExecuteAddScoreAsync(action.Arguments, state, game),

                // Acciones de estado (flags y contadores)
                "set_flag" => await ExecuteSetFlagAsync(action.Arguments, state, game),
                "clear_flag" => await ExecuteClearFlagAsync(action.Arguments, state, game),
                "increment_counter" => await ExecuteIncrementCounterAsync(action.Arguments, state, game),
                "decrement_counter" => await ExecuteDecrementCounterAsync(action.Arguments, state, game),
                "set_counter" => await ExecuteSetCounterAsync(action.Arguments, state, game),

                // Acciones de control de flujo
                "done" => await ExecuteDoneAsync(action.Arguments, state, game),
                "end_game" => await ExecuteEndGameAsync(action.Arguments, state, game),
                "restart" => await ExecuteRestartAsync(action.Arguments, state, game),

                // Acciones condicionales (if, while) requieren manejo especial
                "if" => await ExecuteIfAsync(action, state, game),
                "while" => await ExecuteWhileAsync(action, state, game),

                _ => ActionResult.Failure($"Acción no reconocida: {action.Function}")
            };

            if (result.IsSuccess)
            {
                _logger.LogDebug("Acción ejecutada exitosamente: {ActionFunction}", action.Function);
            }
            else
            {
                _logger.LogWarning("Fallo ejecutando acción {ActionFunction}: {Error}", 
                    action.Function, result.Message);
            }

            return result;
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Error ejecutando acción: {ActionFunction}", action.Function);
            return ActionResult.Failure($"Error ejecutando acción: {ex.Message}");
        }
    }

    // === ACCIONES DE MANIPULACIÓN DE OBJETOS ===

    private async Task<ActionResult> ExecuteTakeAsync(List<string> args, GameState state, ModernDaadGame game)
    {
        if (args.Count != 1)
            return ActionResult.Failure("La acción 'take' requiere exactamente un argumento (objeto)");

        var objectId = args[0];

        // Verificar que el objeto existe
        if (!game.Objects.TryGetValue(objectId, out var gameObject))
            return ActionResult.Failure($"Objeto no encontrado: {objectId}");

        // Verificar que el objeto está presente en la localidad actual
        if (!state.ObjectLocations.TryGetValue(objectId, out var objectLocation) || 
            objectLocation != state.CurrentLocationId)
        {
            return ActionResult.Failure($"El objeto {gameObject.Name} no está aquí");
        }

        // Verificar que el objeto es cogible
        if (!gameObject.IsTakeable)
        {
            return ActionResult.Failure($"No puedes coger {gameObject.Name}");
        }

        // Verificar límites de peso/inventario si están definidos
        if (gameObject.Weight > 0)
        {
            var currentWeight = CalculateInventoryWeight(state, game);
            var maxWeight = 100; // Esto podría venir de la configuración del juego
            
            if (currentWeight + gameObject.Weight > maxWeight)
            {
                return ActionResult.Failure("Llevas demasiado peso");
            }
        }

        // Ejecutar la acción: mover objeto al inventario
        state.ObjectLocations[objectId] = "inventory";
        state.PlayerInventory.Add(objectId);

        _logger.LogInformation("Jugador cogió objeto: {ObjectName}", gameObject.Name);

        // Notificar cambio de inventario
        _runtime.EmitInventoryChanged(objectId, true);

        return ActionResult.Success($"Coges {gameObject.Name}");
    }

    private async Task<ActionResult> ExecuteDropAsync(List<string> args, GameState state, ModernDaadGame game)
    {
        if (args.Count != 1)
            return ActionResult.Failure("La acción 'drop' requiere exactamente un argumento (objeto)");

        var objectId = args[0];

        // Verificar que el jugador lleva el objeto
        if (!state.PlayerInventory.Contains(objectId))
        {
            if (game.Objects.TryGetValue(objectId, out var obj))
                return ActionResult.Failure($"No llevas {obj.Name}");
            else
                return ActionResult.Failure($"Objeto no encontrado: {objectId}");
        }

        // Ejecutar la acción: mover objeto a la localidad actual
        state.PlayerInventory.Remove(objectId);
        state.ObjectLocations[objectId] = state.CurrentLocationId;

        var gameObject = game.Objects[objectId];
        _logger.LogInformation("Jugador dejó objeto: {ObjectName}", gameObject.Name);

        // Notificar cambio de inventario
        _runtime.EmitInventoryChanged(objectId, false);

        return ActionResult.Success($"Dejas {gameObject.Name}");
    }

    // === ACCIONES DE MOVIMIENTO ===

    private async Task<ActionResult> ExecuteGotoAsync(List<string> args, GameState state, ModernDaadGame game)
    {
        if (args.Count != 1)
            return ActionResult.Failure("La acción 'goto' requiere exactamente un argumento (localidad)");

        var destinationId = args[0];

        // Verificar que la localidad destino existe
        if (!game.Locations.ContainsKey(destinationId))
            return ActionResult.Failure($"Localidad no encontrada: {destinationId}");

        var oldLocation = state.CurrentLocationId;
        state.CurrentLocationId = destinationId;

        _logger.LogInformation("Jugador se movió de {OldLocation} a {NewLocation}", 
            oldLocation, destinationId);

        // Notificar cambio de localidad
        _runtime.EmitLocationChanged(oldLocation, destinationId);

        // Mostrar descripción de la nueva localidad
        await _runtime.ShowCurrentLocationAsync();

        return ActionResult.Success();
    }

    // === ACCIONES DE COMUNICACIÓN ===

    private async Task<ActionResult> ExecuteMessageAsync(List<string> args, GameState state, ModernDaadGame game)
    {
        if (args.Count != 1)
            return ActionResult.Failure("La acción 'message' requiere exactamente un argumento (ID del mensaje)");

        var messageId = args[0];

        // Buscar el mensaje en la colección de mensajes del juego
        if (!game.Messages.TryGetValue(messageId, out var messageText))
        {
            // Si no se encuentra como ID, tratarlo como texto literal
            messageText = messageId;
        }

        // Enviar mensaje al jugador
        _runtime.EmitMessage(messageText);

        return ActionResult.Success();
    }

    // === ACCIONES DE PUNTUACIÓN ===

    private async Task<ActionResult> ExecuteAddScoreAsync(List<string> args, GameState state, ModernDaadGame game)
    {
        if (args.Count != 1)
            return ActionResult.Failure("La acción 'add_score' requiere exactamente un argumento (puntos)");

        if (!int.TryParse(args[0], out var points))
            return ActionResult.Failure($"Valor de puntuación inválido: {args[0]}");

        var oldScore = state.CurrentScore;
        state.CurrentScore += points;

        // Aplicar límite máximo si está definido
        if (game.Metadata.MaxScore > 0 && state.CurrentScore > game.Metadata.MaxScore)
        {
            state.CurrentScore = game.Metadata.MaxScore;
        }

        _logger.LogInformation("Puntuación cambiada: {OldScore} → {NewScore} (+{Points})", 
            oldScore, state.CurrentScore, points);

        // Notificar cambio de puntuación
        _runtime.EmitScoreChanged(oldScore, state.CurrentScore);

        return ActionResult.Success();
    }

    // === ACCIONES DE ESTADO ===

    private async Task<ActionResult> ExecuteSetFlagAsync(List<string> args, GameState state, ModernDaadGame game)
    {
        if (args.Count != 1)
            return ActionResult.Failure("La acción 'set_flag' requiere exactamente un argumento (nombre del flag)");

        var flagName = args[0];
        state.Flags[flagName] = true;

        _logger.LogDebug("Flag establecido: {FlagName} = true", flagName);
        return ActionResult.Success();
    }

    private async Task<ActionResult> ExecuteClearFlagAsync(List<string> args, GameState state, ModernDaadGame game)
    {
        if (args.Count != 1)
            return ActionResult.Failure("La acción 'clear_flag' requiere exactamente un argumento (nombre del flag)");

        var flagName = args[0];
        state.Flags[flagName] = false;

        _logger.LogDebug("Flag limpiado: {FlagName} = false", flagName);
        return ActionResult.Success();
    }

    // === ACCIONES DE CONTROL DE FLUJO ===

    private async Task<ActionResult> ExecuteIfAsync(ModernAction action, GameState state, ModernDaadGame game)
    {
        if (action.ConditionExpression == null)
            return ActionResult.Failure("La estructura 'if' requiere una condición");

        // Evaluar la condición
        var conditionEvaluator = new ConditionEvaluator(_logger);
        var conditionResult = await conditionEvaluator.EvaluateAsync(action.ConditionExpression, state, game);

        if (conditionResult)
        {
            // Ejecutar acciones del bloque 'then'
            if (action.ThenActions != null)
            {
                foreach (var thenAction in action.ThenActions)
                {
                    var result = await ExecuteActionAsync(thenAction, state, game);
                    if (!result.IsSuccess)
                        return result; // Propagar error
                }
            }
        }
        else
        {
            // Ejecutar acciones del bloque 'else' si existe
            if (action.ElseActions != null)
            {
                foreach (var elseAction in action.ElseActions)
                {
                    var result = await ExecuteActionAsync(elseAction, state, game);
                    if (!result.IsSuccess)
                        return result; // Propagar error
                }
            }
        }

        return ActionResult.Success();
    }

    private async Task<ActionResult> ExecuteDoneAsync(List<string> args, GameState state, ModernDaadGame game)
    {
        // 'done' significa que hemos terminado de procesar esta respuesta
        // En el contexto del ejecutor, esto se maneja a nivel superior
        return ActionResult.Success().WithStopProcessing();
    }

    private async Task<ActionResult> ExecuteEndGameAsync(List<string> args, GameState state, ModernDaadGame game)
    {
        _logger.LogInformation("Finalizando juego por acción 'end_game'");

        // Notificar fin del juego
        _runtime.EmitGameEnded(GameEndReason.Victory, "¡Has completado la aventura!");

        return ActionResult.Success().WithGameEnd();
    }

    // === MÉTODOS AUXILIARES ===

    private int CalculateInventoryWeight(GameState state, ModernDaadGame game)
    {
        return state.PlayerInventory
            .Where(objId => game.Objects.ContainsKey(objId))
            .Sum(objId => game.Objects[objId].Weight);
    }
}

/// <summary>
/// Resultado de ejecutar una acción específica.
/// Incluye información sobre éxito/fallo y cualquier efecto especial.
/// </summary>
public class ActionResult
{
    public bool IsSuccess { get; init; }
    public string Message { get; init; } = "";
    public bool StopProcessing { get; init; } = false;
    public bool EndGame { get; init; } = false;

    public static ActionResult Success(string message = "") => 
        new() { IsSuccess = true, Message = message };

    public static ActionResult Failure(string message) => 
        new() { IsSuccess = false, Message = message };

    public ActionResult WithStopProcessing() => 
        this with { StopProcessing = true };

    public ActionResult WithGameEnd() => 
        this with { EndGame = true };
}
```

Esta implementación del Motor de Ejecución proporciona la funcionalidad básica necesaria para ejecutar aventuras DAAD Modernizadas. En la siguiente parte (5.8) exploraremos las herramientas de desarrollo avanzadas que hacen que trabajar con este sistema sea una experiencia fluida y productiva para los creadores de aventuras.

