// =====================================================================
// DAAD# - Implementación Fase 3: Familia COPY
// =====================================================================

using System;
using System.Collections.Generic;
using Microsoft.Extensions.Logging;

namespace DaadModern.Core
{
    /// <summary>
    /// Implementación de CondActs de Fase 3: Familia COPY para manipulación de datos
    /// </summary>
    public partial class Phase3CondactsImplementer
    {
        private readonly ILogger<Phase3CondactsImplementer> _logger;
        private readonly GameState _gameState;

        public Phase3CondactsImplementer(ILogger<Phase3CondactsImplementer> logger, GameState gameState)
        {
            _logger = logger;
            _gameState = gameState;
        }

        #region Familia COPY

        /// <summary>
        /// COPYFF - Copiar flag a flag
        /// ID: 101 - Copia el valor de un flag a otro flag
        /// </summary>
        public bool ExecuteCopyff(int sourceFlag, int targetFlag)
        {
            _logger.LogInformation($"Ejecutando COPYFF flag {sourceFlag} -> flag {targetFlag}");
            
            if (sourceFlag < 0 || sourceFlag > 255 || targetFlag < 0 || targetFlag > 255)
            {
                _logger.LogWarning($"COPYFF: IDs de flags fuera de rango (0-255): {sourceFlag}, {targetFlag}");
                return false;
            }
            
            var sourceValue = _gameState.GetFlag(sourceFlag);
            _gameState.SetFlag(targetFlag, sourceValue);
            
            _logger.LogDebug($"COPYFF: Copiado valor {sourceValue} de flag {sourceFlag} a flag {targetFlag}");
            return true;
        }

        /// <summary>
        /// COPYOF - Copiar objeto a flag
        /// ID: 100 - Copia la localización de un objeto a un flag
        /// </summary>
        public bool ExecuteCopyof(int objectId, int targetFlag)
        {
            _logger.LogInformation($"Ejecutando COPYOF objeto {objectId} -> flag {targetFlag}");
            
            if (targetFlag < 0 || targetFlag > 255)
            {
                _logger.LogWarning($"COPYOF: ID de flag fuera de rango (0-255): {targetFlag}");
                return false;
            }
            
            var resolvedObjectId = ResolveValue(objectId);
            
            if (_gameState.ObjectLocations.ContainsKey(resolvedObjectId))
            {
                var objectLocation = _gameState.ObjectLocations[resolvedObjectId];
                _gameState.SetFlag(targetFlag, objectLocation);
                
                _logger.LogDebug($"COPYOF: Copiada localización {objectLocation} del objeto {resolvedObjectId} a flag {targetFlag}");
                return true;
            }
            else
            {
                // Si el objeto no existe, copiar -1 (no existe)
                _gameState.SetFlag(targetFlag, -1);
                _logger.LogDebug($"COPYOF: Objeto {resolvedObjectId} no existe, copiado -1 a flag {targetFlag}");
                return true;
            }
        }

        /// <summary>
        /// COPYFO - Copiar flag a objeto
        /// ID: 99 - Copia el valor de un flag como nueva localización de un objeto
        /// </summary>
        public bool ExecuteCopyfo(int sourceFlag, int objectId)
        {
            _logger.LogInformation($"Ejecutando COPYFO flag {sourceFlag} -> objeto {objectId}");
            
            if (sourceFlag < 0 || sourceFlag > 255)
            {
                _logger.LogWarning($"COPYFO: ID de flag fuera de rango (0-255): {sourceFlag}");
                return false;
            }
            
            var resolvedObjectId = ResolveValue(objectId);
            var newLocation = Convert.ToInt32(_gameState.GetFlag(sourceFlag));
            
            // Validar que la nueva localización es válida
            if (newLocation < -1 || newLocation > 255)
            {
                _logger.LogWarning($"COPYFO: Localización inválida {newLocation} para objeto {resolvedObjectId}");
                return false;
            }
            
            _gameState.ObjectLocations[resolvedObjectId] = newLocation;
            
            _logger.LogDebug($"COPYFO: Movido objeto {resolvedObjectId} a localización {newLocation} desde flag {sourceFlag}");
            return true;
        }

        /// <summary>
        /// COPYOO - Copiar objeto a objeto
        /// ID: 98 - Copia la localización de un objeto a otro objeto
        /// </summary>
        public bool ExecuteCopyoo(int sourceObjectId, int targetObjectId)
        {
            _logger.LogInformation($"Ejecutando COPYOO objeto {sourceObjectId} -> objeto {targetObjectId}");
            
            var resolvedSourceId = ResolveValue(sourceObjectId);
            var resolvedTargetId = ResolveValue(targetObjectId);
            
            if (_gameState.ObjectLocations.ContainsKey(resolvedSourceId))
            {
                var sourceLocation = _gameState.ObjectLocations[resolvedSourceId];
                _gameState.ObjectLocations[resolvedTargetId] = sourceLocation;
                
                _logger.LogDebug($"COPYOO: Copiada localización {sourceLocation} del objeto {resolvedSourceId} al objeto {resolvedTargetId}");
                return true;
            }
            else
            {
                // Si el objeto fuente no existe, mover el objeto destino a -1 (no existe)
                _gameState.ObjectLocations[resolvedTargetId] = -1;
                _logger.LogDebug($"COPYOO: Objeto fuente {resolvedSourceId} no existe, movido objeto {resolvedTargetId} a -1");
                return true;
            }
        }

        /// <summary>
        /// COPYBF - Copiar byte a flag
        /// ID: 97 - Copia un byte específico de un flag a otro flag
        /// </summary>
        public bool ExecuteCopybf(int sourceFlag, int targetFlag)
        {
            _logger.LogInformation($"Ejecutando COPYBF byte de flag {sourceFlag} -> flag {targetFlag}");
            
            if (sourceFlag < 0 || sourceFlag > 255 || targetFlag < 0 || targetFlag > 255)
            {
                _logger.LogWarning($"COPYBF: IDs de flags fuera de rango (0-255): {sourceFlag}, {targetFlag}");
                return false;
            }
            
            var sourceValue = Convert.ToInt32(_gameState.GetFlag(sourceFlag));
            
            // Extraer solo el byte bajo (0-255)
            var byteValue = sourceValue & 0xFF;
            
            _gameState.SetFlag(targetFlag, byteValue);
            
            _logger.LogDebug($"COPYBF: Copiado byte {byteValue} de flag {sourceFlag} (valor completo: {sourceValue}) a flag {targetFlag}");
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
            if (value > 255)
            {
                return value; // Valor literal directo
            }
            
            // Para objetos, usar el valor directo si está en rango
            if (value >= 0 && value <= 255)
            {
                // Verificar si es una referencia a flag o un ID de objeto directo
                var flagValue = _gameState.GetFlag(value);
                if (flagValue != null && Convert.ToInt32(flagValue) != 0)
                {
                    return Convert.ToInt32(flagValue);
                }
            }
            
            // Si no hay flag o es 0, usar el valor literal
            return value;
        }

        /// <summary>
        /// Obtiene información de CondActs de Fase 3 para el transpilador
        /// </summary>
        public static Dictionary<string, CondactInfo> GetPhase3Condacts()
        {
            return new Dictionary<string, CondactInfo>
            {
                ["copyff"] = new(CondactType.Action, "COPYFF", 2, "Copiar flag a flag"),
                ["copyof"] = new(CondactType.Action, "COPYOF", 2, "Copiar objeto a flag"),
                ["copyfo"] = new(CondactType.Action, "COPYFO", 2, "Copiar flag a objeto"),
                ["copyoo"] = new(CondactType.Action, "COPYOO", 2, "Copiar objeto a objeto"),
                ["copybf"] = new(CondactType.Action, "COPYBF", 2, "Copiar byte a flag")
            };
        }

        #endregion
    }
}
