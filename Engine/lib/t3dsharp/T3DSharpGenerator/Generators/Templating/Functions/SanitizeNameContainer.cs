using System.Collections.Generic;
using Scriban.Runtime;

namespace T3DSharpGenerator.Generators.Templating.Functions
{
    public class SanitizeNameContainer : ScriptObject
    {
        private static readonly List<string> ReservedKeywords = new List<string> {
            "this",
            "object",
            "checked",
            "event",
            "params",
            "static",
            "string",
            "lock",
            "class"
        };

        public static string SanitizeName(string name, bool camelCase = false) {
            if (name.Equals("sizeof")) {
                return "sizeOf";
            }

            name = name.Replace('.', '_');
            name = name.Replace(' ', '_');
            name = name.Replace("+", "plus");
            name = name.Replace("-", "minus");

            if (camelCase) {
                name = char.ToUpper(name[0]) + name.Substring(1);
            }

            if (ReservedKeywords.Contains(name)) {
                name = "_" + name;
            }

            return name;
        }
    }
}