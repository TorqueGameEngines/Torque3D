using System.Collections.Generic;

namespace T3DSharpGenerator.Model.Docs {
   public interface IDocElement {
      bool IsLeaf();
      List<IDocElement> GetChildren();
      void SetChildren(List<IDocElement> elements);
   }
}