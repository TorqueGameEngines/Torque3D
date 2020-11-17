function initClient()
{
   echo("\n--------- Initializing " @ $appName @ ": Client Scripts ---------");

   // Make sure this variable reflects the correct state.
   $Server::Dedicated = false;

   // Game information used to query the master server
   $Client::GameTypeQuery = $appName;
   $Client::MissionTypeQuery = "Any";
   
   exec( "./message.ts" );
   exec( "./connectionToServer.ts" );
   exec( "./levelDownload.ts" );
   exec( "./levelLoad.ts" );
   
   //load prefs
   exec( "data/defaults.ts" );
   %prefPath = getPrefpath();
   if ( isFile( %prefPath @ "/clientPrefs.ts" ) )
      exec( %prefPath @ "/clientPrefs.ts" );
      
   callOnModules("initClient");

   loadMaterials();

   // Copy saved script prefs into C++ code.
   setDefaultFov( $pref::Player::defaultFov );
   setZoomSpeed( $pref::Player::zoomSpeed );
}