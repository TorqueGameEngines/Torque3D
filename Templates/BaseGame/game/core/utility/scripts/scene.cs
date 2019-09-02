function callGamemodeFunction(%gameModeFuncName, %data)
{
   if(%data !$= "")
      %data = "\""@%data@"\"";
      
   %hasGameMode = 0;
   for(%i=0; %i < %activeSceneCount; %i++)
   {
      if(getScene(%i).gameModeName !$= "")
      {
         //if the scene defines a game mode, go ahead and envoke it here
         if(isMethod(getScene(%i).gameModeName, %gameModeFuncName))
         {
            
            eval(getScene(%i).gameModeName @ "::"@%gameModeFuncName@"("@%data@");" );
            %hasGameMode = 1;
         }
      }
   }
   
   //if none of our scenes have gamemodes, we need to kick off a default
   if(%hasGameMode == 0)
   {
      %defaultModeName = ProjectSettings.value("Gameplay/GameModes/defaultModeName");
      if(%defaultModeName !$= "")
      {
         if(isMethod(%defaultModeName, %gameModeFuncName))
         {
            eval(%defaultModeName @ "::"@%gameModeFuncName@"("@%data@");" );
            %hasGameMode = 1;
         }
      }
   }  
   
   return %hasGameMode;
}