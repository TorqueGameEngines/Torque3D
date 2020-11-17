
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
   
   exec("./scripts/graphicsOptions.ts");
   exec("./scripts/renderManager.ts");
   exec("./scripts/gfxData/clouds.ts");
   exec("./scripts/gfxData/commonMaterialData.ts");
   exec("./scripts/gfxData/scatterSky.ts");
   exec("./scripts/gfxData/shaders.ts");
   exec("./scripts/gfxData/terrainBlock.ts");
   exec("./scripts/gfxData/water.ts");
   exec("./scripts/gfxData/warningTerrainMat.ts");
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
   exec("data/defaults.ts");
   %prefPath = getPrefpath();
   if ( isFile( %prefPath @ "/clientPrefs.ts" ) )
      exec( %prefPath @ "/clientPrefs.ts" );
   
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