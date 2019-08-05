function callOnModules(%functionName, %moduleGroup)
{
   //Get our modules so we can exec any specific client-side loading/handling
   %modulesList = ModuleDatabase.findModules(false);
   for(%i=0; %i < getWordCount(%modulesList); %i++)
   {
      %module = getWord(%modulesList, %i);
      
      if(%moduleGroup !$= "")
      {
         if(%module.group !$= %moduleGroup)
            continue;  
      }
      
      if(isObject(%module.scopeSet) && %module.scopeSet.isMethod(%functionName))
      {
         eval(%module.scopeSet @ "." @ %functionName @ "();");
      }
   }   
}