using T3DSharpGenerator.Model.Docs;

namespace T3DSharpGenerator.DocParsers {
   public interface IDocStringParser {
      bool MatchesTag(DocTag tag);
      
      IDocElement Parse(DocTag tag);
   }
}