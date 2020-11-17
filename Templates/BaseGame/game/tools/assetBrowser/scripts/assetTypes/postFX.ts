function AssetBrowser::createPostEffectAsset(%this)
{
   %moduleName = AssetBrowser.newAssetSettings.moduleName;
      
   %assetName = AssetBrowser.newAssetSettings.assetName;   
   %assetPath = AssetBrowser.dirHandler.currentAddress @ "/";
   
   %tamlpath = %assetPath @ %assetName @ ".asset.taml";
   %scriptPath = %assetPath @ %assetName @ ".cs";
   %hlslPath = %assetPath @ %assetName @ "P.hlsl";
   %glslPath = %assetPath @ %assetName @ "P.glsl";
   
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

//Renames the asset
function AssetBrowser::renamePostEffectAsset(%this, %assetDef, %newAssetName)
{
   %newScriptFilename = renameAssetLooseFile(%assetDef.scriptPath, %newAssetName);
   
   if(!%newScriptFilename $= "")
      return;
      
   %newHLSLFilename = renameAssetLooseFile(%assetDef.hlslShader, %newAssetName);
   
   if(!%newHLSLFilename $= "")
      return;
      
   %newGLSLFilename = renameAssetLooseFile(%assetDef.glslShader, %newAssetName);
   
   if(!%newGLSLFilename $= "")
      return;
      
   %assetDef.scriptPath = %newScriptFilename;
   %assetDef.hlslShader = %newHLSLFilename;
   %assetDef.glslShader = %newGLSLFilename;
   %assetDef.saveAsset();
   
   renameAssetFile(%assetDef, %newAssetName);
}

//Deletes the asset
function AssetBrowser::deletePostEffectAsset(%this, %assetDef)
{
   AssetDatabase.deleteAsset(%assetDef.getAssetId(), true);
}

//Moves the asset to a new path/module
function AssetBrowser::movePostEffectAsset(%this, %assetDef, %destination)
{
   %currentModule = AssetDatabase.getAssetModule(%assetDef.getAssetId());
   %targetModule = AssetBrowser.getModuleFromAddress(%destination);
   
   %newAssetPath = moveAssetFile(%assetDef, %destination);
   
   if(%newAssetPath $= "")
      return false;

   moveAssetLooseFile(%assetDef.scriptPath, %destination);
   moveAssetLooseFile(%assetDef.hlslShader, %destination);
   moveAssetLooseFile(%assetDef.glslShader, %destination);
   
   AssetDatabase.removeDeclaredAsset(%assetDef.getAssetId());
   AssetDatabase.addDeclaredAsset(%targetModule, %newAssetPath);
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