using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Scriban.Runtime;
using T3DSharpGenerator.Generators.Templating;
using T3DSharpGenerator.Model;

namespace T3DSharpGenerator.Generators
{
    public static class StructGenerator
    {
        public static void GenerateFor(string outputDir, EngineApi engineApi, List<EngineStruct> structs) {
            structs.GroupBy(x => x.Scope)
                .Select(x => new {Scope = x.Key, Structs = x})
                .ToList()
                .ForEach(x => GenerateStructsInScope(outputDir, engineApi, x.Structs, x.Scope));
        }

        private static void GenerateStructsInScope(string outputDir, EngineApi engineApi, IEnumerable<EngineStruct> structs, string scope) {
            scope = string.IsNullOrEmpty(scope) ? "Global" : scope;
            
            string output = StructTemplate.Render(structs.ToList(), scope);
            
            Console.WriteLine(scope + "_structs.cs");

            Directory.CreateDirectory($"{outputDir}/Structs");
            
            using (StreamWriter SW = new StreamWriter($"{outputDir}/Structs/{scope}.cs")) {
                SW.Write(output);        
            }
        }
    }
}
