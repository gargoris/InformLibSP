# Sistema Parser DAAD Modernizado - Parte 5: Guía de Implementación

## Parte 5.9: Integración del Ecosistema Completo - Orquestando la Sinfonía Digital

### 5.9.1 Entendiendo la Arquitectura como un Organismo Vivo

Imagina por un momento una orquesta sinfónica. Cada músico es un virtuoso en su instrumento, cada sección tiene su papel específico, pero la magia real ocurre cuando todos tocan juntos bajo la dirección de un maestro conductor. Lo que escuchamos no es la suma de instrumentos individuales, sino algo completamente nuevo y trascendente que emerge de su coordinación perfecta.

Esto mismo sucede con el sistema DAAD Modernizado que hemos estado construyendo. Hemos desarrollado componentes extraordinarios de manera individual: un parser robusto que entiende la sintaxis moderna, un analizador de español que puede interpretar el lenguaje natural, un transpilador que mantiene compatibilidad con el pasado, y herramientas de desarrollo que facilitan el trabajo creativo. Pero el verdadero valor del sistema emerge cuando todos estos componentes trabajan en perfecta armonía.

La integración no se trata simplemente de hacer que las piezas encajen mecánicamente, como engranajes en una máquina. Se trata de crear un ecosistema donde cada componente no solo cumple su función individual, sino que también potencia y enriquece la funcionalidad de todos los demás componentes. Es la diferencia entre una colección de herramientas y un entorno de desarrollo verdaderamente integrado.

```csharp
// Integration/DaadEcosystem.cs
namespace DaadModernizado.Integration;

/// <summary>
/// El ecosistema integrado de DAAD Modernizado que orquesta todos los componentes
/// para proporcionar una experiencia de desarrollo fluida y coherente.
/// 
/// Esta clase actúa como el director de orquesta que coordina la interacción
/// entre parsing, ejecución, depuración, y todas las herramientas de desarrollo.
/// Piensa en ella como el cerebro central que entiende cómo cada parte del
/// sistema puede colaborar con las demás para crear valor exponencial.
/// </summary>
public class DaadEcosystem : IDisposable
{
    // Componentes centrales del ecosistema
    private readonly IServiceProvider _serviceProvider;
    private readonly ILogger<DaadEcosystem> _logger;
    
    // Servicios integrados
    private readonly IntegratedProjectManager _projectManager;
    private readonly RealTimeValidator _realTimeValidator;
    private readonly IntelligentCodeAssistant _codeAssistant;
    private readonly ContextualHelpSystem _helpSystem;
    private readonly CollaborativeWorkspace _workspace;

    // Estado del ecosistema
    private EcosystemState _currentState = EcosystemState.Initializing;
    private readonly Dictionary<string, ComponentHealth> _componentHealth = new();
    private readonly EventOrchestrator _eventOrchestrator;

    public DaadEcosystem(IServiceProvider serviceProvider)
    {
        _serviceProvider = serviceProvider;
        _logger = serviceProvider.GetRequiredService<ILogger<DaadEcosystem>>();
        
        // Inicializar el orquestador de eventos que coordina la comunicación
        // entre componentes de manera que cada uno pueda reaccionar a cambios
        // en otros sin crear dependencias rígidas
        _eventOrchestrator = new EventOrchestrator(_logger);
        
        // Inicializar servicios integrados que aprovechan la sinergia
        // entre múltiples componentes básicos
        _projectManager = new IntegratedProjectManager(serviceProvider, _eventOrchestrator);
        _realTimeValidator = new RealTimeValidator(serviceProvider, _eventOrchestrator);
        _codeAssistant = new IntelligentCodeAssistant(serviceProvider, _eventOrchestrator);
        _helpSystem = new ContextualHelpSystem(serviceProvider, _eventOrchestrator);
        _workspace = new CollaborativeWorkspace(serviceProvider, _eventOrchestrator);
        
        InitializeEcosystem();
    }

    /// <summary>
    /// Inicializa el ecosistema completo, estableciendo las conexiones entre
    /// componentes y configurando los flujos de información que permiten
    /// que el sistema funcione como una unidad coherente.
    /// </summary>
    private async void InitializeEcosystem()
    {
        try
        {
            _logger.LogInformation("Inicializando ecosistema DAAD Modernizado");
            _currentState = EcosystemState.Initializing;

            // Fase 1: Verificar disponibilidad de componentes base
            await VerifyComponentAvailabilityAsync();

            // Fase 2: Establecer canales de comunicación entre componentes
            SetupInterComponentCommunication();

            // Fase 3: Configurar flujos de trabajo integrados
            ConfigureIntegratedWorkflows();

            // Fase 4: Inicializar servicios de valor agregado
            await InitializeValueAddedServicesAsync();

            _currentState = EcosystemState.Ready;
            _logger.LogInformation("Ecosistema DAAD Modernizado listo para usar");

            // Notificar que el ecosistema está completamente operativo
            await _eventOrchestrator.BroadcastAsync(new EcosystemEvent
            {
                Type = EcosystemEventType.SystemReady,
                Message = "El ecosistema DAAD Modernizado está completamente operativo",
                Timestamp = DateTime.UtcNow
            });
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Error inicializando ecosistema");
            _currentState = EcosystemState.Error;
            throw;
        }
    }

    /// <summary>
    /// Establece los canales de comunicación que permiten que los componentes
    /// se enteren de cambios relevantes en otros componentes y reaccionen
    /// apropiadamente.
    /// 
    /// Por ejemplo, cuando el parser detecta un error en el código, el sistema
    /// de validación en tiempo real debe saberlo, el editor debe mostrar la
    /// indicación visual, y el sistema de ayuda puede ofrecer sugerencias
    /// contextuales para resolver el problema.
    /// </summary>
    private void SetupInterComponentCommunication()
    {
        _logger.LogDebug("Configurando comunicación entre componentes");

        // El parser notifica cambios en el modelo semántico
        _eventOrchestrator.Subscribe<ParseCompletedEvent>(async (parseEvent) =>
        {
            // Cuando se completa un parsing exitoso, múltiples componentes
            // necesitan actuar: el validador debe revisar la consistencia,
            // el asistente de código debe actualizar las sugerencias,
            // y el depurador debe actualizar sus breakpoints disponibles
            
            await _realTimeValidator.OnParseCompletedAsync(parseEvent);
            await _codeAssistant.OnSemanticModelUpdatedAsync(parseEvent.SemanticModel);
            
            if (parseEvent.Game != null)
            {
                await _helpSystem.OnGameStructureChangedAsync(parseEvent.Game);
            }
        });

        // El editor notifica cambios en el código
        _eventOrchestrator.Subscribe<CodeChangedEvent>(async (codeEvent) =>
        {
            // Cuando el código cambia, el parser necesita reanalizarlo,
            // el validador debe verificar errores en tiempo real,
            // y el asistente debe actualizar las sugerencias disponibles
            
            await _realTimeValidator.OnCodeChangedAsync(codeEvent);
            await _codeAssistant.OnCodeChangedAsync(codeEvent);
        });

        // El depurador notifica cambios en el estado del juego
        _eventOrchestrator.Subscribe<GameStateChangedEvent>(async (stateEvent) =>
        {
            // Cuando cambia el estado del juego durante depuración,
            // múltiples vistas pueden necesitar actualizarse: el mapa
            // de localidades, el inventario visual, las métricas de progreso
            
            await _workspace.OnGameStateChangedAsync(stateEvent);
            await _helpSystem.OnGameStateChangedAsync(stateEvent);
        });

        // El sistema de proyectos notifica cambios en la estructura
        _eventOrchestrator.Subscribe<ProjectStructureChangedEvent>(async (projectEvent) =>
        {
            // Cuando la estructura del proyecto cambia (archivos añadidos,
            // eliminados, renombrados), todos los componentes que mantienen
            // referencias internas deben actualizarse
            
            await _codeAssistant.OnProjectStructureChangedAsync(projectEvent);
            await _realTimeValidator.OnProjectStructureChangedAsync(projectEvent);
        });
    }

    /// <summary>
    /// Configura flujos de trabajo integrados que aprovechan la combinación
    /// de múltiples componentes para proporcionar funcionalidades que ningún
    /// componente individual podría ofrecer por sí solo.
    /// </summary>
    private void ConfigureIntegratedWorkflows()
    {
        _logger.LogDebug("Configurando flujos de trabajo integrados");

        // Flujo de trabajo: Desarrollo con validación en tiempo real
        ConfigureRealTimeValidationWorkflow();

        // Flujo de trabajo: Depuración con análisis contextual
        ConfigureContextualDebuggingWorkflow();

        // Flujo de trabajo: Refactoring con impacto semántico
        ConfigureSemanticRefactoringWorkflow();

        // Flujo de trabajo: Testing automático integrado
        ConfigureIntegratedTestingWorkflow();

        // Flujo de trabajo: Colaboración y versionado
        ConfigureCollaborativeWorkflow();
    }

    /// <summary>
    /// Configura el flujo de trabajo de validación en tiempo real que combina
    /// el parser, el validador semántico, y la interfaz de usuario para
    /// proporcionar retroalimentación inmediata sobre la calidad del código.
    /// </summary>
    private void ConfigureRealTimeValidationWorkflow()
    {
        // Este flujo de trabajo funciona como un equipo médico que monitorea
        // constantemente los signos vitales de un paciente. Cada cambio en
        // el código es como un latido del corazón que debe ser evaluado
        // inmediatamente para detectar cualquier anomalía.

        _realTimeValidator.Configure(options =>
        {
            // Validación sintáctica inmediata (mientras el usuario escribe)
            options.EnableSyntaxValidation = true;
            options.SyntaxValidationDelay = TimeSpan.FromMilliseconds(300);

            // Validación semántica inteligente (después de pausas en la escritura)
            options.EnableSemanticValidation = true;
            options.SemanticValidationDelay = TimeSpan.FromSeconds(1);

            // Validación de compatibilidad con DAAD clásico
            options.EnableCompatibilityValidation = true;
            options.CompatibilityValidationDelay = TimeSpan.FromSeconds(2);

            // Integración con el sistema de ayuda contextual
            options.EnableContextualHelp = true;
            options.AutoShowHelpForErrors = true;
        });
    }

    /// <summary>
    /// Configura el flujo de trabajo de depuración contextual que combina
    /// el motor de ejecución, el depurador visual, y el analizador de español
    /// para proporcionar una experiencia de depuración que entiende tanto
    /// el código como el contexto de la aventura.
    /// </summary>
    private void ConfigureContextualDebuggingWorkflow()
    {
        // La depuración contextual es como tener un asistente experto que
        // no solo puede pausar y examinar el código, sino que también entiende
        // la narrativa de la aventura y puede explicar por qué cierta lógica
        // tiene sentido o no en el contexto de la historia.

        var debuggingIntegrator = new DebuggingWorkflowIntegrator();
        
        debuggingIntegrator.Configure(config =>
        {
            // Integrar el analizador de español para interpretar comandos de depuración
            config.EnableSpanishDebugCommands = true;
            config.SpanishCommandPatterns = new[]
            {
                "parar en {localidad}",
                "examinar {objeto}",
                "mostrar estado del {jugador|juego}",
                "ejecutar hasta {condición}"
            };

            // Análisis narrativo automático durante depuración
            config.EnableNarrativeAnalysis = true;
            config.AnalyzePlayerJourney = true;
            config.TrackEmotionalArc = true;

            // Integración con el sistema de proyectos para contexto completo
            config.LoadProjectContext = true;
            config.ShowRelatedFiles = true;
        });
    }

    /// <summary>
    /// Inicializa servicios de valor agregado que emergen de la integración
    /// de múltiples componentes base, proporcionando capacidades que van
    /// más allá de la suma de las partes individuales.
    /// </summary>
    private async Task InitializeValueAddedServicesAsync()
    {
        _logger.LogDebug("Inicializando servicios de valor agregado");

        // Servicio de análisis narrativo inteligente
        await InitializeNarrativeAnalysisServiceAsync();

        // Servicio de optimización automática
        await InitializeAutoOptimizationServiceAsync();

        // Servicio de traducción y localización
        await InitializeLocalizationServiceAsync();

        // Servicio de métricas y analytics
        await InitializeAnalyticsServiceAsync();

        // Servicio de recomendaciones basadas en IA
        await InitializeIntelligentRecommendationsAsync();
    }

    /// <summary>
    /// Inicializa el servicio de análisis narrativo que examina la estructura
    /// de la aventura desde una perspectiva de diseño de narrativa interactiva,
    /// proporcionando insights sobre pacing, balance, y experiencia del jugador.
    /// </summary>
    private async Task InitializeNarrativeAnalysisServiceAsync()
    {
        var narrativeAnalyzer = _serviceProvider.GetRequiredService<INarrativeAnalyzer>();
        
        await narrativeAnalyzer.ConfigureAsync(options =>
        {
            // Análisis de estructura narrativa
            options.AnalyzeNarrativeStructure = true;
            options.DetectPlotHoles = true;
            options.AnalyzePacing = true;

            // Análisis de experiencia del jugador
            options.AnalyzePlayerAgency = true;
            options.DetectLinearityIssues = true;
            options.AnalyzeDifficultyProgression = true;

            // Análisis de elementos específicos del español
            options.AnalyzeSpanishLanguageFlow = true;
            options.DetectCulturalInconsistencies = true;
            options.AnalyzeDialogueNaturalness = true;
        });

        // Integrar con el validador para incluir recomendaciones narrativas
        _realTimeValidator.RegisterAnalyzer(narrativeAnalyzer);
    }

    /// <summary>
    /// Proporciona una vista unificada del estado de salud de todo el ecosistema,
    /// permitiendo identificar rápidamente cualquier componente que pueda estar
    /// experimentando problemas o degradación en el rendimiento.
    /// </summary>
    public async Task<EcosystemHealthReport> GetHealthReportAsync()
    {
        var report = new EcosystemHealthReport
        {
            Timestamp = DateTime.UtcNow,
            OverallHealth = EcosystemHealth.Unknown,
            ComponentReports = new Dictionary<string, ComponentHealthReport>()
        };

        try
        {
            // Verificar salud de componentes centrales
            var coreComponents = new[]
            {
                "Parser", "SpanishAnalyzer", "Transpiler", "Runtime",
                "Debugger", "ProjectManager", "Validator"
            };

            var healthChecks = new List<Task<ComponentHealthReport>>();

            foreach (var component in coreComponents)
            {
                healthChecks.Add(CheckComponentHealthAsync(component));
            }

            var results = await Task.WhenAll(healthChecks);

            foreach (var result in results)
            {
                report.ComponentReports[result.ComponentName] = result;
            }

            // Calcular salud general del ecosistema
            report.OverallHealth = CalculateOverallHealth(results);

            // Generar recomendaciones si hay problemas
            if (report.OverallHealth != EcosystemHealth.Healthy)
            {
                report.Recommendations = await GenerateHealthRecommendationsAsync(results);
            }

            _logger.LogInformation("Reporte de salud del ecosistema generado: {OverallHealth}", 
                report.OverallHealth);

            return report;
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Error generando reporte de salud del ecosistema");
            report.OverallHealth = EcosystemHealth.Critical;
            report.Error = ex.Message;
            return report;
        }
    }

    /// <summary>
    /// Verifica la salud de un componente específico del ecosistema,
    /// incluyendo métricas de rendimiento, utilización de recursos,
    /// y calidad de las respuestas.
    /// </summary>
    private async Task<ComponentHealthReport> CheckComponentHealthAsync(string componentName)
    {
        var report = new ComponentHealthReport
        {
            ComponentName = componentName,
            Timestamp = DateTime.UtcNow
        };

        try
        {
            switch (componentName.ToLowerInvariant())
            {
                case "parser":
                    report = await CheckParserHealthAsync();
                    break;
                case "spanishanalyzer":
                    report = await CheckSpanishAnalyzerHealthAsync();
                    break;
                case "transpiler":
                    report = await CheckTranspilerHealthAsync();
                    break;
                case "runtime":
                    report = await CheckRuntimeHealthAsync();
                    break;
                default:
                    report.Health = ComponentHealth.Unknown;
                    report.Message = $"Verificación de salud no implementada para {componentName}";
                    break;
            }
        }
        catch (Exception ex)
        {
            report.Health = ComponentHealth.Critical;
            report.Error = ex.Message;
            _logger.LogError(ex, "Error verificando salud del componente {ComponentName}", componentName);
        }

        return report;
    }

    /// <summary>
    /// Verifica específicamente la salud del parser, incluyendo tiempo de respuesta,
    /// tasa de éxito, y calidad de los mensajes de error producidos.
    /// </summary>
    private async Task<ComponentHealthReport> CheckParserHealthAsync()
    {
        var parser = _serviceProvider.GetRequiredService<IGameParser>();
        var report = new ComponentHealthReport { ComponentName = "Parser" };

        // Test de rendimiento: parsear una aventura de ejemplo
        var stopwatch = Stopwatch.StartNew();
        
        var testCode = """
            game {
              title: "Health Check"
              start: test_location
            }
            location test_location {
              desc: "Test location for health check"
            }
            """;

        var result = await parser.ParseAsync(testCode);
        stopwatch.Stop();

        // Evaluar métricas
        var responseTime = stopwatch.ElapsedMilliseconds;
        var parseSuccess = result.IsSuccess;

        // Determinar salud basándose en métricas
        if (parseSuccess && responseTime < 100)
        {
            report.Health = ComponentHealth.Healthy;
            report.Message = $"Parser funcionando óptimamente (tiempo: {responseTime}ms)";
        }
        else if (parseSuccess && responseTime < 500)
        {
            report.Health = ComponentHealth.Degraded;
            report.Message = $"Parser funcionando lentamente (tiempo: {responseTime}ms)";
        }
        else if (!parseSuccess)
        {
            report.Health = ComponentHealth.Critical;
            report.Message = "Parser fallando en código básico";
        }

        report.Metrics = new Dictionary<string, object>
        {
            ["response_time_ms"] = responseTime,
            ["parse_success"] = parseSuccess,
            ["error_count"] = result.Errors.Count
        };

        return report;
    }

    private async Task<ComponentHealthReport> CheckSpanishAnalyzerHealthAsync()
    {
        var analyzer = _serviceProvider.GetRequiredService<ISpanishSyntaxAnalyzer>();
        var report = new ComponentHealthReport { ComponentName = "SpanishAnalyzer" };

        try
        {
            // Crear un contexto de juego simple para testing
            var gameContext = new GameContext();
            gameContext.AddObject(new GameObject { Id = "test_object", Name = "objeto de prueba" });

            // Test de comandos básicos en español
            var testCommands = new[]
            {
                "mirar objeto",
                "coger objeto de prueba",
                "ir norte",
                "inventario"
            };

            var successCount = 0;
            var totalResponseTime = 0L;

            foreach (var command in testCommands)
            {
                var stopwatch = Stopwatch.StartNew();
                var result = analyzer.ParseCommand(command, gameContext);
                stopwatch.Stop();

                totalResponseTime += stopwatch.ElapsedMilliseconds;
                if (result.IsSuccess && result.ConfidenceScore > 0.7f)
                {
                    successCount++;
                }
            }

            var averageResponseTime = totalResponseTime / testCommands.Length;
            var successRate = (float)successCount / testCommands.Length;

            // Determinar salud
            if (successRate >= 0.9f && averageResponseTime < 50)
            {
                report.Health = ComponentHealth.Healthy;
                report.Message = $"Analizador de español funcionando óptimamente";
            }
            else if (successRate >= 0.7f && averageResponseTime < 200)
            {
                report.Health = ComponentHealth.Degraded;
                report.Message = $"Analizador de español con rendimiento reducido";
            }
            else
            {
                report.Health = ComponentHealth.Critical;
                report.Message = $"Analizador de español con problemas significativos";
            }

            report.Metrics = new Dictionary<string, object>
            {
                ["success_rate"] = successRate,
                ["average_response_time_ms"] = averageResponseTime,
                ["test_commands_count"] = testCommands.Length
            };
        }
        catch (Exception ex)
        {
            report.Health = ComponentHealth.Critical;
            report.Error = ex.Message;
        }

        return report;
    }

    private EcosystemHealth CalculateOverallHealth(ComponentHealthReport[] reports)
    {
        if (reports.Any(r => r.Health == ComponentHealth.Critical))
            return EcosystemHealth.Critical;
        
        if (reports.Count(r => r.Health == ComponentHealth.Degraded) > reports.Length / 2)
            return EcosystemHealth.Degraded;
        
        if (reports.All(r => r.Health == ComponentHealth.Healthy))
            return EcosystemHealth.Healthy;
        
        return EcosystemHealth.Warning;
    }

    public void Dispose()
    {
        _eventOrchestrator?.Dispose();
        _projectManager?.Dispose();
        _workspace?.Dispose();
    }
}

// Clases de apoyo para la integración del ecosistema
public enum EcosystemState
{
    Initializing,
    Ready,
    Degraded,
    Error
}

public enum EcosystemHealth
{
    Healthy,
    Warning,
    Degraded,
    Critical,
    Unknown
}

public enum ComponentHealth
{
    Healthy,
    Degraded,
    Critical,
    Unknown
}

public class EcosystemHealthReport
{
    public DateTime Timestamp { get; set; }
    public EcosystemHealth OverallHealth { get; set; }
    public Dictionary<string, ComponentHealthReport> ComponentReports { get; set; } = new();
    public List<string> Recommendations { get; set; } = new();
    public string? Error { get; set; }
}

public class ComponentHealthReport
{
    public string ComponentName { get; set; } = "";
    public DateTime Timestamp { get; set; }
    public ComponentHealth Health { get; set; }
    public string Message { get; set; } = "";
    public Dictionary<string, object> Metrics { get; set; } = new();
    public string? Error { get; set; }
}
```

### 5.9.2 Los Patrones de Integración: Conectando sin Acoplar

Uno de los desafíos más importantes en la construcción de un ecosistema integrado es lograr que los componentes trabajen juntos sin crear dependencias rígidas que hagan el sistema frágil y difícil de mantener. Es como diseñar una ciudad donde diferentes distritos pueden especializarse en sus funciones únicas, pero también pueden comunicarse y colaborar eficientemente cuando es necesario.

La clave está en usar patrones de integración que permitan comunicación rica entre componentes mientras mantienen su independencia. Esto se logra principalmente a través de eventos asincrónicos, interfaces bien definidas, y un sistema de mediación que coordina las interacciones complejas.

```csharp
// Integration/EventOrchestrator.cs
namespace DaadModernizado.Integration;

/// <summary>
/// Orquestador de eventos que coordina la comunicación entre componentes
/// del ecosistema de manera desacoplada y asíncrona.
/// 
/// Este sistema permite que los componentes publiquen eventos cuando algo
/// interesante sucede, y que otros componentes se suscriban a esos eventos
/// para reaccionar apropiadamente, sin que ningún componente necesite
/// conocer directamente a los demás.
/// </summary>
public class EventOrchestrator : IDisposable
{
    private readonly ILogger<EventOrchestrator> _logger;
    private readonly ConcurrentDictionary<Type, List<Func<object, Task>>> _subscribers = new();
    private readonly Channel<EventEnvelope> _eventChannel;
    private readonly ChannelWriter<EventEnvelope> _eventWriter;
    private readonly CancellationTokenSource _cancellationTokenSource = new();
    private readonly Task _processingTask;

    public EventOrchestrator(ILogger<EventOrchestrator> logger)
    {
        _logger = logger;
        
        // Crear canal para procesamiento asíncrono de eventos
        // Esto permite que la publicación de eventos sea muy rápida
        // mientras que el procesamiento puede tomar el tiempo necesario
        var channel = Channel.CreateUnbounded<EventEnvelope>();
        _eventChannel = channel;
        _eventWriter = channel.Writer;
        
        // Iniciar tarea de procesamiento en segundo plano
        _processingTask = ProcessEventsAsync(_cancellationTokenSource.Token);
    }

    /// <summary>
    /// Permite que un componente se suscriba a eventos de un tipo específico.
    /// El handler proporcionado será llamado cada vez que se publique un evento
    /// de ese tipo, permitiendo que el componente reaccione apropiadamente.
    /// </summary>
    public void Subscribe<T>(Func<T, Task> handler) where T : class
    {
        var eventType = typeof(T);
        
        _subscribers.AddOrUpdate(eventType,
            new List<Func<object, Task>> { evt => handler((T)evt) },
            (key, existing) =>
            {
                existing.Add(evt => handler((T)evt));
                return existing;
            });

        _logger.LogDebug("Suscriptor añadido para eventos de tipo {EventType}", eventType.Name);
    }

    /// <summary>
    /// Publica un evento de manera asíncrona, notificando a todos los
    /// suscriptores interesados. La publicación es no-bloqueante para
    /// garantizar que el componente que publica no se vea afectado por
    /// la velocidad de procesamiento de los suscriptores.
    /// </summary>
    public async Task PublishAsync<T>(T eventObject) where T : class
    {
        if (eventObject == null) return;

        var envelope = new EventEnvelope
        {
            EventType = typeof(T),
            EventData = eventObject,
            Timestamp = DateTime.UtcNow,
            CorrelationId = Guid.NewGuid().ToString()
        };

        // Enviar al canal para procesamiento asíncrono
        await _eventWriter.WriteAsync(envelope, _cancellationTokenSource.Token);

        _logger.LogDebug("Evento publicado: {EventType} (ID: {CorrelationId})", 
            typeof(T).Name, envelope.CorrelationId);
    }

    /// <summary>
    /// Procesa eventos del canal de manera asíncrona, distribuyendo cada
    /// evento a todos sus suscriptores registrados. Este procesamiento
    /// incluye manejo de errores robusto para garantizar que un suscriptor
    /// con problemas no afecte a los demás.
    /// </summary>
    private async Task ProcessEventsAsync(CancellationToken cancellationToken)
    {
        await foreach (var envelope in _eventChannel.Reader.ReadAllAsync(cancellationToken))
        {
            try
            {
                if (_subscribers.TryGetValue(envelope.EventType, out var handlers))
                {
                    // Ejecutar todos los handlers en paralelo para mejor rendimiento
                    var tasks = handlers.Select(async handler =>
                    {
                        try
                        {
                            await handler(envelope.EventData);
                        }
                        catch (Exception ex)
                        {
                            _logger.LogError(ex, "Error en handler de evento {EventType} (ID: {CorrelationId})", 
                                envelope.EventType.Name, envelope.CorrelationId);
                        }
                    });

                    await Task.WhenAll(tasks);
                }

                _logger.LogDebug("Evento procesado: {EventType} (ID: {CorrelationId})", 
                    envelope.EventType.Name, envelope.CorrelationId);
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error procesando evento {EventType} (ID: {CorrelationId})", 
                    envelope.EventType.Name, envelope.CorrelationId);
            }
        }
    }

    /// <summary>
    /// Proporciona un método conveniente para hacer broadcast de eventos del sistema
    /// que múltiples componentes pueden necesitar conocer.
    /// </summary>
    public async Task BroadcastAsync(EcosystemEvent systemEvent)
    {
        await PublishAsync(systemEvent);
        
        // Los eventos del sistema también se registran para auditoría
        _logger.LogInformation("Evento del sistema: {EventType} - {Message}", 
            systemEvent.Type, systemEvent.Message);
    }

    public void Dispose()
    {
        _cancellationTokenSource.Cancel();
        _eventWriter.Complete();
        
        try
        {
            _processingTask.Wait(TimeSpan.FromSeconds(5));
        }
        catch (Exception ex)
        {
            _logger.LogWarning(ex, "Timeout esperando finalización del procesamiento de eventos");
        }
        
        _cancellationTokenSource.Dispose();
    }
}

// Eventos específicos del ecosistema que coordinan la interacción entre componentes
public class ParseCompletedEvent
{
    public string FileName { get; set; } = "";
    public bool IsSuccess { get; set; }
    public ModernDaadGame? Game { get; set; }
    public SemanticModel SemanticModel { get; set; } = new();
    public List<ParseError> Errors { get; set; } = new();
    public TimeSpan ParseDuration { get; set; }
}

public class CodeChangedEvent
{
    public string FileName { get; set; } = "";
    public string NewContent { get; set; } = "";
    public TextRange ChangedRange { get; set; } = new();
    public ChangeType ChangeType { get; set; }
    public DateTime Timestamp { get; set; } = DateTime.UtcNow;
}

public class GameStateChangedEvent
{
    public string SessionId { get; set; } = "";
    public GameStateSnapshot OldState { get; set; } = new();
    public GameStateSnapshot NewState { get; set; } = new();
    public string TriggerCommand { get; set; } = "";
    public List<string> ChangedAspects { get; set; } = new();
}

public class ProjectStructureChangedEvent
{
    public string ProjectPath { get; set; } = "";
    public ProjectChangeType ChangeType { get; set; }
    public List<string> AffectedFiles { get; set; } = new();
    public Dictionary<string, object> Metadata { get; set; } = new();
}

public enum ProjectChangeType
{
    FileAdded,
    FileRemoved,
    FileRenamed,
    FolderAdded,
    FolderRemoved,
    ProjectRenamed,
    ConfigurationChanged
}

public enum ChangeType
{
    Insert,
    Delete,
    Replace,
    Move
}

public class TextRange
{
    public int StartLine { get; set; }
    public int StartColumn { get; set; }
    public int EndLine { get; set; }
    public int EndColumn { get; set; }
}

public class EcosystemEvent
{
    public EcosystemEventType Type { get; set; }
    public string Message { get; set; } = "";
    public DateTime Timestamp { get; set; }
    public Dictionary<string, object> Data { get; set; } = new();
}

public enum EcosystemEventType
{
    SystemReady,
    SystemShutdown,
    ComponentInitialized,
    ComponentError,
    WorkflowStarted,
    WorkflowCompleted,
    PerformanceWarning,
    SecurityAlert
}

private class EventEnvelope
{
    public Type EventType { get; set; } = typeof(object);
    public object EventData { get; set; } = new();
    public DateTime Timestamp { get; set; }
    public string CorrelationId { get; set; } = "";
}
```

Esta arquitectura de integración permite que el ecosistema DAAD Modernizado funcione como una unidad coherente mientras mantiene la flexibilidad para evolucionar y extenderse. En la próxima y final parte (5.10) exploraremos las mejores prácticas para implementar este sistema completo y el roadmap recomendado para llevarlo desde el concepto hasta la realidad funcional.

