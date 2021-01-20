function AssetBrowser::buildSoundAssetPreview(%this, %assetDef, %previewData)
{
   %previewData.assetName = %assetDef.assetName;
   %previewData.assetPath = %assetDef.soundFilePath;
   //%previewData.doubleClickCommand = "EditorOpenFileInTorsion( "@%previewData.assetPath@", 0 );";
   
   if(%this.selectMode)
      %previewData.doubleClickCommand = "AssetBrowser.selectAsset( AssetBrowser.selectedAsset );";
   else
      %previewData.doubleClickCommand = "AssetBrowser.editAsset( "@%assetDef@" );";
   
   %previewData.previewImage = "tools/assetBrowser/art/soundIcon";   
   
   %previewData.assetFriendlyName = %assetDef.assetName;
   %previewData.assetDesc = %assetDef.description;
   %previewData.tooltip = %assetDef.assetName;
}

function AssetBrowser::onSoundAssetEditorDropped(%this, %assetDef, %position)
{
   %targetPosition = EWorldEditor.unproject(%position SPC 1000);
   %camPos = LocalClientConnection.camera.getPosition();
   %rayResult = containerRayCast(%camPos, %targetPosition, -1);
   
   %pos = EWCreatorWindow.getCreateObjectPosition();

   if(%rayResult != 0)
   {
      %pos = getWords(%rayResult, 1, 3);
   }
   else
   {
      %pos = "0 0 0";  
   }
   
   %assetId = %assetDef.getAssetId();
   
   %newSFXEmitter = new SFXEmitter()
   {
      position = %pos;
      fileName = %assetDef.getSoundPath();
      pitch = %assetDef.pitchAdjust;
      volume = %assetDef.volumeAdjust;
   };
   
   getScene(0).add(%newSFXEmitter);
   
   EWorldEditor.clearSelection();
   EWorldEditor.selectObject(%newSFXEmitter);
      
   EWorldEditor.isDirty = true;
   
}