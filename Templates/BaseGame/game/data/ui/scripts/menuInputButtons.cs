//==============================================================================
// Menu Input Buttons
// This file manages the Menu Input Buttons stuff
// Any time you have a GUI button that should be clickable AND map to a key input
// such as a gamepad button, or enter, etc, this stuff can be used
//==============================================================================
/*
Gamepad input reference for 360 controller
btn_a = A
btn_b = B
btn_x = X
btn_y = Y
btn_r = Right Bumper
btn_l = Right Bumper
upov = Dpad Up
dpov = Dpad Down
lpov = Dpad Left
rpov = Dpad Right
xaxis = Left Stick | + values = up, - values = down
yaxis = Left Stick | + values = up, - values = down
rxaxis = Right Stick | + values = up, - values = down
ryaxis = Right Stick | + values = up, - values = down
zaxis = Left Trigger
rzaxis = Right Trigger
btn_start = Start
btn_back = Back/Select
*/

/// This is used with the main UI menu lists, when a non-axis input event is called
/// such as pressing a button
/// It is called from the engine
function UIMenuButtonList::onInputEvent(%this, %device, %action, %state)
{
   if(%state)
      $activeMenuButtonContainer.processInputs(%device, %action);
}

/// This is used with the main UI menu lists, when an axis input event is called
/// such as moving a joystick
/// It is called from the engine
function UIMenuButtonList::onAxisEvent(%this, %device, %action, %axisVal)
{
   //Skip out of the value is too low as it could just be noise or miscalibrated defaults
   if(%axisVal < 0.02)
      return;
      
   $activeMenuButtonContainer.processAxisEvent(%device, %action);
}

/// Sets the command and text for the specified button. If %text and %command
/// are left empty, the button will be disabled and hidden.
///
/// \param %gamepadButton (string) The button to set for when using gamepad input. See the input map reference comment at the top of the file
/// \param %keyboardButton (string) The button to set for when using keyboard/mouse input.
/// \param %text (string) The text to display next to the A button graphic.
/// \param %command (string) The command executed when the A button is pressed.
/// \param %gamepadOnly (bool) If true, will only show the button when working in the gamepad input mode
function MenuInputButton::set(%this, %gamepadButton, %keyboardButton, %text, %command, %gamepadOnly)
{
   %set = (! ((%text $= "") && (%command $= "")));
   %this.setText(%text);
   %this.setActive(%set);
   %this.setVisible(%set);
   
   %this.gamepadButton = %gamepadButton;
   %this.keyboardButton = %keyboardButton;
   
   if(%gamepadOnly $= "")
      %gamepadOnly = false;
      
   %this.gamepadOnly = %gamepadOnly;

   %this.Command = %command;
}

/// Refreshes the specific button, updating it's visbility status and the displayed input image
function MenuInputButton::refresh(%this)
{
   %set = (! ((%this.text $= "") && (%this.command $= "")));
   
   //Special-case of where we're in keyboard+mouse mode, but the menubutton is gamepad only mode, so we early out
   if(%this.gamepadOnly && $activeControllerType !$= "gamepad")
      %set = false;
      
   %this.setActive(%set);
   %this.setVisible(%set);
   
   if(!%this.isActive())
      return;
   
   if($activeControllerType $= "gamepad")
   {
      if(%this.gamepadButton !$= "")
      {
         %path = "";
         if($activeControllerName $= "PS4 Controller")
         { 
            %path = "data/ui/images/inputs/PS4/PS4_";
            
            if(%this.gamepadButton $= "btn_a")
               %path = %path @ "Cross";
            else if(%this.gamepadButton $= "btn_b")
               %path = %path @ "Circle";
            else if(%this.gamepadButton $= "btn_x")
               %path = %path @ "Square";
            else if(%this.gamepadButton $= "btn_y")
               %path = %path @ "Triangle";
            else if(%this.gamepadButton $= "btn_l")
               %path = %path @ "L1";
            else if(%this.gamepadButton $= "zaxis")
               %path = %path @ "L2";
            else if(%this.gamepadButton $= "btn_r")
               %path = %path @ "R1";
            else if(%this.gamepadButton $= "rzaxis")
               %path = %path @ "R2";
            else if(%this.gamepadButton $= "btn_start")
               %path = %path @ "Options";
            else if(%this.gamepadButton $= "btn_back")
               %path = %path @ "Share";
         }
         else if($activeControllerName $= "Nintendo Switch Pro Controller")
         {
            %path = "data/ui/images/inputs/Switch/Switch_";
            
            if(%this.gamepadButton $= "btn_a")
               %path = %path @ "B";
            else if(%this.gamepadButton $= "btn_b")
               %path = %path @ "A";
            else if(%this.gamepadButton $= "btn_x")
               %path = %path @ "Y";
            else if(%this.gamepadButton $= "btn_y")
               %path = %path @ "X";
            else if(%this.gamepadButton $= "btn_l")
               %path = %path @ "LB";
            else if(%this.gamepadButton $= "zaxis")
               %path = %path @ "LT";
            else if(%this.gamepadButton $= "btn_r")
               %path = %path @ "RB";
            else if(%this.gamepadButton $= "rzaxis")
               %path = %path @ "RT";
            else if(%this.gamepadButton $= "btn_start")
               %path = %path @ "Plus";
            else if(%this.gamepadButton $= "btn_back")
               %path = %path @ "Minus";
         }
         else if($activeControllerName !$= "")
         {
            %path = "data/ui/images/inputs/Xbox/Xbox_";
            
            if(%this.gamepadButton $= "btn_a")
               %path = %path @ "A";
            else if(%this.gamepadButton $= "btn_b")
               %path = %path @ "B";
            else if(%this.gamepadButton $= "btn_x")
               %path = %path @ "X";
            else if(%this.gamepadButton $= "btn_y")
               %path = %path @ "Y";
            else if(%this.gamepadButton $= "btn_l")
               %path = %path @ "LB";
            else if(%this.gamepadButton $= "zaxis")
               %path = %path @ "LT";
            else if(%this.gamepadButton $= "btn_r")
               %path = %path @ "RB";
            else if(%this.gamepadButton $= "rzaxis")
               %path = %path @ "RT";
            else if(%this.gamepadButton $= "btn_start")
               %path = %path @ "Menu";
            else if(%this.gamepadButton $= "btn_back")
               %path = %path @ "Windows";
         }
      } 
   }
   else
   {
      if(%this.keyboardButton !$= "")
      {
         %path = "data/ui/images/Inputs/Keyboard & Mouse/Keyboard_Black_" @ %this.keyboardButton;
      }
   }
   
   %this.setBitmap(%path);

   return true;
}

/// Refreshes a menu input container, updating the buttons inside it
function MenuInputButtonContainer::refresh(%this)
{
   %count = %this.getCount();
   for(%i=0; %i < %count; %i++)
   {
      %btn = %this.getObject(%i);
      
      %btn.refresh();
   }
}

/// Sets the given MenuInputButtonContainer as the active one. This directs input events
/// to it's buttons, ensures it's visible, and auto-hides the old active container if it was set
function MenuInputButtonContainer::setActive(%this)
{
   if(isObject($activeMenuButtonContainer))
      $activeMenuButtonContainer.hidden = true;
      
   $activeMenuButtonContainer = %this;
   $activeMenuButtonContainer.hidden = false;
   $activeMenuButtonContainer.refresh();
}

/// Checks the input manager for if we have a gamepad active and gets it's name
/// If we have one, also sets the active input type to gamepad
function MenuInputButtonContainer::checkGamepad(%this)
{
   %controllerName = SDLInputManager::JoystickNameForIndex(0);
   
   $activeControllerName = %controllerName;
   
   if($activeControllerName $= "")
      $activeControllerType = "K&M";
   else
      $activeControllerType = "gamepad";     
}
   
/// This is called by the earlier inputs callback that comes from the menu list
/// this allows us to first check what the input type is, and if the device is different
/// (such as going from keyboard and mouse to gamepad) we can refresh the buttons to update
/// the display
/// Then we process the input to see if it matches to any of the button maps for our 
/// MenuInputButtons. If we have a match, we execute it's command.
function MenuInputButtonContainer::processInputs(%this, %device, %action)
{
   //check to see if our status has changed
   %changed = false;
   
   %oldDevice = $activeControllerName;
   
   %deviceName = stripTrailingNumber(%device);
   
   if(%deviceName $= "keyboard" || %deviceName $= "mouse")
   {
      if($activeControllerName !$= "K&M")
         %changed = true;
         
      $activeControllerName = "K&M";
      $activeControllerType = "K&M";
      Canvas.showCursor();
   }
   else
   {
      if(%this.checkGamepad())
      {
         Canvas.hideCursor();
      }
      
      if($activeControllerType !$= %oldDevice)
         %changed = true;
   }
   
   if(%changed)
      %this.refresh();
      
   //Now process the input for the button accelerator, if applicable
   //Set up our basic buttons
   for(%i=0; %i < %this.getCount(); %i++)
   {
      %btn = %this.getObject(%i);
      
      if(!%btn.isActive())
         continue;
      
      if($activeControllerType !$= "K&M")
      {
         if(%btn.gamepadButton $= %action)
         {
            eval(%btn.command);
         }
      }
      else
      {
         if(%btn.keyboardButton $= %action)
         {
            eval(%btn.command);
         }
      }
   }
}

/// This is called by the earlier inputs callback that comes from the menu list
/// this allows us to first check what the input type is, and if the device is different
/// (such as going from keyboard and mouse to gamepad) we can refresh the buttons to update
/// the display
function MenuInputButtonContainer::processAxisEvent(%this, %device, %action, %axisVal)
{
   //check to see if our status has changed
   %changed = false;
   
   %oldDevice = $activeControllerName;
   
   %deviceName = stripTrailingNumber(%device);
   
   if(%deviceName $= "mouse")
   {
      if($activeControllerName !$= "K&M")
         %changed = true;
         
      $activeControllerName = "K&M";
      $activeControllerType = "K&M";
      Canvas.showCursor();
   }
   else
   {
      if(%this.checkGamepad())
      {
         Canvas.hideCursor();
      }
      
      if($activeControllerType !$= %oldDevice)
         %changed = true;
   }
   
   if(%changed)
      %this.refresh();
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