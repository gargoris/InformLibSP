// =====================================================================
// DAAD# - Implementación Fase 4: Acciones Automáticas
// =====================================================================

using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Extensions.Logging;

namespace DaadModern.Core
{
    /// <summary>
    /// Implementación de CondActs de Fase 4: Acciones automáticas para mejorar UX
    /// </summary>
    public partial class Phase4CondactsImplementer
    {
        private readonly ILogger<Phase4CondactsImplementer> _logger;
        private readonly GameState _gameState;

        public Phase4CondactsImplementer(ILogger<Phase4CondactsImplementer> logger, GameState gameState)
        {
            _logger = logger;
            _gameState = gameState;
        }

        #region Acciones Automáticas

        /// <summary>
        /// AUTOG - Coger automático
        /// ID: 96 - Coge automáticamente el objeto si está presente
        /// </summary>
        public bool ExecuteAutog()
        {
            _logger.LogInformation("Ejecutando AUTOG - Coger automático");
            
            var currentObject = _gameState.CurrentObject;
            
            if (currentObject == 255) // No hay objeto actual
            {
                _logger.LogDebug("AUTOG: No hay objeto actual definido");
                return false;
            }
            
            // Verificar si el objeto está presente (en la localización actual)
            if (!IsObjectPresent(currentObject))
            {
                _logger.LogDebug($"AUTOG: Objeto {currentObject} no está presente");
                return false;
            }
            
            // Verificar si ya lo lleva el jugador
            if (IsObjectCarried(currentObject))
            {
                _logger.LogDebug($"AUTOG: Objeto {currentObject} ya está siendo llevado");
                return true; // Ya lo tiene, consideramos éxito
            }
            
            // Verificar capacidad de carga
            if (!CanCarryMoreObjects())
            {
                _logger.LogDebug("AUTOG: Jugador no puede cargar más objetos");
                return false;
            }
            
            // Coger el objeto
            _gameState.MoveObject(currentObject, 254); // 254 = llevado por jugador
            _logger.LogInformation($"AUTOG: Objeto {currentObject} cogido automáticamente");
            
            return true;
        }

        /// <summary>
        /// AUTOD - Soltar automático
        /// ID: 95 - Suelta automáticamente el objeto en la localización actual
        /// </summary>
        public bool ExecuteAutod()
        {
            _logger.LogInformation("Ejecutando AUTOD - Soltar automático");
            
            var currentObject = _gameState.CurrentObject;
            
            if (currentObject == 255)
            {
                _logger.LogDebug("AUTOD: No hay objeto actual definido");
                return false;
            }
            
            // Verificar si el jugador lleva el objeto
            if (!IsObjectCarried(currentObject))
            {
                _logger.LogDebug($"AUTOD: Objeto {currentObject} no está siendo llevado");
                return false;
            }
            
            // Soltar el objeto en la localización actual
            _gameState.MoveObject(currentObject, _gameState.CurrentLocation);
            _logger.LogInformation($"AUTOD: Objeto {currentObject} soltado automáticamente en localización {_gameState.CurrentLocation}");
            
            return true;
        }

        /// <summary>
        /// AUTOW - Vestir automático
        /// ID: 94 - Viste automáticamente el objeto si es posible
        /// </summary>
        public bool ExecuteAutow()
        {
            _logger.LogInformation("Ejecutando AUTOW - Vestir automático");
            
            var currentObject = _gameState.CurrentObject;
            
            if (currentObject == 255)
            {
                _logger.LogDebug("AUTOW: No hay objeto actual definido");
                return false;
            }
            
            // Verificar si el objeto es vestible
            if (!IsObjectWearable(currentObject))
            {
                _logger.LogDebug($"AUTOW: Objeto {currentObject} no es vestible");
                return false;
            }
            
            // Verificar si ya lo lleva puesto
            if (IsObjectWorn(currentObject))
            {
                _logger.LogDebug($"AUTOW: Objeto {currentObject} ya está siendo usado");
                return true; // Ya puesto, consideramos éxito
            }
            
            // Verificar si el jugador lo tiene
            if (!IsObjectCarried(currentObject))
            {
                // Intentar cogerlo primero
                if (!ExecuteAutog())
                {
                    _logger.LogDebug("AUTOW: No se pudo coger el objeto automáticamente");
                    return false;
                }
            }
            
            // Vestir el objeto
            _gameState.MoveObject(currentObject, 253); // 253 = vestido por jugador
            _logger.LogInformation($"AUTOW: Objeto {currentObject} vestido automáticamente");
            
            return true;
        }

        /// <summary>
        /// AUTOR - Quitar automático
        /// ID: 93 - Quita automáticamente el objeto vestido
        /// </summary>
        public bool ExecuteAutor()
        {
            _logger.LogInformation("Ejecutando AUTOR - Quitar automático");
            
            var currentObject = _gameState.CurrentObject;
            
            if (currentObject == 255)
            {
                _logger.LogDebug("AUTOR: No hay objeto actual definido");
                return false;
            }
            
            // Verificar si el objeto está siendo usado
            if (!IsObjectWorn(currentObject))
            {
                _logger.LogDebug($"AUTOR: Objeto {currentObject} no está siendo usado");
                return false;
            }
            
            // Quitar el objeto (pasarlo a llevado)
            _gameState.MoveObject(currentObject, 254); // 254 = llevado por jugador
            _logger.LogInformation($"AUTOR: Objeto {currentObject} quitado automáticamente");
            
            return true;
        }

        /// <summary>
        /// AUTOP - Meter automático
        /// ID: 92 - Mete automáticamente el objeto en el contenedor especificado
        /// </summary>
        public bool ExecuteAutop(int containerId)
        {
            _logger.LogInformation($"Ejecutando AUTOP - Meter automático en contenedor {containerId}");
            
            var currentObject = _gameState.CurrentObject;
            
            if (currentObject == 255)
            {
                _logger.LogDebug("AUTOP: No hay objeto actual definido");
                return false;
            }
            
            var resolvedContainerId = ResolveValue(containerId);
            
            // Verificar si el contenedor existe y es un contenedor
            if (!IsValidContainer(resolvedContainerId))
            {
                _logger.LogDebug($"AUTOP: {resolvedContainerId} no es un contenedor válido");
                return false;
            }
            
            // Verificar si el objeto está disponible para ser metido
            if (!IsObjectCarried(currentObject))
            {
                _logger.LogDebug($"AUTOP: Objeto {currentObject} no está siendo llevado");
                return false;
            }
            
            // Verificar capacidad del contenedor
            if (!CanContainerHoldObject(resolvedContainerId, currentObject))
            {
                _logger.LogDebug($"AUTOP: Contenedor {resolvedContainerId} no puede contener objeto {currentObject}");
                return false;
            }
            
            // Meter el objeto en el contenedor
            _gameState.MoveObject(currentObject, resolvedContainerId);
            _logger.LogInformation($"AUTOP: Objeto {currentObject} metido automáticamente en contenedor {resolvedContainerId}");
            
            return true;
        }

        /// <summary>
        /// AUTOT - Sacar automático
        /// ID: 91 - Saca automáticamente el objeto del contenedor especificado
        /// </summary>
        public bool ExecuteAutot(int containerId)
        {
            _logger.LogInformation($"Ejecutando AUTOT - Sacar automático de contenedor {containerId}");
            
            var currentObject = _gameState.CurrentObject;
            
            if (currentObject == 255)
            {
                _logger.LogDebug("AUTOT: No hay objeto actual definido");
                return false;
            }
            
            var resolvedContainerId = ResolveValue(containerId);
            
            // Verificar si el objeto está en el contenedor
            var objectLocation = _gameState.GetObjectLocation(currentObject);
            if (objectLocation != resolvedContainerId)
            {
                _logger.LogDebug($"AUTOT: Objeto {currentObject} no está en contenedor {resolvedContainerId}");
                return false;
            }
            
            // Verificar capacidad de carga del jugador
            if (!CanCarryMoreObjects())
            {
                _logger.LogDebug("AUTOT: Jugador no puede cargar más objetos");
                return false;
            }
            
            // Sacar el objeto del contenedor (al inventario del jugador)
            _gameState.MoveObject(currentObject, 254); // 254 = llevado por jugador
            _logger.LogInformation($"AUTOT: Objeto {currentObject} sacado automáticamente de contenedor {resolvedContainerId}");
            
            return true;
        }

        #endregion

        #region Métodos de Apoyo

        private bool IsObjectPresent(int objectId)
        {
            var location = _gameState.GetObjectLocation(objectId);
            return location == _gameState.CurrentLocation;
        }

        private bool IsObjectCarried(int objectId)
        {
            return _gameState.GetObjectLocation(objectId) == 254; // 254 = llevado
        }

        private bool IsObjectWorn(int objectId)
        {
            return _gameState.GetObjectLocation(objectId) == 253; // 253 = vestido
        }

        private bool IsObjectWearable(int objectId)
        {
            if (!_gameState.Objects.ContainsKey(objectId))
                return false;
                
            var obj = _gameState.Objects[objectId];
            return obj.Attributes.Contains(AttributeIds.Wearable);
        }

        private bool CanCarryMoreObjects()
        {
            var carriedObjects = _gameState.GetCarriedObjects();
            var maxCarry = GetMaxCarryCapacity();
            
            return carriedObjects.Count < maxCarry;
        }

        private int GetMaxCarryCapacity()
        {
            // Capacidad por defecto, puede ser configurada por el juego
            return 10; // DAAD tradicional permite hasta 10 objetos
        }

        private bool IsValidContainer(int objectId)
        {
            if (!_gameState.Objects.ContainsKey(objectId))
                return false;
                
            var obj = _gameState.Objects[objectId];
            return obj.Attributes.Contains(AttributeIds.Container);
        }

        private bool CanContainerHoldObject(int containerId, int objectId)
        {
            if (!_gameState.Objects.ContainsKey(containerId) || !_gameState.Objects.ContainsKey(objectId))
                return false;
                
            var container = _gameState.Objects[containerId];
            var obj = _gameState.Objects[objectId];
            
            // Verificar peso máximo del contenedor
            var currentWeight = container.CurrentWeight;
            var objectWeight = obj.Weight;
            var maxWeight = container.Weight; // Peso máximo que puede contener
            
            return (currentWeight + objectWeight) <= maxWeight;
        }

        private int ResolveValue(int value)
        {
            if (value > 255)
                return value;
                
            var flagValue = _gameState.GetFlag(value);
            if (flagValue != null)
            {
                return Convert.ToInt32(flagValue);
            }
            
            return value;
        }

        /// <summary>
        /// Obtiene información de CondActs de Fase 4 para el transpilador
        /// </summary>
        public static Dictionary<string, CondactInfo> GetPhase4Condacts()
        {
            return new Dictionary<string, CondactInfo>
            {
                ["autog"] = new(CondactType.Action, "AUTOG", 0, "Coger automático"),
                ["autod"] = new(CondactType.Action, "AUTOD", 0, "Soltar automático"),
                ["autow"] = new(CondactType.Action, "AUTOW", 0, "Vestir automático"),
                ["autor"] = new(CondactType.Action, "AUTOR", 0, "Quitar automático"),
                ["autop"] = new(CondactType.Action, "AUTOP", 1, "Meter automático"),
                ["autot"] = new(CondactType.Action, "AUTOT", 1, "Sacar automático")
            };
        }

        #endregion
    }
}
