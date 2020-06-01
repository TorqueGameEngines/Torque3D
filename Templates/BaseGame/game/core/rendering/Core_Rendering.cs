
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
   
   exec("./scripts/graphicsOptions.cs");
   exec("./scripts/renderManager.cs");
   exec("./scripts/gfxData/clouds.cs");
   exec("./scripts/gfxData/commonMaterialData.cs");
   exec("./scripts/gfxData/scatterSky.cs");
   exec("./scripts/gfxData/shaders.cs");
   exec("./scripts/gfxData/terrainBlock.cs");
   exec("./scripts/gfxData/water.cs");
   exec("./scripts/gfxData/warningTerrainMat.cs");
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
   %prefPath = getPrefpath();
   if ( isFile( %prefPath @ "/clientPrefs.cs" ) )
      exec( %prefPath @ "/clientPrefs.cs" );
   else
      exec("data/defaults.cs");
   
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