// =====================================================================
// DAAD Moderno - Transpilador de Patrones Complejos
// Convierte patrones sofisticados a múltiples entradas DAAD clásicas
// =====================================================================

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace DaadModern.Transpiler
{
    // =====================================================================
    // TIPOS PARA PATRONES COMPLEJOS
    // =====================================================================
    
    /// <summary>
    /// Patrón complejo que puede expandirse a múltiples patrones simples
    /// </summary>
    public record ComplexPattern(
        string Template,                    // "[NPC], mata a [OBJETO] con [INSTRUMENTO]"
        List<PatternParameter> Parameters,  // Definiciones de los placeholders
        PatternOptions Options              // Opciones de generación
    );
    
    /// <summary>
    /// Parámetro en un patrón (placeholder)
    /// </summary>
    public record PatternParameter(
        string Name,                        // "NPC", "OBJETO", "INSTRUMENTO"
        ParameterType Type,                 // Tipo del parámetro
        bool IsOptional,                    // Si es opcional: "[NPC], ..." vs "mata a..."
        List<string> PossibleValues,        // Valores específicos si los hay
        PatternConstraints Constraints      // Restricciones adicionales
    );
    
    /// <summary>
    /// Tipos de parámetros en patrones
    /// </summary>
    public enum ParameterType
    {
        NPC,           // Personaje no jugador
        Object,        // Objeto del juego
        Location,      // Localización
        Direction,     // Dirección (norte, sur, etc.)
        Adjective,     // Adjetivo (brillante, grande)
        Verb,          // Verbo adicional
        Preposition,   // Preposición (con, en, de)
        Wildcard       // Cualquier palabra
    }
    
    /// <summary>
    /// Restricciones para parámetros
    /// </summary>
    public record PatternConstraints(
        bool MustBePresent = false,         // Objeto debe estar presente
        bool MustBeCarried = false,         // Objeto debe estar en inventario
        bool MustBeWearable = false,        // Objeto debe ser vestible
        List<string> ExcludeValues = null   // Valores a excluir
    );
    
    /// <summary>
    /// Opciones de generación de patrones
    /// </summary>
    public record PatternOptions(
        bool GenerateWithArticles = true,   // "mata AL ogro" vs "mata ogro"
        bool GenerateWithoutArticles = true,
        bool GenerateVariations = true,     // Generar variaciones de sinónimos
        int MaxCombinations = 50            // Límite de combinaciones generadas
    );
    
    // =====================================================================
    // GENERADOR DE PATRONES CLÁSICOS
    // =====================================================================
    
    /// <summary>
    /// Convierte patrones complejos DAAD Moderno a entradas DAAD clásicas
    /// </summary>
    public class PatternTranspiler
    {
        private readonly GameVocabulary _vocabulary;
        private readonly GameDatabase _gameDb;
        
        public PatternTranspiler(GameVocabulary vocabulary, GameDatabase gameDb)
        {
            _vocabulary = vocabulary;
            _gameDb = gameDb;
        }
        
        /// <summary>
        /// Transpila un patrón complejo a múltiples entradas DAAD clásicas
        /// </summary>
        public List<ClassicDaadEntry> TranspilePattern(ComplexPattern pattern, 
                                                      Condition condition, 
                                                      List<Action> actions)
        {
            var entries = new List<ClassicDaadEntry>();
            
            // 1. Extraer placeholders del template
            var placeholders = ExtractPlaceholders(pattern.Template);
            
            // 2. Generar todas las combinaciones posibles
            var combinations = GenerateCombinations(placeholders, pattern.Parameters, pattern.Options);
            
            // 3. Para cada combinación, crear una entrada DAAD clásica
            foreach (var combination in combinations.Take(pattern.Options.MaxCombinations))
            {
                var entry = CreateClassicEntry(combination, condition, actions);
                entries.Add(entry);
            }
            
            return entries;
        }
        
        /// <summary>
        /// Extrae placeholders de un template: "[NPC], mata a [OBJETO]" -> ["NPC", "OBJETO"]
        /// </summary>
        private List<string> ExtractPlaceholders(string template)
        {
            var regex = new Regex(@"\[(\w+)\]");
            return regex.Matches(template)
                       .Cast<Match>()
                       .Select(m => m.Groups[1].Value)
                       .ToList();
        }
        
        /// <summary>
        /// Genera todas las combinaciones posibles de valores para los placeholders
        /// </summary>
        private List<PatternCombination> GenerateCombinations(List<string> placeholders, 
                                                              List<PatternParameter> parameters,
                                                              PatternOptions options)
        {
            var combinations = new List<PatternCombination>();
            var parameterMap = parameters.ToDictionary(p => p.Name);
            
            // Generar combinaciones recursivamente
            GenerateCombinationsRecursive(
                placeholders, 
                parameterMap, 
                options,
                new Dictionary<string, string>(), 
                0, 
                combinations);
            
            return combinations;
        }
        
        private void GenerateCombinationsRecursive(List<string> placeholders,
                                                  Dictionary<string, PatternParameter> parameterMap,
                                                  PatternOptions options,
                                                  Dictionary<string, string> currentValues,
                                                  int index,
                                                  List<PatternCombination> results)
        {
            if (index >= placeholders.Count)
            {
                // Generar variaciones de artículos si es necesario
                if (options.GenerateWithArticles)
                    results.Add(new PatternCombination(new Dictionary<string, string>(currentValues), true));
                if (options.GenerateWithoutArticles)
                    results.Add(new PatternCombination(new Dictionary<string, string>(currentValues), false));
                return;
            }
            
            var placeholder = placeholders[index];
            var parameter = parameterMap.GetValueOrDefault(placeholder);
            
            if (parameter == null)
            {
                // Placeholder sin definición - saltar
                GenerateCombinationsRecursive(placeholders, parameterMap, options, currentValues, index + 1, results);
                return;
            }
            
            // Obtener valores posibles para este parámetro
            var possibleValues = GetPossibleValues(parameter);
            
            foreach (var value in possibleValues)
            {
                currentValues[placeholder] = value;
                GenerateCombinationsRecursive(placeholders, parameterMap, options, currentValues, index + 1, results);
                currentValues.Remove(placeholder);
            }
            
            // Si es opcional, también generar sin este parámetro
            if (parameter.IsOptional)
            {
                GenerateCombinationsRecursive(placeholders, parameterMap, options, currentValues, index + 1, results);
            }
        }
        
        /// <summary>
        /// Obtiene valores posibles para un parámetro basándose en su tipo
        /// </summary>
        private List<string> GetPossibleValues(PatternParameter parameter)
        {
            if (parameter.PossibleValues?.Any() == true)
                return parameter.PossibleValues;
            
            return parameter.Type switch
            {
                ParameterType.NPC => _gameDb.GetAllNPCs().Select(npc => npc.Name).ToList(),
                ParameterType.Object => GetObjectValues(parameter.Constraints),
                ParameterType.Location => _gameDb.GetAllLocations().Select(loc => loc.Name).ToList(),
                ParameterType.Direction => _vocabulary.GetDirections(),
                ParameterType.Adjective => _vocabulary.GetAdjectives(),
                ParameterType.Verb => _vocabulary.GetVerbs(),
                ParameterType.Preposition => _vocabulary.GetPrepositions(),
                ParameterType.Wildcard => new List<string> { "*" }, // Comodín
                _ => new List<string>()
            };
        }
        
        private List<string> GetObjectValues(PatternConstraints constraints)
        {
            var objects = _gameDb.GetAllObjects();
            
            if (constraints.MustBeCarried)
                objects = objects.Where(o => o.IsCarriable).ToList();
            
            if (constraints.MustBeWearable)
                objects = objects.Where(o => o.IsWearable).ToList();
            
            if (constraints.ExcludeValues?.Any() == true)
                objects = objects.Where(o => !constraints.ExcludeValues.Contains(o.Name)).ToList();
            
            return objects.Select(o => o.Name).ToList();
        }
        
        /// <summary>
        /// Crea una entrada DAAD clásica a partir de una combinación de valores
        /// </summary>
        private ClassicDaadEntry CreateClassicEntry(PatternCombination combination, 
                                                   Condition condition, 
                                                   List<Action> actions)
        {
            var entry = new ClassicDaadEntry();
            
            // Generar los condacts de la condición
            if (condition != null)
                entry.Condacts.AddRange(TranspileCondition(condition, combination.Values));
            
            // Generar los condacts de las acciones
            entry.Condacts.AddRange(TranspileActions(actions, combination.Values));
            
            // Generar el patrón de entrada (verbo + sustantivo)
            var pattern = GenerateClassicPattern(combination);
            entry.Verb = pattern.Verb;
            entry.Noun = pattern.Noun;
            
            return entry;
        }
        
        /// <summary>
        /// Genera el patrón de entrada clásico (verbo/sustantivo) a partir de la combinación
        /// </summary>
        private (int Verb, int Noun) GenerateClassicPattern(PatternCombination combination)
        {
            // Esta es una simplificación - en la implementación real,
            // necesitarías extraer verbo y sustantivo del patrón completo
            // y mapearlos a números del vocabulario DAAD clásico
            
            var verb = _vocabulary.GetVerbNumber("mata"); // Verbo por defecto
            var noun = 0; // Sin sustantivo por defecto
            
            // Buscar objeto principal en la combinación
            if (combination.Values.ContainsKey("OBJETO"))
            {
                noun = _vocabulary.GetNounNumber(combination.Values["OBJETO"]);
            }
            
            return (verb, noun);
        }
        
        private List<Condact> TranspileCondition(Condition condition, Dictionary<string, string> values)
        {
            // Implementación de transpilación de condiciones
            // substituyendo placeholders por valores reales
            return new List<Condact>();
        }
        
        private List<Condact> TranspileActions(List<Action> actions, Dictionary<string, string> values)
        {
            // Implementación de transpilación de acciones
            // substituyendo placeholders por valores reales
            return new List<Condact>();
        }
    }
    
    // =====================================================================
    // DEFINICIÓN DE PATRONES EN DAAD MODERNO
    // =====================================================================
    
    /// <summary>
    /// Extensión de la gramática para soportar patrones complejos
    /// </summary>
    public static class ComplexPatternExamples
    {
        public static List<ComplexPattern> GetExamplePatterns()
        {
            return new List<ComplexPattern>
            {
                // "Fred, mata al ogro con la espada brillante"
                new ComplexPattern(
                    Template: "[NPC], mata a [OBJETO] con [INSTRUMENTO]",
                    Parameters: new List<PatternParameter>
                    {
                        new("NPC", ParameterType.NPC, IsOptional: true, 
                            PossibleValues: new List<string>(), 
                            new PatternConstraints()),
                        new("OBJETO", ParameterType.Object, IsOptional: false,
                            PossibleValues: new List<string>(),
                            new PatternConstraints(MustBePresent: true)),
                        new("INSTRUMENTO", ParameterType.Object, IsOptional: false,
                            PossibleValues: new List<string>(),
                            new PatternConstraints(MustBeCarried: true))
                    },
                    Options: new PatternOptions(MaxCombinations: 20)
                ),
                
                // "habla con [NPC] del [TEMA]"
                new ComplexPattern(
                    Template: "habla con [NPC] del [TEMA]",
                    Parameters: new List<PatternParameter>
                    {
                        new("NPC", ParameterType.NPC, IsOptional: false,
                            PossibleValues: new List<string>(),
                            new PatternConstraints(MustBePresent: true)),
                        new("TEMA", ParameterType.Object, IsOptional: true,
                            PossibleValues: new List<string> { "tesoro", "aventura", "peligro" },
                            new PatternConstraints())
                    },
                    Options: new PatternOptions(MaxCombinations: 15)
                ),
                
                // Patrón de uso con preposiciones múltiples
                new ComplexPattern(
                    Template: "usa [OBJETO] en [LUGAR] para [PROPOSITO]",
                    Parameters: new List<PatternParameter>
                    {
                        new("OBJETO", ParameterType.Object, IsOptional: false,
                            PossibleValues: new List<string>(),
                            new PatternConstraints(MustBeCarried: true)),
                        new("LUGAR", ParameterType.Location, IsOptional: false,
                            PossibleValues: new List<string>(),
                            new PatternConstraints()),
                        new("PROPOSITO", ParameterType.Wildcard, IsOptional: true,
                            PossibleValues: new List<string> { "abrir", "activar", "reparar" },
                            new PatternConstraints())
                    },
                    Options: new PatternOptions(MaxCombinations: 25)
                )
            };
        }
    }
    
    // =====================================================================
    // EJEMPLO DE TRANSPILACIÓN
    // =====================================================================
    
    /// <summary>
    /// Ejemplo de cómo se vería el código DAAD Moderno transpilado
    /// </summary>
    public static class TranspilationExample
    {
        public static string GetDaadModernCode()
        {
            return @"
respuestas {
    // Patrón complejo que se expande automáticamente
    al patron_complejo {
        template: ""[NPC], mata a [OBJETO] con [INSTRUMENTO]""
        parametros: {
            NPC: { tipo: npc, opcional: verdadero }
            OBJETO: { tipo: objeto, presente: verdadero }
            INSTRUMENTO: { tipo: objeto, llevado: verdadero }
        }
        opciones: {
            max_combinaciones: 20
            generar_con_articulos: verdadero
        }
    } {
        requiere: presente(OBJETO) y llevado(INSTRUMENTO)
        hacer: {
            si presente(NPC) {
                mensaje(""Le dices a "" + NPC + "" que ataque."")
                npc_accion(NPC, ""atacar"", OBJETO)
            } sino {
                mensaje(""Atacas a "" + OBJETO + "" con "" + INSTRUMENTO)
                atacar(OBJETO, INSTRUMENTO)
            }
        }
    }
}";
        }
        
        public static string GetTranspiledClassicCode()
        {
            return @"
/PRO
; Entrada generada 1: Fred mata ogro con espada
> MATA OGRO
PRESENT 50    ; ogro
CARRIED 51    ; espada
MESSAGE ""Atacas al ogro con la espada""
; ... acciones ...
DONE

; Entrada generada 2: mata ogro con espada (sin NPC)  
> MATA OGRO
PRESENT 50    ; ogro
CARRIED 51    ; espada  
MESSAGE ""Atacas al ogro con la espada""
; ... acciones ...
DONE

; Entrada generada 3: Fred mata troll con hacha
> MATA TROLL
PRESENT 52    ; troll
CARRIED 53    ; hacha
MESSAGE ""Le dices a Fred que ataque""
; ... acciones ...
DONE

; ... más entradas generadas automáticamente ...
";
        }
    }
    
    // =====================================================================
    // TIPOS DE APOYO
    // =====================================================================
    
    public record PatternCombination(Dictionary<string, string> Values, bool WithArticles);
    
    public class ClassicDaadEntry
    {
        public int Verb { get; set; }
        public int Noun { get; set; }
        public List<Condact> Condacts { get; set; } = new();
    }
    
    public record Condact(string Name, List<int> Parameters);
    
    // Interfaces que implementarías
    public interface IGameDatabase
    {
        List<GameObject> GetAllObjects();
        List<NPC> GetAllNPCs();
        List<Location> GetAllLocations();
    }
    
    public interface IGameVocabulary  
    {
        int GetVerbNumber(string verb);
        int GetNounNumber(string noun);
        List<string> GetDirections();
        List<string> GetAdjectives();
        List<string> GetVerbs();
        List<string> GetPrepositions();
    }
    
    // Clases dummy para el ejemplo
    public class GameVocabulary : IGameVocabulary
    {
        public int GetVerbNumber(string verb) => 1;
        public int GetNounNumber(string noun) => 50;
        public List<string> GetDirections() => new() { "norte", "sur", "este", "oeste" };
        public List<string> GetAdjectives() => new() { "brillante", "grande", "pequeño" };
        public List<string> GetVerbs() => new() { "mata", "habla", "coge" };
        public List<string> GetPrepositions() => new() { "con", "en", "de", "para" };
    }
    
    public class GameDatabase : IGameDatabase
    {
        public List<GameObject> GetAllObjects() => new();
        public List<NPC> GetAllNPCs() => new();
        public List<Location> GetAllLocations() => new();
    }
}