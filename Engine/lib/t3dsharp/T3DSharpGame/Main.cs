using System.Reflection;
using T3DSharpFramework.Engine;
using T3DSharpFramework.Generated.Classes.Sim;
using T3DSharpFramework.Generated.Functions;
using T3DSharpFramework.Interop;

namespace Game
{
   class Main
   {
      [ScriptEntryPoint]
      public static void Entry()
      {
         // --- Boilerplate C#-specific setup. Normally Torque uses the main.cs file to set these variables, here we have to do it ourselves.
         string CSDir = System.IO.Path.GetDirectoryName(Assembly.GetEntryAssembly().Location).Replace('\\', '/');
         Global.SetMainDotCsDir(CSDir);
         Global.SetCurrentDirectory(CSDir);
         // ---
         Global.SetCurrentDirectory(CSDir);

         Global.SetConsoleString("Core::windowIcon", "data/icon.png");
         Global.SetConsoleString("Core::splashWindowImage", "data/splash.png");

         // Display a splash window immediately to improve app responsiveness before
         // engine is initialized and main window created.
         Global.DisplaySplashWindow(Global.GetConsoleString("Core::splashWindowImage"));

         // Enable console logging, which creates the file console.log each time you run
         // the engine.
         Global.SetLogMode(6);

         // Disable script trace.
         Global.Trace(false);

         // Set the name of our application
         Global.SetConsoleString("appName", "Game");

         //-----------------------------------------------------------------------------
         // Load up scripts to initialise subsystems.
         ModuleManager ModuleDatabase = Sim.FindObject<ModuleManager>("ModuleDatabase");
         ModuleDatabase.SetModuleExtension("module");
         ModuleDatabase.ScanModules("core", false);
         ModuleDatabase.LoadExplicit("CoreModule");

         //-----------------------------------------------------------------------------
         // Load any gameplay modules
         ModuleDatabase.ScanModules("data", false);
         ModuleDatabase.LoadGroup("Game");

         //Finally, initialize the client/server structure
         ModuleDatabase.LoadExplicit("Core_ClientServer");

         if (Global.IsFunction("loadStartup"))
         {
            Global.Call("loadStartup");
         }
         else
         {
            GuiCanvas Canvas = Sim.FindObject<GuiCanvas>("Canvas");
            //If nothing else set a main menu, try to do so now
            if (Canvas != null && Sim.FindObjectById<GuiControl>((uint)Canvas.GetContent()) != null)
            {
               Settings ProjectSettings = Sim.FindObject<Settings>("ProjectSettings");
               string mainMenuGUI = ProjectSettings?.Value("UI/mainMenuName");
               if (Global.IsObject( mainMenuGUI))
                  Canvas.SetContent(Sim.FindObject<GuiControl>(mainMenuGUI));
            }
         }

         Global.CloseSplashWindow();

         Global.Echo("Engine initialized...");
      }

      //-----------------------------------------------------------------------------
      // Called when the engine is shutting down.
      [ConsoleFunction]
      public static void onExit()
      {
         ModuleManager ModuleDatabase = Sim.FindObject<ModuleManager>("ModuleDatabase");
         ModuleDatabase.UnloadExplicit("CoreModule");
         ModuleDatabase.UnloadGroup("Game");
      }
   }
}


