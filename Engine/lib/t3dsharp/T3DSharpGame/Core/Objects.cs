using System;
using T3DSharpFramework.Engine;
using T3DSharpFramework.Generated.Classes.Sim;
using T3DSharpFramework.Generated.Classes.Sim.Net;

namespace CoinCollection.Core {
   public static class Objects {
      public static SimGroup MissionCleanup => Sim.FindObject<SimGroup>("MissionCleanup");
      public static GameConnection ServerConnection => Sim.FindObject<GameConnection>("ServerConnection");
      public static ActionMap GlobalActionMap => Sim.FindObject<ActionMap>("GlobalActionMap");
      public static SimGroup ClientGroup => Sim.FindObject<SimGroup>("ClientGroup");
      public static GuiCanvas Canvas => Sim.FindObject<GuiCanvas>("Canvas");
   }
}
