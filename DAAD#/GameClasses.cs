// =====================================================================
// DAAD# - Clases del Juego y Estructuras de Datos
// =====================================================================

using System;
using System.Collections.Generic;

namespace DaadModern.Core
{
    /// <summary>
    /// Representa un objeto del juego
    /// </summary>
    public class GameObject
    {
        public string Name { get; set; } = "";
        public string Description { get; set; } = "";
        public bool IsContainer { get; set; } = false;
        public bool IsWearable { get; set; } = false;
        public int Weight { get; set; } = 0;
        public int CurrentLocation { get; set; } = 0;
    }

    /// <summary>
    /// Representa una localización del juego
    /// </summary>
    public class GameLocation
    {
        public string Name { get; set; } = "";
        public string Description { get; set; } = "";
        public Dictionary<int, int> Connections { get; set; } = new Dictionary<int, int>();
        public List<int> Objects { get; set; } = new List<int>();
    }

    /// <summary>
    /// Representa una conexión entre localizaciones
    /// </summary>
    public class Connection
    {
        public int FromLocation { get; set; }
        public int ToLocation { get; set; }
        public int Direction { get; set; }
        public string DirectionName { get; set; } = "";
    }

    /// <summary>
    /// Representa un proceso del juego
    /// </summary>
    public class GameProcess
    {
        public int Id { get; set; }
        public string Name { get; set; } = "";
        public List<string> Commands { get; set; } = new List<string>();
        public bool IsActive { get; set; } = true;
    }

    /// <summary>
    /// Palabra analizada por el parser
    /// </summary>
    public class ParsedWord
    {
        public string Text { get; set; } = "";
        public int Type { get; set; } = 0;
        public int Id { get; set; } = 0;
    }

    /// <summary>
    /// Estado del mouse
    /// </summary>
    public class MouseState
    {
        public int X { get; set; } = 0;
        public int Y { get; set; } = 0;
        public bool LeftButtonPressed { get; set; } = false;
        public bool RightButtonPressed { get; set; } = false;
        public bool MiddleButtonPressed { get; set; } = false;
    }

    /// <summary>
    /// Interfaz para gestión de entrada
    /// </summary>
    public interface IInputManager
    {
        bool HasKeyPressed();
        char? GetKey();
        bool WaitForKeypress();
        string? GetInput();
        void ClearInput();
    }

    /// <summary>
    /// Interfaz para gestión de sistema extendida
    /// </summary>
    public interface IExtendedSystemManager
    {
        bool SaveState(string filename, Dictionary<string, object> state);
        Dictionary<string, object>? LoadState(string filename);
        void DisplayGraphics(int graphicsId);
        MouseState GetMouseState();
        void Redo();
        void MoveObject(int objectId, int newLocation);
    }
}
