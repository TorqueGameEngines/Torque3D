using System.Text;
using Scriban.Runtime;
using T3DSharpGenerator.Model;

namespace T3DSharpGenerator.Generators.Templating.Functions
{
    public class FreeContainer : ScriptObject {
        public static string Free(EngineFunction.Argument arg) {
            StringBuilder result = new StringBuilder();
            
            if (arg.Type is EngineStruct @struct) {
                result.Append($"{SanitizeNameContainer.SanitizeName(arg.Name, false)}.Free();");
            }

            return result.ToString().Trim();
        }
    }
}