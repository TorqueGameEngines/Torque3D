using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using Scriban;
using Scriban.Runtime;
using T3DSharpGenerator.Model;

namespace T3DSharpGenerator.Generators.Templating.Functions
{
    public class StructFieldAllocContainer : ScriptObject
    {
        public static string StructFieldAlloc(TemplateContext context, EngineStruct.Field field) {
            string name_cC = SanitizeNameContainer.SanitizeName(field.Name, false);
            string name_CC = SanitizeNameContainer.SanitizeName(field.Name, true);

            StringBuilder result = new StringBuilder();
            
            switch (field.Type) {
                case EngineStruct @struct:
                    result.AppendLine($"{name_CC}.Alloc();");
                    result.AppendLine($"internalStruct.{name_cC} = {name_CC}.internalStruct;");
                    break;
                case EngineClass @class:
                    result.AppendLine($"internalStruct.{name_cC} = {name_CC}.ObjectPtr;");
                    break;
                case EnginePrimitive @primitive when @primitive.NativeReturnType.Equals("IntPtr"):
                    result.AppendLine($"internalStruct.{name_cC} = GenericMarshal.ToPtr({name_CC});");
                    break;
                case EnginePrimitive @primitive:
                    result.AppendLine($"internalStruct.{name_cC} = {name_CC};");
                    break;
            }
            
            int indentation = Regex.Split(context.Output.ToString(), @"\r?\n|\r")
                .ToList()
                .Last()
                .Length;

            return IndentContainer.PrefixLines(result.ToString().Trim(), " ", indentation);
        }
    }
}