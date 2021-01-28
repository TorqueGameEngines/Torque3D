
function GuiInspectorVariableGroup::buildRangeField(%this, %fieldName, %fieldLabel, %fieldDesc, %fieldDefaultVal, %fieldDataVals, %callbackName, %ownerObj)
{
   %extent = 200;
   
   %fieldCtrl = %this.createInspectorField();
   
   %extent = %this.stack.getExtent();

   %width = mRound(%extent/2);
   %height = 20;
   %inset = 10;
   
   %fieldCtrl.setHeightOverride(true, %height);
   
   %minRange = getWord(%fieldDataVals,0);
   %maxRange = getWord(%fieldDataVals,1);
   %tickCount = getWord(%fieldDataVals,2);
   %doSnap = getWord(%fieldDataVals,3);
   
   if(%doSnap $= "")
      %doSnap = 0;
   
   %editControl = new GuiControl()
   {
      class = "guiInspectorRangeField";
      Position = %fieldCtrl.edit.position;
      Extent = %fieldCtrl.edit.extent;
   };
   
   %editText = new GuiTextEditCtrl() {
      class = "guiInspectorRangeFieldText";
      historySize = "0";
      tabComplete = "0";
      sinkAllKeyEvents = "0";
      password = "0";
      passwordMask = "*";
      maxLength = "1024";
      margin = "0 0 0 0";
      padding = "0 0 0 0";
      anchorTop = "1";
      anchorBottom = "0";
      anchorLeft = "1";
      anchorRight = "0";
      Position = "0 0";
      Extent = %fieldCtrl.edit.extent.x * 0.2 SPC %fieldCtrl.edit.extent.y;
      minExtent = "8 2";
      horizSizing = "right";
      vertSizing = "bottom";
      profile = "ToolsGuiTextEditProfile";
      visible = "1";
      active = "1";
      tooltipProfile = "GuiToolTipProfile";
      hovertime = "1000";
      isContainer = "1";
      canSave = "1";
      canSaveDynamicFields = "0";
      text = %fieldDefaultVal;
   };
   
   %editSlider = new GuiSliderCtrl() {
      class = "guiInspectorRangeFieldSlider";
      range = %minRange SPC %maxRange;
      ticks = %tickCount;
      value = %fieldDefaultVal;
      snap = %doSnap;
      renderTicks = "true";
      isContainer = "0";
      Profile = "GuiSliderProfile";
      HorizSizing = "width";
      VertSizing = "bottom";
      Position = (%fieldCtrl.edit.extent.x * 0.2) + 5 SPC 0;
      Extent = (%fieldCtrl.edit.extent.x * 0.8) - 5 SPC %fieldCtrl.edit.extent.y;
      MinExtent = "8 2";
      canSave = "1";
      Visible = "1";
      Command = "$thisControl.onDragComplete();";
      tooltipprofile = "GuiToolTipProfile";
      tooltip = %tooltip;
      hovertime = "1000";
      canSaveDynamicFields = "0";
      ownerObject = %ownerObj;
      fieldName = %fieldName;
      callbackName = %callbackName;
   };
   
   %editText.sliderControl = %editSlider;
   %editSlider.textControl = %editText;
   
   %editControl.add(%editText);
   %editControl.add(%editSlider);
   
   //set the field value
   if(getSubStr(%this.fieldName, 0, 1) $= "$")
   {
      if(%fieldName $= "")
         %editControl.setValue(%fieldName);
   }
   else if(isObject(%ownerObj))
   {
      //regular variable
      %setCommand = %editControl @ ".setValue(" @ %ownerObj @ "." @ %fieldName @ ");";
      eval(%setCommand);
   }
   
   %fieldCtrl.setCaption(%fieldLabel);
   %fieldCtrl.setEditControl(%editControl);

   %this.addInspectorField(%fieldCtrl);
}

function guiInspectorRangeField::onResize(%this)
{
   echo("RESIIIIIIIIIIIZED");  
}

function guiInspectorRangeFieldText::onReturn(%this)
{
   %value = %this.getText();
   %this.sliderControl.setValue(%value);
}

function guiInspectorRangeFieldSlider::onDragComplete( %this )
{   
   %value = %this.getValue();
   %this.textControl.setText(%value);
   
   if(getSubStr(%this.fieldName, 0, 1) $= "$")
   {
      //ah, a global var, just do it straight, then
      %setCommand = %this.fieldName @ " = \"" @ %value @ "\";";
   }
   else if(isObject(%this.ownerObject))
   {
      //regular variable
      %setCommand = %this.ownerObject @ "." @ %this.fieldName @ " = \"" @ %value @ "\";";
   }
   else if(%this.callbackName !$= "")
   {
      %setCommand = %this.callbackName @ "(\"" @ %this.fieldName @ "\",\"" @ %value @"\");";
   }
   
   eval(%setCommand);
}