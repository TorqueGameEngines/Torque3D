using System.Collections.Generic;
using T3DSharpGenerator.Model.Docs;

namespace T3DSharpGenerator.DocParsers {
   public class ReturnStringParser : IDocStringParser {
      public bool MatchesTag(DocTag tag) {
         return tag.Tag.Equals("@return")
            || tag.Tag.Equals("@returns");
      }
      
      public IDocElement Parse(DocTag tag) {
         return new ReturnDocElement {
            Children = new List<IDocElement>() {
               new TextDocElement {
                  Text = tag.Text.Trim()
               }
            }
         };
      }
   }
}