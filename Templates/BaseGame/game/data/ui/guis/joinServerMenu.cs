
function JoinServerMenu::onWake()
{
   // Double check the status. Tried setting this the control
   // inactive to start with, but that didn't seem to work.
   JoinServerJoinBtn.setActive(JS_serverList.rowCount() > 0);
}   

function JoinServerButtonHolder::onWake(%this)
{
   %this.refresh();
}

function JoinServerButtonHolder::refresh(%this)
{
   JoinServerButtonHolder.add(GamepadButtonsGui);
   
   GamepadButtonsGui.clearButtons();
   
   GamepadButtonsGui.setButton(1, "A", "", "Query LAN", "JoinServerMenu.queryLan();");
   GamepadButtonsGui.setButton(2, "X", "", "Query Internet", "JoinServerMenu.query();");
   GamepadButtonsGui.setButton(3, "B", "", "Refresh", "JoinServerMenu.refresh();");
   GamepadButtonsGui.setButton(6, "Start", "Enter", "Join", "JoinServerMenu.join();");
   GamepadButtonsGui.setButton(7, "B", "Esc", "Back", "JoinServerMenu.backOut();");
   
   GamepadButtonsGui.refreshButtons();
}

//----------------------------------------
function JoinServerMenu::query(%this)
{
   queryMasterServer(
      0,          // Query flags
      $Client::GameTypeQuery,       // gameTypes
      $Client::MissionTypeQuery,    // missionType
      0,          // minPlayers
      100,        // maxPlayers
      0,          // maxBots
      2,          // regionMask
      0,          // maxPing
      100,        // minCPU
      0           // filterFlags
   );
}

//----------------------------------------
function JoinServerMenu::queryLan(%this)
{
   queryLANServers(
      $pref::Net::Port,      // lanPort for local queries
      0,          // Query flags
      $Client::GameTypeQuery,       // gameTypes
      $Client::MissionTypeQuery,    // missionType
      0,          // minPlayers
      100,        // maxPlayers
      0,          // maxBots
      2,          // regionMask
      0,          // maxPing
      100,        // minCPU
      0           // filterFlags
   );
}

//----------------------------------------
function JoinServerMenu::cancel(%this)
{
   cancelServerQuery();
   JS_queryStatus.setVisible(false);
}


//----------------------------------------
function JoinServerMenu::join(%this)
{
   cancelServerQuery();
   %index = JS_serverList.getSelectedId();

   JoinGame(%index);
}

//----------------------------------------
function JoinServerMenu::refresh(%this)
{
   cancelServerQuery();
   %index= JS_serverList.getSelectedId();

   // The server info index is stored in the row along with the
   // rest of displayed info.
   if( setServerInfo( %index ) )
      querySingleServer( $ServerInfo::Address, 0 );
}

//----------------------------------------
function JoinServerMenu::refreshSelectedServer( %this )
{
   querySingleServer( $JoinGameAddress, 0 );
}

//----------------------------------------
function JoinServerMenu::backOut(%this)
{
   cancelServerQuery();
   
   Canvas.popDialog(JoinServerMenu);
   if(isObject(JoinServerMenu.returnGui) && JoinServerMenu.returnGui.isMethod("onReturnTo"))    
      JoinServerMenu.returnGui.onReturnTo();  
}

//----------------------------------------
function JoinServerMenu::update(%this)
{
   // Copy the servers into the server list.
   JS_queryStatus.setVisible(false);
   JS_serverList.clear();
   %sc = getServerCount();
   for( %i = 0; %i < %sc; %i ++ ) {
      setServerInfo(%i);
      JS_serverList.addRow( %i,
         $ServerInfo::Name TAB
         $ServerInfo::Ping TAB
         $ServerInfo::PlayerCount @ "/" @ $ServerInfo::MaxPlayers TAB
         $ServerInfo::Version TAB
         $ServerInfo::MissionName
      );
   }
   JS_serverList.sort(0);
   JS_serverList.setSelectedRow(0);
   JS_serverList.scrollVisible(0);

   JoinServerJoinBtn.setActive(JS_serverList.rowCount() > 0);
} 

//----------------------------------------
function onServerQueryStatus(%status, %msg, %value)
{
	echo("ServerQuery: " SPC %status SPC %msg SPC %value);
   // Update query status
   // States: start, update, ping, query, done
   // value = % (0-1) done for ping and query states
   if (!JS_queryStatus.isVisible())
      JS_queryStatus.setVisible(true);

   switch$ (%status) {
      case "start":
         JoinServerJoinBtn.setActive(false);
         JoinServerQryInternetBtn.setActive(false);
         JS_statusText.setText(%msg);
         JS_statusBar.setValue(0);
         JS_serverList.clear();

      case "ping":
         JS_statusText.setText("Ping Servers");
         JS_statusBar.setValue(%value);

      case "query":
         JS_statusText.setText("Query Servers");
         JS_statusBar.setValue(%value);

      case "done":
         JoinServerQryInternetBtn.setActive(true);
         JS_queryStatus.setVisible(false);
         JS_status.setText(%msg);
         JoinServerMenu.update();
   }
}
