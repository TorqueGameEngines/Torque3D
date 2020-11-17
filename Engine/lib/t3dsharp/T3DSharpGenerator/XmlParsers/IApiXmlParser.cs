using System.Xml;

namespace T3DSharpGenerator.XmlParsers
{
    internal interface IApiXmlParser
    {
        bool Parses(XmlElement element);
        ParseState Parse(XmlElement element, ParseState parseState);
    }
}