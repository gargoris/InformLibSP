// =====================================================================
// DAAD Moderno - Implementación Práctica de Sentencias Secuenciales
// Ejemplo funcional para demostrar el concepto
// =====================================================================

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Extensions.Logging;

namespace DaadModern.Sequential
{
    // =====================================================================
    // TIPOS PARA SENTENCIAS SECUENCIALES
    // =====================================================================

    /// <summary>
    /// Sentencia secuencial base
    /// </summary>
    public abstract record SequentialStatement
    {
        public abstract string GetDescription();
    }

    /// <summary>
    /// Acción simple en secuencia
    /// </summary>
    public record SimpleSequentialStatement(string ActionName, List<string> Parameters) : SequentialStatement
    {
        public override string GetDescription() => $"Action: {ActionName}({string.Join(", ", Parameters)})";
    }

    /// <summary>
    /// Cadena de sentencias con operador
    /// </summary>
    public record ChainedSequentialStatement(
        SequentialStatement First,
        SequenceOperator Operator,
        SequentialStatement Second
    ) : SequentialStatement
    {
        public override string GetDescription() => $"{First.GetDescription()} {Operator} {Second.GetDescription()}";
    }

    /// <summary>
    /// Sentencia condicional secuencial
    /// </summary>
    public record ConditionalSequentialStatement(
        string Condition,
        SequentialStatement ThenBranch,
        SequentialStatement? ElseBranch = null
    ) : SequentialStatement
    {
        public override string GetDescription() => $"If {Condition} then {ThenBranch.GetDescription()}" + 
                                                 (ElseBranch != null ? $" else {ElseBranch.GetDescription()}" : "");
    }

    /// <summary>
    /// Sentencia con delay temporal
    /// </summary>
    public record DelayedSequentialStatement(
        TimeSpan Delay,
        SequentialStatement Statement
    ) : SequentialStatement
    {
        public override string GetDescription() => $"After {Delay.TotalSeconds}s: {Statement.GetDescription()}";
    }

    /// <summary>
    /// Sentencia de loop
    /// </summary>
    public record LoopSequentialStatement(
        LoopType Type,
        string? Condition,
        int? Count,
        SequentialStatement Body
    ) : SequentialStatement
    {
        public override string GetDescription() => $"{Type} loop: {Body.GetDescription()}";
    }

    /// <summary>
    /// Sentencia con manejo de errores
    /// </summary>
    public record ErrorHandlingSequentialStatement(
        SequentialStatement TryStatement,
        SequentialStatement ErrorHandler
    ) : SequentialStatement
    {
        public override string GetDescription() => $"Try {TryStatement.GetDescription()} catch {ErrorHandler.GetDescription()}";
    }

    /// <summary>
    /// Operadores de secuencia
    /// </summary>
    public enum SequenceOperator
    {
        Then,       // Ejecutar inmediatamente después
        After,      // Ejecutar después de un delay
        Next,       // Siguiente en la secuencia
        Finally,    // Ejecutar al final (siempre)
        OnError     // Ejecutar solo si hay error
    }

    /// <summary>
    /// Tipos de loop
    /// </summary>
    public enum LoopType
    {
        While,      // Mientras condición sea true
        For,        // Para un rango/conteo
        Repeat      // Repetir N veces
    }

    // =====================================================================
    // TRANSPILADOR SECUENCIAL
    // =====================================================================

    /// <summary>
    /// Transpila sentencias secuenciales a código DAAD clásico
    /// </summary>
    public class SequentialTranspiler
    {
        private readonly ILogger<SequentialTranspiler> _logger;
        private int _nextProcessNumber = 10;
        private int _nextFlagNumber = 100;

        public SequentialTranspiler(ILogger<SequentialTranspiler> logger)
        {
            _logger = logger;
        }

        /// <summary>
        /// Transpila una sentencia secuencial a procesos DAAD clásicos
        /// </summary>
        public SequentialTranspileResult TranspileSequential(SequentialStatement statement)
        {
            var processes = new List<DaadProcess>();
            
            _logger.LogInformation("Iniciando transpilación secuencial");
            
            try
            {
                // Crear proceso principal
                var mainProcess = new DaadProcess { Number = _nextProcessNumber++, Condacts = new List<DaadCondact>() };
                var context = new SequentialContext { CurrentProcess = mainProcess };
                
                // Transpile the statement
                TranspileStatement(statement, processes, context);
                
                // Agregar proceso principal
                processes.Insert(0, mainProcess);
                
                // Generar código DAAD clásico
                var classicCode = GenerateClassicCode(processes);
                
                return new SequentialTranspileResult
                {
                    Success = true,
                    Processes = processes,
                    ClassicCode = classicCode,
                    ProcessesGenerated = processes.Count
                };
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error durante transpilación secuencial");
                return new SequentialTranspileResult
                {
                    Success = false,
                    ErrorMessage = ex.Message
                };
            }
        }

        /// <summary>
        /// Transpila una sentencia individual
        /// </summary>
        private void TranspileStatement(SequentialStatement statement, 
                                       List<DaadProcess> processes, 
                                       SequentialContext context)
        {
            switch (statement)
            {
                case SimpleSequentialStatement simple:
                    TranspileSimple(simple, context);
                    break;
                    
                case ChainedSequentialStatement chained:
                    TranspileChained(chained, processes, context);
                    break;
                    
                case ConditionalSequentialStatement conditional:
                    TranspileConditional(conditional, processes, context);
                    break;
                    
                case DelayedSequentialStatement delayed:
                    TranspileDelayed(delayed, processes, context);
                    break;
                    
                case LoopSequentialStatement loop:
                    TranspileLoop(loop, processes, context);
                    break;
                    
                case ErrorHandlingSequentialStatement errorHandling:
                    TranspileErrorHandling(errorHandling, processes, context);
                    break;
                    
                default:
                    throw new NotSupportedException($"Tipo de sentencia no soportado: {statement.GetType()}");
            }
        }

        /// <summary>
        /// Transpila una acción simple
        /// </summary>
        private void TranspileSimple(SimpleSequentialStatement simple, SequentialContext context)
        {
            var condact = new DaadCondact
            {
                Name = simple.ActionName.ToUpper(),
                Parameters = simple.Parameters.Select(p => ParseParameter(p)).ToList()
            };
            
            context.CurrentProcess.Condacts.Add(condact);
            _logger.LogDebug("Transpilada acción simple: {Action}", simple.ActionName);
        }

        /// <summary>
        /// Transpila una cadena de sentencias
        /// </summary>
        private void TranspileChained(ChainedSequentialStatement chained, 
                                     List<DaadProcess> processes, 
                                     SequentialContext context)
        {
            // Transpile first statement
            TranspileStatement(chained.First, processes, context);
            
            // Handle sequence operator
            switch (chained.Operator)
            {
                case SequenceOperator.Then:
                    // Ejecutar inmediatamente después
                    TranspileStatement(chained.Second, processes, context);
                    break;
                    
                case SequenceOperator.After:
                    // Crear proceso con delay
                    var delayedProcess = CreateDelayedProcess(chained.Second, processes, context);
                    context.CurrentProcess.Condacts.Add(new DaadCondact 
                    { 
                        Name = "PROCESS", 
                        Parameters = new List<int> { delayedProcess.Number } 
                    });
                    break;
                    
                case SequenceOperator.Next:
                    // Crear nuevo proceso para la siguiente parte
                    var nextProcess = new DaadProcess { Number = _nextProcessNumber++, Condacts = new List<DaadCondact>() };
                    processes.Add(nextProcess);
                    
                    // Llamar al siguiente proceso
                    context.CurrentProcess.Condacts.Add(new DaadCondact 
                    { 
                        Name = "PROCESS", 
                        Parameters = new List<int> { nextProcess.Number } 
                    });
                    
                    // Cambiar contexto
                    context.CurrentProcess = nextProcess;
                    TranspileStatement(chained.Second, processes, context);
                    break;
                    
                case SequenceOperator.Finally:
                    // Agregar a finally statements
                    context.FinallyStatements.Add(chained.Second);
                    break;
                    
                case SequenceOperator.OnError:
                    // Establecer error handler
                    context.ErrorHandler = chained.Second;
                    break;
            }
        }

        /// <summary>
        /// Transpila una sentencia condicional
        /// </summary>
        private void TranspileConditional(ConditionalSequentialStatement conditional, 
                                         List<DaadProcess> processes, 
                                         SequentialContext context)
        {
            // Crear procesos para las ramas
            var thenProcess = new DaadProcess { Number = _nextProcessNumber++, Condacts = new List<DaadCondact>() };
            var elseProcess = conditional.ElseBranch != null ? 
                new DaadProcess { Number = _nextProcessNumber++, Condacts = new List<DaadCondact>() } : null;
            
            // Agregar condición
            var conditionCondact = ParseCondition();
            context.CurrentProcess.Condacts.Add(conditionCondact);
            
            // Saltar al proceso then
            context.CurrentProcess.Condacts.Add(new DaadCondact 
            { 
                Name = "PROCESS", 
                Parameters = new List<int> { thenProcess.Number } 
            });
            
            // Si hay else, agregar salto condicional
            if (elseProcess != null)
            {
                context.CurrentProcess.Condacts.Add(new DaadCondact 
                { 
                    Name = "PROCESS", 
                    Parameters = new List<int> { elseProcess.Number } 
                });
            }
            
            // Transpile then branch
            context.CurrentProcess = thenProcess;
            TranspileStatement(conditional.ThenBranch, processes, context);
            processes.Add(thenProcess);
            
            // Transpile else branch if exists
            if (conditional.ElseBranch != null && elseProcess != null)
            {
                context.CurrentProcess = elseProcess;
                TranspileStatement(conditional.ElseBranch, processes, context);
                processes.Add(elseProcess);
            }
        }

        /// <summary>
        /// Transpila una sentencia con delay
        /// </summary>
        private void TranspileDelayed(DelayedSequentialStatement delayed, 
                                     List<DaadProcess> processes, 
                                     SequentialContext context)
        {
            var delayedProcess = CreateDelayedProcess(delayed.Statement, processes, context);
            
            // Usar flag temporal para el delay
            var delayFlag = _nextFlagNumber++;
            var delayValue = (int)delayed.Delay.TotalSeconds;
            
            // Establecer flag de delay
            context.CurrentProcess.Condacts.Add(new DaadCondact 
            { 
                Name = "LET", 
                Parameters = new List<int> { delayFlag, delayValue } 
            });
            
            // Activar el proceso de delay
            context.CurrentProcess.Condacts.Add(new DaadCondact 
            { 
                Name = "PROCESS", 
                Parameters = new List<int> { delayedProcess.Number } 
            });
        }

        /// <summary>
        /// Transpila un loop
        /// </summary>
        private void TranspileLoop(LoopSequentialStatement loop, 
                                  List<DaadProcess> processes, 
                                  SequentialContext context)
        {
            var loopProcess = new DaadProcess { Number = _nextProcessNumber++, Condacts = new List<DaadCondact>() };
            var bodyProcess = new DaadProcess { Number = _nextProcessNumber++, Condacts = new List<DaadCondact>() };
            
            switch (loop.Type)
            {
                case LoopType.While:
                    // Verificar condición
                    if (loop.Condition != null)
                    {
                        var conditionCondact = ParseCondition();
                        loopProcess.Condacts.Add(conditionCondact);
                    }
                    
                    // Ejecutar body
                    loopProcess.Condacts.Add(new DaadCondact 
                    { 
                        Name = "PROCESS", 
                        Parameters = new List<int> { bodyProcess.Number } 
                    });
                    break;
                    
                case LoopType.For:
                case LoopType.Repeat:
                    // Usar contador para loops finitos
                    var counterFlag = _nextFlagNumber++;
                    var count = loop.Count ?? 1;
                    
                    // Inicializar contador
                    loopProcess.Condacts.Add(new DaadCondact 
                    { 
                        Name = "LET", 
                        Parameters = new List<int> { counterFlag, count } 
                    });
                    
                    // Verificar contador
                    loopProcess.Condacts.Add(new DaadCondact 
                    { 
                        Name = "GT", 
                        Parameters = new List<int> { counterFlag, 0 } 
                    });
                    
                    // Ejecutar body
                    loopProcess.Condacts.Add(new DaadCondact 
                    { 
                        Name = "PROCESS", 
                        Parameters = new List<int> { bodyProcess.Number } 
                    });
                    
                    // Decrementar contador en el body
                    bodyProcess.Condacts.Add(new DaadCondact 
                    { 
                        Name = "MINUS", 
                        Parameters = new List<int> { counterFlag, 1 } 
                    });
                    break;
            }
            
            // Transpile body
            context.CurrentProcess = bodyProcess;
            TranspileStatement(loop.Body, processes, context);
            
            // Volver al loop
            bodyProcess.Condacts.Add(new DaadCondact 
            { 
                Name = "PROCESS", 
                Parameters = new List<int> { loopProcess.Number } 
            });
            
            // Llamar al proceso de loop
            context.CurrentProcess.Condacts.Add(new DaadCondact 
            { 
                Name = "PROCESS", 
                Parameters = new List<int> { loopProcess.Number } 
            });
            
            processes.Add(loopProcess);
            processes.Add(bodyProcess);
        }

        /// <summary>
        /// Transpila manejo de errores
        /// </summary>
        private void TranspileErrorHandling(ErrorHandlingSequentialStatement errorHandling, 
                                           List<DaadProcess> processes, 
                                           SequentialContext context)
        {
            var errorFlag = _nextFlagNumber++;
            var errorProcess = new DaadProcess { Number = _nextProcessNumber++, Condacts = new List<DaadCondact>() };
            
            // Establecer flag de error
            context.ErrorFlag = errorFlag;
            context.ErrorHandler = errorHandling.ErrorHandler;
            
            // Transpile try statement
            TranspileStatement(errorHandling.TryStatement, processes, context);
            
            // Error handler process
            errorProcess.Condacts.Add(new DaadCondact 
            { 
                Name = "EQ", 
                Parameters = new List<int> { errorFlag, 1 } 
            });
            
            context.CurrentProcess = errorProcess;
            TranspileStatement(errorHandling.ErrorHandler, processes, context);
            processes.Add(errorProcess);
        }

        /// <summary>
        /// Crea un proceso con delay
        /// </summary>
        private DaadProcess CreateDelayedProcess(SequentialStatement statement, 
                                               List<DaadProcess> processes, 
                                               SequentialContext context)
        {
            var delayProcess = new DaadProcess { Number = _nextProcessNumber++, Condacts = new List<DaadCondact>() };
            
            var originalProcess = context.CurrentProcess;
            context.CurrentProcess = delayProcess;
            
            TranspileStatement(statement, processes, context);
            
            context.CurrentProcess = originalProcess;
            processes.Add(delayProcess);
            
            return delayProcess;
        }

        /// <summary>
        /// Genera código DAAD clásico
        /// </summary>
        private static string GenerateClassicCode(List<DaadProcess> processes)
        {
            var builder = new StringBuilder();
            
            builder.AppendLine("; Código generado por SequentialTranspiler");
            builder.AppendLine("; " + DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss"));
            builder.AppendLine();
            
            foreach (var process in processes)
            {
                builder.AppendLine($"; Proceso {process.Number}");
                
                foreach (var condact in process.Condacts)
                {
                    var paramStr = string.Join(" ", condact.Parameters);
                    builder.AppendLine($"{condact.Name} {paramStr}");
                }
                
                builder.AppendLine("DONE");
                builder.AppendLine();
            }
            
            return builder.ToString();
        }

        // Métodos de utilidad
        private static int ParseParameter(string param)
        {
            return int.TryParse(param, out int result) ? result : 0;
        }

        private static DaadCondact ParseCondition()
        {
            // Simplificado - en implementación real, parsear condición completa
            return new DaadCondact { Name = "TRUE", Parameters = new List<int>() };
        }
    }

    // =====================================================================
    // TIPOS DE APOYO
    // =====================================================================

    /// <summary>
    /// Contexto para transpilación secuencial
    /// </summary>
    public class SequentialContext
    {
        public required DaadProcess CurrentProcess { get; set; }
        public List<SequentialStatement> FinallyStatements { get; set; } = new();
        public SequentialStatement? ErrorHandler { get; set; }
        public int ErrorFlag { get; set; }
    }

    /// <summary>
    /// Proceso DAAD generado
    /// </summary>
    public class DaadProcess
    {
        public int Number { get; set; }
        public List<DaadCondact> Condacts { get; set; } = new();
    }

    /// <summary>
    /// Condact DAAD
    /// </summary>
    public class DaadCondact
    {
        public string Name { get; set; } = "";
        public List<int> Parameters { get; set; } = new();
    }

    /// <summary>
    /// Resultado de transpilación secuencial
    /// </summary>
    public class SequentialTranspileResult
    {
        public bool Success { get; set; }
        public List<DaadProcess> Processes { get; set; } = new();
        public string ClassicCode { get; set; } = "";
        public int ProcessesGenerated { get; set; }
        public string ErrorMessage { get; set; } = "";
    }

    // =====================================================================
    // EJEMPLOS DE USO
    // =====================================================================

    /// <summary>
    /// Ejemplos demostrativos de sentencias secuenciales
    /// </summary>
    public static class SequentialExamples
    {
        /// <summary>
        /// Ejemplo 1: Secuencia simple con "then"
        /// </summary>
        public static SequentialStatement SimpleSequenceExample()
        {
            return new ChainedSequentialStatement(
                new SimpleSequentialStatement("MESSAGE", new List<string> { "Abriendo puerta..." }),
                SequenceOperator.Then,
                new ChainedSequentialStatement(
                    new SimpleSequentialStatement("SET", new List<string> { "50", "1" }),
                    SequenceOperator.Then,
                    new SimpleSequentialStatement("GOTO", new List<string> { "2" })
                )
            );
        }

        /// <summary>
        /// Ejemplo 2: Secuencia con delay
        /// </summary>
        public static SequentialStatement DelayedSequenceExample()
        {
            return new ChainedSequentialStatement(
                new SimpleSequentialStatement("MESSAGE", new List<string> { "Preparando ritual..." }),
                SequenceOperator.After,
                new DelayedSequentialStatement(
                    TimeSpan.FromSeconds(3),
                    new SimpleSequentialStatement("MESSAGE", new List<string> { "¡Ritual completo!" })
                )
            );
        }

        /// <summary>
        /// Ejemplo 3: Secuencia condicional
        /// </summary>
        public static SequentialStatement ConditionalSequenceExample()
        {
            return new ConditionalSequentialStatement(
                "CARRIED 10",
                new SimpleSequentialStatement("MESSAGE", new List<string> { "Tienes la llave" }),
                new SimpleSequentialStatement("MESSAGE", new List<string> { "Necesitas la llave" })
            );
        }

        /// <summary>
        /// Ejemplo 4: Loop con secuencia
        /// </summary>
        public static SequentialStatement LoopSequenceExample()
        {
            return new LoopSequentialStatement(
                LoopType.Repeat,
                null,
                3,
                new ChainedSequentialStatement(
                    new SimpleSequentialStatement("MESSAGE", new List<string> { "Intentando..." }),
                    SequenceOperator.Then,
                    new SimpleSequentialStatement("BEEP", new List<string> { "1" })
                )
            );
        }

        /// <summary>
        /// Ejemplo 5: Secuencia compleja con manejo de errores
        /// </summary>
        public static SequentialStatement ComplexSequenceExample()
        {
            var mainSequence = new ChainedSequentialStatement(
                new SimpleSequentialStatement("MESSAGE", new List<string> { "Iniciando secuencia compleja..." }),
                SequenceOperator.Then,
                new ConditionalSequentialStatement(
                    "PRESENT 20",
                    new ChainedSequentialStatement(
                        new SimpleSequentialStatement("GET", new List<string> { "20" }),
                        SequenceOperator.Then,
                        new SimpleSequentialStatement("MESSAGE", new List<string> { "Objeto obtenido" })
                    ),
                    new SimpleSequentialStatement("MESSAGE", new List<string> { "Objeto no presente" })
                )
            );

            return new ErrorHandlingSequentialStatement(
                mainSequence,
                new SimpleSequentialStatement("MESSAGE", new List<string> { "Error en secuencia" })
            );
        }
    }

    // =====================================================================
    // DEMO Y TESTING
    // =====================================================================

    /// <summary>
    /// Clase demo para mostrar funcionalidad
    /// </summary>
    public class SequentialDemo
    {
        private readonly SequentialTranspiler _transpiler;

        public SequentialDemo(ILogger<SequentialTranspiler> logger)
        {
            _transpiler = new SequentialTranspiler(logger);
        }

        /// <summary>
        /// Ejecuta todos los ejemplos
        /// </summary>
        public void RunAllExamples()
        {
            Console.WriteLine("=== DEMO: Sentencias Secuenciales DAAD Moderno ===\n");

            RunExample("Secuencia Simple", SequentialExamples.SimpleSequenceExample());
            RunExample("Secuencia con Delay", SequentialExamples.DelayedSequenceExample());
            RunExample("Secuencia Condicional", SequentialExamples.ConditionalSequenceExample());
            RunExample("Loop con Secuencia", SequentialExamples.LoopSequenceExample());
            RunExample("Secuencia Compleja", SequentialExamples.ComplexSequenceExample());
        }

        private void RunExample(string title, SequentialStatement statement)
        {
            Console.WriteLine($"--- {title} ---");
            
            var result = _transpiler.TranspileSequential(statement);
            
            if (result.Success)
            {
                Console.WriteLine($"✅ Transpilación exitosa - {result.ProcessesGenerated} procesos generados");
                Console.WriteLine("\nCódigo DAAD clásico generado:");
                Console.WriteLine(result.ClassicCode);
            }
            else
            {
                Console.WriteLine($"❌ Error: {result.ErrorMessage}");
            }
            
            Console.WriteLine(new string('-', 50));
            Console.WriteLine();
        }
    }
}
