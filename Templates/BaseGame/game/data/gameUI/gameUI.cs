function gameUI::create( %this )
{
   if (!$Server::Dedicated)
   {
      //guis
      exec("./GUIs/playGui.gui");
      exec("./GUIs/playGui.cs");
   }
}

function gameUI::destroy( %this )
{
   
}