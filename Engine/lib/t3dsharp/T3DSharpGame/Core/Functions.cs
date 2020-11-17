using System.Linq;
using T3DSharpFramework.Generated.Functions;

namespace CoinCollection.Core {
   public class Functions {
      public static void RegisterDatablock(string path) {
         Global.Call("registerDatablock", path);
      }

      public static void MessageBoxOK(string title, string message, string callback) {
         Global.Call("MessageBoxOK", title, message, callback);
      }

      public static void MessageClient(string client, string msgType, string msgString, params string[] args) {
         Global.Call(args.Prepend(msgString).Prepend(msgType).Prepend(client).Prepend("MessageClient").ToArray());
      }

      public static void MessageAll(string msgType, string msgString, params string[] args) {
         Global.Call(args.Prepend(msgString).Prepend(msgType).Prepend("MessageAll").ToArray());
      }

      public static void MessageAllExcept(string client, string team, string msgType, string msgString, params string[] args) {
         Global.Call(args.Prepend(msgString).Prepend(msgType).Prepend(team).Prepend(client).Prepend("MessageAllExcept").ToArray());
      }

      public static void AddMessageCallback(string message, string callback) {
         Global.Call("AddMessageCallback", message, callback);
      }
   }
}
