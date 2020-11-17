using System.Collections.Generic;
using T3DSharpGenerator.Model.Docs;

namespace T3DSharpGenerator.DocParsers {
   public class ParameterStringParser : IDocStringParser {
      public bool MatchesTag(DocTag tag) {
         return tag.Tag.Equals("@param")
                || tag.Tag.Equals("@params");
      }

      public IDocElement Parse(DocTag tag) {
         string text = tag.Text.Trim();
         if (text.IndexOf(' ') > -1) {
            return new ParameterDocElement {
               ParameterName = text.Substring(0, text.IndexOf(' ')),
               Children = new List<IDocElement>() {
                  new TextDocElement {
                     Text = text.Substring(text.IndexOf(' ')).Trim()
                  }
               }
            };
         } else {
            return new ParameterDocElement {
               ParameterName = text
            };
         }
      }
   }
}