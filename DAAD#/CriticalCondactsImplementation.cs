// =====================================================================
// DAAD# - Implementación de CondActs Faltantes Críticos
// Fase 1: CondActs Fundamentales (QUIT, PARSE, PROCESS, DOALL, SYSMESS)
// =====================================================================

using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Extensions.Logging;

namespace DaadModern.Core
{
    /// <summary>
    /// Implementación de CondActs críticos faltantes para DAAD#
    /// </summary>
    public partial class CompleteDaadTranspiler
    {
        private readonly ILogger<CompleteDaadTranspiler> _logger;
        private readonly Dictionary<string, CondactInfo> _criticalCondacts;

        public CompleteDaadTranspiler(ILogger<CompleteDaadTranspiler> logger)
        {
            _logger = logger;
            _criticalCondacts = InitializeCriticalCondacts();
        }

        /// <summary>
        /// Inicializa los CondActs críticos faltantes
        /// </summary>
        private static Dictionary<string, CondactInfo> InitializeCriticalCondacts()
        {
            return new Dictionary<string, CondactInfo>
            {
                // ===== NIVEL CRÍTICO (Imprescindibles) =====
                ["quit"] = new(CondactType.Condition, "QUIT", 0, "Salir del juego con confirmación"),
                ["parse"] = new(CondactType.Action, "PARSE", 0, "Analizar entrada del jugador"),
                ["process"] = new(CondactType.Action, "PROCESS", 1, "Llamar a sub-proceso"),
                ["doall"] = new(CondactType.Action, "DOALL", 1, "Ejecutar para todos los objetos"),
                ["sysmess"] = new(CondactType.Action, "SYSMESS", 1, "Mostrar mensaje del sistema"),
                ["extern"] = new(CondactType.Action, "EXTERN", 1, "Ejecutar código externo"),
                ["save"] = new(CondactType.Action, "SAVE", 1, "Guardar estado del juego"),
                ["load"] = new(CondactType.Action, "LOAD", 1, "Cargar estado del juego"),

                // ===== ATRIBUTOS DE OBJETOS =====
                ["hasat"] = new(CondactType.Condition, "HASAT", 1, "Objeto tiene atributo"),
                ["hasnat"] = new(CondactType.Condition, "HASNAT", 1, "Objeto NO tiene atributo"),

                // ===== CONTENEDORES =====
                ["putin"] = new(CondactType.Action, "PUTIN", 2, "Meter objeto en contenedor"),
                ["takeout"] = new(CondactType.Action, "TAKEOUT", 2, "Sacar objeto de contenedor"),

                // ===== FAMILIA COPY =====
                ["copyff"] = new(CondactType.Action, "COPYFF", 2, "Copiar flag a flag"),
                ["copyof"] = new(CondactType.Action, "COPYOF", 2, "Copiar objeto a flag"),
                ["copyfo"] = new(CondactType.Action, "COPYFO", 2, "Copiar flag a objeto"),
                ["copyoo"] = new(CondactType.Action, "COPYOO", 2, "Copiar objeto a objeto"),
                ["copybf"] = new(CondactType.Action, "COPYBF", 2, "Copiar byte a flag"),

                // ===== ACCIONES AUTOMÁTICAS =====
                ["autog"] = new(CondactType.Action, "AUTOG", 0, "Coger automático"),
                ["autod"] = new(CondactType.Action, "AUTOD", 0, "Soltar automático"),
                ["autow"] = new(CondactType.Action, "AUTOW", 0, "Vestir automático"),
                ["autor"] = new(CondactType.Action, "AUTOR", 0, "Quitar automático"),
                ["autop"] = new(CondactType.Action, "AUTOP", 1, "Meter automático"),
                ["autot"] = new(CondactType.Action, "AUTOT", 1, "Sacar automático"),

                // ===== LISTAS DE OBJETOS =====
                ["listobj"] = new(CondactType.Action, "LISTOBJ", 0, "Listar objetos presentes"),
                ["listat"] = new(CondactType.Action, "LISTAT", 1, "Listar objetos en localización"),

                // ===== PARSER AVANZADO =====
                ["adject1"] = new(CondactType.Condition, "ADJECT1", 1, "Primer adjetivo"),
                ["adject2"] = new(CondactType.Condition, "ADJECT2", 1, "Segundo adjetivo"),
                ["adverb"] = new(CondactType.Condition, "ADVERB", 1, "Adverbio"),
                ["prep"] = new(CondactType.Condition, "PREP", 1, "Preposición"),
                ["noun2"] = new(CondactType.Condition, "NOUN2", 1, "Segundo sustantivo"),

                // ===== COMPARACIONES =====
                ["noteq"] = new(CondactType.Condition, "NOTEQ", 2, "No igual"),
                ["notsame"] = new(CondactType.Condition, "NOTSAME", 2, "No mismo"),
                ["bigger"] = new(CondactType.Condition, "BIGGER", 2, "Mayor que"),
                ["smaller"] = new(CondactType.Condition, "SMALLER", 2, "Menor que"),
                ["isnotat"] = new(CondactType.Condition, "ISNOTAT", 2, "Objeto NO en localización"),

                // ===== ESTADO DE PROCESOS =====
                ["isdone"] = new(CondactType.Condition, "ISDONE", 0, "Proceso terminó exitosamente"),
                ["isndone"] = new(CondactType.Condition, "ISNDONE", 0, "Proceso terminó sin éxito"),
                ["notdone"] = new(CondactType.Action, "NOTDONE", 0, "Marcar proceso como no exitoso"),

                // ===== CONTROL DE FLUJO =====
                ["skip"] = new(CondactType.Action, "SKIP", 1, "Saltar N CondActs"),
                ["move"] = new(CondactType.Action, "MOVE", 1, "Mover usando conexiones"),

                // ===== MULTIMEDIA =====
                ["beep"] = new(CondactType.Action, "BEEP", 0, "Sonido básico"),
                ["picture"] = new(CondactType.Action, "PICTURE", 1, "Mostrar imagen"),
                ["sfx"] = new(CondactType.Action, "SFX", 1, "Efecto de sonido"),

                // ===== PANTALLA Y VENTANAS =====
                ["window"] = new(CondactType.Action, "WINDOW", 1, "Seleccionar ventana"),
                ["winat"] = new(CondactType.Action, "WINAT", 2, "Posicionar ventana"),
                ["winsize"] = new(CondactType.Action, "WINSIZE", 2, "Tamaño ventana"),
                ["centre"] = new(CondactType.Action, "CENTRE", 0, "Centrar ventana"),
                ["paper"] = new(CondactType.Action, "PAPER", 1, "Color fondo"),
                ["ink"] = new(CondactType.Action, "INK", 1, "Color tinta"),
                ["border"] = new(CondactType.Action, "BORDER", 1, "Color borde"),

                // ===== IMPRESIÓN =====
                ["dprint"] = new(CondactType.Action, "DPRINT", 1, "Imprimir doble byte"),
                ["printat"] = new(CondactType.Action, "PRINTAT", 2, "Imprimir en posición"),
                ["tab"] = new(CondactType.Action, "TAB", 1, "Tabular"),
                ["space"] = new(CondactType.Action, "SPACE", 0, "Imprimir espacio"),
                ["mes"] = new(CondactType.Action, "MES", 1, "Mensaje sin nueva línea"),

                // ===== UTILIDADES =====
                ["anykey"] = new(CondactType.Action, "ANYKEY", 0, "Esperar tecla"),
                ["pause"] = new(CondactType.Action, "PAUSE", 1, "Pausa en frames"),
                ["time"] = new(CondactType.Action, "TIME", 2, "Configurar timeout"),
                ["input"] = new(CondactType.Action, "INPUT", 2, "Configurar entrada"),
                ["inkey"] = new(CondactType.Condition, "INKEY", 0, "Tecla presionada"),

                // ===== OBJETOS AVANZADO =====
                ["whato"] = new(CondactType.Action, "WHATO", 0, "Buscar objeto por sustantivo"),
                ["setco"] = new(CondactType.Action, "SETCO", 1, "Establecer objeto actual"),
                ["weigh"] = new(CondactType.Action, "WEIGH", 2, "Pesar objeto"),
                ["weight"] = new(CondactType.Action, "WEIGHT", 1, "Peso total jugador"),
                ["ability"] = new(CondactType.Action, "ABILITY", 2, "Configurar capacidades"),
                ["swap"] = new(CondactType.Action, "SWAP", 2, "Intercambiar objetos"),
                ["dropall"] = new(CondactType.Action, "DROPALL", 0, "Soltar todo"),
                ["puto"] = new(CondactType.Action, "PUTO", 1, "Mover objeto actual"),

                // ===== FLAGS Y CÁLCULOS =====
                ["add"] = new(CondactType.Action, "ADD", 2, "Sumar flags"),
                ["sub"] = new(CondactType.Action, "SUB", 2, "Restar flags"),
                ["random"] = new(CondactType.Action, "RANDOM", 1, "Número aleatorio"),

                // ===== SISTEMA =====
                ["mode"] = new(CondactType.Action, "MODE", 1, "Modo pantalla"),
                ["reset"] = new(CondactType.Action, "RESET", 0, "Reiniciar objetos"),
                ["exit"] = new(CondactType.Action, "EXIT", 0, "Salir a sistema"),
                ["ok"] = new(CondactType.Action, "OK", 0, "Marcar OK"),
                ["newtext"] = new(CondactType.Action, "NEWTEXT", 0, "Limpiar buffer texto"),
                ["display"] = new(CondactType.Action, "DISPLAY", 1, "Mostrar pantalla"),
                ["call"] = new(CondactType.Action, "CALL", 1, "Llamar rutina"),
                ["synonym"] = new(CondactType.Action, "SYNONYM", 2, "Definir sinónimo"),

                // ===== GUARDADO AVANZADO =====
                ["ramsave"] = new(CondactType.Action, "RAMSAVE", 0, "Guardar en RAM"),
                ["ramload"] = new(CondactType.Action, "RAMLOAD", 0, "Cargar de RAM"),
                ["saveat"] = new(CondactType.Action, "SAVEAT", 0, "Guardar posición cursor"),
                ["backat"] = new(CondactType.Action, "BACKAT", 0, "Restaurar posición cursor"),

                // ===== GRÁFICOS =====
                ["gfx"] = new(CondactType.Action, "GFX", 1, "Comando gráfico"),
                ["mouse"] = new(CondactType.Action, "MOUSE", 0, "Leer ratón"),

                // ===== OTROS =====
                ["redo"] = new(CondactType.Action, "REDO", 0, "Rehacer comando")
            };
        }

        /// <summary>
        /// Obtiene todos los CondActs implementados (originales + nuevos)
        /// </summary>
        public Dictionary<string, object> GetImplementedCondacts()
        {
            var implemented = new Dictionary<string, object>();

            // CondActs básicos ya implementados (los 82 originales)
            var basicCondacts = GetBasicImplementedCondacts();
            foreach (var condact in basicCondacts)
            {
                implemented[condact.Key] = condact.Value;
            }

            // CondActs críticos nuevos
            foreach (var condact in _criticalCondacts)
            {
                implemented[condact.Key] = condact.Value;
            }

            return implemented;
        }

        /// <summary>
        /// CondActs básicos ya implementados (placeholder - implementar según código existente)
        /// </summary>
        private Dictionary<string, object> GetBasicImplementedCondacts()
        {
            return new Dictionary<string, object>
            {
                // Condiciones básicas implementadas
                ["at"] = new { Type = "Condition", Params = 1 },
                ["notat"] = new { Type = "Condition", Params = 1 },
                ["present"] = new { Type = "Condition", Params = 1 },
                ["absent"] = new { Type = "Condition", Params = 1 },
                ["worn"] = new { Type = "Condition", Params = 1 },
                ["notworn"] = new { Type = "Condition", Params = 1 },
                ["carried"] = new { Type = "Condition", Params = 1 },
                ["notcarr"] = new { Type = "Condition", Params = 1 },
                ["zero"] = new { Type = "Condition", Params = 1 },
                ["notzero"] = new { Type = "Condition", Params = 1 },
                ["eq"] = new { Type = "Condition", Params = 2 },
                ["gt"] = new { Type = "Condition", Params = 2 },
                ["lt"] = new { Type = "Condition", Params = 2 },
                ["chance"] = new { Type = "Condition", Params = 1 },
                ["same"] = new { Type = "Condition", Params = 2 },
                ["isat"] = new { Type = "Condition", Params = 2 },

                // Acciones básicas implementadas
                ["goto"] = new { Type = "Action", Params = 1 },
                ["get"] = new { Type = "Action", Params = 1 },
                ["drop"] = new { Type = "Action", Params = 1 },
                ["wear"] = new { Type = "Action", Params = 1 },
                ["remove"] = new { Type = "Action", Params = 1 },
                ["message"] = new { Type = "Action", Params = 1 },
                ["restart"] = new { Type = "Action", Params = 0 },
                ["end"] = new { Type = "Action", Params = 0 },
                ["done"] = new { Type = "Action", Params = 0 },
                ["set"] = new { Type = "Action", Params = 1 },
                ["clear"] = new { Type = "Action", Params = 1 },
                ["let"] = new { Type = "Action", Params = 2 },
                ["plus"] = new { Type = "Action", Params = 2 },
                ["minus"] = new { Type = "Action", Params = 2 },
                ["create"] = new { Type = "Action", Params = 1 },
                ["destroy"] = new { Type = "Action", Params = 1 },
                ["place"] = new { Type = "Action", Params = 2 },
                ["cls"] = new { Type = "Action", Params = 0 },
                ["desc"] = new { Type = "Action", Params = 1 },
                ["print"] = new { Type = "Action", Params = 1 },
                ["newline"] = new { Type = "Action", Params = 0 }
                // ... (resto de los 82 implementados)
            };
        }

        /// <summary>
        /// Obtiene lista de CondActs soportados
        /// </summary>
        public IEnumerable<string> GetSupportedCondactos()
        {
            return GetImplementedCondacts().Keys;
        }

        /// <summary>
        /// Verifica si un CondAct está implementado
        /// </summary>
        public bool IsCondactImplemented(string condactName)
        {
            return GetImplementedCondacts().ContainsKey(condactName.ToLower());
        }

        /// <summary>
        /// Obtiene información sobre un CondAct
        /// </summary>
        public CondactInfo? GetCondactInfo(string condactName)
        {
            var key = condactName.ToLower();
            return _criticalCondacts.ContainsKey(key) ? _criticalCondacts[key] : null;
        }

        /// <summary>
        /// Obtiene todos los CondActs críticos para integración con el transpilador
        /// </summary>
        public static Dictionary<string, CondactInfo> GetCriticalCondacts()
        {
            return InitializeCriticalCondacts();
        }
    }

    /// <summary>
    /// Información sobre un CondAct
    /// </summary>
    public record CondactInfo(
        CondactType Type,
        string Name,
        int ParameterCount,
        string Description
    );

    /// <summary>
    /// Tipo de CondAct
    /// </summary>
    public enum CondactType
    {
        Condition,
        Action
    }
}
