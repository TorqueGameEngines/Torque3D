using System.Text;
using Scriban.Runtime;
using T3DSharpGenerator.Model;

namespace T3DSharpGenerator.Generators.Templating.Functions
{
    public class MarshalContainer : ScriptObject {
        public static string Marshal(EngineFunction.Argument arg) {
            StringBuilder result = new StringBuilder();

            string name = SanitizeNameContainer.SanitizeName(arg.Name);
            
            switch (arg.Type) {
                case EngineClass @class:
                    result.Append($"{name}.ObjectPtr");
                    break;
                case EngineEnum @enum:
                    result.Append($"(int){name}");
                    break;
                case EngineStruct @struct:
                    //result.Write($"GenericMarshal.ToPtr({arg.Name}");
                    result.Append($"{name}.internalStructPtr");
                    //result.Write($"StructMarshal.StructToIntPtr(({arg.Name}");
                    //result.Write($"ref ({arg.Name}");
                    //if (arg.DefaultValue != null) {
                    //    result.Write($" ?? new {@struct.Name}(\"{arg.DefaultValue}\")");
                    //}
                    //result.Write(").internalStruct)");
                break;
                default:
                    result.Append($"{name}");
                    break;
            }

            return result.ToString().Trim();
        }
    }
}