// =====================================================================
// DAAD Moderno - Condactos Faltantes para Fase 1
// Implementación completa de condactos críticos
// =====================================================================

using System;
using System.Collections.Generic;
using Microsoft.Extensions.Logging;

namespace DaadModern.Transpiler
{
    /// <summary>
    /// Extensión del transpilador con condactos faltantes críticos
    /// </summary>
    public static class MissingCondactsExtension
    {
        /// <summary>
        /// Condactos críticos que faltan para completar Fase 1
        /// </summary>
        public static Dictionary<string, CondactInfo> GetMissingCriticalCondacts()
        {
            return new Dictionary<string, CondactInfo>
            {
                // ===== CONDICIONES DE ESTADO ZERO/NOTZERO =====
                ["zero"] = new(CondactType.Condition, "ZERO", 1, "Verificar si flag/counter = 0"),
                ["notzero"] = new(CondactType.Condition, "NOTZERO", 1, "Verificar si flag/counter ≠ 0"),
                
                // ===== SISTEMA DE OBJETOS VESTIBLES =====
                ["worn"] = new(CondactType.Condition, "WORN", 1, "Objeto vestido"),
                ["notworn"] = new(CondactType.Condition, "NOTWORN", 1, "Objeto NO vestido"),
                ["wear"] = new(CondactType.Action, "WEAR", 1, "Vestir objeto"),
                ["remove"] = new(CondactType.Action, "REMOVE", 1, "Quitar objeto vestido"),
                
                // ===== CONTROL DE FLUJO DEL JUEGO =====
                ["restart"] = new(CondactType.Action, "RESTART", 0, "Reiniciar juego"),
                ["quit"] = new(CondactType.Action, "QUIT", 0, "Salir del juego"),
                
                // ===== VERIFICACIÓN DE UBICACIONES =====
                ["isat"] = new(CondactType.Condition, "ISAT", 2, "Verificar localización de objeto"),
                
                // ===== ELEMENTOS ALEATORIOS =====
                ["chance"] = new(CondactType.Condition, "CHANCE", 1, "Probabilidad (0-100%)"),
                
                // ===== SISTEMA DE TURNOS =====
                ["turns"] = new(CondactType.Condition, "TURNS", 2, "Comparar contador de turnos"),
                
                // ===== COMPARACIÓN DE OBJETOS =====
                ["same"] = new(CondactType.Condition, "SAME", 2, "Mismo objeto que última vez")
            };
        }
    }
    
    /// <summary>
    /// Modelo extendido para objetos vestibles
    /// </summary>
    public class WearableObject : ModernObject
    {
        public bool IsWearable { get; set; } = false;
        public bool IsCurrentlyWorn { get; set; } = false;
        public WearableSlot Slot { get; set; } = WearableSlot.None;
        public string? WornDescription { get; set; }
        public List<string> RequiredStats { get; set; } = new();
        
        public override string ToString() => 
            $"{base.ToString()} [Wearable: {IsWearable}, Worn: {IsCurrentlyWorn}, Slot: {Slot}]";
    }
    
    /// <summary>
    /// Tipos de slots para objetos vestibles
    /// </summary>
    public enum WearableSlot
    {
        None,
        Head,        // casco, sombrero
        Body,        // armadura, ropa
        Hands,       // guantes, anillos
        Feet,        // botas, zapatos
        Weapon,      // armas empuñadas
        Shield,      // escudos
        Neck,        // collares, amuletos
        Ring         // anillos especiales
    }
    
    /// <summary>
    /// Transpilador extendido con condactos faltantes
    /// </summary>
    public partial class ExtendedCondactTranspiler
    {
        private readonly Dictionary<string, CondactInfo> _extendedCondacts;
        private readonly ILogger<ExtendedCondactTranspiler> _logger;
        
        public ExtendedCondactTranspiler(ILogger<ExtendedCondactTranspiler> logger)
        {
            _logger = logger;
            _extendedCondacts = MissingCondactsExtension.GetMissingCriticalCondacts();
        }
        
        /// <summary>
        /// Transpila condición ZERO/NOTZERO
        /// </summary>
        public List<ClassicCondact> TranspileZeroCondition(ModernCondition condition)
        {
            var flagOrCounter = GetFlagOrCounterNumber(condition.Arguments[0]);
            var condactName = condition.Function.ToUpper();
            
            return new List<ClassicCondact>
            {
                new() { Name = condactName, Parameters = [flagOrCounter] }
            };
        }
        
        /// <summary>
        /// Transpila condición de objeto vestible (WORN/NOTWORN)
        /// </summary>
        public List<ClassicCondact> TranspileWornCondition(ModernCondition condition)
        {
            var objectNumber = GetObjectNumber(condition.Arguments[0]);
            var condactName = condition.Function.ToUpper();
            
            return new List<ClassicCondact>
            {
                new() { Name = condactName, Parameters = [objectNumber] }
            };
        }
        
        /// <summary>
        /// Transpila acción de vestir/quitar (WEAR/REMOVE)
        /// </summary>
        public List<ClassicCondact> TranspileWearAction(ModernAction action)
        {
            var objectNumber = GetObjectNumber(action.Arguments[0]);
            var condactName = action.Function.ToUpper();
            
            var result = new List<ClassicCondact>
            {
                new() { Name = condactName, Parameters = [objectNumber] }
            };
            
            // Agregar verificaciones automáticas si es necesario
            if (action.Function == "wear")
            {
                // Verificar que el objeto no esté ya vestido
                result.Insert(0, new() { Name = "NOTWORN", Parameters = [objectNumber] });
            }
            
            return result;
        }
        
        /// <summary>
        /// Transpila condición ISAT (verificar localización de objeto)
        /// </summary>
        public List<ClassicCondact> TranspileIsAtCondition(ModernCondition condition)
        {
            var objectNumber = GetObjectNumber(condition.Arguments[0]);
            var locationNumber = GetLocationNumber(condition.Arguments[1]);
            
            return new List<ClassicCondact>
            {
                new() { Name = "ISAT", Parameters = [objectNumber, locationNumber] }
            };
        }
        
        /// <summary>
        /// Transpila condición CHANCE (probabilidad)
        /// </summary>
        public List<ClassicCondact> TranspileChanceCondition(ModernCondition condition)
        {
            var percentage = int.Parse(condition.Arguments[0]);
            
            return new List<ClassicCondact>
            {
                new() { Name = "CHANCE", Parameters = [percentage] }
            };
        }
        
        /// <summary>
        /// Transpila acciones de control de flujo (RESTART/QUIT)
        /// </summary>
        public List<ClassicCondact> TranspileGameControlAction(ModernAction action)
        {
            var condactName = action.Function.ToUpper();
            
            return new List<ClassicCondact>
            {
                new() { Name = condactName, Parameters = [] }
            };
        }
        
        /// <summary>
        /// Validar si todos los condactos críticos están soportados
        /// </summary>
        public ValidationResult ValidateCriticalCondacts(DaadProgram program)
        {
            var result = new ValidationResult { IsValid = true };
            var unsupportedCondacts = new List<string>();
            
            // Verificar condiciones en responses
            foreach (var response in program.Responses)
            {
                CheckConditionsSupport(response.Conditions, unsupportedCondacts);
                CheckActionsSupport(response.Actions, unsupportedCondacts);
            }
            
            // Verificar procesos
            foreach (var process in program.Processes)
            {
                CheckConditionsSupport(process.Conditions, unsupportedCondacts);
                CheckActionsSupport(process.Actions, unsupportedCondacts);
            }
            
            if (unsupportedCondacts.Count > 0)
            {
                result.IsValid = false;
                result.Errors = unsupportedCondacts.Select(c => 
                    $"Condacto no soportado: {c}").ToList();
            }
            
            return result;
        }
        
        private void CheckConditionsSupport(List<ModernCondition> conditions, List<string> unsupported)
        {
            foreach (var condition in conditions)
            {
                if (!_extendedCondacts.ContainsKey(condition.Function.ToLower()) && 
                    !IsBasicCondition(condition.Function))
                {
                    unsupported.Add(condition.Function);
                }
            }
        }
        
        private void CheckActionsSupport(List<ModernAction> actions, List<string> unsupported)
        {
            foreach (var action in actions)
            {
                if (!_extendedCondacts.ContainsKey(action.Function.ToLower()) && 
                    !IsBasicAction(action.Function))
                {
                    unsupported.Add(action.Function);
                }
            }
        }
        
        private bool IsBasicCondition(string function) => 
            new[] { "at", "present", "carried", "eq", "lt", "gt" }.Contains(function.ToLower());
            
        private bool IsBasicAction(string function) => 
            new[] { "goto", "get", "drop", "message", "set" }.Contains(function.ToLower());
    }
    
    /// <summary>
    /// Resultado de validación extendido
    /// </summary>
    public class ValidationResult
    {
        public bool IsValid { get; set; }
        public List<string> Errors { get; set; } = new();
        public List<string> Warnings { get; set; } = new();
        public Dictionary<string, int> CondactUsage { get; set; } = new();
    }
}