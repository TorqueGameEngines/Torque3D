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
#include "console/console.h"
#include "gfx/gfxDevice.h"
#include "console/consoleTypes.h"
#include "console/engineAPI.h"
#include "gui/core/guiCanvas.h"
#include "gui/buttons/guiButtonCtrl.h"
#include "gui/core/guiDefaultControlRender.h"
#include "gui/controls/guiColorPicker.h"
#include "gfx/primBuilder.h"
#include "gfx/gfxDrawUtil.h"
#include "console/typeValidators.h"
#include "postFx/postEffectManager.h"
#include "gfx/screenshot.h"

IMPLEMENT_CONOBJECT(GuiColorPickerCtrl);

ConsoleDocClass( GuiColorPickerCtrl,
   "@brief Editor GUI used for picking a LinearColorF from a palette.\n\n"
   "@note Editor use only.\n\n"
   "@internal"
);

GuiColorPickerCtrl::GuiColorPickerCtrl()
{
   setExtent(140, 30);
   mDisplayMode = pPalette;
   mSelectorMode = sHorizontal;
   mMouseDown = mMouseOver = false;
   mActive = true;
   mSelectorGap = 1;
   mActionOnMove = false;
   mDropperActive = false;
   mShowReticle = true;
   mSelectedHue = 0;
   mSelectedAlpha = 255;
   mSelectedSaturation = 100;
   mSelectedBrightness = 100;
   eyeDropperPos = Point2I::Zero;
   eyeDropperCap = NULL;
}

GuiColorPickerCtrl::~GuiColorPickerCtrl()
{
   if (eyeDropperCap != NULL)
   {
      delete eyeDropperCap;
      eyeDropperCap = NULL;
   }
}

ImplementEnumType( GuiColorPickMode,
   "\n\n"
   "@ingroup GuiUtil"
   "@internal" )
   { GuiColorPickerCtrl::pPalette,            "Pallete" },
   { GuiColorPickerCtrl::pBlendRange,        "BlendRange" },
   { GuiColorPickerCtrl::pHueRange,          "HueRange"},
   { GuiColorPickerCtrl::pAlphaRange,        "AlphaRange" },
   { GuiColorPickerCtrl::pDropperBackground, "Dropper" },
EndImplementEnumType;

ImplementEnumType(GuiColorSelectorMode,
   "\n\n"
   "@ingroup GuiUtil"
   "@internal")
{ GuiColorPickerCtrl::sHorizontal,  "Horizontal" },
{ GuiColorPickerCtrl::sVertical,    "Vertical" },
EndImplementEnumType;

void GuiColorPickerCtrl::initPersistFields()
{
   docsURL;
   addGroup("ColorPicker");
      addFieldV("selectorGap", TypeRangedS32,  Offset(mSelectorGap, GuiColorPickerCtrl),&CommonValidators::NaturalNumber);
      addField("displayMode", TYPEID< PickMode >(), Offset(mDisplayMode, GuiColorPickerCtrl) );
      addField("selectorMode", TYPEID< SelectorMode >(), Offset(mSelectorMode, GuiColorPickerCtrl) );
      addField("actionOnMove", TypeBool,Offset(mActionOnMove, GuiColorPickerCtrl));
      addField("showReticle", TypeBool, Offset(mShowReticle, GuiColorPickerCtrl));
   endGroup("ColorPicker");

   Parent::initPersistFields();
}

void GuiColorPickerCtrl::renderBlendRange(RectI& bounds)
{
   ColorI currentColor;
   currentColor.set(Hsb(mSelectedHue, 100, 100));
   GFX->getDrawUtil()->drawRectFill(bounds, currentColor, 0.0f, ColorI(0,0,0,0), true);
}

void GuiColorPickerCtrl::renderBlendSelector(RectI& bounds)
{
   // Determine the relative saturation position within the gradient
   F32 relPosX = F32(mSelectedSaturation) / 100.0f;
   // Determine the relative brightness position within the gradient
   F32 relPosY = 1.0f - F32(mSelectedBrightness) / 100.0f;

   // Calculate the selector position
   Point2I selectorPos;
   RectI selectorRect;

   selectorPos.x = bounds.point.x + static_cast<S32>(relPosX * bounds.extent.x);
   selectorPos.y = bounds.point.y + static_cast<S32>(relPosY * bounds.extent.y);
   selectorRect.set(Point2I(selectorPos.x - mSelectorGap, selectorPos.y - mSelectorGap), Point2I(mSelectorGap * 2, mSelectorGap * 2));

   ColorI currentColor;
   currentColor.set(Hsb(mSelectedHue, mSelectedSaturation, mSelectedBrightness));
   GFX->getDrawUtil()->drawRectFill(selectorRect, currentColor, 2.0f, ColorI::WHITE);
}

void GuiColorPickerCtrl::renderHueGradient(RectI& bounds, U32 numColours)
{
   GFX->setStateBlock(mStateBlock);

   F32 stepSize = F32(bounds.extent.x) / F32(numColours); // For horizontal mode
   F32 stepSizeY = F32(bounds.extent.y) / F32(numColours); // For vertical mode
   S32 l = bounds.point.x, r = bounds.point.x + bounds.extent.x;
   S32 t = bounds.point.y, b = bounds.point.y + bounds.extent.y;

   // Begin primitive building, 4 vertices per rectangle
   PrimBuild::begin(GFXTriangleStrip, numColours * 4);

   for (U32 i = 0; i < numColours; i++)
   {
      U32 currentHue = static_cast<U32>((F32(i) / F32(numColours)) * 360.0f);
      U32 nextHue = static_cast<U32>((F32(i + 1) / F32(numColours)) * 360.0f);

      ColorI currentColor, nextColor;
      currentColor.set(Hsb(currentHue, 100, 100));
      nextColor.set(Hsb(nextHue, 100, 100));

      switch (mSelectorMode)
      {
      case GuiColorPickerCtrl::sHorizontal:
      {
         // Draw a rectangle for the current segment
         F32 xStart = l + i * stepSize;
         F32 xEnd = l + (i + 1) * stepSize;

         PrimBuild::color(currentColor);
         PrimBuild::vertex2i(xStart, t); // Top-left

         PrimBuild::color(nextColor);
         PrimBuild::vertex2i(xEnd, t); // Top-right

         PrimBuild::color(currentColor);
         PrimBuild::vertex2i(xStart, b); // Bottom-left

         PrimBuild::color(nextColor);
         PrimBuild::vertex2i(xEnd, b); // Bottom-right

         break;
      }
      case GuiColorPickerCtrl::sVertical:
      {
         // Draw a rectangle for the current segment
         F32 yStart = t + i * stepSizeY;
         F32 yEnd = t + (i + 1) * stepSizeY;

         PrimBuild::color(currentColor);
         PrimBuild::vertex2i(l, yStart); // Top-left

         PrimBuild::color(currentColor);
         PrimBuild::vertex2i(r, yStart); // Top-right

         PrimBuild::color(nextColor);
         PrimBuild::vertex2i(l, yEnd); // Bottom-left

         PrimBuild::color(nextColor);
         PrimBuild::vertex2i(r, yEnd); // Bottom-right

         break;
      }
      default:
         break;
      }
   }

   PrimBuild::end();
}

void GuiColorPickerCtrl::renderHueSelector(RectI& bounds)
{
   // Determine the relative position within the gradient
   F32 relPos = F32(mSelectedHue) / 360.0f;

   // Calculate the selector position
   Point2I selectorPos;
   RectI selectorRect;
   switch (mSelectorMode)
   {
   case GuiColorPickerCtrl::sHorizontal:
      // X is proportional to the hue, Y is centered vertically
      selectorPos.x = bounds.point.x + static_cast<S32>(relPos * bounds.extent.x);
      selectorPos.y = bounds.point.y;
      selectorRect.set(Point2I(selectorPos.x - mSelectorGap, selectorPos.y), Point2I(mSelectorGap * 2, bounds.extent.y));
      break;

   case GuiColorPickerCtrl::sVertical:
      // Y is proportional to the hue, X is centered horizontally
      selectorPos.x = bounds.point.x;
      selectorPos.y = bounds.point.y + static_cast<S32>(relPos * bounds.extent.y);
      selectorRect.set(Point2I(selectorPos.x, selectorPos.y - mSelectorGap), Point2I(bounds.extent.x, mSelectorGap * 2));
      break;
   default:
      return; // Invalid mode, don't render selector
   }

   ColorI currentColor;
   currentColor.set(Hsb(mSelectedHue, 100, 100));
   GFX->getDrawUtil()->drawRectFill(selectorRect, currentColor, 2.0f, ColorI::WHITE);
}

void GuiColorPickerCtrl::renderAlphaGradient(RectI& bounds)
{
   GFX->setStateBlock(mStateBlock);

   // Define the rectangle bounds
   S32 l = bounds.point.x;
   S32 r = bounds.point.x + bounds.extent.x;
   S32 t = bounds.point.y;
   S32 b = bounds.point.y + bounds.extent.y;

   ColorI currentColor;
   currentColor.set(Hsb(mSelectedHue, 100, 100));

   ColorI alphaCol = ColorI::BLACK;
   alphaCol.alpha = 0;

   // Begin primitive building, 4 vertices per rectangle
   PrimBuild::begin(GFXTriangleStrip,4);

   switch (mSelectorMode)
   {
   case GuiColorPickerCtrl::sHorizontal:
   {
      PrimBuild::color(alphaCol);
      PrimBuild::vertex2i(l, t); // Top-left

      PrimBuild::color(currentColor);
      PrimBuild::vertex2i(r, t); // Top-right

      PrimBuild::color(alphaCol);
      PrimBuild::vertex2i(l, b); // Bottom-left

      PrimBuild::color(currentColor);
      PrimBuild::vertex2i(r, b); // Bottom-right
      break;
   }
   case GuiColorPickerCtrl::sVertical:
   {
      PrimBuild::color(currentColor);
      PrimBuild::vertex2i(l, t); // Top-left

      PrimBuild::color(currentColor);
      PrimBuild::vertex2i(r, t); // Top-right

      PrimBuild::color(alphaCol);
      PrimBuild::vertex2i(l, b); // Bottom-left

      PrimBuild::color(alphaCol);
      PrimBuild::vertex2i(r, b); // Bottom-right
      break;
   }
   default:
      break;
   }

   PrimBuild::end();

}

void GuiColorPickerCtrl::renderAlphaSelector(RectI& bounds)
{
   // Determine the relative position within the gradient
   F32 relPos = F32(mSelectedAlpha) / 255.0f;

   // Calculate the selector position
   Point2I selectorPos;
   RectI selectorRect;
   switch (mSelectorMode)
   {
   case GuiColorPickerCtrl::sHorizontal:
      // X is proportional to the hue, Y is centered vertically
      selectorPos.x = bounds.point.x + static_cast<S32>(relPos * bounds.extent.x);
      selectorPos.y = bounds.point.y;
      selectorRect.set(Point2I(selectorPos.x - mSelectorGap, selectorPos.y), Point2I(mSelectorGap * 2, bounds.extent.y));
      break;

   case GuiColorPickerCtrl::sVertical:
      // Y is proportional to the hue, X is centered horizontally
      selectorPos.x = bounds.point.x;
      selectorPos.y = bounds.point.y + static_cast<S32>(relPos * bounds.extent.y);
      selectorRect.set(Point2I(selectorPos.x, selectorPos.y - mSelectorGap), Point2I(bounds.extent.x, mSelectorGap * 2));
      break;
   default:
      return; // Invalid mode, don't render selector
   }

   ColorI currentColor;
   currentColor.set(Hsb(mSelectedHue, 100, 100));
   currentColor.alpha = mSelectedAlpha;

   GFX->getDrawUtil()->drawRectFill(selectorRect, currentColor, 2.0f, ColorI::WHITE);
}

void GuiColorPickerCtrl::renderEyeDropper()
{
   if (eyeDropperCap != NULL)
   {
      GFX->getDrawUtil()->drawBitmap(eyeHandle, getRoot()->getPosition());

      Point2I resolution = getRoot()->getExtent();
      Point2I magnifierSize(100, 100);
      Point2I magnifierPosition = eyeDropperPos + Point2I(20, 20);

      // Adjust position to ensure magnifier stays on screen
      if (magnifierPosition.x + magnifierSize.x > resolution.x)
         magnifierPosition.x = eyeDropperPos.x - magnifierSize.x - 20;
      if (magnifierPosition.y + magnifierSize.y > resolution.y)
         magnifierPosition.y = eyeDropperPos.y - magnifierSize.y - 20;

      RectI magnifierBounds(magnifierPosition, magnifierSize);

      ColorI currentColor;
      currentColor.set(Hsb(mSelectedHue, mSelectedSaturation, mSelectedBrightness));
      currentColor.alpha = mSelectedAlpha;

      GFX->getDrawUtil()->drawRectFill(magnifierBounds, currentColor, 2.0f, ColorI::BLACK);
   }
}

void GuiColorPickerCtrl::onRender(Point2I offset, const RectI& updateRect)
{
   if (mStateBlock.isNull())
   {
      GFXStateBlockDesc desc;
      desc.setBlend(true, GFXBlendSrcAlpha, GFXBlendInvSrcAlpha);
      desc.setZReadWrite(false);
      desc.zWriteEnable = false;
      desc.setCullMode(GFXCullNone);
      mStateBlock = GFX->createStateBlock(desc);
   }

   RectI boundsRect(offset, getExtent());

   switch (mDisplayMode)
   {
   case GuiColorPickerCtrl::pPalette:
   {
      ColorI currentColor;
      currentColor.set(Hsb(mSelectedHue, mSelectedSaturation, mSelectedBrightness));
      currentColor.alpha = mSelectedAlpha;
      GFX->getDrawUtil()->drawRectFill(boundsRect, currentColor);
      break;
   }
   case GuiColorPickerCtrl::pBlendRange:
   {
      renderBlendRange(boundsRect);
      renderBlendSelector(boundsRect);
      break;
   }
   case GuiColorPickerCtrl::pHueRange:
   {
      renderHueGradient(boundsRect, 7);
      if(mShowReticle) renderHueSelector(boundsRect);
      break;
   }
   case GuiColorPickerCtrl::pAlphaRange:
   {
      renderAlphaGradient(boundsRect);
      if (mShowReticle) renderAlphaSelector(boundsRect);
      break;
   }
   case GuiColorPickerCtrl::pDropperBackground:
   {
      if (mDropperActive)
      {
         // Render the magnified view of our currently selected color.
         renderEyeDropper();
      }
      break;
   }
   default:
      break;
   }

   //render the children
   renderChildControls(offset, updateRect);
}

void GuiColorPickerCtrl::onMouseDown(const GuiEvent &event)
{
   if (!mActive)
      return;

   // we need to do this first.
   if (mDisplayMode == GuiColorPickerCtrl::pDropperBackground) {
      if (mDropperActive)
      {
         mDropperActive = false;

         //getRoot()->pushObjectToBack(this);

         onAction();
         mouseUnlock();

         if (eyeDropperCap != NULL)
         {
            delete eyeDropperCap;
            eyeDropperCap = NULL;
         }
      }

      return;
   }
   
   mouseLock(this);
   
   if (mProfile->mCanKeyFocus)
      setFirstResponder();

   Point2I ext = getExtent();
   Point2I mousePoint = globalToLocalCoord(event.mousePoint);
   mMouseDown = true;

   switch (mDisplayMode)
   {
   case GuiColorPickerCtrl::pPalette:
      return;
   case GuiColorPickerCtrl::pBlendRange:
   {
      F32 relX = F32(mousePoint.x) / F32(ext.x);
      F32 relY = 1.0f - F32(mousePoint.y) / F32(ext.y);
      setSelectedSaturation(relX * 100.0);
      setSelectedBrightness(relY * 100.0);
      break;
   }
   case GuiColorPickerCtrl::pHueRange:
   {
      switch (mSelectorMode)
      {
      case GuiColorPickerCtrl::sHorizontal:
      {
         F32 relX = F32(mousePoint.x) / F32(ext.x);
         setSelectedHue(relX * 360.0);
         break;
      }
      case GuiColorPickerCtrl::sVertical:
      {
         F32 relY = F32(mousePoint.y) / F32(ext.y);
         setSelectedHue(relY * 360.0);
         break;
      }
      default:
         break;
      }
      break;
   }
   case GuiColorPickerCtrl::pAlphaRange:
   {
      switch (mSelectorMode)
      {
      case GuiColorPickerCtrl::sHorizontal:
      {
         F32 relX = F32(mousePoint.x) / F32(ext.x);
         setSelectedAlpha(relX * 255.0);
         break;
      }
      case GuiColorPickerCtrl::sVertical:
      {
         F32 relY = F32(mousePoint.y) / F32(ext.y);
         setSelectedAlpha(relY * 255.0);
         break;
      }
      default:
         break;
      }
      break;
   }
   default:
      break;
   }

   if (mActive)
      onAction();
}

//--------------------------------------------------------------------------
void GuiColorPickerCtrl::onMouseDragged(const GuiEvent &event)
{
   if ((mActive && mMouseDown))
   {
      Point2I ext = getExtent();
      Point2I mousePoint = globalToLocalCoord(event.mousePoint);

      F32 relX = mClampF(F32(mousePoint.x) / F32(ext.x), 0.0, 1.0);
      F32 relY = mClampF(F32(mousePoint.y) / F32(ext.y), 0.0, 1.0);
      switch (mDisplayMode)
      {
      case GuiColorPickerCtrl::pPalette:
         return;
      case GuiColorPickerCtrl::pBlendRange:
      {
         relY = 1.0f - relY;
         setSelectedSaturation(relX * 100.0);
         setSelectedBrightness(relY * 100.0);
         break;
      }
      case GuiColorPickerCtrl::pHueRange:
      {
         switch (mSelectorMode)
         {
         case GuiColorPickerCtrl::sHorizontal:
         {
            setSelectedHue(relX * 360.0);
            break;
         }
         case GuiColorPickerCtrl::sVertical:
         {
            setSelectedHue(relY * 360.0);
            break;
         }
         default:
            break;
         }
         break;
      }
      case GuiColorPickerCtrl::pAlphaRange:
      {
         switch (mSelectorMode)
         {
         case GuiColorPickerCtrl::sHorizontal:
         {
            setSelectedAlpha(relX * 255.0);
            break;
         }
         case GuiColorPickerCtrl::sVertical:
         {
            setSelectedAlpha(relY * 255.0);
            break;
         }
         default:
            break;
         }
         break;
      }
      default:
         break;
      }

      onAction();
   }
}

void GuiColorPickerCtrl::onMouseMove(const GuiEvent &event)
{
   if (mDisplayMode != pDropperBackground)
      return;

   if (!mDropperActive)
      return;

   // should not need globalToLocal as we are capturing the whole screen.
   eyeDropperPos = globalToLocalCoord(event.mousePoint);

   if (eyeDropperCap != NULL)
   {
      // Sample the pixel color at the mouse position. Mouse position should translate directly.
      ColorI sampledColor;
      eyeDropperCap->getColor(eyeDropperPos.x, eyeDropperPos.y, sampledColor);

      // Convert the sampled color to HSB
      Hsb hsb = sampledColor.getHSB();
      mSelectedHue = hsb.hue;
      mSelectedSaturation = hsb.sat;
      mSelectedBrightness = hsb.brightness;
      mSelectedAlpha = sampledColor.alpha;
   }

}

void GuiColorPickerCtrl::onMouseEnter(const GuiEvent &event)
{
   mMouseOver = true;
}

void GuiColorPickerCtrl::onMouseLeave(const GuiEvent &)
{
   // Reset state
   mMouseOver = false;
}

void GuiColorPickerCtrl::onMouseUp(const GuiEvent&)
{
   //if we released the mouse within this control, perform the action
   if (mActive && mMouseDown)
      mMouseDown = false;

   mouseUnlock();
}

void GuiColorPickerCtrl::setSelectedHue(const U32& hueValue)
{
   if (hueValue < 0)
   {
      mSelectedHue = 0;
      return;
   }

   if (hueValue > 360)
   {
      mSelectedHue = 360;
      return;
   }

   mSelectedHue = hueValue;
   
}

void GuiColorPickerCtrl::setSelectedBrightness(const U32& brightValue)
{
   if (brightValue < 0)
   {
      mSelectedBrightness = 0;
      return;
   }

   if (brightValue > 100)
   {
      mSelectedBrightness = 100;
      return;
   }

   mSelectedBrightness = brightValue;
}

void GuiColorPickerCtrl::setSelectedSaturation(const U32& satValue)
{
   if (satValue < 0)
   {
      mSelectedSaturation = 0;
      return;
   }

   if (satValue > 100)
   {
      mSelectedSaturation = 100;
      return;
   }

   mSelectedSaturation = satValue;
}

void GuiColorPickerCtrl::setSelectedAlpha(const U32& alphaValue)
{
   if (alphaValue < 0)
   {
      mSelectedAlpha = 0;
      return;
   }

   if (alphaValue > 255)
   {
      mSelectedAlpha = 255;
      return;
   }

   mSelectedAlpha = alphaValue;
}

void GuiColorPickerCtrl::activateEyeDropper()
{
   // Make sure we are a pDropperBackground
   if (mDisplayMode == GuiColorPickerCtrl::pDropperBackground)
   {
      mouseLock(this); // take over!

      setFirstResponder(); // we need this to be first responder regardless.

      //getRoot()->bringObjectToFront(this);

      mDropperActive = true;

      // Set up our resolution.
      Point2I resolution = getRoot()->getExtent();

      eyeDropperCap = gScreenShot->_captureBackBuffer();

      // Texture handle to resolve the target to.
      eyeHandle.set(eyeDropperCap, &GFXStaticTextureSRGBProfile, false, avar("%s() - bb (line %d)", __FUNCTION__, __LINE__));
   }
}

/// <summary>
/// This command is to be used by Palette only as it updates everything else across the colour picker gui.
/// </summary>
DefineEngineMethod(GuiColorPickerCtrl, executeUpdate, void, (), , "Execute the onAction command.")
{
   object->onAction();
}

/// <summary>
/// This command should only be used with guiColorPicker in pDropperBackground mode.
/// </summary>
DefineEngineMethod(GuiColorPickerCtrl, activateEyeDropper, void, (), , "Activate the dropper mode.")
{
   object->activateEyeDropper();
}

DefineEngineMethod(GuiColorPickerCtrl, setSelectedHue, void, (S32 hueValue), , "Sets the selected hue value should be 0-360.")
{
   object->setSelectedHue(hueValue);
}

DefineEngineMethod(GuiColorPickerCtrl, getSelectedHue, S32, (), , "Gets the current selected hue value.")
{
   return object->getSelectedHue();
}

DefineEngineMethod(GuiColorPickerCtrl, setSelectedBrightness, void, (S32 brightness), , "Sets the selected brightness value should be 0-100.")
{
   object->setSelectedBrightness(brightness);
}

DefineEngineMethod(GuiColorPickerCtrl, getSelectedBrightness, S32, (), , "Gets the current selected brightness.")
{
   return object->getSelectedBrightness();
}

DefineEngineMethod(GuiColorPickerCtrl, setSelectedSaturation, void, (S32 saturation), , "Sets the selected saturation value should be 0-100.")
{
   object->setSelectedSaturation(saturation);
}

DefineEngineMethod(GuiColorPickerCtrl, getSelectedSaturation, S32, (), , "Gets the current selected saturation value.")
{
   return object->getSelectedSaturation();
}

DefineEngineMethod(GuiColorPickerCtrl, setSelectedAlpha, void, (S32 alpha), , "Sets the selected alpha value should be 0-255.")
{
   object->setSelectedAlpha(alpha);
}

DefineEngineMethod(GuiColorPickerCtrl, getSelectedAlpha, S32, (), , "Gets the current selected alpha value.")
{
   return object->getSelectedAlpha();
}

DefineEngineMethod(GuiColorPickerCtrl, setSelectedColorI, void, (ColorI col), , "Sets the current selected hsb from a colorI value.")
{
   Hsb hsb(col.getHSB());
   object->setSelectedHue(hsb.hue);
   object->setSelectedSaturation(hsb.sat);
   object->setSelectedBrightness(hsb.brightness);
   object->setSelectedAlpha(col.alpha);
}

DefineEngineMethod(GuiColorPickerCtrl, getSelectedColorI, ColorI, (), , "Gets the current selected hsb as a colorI value.")
{
   ColorI col;
   col.set(Hsb(object->getSelectedHue(), object->getSelectedSaturation(), object->getSelectedBrightness()));
   col.alpha = object->getSelectedAlpha();
   return col;
}

DefineEngineMethod(GuiColorPickerCtrl, setSelectedLinearColor, void, (LinearColorF colF), , "Sets the current selected hsb froma a LinearColorF value.")
{
   Hsb hsb = colF.getHSB();
   object->setSelectedHue(hsb.hue);
   object->setSelectedSaturation(hsb.sat);
   object->setSelectedBrightness(hsb.brightness);
   object->setSelectedAlpha(colF.alpha * 255.0);
}


DefineEngineMethod(GuiColorPickerCtrl, getSelectedLinearColor, LinearColorF, (), , "Gets the current selected hsb as a LinearColorF value.")
{
   LinearColorF col;
   col.set(Hsb(object->getSelectedHue(), object->getSelectedSaturation(), object->getSelectedBrightness()));
   col.alpha = (F32)object->getSelectedAlpha() / 255.0f;
   return col;
}
