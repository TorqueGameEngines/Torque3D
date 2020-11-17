using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using Scriban;
using Scriban.Runtime;
using T3DSharpGenerator.Model;

namespace T3DSharpGenerator.Generators.Templating.Functions
{
    public class StructFieldFreeContainer : ScriptObject
    {
        public static string StructFieldFree(TemplateContext context, EngineStruct.Field field) {
            string name_cC = SanitizeNameContainer.SanitizeName(field.Name, false);
            string name_CC = SanitizeNameContainer.SanitizeName(field.Name, true);
            string baseType = field.Type.ManagedType;
            if (baseType.StartsWith("ptr_")) {
                baseType = baseType.Substring(4);
            }
            
            StringBuilder result = new StringBuilder();

            switch (field.Type) {
                case EngineStruct @struct:
                    result.AppendLine($"{name_CC}?.Free();");
                    result.AppendLine($"{name_CC} = new {@struct.ManagedType}(internalStruct.{name_cC});");
                    break;
                case EngineClass @class:
                    result.AppendLine($"{name_CC}.ObjectPtr = internalStruct.{name_cC};");
                    break;
                case EnginePrimitive @primitive when @primitive.NativeReturnType.Equals("IntPtr"):
                    baseType = baseType.Substring(0, baseType.Length - 2);
                    if (field.IndexedSize > 1) {
                        result.AppendLine($"{name_CC} = GenericMarshal.FromPtr<{baseType}>(internalStruct.{name_cC}, {field.IndexedSize}, true);");
                    } else {
                        result.AppendLine($"{name_CC} = GenericMarshal.FromPtr<{baseType}>(internalStruct.{name_cC}, ElementCount, true);");
                    }
                    break;
                case EnginePrimitive @primitive:
                    result.AppendLine($"{name_CC} = internalStruct.{name_cC};");
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