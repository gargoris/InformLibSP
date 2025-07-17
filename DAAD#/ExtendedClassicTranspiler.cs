// =====================================================================
// DAAD Moderno - Extensiones Críticas del Transpilador
// Implementa condactos faltantes para paridad completa con DAAD clásico
// =====================================================================

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using DaadModern.Parser;
using Microsoft.Extensions.Logging;

namespace DaadModern.Transpiler
{
    /// <summary>
    /// Transpilador extendido que incluye todos los condactos DAAD clásicos
    /// </summary>
    public class ExtendedClassicTranspiler : IExtendedTranspiler
    {
        private readonly ILogger<ExtendedClassicTranspiler> _logger;
        private readonly TranspilerContext _context;
        
        public ExtendedClassicTranspiler(ILogger<ExtendedClassicTranspiler> logger)
        {
            _logger = logger;
            _context = new TranspilerContext();
        }

        #region Condactos Críticos Faltantes

        /// <summary>
        /// Transpila condición ZERO (flag/counter == 0)
        /// </summary>
        public List<Condact> TranspileZeroCondition(string flagOrCounter)
        {
            var flagNumber = _context.GetFlagNumber(flagOrCounter);
            return new List<Condact>
            {
                new() { Name = "ZERO", Parameters = [flagNumber] }
            };
        }

        /// <summary>
        /// Transpila condición NOTZERO (flag/counter != 0)
        /// </summary>
        public List<Condact> TranspileNotZeroCondition(string flagOrCounter)
        {
            var flagNumber = _context.GetFlagNumber(flagOrCounter);
            return new List<Condact>
            {
                new() { Name = "NOTZERO", Parameters = [flagNumber] }
            };
        }

        /// <summary>
        /// Transpila condición WORN (objeto vestido)
        /// </summary>
        public List<Condact> TranspileWornCondition(string objectId)
        {
            var objectNumber = _context.GetObjectNumber(objectId);
            return new List<Condact>
            {
                new() { Name = "WORN", Parameters = [objectNumber] }
            };
        }

        /// <summary>
        /// Transpila condición NOTWORN (objeto no vestido)
        /// </summary>
        public List<Condact> TranspileNotWornCondition(string objectId)
        {
            var objectNumber = _context.GetObjectNumber(objectId);
            return new List<Condact>
            {
                new() { Name = "NOTWORN", Parameters = [objectNumber] }
            };
        }

        /// <summary>
        /// Transpila acción WEAR (vestir objeto)
        /// </summary>
        public List<Condact> TranspileWearAction(string objectId)
        {
            var objectNumber = _context.GetObjectNumber(objectId);
            return new List<Condact>
            {
                new() { Name = "WEAR", Parameters = [objectNumber] }
            };
        }

        /// <summary>
        /// Transpila acción REMOVE (quitar objeto vestido)
        /// </summary>
        public List<Condact> TranspileRemoveAction(string objectId)
        {
            var objectNumber = _context.GetObjectNumber(objectId);
            return new List<Condact>
            {
                new() { Name = "REMOVE", Parameters = [objectNumber] }
            };
        }

        /// <summary>
        /// Transpila acción RESTART (reiniciar juego)
        /// </summary>
        public List<Condact> TranspileRestartAction()
        {
            return new List<Condact>
            {
                new() { Name = "RESTART", Parameters = [] }
            };
        }

        /// <summary>
        /// Transpila acción QUIT (salir del juego)
        /// </summary>
        public List<Condact> TranspileQuitAction()
        {
            return new List<Condact>
            {
                new() { Name = "QUIT", Parameters = [] }
            };
        }

        /// <summary>
        /// Transpila condición CHANCE (probabilística)
        /// </summary>
        public List<Condact> TranspileChanceCondition(int percentage)
        {
            return new List<Condact>
            {
                new() { Name = "CHANCE", Parameters = [percentage] }
            };
        }

        /// <summary>
        /// Transpila condición ISAT (verificar ubicación de objeto)
        /// </summary>
        public List<Condact> TranspileIsAtCondition(string objectId, string locationId)
        {
            var objectNumber = _context.GetObjectNumber(objectId);
            var locationNumber = _context.GetLocationNumber(locationId);
            return new List<Condact>
            {
                new() { Name = "ISAT", Parameters = [objectNumber, locationNumber] }
            };
        }

        #endregion

        #region Condactos de Copia (Familia COPY)

        /// <summary>
        /// COPYOO - Copiar ubicación de objeto a objeto
        /// </summary>
        public List<Condact> TranspileCopyObjectToObject(string sourceObj, string destObj)
        {
            var sourceNum = _context.GetObjectNumber(sourceObj);
            var destNum = _context.GetObjectNumber(destObj);
            return new List<Condact>
            {
                new() { Name = "COPYOO", Parameters = [sourceNum, destNum] }
            };
        }

        /// <summary>
        /// COPYOF - Copiar ubicación de objeto a flag
        /// </summary>
        public List<Condact> TranspileCopyObjectToFlag(string objectId, string flagId)
        {
            var objectNum = _context.GetObjectNumber(objectId);
            var flagNum = _context.GetFlagNumber(flagId);
            return new List<Condact>
            {
                new() { Name = "COPYOF", Parameters = [objectNum, flagNum] }
            };
        }

        /// <summary>
        /// COPYFO - Copiar flag a ubicación de objeto
        /// </summary>
        public List<Condact> TranspileCopyFlagToObject(string flagId, string objectId)
        {
            var flagNum = _context.GetFlagNumber(flagId);
            var objectNum = _context.GetObjectNumber(objectId);
            return new List<Condact>
            {
                new() { Name = "COPYFO", Parameters = [flagNum, objectNum] }
            };
        }

        /// <summary>
        /// COPYFF - Copiar flag a flag
        /// </summary>
        public List<Condact> TranspileCopyFlagToFlag(string sourceFlagId, string destFlagId)
        {
            var sourceNum = _context.GetFlagNumber(sourceFlagId);
            var destNum = _context.GetFlagNumber(destFlagId);
            return new List<Condact>
            {
                new() { Name = "COPYFF", Parameters = [sourceNum, destNum] }
            };
        }

        #endregion

        #region Soporte de Condiciones OR y NOT

        /// <summary>
        /// Transpila condiciones OR creando múltiples entradas DAAD
        /// </summary>
        public List<ClassicEntry> TranspileOrCondition(CompoundCondition orCondition, ResponseDefinition response)
        {
            var entries = new List<ClassicEntry>();
            
            // Extraer todas las condiciones OR
            var orConditions = FlattenOrConditions(orCondition);
            
            foreach (var condition in orConditions)
            {
                var entry = new ClassicEntry
                {
                    Verb = ExtractVerb(response.Patterns.First()),
                    Noun = ExtractNoun(response.Patterns.First()),
                    Condacts = new List<Condact>()
                };
                
                // Transpiler la condición individual
                entry.Condacts.AddRange(TranspileCondition(condition));
                
                // Añadir las acciones
                entry.Condacts.AddRange(TranspileActions(response.ActionBlock));
                
                entries.Add(entry);
            }
            
            _logger.LogInformation($"Condición OR expandida a {entries.Count} entradas DAAD");
            return entries;
        }

        /// <summary>
        /// Transpila condiciones NOT convirtiéndolas a condactos opuestos
        /// </summary>
        public List<Condact> TranspileNotCondition(NotCondition notCondition)
        {
            return notCondition.Inner switch
            {
                SimpleCondition simple when simple.Function == "present" =>
                    new List<Condact> { new() { Name = "ABSENT", Parameters = [_context.GetObjectNumber(simple.Args[0].ToString()!)] } },
                
                SimpleCondition simple when simple.Function == "carried" =>
                    new List<Condact> { new() { Name = "NOTCARR", Parameters = [_context.GetObjectNumber(simple.Args[0].ToString()!)] } },
                
                SimpleCondition simple when simple.Function == "worn" =>
                    TranspileNotWornCondition(simple.Args[0].ToString()!),
                
                SimpleCondition simple when simple.Function == "zero" =>
                    TranspileNotZeroCondition(simple.Args[0].ToString()!),
                
                SimpleCondition simple when simple.Function == "at" =>
                    new List<Condact> { new() { Name = "NOTAT", Parameters = [_context.GetLocationNumber(simple.Args[0].ToString()!)] } },
                
                _ => throw new TranspilerException($"Condición NOT no soportada: {notCondition.Inner.GetType().Name}")
            };
        }

        #endregion

        #region Estructuras If-Then-Else Avanzadas

        /// <summary>
        /// Transpila bloques if-then-else a saltos condicionales DAAD
        /// </summary>
        public List<Condact> TranspileIfThenElse(ConditionalAction ifAction)
        {
            var condacts = new List<Condact>();
            var labelCounter = _context.GetNextLabelNumber();
            
            // Transpiler condición (invertida para salto)
            var invertedCondition = InvertCondition(ifAction.Condition);
            condacts.AddRange(TranspileCondition(invertedCondition));
            
            // Salto condicional al ELSE si la condición falla
            var elseLabel = $"ELSE_{labelCounter}";
            var endLabel = $"END_{labelCounter}";
            
            condacts.Add(new Condact { Name = "SKIP", Parameters = [GetSkipDistance(ifAction.ThenActions)] });
            
            // Acciones THEN
            condacts.AddRange(TranspileActions(new BlockAction(ifAction.ThenActions)));
            
            // Si hay ELSE, saltar al final
            if (ifAction.ElseActions?.Any() == true)
            {
                condacts.Add(new Condact { Name = "SKIP", Parameters = [GetSkipDistance(ifAction.ElseActions)] });
                
                // Acciones ELSE
                condacts.AddRange(TranspileActions(new BlockAction(ifAction.ElseActions)));
            }
            
            return condacts;
        }

        private Condition InvertCondition(Condition condition)
        {
            return condition switch
            {
                NotCondition not => not.Inner,
                SimpleCondition simple => new NotCondition(simple),
                CompoundCondition compound when compound.Operator == "and" =>
                    new CompoundCondition(InvertCondition(compound.Left), "or", InvertCondition(compound.Right)),
                CompoundCondition compound when compound.Operator == "or" =>
                    new CompoundCondition(InvertCondition(compound.Left), "and", InvertCondition(compound.Right)),
                _ => new NotCondition(condition)
            };
        }

        #endregion

        #region Condactos Multimedia y Externos

        /// <summary>
        /// Transpila acción PICTURE (mostrar imagen)
        /// </summary>
        public List<Condact> TranspilePictureAction(int pictureNumber)
        {
            return new List<Condact>
            {
                new() { Name = "PICTURE", Parameters = [pictureNumber] }
            };
        }

        /// <summary>
        /// Transpila acción BEEP (sonido)
        /// </summary>
        public List<Condact> TranspileBeepAction(int? duration = null)
        {
            var parameters = duration.HasValue ? new List<int> { duration.Value } : new List<int>();
            return new List<Condact>
            {
                new() { Name = "BEEP", Parameters = parameters }
            };
        }

        /// <summary>
        /// Transpila acción EXTERN (código externo)
        /// </summary>
        public List<Condact> TranspileExternAction(int value1, int value2)
        {
            return new List<Condact>
            {
                new() { Name = "EXTERN", Parameters = [value1, value2] }
            };
        }

        #endregion

        #region Sistema PSI (Process State Indicator)

        /// <summary>
        /// Transpila configuración de timeout PSI
        /// </summary>
        public List<Condact> TranspileTimeoutConfiguration(TimeoutConfiguration config)
        {
            var condacts = new List<Condact>();
            
            // Flag 48: Duración del timeout
            if (config.Duration.HasValue)
            {
                condacts.Add(new Condact { Name = "LET", Parameters = [48, config.Duration.Value] });
            }
            
            // Flag 49: Flags de control
            if (config.ControlFlags.HasValue)
            {
                condacts.Add(new Condact { Name = "LET", Parameters = [49, config.ControlFlags.Value] });
            }
            
            return condacts;
        }

        /// <summary>
        /// Transpila llamada a proceso específico
        /// </summary>
        public List<Condact> TranspileProcessCall(int processNumber)
        {
            return new List<Condact>
            {
                new() { Name = "PROCESS", Parameters = [processNumber] }
            };
        }

        /// <summary>
        /// Transpila acción PAUSE (pausa temporal)
        /// </summary>
        public List<Condact> TranspilePauseAction(int duration)
        {
            return new List<Condact>
            {
                new() { Name = "PAUSE", Parameters = [duration] }
            };
        }

        #endregion

        #region Bucles DOALL Avanzados

        /// <summary>
        /// Transpila bucles DOALL con condiciones complejas
        /// </summary>
        public List<Condact> TranspileDoAllLoop(string objectPattern, List<Action> actions, Condition? condition = null)
        {
            var condacts = new List<Condact>();
            
            // Inicio del bucle DOALL
            var objectNumber = GetObjectPatternNumber(objectPattern);
            condacts.Add(new Condact { Name = "DOALL", Parameters = [objectNumber] });
            
            // Condición opcional dentro del bucle
            if (condition != null)
            {
                condacts.AddRange(TranspileCondition(condition));
            }
            
            // Acciones del bucle
            condacts.AddRange(TranspileActions(new BlockAction(actions)));
            
            // Fin del bucle
            condacts.Add(new Condact { Name = "UNDO", Parameters = [] });
            
            return condacts;
        }

        #endregion

        #region Métodos de Utilidad

        private List<Condition> FlattenOrConditions(Condition condition)
        {
            return condition switch
            {
                CompoundCondition compound when compound.Operator == "or" =>
                    FlattenOrConditions(compound.Left).Concat(FlattenOrConditions(compound.Right)).ToList(),
                _ => new List<Condition> { condition }
            };
        }

        private int ExtractVerb(CommandPattern pattern) => pattern switch
        {
            SimplePattern simple => _context.GetVerbFromPattern(simple.Text),
            _ => 0
        };

        private int ExtractNoun(CommandPattern pattern) => pattern switch
        {
            SimplePattern simple => _context.GetNounFromPattern(simple.Text),
            _ => 0
        };

        private int GetSkipDistance(List<Action> actions)
        {
            // Calcular cuántos condacts ocuparán las acciones
            return actions.Sum(action => EstimateCondactCount(action));
        }

        private int EstimateCondactCount(Action action) => action switch
        {
            SimpleAction _ => 1,
            BlockAction block => block.Actions.Sum(EstimateCondactCount),
            ConditionalAction conditional => 2 + EstimateCondactCount(new BlockAction(conditional.ThenActions)) +
                                           (conditional.ElseActions?.Sum(EstimateCondactCount) ?? 0),
            _ => 1
        };

        private int GetObjectPatternNumber(string pattern)
        {
            return pattern.ToLowerInvariant() switch
            {
                "here" => 0,      // Objetos en localización actual
                "carried" => 252, // Objetos llevados
                "worn" => 253,    // Objetos vestidos
                "all" => 254,     // Todos los objetos
                _ => _context.GetObjectNumber(pattern)
            };
        }

        #endregion
    }

    #region Clases de Soporte

    /// <summary>
    /// Contexto del transpilador con mapeos de identificadores
    /// </summary>
    public class TranspilerContext
    {
        private readonly Dictionary<string, int> _flagNumbers = new();
        private readonly Dictionary<string, int> _objectNumbers = new();
        private readonly Dictionary<string, int> _locationNumbers = new();
        private readonly Dictionary<string, int> _messageNumbers = new();
        private int _nextFlagNumber = 100;
        private int _nextObjectNumber = 1;
        private int _nextLocationNumber = 1;
        private int _nextMessageNumber = 1;
        private int _labelCounter = 1;

        public int GetFlagNumber(string flagId)
        {
            if (!_flagNumbers.TryGetValue(flagId, out var number))
            {
                number = _nextFlagNumber++;
                _flagNumbers[flagId] = number;
            }
            return number;
        }

        public int GetObjectNumber(string objectId)
        {
            if (!_objectNumbers.TryGetValue(objectId, out var number))
            {
                number = _nextObjectNumber++;
                _objectNumbers[objectId] = number;
            }
            return number;
        }

        public int GetLocationNumber(string locationId)
        {
            if (!_locationNumbers.TryGetValue(locationId, out var number))
            {
                number = _nextLocationNumber++;
                _locationNumbers[locationId] = number;
            }
            return number;
        }

        public int GetMessageNumber(string messageId)
        {
            if (!_messageNumbers.TryGetValue(messageId, out var number))
            {
                number = _nextMessageNumber++;
                _messageNumbers[messageId] = number;
            }
            return number;
        }

        public int GetNextLabelNumber() => _labelCounter++;

        public int GetVerbFromPattern(string pattern)
        {
            // Extraer verbo del patrón usando expresiones regulares o parsing
            // Implementación simplificada
            var words = pattern.Split(' ', StringSplitOptions.RemoveEmptyEntries);
            return words.Length > 0 ? GetVerbNumber(words[0]) : 0;
        }

        public int GetNounFromPattern(string pattern)
        {
            // Extraer sustantivo del patrón
            var words = pattern.Split(' ', StringSplitOptions.RemoveEmptyEntries);
            return words.Length > 1 ? GetNounNumber(words[1]) : 0;
        }

        private int GetVerbNumber(string verb) => verb.ToLowerInvariant() switch
        {
            "examinar" or "mirar" or "look" => 1,
            "coger" or "take" => 2,
            "soltar" or "drop" => 3,
            "ir" or "go" => 4,
            _ => 0
        };

        private int GetNounNumber(string noun) => 50; // Simplificado
    }

    /// <summary>
    /// Entrada DAAD clásica generada
    /// </summary>
    public class ClassicEntry
    {
        public int Verb { get; set; }
        public int Noun { get; set; }
        public List<Condact> Condacts { get; set; } = new();
    }

    /// <summary>
    /// Condact DAAD clásico
    /// </summary>
    public class Condact
    {
        public string Name { get; set; } = "";
        public List<int> Parameters { get; set; } = new();
    }

    /// <summary>
    /// Excepción específica del transpilador
    /// </summary>
    public class TranspilerException : Exception
    {
        public TranspilerException(string message) : base(message) { }
        public TranspilerException(string message, Exception innerException) : base(message, innerException) { }
    }

    #endregion
}