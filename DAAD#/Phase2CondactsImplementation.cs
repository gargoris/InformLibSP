// =====================================================================
// DAAD# - Implementación Fase 2: Parser Avanzado y Comparaciones
// =====================================================================

using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Extensions.Logging;

namespace DaadModern.Core
{
    /// <summary>
    /// Implementación de CondActs de Fase 2: Parser avanzado y comparaciones
    /// </summary>
    public partial class Phase2CondactsImplementer
    {
        private readonly ILogger<Phase2CondactsImplementer> _logger;
        private readonly GameState _gameState;

        public Phase2CondactsImplementer(ILogger<Phase2CondactsImplementer> logger, GameState gameState)
        {
            _logger = logger;
            _gameState = gameState;
        }

        #region Parser Avanzado

        /// <summary>
        /// ADJECT1 - Primer adjetivo
        /// ID: 115 - Verificar primer adjetivo parseado
        /// </summary>
        public bool CheckAdject1(int adjectiveId)
        {
            _logger.LogDebug($"Verificando ADJECT1 {adjectiveId}");
            
            var firstAdjective = _gameState.ParsedWords
                .Where(w => w.Type == WordType.Adjective)
                .FirstOrDefault();
                
            return firstAdjective?.Id == adjectiveId;
        }

        /// <summary>
        /// ADJECT2 - Segundo adjetivo
        /// ID: 114 - Verificar segundo adjetivo parseado
        /// </summary>
        public bool CheckAdject2(int adjectiveId)
        {
            _logger.LogDebug($"Verificando ADJECT2 {adjectiveId}");
            
            var adjectives = _gameState.ParsedWords
                .Where(w => w.Type == WordType.Adjective)
                .ToList();
                
            return adjectives.Count > 1 && adjectives[1].Id == adjectiveId;
        }

        /// <summary>
        /// ADVERB - Adverbio
        /// ID: 113 - Verificar adverbio parseado
        /// </summary>
        public bool CheckAdverb(int adverbId)
        {
            _logger.LogDebug($"Verificando ADVERB {adverbId}");
            
            var adverb = _gameState.ParsedWords
                .Where(w => w.Type == WordType.Adverb)
                .FirstOrDefault();
                
            return adverb?.Id == adverbId;
        }

        /// <summary>
        /// PREP - Preposición
        /// ID: 112 - Verificar preposición parseada
        /// </summary>
        public bool CheckPrep(int prepositionId)
        {
            _logger.LogDebug($"Verificando PREP {prepositionId}");
            
            var preposition = _gameState.ParsedWords
                .Where(w => w.Type == WordType.Preposition)
                .FirstOrDefault();
                
            return preposition?.Id == prepositionId;
        }

        /// <summary>
        /// NOUN2 - Segundo sustantivo
        /// ID: 111 - Verificar segundo sustantivo parseado
        /// </summary>
        public bool CheckNoun2(int nounId)
        {
            _logger.LogDebug($"Verificando NOUN2 {nounId}");
            
            var nouns = _gameState.ParsedWords
                .Where(w => w.Type == WordType.Noun)
                .ToList();
                
            return nouns.Count > 1 && nouns[1].Id == nounId;
        }

        #endregion

        #region Comparaciones

        /// <summary>
        /// NOTEQ - No igual
        /// ID: 110 - Verificar que dos valores NO son iguales
        /// </summary>
        public bool CheckNoteq(int value1, int value2)
        {
            _logger.LogDebug($"Verificando NOTEQ {value1} != {value2}");
            
            var resolvedValue1 = ResolveValue(value1);
            var resolvedValue2 = ResolveValue(value2);
            
            return resolvedValue1 != resolvedValue2;
        }

        /// <summary>
        /// NOTSAME - No mismo
        /// ID: 109 - Verificar que dos referencias NO son la misma
        /// </summary>
        public bool CheckNotsame(int reference1, int reference2)
        {
            _logger.LogDebug($"Verificando NOTSAME {reference1} != {reference2}");
            
            // En DAAD, SAME/NOTSAME compara referencias directas sin resolver
            return reference1 != reference2;
        }

        /// <summary>
        /// BIGGER - Mayor que
        /// ID: 108 - Verificar que valor1 > valor2
        /// </summary>
        public bool CheckBigger(int value1, int value2)
        {
            _logger.LogDebug($"Verificando BIGGER {value1} > {value2}");
            
            var resolvedValue1 = ResolveValue(value1);
            var resolvedValue2 = ResolveValue(value2);
            
            return resolvedValue1 > resolvedValue2;
        }

        /// <summary>
        /// SMALLER - Menor que
        /// ID: 107 - Verificar que valor1 < valor2
        /// </summary>
        public bool CheckSmaller(int value1, int value2)
        {
            _logger.LogDebug($"Verificando SMALLER {value1} < {value2}");
            
            var resolvedValue1 = ResolveValue(value1);
            var resolvedValue2 = ResolveValue(value2);
            
            return resolvedValue1 < resolvedValue2;
        }

        /// <summary>
        /// ISNOTAT - Objeto NO está en localización
        /// ID: 106 - Verificar que objeto NO está en localización específica
        /// </summary>
        public bool CheckIsnotat(int objectId, int locationId)
        {
            _logger.LogDebug($"Verificando ISNOTAT objeto {objectId} no en localización {locationId}");
            
            var resolvedObjectId = ResolveValue(objectId);
            var resolvedLocationId = ResolveValue(locationId);
            
            if (!_gameState.ObjectLocations.ContainsKey(resolvedObjectId))
            {
                return true; // Objeto no existe, por tanto no está en la localización
            }
            
            return _gameState.ObjectLocations[resolvedObjectId] != resolvedLocationId;
        }

        #endregion

        #region Control de Procesos

        /// <summary>
        /// ISDONE - Proceso terminó exitosamente
        /// ID: 105 - Verificar si el último proceso terminó con éxito
        /// </summary>
        public bool CheckIsdone()
        {
            _logger.LogDebug("Verificando ISDONE");
            
            // En DAAD, ISDONE verifica el flag de estado del último proceso ejecutado
            var doneFlag = _gameState.GetFlag(50); // Flag 50 tradicionalmente usado para DONE
            return Convert.ToInt32(doneFlag) == 1;
        }

        /// <summary>
        /// ISNDONE - Proceso terminó sin éxito
        /// ID: 104 - Verificar si el último proceso NO terminó con éxito
        /// </summary>
        public bool CheckIsndone()
        {
            _logger.LogDebug("Verificando ISNDONE");
            
            var doneFlag = _gameState.GetFlag(50);
            return Convert.ToInt32(doneFlag) != 1;
        }

        /// <summary>
        /// NOTDONE - Marcar proceso como no exitoso
        /// ID: 103 - Establecer que el proceso actual no fue exitoso
        /// </summary>
        public bool ExecuteNotdone()
        {
            _logger.LogInformation("Ejecutando NOTDONE");
            
            // Limpiar el flag DONE
            _gameState.SetFlag(50, 0);
            
            // También podemos marcar en el estado del proceso actual
            _gameState.ProcessExecutionSuccess = false;
            
            return true;
        }

        /// <summary>
        /// SKIP - Saltar N CondActs
        /// ID: 102 - Saltar las siguientes N líneas de CondActs
        /// </summary>
        public bool ExecuteSkip(int linesToSkip)
        {
            _logger.LogInformation($"Ejecutando SKIP {linesToSkip}");
            
            if (linesToSkip < 0)
            {
                _logger.LogWarning("SKIP con valor negativo, ignorando");
                return false;
            }
            
            // Incrementar el contador de línea del proceso actual
            _gameState.CurrentLine += linesToSkip;
            
            return true;
        }

        #endregion

        #region Métodos de Apoyo

        /// <summary>
        /// Resuelve un valor que puede ser literal o referencia a flag
        /// </summary>
        private int ResolveValue(int value)
        {
            // En DAAD, valores 0-255 pueden ser literales o referencias a flags
            // Tradicionalmente, valores > 127 se consideran literales
            if (value > 255)
            {
                return value; // Valor literal directo
            }
            
            // Verificar si es una referencia a flag
            var flagValue = _gameState.GetFlag(value);
            if (flagValue != null)
            {
                return Convert.ToInt32(flagValue);
            }
            
            // Si no hay flag, usar el valor literal
            return value;
        }

        /// <summary>
        /// Obtiene información de CondActs de Fase 2 para el transpilador
        /// </summary>
        public static Dictionary<string, CondactInfo> GetPhase2Condacts()
        {
            return new Dictionary<string, CondactInfo>
            {
                // Parser Avanzado
                ["adject1"] = new(CondactType.Condition, "ADJECT1", 1, "Primer adjetivo"),
                ["adject2"] = new(CondactType.Condition, "ADJECT2", 1, "Segundo adjetivo"),
                ["adverb"] = new(CondactType.Condition, "ADVERB", 1, "Adverbio"),
                ["prep"] = new(CondactType.Condition, "PREP", 1, "Preposición"),
                ["noun2"] = new(CondactType.Condition, "NOUN2", 1, "Segundo sustantivo"),
                
                // Comparaciones
                ["noteq"] = new(CondactType.Condition, "NOTEQ", 2, "No igual"),
                ["notsame"] = new(CondactType.Condition, "NOTSAME", 2, "No mismo"),
                ["bigger"] = new(CondactType.Condition, "BIGGER", 2, "Mayor que"),
                ["smaller"] = new(CondactType.Condition, "SMALLER", 2, "Menor que"),
                ["isnotat"] = new(CondactType.Condition, "ISNOTAT", 2, "Objeto NO en localización"),
                
                // Control de Procesos
                ["isdone"] = new(CondactType.Condition, "ISDONE", 0, "Proceso terminó exitosamente"),
                ["isndone"] = new(CondactType.Condition, "ISNDONE", 0, "Proceso terminó sin éxito"),
                ["notdone"] = new(CondactType.Action, "NOTDONE", 0, "Marcar proceso como no exitoso"),
                ["skip"] = new(CondactType.Action, "SKIP", 1, "Saltar N CondActs")
            };
        }

        #endregion
    }
}
