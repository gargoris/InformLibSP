using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Pidgin;
using static Pidgin.Parser;
using static Pidgin.Parser<char>;
using Microsoft.Extensions.Logging;
using DaadModern.Models;

namespace DaadModern.Parser
{
    // =====================================================================
    // MODELO DE DATOS (AST) - Completado
    // =====================================================================
    
    public record DaadProgram(List<Section> Sections);
    
    public abstract record Section;
    public record GameSection(List<GameProperty> Properties) : Section;
    public record LocationSection(string Id, List<LocationProperty> Properties) : Section;
    public record ObjectSection(string Id, List<ObjectProperty> Properties) : Section;
    public record ResponseSection(List<Response> Responses) : Section;
    public record VocabSection(List<VocabEntry> Entries) : Section;
    
    public record GameProperty(string Name, Value Value);
    public record LocationProperty(string Name, Value Value);
    public record ObjectProperty(string Name, Value Value);
    public record VocabEntry(string Word, int Number, string Type);
    
    public record Response(List<string> Patterns, Condition? Condition, List<Action> Actions);
    
    public abstract record Value;
    public record StringValue(string Text) : Value;
    public record NumberValue(int Number) : Value;
    public record BoolValue(bool Value) : Value;
    public record IdentifierValue(string Id) : Value;
    public record ListValue(List<Value> Items) : Value;
    public record MapValue(Dictionary<string, Value> Items) : Value;
    
    public abstract record Condition;
    public record SimpleCondition(string Function, List<Value> Args) : Condition;
    public record CompoundCondition(Condition Left, string Operator, Condition Right) : Condition;
    
    public abstract record Action;
    public record SimpleAction(string Function, List<Value> Args) : Action;
    public record BlockAction(List<Action> Actions) : Action;
    
    // =====================================================================
    // INTERFACES
    // =====================================================================
    
    public interface IDaadParser
    {
        Task<ParseResult> ParseAsync(string input);
    }

    public class ParseResult
    {
        public bool Success { get; set; }
        public DaadAst Ast { get; set; } = new();
        public List<ParseError> Errors { get; set; } = new();
    }

    public class ParseError
    {
        public int Line { get; set; }
        public int Column { get; set; }
        public string Message { get; set; } = string.Empty;
        public string Code { get; set; } = string.Empty;
    }
    
    // =====================================================================
    // PARSER DAAD MODERNO CON PIDGIN - COMPLETADO
    // =====================================================================
    
    public static class DaadParser
    {
        // =====================================================================
        // TOKENS BÁSICOS
        // =====================================================================
        
        private static readonly Parser<char, Unit> Whitespace =
            OneOf(Char(' '), Char('\t'), Char('\r'), Char('\n')).SkipMany();
        
        private static readonly Parser<char, Unit> LineComment =
            String("//").Then(Any.Until(Char('\n'))).Void();
        
        private static readonly Parser<char, Unit> BlockComment =
            String("/*").Then(Any.Until(String("*/"))).Void();
        
        private static readonly Parser<char, Unit> WS =
            OneOf(Whitespace, LineComment, BlockComment).SkipMany();
        
        private static readonly Parser<char, string> Identifier =
            Letter.Or(Char('_'))
            .Then(LetterOrDigit.Or(Char('_')).ManyString())
            .Map((first, rest) => first + rest)
            .Between(WS);
        
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
        
        private static readonly Parser<char, string> StringLiteral =
            Char('"')
            .Then(
                OneOf(
                    String("\\\"").ThenReturn('"'),
                    String("\\\\").ThenReturn('\\'),
                    String("\\n").ThenReturn('\n'),
                    String("\\t").ThenReturn('\t'),
                    Any.Where(c => c != '"' && c != '\\')
                ).ManyString()
            )
            .Before(Char('"'))
            .Between(WS);
        
        private static readonly Parser<char, bool> Boolean =
            OneOf(
                String("true").ThenReturn(true),
                String("false").ThenReturn(false),
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
            OneOf(
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
        // PALABRAS CLAVE MULTIIDIOMA
        // =====================================================================
        
        private static Parser<char, string> Keyword(string english, string spanish) =>
            OneOf(String(english), String(spanish)).Between(WS);
        
        private static readonly Parser<char, string> GameKeyword = Keyword("game", "juego");
        private static readonly Parser<char, string> LocationKeyword = Keyword("location", "localidad");
        private static readonly Parser<char, string> ObjectKeyword = Keyword("object", "objeto");
        private static readonly Parser<char, string> ResponsesKeyword = Keyword("responses", "respuestas");
        private static readonly Parser<char, string> VocabKeyword = Keyword("vocab", "vocabulario");
        private static readonly Parser<char, string> OnKeyword = Keyword("on", "al");
        private static readonly Parser<char, string> RequireKeyword = Keyword("require", "requiere");
        private static readonly Parser<char, string> DoKeyword = Keyword("do", "hacer");
        
        // =====================================================================
        // PROPIEDADES Y ASIGNACIONES
        // =====================================================================
        
        private static readonly Parser<char, GameProperty> GameProperty =
            Identifier.Before(Char(':').Between(WS))
            .Then(Value)
            .Map((name, val) => new GameProperty(name, val));
        
        private static readonly Parser<char, LocationProperty> LocationProperty =
            Identifier.Before(Char(':').Between(WS))
            .Then(Value)
            .Map((name, val) => new LocationProperty(name, val));
        
        private static readonly Parser<char, ObjectProperty> ObjectProperty =
            Identifier.Before(Char(':').Between(WS))
            .Then(Value)
            .Map((name, val) => new ObjectProperty(name, val));
        
        // =====================================================================
        // CONDICIONES
        // =====================================================================
        
        private static Parser<char, Condition> Condition => Rec(() => ConditionImpl);
        
        private static readonly Parser<char, Condition> SimpleCondition =
            Identifier
            .Then(
                Char('(').Between(WS)
                .Then(Value.SeparatedBy(Char(',').Between(WS)))
                .Before(Char(')').Between(WS))
            )
            .Map((func, args) => (Condition)new SimpleCondition(func, args.ToList()));
        
        private static readonly Parser<char, Condition> ConditionImpl =
            OneOf(
                Char('(').Between(WS).Then(Condition).Before(Char(')').Between(WS)),
                SimpleCondition
            )
            .Then(
                OneOf(
                    String("&&").Between(WS).ThenReturn("and"),
                    String("||").Between(WS).ThenReturn("or"),
                    String("y").Between(WS).ThenReturn("and"),
                    String("o").Between(WS).ThenReturn("or")
                )
                .Then(Condition)
                .Optional()
            )
            .Map((left, op_right) =>
                op_right.HasValue 
                    ? (Condition)new CompoundCondition(left, op_right.Value.Item1, op_right.Value.Item2)
                    : left
            );
        
        // =====================================================================
        // ACCIONES
        // =====================================================================
        
        private static Parser<char, Action> Action => Rec(() => ActionImpl);
        
        private static readonly Parser<char, Action> SimpleAction =
            Identifier
            .Then(
                Char('(').Between(WS)
                .Then(Value.SeparatedBy(Char(',').Between(WS)))
                .Before(Char(')').Between(WS))
            )
            .Map((func, args) => (Action)new SimpleAction(func, args.ToList()));
        
        private static readonly Parser<char, Action> BlockAction =
            Char('{').Between(WS)
            .Then(Action.SeparatedBy(Char(';').Between(WS)))
            .Before(Char('}').Between(WS))
            .Map(actions => (Action)new BlockAction(actions.ToList()));
        
        private static readonly Parser<char, Action> ActionImpl =
            OneOf(BlockAction, SimpleAction);
        
        // =====================================================================
        // SECCIONES PRINCIPALES
        // =====================================================================
        
        private static readonly Parser<char, Section> GameSection =
            GameKeyword
            .Then(Char('{').Between(WS))
            .Then(GameProperty.SeparatedBy(Char(',').Between(WS).Or(Char(';').Between(WS))))
            .Before(Char('}').Between(WS))
            .Map(props => (Section)new GameSection(props.ToList()));
        
        private static readonly Parser<char, Section> LocationSection =
            LocationKeyword
            .Then(Identifier)
            .Before(Char('{').Between(WS))
            .Then(LocationProperty.SeparatedBy(Char(',').Between(WS).Or(Char(';').Between(WS))))
            .Before(Char('}').Between(WS))
            .Map((id, props) => (Section)new LocationSection(id, props.ToList()));
        
        private static readonly Parser<char, Section> ObjectSection =
            ObjectKeyword
            .Then(Identifier)
            .Before(Char('{').Between(WS))
            .Then(ObjectProperty.SeparatedBy(Char(',').Between(WS).Or(Char(';').Between(WS))))
            .Before(Char('}').Between(WS))
            .Map((id, props) => (Section)new ObjectSection(id, props.ToList()));
        
        private static readonly Parser<char, VocabEntry> VocabEntry =
            Identifier
            .Before(Char(':').Between(WS))
            .Then(Integer)
            .Before(Char(':').Between(WS))
            .Then(Identifier)
            .Map((word, num, type) => new VocabEntry(word, num, type));
        
        private static readonly Parser<char, Section> VocabSection =
            VocabKeyword
            .Then(Char('{').Between(WS))
            .Then(VocabEntry.SeparatedBy(Char(',').Between(WS).Or(Char(';').Between(WS))))
            .Before(Char('}').Between(WS))
            .Map(entries => (Section)new VocabSection(entries.ToList()));
        
        private static readonly Parser<char, Response> Response =
            OnKeyword
            .Then(StringLiteral.SeparatedBy(Char(',').Between(WS)))
            .Then(RequireKeyword.Then(Condition).Optional())
            .Before(DoKeyword)
            .Then(Action.SeparatedBy(Char(';').Between(WS)))
            .Map((patterns, condition, actions) => 
                new Response(patterns.ToList(), condition, actions.ToList()));
        
        private static readonly Parser<char, Section> ResponseSection =
            ResponsesKeyword
            .Then(Char('{').Between(WS))
            .Then(Response.SeparatedBy(WS))
            .Before(Char('}').Between(WS))
            .Map(responses => (Section)new ResponseSection(responses.ToList()));
        
        // =====================================================================
        // PROGRAMA PRINCIPAL
        // =====================================================================
        
        private static readonly Parser<char, Section> Section =
            OneOf(
                GameSection,
                LocationSection,
                ObjectSection,
                ResponseSection,
                VocabSection
            );
        
        public static readonly Parser<char, DaadProgram> Program =
            WS.Then(Section.SeparatedBy(WS)).Before(WS).AtEnd()
            .Map(sections => new DaadProgram(sections.ToList()));
    }
}
