// =====================================================================
// DAAD Moderno - Aplicación Principal
// Sistema completo de transpilación y desarrollo de aventuras
// =====================================================================

using System.CommandLine;
using System.CommandLine.Builder;
using System.CommandLine.Hosting;
using System.CommandLine.Parsing;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using Serilog;
using Serilog.Events;
using DaadModern.Parser;
using DaadModern.Transpiler;
using DaadModern.Analysis;
using DaadModern.CodeGeneration;
using DaadModern.Runtime;

namespace DaadModern;

/// <summary>
/// Punto de entrada principal de DAAD Moderno
/// </summary>
public class Program
{
    public static async Task<int> Main(string[] args)
    {
        // Configurar logging inicial
        Log.Logger = new LoggerConfiguration()
            .MinimumLevel.Information()
            .MinimumLevel.Override("Microsoft", LogEventLevel.Warning)
            .Enrich.FromLogContext()
            .WriteTo.Console(outputTemplate: "[{Timestamp:HH:mm:ss} {Level:u3}] {Message:lj}{NewLine}{Exception}")
            .CreateLogger();

        try
        {
            var rootCommand = BuildCommandLine();
            var parser = new CommandLineBuilder(rootCommand)
                .UseHost(Host.CreateDefaultBuilder, ConfigureServices)
                .UseDefaults()
                .Build();

            return await parser.InvokeAsync(args);
        }
        catch (Exception ex)
        {
            Log.Fatal(ex, "Error fatal en la aplicación");
            return 1;
        }
        finally
        {
            Log.CloseAndFlush();
        }
    }

    /// <summary>
    /// Configura los servicios de inyección de dependencias
    /// </summary>
    private static void ConfigureServices(IServiceCollection services)
    {
        // Logging con Serilog
        services.AddLogging(builder =>
        {
            builder.ClearProviders();
            builder.AddSerilog();
        });

        // Servicios principales
        services.AddSingleton<IDaadParser, DaadPidginParser>();
        services.AddSingleton<IClassicTranspiler, ClassicDaadTranspiler>();
        services.AddSingleton<IModernTranspiler, ModernDaadTranspiler>();
        services.AddSingleton<IGameAnalyzer, GameAnalyzer>();
        services.AddSingleton<IVocabularyService, SpanishVocabularyService>();
        services.AddSingleton<ICodeGenerator, BytecodeGenerator>();
        services.AddSingleton<IGameRuntime, DaadGameRuntime>();

        // Servicios de validación
        services.AddSingleton<IGameValidator, ComprehensiveGameValidator>();
        services.AddSingleton<ICompatibilityChecker, DaadCompatibilityChecker>();

        // Servicios de archivos
        services.AddSingleton<IFileService, FileService>();
        services.AddSingleton<ITemplateService, TemplateService>();


            // Servicios principales (mantener existentes)
                services.AddSingleton<IDaadParser, DaadPidginParser>();
                services.AddSingleton<IClassicTranspiler, ClassicDaadTranspiler>();
                
                // ===== NUEVOS SERVICIOS FASE 1 =====
                services.AddSingleton<ICompatibilityChecker, ExtendedCompatibilityChecker>();
                services.AddSingleton<IBenchmarkRunner, TranspilerBenchmarkRunner>();
                services.AddSingleton<IMigrationService, ClassicToModernMigrationService>();
                services.AddSingleton<IPerformanceProfiler, DetailedPerformanceProfiler>();
                
                // Command handlers (nuevos)
                services.AddTransient<CompatibilityCommandHandler>();
                services.AddTransient<BenchmarkCommandHandler>();
                services.AddTransient<MigrateCommandHandler>();
                
                // Configuración mejorada
                services.Configure<TranspilerOptions>(options =>
                {
                    options.EnableExtendedCondacts = true;
                    options.Phase1ComplianceMode = true;
                    options.StrictCompatibilityCheck = true;
                    options.PerformanceOptimizations = true;
                });

        
    }

    /// <summary>
    /// Construye la línea de comandos completa
    /// </summary>
    private static RootCommand BuildCommandLine()
    {
        var rootCommand = new RootCommand("DAAD Moderno - Sistema de desarrollo de aventuras conversacionales")
        {
            BuildParseCommand(),
            BuildTranspileCommand(),
            BuildValidateCommand(),
            BuildRunCommand(),
            BuildAnalyzeCommand(),
            BuildCreateCommand(),
            BuildTestCommand(),
            BuildCompatibilityCommand(),
            BuildBenchmarkCommand(),
            BuildMigrateCommand()
        };

        // Opciones globales
        rootCommand.AddGlobalOption(new Option<bool>("--verbose", "Salida detallada"));
        rootCommand.AddGlobalOption(new Option<bool>("--debug", "Modo debugging con breakpoints"));
        rootCommand.AddGlobalOption(new Option<string?>("--config", "Archivo de configuración personalizado"));
        rootCommand.AddGlobalOption(new Option<bool>("--no-color", "Desactivar colores en output"));
        rootCommand.AddGlobalOption(new Option<LogLevel>("--log-level", () => LogLevel.Information, "Nivel de logging"));


        return rootCommand;
    }

    #region Comandos Principales

    /// <summary>
    /// Comando para parsear archivos DAAD modernos
    /// </summary>
    private static Command BuildParseCommand()
    {
        var parseCommand = new Command("parse", "Parsea archivos DAAD modernos y verifica la sintaxis");

        var inputOption = new Option<FileInfo>("--input", "Archivo DAAD moderno a parsear") { IsRequired = true };
        var outputOption = new Option<FileInfo?>("--output", "Archivo de salida para el AST (JSON)");
        var formatOption = new Option<OutputFormat>("--format", () => OutputFormat.Json, "Formato de salida");
        var validateOption = new Option<bool>("--validate", () => true, "Validar semánticamente");

        parseCommand.AddOption(inputOption);
        parseCommand.AddOption(outputOption);
        parseCommand.AddOption(formatOption);
        parseCommand.AddOption(validateOption);

        parseCommand.SetHandler(async (input, output, format, validate, verbose, debug) =>
        {
            var handler = new ParseCommandHandler();
            return await handler.ExecuteAsync(input, output, format, validate, verbose, debug);
        }, inputOption, outputOption, formatOption, validateOption,
           new Option<bool>("--verbose"), new Option<bool>("--debug"));

        return parseCommand;
    }

    /// <summary>
    /// Comando para transpilar entre formatos
    /// </summary>
    private static Command BuildTranspileCommand()
    {
        var transpileCommand = new Command("transpile", "Transpila entre DAAD moderno y clásico");

        var inputOption = new Option<FileInfo>("--input", "Archivo de entrada") { IsRequired = true };
        var outputOption = new Option<FileInfo>("--output", "Archivo de salida") { IsRequired = true };
        var targetOption = new Option<TranspileTarget>("--target", () => TranspileTarget.Classic, "Target de transpilación");
        var platformOption = new Option<ClassicPlatform>("--platform", () => ClassicPlatform.ZxSpectrum, "Plataforma clásica");
        var optimizeOption = new Option<bool>("--optimize", () => true, "Optimizar código generado");

        transpileCommand.AddOption(inputOption);
        transpileCommand.AddOption(outputOption);
        transpileCommand.AddOption(targetOption);
        transpileCommand.AddOption(platformOption);
        transpileCommand.AddOption(optimizeOption);

        transpileCommand.SetHandler(async (input, output, target, platform, optimize, verbose) =>
        {
            var handler = new TranspileCommandHandler();
            return await handler.ExecuteAsync(input, output, target, platform, optimize, verbose);
        }, inputOption, outputOption, targetOption, platformOption, optimizeOption, new Option<bool>("--verbose"));

        return transpileCommand;
    }

    /// <summary>
    /// Comando para validar aventuras
    /// </summary>
    private static Command BuildValidateCommand()
    {
        var validateCommand = new Command("validate", "Valida aventuras DAAD y detecta problemas");

        var inputOption = new Option<FileInfo>("--input", "Archivo DAAD a validar") { IsRequired = true };
        var levelOption = new Option<ValidationLevel>("--level", () => ValidationLevel.Full, "Nivel de validación");
        var reportOption = new Option<FileInfo?>("--report", "Archivo de reporte de validación");
        var fixOption = new Option<bool>("--fix", "Intentar arreglar problemas automáticamente");

        validateCommand.AddOption(inputOption);
        validateCommand.AddOption(levelOption);
        validateCommand.AddOption(reportOption);
        validateCommand.AddOption(fixOption);

        validateCommand.SetHandler(async (input, level, report, fix, verbose) =>
        {
            var handler = new ValidateCommandHandler();
            return await handler.ExecuteAsync(input, level, report, fix, verbose);
        }, inputOption, levelOption, reportOption, fixOption, new Option<bool>("--verbose"));

        return validateCommand;
    }

    /// <summary>
    /// Comando para ejecutar aventuras
    /// </summary>
    private static Command BuildRunCommand()
    {
        var runCommand = new Command("run", "Ejecuta aventuras DAAD modernas");

        var inputOption = new Option<FileInfo>("--input", "Archivo DAAD a ejecutar") { IsRequired = true };
        var debugOption = new Option<bool>("--debug-mode", "Ejecutar en modo debugging");
        var stepOption = new Option<bool>("--step", "Ejecución paso a paso");
        var portOption = new Option<int>("--port", () => 8080, "Puerto para interfaz web");

        runCommand.AddOption(inputOption);
        runCommand.AddOption(debugOption);
        runCommand.AddOption(stepOption);
        runCommand.AddOption(portOption);

        runCommand.SetHandler(async (input, debugMode, step, port, verbose) =>
        {
            var handler = new RunCommandHandler();
            return await handler.ExecuteAsync(input, debugMode, step, port, verbose);
        }, inputOption, debugOption, stepOption, portOption, new Option<bool>("--verbose"));

        return runCommand;
    }

    /// <summary>
    /// Comando para analizar aventuras
    /// </summary>
    private static Command BuildAnalyzeCommand()
    {
        var analyzeCommand = new Command("analyze", "Analiza aventuras y genera métricas");

        var inputOption = new Option<FileInfo>("--input", "Archivo DAAD a analizar") { IsRequired = true };
        var reportOption = new Option<FileInfo>("--output", "Archivo de reporte") { IsRequired = true };
        var metricsOption = new Option<AnalysisMetrics>("--metrics", () => AnalysisMetrics.All, "Métricas a calcular");
        var compareOption = new Option<FileInfo?>("--compare", "Archivo para comparación");

        analyzeCommand.AddOption(inputOption);
        analyzeCommand.AddOption(reportOption);
        analyzeCommand.AddOption(metricsOption);
        analyzeCommand.AddOption(compareOption);

        analyzeCommand.SetHandler(async (input, output, metrics, compare, verbose) =>
        {
            var handler = new AnalyzeCommandHandler();
            return await handler.ExecuteAsync(input, output, metrics, compare, verbose);
        }, inputOption, reportOption, metricsOption, compareOption, new Option<bool>("--verbose"));

        return analyzeCommand;
    }

    /// <summary>
    /// Comando para crear proyectos nuevos
    /// </summary>
    private static Command BuildCreateCommand()
    {
        var createCommand = new Command("create", "Crea nuevos proyectos DAAD");

        var nameOption = new Option<string>("--name", "Nombre del proyecto") { IsRequired = true };
        var templateOption = new Option<ProjectTemplate>("--template", () => ProjectTemplate.Basic, "Template del proyecto");
        var dirOption = new Option<DirectoryInfo?>("--directory", "Directorio de destino");
        var forceOption = new Option<bool>("--force", "Sobrescribir si existe");

        createCommand.AddOption(nameOption);
        createCommand.AddOption(templateOption);
        createCommand.AddOption(dirOption);
        createCommand.AddOption(forceOption);

        createCommand.SetHandler(async (name, template, directory, force, verbose) =>
        {
            var handler = new CreateCommandHandler();
            return await handler.ExecuteAsync(name, template, directory, force, verbose);
        }, nameOption, templateOption, dirOption, forceOption, new Option<bool>("--verbose"));

        return createCommand;
    }

    /// <summary>
    /// Comando para testing automatizado
    /// </summary>
    private static Command BuildTestCommand()
    {
        var testCommand = new Command("test", "Ejecuta tests automatizados de aventuras");

        var inputOption = new Option<FileInfo>("--input", "Archivo DAAD o directorio de tests") { IsRequired = true };
        var suiteOption = new Option<string?>("--suite", "Suite de tests específica");
        var coverageOption = new Option<bool>("--coverage", "Generar reporte de cobertura");
        var parallelOption = new Option<bool>("--parallel", () => true, "Ejecución paralela");

        testCommand.AddOption(inputOption);
        testCommand.AddOption(suiteOption);
        testCommand.AddOption(coverageOption);
        testCommand.AddOption(parallelOption);

        testCommand.SetHandler(async (input, suite, coverage, parallel, verbose) =>
        {
            var handler = new TestCommandHandler();
            return await handler.ExecuteAsync(input, suite, coverage, parallel, verbose);
        }, inputOption, suiteOption, coverageOption, parallelOption, new Option<bool>("--verbose"));

        return testCommand;
    }

    /// <summary>
    /// Comando para verificar compatibilidad con DAAD clásico
    /// </summary>
    private static Command BuildCompatibilityCommand()
    {
        var compatCommand = new Command("compat", "Verifica compatibilidad completa con DAAD clásico");

        var inputOption = new Option<FileInfo>("--input", "Archivo DAAD clásico (.ddb)") { IsRequired = true };
        var reportOption = new Option<FileInfo?>("--report", "Archivo de reporte de compatibilidad");
        var strictOption = new Option<bool>("--strict", "Validación estricta (incluye condactos experimentales)");
        var coverageOption = new Option<bool>("--coverage", "Calcular cobertura de condactos");
        var fixOption = new Option<bool>("--autofix", "Intentar corregir problemas automáticamente");

        compatCommand.AddOption(inputOption);
        compatCommand.AddOption(reportOption);
        compatCommand.AddOption(strictOption);
        compatCommand.AddOption(coverageOption);
        compatCommand.AddOption(fixOption);

        compatCommand.SetHandler(async (input, report, strict, coverage, autofix, verbose) =>
        {
            var handler = new CompatibilityCommandHandler();
            return await handler.ExecuteAsync(input, report, strict, coverage, autofix, verbose);
        }, inputOption, reportOption, strictOption, coverageOption, fixOption, new Option<bool>("--verbose"));

        return compatCommand;
    }

    /// <summary>
    /// Comando para benchmarking y tests de performance
    /// </summary>
    private static Command BuildBenchmarkCommand()
    {
        var benchCommand = new Command("bench", "Ejecuta benchmarks de performance del transpilador");

        var inputOption = new Option<DirectoryInfo>("--input", "Directorio con aventuras de prueba") { IsRequired = true };
        var iterationsOption = new Option<int>("--iterations", () => 10, "Número de iteraciones");
        var outputOption = new Option<FileInfo?>("--output", "Archivo de resultados");
        var memoryOption = new Option<bool>("--memory", "Incluir análisis de memoria");

        benchCommand.AddOption(inputOption);
        benchCommand.AddOption(iterationsOption);
        benchCommand.AddOption(outputOption);
        benchCommand.AddOption(memoryOption);

        benchCommand.SetHandler(async (input, iterations, output, memory, verbose) =>
        {
            var handler = new BenchmarkCommandHandler();
            return await handler.ExecuteAsync(input, iterations, output, memory, verbose);
        }, inputOption, iterationsOption, outputOption, memoryOption, new Option<bool>("--verbose"));

        return benchCommand;
    }

    /// <summary>
    /// Comando para migration de aventuras clásicas
    /// </summary>
    private static Command BuildMigrateCommand()
    {
        var migrateCommand = new Command("migrate", "Migra aventuras DAAD clásicas a formato moderno");

        var inputOption = new Option<FileInfo>("--input", "Archivo DAAD clásico") { IsRequired = true };
        var outputOption = new Option<FileInfo>("--output", "Archivo DAAD moderno de salida") { IsRequired = true };
        var preserveOption = new Option<bool>("--preserve-comments", () => true, "Preservar comentarios originales");
        var modernizeOption = new Option<bool>("--modernize-syntax", () => true, "Modernizar sintaxis automáticamente");
        var backupOption = new Option<bool>("--backup", () => true, "Crear backup del archivo original");

        migrateCommand.AddOption(inputOption);
        migrateCommand.AddOption(outputOption);
        migrateCommand.AddOption(preserveOption);
        migrateCommand.AddOption(modernizeOption);
        migrateCommand.AddOption(backupOption);

        migrateCommand.SetHandler(async (input, output, preserve, modernize, backup, verbose) =>
        {
            var handler = new MigrateCommandHandler();
            return await handler.ExecuteAsync(input, output, preserve, modernize, backup, verbose);
        }, inputOption, outputOption, preserveOption, modernizeOption, backupOption, new Option<bool>("--verbose"));

        return migrateCommand;
    }

    #endregion
}

#region Enums y Tipos de Configuración

public enum OutputFormat
{
    Json,
    Xml,
    Yaml,
    Pretty
}

public enum TranspileTarget
{
    Classic,
    Modern,
    Bytecode,
    JavaScript,
    Web
}

public enum ClassicPlatform
{
    ZxSpectrum,
    Commodore64,
    AmstradCpc,
    Msx,
    Amiga,
    AtariSt,
    MsDos
}

public enum ValidationLevel
{
    Syntax,
    Semantic,
    Full,
    Compatibility
}

public enum AnalysisMetrics
{
    Basic,
    Complexity,
    Vocabulary,
    Flow,
    All
}

public enum ProjectTemplate
{
    Basic,
    Adventure,
    Tutorial,
    Complex,
    Horror,
    Fantasy,
    Sci_Fi
}

#endregion