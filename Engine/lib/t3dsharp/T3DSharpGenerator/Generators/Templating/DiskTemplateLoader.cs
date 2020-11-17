using System;
using System.IO;
using System.Threading.Tasks;
using Scriban;
using Scriban.Parsing;
using Scriban.Runtime;

namespace T3DSharpGenerator.Generators.Templating {
   public class DiskTemplateLoader : ITemplateLoader {
      public string GetPath(TemplateContext context, SourceSpan callerSpan, string templateName) {
         return Path.Combine(Environment.CurrentDirectory, $"Resources/Templates/{templateName}.scriban");
      }

      public string Load(TemplateContext context, SourceSpan callerSpan, string templatePath) {
         return File.ReadAllText(templatePath);
      }

      public async ValueTask<string> LoadAsync(TemplateContext context, SourceSpan callerSpan, string templatePath) {
         using (StreamReader reader = File.OpenText(templatePath))
         {
            return await reader.ReadToEndAsync();
         }
      }
   }
}