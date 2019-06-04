
function ToolsModule::onCreate(%this)
{
   // ----------------------------------------------------------------------------
   // Initialize core sub system functionality such as audio, the Canvas, PostFX,
   // rendermanager, light managers, etc.
   //
   // Note that not all of these need to be initialized before the client, although
   // the audio should and the canvas definitely needs to be.  I've put things here
   // to distinguish between the purpose and functionality of the various client
   // scripts.  Game specific script isn't needed until we reach the shell menus
   // and start a game or connect to a server. We get the various subsystems ready
   // to go, and then use initClient() to handle the rest of the startup sequence.
   //
   // If this is too convoluted we can reduce this complexity after futher testing
   // to find exactly which subsystems should be readied before kicking things off. 
   // ----------------------------------------------------------------------------
   
   new Settings(EditorSettings) { file = "tools/settings.xml"; };
   EditorSettings.read();
   
   ModuleDatabase.LoadExplicit( "MainEditor" );
   ModuleDatabase.LoadExplicit( "Tools_ObjectViewer" );
}

function ToolsModule::onDestroy(%this)
{

}