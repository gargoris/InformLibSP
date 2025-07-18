// =====================================================================
// DAAD Moderno - Parser de Comandos de Jugador en Tiempo Real
// Extensión para interpretar comandos complejos como lenguaje natural
// =====================================================================

using System;
using System.Collections.Generic;
using System.Linq;
using Pidgin;
using static Pidgin.Parser;
using static Pidgin.Parser<char>;


namespace DaadModern.Runtime
{
    // =====================================================================
    // MODELO DE DATOS PARA COMANDOS DE JUGADOR
    // =====================================================================
    
    #region Player Command AST
    
    /// <summary>
    /// Comando completo del jugador, puede ser simple o compuesto
    /// </summary>
    public abstract record PlayerCommand;
    
    /// <summary>
    /// Comando simple: "mata al ogro"
    /// </summary>
    public record SimplePlayerCommand(
        string? TargetNPC,           // "Fred" en "Fred, mata al ogro"
        string Verb,                 // "mata"
        List<GameObject> Objects,    // ["ogro"]
        List<PrepositionalPhrase> Phrases  // ["con la espada brillante"]
    ) : PlayerCommand;
    
    /// <summary>
    /// Comando compuesto: "habla con gandalf y mata al troll"
    /// </summary>
    public record CompoundPlayerCommand(
        List<SimplePlayerCommand> Commands,
        string Coordinator  // "y", "pero", "entonces"
    ) : PlayerCommand;
    
    /// <summary>
    /// Objeto del juego con posibles adjetivos
    /// </summary>
    public record GameObject(
        string Name,                 // "espada"
        List<string> Adjectives,     // ["brillante"]
        string? Article              // "la", "el", "un", "una"
    );
    
    /// <summary>
    /// Frase preposicional: "con la espada", "del tesoro de los enanos"
    /// </summary>
    public record PrepositionalPhrase(
        string Preposition,          // "con", "del"
        GameObject Object,           // "espada brillante"
        PrepositionalPhrase? Nested  // "de los enanos" dentro de "del tesoro"
    );
    
    #endregion
    
    // =====================================================================
    // PARSER DE COMANDOS DE JUGADOR
    // =====================================================================
    
    public static class PlayerCommandParser
    {
        // =====================================================================
        // TOKENS BÁSICOS PARA ESPAÑOL
        // =====================================================================
        
        private static readonly Parser<char, Unit> WS = 

            Pidgin.Parser.OneOf(Char(' '), Char('\t')).SkipMany();
        
        // Artículos en español
        private static readonly Parser<char, string> Article =
           Pidgin.Parser.OneOf(
                String("el"), String("la"), String("los"), String("las"),
                String("un"), String("una"), String("unos"), String("unas"),
                String("del"), String("al")  // Contracciones
            ).Between(WS);
        
        // Preposiciones comunes
        private static readonly Parser<char, string> Preposition =
           Pidgin.Parser.OneOf(
                String("con"), String("sin"), String("en"), String("de"), 
                String("para"), String("por"), String("desde"), String("hasta"),
                String("sobre"), String("bajo"), String("dentro"), String("fuera"),
                String("contra"), String("entre"), String("tras"), String("ante")
            ).Between(WS);
        
        // Coordinadores
        private static readonly Parser<char, string> Coordinator =
           Pidgin.Parser.OneOf(
                String("y"), String("pero"), String("entonces"), 
                String("después"), String("luego"), String("mientras")
            ).Between(WS);
        
        // Verbos comunes (puedes expandir esta lista)
        private static readonly Parser<char, string> Verb =
           Pidgin.Parser.OneOf(
                String("mata"), String("matar"), String("atacar"), String("ataca"),
                String("habla"), String("hablar"), String("dice"), String("decir"),
                String("coge"), String("coger"), String("toma"), String("tomar"),
                String("mira"), String("mirar"), String("examina"), String("examinar"),
                String("abre"), String("abrir"), String("cierra"), String("cerrar"),
                String("usa"), String("usar"), String("utiliza"), String("utilizar"),
                String("ve"), String("ir"), String("camina"), String("caminar")
            ).Between(WS);
        
        // Nombres/sustantivos (en un juego real, esto vendría del vocabulario)
        private static readonly Parser<char, string> Noun =
            Letter.AtLeastOnce().Map(chars => new string(chars.ToArray())).Between(WS);
        
        // Adjetivos
        private static readonly Parser<char, string> Adjective =
           Pidgin.Parser.OneOf(
                String("brillante"), String("oscuro"), String("grande"), String("pequeño"),
                String("afilado"), String("romo"), String("mágico"), String("antiguo"),
                String("nuevo"), String("viejo"), String("roto"), String("perfecto"),
                String("miniada"), String("dorada"), String("plateada")
            ).Between(WS);
        
        // =====================================================================
        // PARSERS COMPOSITIVOS
        // =====================================================================
        
        // Objeto del juego: [artículo] [adjetivos...] nombre
        private static readonly Parser<char, GameObject> GameObject =
            Article.Optional()
            .Then(Adjective.Many())
            .Then(Noun)
            .Map(((article, adjectives), name) => 
                new GameObject(name, adjectives.ToList(), article));
        
        // Frase preposicional recursiva: "del tesoro de los enanos"
        private static Parser<char, PrepositionalPhrase> PrepositionalPhrase => 
            Rec(() => PrepositionalPhraseImpl);
        
        private static readonly Parser<char, PrepositionalPhrase> PrepositionalPhraseImpl =
            Preposition
            .Then(GameObject)
            .Then(PrepositionalPhrase.Optional())
            .Map(((prep, obj), nested) => 
                new PrepositionalPhrase(prep, obj, nested));
        
        // Comando simple: [NPC,] verbo objeto [frases_preposicionales...]
        private static readonly Parser<char, SimplePlayerCommand> SimpleCommand =
            // NPC dirigido opcional: "Fred, ..."
            (Noun.Before(Char(',').Between(WS))).Optional()
            .Then(Verb)
            .Then(GameObject.Many())  // Puede haber múltiples objetos
            .Then(PrepositionalPhrase.Many())
            .Map((((targetNPC, verb), objects), phrases) =>
                new SimplePlayerCommand(targetNPC, verb, objects.ToList(), phrases.ToList()));
        
        // Comando compuesto: comando1 coordinator comando2 [coordinator comando3...]
        private static readonly Parser<char, PlayerCommand> CompoundCommand =
            SimpleCommand
            .Then(Coordinator.Then(SimpleCommand).AtLeastOnce())
            .Map((first, rest) =>
            {
                var allCommands = new List<SimplePlayerCommand> { first };
                allCommands.AddRange(rest.Select(r => r.Item2));
                var coordinator = rest.First().Item1; // Usar el primer coordinador
                return (PlayerCommand)new CompoundPlayerCommand(allCommands, coordinator);
            });
        
        // Parser principal: comando compuesto o simple
        private static readonly Parser<char, PlayerCommand> PlayerCommand =
           Pidgin.Parser.OneOf(
                CompoundCommand,
                SimpleCommand.Map(cmd => (PlayerCommand)cmd)
            ).Before(End);
        
        // =====================================================================
        // API PÚBLICA
        // =====================================================================
        
        /// <summary>
        /// Parsea un comando de jugador desde texto
        /// </summary>
        public static ParseResult<char, PlayerCommand> ParseCommand(string input)
        {
            return PlayerCommand.Parse(input.Trim());
        }
        
        /// <summary>
        /// Intenta parsear un comando y devuelve null si falla
        /// </summary>
        public static PlayerCommand? TryParseCommand(string input)
        {
            var result = ParseCommand(input);
            return result.Success ? result.Value : null;
        }
    }
    
    // =====================================================================
    // INTÉRPRETE DE COMANDOS
    // =====================================================================
    
    /// <summary>
    /// Convierte comandos parseados en acciones ejecutables
    /// </summary>
    public class CommandInterpreter
    {
        private readonly IGameState _gameState;
        private readonly IVocabulary _vocabulary;
        
        public CommandInterpreter(IGameState gameState, IVocabulary vocabulary)
        {
            _gameState = gameState;
            _vocabulary = vocabulary;
        }
        
        /// <summary>
        /// Interpreta un comando parseado y lo convierte en acciones DAAD
        /// </summary>
        public List<GameAction> InterpretCommand(PlayerCommand command)
        {
            return command switch
            {
                SimplePlayerCommand simple => InterpretSimpleCommand(simple),
                CompoundPlayerCommand compound => InterpretCompoundCommand(compound),
                _ => new List<GameAction>()
            };
        }
        
        private List<GameAction> InterpretSimpleCommand(SimplePlayerCommand cmd)
        {
            var actions = new List<GameAction>();
            
            // Si hay un NPC dirigido, agregarlo como contexto
            if (cmd.TargetNPC != null)
            {
                actions.Add(new SetContextAction("target_npc", cmd.TargetNPC));
            }
            
            // Resolver objetos usando el estado del juego
            var resolvedObjects = ResolveObjects(cmd.Objects, cmd.Phrases);
            
            // Generar acción principal basada en el verbo
            var mainAction = cmd.Verb switch
            {
                "mata" or "matar" or "atacar" or "ataca" => 
                    new AttackAction(resolvedObjects.FirstOrDefault()?.Id),
                
                "habla" or "hablar" => 
                    GenerateTalkAction(cmd, resolvedObjects),
                
                "coge" or "coger" or "toma" or "tomar" => 
                    new TakeAction(resolvedObjects.FirstOrDefault()?.Id),
                
                "usa" or "usar" => 
                    GenerateUseAction(cmd, resolvedObjects),
                
                _ => new UnknownVerbAction(cmd.Verb)
            };
            
            actions.Add(mainAction);
            return actions;
        }
        
        private List<GameAction> InterpretCompoundCommand(CompoundPlayerCommand cmd)
        {
            var allActions = new List<GameAction>();
            
            foreach (var simpleCmd in cmd.Commands)
            {
                allActions.AddRange(InterpretSimpleCommand(simpleCmd));
                
                // Añadir delay entre comandos si es necesario
                if (cmd.Coordinator == "entonces" || cmd.Coordinator == "luego")
                {
                    allActions.Add(new DelayAction(1));
                }
            }
            
            return allActions;
        }
        
        private List<ResolvedObject> ResolveObjects(List<GameObject> objects, List<PrepositionalPhrase> phrases)
        {
            var resolved = new List<ResolvedObject>();
            
            // Resolver objetos directos
            foreach (var obj in objects)
            {
                var candidates = _gameState.FindObjects(obj.Name, obj.Adjectives);
                var best = SelectBestMatch(candidates, obj);
                if (best != null)
                    resolved.Add(best);
            }
            
            // Resolver objetos en frases preposicionales
            foreach (var phrase in phrases)
            {
                var candidates = _gameState.FindObjects(phrase.Object.Name, phrase.Object.Adjectives);
                var best = SelectBestMatch(candidates, phrase.Object);
                if (best != null)
                    resolved.Add(new ResolvedObject(best.Id, best.Name, phrase.Preposition));
            }
            
            return resolved;
        }
        
        private ResolvedObject? SelectBestMatch(List<GameObject> candidates, GameObject target)
        {
            // Algoritmo de selección del mejor candidato
            // 1. Exacto match de nombre + todos los adjetivos
            // 2. Match de nombre + algunos adjetivos
            // 3. Solo match de nombre
            // 4. Match parcial considerando sinónimos
            
            return candidates
                .Select(c => new { 
                    Object = c, 
                    Score = CalculateMatchScore(c, target) 
                })
                .Where(x => x.Score > 0)
                .OrderByDescending(x => x.Score)
                .FirstOrDefault()
                ?.Object.Let(obj => new ResolvedObject(obj.Name, obj.Name));
        }
        
        private int CalculateMatchScore(GameObject candidate, GameObject target)
        {
            int score = 0;
            
            // Match exacto de nombre
            if (candidate.Name.Equals(target.Name, StringComparison.OrdinalIgnoreCase))
                score += 100;
            
            // Match de adjetivos
            foreach (var adj in target.Adjectives)
            {
                if (candidate.Adjectives.Any(a => a.Equals(adj, StringComparison.OrdinalIgnoreCase)))
                    score += 10;
            }
            
            // Penalizar si el candidato tiene adjetivos que no coinciden
            var unmatchedAdjectives = candidate.Adjectives.Count - 
                candidate.Adjectives.Intersect(target.Adjectives, StringComparer.OrdinalIgnoreCase).Count();
            score -= unmatchedAdjectives * 5;
            
            return Math.Max(0, score);
        }
        
        private GameAction GenerateTalkAction(SimplePlayerCommand cmd, List<ResolvedObject> objects)
        {
            var target = objects.FirstOrDefault();
            var topic = cmd.Phrases.FirstOrDefault()?.Object.Name;
            
            return new TalkAction(target?.Id, topic);
        }
        
        private GameAction GenerateUseAction(SimplePlayerCommand cmd, List<ResolvedObject> objects)
        {
            var item = objects.FirstOrDefault();
            var target = cmd.Phrases.FirstOrDefault(p => p.Preposition == "con")?.Object.Name;
            
            return new UseAction(item?.Id, target);
        }
    }
    
    // =====================================================================
    // TIPOS DE APOYO
    // =====================================================================
    
    public record ResolvedObject(string Id, string Name, string? Context = null);
    
    public abstract record GameAction;
    public record AttackAction(string? Target) : GameAction;
    public record TalkAction(string? Target, string? Topic) : GameAction;
    public record TakeAction(string? Target) : GameAction;
    public record UseAction(string? Item, string? Target) : GameAction;
    public record SetContextAction(string Key, string Value) : GameAction;
    public record DelayAction(int Turns) : GameAction;
    public record UnknownVerbAction(string Verb) : GameAction;
    
    // Interfaces que implementarías en tu motor de juego
    public interface IGameState
    {
        List<GameObject> FindObjects(string name, List<string> adjectives);
    }
    
    public interface IVocabulary
    {
        List<string> GetSynonyms(string word);
        bool IsKnownWord(string word);
    }
    
    // Extension method para sintaxis más limpia
    public static class Extensions
    {
        public static T Let<T>(this T source, Func<T, T> func) => func(source);
    }
    
    // =====================================================================
    // EJEMPLO DE USO
    // =====================================================================
    
    public static class PlayerCommandExample
    {
        public static void TestComplexCommands()
        {
            var commands = new[]
            {
                "Fred, mata al ogro con la espada brillante",
                "habla con gandalf del tesoro de los enanos y mata al troll con el hacha miniada",
                "coge la llave dorada y abre la puerta del castillo",
                "usa la poción en el guerrero herido"
            };
            
            foreach (var commandText in commands)
            {
                Console.WriteLine($"\nParsing: '{commandText}'");
                
                var result = PlayerCommandParser.ParseCommand(commandText);
                if (result.Success)
                {
                    PrintCommand(result.Value, 0);
                }
                else
                {
                    Console.WriteLine($"  ❌ Error: {result.Error}");
                }
            }
        }
        
        private static void PrintCommand(PlayerCommand cmd, int indent = 0)
        {
            var prefix = new string(' ', indent * 2);
            
            switch (cmd)
            {
                case SimplePlayerCommand simple:
                    Console.WriteLine($"{prefix}✅ Comando Simple:");
                    if (simple.TargetNPC != null)
                        Console.WriteLine($"{prefix}  👤 NPC: {simple.TargetNPC}");
                    Console.WriteLine($"{prefix}  🎯 Verbo: {simple.Verb}");
                    
                    foreach (var obj in simple.Objects)
                    {
                        var adjectives = obj.Adjectives.Any() ? $" ({string.Join(", ", obj.Adjectives)})" : "";
                        Console.WriteLine($"{prefix}  📦 Objeto: {obj.Article} {obj.Name}{adjectives}");
                    }
                    
                    foreach (var phrase in simple.Phrases)
                    {
                        PrintPrepositionalPhrase(phrase, indent + 2);
                    }
                    break;
                    
                case CompoundPlayerCommand compound:
                    Console.WriteLine($"{prefix}🔗 Comando Compuesto ({compound.Coordinator}):");
                    foreach (var subCmd in compound.Commands)
                    {
                        PrintCommand(subCmd, indent + 1);
                    }
                    break;
            }
        }
        
        private static void PrintPrepositionalPhrase(PrepositionalPhrase phrase, int indent)
        {
            var prefix = new string(' ', indent * 2);
            var adjectives = phrase.Object.Adjectives.Any() ? $" ({string.Join(", ", phrase.Object.Adjectives)})" : "";
            Console.WriteLine($"{prefix}🔗 {phrase.Preposition} {phrase.Object.Article} {phrase.Object.Name}{adjectives}");
            
            if (phrase.Nested != null)
                PrintPrepositionalPhrase(phrase.Nested, indent + 1);
        }
    }
}