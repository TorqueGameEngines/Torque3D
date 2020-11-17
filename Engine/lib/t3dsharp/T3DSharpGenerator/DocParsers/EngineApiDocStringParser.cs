using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.RegularExpressions;
using T3DSharpGenerator.Model.Docs;

namespace T3DSharpGenerator.DocParsers {
   public class EngineApiDocStringParser {
      private static List<IDocStringParser> DocStringParsers { get; set; } = new List<IDocStringParser> {
         new DescriptionStringParser(),
         new SummaryStringParser(),
         new RemarkStringParser(),
         new CodeExampleStringParser(),
         new ParameterStringParser(),
         new ReturnStringParser(),
         new InGroupStringParser(),
         new SeeStringParser(),
         new InternalStringParser(),
         new ParameterRefStringParser(),
         new InlineStringParser(),
         new NullStringParser(),
      };

      public static IDocElement Parse(string docs) {
         DocTag[] docTags = Regex.Split(docs, "(?=@)")
            .Select(s => new DocTag(s))
            .ToArray();

         for (int i = 0; i < docTags.Count(); i++) {
            if (i == 0) {
               continue;
            }

            docTags[i - 1].Next = docTags[i];
            docTags[i].Previous = docTags[i - 1];
         }

         List<IDocElement> docElements = docTags.Select(docTag => {
            IDocElement element = ParseDocTag(docTag);
            if (element.IsLeaf()) {
               return null;
            }

            if (docTag.Next == null || !ParseDocTag(docTag.Next).IsLeaf()) {
               return element;
            }

            List<IDocElement> children = element.GetChildren();
            switch (ParseDocTag(docTag.Next)) {
               case ParameterRefDocElement refDocElement:
                  children.Add(refDocElement);
                  children.Add(new TextDocElement {
                     Text = refDocElement.Remainder
                  });
                  element.SetChildren(children);
                  return element;
               case TextDocElement textDocElement:
                  children.Add(textDocElement);
                  element.SetChildren(children);
                  return element;
               case NullDocElement nullDocElement:
                  return element;
               case InternalDocElement internalDocElement:
                  return element;
               default:
                  throw new NotImplementedException();
            }
         })
            .Where(x => x != null)
            .ToList();
         return new CompoundDocElement() {
            Children = docElements
         };
      }


      public static IDocElement ParseDocTag(DocTag tag) {
         return DocStringParsers
            .Find(parser => parser.MatchesTag(tag))
            .Parse(tag);
      }
   }
}