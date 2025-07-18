// =====================================================================
// DAAD# - Implementación Fase 6: Sistema Avanzado y Utilidades
// =====================================================================

using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Extensions.Logging;

namespace DaadModern.Core
{
    /// <summary>
    /// Implementación de CondActs de Fase 6: Sistema avanzado, multimedia y utilidades especializadas
    /// </summary>
    public partial class Phase6CondactsImplementer
    {
        private readonly ILogger<Phase6CondactsImplementer> _logger;
        private readonly GameState _gameState;
        private readonly IMultimediaManager _multimediaManager;
        private readonly ISystemManager _systemManager;

        public Phase6CondactsImplementer(ILogger<Phase6CondactsImplementer> logger, 
                                       GameState gameState,
                                       IMultimediaManager multimediaManager,
                                       ISystemManager systemManager)
        {
            _logger = logger;
            _gameState = gameState;
            _multimediaManager = multimediaManager;
            _systemManager = systemManager;
        }

        #region CondActs Multimedia

        /// <summary>
        /// BEEP - Sonido básico del sistema
        /// ID: 84 - Emite un pitido o sonido básico
        /// </summary>
        public bool ExecuteBeep()
        {
            _logger.LogInformation("Ejecutando BEEP - Sonido básico");
            
            try
            {
                _multimediaManager.PlaySystemBeep();
                _logger.LogInformation("BEEP: Sonido básico emitido");
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "BEEP: Error emitiendo sonido básico");
                return false;
            }
        }

        /// <summary>
        /// PICTURE - Mostrar imagen
        /// ID: 83 - Muestra una imagen en la pantalla
        /// </summary>
        public bool ExecutePicture(int imageId)
        {
            _logger.LogInformation($"Ejecutando PICTURE - Mostrar imagen {imageId}");
            
            var resolvedImageId = ResolveValue(imageId);
            
            try
            {
                _multimediaManager.ShowPicture(resolvedImageId);
                _gameState.CurrentPictureId = resolvedImageId;
                
                _logger.LogInformation($"PICTURE: Imagen {resolvedImageId} mostrada");
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"PICTURE: Error mostrando imagen {resolvedImageId}");
                return false;
            }
        }

        /// <summary>
        /// SFX - Efecto de sonido
        /// ID: 82 - Reproduce un efecto de sonido específico
        /// </summary>
        public bool ExecuteSfx(int soundId)
        {
            _logger.LogInformation($"Ejecutando SFX - Efecto de sonido {soundId}");
            
            var resolvedSoundId = ResolveValue(soundId);
            
            try
            {
                _multimediaManager.PlaySoundEffect(resolvedSoundId);
                _logger.LogInformation($"SFX: Efecto de sonido {resolvedSoundId} reproducido");
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"SFX: Error reproduciendo sonido {resolvedSoundId}");
                return false;
            }
        }

        #endregion

        #region CondActs del Sistema

        /// <summary>
        /// MODE - Cambiar modo de pantalla
        /// ID: 81 - Cambia el modo de pantalla (texto/gráfico)
        /// </summary>
        public bool ExecuteMode(int modeId)
        {
            _logger.LogInformation($"Ejecutando MODE - Cambiar modo a {modeId}");
            
            var resolvedModeId = ResolveValue(modeId);
            var mode = MapDisplayMode(resolvedModeId);
            
            try
            {
                _systemManager.SetDisplayMode(mode);
                _gameState.CurrentDisplayMode = resolvedModeId;
                
                _logger.LogInformation($"MODE: Modo cambiado a {mode} (ID: {resolvedModeId})");
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"MODE: Error cambiando modo a {resolvedModeId}");
                return false;
            }
        }

        /// <summary>
        /// RESET - Reiniciar objetos al estado inicial
        /// ID: 80 - Reinicia todos los objetos a sus posiciones iniciales
        /// </summary>
        public bool ExecuteReset()
        {
            _logger.LogInformation("Ejecutando RESET - Reiniciar objetos");
            
            try
            {
                _gameState.ResetObjectsToInitialState();
                _logger.LogInformation("RESET: Objetos reiniciados al estado inicial");
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "RESET: Error reiniciando objetos");
                return false;
            }
        }

        /// <summary>
        /// EXIT - Salir al sistema operativo
        /// ID: 79 - Termina el juego y sale al sistema
        /// </summary>
        public bool ExecuteExit()
        {
            _logger.LogInformation("Ejecutando EXIT - Salir al sistema");
            
            try
            {
                _gameState.GameExiting = true;
                _systemManager.ExitToSystem();
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "EXIT: Error saliendo al sistema");
                return false;
            }
        }

        #endregion

        #region CondActs de Control Avanzado

        /// <summary>
        /// ANYKEY - Esperar cualquier tecla
        /// ID: 78 - Pausa hasta que se presione una tecla
        /// </summary>
        public bool ExecuteAnykey()
        {
            _logger.LogInformation("Ejecutando ANYKEY - Esperar tecla");
            
            try
            {
                _systemManager.WaitForAnyKey();
                _logger.LogInformation("ANYKEY: Tecla presionada, continuando");
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "ANYKEY: Error esperando tecla");
                return false;
            }
        }

        /// <summary>
        /// PAUSE - Pausa en frames
        /// ID: 77 - Pausa durante un número específico de frames
        /// </summary>
        public bool ExecutePause(int frames)
        {
            _logger.LogInformation($"Ejecutando PAUSE - Pausar {frames} frames");
            
            var resolvedFrames = ResolveValue(frames);
            
            try
            {
                var milliseconds = FramesToMilliseconds(resolvedFrames);
                _systemManager.PauseForMilliseconds(milliseconds);
                
                _logger.LogInformation($"PAUSE: Pausa de {resolvedFrames} frames ({milliseconds}ms) completada");
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"PAUSE: Error pausando {resolvedFrames} frames");
                return false;
            }
        }

        /// <summary>
        /// TIME - Configurar timeout
        /// ID: 76 - Establece un timeout para entrada del jugador
        /// </summary>
        public bool ExecuteTime(int timeoutValue, int timeoutAction)
        {
            _logger.LogInformation($"Ejecutando TIME - Timeout {timeoutValue}, acción {timeoutAction}");
            
            var resolvedTimeout = ResolveValue(timeoutValue);
            var resolvedAction = ResolveValue(timeoutAction);
            
            try
            {
                _gameState.InputTimeout = resolvedTimeout;
                _gameState.TimeoutAction = resolvedAction;
                
                _logger.LogInformation($"TIME: Timeout configurado a {resolvedTimeout}, acción {resolvedAction}");
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"TIME: Error configurando timeout");
                return false;
            }
        }

        #endregion

        #region CondActs de Entrada/Salida

        /// <summary>
        /// INPUT - Configurar entrada
        /// ID: 75 - Configura el modo de entrada del jugador
        /// </summary>
        public bool ExecuteInput(int inputMode, int bufferSize)
        {
            _logger.LogInformation($"Ejecutando INPUT - Modo {inputMode}, buffer {bufferSize}");
            
            var resolvedMode = ResolveValue(inputMode);
            var resolvedBuffer = ResolveValue(bufferSize);
            
            try
            {
                var mode = MapInputMode(resolvedMode);
                _systemManager.ConfigureInput(mode, resolvedBuffer);
                
                _gameState.InputMode = resolvedMode;
                _gameState.InputBufferSize = resolvedBuffer;
                
                _logger.LogInformation($"INPUT: Entrada configurada - modo {mode}, buffer {resolvedBuffer}");
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"INPUT: Error configurando entrada");
                return false;
            }
        }

        /// <summary>
        /// PRINTAT - Imprimir en posición específica
        /// ID: 74 - Imprime texto en coordenadas específicas
        /// </summary>
        public bool ExecutePrintat(int x, int y, int messageId)
        {
            _logger.LogInformation($"Ejecutando PRINTAT - Posición ({x},{y}), mensaje {messageId}");
            
            var resolvedX = ResolveValue(x);
            var resolvedY = ResolveValue(y);
            var resolvedMessageId = ResolveValue(messageId);
            
            try
            {
                var message = _gameState.GetMessage(resolvedMessageId);
                _systemManager.PrintAt(resolvedX, resolvedY, message);
                
                _logger.LogInformation($"PRINTAT: Mensaje impreso en ({resolvedX},{resolvedY})");
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"PRINTAT: Error imprimiendo en posición");
                return false;
            }
        }

        #endregion

        #region CondActs de Objetos Avanzados

        /// <summary>
        /// WHATO - Buscar objeto por sustantivo
        /// ID: 73 - Busca y establece el objeto correspondiente al sustantivo actual
        /// </summary>
        public bool ExecuteWhato()
        {
            _logger.LogInformation("Ejecutando WHATO - Buscar objeto por sustantivo");
            
            try
            {
                var currentNoun = _gameState.CurrentNoun;
                var foundObject = FindObjectByNoun(currentNoun);
                
                if (foundObject != -1)
                {
                    _gameState.CurrentObject = foundObject;
                    _logger.LogInformation($"WHATO: Objeto {foundObject} encontrado para sustantivo {currentNoun}");
                    return true;
                }
                else
                {
                    _logger.LogDebug($"WHATO: No se encontró objeto para sustantivo {currentNoun}");
                    return false;
                }
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "WHATO: Error buscando objeto por sustantivo");
                return false;
            }
        }

        /// <summary>
        /// SETCO - Establecer objeto actual
        /// ID: 72 - Establece el objeto actual sin búsqueda
        /// </summary>
        public bool ExecuteSetco(int objectId)
        {
            _logger.LogInformation($"Ejecutando SETCO - Establecer objeto actual {objectId}");
            
            var resolvedObjectId = ResolveValue(objectId);
            
            try
            {
                if (_gameState.Objects.ContainsKey(resolvedObjectId))
                {
                    _gameState.CurrentObject = resolvedObjectId;
                    _logger.LogInformation($"SETCO: Objeto actual establecido a {resolvedObjectId}");
                    return true;
                }
                else
                {
                    _logger.LogWarning($"SETCO: Objeto {resolvedObjectId} no existe");
                    return false;
                }
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"SETCO: Error estableciendo objeto actual");
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

        private DisplayMode MapDisplayMode(int modeId)
        {
            return modeId switch
            {
                0 => DisplayMode.Text,
                1 => DisplayMode.Graphics,
                2 => DisplayMode.Mixed,
                _ => DisplayMode.Text
            };
        }

        private InputMode MapInputMode(int modeId)
        {
            return modeId switch
            {
                0 => InputMode.Normal,
                1 => InputMode.SingleKey,
                2 => InputMode.NoEcho,
                _ => InputMode.Normal
            };
        }

        private int FramesToMilliseconds(int frames)
        {
            // Asumiendo 50 FPS (PAL) = 20ms por frame
            return frames * 20;
        }

        private int FindObjectByNoun(int nounId)
        {
            foreach (var obj in _gameState.Objects.Values)
            {
                if (obj.Nouns.Contains(nounId))
                {
                    return obj.Id;
                }
            }
            return -1; // No encontrado
        }

        /// <summary>
        /// Obtiene información de CondActs de Fase 6 para el transpilador
        /// </summary>
        public static Dictionary<string, CondactInfo> GetPhase6Condacts()
        {
            return new Dictionary<string, CondactInfo>
            {
                // Multimedia
                ["beep"] = new(CondactType.Action, "BEEP", 0, "Sonido básico del sistema"),
                ["picture"] = new(CondactType.Action, "PICTURE", 1, "Mostrar imagen"),
                ["sfx"] = new(CondactType.Action, "SFX", 1, "Efecto de sonido"),
                
                // Sistema
                ["mode"] = new(CondactType.Action, "MODE", 1, "Cambiar modo de pantalla"),
                ["reset"] = new(CondactType.Action, "RESET", 0, "Reiniciar objetos"),
                ["exit"] = new(CondactType.Action, "EXIT", 0, "Salir al sistema"),
                
                // Control Avanzado
                ["anykey"] = new(CondactType.Action, "ANYKEY", 0, "Esperar cualquier tecla"),
                ["pause"] = new(CondactType.Action, "PAUSE", 1, "Pausa en frames"),
                ["time"] = new(CondactType.Action, "TIME", 2, "Configurar timeout"),
                
                // Entrada/Salida
                ["input"] = new(CondactType.Action, "INPUT", 2, "Configurar entrada"),
                ["printat"] = new(CondactType.Action, "PRINTAT", 3, "Imprimir en posición"),
                
                // Objetos Avanzados
                ["whato"] = new(CondactType.Action, "WHATO", 0, "Buscar objeto por sustantivo"),
                ["setco"] = new(CondactType.Action, "SETCO", 1, "Establecer objeto actual")
            };
        }

        #endregion
    }

    #region Interfaces y Tipos de Apoyo

    /// <summary>
    /// Interfaz para gestión multimedia
    /// </summary>
    public interface IMultimediaManager
    {
        void PlaySystemBeep();
        void ShowPicture(int imageId);
        void PlaySoundEffect(int soundId);
    }

    /// <summary>
    /// Interfaz para gestión del sistema
    /// </summary>
    public interface ISystemManager
    {
        void SetDisplayMode(DisplayMode mode);
        void ExitToSystem();
        void WaitForAnyKey();
        void PauseForMilliseconds(int milliseconds);
        void ConfigureInput(InputMode mode, int bufferSize);
        void PrintAt(int x, int y, string message);
    }

    /// <summary>
    /// Modos de pantalla disponibles
    /// </summary>
    public enum DisplayMode
    {
        Text = 0,
        Graphics = 1,
        Mixed = 2
    }

    /// <summary>
    /// Modos de entrada disponibles
    /// </summary>
    public enum InputMode
    {
        Normal = 0,
        SingleKey = 1,
        NoEcho = 2
    }

    #endregion
}
