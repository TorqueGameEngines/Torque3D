using System.Collections.Generic;
using T3DSharpGenerator.Model.Docs;

namespace T3DSharpGenerator.DocParsers {
   public class CodeExampleStringParser : IDocStringParser {
      public bool MatchesTag(DocTag tag) {
         return tag.Tag.Equals("@tsexample");
      }
      
      public IDocElement Parse(DocTag tag) {
         return new CodeExampleDocElement {
            Language = "TorqueScript",
            Children = new List<IDocElement>() {
               new TextDocElement {
                  Text = tag.Text.Trim()
               }
            }
         };
      }
   }
}