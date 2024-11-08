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

#ifndef  _WINDOWMANAGER_WIN32_WIN32WINDOW_
#define  _WINDOWMANAGER_WIN32_WIN32WINDOW_

#include <windows.h>
#include "windowManager/platformWindowMgr.h"
#include "gfx/gfxTarget.h"
#include "gfx/gfxStructs.h"
#include "sim/actionMap.h"

class Win32WindowManager;
class GFXGLDevice;

/// Implementation of a window on Win32.
class Win32Window : public PlatformWindow
{
   friend class Win32WindowManager;
   friend class GFXGLDevice;

public:
   struct Accelerator
   {
      U32 mID;
      EventDescriptor mDescriptor;
   };
   typedef Vector<Accelerator> AcceleratorList;

private:
   typedef Vector<ACCEL> WinAccelList;

   /// @name Active window list
   ///
   /// Items used to track window instances.
   ///
   /// @{

   /// Which manager created us?
   Win32WindowManager *mOwningManager;

   /// Which window comes next in list?
   Win32Window *mNextWindow;
   
   /// @}

   /// @name Window Information
   ///
   /// @{

   /// Our HWND - Win32 window handle.
   HWND mWindowHandle;

   /// Our former Parent HWND
   HWND mOldParent;

   /// The Win32 window style we want to use when windowed.
   DWORD mWindowedWindowStyle;

   /// The GFX device that we're tied to.
   GFXDevice *mDevice;

   /// Reference to the render target allocated on this window.
   GFXWindowTargetRef mTarget;

   /// Our current size/resolution/fullscreen status.
   GFXVideoMode mVideoMode;

   /// Our position on the desktop.
   Point2I mPosition;

   /// Windows HACCEL for accelerators
   HACCEL mAccelHandle;

   /// Keyboard accelerators for menus
   WinAccelList mWinAccelList;

   /// Is the mouse locked to this window?
   bool mMouseLocked;

   /// The position the cursor was at when a mouse lock occured
   Point2I mMouseLockPosition;

   /// Determines whether this window should lock the mouse when it has an opportunity
   bool mShouldLockMouse;

   /// When set, we don't trigger device resets due to sizing events.
   bool mSuppressReset;

   /// Menu associated with this window.  This is a passive property of the window and is not required to be used at all.
   HMENU mMenuHandle;

   /// Do we have a fullscreen window style set?
   bool                 mFullscreen;

   /// @}

   /// Helper to allocate our Win32 window class.
   void _registerWindowClass();
   void _unregisterWindowClass();

   /// Windows message handler callback.
   static LRESULT PASCAL WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

   /// Add an accelerator to the list of accelerators for this window. Intended for use by addAccelerators()
   void addAccelerator(Accelerator &accel);
   /// Remove an accelerator from the list of accelerators for this window. Intended for use by removeAccelerators()
   void removeAccelerator(Accelerator &accel);

public:
   Win32Window();
   ~Win32Window();

   /// Return the HWND (win32 window handle) for this window.
   HWND &getHWND()
   {
      return mWindowHandle;
   }

   void* getSystemWindow(const WindowSystem system) override;

   HMENU &getMenuHandle()
   {
      return mMenuHandle;
   }

   void setMenuHandle( HMENU menuHandle ) 
   {
      mMenuHandle = menuHandle;
      if(!mFullscreen)
         SetMenu(mWindowHandle, mMenuHandle);
   }

   /// Add a list of accelerators to this window
   void addAccelerators(AcceleratorList &list);
   /// Remove a list of accelerators from this window
   void removeAccelerators(AcceleratorList &list);

   /// Returns true if @p info matches an accelerator
   bool isAccelerator(const InputEventInfo &info);

   /// Allow windows to translate messages. Used for accelerators.
   bool translateMessage(MSG &msg);

   GFXDevice *getGFXDevice() override;
   GFXWindowTarget *getGFXTarget() override;
   
   void _setVideoMode(const GFXVideoMode &mode) override;
   const GFXVideoMode &getVideoMode() override;
   bool clearFullscreen() override;
   bool isFullscreen() override;
   void _setFullscreen(const bool fullscreen) override;
   
   bool setCaption(const char *cap) override;
   const char *getCaption() override;
   
   // Window Client Area Extent
   void setClientExtent( const Point2I newExtent ) override;
   const Point2I getClientExtent() override;
  
   // Window Bounds
   void setBounds(const RectI &newBounds) override;
   const RectI getBounds() const override;

   // Window Position
   void setPosition( const Point2I newPosition ) override;
   const Point2I getPosition() override;
   void centerWindow() override;
   bool setSize(const Point2I &newSize) override;
   
   // Coordinate space conversion.
   Point2I clientToScreen( const Point2I& pos ) override;
   Point2I screenToClient( const Point2I& pos ) override;

   bool isOpen() override;
   bool isVisible() override;
   bool isFocused() override;
   bool isMinimized() override;
   bool isMaximized() override;

   void minimize() override;
   void maximize() override;
   void hide() override;
   void show() override;
   void close() override;
   void restore() override;
   void setFocus() override;

   void setMouseLocked(bool enable) override;
   bool isMouseLocked() const override { return mMouseLocked; };
   bool shouldLockMouse() const override { return mShouldLockMouse; };

   WindowId getWindowId() override;

   PlatformWindow * getNextWindow() const override
   {
      return mNextWindow;
   }

   /// Provide a simple GDI-based render for when the game is not rendering.
   virtual void defaultRender();

   /// Return the class name for the windows we create with this class.
   static const UTF16 *getWindowClassName();

   /// Return the class name for the curtain window class.
   static const UTF16 *getCurtainWindowClassName();

   /// Return the platform specific object needed to create or attach an
   /// accelerated graohics drawing context on or to the window
   void* getPlatformDrawable() const override { return mWindowHandle; }
};
#endif
