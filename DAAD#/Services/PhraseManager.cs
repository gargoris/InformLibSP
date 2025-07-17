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
    public class PhraseManager
    {
        private readonly ILogger<PhraseManager> _logger;
        public List<string> ProcessedPhrases { get; private set; } = new();

        public PhraseManager(ILogger<PhraseManager> logger)
        {
            _logger = logger;
        }

        public async Task<DaadAst> ProcessMultiplePhrases(DaadAst ast)
        {
            _logger.LogInformation("Procesando frases múltiples...");
            
            var processedAst = ast.Clone();
            ProcessedPhrases.Clear();

            foreach (var command in processedAst.Commands.Where(c => c.Type == Models.CommandType.Modern && c.Name.StartsWith("MULTI_")))
            {
                var phraseCommands = await ProcessPhraseCommand(command);
                var index = processedAst.Commands.IndexOf(command);
                
                processedAst.Commands.RemoveAt(index);
                processedAst.Commands.InsertRange(index, phraseCommands);
                
                ProcessedPhrases.Add(command.Parameters[0].Value);
            }

            return processedAst;
        }

        private async Task<List<DaadCommand>> ProcessPhraseCommand(DaadCommand modernCommand)
        {
            return modernCommand.Name switch
            {
                "MULTI_PHRASE" => await ConvertMultiPhrase(modernCommand),
                "MULTI_RESPONSE" => await ConvertMultiResponse(modernCommand),
                "MULTI_CONDITION" => await ConvertMultiCondition(modernCommand),
                _ => new List<DaadCommand> { modernCommand }
            };
        }

        private Task<List<DaadCommand>> ConvertMultiPhrase(DaadCommand command)
        {
            var phrases = command.Parameters.Select(p => p.Value).ToArray();
            var commands = new List<DaadCommand>();
            
            commands.Add(new DaadCommand
            {
                Name = "RANDOM",
                Type = Models.CommandType.Action,
                Parameters = new List<DaadParameter>
                {
                    new DaadParameter { Type = ParameterType.Flag, Value = "PHRASE_SELECTOR" }
                }
            });

            for (int i = 0; i < phrases.Length; i++)
            {
                commands.Add(new DaadCommand
                {
                    Name = "EQ",
                    Type = Models.CommandType.Condition,
                    Parameters = new List<DaadParameter>
                    {
                        new DaadParameter { Type = ParameterType.Flag, Value = "PHRASE_SELECTOR" },
                        new DaadParameter { Type = ParameterType.Number, Value = i.ToString() }
                    }
                });

                commands.Add(new DaadCommand
                {
                    Name = "WRITE",
                    Type = Models.CommandType.Action,
                    Parameters = new List<DaadParameter>
                    {
                        new DaadParameter { Type = ParameterType.Message, Value = phrases[i] }
                    }
                });
            }

            return Task.FromResult(commands);
        }

        private Task<List<DaadCommand>> ConvertMultiResponse(DaadCommand command)
        {
            var responses = command.Parameters.Select(p => p.Value).ToArray();
            var commands = new List<DaadCommand>();
            
            commands.Add(new DaadCommand
            {
                Name = "RANDOM",
                Type = Models.CommandType.Action,
                Parameters = new List<DaadParameter>
                {
                    new DaadParameter { Type = ParameterType.Flag, Value = "RESPONSE_SELECTOR" }
                }
            });

            for (int i = 0; i < responses.Length; i++)
            {
                commands.Add(new DaadCommand
                {
                    Name = "EQ",
                    Type = Models.CommandType.Condition,
                    Parameters = new List<DaadParameter>
                    {
                        new DaadParameter { Type = ParameterType.Flag, Value = "RESPONSE_SELECTOR" },
                        new DaadParameter { Type = ParameterType.Number, Value = i.ToString() }
                    }
                });

                commands.Add(new DaadCommand
                {
                    Name = "WRITE",
                    Type = Models.CommandType.Action,
                    Parameters = new List<DaadParameter>
                    {
                        new DaadParameter { Type = ParameterType.Message, Value = responses[i] }
                    }
                });
            }

            return Task.FromResult(commands);
        }

        private Task<List<DaadCommand>> ConvertMultiCondition(DaadCommand command)
        {
            var conditions = command.Parameters.Select(p => p.Value).ToArray();
            var commands = new List<DaadCommand>();
            
            for (int i = 0; i < conditions.Length; i++)
            {
                commands.Add(new DaadCommand
                {
                    Name = "PROCESS",
                    Type = Models.CommandType.Action,
                    Parameters = new List<DaadParameter>
                    {
                        new DaadParameter { Type = ParameterType.Process, Value = $"CONDITION_{i}" }
                    }
                });
            }

            return Task.FromResult(commands);
        }

        public Task<string> GenerateClassicPhraseCode(string[] phrases, TranspileContext context, TranspileOptions options)
        {
            var result = new StringBuilder();
            
            result.AppendLine("; Frases múltiples");
            result.AppendLine("RANDOM PHRASE_SELECTOR");
            
            for (int i = 0; i < phrases.Length; i++)
            {
                result.AppendLine($"EQ PHRASE_SELECTOR {i}");
                result.AppendLine($"WRITE \"{phrases[i]}\"");
            }
            
            return Task.FromResult(result.ToString());
        }
    }
}
