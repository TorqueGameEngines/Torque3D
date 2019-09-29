// =============================================================================
// GRAPHICS MENU
// =============================================================================
function GraphicsMenu::refresh(%this)
{
   //
   // Display Menu
   GraphicsMenuFullScreen.setStateOn( Canvas.isFullScreen() );
   GraphicsMenuVSync.setStateOn( !$pref::Video::disableVerticalSync );
   
   %this.initResMenu();
   %resSelId = GraphicsMenuResolution.findText( _makePrettyResString( $pref::Video::mode ) );
   if( %resSelId != -1 )
      GraphicsMenuResolution.setSelected( %resSelId );
   
   GraphicsMenuDriver.clear();
   
   %buffer = getDisplayDeviceList();
   %count = getFieldCount( %buffer );   
   for(%i = 0; %i < %count; %i++)
      GraphicsMenuDriver.add(getField(%buffer, %i), %i);

   %selId = GraphicsMenuDriver.findText( getDisplayDeviceInformation() );
	if ( %selId == -1 )
		GraphicsMenuDriver.setFirstSelected();
   else
	   GraphicsMenuDriver.setSelected( %selId );
   //

   //
   // General Graphics menu
   GraphicsMenuShadowQlty.init(ShadowQualityList);
   GraphicsMenuSoftShadow.init(SoftShadowList);
   
   GraphicsMenuModelDtl.init(MeshQualityGroup);
   GraphicsMenuTextureDtl.init(TextureQualityGroup);
   GraphicsMenuTerrainDtl.init(TerrainQualityGroup);
   GraphicsMenuDecalLife.init(DecalLifetimeGroup);
   GraphicsMenuGroundClutter.init(GroundCoverDensityGroup);
   
   GraphicsMenuMaterialQlty.init(ShaderQualityGroup);
   
   // Setup the anisotropic filtering menu.
   %ansioCtrl = GraphicsMenuAniso;
   %ansioCtrl.clear();
   %ansioCtrl.add( "16X", 16 );
   %ansioCtrl.add( "8X", 8 );
   %ansioCtrl.add( "4X", 4 );
   %ansioCtrl.add( "Off", 0 );
   %ansioCtrl.setSelected( $pref::Video::defaultAnisotropy, false );
            
   // set up the Refresh Rate menu.
   %refreshMenu = GraphicsMenuRefreshRate;
   %refreshMenu.clear();
   // %refreshMenu.add("Auto", 60);
   %refreshMenu.add("60", 60);
   %refreshMenu.add("75", 75);
   %refreshMenu.setSelected( $pref::Video::RefreshRate );
	   
   // Populate the Anti-aliasing popup.
   %aaMenu = GraphicsMenuAA;
   %aaMenu.clear();
   %aaMenu.Add( "4x", 4 );
   %aaMenu.Add( "2x", 2 );
   %aaMenu.Add( "1x", 1 );
   %aaMenu.Add( "Off", 0 );
   %aaMenu.setSelected( $pref::Video::AA );
   
   //Parallax
   GraphicsMenuParallax.setStateOn(!$pref::Video::disableParallaxMapping);
   
   //water reflections
   GraphicsMenuWaterRefl.setStateOn(!$pref::Water::disableTrueReflections);
   
   GraphicsMenuParallax.setStateOn(!$pref::Video::disableParallaxMapping);
      
   GraphicsMenuAO.setStateOn($pref::PostFX::EnableSSAO);
   GraphicsMenuHDR.setStateOn($pref::PostFX::EnableHDR);
   GraphicsMenuDOF.setStateOn($pref::PostFX::EnableDOF);
   GraphicsMenuVignette.setStateOn($pref::PostFX::EnableVignette);
   GraphicsMenuLightRay.setStateOn($pref::PostFX::EnableLightRays);
}

function GraphicsMenu::initResMenu( %this )
{
   // Clear out previous values
   %resMenu = GraphicsMenuResolution;	   
   %resMenu.clear();
   
   // If we are in a browser then we can't change our resolution through
   // the options dialog
   if (getWebDeployment())
   {
      %count = 0;
      %currRes = getWords(Canvas.getVideoMode(), $WORD::RES_X, $WORD::RES_Y);
      %resMenu.add(%currRes, %count);
      %count++;

      return;
   }
   
   // Loop through all and add all valid resolutions
   %count = 0;
   %resCount = Canvas.getModeCount();
   for (%i = 0; %i < %resCount; %i++)
   {
      %testResString = Canvas.getMode( %i );
      %testRes = _makePrettyResString( %testResString );
                     
      // Only add to list if it isn't there already.
      if (%resMenu.findText(%testRes) == -1)
      {
         %resMenu.add(%testRes, %i);
         %count++;
      }
   }
   
   %resMenu.sort();
}

//
function GraphicsMenu::Autodetect(%this)
{
   $pref::Video::autoDetect = false;
   
   %shaderVer = getPixelShaderVersion();
   %intel = ( strstr( strupr( getDisplayDeviceInformation() ), "INTEL" ) != -1 ) ? true : false;
   %videoMem = GFXCardProfilerAPI::getVideoMemoryMB();
   
   return %this.Autodetect_Apply( %shaderVer, %intel, %videoMem );
}

function GraphicsMenu::Autodetect_Apply(%this, %shaderVer, %intel, %videoMem )
{
   if ( %shaderVer < 2.0 )
   {      
      return "Your video card does not meet the minimum requirment of shader model 2.0.";
   }
   
   if ( %shaderVer < 3.0 || %intel )
   {
      // Allow specular and normals for 2.0a and 2.0b
      if ( %shaderVer > 2.0 )
      {
         MeshQualityGroup.applySetting("Lowest");
         TextureQualityGroup.applySetting("Lowest");
         GroundCoverDensityGroup.applySetting("Lowest");
         DecalLifetimeGroup.applySetting("None");
         TerrainQualityGroup.applySetting("Lowest");
         ShaderQualityGroup.applySetting("High");
         
         ShadowQualityList.applySetting("None");
         
         SoftShadowList.applySetting("Off");
         
         $pref::Shadows::useShadowCaching = true;
         
         $pref::Water::disableTrueReflections = true;
         $pref::Video::disableParallaxMapping = true;
         $pref::PostFX::EnableSSAO = false;
         $pref::PostFX::EnableHDR = false;
         $pref::PostFX::EnableDOF = false;
         $pref::PostFX::EnableLightRays = false;
         $pref::PostFX::EnableVignette = false;
         
         $pref::Video::AA = 0;
         $pref::Video::disableVerticalSync = 0;
      }
      else
      {
         MeshQualityGroup.applySetting("Lowest");
         TextureQualityGroup.applySetting("Lowest");
         GroundCoverDensityGroup.applySetting("Lowest");
         DecalLifetimeGroup.applySetting("None");
         TerrainQualityGroup.applySetting("Lowest");
         ShaderQualityGroup.applySetting("Low");
         
         ShadowQualityList.applySetting("None");
         
         SoftShadowList.applySetting("Off");
         
         $pref::Shadows::useShadowCaching = true;
         
         $pref::Water::disableTrueReflections = true;
         $pref::Video::disableParallaxMapping = true;
         $pref::PostFX::EnableSSAO = false;
         $pref::PostFX::EnableHDR = false;
         $pref::PostFX::EnableDOF = false;
         $pref::PostFX::EnableLightRays = false;
         $pref::PostFX::EnableVignette = false;
         
         $pref::Video::AA = 0;
         $pref::Video::disableVerticalSync = 0;
      }
   }   
   else
   {
      if ( %videoMem > 1000 )
      {
         MeshQualityGroup.applySetting("High");
         TextureQualityGroup.applySetting("High");
         GroundCoverDensityGroup.applySetting("High");
         DecalLifetimeGroup.applySetting("High");
         TerrainQualityGroup.applySetting("High");
         ShaderQualityGroup.applySetting("High");
         
         ShadowQualityList.applySetting("High");
         
         SoftShadowList.applySetting("High");
         
         //Should this default to on in ultra settings?
         $pref::Shadows::useShadowCaching = true;
         
         $pref::Water::disableTrueReflections = false;
         $pref::Video::disableParallaxMapping = false;
         $pref::PostFX::EnableSSAO = true;
         $pref::PostFX::EnableHDR = true;
         $pref::PostFX::EnableDOF = true;
         $pref::PostFX::EnableLightRays = true;
         $pref::PostFX::EnableVignette = true;
         
         $pref::Video::AA = 4;
         $pref::Video::disableVerticalSync = 16;
      }
      else if ( %videoMem > 400 || %videoMem == 0 )
      {
         MeshQualityGroup.applySetting("Medium");
         TextureQualityGroup.applySetting("Medium");
         GroundCoverDensityGroup.applySetting("Medium");
         DecalLifetimeGroup.applySetting("Medium");
         TerrainQualityGroup.applySetting("Medium");
         ShaderQualityGroup.applySetting("High");
         
         ShadowQualityList.applySetting("Medium");
         
         SoftShadowList.applySetting("Low");
         
         $pref::Shadows::useShadowCaching = true;
         
         $pref::Water::disableTrueReflections = false;
         $pref::Video::disableParallaxMapping = true;
         $pref::PostFX::EnableSSAO = false;
         $pref::PostFX::EnableHDR = true;
         $pref::PostFX::EnableDOF = true;
         $pref::PostFX::EnableLightRays = true;
         $pref::PostFX::EnableVignette = true;
         
         $pref::Video::AA = 4;
         $pref::Video::disableVerticalSync = 4;
         
         if ( %videoMem == 0 )
            return "Torque was unable to detect available video memory. Applying 'Medium' quality.";
      }
      else
      {
         MeshQualityGroup.applySetting("Low");
         TextureQualityGroup.applySetting("Low");
         GroundCoverDensityGroup.applySetting("Low");
         DecalLifetimeGroup.applySetting("Low");
         TerrainQualityGroup.applySetting("Low");
         ShaderQualityGroup.applySetting("Low");
         
         ShadowQualityList.applySetting("None");
         
         SoftShadowList.applySetting("Off");
         
         $pref::Shadows::useShadowCaching = true;
         
         $pref::Water::disableTrueReflections = false;
         $pref::Video::disableParallaxMapping = true;
         $pref::PostFX::EnableSSAO = false;
         $pref::PostFX::EnableHDR = false;
         $pref::PostFX::EnableDOF = false;
         $pref::PostFX::EnableLightRays = false;
         $pref::PostFX::EnableVignette = false;
         
         $pref::Video::AA = 0;
         $pref::Video::disableVerticalSync = 0;
      }
   }
   
   %this.refresh();
   
   %this.apply();
   
   //force postFX updates
   PostFXManager.settingsEffectSetEnabled(SSAOPostFx, $pref::PostFX::EnableSSAO);
   PostFXManager.settingsEffectSetEnabled(HDRPostFX, $pref::PostFX::EnableHDR);
   PostFXManager.settingsEffectSetEnabled(DOFPostEffect, $pref::PostFX::EnableDOF);
   PostFXManager.settingsEffectSetEnabled(LightRayPostFX, $pref::PostFX::EnableLightRays);
   PostFXManager.settingsEffectSetEnabled(VignettePostEffect, $pref::PostFX::EnableVignette);
   
   return "Graphics quality settings have been auto detected.";
}

function _makePrettyResString( %resString, %giveAspectRation )
{
   %width = getWord( %resString, $WORD::RES_X );
   %height = getWord( %resString, $WORD::RES_Y );
   
   %aspect = %width / %height;
   %aspect = mRound( %aspect * 100 ) * 0.01;            
   
   switch$( %aspect )
   {
      case "1.33":
         %aspect = "4:3";
      case "1.78":
         %aspect = "16:9";
      default:
         %aspect = "";
   }
   
   %outRes = %width @ " x " @ %height;
   if ( %giveAspectRation && %aspect !$= "" )
      %outRes = %outRes @ "  (" @ %aspect @ ")";
      
   return %outRes;   
}

function GraphicsMenu::apply(%this)
{
   //Loop through the settings cache and actually apply the values
   %cachedSettingCount = GraphicsSettingsCache.count();
   %canvasUpdate = false;
   
   for(%i=0; %i < %cachedSettingCount; %i++)
   {
      %var = GraphicsSettingsCache.getKey(%i);  
      %val = GraphicsSettingsCache.getValue(%i);
      
      if(%var $= "$pref::Video::AA")
      {
         %canvasUpdate = true;
      }
      
      setVariable(%var, %val);
   }
   
   //Update Textures
   reloadTextures();

   //Update lighting
   // Set the light manager.  This should do nothing 
   // if its already set or if its not compatible.   
   //setLightManager( $pref::lightManager );   
   
   PostFXManager.settingsEffectSetEnabled("SSAO", $pref::PostFX::EnableSSAO);
   PostFXManager.settingsEffectSetEnabled("HDR", $pref::PostFX::EnableHDR);
   PostFXManager.settingsEffectSetEnabled("DOF", $pref::PostFX::EnableDOF);
   PostFXManager.settingsEffectSetEnabled("LightRays", $pref::PostFX::EnableLightRays);
   PostFXManager.settingsEffectSetEnabled("Vignette", $pref::PostFX::EnableVignette);

   if (  %canvasUpdate )
   {
      // Change the video mode.   
      configureCanvas();
   }
   
   echo("Exporting client prefs");
   %prefPath = getPrefpath();
   export("$pref::*", %prefPath @ "/clientPrefs.cs", false);
}

function GraphicsMenu::loadSettings()
{
   OptionsMenu.currentMenu = "GraphicsMenu";
   OptionsSettingStack.clear();
   
   OptionsMenu.addSettingOption(OptionsSettingStack, "Shadow Quality", "", "ShadowQuality");
   //OptionsMenu.addSettingOption(OptionsSettingStack, "Shadow Caching", "", "ShadowCaching");
   OptionsMenu.addSettingOption(OptionsSettingStack, "Soft Shadows", "", "SoftShadow");
   
   OptionsMenu.addSettingOption(OptionsSettingStack, "Model Detail", "", "MeshQuality");
   OptionsMenu.addSettingOption(OptionsSettingStack, "Texture Detail", "", "TextureQuality");
   OptionsMenu.addSettingOption(OptionsSettingStack, "Terrain Detail", "", "TerrainQuality");
   OptionsMenu.addSettingOption(OptionsSettingStack, "Decal Lifetime", "", "DecalLifetime");
   OptionsMenu.addSettingOption(OptionsSettingStack, "Ground Clutter Density", "", "GroundCoverDensity");
   
   OptionsMenu.addSettingOption(OptionsSettingStack, "Material Quality", "", "ShaderQuality");
   OptionsMenu.addSettingOption(OptionsSettingStack, "Parallax", "", "ParallaxSetting");
   OptionsMenu.addSettingOption(OptionsSettingStack, "Ambient Occlusion", "", "AmbientOcclusionSetting");
   OptionsMenu.addSettingOption(OptionsSettingStack, "Light Rays", "", "LightRaysSetting");
   OptionsMenu.addSettingOption(OptionsSettingStack, "Depth of Field", "", "DOFSetting");
   OptionsMenu.addSettingOption(OptionsSettingStack, "Vignetting", "", "VignetteSetting");
   OptionsMenu.addSettingOption(OptionsSettingStack, "Water Reflections", "", "WaterReflectionSetting");
   OptionsMenu.addSettingOption(OptionsSettingStack, "Anti Aliasing", "", "AASetting");
   OptionsMenu.addSettingOption(OptionsSettingStack, "Anisotropic Filtering", "", "AnisotropicFilteringSetting");
   
   GraphicsSettingsCache.empty();
}

function GraphicsMenu::set(%var, %val)
{
   %ex = GraphicsSettingsCache.getIndexFromKey(%var);
   if(%ex != -1)
      GraphicsSettingsCache.erase(%ex);
      
   GraphicsSettingsCache.add(%var, %val);
}

//
//
//
function MeshQuality::set(%setting)
{
   switch$(%setting)
   {
      case "High":
         GraphicsMenu::set("$pref::TS::detailAdjust", "1.5");
         GraphicsMenu::set("$pref::TS::skipRenderDLs", "0");
      case "Medium":
         GraphicsMenu::set("$pref::TS::detailAdjust", "1.0");
         GraphicsMenu::set("$pref::TS::skipRenderDLs", "0");
      case "Low":
         GraphicsMenu::set("$pref::TS::detailAdjust", "0.75");
         GraphicsMenu::set("$pref::TS::skipRenderDLs", "0");
      case "Lowest":
         GraphicsMenu::set("$pref::TS::detailAdjust", "0.5");
         GraphicsMenu::set("$pref::TS::skipRenderDLs", "0");
      default:
         GraphicsMenu::set("$pref::TS::detailAdjust", "1.0");
         GraphicsMenu::set("$pref::TS::skipRenderDLs", "0");
   }
}

function MeshQuality::get()
{
   if($pref::TS::detailAdjust == 1.5)
      return "High";
   else if($pref::TS::detailAdjust == 1.0)
      return "Medium";
   else if($pref::TS::detailAdjust == 0.75)
      return "Low";
   else if($pref::TS::detailAdjust == 0.5)
      return "Lowest";
   else
      return "Custom";
}

function MeshQuality::getList()
{
   return "Lowest,Low,Medium,High";
}

//
function TextureQuality::set(%setting)
{
   switch$(%setting)
   {
      case "High":
         GraphicsMenu::set("$pref::Video::textureReductionLevel", "0");
         GraphicsMenu::set("$pref::Reflect::refractTexScale", "1.25");
      case "Medium":
         GraphicsMenu::set("$pref::Video::textureReductionLevel", "0");
         GraphicsMenu::set("$pref::Reflect::refractTexScale", "1");
      case "Low":
         GraphicsMenu::set("$pref::Video::textureReductionLevel", "1");
         GraphicsMenu::set("$pref::Reflect::refractTexScale", "0.75");
      case "Lowest":
         GraphicsMenu::set("$pref::Video::textureReductionLevel", "2");
         GraphicsMenu::set("$pref::Reflect::refractTexScale", "0.5");
      default:
         GraphicsMenu::set("$pref::Video::textureReductionLevel", "0");
         GraphicsMenu::set("$pref::Reflect::refractTexScale", "1");
   }
}

function TextureQuality::get()
{
   if($pref::Video::textureReductionLevel == 0 && $pref::Reflect::refractTexScale == 1.25)
      return "High";
   else if($pref::Video::textureReductionLevel == 0 && $pref::Reflect::refractTexScale == 1)
      return "Medium";
   else if($pref::Video::textureReductionLevel == 1 && $pref::Reflect::refractTexScale == 0.75)
      return "Low";
   else if($pref::Video::textureReductionLevel == 2 && $pref::Reflect::refractTexScale == 0.5)
      return "Lowest";
   else
      return "Custom";
}

function TextureQuality::getList()
{
   return "Lowest,Low,Medium,High";
}

//
function GroundCoverDensity::set(%setting)
{
   switch$(%setting)
   {
      case "High":
         GraphicsMenu::set("$pref::GroundCover::densityScale", "1");
      case "Medium":
         GraphicsMenu::set("$pref::GroundCover::densityScale", "0.75");
      case "Low":
         GraphicsMenu::set("$pref::GroundCover::densityScale", "0.5");
      case "Lowest":
         GraphicsMenu::set("$pref::GroundCover::densityScale", "0.25");
      default:
         GraphicsMenu::set("$pref::GroundCover::densityScale", "0.75");
   }
}

function GroundCoverDensity::get()
{
   if($pref::GroundCover::densityScale == 1)
      return "High";
   else if($pref::GroundCover::densityScale == 0.75)
      return "Medium";
   else if($pref::GroundCover::densityScale == 0.5)
      return "Low";
   else if($pref::GroundCover::densityScale == 0.25)
      return "Lowest";
   else
      return "Custom";
}

function GroundCoverDensity::getList()
{
   return "Lowest,Low,Medium,High";
}

//
function DecalLifetime::set(%setting)
{
   switch$(%setting)
   {
      case "High":
         GraphicsMenu::set("$pref::decalMgr::enabled", "true");
         GraphicsMenu::set("$pref::Decals::lifeTimeScale", "1");
      case "Medium":
         GraphicsMenu::set("$pref::decalMgr::enabled", "true");
         GraphicsMenu::set("$pref::Decals::lifeTimeScale", "0.5");
      case "Low":
         GraphicsMenu::set("$pref::decalMgr::enabled", "true");
         GraphicsMenu::set("$pref::Decals::lifeTimeScale", "0.25");
      case "None":
         GraphicsMenu::set("$pref::decalMgr::enabled", "false");
      default:
         GraphicsMenu::set("$pref::decalMgr::enabled", "true");
         GraphicsMenu::set("$pref::Decals::lifeTimeScale", "0.5");
   }
}

function DecalLifetime::get()
{
   if($pref::decalMgr::enabled == true && $pref::Decals::lifeTimeScale == 1)
      return "High";
   else if($pref::decalMgr::enabled == true && $pref::Decals::lifeTimeScale == 0.5)
      return "Medium";
   else if($pref::decalMgr::enabled == true && $pref::Decals::lifeTimeScale == 0.25)
      return "Low";
   else if($pref::decalMgr::enabled == true )
      return "None";
   else
      return "Custom";
}

function DecalLifetime::getList()
{
   return "None,Low,Medium,High";
}

//
function TerrainQuality::set(%setting)
{
   switch$(%setting)
   {
      case "High":
         GraphicsMenu::set("$pref::Terrain::lodScale", "0.75");
         GraphicsMenu::set("$pref::Terrain::detailScale", "1.5");
      case "Medium":
         GraphicsMenu::set("$pref::Terrain::lodScale", "1");
         GraphicsMenu::set("$pref::Terrain::detailScale", "1");
      case "Low":
         GraphicsMenu::set("$pref::Terrain::lodScale", "1.5");
         GraphicsMenu::set("$pref::Terrain::detailScale", "0.75");
      case "Lowest":
         GraphicsMenu::set("$pref::Terrain::lodScale", "2");
         GraphicsMenu::set("$pref::Terrain::detailScale", "0.5");
      default:
         GraphicsMenu::set("$pref::decalMgr::enabled", "1");
         GraphicsMenu::set("$pref::Decals::lifeTimeScale", "1");
   }
}

function TerrainQuality::get()
{
   if($pref::Terrain::lodScale == 0.75 && $pref::Terrain::detailScale == 1.5)
      return "High";
   else if($pref::Terrain::lodScale == 1 && $pref::Terrain::detailScale == 1)
      return "Medium";
   else if($pref::Terrain::lodScale == 1.5 && $pref::Terrain::detailScale == 0.75)
      return "Low";
   else if($pref::Terrain::lodScale == 2 && $pref::Terrain::detailScale == 0.5)
      return "Lowest";
   else
      return "Custom";
}

function TerrainQuality::getList()
{
   return "Lowest,Low,Medium,High";
}

//
function ShadowQuality::set(%setting)
{
   switch$(%setting)
   {
      case "High":
         GraphicsMenu::set("$pref::Shadows::disable", "false");
         GraphicsMenu::set("$pref::Shadows::textureScalar", "1.0");
      case "Medium":
         GraphicsMenu::set("$pref::Shadows::disable", "false");
         GraphicsMenu::set("$pref::Shadows::textureScalar", "0.5");
      case "Low":
         GraphicsMenu::set("$pref::Shadows::disable", "false");
         GraphicsMenu::set("$pref::Shadows::textureScalar", "0.25");
      case "None":
         GraphicsMenu::set("$pref::Shadows::disable", "true");
         GraphicsMenu::set("$pref::Shadows::textureScalar", "0.5");
      default:
         GraphicsMenu::set("$pref::Shadows::disable", "false");
         GraphicsMenu::set("$pref::Shadows::textureScalar", "0.5");
   }
}

function ShadowQuality::get()
{
   if($pref::Shadows::disable == false && $pref::Shadows::textureScalar == 1.0)
      return "High";
   else if($pref::Shadows::disable == false && $pref::Shadows::textureScalar == 0.5)
      return "Medium";
   else if($pref::Shadows::disable == false && $pref::Shadows::textureScalar == 0.25)
      return "Low";
   else if($pref::Shadows::disable == true)
      return "None";
   else
      return "Custom";
}

function ShadowQuality::getList()
{
   return "None,Low,Medium,High";
}

//
function ShadowDistance::set(%setting)
{
   switch$(%setting)
   {
      case "Highest":
         GraphicsMenu::set("$pref::Shadows::drawDistance", "1.0");
      case "High":
         GraphicsMenu::set("$pref::Shadows::drawDistance", "0.75");
      case "Medium":
         GraphicsMenu::set("$pref::Shadows::drawDistance", "0.5");
      case "Low":
         GraphicsMenu::set("$pref::Shadows::drawDistance", "0.25");
      default:
         GraphicsMenu::set("$pref::Shadows::drawDistance", "0.5");
   }
}

function ShadowDistance::get()
{
   if($pref::Shadows::drawDistance == 1.0)
      return "Highest";
   else if($pref::Shadows::drawDistance == 0.75)
      return "High";
   else if($pref::Shadows::drawDistance == 0.5)
      return "Medium";
   else if($pref::Shadows::drawDistance == 0.25)
      return "Low";
   else
      return "Custom";
}

function ShadowDistance::getList()
{
   return "Low,Medium,High,Highest";
}

//
function SoftShadow::set(%setting)
{
   switch$(%setting)
   {
      case "High":
         GraphicsMenu::set("$pref::Shadows::filterMode", "SoftShadowHighQuality");
      case "Low":
         GraphicsMenu::set("$pref::Shadows::filterMode", "SoftShadow");
      case "Off":
         GraphicsMenu::set("$pref::Shadows::filterMode", "None");
      default:
         GraphicsMenu::set("$pref::Shadows::filterMode", "SoftShadow");
   }
}

function SoftShadow::get()
{
   if($pref::Shadows::filterMode $= "SoftShadowHighQuality")
      return "High";
   else if($pref::Shadows::filterMode $= "SoftShadow")
      return "Low";
   else if($pref::Shadows::filterMode $= "None")
      return "Off";
   else
      return "Custom";
}

function SoftShadow::getList()
{
   return "Off,Low,High";
}

//
function LightDistance::set(%setting)
{
   switch$(%setting)
   {
      case "High":
         GraphicsMenu::set("$pref::Lights::drawDistance", "1");
      case "Medium":
         GraphicsMenu::set("$pref::Lights::drawDistance", "0.75");
      case "Low":
         GraphicsMenu::set("$pref::Lights::drawDistance", "0.5");
      case "Lowest":
         GraphicsMenu::set("$pref::Lights::drawDistance", "0.25");
      default:
         GraphicsMenu::set("$pref::Lights::drawDistance", "0.75");
   }
}

function LightDistance::get()
{
   if($pref::Lights::drawDistance == 1)
      return "High";
   else if($pref::Lights::drawDistance == 0.75)
      return "Medium";
   else if($pref::Lights::drawDistance == 0.5)
      return "Low";
   else if($pref::Lights::drawDistance == 0.25)
      return "Lowest";
   else
      return "Custom";
}

function LightDistance::getList()
{
   return "Lowest,Low,Medium,High";
}

//
function ShaderQuality::set(%setting)
{
   switch$(%setting)
   {
      case "High":
         GraphicsMenu::set("$pref::Video::disablePixSpecular", "false");
         GraphicsMenu::set("$pref::Video::disableNormalmapping", "false");
      case "Low":
         GraphicsMenu::set("$pref::Video::disablePixSpecular", "true");
         GraphicsMenu::set("$pref::Video::disableNormalmapping", "true");
      default:
         GraphicsMenu::set("$pref::Video::disablePixSpecular", "false");
         GraphicsMenu::set("$pref::Video::disableNormalmapping", "false");
   }
}

function ShaderQuality::get()
{
   if($pref::Video::disablePixSpecular == false || $pref::Video::disableNormalmapping == false)
      return "High";
   else if($pref::Video::disablePixSpecular == true || $pref::Video::disableNormalmapping == true)
      return "Low";
   else
      return "Custom";
}

function ShaderQuality::getList()
{
   return "Low,High";
}

//
function ShadowCaching::set(%setting)
{
   switch$(%setting)
   {
      case "On":
         GraphicsMenu::set("$pref::Shadows::useShadowCaching", "true");
      case "Off":
         GraphicsMenu::set("$pref::Shadows::useShadowCaching", "false");
      default:
         GraphicsMenu::set("$pref::Shadows::useShadowCaching", "true");
   }
}

function ShadowCaching::get()
{
   if($pref::Shadows::useShadowCaching == true)
      return "On";
   else 
      return "Off";
}

function ShadowCaching::getList()
{
   return "Off,On";
}

//
function ParallaxSetting::set(%setting)
{
   switch$(%setting)
   {
      case "On":
         GraphicsMenu::set("$pref::Video::disableParallaxMapping", "false");
      case "Off":
         GraphicsMenu::set("$pref::Video::disableParallaxMapping", "true");
      default:
         GraphicsMenu::set("$pref::Video::disableParallaxMapping", "false");
   }
}

function ParallaxSetting::get()
{
   if($pref::Video::disableParallaxMapping == false)
      return "On";
   else 
      return "Off";
}

function ParallaxSetting::getList()
{
   return "Off,On";
}

//
function AmbientOcclusionSetting::set(%setting)
{
   switch$(%setting)
   {
      case "On":
         GraphicsMenu::set("$pref::PostFX::EnableSSAO", "true");
      case "Off":
         GraphicsMenu::set("$pref::PostFX::EnableSSAO", "false");
      default:
         GraphicsMenu::set("$pref::PostFX::EnableSSAO", "true");
   }
}

function AmbientOcclusionSetting::get()
{
   if($pref::PostFX::EnableSSAO == true)
      return "On";
   else 
      return "Off";
}

function AmbientOcclusionSetting::getList()
{
   return "Off,On";
}

//
function LightRaysSetting::set(%setting)
{
   switch$(%setting)
   {
      case "On":
         GraphicsMenu::set("$pref::PostFX::EnableLightRays", "true");
      case "Off":
         GraphicsMenu::set("$pref::PostFX::EnableLightRays", "false");
      default:
         GraphicsMenu::set("$pref::PostFX::EnableLightRays", "true");
   }
}

function LightRaysSetting::get()
{
   if($pref::PostFX::EnableLightRays == true)
      return "On";
   else 
      return "Off";
}

function LightRaysSetting::getList()
{
   return "Off,On";
}

//
function DOFSetting::set(%setting)
{
   switch$(%setting)
   {
      case "On":
         GraphicsMenu::set("$pref::PostFX::EnableDOF", "true");
      case "Off":
         GraphicsMenu::set("$pref::PostFX::EnableDOF", "false");
      default:
         GraphicsMenu::set("$pref::PostFX::EnableDOF", "true");
   }
}

function DOFSetting::get()
{
   if($pref::PostFX::EnableLightRays == true)
      return "On";
   else 
      return "Off";
}

function DOFSetting::getList()
{
   return "Off,On";
}

//
function WaterReflectionSetting::set(%setting)
{
   switch$(%setting)
   {
      case "On":
         GraphicsMenu::set("$pref::Water::disableTrueReflections", "false");
      case "Off":
         GraphicsMenu::set("$pref::Water::disableTrueReflections", "true");
      default:
         GraphicsMenu::set("$pref::Water::disableTrueReflections", "false");
   }
}

function WaterReflectionSetting::get()
{
   if($pref::Water::disableTrueReflections == false)
      return "On";
   else 
      return "Off";
}

function WaterReflectionSetting::getList()
{
   return "Off,On";
}

//
function VignetteSetting::set(%setting)
{
   switch$(%setting)
   {
      case "On":
         GraphicsMenu::set("$pref::PostFX::EnableVignette", "true");
      case "Off":
         GraphicsMenu::set("$pref::PostFX::EnableVignette", "false");
      default:
         GraphicsMenu::set("$pref::PostFX::EnableVignette", "true");
   }
}

function VignetteSetting::get()
{
   if($pref::PostFX::EnableVignette == true)
      return "On";
   else 
      return "Off";
}

function VignetteSetting::getList()
{
   return "Off,On";
}

//
function AASetting::set(%setting)
{
   switch$(%setting)
   {
      case "4x":
         GraphicsMenu::set("$pref::Video::AA", "4");
      case "2x":
         GraphicsMenu::set("$pref::Video::AA", "2");
      case "1x":
         GraphicsMenu::set("$pref::Video::AA", "1");
      case "Off":
         GraphicsMenu::set("$pref::Video::AA", "0");
      default:
         GraphicsMenu::set("$pref::Video::AA", "0");
   }
}

function AASetting::get()
{
   if($pref::Video::AA == 4)
      return "4x";
   else if($pref::Video::AA == 2)
      return "2x";
   else if($pref::Video::AA == 1)
      return "1x";
   else if($pref::Video::AA == 0)
      return "Off";
   else
      return "Custom";
}

function AASetting::getList()
{
   return "Off,1x,2x,4x";
}

//
function AnisotropicFilteringSetting::set(%setting)
{
   switch$(%setting)
   {
      case "16x":
         GraphicsMenu::set("$pref::Video::defaultAnisotropy", "16");
      case "8x":
         GraphicsMenu::set("$pref::Video::defaultAnisotropy", "8");
      case "4x":
         GraphicsMenu::set("$pref::Video::defaultAnisotropy", "4");
      case "Off":
         GraphicsMenu::set("$pref::Video::defaultAnisotropy", "0");
      default:
         GraphicsMenu::set("$pref::Video::defaultAnisotropy", "0");
   }
}

function AnisotropicFilteringSetting::get()
{
   if($pref::Video::defaultAnisotropy == 16)
      return "16x";
   else if($pref::Video::defaultAnisotropy == 8)
      return "8x";
   else if($pref::Video::defaultAnisotropy == 4)
      return "4x";
   else if($pref::Video::defaultAnisotropy == 0)
      return "Off";
   else
      return "Custom";
}

function AnisotropicFilteringSetting::getList()
{
   return "Off,4x,8x,16x";
}