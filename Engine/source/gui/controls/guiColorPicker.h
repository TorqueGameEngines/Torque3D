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
#ifndef _GUICOLORPICKER_H_
#define _GUICOLORPICKER_H_

#ifndef _GUICONTROL_H_
#include "gui/core/guiControl.h"
#endif

//----------------------------
/// GuiColorPickerCtrl
///
/// This control draws a box containing a color specified by mPickColor, 
/// in a way according to one of the PickMode enum's, stored as mDisplayMode.
/// 
/// The color the box represents is stored as mBaseColour (for pPalette, pBlendColorRange), 
/// whilst the color chosen by the box is stored as mPickColor.
///
/// Whenever the control is clicked, it will do one of many things :
///
/// -# If its in pPalette mode, execute the regular "command"
/// -# If its in pBlendRange mode, update the selector position. The position will be re-read upon the next render. In addition, a cross will be drawn where the color has been selected from. As with 1, "command" will be executed.
/// -# If its in pHueRange or pAlphaRange mode, it will function in a similar manner to 2, but the selector will resemble a horizontal or vertical bar.
/// -# If its in pAlphaRange mode, it will also function the same way as 3
/// -# If its in pDropperBackground mode, nothing will happen
///
/// Colours are drawn in different ways according to mDisplayMode:
///
/// -# With pPalette, a box with a blank color, mBaseColor is drawn.
/// -# With pHueRange, a box containing the hue range 0-360.
/// -# With pAlphaRange, a box containing the alpha range 0-255.
/// -# With pDropperBackground, nothing is drawn
class GuiColorPickerCtrl : public GuiControl
{
   typedef GuiControl Parent;
   
  public:
   enum PickMode
   {
     pPalette = 0,                ///< We just have a solid color; We just act like a pallet
     pBlendRange,                ///< The full range of brightness and saturation.
     pHueRange,                  ///< The full hue range 0-360.
     pAlphaRange,                ///< The full alpha range 0-255.
     pDropperBackground          ///< The control does not draw anything; Only does something when you click, or move the mouse (when active)
   };
   
   enum SelectorMode
   {
     sHorizontal = 0,            ///< Horizontal selector with small gap
     sVertical,                  ///< Vertical selector with small gap
   };

  protected:

   /// <summary>
   /// Render the hue gradient for pBlendRange mode.
   /// </summary>
   /// <param name="bounds">The bounds of the ctrl.</param>
   void renderBlendRange(RectI& bounds);

   /// <summary>
   /// Render the selector for pBlendRange mode.
   /// </summary>
   /// <param name="bounds">The bounds of the ctrl.</param>
   void renderBlendSelector(RectI& bounds);

   /// <summary>
   /// Render the hue gradient for pHueRange mode.
   /// </summary>
   /// <param name="bounds">The bounds of the ctrl.</param>
   /// <param name="numColours">The number of splits in the gradient. 7 as default.</param>
   void renderHueGradient(RectI& bounds, U32 numColours);

   /// <summary>
   /// Render the selector for pHueRange mode.
   /// </summary>
   /// <param name="bounds">The bounds of the ctrl.</param>
   void renderHueSelector(RectI& bounds);

   /// <summary>
   /// Render the alpha gradient for pAlphaRange mode.
   /// </summary>
   /// <param name="bounds">The bounds of the ctrl.</param>
   void renderAlphaGradient(RectI& bounds);

   /// <summary>
   /// Render the selector for pAlphaRange mode.
   /// </summary>
   /// <param name="bounds">The bounds of the ctrl.</param>
   void renderAlphaSelector(RectI& bounds);

   void renderEyeDropper();

   /// @name Core Variables
   /// @{
   PickMode mDisplayMode;	      ///< Current color display mode of the selector
   SelectorMode mSelectorMode;	///< Current color display mode of the selector
   U32 mSelectedHue;
   U32 mSelectedSaturation;
   U32 mSelectedBrightness;
   U32 mSelectedAlpha;
   Point2I eyeDropperPos;
   GBitmap* eyeDropperCap;
   GFXTexHandle eyeHandle;

   bool mDropperActive;       ///< Is the eye dropper active?
   bool mMouseOver;		      ///< Mouse is over?
   bool mMouseDown;		      ///< Mouse button down?
   bool mActionOnMove;		   ///< Perform onAction() when position has changed?
   bool mShowReticle;         ///< Show reticle on render

   S32   mSelectorGap;		   ///< The half-way "gap" between the selector pos and where the selector is allowed to draw. 

   GFXStateBlockRef mStateBlock;
   /// @}

  public:

   DECLARE_CONOBJECT(GuiColorPickerCtrl);
   DECLARE_CATEGORY( "Gui Editor" );
   
   GuiColorPickerCtrl();
   ~GuiColorPickerCtrl();

   static void initPersistFields();
   void onRender(Point2I offset, const RectI &updateRect) override;
   
   /// @}

   /// @name Input Events
   /// @{
   void onMouseDown(const GuiEvent &) override;
   void onMouseUp(const GuiEvent &) override;
   void onMouseMove(const GuiEvent &event) override;
   void onMouseDragged(const GuiEvent &event) override;

   void onMouseEnter(const GuiEvent &) override;
   void onMouseLeave(const GuiEvent &) override;
   /// @}

   // script getters and setters
   /// <summary>
   /// Set the selected hue.
   /// </summary>
   /// <param name="hueValue">Hue value, 0 - 360.</param>
   void setSelectedHue(const U32& hueValue);
   U32 getSelectedHue() { return mSelectedHue; }

   /// <summary>
   /// Set the selected brightness.
   /// </summary>
   /// <param name="brightValue">Brightness value, 0 - 100.</param>
   void setSelectedBrightness(const U32& brightValue);
   U32 getSelectedBrightness() { return mSelectedBrightness; }

   /// <summary>
   /// Set the selected saturation.
   /// </summary>
   /// <param name="satValue">Saturation value, 0 - 100.</param>
   void setSelectedSaturation(const U32& satValue);
   U32 getSelectedSaturation() { return mSelectedSaturation; }

   /// <summary>
   /// Set the selected alpha.
   /// </summary>
   /// <param name="alphaValue">Alpha value, 0 - 255.</param>
   void setSelectedAlpha(const U32& alphaValue);
   U32 getSelectedAlpha() { return mSelectedAlpha; }

   void activateEyeDropper();

};

typedef GuiColorPickerCtrl::PickMode GuiColorPickMode;
typedef GuiColorPickerCtrl::SelectorMode GuiColorSelectorMode;
DefineEnumType( GuiColorPickMode );
DefineEnumType(GuiColorSelectorMode);

#endif
