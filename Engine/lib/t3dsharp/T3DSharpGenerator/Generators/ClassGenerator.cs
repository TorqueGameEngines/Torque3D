using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Scriban.Runtime;
using T3DSharpGenerator.Generators.Templating;
using T3DSharpGenerator.Generators.Util;
using T3DSharpGenerator.Model;

namespace T3DSharpGenerator.Generators
{
    public static class ClassGenerator
    {
        public static void GenerateFor(string outputDir, EngineApi engineApi, List<EngineClass> classes) {
            List<EngineClass> simObjectClasses = SimObjectTree.BuildAsList(classes);

            simObjectClasses.ForEach(x => x.Scope = $"Sim{(string.IsNullOrEmpty(x.Scope) ? "" : "." + x.Scope)}");
            
            simObjectClasses.ForEach(x => GenerateFor(outputDir, engineApi, x));

            List<EngineClass> otherClasses = classes.Where(c => !simObjectClasses.Any(c2 => c.Name.Equals(c2.Name)))
                .ToList();

            Console.WriteLine("Other classes:");
            otherClasses.ForEach(x => Console.WriteLine(x.Name));
            Console.WriteLine("End.");
            otherClasses.ForEach(x => GenerateFor(outputDir, engineApi, x));
        }
        
        private static void GenerateFor(string outputDir, EngineApi engineApi, EngineClass @class) {
            string scope = (string.IsNullOrEmpty(@class.Scope) ? "Global" : @class.Scope);

            var scriptObject = new ScriptObject();
            scriptObject.Add("class", @class);
            scriptObject.Add("scope", scope);

            string output = ClassTemplate.Render(@class, scope);

            string dir = $"{outputDir}/Classes/{scope.Replace('.', '/')}";
            
            Console.WriteLine($"{dir}/{@class.Name}.cs");

            Directory.CreateDirectory(dir);

            using (StreamWriter SW = new StreamWriter($"{dir}/{@class.Name}.cs")
            ) {
                SW.Write(output);
            }
        }
    }
}
