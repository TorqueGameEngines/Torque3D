function initClient()
{
   echo("\n--------- Initializing " @ $appName @ ": Client Scripts ---------");

   // Make sure this variable reflects the correct state.
   $Server::Dedicated = false;

   // Game information used to query the master server
   $Client::GameTypeQuery = $appName;
   $Client::MissionTypeQuery = "Any";
   
   exec( "./message.cs" );
   exec( "./connectionToServer.cs" );
   exec( "./levelDownload.cs" );
   exec( "./levelLoad.cs" );
   
   //load prefs
   exec( "data/defaults.cs" );
   %prefPath = getPrefpath();
   if ( isFile( %prefPath @ "/clientPrefs.cs" ) )
      exec( %prefPath @ "/clientPrefs.cs" );
      
   callOnModules("initClient");

   loadMaterials();

   // Copy saved script prefs into C++ code.
   setDefaultFov( $pref::Player::defaultFov );
   setZoomSpeed( $pref::Player::zoomSpeed );
}