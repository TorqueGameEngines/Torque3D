function AssetBrowser::buildLooseFilePreview(%this, %assetDef, %previewData)
{
   %fullPath = %assetDef.dirPath @ "/" @ %assetDef.assetName;
   %previewData.assetName = %assetDef.assetName;
   %previewData.assetPath = %fullPath;
   
   %previewData.previewImage = "tools/assetBrowser/art/looseFileIcon";
   
   //%previewData.assetFriendlyName = %assetDef.assetName;
   %previewData.assetDesc = %assetDef.description;
   %previewData.tooltip = %fullPath;
   //%previewData.doubleClickCommand = "AssetBrowser.schedule(10, \"navigateTo\",\""@ %assetDef.dirPath @ "/" @ %assetDef.assetName @"\");";//browseTo %assetDef.dirPath / %assetDef.assetName
   %previewData.doubleClickCommand = "AssetBrowser.autoImportFile(\"" @ %fullPath @ "\");";
}