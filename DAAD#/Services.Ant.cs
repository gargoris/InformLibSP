// =====================================================================
// DAAD Moderno - Servicios Adicionales y Configuración
// Implementaciones de interfaces y servicios de apoyo
// =====================================================================

using System.Text.Json;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Configuration;
using System.Collections.Generic;

namespace DaadModern.Services
{
    #region Interfaces Principales

    /// <summary>
    /// Parser principal para DAAD Moderno usando Pidgin
    /// </summary>
    public interface IDaadParser
    {
        ParseResult<DaadProgram> ParseProgram(string source);
        ParseResult<Section> ParseSection(string source);
        ParseResult<Condition> ParseCondition(string source);
        ParseResult<Action> ParseAction(string source);
    }

    /// <summary>
    /// Transpilador a DAAD clásico
    /// </summary>
    public interface IClassicTranspiler
    {
        TranspileResult TranspileToClassic(DaadProgram program, ClassicPlatform target);
        string GenerateClassicSource(DaadProgram program);
        ValidationResult ValidateCompatibility(DaadProgram program);
    }

    /// <summary>
    /// Transpilador desde DAAD clásico
    /// </summary>
    public interface IModernTranspiler
    {
        TranspileResult TranspileToModern(string classicSource);
        DaadProgram ParseClassicSource(string source);
        ModernizationReport GenerateModernizationReport(string classicSource);
    }

    /// <summary>
    /// Servicio de análisis de aventuras
    /// </summary>
    public interface IGameAnalyzer
    {
        AnalysisReport AnalyzeGame(DaadProgram program);
        ComplexityMetrics CalculateComplexity(DaadProgram program);
        VocabularyAnalysis AnalyzeVocabulary(DaadProgram program);
        FlowAnalysis AnalyzeGameFlow(DaadProgram program);
    }

    /// <summary>
    /// Generador de bytecode firmado
    /// </summary>
    public interface ICodeGenerator
    {
        BytecodeResult GenerateBytecode(DaadProgram program);
        SignedBytecode SignBytecode(byte[] bytecode, SigningOptions options);
        ValidationResult ValidateBytecode(SignedBytecode bytecode);
    }

    /// <summary>
    /// Motor de ejecución de aventuras
    /// </summary>
    public interface IGameRuntime
    {
        Task<RuntimeResult> ExecuteGameAsync(SignedBytecode bytecode, RuntimeOptions options);
        GameState LoadGameState(SignedBytecode bytecode);
        Task<CommandResult> ProcessPlayerCommandAsync(string command, GameState state);
    }

    #endregion

    #region Implementaciones de Servicios

    /// <summary>
    /// Parser principal implementado con Pidgin
    /// </summary>
    public class DaadPidginParser : IDaadParser
    {
        private readonly ILogger<DaadPidginParser> _logger;

        public DaadPidginParser(ILogger<DaadPidginParser> logger)
        {
            _logger = logger;
        }

        public ParseResult<DaadProgram> ParseProgram(string source)
        {
            try
            {
                _logger.LogDebug("Iniciando parsing de programa DAAD");
                var result = DaadParser.ParseProgram(source);
                
                if (result.Success)
                {
                    _logger.LogInformation("Programa parseado exitosamente");
                    return ParseResult<DaadProgram>.Success(result.Value);
                }
                else
                {
                    _logger.LogError("Error al parsear programa: {Error}", result.Error);
                    return ParseResult<DaadProgram>.Failure(result.Error?.ToString() ?? "Error desconocido");
                }
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Excepción durante el parsing");
                return ParseResult<DaadProgram>.Failure($"Excepción: {ex.Message}");
            }
        }

        public ParseResult<Section> ParseSection(string source)
        {
            var result = DaadParser.ParseSection(source);
            return result.Success 
                ? ParseResult<Section>.Success(result.Value)
                : ParseResult<Section>.Failure(result.Error?.ToString() ?? "Error");
        }

        public ParseResult<Condition> ParseCondition(string source)
        {
            var result = DaadParser.ParseCondition(source);
            return result.Success 
                ? ParseResult<Condition>.Success(result.Value)
                : ParseResult<Condition>.Failure(result.Error?.ToString() ?? "Error");
        }

        public ParseResult<Action> ParseAction(string source)
        {
            var result = DaadParser.ParseAction(source);
            return result.Success 
                ? ParseResult<Action>.Success(result.Value)
                : ParseResult<Action>.Failure(result.Error?.ToString() ?? "Error");
        }
    }

    /// <summary>
    /// Transpilador completo a DAAD clásico
    /// </summary>
    public class ClassicDaadTranspiler : IClassicTranspiler
    {
        private readonly ILogger<ClassicDaadTranspiler> _logger;
        private readonly ExtendedClassicTranspiler _extendedTranspiler;

        public ClassicDaadTranspiler(ILogger<ClassicDaadTranspiler> logger)
        {
            _logger = logger;
            _extendedTranspiler = new ExtendedClassicTranspiler(
                logger.CreateLogger<ExtendedClassicTranspiler>());
        }

        public TranspileResult TranspileToClassic(DaadProgram program, ClassicPlatform target)
        {
            try
            {
                _logger.LogInformation("Transpilando a DAAD clásico para {Platform}", target);
                
                var classicSource = GenerateClassicSource(program);
                var validation = ValidateCompatibility(program);
                
                return new TranspileResult
                {
                    Success = validation.IsValid,
                    GeneratedCode = classicSource,
                    Validation = validation,
                    TargetPlatform = target
                };
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error durante transpilación");
                return TranspileResult.Failure($"Error: {ex.Message}");
            }
        }

        public string GenerateClassicSource(DaadProgram program)
        {
            var builder = new StringBuilder();
            
            // Generar header
            builder.AppendLine("; Generado por DAAD Moderno");
            builder.AppendLine($"; Fecha: {DateTime.Now:yyyy-MM-dd HH:mm:ss}");
            builder.AppendLine();
            
            // Generar secciones
            builder.AppendLine(GenerateControlSection(program));
            builder.AppendLine(GenerateVocabularySection(program));
            builder.AppendLine(GenerateMessagesSection(program));
            builder.AppendLine(GenerateConnectionsSection(program));
            builder.AppendLine(GenerateObjectsSection(program));
            builder.AppendLine(GenerateProcessesSection(program));
            
            return builder.ToString();
        }

        public ValidationResult ValidateCompatibility(DaadProgram program)
        {
            var issues = new List<ValidationIssue>();
            
            // Validar condactos soportados
            foreach (var section in program.Sections.OfType<ResponsesSection>())
            {
                foreach (var response in section.Responses)
                {
                    ValidateResponse(response, issues);
                }
            }
            
            // Validar limites de DAAD clásico
            ValidateClassicLimits(program, issues);
            
            return new ValidationResult
            {
                IsValid = !issues.Any(i => i.Severity == ValidationSeverity.Error),
                Issues = issues
            };
        }

        private string GenerateControlSection(DaadProgram program)
        {
            var gameSection = program.Sections.OfType<GameSection>().FirstOrDefault();
            if (gameSection == null) return "/CTL\n/END\n";
            
            var builder = new StringBuilder();
            builder.AppendLine("/CTL");
            
            foreach (var prop in gameSection.Properties)
            {
                string line = prop.Name.ToLower() switch
                {
                    "start_location" => $"Player start location: {GetLocationNumber(prop.Value)}",
                    "max_score" => $"Maximum score: {prop.Value}",
                    "time_limit" => $"Time limit: {prop.Value}",
                    _ => $"; {prop.Name}: {prop.Value}"
                };
                builder.AppendLine(line);
            }
            
            builder.AppendLine("/END");
            return builder.ToString();
        }

        private string GenerateVocabularySection(DaadProgram program)
        {
            var vocabSection = program.Sections.OfType<VocabSection>().FirstOrDefault();
            if (vocabSection == null) return "/VOC\n/END\n";
            
            var builder = new StringBuilder();
            builder.AppendLine("/VOC");
            
            foreach (var category in vocabSection.Categories)
            {
                foreach (var entry in category.Entries)
                {
                    foreach (var word in entry.Words)
                    {
                        builder.AppendLine($"{word} {entry.Number}");
                    }
                }
            }
            
            builder.AppendLine("/END");
            return builder.ToString();
        }

        private string GenerateProcessesSection(DaadProgram program)
        {
            var processSection = program.Sections.OfType<ProcessesSection>().FirstOrDefault();
            var responseSection = program.Sections.OfType<ResponsesSection>().FirstOrDefault();
            
            var builder = new StringBuilder();
            builder.AppendLine("/PRO");
            
            // Generar procesos del sistema
            if (processSection != null)
            {
                foreach (var process in processSection.Processes)
                {
                    GenerateProcess(process, builder);
                }
            }
            
            // Generar respuestas como proceso 5
            if (responseSection != null)
            {
                builder.AppendLine();
                builder.AppendLine("; Proceso 5 - Command decoder");
                
                foreach (var response in responseSection.Responses)
                {
                    GenerateResponse(response, builder);
                }
            }
            
            builder.AppendLine("/END");
            return builder.ToString();
        }

        private void GenerateResponse(ResponseDefinition response, StringBuilder builder)
        {
            foreach (var pattern in response.Patterns)
            {
                if (pattern is SimplePattern simple)
                {
                    var (verb, noun) = ParsePattern(simple.Text);
                    builder.AppendLine($"> {verb} {noun}");
                    
                    // Generar condiciones
                    if (response.Condition != null)
                    {
                        var condacts = _extendedTranspiler.TranspileCondition(response.Condition);
                        foreach (var condact in condacts)
                        {
                            builder.AppendLine($"  {condact.Name} {string.Join(" ", condact.Parameters)}");
                        }
                    }
                    
                    // Generar acciones
                    var actionCondacts = _extendedTranspiler.TranspileActions(response.ActionBlock);
                    foreach (var condact in actionCondacts)
                    {
                        builder.AppendLine($"  {condact.Name} {string.Join(" ", condact.Parameters)}");
                    }
                    
                    builder.AppendLine("  DONE");
                }
            }
        }

        // Métodos de utilidad...
        private int GetLocationNumber(Value value) => 1; // Simplificado
        private (string verb, string noun) ParsePattern(string pattern) => ("VERB", "NOUN"); // Simplificado
    }

    /// <summary>
    /// Analizador de aventuras completo
    /// </summary>
    public class GameAnalyzer : IGameAnalyzer
    {
        private readonly ILogger<GameAnalyzer> _logger;

        public GameAnalyzer(ILogger<GameAnalyzer> logger)
        {
            _logger = logger;
        }

        public AnalysisReport AnalyzeGame(DaadProgram program)
        {
            _logger.LogInformation("Iniciando análisis completo del juego");
            
            return new AnalysisReport
            {
                ComplexityMetrics = CalculateComplexity(program),
                VocabularyAnalysis = AnalyzeVocabulary(program),
                FlowAnalysis = AnalyzeGameFlow(program),
                GeneratedAt = DateTime.UtcNow
            };
        }

        public ComplexityMetrics CalculateComplexity(DaadProgram program)
        {
            var locations = program.Sections.OfType<LocationsSection>().Sum(s => s.Locations.Count);
            var objects = program.Sections.OfType<ObjectsSection>().Sum(s => s.Objects.Count);
            var responses = program.Sections.OfType<ResponsesSection>().Sum(s => s.Responses.Count);
            var processes = program.Sections.OfType<ProcessesSection>().Sum(s => s.Processes.Count);
            
            var complexity = (locations * 2) + (objects * 1.5) + (responses * 3) + (processes * 4);
            
            return new ComplexityMetrics
            {
                TotalLocations = locations,
                TotalObjects = objects,
                TotalResponses = responses,
                TotalProcesses = processes,
                ComplexityScore = (int)complexity,
                ComplexityLevel = complexity switch
                {
                    < 100 => "Básico",
                    < 500 => "Intermedio", 
                    < 1000 => "Avanzado",
                    _ => "Experto"
                }
            };
        }

        public VocabularyAnalysis AnalyzeVocabulary(DaadProgram program)
        {
            var vocabSection = program.Sections.OfType<VocabSection>().FirstOrDefault();
            if (vocabSection == null)
                return new VocabularyAnalysis { TotalWords = 0, Categories = new() };
            
            var analysis = new VocabularyAnalysis();
            
            foreach (var category in vocabSection.Categories)
            {
                var categoryAnalysis = new VocabularyCategoryAnalysis
                {
                    Name = category.Type,
                    WordCount = category.Entries.Sum(e => e.Words.Count),
                    UniqueEntries = category.Entries.Count
                };
                
                analysis.Categories.Add(categoryAnalysis);
                analysis.TotalWords += categoryAnalysis.WordCount;
            }
            
            return analysis;
        }

        public FlowAnalysis AnalyzeGameFlow(DaadProgram program)
        {
            // Análisis de flujo del juego
            var locations = program.Sections.OfType<LocationsSection>()
                .SelectMany(s => s.Locations).ToList();
            
            var connections = locations
                .SelectMany(l => l.Properties.OfType<LocationProperty>()
                    .Where(p => p.Name == "connections"))
                .Count();
            
            var deadEnds = locations.Count(l => GetConnectionCount(l) <= 1);
            var hubs = locations.Count(l => GetConnectionCount(l) >= 4);
            
            return new FlowAnalysis
            {
                TotalConnections = connections,
                DeadEnds = deadEnds,
                Hubs = hubs,
                AverageConnections = locations.Count > 0 ? (double)connections / locations.Count : 0,
                IsLinear = connections <= locations.Count,
                Complexity = connections > locations.Count * 1.5 ? "Alta" : "Media"
            };
        }

        private int GetConnectionCount(LocationDefinition location)
        {
            return location.Properties
                .Where(p => p.Name == "connections")
                .Count(); // Simplificado
        }
    }

    #endregion

    #region Modelos de Datos

    public class ParseResult<T>
    {
        public bool Success { get; private set; }
        public T? Value { get; private set; }
        public string? Error { get; private set; }

        private ParseResult() { }

        public static ParseResult<T> Success(T value) => new() { Success = true, Value = value };
        public static ParseResult<T> Failure(string error) => new() { Success = false, Error = error };
    }

    public class TranspileResult
    {
        public bool Success { get; set; }
        public string? GeneratedCode { get; set; }
        public ValidationResult? Validation { get; set; }
        public ClassicPlatform TargetPlatform { get; set; }
        public string? Error { get; set; }

        public static TranspileResult Failure(string error) => new() { Success = false, Error = error };
    }

    public class ValidationResult
    {
        public bool IsValid { get; set; }
        public List<ValidationIssue> Issues { get; set; } = new();
    }

    public class ValidationIssue
    {
        public ValidationSeverity Severity { get; set; }
        public string Message { get; set; } = "";
        public string? Location { get; set; }
        public int? LineNumber { get; set; }
    }

    public enum ValidationSeverity
    {
        Info,
        Warning,
        Error
    }

    public class AnalysisReport
    {
        public ComplexityMetrics ComplexityMetrics { get; set; } = new();
        public VocabularyAnalysis VocabularyAnalysis { get; set; } = new();
        public FlowAnalysis FlowAnalysis { get; set; } = new();
        public DateTime GeneratedAt { get; set; }
    }

    public class ComplexityMetrics
    {
        public int TotalLocations { get; set; }
        public int TotalObjects { get; set; }
        public int TotalResponses { get; set; }
        public int TotalProcesses { get; set; }
        public int ComplexityScore { get; set; }
        public string ComplexityLevel { get; set; } = "";
    }

    public class VocabularyAnalysis
    {
        public int TotalWords { get; set; }
        public List<VocabularyCategoryAnalysis> Categories { get; set; } = new();
    }

    public class VocabularyCategoryAnalysis
    {
        public string Name { get; set; } = "";
        public int WordCount { get; set; }
        public int UniqueEntries { get; set; }
    }

    public class FlowAnalysis
    {
        public int TotalConnections { get; set; }
        public int DeadEnds { get; set; }
        public int Hubs { get; set; }
        public double AverageConnections { get; set; }
        public bool IsLinear { get; set; }
        public string Complexity { get; set; } = "";
    }

    public class BytecodeResult
    {
        public bool Success { get; set; }
        public byte[]? Bytecode { get; set; }
        public string? Error { get; set; }
    }

    public class SignedBytecode
    {
        public byte[] Bytecode { get; set; } = Array.Empty<byte>();
        public byte[] Signature { get; set; } = Array.Empty<byte>();
        public string Algorithm { get; set; } = "";
        public DateTime SignedAt { get; set; }
    }

    public class RuntimeOptions
    {
        public bool DebugMode { get; set; }
        public bool StepMode { get; set; }
        public string? SaveFile { get; set; }
    }

    public class RuntimeResult
    {
        public bool Success { get; set; }
        public GameState? FinalState { get; set; }
        public string? Error { get; set; }
    }

    public class GameState
    {
        public int CurrentLocation { get; set; }
        public Dictionary<int, int> ObjectLocations { get; set; } = new();
        public Dictionary<int, int> Flags { get; set; } = new();
        public int Score { get; set; }
        public int Turns { get; set; }
    }

    public class CommandResult
    {
        public bool Success { get; set; }
        public string? Output { get; set; }
        public GameState? NewState { get; set; }
        public bool GameEnded { get; set; }
    }

    public class SigningOptions
    {
        public string Algorithm { get; set; } = "RSA";
        public string? PrivateKeyPath { get; set; }
        public bool TimestampSignature { get; set; } = true;
    }

    #endregion
}

// =====================================================================
// ARCHIVOS DE CONFIGURACIÓN JSON
// =====================================================================

namespace DaadModern.Configuration
{
    /// <summary>
    /// appsettings.json
    /// </summary>
    public static class AppSettingsContent
    {
        public static readonly string Json = """
        {
          "Logging": {
            "LogLevel": {
              "Default": "Information",
              "Microsoft": "Warning",
              "Microsoft.Hosting.Lifetime": "Information"
            }
          },
          "DaadModern": {
            "Parser": {
              "StrictMode": true,
              "AllowDeprecatedSyntax": false,
              "MaxRecursionDepth": 100
            },
            "Transpiler": {
              "OptimizeOutput": true,
              "PreserveComments": true,
              "TargetCompatibility": "DAAD_2.8"
            },
            "Runtime": {
              "MaxExecutionTime": "00:05:00",
              "AllowUnsafeOperations": false,
              "DebugPort": 9000
            },
            "Validation": {
              "StrictTypeChecking": true,
              "WarnOnDeprecated": true,
              "ErrorOnIncompatible": true
            }
          },
          "Serilog": {
            "MinimumLevel": {
              "Default": "Information",
              "Override": {
                "Microsoft": "Warning",
                "System": "Warning"
              }
            },
            "WriteTo": [
              {
                "Name": "Console",
                "Args": {
                  "outputTemplate": "[{Timestamp:HH:mm:ss} {Level:u3}] {Message:lj}{NewLine}{Exception}"
                }
              },
              {
                "Name": "File",
                "Args": {
                  "path": "logs/daad-modern-.log",
                  "rollingInterval": "Day",
                  "outputTemplate": "{Timestamp:yyyy-MM-dd HH:mm:ss.fff zzz} [{Level:u3}] {Message:lj}{NewLine}{Exception}"
                }
              }
            ]
          }
        }
        """;
    }

    /// <summary>
    /// Configuración específica de desarrollo
    /// </summary>
    public static class DevelopmentSettingsContent
    {
        public static readonly string Json = """
        {
          "Logging": {
            "LogLevel": {
              "Default": "Debug",
              "DaadModern": "Trace"
            }
          },
          "DaadModern": {
            "Parser": {
              "StrictMode": false,
              "AllowDeprecatedSyntax": true
            },
            "Runtime": {
              "AllowUnsafeOperations": true,
              "DebugMode": true
            }
          }
        }
        """;
    }
}