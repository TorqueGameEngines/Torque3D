
function Core_PostFX::onCreate(%this)
{
   //
   exec("./scripts/postFxManager.ts");
   exec("./scripts/postFx.ts");
   
   //Load the default config
   loadPresetHandler("./scripts/default.postfxpreset.ts");
}

function Core_PostFX::onDestroy(%this)
{
}