using T3DSharpFramework.Generated.Functions;
using T3DSharpFramework.Interop;

namespace CoinCollection.Core {
   public class Editor {
      public static bool EditorIsActive() {
         return GenericMarshal.StringTo<bool>(Global.Call("EditorIsActive"));
      }

      public static bool GuiEditorIsActive() {
         return GenericMarshal.StringTo<bool>(Global.Call("GuiEditorIsActive"));
      }
   }
}
