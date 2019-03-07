//-----------------------------------------------------------------------------
// Verve
// Copyright (C) 2014 - Violent Tulip
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
#include "Verve/GUI/VEditorWindow.h"
#include "gfx/gfxInit.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT( VEditorWindow );
//-----------------------------------------------------------------------------

bool VEditorWindow::onAdd( void )
{
    if ( !Parent::onAdd() )
    {
        return false;
    }

    GFXAdapter *adapter = GFXInit::getBestAdapterChoice();
    if ( adapter && adapter->mType != NullDevice )
    {
        mPlatformWindow->setMinimumWindowSize( Point2I( 904, 287 ) );
    }

    return true;
}

//-----------------------------------------------------------------------------

DefineEngineMethod( VEditorWindow, resetCursor, void, (),, "( )" )
{
    S32 currCursor = PlatformCursorController::curArrow;
    if ( object->mCursorChanged == currCursor )
    {
        return;
    }

    PlatformWindow *window = object->getPlatformWindow();
    PlatformCursorController *controller = window->getCursorController();

    if( object->mCursorChanged != -1)
    {
        controller->popCursor();
    }

    controller->pushCursor(currCursor);
    object->mCursorChanged = currCursor;   

    Platform::setWindowLocked( false );
}

DefineEngineMethod( VEditorWindow, setVideoMode, void, (S32 width, S32 height, bool fullscreen, S32 bitDepth, S32 refreshRate, S32 antiAliasLevel),
               (800,600,false,32,60, 0),
               "(int width, int height, bool fullscreen, [int bitDepth], [int refreshRate])\n"
               "Change the video mode of this canvas. This method has the side effect of setting the $pref::Video::mode to the new values.\n\n"
               "\\param width The screen width to set.\n"
               "\\param height The screen height to set.\n"
               "\\param fullscreen Specify true to run fullscreen or false to run in a window\n"
               "\\param bitDepth [optional] The desired bit-depth. Defaults to the current setting. This parameter is ignored if you are running in a window.\n"
               "\\param refreshRate [optional] The desired refresh rate. Defaults to the current setting. This parameter is ignored if you are running in a window"
                    "\\param antialiasLevel [optional] The level of anti-aliasing to apply 0 = none" )
{
   if (!object->getPlatformWindow())
      return;

   // Update the video mode and tell the window to reset.
   GFXVideoMode vm = object->getPlatformWindow()->getVideoMode();

   bool changed = false;
   if (width == 0 && height > 0)
   {
      // Our width is 0 but our height isn't...
      // Try to find a matching width
      for(S32 i=0; i<object->getPlatformWindow()->getGFXDevice()->getVideoModeList()->size(); i++)
      {
         const GFXVideoMode &newVm = (*(object->getPlatformWindow()->getGFXDevice()->getVideoModeList()))[i];

         if(newVm.resolution.y == height)
         {
            width = newVm.resolution.x;
            changed = true;
            break;
         }
      }
   }
   else if (height == 0 && width > 0)
   {
      // Our height is 0 but our width isn't...
      // Try to find a matching height
      for(S32 i=0; i<object->getPlatformWindow()->getGFXDevice()->getVideoModeList()->size(); i++)
      {
         const GFXVideoMode &newVm = (*(object->getPlatformWindow()->getGFXDevice()->getVideoModeList()))[i];

         if(newVm.resolution.x == width)
         {
            height = newVm.resolution.y;
            changed = true;
            break;
         }
      }
   }

   if (width == 0 || height == 0)
   {
      // Got a bad size for both of our dimensions or one of our dimensions and
      // didn't get a match for the other default back to our current resolution
      width  = vm.resolution.x;
      height = vm.resolution.y;

      changed = true;
   }

   if (changed)
      Con::errorf("GuiCanvas::setVideoMode(): Error - Invalid resolution of (%d, %d) - attempting (%d, %d)", width, height, width, height);

   vm.resolution  = Point2I(width, height);
   vm.fullScreen  = fullscreen;

   vm.bitDepth = bitDepth;
   vm.refreshRate = refreshRate;

   vm.antialiasLevel = antiAliasLevel;

#ifndef TORQUE_OS_XENON
   object->getPlatformWindow()->setVideoMode(vm);
#endif
}
