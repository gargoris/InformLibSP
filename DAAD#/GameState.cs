// =====================================================================
// DAAD# - Estado del Juego y Estructuras de Datos
// =====================================================================

using System;
using System.Collections.Generic;
using System.Linq;

namespace DaadModern.Core
{
    /// <summary>
    /// Estado completo del juego DAAD
    /// </summary>
    public class GameState
    {
        #region Propiedades Básicas

        /// <summary>
        /// Localización actual del jugador
        /// </summary>
        public int CurrentLocation { get; set; } = 0;

        /// <summary>
        /// Objeto actual seleccionado
        /// </summary>
        public int CurrentObject { get; set; } = 255;

        /// <summary>
        /// Proceso actual ejecutándose
        /// </summary>
        public int CurrentProcess { get; set; } = 0;

        /// <summary>
        /// Línea actual del proceso
        /// </summary>
        public int CurrentLine { get; set; } = 0;

        /// <summary>
        /// Entrada actual del jugador
        /// </summary>
        public string? CurrentInput { get; set; }

        /// <summary>
        /// Indica si el juego debe terminar
        /// </summary>
        public bool ExitGame { get; set; } = false;

        /// <summary>
        /// Indica si la ejecución del proceso actual fue exitosa
        /// </summary>
        public bool ProcessExecutionSuccess { get; set; } = true;

        /// <summary>
        /// Flags del juego (estado de variables)
        /// </summary>
        public Dictionary<string, int> Flags { get; set; } = new Dictionary<string, int>();

        /// <summary>
        /// Objetos del juego
        /// </summary>
        public Dictionary<int, GameObject> Objects { get; set; } = new Dictionary<int, GameObject>();

        /// <summary>
        /// Localizaciones (ubicaciones de objetos)
        /// </summary>
        public Dictionary<int, int> ObjectLocations { get; set; } = new Dictionary<int, int>();

        /// <summary>
        /// Descripciones de localizaciones
        /// </summary>
        public Dictionary<int, GameLocation> Locations { get; set; } = new Dictionary<int, GameLocation>();

        /// <summary>
        /// Vocabulario de verbos
        /// </summary>
        public Dictionary<string, int> Verbs { get; set; } = new Dictionary<string, int>();

        /// <summary>
        /// Vocabulario de sustantivos
        /// </summary>
        public Dictionary<string, int> Nouns { get; set; } = new Dictionary<string, int>();

        /// <summary>
        /// Vocabulario de adjetivos
        /// </summary>
        public Dictionary<string, int> Adjectives { get; set; } = new Dictionary<string, int>();

        /// <summary>
        /// Vocabulario de preposiciones
        /// </summary>
        public Dictionary<string, int> Prepositions { get; set; } = new Dictionary<string, int>();

        /// <summary>
        /// Mensajes del sistema
        /// </summary>
        public Dictionary<int, string> Messages { get; set; } = new Dictionary<int, string>();

        /// <summary>
        /// Sinónimos de palabras
        /// </summary>
        public Dictionary<int, List<int>> Synonyms { get; set; } = new Dictionary<int, List<int>>();

        /// <summary>
        /// Procesos del juego
        /// </summary>
        public List<GameProcess> Processes { get; set; } = new List<GameProcess>();

        /// <summary>
        /// Palabras analizadas por el parser
        /// </summary>
        public List<ParsedWord> ParsedWords { get; set; } = new List<ParsedWord>();

        #endregion

        #region Propiedades Gráficas y Display (Fase 5)

        /// <summary>
        /// ID de la imagen de fondo actual
        /// </summary>
        public int CurrentBackgroundImage { get; set; } = 0;

        /// <summary>
        /// Color de papel (fondo de texto) actual
        /// </summary>
        public int CurrentPaperColor { get; set; } = 0;

        /// <summary>
        /// Color de tinta (texto) actual
        /// </summary>
        public int CurrentInkColor { get; set; } = 7; // Blanco por defecto

        /// <summary>
        /// Color de borde actual
        /// </summary>
        public int CurrentBorderColor { get; set; } = 0;

        /// <summary>
        /// Conjunto de caracteres actual
        /// </summary>
        public int CurrentCharset { get; set; } = 0;

        /// <summary>
        /// Indica si el texto está centrado
        /// </summary>
        public bool TextCentered { get; set; } = false;

        #endregion

        #region Propiedades del Sistema (Fase 6)

        /// <summary>
        /// Modo de pantalla actual
        /// </summary>
        public int CurrentDisplayMode { get; set; } = 0;

        /// <summary>
        /// ID de la imagen actual mostrada
        /// </summary>
        public int CurrentPictureId { get; set; } = 0;

        /// <summary>
        /// Indica si el juego está saliendo al sistema
        /// </summary>
        public bool GameExiting { get; set; } = false;

        /// <summary>
        /// Timeout para entrada del jugador (en centésimas de segundo)
        /// </summary>
        public int InputTimeout { get; set; } = 0;

        /// <summary>
        /// Acción a ejecutar cuando expire el timeout
        /// </summary>
        public int TimeoutAction { get; set; } = 0;

        /// <summary>
        /// Modo de entrada actual
        /// </summary>
        public int InputMode { get; set; } = 0;

        /// <summary>
        /// Tamaño del buffer de entrada
        /// </summary>
        public int InputBufferSize { get; set; } = 80;

        #endregion

        #region Propiedades Fase 7 - Sistema Avanzado

        /// <summary>
        /// Última tecla presionada
        /// </summary>
        public char LastKeyPressed { get; set; } = '\0';

        /// <summary>
        /// Buffer de entrada de texto
        /// </summary>
        public string InputBuffer { get; set; } = string.Empty;

        /// <summary>
        /// ID de pantalla actual
        /// </summary>
        public int CurrentScreen { get; set; } = 0;

        /// <summary>
        /// Último comando ejecutado por el jugador
        /// </summary>
        public string LastCommand { get; set; } = string.Empty;

        /// <summary>
        /// Posición X guardada del cursor
        /// </summary>
        public int SavedCursorX { get; set; } = 0;

        /// <summary>
        /// Posición Y guardada del cursor
        /// </summary>
        public int SavedCursorY { get; set; } = 0;

        /// <summary>
        /// Estado guardado en RAM
        /// </summary>
        private Dictionary<string, object>? _ramSavedState;

        #endregion

        #region Propiedades Parser Avanzado (Fase 2)

        // ...existing code...

        #endregion

        #region Métodos de Inicialización

        /// <summary>
        /// Inicializa el estado del juego con valores predeterminados
        /// </summary>
        public void Initialize()
        {
            InitializeFlags();
            InitializeObjects();
            InitializeLocations();
            InitializeVocabulary();
            InitializeMessages();
            InitializeProcesses();
        }

        private void InitializeFlags()
        {
            // Inicializar flags principales (0-255)
            for (int i = 0; i <= 255; i++)
            {
                Flags[i.ToString()] = 0;
            }

            // Flags especiales del parser
            Flags["51"] = 255; // Verbo
            Flags["52"] = 255; // Sustantivo 1
            Flags["53"] = 255; // Adjetivo 1
            Flags["54"] = 255; // Adverbio
            Flags["55"] = 255; // Preposición
            Flags["56"] = 255; // Sustantivo 2
            Flags["57"] = 255; // Adjetivo 2
        }

        private void InitializeObjects()
        {
            // Objetos básicos de ejemplo
            Objects[0] = new GameObject 
            { 
                Id = 0, 
                Name = "lámpara", 
                Description = "Una lámpara antigua",
                Weight = 5,
                Attributes = new HashSet<int> { AttributeIds.Light }
            };

            Objects[1] = new GameObject 
            { 
                Id = 1, 
                Name = "llave", 
                Description = "Una pequeña llave de bronce",
                Weight = 1
            };

            Objects[2] = new GameObject 
            { 
                Id = 2, 
                Name = "caja", 
                Description = "Una caja de madera",
                Weight = 10,
                Attributes = new HashSet<int> { AttributeIds.Container }
            };

            // Inicializar ubicaciones (todos los objetos empiezan en localización 1)
            ObjectLocations[0] = 1; // lámpara en localización 1
            ObjectLocations[1] = 1; // llave en localización 1
            ObjectLocations[2] = 2; // caja en localización 2
        }

        private void InitializeLocations()
        {
            Locations[0] = new GameLocation 
            { 
                Name = "Inicio", 
                Description = "Punto de inicio del juego" 
            };

            Locations[1] = new GameLocation 
            { 
                Name = "Habitación", 
                Description = "Una pequeña habitación con una puerta al norte."
            };

            Locations[2] = new GameLocation 
            { 
                Name = "Pasillo", 
                Description = "Un largo pasillo con puertas a ambos lados."
            };
        }

        private void InitializeVocabulary()
        {
            // Verbos básicos
            Verbs["coger"] = 1;
            Verbs["tomar"] = 1;
            Verbs["soltar"] = 2;
            Verbs["dejar"] = 2;
            Verbs["ir"] = 3;
            Verbs["caminar"] = 3;
            Verbs["examinar"] = 4;
            Verbs["mirar"] = 4;
            Verbs["abrir"] = 5;
            Verbs["cerrar"] = 6;
            Verbs["usar"] = 7;
            Verbs["salir"] = 8;
            Verbs["quit"] = 8;

            // Sustantivos básicos
            Nouns["lampara"] = 0;
            Nouns["llave"] = 1;
            Nouns["caja"] = 2;
            Nouns["puerta"] = 3;
            Nouns["norte"] = 10;
            Nouns["sur"] = 11;
            Nouns["este"] = 12;
            Nouns["oeste"] = 13;

            // Adjetivos básicos
            Adjectives["pequeña"] = 1;
            Adjectives["grande"] = 2;
            Adjectives["vieja"] = 3;
            Adjectives["nueva"] = 4;

            // Preposiciones básicas
            Prepositions["en"] = 1;
            Prepositions["con"] = 2;
            Prepositions["de"] = 3;
            Prepositions["hacia"] = 4;
        }

        private void InitializeMessages()
        {
            Messages[0] = "Bienvenido al juego.";
            Messages[1] = "No entiendo esa palabra.";
            Messages[2] = "No puedes hacer eso.";
            Messages[3] = "No hay nada especial aquí.";
            Messages[4] = "Está demasiado oscuro para ver.";
            Messages[5] = "No tienes eso.";
            Messages[6] = "Ya lo tienes.";
            Messages[7] = "No puedes coger eso.";
            Messages[8] = "Tus manos están llenas.";
            Messages[9] = "¡Hecho!";
        }

        private void InitializeProcesses()
        {
            // Proceso 0: Proceso principal de entrada
            var mainProcess = new GameProcess { Id = 0 };
            Processes.Add(mainProcess);

            // Proceso 1: Proceso de respuestas
            var responseProcess = new GameProcess { Id = 1 };
            Processes.Add(responseProcess);
        }

        #endregion

        #region Métodos de Utilidad

        /// <summary>
        /// Obtiene un flag por su ID
        /// </summary>
        public object GetFlag(int flagId)
        {
            var key = flagId.ToString();
            return Flags.ContainsKey(key) ? Flags[key] : 0;
        }

        /// <summary>
        /// Establece un flag por su ID
        /// </summary>
        public void SetFlag(int flagId, object value)
        {
            Flags[flagId.ToString()] = Convert.ToInt32(value);
        }

        /// <summary>
        /// Obtiene la ubicación de un objeto
        /// </summary>
        public int GetObjectLocation(int objectId)
        {
            return ObjectLocations.ContainsKey(objectId) ? ObjectLocations[objectId] : -1;
        }

        /// <summary>
        /// Mueve un objeto a una nueva ubicación
        /// </summary>
        public void MoveObject(int objectId, int newLocation)
        {
            ObjectLocations[objectId] = newLocation;
        }

        /// <summary>
        /// Verifica si un objeto está presente en la localización actual
        /// </summary>
        public bool IsObjectPresent(int objectId)
        {
            var objectLocation = GetObjectLocation(objectId);
            return objectLocation == CurrentLocation || objectLocation == 254; // 254 = llevado por el jugador
        }

        /// <summary>
        /// Verifica si el jugador lleva un objeto
        /// </summary>
        public bool IsObjectCarried(int objectId)
        {
            return GetObjectLocation(objectId) == 254; // 254 = llevado por el jugador
        }

        /// <summary>
        /// Obtiene todos los objetos en una localización
        /// </summary>
        public List<int> GetObjectsAtLocation(int locationId)
        {
            var objects = new List<int>();
            
            foreach (var kvp in ObjectLocations)
            {
                if (kvp.Value == locationId)
                {
                    objects.Add(kvp.Key);
                }
            }
            
            return objects;
        }

        /// <summary>
        /// Obtiene todos los objetos llevados por el jugador
        /// </summary>
        public List<int> GetCarriedObjects()
        {
            return GetObjectsAtLocation(254); // 254 = llevado por el jugador
        }

        /// <summary>
        /// Reinicia el estado del juego
        /// </summary>
        public void Reset()
        {
            CurrentLocation = 0;
            CurrentObject = 255;
            CurrentProcess = 0;
            CurrentLine = 0;
            CurrentInput = null;
            ExitGame = false;
            ParsedWords.Clear();
            
            Initialize();
        }

        /// <summary>
        /// Guarda el estado actual en RAM
        /// </summary>
        public void SaveStateToRam()
        {
            _ramSavedState = new Dictionary<string, object>
            {
                ["CurrentLocation"] = CurrentLocation,
                ["CurrentObject"] = CurrentObject,
                ["Flags"] = Flags.ToDictionary(f => f.Key, f => (object)f.Value),
                ["ObjectLocations"] = ObjectLocations,
                ["GameTime"] = DateTime.Now
            };
        }

        /// <summary>
        /// Carga el estado desde RAM
        /// </summary>
        public bool LoadStateFromRam()
        {
            if (_ramSavedState == null)
                return false;

            try
            {
                CurrentLocation = (int)_ramSavedState["CurrentLocation"];
                CurrentObject = (int)_ramSavedState["CurrentObject"];
                
                var savedFlags = (Dictionary<string, object>)_ramSavedState["Flags"];
                foreach (var flag in savedFlags)
                {
                    Flags[flag.Key] = Convert.ToInt32(flag.Value);
                }

                var savedLocations = (Dictionary<int, int>)_ramSavedState["ObjectLocations"];
                foreach (var objLoc in savedLocations)
                {
                    ObjectLocations[objLoc.Key] = objLoc.Value;
                }

                return true;
            }
            catch
            {
                return false;
            }
        }

        /// <summary>
        /// Añade un sinónimo al diccionario
        /// </summary>
        public void AddSynonym(int wordId, int synonymId)
        {
            if (!Synonyms.ContainsKey(wordId))
            {
                Synonyms[wordId] = new List<int>();
            }
            
            if (!Synonyms[wordId].Contains(synonymId))
            {
                Synonyms[wordId].Add(synonymId);
            }
        }

        /// <summary>
        /// Obtiene una conexión desde una localización en una dirección
        /// </summary>
        public Connection? GetConnection(int fromLocation, int direction)
        {
            if (Locations.ContainsKey(fromLocation))
            {
                var location = Locations[fromLocation];
                if (location.Connections.ContainsKey(direction))
                {
                    return new Connection 
                    { 
                        FromLocation = fromLocation, 
                        ToLocation = location.Connections[direction], 
                        Direction = direction 
                    };
                }
            }
            return null;
        }

        #endregion
    }

    /// <summary>
    /// Representa una localización en el juego
    /// </summary>
    public class Location
    {
        public int Id { get; set; }
        public string Name { get; set; } = string.Empty;
        public string Description { get; set; } = string.Empty;
        public Dictionary<string, int> Exits { get; set; } = new();
    }
}
