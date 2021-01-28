
function GuiInspectorVariableGroup::buildModuleDependenciesButtonField(%this, %fieldName, %fieldLabel, %fieldDesc, %fieldDefaultVal, %fieldDataVals, %callbackName, %ownerObj)
{
   %extent = %this.stack.getExtent();
   
   %width = mRound(%extent/2);
   %height = 20;
      
   %button = new GuiButtonCtrl()
   {
      extent = %extent.x SPC %height;  
      text = "Edit Module Dependencies";
      class = "ModuleDependenciesButton";
      profile = "ToolsGuiButtonProfile";
   };
   
   %this.stack.add(%button);
}

function ModuleDependenciesButton::onClick( %this )
{   
   /*if(getSubStr(%this.fieldName, 0, 1) $= "$")
   {
      //ah, a global var, just do it straight, then
      %setCommand = %this.fieldName @ " = \"" @ %text @ "\";";
   }
   else if(isObject(%this.ownerObj))
   {
      //regular variable
      %setCommand = %this.ownerObject @ "." @ %this.fieldName @ " = \"" @ %text @ "\";";
   }
   else if(%this.callbackName !$= "")
   {
      %setCommand = %this.callbackName @ "(\"" @ %this.fieldName @ "\",\"" @ %text @"\");";
   }
   
   eval(%setCommand);*/
   echo("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
}