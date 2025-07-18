// =====================================================================
// DAAD# - Implementación Específica de CondActs Críticos
// =====================================================================

using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using Microsoft.Extensions.Logging;

namespace DaadModern.Core
{
    /// <summary>
    /// Implementaciones específicas de los CondActs críticos más importantes
    /// </summary>
    public partial class CriticalCondactsImplementer
    {
        private readonly ILogger<CriticalCondactsImplementer> _logger;
        private readonly Dictionary<string, object> _gameFlags;
        private readonly Dictionary<int, int> _objectLocations;
        private readonly GameState _gameState;

        public CriticalCondactsImplementer(ILogger<CriticalCondactsImplementer> logger, GameState gameState)
        {
            _logger = logger;
            _gameState = gameState;
            _gameFlags = gameState.Flags;
            _objectLocations = gameState.ObjectLocations;
        }

        #region CondActs Críticos - Nivel Imprescindible

        /// <summary>
        /// QUIT - Salir del juego con confirmación
        /// ID: 127 - Crítico para finalización del juego
        /// </summary>
        public bool ExecuteQuit()
        {
            _logger.LogInformation("Ejecutando QUIT - Solicitud de salir del juego");
            
            Console.WriteLine("\n¿Estás seguro de que quieres salir? (S/N)");
            var response = Console.ReadLine()?.ToUpper();
            
            if (response == "S" || response == "SI" || response == "Y" || response == "YES")
            {
                Console.WriteLine("\n¡Gracias por jugar!");
                _gameState.ExitGame = true;
                return true;
            }
            
            Console.WriteLine("\nContinuando el juego...");
            return true;
        }

        /// <summary>
        /// PARSE - Analizar entrada del jugador
        /// ID: 126 - Crítico para procesamiento de comandos
        /// </summary>
        public bool ExecuteParse()
        {
            _logger.LogInformation("Ejecutando PARSE - Analizando entrada del jugador");
            
            // Analizar la entrada actual del jugador
            var input = _gameState.CurrentInput?.Trim().ToLower();
            if (string.IsNullOrEmpty(input))
            {
                return false;
            }

            // Dividir en palabras
            var words = input.Split(' ', StringSplitOptions.RemoveEmptyEntries);
            
            // Limpiar palabras parseadas previas
            _gameState.ParsedWords.Clear();
            
            // Procesar cada palabra
            foreach (var word in words)
            {
                var wordInfo = AnalyzeWord(word);
                _gameState.ParsedWords.Add(wordInfo);
            }

            // Establecer flags del parser
            SetParserFlags();
            
            return true;
        }

        /// <summary>
        /// PROCESS - Llamar a sub-proceso
        /// ID: 125 - Crítico para control de flujo
        /// </summary>
        public bool ExecuteProcess(int processNumber)
        {
            _logger.LogInformation($"Ejecutando PROCESS {processNumber}");
            
            if (processNumber < 0 || processNumber >= _gameState.Processes.Count)
            {
                _logger.LogWarning($"Número de proceso inválido: {processNumber}");
                return false;
            }

            // Guardar estado actual
            var previousProcess = _gameState.CurrentProcess;
            var previousLine = _gameState.CurrentLine;
            
            try
            {
                // Ejecutar el sub-proceso
                _gameState.CurrentProcess = processNumber;
                _gameState.CurrentLine = 0;
                
                var process = _gameState.Processes[processNumber];
                var result = ExecuteProcess(process);
                
                return result;
            }
            finally
            {
                // Restaurar estado
                _gameState.CurrentProcess = previousProcess;
                _gameState.CurrentLine = previousLine;
            }
        }

        /// <summary>
        /// DOALL - Ejecutar para todos los objetos que cumplen condición
        /// ID: 124 - Crítico para operaciones masivas
        /// </summary>
        public bool ExecuteDoall(int locationId)
        {
            _logger.LogInformation($"Ejecutando DOALL en localización {locationId}");
            
            var objectsAtLocation = GetObjectsAtLocation(locationId);
            var processedObjects = new List<int>();
            
            foreach (var objectId in objectsAtLocation)
            {
                // Establecer objeto actual
                _gameState.CurrentObject = objectId;
                
                // Ejecutar las siguientes acciones para este objeto
                // (El parser DAAD original continúa con las siguientes líneas)
                var success = ExecuteNextCondactsForCurrentObject();
                
                if (success)
                {
                    processedObjects.Add(objectId);
                }
            }
            
            _logger.LogInformation($"DOALL procesó {processedObjects.Count} objetos");
            return processedObjects.Count > 0;
        }

        /// <summary>
        /// SYSMESS - Mostrar mensaje del sistema
        /// ID: 123 - Crítico para comunicación con jugador
        /// </summary>
        public bool ExecuteSysmess(int messageId)
        {
            _logger.LogInformation($"Ejecutando SYSMESS {messageId}");
            
            var systemMessages = GetSystemMessages();
            
            if (messageId >= 0 && messageId < systemMessages.Count)
            {
                var message = systemMessages[messageId];
                Console.Write(message);
                return true;
            }
            
            _logger.LogWarning($"ID de mensaje de sistema inválido: {messageId}");
            return false;
        }

        /// <summary>
        /// EXTERN - Ejecutar código externo
        /// ID: 122 - Crítico para extensibilidad
        /// </summary>
        public bool ExecuteExtern(int externId)
        {
            _logger.LogInformation($"Ejecutando EXTERN {externId}");
            
            // Buscar rutina externa registrada
            if (_gameState.ExternalRoutines.ContainsKey(externId))
            {
                var routine = _gameState.ExternalRoutines[externId];
                return routine.Invoke(_gameState);
            }
            
            _logger.LogWarning($"Rutina externa no encontrada: {externId}");
            return false;
        }

        #endregion

        #region CondActs de Objetos y Atributos

        /// <summary>
        /// HASAT - Verificar si objeto tiene atributo
        /// ID: 121 - Importante para lógica de objetos
        /// </summary>
        public bool CheckHasat(int objectId, int attributeId)
        {
            _logger.LogDebug($"Verificando HASAT objeto {objectId} atributo {attributeId}");
            
            if (!_gameState.Objects.ContainsKey(objectId))
            {
                return false;
            }
            
            var obj = _gameState.Objects[objectId];
            return obj.Attributes.Contains(attributeId);
        }

        /// <summary>
        /// HASNAT - Verificar si objeto NO tiene atributo
        /// ID: 120 - Importante para lógica de objetos
        /// </summary>
        public bool CheckHasnat(int objectId, int attributeId)
        {
            return !CheckHasat(objectId, attributeId);
        }

        /// <summary>
        /// PUTIN - Meter objeto en contenedor
        /// ID: 119 - Importante para manipulación de objetos
        /// </summary>
        public bool ExecutePutin(int objectId, int containerId)
        {
            _logger.LogInformation($"Ejecutando PUTIN objeto {objectId} en contenedor {containerId}");
            
            if (!CanPutObjectInContainer(objectId, containerId))
            {
                return false;
            }
            
            // Mover objeto al contenedor
            _objectLocations[objectId] = containerId;
            
            // Actualizar peso del contenedor si es necesario
            UpdateContainerWeight(containerId);
            
            return true;
        }

        /// <summary>
        /// TAKEOUT - Sacar objeto de contenedor
        /// ID: 118 - Importante para manipulación de objetos
        /// </summary>
        public bool ExecuteTakeout(int objectId, int containerId)
        {
            _logger.LogInformation($"Ejecutando TAKEOUT objeto {objectId} de contenedor {containerId}");
            
            if (_objectLocations.ContainsKey(objectId) && _objectLocations[objectId] == containerId)
            {
                // Mover objeto a la localización del contenedor
                var containerLocation = _objectLocations.ContainsKey(containerId) 
                    ? _objectLocations[containerId] 
                    : _gameState.CurrentLocation;
                    
                _objectLocations[objectId] = containerLocation;
                
                // Actualizar peso del contenedor
                UpdateContainerWeight(containerId);
                
                return true;
            }
            
            return false;
        }

        #endregion

        #region CondActs de Guardado/Carga

        /// <summary>
        /// SAVE - Guardar estado del juego
        /// ID: 117 - Crítico para persistencia
        /// </summary>
        public bool ExecuteSave(int slotId)
        {
            _logger.LogInformation($"Ejecutando SAVE en slot {slotId}");
            
            try
            {
                var saveData = SerializeGameState(_gameState);
                var filename = $"daad_save_{slotId}.dat";
                
                File.WriteAllText(filename, saveData);
                Console.WriteLine($"Partida guardada en {filename}");
                
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"Error guardando en slot {slotId}");
                Console.WriteLine("Error al guardar la partida.");
                return false;
            }
        }

        /// <summary>
        /// LOAD - Cargar estado del juego
        /// ID: 116 - Crítico para persistencia
        /// </summary>
        public bool ExecuteLoad(int slotId)
        {
            _logger.LogInformation($"Ejecutando LOAD desde slot {slotId}");
            
            try
            {
                var filename = $"daad_save_{slotId}.dat";
                
                if (!File.Exists(filename))
                {
                    Console.WriteLine("No hay partida guardada en ese slot.");
                    return false;
                }
                
                var saveData = File.ReadAllText(filename);
                DeserializeGameState(saveData, _gameState);
                
                Console.WriteLine("Partida cargada correctamente.");
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"Error cargando desde slot {slotId}");
                Console.WriteLine("Error al cargar la partida.");
                return false;
            }
        }

        #endregion

        #region Métodos de Apoyo

        private WordInfo AnalyzeWord(string word)
        {
            // Buscar en diccionario de verbos
            if (_gameState.Verbs.ContainsKey(word))
            {
                return new WordInfo(WordType.Verb, _gameState.Verbs[word], word);
            }
            
            // Buscar en diccionario de sustantivos
            if (_gameState.Nouns.ContainsKey(word))
            {
                return new WordInfo(WordType.Noun, _gameState.Nouns[word], word);
            }
            
            // Buscar en diccionario de adjetivos
            if (_gameState.Adjectives.ContainsKey(word))
            {
                return new WordInfo(WordType.Adjective, _gameState.Adjectives[word], word);
            }
            
            // Buscar en diccionario de adverbios
            if (_gameState.Adverbs.ContainsKey(word))
            {
                return new WordInfo(WordType.Adverb, _gameState.Adverbs[word], word);
            }
            
            // Buscar en diccionario de preposiciones
            if (_gameState.Prepositions.ContainsKey(word))
            {
                return new WordInfo(WordType.Preposition, _gameState.Prepositions[word], word);
            }
            
            // Palabra no reconocida
            return new WordInfo(WordType.Unknown, 255, word);
        }

        private void SetParserFlags()
        {
            // Establecer flags basados en las palabras parseadas
            var words = _gameState.ParsedWords;
            
            // Flag 51: Verbo
            var verb = words.Find(w => w.Type == WordType.Verb);
            _gameFlags["51"] = verb?.Id ?? 255;
            
            // Flag 52: Sustantivo 1
            var noun1 = words.Find(w => w.Type == WordType.Noun);
            _gameFlags["52"] = noun1?.Id ?? 255;
            
            // Flag 53: Adjetivo 1
            var adj1 = words.Find(w => w.Type == WordType.Adjective);
            _gameFlags["53"] = adj1?.Id ?? 255;
            
            // Flag 54: Adverbio
            var adverb = words.Find(w => w.Type == WordType.Adverb);
            _gameFlags["54"] = adverb?.Id ?? 255;
            
            // Flag 55: Preposición
            var prep = words.Find(w => w.Type == WordType.Preposition);
            _gameFlags["55"] = prep?.Id ?? 255;
            
            // Flag 56: Sustantivo 2
            var nouns = words.FindAll(w => w.Type == WordType.Noun);
            _gameFlags["56"] = nouns.Count > 1 ? nouns[1].Id : 255;
            
            // Flag 57: Adjetivo 2
            var adjectives = words.FindAll(w => w.Type == WordType.Adjective);
            _gameFlags["57"] = adjectives.Count > 1 ? adjectives[1].Id : 255;
        }

        private List<int> GetObjectsAtLocation(int locationId)
        {
            var objects = new List<int>();
            
            foreach (var kvp in _objectLocations)
            {
                if (kvp.Value == locationId)
                {
                    objects.Add(kvp.Key);
                }
            }
            
            return objects;
        }

        private bool ExecuteNextCondactsForCurrentObject()
        {
            // Implementación simplificada - en la realidad continuaría
            // ejecutando las siguientes líneas del proceso actual
            // TODO: Implementar lógica real de ejecución de CondActs
            return true;
        }

        private bool ExecuteProcess(Process process)
        {
            // Implementación simplificada de ejecución de proceso
            foreach (var line in process.Lines)
            {
                var result = ExecuteCondactLine(line);
                if (!result)
                {
                    return false;
                }
            }
            return true;
        }

        private static bool ExecuteCondactLine(CondactLine line)
        {
            // Implementación simplificada de ejecución de línea
            // TODO: Implementar parser real de CondActs desde CondactLine
            return !string.IsNullOrEmpty(line.Condact);
        }

        private static List<string> GetSystemMessages()
        {
            return new List<string>
            {
                "Está muy oscuro para ver nada.",
                "No puedes ir en esa dirección.",
                "No entiendo lo que quieres decir.",
                "No puedes hacer eso.",
                "No hay nada especial aquí.",
                "No tienes eso.",
                "Ya lo tienes.",
                "No puedes coger eso.",
                "Tus manos están llenas.",
                "Ya lo llevas puesto.",
                "No lo llevas puesto."
            };
        }

        private bool CanPutObjectInContainer(int objectId, int containerId)
        {
            // Verificar que ambos objetos existen
            if (!_gameState.Objects.ContainsKey(objectId) || !_gameState.Objects.ContainsKey(containerId))
            {
                return false;
            }
            
            // Verificar que el contenedor es realmente un contenedor
            var container = _gameState.Objects[containerId];
            if (!container.Attributes.Contains(AttributeIds.Container))
            {
                return false;
            }
            
            // Verificar capacidad del contenedor
            return CheckContainerCapacity(containerId, objectId);
        }

        private static bool CheckContainerCapacity(int containerId, int objectId)
        {
            // Implementación simplificada de verificación de capacidad
            // En una implementación real, verificaríamos peso, tamaño, etc.
            return containerId >= 0 && objectId >= 0;
        }

        private void UpdateContainerWeight(int containerId)
        {
            // Actualizar peso del contenedor basado en su contenido
            var totalWeight = 0;
            var objectsInContainer = GetObjectsAtLocation(containerId);
            
            foreach (var objId in objectsInContainer)
            {
                if (_gameState.Objects.ContainsKey(objId))
                {
                    totalWeight += _gameState.Objects[objId].Weight;
                }
            }
            
            if (_gameState.Objects.ContainsKey(containerId))
            {
                _gameState.Objects[containerId].CurrentWeight = totalWeight;
            }
        }

        private static string SerializeGameState(GameState state)
        {
            // Implementación simplificada de serialización
            // En una implementación real, usaríamos JSON o formato binario
            var sb = new StringBuilder();
            
            sb.AppendLine($"CurrentLocation={state.CurrentLocation}");
            sb.AppendLine($"CurrentObject={state.CurrentObject}");
            
            // Serializar flags
            foreach (var flag in state.Flags)
            {
                sb.AppendLine($"Flag:{flag.Key}={flag.Value}");
            }
            
            // Serializar ubicaciones de objetos
            foreach (var location in state.ObjectLocations)
            {
                sb.AppendLine($"Object:{location.Key}={location.Value}");
            }
            
            return sb.ToString();
        }

        private static void DeserializeGameState(string data, GameState state)
        {
            // Implementación simplificada de deserialización
            var lines = data.Split('\n', StringSplitOptions.RemoveEmptyEntries);
            
            foreach (var line in lines)
            {
                if (line.StartsWith("CurrentLocation="))
                {
                    state.CurrentLocation = int.Parse(line.Substring(16));
                }
                else if (line.StartsWith("CurrentObject="))
                {
                    state.CurrentObject = int.Parse(line.Substring(14));
                }
                else if (line.StartsWith("Flag:"))
                {
                    var parts = line.Substring(5).Split('=');
                    if (parts.Length == 2)
                    {
                        state.Flags[parts[0]] = int.Parse(parts[1]);
                    }
                }
                else if (line.StartsWith("Object:"))
                {
                    var parts = line.Substring(7).Split('=');
                    if (parts.Length == 2)
                    {
                        state.ObjectLocations[int.Parse(parts[0])] = int.Parse(parts[1]);
                    }
                }
            }
        }

        #endregion
    }

    #region Clases de Apoyo

    public record WordInfo(WordType Type, int Id, string Text);

    public enum WordType
    {
        Unknown,
        Verb,
        Noun,
        Adjective,
        Adverb,
        Preposition
    }

    public static class AttributeIds
    {
        public const int Container = 1;
        public const int Wearable = 2;
        public const int Edible = 3;
        public const int Drinkable = 4;
        public const int Light = 5;
        // ... más atributos según sea necesario
    }

    public class Process
    {
        public int Id { get; set; }
        public List<CondactLine> Lines { get; set; } = new();
    }

    public class CondactLine
    {
        public string Condact { get; set; } = string.Empty;
        public List<int> Parameters { get; set; } = new();
    }

    public class GameObject
    {
        public int Id { get; set; }
        public string Name { get; set; } = string.Empty;
        public string Description { get; set; } = string.Empty;
        public int Weight { get; set; }
        public int CurrentWeight { get; set; }
        public HashSet<int> Attributes { get; set; } = new();
    }

    #endregion
}
