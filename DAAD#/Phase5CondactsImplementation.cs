// =====================================================================
// DAAD# - Implementación Fase 5: Gráficos y Display
// =====================================================================

using System;
using System.Collections.Generic;
using Microsoft.Extensions.Logging;

namespace DaadModern.Core
{
    /// <summary>
    /// Implementación de CondActs de Fase 5: Características gráficas y de display
    /// </summary>
    public partial class Phase5CondactsImplementer
    {
        private readonly ILogger<Phase5CondactsImplementer> _logger;
        private readonly GameState _gameState;
        private readonly IDisplayManager _displayManager;

        public Phase5CondactsImplementer(ILogger<Phase5CondactsImplementer> logger, 
                                       GameState gameState, 
                                       IDisplayManager displayManager)
        {
            _logger = logger;
            _gameState = gameState;
            _displayManager = displayManager;
        }

        #region CondActs Gráficos y Display

        /// <summary>
        /// BACKG - Cambiar imagen de fondo
        /// ID: 90 - Establece la imagen de fondo de la pantalla
        /// </summary>
        public bool ExecuteBackg(int imageId)
        {
            _logger.LogInformation($"Ejecutando BACKG - Cambiar fondo a imagen {imageId}");
            
            var resolvedImageId = ResolveValue(imageId);
            
            try
            {
                _displayManager.SetBackgroundImage(resolvedImageId);
                _gameState.CurrentBackgroundImage = resolvedImageId;
                
                _logger.LogInformation($"BACKG: Fondo cambiado a imagen {resolvedImageId}");
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"BACKG: Error cambiando fondo a imagen {resolvedImageId}");
                return false;
            }
        }

        /// <summary>
        /// PAPER - Cambiar color del papel/fondo de texto
        /// ID: 89 - Establece el color de fondo del texto
        /// </summary>
        public bool ExecutePaper(int colorId)
        {
            _logger.LogInformation($"Ejecutando PAPER - Cambiar color de papel a {colorId}");
            
            var resolvedColorId = ResolveValue(colorId);
            var color = MapColorId(resolvedColorId);
            
            try
            {
                _displayManager.SetPaperColor(color);
                _gameState.CurrentPaperColor = resolvedColorId;
                
                _logger.LogInformation($"PAPER: Color de papel cambiado a {color} (ID: {resolvedColorId})");
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"PAPER: Error cambiando color de papel a {resolvedColorId}");
                return false;
            }
        }

        /// <summary>
        /// INK - Cambiar color de tinta/texto
        /// ID: 88 - Establece el color del texto
        /// </summary>
        public bool ExecuteInk(int colorId)
        {
            _logger.LogInformation($"Ejecutando INK - Cambiar color de tinta a {colorId}");
            
            var resolvedColorId = ResolveValue(colorId);
            var color = MapColorId(resolvedColorId);
            
            try
            {
                _displayManager.SetInkColor(color);
                _gameState.CurrentInkColor = resolvedColorId;
                
                _logger.LogInformation($"INK: Color de tinta cambiado a {color} (ID: {resolvedColorId})");
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"INK: Error cambiando color de tinta a {resolvedColorId}");
                return false;
            }
        }

        /// <summary>
        /// BORDER - Cambiar color del borde
        /// ID: 87 - Establece el color del borde de la pantalla
        /// </summary>
        public bool ExecuteBorder(int colorId)
        {
            _logger.LogInformation($"Ejecutando BORDER - Cambiar color de borde a {colorId}");
            
            var resolvedColorId = ResolveValue(colorId);
            var color = MapColorId(resolvedColorId);
            
            try
            {
                _displayManager.SetBorderColor(color);
                _gameState.CurrentBorderColor = resolvedColorId;
                
                _logger.LogInformation($"BORDER: Color de borde cambiado a {color} (ID: {resolvedColorId})");
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"BORDER: Error cambiando color de borde a {resolvedColorId}");
                return false;
            }
        }

        /// <summary>
        /// CHARSET - Cambiar conjunto de caracteres
        /// ID: 86 - Establece el conjunto de caracteres a usar
        /// </summary>
        public bool ExecuteCharset(int charsetId)
        {
            _logger.LogInformation($"Ejecutando CHARSET - Cambiar charset a {charsetId}");
            
            var resolvedCharsetId = ResolveValue(charsetId);
            
            try
            {
                var charset = GetCharacterSet(resolvedCharsetId);
                _displayManager.SetCharacterSet(charset);
                _gameState.CurrentCharset = resolvedCharsetId;
                
                _logger.LogInformation($"CHARSET: Conjunto de caracteres cambiado a {charset} (ID: {resolvedCharsetId})");
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"CHARSET: Error cambiando charset a {resolvedCharsetId}");
                return false;
            }
        }

        /// <summary>
        /// CENTER - Centrar texto
        /// ID: 85 - Activa/desactiva el centrado de texto
        /// </summary>
        public bool ExecuteCenter(int enabled)
        {
            _logger.LogInformation($"Ejecutando CENTER - Centrado: {(enabled != 0 ? "activado" : "desactivado")}");
            
            var resolvedEnabled = ResolveValue(enabled);
            var isCentered = resolvedEnabled != 0;
            
            try
            {
                _displayManager.SetTextCentering(isCentered);
                _gameState.TextCentered = isCentered;
                
                _logger.LogInformation($"CENTER: Centrado de texto {(isCentered ? "activado" : "desactivado")}");
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"CENTER: Error configurando centrado de texto");
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

        private DisplayColor MapColorId(int colorId)
        {
            // Mapeo de colores DAAD clásico
            return colorId switch
            {
                0 => DisplayColor.Black,
                1 => DisplayColor.Blue,
                2 => DisplayColor.Red,
                3 => DisplayColor.Magenta,
                4 => DisplayColor.Green,
                5 => DisplayColor.Cyan,
                6 => DisplayColor.Yellow,
                7 => DisplayColor.White,
                8 => DisplayColor.BrightBlack,
                9 => DisplayColor.BrightBlue,
                10 => DisplayColor.BrightRed,
                11 => DisplayColor.BrightMagenta,
                12 => DisplayColor.BrightGreen,
                13 => DisplayColor.BrightCyan,
                14 => DisplayColor.BrightYellow,
                15 => DisplayColor.BrightWhite,
                _ => DisplayColor.White // Por defecto
            };
        }

        private CharacterSet GetCharacterSet(int charsetId)
        {
            return charsetId switch
            {
                0 => CharacterSet.Standard,
                1 => CharacterSet.Extended,
                2 => CharacterSet.Spanish,
                3 => CharacterSet.French,
                4 => CharacterSet.German,
                5 => CharacterSet.Italian,
                _ => CharacterSet.Standard
            };
        }

        /// <summary>
        /// Obtiene información de CondActs de Fase 5 para el transpilador
        /// </summary>
        public static Dictionary<string, CondactInfo> GetPhase5Condacts()
        {
            return new Dictionary<string, CondactInfo>
            {
                ["backg"] = new(CondactType.Action, "BACKG", 1, "Cambiar imagen de fondo"),
                ["paper"] = new(CondactType.Action, "PAPER", 1, "Cambiar color de papel"),
                ["ink"] = new(CondactType.Action, "INK", 1, "Cambiar color de tinta"),
                ["border"] = new(CondactType.Action, "BORDER", 1, "Cambiar color de borde"),
                ["charset"] = new(CondactType.Action, "CHARSET", 1, "Cambiar conjunto de caracteres"),
                ["center"] = new(CondactType.Action, "CENTER", 1, "Centrar texto")
            };
        }

        #endregion
    }

    #region Interfaces y Tipos de Apoyo

    /// <summary>
    /// Interfaz para gestión de display
    /// </summary>
    public interface IDisplayManager
    {
        void SetBackgroundImage(int imageId);
        void SetPaperColor(DisplayColor color);
        void SetInkColor(DisplayColor color);
        void SetBorderColor(DisplayColor color);
        void SetCharacterSet(CharacterSet charset);
        void SetTextCentering(bool enabled);
    }

    /// <summary>
    /// Colores de display DAAD
    /// </summary>
    public enum DisplayColor
    {
        Black = 0,
        Blue = 1,
        Red = 2,
        Magenta = 3,
        Green = 4,
        Cyan = 5,
        Yellow = 6,
        White = 7,
        BrightBlack = 8,
        BrightBlue = 9,
        BrightRed = 10,
        BrightMagenta = 11,
        BrightGreen = 12,
        BrightCyan = 13,
        BrightYellow = 14,
        BrightWhite = 15
    }

    /// <summary>
    /// Conjuntos de caracteres disponibles
    /// </summary>
    public enum CharacterSet
    {
        Standard = 0,
        Extended = 1,
        Spanish = 2,
        French = 3,
        German = 4,
        Italian = 5
    }

    #endregion
}
