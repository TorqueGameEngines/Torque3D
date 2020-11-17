using System;
using System.Globalization;
using System.IO;
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

         foreach (string library in Directory.GetFiles("./", "*.dll"))
         {
            try
            {
               Initializer.InitializeTypeDictionaries(Assembly.LoadFile(Path.GetFullPath(library)).GetTypes());
            }
            catch (BadImageFormatException e)
            {
               // Skip
            }
            catch (ReflectionTypeLoadException e)
            {
               // Skip
            }
         }

         Torque3D.Libraries libraries = new Torque3D.Libraries
         {
            Windows32bit = "CoinCollection_DEBUG.dll", // <- Change this to match your build output
            Windows64bit = "CoinCollection_DEBUG.dll"  // <- Change this to match your build output
         };

         Torque3D.Initialize(args, libraries);
      }
   }
}
