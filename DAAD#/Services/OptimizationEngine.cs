using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Extensions.Logging;
using DaadModern.Interfaces;

namespace DaadModern.Services
{
    public class OptimizationEngine
    {
        private readonly ILogger<OptimizationEngine> _logger;
        public int LastOptimizationCount { get; private set; }

        public OptimizationEngine(ILogger<OptimizationEngine> logger)
        {
            _logger = logger;
        }

        public async Task<string> OptimizeAsync(string code, TranspileOptions options)
        {
            _logger.LogInformation("Iniciando optimización de código...");
            
            LastOptimizationCount = 0;
            var optimizedCode = code;

            if (options.OptimizationLevel >= 1)
            {
                optimizedCode = await OptimizeLevel1(optimizedCode);
            }

            if (options.OptimizationLevel >= 2)
            {
                optimizedCode = await OptimizeLevel2(optimizedCode);
            }

            if (options.OptimizationLevel >= 3)
            {
                optimizedCode = await OptimizeLevel3(optimizedCode);
            }

            _logger.LogInformation("Optimización completada: {Count} optimizaciones aplicadas", LastOptimizationCount);
            return optimizedCode;
        }

        private async Task<string> OptimizeLevel1(string code)
        {
            var lines = code.Split('\n');
            var optimizedLines = new List<string>();
            
            foreach (var line in lines)
            {
                var trimmedLine = line.Trim();
                
                if (string.IsNullOrEmpty(trimmedLine))
                {
                    if (optimizedLines.Count > 0 && !string.IsNullOrEmpty(optimizedLines.Last()))
                    {
                        optimizedLines.Add(line);
                    }
                    continue;
                }

                var optimizedLine = await OptimizeRedundantCommands(trimmedLine);
                if (optimizedLine != trimmedLine)
                {
                    LastOptimizationCount++;
                }

                optimizedLines.Add(optimizedLine);
            }

            return string.Join('\n', optimizedLines);
        }

        private async Task<string> OptimizeLevel2(string code)
        {
            var lines = code.Split('\n');
            var optimizedLines = new List<string>();
            
            for (int i = 0; i < lines.Length; i++)
            {
                var currentLine = lines[i].Trim();
                
                if (i < lines.Length - 1)
                {
                    var nextLine = lines[i + 1].Trim();
                    var combined = await TryCombineCommands(currentLine, nextLine);
                    
                    if (combined != null)
                    {
                        optimizedLines.Add(combined);
                        i++; // Saltar la siguiente línea
                        LastOptimizationCount++;
                        continue;
                    }
                }

                optimizedLines.Add(lines[i]);
            }

            return string.Join('\n', optimizedLines);
        }

        private async Task<string> OptimizeLevel3(string code)
        {
            var lines = code.Split('\n');
            var optimizedLines = new List<string>();
            
            for (int i = 0; i < lines.Length; i++)
            {
                var line = lines[i].Trim();
                
                if (line.StartsWith("EQ") || line.StartsWith("GT") || line.StartsWith("LT"))
                {
                    var optimizedSequence = await OptimizeConditionSequence(lines, i);
                    if (optimizedSequence.Count > 1)
                    {
                        optimizedLines.AddRange(optimizedSequence);
                        i += optimizedSequence.Count - 1;
                        LastOptimizationCount++;
                        continue;
                    }
                }

                optimizedLines.Add(lines[i]);
            }

            return string.Join('\n', optimizedLines);
        }

        private Task<string> OptimizeRedundantCommands(string line)
        {
            if (line.StartsWith("SET ") && line.Contains(" 0"))
            {
                return Task.FromResult(line.Replace("SET ", "CLEAR ").Replace(" 0", ""));
            }

            if (line.StartsWith("PLUS ") && line.Contains(" 0"))
            {
                return Task.FromResult(""); // Eliminar suma de 0
            }

            if (line.StartsWith("MINUS ") && line.Contains(" 0"))
            {
                return Task.FromResult(""); // Eliminar resta de 0
            }

            return Task.FromResult(line);
        }

        private Task<string?> TryCombineCommands(string line1, string line2)
        {
            if (line1.StartsWith("SET ") && line2.StartsWith("CLEAR "))
            {
                var flag1 = line1.Substring(4).Trim();
                var flag2 = line2.Substring(6).Trim();
                
                if (flag1 == flag2)
                {
                    return Task.FromResult<string?>(""); // Cancelar SET y CLEAR del mismo flag
                }
            }

            if (line1.StartsWith("GET ") && line2.StartsWith("DROP "))
            {
                var obj1 = line1.Substring(4).Trim();
                var obj2 = line2.Substring(5).Trim();
                
                if (obj1 == obj2)
                {
                    return Task.FromResult<string?>(""); // Cancelar GET y DROP del mismo objeto
                }
            }

            return Task.FromResult<string?>(null);
        }

        private async Task<List<string>> OptimizeConditionSequence(string[] lines, int startIndex)
        {
            var sequence = new List<string>();
            var currentIndex = startIndex;
            
            while (currentIndex < lines.Length)
            {
                var line = lines[currentIndex].Trim();
                
                if (line.StartsWith("EQ") || line.StartsWith("GT") || line.StartsWith("LT"))
                {
                    sequence.Add(lines[currentIndex]);
                    currentIndex++;
                }
                else
                {
                    break;
                }
            }

            if (sequence.Count > 2)
            {
                return await OptimizeMultipleConditions(sequence);
            }

            return sequence;
        }

        private async Task<List<string>> OptimizeMultipleConditions(List<string> conditions)
        {
            var optimized = new List<string>();
            
            var flagGroups = conditions
                .GroupBy(c => GetFlagFromCondition(c))
                .Where(g => g.Count() > 1);

            foreach (var group in flagGroups)
            {
                var combined = await CombineConditionsOfSameFlag(group.ToList());
                optimized.AddRange(combined);
            }

            var ungrouped = conditions.Except(flagGroups.SelectMany(g => g));
            optimized.AddRange(ungrouped);

            return optimized;
        }

        private static string GetFlagFromCondition(string condition)
        {
            var parts = condition.Split(' ');
            return parts.Length > 1 ? parts[1] : "";
        }

        private Task<List<string>> CombineConditionsOfSameFlag(List<string> conditions)
        {
            if (conditions.Count <= 1)
                return Task.FromResult(conditions);

            return Task.FromResult(conditions);
        }
    }
}
