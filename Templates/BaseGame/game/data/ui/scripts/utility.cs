function getButtonBitmap(%device, %button)
{
   %path = "";
   if(%device $= "PS4")
   { 
      %path = "data/ui/images/inputs/PS4/PS4_";
      
      if(%button $= "A")
         %path = %path @ "Cross";
      else if(%button $= "B")
         %path = %path @ "Circle";
      else if(%button $= "X")
         %path = %path @ "Square";
      else if(%button $= "Y")
         %path = %path @ "Triangle";
      else if(%button $= "LB")
         %path = %path @ "L1";
      else if(%button $= "LT")
         %path = %path @ "L2";
      else if(%button $= "RB")
         %path = %path @ "R1";
      else if(%button $= "RT")
         %path = %path @ "R2";
      else      
         continue;
   }
   else if(%device $= "Switch")
   {
      %path = "data/ui/images/inputs/Switch/Switch_";
      
      if(%button $= "A")
         %path = %path @ "B";
      else if(%button $= "B")
         %path = %path @ "A";
      else if(%button $= "X")
         %path = %path @ "Y";
      else if(%button $= "Y")
         %path = %path @ "X";
      else if(%button $= "LB")
         %path = %path @ "LB";
      else if(%button $= "LT")
         %path = %path @ "LT";
      else if(%button $= "RB")
         %path = %path @ "RB";
      else if(%button $= "RT")
         %path = %path @ "RT";
      else      
         continue;
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
      
      %path = %path @ %button;
   }
   
   return %path;
}