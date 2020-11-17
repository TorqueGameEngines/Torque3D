using T3DSharpGenerator.Model.Docs;

namespace T3DSharpGenerator.DocParsers {
   public class SeeStringParser : IDocStringParser {
      public bool MatchesTag(DocTag tag) {
         return tag.Tag.Equals("@see");
      }
      
      public IDocElement Parse(DocTag tag) {
         return new SeeDocElement {
            Element = tag.Text.Trim()
         };
      }
   }
}