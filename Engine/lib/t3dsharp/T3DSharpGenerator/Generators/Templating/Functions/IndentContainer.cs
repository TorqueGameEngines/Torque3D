using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using Scriban.Runtime;

namespace T3DSharpGenerator.Generators.Templating.Functions
{
    public class IndentContainer : ScriptObject {
        public static string Indentation = "    ";
        
        public static string Indent(string text, int levels, bool indentFirstLine = false) {
            return Regex.Split(text, @"\r?\n|\r")
                .ToList()
                .Select((x, i) => i > 0 || indentFirstLine ? Prefix(x, Indentation, levels) : x)
                .Aggregate(new StringBuilder(), (acc, x) => acc.AppendLine(x))
                .ToString();
        }
        
        public static string PrefixLines(string text, string prefix, int times = 1, bool indentFirstLine = false) {
            return Regex.Split(text, @"\r?\n|\r")
                .ToList()
                .Select((x, i) => i > 0 || indentFirstLine ? Prefix(x, prefix, times) : x)
                .Aggregate(new StringBuilder(), (acc, x) => acc.AppendLine(x))
                .ToString();
        }

        public static string Prefix(string text, string prefix, int times = 1) {
            StringBuilder result = new StringBuilder();
            for (int i = 0; i < times; ++i) {
                result.Append(prefix);
            }

            result.Append(text);

            return result.ToString();
        }
    }
}