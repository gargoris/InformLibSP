using System;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Logging.Console;
using DaadModern.Transpiler;
using DaadModern.Interfaces;

namespace DaadModern
{
    public static class TestTranspiler
    {
        public static async Task Main(string[] args)
        {
            // Crear logger
            using var loggerFactory = LoggerFactory.Create(builder =>
                builder.AddConsole().SetMinimumLevel(LogLevel.Information));
            var logger = loggerFactory.CreateLogger<CompleteDaadTranspiler>();

            // Crear transpilador
            var transpiler = new CompleteDaadTranspiler(logger);

            // Obtener condactos soportados
            var condactos = transpiler.GetSupportedCondactos();
            Console.WriteLine($"Condactos soportados: {string.Join(", ", condactos)}");
            Console.WriteLine($"Total condactos: {condactos.Count()}");

            // Obtener información de un condacto específico
            var info = transpiler.GetCondactoInfo("at");
            Console.WriteLine($"Condacto 'at': {info.ClassicName} - {info.Type}");

            // Probar transpilación
            var options = new TranspileOptions
            {
                IncludeHeader = true,
                IncludeFooter = true,
                IncludeComments = true
            };

            var result = await transpiler.TranspileAsync("test code", options);
            Console.WriteLine($"Transpilación exitosa: {result.Success}");
            Console.WriteLine($"Condactos usados: {result.Statistics.CondactosUsed}");

            // Verificar compatibilidad
            var compatibility = await transpiler.CheckCompatibilityAsync("test code");
            Console.WriteLine($"Compatibilidad: {compatibility.CompatibilityPercentage}%");
        }
    }
}
