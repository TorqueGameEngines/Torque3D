using System.Globalization;
using System.Reflection;
using System.Threading;
using T3DSharpFramework.Interop;

namespace Game
{
   class Program
    {
      static void Main(string[] args)
      {
         CultureInfo customCulture =
           (CultureInfo)Thread.CurrentThread.CurrentCulture.Clone();
         customCulture.NumberFormat.NumberDecimalSeparator = ".";

         Thread.CurrentThread.CurrentCulture = customCulture;

         Initializer.InitializeTypeDictionaries(Assembly.GetExecutingAssembly().GetTypes());

         Torque3D.Libraries libraries = new Torque3D.Libraries
         {
            Windows32bit = "Stock_DEBUG.dll", // <- Change this to match your build output
            Windows64bit = "Stock_DEBUG.dll"  // <- Change this to match your build output
         };

         Torque3D.Initialize(args, libraries);
      }
   }
}
