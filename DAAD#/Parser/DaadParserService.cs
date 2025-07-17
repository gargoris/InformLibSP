using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.Extensions.Logging;
using DaadModern.Models;
using DaadModern.Parser;

namespace DaadModern.Parser
{
    public class DaadParserService : IDaadParser
    {
        private readonly ILogger<DaadParserService> _logger;

        public DaadParserService(ILogger<DaadParserService> logger)
        {
            _logger = logger;
        }

        public async Task<ParseResult> ParseAsync(string input)
        {
            try
            {
                _logger.LogInformation("Iniciando parsing del código DAAD moderno");
                
                var result = await Task.Run(() => DaadParser.Program.Parse(input));
                
                if (result.Success)
                {
                    var ast = ConvertToInternalAst(result.Value);
                    
                    _logger.LogInformation("Parsing completado exitosamente. Secciones: {Count}", 
                        result.Value.Sections.Count);
                    
                    return new ParseResult
                    {
                        Success = true,
                        Ast = ast,
                        Errors = new List<ParseError>()
                    };
                }
                else
                {
                    _logger.LogError("Error de parsing en posición {Position}: {Message}",
                        result.Error?.Position, result.Error?.Message);
                    
                    return new ParseResult
                    {
                        Success = false,
                        Ast = new DaadAst(),
                        Errors = new List<ParseError>
                        {
                            new ParseError
                            {
                                Line = result.Error?.Position.Line ?? 0,
                                Column = result.Error?.Position.Col ?? 0,
                                Message = result.Error?.Message ?? "Error desconocido",
                                Code = "PARSE_ERROR"
                            }
                        }
                    };
                }
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Excepción durante el parsing");
                
                return new ParseResult
                {
                    Success = false,
                    Ast = new DaadAst(),
                    Errors = new List<ParseError>
                    {
                        new ParseError
                        {
                            Message = ex.Message,
                            Code = "PARSE_EXCEPTION"
                        }
                    }
                };
            }
        }

        private DaadAst ConvertToInternalAst(DaadProgram program)
        {
            var ast = new DaadAst();
            
            foreach (var section in program.Sections)
            {
                switch (section)
                {
                    case ResponseSection responseSection:
                        ast.Commands.AddRange(ConvertResponsesToCommands(responseSection.Responses));
                        break;
                    case GameSection gameSection:
                        ast.Commands.AddRange(ConvertGamePropertiesToCommands(gameSection.Properties));
                        break;
                    case LocationSection locationSection:
                        ast.Commands.AddRange(ConvertLocationToCommands(locationSection));
                        break;
                    case ObjectSection objectSection:
                        ast.Commands.AddRange(ConvertObjectToCommands(objectSection));
                        break;
                    case VocabSection vocabSection:
                        ast.Commands.AddRange(ConvertVocabToCommands(vocabSection.Entries));
                        break;
                }
            }
            
            return ast;
        }

        private List<DaadCommand> ConvertResponsesToCommands(List<Response> responses)
        {
            var commands = new List<DaadCommand>();
            
            foreach (var response in responses)
            {
                var responseCommand = new DaadCommand
                {
                    Name = "RESPONSE",
                    Type = CommandType.Action,
                    Parameters = new List<DaadParameter>
                    {
                        new DaadParameter
                        {
                            Type = ParameterType.String,
                            Value = string.Join(" ", response.Patterns)
                        }
                    }
                };
                
                commands.Add(responseCommand);
                
                if (response.Condition != null)
                {
                    commands.AddRange(ConvertConditionToCommands(response.Condition));
                }
                
                commands.AddRange(ConvertActionsToCommands(response.Actions));
                
                commands.Add(new DaadCommand
                {
                    Name = "DONE",
                    Type = CommandType.Action,
                    Parameters = new List<DaadParameter>()
                });
            }
            
            return commands;
        }

        private List<DaadCommand> ConvertConditionToCommands(Condition condition)
        {
            var commands = new List<DaadCommand>();
            
            switch (condition)
            {
                case SimpleCondition simple:
                    commands.Add(new DaadCommand
                    {
                        Name = MapConditionFunction(simple.Function),
                        Type = CommandType.Condition,
                        Parameters = ConvertValuesToParameters(simple.Args)
                    });
                    break;
                    
                case CompoundCondition compound:
                    commands.AddRange(ConvertConditionToCommands(compound.Left));
                    commands.AddRange(ConvertConditionToCommands(compound.Right));
                    break;
            }
            
            return commands;
        }

        private List<DaadCommand> ConvertActionsToCommands(List<Action> actions)
        {
            var commands = new List<DaadCommand>();
            
            foreach (var action in actions)
            {
                switch (action)
                {
                    case SimpleAction simple:
                        commands.Add(new DaadCommand
                        {
                            Name = MapActionFunction(simple.Function),
                            Type = CommandType.Action,
                            Parameters = ConvertValuesToParameters(simple.Args)
                        });
                        break;
                        
                    case BlockAction block:
                        commands.AddRange(ConvertActionsToCommands(block.Actions));
                        break;
                }
            }
            
            return commands;
        }

        private List<DaadParameter> ConvertValuesToParameters(List<Value> values)
        {
            var parameters = new List<DaadParameter>();
            
            foreach (var value in values)
            {
                switch (value)
                {
                    case StringValue str:
                        parameters.Add(new DaadParameter
                        {
                            Type = ParameterType.String,
                            Value = str.Text
                        });
                        break;
                        
                    case NumberValue num:
                        parameters.Add(new DaadParameter
                        {
                            Type = ParameterType.Number,
                            Value = num.Number.ToString()
                        });
                        break;
                        
                    case IdentifierValue id:
                        parameters.Add(new DaadParameter
                        {
                            Type = ParameterType.Object,
                            Value = id.Id
                        });
                        break;
                        
                    case BoolValue boolean:
                        parameters.Add(new DaadParameter
                        {
                            Type = ParameterType.Number,
                            Value = boolean.Value ? "1" : "0"
                        });
                        break;
                        
                    case ListValue list:
                        parameters.AddRange(ConvertValuesToParameters(list.Items));
                        break;
                }
            }
            
            return parameters;
        }

        private static string MapConditionFunction(string modernFunction)
        {
            return modernFunction.ToUpperInvariant() switch
            {
                "PRESENTE" => "PRESENT",
                "AUSENTE" => "ABSENT",
                "LLEVADO" => "CARRIED",
                "VESTIDO" => "WORN",
                "EN" => "AT",
                "IGUAL" => "EQ",
                "MAYOR" => "GT",
                "MENOR" => "LT",
                "CERO" => "ZERO",
                "NO_CERO" => "NOTZERO",
                _ => modernFunction.ToUpperInvariant()
            };
        }

        private static string MapActionFunction(string modernFunction)
        {
            return modernFunction.ToUpperInvariant() switch
            {
                "COGER" => "GET",
                "SOLTAR" => "DROP",
                "PONER" => "WEAR",
                "QUITAR" => "REMOVE",
                "IR" => "GOTO",
                "DECIR" => "WRITE",
                "ESCRIBIR" => "WRITE",
                "INVENTARIO" => "INVEN",
                "DESCRIBIR" => "DESC",
                "TERMINAR" => "END",
                "SALIR" => "QUIT",
                "PONER_BANDERA" => "SET",
                "QUITAR_BANDERA" => "CLEAR",
                "SUMAR" => "PLUS",
                "RESTAR" => "MINUS",
                _ => modernFunction.ToUpperInvariant()
            };
        }

        private List<DaadCommand> ConvertGamePropertiesToCommands(List<GameProperty> properties)
        {
            var commands = new List<DaadCommand>();
            
            foreach (var prop in properties)
            {
                commands.Add(new DaadCommand
                {
                    Name = "SET_GAME_PROPERTY",
                    Type = CommandType.Action,
                    Parameters = new List<DaadParameter>
                    {
                        new DaadParameter { Type = ParameterType.String, Value = prop.Name },
                        new DaadParameter { Type = ParameterType.String, Value = ConvertValueToString(prop.Value) }
                    }
                });
            }
            
            return commands;
        }

        private List<DaadCommand> ConvertLocationToCommands(LocationSection location)
        {
            var commands = new List<DaadCommand>();
            
            commands.Add(new DaadCommand
            {
                Name = "DEFINE_LOCATION",
                Type = CommandType.Action,
                Parameters = new List<DaadParameter>
                {
                    new DaadParameter { Type = ParameterType.Location, Value = location.Id }
                }
            });
            
            foreach (var prop in location.Properties)
            {
                commands.Add(new DaadCommand
                {
                    Name = "SET_LOCATION_PROPERTY",
                    Type = CommandType.Action,
                    Parameters = new List<DaadParameter>
                    {
                        new DaadParameter { Type = ParameterType.Location, Value = location.Id },
                        new DaadParameter { Type = ParameterType.String, Value = prop.Name },
                        new DaadParameter { Type = ParameterType.String, Value = ConvertValueToString(prop.Value) }
                    }
                });
            }
            
            return commands;
        }

        private List<DaadCommand> ConvertObjectToCommands(ObjectSection obj)
        {
            var commands = new List<DaadCommand>();
            
            commands.Add(new DaadCommand
            {
                Name = "DEFINE_OBJECT",
                Type = CommandType.Action,
                Parameters = new List<DaadParameter>
                {
                    new DaadParameter { Type = ParameterType.Object, Value = obj.Id }
                }
            });
            
            foreach (var prop in obj.Properties)
            {
                commands.Add(new DaadCommand
                {
                    Name = "SET_OBJECT_PROPERTY",
                    Type = CommandType.Action,
                    Parameters = new List<DaadParameter>
                    {
                        new DaadParameter { Type = ParameterType.Object, Value = obj.Id },
                        new DaadParameter { Type = ParameterType.String, Value = prop.Name },
                        new DaadParameter { Type = ParameterType.String, Value = ConvertValueToString(prop.Value) }
                    }
                });
            }
            
            return commands;
        }

        private List<DaadCommand> ConvertVocabToCommands(List<VocabEntry> entries)
        {
            var commands = new List<DaadCommand>();
            
            foreach (var entry in entries)
            {
                commands.Add(new DaadCommand
                {
                    Name = "DEFINE_VOCAB",
                    Type = CommandType.Action,
                    Parameters = new List<DaadParameter>
                    {
                        new DaadParameter { Type = ParameterType.Word, Value = entry.Word },
                        new DaadParameter { Type = ParameterType.Number, Value = entry.Number.ToString() },
                        new DaadParameter { Type = ParameterType.String, Value = entry.Type }
                    }
                });
            }
            
            return commands;
        }

        private string ConvertValueToString(Value value)
        {
            return value switch
            {
                StringValue str => str.Text,
                NumberValue num => num.Number.ToString(),
                BoolValue boolean => boolean.Value.ToString(),
                IdentifierValue id => id.Id,
                ListValue list => string.Join(",", list.Items.Select(ConvertValueToString)),
                MapValue map => string.Join(",", map.Items.Select(kvp => $"{kvp.Key}:{ConvertValueToString(kvp.Value)}")),
                _ => value.ToString() ?? ""
            };
        }
    }
}
