
function Core_Lighting::onCreate(%this)
{
   exec("./scripts/lighting.ts");
   
   //Advanced/Deferred
   exec("./scripts/advancedLighting_Shaders.ts");
   exec("./scripts/deferredShading.ts");
   exec("./scripts/advancedLighting_Init.ts");
   
   //Basic/Forward
   exec("./scripts/basicLighting_shadowFilter.ts");
   exec("./scripts/shadowMaps_Init.ts");
   exec("./scripts/basicLighting_Init.ts");
   
}

function Core_Lighting::onDestroy(%this)
{
}