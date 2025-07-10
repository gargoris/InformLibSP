# Sistema Parser DAAD Modernizado - Parte 5: Guía de Implementación

## Parte 5.3: Implementación del Parser de Condiciones y Acciones (3D4) - Componente Prioritario

### 5.3.1 Arquitectura del Parser de Expresiones

El Parser de Condiciones y Acciones debe manejar expresiones lógicas complejas con precedencia de operadores y análisis semántico. Utilizaremos un enfoque de parser descendente recursivo con manejo de precedencia.

```csharp
// ConditionAction/IConditionActionParser.cs
namespace DaadModernizado.Parser.ConditionAction;

public interface IConditionActionParser
{
    ParseResult<ModernCondition> ParseCondition(TokenStream tokens, ParseContext context);
    ParseResult<List<ModernAction>> ParseActionBlock(TokenStream tokens, ParseContext context);
    ParseResult<ModernAction> ParseAction(TokenStream tokens, ParseContext context);
}

// ConditionAction/ExpressionParser.cs
public class ExpressionParser : IConditionActionParser
{
    private readonly ILogger<ExpressionParser> _logger;
    private readonly IGameValidator _validator;

    public ExpressionParser(ILogger<ExpressionParser> logger, IGameValidator validator)
    {
        _logger = logger;
        _validator = validator;
    }

    // Precedencia de operadores (mayor número = mayor precedencia)
    private static readonly Dictionary<string, int> OperatorPrecedence = new()
    {
        ["||"] = 1,  // OR lógico
        ["&&"] = 2,  // AND lógico
        ["!"] = 3    // NOT lógico (unario)
    };
}
```

### 5.3.2 Parser de Condiciones con Precedencia

Implementar parsing de expresiones lógicas con manejo correcto de precedencia:

```csharp
// ConditionAction/ExpressionParser.cs (continuación)
public class ExpressionParser : IConditionActionParser
{
    public ParseResult<ModernCondition> ParseCondition(TokenStream tokens, ParseContext context)
    {
        try
        {
            var condition = ParseOrExpression(tokens, context);
            return ParseResult<ModernCondition>.Success(condition);
        }
        catch (ParseException ex)
        {
            _logger.LogParsingError(ex.LineNumber, ex.Message);
            return ParseResult<ModernCondition>.Failure(ex.Message);
        }
    }

    // OR tiene la precedencia más baja
    private ModernCondition ParseOrExpression(TokenStream tokens, ParseContext context)
    {
        var left = ParseAndExpression(tokens, context);

        while (tokens.Match(TokenType.Operator) && tokens.Current.Value == "||")
        {
            var operatorToken = tokens.Advance();
            var right = ParseAndExpression(tokens, context);

            left = new ModernCondition
            {
                Type = ConditionType.Logical,
                Operator = "||",
                Left = left,
                Right = right
            };
        }

        return left;
    }

    // AND tiene precedencia media
    private ModernCondition ParseAndExpression(TokenStream tokens, ParseContext context)
    {
        var left = ParseUnaryExpression(tokens, context);

        while (tokens.Match(TokenType.Operator) && tokens.Current.Value == "&&")
        {
            var operatorToken = tokens.Advance();
            var right = ParseUnaryExpression(tokens, context);

            left = new ModernCondition
            {
                Type = ConditionType.Logical,
                Operator = "&&",
                Left = left,
                Right = right
            };
        }

        return left;
    }

    // NOT tiene la precedencia más alta
    private ModernCondition ParseUnaryExpression(TokenStream tokens, ParseContext context)
    {
        if (tokens.Match(TokenType.Operator) && tokens.Current.Value == "!")
        {
            tokens.Advance(); // Consumir '!'
            var operand = ParsePrimaryExpression(tokens, context);
            
            return new ModernCondition
            {
                Type = ConditionType.Simple,
                Function = operand.Function,
                Arguments = operand.Arguments,
                IsNegated = !operand.IsNegated // Doble negación se cancela
            };
        }

        return ParsePrimaryExpression(tokens, context);
    }

    // Expresiones primarias: funciones y expresiones agrupadas
    private ModernCondition ParsePrimaryExpression(TokenStream tokens, ParseContext context)
    {
        if (tokens.Match(TokenType.LeftParen))
        {
            tokens.Advance(); // Consumir '('
            var condition = ParseOrExpression(tokens, context);
            tokens.Consume(TokenType.RightParen, "Se esperaba ')' después de la expresión agrupada");
            return condition;
        }

        if (tokens.Match(TokenType.Identifier))
        {
            return ParseConditionFunction(tokens, context);
        }

        throw new ParseException($"Se esperaba función de condición o '(', se encontró {tokens.Current.Type}", tokens.Current.LineNumber);
    }
}
```

### 5.3.3 Parser de Funciones de Condición

Manejar las funciones específicas del dominio DAAD:

```csharp
// ConditionAction/ConditionFunctionParser.cs
public partial class ExpressionParser
{
    private ModernCondition ParseConditionFunction(TokenStream tokens, ParseContext context)
    {
        var functionName = tokens.Consume(TokenType.Identifier).Value;
        tokens.Consume(TokenType.LeftParen, $"Se esperaba '(' después de la función '{functionName}'");

        var arguments = ParseFunctionArguments(tokens);
        
        tokens.Consume(TokenType.RightParen, $"Se esperaba ')' al final de la función '{functionName}'");

        var condition = new ModernCondition
        {
            Type = ConditionType.Simple,
            Function = functionName,
            Arguments = arguments
        };

        // Validación semántica específica de la función
        ValidateConditionFunction(condition, context);

        return condition;
    }

    private List<string> ParseFunctionArguments(TokenStream tokens)
    {
        var arguments = new List<string>();

        if (tokens.Match(TokenType.RightParen))
        {
            return arguments; // Función sin argumentos
        }

        do
        {
            var argument = ParseFunctionArgument(tokens);
            arguments.Add(argument);
        }
        while (tokens.TryConsume(TokenType.Comma, out _));

        return arguments;
    }

    private string ParseFunctionArgument(TokenStream tokens)
    {
        return tokens.Current.Type switch
        {
            TokenType.Identifier => tokens.Advance().Value,
            TokenType.StringLiteral => tokens.Advance().Value.Trim('"'),
            TokenType.NumberLiteral => tokens.Advance().Value,
            _ => throw new ParseException($"Argumento de función inesperado: {tokens.Current.Type}", tokens.Current.LineNumber)
        };
    }

    private void ValidateConditionFunction(ModernCondition condition, ParseContext context)
    {
        var expectedArgCount = GetExpectedArgumentCount(condition.Function);
        
        if (expectedArgCount.HasValue && condition.Arguments.Count != expectedArgCount.Value)
        {
            throw new ParseException(
                $"La función '{condition.Function}' espera {expectedArgCount} argumentos, pero recibió {condition.Arguments.Count}",
                context.CurrentLineNumber);
        }

        // Validaciones específicas por función
        switch (condition.Function.ToLowerInvariant())
        {
            case "present" or "absent" or "carried" or "worn":
                ValidateObjectReference(condition.Arguments[0], context);
                break;

            case "at" or "notat":
                ValidateLocationReference(condition.Arguments[0], context);
                break;

            case "flag":
                ValidateFlagReference(condition.Arguments[0], context);
                break;

            case "counter":
                ValidateCounterReference(condition.Arguments[0], context);
                break;
        }
    }

    private static int? GetExpectedArgumentCount(string function)
    {
        return function.ToLowerInvariant() switch
        {
            "present" or "absent" or "carried" or "worn" => 1,
            "at" or "notat" => 1,
            "flag" => 1,
            "counter" => 1,
            "chance" => 1,
            _ => null // Función no reconocida o con argumentos variables
        };
    }

    private void ValidateObjectReference(string objectId, ParseContext context)
    {
        if (!context.IsValidObjectReference(objectId))
        {
            _logger.LogUnresolvedReference("objeto", objectId, context.CurrentLineNumber);
            context.AddUnresolvedReference(ReferenceType.Object, objectId, context.CurrentLineNumber);
        }
    }

    private void ValidateLocationReference(string locationId, ParseContext context)
    {
        if (!context.IsValidLocationReference(locationId))
        {
            _logger.LogUnresolvedReference("localidad", locationId, context.CurrentLineNumber);
            context.AddUnresolvedReference(ReferenceType.Location, locationId, context.CurrentLineNumber);
        }
    }

    private void ValidateFlagReference(string flagId, ParseContext context)
    {
        // Las flags pueden ser definidas dinámicamente, solo advertencia
        _logger.LogInformation("Referencia a flag: {FlagId}", flagId);
    }

    private void ValidateCounterReference(string counterId, ParseContext context)
    {
        // Los counters pueden ser definidos dinámicamente, solo advertencia
        _logger.LogInformation("Referencia a counter: {CounterId}", counterId);
    }
}
```

### 5.3.4 Parser de Bloques de Acciones

Implementar parsing de secuencias de acciones con control de flujo:

```csharp
// ConditionAction/ActionParser.cs
public partial class ExpressionParser
{
    public ParseResult<List<ModernAction>> ParseActionBlock(TokenStream tokens, ParseContext context)
    {
        try
        {
            var actions = new List<ModernAction>();

            tokens.Consume(TokenType.LeftBrace, "Se esperaba '{' al inicio del bloque de acciones");

            while (!tokens.IsAtEnd && !tokens.Match(TokenType.RightBrace))
            {
                var actionResult = ParseAction(tokens, context);
                if (!actionResult.IsSuccess)
                {
                    return ParseResult<List<ModernAction>>.Failure(actionResult.Error ?? "Error parsing action");
                }

                actions.Add(actionResult.Value!);

                // Las acciones pueden estar separadas por comas o saltos de línea
                tokens.TryConsume(TokenType.Comma, out _);
            }

            tokens.Consume(TokenType.RightBrace, "Se esperaba '}' al final del bloque de acciones");

            return ParseResult<List<ModernAction>>.Success(actions);
        }
        catch (ParseException ex)
        {
            return ParseResult<List<ModernAction>>.Failure(ex.Message);
        }
    }

    public ParseResult<ModernAction> ParseAction(TokenStream tokens, ParseContext context)
    {
        try
        {
            var action = ParseSingleAction(tokens, context);
            return ParseResult<ModernAction>.Success(action);
        }
        catch (ParseException ex)
        {
            return ParseResult<ModernAction>.Failure(ex.Message);
        }
    }

    private ModernAction ParseSingleAction(TokenStream tokens, ParseContext context)
    {
        // Verificar si es una estructura de control de flujo
        if (tokens.Match(TokenType.Keyword))
        {
            return tokens.Current.Value.ToLowerInvariant() switch
            {
                "if" => ParseIfAction(tokens, context),
                "while" => ParseWhileAction(tokens, context),
                _ => ParseFunctionAction(tokens, context)
            };
        }

        if (tokens.Match(TokenType.Identifier))
        {
            return ParseFunctionAction(tokens, context);
        }

        throw new ParseException($"Se esperaba acción o estructura de control, se encontró {tokens.Current.Type}", tokens.Current.LineNumber);
    }

    private ModernAction ParseFunctionAction(TokenStream tokens, ParseContext context)
    {
        var functionName = tokens.Consume(TokenType.Identifier).Value;
        tokens.Consume(TokenType.LeftParen, $"Se esperaba '(' después de la acción '{functionName}'");

        var arguments = ParseFunctionArguments(tokens);
        
        tokens.Consume(TokenType.RightParen, $"Se esperaba ')' al final de la acción '{functionName}'");

        var action = new ModernAction
        {
            Function = functionName,
            Arguments = arguments
        };

        ValidateActionFunction(action, context);
        return action;
    }

    private ModernAction ParseIfAction(TokenStream tokens, ParseContext context)
    {
        tokens.Consume(TokenType.Keyword, "Se esperaba 'if'"); // Consumir 'if'
        
        var conditionResult = ParseCondition(tokens, context);
        if (!conditionResult.IsSuccess)
        {
            throw new ParseException($"Error en condición del if: {conditionResult.Error}", tokens.Current.LineNumber);
        }

        var thenActions = ParseActionBlock(tokens, context);
        if (!thenActions.IsSuccess)
        {
            throw new ParseException($"Error en bloque then: {thenActions.Error}", tokens.Current.LineNumber);
        }

        List<ModernAction>? elseActions = null;
        if (tokens.TryConsume(TokenType.Keyword, out var elseToken) && elseToken.Value == "else")
        {
            var elseResult = ParseActionBlock(tokens, context);
            if (!elseResult.IsSuccess)
            {
                throw new ParseException($"Error en bloque else: {elseResult.Error}", tokens.Current.LineNumber);
            }
            elseActions = elseResult.Value;
        }

        return new ModernAction
        {
            Function = "if",
            Arguments = [], // La condición se almacena en ConditionExpression
            ConditionExpression = conditionResult.Value,
            ThenActions = thenActions.Value,
            ElseActions = elseActions
        };
    }

    private ModernAction ParseWhileAction(TokenStream tokens, ParseContext context)
    {
        tokens.Consume(TokenType.Keyword, "Se esperaba 'while'");
        
        var conditionResult = ParseCondition(tokens, context);
        if (!conditionResult.IsSuccess)
        {
            throw new ParseException($"Error en condición del while: {conditionResult.Error}", tokens.Current.LineNumber);
        }

        var bodyActions = ParseActionBlock(tokens, context);
        if (!bodyActions.IsSuccess)
        {
            throw new ParseException($"Error en cuerpo del while: {bodyActions.Error}", tokens.Current.LineNumber);
        }

        return new ModernAction
        {
            Function = "while",
            Arguments = [],
            ConditionExpression = conditionResult.Value,
            ThenActions = bodyActions.Value
        };
    }

    private void ValidateActionFunction(ModernAction action, ParseContext context)
    {
        var expectedArgCount = GetExpectedActionArgumentCount(action.Function);
        
        if (expectedArgCount.HasValue && action.Arguments.Count != expectedArgCount.Value)
        {
            throw new ParseException(
                $"La acción '{action.Function}' espera {expectedArgCount} argumentos, pero recibió {action.Arguments.Count}",
                context.CurrentLineNumber);
        }

        // Validaciones específicas por acción
        switch (action.Function.ToLowerInvariant())
        {
            case "take" or "drop" or "destroy" or "create":
                ValidateObjectReference(action.Arguments[0], context);
                break;

            case "goto" or "place":
                if (action.Arguments.Count > 0)
                    ValidateLocationReference(action.Arguments[0], context);
                break;

            case "message":
                ValidateMessageReference(action.Arguments[0], context);
                break;

            case "set_flag" or "clear_flag":
                ValidateFlagReference(action.Arguments[0], context);
                break;

            case "increment_counter" or "decrement_counter" or "set_counter":
                ValidateCounterReference(action.Arguments[0], context);
                break;
        }
    }

    private static int? GetExpectedActionArgumentCount(string function)
    {
        return function.ToLowerInvariant() switch
        {
            "take" or "drop" or "destroy" or "create" => 1,
            "goto" => 1,
            "message" => 1,
            "add_score" => 1,
            "set_flag" or "clear_flag" => 1,
            "increment_counter" or "decrement_counter" => 1,
            "set_counter" => 2,
            "place" => 2,
            "done" or "end_game" or "restart" => 0,
            _ => null
        };
    }

    private void ValidateMessageReference(string messageId, ParseContext context)
    {
        if (!context.IsValidMessageReference(messageId))
        {
            _logger.LogUnresolvedReference("mensaje", messageId, context.CurrentLineNumber);
            context.AddUnresolvedReference(ReferenceType.Message, messageId, context.CurrentLineNumber);
        }
    }
}
```

### 5.3.5 Contexto de Parsing Expandido

Extender ParseContext para manejar referencias y validación semántica:

```csharp
// Parser/ParseContext.cs
namespace DaadModernizado.Parser;

public enum ReferenceType
{
    Object,
    Location,
    Message,
    Flag,
    Counter
}

public record UnresolvedReference(ReferenceType Type, string Name, int LineNumber);

public class ParseContext
{
    private readonly HashSet<string> _knownObjects = new();
    private readonly HashSet<string> _knownLocations = new();
    private readonly HashSet<string> _knownMessages = new();
    private readonly List<UnresolvedReference> _unresolvedReferences = new();

    public int CurrentLineNumber { get; set; }
    public string CurrentSection { get; set; } = "";
    public IReadOnlyList<UnresolvedReference> UnresolvedReferences => _unresolvedReferences.AsReadOnly();

    // Métodos para registrar elementos conocidos
    public void AddKnownObject(string objectId) => _knownObjects.Add(objectId);
    public void AddKnownLocation(string locationId) => _knownLocations.Add(locationId);
    public void AddKnownMessage(string messageId) => _knownMessages.Add(messageId);

    // Métodos para validar referencias
    public bool IsValidObjectReference(string objectId) => _knownObjects.Contains(objectId);
    public bool IsValidLocationReference(string locationId) => _knownLocations.Contains(locationId);
    public bool IsValidMessageReference(string messageId) => _knownMessages.Contains(messageId);

    // Gestión de referencias no resueltas
    public void AddUnresolvedReference(ReferenceType type, string name, int lineNumber)
    {
        _unresolvedReferences.Add(new UnresolvedReference(type, name, lineNumber));
    }

    // Métodos para cargar referencias desde un juego parcialmente parseado
    public void LoadFromGame(ModernDaadGame game)
    {
        foreach (var objectId in game.Objects.Keys)
            AddKnownObject(objectId);

        foreach (var locationId in game.Locations.Keys)
            AddKnownLocation(locationId);

        foreach (var messageId in game.Messages.Keys)
            AddKnownMessage(messageId);
    }

    // Validar referencias no resueltas al final del parsing
    public ValidationResult ValidateReferences()
    {
        var result = new ValidationResult();

        foreach (var unresolvedRef in _unresolvedReferences)
        {
            var isValid = unresolvedRef.Type switch
            {
                ReferenceType.Object => IsValidObjectReference(unresolvedRef.Name),
                ReferenceType.Location => IsValidLocationReference(unresolvedRef.Name),
                ReferenceType.Message => IsValidMessageReference(unresolvedRef.Name),
                ReferenceType.Flag => true, // Las flags se pueden crear dinámicamente
                ReferenceType.Counter => true, // Los counters se pueden crear dinámicamente
                _ => false
            };

            if (!isValid)
            {
                result.Errors.Add($"Referencia no resuelta: {unresolvedRef.Type} '{unresolvedRef.Name}' en línea {unresolvedRef.LineNumber}");
            }
        }

        return result;
    }
}
```

### 5.3.6 Integración con Secciones de Respuestas y Procesos

Crear parsers específicos para las secciones que usan condiciones y acciones:

```csharp
// SectionParser/ResponsesSectionParser.cs
namespace DaadModernizado.Parser.Sections;

public class ResponsesSectionParser : BaseSectionParser
{
    private readonly IConditionActionParser _conditionActionParser;

    public override string SectionName => "responses";

    public ResponsesSectionParser(
        IConditionActionParser conditionActionParser,
        ILogger<ResponsesSectionParser> logger) : base(logger)
    {
        _conditionActionParser = conditionActionParser;
    }

    public override ParseSectionResult Parse(TokenStream tokens, ParseContext context)
    {
        try
        {
            var responses = new List<ModernResponse>();
            
            tokens.Consume(TokenType.LeftBrace, "Se esperaba '{' al inicio de la sección responses");

            while (!tokens.IsAtEnd && !tokens.Match(TokenType.RightBrace))
            {
                var response = ParseSingleResponse(tokens, context);
                responses.Add(response);
            }

            tokens.Consume(TokenType.RightBrace, "Se esperaba '}' al final de la sección responses");

            return new ParseSectionResult
            {
                IsSuccess = true,
                SectionData = responses
            };
        }
        catch (ParseException ex)
        {
            return new ParseSectionResult
            {
                IsSuccess = false,
                Errors = { new ParseError(ex.LineNumber, ex.Message, "responses") }
            };
        }
    }

    private ModernResponse ParseSingleResponse(TokenStream tokens, ParseContext context)
    {
        tokens.Consume(TokenType.Keyword, "Se esperaba 'on'"); // Consumir 'on'
        
        var patterns = ParseResponsePatterns(tokens);
        
        tokens.Consume(TokenType.LeftBrace, "Se esperaba '{' después de los patrones de respuesta");

        var response = new ModernResponse
        {
            Patterns = patterns
        };

        // Parsear cláusulas opcionales
        while (!tokens.IsAtEnd && !tokens.Match(TokenType.RightBrace))
        {
            if (tokens.Match(TokenType.Keyword))
            {
                switch (tokens.Current.Value.ToLowerInvariant())
                {
                    case "require":
                        tokens.Advance(); // Consumir 'require'
                        tokens.Consume(TokenType.Colon, "Se esperaba ':' después de 'require'");
                        var conditionResult = _conditionActionParser.ParseCondition(tokens, context);
                        if (!conditionResult.IsSuccess)
                            throw new ParseException($"Error en condición: {conditionResult.Error}", tokens.Current.LineNumber);
                        response.Condition = conditionResult.Value;
                        break;

                    case "do":
                        tokens.Advance(); // Consumir 'do'
                        tokens.Consume(TokenType.Colon, "Se esperaba ':' después de 'do'");
                        var actionsResult = _conditionActionParser.ParseActionBlock(tokens, context);
                        if (!actionsResult.IsSuccess)
                            throw new ParseException($"Error en bloque de acciones: {actionsResult.Error}", tokens.Current.LineNumber);
                        response.Actions = actionsResult.Value ?? new List<ModernAction>();
                        break;

                    default:
                        throw new ParseException($"Cláusula no reconocida: {tokens.Current.Value}", tokens.Current.LineNumber);
                }
            }
            else
            {
                throw new ParseException($"Se esperaba cláusula (require/do), se encontró {tokens.Current.Type}", tokens.Current.LineNumber);
            }
        }

        tokens.Consume(TokenType.RightBrace, "Se esperaba '}' al final de la respuesta");
        
        return response;
    }

    private List<string> ParseResponsePatterns(TokenStream tokens)
    {
        var patterns = new List<string>();

        if (tokens.Match(TokenType.StringLiteral))
        {
            // Patrón simple: "comando"
            patterns.Add(tokens.Advance().Value.Trim('"'));
        }
        else if (tokens.Match(TokenType.LeftBracket))
        {
            // Múltiples patrones: ["comando1", "comando2"]
            tokens.Advance(); // Consumir '['

            while (!tokens.IsAtEnd && !tokens.Match(TokenType.RightBracket))
            {
                var pattern = tokens.Consume(TokenType.StringLiteral, "Se esperaba patrón de comando").Value.Trim('"');
                patterns.Add(pattern);

                if (!tokens.TryConsume(TokenType.Comma, out _) && !tokens.Match(TokenType.RightBracket))
                {
                    throw new ParseException("Se esperaba ',' o ']' en lista de patrones", tokens.Current.LineNumber);
                }
            }

            tokens.Consume(TokenType.RightBracket, "Se esperaba ']' al final de la lista de patrones");
        }
        else
        {
            throw new ParseException("Se esperaba patrón de comando o lista de patrones", tokens.Current.LineNumber);
        }

        return patterns;
    }
}
```

### 5.3.7 Testing del Parser de Condiciones y Acciones

Implementar tests específicos para expresiones complejas:

```csharp
// Tests/ConditionActionParserTests.cs
namespace DaadModernizado.Parser.Tests;

public class ConditionActionParserTests : ParserTestBase
{
    private readonly IConditionActionParser _parser;

    public ConditionActionParserTests(ITestOutputHelper output) : base(output)
    {
        _parser = GetService<IConditionActionParser>();
    }

    [Theory]
    [InlineData("present(espada)", "present", new[] { "espada" }, false)]
    [InlineData("!carried(escudo)", "carried", new[] { "escudo" }, true)]
    [InlineData("at(bosque)", "at", new[] { "bosque" }, false)]
    public void ParseCondition_SimpleConditions_ParsesCorrectly(string input, string expectedFunction, string[] expectedArgs, bool expectedNegated)
    {
        // Arrange
        var tokens = CreateTokenStream(input);
        var context = new ParseContext();

        // Act
        var result = _parser.ParseCondition(tokens, context);

        // Assert
        Assert.True(result.IsSuccess);
        var condition = result.Value!;
        Assert.Equal(ConditionType.Simple, condition.Type);
        Assert.Equal(expectedFunction, condition.Function);
        Assert.Equal(expectedArgs, condition.Arguments);
        Assert.Equal(expectedNegated, condition.IsNegated);
    }

    [Fact]
    public void ParseCondition_ComplexLogicalExpression_ParsesWithCorrectPrecedence()
    {
        // Arrange
        var input = "present(espada) && !carried(escudo) || at(bosque)";
        var tokens = CreateTokenStream(input);
        var context = new ParseContext();

        // Act
        var result = _parser.ParseCondition(tokens, context);

        // Assert
        Assert.True(result.IsSuccess);
        var condition = result.Value!;
        Assert.Equal(ConditionType.Logical, condition.Type);
        Assert.Equal("||", condition.Operator);
        
        // Verificar que && tiene mayor precedencia que ||
        Assert.Equal("&&", condition.Left!.Operator);
    }

    [Fact]
    public void ParseActionBlock_IfElseStructure_ParsesCorrectly()
    {
        // Arrange
        var input = """
            {
              if present(llave) {
                message("Tienes la llave")
                add_score(10)
              } else {
                message("Necesitas la llave")
              }
              done
            }
            """;

        var tokens = CreateTokenStream(input);
        var context = new ParseContext();

        // Act
        var result = _parser.ParseActionBlock(tokens, context);

        // Assert
        Assert.True(result.IsSuccess);
        var actions = result.Value!;
        Assert.Equal(2, actions.Count);
        
        var ifAction = actions[0];
        Assert.Equal("if", ifAction.Function);
        Assert.NotNull(ifAction.ConditionExpression);
        Assert.NotNull(ifAction.ThenActions);
        Assert.NotNull(ifAction.ElseActions);
        Assert.Equal(2, ifAction.ThenActions.Count);
        Assert.Single(ifAction.ElseActions);
    }

    [Fact]
    public void ParseAction_NestedControlFlow_ParsesCorrectly()
    {
        // Arrange
        var input = """
            {
              while counter("vidas") > 0 {
                if present(enemigo) {
                  message("¡Combate!")
                  decrement_counter("vidas")
                }
              }
            }
            """;

        var tokens = CreateTokenStream(input);
        var context = new ParseContext();

        // Act
        var result = _parser.ParseActionBlock(tokens, context);

        // Assert
        Assert.True(result.IsSuccess);
        var actions = result.Value!;
        Assert.Single(actions);
        
        var whileAction = actions[0];
        Assert.Equal("while", whileAction.Function);
        Assert.NotNull(whileAction.ThenActions);
        
        var ifAction = whileAction.ThenActions[0];
        Assert.Equal("if", ifAction.Function);
    }

    private TokenStream CreateTokenStream(string input)
    {
        var lexer = GetService<ILexicalAnalyzer>();
        var tokenResult = lexer.Tokenize(input);
        return new TokenStream(tokenResult.Tokens);
    }
}
```

### 5.3.8 Optimización de Expresiones

Implementar optimizaciones básicas para condiciones:

```csharp
// ConditionAction/ConditionOptimizer.cs
namespace DaadModernizado.Parser.ConditionAction;

public static class ConditionOptimizer
{
    public static ModernCondition Optimize(ModernCondition condition)
    {
        return condition.Type switch
        {
            ConditionType.Simple => OptimizeSimpleCondition(condition),
            ConditionType.Logical => OptimizeLogicalCondition(condition),
            _ => condition
        };
    }

    private static ModernCondition OptimizeSimpleCondition(ModernCondition condition)
    {
        // Optimizaciones para condiciones simples
        return condition;
    }

    private static ModernCondition OptimizeLogicalCondition(ModernCondition condition)
    {
        var left = condition.Left != null ? Optimize(condition.Left) : null;
        var right = condition.Right != null ? Optimize(condition.Right) : null;

        // Optimizaciones lógicas básicas
        if (condition.Operator == "&&")
        {
            // true && X = X
            if (IsAlwaysTrue(left)) return right ?? condition;
            if (IsAlwaysTrue(right)) return left ?? condition;
            
            // false && X = false
            if (IsAlwaysFalse(left) || IsAlwaysFalse(right))
                return CreateFalseCondition();
        }
        else if (condition.Operator == "||")
        {
            // false || X = X
            if (IsAlwaysFalse(left)) return right ?? condition;
            if (IsAlwaysFalse(right)) return left ?? condition;
            
            // true || X = true
            if (IsAlwaysTrue(left) || IsAlwaysTrue(right))
                return CreateTrueCondition();
        }

        return new ModernCondition
        {
            Type = condition.Type,
            Operator = condition.Operator,
            Left = left,
            Right = right
        };
    }

    private static bool IsAlwaysTrue(ModernCondition? condition)
    {
        // Implementar detección de condiciones que siempre son verdaderas
        return false; // Simplificado por ahora
    }

    private static bool IsAlwaysFalse(ModernCondition? condition)
    {
        // Implementar detección de condiciones que siempre son falsas
        return false; // Simplificado por ahora
    }

    private static ModernCondition CreateTrueCondition()
    {
        return new ModernCondition
        {
            Type = ConditionType.Simple,
            Function = "true",
            Arguments = []
        };
    }

    private static ModernCondition CreateFalseCondition()
    {
        return new ModernCondition
        {
            Type = ConditionType.Simple,
            Function = "false",
            Arguments = []
        };
    }
}
```

Esta implementación del Parser de Condiciones y Acciones proporciona manejo robusto de expresiones lógicas complejas con validación semántica y optimización básica. En la siguiente parte (5.4) abordaremos el **Transpilador a DAAD Clásico (3D5)**, que permite la compatibilidad con el ecosistema existente.