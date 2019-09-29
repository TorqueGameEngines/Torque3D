function PostFXEditor::onDialogPush( %this )
{
   //Apply the settings to the controls
   postVerbose("% - PostFX Editor - Loading GUI.");
   
   %this.initialOpen = true;
   %this.refresh();
}

function PostFXEditor::refresh(%this)
{
   PostEffectEditorInspector.clearFields();
   
   %count = PostFXManager.Count();
   for(%i=0; %i < %count; %i++)
   {
      %postEffect = PostFXManager.getKey(%i);  
      
      if(isObject(%postEffect) && %postEffect.isMethod("populatePostFXSettings"))
      {
         %postEffect.populatePostFXSettings();
      }
   }
   
   //First time we open it this 'session', we'll go ahead and collapse the groups
   //so it's not too visually busy
   if(%this.initialOpen)
      PostEffectEditorInspector.setGroupsExpanded(false);   
      
   %this.initialOpen = false;
}

function PostFXEditor::apply(%this)
{
   %count = PostFXManager.Count();
   for(%i=0; %i < %count; %i++)
   {
      %postEffect = PostFXManager.getKey(%i);  
      
      if(isObject(%postEffect) && %postEffect.isMethod("applyFromPreset"))
      {     
         %postEffect.applyFromPreset();
      }
   }
}

function PostFXEditor::revert(%this)
{
   PostFXManager::loadPresetHandler($PostFXManager::currentPreset);
}