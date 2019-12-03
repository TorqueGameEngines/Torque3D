function PostFXEditor::onDialogPush( %this )
{
   //Apply the settings to the controls
   postVerbose("% - PostFX Editor - Loading GUI.");
   
   %this.refresh();
   
   ESettingsWindowList.setSelectedById( 1 );
}

function PostFXEditor::refresh(%this)
{
   PostEffectEditorList.clear();

   %count = PostFXManager.Count();
   for(%i=0; %i < %count; %i++)
   {
      %postEffect = PostFXManager.getKey(%i);  
      
      PostEffectEditorList.addRow( %i, %postEffect.getName() );
   }
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

function PostEffectEditorList::onSelect( %this, %id, %text )
{
   PostEffectEditorInspector.clearFields();
   
   %postEffect = PostFXManager.getKey(%id);  
      
   if(isObject(%postEffect) && %postEffect.isMethod("populatePostFXSettings"))
   {
      %postEffect.populatePostFXSettings();
   }
}