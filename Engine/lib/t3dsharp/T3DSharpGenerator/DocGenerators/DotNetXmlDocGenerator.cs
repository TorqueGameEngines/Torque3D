using System;
using System.Linq;
using T3DSharpGenerator.Model.Docs;

namespace T3DSharpGenerator.DocGenerators {
   public class DotNetXmlDocGenerator {
      public static string Generate(IDocElement docElement) {
         string content = docElement.GetChildren()
            .Select(Generate)
            .Aggregate("", (acc, x) => acc + x);
         switch (docElement) {
            case SummaryDocElement summaryDocElement:
               return $"<summary>{content}</summary>\n";
            case DescriptionDocElement descriptionDocElement:
               return $"<description>\n{content}\n</description>\n";
            case CodeExampleDocElement codeExampleDocElement:
               return $"<code>\n{content}\n</code>\n";
            case ParameterDocElement parameterDocElement:
               return $"<param name=\"{parameterDocElement.ParameterName}\">{content}</param>\n";
            case RemarkDocElement remarkDocElement:
               return $"<remarks>{content}</remarks>\n";
            case ReturnDocElement returnDocElement:
               return $"<returns>{content}</returns>\n";
            case SeeDocElement seeDocElement:
               if (seeDocElement.Element.StartsWith("http")) {
                  return $"<see href=\"{seeDocElement.Element}\" />\n";
               }
               return $"<see cref=\"{seeDocElement.Element}\" />\n";
            case TextDocElement textDocElement:
               return textDocElement.Text;
            case NullDocElement nullDocElement:
               return nullDocElement.Tag + nullDocElement.Text;
            case ParameterRefDocElement parameterRefDocElement:
               return $"<paramref name=\"{parameterRefDocElement.ParameterName}\" />";
            case InGroupDocElement inGroupDocElement:
               // No equivalent
               return "";
            case InternalDocElement internalDocElement:
               // No equivalent
               return "";
            case CompoundDocElement compoundDocElement:
               return content;
            default:
               throw new NotImplementedException();
         }
      }
   }
}