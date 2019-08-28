function Core_GameObjects::onCreate(%this)
{
}

function Core_GameObjects::onDestroy(%this)
{
}

function Core_GameObjects::initServer( %this )
{
}

function Core_GameObjects::onCreateGameServer(%this)
{
   %this.registerDatablock("./datablocks/defaultDatablocks.cs");
}

function Core_GameObjects::onDestroyGameServer(%this)
{
}

function Core_GameObjects::initClient( %this )
{
}

function Core_GameObjects::onCreateClientConnection(%this)
{
}

function Core_GameObjects::onDestroyClientConnection(%this)
{
}