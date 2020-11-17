using System.Collections.Generic;
using System.IO;
using Scriban;
using Scriban.Runtime;
using T3DSharpGenerator.Model;

namespace T3DSharpGenerator.Generators.Templating {
   public static class StructTemplate {
      public static string Render(List<EngineStruct> structs, string scope) {
         Template template;
         using (StreamReader reader = new StreamReader("Resources/Templates/SimStruct.scriban")) {
            template = Template.Parse(reader.ReadToEnd());
         }

         var scriptObject = new ScriptObject {
            {"structs", structs},
            {"scope", scope}
         };

         scriptObject.Import(BaseTemplate.GetScriptObject());

         var context = BaseTemplate.GetTemplateContext();
         context.PushGlobal(scriptObject);

         return template.Render(context);
      }
   }
}