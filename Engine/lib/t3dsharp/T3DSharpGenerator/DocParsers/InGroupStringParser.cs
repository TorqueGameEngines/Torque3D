using T3DSharpGenerator.Model.Docs;

namespace T3DSharpGenerator.DocParsers {
   public class InGroupStringParser : IDocStringParser {
      public bool MatchesTag(DocTag tag) {
         return tag.Tag.Equals("@ingroup");
      }
      
      public IDocElement Parse(DocTag tag) {
         return new InGroupDocElement {
            GroupName = tag.Text
         };
      }
   }
}