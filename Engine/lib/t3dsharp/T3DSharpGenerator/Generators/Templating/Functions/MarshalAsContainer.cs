using Scriban.Runtime;

namespace T3DSharpGenerator.Generators.Templating.Functions {
   public class MarshalAsContainer : ScriptObject {
      public static string MarshalAs(string type, bool @return = false) {
         string retStr = @return ? "return: " : "";
         switch (type) {
            case "string":
            case "cstring":
               // When Torque3D returns string, it uses a static string object which it "owns" and is valid untill
               // the next API call is made. To make sure we handle these properties, we don't use any automatic 
               // interop stuff on returned strings.
               if (@return == false) {
                  return $"[{retStr}MarshalAs(UnmanagedType.LPUTF8Str)]";
               }

               return null;
            case "bool":
               return $"[{retStr}MarshalAs(UnmanagedType.I1)]";
            default:
               return null;
         }
      }
   }
}