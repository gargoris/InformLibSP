using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Extensions.Logging;
using DaadModern.Models;
using DaadModern.Interfaces;

namespace DaadModern.Services
{
    public class TimeManager
    {
        private readonly ILogger<TimeManager> _logger;
        public List<string> ProcessedEvents { get; private set; } = new();

        public TimeManager(ILogger<TimeManager> logger)
        {
            _logger = logger;
        }

        public async Task<DaadAst> ProcessTimeSystem(DaadAst ast)
        {
            _logger.LogInformation("Procesando sistema de tiempo...");
            
            var processedAst = ast.Clone();
            ProcessedEvents.Clear();

            foreach (var command in processedAst.Commands.Where(c => c.Type == Models.CommandType.Modern && c.Name.StartsWith("TIME_")))
            {
                var timeCommand = await ProcessTimeCommand(command);
                var index = processedAst.Commands.IndexOf(command);
                processedAst.Commands[index] = timeCommand;
                ProcessedEvents.Add(command.Parameters[0].Value);
            }

            return processedAst;
        }

        private async Task<DaadCommand> ProcessTimeCommand(DaadCommand modernCommand)
        {
            return modernCommand.Name switch
            {
                "TIME_EVENT" => await ConvertTimeEvent(modernCommand),
                "TIME_DELAY" => await ConvertTimeDelay(modernCommand),
                "TIME_CONDITION" => await ConvertTimeCondition(modernCommand),
                _ => modernCommand
            };
        }

        private Task<DaadCommand> ConvertTimeEvent(DaadCommand command)
        {
            var eventType = command.Parameters[0].Value;
            var condition = command.Parameters[1].Value;
            
            return Task.FromResult(new DaadCommand
            {
                Name = "TIMEOUT",
                Type = Models.CommandType.Action,
                Parameters = new List<DaadParameter>
                {
                    new DaadParameter { Type = ParameterType.Number, Value = GetTimeoutValue(eventType) }
                }
            });
        }

        private Task<DaadCommand> ConvertTimeDelay(DaadCommand command)
        {
            var delay = command.Parameters[0].Value;
            
            return Task.FromResult(new DaadCommand
            {
                Name = "PAUSE",
                Type = Models.CommandType.Action,
                Parameters = new List<DaadParameter>
                {
                    new DaadParameter { Type = ParameterType.Number, Value = delay }
                }
            });
        }

        private Task<DaadCommand> ConvertTimeCondition(DaadCommand command)
        {
            var condition = command.Parameters[0].Value;
            
            return Task.FromResult(new DaadCommand
            {
                Name = "GT",
                Type = Models.CommandType.Condition,
                Parameters = new List<DaadParameter>
                {
                    new DaadParameter { Type = ParameterType.Flag, Value = "TIMER" },
                    new DaadParameter { Type = ParameterType.Number, Value = condition }
                }
            });
        }

        private static string GetTimeoutValue(string eventType)
        {
            return eventType switch
            {
                "FAST" => "10",
                "MEDIUM" => "50",
                "SLOW" => "100",
                _ => "25"
            };
        }

        public Task<string> GenerateClassicTimeCode(string eventType, string condition, TranspileContext context, TranspileOptions options)
        {
            var result = new StringBuilder();
            
            result.AppendLine($"; Evento de tiempo: {eventType}");
            result.AppendLine($"TIMEOUT {GetTimeoutValue(eventType)}");
            result.AppendLine($"GT TIMER {condition}");
            result.AppendLine("GOSUB TIME_EVENT");
            
            return Task.FromResult(result.ToString());
        }
    }
}
