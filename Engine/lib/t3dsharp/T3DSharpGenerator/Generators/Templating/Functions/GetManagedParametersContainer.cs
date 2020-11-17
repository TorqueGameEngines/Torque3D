using System.Text;
using Scriban.Runtime;
using T3DSharpGenerator.Model;

namespace T3DSharpGenerator.Generators.Templating.Functions
{
    public class GetManagedParametersContainer : ScriptObject {
        public static string GetManagedParameters(EngineFunction function) {
            StringBuilder result = new StringBuilder();
            
            int firstArgIndex = function.IsStatic ? 0 : 1;
            
            for (var index = firstArgIndex; index < function.Arguments.Count; index++) {
                EngineFunction.Argument functionArgument = function.Arguments[index];
                result.Append(functionArgument.Type.ManagedType);
                if (functionArgument.Type is EngineStruct @struct
                    && functionArgument.DefaultValue != null) {
                    //result.Write("?");
                }

                result.Append($" {SanitizeNameContainer.SanitizeName(functionArgument.Name, false)}");
                if (functionArgument.DefaultValue != null) {
                    result.Append(DefaultParamValueContainer.DefaultParamValue(functionArgument));
                }

                if (index != function.Arguments.Count - 1) {
                    result.Append(", ");
                }
            }

            return result.ToString().Trim();
        }
    }
}