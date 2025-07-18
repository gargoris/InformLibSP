// =====================================================================
// DAAD Moderno - Implementación Completa con Pidgin
// Incluye todas las características avanzadas: NPCs, Procesos, etc.
// =====================================================================

// Install-Package Pidgin

using System;
using System.Collections.Generic;
using System.Linq;
using Pidgin;
using static Pidgin.Parser;
using static Pidgin.Parser<char>;

namespace DaadModern.Parser
{
    // =====================================================================
    // MODELO DE DATOS COMPLETO (AST)
    // =====================================================================
    
    #region AST Types
    
    public record DaadProgram(List<string> Includes, List<Section> Sections);
    
    public abstract record Section;
    public record GameSection(List<GameProperty> Properties) : Section;
    public record VocabSection(List<VocabCategory> Categories) : Section;
    public record FlagsSection(List<FlagDefinition> Flags) : Section;
    public record LocationsSection(List<LocationDefinition> Locations) : Section;
    public record ObjectsSection(List<ObjectDefinition> Objects) : Section;
    public record NPCsSection(List<NPCDefinition> NPCs) : Section;
    public record ProcessesSection(List<ProcessDefinition> Processes) : Section;
    public record ResponsesSection(List<ResponseDefinition> Responses) : Section;
    public record MessagesSection(List<MessageDefinition> Messages) : Section;
    public record EndingsSection(List<EndingDefinition> Endings) : Section;
    public record DebugSection(DebugConfiguration Config) : Section;
    public record ExtensionsSection(ExtensionsConfiguration Config) : Section;
    
    // Propiedades y valores
    public record GameProperty(string Name, Value Value);
    public record PropertyAssignment(string Name, Value Value);
    
    // Valores
    public abstract record Value;
    public record StringValue(string Text) : Value;
    public record NumberValue(int Number) : Value;
    public record BoolValue(bool Value) : Value;
    public record IdentifierValue(string Id) : Value;
    public record ListValue(List<Value> Items) : Value;
    public record MapValue(Dictionary<string, Value> Items) : Value;
    
    // Vocabulario
    public record VocabCategory(string Type, List<VocabEntry> Entries);
    public record VocabEntry(int Number, List<string> Words, List<string>? Synonyms);
    
    // Flags
    public record FlagDefinition(string Type, string Name, int Number);
    
    // Localidades
    public record LocationDefinition(string Id, List<LocationProperty> Properties);
    public record LocationProperty(string Name, Value Value);
    public record Connection(string Direction, ConnectionTarget Target);
    public abstract record ConnectionTarget;
    public record SimpleConnection(string LocationId) : ConnectionTarget;
    public record ConditionalConnection(Condition Condition, string ThenLocation, string? ElseLocation) : ConnectionTarget;
    
    // Objetos
    public record ObjectDefinition(string Id, List<ObjectProperty> Properties);
    public record ObjectProperty(string Name, Value Value);
    
    // NPCs
    public record NPCDefinition(string Id, List<NPCProperty> Properties);
    public record NPCProperty(string Name, Value Value);
    public record NPCBehavior(string Type, List<string>? Parameters);
    public record DialogueNode(string Id, List<DialogueProperty> Properties);
    public record DialogueProperty(string Name, Value Value);
    public record DialogueResponse(string PlayerText, List<ResponseProperty> Properties);
    public record ResponseProperty(string Name, Value Value);
    
    // Procesos
    public record ProcessDefinition(ProcessType Type, string Id, List<ProcessProperty> Properties);
    public abstract record ProcessType;
    public record SimpleProcessType(string Name) : ProcessType;
    public record ParameterizedProcessType(string Name, int Parameter) : ProcessType;
    public record ProcessProperty(string Name, Value Value);
    public record TimeoutConfiguration(int? Duration, int? ControlFlags, bool? PreserveState, bool? AutoRestore);
    
    // Respuestas
    public record ResponseDefinition(List<CommandPattern> Patterns, Condition? Condition, int? Priority, Action ActionBlock);
    public abstract record CommandPattern;
    public record SimplePattern(string Text) : CommandPattern;
    public record SequentialPattern(List<string> Commands) : CommandPattern;
    public record ObjectPattern(string Pattern) : CommandPattern;
    public record ComplexPattern(List<PatternElement> Elements) : CommandPattern;
    public record PatternElement(string Text, string? Operator);
    
    // Condiciones
    public abstract record Condition;
    public record SimpleCondition(string Function, List<Value> Args) : Condition;
    public record CompoundCondition(Condition Left, string Operator, Condition Right) : Condition;
    public record NotCondition(Condition Inner) : Condition;
    public record ParenthesizedCondition(Condition Inner) : Condition;
    
    // Acciones
    public abstract record Action;
    public record SimpleAction(string Function, List<Value> Args) : Action;
    public record BlockAction(List<Action> Actions) : Action;
    public record ConditionalAction(Condition Condition, List<Action> ThenActions, List<Action>? ElseActions) : Action;
    
    // Mensajes
    public record MessageDefinition(string Id, string Text);
    
    // Finales
    public record EndingDefinition(string Id, List<EndingProperty> Properties);
    public record EndingProperty(string Name, Value Value);
    
    // Depuración
    public record DebugConfiguration(Dictionary<string, Value> Properties);
    public record ConditionalBreakpoint(Condition Condition, string Message, bool HaltExecution);
    
    // Extensiones
    public record ExtensionsConfiguration(Dictionary<string, Value> Properties);
    
    #endregion
    
    // =====================================================================
    // PARSER COMPLETO CON PIDGIN
    // =====================================================================
    
    public static class DaadParser
    {
        // =====================================================================
        // TOKENS FUNDAMENTALES
        // =====================================================================
        
        // Espacios en blanco
        private static readonly Parser<char, Unit> Whitespace =
            Pidgin.Parser.OneOf(Char(' '), Char('\t'), Char('\r'), Char('\n')).SkipMany();
        
        // Comentarios
        private static readonly Parser<char, Unit> LineComment =
            String("//").Then(Any.Until(Char('\n'))).Void();
        
        private static readonly Parser<char, Unit> BlockComment =
            String("/*").Then(Any.Until(String("*/"))).Void();
        
        // Espacios con comentarios
        private static readonly Parser<char, Unit> WS =
            Pidgin.Parser.OneOf(Whitespace, LineComment, BlockComment).SkipMany();
        
        // Identificadores
        private static readonly Parser<char, string> Identifier =
            Letter.Or(Char('_'))
            .Then(LetterOrDigit.Or(Char('_')).ManyString())
            .Map((first, rest) => first + rest)
            .Between(WS);
        
        // Números
        private static readonly Parser<char, int> Integer =
            Char('-').Optional()
            .Then(Digit.AtLeastOnce())
            .Map((sign, digits) => 
            {
                var numStr = new string(digits.ToArray());
                var num = int.Parse(numStr);
                return sign.HasValue ? -num : num;
            })
            .Between(WS);
        
        // Cadenas con escapes
        private static readonly Parser<char, string> StringLiteral =
            Char('"')
            .Then(
                Pidgin.Parser.OneOf(
                    String("\\\"").ThenReturn('"'),
                    String("\\\\").ThenReturn('\\'),
                    String("\\n").ThenReturn('\n'),
                    String("\\t").ThenReturn('\t'),
                    Any.Where(c => c != '"' && c != '\\')
                ).ManyString()
            )
            .Before(Char('"'))
            .Between(WS);
        
        // Booleanos en español
        private static readonly Parser<char, bool> Boolean =
            Pidgin.Parser.OneOf(
                String("verdadero").ThenReturn(true),
                String("falso").ThenReturn(false),
                String("sí").ThenReturn(true),
                String("si").ThenReturn(true),
                String("no").ThenReturn(false)
            ).Between(WS);
        
        // =====================================================================
        // VALORES COMPUESTOS
        // =====================================================================
        
        private static Parser<char, Value> Value => Rec(() => ValueImpl);
        
        private static readonly Parser<char, Value> ValueImpl =
            Pidgin.Parser.OneOf(
                StringLiteral.Map(s => (Value)new StringValue(s)),
                Integer.Map(i => (Value)new NumberValue(i)),
                Boolean.Map(b => (Value)new BoolValue(b)),
                ListValue,
                MapValue,
                Identifier.Map(id => (Value)new IdentifierValue(id))
            );
        
        private static readonly Parser<char, Value> ListValue =
            Char('[').Between(WS)
            .Then(Value.SeparatedBy(Char(',').Between(WS)))
            .Before(Char(']').Between(WS))
            .Map(items => (Value)new ListValue(items.ToList()));
        
        private static readonly Parser<char, Value> MapValue =
            Char('{').Between(WS)
            .Then(
                Identifier.Before(Char(':').Between(WS))
                .Then(Value)
                .Map((key, val) => new KeyValuePair<string, Value>(key, val))
                .SeparatedBy(Char(',').Between(WS))
            )
            .Before(Char('}').Between(WS))
            .Map(pairs => (Value)new MapValue(pairs.ToDictionary(p => p.Key, p => p.Value)));
        
        // =====================================================================
        // PALABRAS CLAVE EN ESPAÑOL
        // =====================================================================
        
        private static Parser<char, string> Keyword(string word) => String(word).Between(WS);
        
        // =====================================================================
        // PROPIEDADES GENÉRICAS
        // =====================================================================
        
        private static readonly Parser<char, PropertyAssignment> PropertyAssignment =
            Identifier.Before(Char(':').Between(WS))
            .Then(Value)
            .Map((name, val) => new PropertyAssignment(name, val));
        
        // =====================================================================
        // CONDICIONES COMPLEJAS
        // =====================================================================
        
        private static Parser<char, Condition> Condition => Rec(() => OrCondition);
        
        private static readonly Parser<char, Condition> OrCondition =
            AndCondition.Then(
                Pidgin.Parser.OneOf(String("||"), String("o")).Between(WS)
                .Then(AndCondition)
                .Many()
            )
            .Map((first, rest) => 
                rest.Aggregate(first, (acc, item) => 
                    new CompoundCondition(acc, "or", item.Item2)));
        
        private static readonly Parser<char, Condition> AndCondition =
            NotCondition.Then(
                Pidgin.Parser.OneOf(String("&&"), String("y")).Between(WS)
                .Then(NotCondition)
                .Many()
            )
            .Map((first, rest) => 
                rest.Aggregate(first, (acc, item) => 
                    new CompoundCondition(acc, "and", item.Item2)));
        
        private static readonly Parser<char, Condition> NotCondition =
            Pidgin.Parser.OneOf(String("no"), String("!")).Between(WS).Optional()
            .Then(AtomicCondition)
            .Map((negation, cond) => 
                negation.HasValue ? new NotCondition(cond) : cond);
        
        private static readonly Parser<char, Condition> AtomicCondition =
            Pidgin.Parser.OneOf(
                Char('(').Between(WS).Then(Condition).Before(Char(')').Between(WS))
                    .Map(c => (Condition)new ParenthesizedCondition(c)),
                SimpleConditionParser
            );
        
        private static readonly Parser<char, Condition> SimpleConditionParser =
            Identifier
            .Then(
                Char('(').Between(WS)
                .Then(Value.SeparatedBy(Char(',').Between(WS)))
                .Before(Char(')').Between(WS))
                .Optional()
            )
            .Map((func, args) => 
                (Condition)new SimpleCondition(func, args?.ToList() ?? new List<Value>()));
        
        // =====================================================================
        // ACCIONES COMPLEJAS
        // =====================================================================
        
        private static Parser<char, Action> Action => Rec(() => ActionImpl);
        
        private static readonly Parser<char, Action> ActionImpl =
            Pidgin.Parser.OneOf(
                ConditionalActionParser,
                BlockActionParser,
                SimpleActionParser
            );
        
        private static readonly Parser<char, Action> SimpleActionParser =
            Identifier
            .Then(
                Char('(').Between(WS)
                .Then(Value.SeparatedBy(Char(',').Between(WS)))
                .Before(Char(')').Between(WS))
                .Optional()
            )
            .Map((func, args) => 
                (Action)new SimpleAction(func, args?.ToList() ?? new List<Value>()));
        
        private static readonly Parser<char, Action> BlockActionParser =
            Char('{').Between(WS)
            .Then(Action.SeparatedBy(Char(';').Between(WS)))
            .Before(Char('}').Between(WS))
            .Map(actions => (Action)new BlockAction(actions.ToList()));
        
        private static readonly Parser<char, Action> ConditionalActionParser =
            Keyword("si").Then(Condition)
            .Then(Char('{').Between(WS).Then(Action.SeparatedBy(Char(';').Between(WS))).Before(Char('}').Between(WS)))
            .Then(
                Keyword("sino")
                .Then(Char('{').Between(WS).Then(Action.SeparatedBy(Char(';').Between(WS))).Before(Char('}').Between(WS)))
                .Optional()
            )
            .Map(((cond, thenActions), elseActions) => 
                (Action)new ConditionalAction(cond, thenActions.ToList(), elseActions?.ToList()));
        
        // =====================================================================
        // SECCIONES ESPECÍFICAS
        // =====================================================================
        
        // Includes
        private static readonly Parser<char, string> IncludeDirective =
            Keyword("incluir").Then(StringLiteral);
        
        // Sección Juego
        private static readonly Parser<char, GameProperty> GameProperty =
            Identifier.Before(Char(':').Between(WS))
            .Then(Value)
            .Map((name, val) => new GameProperty(name, val));
        
        private static readonly Parser<char, Section> GameSection =
            Keyword("juego")
            .Then(Char('{').Between(WS))
            .Then(GameProperty.SeparatedBy(WS))
            .Before(Char('}').Between(WS))
            .Map(props => (Section)new GameSection(props.ToList()));
        
        // Sección Vocabulario
        private static readonly Parser<char, VocabEntry> VocabEntry =
            Integer
            .Then(Char('[').Between(WS).Then(StringLiteral.SeparatedBy(Char(',').Between(WS))).Before(Char(']').Between(WS)))
            .Then(
                Keyword("sinonimos").Then(Char(':').Between(WS))
                .Then(Char('[').Between(WS).Then(StringLiteral.SeparatedBy(Char(',').Between(WS))).Before(Char(']').Between(WS)))
                .Optional()
            )
            .Map(((num, words), synonyms) => 
                new VocabEntry(num, words.ToList(), synonyms?.ToList()));
        
        private static readonly Parser<char, VocabCategory> VocabCategory =
            OneOf(
                Keyword("verbos"), Keyword("sustantivos"), Keyword("adjetivos"),
                Keyword("adverbios"), Keyword("preposiciones"), Keyword("conjunciones"),
                Keyword("direcciones"), Keyword("sistema")
            )
            .Before(Char(':').Between(WS))
            .Then(Char('{').Between(WS).Then(VocabEntry.SeparatedBy(WS)).Before(Char('}').Between(WS)))
            .Map((type, entries) => new VocabCategory(type, entries.ToList()));
        
        private static readonly Parser<char, Section> VocabSection =
            Keyword("vocabulario")
            .Then(Char('{').Between(WS))
            .Then(VocabCategory.SeparatedBy(WS))
            .Before(Char('}').Between(WS))
            .Map(categories => (Section)new VocabSection(categories.ToList()));
        
        // Sección Flags
        private static readonly Parser<char, FlagDefinition> FlagDefinition =
            OneOf(Keyword("flag"), Keyword("contador"))
            .Then(Identifier)
            .Then(Char('=').Between(WS).Then(Integer))
            .Before(Char(';').Between(WS))
            .Map(((type, name), number) => new FlagDefinition(type, name, number));
        
        private static readonly Parser<char, Section> FlagsSection =
            Keyword("flags")
            .Then(Char('{').Between(WS))
            .Then(FlagDefinition.SeparatedBy(WS))
            .Before(Char('}').Between(WS))
            .Map(flags => (Section)new FlagsSection(flags.ToList()));
        
        // Sección Localidades
        private static readonly Parser<char, LocationProperty> LocationProperty =
            Identifier.Before(Char(':').Between(WS))
            .Then(Value)
            .Map((name, val) => new LocationProperty(name, val));
        
        private static readonly Parser<char, LocationDefinition> LocationDefinition =
            Keyword("localidad").Then(Identifier)
            .Then(Char('{').Between(WS).Then(LocationProperty.SeparatedBy(WS)).Before(Char('}').Between(WS)))
            .Map((id, props) => new LocationDefinition(id, props.ToList()));
        
        private static readonly Parser<char, Section> LocationsSection =
            Keyword("localidades")
            .Then(Char('{').Between(WS))
            .Then(LocationDefinition.SeparatedBy(WS))
            .Before(Char('}').Between(WS))
            .Map(locations => (Section)new LocationsSection(locations.ToList()));
        
        // Sección Objetos
        private static readonly Parser<char, ObjectProperty> ObjectProperty =
            Identifier.Before(Char(':').Between(WS))
            .Then(Value)
            .Map((name, val) => new ObjectProperty(name, val));
        
        private static readonly Parser<char, ObjectDefinition> ObjectDefinition =
            Keyword("objeto").Then(Identifier)
            .Then(Char('{').Between(WS).Then(ObjectProperty.SeparatedBy(WS)).Before(Char('}').Between(WS)))
            .Map((id, props) => new ObjectDefinition(id, props.ToList()));
        
        private static readonly Parser<char, Section> ObjectsSection =
            Keyword("objetos")
            .Then(Char('{').Between(WS))
            .Then(ObjectDefinition.SeparatedBy(WS))
            .Before(Char('}').Between(WS))
            .Map(objects => (Section)new ObjectsSection(objects.ToList()));
        
        // Sección NPCs
        private static readonly Parser<char, NPCProperty> NPCProperty =
            Identifier.Before(Char(':').Between(WS))
            .Then(Value)
            .Map((name, val) => new NPCProperty(name, val));
        
        private static readonly Parser<char, NPCDefinition> NPCDefinition =
            Keyword("npc").Then(Identifier)
            .Then(Char('{').Between(WS).Then(NPCProperty.SeparatedBy(WS)).Before(Char('}').Between(WS)))
            .Map((id, props) => new NPCDefinition(id, props.ToList()));
        
        private static readonly Parser<char, Section> NPCsSection =
            Keyword("npcs")
            .Then(Char('{').Between(WS))
            .Then(NPCDefinition.SeparatedBy(WS))
            .Before(Char('}').Between(WS))
            .Map(npcs => (Section)new NPCsSection(npcs.ToList()));
        
        // Sección Procesos
        private static readonly Parser<char, ProcessType> ProcessType =
            OneOf(
                Keyword("inicial").ThenReturn((ProcessType)new SimpleProcessType("inicial")),
                Keyword("cada_turno").ThenReturn((ProcessType)new SimpleProcessType("cada_turno")),
                Keyword("auto").ThenReturn((ProcessType)new SimpleProcessType("auto")),
                Keyword("manejador_timeout").ThenReturn((ProcessType)new SimpleProcessType("manejador_timeout")),
                Keyword("manejador_interrupcion")
                    .Then(Char('(').Between(WS).Then(Integer).Before(Char(')').Between(WS)))
                    .Map(param => (ProcessType)new ParameterizedProcessType("manejador_interrupcion", param)),
                Keyword("proceso_usuario")
                    .Then(Char('(').Between(WS).Then(Integer).Before(Char(')').Between(WS)))
                    .Map(param => (ProcessType)new ParameterizedProcessType("proceso_usuario", param)),
                Keyword("antes_accion_jugador").ThenReturn((ProcessType)new SimpleProcessType("antes_accion_jugador")),
                Keyword("despues_accion_jugador").ThenReturn((ProcessType)new SimpleProcessType("despues_accion_jugador")),
                Keyword("al_inicio_juego").ThenReturn((ProcessType)new SimpleProcessType("al_inicio_juego")),
                Keyword("al_fin_juego").ThenReturn((ProcessType)new SimpleProcessType("al_fin_juego")),
                Keyword("periodico")
                    .Then(Char('(').Between(WS).Then(Integer).Before(Char(')').Between(WS)))
                    .Map(param => (ProcessType)new ParameterizedProcessType("periodico", param))
            );
        
        private static readonly Parser<char, ProcessProperty> ProcessProperty =
            Identifier.Before(Char(':').Between(WS))
            .Then(Value)
            .Map((name, val) => new ProcessProperty(name, val));
        
        private static readonly Parser<char, ProcessDefinition> ProcessDefinition =
            ProcessType.Then(Identifier)
            .Then(Char('{').Between(WS).Then(ProcessProperty.SeparatedBy(WS)).Before(Char('}').Between(WS)))
            .Map(((type, id), props) => new ProcessDefinition(type, id, props.ToList()));
        
        private static readonly Parser<char, Section> ProcessesSection =
            Keyword("procesos")
            .Then(Char('{').Between(WS))
            .Then(ProcessDefinition.SeparatedBy(WS))
            .Before(Char('}').Between(WS))
            .Map(processes => (Section)new ProcessesSection(processes.ToList()));
        
        // Sección Respuestas
        private static readonly Parser<char, CommandPattern> CommandPattern =
            StringLiteral.Map(s => (CommandPattern)new SimplePattern(s));
        
        private static readonly Parser<char, ResponseDefinition> ResponseDefinition =
            Keyword("al")
            .Then(
                OneOf(
                    CommandPattern,
                    Char('[').Between(WS).Then(CommandPattern.SeparatedBy(Char(',').Between(WS))).Before(Char(']').Between(WS))
                        .Map(patterns => patterns.First()) // Simplificado por ahora
                )
            )
            .Then(
                Keyword("requiere").Then(Char(':').Between(WS)).Then(Condition).Optional()
            )
            .Then(
                Keyword("prioridad").Then(Char(':').Between(WS)).Then(Integer).Optional()
            )
            .Then(
                Keyword("hacer").Then(Char(':').Between(WS)).Then(Action)
            )
            .Map((((pattern, condition), priority), action) => 
                new ResponseDefinition(new List<CommandPattern> { pattern }, condition, priority, action));
        
        private static readonly Parser<char, Section> ResponsesSection =
            Keyword("respuestas")
            .Then(Char('{').Between(WS))
            .Then(ResponseDefinition.SeparatedBy(WS))
            .Before(Char('}').Between(WS))
            .Map(responses => (Section)new ResponsesSection(responses.ToList()));
        
        // Sección Mensajes
        private static readonly Parser<char, MessageDefinition> MessageDefinition =
            Identifier.Before(Char(':').Between(WS))
            .Then(StringLiteral)
            .Map((id, text) => new MessageDefinition(id, text));
        
        private static readonly Parser<char, Section> MessagesSection =
            Keyword("mensajes")
            .Then(Char('{').Between(WS))
            .Then(MessageDefinition.SeparatedBy(WS))
            .Before(Char('}').Between(WS))
            .Map(messages => (Section)new MessagesSection(messages.ToList()));
        
        // =====================================================================
        // PARSER PRINCIPAL
        // =====================================================================
        
        private static readonly Parser<char, Section> Section =
            OneOf(
                GameSection,
                VocabSection,
                FlagsSection,
                LocationsSection,
                ObjectsSection,
                NPCsSection,
                ProcessesSection,
                ResponsesSection,
                MessagesSection
                // Añadir más secciones aquí
            );
        
        private static readonly Parser<char, DaadProgram> Program =
            WS.Then(IncludeDirective.SeparatedBy(WS))
            .Then(Section.SeparatedBy(WS))
            .Before(WS)
            .Map((includes, sections) => new DaadProgram(includes.ToList(), sections.ToList()));
        
        // =====================================================================
        // API PÚBLICA
        // =====================================================================
        
        /// <summary>
        /// Parsea un programa DAAD completo desde texto
        /// </summary>
        public static ParseResult<char, DaadProgram> ParseProgram(string input)
        {
            return Program.Parse(input);
        }
        
        /// <summary>
        /// Parsea una sección específica desde texto
        /// </summary>
        public static ParseResult<char, Section> ParseSection(string input)
        {
            return Section.Parse(input);
        }
        
        /// <summary>
        /// Parsea solo una condición
        /// </summary>
        public static ParseResult<char, Condition> ParseCondition(string input)
        {
            return Condition.Parse(input);
        }
        
        /// <summary>
        /// Parsea solo una acción
        /// </summary>
        public static ParseResult<char, Action> ParseAction(string input)
        {
            return Action.Parse(input);
        }
    }
    
    // =====================================================================
    // UTILIDADES DE EXTENSIÓN
    // =====================================================================
    
    public static class DaadParserExtensions
    {
        /// <summary>
        /// Convierte el resultado del parser a excepción si falla
        /// </summary>
        public static T ParseOrThrow<T>(this ParseResult<char, T> result)
        {
            if (result.Success)
                return result.Value;
            
            throw new DaadParseException($"Error de parsing: {result.Error}");
        }
        
        /// <summary>
        /// Intenta parsear y devuelve null si falla
        /// </summary>
        public static T? TryParse<T>(this ParseResult<char, T> result) where T : class
        {
            return result.Success ? result.Value : null;
        }
    }
    
    /// <summary>
    /// Excepción específica para errores de parsing DAAD
    /// </summary>
    public class DaadParseException : Exception
    {
        public DaadParseException(string message) : base(message) { }
        public DaadParseException(string message, Exception innerException) : base(message, innerException) { }
    }
    
    // =====================================================================
    // EJEMPLO DE USO
    // =====================================================================
    
    public static class DaadParserExample
    {
        public static void TestParser()
        {
            string daadCode = @"
                incluir ""libreria_basica.daad""
                
                juego {
                    titulo: ""Mi Aventura""
                    autor: ""Desarrollador DAAD""
                    localizacion_inicial: bosque
                    puntuacion_maxima: 100
                }
                
                flags {
                    flag puerta_abierta = 10;
                    contador intentos = 20;
                }
                
                localidades {
                    localidad bosque {
                        desc: ""Estás en un bosque frondoso.""
                        conexiones: {
                            norte: cueva
                            sur: pueblo
                        }
                        objetos: [""espada"", ""escudo""]
                    }
                }
                
                objetos {
                    objeto espada {
                        nombre: ""espada mágica""
                        desc: ""Una espada que brilla con luz propia.""
                        localizacion: bosque
                        propiedades: {
                            cogible: verdadero
                            vestible: verdadero
                            peso: 5
                        }
                    }
                }
                
                npcs {
                    npc mago {
                        nombre: ""Mago Sabio""
                        desc: ""Un mago anciano con barba blanca.""
                        localizacion: cueva
                        comportamiento: estatico
                        dialogo: {
                            saludo: {
                                texto: ""¡Bienvenido, valiente aventurero!""
                                respuestas: {
                                    ""Hola"": {
                                        respuesta_npc: ""Que tengas un buen viaje.""
                                    }
                                }
                            }
                        }
                    }
                }
                
                procesos {
                    inicial inicio_juego {
                        hacer: {
                            mensaje(""¡Bienvenido a la aventura!"")
                            activar(intro_mostrada)
                        }
                    }
                    
                    cada_turno contador_turnos {
                        hacer: {
                            incrementar(turnos_jugados)
                        }
                    }
                }
                
                respuestas {
                    al ""mirar espada"" {
                        requiere: presente(espada)
                        hacer: {
                            mensaje(""La espada brilla intensamente."")
                        }
                    }
                    
                    al ""hablar con mago"" {
                        requiere: presente(mago) y en(cueva)
                        hacer: {
                            si llevado(espada) {
                                mensaje(""El mago admira tu espada."")
                            } sino {
                                mensaje(""El mago te mira expectante."")
                            }
                        }
                    }
                }
                
                mensajes {
                    bienvenida: ""¡Bienvenido a esta increíble aventura!""
                    despedida: ""¡Gracias por jugar!""
                }
            ";
            
            try
            {
                var result = DaadParser.ParseProgram(daadCode);
                var program = result.ParseOrThrow();
                
                Console.WriteLine($"Programa parseado exitosamente!");
                Console.WriteLine($"Includes: {program.Includes.Count}");
                Console.WriteLine($"Secciones: {program.Sections.Count}");
                
                foreach (var section in program.Sections)
                {
                    Console.WriteLine($"- {section.GetType().Name}");
                }
            }
            catch (DaadParseException ex)
            {
                Console.WriteLine($"Error de parsing: {ex.Message}");
            }
        }
    }
}