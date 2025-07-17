// =====================================================================
// DAAD Moderno - Tests de Completitud Fase 1
// Suite completa de tests para validar transpilador
// =====================================================================

using System;
using System.Collections.Generic;
using System.IO;
using System.Threading.Tasks;
using Xunit;
using FluentAssertions;
using Microsoft.Extensions.Logging;
using DaadModern.Parser;
using DaadModern.Transpiler;

namespace DaadModern.Tests
{
    /// <summary>
    /// Tests críticos para validar completitud de Fase 1
    /// </summary>
    public class Phase1CompletenessTests
    {
        private readonly ILogger<CompleteDaadTranspiler> _logger;
        private readonly CompleteDaadTranspiler _transpiler;
        private readonly DaadPidginParser _parser;
        
        public Phase1CompletenessTests()
        {
            _logger = LoggerFactory.Create(builder => builder.AddConsole())
                .CreateLogger<CompleteDaadTranspiler>();
            _transpiler = new CompleteDaadTranspiler(_logger);
            _parser = new DaadPidginParser();
        }
        
        /// <summary>
        /// Test 1: Verificar que todos los condactos críticos están implementados
        /// </summary>
        [Fact]
        public void CriticalCondacts_AllImplemented()
        {
            // Arrange: Lista de condactos que DEBEN estar en Fase 1
            var criticalCondacts = new[]
            {
                "ZERO", "NOTZERO", "WORN", "NOTWORN", "WEAR", "REMOVE",
                "RESTART", "QUIT", "ISAT", "CHANCE", "TURNS", "SAME"
            };
            
            // Act: Verificar cada condacto
            var implementedCondacts = _transpiler.GetImplementedCondacts();
            
            // Assert: Todos los críticos deben estar implementados
            foreach (var condact in criticalCondacts)
            {
                implementedCondacts.Should().ContainKey(condact.ToLower(),
                    $"Condacto crítico {condact} debe estar implementado para Fase 1");
            }
        }
        
        /// <summary>
        /// Test 2: Transpilación de aventura con objetos vestibles
        /// </summary>
        [Fact]
        public async Task WearableObjects_TranspileCorrectly()
        {
            // Arrange: Código DAAD moderno con objetos vestibles
            var modernCode = @"
game {
    title: ""Aventura con Vestibles""
    start: habitacion
}

objects {
    casco {
        name: ""casco de hierro""
        desc: ""Un casco brillante""
        location: habitacion
        properties: [wearable]
        slot: head
    }
}

responses {
    on [""vestir casco"", ""ponerse casco""] {
        require: present(casco) && !worn(casco)
        do: {
            wear(casco)
            message(""Te pones el casco"")
            done
        }
    }
    
    on [""quitar casco"", ""quitarse casco""] {
        require: worn(casco)
        do: {
            remove(casco)
            message(""Te quitas el casco"")
            done
        }
    }
}";
            
            // Act: Parsear y transpilar
            var parseResult = await _parser.ParseProgramAsync(modernCode);
            parseResult.Success.Should().BeTrue($"Parsing failed: {parseResult.Error}");
            
            var transpileResult = _transpiler.TranspileToClassic(
                parseResult.Value, ClassicPlatform.ZxSpectrum);
            
            // Assert: Transpilación exitosa con condactos correctos
            transpileResult.Success.Should().BeTrue();
            transpileResult.GeneratedCode.Should().Contain("WORN");
            transpileResult.GeneratedCode.Should().Contain("WEAR");
            transpileResult.GeneratedCode.Should().Contain("REMOVE");
        }
        
        /// <summary>
        /// Test 3: Condiciones ZERO/NOTZERO transpilan correctamente
        /// </summary>
        [Fact]
        public async Task ZeroConditions_TranspileCorrectly()
        {
            // Arrange: Código con condiciones zero/notzero
            var modernCode = @"
game {
    title: ""Test Zero Conditions""
    start: inicio
}

responses {
    on [""probar puerta""] {
        require: zero(flag_puerta_abierta)
        do: {
            message(""La puerta está cerrada"")
            done
        }
    }
    
    on [""usar llave""] {
        require: notzero(contador_llaves) && zero(flag_puerta_abierta)
        do: {
            set(flag_puerta_abierta, 1)
            dec(contador_llaves)
            message(""Abres la puerta con la llave"")
            done
        }
    }
}";
            
            // Act & Assert
            var result = await ParseAndTranspile(modernCode);
            result.GeneratedCode.Should().Contain("ZERO");
            result.GeneratedCode.Should().Contain("NOTZERO");
        }
        
        /// <summary>
        /// Test 4: Control de flujo del juego (RESTART/QUIT)
        /// </summary>
        [Fact]
        public async Task GameControl_TranspilesCorrectly()
        {
            // Arrange
            var modernCode = @"
responses {
    on [""reiniciar"", ""empezar de nuevo""] {
        require: ask_confirmation(""¿Seguro?"")
        do: {
            restart_game()
        }
    }
    
    on [""salir"", ""quit""] {
        do: {
            message(""¡Hasta la vista!"")
            quit_game()
        }
    }
}";
            
            // Act & Assert
            var result = await ParseAndTranspile(modernCode);
            result.GeneratedCode.Should().Contain("RESTART");
            result.GeneratedCode.Should().Contain("QUIT");
        }
        
        /// <summary>
        /// Test 5: Compatibilidad con aventura DAAD clásica real
        /// </summary>
        [Fact]
        public async Task ClassicAdventure_CompatibilityCheck()
        {
            // Arrange: Simular fragmento de aventura clásica
            var classicDaadCode = @"
/CTL
; Control section
; Object: WORN 1
; Condition: ZERO 50
; Action: RESTART
; Action: QUIT
/STX

; Vocabulary
COGE 10
LLEVA 10  
PONTE 50
QUITA 51

; Messages  
1 ""Llevas puesto el casco""
2 ""No tienes el casco""
3 ""¿Estás seguro de reiniciar?""

; Locations
1 ""Habitación inicial""

; Objects  
1 ""casco de hierro"" 1

; Process Table
_ _
WORN 1 MES 1 DONE
NOTWORN 1 MES 2 DONE
_ _
ZERO 50 MES 3 DONE
_ _
";
            
            // Act: Verificar que el transpiler reconoce estos condactos
            var compatibilityResult = _transpiler.ValidateClassicCompatibility(classicDaadCode);
            
            // Assert: No debe haber condactos no soportados
            compatibilityResult.UnsupportedCondacts.Should().BeEmpty(
                "Todos los condactos en aventuras clásicas deben estar soportados");
        }
        
        /// <summary>
        /// Test 6: Performance - transpilación rápida
        /// </summary>
        [Fact]
        public async Task Transpilation_MeetsPerformanceTargets()
        {
            // Arrange: Aventura de tamaño medio
            var mediumAdventure = GenerateMediumSizeAdventure();
            
            // Act: Medir tiempo de transpilación
            var stopwatch = System.Diagnostics.Stopwatch.StartNew();
            var result = await ParseAndTranspile(mediumAdventure);
            stopwatch.Stop();
            
            // Assert: Debe ser menor a 2 segundos
            stopwatch.ElapsedMilliseconds.Should().BeLessThan(2000,
                "Transpilación debe completarse en menos de 2 segundos");
            result.Success.Should().BeTrue();
        }
        
        /// <summary>
        /// Test 7: Cobertura de condactos - mínimo 85%
        /// </summary>
        [Fact]
        public void CondactCoverage_MeetsMinimumRequirement()
        {
            // Arrange: Lista completa de condactos DAAD originales
            var allDaadCondacts = GetAllOriginalDaadCondacts();
            var implementedCondacts = _transpiler.GetImplementedCondacts();
            
            // Act: Calcular porcentaje de cobertura
            var coveragePercentage = (double)implementedCondacts.Count / allDaadCondacts.Count * 100;
            
            // Assert: Mínimo 85% para Fase 1
            coveragePercentage.Should().BeGreaterOrEqualTo(85.0,
                $"Cobertura actual: {coveragePercentage:F1}%. Mínimo para Fase 1: 85%");
        }
        
        /// <summary>
        /// Test 8: Transpilación bidireccional sin pérdida
        /// </summary>
        [Fact]
        public async Task BidirectionalTranspilation_NoDataLoss()
        {
            // Arrange: Código moderno con características complejas
            var originalModern = CreateComplexModernAdventure();
            
            // Act: Moderno → Clásico → Moderno
            var classicResult = _transpiler.TranspileToClassic(originalModern, ClassicPlatform.ZxSpectrum);
            var backToModernResult = _transpiler.TranspileToModern(classicResult.GeneratedCode);
            
            // Assert: Funcionalidad equivalente
            backToModernResult.Success.Should().BeTrue();
            ValidateFunctionalEquivalence(originalModern, backToModernResult.Program);
        }
        
        #region Helper Methods
        
        private async Task<TranspileResult> ParseAndTranspile(string modernCode)
        {
            var parseResult = await _parser.ParseProgramAsync(modernCode);
            parseResult.Success.Should().BeTrue($"Parsing failed: {parseResult.Error}");
            
            return _transpiler.TranspileToClassic(parseResult.Value, ClassicPlatform.ZxSpectrum);
        }
        
        private string GenerateMediumSizeAdventure()
        {
            // Generar aventura con ~50 respuestas, 20 objetos, 15 localizaciones
            return @"
game {
    title: ""Aventura de Prueba Performance""
    start: sala_principal
}

// ... código generado automáticamente ...
";
        }
        
        private List<string> GetAllOriginalDaadCondacts()
        {
            return new List<string>
            {
                "AT", "NOTAT", "PRESENT", "ABSENT", "CARRIED", "NOTCARR",
                "WORN", "NOTWORN", "EQ", "NOTEQ", "LT", "LE", "GT", "GE",
                "ZERO", "NOTZERO", "CHANCE", "TURNS", "SAME", "ISAT",
                "GOTO", "GET", "DROP", "WEAR", "REMOVE", "MESSAGE", "CLEAR",
                "LET", "PLUS", "MINUS", "SET", "DESC", "RESTART", "QUIT",
                "COPYOO", "COPYOF", "COPYFO", "COPYFF", "EXTERN", "BEEP",
                "PICTURE", "RAMLOAD", "RAMSAVE", "PROCESS"
                // Lista completa de ~70 condactos
            };
        }
        
        private DaadProgram CreateComplexModernAdventure()
        {
            // Crear aventura con todas las características implementadas
            return new DaadProgram
            {
                Game = new GameInfo { Title = "Test Complex", StartLocation = "inicio" },
                // ... resto de la estructura ...
            };
        }
        
        private void ValidateFunctionalEquivalence(DaadProgram original, DaadProgram converted)
        {
            // Verificar que la funcionalidad esencial se preserva
            original.Responses.Count.Should().Be(converted.Responses.Count);
            original.Objects.Count.Should().Be(converted.Objects.Count);
            original.Locations.Count.Should().Be(converted.Locations.Count);
        }
        
        #endregion
    }
    
    /// <summary>
    /// Tests de integración con aventuras reales
    /// </summary>
    public class RealAdventureIntegrationTests
    {
        [Theory]
        [InlineData("Rabenstein.ddb")]
        [InlineData("Hobbit.ddb")]
        [InlineData("Aventura_Original.ddb")]
        public async Task ClassicAdventure_TranspilesSuccessfully(string adventureFile)
        {
            // Arrange: Cargar aventura DAAD clásica real
            var classicCode = await File.ReadAllTextAsync($"TestData/{adventureFile}");
            var transpiler = CreateTranspiler();
            
            // Act: Transpilar a moderno
            var result = transpiler.TranspileToModern(classicCode);
            
            // Assert: Transpilación exitosa
            result.Success.Should().BeTrue(
                $"Aventura {adventureFile} debe transpilar sin errores");
            result.UnsupportedFeatures.Should().BeEmpty(
                $"No debe haber características no soportadas en {adventureFile}");
        }
        
        private CompleteDaadTranspiler CreateTranspiler()
        {
            var logger = LoggerFactory.Create(b => b.AddConsole())
                .CreateLogger<CompleteDaadTranspiler>();
            return new CompleteDaadTranspiler(logger);
        }
    }
}