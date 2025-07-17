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
    public class NpcManager
    {
        private readonly ILogger<NpcManager> _logger;
        public List<string> ProcessedNpcs { get; private set; } = new();

        public NpcManager(ILogger<NpcManager> logger)
        {
            _logger = logger;
        }

        public async Task<DaadAst> ProcessAdvancedNpcs(DaadAst ast)
        {
            _logger.LogInformation("Procesando NPCs avanzados...");
            
            var processedAst = ast.Clone();
            ProcessedNpcs.Clear();

            foreach (var command in processedAst.Commands.Where(c => c.Type == Models.CommandType.Modern && c.Name.StartsWith("NPC_")))
            {
                var npcCommand = await ProcessNpcCommand(command);
                var index = processedAst.Commands.IndexOf(command);
                processedAst.Commands[index] = npcCommand;
                ProcessedNpcs.Add(command.Parameters[0].Value);
            }

            return processedAst;
        }

        private async Task<DaadCommand> ProcessNpcCommand(DaadCommand modernCommand)
        {
            return modernCommand.Name switch
            {
                "NPC_INTERACT" => await ConvertNpcInteract(modernCommand),
                "NPC_DIALOGUE" => await ConvertNpcDialogue(modernCommand),
                "NPC_BEHAVIOR" => await ConvertNpcBehavior(modernCommand),
                _ => modernCommand
            };
        }

        private Task<DaadCommand> ConvertNpcInteract(DaadCommand command)
        {
            var npcId = command.Parameters[0].Value;
            var action = command.Parameters[1].Value;
            
            return Task.FromResult(new DaadCommand
            {
                Name = "PROCESS",
                Type = Models.CommandType.Action,
                Parameters = new List<DaadParameter>
                {
                    new DaadParameter { Type = ParameterType.Process, Value = $"NPC_{npcId}_{action}" }
                }
            });
        }

        private Task<DaadCommand> ConvertNpcDialogue(DaadCommand command)
        {
            var npcId = command.Parameters[0].Value;
            
            return Task.FromResult(new DaadCommand
            {
                Name = "GOSUB",
                Type = Models.CommandType.Flow,
                Parameters = new List<DaadParameter>
                {
                    new DaadParameter { Type = ParameterType.Process, Value = $"DIALOGUE_{npcId}" }
                }
            });
        }

        private Task<DaadCommand> ConvertNpcBehavior(DaadCommand command)
        {
            var npcId = command.Parameters[0].Value;
            var behavior = command.Parameters[1].Value;
            
            return Task.FromResult(new DaadCommand
            {
                Name = "PROCESS",
                Type = Models.CommandType.Action,
                Parameters = new List<DaadParameter>
                {
                    new DaadParameter { Type = ParameterType.Process, Value = $"BEHAVIOR_{npcId}_{behavior}" }
                }
            });
        }

        public Task<string> GenerateClassicNpcCode(string npcId, string action, TranspileContext context, TranspileOptions options)
        {
            var result = new StringBuilder();
            
            result.AppendLine($"; NPC {npcId} - {action}");
            result.AppendLine($"PROCESS NPC_{npcId}_{action}");
            result.AppendLine($"  AT {GetNpcLocation()}");
            result.AppendLine($"  PRESENT {GetNpcObject(npcId)}");
            result.AppendLine($"  GOSUB {action}_{npcId}");
            result.AppendLine("END");
            
            return Task.FromResult(result.ToString());
        }

        private static string GetNpcLocation()
        {
            return "1"; // Placeholder
        }

        private static string GetNpcObject(string npcId)
        {
            return "NPC_" + npcId;
        }
    }
}
