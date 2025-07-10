# Sistema Parser DAAD Modernizado - Parte 5: Guía de Implementación

## Parte 5.1: Arquitectura General y Configuración del Proyecto

### 5.1.1 Estructura del Proyecto en C# .NET Core 9

La arquitectura del proyecto debe seguir los principios SOLID y utilizar las características modernas de .NET Core 9. La estructura recomendada es:

```
DaadModernizado/
├── src/
│   ├── DaadModernizado.Core/              # Modelo de datos y lógica central
│   ├── DaadModernizado.Parser/            # Componentes de parsing
│   ├── DaadModernizado.Spanish/           # Biblioteca de vocabulario español  
│   ├── DaadModernizado.Transpiler/        # Transpilador a DAAD clásico
│   ├── DaadModernizado.Runtime/           # Motor de ejecución
│   ├── DaadModernizado.Tools/             # Herramientas de desarrollo
│   └── DaadModernizado.CLI/               # Interfaz de línea de comandos
├── tests/
│   ├── DaadModernizado.Core.Tests/
│   ├── DaadModernizado.Parser.Tests/
│   └── DaadModernizado.Integration.Tests/
├── samples/
│   ├── BasicAdventure/                    # Aventura simple de ejemplo
│   └── ComplexAdventure/                  # Aventura compleja de ejemplo
└── docs/
    ├── api/                               # Documentación de API
    └── tutorials/                         # Tutoriales paso a paso
```

### 5.1.2 Configuración de Proyectos .csproj

#### DaadModernizado.Core.csproj
```xml
<Project Sdk="Microsoft.NET.Sdk">
  <PropertyGroup>
    <TargetFramework>net9.0</TargetFramework>
    <LangVersion>12.0</LangVersion>
    <Nullable>enable</Nullable>
    <WarningsAsErrors />
    <TreatWarningsAsErrors>true</TreatWarningsAsErrors>
  </PropertyGroup>

  <ItemGroup>
    <PackageReference Include="System.Text.Json" Version="9.0.0" />
    <PackageReference Include="Microsoft.Extensions.Logging.Abstractions" Version="9.0.0" />
    <PackageReference Include="Microsoft.Extensions.Options" Version="9.0.0" />
  </ItemGroup>
</Project>
```

#### DaadModernizado.Parser.csproj
```xml
<Project Sdk="Microsoft.NET.Sdk">
  <PropertyGroup>
    <TargetFramework>net9.0</TargetFramework>
    <LangVersion>12.0</LangVersion>
    <Nullable>enable</Nullable>
  </PropertyGroup>

  <ItemGroup>
    <ProjectReference Include="..\DaadModernizado.Core\DaadModernizado.Core.csproj" />
    <ProjectReference Include="..\DaadModernizado.Spanish\DaadModernizado.Spanish.csproj" />
  </ItemGroup>

  <ItemGroup>
    <PackageReference Include="Microsoft.Extensions.DependencyInjection" Version="9.0.0" />
    <PackageReference Include="Microsoft.Extensions.Logging" Version="9.0.0" />
  </ItemGroup>
</Project>
```

### 5.1.3 Servicios Base y Dependency Injection

Configurar un sistema de inyección de dependencias que permita testing fácil y extensibilidad:

```csharp
// IServiceCollectionExtensions.cs
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;

namespace DaadModernizado.Core.Extensions;

public static class ServiceCollectionExtensions
{
    public static IServiceCollection AddDaadModernizado(this IServiceCollection services)
    {
        // Servicios centrales
        services.AddSingleton<ISpanishVocabularyService, SpanishVocabularyService>();
        services.AddTransient<IGameValidator, GameValidator>();
        
        // Servicios de parsing (se añadirán en siguientes partes)
        services.AddTransient<ISectionParser, SectionParser>();
        services.AddTransient<IConditionActionParser, ConditionActionParser>();
        services.AddTransient<ISpanishSyntaxAnalyzer, SpanishSyntaxAnalyzer>();
        
        // Servicios de transpilación
        services.AddTransient<IClassicDaadTranspiler, ClassicDaadTranspiler>();
        
        // Configuración de logging
        services.AddLogging(builder =>
        {
            builder.AddConsole();
            builder.SetMinimumLevel(LogLevel.Information);
        });

        return services;
    }
}
```

### 5.1.4 Patrones de Configuración Modernos

Utilizar el patrón Options para configuración tipada:

```csharp
// ParserConfiguration.cs
namespace DaadModernizado.Core.Configuration;

public class ParserConfiguration
{
    public const string SectionName = "Parser";
    
    public bool EnableDetailedErrorReporting { get; set; } = true;
    public bool EnableSpanishDialectDetection { get; set; } = true;
    public string DefaultEncoding { get; set; } = "UTF-8";
    public int MaxFileSize { get; set; } = 10 * 1024 * 1024; // 10MB
    public bool EnableAsyncParsing { get; set; } = true;
    
    public SpanishLanguageSettings Spanish { get; set; } = new();
}

public class SpanishLanguageSettings
{
    public bool EnableSynonymExpansion { get; set; } = true;
    public bool FilterArticles { get; set; } = true;
    public bool NormalizeAccents { get; set; } = true;
    public string[] SupportedDialects { get; set; } = { "es-ES", "es-MX", "es-AR" };
}
```

### 5.1.5 Interfaces Principales del Sistema

Definir interfaces claras que guíen la implementación:

```csharp
// Interfaces/IParser.cs
namespace DaadModernizado.Core.Interfaces;

public interface IParser<TInput, TOutput>
{
    Task<ParseResult<TOutput>> ParseAsync(TInput input, CancellationToken cancellationToken = default);
    ParseResult<TOutput> Parse(TInput input);
}

// Interfaces/IGameParser.cs
public interface IGameParser : IParser<string, ModernDaadGame>
{
    ParseResult<ModernDaadGame> ParseFromFile(string filePath);
    Task<ParseResult<ModernDaadGame>> ParseFromFileAsync(string filePath, CancellationToken cancellationToken = default);
}

// Interfaces/ISectionParser.cs
public interface ISectionParser
{
    bool CanParse(string sectionName);
    ParseResult<object> ParseSection(string sectionName, List<Token> tokens, ParseContext context);
}

// Interfaces/IValidator.cs
public interface IValidator<T>
{
    ValidationResult Validate(T item);
    Task<ValidationResult> ValidateAsync(T item, CancellationToken cancellationToken = default);
}
```

### 5.1.6 Sistema de Logging Estructurado

Implementar logging estructurado para facilitar debugging y monitoreo:

```csharp
// Logging/LoggerExtensions.cs
using Microsoft.Extensions.Logging;

namespace DaadModernizado.Core.Logging;

public static partial class LoggerExtensions
{
    [LoggerMessage(
        EventId = 1001,
        Level = LogLevel.Information,
        Message = "Iniciando parsing de archivo: {FileName}")]
    public static partial void LogParsingStarted(this ILogger logger, string fileName);

    [LoggerMessage(
        EventId = 1002,
        Level = LogLevel.Information,
        Message = "Parsing completado exitosamente. Tokens procesados: {TokenCount}, Tiempo: {ElapsedMs}ms")]
    public static partial void LogParsingCompleted(this ILogger logger, int tokenCount, long elapsedMs);

    [LoggerMessage(
        EventId = 2001,
        Level = LogLevel.Error,
        Message = "Error de parsing en línea {LineNumber}: {ErrorMessage}")]
    public static partial void LogParsingError(this ILogger logger, int lineNumber, string errorMessage);

    [LoggerMessage(
        EventId = 3001,
        Level = LogLevel.Warning,
        Message = "Referencia no encontrada: {ReferenceType} '{ReferenceName}' en línea {LineNumber}")]
    public static partial void LogUnresolvedReference(this ILogger logger, string referenceType, string referenceName, int lineNumber);
}
```

### 5.1.7 Estrategia de Testing Base

Configurar estructura de testing que permita pruebas unitarias, de integración y end-to-end:

```csharp
// Tests/TestBase.cs
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
using Xunit.Abstractions;

namespace DaadModernizado.Tests.Base;

public abstract class TestBase
{
    protected IServiceProvider ServiceProvider { get; }
    protected ILogger Logger { get; }

    protected TestBase(ITestOutputHelper output)
    {
        var services = new ServiceCollection();
        services.AddDaadModernizado();
        services.AddLogging(builder => builder.AddXUnit(output));
        
        ServiceProvider = services.BuildServiceProvider();
        Logger = ServiceProvider.GetRequiredService<ILogger<TestBase>>();
    }

    protected T GetService<T>() where T : notnull
        => ServiceProvider.GetRequiredService<T>();
}

// Tests/ParserTestBase.cs
public abstract class ParserTestBase : TestBase
{
    protected ParserTestBase(ITestOutputHelper output) : base(output) { }

    protected static string GetTestDataPath(string fileName)
        => Path.Combine("TestData", fileName);

    protected static ModernDaadGame CreateBasicGame(string title = "Test Game")
    {
        return new ModernDaadGame
        {
            Metadata = new GameMetadata
            {
                Title = title,
                Author = "Test Author",
                StartLocation = "start"
            }
        };
    }
}
```

### 5.1.8 Gestión de Errores Moderna

Implementar manejo de errores que aproveche las características modernas de C#:

```csharp
// Errors/DaadException.cs
namespace DaadModernizado.Core.Errors;

public abstract class DaadException : Exception
{
    public string ErrorCode { get; }
    
    protected DaadException(string errorCode, string message) : base(message)
    {
        ErrorCode = errorCode;
    }
    
    protected DaadException(string errorCode, string message, Exception innerException) 
        : base(message, innerException)
    {
        ErrorCode = errorCode;
    }
}

public class ParseException : DaadException
{
    public int LineNumber { get; }
    public string FileName { get; }
    
    public ParseException(string message, int lineNumber, string fileName = "") 
        : base("PARSE_ERROR", message)
    {
        LineNumber = lineNumber;
        FileName = fileName;
    }
}

// Result Pattern para operaciones que pueden fallar
public record Result<T>
{
    public bool IsSuccess { get; init; }
    public T? Value { get; init; }
    public string? Error { get; init; }
    public Exception? Exception { get; init; }

    public static Result<T> Success(T value) => new() { IsSuccess = true, Value = value };
    public static Result<T> Failure(string error) => new() { IsSuccess = false, Error = error };
    public static Result<T> Failure(Exception exception) => new() { IsSuccess = false, Exception = exception, Error = exception.Message };
}
```

### 5.1.9 Performance y Memoria

Configurar para performance óptimo aprovechando .NET Core 9:

```csharp
// Performance/MemoryPools.cs
using System.Buffers;

namespace DaadModernizado.Core.Performance;

public static class MemoryPools
{
    public static readonly ArrayPool<char> CharPool = ArrayPool<char>.Shared;
    public static readonly ArrayPool<Token> TokenPool = ArrayPool<Token>.Shared;
    
    public static IDisposable RentChars(int minLength, out char[] buffer)
    {
        buffer = CharPool.Rent(minLength);
        return new ArrayReturn<char>(CharPool, buffer);
    }
}

internal record struct ArrayReturn<T>(ArrayPool<T> Pool, T[] Array) : IDisposable
{
    public void Dispose() => Pool.Return(Array);
}

// Performance/StringBuilderCache.cs  
public static class StringBuilderCache
{
    [ThreadStatic]
    private static StringBuilder? _cache;

    public static StringBuilder Acquire(int capacity = 256)
    {
        var sb = _cache;
        if (sb != null && sb.Capacity >= capacity)
        {
            _cache = null;
            sb.Clear();
            return sb;
        }
        return new StringBuilder(capacity);
    }

    public static void Release(StringBuilder sb)
    {
        if (sb.Capacity <= 8192) // No cachear StringBuilder muy grandes
        {
            _cache = sb;
        }
    }

    public static string GetStringAndRelease(StringBuilder sb)
    {
        var result = sb.ToString();
        Release(sb);
        return result;
    }
}
```

### 5.1.10 Próximos Pasos

Esta configuración base proporciona:

1. **Estructura modular** que facilita el desarrollo independiente de componentes
2. **Inyección de dependencias** para testing y extensibilidad
3. **Configuración tipada** usando el patrón Options
4. **Logging estructurado** para debugging eficaz
5. **Manejo de errores moderno** con Result patterns
6. **Optimizaciones de performance** aprovechando .NET Core 9

En la siguiente parte (5.2) abordaremos la implementación específica del **Parser de Secciones (3D3)**, que es el componente prioritario más crítico del sistema.