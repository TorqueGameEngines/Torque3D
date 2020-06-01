function getButtonBitmap(%device, %button)
{
   if(%device $= "gamepad")
   {
      //In the event we passed in a generic gamepad device name, we'll try fetching the actual device here
      %device = SDLInputManager::JoystickNameForIndex(0);
      
      //If we couldn't figure out what it was, just use the generic Xbox images
      if(%device $= "")
         %device = "Xbox";
   }
   
   %path = "";
   if(%device $= "PS4")
   { 
      %path = "data/ui/images/inputs/PS4/PS4_";
      
      if(%button $= "A" || %button $= "btn_a")
         %path = %path @ "Cross";
      else if(%button $= "B" || %button $= "btn_b")
         %path = %path @ "Circle";
      else if(%button $= "X" || %button $= "btn_x")
         %path = %path @ "Square";
      else if(%button $= "Y" || %button $= "btn_y")
         %path = %path @ "Triangle";
      else if(%button $= "LB")
         %path = %path @ "L1";
      else if(%button $= "LT")
         %path = %path @ "L2";
      else if(%button $= "RB")
         %path = %path @ "R1";
      else if(%button $= "RT")
         %path = %path @ "R2";
      else if(%button $= "thumbrx" || %button $= "thumbry")
         %path = %path @ "Right_Stick";
      else if(%button $= "thumblx" || %button $= "thumbly")
         %path = %path @ "Left_Stick";
      else if(%button $= "start")
         %path = %path @ "Options";
      else if(%button $= "back")
         %path = %path @ "Share";   
      else if(%button $= "dpadu")
         %path = %path @ "Dpad_Up";  
      else if(%button $= "dpadd")
         %path = %path @ "Dpad_Down";  
      else if(%button $= "dpadl")
         %path = %path @ "Dpad_Left";  
      else if(%button $= "dpadr")
         %path = %path @ "Dpad_Right";  
   }
   else if(%device $= "Switch")
   {
      %path = "data/ui/images/inputs/Switch/Switch_";
      
      if(%button $= "A" || %button $= "btn_a")
         %path = %path @ "B";
      else if(%button $= "B" || %button $= "btn_b")
         %path = %path @ "A";
      else if(%button $= "X" || %button $= "btn_x")
         %path = %path @ "Y";
      else if(%button $= "Y" || %button $= "btn_y")
         %path = %path @ "X";
      else if(%button $= "LB")
         %path = %path @ "LB";
      else if(%button $= "LT")
         %path = %path @ "LT";
      else if(%button $= "RB")
         %path = %path @ "RB";
      else if(%button $= "RT")
         %path = %path @ "RT";
      else if(%button $= "thumbrx" || %button $= "thumbry")
         %path = %path @ "Right_Stick";
      else if(%button $= "thumblx" || %button $= "thumbly")
         %path = %path @ "Left_Stick";
      else if(%button $= "start")
         %path = %path @ "Plus";
      else if(%button $= "back")
         %path = %path @ "Minus";   
      else if(%button $= "dpadu")
         %path = %path @ "Dpad_Up";  
      else if(%button $= "dpadd")
         %path = %path @ "Dpad_Down";  
      else if(%button $= "dpadl")
         %path = %path @ "Dpad_Left";  
      else if(%button $= "dpadr")
         %path = %path @ "Dpad_Right"; 
   }
   else if(%device $= "Keyboard" || %device $= "Mouse")
   {
      %pathBase = "data/ui/images/Inputs/Keyboard & Mouse/Keyboard_Black_";
      %path = %pathBase @ %button @ ".png";
      if(!isFile(%path))
         %path = %pathBase @ "Blank";
   }
   else if(%device !$= "")
   {
      %path = "data/ui/images/inputs/Xbox/Xbox_";
      
      if(%button $= "btn_a")
         %path = %path @ "B";
      else if(%button $= "btn_b")
         %path = %path @ "A";
      else if(%button $= "btn_x")
         %path = %path @ "Y";
      else if(%button $= "btn_y")
         %path = %path @ "X";
      else if(%button $= "thumbrx" || %button $= "thumbry")
         %path = %path @ "Right_Stick";
      else if(%button $= "thumblx" || %button $= "thumbly")
         %path = %path @ "Left_Stick";
      else if(%button $= "start")
         %path = %path @ "Menu";
      else if(%button $= "back")
         %path = %path @ "Windows";   
      else if(%button $= "dpadu")
         %path = %path @ "Dpad_Up";  
      else if(%button $= "dpadd")
         %path = %path @ "Dpad_Down";  
      else if(%button $= "dpadl")
         %path = %path @ "Dpad_Left";  
      else if(%button $= "dpadr")
         %path = %path @ "Dpad_Right"; 
   }
   
   return %path;
}