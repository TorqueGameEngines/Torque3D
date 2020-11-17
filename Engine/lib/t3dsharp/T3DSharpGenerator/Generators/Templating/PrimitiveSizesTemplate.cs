using System.Collections.Generic;
using System.IO;
using Scriban;
using Scriban.Runtime;
using T3DSharpGenerator.Model;

namespace T3DSharpGenerator.Generators.Templating
{
    public static class PrimitiveSizesTemplate
    {
        public static string Render(List<EnginePrimitive> primitives) {
            Template template;
            using (StreamReader reader = new StreamReader("Resources/Templates/PrimitiveSizes.scriban")) {
                template = Template.Parse(reader.ReadToEnd());
            }
            
            var scriptObject = new ScriptObject {
                {"primitives", primitives}
            };
            
            scriptObject.Import(BaseTemplate.GetScriptObject());

            var context = BaseTemplate.GetTemplateContext();
            context.PushGlobal(scriptObject);
            
            return template.Render(context);
        }
    }
}