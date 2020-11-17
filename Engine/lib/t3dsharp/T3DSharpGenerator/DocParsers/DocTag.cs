namespace T3DSharpGenerator.DocParsers {
   public class DocTag {
      public string Tag;
      public string Text;
      public DocTag Next;
      public DocTag Previous;
         
      public DocTag(string s) {
         if (s.IndexOf(' ') < 0 || !s.Trim().StartsWith("@")) {
            Tag = "";
            Text = "";
            if (s.StartsWith("@")) {
               Tag = s;
            } else {
               Text = s;
            }
         } else {
            Tag = s.Substring(0, s.IndexOfAny(new []{' ', '\n'}));
            Text = s.Substring(s.IndexOfAny(new []{' ', '\n'}));
         }
         Next = null;
      }
   }
}