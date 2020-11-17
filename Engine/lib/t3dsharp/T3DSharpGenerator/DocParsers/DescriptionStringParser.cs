using System.Collections.Generic;
using T3DSharpGenerator.Model.Docs;

namespace T3DSharpGenerator.DocParsers {
   public class DescriptionStringParser : IDocStringParser {
      public bool MatchesTag(DocTag tag) {
         return !string.IsNullOrWhiteSpace(tag.Text) &&
                (string.IsNullOrWhiteSpace(tag.Tag)
                 || !tag.Tag.StartsWith("(") && !tag.Tag.StartsWith("@")
                );
      }

      public IDocElement Parse(DocTag tag) {
         return new DescriptionDocElement {
            Children = new List<IDocElement>() {
               new TextDocElement {
                  Text = tag.Text.Trim()
               }
            }
         };
      }
   }
}