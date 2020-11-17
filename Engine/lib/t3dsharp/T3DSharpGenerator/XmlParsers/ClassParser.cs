using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Xml;
using T3DSharpFramework.Interop;
using T3DSharpGenerator.Model;

namespace T3DSharpGenerator.XmlParsers
{
    internal class ClassParser : IApiXmlParser
    {
        public bool Parses(XmlElement element) {
            return element.Name.Equals("EngineClassType");
        }

        public ParseState Parse(XmlElement element, ParseState parseState) {
            string name = element.Attributes["name"].InnerText;
            string docs = element.Attributes["docs"].InnerText;
            string superType = element.Attributes["superType"]?.InnerText;
            bool isAbstract = GenericMarshal.StringToBool(element.Attributes["isAbstract"].InnerText);
            bool isInstantiable = GenericMarshal.StringToBool(element.Attributes["isInstantiable"].InnerText);
            bool isDisposable = GenericMarshal.StringToBool(element.Attributes["isDisposable"].InnerText);
            bool isSingleton = GenericMarshal.StringToBool(element.Attributes["isSingleton"].InnerText);

            EngineClass engineClass = new EngineClass(name) {
                Docs = docs,
                SuperTypeName = superType,
                Scope = parseState.Scope,
                IsAbstract = isAbstract,
                IsInstantiable = isInstantiable,
                IsDisposable = isDisposable,
                IsSingleton = isSingleton
            };

            ParseState functionParseState = new ParseState()
                .EnterScope(name);

            foreach (XmlElement childNode in element.ChildNodes) {
                if (childNode.Name.Equals("properties")) {
                    List<EngineClass.Property> properties = ParseProperties(childNode, null);
                    foreach (EngineClass.Property property in properties) {
                        engineClass.Add(property);
                    }
                } else if (childNode.Name.Equals("exports")) {
                    foreach (XmlElement funElement in childNode.ChildNodes) {
                        if (funElement.Name.Equals("RegisterObject")) Debugger.Break();
                        new FunctionParser().Parse(funElement, functionParseState);
                    }
                } else {
                }
            }

            foreach (EngineFunction engineFunction in functionParseState.Functions) {
                engineClass.Add(engineFunction);
            }

            parseState.Classes.Add(engineClass);

            return parseState;
        }

        private List<EngineClass.Property> ParseProperties(XmlElement childNode, string group) {
            List<EngineClass.Property> properties = new List<EngineClass.Property>();
            foreach (XmlElement propElement in childNode.ChildNodes) {
                if (propElement.Name.Equals("EngineProperty")) {
                    EngineClass.Property property = new EngineClass.Property() {
                        Name = propElement.Attributes["name"].InnerText,
                        Docs = propElement.Attributes["docs"].InnerText,
                        TypeName = propElement.Attributes["type"].InnerText,
                        IndexedSize = int.Parse(propElement.Attributes["indexedSize"].InnerText),
                        Group = group,
                        IsConstant = propElement.Attributes["isConstant"].InnerText,
                        IsTransient = propElement.Attributes["isTransient"].InnerText,
                        IsVisible = propElement.Attributes["isVisible"].InnerText
                    };
                    if (property.TypeName.Equals("deprecated")) {
                        Console.WriteLine($"Property {property.Name} is deprecated, so it is ignored.");
                    } else {
                        properties.Add(property);
                    }
                } else {
                    string newGroupName = propElement.Attributes["name"].InnerText;
                    properties.AddRange(ParseProperties((XmlElement) propElement.ChildNodes[0],
                        newGroupName.Substring(0, newGroupName.Length - "_begingroup".Length)));
                }
            }

            return properties;
        }
    }
}