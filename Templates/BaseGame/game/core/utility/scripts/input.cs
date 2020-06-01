function getGamepadAdjustAmount(%val)
{
   // based on a default camera FOV of 90'
   return(%val * ($cameraFov / 90) * 0.01) * 10.0;
}

function getMouseAdjustAmount(%val)
{
   // based on a default camera FOV of 90'
   return(%val * ($cameraFov / 90) * 0.01) * $pref::Input::LinkMouseSensitivity;
}