using System.Collections.Generic;
using T3DSharpGenerator.Model.Docs;

namespace T3DSharpGenerator.DocParsers {
   public class SummaryStringParser : IDocStringParser {
      public bool MatchesTag(DocTag tag) {
         return tag.Tag.Trim().Equals("@brief");
      }

      public IDocElement Parse(DocTag tag) {
         if (tag.Text.IndexOf('\n') > -1) {
            return new CompoundDocElement {
               Children = new List<IDocElement>() {
                  new SummaryDocElement {
                     Children = new List<IDocElement>() {
                        new TextDocElement {
                           Text = tag.Text.Substring(0, tag.Text.IndexOf('\n')).Trim()
                        }
                     }
                  },
                  new DescriptionDocElement {
                     Children = new List<IDocElement>() {
                        new TextDocElement {
                           Text = tag.Text.Substring(tag.Text.IndexOf('\n')).Trim()
                        }
                     }
                  },
               }
            };
         }
         
         return new SummaryDocElement() {
            Children = new List<IDocElement>() {
               new TextDocElement {
                  Text = tag.Text.Trim()
               }
            }
         };
      }
   }
}