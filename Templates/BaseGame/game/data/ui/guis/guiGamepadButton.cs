//------------------------------------------------------------------------------
// global vars
//------------------------------------------------------------------------------

$BUTTON_A         =  0;
$BUTTON_B         =  1;
$BUTTON_X         =  2;
$BUTTON_Y         =  3;
$BUTTON_BACK      =  4;
$BUTTON_START     =  5;
$BUTTON_LTRIGGER  =  6;
$BUTTON_RTRIGGER  =  7;
$BUTTON_LSHOULDER =  8;
$BUTTON_RSHOULDER =  9;
$BUTTON_LSTICK    =  10;
$BUTTON_RSTICK    =  11;

//------------------------------------------------------------------------------
// GamepadButtonsGui methods
//------------------------------------------------------------------------------

/// Callback when this control wakes up. All buttons are set to invisible and
/// disabled.
function GamepadButtonsGui::onWake(%this)
{
   GamepadButtonsGui.controllerName = "K&M";
}

function GamepadButtonsGui::initMenuButtons(%this)
{
   %buttonExt = %this.extent.x / 4 SPC %this.extent.y / 2;
   
   for(%i=0; %i < 9; %i++)
   {
      %btn = new GuiIconButtonCtrl()
      {
         iconLocation = "Left";
         sizeIconToButton = true;
         makeIconSquare = true;
         textLocation = "Right";
         extent = %buttonExt;
         profile="GuiMenuButtonProfile";
         gamepadButton = "";
         keyboardButton = "";
      };
   
      GamepadButtonsGui.addGuiControl(%btn); 
   } 
   
   GamepadButtonsGui.refresh();
}

/// Sets the command and text for the specified button. If %text and %command
/// are left empty, the button will be disabled and hidden.
/// Note: This command is not executed when the A button is pressed. That
/// command is executed directly from the GuiGameList___Ctrl. This command is
/// for the graphical hint and to allow a mouse equivalent.
///
/// \param %button (constant) The button to set. See: $BUTTON_A, _B, _X, _Y
/// \param %text (string) The text to display next to the A button graphic.
/// \param %command (string) The command executed when the A button is pressed.
function GamepadButtonsGui::setButton(%this, %buttonIdx, %gamepadButton, %keyboardButton, %text, %command, %gamepadOnly)
{
   if(%buttonIdx >= GamepadButtonsGui.getCount())
      return;
      
   %btn = GamepadButtonsGui.getObject(%buttonIdx);
   
   %set = (! ((%text $= "") && (%command $= "")));
   %btn.setText(%text);
   %btn.setActive(%set);
   %btn.setVisible(%set);
   
   %btn.gamepadButton = %gamepadButton;
   %btn.keyboardButton = %keyboardButton;
   
   if(%gamepadOnly $= "")
      %gamepadOnly = false;
      
   %btn.gamepadOnly = %gamepadOnly;

   %btn.Command = %command;
}

function GamepadButtonsGui::checkGamepad(%this)
{
   %controllerName = SDLInputManager::JoystickNameForIndex(0);
   
   GamepadButtonsGui.controllerName = %controllerName;
}
   
function GamepadButtonsGui::clearButtons(%this)
{
   for(%i=0; %i < GamepadButtonsGui.getCount(); %i++)
   {
      %btn = GamepadButtonsGui.getObject(%i);
      
      %btn.setBitmap("");
      %btn.text = "";
      %btn.command = "";
   }
}

function GamepadButtonsGui::refreshButtons(%this)
{
   //Set up our basic buttons
   for(%i=0; %i < GamepadButtonsGui.getCount(); %i++)
   {
      %btn = GamepadButtonsGui.getObject(%i);
      
      %set = (! ((%btn.text $= "") && (%btn.command $= "")));
      
      //Special-case of where we're in keyboard+mouse mode, but the menubutton is gamepad only mode, so we early out
      if(%btn.gamepadOnly && GamepadButtonsGui.controllerName $= "K&M")
         %set = false;
         
      %btn.setActive(%set);
      %btn.setVisible(%set);
      
      if(!%btn.isActive())
         continue;
      
      if(GamepadButtonsGui.controllerName !$= "K&M")
      {
         if(%btn.gamepadButton !$= "")
         {
            %path = "";
            if(GamepadButtonsGui.controllerName $= "PS4 Controller")
            { 
               %path = "data/ui/images/inputs/PS4/PS4_";
               
               if(%btn.gamepadButton $= "A")
                  %path = %path @ "Cross";
               else if(%btn.gamepadButton $= "B")
                  %path = %path @ "Circle";
               else if(%btn.gamepadButton $= "X")
                  %path = %path @ "Square";
               else if(%btn.gamepadButton $= "Y")
                  %path = %path @ "Triangle";
               else if(%btn.gamepadButton $= "LB")
                  %path = %path @ "L1";
               else if(%btn.gamepadButton $= "LT")
                  %path = %path @ "L2";
               else if(%btn.gamepadButton $= "RB")
                  %path = %path @ "R1";
               else if(%btn.gamepadButton $= "RT")
                  %path = %path @ "R2";
               else      
                  continue;
            }
            else if(GamepadButtonsGui.controllerName $= "Nintendo Switch Pro Controller")
            {
               %path = "data/ui/images/inputs/Switch/Switch_";
               
               if(%btn.gamepadButton $= "A")
                  %path = %path @ "B";
               else if(%btn.gamepadButton $= "B")
                  %path = %path @ "A";
               else if(%btn.gamepadButton $= "X")
                  %path = %path @ "Y";
               else if(%btn.gamepadButton $= "Y")
                  %path = %path @ "X";
               else if(%btn.gamepadButton $= "LB")
                  %path = %path @ "LB";
               else if(%btn.gamepadButton $= "LT")
                  %path = %path @ "LT";
               else if(%btn.gamepadButton $= "RB")
                  %path = %path @ "RB";
               else if(%btn.gamepadButton $= "RT")
                  %path = %path @ "RT";
               else      
                  continue;
            }
            else if(GamepadButtonsGui.controllerName !$= "")
            {
               %path = "data/ui/images/inputs/Xbox/Xbox_";
               
               %path = %path @ %btn.gamepadButton;
            }
         } 
      }
      else
      {
         if(%btn.keyboardButton !$= "")
         {
            %path = "data/ui/images/Inputs/Keyboard & Mouse/Keyboard_Black_" @ %btn.keyboardButton;
         }
      }
      
      %btn.setBitmap(%path);
   }
   
   return true;
}

function GamepadButtonsGui::processInputs(%this, %device, %action)
{
   //check to see if our status has changed
   %changed = false;
   
   %oldDevice = GamepadButtonsGui.controllerName;
   
   if(startsWith(%device, "Keyboard"))
   {
      if(GamepadButtonsGui.controllerName !$= %device)
         %changed = true;
         
      GamepadButtonsGui.controllerName = "K&M";
      Canvas.showCursor();
   }
   else if(startsWith(%device, "Mouse"))
   {
      if(startsWith(%action, "button"))
      {
         if(GamepadButtonsGui.controllerName !$= %device)
            %changed = true;
            
         GamepadButtonsGui.controllerName = "K&M";
         Canvas.showCursor();
      }
   }
   else
   {
      if(GamepadButtonsGui.checkGamepad())
      {
         Canvas.hideCursor();
      }
      
      if(GamepadButtonsGui.controllerName !$= %device)
         %changed = true;
   }
   
   if(%changed)
      GamepadButtonsGui.refreshButtons();
      
   //Now process the input for the button accelerator, if applicable
   //Set up our basic buttons
   for(%i=0; %i < GamepadButtonsGui.getCount(); %i++)
   {
      %btn = GamepadButtonsGui.getObject(%i);
      
      if(!%btn.isActive())
         continue;
      
      if(GamepadButtonsGui.controllerName !$= "K&M")
      {
         if(%action $= "btn_r")
            %action = "RB";
         else if(%action $= "btn_l")
            %action = "LB";
            
         if(%btn.gamepadButton $= %action)
         {
            eval(%btn.command);
         }
      }
      else
      {
         if(%action $= "return")
            %action = "enter";
         else if(%action $= "escape")
            %action = "esc";
            
         if(%btn.keyboardButton $= %action)
         {
            eval(%btn.command);
         }
      }
   }
}

function GamepadButtonsGui::processAxisEvent(%this, %device, %action, %axisVal)
{
   %changed = false;
   
   %oldDevice = GamepadButtonsGui.controllerName;
   
   if(startsWith(%device, "Mouse"))
   {
      if(startsWith(%action, "button"))
      {
         if(GamepadButtonsGui.controllerName !$= %device)
            %changed = true;
            
         GamepadButtonsGui.controllerName = "K&M";
         Canvas.showCursor();
      }
   }
   else
   {
      if(GamepadButtonsGui.checkGamepad())
      {
         Canvas.hideCursor();
      }
      
      if(GamepadButtonsGui.controllerName !$= %device)
         %changed = true;
   }
   
   if(%changed)
      GamepadButtonsGui.refreshButtons();
}
//
//
function onSDLDeviceConnected(%sdlIndex, %deviceName, %deviceType)
{
   /*if(GamepadButtonsGui.checkGamepad())
   {
      GamepadButtonsGui.hidden = false;  
   }*/
}

function onSDLDeviceDisconnected(%sdlIndex)
{
   /*if(!GamepadButtonsGui.checkGamepad())
   {
      GamepadButtonsGui.hidden = true;
   }*/   
}