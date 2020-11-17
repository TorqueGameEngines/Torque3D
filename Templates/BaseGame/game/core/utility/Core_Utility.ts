
function Core_Utility::onCreate(%this)
{
   exec("./scripts/parseArgs.ts");
   exec("./scripts/globals.ts");
   exec("./scripts/helperFunctions.ts");
   exec("./scripts/gameObjectManagement.ts");
   exec("./scripts/persistanceManagement.ts");
   exec("./scripts/module.ts");
   exec("./scripts/scene.ts");
   exec("./scripts/input.ts");
}

function Core_Utility::onDestroy(%this)
{
}