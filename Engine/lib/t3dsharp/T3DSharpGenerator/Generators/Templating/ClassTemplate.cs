using System.IO;
using Scriban.Runtime;
using T3DSharpGenerator.Model;
using Template = Scriban.Template;

namespace T3DSharpGenerator.Generators.Templating
{
    public static class ClassTemplate
    {
        public static string Render(EngineClass @class, string scope) {
            Template template;
            using (StreamReader reader = new StreamReader("Resources/Templates/SimClass.scriban")) {
                template = Template.Parse(reader.ReadToEnd(), "Resources/Templates/SimClass.scriban");
            }

            var scriptObject = new ScriptObject {
                {"class", @class}, 
                {"scope", scope}
            };

            scriptObject.Import(BaseTemplate.GetScriptObject());

            var context = BaseTemplate.GetTemplateContext();
            context.PushGlobal(scriptObject);
            
            return template.Render(context);
        }
    }
}