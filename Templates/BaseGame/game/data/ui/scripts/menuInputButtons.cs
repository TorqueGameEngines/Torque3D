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

function UIMenuButtonList::onInputEvent(%this, %device, %action, %state)
{
   if(%state)
      $activeMenuButtonContainer.processInputs(%device, %action);
}

function UIMenuButtonList::onAxisEvent(%this, %device, %action, %axisVal)
{
   $activeMenuButtonContainer.processAxisEvent(%device, %action);
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

function MenuInputButton::refresh(%this)
{

   %set = (! ((%this.text $= "") && (%this.command $= "")));
   
   //Special-case of where we're in keyboard+mouse mode, but the menubutton is gamepad only mode, so we early out
   if(%this.gamepadOnly && $activeControllerName $= "K&M")
      %set = false;
      
   %this.setActive(%set);
   %this.setVisible(%set);
   
   if(!%this.isActive())
      return;
   
   if($activeControllerName !$= "K&M")
   {
      if(%this.gamepadButton !$= "")
      {
         %path = "";
         if($activeControllerName $= "PS4 Controller")
         { 
            %path = "data/ui/images/inputs/PS4/PS4_";
            
            if(%this.gamepadButton $= "A")
               %path = %path @ "Cross";
            else if(%this.gamepadButton $= "B")
               %path = %path @ "Circle";
            else if(%this.gamepadButton $= "X")
               %path = %path @ "Square";
            else if(%this.gamepadButton $= "Y")
               %path = %path @ "Triangle";
            else if(%this.gamepadButton $= "LB")
               %path = %path @ "L1";
            else if(%this.gamepadButton $= "LT")
               %path = %path @ "L2";
            else if(%this.gamepadButton $= "RB")
               %path = %path @ "R1";
            else if(%this.gamepadButton $= "RT")
               %path = %path @ "R2";
            //else      
            //   continue;
         }
         else if($activeControllerName $= "Nintendo Switch Pro Controller")
         {
            %path = "data/ui/images/inputs/Switch/Switch_";
            
            if(%this.gamepadButton $= "A")
               %path = %path @ "B";
            else if(%this.gamepadButton $= "B")
               %path = %path @ "A";
            else if(%this.gamepadButton $= "X")
               %path = %path @ "Y";
            else if(%this.gamepadButton $= "Y")
               %path = %path @ "X";
            else if(%this.gamepadButton $= "LB")
               %path = %path @ "LB";
            else if(%this.gamepadButton $= "LT")
               %path = %path @ "LT";
            else if(%this.gamepadButton $= "RB")
               %path = %path @ "RB";
            else if(%this.gamepadButton $= "RT")
               %path = %path @ "RT";
            //else      
            //   continue;
         }
         else if($activeControllerName !$= "")
         {
            %path = "data/ui/images/inputs/Xbox/Xbox_";
            
            %path = %path @ %this.gamepadButton;
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

function MenuInputButtonContainer::refresh(%this)
{
   %count = %this.getCount();
   for(%i=0; %i < %count; %i++)
   {
      %btn = %this.getObject(%i);
      
      %btn.refresh();
   }
}

function MenuInputButtonContainer::setActive(%this)
{
   if(isObject($activeMenuButtonContainer))
      $activeMenuButtonContainer.hidden = true;
      
   $activeMenuButtonContainer = %this;
   $activeMenuButtonContainer.hidden = false;
   $activeMenuButtonContainer.refresh();
}

function MenuInputButtonContainer::checkGamepad(%this)
{
   %controllerName = SDLInputManager::JoystickNameForIndex(0);
   
   $activeControllerName = %controllerName;
   
   if($activeControllerName $= "")
      $activeControllerName = "K&M";
}
   
function MenuInputButtonContainer::refreshButtons(%this)
{
   //Set up our basic buttons
   for(%i=0; %i < %this.getCount(); %i++)
   {
      %btn = %this.getObject(%i);
      
      %set = (! ((%btn.text $= "") && (%btn.command $= "")));
      
      //Special-case of where we're in keyboard+mouse mode, but the menubutton is gamepad only mode, so we early out
      if(%btn.gamepadOnly && $activeControllerName $= "K&M")
         %set = false;
         
      %btn.setActive(%set);
      %btn.setVisible(%set);
      
      if(!%btn.isActive())
         continue;
      
      if($activeControllerName !$= "K&M")
      {
         if(%btn.gamepadButton !$= "")
         {
            %path = "";
            if($activeControllerName $= "PS4 Controller")
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
            else if($activeControllerName $= "Nintendo Switch Pro Controller")
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
            else if($activeControllerName !$= "")
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

function MenuInputButtonContainer::processInputs(%this, %device, %action)
{
   //check to see if our status has changed
   %changed = false;
   
   %oldDevice = $activeControllerName;
   
   if(startsWith(%device, "Keyboard"))
   {
      if($activeControllerName !$= %device)
         %changed = true;
         
      $activeControllerName = "K&M";
      Canvas.showCursor();
   }
   else if(startsWith(%device, "Mouse"))
   {
      if(startsWith(%action, "button"))
      {
         if($activeControllerName !$= %device)
            %changed = true;
            
         $activeControllerName = "K&M";
         Canvas.showCursor();
      }
   }
   else
   {
      if(%this.checkGamepad())
      {
         Canvas.hideCursor();
      }
      
      if($activeControllerName !$= %device)
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
      
      if($activeControllerName !$= "K&M")
      {
         if(%action $= "btn_a")
            %action = "A";
         else if(%action $= "btn_b")
            %action = "B";
         else if(%action $= "btn_x")
            %action = "X";
         else if(%action $= "btn_y")
            %action = "Y";
         else if(%action $= "btn_r")
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

function MenuInputButtonContainer::processAxisEvent(%this, %device, %action, %axisVal)
{
   %changed = false;
   
   %oldDevice = $activeControllerName;
   
   if(startsWith(%device, "Mouse"))
   {
      if(startsWith(%action, "button"))
      {
         if($activeControllerName !$= %device)
            %changed = true;
            
         $activeControllerName = "K&M";
         Canvas.showCursor();
      }
   }
   else
   {
      if(%this.checkGamepad())
      {
         Canvas.hideCursor();
      }
      
      if($activeControllerName !$= %device)
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