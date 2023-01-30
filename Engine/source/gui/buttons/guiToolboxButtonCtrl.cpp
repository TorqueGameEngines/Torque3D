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

#include "platform/platform.h"
#include "gui/buttons/guiToolboxButtonCtrl.h"

#include "console/console.h"
#include "console/engineAPI.h"
#include "gfx/gfxDevice.h"
#include "gfx/gfxDrawUtil.h"
#include "console/consoleTypes.h"
#include "gui/core/guiCanvas.h"
#include "gui/core/guiDefaultControlRender.h"


IMPLEMENT_CONOBJECT(GuiToolboxButtonCtrl);

ConsoleDocClass( GuiToolboxButtonCtrl,
   "@brief Unimplemented GUI control meant to interact with Toolbox.\n\n"
   "For Torque 3D editors only, soon to be deprecated\n\n"
   "@internal"
);

//-------------------------------------
GuiToolboxButtonCtrl::GuiToolboxButtonCtrl()
{
   INIT_ASSET(NormalBitmap);
   INIT_ASSET(LoweredBitmap);
   INIT_ASSET(HoverBitmap);

   setMinExtent(Point2I(16,16));
   setExtent(48, 48);
   mButtonType = ButtonTypeRadio;
   mTipHoverTime = 100;
   
}


//-------------------------------------
void GuiToolboxButtonCtrl::initPersistFields()
{
   docsURL;
   INITPERSISTFIELD_IMAGEASSET(NormalBitmap, GuiToolboxButtonCtrl, "");
   INITPERSISTFIELD_IMAGEASSET(LoweredBitmap, GuiToolboxButtonCtrl, "");
   INITPERSISTFIELD_IMAGEASSET(HoverBitmap, GuiToolboxButtonCtrl, "");

   Parent::initPersistFields();
}


//-------------------------------------
bool GuiToolboxButtonCtrl::onWake()
{
   if (! Parent::onWake())
      return false;

   setActive( true );
   
   setNormalBitmap( getNormalBitmap() );
   setLoweredBitmap( getLoweredBitmap() );
   setHoverBitmap( getHoverBitmap() );

   return true;
}


//-------------------------------------
void GuiToolboxButtonCtrl::onSleep()
{
   Parent::onSleep();
}

//-------------------------------------
void GuiToolboxButtonCtrl::inspectPostApply()
{
   // if the extent is set to (0,0) in the gui editor and appy hit, this control will
   // set it's extent to be exactly the size of the normal bitmap (if present)
   Parent::inspectPostApply();

   if ((getWidth() == 0) && (getHeight() == 0) && mNormalBitmap)
   {
      setExtent(mNormalBitmap->getWidth(), mNormalBitmap->getHeight());
   }
}


//-------------------------------------
void GuiToolboxButtonCtrl::setNormalBitmap( StringTableEntry bitmapName )
{
   _setNormalBitmap(bitmapName);
   
   if(!isAwake())
      return;
   
   setUpdate();
}   

void GuiToolboxButtonCtrl::setLoweredBitmap( StringTableEntry bitmapName )
{
   _setLoweredBitmap(bitmapName);
   
   if(!isAwake())
      return;
   
   setUpdate();
}   

void GuiToolboxButtonCtrl::setHoverBitmap( StringTableEntry bitmapName )
{
   _setHoverBitmap(bitmapName);

   if(!isAwake())
      return;

   setUpdate();
}   



//-------------------------------------
void GuiToolboxButtonCtrl::onRender(Point2I offset, const RectI& updateRect)
{
   // Only render the state rect (hover/down) if we're active
   if (mActive)
   {
      RectI r(offset, getExtent());
      if ( mDepressed  || mStateOn )
         renderStateRect( mLoweredBitmap , r );
      else if ( mHighlighted )
         renderStateRect( mHoverBitmap , r );
   }

   // Now render the image
   if( mNormalBitmap )
   {
      renderButton(mNormalBitmap, offset, updateRect );
      return;
   }

   Point2I textPos = offset;
   if( mDepressed )
      textPos += Point2I(1,1);

   // Make sure we take the profile's textOffset into account.
   textPos += mProfile->mTextOffset;

   GFX->getDrawUtil()->setBitmapModulation( mProfile->mFontColor );
   renderJustifiedText(textPos, getExtent(), mButtonText);

}

void GuiToolboxButtonCtrl::renderStateRect( GFXTexHandle &texture, const RectI& rect )
{
   if (texture)
   {
      GFX->getDrawUtil()->clearBitmapModulation();
      GFX->getDrawUtil()->drawBitmapStretch( texture, rect );
   }
}

//------------------------------------------------------------------------------

void GuiToolboxButtonCtrl::renderButton(GFXTexHandle &texture, Point2I &offset, const RectI& updateRect)
{
   if (texture)
   {
      Point2I finalOffset = offset;

      finalOffset.x += ( ( getWidth() / 2 ) - ( texture.getWidth() / 2 ) );
      finalOffset.y += ( ( getHeight() / 2 ) - ( texture.getHeight() / 2 ) );

      GFX->getDrawUtil()->clearBitmapModulation();
      GFX->getDrawUtil()->drawBitmap(texture, finalOffset);
      renderChildControls( offset, updateRect);
   }
}

DEF_ASSET_BINDS(GuiToolboxButtonCtrl, NormalBitmap);
DEF_ASSET_BINDS(GuiToolboxButtonCtrl, LoweredBitmap);
DEF_ASSET_BINDS(GuiToolboxButtonCtrl, HoverBitmap);
