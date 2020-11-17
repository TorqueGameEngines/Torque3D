using System.Diagnostics.Eventing.Reader;
using System.Xml;
using T3DSharpGenerator.Model;

namespace T3DSharpGenerator.XmlParsers
{
    internal class StructParser : IApiXmlParser
    {
        public bool Parses(XmlElement element) {
            return element.Name.Equals("EngineStructType");
        }

        public ParseState Parse(XmlElement element, ParseState parseState) {
            string name = element.Attributes["name"].InnerText;
            string docs = element.Attributes["docs"].InnerText;

            EngineStruct engineStruct = new EngineStruct(name) {
                Docs = docs,
                Scope = parseState.Scope
            };

            foreach (XmlElement childNode in element.ChildNodes) {
                if (!childNode.Name.Equals("fields")) continue;
                foreach (XmlElement fieldNode in childNode.ChildNodes) {
                    engineStruct.Add(new EngineStruct.Field() {
                        Name = fieldNode.Attributes["name"].InnerText,
                        TypeName = fieldNode.Attributes["type"].InnerText,
                        Offset = fieldNode.Attributes["offset"].InnerText,
                        Docs = fieldNode.Attributes["docs"].InnerText,
                        IndexedSize = int.Parse(fieldNode.Attributes["indexedSize"].InnerText)
                    });
                }
            }

            parseState.Structs.Add(engineStruct);
            return parseState;
        }
    }
}
