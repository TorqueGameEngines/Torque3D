using System.Collections.Generic;
using System.Linq;
using System.Xml;
using T3DSharpGenerator.Model;
using T3DSharpGenerator.XmlParsers;

namespace T3DSharpGenerator
{
    internal class ParseState
    {
        public string Scope { get; private set; }
        public List<EngineEnum> Enums { get; }
        public List<EngineStruct> Structs { get; }
        public List<EngineFunction> Functions { get; }
        public List<EngineClass> Classes { get; }
        public List<EnginePrimitive> Primitives { get; set; }

        public ParseState() {
            Enums = new List<EngineEnum>();
            Structs = new List<EngineStruct>();
            Functions = new List<EngineFunction>();
            Classes = new List<EngineClass>();
            Primitives = new List<EnginePrimitive>();
        }

        public ParseState EnterScope(string scope) {
            if (string.IsNullOrEmpty(Scope)) {
                Scope = scope;
            } else if (!string.IsNullOrEmpty(scope)) {
                Scope += "." + scope;
            }

            return this;
        }

        public void ExitScope(string scope) {
            if (!string.IsNullOrEmpty(scope)) {
                Scope = Scope.Substring(0, Scope.Length - scope.Length);
            }

            if (Scope.EndsWith(".")) {
                Scope = Scope.Substring(0, Scope.Length - 1);
            }
        }
    }

    internal static class EngineApiParser
    {
        private static readonly List<IApiXmlParser> Parsers = new List<IApiXmlParser>() {
            new ScopeParser(),
            new ClassParser(),
            new EnumParser(),
            new StructParser(),
            new PrimitiveParser(),
            new FunctionParser(),
            new BitfieldParser()
        };

        public static EngineApi Parse(string content) {
            XmlDocument doc = new XmlDocument();
            doc.LoadXml(content);

            if (doc.DocumentElement == null) return null;

            ParseState parseState = ParseElement(doc.DocumentElement, new ParseState());

            return new EngineApi()
                .SetEnums(parseState.Enums)
                .SetStructs(parseState.Structs)
                .SetClasses(parseState.Classes)
                .SetFunctions(parseState.Functions)
                .SetPrimitives(parseState.Primitives)
                .AddVoidType()
                .AnnotateTypes()
                .AnnotateFunctionOverrides()
                .PruneSubClassProperties();
        }

        public static ParseState ParseElement(XmlElement element, ParseState parseState) {
            return Parsers.FindAll(x => x.Parses(element))
                .DefaultIfEmpty(new NotHandledParser())
                .Single()
                .Parse(element, parseState);
        }
    }
}