using System.Xml;
using T3DSharpGenerator.Model;

namespace T3DSharpGenerator.XmlParsers
{
    internal class BitfieldParser : IApiXmlParser
    {
        public bool Parses(XmlElement element) {
            return element.Name.Equals("EngineBitfieldType");
        }

        public ParseState Parse(XmlElement element, ParseState parseState) {
            return new EnumParser().Parse(element, parseState);
        }
    }
}