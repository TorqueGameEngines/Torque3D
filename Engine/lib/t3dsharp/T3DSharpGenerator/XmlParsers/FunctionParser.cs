using System.Xml;
using T3DSharpFramework.Interop;
using T3DSharpGenerator.Model;

namespace T3DSharpGenerator.XmlParsers
{
    internal class FunctionParser : IApiXmlParser
    {
        public bool Parses(XmlElement element) {
            return element.Name.Equals("EngineFunction");
        }

        public ParseState Parse(XmlElement element, ParseState parseState) {
            string name = element.Attributes["name"].InnerText;
            string docs = element.Attributes["docs"].InnerText;
            string returnType = element.Attributes["returnType"].InnerText;
            string symbol = element.Attributes["symbol"].InnerText;
            bool isCallback = GenericMarshal.StringToBool(element.Attributes["isCallback"].InnerText);
            bool isVariadic = GenericMarshal.StringToBool(element.Attributes["isVariadic"].InnerText);
            
            
            EngineFunction engineFunction = new EngineFunction(name) {
                Docs = docs,
                ReturnTypeName = returnType,
                Symbol = symbol,
                IsCallback = isCallback,
                IsVariadic = isVariadic,
                Scope = parseState.Scope
            };

            foreach (XmlElement childNode in element.ChildNodes[0].ChildNodes) {
                engineFunction.Add(new EngineFunction.Argument() {
                    Name = childNode.Attributes["name"].InnerText,
                    TypeName = childNode.Attributes["type"].InnerText,
                    DefaultValue = childNode.Attributes["defaultValue"]?.InnerText
                });
            }
            
            // Assume that functions that take a first parameter named "this"
            // and with the same type as the current Scope (class), are methods.
            if (engineFunction.Arguments.Count >= 1
                && engineFunction.Arguments[0].Name.Equals("this")) {
                string arg0 = engineFunction.Arguments[0].TypeName;
                int lastIndexOfColon = arg0.LastIndexOf(':');
                if (lastIndexOfColon > 0) {
                    arg0 = arg0.Remove(0, lastIndexOfColon + 1);
                }
                engineFunction.IsStatic = !parseState.Scope.EndsWith(arg0);
            }

            int firstArgIndex = 0;
            if (!engineFunction.IsStatic) {
                firstArgIndex = 1;
            }
            
            // TODO special-handling of argc, argv parameters to mark them as variadic. This is an assumption.
            if (engineFunction.Arguments.Count == 2
                && engineFunction.Arguments[0].Name.Equals("argc")
                && engineFunction.Arguments[1].Name.Equals("argv")) {
                engineFunction.IsVariadic = true;
            } else if(engineFunction.Arguments.Count == firstArgIndex + 1
                      && engineFunction.Arguments[firstArgIndex].Name.Equals("args")
                      && engineFunction.Arguments[firstArgIndex].TypeName.Equals("StringVector")) {
                engineFunction.IsVariadic = true;
            }
            
            // False by default, only class can set this to true.
            engineFunction.IsOverride = false;
            
            parseState.Functions.Add(engineFunction);
            
            return parseState;
        }
    }
}