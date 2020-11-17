using System;
using System.Collections.Generic;

namespace T3DSharpGenerator.Model.Docs {
   public class LeafDocElement : IDocElement {
      public virtual bool IsLeaf() => true;
      public List<IDocElement> GetChildren() => new List<IDocElement>();
      public void SetChildren(List<IDocElement> elements) => throw new NotImplementedException();
   }
}