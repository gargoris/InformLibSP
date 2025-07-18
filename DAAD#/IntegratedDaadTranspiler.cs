// =====================================================================
// DAAD# - Transpilador Completo con Todas las Fases Implementadas
// =====================================================================

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Extensions.Logging;

namespace DaadModern.Core
{
    /// <summary>
    /// Transpilador completo que integra todas las fases de CondActs implementadas
    /// </summary>
    public class IntegratedDaadTranspiler : ICompleteDaadTranspiler
    {
        private readonly ILogger<IntegratedDaadTranspiler> _logger;
        private readonly Dictionary<string, CondactInfo> _allCondacts;
        private readonly CriticalCondactsImplementer _phase1Implementer;
        private readonly Phase2CondactsImplementer _phase2Implementer;
        private readonly Phase3CondactsImplementer _phase3Implementer;
        private readonly Phase4CondactsImplementer _phase4Implementer;

        public IntegratedDaadTranspiler(ILogger<IntegratedDaadTranspiler> logger)
        {
            _logger = logger;
            _allCondacts = InitializeAllCondacts();
            
            // Inicializar implementadores de cada fase
            var gameState = new GameState();
            gameState.Initialize();
            
            _phase1Implementer = new CriticalCondactsImplementer(
                LoggerFactory.Create(builder => builder.AddConsole()).CreateLogger<CriticalCondactsImplementer>(),
                gameState);
            _phase2Implementer = new Phase2CondactsImplementer(
                LoggerFactory.Create(builder => builder.AddConsole()).CreateLogger<Phase2CondactsImplementer>(),
                gameState);
            _phase3Implementer = new Phase3CondactsImplementer(
                LoggerFactory.Create(builder => builder.AddConsole()).CreateLogger<Phase3CondactsImplementer>(),
                gameState);
            _phase4Implementer = new Phase4CondactsImplementer(
                LoggerFactory.Create(builder => builder.AddConsole()).CreateLogger<Phase4CondactsImplementer>(),
                gameState);
        }

        #region Interfaz ICompleteDaadTranspiler

        public string TranspileToClassic(string modernDaadCode)
        {
            _logger.LogInformation("Iniciando transpilación DAAD Moderno -> Clásico");
            
            var lines = modernDaadCode.Split('\n', StringSplitOptions.RemoveEmptyEntries);
            var result = new StringBuilder();
            
            foreach (var line in lines)
            {
                var trimmedLine = line.Trim();
                if (string.IsNullOrEmpty(trimmedLine) || trimmedLine.StartsWith("//"))
                {
                    continue; // Saltar comentarios y líneas vacías
                }
                
                var classicLine = TranspileLineToClassic(trimmedLine);
                if (!string.IsNullOrEmpty(classicLine))
                {
                    result.AppendLine(classicLine);
                }
            }
            
            _logger.LogInformation("Transpilación completada");
            return result.ToString();
        }

        public string TranspileToModern(string classicDaadCode)
        {
            _logger.LogInformation("Iniciando transpilación DAAD Clásico -> Moderno");
            
            var lines = classicDaadCode.Split('\n', StringSplitOptions.RemoveEmptyEntries);
            var result = new StringBuilder();
            
            foreach (var line in lines)
            {
                var trimmedLine = line.Trim();
                if (string.IsNullOrEmpty(trimmedLine))
                {
                    continue;
                }
                
                var modernLine = TranspileLineToModern(trimmedLine);
                if (!string.IsNullOrEmpty(modernLine))
                {
                    result.AppendLine(modernLine);
                }
            }
            
            _logger.LogInformation("Transpilación completada");
            return result.ToString();
        }

        public IEnumerable<string> GetSupportedCondacts()
        {
            return _allCondacts.Keys;
        }

        public bool IsCondactSupported(string condactName)
        {
            return _allCondacts.ContainsKey(condactName.ToLower());
        }

        public CondactInfo? GetCondactInfo(string condactName)
        {
            var key = condactName.ToLower();
            return _allCondacts.ContainsKey(key) ? _allCondacts[key] : null;
        }

        #endregion

        #region Transpilación de Líneas

        private string TranspileLineToClassic(string modernLine)
        {
            // Analizar línea de DAAD moderno y convertir a clásico
            var parts = modernLine.Split(' ', StringSplitOptions.RemoveEmptyEntries);
            if (parts.Length == 0) return string.Empty;
            
            var condactName = parts[0].ToLower();
            
            if (!_allCondacts.ContainsKey(condactName))
            {
                _logger.LogWarning($"CondAct no soportado: {condactName}");
                return $"// CondAct no soportado: {condactName}";
            }
            
            var condactInfo = _allCondacts[condactName];
            var classicName = condactInfo.Name;
            
            // Convertir parámetros
            var parameters = parts.Skip(1).Take(condactInfo.ParameterCount).ToArray();
            var classicParameters = string.Join(" ", parameters);
            
            return string.IsNullOrEmpty(classicParameters) 
                ? classicName 
                : $"{classicName} {classicParameters}";
        }

        private string TranspileLineToModern(string classicLine)
        {
            // Analizar línea de DAAD clásico y convertir a moderno
            var parts = classicLine.Split(' ', StringSplitOptions.RemoveEmptyEntries);
            if (parts.Length == 0) return string.Empty;
            
            var classicName = parts[0].ToUpper();
            
            // Buscar CondAct por nombre clásico
            var condactPair = _allCondacts.FirstOrDefault(kvp => 
                kvp.Value.Name.Equals(classicName, StringComparison.OrdinalIgnoreCase));
                
            if (condactPair.Key == null)
            {
                _logger.LogWarning($"CondAct clásico no reconocido: {classicName}");
                return $"// CondAct no reconocido: {classicName}";
            }
            
            var modernName = condactPair.Key;
            var condactInfo = condactPair.Value;
            
            // Convertir parámetros
            var parameters = parts.Skip(1).Take(condactInfo.ParameterCount).ToArray();
            var modernParameters = string.Join(" ", parameters);
            
            return string.IsNullOrEmpty(modernParameters) 
                ? modernName 
                : $"{modernName} {modernParameters}";
        }

        #endregion

        #region Inicialización de CondActs

        private Dictionary<string, CondactInfo> InitializeAllCondacts()
        {
            var allCondacts = new Dictionary<string, CondactInfo>();
            
            // Integrar CondActs de todas las fases
            AddCondactsFromPhase(allCondacts, GetBasicCondacts()); // CondActs básicos originales
            AddCondactsFromPhase(allCondacts, CriticalCondactsImplementation.GetCriticalCondacts()); // Fase 1
            AddCondactsFromPhase(allCondacts, Phase2CondactsImplementer.GetPhase2Condacts()); // Fase 2
            AddCondactsFromPhase(allCondacts, Phase3CondactsImplementer.GetPhase3Condacts()); // Fase 3
            AddCondactsFromPhase(allCondacts, Phase4CondactsImplementer.GetPhase4Condacts()); // Fase 4
            
            _logger.LogInformation($"Inicializados {allCondacts.Count} CondActs en total");
            return allCondacts;
        }

        private void AddCondactsFromPhase(Dictionary<string, CondactInfo> target, Dictionary<string, CondactInfo> source)
        {
            foreach (var kvp in source)
            {
                if (target.ContainsKey(kvp.Key))
                {
                    _logger.LogWarning($"CondAct duplicado detectado: {kvp.Key}");
                }
                target[kvp.Key] = kvp.Value;
            }
        }

        private Dictionary<string, CondactInfo> GetBasicCondacts()
        {
            return new Dictionary<string, CondactInfo>
            {
                // CondActs básicos ya implementados en el sistema base
                ["at"] = new(CondactType.Condition, "AT", 1, "Jugador en localización"),
                ["notat"] = new(CondactType.Condition, "NOTAT", 1, "Jugador NO en localización"),
                ["present"] = new(CondactType.Condition, "PRESENT", 1, "Objeto presente"),
                ["absent"] = new(CondactType.Condition, "ABSENT", 1, "Objeto ausente"),
                ["worn"] = new(CondactType.Condition, "WORN", 1, "Objeto vestido"),
                ["notworn"] = new(CondactType.Condition, "NOTWORN", 1, "Objeto NO vestido"),
                ["carried"] = new(CondactType.Condition, "CARRIED", 1, "Objeto llevado"),
                ["notcarr"] = new(CondactType.Condition, "NOTCARR", 1, "Objeto NO llevado"),
                ["zero"] = new(CondactType.Condition, "ZERO", 1, "Flag es cero"),
                ["notzero"] = new(CondactType.Condition, "NOTZERO", 1, "Flag NO es cero"),
                ["eq"] = new(CondactType.Condition, "EQ", 2, "Igual a"),
                ["gt"] = new(CondactType.Condition, "GT", 2, "Mayor que"),
                ["lt"] = new(CondactType.Condition, "LT", 2, "Menor que"),
                ["chance"] = new(CondactType.Condition, "CHANCE", 1, "Probabilidad"),
                ["same"] = new(CondactType.Condition, "SAME", 2, "Mismo"),
                ["isat"] = new(CondactType.Condition, "ISAT", 2, "Objeto en localización"),
                
                // Acciones básicas
                ["goto"] = new(CondactType.Action, "GOTO", 1, "Ir a localización"),
                ["get"] = new(CondactType.Action, "GET", 1, "Coger objeto"),
                ["drop"] = new(CondactType.Action, "DROP", 1, "Soltar objeto"),
                ["wear"] = new(CondactType.Action, "WEAR", 1, "Vestir objeto"),
                ["remove"] = new(CondactType.Action, "REMOVE", 1, "Quitar objeto"),
                ["message"] = new(CondactType.Action, "MESSAGE", 1, "Mostrar mensaje"),
                ["restart"] = new(CondactType.Action, "RESTART", 0, "Reiniciar juego"),
                ["end"] = new(CondactType.Action, "END", 0, "Terminar proceso"),
                ["done"] = new(CondactType.Action, "DONE", 0, "Marcar como hecho"),
                ["set"] = new(CondactType.Action, "SET", 1, "Establecer flag"),
                ["clear"] = new(CondactType.Action, "CLEAR", 1, "Limpiar flag"),
                ["let"] = new(CondactType.Action, "LET", 2, "Asignar valor"),
                ["plus"] = new(CondactType.Action, "PLUS", 2, "Sumar a flag"),
                ["minus"] = new(CondactType.Action, "MINUS", 2, "Restar de flag"),
                ["create"] = new(CondactType.Action, "CREATE", 1, "Crear objeto"),
                ["destroy"] = new(CondactType.Action, "DESTROY", 1, "Destruir objeto"),
                ["place"] = new(CondactType.Action, "PLACE", 2, "Colocar objeto"),
                ["cls"] = new(CondactType.Action, "CLS", 0, "Limpiar pantalla"),
                ["desc"] = new(CondactType.Action, "DESC", 1, "Describir localización"),
                ["print"] = new(CondactType.Action, "PRINT", 1, "Imprimir texto"),
                ["newline"] = new(CondactType.Action, "NEWLINE", 0, "Nueva línea")
            };
        }

        #endregion

        #region Estadísticas

        public TranspilerStatistics GetStatistics()
        {
            var totalCondacts = 125; // Total de CondActs en DAAD original
            var implementedCondacts = _allCondacts.Count;
            var coveragePercentage = (implementedCondacts * 100.0) / totalCondacts;
            
            var conditionCount = _allCondacts.Values.Count(c => c.Type == CondactType.Condition);
            var actionCount = _allCondacts.Values.Count(c => c.Type == CondactType.Action);
            
            return new TranspilerStatistics
            {
                TotalCondacts = totalCondacts,
                ImplementedCondacts = implementedCondacts,
                CoveragePercentage = coveragePercentage,
                ConditionsImplemented = conditionCount,
                ActionsImplemented = actionCount,
                Phase1Implemented = 12, // CondActs críticos
                Phase2Implemented = 14, // Parser avanzado y comparaciones
                Phase3Implemented = 5,  // Familia COPY
                Phase4Implemented = 6   // Acciones automáticas
            };
        }

        #endregion
    }

    /// <summary>
    /// Estadísticas del transpilador
    /// </summary>
    public class TranspilerStatistics
    {
        public int TotalCondacts { get; set; }
        public int ImplementedCondacts { get; set; }
        public double CoveragePercentage { get; set; }
        public int ConditionsImplemented { get; set; }
        public int ActionsImplemented { get; set; }
        public int Phase1Implemented { get; set; }
        public int Phase2Implemented { get; set; }
        public int Phase3Implemented { get; set; }
        public int Phase4Implemented { get; set; }
    }

    /// <summary>
    /// Interfaz del transpilador completo
    /// </summary>
    public interface ICompleteDaadTranspiler
    {
        string TranspileToClassic(string modernDaadCode);
        string TranspileToModern(string classicDaadCode);
        IEnumerable<string> GetSupportedCondacts();
        bool IsCondactSupported(string condactName);
        CondactInfo? GetCondactInfo(string condactName);
    }
}
