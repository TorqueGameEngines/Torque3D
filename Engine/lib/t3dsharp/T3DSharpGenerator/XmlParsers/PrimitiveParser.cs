using System.Xml;
using T3DSharpGenerator.Model;

namespace T3DSharpGenerator.XmlParsers
{
    internal class PrimitiveParser : IApiXmlParser
    {
        public bool Parses(XmlElement element) {
            return element.Name.Equals("EnginePrimitiveType");
        }

        public ParseState Parse(XmlElement element, ParseState parseState) {
            string name = element.Attributes["name"].InnerText;
            string docs = element.Attributes["docs"].InnerText;
            string size = element.Attributes["size"].InnerText;

            EnginePrimitive enginePrimitive = new EnginePrimitive(name) {
                Docs = docs,
                Scope = parseState.Scope,
                Size = size
            };

            AnnotateMarshallingTypes(enginePrimitive);

            parseState.Primitives.Add(enginePrimitive);
            return parseState;
        }

        private void AnnotateMarshallingTypes(EnginePrimitive enginePrimitive) {
            switch (enginePrimitive.Name) {
                case "ubyte":
                    enginePrimitive.ManagedType = "byte";
                    enginePrimitive.NativeArgType = "byte";
                    enginePrimitive.NativeReturnType = "byte";
                    break;
                case "byte":
                case "char":
                    enginePrimitive.ManagedType = "sbyte";
                    enginePrimitive.NativeArgType = "sbyte";
                    enginePrimitive.NativeReturnType = "sbyte";
                    break;
                case "string":
                case "cstring":
                    enginePrimitive.ManagedType = "string";
                    enginePrimitive.NativeArgType = "string";
                    enginePrimitive.NativeReturnType = "IntPtr";
                    break;
                case "SimObjectPtr":
                case "ptr":
                    enginePrimitive.ManagedType = "IntPtr";
                    enginePrimitive.NativeArgType = "IntPtr";
                    enginePrimitive.NativeReturnType = "IntPtr";
                    break;
                case "ptr_string":
                case "ptr_bool":
                case "ptr_Edge":
                case "ptr_PlaneF":
                case "ptr_Point3F":
                case "ptr_float":
                case "ptr_int":
                case "ptr_uint":
                    enginePrimitive.ManagedType = enginePrimitive.Name.Substring(4) + "[]";
                    enginePrimitive.NativeArgType = "IntPtr";
                    enginePrimitive.NativeReturnType = "IntPtr";
                    break;
                case "ptr_ubyte":
                    enginePrimitive.ManagedType = "byte[]";
                    enginePrimitive.NativeArgType = "IntPtr";
                    enginePrimitive.NativeReturnType = "IntPtr";
                    break;
                default:
                    enginePrimitive.ManagedType = enginePrimitive.Name;
                    enginePrimitive.NativeArgType = enginePrimitive.Name;
                    enginePrimitive.NativeReturnType = enginePrimitive.Name;
                    break;
            }
        }
    }
}