
function GuiInspectorVariableGroup::buildButtonField(%this, %fieldName, %fieldLabel, %fieldDesc, %fieldDefaultVal, %fieldDataVals, %callbackName, %ownerObj)
{
   %extent = 200;
   
   %fieldCtrl = %this.createInspectorField();
   
   %extent = %this.stack.getExtent();
   
   %width = mRound(%extent/2);
   %height = 20;
   %inset = 10;

   %editControl = new GuiButtonCtrl() {
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
      Profile = "ToolsGuiButtonProfile";
      HorizSizing = "right";
      VertSizing = "bottom";
      Position = %fieldCtrl.edit.position;
      Extent = %fieldCtrl.edit.extent;
      MinExtent = "8 2";
      canSave = "1";
      Visible = "1";
      tooltipprofile = "ToolsGuiToolTipProfile";
      tooltip = %tooltip;
      text = %fieldName;
      hovertime = "1000";
      command = %fieldDataVals;
   };

   %fieldCtrl.setCaption(%fieldLabel);
   %fieldCtrl.setEditControl(%editControl);

   %this.addInspectorField(%fieldCtrl);
}