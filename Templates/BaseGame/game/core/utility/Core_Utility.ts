
function Core_Utility::onCreate(%this)
{
   exec("./scripts/parseArgs.cs");
   exec("./scripts/globals.cs");
   exec("./scripts/helperFunctions.cs");
   exec("./scripts/gameObjectManagement.cs");
   exec("./scripts/persistanceManagement.cs");
   exec("./scripts/module.cs");
   exec("./scripts/scene.cs");
   exec("./scripts/input.cs");
}

function Core_Utility::onDestroy(%this)
{
}