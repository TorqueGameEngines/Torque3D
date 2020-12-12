function GuiVariableInspector::onInspectorFieldModified(%this, %targetObj, %fieldName, %index, %oldValue, %newValue)
{
   echo("FIELD CHANGED: " @ %fieldName @ " from " @ %oldValue @ " to " @ %newValue);
}

function GuiInspectorVariableGroup::onConstructField(%this, %fieldName, %fieldLabel, %fieldTypeName, %fieldDesc, %fieldDefaultVal, %fieldDataVals, %callbackName, %ownerObj)
{
   %inspector = %this.getParent();
   %makeCommand = %this @ ".build" @ %fieldTypeName @ "Field(\""@ %fieldName @ "\",\"" @ %fieldLabel @ "\",\"" @ %fieldDesc @ "\",\"" @ 
            %fieldDefaultVal @ "\",\"" @ %fieldDataVals @ "\",\"" @ %inspector @ "." @ %callbackName @ "\",\"" @ %ownerObj @"\");";
   eval(%makeCommand);
}

function GuiInspectorGroup::onConstructField(%this, %fieldName, %fieldLabel, %fieldTypeName, %fieldDesc, %fieldDefaultVal, %fieldDataVals, %callbackName, %ownerObj)
{
   %inspector = %this.getParent();
   %makeCommand = %this @ ".build" @ %fieldTypeName @ "Field(\""@ %fieldName @ "\",\"" @ %fieldLabel @ "\",\"" @ %fieldDesc @ "\",\"" @ 
            %fieldDefaultVal @ "\",\"" @ %fieldDataVals @ "\",\"" @ %inspector @ "." @ %callbackName @ "\",\"" @ %ownerObj @"\");";
   eval(%makeCommand);
}
