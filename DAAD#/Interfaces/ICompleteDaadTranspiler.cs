using System;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace DaadModern.Interfaces
{
    public interface ICompleteDaadTranspiler
    {
        Task<TranspileResult> TranspileAsync(string modernCode, TranspileOptions options);
        Task<CompatibilityReport> CheckCompatibilityAsync(string modernCode);
        IEnumerable<string> GetSupportedCondactos();
        CondactoInfo GetCondactoInfo(string condactoName);
    }

    // ===== CLASES AUXILIARES =====

    /// <summary>
    /// Opciones para la transpilación
    /// </summary>
    public class TranspileOptions
    {
        public bool IncludeHeader { get; set; } = true;
        public bool IncludeFooter { get; set; } = true;
        public bool OptimizeCode { get; set; } = false;
        public bool IncludeComments { get; set; } = true;
    }

    /// <summary>
    /// Resultado de la transpilación
    /// </summary>
    public class TranspileResult
    {
        public bool Success { get; set; }
        public string Output { get; set; } = string.Empty;
        public List<TranspileError> Errors { get; set; } = new();
        public TranspileStatistics Statistics { get; set; } = new();
    }

    /// <summary>
    /// Error durante la transpilación
    /// </summary>
    public class TranspileError
    {
        public string Message { get; set; } = string.Empty;
        public int Line { get; set; }
        public int Column { get; set; }
        public string Severity { get; set; } = "Error";
    }

    /// <summary>
    /// Estadísticas de transpilación
    /// </summary>
    public class TranspileStatistics
    {
        public int InputLines { get; set; }
        public int OutputLines { get; set; }
        public int CondactosUsed { get; set; }
        public TimeSpan ProcessingTime { get; set; }
    }

    /// <summary>
    /// Reporte de compatibilidad
    /// </summary>
    public class CompatibilityReport
    {
        public bool IsCompatible { get; set; }
        public double CompatibilityPercentage { get; set; }
        public List<CompatibilityIssue> Issues { get; set; } = new();
    }

    /// <summary>
    /// Problema de compatibilidad
    /// </summary>
    public class CompatibilityIssue
    {
        public string Message { get; set; } = string.Empty;
        public CompatibilityIssueSeverity Severity { get; set; } = CompatibilityIssueSeverity.Warning;
        public int Line { get; set; }
        public int Column { get; set; }
    }

    /// <summary>
    /// Severidad de los problemas de compatibilidad
    /// </summary>
    public enum CompatibilityIssueSeverity
    {
        Info,
        Warning,
        Error
    }

    public class CondactoInfo
    {
        public string ModernName { get; set; }
        public string ClassicName { get; set; }
        public CommandType Type { get; set; }
        public ParamType[] Parameters { get; set; }

        public CondactoInfo(string modernName, string classicName, CommandType type, ParamType[] parameters)
        {
            ModernName = modernName;
            ClassicName = classicName;
            Type = type;
            Parameters = parameters;
        }
    }

    public enum ParamType
    {
        Number,
        Flag,
        Location,
        Object,
        Message,
        Process,
        Word,
        String
    }

    public enum CommandType
    {
        Condition,
        Action,
        Flow,
        Modern
    }

    public class TranspileContext
    {
        public Dictionary<string, object> Variables { get; set; } = new();
        public int CurrentLine { get; set; }
        public string CurrentProcess { get; set; } = string.Empty;
    }

    public class TranspileException : Exception
    {
        public TranspileException(string message) : base(message) { }
        public TranspileException(string message, Exception innerException) : base(message, innerException) { }
    }
}
