using Scriban;
using Scriban.Runtime;

namespace T3DSharpGenerator.Generators.Templating
{
    public static class BaseTemplate
    {
        public static TemplateContext GetTemplateContext() {
            var context = new TemplateContext();
            context.TemplateLoader = new DiskTemplateLoader();
            return context;
        }

        public static ScriptObject GetScriptObject() {
            ScriptObject scriptObject = new ScriptObject();
            scriptObject.Import(new Functions.SanitizeNameContainer());
            scriptObject.Import(new Functions.MarshalAsContainer());
            scriptObject.Import(new Functions.GetManagedParametersContainer());
            scriptObject.Import(new Functions.GetReturnStringContainer());
            scriptObject.Import(new Functions.AllocContainer());
            scriptObject.Import(new Functions.FreeContainer());
            scriptObject.Import(new Functions.MarshalContainer());
            scriptObject.Import(new Functions.MarshalAsContainer());
            scriptObject.Import(new Functions.DefaultParamValueContainer());
            scriptObject.Import(new Functions.StructFieldAllocContainer());
            scriptObject.Import(new Functions.StructFieldFreeContainer());
            scriptObject.Import(new Functions.IndentContainer());

            return scriptObject;
        }
    }
}