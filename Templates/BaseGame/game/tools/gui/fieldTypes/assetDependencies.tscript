
function GuiInspectorVariableGroup::buildAssetDependenciesField(%this, %fieldName, %fieldLabel, %fieldDesc, %fieldDefaultVal, %fieldDataVals, %callbackName, %ownerObj)
{
   %extent = 200;
   
   %fieldCtrl = %this.createInspectorField();
   
   %extent = %this.stack.getExtent();
   
   %width = mRound(%extent/2);
   %height = 20;
   %inset = 10;
   
   %editControl = new GuiPopUpMenuCtrl() {
      class = "guiInspectorListField";
      maxPopupHeight = "200";
      sbUsesNAColor = "0";
      reverseTextList = "0";
      bitmapBounds = "16 16";
      maxLength = "1024";
      Margin = "0 0 0 0";
      Padding = "0 0 0 0";
      AnchorTop = "1";
      AnchorBottom = "0";
      AnchorLeft = "1";
      AnchorRight = "0";
      isContainer = "0";
      Profile = "ToolsGuiPopUpMenuProfile";
      HorizSizing = "right";
      VertSizing = "bottom";
      Position = %fieldCtrl.edit.position;
      Extent = %fieldCtrl.edit.extent;
      MinExtent = "8 2";
      canSave = "1";
      Visible = "1";
      tooltipprofile = "ToolsGuiToolTipProfile";
      tooltip = %tooltip;
      text = %fieldDefaultVal;
      hovertime = "1000";
      ownerObject = %ownerObj;
      fieldName = %fieldName;
      callbackName = %callbackName;
   };
   
   //set the field value
   if(getSubStr(%this.fieldName, 0, 1) $= "$")
   {
      if(%fieldName $= "")
         %editControl.setText(%fieldName);
   }
   else if(isObject(%ownerObj))
   {
      //regular variable
      %setCommand = %editControl @ ".setText(" @ %ownerObj @ "." @ %fieldName @ ");";
      eval(%setCommand);
   }
   
   %listCount = getTokenCount(%fieldDataVals, ",");
   
   for(%i=0; %i < %listCount; %i++)
   {
      %entryText = getToken(%fieldDataVals, ",", %i);
      %editControl.add(%entryText); 
   }

   %fieldCtrl.setCaption(%fieldLabel);
   %fieldCtrl.setEditControl(%editControl);
   
   //echo("GuiInspectorListField - " @ %editControl.getID() @ " - " @ %fieldName);

   %this.addInspectorField(%fieldCtrl);
}

function guiInspectorListField::onSelect( %this, %id, %text )
{   
   if(getSubStr(%this.fieldName, 0, 1) $= "$")
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
   
   eval(%setCommand);
}