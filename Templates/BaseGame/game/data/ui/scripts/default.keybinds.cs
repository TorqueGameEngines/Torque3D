$movementSpeed = 1; // m/s

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

moveMap.bind( keyboard, a, moveleft );
moveMap.bind( keyboard, d, moveright );
moveMap.bind( keyboard, w, moveforward );
moveMap.bind( keyboard, s, movebackward );

moveMap.bind( gamepad, thumbrx, "D", "-0.23 0.23", gamepadYaw );
moveMap.bind( gamepad, thumbry, "D", "-0.23 0.23", gamepadPitch );
moveMap.bind( gamepad, thumblx, "D", "-0.23 0.23", gamePadMoveX );
moveMap.bind( gamepad, thumbly, "D", "-0.23 0.23", gamePadMoveY );