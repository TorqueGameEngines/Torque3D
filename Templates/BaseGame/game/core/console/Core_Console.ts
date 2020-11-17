
function Core_Console::onCreate(%this)
{
    exec("./scripts/profiles.ts");
    exec("./scripts/console.ts");

    exec("./guis/console.gui");
}

function Core_Console::onDestroy(%this)
{
}