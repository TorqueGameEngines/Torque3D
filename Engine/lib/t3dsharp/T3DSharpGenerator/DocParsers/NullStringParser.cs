using T3DSharpGenerator.Model.Docs;

namespace T3DSharpGenerator.DocParsers {
   public class NullStringParser : IDocStringParser {
      public bool MatchesTag(DocTag tag) {
         return string.IsNullOrWhiteSpace(tag.Tag) && string.IsNullOrWhiteSpace(tag.Text)
            || tag.Tag.StartsWith("(")
            || tag.Tag.StartsWith("@")
            || tag.Tag.StartsWith("@endtsexample")
            || tag.Tag.StartsWith("@hide");
      }
      
      public IDocElement Parse(DocTag tag) {
         return new NullDocElement {
            Tag = tag.Tag,
            Text = tag.Text
         };
      }
   }
}