
function Core_GUI::onCreate(%this)
{
   exec("./scripts/profiles.ts");
   exec("./scripts/canvas.ts");
   exec("./scripts/cursor.ts");
}

function Core_GUI::onDestroy(%this)
{
}