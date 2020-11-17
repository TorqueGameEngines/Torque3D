using T3DSharpGenerator.Model.Docs;

namespace T3DSharpGenerator.DocParsers {
   public class ParameterRefStringParser : IDocStringParser {
      public bool MatchesTag(DocTag tag) {
         return tag.Tag.Equals("@a");
      }
      
      public IDocElement Parse(DocTag tag) {
         return new ParameterRefDocElement {
            ParameterName = tag.Text.Substring(0, tag.Text.IndexOf(' ')),
            Remainder = tag.Text.Substring(tag.Text.IndexOf(' '))
         };
      }
   }
}