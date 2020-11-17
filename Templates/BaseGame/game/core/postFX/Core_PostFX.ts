
function Core_PostFX::onCreate(%this)
{
   //
   exec("./scripts/postFxManager.cs");
   exec("./scripts/postFx.cs");
   
   //Load the default config
   loadPresetHandler("./scripts/default.postfxpreset.cs");
}

function Core_PostFX::onDestroy(%this)
{
}