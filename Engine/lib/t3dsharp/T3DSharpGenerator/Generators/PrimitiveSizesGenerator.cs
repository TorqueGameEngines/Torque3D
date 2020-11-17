using System;
using System.Collections.Generic;
using System.IO;
using T3DSharpGenerator.Generators.Templating;
using T3DSharpGenerator.Model;

namespace T3DSharpGenerator.Generators
{
    public static class PrimitiveSizesGenerator
    {
        public static void GenerateFor(string outputDir, EngineApi engineApi, List<EnginePrimitive> primitives) {
            string output = PrimitiveSizesTemplate.Render(primitives);
            
            Console.WriteLine("PrimitiveSizes.cs");

            Directory.CreateDirectory(outputDir);
            
            using (StreamWriter SW = new StreamWriter($"{outputDir}/PrimitiveSizes.cs")) {
                SW.Write(output);        
            }
        }
    }
}
