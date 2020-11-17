using System.Collections.Generic;
using T3DSharpGenerator.Model.Docs;

namespace T3DSharpGenerator.DocParsers {
   public class RemarkStringParser : IDocStringParser {
      public bool MatchesTag(DocTag tag) {
         return tag.Tag.Equals("@note");
      }
      
      public IDocElement Parse(DocTag tag) {
         return new RemarkDocElement {
            Children = new List<IDocElement>() {
               new TextDocElement {
                  Text = tag.Text
               }
            }
         };
      }
   }
}