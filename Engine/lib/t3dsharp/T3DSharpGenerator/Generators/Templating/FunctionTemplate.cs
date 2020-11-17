using System.Collections;
using System.Collections.Generic;
using System.IO;
using Scriban;
using Scriban.Runtime;
using T3DSharpGenerator.Model;

namespace T3DSharpGenerator.Generators.Templating
{
    public static class FunctionTemplate
    {
        public static string Render(List<EngineFunction> functions, string scope, string scopeClass) {
            Template template;
            using (StreamReader reader = new StreamReader("Resources/Templates/SimFunction.scriban")) {
                template = Template.Parse(reader.ReadToEnd());
            }
            
            var scriptObject = new ScriptObject {
                {"functions", functions},
                {"scope", scope},
                {"scopeClass", scopeClass}
            };
            
            scriptObject.Import(BaseTemplate.GetScriptObject());

            var context = BaseTemplate.GetTemplateContext();
            context.PushGlobal(scriptObject);
            
            return template.Render(context);
        }
    }
}