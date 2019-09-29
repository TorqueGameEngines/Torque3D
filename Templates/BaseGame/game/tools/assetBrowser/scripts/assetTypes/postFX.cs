function AssetBrowser::createPostEffectAsset(%this)
{
   %moduleName = AssetBrowser.newAssetSettings.moduleName;
   %modulePath = "data/" @ %moduleName;
      
   %assetName = AssetBrowser.newAssetSettings.assetName;      
   
   %tamlpath = %modulePath @ "/postFXs/" @ %assetName @ ".asset.taml";
   %scriptPath = %modulePath @ "/postFXs/" @ %assetName @ ".cs";
   %hlslPath = %modulePath @ "/postFXs/" @ %assetName @ "P.hlsl";
   %glslPath = %modulePath @ "/postFXs/" @ %assetName @ "P.glsl";
   
   %asset = new PostEffectAsset()
   {
      AssetName = %assetName;
      versionId = 1;
      scriptFile = %assetName @ ".cs";
      hlslShader = %assetName @ "P.hlsl";
      glslShader = %assetName @ "P.glsl";
   };
   
   TamlWrite(%asset, %tamlpath);
   
   %moduleDef = ModuleDatabase.findModule(%moduleName, 1);
	AssetDatabase.addDeclaredAsset(%moduleDef, %tamlpath);

	AssetBrowser.loadFilters();
	
	%treeItemId = AssetBrowserFilterTree.findItemByName(%moduleName);
	%smItem = AssetBrowserFilterTree.findChildItemByName(%treeItemId, "PostEffectAsset");
	
	AssetBrowserFilterTree.onSelect(%smItem);
	
   %file = new FileObject();
	%templateFile = new FileObject();
	
   %postFXTemplateCodeFilePath = %this.templateFilesPath @ "postFXFile.cs.template";
   
   if(%file.openForWrite(%scriptPath) && %templateFile.openForRead(%postFXTemplateCodeFilePath))
   {
      while( !%templateFile.isEOF() )
      {
         %line = %templateFile.readline();
         %line = strreplace( %line, "@@", %assetName );
         
         %file.writeline(%line);
         echo(%line);
      }
      
      %file.close();
      %templateFile.close();
   }
   else
   {
      %file.close();
      %templateFile.close();
      
      warnf("CreatePostFXAsset - Something went wrong and we couldn't write the PostFX script file!");
   }
   
   //hlsl shader
   %postFXTemplateCodeFilePath = %this.templateFilesPath @ "postFXFileP.hlsl.template";
   
   if(%file.openForWrite(%hlslPath) && %templateFile.openForRead(%postFXTemplateCodeFilePath))
   {
      while( !%templateFile.isEOF() )
      {
         %line = %templateFile.readline();
         %line = strreplace( %line, "@@", %assetName );
         
         %file.writeline(%line);
         echo(%line);
      }
      
      %file.close();
      %templateFile.close();
   }
   else
   {
      %file.close();
      %templateFile.close();
      
      warnf("CreatePostFXAsset - Something went wrong and we couldn't write the PostFX hlsl file!");
   }
   
   //glsl shader
   %postFXTemplateCodeFilePath = %this.templateFilesPath @ "postFXFileP.glsl.template";
   
   if(%file.openForWrite(%glslPath) && %templateFile.openForRead(%postFXTemplateCodeFilePath))
   {
      while( !%templateFile.isEOF() )
      {
         %line = %templateFile.readline();
         %line = strreplace( %line, "@@", %assetName );
         
         %file.writeline(%line);
         echo(%line);
      }
      
      %file.close();
      %templateFile.close();
   }
   else
   {
      %file.close();
      %templateFile.close();
      
      warnf("CreatePostFXAsset - Something went wrong and we couldn't write the PostFX glsl file!");
   }
   
	return %tamlpath;
}

function AssetBrowser::buildPostEffectAssetPreview(%this, %assetDef, %previewData)
{
   %previewData.assetName = %assetDef.assetName;
   %previewData.assetPath = %assetDef.scriptFilePath;
   %previewData.doubleClickCommand = "";
   
   %previewData.previewImage = "tools/assetBrowser/art/postEffectIcon";
   
   %previewData.assetFriendlyName = %assetDef.assetName;
   %previewData.assetDesc = %assetDef.description;
   %previewData.tooltip = %assetDef.assetName;
}