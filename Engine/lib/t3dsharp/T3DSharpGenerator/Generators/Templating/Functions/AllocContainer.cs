using System.Text;
using Scriban.Runtime;
using T3DSharpGenerator.Model;

namespace T3DSharpGenerator.Generators.Templating.Functions
{
    public class AllocContainer : ScriptObject {
        public static string Alloc(EngineFunction.Argument arg) {
            StringBuilder result = new StringBuilder();
            
            if (arg.Type is EngineStruct @struct)
            {
                string argName = SanitizeNameContainer.SanitizeName(arg.Name, false);
                if (arg.DefaultValue != null)
                {
                    result.AppendLine($"{argName} = {argName} ?? new {@struct.Name}(\"{arg.DefaultValue}\");");
                }

                result.Append($"{argName}.Alloc();");
            }

            return result.ToString().Trim();
        }
    }
}