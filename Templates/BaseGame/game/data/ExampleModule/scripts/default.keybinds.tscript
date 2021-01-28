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

$RemapName[$RemapCount] = "Forward";
$RemapCmd[$RemapCount] = "moveforward";
$RemapActionMap[$RemapCount] = "ExampleMoveMap";
$RemapDevice[$RemapCount] = "keyboard";
$RemapDescription[$RemapCount] = "Forward Movement";
$RemapCount++;
$RemapName[$RemapCount] = "Backward";
$RemapCmd[$RemapCount] = "movebackward";
$RemapActionMap[$RemapCount] = "ExampleMoveMap";
$RemapDevice[$RemapCount] = "keyboard";
$RemapDescription[$RemapCount] = "Backward Movement";
$RemapCount++;
$RemapName[$RemapCount] = "Strafe Left";
$RemapCmd[$RemapCount] = "moveleft";
$RemapActionMap[$RemapCount] = "ExampleMoveMap";
$RemapDevice[$RemapCount] = "keyboard";
$RemapDescription[$RemapCount] = "Left Strafing Movement";
$RemapCount++;
$RemapName[$RemapCount] = "Strafe Right";
$RemapCmd[$RemapCount] = "moveright";
$RemapActionMap[$RemapCount] = "ExampleMoveMap";
$RemapDevice[$RemapCount] = "keyboard";
$RemapDescription[$RemapCount] = "Right Strafing Movement";
$RemapCount++;
$RemapName[$RemapCount] = "Ascend";
$RemapCmd[$RemapCount] = "moveup";
$RemapActionMap[$RemapCount] = "ExampleMoveMap";
$RemapDevice[$RemapCount] = "keyboard";
$RemapDescription[$RemapCount] = "Makes the camera ascend";
$RemapCount++;
$RemapName[$RemapCount] = "Descend";
$RemapCmd[$RemapCount] = "movedown";
$RemapActionMap[$RemapCount] = "ExampleMoveMap";
$RemapDevice[$RemapCount] = "keyboard";
$RemapDescription[$RemapCount] = "Makes the camera descend";
$RemapCount++;
$RemapName[$RemapCount] = "Jump";
$RemapCmd[$RemapCount] = "jump";
$RemapActionMap[$RemapCount] = "ExampleMoveMap";
$RemapDevice[$RemapCount] = "keyboard";
$RemapDescription[$RemapCount] = "Jump";
$RemapCount++;

$RemapName[$RemapCount] = "Ascend";
$RemapCmd[$RemapCount] = "moveup";
$RemapActionMap[$RemapCount] = "ExampleMoveMap";
$RemapDevice[$RemapCount] = "gamepad";
$RemapDescription[$RemapCount] = "Makes the camera ascend";
$RemapCount++;
$RemapName[$RemapCount] = "Descend";
$RemapCmd[$RemapCount] = "movedown";
$RemapActionMap[$RemapCount] = "ExampleMoveMap";
$RemapDevice[$RemapCount] = "gamepad";
$RemapDescription[$RemapCount] = "Makes the camera descend";
$RemapCount++;
$RemapName[$RemapCount] = "Jump";
$RemapCmd[$RemapCount] = "jump";
$RemapActionMap[$RemapCount] = "ExampleMoveMap";
$RemapDevice[$RemapCount] = "gamepad";
$RemapDescription[$RemapCount] = "Jump";
$RemapCount++;

if ( isObject( ExampleMoveMap ) )
   ExampleMoveMap.delete();
   
new ActionMap(ExampleMoveMap);
ExampleMoveMap.humanReadableName = "Example Movement";

//------------------------------------------------------------------------------
// Non-remapable binds
//------------------------------------------------------------------------------
ExampleMoveMap.bind( keyboard, F2, showPlayerList );

ExampleMoveMap.bind(keyboard, "ctrl h", hideHUDs);

ExampleMoveMap.bind(keyboard, "alt p", doScreenShotHudless);

function openPauseMenu(%val)
{
   if(%val && PauseMenu.isAwake() == false)
   {
      echo("PUSHING PAUSE MENU");
      Canvas.pushDialog(PauseMenu);
   }
}

ExampleMoveMap.bind(keyboard, "escape", openPauseMenu);

//------------------------------------------------------------------------------
// Movement Keys
//------------------------------------------------------------------------------
ExampleMoveMap.bind( keyboard, a, moveleft );
ExampleMoveMap.bind( keyboard, d, moveright );
ExampleMoveMap.bind( keyboard, left, moveleft );
ExampleMoveMap.bind( keyboard, right, moveright );

ExampleMoveMap.bind( keyboard, w, moveforward );
ExampleMoveMap.bind( keyboard, s, movebackward );
ExampleMoveMap.bind( keyboard, up, moveforward );
ExampleMoveMap.bind( keyboard, down, movebackward );

ExampleMoveMap.bind( keyboard, e, moveup );
ExampleMoveMap.bind( keyboard, c, movedown );

ExampleMoveMap.bind( keyboard, space, jump );
ExampleMoveMap.bind( mouse, xaxis, yaw );
ExampleMoveMap.bind( mouse, yaxis, pitch );

ExampleMoveMap.bind( gamepad, rxaxis, "D", "-0.23 0.23", gamepadYaw );
ExampleMoveMap.bind( gamepad, ryaxis, "D", "-0.23 0.23", gamepadPitch );
ExampleMoveMap.bind( gamepad, xaxis, "D", "-0.23 0.23", gamePadMoveX );
ExampleMoveMap.bind( gamepad, yaxis, "D", "-0.23 0.23", gamePadMoveY );

ExampleMoveMap.bind( gamepad, btn_a, jump );
ExampleMoveMap.bind( gamepad, btn_x, moveup );
ExampleMoveMap.bind( gamepad, btn_y, movedown );
ExampleMoveMap.bindCmd( gamepad, btn_start, "Canvas.pushDialog(PauseMenu);", "" );

//------------------------------------------------------------------------------
// Misc.
//------------------------------------------------------------------------------
GlobalActionMap.bind(keyboard, "tilde", toggleConsole);
GlobalActionMap.bindCmd(keyboard, "alt k", "cls();","");
GlobalActionMap.bindCmd(keyboard, "alt enter", "", "Canvas.toggleFullscreen();");
GlobalActionMap.bindCmd(keyboard, "F1", "", "contextHelp();");
ExampleMoveMap.bindCmd(keyboard, "n", "toggleNetGraph();", "");