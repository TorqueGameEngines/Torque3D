function PostFXEditor::onDialogPush( %this )
{
   //Apply the settings to the controls
   postVerbose("% - PostFX Editor - Loading GUI.");
   
   %this.refresh();
   
   PostEffectEditorList.setSelectedById( 1 );
}

function PostFXEditor::onDialogPop( %this )
{
   //Always change the manager target back to the scene's just to be save when done editing
   $PostFXManager::currentPreset = $Client::LevelAsset.getPostFXPresetPath();
   
   PostFXManager.loadPresetHandler($PostFXManager::currentPreset);
   
   PostFXEditorWindow.text = "PostFX Editor";
}

function PostFXEditor::editScenePostFXSettings( %this )
{
   $PostFXManager::currentPreset = $Client::LevelAsset.getPostFXPresetPath();
   Canvas.pushDialog(%this);
   
   PostFXEditorWindow.text = "PostFX Editor - " @ getScene(0).getName();
   
   PostFXEditorActionButton.text = "Revert";
   PostFXEditorActionButton.command = "PostFXEditor.revert();";
}

function PostFXEditor::editDefaultPostFXSettings( %this )
{
   $PostFXManager::currentPreset = $PostFXManager::defaultPreset;
   PostFXManager.loadPresetHandler($PostFXManager::currentPreset);
   
   Canvas.pushDialog(%this);
   
   PostFXEditorWindow.text = "PostFX Editor - Default Config";
   
   PostFXEditorActionButton.text = "Save";
   PostFXEditorActionButton.command = "PostFXManager::savePresetHandler($PostFXManager::defaultPreset);";
}


function PostFXEditor::refresh(%this)
{
   PostEffectEditorList.clear();

   %count = PostFXManager.Count();
   for(%i=0; %i < %count; %i++)
   {
      %postEffect = PostFXManager.getKey(%i);  
      
      if(%postEffect.isEnabled)
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
   %targetPreset = $PostFXManager::currentPreset;
   if(%targetPreset $= "")
      %targetPreset = $PostFXManager::defaultPreset;
      
   PostFXManager::loadPresetHandler(%targetPreset);
   
   %this.refresh();
   
   PostEffectEditorInspector.clearFields();
   PostEffectEditorList.setSelectedRow(1);
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

function PostFXEditor::addNewPostFXs(%this)
{
   %rowIndex = PostFXEditorNewPFXList.getSelectedRow();
   %postFXName = PostFXEditorNewPFXList.getRowText(%rowIndex);
   
   %postFXName.enable();
   
   %this.refresh();
   
   %rowIndex = PostEffectEditorList.findTextIndex(%postFXName);
   PostEffectEditorList.setSelectedRow(%rowIndex);
     
   PostFXEditorNewPFXWindow.setHidden(true);
}

function PostFXEditor::removePostFX(%this)
{
   %rowIndex = PostEffectEditorList.getSelectedRow();
   %postFXName = PostEffectEditorList.getRowText(%rowIndex);
   
   %postFXName.disable();
   
   %this.refresh();
   
   PostEffectEditorInspector.clearFields();
   PostEffectEditorList.setSelectedRow(1);
}

function editScenePostEffects(%scene)
{
   if(EditorIsActive())
      PostFXEditor.editScenePostFXSettings();
}

function PostFXEditorNewPFXWindow::showDialog(%this)
{
   %this.setHidden(false);
   
   PostFXEditorNewPFXList.clear();
   
   %count = PostFXManager.Count();
   for(%i=0; %i < %count; %i++)
   {
      %postEffect = PostFXManager.getKey(%i);  
      
      if(!%postEffect.isEnabled)
         PostFXEditorNewPFXList.addRow( %i, %postEffect.getName() );
   }
}