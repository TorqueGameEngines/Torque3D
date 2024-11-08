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

#ifndef  _WINDOWMANAGER_SDL_WINDOW_
#define  _WINDOWMANAGER_SDL_WINDOW_

#include "windowManager/platformWindowMgr.h"
#include "gfx/gfxTarget.h"
#include "gfx/gfxStructs.h"
#include "sim/actionMap.h"

class PlatformWindowManagerSDL;
struct SDL_Window;
union SDL_Event;

/// Implementation of a window on SDL.
class PlatformWindowSDL : public PlatformWindow
{
   friend class PlatformWindowManagerSDL;

private:

   /// @name Active window list
   ///
   /// Items used to track window instances.
   ///
   /// @{

   /// Which manager created us?
   PlatformWindowManagerSDL *mOwningManager;

   /// Which window comes next in list?
   PlatformWindowSDL *mNextWindow;
   
   /// @}

   /// @name Window Information
   ///
   /// @{

   /// Our SDL window.
   SDL_Window *mWindowHandle;

   /// Our former Parent
   SDL_Window *mOldParent;   

   /// The GFX device that we're tied to.
   GFXDevice *mDevice;

   /// Reference to the render target allocated on this window.
   GFXWindowTargetRef mTarget;

   /// Our current size/resolution/fullscreen status.
   GFXVideoMode mVideoMode;

   /// Our position on the desktop.
   Point2I mPosition;

   /// Is the mouse locked to this window?
   bool mMouseLocked;

   /// Determines whether this window should lock the mouse when it has an opportunity
   bool mShouldLockMouse;

   /// When set, we don't trigger device resets due to sizing events.
   bool mSuppressReset;

   /// Menu associated with this window.  This is a passive property of the window and is not required to be used at all.
   void* mMenuHandle;

   /// Indicates if the window is being closed. This allows us to safely ignore other events like focus being gained or losed after cleanup has begun
   bool mClosing;

   /// @}

   void _processSDLEvent(SDL_Event &evt);
   void _triggerMouseLocationNotify(const SDL_Event& evt);
   void _triggerMouseButtonNotify(const SDL_Event& event);
   void _triggerMouseWheelNotify(const SDL_Event& event);
   void _triggerKeyNotify(const SDL_Event& event);
   void _triggerTextNotify(const SDL_Event& event);
   void _updateMonitorFromMove(const SDL_Event& event);

public:
   PlatformWindowSDL();
   ~PlatformWindowSDL();

   void* getSystemWindow(const WindowSystem system) override;

   void* &getMenuHandle()
   {
      return mMenuHandle;
   }

   void setMenuHandle( void* menuHandle ) 
   {
      mMenuHandle = menuHandle;
   }   

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

   /// Set if relevant keypress events should be translated into character input events.
   void setKeyboardTranslation(const bool enabled) override;

   WindowId getWindowId() override;

   SDL_Window* getSDLWindow() const { return mWindowHandle; }

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
