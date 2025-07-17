using System;
using System.Collections.Generic;

namespace DaadModern.Models
{
    public class DaadAst
    {
        public List<DaadCommand> Commands { get; set; } = new();
        public Dictionary<string, object> Metadata { get; set; } = new();

        public DaadAst Clone()
        {
            return new DaadAst
            {
                Commands = new List<DaadCommand>(Commands),
                Metadata = new Dictionary<string, object>(Metadata)
            };
        }
    }

    public class DaadCommand
    {
        public string Name { get; set; } = string.Empty;
        public CommandType Type { get; set; }
        public List<DaadParameter> Parameters { get; set; } = new();
        public int Line { get; set; }
        public int Column { get; set; }
    }

    public class DaadParameter
    {
        public ParameterType Type { get; set; }
        public string Value { get; set; } = string.Empty;
    }

    public enum CommandType
    {
        Condition,
        Action,
        Flow,
        Modern
    }

    public enum ParameterType
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
}
