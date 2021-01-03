
function Core_Rendering::onCreate(%this)
{
   $Core::MissingTexturePath = "core/rendering/images/missingTexture";
   $Core::UnAvailableTexturePath = "core/rendering/images/unavailable";
   $Core::WarningTexturePath = "core/rendering/images/warnMat";
   $Core::CommonShaderPath = "core/rendering/shaders";
   $Core::DefaultIrradianceCubemap = "core/rendering/images/default_irradiance.dds";
   $Core::DefaultPrefilterCubemap = "core/rendering/images/default_prefilter.dds";
   $Core::BRDFTexture = "core/rendering/images/brdfTexture.dds";
   
   $pref::ReflectionProbes::BakeResolution = ProjectSettings.value("Rendering/ProbeCaptureResolution", "64");
   
   $Terrain::LerpBlend = ProjectSettings.value("Terrain/LerpBlend");
   $Terrain::BlendDepth = ProjectSettings.value("Terrain/BlendDepth");
   
   $Terrain::DetailTextureSize = ProjectSettings.value("Terrain/DetailTextureSize");
   $Terrain::MacroTextureSize = ProjectSettings.value("Terrain/MacroTextureSize");
   $Terrain::NormalTextureSize = ProjectSettings.value("Terrain/NormalTextureSize");
   $Terrain::OrmTextureSize = ProjectSettings.value("Terrain/OrmTextureSize");
   
   $Terrain::DetailTextureFormat = ProjectSettings.value("Terrain/DetailTextureFormat");
   $Terrain::MacroTextureFormat = ProjectSettings.value("Terrain/MacroTextureFormat");
   $Terrain::NormalTextureFormat = ProjectSettings.value("Terrain/NormalTextureFormat");
   $Terrain::OrmTextureFormat = ProjectSettings.value("Terrain/OrmTextureFormat");
   
   exec("./scripts/graphicsOptions.cs");
   exec("./scripts/terrainSettings.cs");
   exec("./scripts/renderManager.cs");
   exec("./scripts/gfxData/clouds.cs");
   exec("./scripts/gfxData/commonMaterialData.cs");
   exec("./scripts/gfxData/scatterSky.cs");
   exec("./scripts/gfxData/shaders.cs");
   exec("./scripts/gfxData/terrainBlock.cs");
   exec("./scripts/gfxData/water.cs");
   exec("./scripts/gfxData/warningTerrainMat.cs");
   
   loadTerrainSettings();
}

function Core_Rendering::onDestroy(%this)
{
}

function Core_Rendering::initClient(%this)
{
   // Start rendering and stuff.
   initRenderManager();
   initLightingSystems("Advanced Lighting"); 

   //load prefs
   exec("data/defaults.cs");
   %prefPath = getPrefpath();
   if ( isFile( %prefPath @ "/clientPrefs.cs" ) )
      exec( %prefPath @ "/clientPrefs.cs" );
   
   configureCanvas();
   
   //Autodetect settings if it's our first time
   if($pref::Video::autoDetect)
      AutodetectGraphics();

   postFXInit();
   
   closeSplashWindow();
   
   // As we know at this point that the initial load is complete,
   // we can hide any splash screen we have, and show the canvas.
   // This keeps things looking nice, instead of having a blank window
   Canvas.showWindow();
}