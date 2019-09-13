function callGamemodeFunction(%gameModeFuncName, %data)
{
   if(%data !$= "")
      %data = "\""@%data@"\"";
      
   %activeSceneCount = getSceneCount();
      
   %hasGameMode = 0;
   for(%i=0; %i < %activeSceneCount; %i++)
   {
      %gamemodeName = getScene(%i).gameModeName;
      if(%gamemodeName !$= "")
      {
         //if the scene defines a game mode, go ahead and envoke it here
         if(isObject(%gamemodeName) && %gamemodeName.isMethod(%gameModeFuncName))
         {
            eval(%gamemodeName @ "."@%gameModeFuncName@"("@%data@");" );
            %hasGameMode = 1;
         }
         else
         {
            //if we don't have an object, attempt the static call  
            if(isMethod(%gamemodeName, %gameModeFuncName))
            {
               eval(%gamemodeName @ "::"@%gameModeFuncName@"("@%data@");" );
               %hasGameMode = 1;
            }
         }
      }
   }
   
   //if none of our scenes have gamemodes, we need to kick off a default
   if(%hasGameMode == 0)
   {
      %defaultModeName = ProjectSettings.value("Gameplay/GameModes/defaultModeName");
      if(%defaultModeName !$= "")
      {
         if(isObject(%defaultModeName) && %defaultModeName.isMethod(%gameModeFuncName))
         {
            eval(%defaultModeName @ "."@%gameModeFuncName@"("@%data@");" );
            %hasGameMode = 1;
         }
         else
         {
            if(isMethod(%defaultModeName, %gameModeFuncName))
            {
               eval(%defaultModeName @ "::"@%gameModeFuncName@"("@%data@");" );
               %hasGameMode = 1;
            }  
         }
      }
   }  
   
   return %hasGameMode;
}