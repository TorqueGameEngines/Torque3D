using Scriban.Runtime;
using T3DSharpGenerator.Model;

namespace T3DSharpGenerator.Generators.Templating.Functions
{
    public class DefaultParamValueContainer : ScriptObject {
        public static string DefaultParamValue(EngineFunction.Argument arg) {
            if (arg.DefaultValue == null) return "";


            if (arg.Type.ManagedType.Equals("string")) {
                return $" = \"{arg.DefaultValue}\"";
            }

            if (arg.Type is EnginePrimitive @primitive) {
                string result = "";
                result += $" = {arg.DefaultValue}";
                if (@primitive.ManagedType == "float"
                    && !arg.DefaultValue.EndsWith("f")) {
                    result += "f";
                }

                return result;
            }

            if (arg.Type is EngineStruct @struct) {
                return $" = null";
            }

            if (arg.Type is EngineClass @class) {
                if (arg.DefaultValue.Equals("null")) {
                    return $" = null";
                }
            }

            if (arg.Type is EngineEnum @enum) {
                return $" = {@enum.Name}.{SanitizeNameContainer.SanitizeName(arg.DefaultValue, true)}";
            }

            return "<<Unhandled defaultValue type.>>";
        }
    }
}