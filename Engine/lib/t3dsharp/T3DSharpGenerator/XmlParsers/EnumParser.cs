using System.Xml;
using T3DSharpGenerator.Model;

namespace T3DSharpGenerator.XmlParsers
{
    internal class EnumParser : IApiXmlParser
    {
        public bool Parses(XmlElement element) {
            return element.Name.Equals("EngineEnumType");
        }

        public ParseState Parse(XmlElement element, ParseState parseState) {
            string name = element.Attributes["name"].InnerText;
            string docs = element.Attributes["docs"].InnerText;

            EngineEnum engineEnum = new EngineEnum(name) {
                Docs = docs,
                Scope = parseState.Scope
            };

            foreach (XmlElement childNode in element.ChildNodes[0].ChildNodes) {
                engineEnum.Add(new EngineEnum.Field() {
                    Name = childNode.Attributes["name"].InnerText,
                    Value = int.Parse(childNode.Attributes["value"].InnerText),
                    Docs = childNode.Attributes["docs"].InnerText
                });
            }

            parseState.Enums.Add(engineEnum);
            
            return parseState;
        }
    }
}