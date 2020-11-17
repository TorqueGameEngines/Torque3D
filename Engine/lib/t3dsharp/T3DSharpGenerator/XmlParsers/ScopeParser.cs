using System;
using System.Xml;

namespace T3DSharpGenerator.XmlParsers
{
    internal class ScopeParser : IApiXmlParser
    {
        public bool Parses(XmlElement element) {
            return element.Name.Equals("EngineExportScope");
        }

        public ParseState Parse(XmlElement element, ParseState parseState) {
            Console.WriteLine("Parsing scope with: " + element.Attributes["name"].InnerText,
                ", " + element.Attributes["docs"].InnerText);

            parseState.EnterScope(element.Attributes["name"].InnerText);
            foreach (XmlElement childNode in element.ChildNodes[0].ChildNodes) {
                parseState = EngineApiParser.ParseElement(childNode, parseState);
            }
            parseState.ExitScope(element.Attributes["name"].InnerText);
            
            return parseState;
        }
    }
}