using System.Text;
using Scriban.Runtime;
using T3DSharpGenerator.Model;

namespace T3DSharpGenerator.Generators.Templating.Functions
{
    public class GetReturnStringContainer : ScriptObject {
        public static string GetReturnString(IEngineObject type, string variable) {
            StringBuilder result = new StringBuilder();
            
            if (type.ManagedType != "void") {
                result.Append("return ");
            } 
            
            if (type is EngineEnum @enum) {
                result.Append($"({@enum.ManagedType}){variable}");
            } else if (type.NativeReturnType == "IntPtr" && type.ManagedType == "string") {
                result.Append($"StringMarshal.IntPtrToUtf8String({variable})");
            } else if (type.NativeReturnType == "IntPtr" && type.ManagedType != "IntPtr") {
                if (type.ManagedType == "SimObjectPtr*") {
                    result.Append($"(SimObjectPtr*){variable}");
                } else {
                    result.Append($"new {type.ManagedType}({variable})");
                }
            } else if (type is EngineStruct) {
                result.Append($"new {type.ManagedType}({variable})");
            } else {
                result.Append(variable);
            }

            return result.ToString().Trim();
        }
    }
}