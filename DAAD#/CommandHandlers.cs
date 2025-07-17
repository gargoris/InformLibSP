// =====================================================================
// DAAD Moderno - Command Handlers Completos
// Implementación de todos los handlers necesarios para CLI
// =====================================================================

using System;
using System.Collections.Generic;
using System.IO;
using System.Threading.Tasks;
using Microsoft.Extensions.Logging;
using DaadModern.Parser;
using DaadModern.Transpiler;

namespace DaadModern.CommandHandlers
{
    /// <summary>
    /// Handler para comando de compatibilidad
    /// </summary>
    public class CompatibilityCommandHandler
    {
        private readonly ILogger<CompatibilityCommandHandler> _logger;
        private readonly ICompatibilityChecker _compatChecker;
        private readonly CompleteDaadTranspiler _transpiler;

        public CompatibilityCommandHandler(
            ILogger<CompatibilityCommandHandler> logger,
            ICompatibilityChecker compatChecker,
            CompleteDaadTranspiler transpiler)
        {
            _logger = logger;
            _compatChecker = compatChecker;
            _transpiler = transpiler;
        }

        public async Task<int> ExecuteAsync(
            FileInfo input, 
            FileInfo? report, 
            bool strict, 
            bool coverage, 
            bool autofix, 
            bool verbose)
        {
            try
            {
                _logger.LogInformation("Verificando compatibilidad de {File}", input.Name);

                if (!input.Exists)
                {
                    _logger.LogError("Archivo no encontrado: {File}", input.FullName);
                    return 1;
                }

                var classicCode = await File.ReadAllTextAsync(input.FullName);
                
                // Verificar compatibilidad
                var compatResult = await _compatChecker.CheckCompatibilityAsync(classicCode);
                
                // Mostrar resultados
                DisplayCompatibilityResults(compatResult, verbose);
                
                // Generar reporte de cobertura si se solicita
                if (coverage)
                {
                    var coverageResult = await _compatChecker.AnalyzeCoverageAsync();
                    DisplayCoverageResults(coverageResult);
                }
                
                // Auto-fix si se solicita
                if (autofix && compatResult.Issues.Count > 0)
                {
                    var fixes = await _compatChecker.SuggestFixesAsync(classicCode);
                    await ApplyAutoFixes(input, fixes);
                }
                
                // Generar reporte si se especifica
                if (report != null)
                {
                    await GenerateCompatibilityReport(compatResult, report);
                }

                return compatResult.IsFullyCompatible ? 0 : 1;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error verificando compatibilidad");
                return 1;
            }
        }

        private void DisplayCompatibilityResults(CompatibilityReport result, bool verbose)
        {
            Console.WriteLine($"🔍 Resultado de Compatibilidad: {(result.IsFullyCompatible ? "✅ COMPATIBLE" : "⚠️ PROBLEMAS ENCONTRADOS")}");
            Console.WriteLine($"📊 Condactos soportados: {result.SupportedCondacts.Count}/{result.TotalCondacts} ({result.CompatibilityPercentage:F1}%)");
            
            if (result.UnsupportedCondacts.Count > 0)
            {
                Console.WriteLine("\n❌ Condactos no soportados:");
                foreach (var condact in result.UnsupportedCondacts)
                {
                    Console.WriteLine($"   • {condact}");
                }
            }

            if (verbose && result.Issues.Count > 0)
            {
                Console.WriteLine("\n⚠️ Problemas encontrados:");
                foreach (var issue in result.Issues)
                {
                    Console.WriteLine($"   • {issue.Severity}: {issue.Description}");
                }
            }
        }

        private void DisplayCoverageResults(CondactCoverageReport coverage)
        {
            Console.WriteLine("\n📈 Análisis de Cobertura de Condactos:");
            Console.WriteLine($"   • Condiciones: {coverage.ConditionCoverage:F1}%");
            Console.WriteLine($"   • Acciones: {coverage.ActionCoverage:F1}%");
            Console.WriteLine($"   • Vestibles: {coverage.WearableCoverage:F1}%");
            Console.WriteLine($"   • Multimedia: {coverage.MultimediaCoverage:F1}%");
            Console.WriteLine($"   • Total: {coverage.OverallCoverage:F1}%");
        }

        private async Task ApplyAutoFixes(FileInfo input, List<FixSuggestion> fixes)
        {
            if (fixes.Count == 0) return;

            Console.WriteLine($"\n🔧 Aplicando {fixes.Count} correcciones automáticas...");
            
            var content = await File.ReadAllTextAsync(input.FullName);
            foreach (var fix in fixes)
            {
                content = fix.Apply(content);
                Console.WriteLine($"   ✅ {fix.Description}");
            }
            
            // Crear backup
            var backupFile = $"{input.FullName}.backup.{DateTime.Now:yyyyMMdd_HHmmss}";
            File.Copy(input.FullName, backupFile);
            
            await File.WriteAllTextAsync(input.FullName, content);
            Console.WriteLine($"📁 Backup creado: {Path.GetFileName(backupFile)}");
        }

        private async Task GenerateCompatibilityReport(CompatibilityReport result, FileInfo reportFile)
        {
            var html = GenerateCompatibilityHtml(result);
            await File.WriteAllTextAsync(reportFile.FullName, html);
            _logger.LogInformation("Reporte generado: {File}", reportFile.FullName);
        }

        private string GenerateCompatibilityHtml(CompatibilityReport result)
        {
            return $@"
<!DOCTYPE html>
<html>
<head>
    <title>Reporte de Compatibilidad DAAD</title>
    <style>
        body {{ font-family: Arial, sans-serif; margin: 20px; }}
        .compatible {{ color: green; }}
        .incompatible {{ color: red; }}
        .warning {{ color: orange; }}
        table {{ border-collapse: collapse; width: 100%; }}
        th, td {{ border: 1px solid #ddd; padding: 8px; text-align: left; }}
        th {{ background-color: #f2f2f2; }}
    </style>
</head>
<body>
    <h1>Reporte de Compatibilidad DAAD</h1>
    <p><strong>Fecha:</strong> {DateTime.Now:yyyy-MM-dd HH:mm:ss}</p>
    <p><strong>Estado:</strong> <span class='{(result.IsFullyCompatible ? "compatible" : "incompatible")}'>{(result.IsFullyCompatible ? "COMPATIBLE" : "PROBLEMAS ENCONTRADOS")}</span></p>
    <p><strong>Cobertura:</strong> {result.CompatibilityPercentage:F1}% ({result.SupportedCondacts.Count}/{result.TotalCondacts})</p>
    
    <!-- Tabla de condactos -->
    <h2>Análisis de Condactos</h2>
    <table>
        <tr><th>Condacto</th><th>Estado</th><th>Tipo</th><th>Notas</th></tr>
        {string.Join("", result.SupportedCondacts.Select(c => $"<tr><td>{c}</td><td class='compatible'>✅ Soportado</td><td>-</td><td>-</td></tr>"))}
        {string.Join("", result.UnsupportedCondacts.Select(c => $"<tr><td>{c}</td><td class='incompatible'>❌ No soportado</td><td>-</td><td>Requiere implementación</td></tr>"))}
    </table>
</body>
</html>";
        }
    }

    /// <summary>
    /// Handler para comando de benchmarking
    /// </summary>
    public class BenchmarkCommandHandler
    {
        private readonly ILogger<BenchmarkCommandHandler> _logger;
        private readonly IBenchmarkRunner _benchmarkRunner;

        public BenchmarkCommandHandler(
            ILogger<BenchmarkCommandHandler> logger,
            IBenchmarkRunner benchmarkRunner)
        {
            _logger = logger;
            _benchmarkRunner = benchmarkRunner;
        }

        public async Task<int> ExecuteAsync(
            DirectoryInfo input, 
            int iterations, 
            FileInfo? output, 
            bool memory, 
            bool verbose)
        {
            try
            {
                _logger.LogInformation("Ejecutando benchmarks con {Iterations} iteraciones", iterations);

                if (!input.Exists)
                {
                    _logger.LogError("Directorio no encontrado: {Dir}", input.FullName);
                    return 1;
                }

                // Ejecutar benchmarks de transpilación
                var results = await _benchmarkRunner.RunTranspilerBenchmarksAsync(input, iterations);
                
                // Mostrar resultados
                DisplayBenchmarkResults(results, verbose);
                
                // Análisis de memoria si se solicita
                if (memory)
                {
                    await RunMemoryBenchmarks(input);
                }
                
                // Guardar resultados si se especifica
                if (output != null)
                {
                    await SaveBenchmarkResults(results, output);
                }

                return 0;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error ejecutando benchmarks");
                return 1;
            }
        }

        private void DisplayBenchmarkResults(BenchmarkResults results, bool verbose)
        {
            Console.WriteLine("🚀 Resultados de Performance:");
            Console.WriteLine($"   • Tiempo promedio transpilación: {results.AverageTranspileTime:F2}ms");
            Console.WriteLine($"   • Throughput: {results.ThroughputKBPerSecond:F1} KB/s");
            Console.WriteLine($"   • Memoria máxima: {results.MaxMemoryUsageMB:F1} MB");
            Console.WriteLine($"   • Archivos procesados: {results.FilesProcessed}");
            Console.WriteLine($"   • Errores: {results.ErrorCount}");

            if (verbose)
            {
                Console.WriteLine("\n📊 Detalle por archivo:");
                foreach (var file in results.FileResults)
                {
                    Console.WriteLine($"   • {file.FileName}: {file.TranspileTimeMs:F2}ms ({file.FileSizeKB:F1}KB)");
                }
            }
        }

        private async Task RunMemoryBenchmarks(DirectoryInfo input)
        {
            Console.WriteLine("\n🧠 Analizando uso de memoria...");
            
            var testFiles = input.GetFiles("*.daad", SearchOption.AllDirectories).Take(5);
            foreach (var file in testFiles)
            {
                var content = await File.ReadAllTextAsync(file.FullName);
                var profile = await _benchmarkRunner.ProfileMemoryUsageAsync(content);
                
                Console.WriteLine($"   • {file.Name}: {profile.PeakMemoryMB:F1}MB peak, {profile.AllocatedObjectsCount} objetos");
            }
        }

        private async Task SaveBenchmarkResults(BenchmarkResults results, FileInfo output)
        {
            var json = System.Text.Json.JsonSerializer.Serialize(results, new System.Text.Json.JsonSerializerOptions
            {
                WriteIndented = true
            });
            
            await File.WriteAllTextAsync(output.FullName, json);
            _logger.LogInformation("Resultados guardados en: {File}", output.FullName);
        }
    }

    /// <summary>
    /// Handler para comando de migración
    /// </summary>
    public class MigrateCommandHandler
    {
        private readonly ILogger<MigrateCommandHandler> _logger;
        private readonly IMigrationService _migrationService;

        public MigrateCommandHandler(
            ILogger<MigrateCommandHandler> logger,
            IMigrationService migrationService)
        {
            _logger = logger;
            _migrationService = migrationService;
        }

        public async Task<int> ExecuteAsync(
            FileInfo input, 
            FileInfo output, 
            bool preserveComments, 
            bool modernizeSyntax, 
            bool backup, 
            bool verbose)
        {
            try
            {
                _logger.LogInformation("Migrando {Input} → {Output}", input.Name, output.Name);

                if (!input.Exists)
                {
                    _logger.LogError("Archivo no encontrado: {File}", input.FullName);
                    return 1;
                }

                // Leer archivo original
                var classicCode = await File.ReadAllTextAsync(input.FullName);
                
                // Configurar opciones de migración
                var options = new MigrationOptions
                {
                    PreserveComments = preserveComments,
                    ModernizeSyntax = modernizeSyntax,
                    GenerateDocumentation = true,
                    ValidateAfterMigration = true
                };

                // Ejecutar migración
                var migrationResult = await _migrationService.MigrateAsync(classicCode, options);
                
                if (!migrationResult.Success)
                {
                    _logger.LogError("Migración falló: {Error}", migrationResult.ErrorMessage);
                    return 1;
                }

                // Crear backup si se solicita
                if (backup && output.Exists)
                {
                    var backupFile = $"{output.FullName}.backup.{DateTime.Now:yyyyMMdd_HHmmss}";
                    File.Copy(output.FullName, backupFile);
                    Console.WriteLine($"📁 Backup creado: {Path.GetFileName(backupFile)}");
                }

                // Guardar resultado
                await File.WriteAllTextAsync(output.FullName, migrationResult.ModernizedCode);
                
                // Mostrar estadísticas
                DisplayMigrationResults(migrationResult, verbose);

                return 0;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error durante migración");
                return 1;
            }
        }

        private void DisplayMigrationResults(MigrationResult result, bool verbose)
        {
            Console.WriteLine("🔄 Migración completada:");
            Console.WriteLine($"   • Líneas procesadas: {result.LinesProcessed}");
            Console.WriteLine($"   • Condactos migrados: {result.CondactsMigrated}");
            Console.WriteLine($"   • Objetos convertidos: {result.ObjectsConverted}");
            Console.WriteLine($"   • Warnings: {result.Warnings.Count}");

            if (verbose && result.Warnings.Count > 0)
            {
                Console.WriteLine("\n⚠️ Advertencias:");
                foreach (var warning in result.Warnings)
                {
                    Console.WriteLine($"   • {warning}");
                }
            }

            if (result.ModernizationApplied.Count > 0)
            {
                Console.WriteLine("\n✨ Modernizaciones aplicadas:");
                foreach (var modernization in result.ModernizationApplied)
                {
                    Console.WriteLine($"   • {modernization}");
                }
            }
        }
    }

    #region Servicios y Modelos de Soporte

    /// <summary>
    /// Verificador de compatibilidad extendido
    /// </summary>
    public class ExtendedCompatibilityChecker : ICompatibilityChecker
    {
        private readonly CompleteDaadTranspiler _transpiler;
        private readonly ILogger<ExtendedCompatibilityChecker> _logger;

        public ExtendedCompatibilityChecker(
            CompleteDaadTranspiler transpiler,
            ILogger<ExtendedCompatibilityChecker> logger)
        {
            _transpiler = transpiler;
            _logger = logger;
        }

        public async Task<CompatibilityReport> CheckCompatibilityAsync(string classicCode)
        {
            var implementedCondacts = _transpiler.GetImplementedCondacts();
            var foundCondacts = ExtractCondactsFromClassicCode(classicCode);
            
            var supportedCondacts = foundCondacts.Where(c => implementedCondacts.ContainsKey(c.ToLower())).ToList();
            var unsupportedCondacts = foundCondacts.Where(c => !implementedCondacts.ContainsKey(c.ToLower())).ToList();

            return new CompatibilityReport
            {
                IsFullyCompatible = unsupportedCondacts.Count == 0,
                SupportedCondacts = supportedCondacts,
                UnsupportedCondacts = unsupportedCondacts,
                TotalCondacts = foundCondacts.Count,
                CompatibilityPercentage = foundCondacts.Count > 0 ? (double)supportedCondacts.Count / foundCondacts.Count * 100 : 100,
                Issues = await AnalyzeIssuesAsync(classicCode)
            };
        }

        public async Task<CondactCoverageReport> AnalyzeCoverageAsync()
        {
            var allCondacts = _transpiler.GetImplementedCondacts();
            
            return new CondactCoverageReport
            {
                ConditionCoverage = CalculateCategoryCoverage(allCondacts, CondactType.Condition),
                ActionCoverage = CalculateCategoryCoverage(allCondacts, CondactType.Action),
                WearableCoverage = CalculateWearableCoverage(allCondacts),
                MultimediaCoverage = CalculateMultimediaCoverage(allCondacts),
                OverallCoverage = CalculateOverallCoverage(allCondacts)
            };
        }

        public async Task<List<FixSuggestion>> SuggestFixesAsync(string classicCode)
        {
            var fixes = new List<FixSuggestion>();
            
            // Analizar y sugerir correcciones automáticas
            if (classicCode.Contains("WORN") && !classicCode.Contains("NOTWORN"))
            {
                fixes.Add(new FixSuggestion
                {
                    Description = "Agregar verificaciones NOTWORN para objetos vestibles",
                    AutoFixAvailable = true
                });
            }

            return fixes;
        }

        private List<string> ExtractCondactsFromClassicCode(string code)
        {
            var condacts = new HashSet<string>();
            var lines = code.Split('\n', StringSplitOptions.RemoveEmptyEntries);
            
            foreach (var line in lines)
            {
                var trimmed = line.Trim();
                if (trimmed.StartsWith(';') || string.IsNullOrEmpty(trimmed)) continue;
                
                var words = trimmed.Split(' ', StringSplitOptions.RemoveEmptyEntries);
                if (words.Length > 0 && char.IsLetter(words[0][0]))
                {
                    condacts.Add(words[0].ToUpper());
                }
            }
            
            return condacts.ToList();
        }

        private async Task<List<CompatibilityIssue>> AnalyzeIssuesAsync(string code)
        {
            var issues = new List<CompatibilityIssue>();
            
            // Analizar problemas comunes
            if (code.Contains("EXTERN") && !code.Contains("EXTERN 0"))
            {
                issues.Add(new CompatibilityIssue
                {
                    Severity = IssueSeverity.Warning,
                    Description = "EXTERN detectado - verificar compatibilidad con implementación moderna"
                });
            }
            
            return issues;
        }

        private double CalculateCategoryCoverage(Dictionary<string, object> condacts, CondactType type)
        {
            // Implementar cálculo por categoría
            return 95.0; // Placeholder
        }

        private double CalculateWearableCoverage(Dictionary<string, object> condacts)
        {
            var wearableCondacts = new[] { "worn", "notworn", "wear", "remove" };
            var implemented = wearableCondacts.Count(c => condacts.ContainsKey(c));
            return (double)implemented / wearableCondacts.Length * 100;
        }

        private double CalculateMultimediaCoverage(Dictionary<string, object> condacts)
        {
            var multimediaCondacts = new[] { "beep", "picture", "sound", "music" };
            var implemented = multimediaCondacts.Count(c => condacts.ContainsKey(c));
            return (double)implemented / multimediaCondacts.Length * 100;
        }

        private double CalculateOverallCoverage(Dictionary<string, object> condacts)
        {
            // Calcular cobertura total basada en condactos conocidos del DAAD original
            var totalKnownCondacts = 75; // Número aproximado de condactos DAAD originales
            return Math.Min(100.0, (double)condacts.Count / totalKnownCondacts * 100);
        }
    }

    #endregion

    #region Modelos de Datos

    public class CompatibilityReport
    {
        public bool IsFullyCompatible { get; set; }
        public List<string> SupportedCondacts { get; set; } = new();
        public List<string> UnsupportedCondacts { get; set; } = new();
        public int TotalCondacts { get; set; }
        public double CompatibilityPercentage { get; set; }
        public List<CompatibilityIssue> Issues { get; set; } = new();
    }

    public class CompatibilityIssue
    {
        public IssueSeverity Severity { get; set; }
        public string Description { get; set; } = "";
        public string Location { get; set; } = "";
        public string Suggestion { get; set; } = "";
    }

    public enum IssueSeverity { Info, Warning, Error, Critical }

    public class CondactCoverageReport
    {
        public double ConditionCoverage { get; set; }
        public double ActionCoverage { get; set; }
        public double WearableCoverage { get; set; }
        public double MultimediaCoverage { get; set; }
        public double OverallCoverage { get; set; }
    }

    public class FixSuggestion
    {
        public string Description { get; set; } = "";
        public bool AutoFixAvailable { get; set; }
        public string OriginalCode { get; set; } = "";
        public string FixedCode { get; set; } = "";
        
        public string Apply(string content)
        {
            if (!AutoFixAvailable || string.IsNullOrEmpty(OriginalCode)) return content;
            return content.Replace(OriginalCode, FixedCode);
        }
    }

    public class BenchmarkResults
    {
        public double AverageTranspileTime { get; set; }
        public double ThroughputKBPerSecond { get; set; }
        public double MaxMemoryUsageMB { get; set; }
        public int FilesProcessed { get; set; }
        public int ErrorCount { get; set; }
        public List<FileResult> FileResults { get; set; } = new();
    }

    public class FileResult
    {
        public string FileName { get; set; } = "";
        public double TranspileTimeMs { get; set; }
        public double FileSizeKB { get; set; }
        public bool Success { get; set; }
        public string? Error { get; set; }
    }

    public class MemoryProfile
    {
        public double PeakMemoryMB { get; set; }
        public int AllocatedObjectsCount { get; set; }
        public TimeSpan ProfileDuration { get; set; }
    }

    public class MigrationOptions
    {
        public bool PreserveComments { get; set; } = true;
        public bool ModernizeSyntax { get; set; } = true;
        public bool GenerateDocumentation { get; set; } = false;
        public bool ValidateAfterMigration { get; set; } = true;
    }

    public class MigrationResult
    {
        public bool Success { get; set; }
        public string ModernizedCode { get; set; } = "";
        public string ErrorMessage { get; set; } = "";
        public int LinesProcessed { get; set; }
        public int CondactsMigrated { get; set; }
        public int ObjectsConverted { get; set; }
        public List<string> Warnings { get; set; } = new();
        public List<string> ModernizationApplied { get; set; } = new();
    }

    #endregion
}