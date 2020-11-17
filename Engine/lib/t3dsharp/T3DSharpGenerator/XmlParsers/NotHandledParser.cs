using System;
using System.Xml;

namespace T3DSharpGenerator.XmlParsers
{
    internal class NotHandledParser : IApiXmlParser
    {
        public bool Parses(XmlElement element) {
            return true;
        }

        public ParseState Parse(XmlElement element, ParseState parseState) {
            Console.WriteLine("Element with type " + element.Name + " was not handled");
            return parseState;
        }
    }
}