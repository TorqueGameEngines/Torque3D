//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------
function escapeFromGame()
{
   disconnect();
}

$movementSpeed = 1; // m/s

function setSpeed(%speed)
{
   if(%speed)
      $movementSpeed = %speed;
}

function moveleft(%val)
{
   $mvLeftAction = %val * $movementSpeed;
}

function moveright(%val)
{
   $mvRightAction = %val * $movementSpeed;
}

function moveforward(%val)
{
   $mvForwardAction = %val * $movementSpeed;
}

function movebackward(%val)
{
   $mvBackwardAction = %val * $movementSpeed;
}

function moveup(%val)
{
   %object = ServerConnection.getControlObject();
   
   if(%object.isInNamespaceHierarchy("Camera"))
      $mvUpAction = %val * $movementSpeed;
}

function movedown(%val)
{
   %object = ServerConnection.getControlObject();
   
   if(%object.isInNamespaceHierarchy("Camera"))
      $mvDownAction = %val * $movementSpeed;
}

function turnLeft( %val )
{
   $mvYawRightSpeed = %val ? $Pref::Input::KeyboardTurnSpeed : 0;
}

function turnRight( %val )
{
   $mvYawLeftSpeed = %val ? $Pref::Input::KeyboardTurnSpeed : 0;
}

function panUp( %val )
{
   $mvPitchDownSpeed = %val ? $Pref::Input::KeyboardTurnSpeed : 0;
}

function panDown( %val )
{
   $mvPitchUpSpeed = %val ? $Pref::Input::KeyboardTurnSpeed : 0;
}

function getMouseAdjustAmount(%val)
{
   // based on a default camera FOV of 90'
   return(%val * ($cameraFov / 90) * 0.01) * $pref::Input::LinkMouseSensitivity;
}

function getGamepadAdjustAmount(%val)
{
   // based on a default camera FOV of 90'
   return(%val * ($cameraFov / 90) * 0.01) * 10.0;
}

function yaw(%val)
{
   %yawAdj = getMouseAdjustAmount(%val);
   if(ServerConnection.isControlObjectRotDampedCamera())
   {
      // Clamp and scale
      %yawAdj = mClamp(%yawAdj, -m2Pi()+0.01, m2Pi()-0.01);
      %yawAdj *= 0.5;
   }

   $mvYaw += %yawAdj;
}

function pitch(%val)
{
   %pitchAdj = getMouseAdjustAmount(%val);
   if(ServerConnection.isControlObjectRotDampedCamera())
   {
      // Clamp and scale
      %pitchAdj = mClamp(%pitchAdj, -m2Pi()+0.01, m2Pi()-0.01);
      %pitchAdj *= 0.5;
   }

   $mvPitch += %pitchAdj;
}

function jump(%val)
{
   $mvTriggerCount2++;
}

function gamePadMoveX( %val )
{
   if(%val > 0)
   {
      $mvRightAction = %val * $movementSpeed;
      $mvLeftAction = 0;
   }
   else
   {
      $mvRightAction = 0;
      $mvLeftAction = -%val * $movementSpeed;
   }
}

function gamePadMoveY( %val )
{
   if(%val > 0)
   {
      $mvForwardAction = %val * $movementSpeed;
      $mvBackwardAction = 0;
   }
   else
   {
      $mvForwardAction = 0;
      $mvBackwardAction = -%val * $movementSpeed;
   }
}

function gamepadYaw(%val)
{
   %yawAdj = getGamepadAdjustAmount(%val);
   if(ServerConnection.isControlObjectRotDampedCamera())
   {
      // Clamp and scale
      %yawAdj = mClamp(%yawAdj, -m2Pi()+0.01, m2Pi()-0.01);
      %yawAdj *= 0.5;
   }

   if(%yawAdj > 0)
   {
      $mvYawLeftSpeed = %yawAdj;
      $mvYawRightSpeed = 0;
   }
   else
   {
      $mvYawLeftSpeed = 0;
      $mvYawRightSpeed = -%yawAdj;
   }
}

function gamepadPitch(%val)
{
   %pitchAdj = getGamepadAdjustAmount(%val);
   if(ServerConnection.isControlObjectRotDampedCamera())
   {
      // Clamp and scale
      %pitchAdj = mClamp(%pitchAdj, -m2Pi()+0.01, m2Pi()-0.01);
      %pitchAdj *= 0.5;
   }

   if(%pitchAdj > 0)
   {
      $mvPitchDownSpeed = %pitchAdj;
      $mvPitchUpSpeed = 0;
   }
   else
   {
      $mvPitchDownSpeed = 0;
      $mvPitchUpSpeed = -%pitchAdj;
   }
}