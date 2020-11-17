using System.Collections.Generic;

namespace T3DSharpGenerator.Model.Docs {
   public class DocElement : IDocElement {
      public List<IDocElement> Children = new List<IDocElement>();
      
      public virtual bool IsLeaf() => false;
      public List<IDocElement> GetChildren() => Children;
      public void SetChildren(List<IDocElement> elements) => Children = elements;
   }
}