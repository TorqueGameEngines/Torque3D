using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using T3DSharpGenerator.Generators.Templating;
using T3DSharpGenerator.Model;

namespace T3DSharpGenerator.Generators
{
    public static class EnumGenerator
    {
        public static void GenerateFor(string outputDir, EngineApi engineApi, List<EngineEnum> enums) {
            enums.GroupBy(x => x.Scope)
                .Select(x => new {Scope = x.Key, Enums = x})
                .ToList()
                .ForEach(x => GenerateEnumsInScope(outputDir, engineApi, x.Enums.ToList(), x.Scope));
        }

        private static void GenerateEnumsInScope(string outputDir, EngineApi engineApi, List<EngineEnum> enums, string scope) {
            scope = string.IsNullOrEmpty(scope) ? "Global" : scope;
            
            string output = EnumTemplate.Render(enums, scope);
            
            Console.WriteLine(scope + "_enums.cs");

            Directory.CreateDirectory($"{outputDir}/Enums");

            using (StreamWriter SW =
                new StreamWriter($"{outputDir}/Enums/{scope}.cs")) {
                SW.Write(output);
            }
        }
    }
}
