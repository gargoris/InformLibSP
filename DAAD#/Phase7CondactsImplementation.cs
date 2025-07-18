// =====================================================================
// DAAD# - Implementación Fase 7: Utilidades y Sistema Avanzado
// =====================================================================

using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Extensions.Logging;

namespace DaadModern.Core
{
    /// <summary>
    /// Implementación de CondActs de Fase 7: Utilidades, sistema y funciones especializadas
    /// </summary>
    public partial class Phase7CondactsImplementer
    {
        private readonly ILogger<Phase7CondactsImplementer> _logger;
        private readonly GameState _gameState;
        private readonly ISystemManager _systemManager;
        private readonly IInputManager _inputManager;

        public Phase7CondactsImplementer(ILogger<Phase7CondactsImplementer> logger, 
                                       GameState gameState,
                                       ISystemManager systemManager,
                                       IInputManager inputManager)
        {
            _logger = logger;
            _gameState = gameState;
            _systemManager = systemManager;
            _inputManager = inputManager;
        }

        #region CondActs de Entrada y Control

        /// <summary>
        /// INKEY - Verificar si se presionó una tecla
        /// ID: 61 - Condición que verifica entrada de teclado sin bloqueo
        /// </summary>
        public bool ExecuteInkey()
        {
            _logger.LogInformation("Ejecutando INKEY - Verificar tecla presionada");
            
            try
            {
                var keyPressed = _inputManager.CheckKeyPressed();
                if (keyPressed)
                {
                    _gameState.LastKeyPressed = _inputManager.GetLastKey();
                    _logger.LogInformation($"INKEY: Tecla presionada - {_gameState.LastKeyPressed}");
                }
                else
                {
                    _logger.LogDebug("INKEY: No hay teclas presionadas");
                }
                
                return keyPressed;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "INKEY: Error verificando entrada de teclado");
                return false;
            }
        }

        #endregion

        #region CondActs de Cálculos y Flags

        /// <summary>
        /// ADD - Sumar valores de flags
        /// ID: 60 - Suma el valor de dos flags y almacena en el primero
        /// </summary>
        public bool ExecuteAdd(int flag1, int flag2)
        {
            _logger.LogInformation($"Ejecutando ADD - Sumar flag {flag1} + flag {flag2}");
            
            try
            {
                var value1 = _gameState.GetFlag(flag1) ?? 0;
                var value2 = _gameState.GetFlag(flag2) ?? 0;
                var result = value1 + value2;
                
                _gameState.SetFlag(flag1, result);
                
                _logger.LogInformation($"ADD: {value1} + {value2} = {result} -> flag {flag1}");
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"ADD: Error sumando flags {flag1} y {flag2}");
                return false;
            }
        }

        /// <summary>
        /// SUB - Restar valores de flags
        /// ID: 59 - Resta el valor del segundo flag del primero
        /// </summary>
        public bool ExecuteSub(int flag1, int flag2)
        {
            _logger.LogInformation($"Ejecutando SUB - Restar flag {flag1} - flag {flag2}");
            
            try
            {
                var value1 = _gameState.GetFlag(flag1) ?? 0;
                var value2 = _gameState.GetFlag(flag2) ?? 0;
                var result = value1 - value2;
                
                _gameState.SetFlag(flag1, result);
                
                _logger.LogInformation($"SUB: {value1} - {value2} = {result} -> flag {flag1}");
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"SUB: Error restando flags {flag1} y {flag2}");
                return false;
            }
        }

        /// <summary>
        /// RANDOM - Generar número aleatorio
        /// ID: 58 - Genera un número aleatorio entre 0 y N-1
        /// </summary>
        public bool ExecuteRandom(int maxValue)
        {
            _logger.LogInformation($"Ejecutando RANDOM - Número aleatorio 0-{maxValue - 1}");
            
            try
            {
                var random = new Random();
                var result = random.Next(maxValue);
                
                _gameState.SetFlag(0, result); // DAAD almacena resultado en flag 0
                
                _logger.LogInformation($"RANDOM: Generado {result} (0-{maxValue - 1})");
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"RANDOM: Error generando número aleatorio");
                return false;
            }
        }

        #endregion

        #region CondActs del Sistema

        /// <summary>
        /// OK - Marcar proceso como exitoso
        /// ID: 54 - Establece flag de éxito del proceso
        /// </summary>
        public bool ExecuteOk()
        {
            _logger.LogInformation("Ejecutando OK - Marcar proceso exitoso");
            
            try
            {
                _gameState.ProcessExecutionSuccess = true;
                _gameState.SetFlag(1, 1); // Flag 1 tradicionalmente usado para éxito
                
                _logger.LogInformation("OK: Proceso marcado como exitoso");
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "OK: Error marcando proceso como exitoso");
                return false;
            }
        }

        /// <summary>
        /// NEWTEXT - Limpiar buffer de texto
        /// ID: 53 - Limpia el buffer de entrada de texto
        /// </summary>
        public bool ExecuteNewtext()
        {
            _logger.LogInformation("Ejecutando NEWTEXT - Limpiar buffer de texto");
            
            try
            {
                _gameState.CurrentInput = string.Empty;
                _gameState.InputBuffer = string.Empty;
                _inputManager.ClearInputBuffer();
                
                _logger.LogInformation("NEWTEXT: Buffer de texto limpiado");
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "NEWTEXT: Error limpiando buffer");
                return false;
            }
        }

        /// <summary>
        /// DISPLAY - Mostrar pantalla específica
        /// ID: 52 - Muestra una pantalla o layout específico
        /// </summary>
        public bool ExecuteDisplay(int screenId)
        {
            _logger.LogInformation($"Ejecutando DISPLAY - Mostrar pantalla {screenId}");
            
            var resolvedScreenId = ResolveValue(screenId);
            
            try
            {
                _systemManager.ShowScreen(resolvedScreenId);
                _gameState.CurrentScreen = resolvedScreenId;
                
                _logger.LogInformation($"DISPLAY: Pantalla {resolvedScreenId} mostrada");
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"DISPLAY: Error mostrando pantalla {resolvedScreenId}");
                return false;
            }
        }

        /// <summary>
        /// CALL - Llamar rutina externa
        /// ID: 51 - Llama a una rutina o función externa
        /// </summary>
        public bool ExecuteCall(int routineId)
        {
            _logger.LogInformation($"Ejecutando CALL - Llamar rutina {routineId}");
            
            var resolvedRoutineId = ResolveValue(routineId);
            
            try
            {
                var result = _systemManager.CallExternalRoutine(resolvedRoutineId);
                _gameState.SetFlag(0, result ? 1 : 0); // Resultado en flag 0
                
                _logger.LogInformation($"CALL: Rutina {resolvedRoutineId} ejecutada - resultado: {result}");
                return result;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"CALL: Error llamando rutina {resolvedRoutineId}");
                return false;
            }
        }

        /// <summary>
        /// SYNONYM - Definir sinónimo
        /// ID: 50 - Define un sinónimo para una palabra
        /// </summary>
        public bool ExecuteSynonym(int wordId, int synonymId)
        {
            _logger.LogInformation($"Ejecutando SYNONYM - Definir sinónimo {wordId} -> {synonymId}");
            
            var resolvedWordId = ResolveValue(wordId);
            var resolvedSynonymId = ResolveValue(synonymId);
            
            try
            {
                _gameState.AddSynonym(resolvedWordId, resolvedSynonymId);
                
                _logger.LogInformation($"SYNONYM: Sinónimo definido {resolvedWordId} -> {resolvedSynonymId}");
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"SYNONYM: Error definiendo sinónimo");
                return false;
            }
        }

        #endregion

        #region CondActs de Guardado Avanzado

        /// <summary>
        /// RAMSAVE - Guardar estado en RAM
        /// ID: 49 - Guarda el estado actual en memoria RAM
        /// </summary>
        public bool ExecuteRamsave()
        {
            _logger.LogInformation("Ejecutando RAMSAVE - Guardar en RAM");
            
            try
            {
                _gameState.SaveStateToRam();
                
                _logger.LogInformation("RAMSAVE: Estado guardado en RAM exitosamente");
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "RAMSAVE: Error guardando estado en RAM");
                return false;
            }
        }

        /// <summary>
        /// RAMLOAD - Cargar estado desde RAM
        /// ID: 48 - Carga el estado desde memoria RAM
        /// </summary>
        public bool ExecuteRamload()
        {
            _logger.LogInformation("Ejecutando RAMLOAD - Cargar desde RAM");
            
            try
            {
                var success = _gameState.LoadStateFromRam();
                
                if (success)
                {
                    _logger.LogInformation("RAMLOAD: Estado cargado desde RAM exitosamente");
                }
                else
                {
                    _logger.LogWarning("RAMLOAD: No hay estado guardado en RAM");
                }
                
                return success;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "RAMLOAD: Error cargando estado desde RAM");
                return false;
            }
        }

        /// <summary>
        /// SAVEAT - Guardar posición del cursor
        /// ID: 47 - Guarda la posición actual del cursor
        /// </summary>
        public bool ExecuteSaveat()
        {
            _logger.LogInformation("Ejecutando SAVEAT - Guardar posición cursor");
            
            try
            {
                var (x, y) = _systemManager.GetCursorPosition();
                _gameState.SavedCursorX = x;
                _gameState.SavedCursorY = y;
                
                _logger.LogInformation($"SAVEAT: Posición cursor guardada ({x}, {y})");
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "SAVEAT: Error guardando posición cursor");
                return false;
            }
        }

        /// <summary>
        /// BACKAT - Restaurar posición del cursor
        /// ID: 46 - Restaura la posición guardada del cursor
        /// </summary>
        public bool ExecuteBackat()
        {
            _logger.LogInformation("Ejecutando BACKAT - Restaurar posición cursor");
            
            try
            {
                _systemManager.SetCursorPosition(_gameState.SavedCursorX, _gameState.SavedCursorY);
                
                _logger.LogInformation($"BACKAT: Posición cursor restaurada ({_gameState.SavedCursorX}, {_gameState.SavedCursorY})");
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "BACKAT: Error restaurando posición cursor");
                return false;
            }
        }

        #endregion

        #region CondActs Especializados

        /// <summary>
        /// GFX - Comando gráfico
        /// ID: 45 - Ejecuta un comando gráfico específico
        /// </summary>
        public bool ExecuteGfx(int commandId)
        {
            _logger.LogInformation($"Ejecutando GFX - Comando gráfico {commandId}");
            
            var resolvedCommandId = ResolveValue(commandId);
            
            try
            {
                var result = _systemManager.ExecuteGraphicsCommand(resolvedCommandId);
                
                _logger.LogInformation($"GFX: Comando gráfico {resolvedCommandId} ejecutado - resultado: {result}");
                return result;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"GFX: Error ejecutando comando gráfico {resolvedCommandId}");
                return false;
            }
        }

        /// <summary>
        /// MOUSE - Leer estado del ratón
        /// ID: 44 - Lee la posición y estado del ratón
        /// </summary>
        public bool ExecuteMouse()
        {
            _logger.LogInformation("Ejecutando MOUSE - Leer estado ratón");
            
            try
            {
                var mouseState = _inputManager.GetMouseState();
                
                _gameState.SetFlag(10, mouseState.X); // X en flag 10
                _gameState.SetFlag(11, mouseState.Y); // Y en flag 11
                _gameState.SetFlag(12, mouseState.ButtonPressed ? 1 : 0); // Botón en flag 12
                
                _logger.LogInformation($"MOUSE: Estado leído - X:{mouseState.X}, Y:{mouseState.Y}, Botón:{mouseState.ButtonPressed}");
                return mouseState.ButtonPressed;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "MOUSE: Error leyendo estado del ratón");
                return false;
            }
        }

        /// <summary>
        /// REDO - Rehacer último comando
        /// ID: 43 - Repite la última acción del jugador
        /// </summary>
        public bool ExecuteRedo()
        {
            _logger.LogInformation("Ejecutando REDO - Rehacer comando");
            
            try
            {
                if (!string.IsNullOrEmpty(_gameState.LastCommand))
                {
                    _gameState.CurrentInput = _gameState.LastCommand;
                    _logger.LogInformation($"REDO: Comando repetido - {_gameState.LastCommand}");
                    return true;
                }
                else
                {
                    _logger.LogDebug("REDO: No hay comando previo para repetir");
                    return false;
                }
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "REDO: Error rehaciendo comando");
                return false;
            }
        }

        /// <summary>
        /// MOVE - Mover usando conexiones
        /// ID: 42 - Mueve el jugador usando el sistema de conexiones
        /// </summary>
        public bool ExecuteMove(int direction)
        {
            _logger.LogInformation($"Ejecutando MOVE - Mover dirección {direction}");
            
            var resolvedDirection = ResolveValue(direction);
            
            try
            {
                var currentLocation = _gameState.CurrentLocation;
                var connection = _gameState.GetConnection(currentLocation, resolvedDirection);
                
                if (connection != null && connection.DestinationId >= 0)
                {
                    _gameState.CurrentLocation = connection.DestinationId;
                    _logger.LogInformation($"MOVE: Movido de {currentLocation} a {connection.DestinationId} (dirección {resolvedDirection})");
                    return true;
                }
                else
                {
                    _logger.LogDebug($"MOVE: No hay conexión válida en dirección {resolvedDirection}");
                    return false;
                }
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"MOVE: Error moviendo en dirección {resolvedDirection}");
                return false;
            }
        }

        #endregion

        #region Métodos de Apoyo

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
        /// Obtiene información de CondActs de Fase 7 para el transpilador
        /// </summary>
        public static Dictionary<string, CondactInfo> GetPhase7Condacts()
        {
            return new Dictionary<string, CondactInfo>
            {
                // Entrada y Control
                ["inkey"] = new(CondactType.Condition, "INKEY", 0, "Verificar tecla presionada"),
                
                // Cálculos y Flags
                ["add"] = new(CondactType.Action, "ADD", 2, "Sumar flags"),
                ["sub"] = new(CondactType.Action, "SUB", 2, "Restar flags"),
                ["random"] = new(CondactType.Action, "RANDOM", 1, "Número aleatorio"),
                
                // Sistema
                ["ok"] = new(CondactType.Action, "OK", 0, "Marcar proceso exitoso"),
                ["newtext"] = new(CondactType.Action, "NEWTEXT", 0, "Limpiar buffer texto"),
                ["display"] = new(CondactType.Action, "DISPLAY", 1, "Mostrar pantalla"),
                ["call"] = new(CondactType.Action, "CALL", 1, "Llamar rutina"),
                ["synonym"] = new(CondactType.Action, "SYNONYM", 2, "Definir sinónimo"),
                
                // Guardado Avanzado
                ["ramsave"] = new(CondactType.Action, "RAMSAVE", 0, "Guardar en RAM"),
                ["ramload"] = new(CondactType.Action, "RAMLOAD", 0, "Cargar desde RAM"),
                ["saveat"] = new(CondactType.Action, "SAVEAT", 0, "Guardar posición cursor"),
                ["backat"] = new(CondactType.Action, "BACKAT", 0, "Restaurar posición cursor"),
                
                // Especializados
                ["gfx"] = new(CondactType.Action, "GFX", 1, "Comando gráfico"),
                ["mouse"] = new(CondactType.Condition, "MOUSE", 0, "Leer estado ratón"),
                ["redo"] = new(CondactType.Action, "REDO", 0, "Rehacer comando"),
                ["move"] = new(CondactType.Action, "MOVE", 1, "Mover usando conexiones")
            };
        }

        #endregion
    }

    #region Interfaces y Tipos de Apoyo

    /// <summary>
    /// Interfaz para gestión de entrada
    /// </summary>
    public interface IInputManager
    {
        bool CheckKeyPressed();
        char GetLastKey();
        void ClearInputBuffer();
        MouseState GetMouseState();
    }

    /// <summary>
    /// Estado del ratón
    /// </summary>
    public class MouseState
    {
        public int X { get; set; }
        public int Y { get; set; }
        public bool ButtonPressed { get; set; }
    }

    #endregion
}
