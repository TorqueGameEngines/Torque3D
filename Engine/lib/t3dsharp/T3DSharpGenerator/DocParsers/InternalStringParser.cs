using T3DSharpGenerator.Model.Docs;

namespace T3DSharpGenerator.DocParsers {
   public class InternalStringParser : IDocStringParser {
      public bool MatchesTag(DocTag tag) {
         return tag.Tag.Equals("@internal");
      }
      
      public IDocElement Parse(DocTag tag) {
         return new InternalDocElement();
      }
   }
}