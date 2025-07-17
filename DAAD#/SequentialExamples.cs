// =====================================================================
// DAAD Moderno - Ejemplo de Uso de Sentencias Secuenciales
// Demonstración práctica de las capacidades secuenciales
// =====================================================================

using System;
using System.Collections.Generic;
using Microsoft.Extensions.Logging;
using DaadModern.Sequential;

namespace DaadModern.Examples
{
    /// <summary>
    /// Ejemplos prácticos de uso de sentencias secuenciales
    /// </summary>
    public class SequentialExamplesDemo
    {
        private readonly SequentialTranspiler _transpiler;
        private readonly ILogger<SequentialExamplesDemo> _logger;

        public SequentialExamplesDemo(ILogger<SequentialExamplesDemo> logger, 
                                     ILogger<SequentialTranspiler> transpilerLogger)
        {
            _logger = logger;
            _transpiler = new SequentialTranspiler(transpilerLogger);
        }

        /// <summary>
        /// Ejemplo 1: Secuencia de apertura de puerta con ritual
        /// </summary>
        public void DoorOpeningRitualExample()
        {
            _logger.LogInformation("=== Ejemplo 1: Ritual de Apertura de Puerta ===");

            // Crear la secuencia compleja
            var ritualSequence = new ChainedSequentialStatement(
                // Paso 1: Verificar que tiene los objetos necesarios
                new SimpleSequentialStatement("MESSAGE", new List<string> { "Comienzas el ritual de apertura..." }),
                SequenceOperator.Then,
                
                new ChainedSequentialStatement(
                    // Paso 2: Encender la vela
                    new SimpleSequentialStatement("MESSAGE", new List<string> { "Enciendes la vela mística..." }),
                    SequenceOperator.Then,
                    
                    new ChainedSequentialStatement(
                        // Paso 3: Esperar 3 segundos
                        new DelayedSequentialStatement(
                            TimeSpan.FromSeconds(3),
                            new SimpleSequentialStatement("MESSAGE", new List<string> { "La vela arde con luz sobrenatural..." })
                        ),
                        SequenceOperator.Then,
                        
                        new ChainedSequentialStatement(
                            // Paso 4: Recitar encantamiento 3 veces
                            new LoopSequentialStatement(
                                LoopType.Repeat,
                                null,
                                3,
                                new ChainedSequentialStatement(
                                    new SimpleSequentialStatement("MESSAGE", new List<string> { "Recitas el encantamiento..." }),
                                    SequenceOperator.Then,
                                    new SimpleSequentialStatement("BEEP", new List<string> { "2" })
                                )
                            ),
                            SequenceOperator.Then,
                            
                            new ChainedSequentialStatement(
                                // Paso 5: Verificar éxito del ritual
                                new ConditionalSequentialStatement(
                                    "CHANCE 80", // 80% de éxito
                                    new ChainedSequentialStatement(
                                        new SimpleSequentialStatement("MESSAGE", new List<string> { "¡El ritual es exitoso!" }),
                                        SequenceOperator.Then,
                                        new ChainedSequentialStatement(
                                            new SimpleSequentialStatement("SET", new List<string> { "50", "1" }), // puerta_abierta = 1
                                            SequenceOperator.Then,
                                            new SimpleSequentialStatement("GOTO", new List<string> { "2" }) // ir a través de la puerta
                                        )
                                    ),
                                    // Fallo del ritual
                                    new ChainedSequentialStatement(
                                        new SimpleSequentialStatement("MESSAGE", new List<string> { "El ritual falla..." }),
                                        SequenceOperator.Then,
                                        new SimpleSequentialStatement("MINUS", new List<string> { "30", "10" }) // perder 10 puntos
                                    )
                                ),
                                SequenceOperator.Finally,
                                
                                // Paso 6: Limpiar después del ritual
                                new ChainedSequentialStatement(
                                    new SimpleSequentialStatement("MESSAGE", new List<string> { "La vela se apaga..." }),
                                    SequenceOperator.Then,
                                    new SimpleSequentialStatement("SET", new List<string> { "51", "1" }) // ritual_realizado = 1
                                )
                            )
                        )
                    )
                )
            );

            // Transpile and show results
            var result = _transpiler.TranspileSequential(ritualSequence);
            ShowTranspileResult("Ritual de Apertura de Puerta", result);
        }

        /// <summary>
        /// Ejemplo 2: Combate secuencial con múltiples enemigos
        /// </summary>
        public void SequentialCombatExample()
        {
            _logger.LogInformation("=== Ejemplo 2: Combate Secuencial ===");

            // Secuencia de combate compleja
            var combatSequence = new ChainedSequentialStatement(
                // Iniciar combate
                new SimpleSequentialStatement("MESSAGE", new List<string> { "¡Comienza el combate!" }),
                SequenceOperator.Then,
                
                new ChainedSequentialStatement(
                    // Loop de combate mientras hay enemigos
                    new LoopSequentialStatement(
                        LoopType.While,
                        "GT 52 0", // mientras vida_enemigo > 0
                        null,
                        new ChainedSequentialStatement(
                            // Ataque del jugador
                            new SimpleSequentialStatement("MESSAGE", new List<string> { "Atacas al enemigo..." }),
                            SequenceOperator.Then,
                            
                            new ChainedSequentialStatement(
                                // Calcular daño
                                new ConditionalSequentialStatement(
                                    "CHANCE 70", // 70% de éxito
                                    new ChainedSequentialStatement(
                                        new SimpleSequentialStatement("MESSAGE", new List<string> { "¡Golpe certero!" }),
                                        SequenceOperator.Then,
                                        new SimpleSequentialStatement("MINUS", new List<string> { "52", "20" }) // daño al enemigo
                                    ),
                                    new SimpleSequentialStatement("MESSAGE", new List<string> { "Fallas el ataque..." })
                                ),
                                SequenceOperator.Then,
                                
                                new ChainedSequentialStatement(
                                    // Verificar si enemigo sigue vivo
                                    new ConditionalSequentialStatement(
                                        "GT 52 0", // si enemigo sigue vivo
                                        new ChainedSequentialStatement(
                                            // Ataque del enemigo
                                            new DelayedSequentialStatement(
                                                TimeSpan.FromSeconds(1),
                                                new SimpleSequentialStatement("MESSAGE", new List<string> { "El enemigo contraataca..." })
                                            ),
                                            SequenceOperator.Then,
                                            
                                            new ConditionalSequentialStatement(
                                                "CHANCE 50", // 50% de éxito del enemigo
                                                new ChainedSequentialStatement(
                                                    new SimpleSequentialStatement("MESSAGE", new List<string> { "¡El enemigo te golpea!" }),
                                                    SequenceOperator.Then,
                                                    new SimpleSequentialStatement("MINUS", new List<string> { "31", "15" }) // daño al jugador (vida en flag 31)
                                                ),
                                                new SimpleSequentialStatement("MESSAGE", new List<string> { "El enemigo falla..." })
                                            )
                                        )
                                    ),
                                    SequenceOperator.Then,
                                    
                                    // Pausa entre turnos
                                    new DelayedSequentialStatement(
                                        TimeSpan.FromSeconds(2),
                                        new SimpleSequentialStatement("MESSAGE", new List<string> { "--- Siguiente turno ---" })
                                    )
                                )
                            )
                        )
                    ),
                    SequenceOperator.Finally,
                    
                    // Resultado del combate
                    new ConditionalSequentialStatement(
                        "ZERO 52", // si vida_enemigo = 0
                        new ChainedSequentialStatement(
                            new SimpleSequentialStatement("MESSAGE", new List<string> { "¡Victoria! Has derrotado al enemigo." }),
                            SequenceOperator.Then,
                            new SimpleSequentialStatement("PLUS", new List<string> { "30", "50" }) // +50 puntos
                        ),
                        new ChainedSequentialStatement(
                            new SimpleSequentialStatement("MESSAGE", new List<string> { "Has sido derrotado..." }),
                            SequenceOperator.Then,
                            new SimpleSequentialStatement("RESTART", new List<string>()) // reiniciar
                        )
                    )
                )
            );

            // Transpile and show results
            var result = _transpiler.TranspileSequential(combatSequence);
            ShowTranspileResult("Combate Secuencial", result);
        }

        /// <summary>
        /// Ejemplo 3: Secuencia con manejo de errores
        /// </summary>
        public void ErrorHandlingExample()
        {
            _logger.LogInformation("=== Ejemplo 3: Manejo de Errores ===");

            // Secuencia con manejo de errores
            var errorHandlingSequence = new ErrorHandlingSequentialStatement(
                // Intentar hacer algo peligroso
                new ChainedSequentialStatement(
                    new SimpleSequentialStatement("MESSAGE", new List<string> { "Intentas usar el artefacto mágico..." }),
                    SequenceOperator.Then,
                    
                    new ChainedSequentialStatement(
                        // Verificar si tiene suficiente energía
                        new ConditionalSequentialStatement(
                            "GE 60 50", // si energia_magica >= 50
                            new ChainedSequentialStatement(
                                new SimpleSequentialStatement("MESSAGE", new List<string> { "¡El artefacto resplandece!" }),
                                SequenceOperator.Then,
                                new ChainedSequentialStatement(
                                    new SimpleSequentialStatement("MINUS", new List<string> { "60", "50" }), // gastar energía
                                    SequenceOperator.Then,
                                    new SimpleSequentialStatement("SET", new List<string> { "61", "1" }) // artefacto_activado = 1
                                )
                            ),
                            // No hay suficiente energía - esto causará un "error"
                            new ChainedSequentialStatement(
                                new SimpleSequentialStatement("MESSAGE", new List<string> { "No tienes suficiente energía..." }),
                                SequenceOperator.Then,
                                new SimpleSequentialStatement("SET", new List<string> { "150", "1" }) // error_flag = 1
                            )
                        ),
                        SequenceOperator.Then,
                        
                        // Más acciones que podrían fallar
                        new ConditionalSequentialStatement(
                            "CHANCE 30", // 30% de fallo crítico
                            new ChainedSequentialStatement(
                                new SimpleSequentialStatement("MESSAGE", new List<string> { "¡Fallo crítico del artefacto!" }),
                                SequenceOperator.Then,
                                new SimpleSequentialStatement("SET", new List<string> { "150", "1" }) // error_flag = 1
                            )
                        )
                    )
                ),
                
                // Manejo de errores
                new ChainedSequentialStatement(
                    new SimpleSequentialStatement("MESSAGE", new List<string> { "Algo salió mal con el artefacto..." }),
                    SequenceOperator.Then,
                    
                    new ChainedSequentialStatement(
                        new SimpleSequentialStatement("MESSAGE", new List<string> { "El artefacto se desactiva automáticamente." }),
                        SequenceOperator.Then,
                        
                        new ChainedSequentialStatement(
                            new SimpleSequentialStatement("SET", new List<string> { "61", "0" }), // artefacto_activado = 0
                            SequenceOperator.Then,
                            new SimpleSequentialStatement("CLEAR", new List<string> { "150" }) // limpiar error_flag
                        )
                    )
                )
            );

            // Transpile and show results
            var result = _transpiler.TranspileSequential(errorHandlingSequence);
            ShowTranspileResult("Manejo de Errores", result);
        }

        /// <summary>
        /// Ejemplo 4: Secuencia de puzzle complejo
        /// </summary>
        public void ComplexPuzzleExample()
        {
            _logger.LogInformation("=== Ejemplo 4: Puzzle Complejo ===");

            // Secuencia de puzzle con múltiples pasos
            var puzzleSequence = new ChainedSequentialStatement(
                new SimpleSequentialStatement("MESSAGE", new List<string> { "Te enfrentas a un puzzle antiguo..." }),
                SequenceOperator.Then,
                
                new ChainedSequentialStatement(
                    // Paso 1: Encontrar la secuencia correcta
                    new LoopSequentialStatement(
                        LoopType.While,
                        "ZERO 70", // mientras puzzle_resuelto = 0
                        null,
                        new ChainedSequentialStatement(
                            new SimpleSequentialStatement("MESSAGE", new List<string> { "Examinas las runas..." }),
                            SequenceOperator.Then,
                            
                            new ChainedSequentialStatement(
                                // Generar número aleatorio para el puzzle
                                new ConditionalSequentialStatement(
                                    "CHANCE 25", // 25% de éxito por intento
                                    new ChainedSequentialStatement(
                                        new SimpleSequentialStatement("MESSAGE", new List<string> { "¡Descifras parte del puzzle!" }),
                                        SequenceOperator.Then,
                                        new SimpleSequentialStatement("PLUS", new List<string> { "71", "1" }) // progreso_puzzle++
                                    ),
                                    new SimpleSequentialStatement("MESSAGE", new List<string> { "No encuentras la conexión..." })
                                ),
                                SequenceOperator.Then,
                                
                                new ChainedSequentialStatement(
                                    // Verificar si está completo
                                    new ConditionalSequentialStatement(
                                        "GE 71 4", // si progreso_puzzle >= 4
                                        new ChainedSequentialStatement(
                                            new SimpleSequentialStatement("MESSAGE", new List<string> { "¡Has resuelto el puzzle!" }),
                                            SequenceOperator.Then,
                                            new SimpleSequentialStatement("SET", new List<string> { "70", "1" }) // puzzle_resuelto = 1
                                        )
                                    ),
                                    SequenceOperator.Then,
                                    
                                    // Pausa entre intentos
                                    new DelayedSequentialStatement(
                                        TimeSpan.FromSeconds(1),
                                        new SimpleSequentialStatement("MESSAGE", new List<string> { "Continúas estudiando..." })
                                    )
                                )
                            )
                        )
                    ),
                    SequenceOperator.Then,
                    
                    new ChainedSequentialStatement(
                        // Recompensa por resolver el puzzle
                        new SimpleSequentialStatement("MESSAGE", new List<string> { "Una cámara secreta se abre..." }),
                        SequenceOperator.Then,
                        
                        new ChainedSequentialStatement(
                            new SimpleSequentialStatement("PLUS", new List<string> { "30", "100" }), // +100 puntos
                            SequenceOperator.Then,
                            new SimpleSequentialStatement("CREATE", new List<string> { "25" }) // crear objeto recompensa
                        )
                    )
                )
            );

            // Transpile and show results
            var result = _transpiler.TranspileSequential(puzzleSequence);
            ShowTranspileResult("Puzzle Complejo", result);
        }

        /// <summary>
        /// Ejecutar todos los ejemplos
        /// </summary>
        public void RunAllExamples()
        {
            _logger.LogInformation("Ejecutando todos los ejemplos de sentencias secuenciales...");
            
            DoorOpeningRitualExample();
            SequentialCombatExample();
            ErrorHandlingExample();
            ComplexPuzzleExample();
            
            _logger.LogInformation("Todos los ejemplos completados.");
        }

        /// <summary>
        /// Mostrar resultado de transpilación
        /// </summary>
        private void ShowTranspileResult(string title, SequentialTranspileResult result)
        {
            Console.WriteLine($"\n--- {title} ---");
            
            if (result.Success)
            {
                Console.WriteLine($"✅ Transpilación exitosa");
                Console.WriteLine($"📊 Procesos generados: {result.ProcessesGenerated}");
                Console.WriteLine($"📝 Condactos totales: {result.Processes.Sum(p => p.Condacts.Count)}");
                Console.WriteLine("\n🔤 Código DAAD clásico generado:");
                Console.WriteLine(result.ClassicCode);
            }
            else
            {
                Console.WriteLine($"❌ Error en transpilación: {result.ErrorMessage}");
            }
            
            Console.WriteLine(new string('=', 60));
        }
    }

    /// <summary>
    /// Programa principal para ejecutar los ejemplos
    /// </summary>
    public class SequentialExamplesProgram
    {
        public static void Main(string[] args)
        {
            // Configurar logging
            using var loggerFactory = LoggerFactory.Create(builder =>
                builder.AddConsole().SetMinimumLevel(LogLevel.Information));
            
            var logger = loggerFactory.CreateLogger<SequentialExamplesDemo>();
            var transpilerLogger = loggerFactory.CreateLogger<SequentialTranspiler>();
            
            // Crear y ejecutar ejemplos
            var demo = new SequentialExamplesDemo(logger, transpilerLogger);
            
            Console.WriteLine("=== DAAD Moderno - Ejemplos de Sentencias Secuenciales ===");
            Console.WriteLine("Demonstrando capacidades avanzadas de programación secuencial\n");
            
            try
            {
                demo.RunAllExamples();
            }
            catch (Exception ex)
            {
                logger.LogError(ex, "Error ejecutando ejemplos");
                Console.WriteLine($"❌ Error: {ex.Message}");
            }
            
            Console.WriteLine("\n✅ Demostración completada.");
            Console.WriteLine("Presiona cualquier tecla para salir...");
            Console.ReadKey();
        }
    }
}
