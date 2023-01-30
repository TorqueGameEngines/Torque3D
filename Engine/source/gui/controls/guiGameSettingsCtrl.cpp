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

#include "guiGameSettingsCtrl.h"

#include "console/consoleTypes.h"
#include "console/engineAPI.h"
#include "gfx/gfxDrawUtil.h"
#include "gui/containers/guiScrollCtrl.h"
#include "core/strings/stringUnit.h"
#include "gui/core/guiDefaultControlRender.h"

//-----------------------------------------------------------------------------
// GuiGameSettingsCtrl
//-----------------------------------------------------------------------------

GuiGameSettingsCtrl::GuiGameSettingsCtrl() :
   mLabel(StringTable->EmptyString()),
   mScriptCallback(StringTable->EmptyString()),
   mTooltip(StringTable->EmptyString()),
   mEnabled(true),
   mSelected(false),
   mSelectedOption(0),
   mWrapOptions(false),
   mMode(Mode::Default),
   mValue(0),
   mStepSize(1),
   mRange(Point2F(0, 1)),
   mCallbackOnInputs(false),
   mConsumeKeyInputEvents(false),
   mArrowSize(30),
   mColumnSplit(250),
   mRightPad(20)
{
   VECTOR_SET_ASSOCIATION(mOptions);

   // initialize the control callbacks
   mCallbackOnA = StringTable->EmptyString();
   mCallbackOnB = mCallbackOnA;
   mCallbackOnX = mCallbackOnA;
   mCallbackOnY = mCallbackOnA;

   INIT_ASSET(KeybindBitmap);
   INIT_ASSET(PreviousBitmap);
   INIT_ASSET(NextBitmap);
}

GuiGameSettingsCtrl::~GuiGameSettingsCtrl()
{
   mOptions.clear();
}

void GuiGameSettingsCtrl::onMouseMove(const GuiEvent& event)
{
   //check if we're inside an arrow/slider/etc and kick a highlight action
   Parent::onMouseMove(event);
}

void GuiGameSettingsCtrl::onMouseUp(const GuiEvent& event)
{
   Parent::onMouseUp(event);

   if (isEnabled())
   {
      if (mMode == Mode::Default)
      {
         activate();
      }
      else if (mMode == Mode::OptionList)
      {
         S32 xPos = globalToLocalCoord(event.mousePoint).x;
         clickOption(xPos);
      }
      else if (mMode == Mode::Slider)
      {
         S32 xPos = globalToLocalCoord(event.mousePoint).x;
         clickSlider(xPos);
      }
      else if (mMode == Mode::Keybind)
      {
         S32 xPos = globalToLocalCoord(event.mousePoint).x;
         clickKeybind(xPos);
      }
   }
}

void GuiGameSettingsCtrl::onRender(Point2I offset, const RectI &updateRect)
{
   GFXDrawUtil* drawUtil = GFX->getDrawUtil();

   F32 xScale = (float) getWidth();

   S32 height = getHeight();

   Point2I currentOffset = offset;
   Point2I extent = getExtent();
   Point2I textOffset(mProfile->mTextOffset.x * xScale, mProfile->mTextOffset.y);
   Point2I textExtent(mColumnSplit, height);
   Point2I iconExtent, iconOffset(0.0f, 0.0f);

   bool highlight = mHighlighted;
   bool depressed = mDepressed;

   ColorI fontColor = mActive ? (highlight ? mProfile->mFontColorHL : mProfile->mFontColor) : mProfile->mFontColorNA;
   ColorI fillColor = mActive ? (highlight ? mProfile->mFillColorHL : mProfile->mFillColor) : mProfile->mFillColorNA;
   ColorI borderColor = mActive ? (highlight ? mProfile->mBorderColorHL : mProfile->mBorderColor) : mProfile->mBorderColorNA;

   RectI boundsRect(offset, getExtent());

   if (!mHasTheme)
   {
      if (mProfile->mBorder != 0)
         renderFilledBorder(boundsRect, borderColor, fillColor, mProfile->mBorderThickness);
      else
         GFX->getDrawUtil()->drawRectFill(boundsRect, fillColor);
   }
   else
   {
      S32 indexMultiplier = 1;

      if (!mActive)
         indexMultiplier = 4;
      else if (mDepressed || mStateOn)
         indexMultiplier = 2;
      else if (mHighlighted)
         indexMultiplier = 3;

      renderSizableBitmapBordersFilled(boundsRect, indexMultiplier, mProfile);
   }

   // render the text
   drawUtil->setBitmapModulation(fontColor);
   renderJustifiedText(currentOffset + textOffset, textExtent, mLabel);

   if (mMode == Mode::OptionList)
   {
      onRenderListOption(currentOffset);
   }
   else if (mMode == Mode::Slider)
   {
      onRenderSliderOption(currentOffset);
   }
   else if (mMode == Mode::Keybind)
   {
      onRenderKeybindOption(currentOffset);
   }

   renderChildControls(offset, updateRect);
}

void GuiGameSettingsCtrl::onRenderListOption(Point2I currentOffset)
{
   F32 xScale = (float)getWidth();

   S32 height = getHeight();

   GFXDrawUtil* drawer = GFX->getDrawUtil();

   Point2I arrowOffset;

   S32 arrowOffsetY = 0;

   bool hasOptions = (mOptions.size() > 0) && mSelectedOption > -1;
   if (hasOptions)
   {
      if (mPreviousBitmapAsset.notNull())
      {
         // render the left arrow
         bool arrowOnL = (isSelected() || isHighlighted()) && (mWrapOptions || (mSelectedOption > 0));
         arrowOffset.x = currentOffset.x + mColumnSplit;
         arrowOffset.y = currentOffset.y + arrowOffsetY;

         drawer->clearBitmapModulation();
         drawer->drawBitmapStretch(mPreviousBitmap, RectI(arrowOffset, Point2I(mArrowSize, mArrowSize)), GFXBitmapFlip_None, GFXTextureFilterLinear, false);
      }
      else
      {
         // render the left arrow
         bool arrowOnL = (isSelected() || isHighlighted()) && (mWrapOptions || (mSelectedOption > 0));
         arrowOffset.x = currentOffset.x + mColumnSplit;
         arrowOffset.y = currentOffset.y + height/2;

         drawer->clearBitmapModulation();

         drawer->drawLine(arrowOffset, Point2I(arrowOffset.x + mArrowSize, currentOffset.y), ColorI::WHITE);
         drawer->drawLine(arrowOffset, Point2I(arrowOffset.x + mArrowSize, currentOffset.y + height), ColorI::WHITE);
      }

      if (mNextBitmapAsset.notNull())
      {
         // render the right arrow
         bool arrowOnR = (isSelected() || isHighlighted()) && (mWrapOptions || (mSelectedOption < mOptions.size() - 1));
         arrowOffset.x = currentOffset.x + getWidth() - mRightPad - mArrowSize;
         arrowOffset.y = currentOffset.y + arrowOffsetY;

         drawer->clearBitmapModulation();
         drawer->drawBitmapStretch(mNextBitmap, RectI(arrowOffset, Point2I(mArrowSize, mArrowSize)), GFXBitmapFlip_None, GFXTextureFilterLinear, false);
      }
      else
      {
         // render the left arrow
         bool arrowOnL = (isSelected() || isHighlighted()) && (mWrapOptions || (mSelectedOption > 0));
         arrowOffset.x = currentOffset.x + getWidth() - mRightPad;
         arrowOffset.y = currentOffset.y + height / 2;

         drawer->clearBitmapModulation();

         drawer->drawLine(arrowOffset, Point2I(arrowOffset.x - mArrowSize, currentOffset.y), ColorI::WHITE);
         drawer->drawLine(arrowOffset, Point2I(arrowOffset.x - mArrowSize, currentOffset.y + height), ColorI::WHITE);
      }

      // get the appropriate font color
      ColorI fontColor;
      if (!mEnabled)
      {
         fontColor = mProfile->mFontColorNA;
      }
      else if (isSelected())
      {
         fontColor = mProfile->mFontColorSEL;
      }
      else if (isHighlighted())
      {
         fontColor = mProfile->mFontColorHL;
      }
      else
      {
         fontColor = mProfile->mFontColor;
      }

      // calculate text to be at the center between the arrows
      GFont* font = mProfile->mFont;
      StringTableEntry text = mOptions[mSelectedOption].mDisplayText;
      S32 textWidth = font->getStrWidth(text);
      S32 columnWidth = xScale - mRightPad - mColumnSplit;
      S32 columnCenter = mColumnSplit + (columnWidth >> 1);
      S32 textStartX = columnCenter - (textWidth >> 1);
      Point2I textOffset(textStartX, 0);

      // render the option text itself
      Point2I textExtent(columnWidth, height);
      drawer->setBitmapModulation(fontColor);
      renderJustifiedText(currentOffset + Point2I(mColumnSplit, 0), textExtent, text);
   }
}

void GuiGameSettingsCtrl::onRenderSliderOption(Point2I currentOffset)
{
   F32 xScale = (float)getWidth();

   S32 height = getHeight();

   S32 arrowOffsetY = 0;

   GFXDrawUtil* drawer = GFX->getDrawUtil();

   Point2I arrowOffset;
   S32 columnSplit = mColumnSplit;

   

   /*if (mPreviousBitmapAsset.notNull())
   {
      // render the left arrow
      bool arrowOnL = (isSelected() || isHighlighted()) && (mWrapOptions || (mSelectedOption > 0));
      arrowOffset.x = currentOffset.x + columnSplit;
      arrowOffset.y = currentOffset.y + arrowOffsetY;

      drawer->clearBitmapModulation();
      drawer->drawBitmapStretch(mPreviousBitmap, RectI(arrowOffset, Point2I(mArrowSize, mArrowSize)), GFXBitmapFlip_None, GFXTextureFilterLinear, false);
   }
   else
   {
      // render the left arrow
      bool arrowOnL = (isSelected() || isHighlighted()) && (mWrapOptions || (mSelectedOption > 0));
      arrowOffset.x = currentOffset.x + mColumnSplit;
      arrowOffset.y = currentOffset.y + height / 2;

      drawer->clearBitmapModulation();

      drawer->drawLine(arrowOffset, Point2I(arrowOffset.x + mArrowSize, currentOffset.y), ColorI::WHITE);
      drawer->drawLine(arrowOffset, Point2I(arrowOffset.x + mArrowSize, currentOffset.y + height), ColorI::WHITE);
   }

   if (mNextBitmapAsset.notNull())
   {
      // render the right arrow
      bool arrowOnR = (isSelected() || isHighlighted()) && (mWrapOptions || (mSelectedOption < mOptions.size() - 1));
      arrowOffset.x = currentOffset.x + mRightPad * xScale - mArrowSize;
      arrowOffset.y = currentOffset.y + arrowOffsetY;

      drawer->clearBitmapModulation();
      drawer->drawBitmapStretch(mNextBitmap, RectI(arrowOffset, Point2I(mArrowSize, mArrowSize)), GFXBitmapFlip_None, GFXTextureFilterLinear, false);
   }
   else
   {
      // render the left arrow
      bool arrowOnL = (isSelected() || isHighlighted()) && (mWrapOptions || (mSelectedOption > 0));
      arrowOffset.x = currentOffset.x + getWidth() - mRightPad;
      arrowOffset.y = currentOffset.y + height / 2;

      drawer->clearBitmapModulation();

      drawer->drawLine(arrowOffset, Point2I(arrowOffset.x - mArrowSize, currentOffset.y), ColorI::WHITE);
      drawer->drawLine(arrowOffset, Point2I(arrowOffset.x - mArrowSize, currentOffset.y + height), ColorI::WHITE);
   }*/

   //Draw the slider bar

   RectI sliderRect;

   S32 sliderOffset = 5;

   RectI optionRect;

   sliderRect.point.x = currentOffset.x + columnSplit + mArrowSize;
   sliderRect.point.y = currentOffset.y + sliderOffset;

   sliderRect.extent.x = (currentOffset.x + getWidth() - mRightPad - mArrowSize) - sliderRect.point.x;
   sliderRect.extent.y = height - sliderOffset*2;

   optionRect = sliderRect;

   S32 textWidth = sliderRect.extent.x * 0.3;
   sliderRect.extent.x -= textWidth;

   //Now adjust the bar to match-to our value

   S32 barStart = sliderRect.point.x;
   S32 barEnd = sliderRect.point.x + sliderRect.extent.x;

   S32 xPosFill = (((mValue - mRange.x) * (barEnd - barStart)) / (mRange.y - mRange.x)) + barStart;

   RectI fillRect = sliderRect;
   fillRect.extent.x = xPosFill - sliderRect.point.x;

   ColorI barColor;
   ColorI barOutlineColor;
   if (isSelected())
   {
      barColor = mProfile->mFontColor;
      barOutlineColor = mProfile->mFontColorSEL;
   }
   else
   {
      barColor = mProfile->mFontColor;
      barOutlineColor = mProfile->mFontColorHL;
   }

   drawer->drawRectFill(fillRect, barColor);

   drawer->drawRect(sliderRect, barOutlineColor);

   // get the appropriate font color
   ColorI fontColor;
   if (!mEnabled)
   {
      fontColor = mProfile->mFontColorNA;
   }
   else if (isSelected())
   {
      fontColor = mProfile->mFontColorSEL;
   }
   else if (isHighlighted())
   {
      fontColor = mProfile->mFontColorHL;
   }
   else
   {
      fontColor = mProfile->mFontColor;
   }

   // calculate text to be at the center between the arrows
   GFont* font = mProfile->mFont;

   char stringVal[32];
   dSprintf(stringVal, 32, "%.1f", mValue);

   S32 stringWidth = font->getStrWidth(stringVal);
   Point2I textOffset(sliderRect.point.x + sliderRect.extent.x, 0);

   // render the option text itself
   Point2I textExtent(textWidth, height);

   RectI textRect = optionRect;
   textRect.point.x = sliderRect.point.x + sliderRect.extent.x;
   textRect.extent.x = optionRect.extent.x * 0.3;

   drawer->setBitmapModulation(fontColor);
   renderJustifiedText(textRect.point, textRect.extent, stringVal);

   //drawer->drawRectFill(textRect, ColorI::RED);
}

void GuiGameSettingsCtrl::onRenderKeybindOption(Point2I currentOffset)
{
   F32 xScale = (float)getWidth();
   S32 columnSplit = mColumnSplit;

   S32 height = getHeight();

   GFXDrawUtil* drawer = GFX->getDrawUtil();
   //drawer->drawBitmap(mBitmap, )

   Point2I button;
   button.x = currentOffset.x + columnSplit + (columnSplit / 2.5)/* + (optionWidth / 2)*/;
   button.y = currentOffset.y;

   Point2I buttonSize;
   buttonSize.x = height;
   buttonSize.y = height;

   if (mKeybindBitmapAsset.notNull())
   {
      RectI rect(button, buttonSize);
      drawer->clearBitmapModulation();
      drawer->drawBitmapStretch(mKeybindBitmap, rect, GFXBitmapFlip_None, GFXTextureFilterLinear, false);
   }

   //drawer->drawRectFill(button, ColorI::BLUE);
}

void GuiGameSettingsCtrl::set(const char* label, const char* callback, bool useHighlightIcon, bool enabled, S32 mode, const char* tooltip)
{
   mScriptCallback = (dStrlen(callback) > 0) ? StringTable->insert(callback, true) : NULL;
   mEnabled = enabled;
   mMode = (Mode)mode;
   mTooltip = StringTable->insert(tooltip);
   mLabel = StringTable->insert(label, true);
}

void GuiGameSettingsCtrl::setListSetting(const char* label, const char* optionsList, bool wrapOptions, const char* callback, bool enabled, const char* tooltip, const char* defaultValue)
{
   static StringTableEntry DELIM = StringTable->insert("\t", true);

   Vector<OptionEntry> options(__FILE__, __LINE__);

   S32 defaultOption = 0;

   S32 count = StringUnit::getUnitCount(optionsList, DELIM);
   for (S32 i = 0; i < count; ++i)
   {
      OptionEntry e;
      const char* option = StringUnit::getUnit(optionsList, i, DELIM);
      e.mDisplayText = StringTable->insert(option, true);
      e.mKeyString = e.mDisplayText;
      options.push_back(e);

      if (String::compare(option, defaultValue) == 0)
         defaultOption = options.size() - 1;
   }
   mOptions = options;
   bool hasOptions = mOptions.size() > 0;
   mSelectedOption = (hasOptions) ? defaultOption : NO_OPTION;
   mWrapOptions = wrapOptions;
   set(label, callback, true, (hasOptions) ? enabled : false, Mode::OptionList, tooltip);
}

void GuiGameSettingsCtrl::setSliderSetting(const char* label, F32 defaultValue, F32 increments, Point2F range, const char* callback, bool enabled, const char* tooltip)
{
   static StringTableEntry DELIM = StringTable->insert("\t", true);

   mValue = defaultValue;
   mStepSize = increments;
   mRange = range;

   set(label, callback, true, enabled, Mode::Slider, tooltip);
}

void GuiGameSettingsCtrl::setKeybindSetting(const char* label, const char* bitmapName, const char* callback, bool enabled, const char* tooltip)
{
   static StringTableEntry DELIM = StringTable->insert("\t", true);

   _setKeybindBitmap(StringTable->insert(bitmapName));

   //if(mBitmap != StringTable->EmptyString())
   //   mBitmapTex.set(mBitmap, &GFXDefaultGUIProfile, avar("%s() - mTextureObject (line %d)", __FUNCTION__, __LINE__));

   set(label, callback, true, enabled, Mode::Keybind, tooltip);
}

bool GuiGameSettingsCtrl::onAdd()
{
   if( !Parent::onAdd() )
      return false;
      
   return true;
}

bool GuiGameSettingsCtrl::onWake()
{
   if( !Parent::onWake() )
      return false;

   _setNextBitmap(getNextBitmap());
   _setPreviousBitmap(getPreviousBitmap());
   _setKeybindBitmap(getKeybindBitmap());

   return true;
}

void GuiGameSettingsCtrl::onSleep()
{
   if (mNextBitmapAsset.notNull())
      mNextBitmap = NULL;
   if (mPreviousBitmapAsset.notNull())
      mPreviousBitmap = NULL;
   if (mKeybindBitmapAsset.notNull())
      mKeybindBitmap = NULL;

   Parent::onSleep();
}

void GuiGameSettingsCtrl::activate()
{
   if(isSelected() && isEnabled() && (mScriptCallback != StringTable->EmptyString()))
   {
      setThisControl();
      if (Con::isFunction(mScriptCallback))
      {
         Con::executef(mScriptCallback);
      }
   }
}

void GuiGameSettingsCtrl::setSelected()
{
   if (!isEnabled())
      return;

   mSelected = true;
}

bool GuiGameSettingsCtrl::isEnabled() const
{
   return mEnabled;
}

void GuiGameSettingsCtrl::setEnabled(bool enabled)
{
   mEnabled = enabled;
}

void GuiGameSettingsCtrl::doScriptCommand(StringTableEntry command)
{
   if (command && command[0])
   {
      setThisControl();
      Con::evaluate(command, false, __FILE__);
   }
}

void GuiGameSettingsCtrl::setThisControl()
{
   smThisControl = this;
}

StringTableEntry GuiGameSettingsCtrl::getLabel() const
{
   return mLabel;
}

void GuiGameSettingsCtrl::setLabel( const char * label)
{
   mLabel = StringTable->insert(label, true);
}

void GuiGameSettingsCtrl::clear()
{
   mOptions.clear();
}

//-----------------------------------------------------------------------------
// Console stuff (GuiGameSettingsCtrl)
//-----------------------------------------------------------------------------

StringTableEntry GuiGameSettingsCtrl::getCurrentOption() const
{
   if (mSelectedOption != NO_OPTION && !mOptions.empty())
   {
      return mOptions[mSelectedOption].mDisplayText;
   }

   return StringTable->insert("", false);
}

StringTableEntry GuiGameSettingsCtrl::getCurrentOptionKey() const
{
   if (mSelectedOption != NO_OPTION)
   {
      return mOptions[mSelectedOption].mKeyString;
   }

   return StringTable->insert("", false);
}

S32 GuiGameSettingsCtrl::getCurrentOptionIndex() const
{
   if (mSelectedOption != NO_OPTION)
   {
      return mSelectedOption;
   }

   return S32(-1);
}

bool GuiGameSettingsCtrl::selectOption(const char* theOption)
{
   for (Vector<OptionEntry>::iterator anOption = mOptions.begin(); anOption < mOptions.end(); ++anOption)
   {
      if (String::compare((*anOption).mDisplayText, theOption) == 0)
      {
         S32 newIndex = anOption - mOptions.begin();
         mSelectedOption = newIndex;
         return true;
      }
   }

   return false;
}

bool GuiGameSettingsCtrl::selectOptionByKey(const char* optionKey)
{
   for (Vector<OptionEntry>::iterator anOption = mOptions.begin(); anOption < mOptions.end(); ++anOption)
   {
      if (String::compare((*anOption).mKeyString, optionKey) == 0)
      {
         S32 newIndex = anOption - mOptions.begin();
         mSelectedOption = newIndex;
         return true;
      }
   }

   return false;
}

bool GuiGameSettingsCtrl::selectOptionByIndex(S32 optionIndex)
{
   if (optionIndex < mOptions.size() && optionIndex >= 0)
   {
      mSelectedOption = optionIndex;
      return true;
   }

   return false;
}

void GuiGameSettingsCtrl::setOptions(const char* optionsList)
{
   static StringTableEntry DELIM = StringTable->insert("\t", true);

   S32 count = StringUnit::getUnitCount(optionsList, DELIM);
   mOptions.setSize(count);
   for (S32 i = 0; i < count; ++i)
   {
      const char* option = StringUnit::getUnit(optionsList, i, DELIM);
      OptionEntry e;
      e.mDisplayText = StringTable->insert(option, true);
      e.mKeyString = e.mDisplayText;
      mOptions[i] = e;
   }

   if (mSelectedOption >= mOptions.size())
   {
      mSelectedOption = mOptions.size() - 1;
   }
}

void GuiGameSettingsCtrl::addOption(const char* displayText, const char* keyText)
{
   OptionEntry e;
   e.mDisplayText = StringTable->insert(displayText, true);
   e.mKeyString = (keyText[0] == '\0') ? e.mDisplayText : StringTable->insert(keyText, true);

   mOptions.push_back(e);
}

void GuiGameSettingsCtrl::clickOption(S32 xPos)
{
   F32 xScale = (float)getWidth();

   S32 leftArrowX1 = mColumnSplit;
   S32 leftArrowX2 = leftArrowX1 + mArrowSize;

   S32 rightArrowX2 = getWidth() - mRightPad;
   S32 rightArrowX1 = rightArrowX2 - mArrowSize;

   if ((leftArrowX1 <= xPos) && (xPos <= leftArrowX2))
   {
      changeOption(-1);
   }
   else if ((rightArrowX1 <= xPos) && (xPos <= rightArrowX2))
   {
      changeOption(1);
   }
}

void GuiGameSettingsCtrl::changeOption(S32 delta)
{
   S32 optionCount = mOptions.size();

   S32 newSelection = mSelectedOption + delta;
   if (optionCount == 0)
   {
      newSelection = NO_OPTION;
   }
   else if (!mWrapOptions)
   {
      newSelection = mClamp(newSelection, 0, optionCount - 1);
   }
   else if (newSelection < 0)
   {
      newSelection = optionCount - 1;
   }
   else if (newSelection >= optionCount)
   {
      newSelection = 0;
   }
   mSelectedOption = newSelection;

   if (mMode == GuiGameSettingsCtrl::Slider)
   {
      mValue += mStepSize * delta;

      mValue = mRound(mValue / mStepSize) * mStepSize;

      if (mValue < mRange.x)
         mValue = mRange.x;
      if (mValue > mRange.y)
         mValue = mRange.y;
   }

   static StringTableEntry LEFT = StringTable->insert("LEFT", true);
   static StringTableEntry RIGHT = StringTable->insert("RIGHT", true);

   onChange_callback();

   if (mScriptCallback != NULL && (mSelectedOption != NO_OPTION && mMode != GuiGameSettingsCtrl::Slider))
   {
      setThisControl();
      StringTableEntry direction = StringTable->EmptyString();
      if (delta < 0)
      {
         direction = LEFT;
      }
      else if (delta > 0)
      {
         direction = RIGHT;
      }
      if ((direction != StringTable->EmptyString()) && (Con::isFunction(mScriptCallback)))
      {
         Con::executef(mScriptCallback, direction);
      }
   }
}
IMPLEMENT_CONOBJECT(GuiGameSettingsCtrl);

void GuiGameSettingsCtrl::clickSlider(S32 xPos)
{
   RectI sliderRect;

   S32 sliderOffset = 5;
   S32 height = getHeight();

   RectI optionRect;

   sliderRect.point.x = mColumnSplit + mArrowSize;
   sliderRect.point.y = sliderOffset;

   sliderRect.extent.x = (getWidth() - mRightPad - mArrowSize) - sliderRect.point.x;
   sliderRect.extent.y = height - sliderOffset * 2;

   optionRect = sliderRect;

   S32 textWidth = sliderRect.extent.x * 0.3;
   sliderRect.extent.x -= textWidth;

   //Now adjust the bar to match-to our value

   S32 barStart = sliderRect.point.x;
   S32 barEnd = sliderRect.point.x + sliderRect.extent.x;

   if (xPos >= barStart && xPos <= barEnd)
   {
      //find the position
      F32 newValue = (((xPos - barStart) * (mRange.y - mRange.x)) / (barEnd - barStart)) + mRange.x;

      newValue = mRound(newValue / mStepSize) * mStepSize;

      mValue = newValue;
   }

   onChange_callback();
}

void GuiGameSettingsCtrl::clickKeybind(S32 xPos)
{
   S32 columnSplit = mColumnSplit;

   S32 height = getHeight();
   S32 width = getWidth();

   RectI rect(Point2I::Zero, Point2I(width, height));

   onChange_callback();

   if (rect.pointInRect(Point2I(xPos, getHeight()/2)))
   {
      if (mScriptCallback != StringTable->EmptyString())
      {
         Con::executef(mScriptCallback, this);
      }
   }
}

F32 GuiGameSettingsCtrl::getValue()
{
   return mValue;
}

void GuiGameSettingsCtrl::setValue(F32 value)
{
   mValue = value;
}

F32 GuiGameSettingsCtrl::getIncrement()
{
   return mStepSize;
}

Point2F GuiGameSettingsCtrl::getRange()
{
   return mRange;
}

const char* GuiGameSettingsCtrl::getTooltip()
{
   return mTooltip;
}

ConsoleDocClass( GuiGameSettingsCtrl,
   "@brief A base class for cross platform menu controls that are gamepad friendly.\n\n"

   "This class is used to build row-based menu GUIs that can be easily navigated "
   "using the keyboard, mouse or gamepad. The desired row can be selected using "
   "the mouse, or by navigating using the Up and Down buttons.\n\n"

   "@tsexample\n\n"
   "new GuiGameSettingsCtrl()\n"
   "{\n"
   "   debugRender = \"0\";\n"
   "   callbackOnA = \"applyOptions();\";\n"
   "   callbackOnB = \"Canvas.setContent(MainMenuGui);\";\n"
   "   callbackOnX = \"\";\n"
   "   callbackOnY = \"revertOptions();\";\n"
   "   //Properties not specific to this control have been omitted from this example.\n"
   "};\n"
   "@endtsexample\n\n"

   "@see GuiGameSettingsProfile\n\n"

   "@ingroup GuiGame"
);

IMPLEMENT_CALLBACK( GuiGameSettingsCtrl, onChange, void, (), (),
   "Called when the setting's value changes." );

IMPLEMENT_CALLBACK(GuiGameSettingsCtrl, onInputEvent, void, (const char* device, const char* action, bool state),
   (device, action, state),
   "@brief Callback that occurs when an input is triggered on this control\n\n"
   "@param device The device type triggering the input, such as keyboard, mouse, etc\n"
   "@param action The actual event occuring, such as a key or button\n"
   "@param state True if the action is being pressed, false if it is being release\n\n");

IMPLEMENT_CALLBACK(GuiGameSettingsCtrl, onAxisEvent, void, (const char* device, const char* action, F32 axisValue),
   (device, action, axisValue),
   "@brief Callback that occurs when an axis event is triggered on this control\n\n"
   "@param device The device type triggering the input, such as mouse, joystick, gamepad, etc\n"
   "@param action The ActionMap code for the axis\n"
   "@param axisValue The current value of the axis\n\n");

void GuiGameSettingsCtrl::initPersistFields()
{
   docsURL;
   INITPERSISTFIELD_IMAGEASSET(KeybindBitmap, GuiGameSettingsCtrl, "Bitmap used to display the bound key for this keybind option.");
   INITPERSISTFIELD_IMAGEASSET(PreviousBitmap, GuiGameSettingsCtrl, "Bitmap used for the previous button when in list mode.");
   INITPERSISTFIELD_IMAGEASSET(NextBitmap, GuiGameSettingsCtrl, "Bitmap used for the next button when in list mode.");

   addField("arrowSize", TypeS32, Offset(mArrowSize, GuiGameSettingsCtrl),
      "Size of the arrow buttons' extents");

   addField("columnSplit", TypeS32, Offset(mColumnSplit, GuiGameSettingsCtrl),
      "Position of the split between the leftside label and the rightside setting parts");

   addField("rightPad", TypeS32, Offset(mRightPad, GuiGameSettingsCtrl),
      "Padding between the rightmost edge of the control and right arrow.");

   addField("callbackOnA", TypeString, Offset(mCallbackOnA, GuiGameSettingsCtrl),
      "Script callback when the 'A' button is pressed. 'A' inputs are Keyboard: A, Return, Space; Gamepad: A, Start" );

   addField("callbackOnB", TypeString, Offset(mCallbackOnB, GuiGameSettingsCtrl),
      "Script callback when the 'B' button is pressed. 'B' inputs are Keyboard: B, Esc, Backspace, Delete; Gamepad: B, Back" );

   addField("callbackOnX", TypeString, Offset(mCallbackOnX, GuiGameSettingsCtrl),
      "Script callback when the 'X' button is pressed. 'X' inputs are Keyboard: X; Gamepad: X" );

   addField("callbackOnY", TypeString, Offset(mCallbackOnY, GuiGameSettingsCtrl),
      "Script callback when the 'Y' button is pressed. 'Y' inputs are Keyboard: Y; Gamepad: Y" );

   addField("callbackOnInputs", TypeBool, Offset(mCallbackOnInputs, GuiGameSettingsCtrl),
      "Script callback when any inputs are detected, even if they aren't the regular 4 face buttons. Useful for secondary/speciality handling of menu navigation.");

   addField("consumeKeyInputEvents", TypeBool, Offset(mConsumeKeyInputEvents, GuiGameSettingsCtrl),
      "When callbackOnInputs is active, this indicates if the input event should be consumed, or allowed 'through' to let other things respond to the event as well.");
   

   Parent::initPersistFields();
}

DefineEngineMethod( GuiGameSettingsCtrl, isEnabled, bool, (),,
   "Determines if the control is enabled or disabled.\n\n"
   "@return True if the control is enabled. False if the control is not enabled." )
{
   return object->isEnabled();
}

DefineEngineMethod( GuiGameSettingsCtrl, setEnabled, void, ( bool enabled ),,
   "Sets the control's enabled status according to the given parameters.\n\n"
   "@param enabled Indicate true to enable the control or false to disable it." )
{
   object->setEnabled( enabled );
}

DefineEngineMethod( GuiGameSettingsCtrl, activate, void, (),,
   "Activates the control. The script callback of the control will be called (if it has one)." )
{
   object->activate();
}

DefineEngineMethod(GuiGameSettingsCtrl, getLabel, const char *, (),,
   "Gets the label displayed.\n\n"
   "@return The label." )
{
   return object->getLabel();
}

DefineEngineMethod(GuiGameSettingsCtrl, setLabel, void, ( const char* label ),,
   "Sets the label.\n\n"
   "@param label Text to set as the label.\n" )
{
   object->setLabel(label );
}

DefineEngineMethod( GuiGameSettingsCtrl, setSelected, void, (),,
   "Sets the control as selected. Can only select enabled controls." )
{
   object->setSelected();
}

DefineEngineMethod( GuiGameSettingsCtrl, getSelected, bool, (),,
   "Gets if the control is currently selected.\n\n"
   "@return if the control is selected." )
{
   return object->isSelected();
}

DefineEngineMethod(GuiGameSettingsCtrl, clear, void, (), ,
   "Clears the current options.\n\n")
{
   return object->clear();
}

DefineEngineMethod(GuiGameSettingsCtrl, getMode, S32, (), ,
   "Gets this control's options mode.\n\n")
{
   GuiGameSettingsCtrl::Mode mode = object->getMode();
   if (mode == GuiGameSettingsCtrl::Mode::OptionList)
      return 0;
   else if (mode == GuiGameSettingsCtrl::Mode::Slider)
      return 1;
   else if (mode == GuiGameSettingsCtrl::Mode::Keybind)
      return 2;
   else
      return -1;
}

DefineEngineMethod(GuiGameSettingsCtrl, setListSetting, void,
   (const char* label, const char* options, bool wrapOptions, const char* callback, bool enabled, const char* tooltip, const char* defaultValue),
   (true, "", ""),
   "Sets this setting to a list.\n\n"
   "@param label The text to display  as a label.\n"
   "@param options A tab separated list of options.\n"
   "@param wrapOptions Specify true to allow options to wrap at each end or false to prevent wrapping.\n"
   "@param callback Name of a script function to use as a callback when this control is activated.\n"
   "@param enabled [optional] If this control is initially enabled.")
{
   object->setListSetting(label, options, wrapOptions, callback, enabled, tooltip, defaultValue);
}

DefineEngineMethod(GuiGameSettingsCtrl, setSliderSetting, void,
(const char* label, F32 defaultValue, F32 increment, Point2F range, const char* callback, bool enabled, const char* tooltip),
(true, ""),
"Sets this setting to a slider.\n\n"
"@param label The text to display as a label.\n"
"@param options A tab separated list of options.\n"
"@param wrapOptions Specify true to allow options to wrap at each end or false to prevent wrapping.\n"
"@param callback Name of a script function to use as a callback when this control is activated.\n"
"@param enabled [optional] If this control is initially enabled.")
{
   object->setSliderSetting(label, defaultValue, increment, range, callback, enabled, tooltip);
}

DefineEngineMethod(GuiGameSettingsCtrl, setKeybindSetting, void,
(const char* label, const char* bitmapName, const char* callback, bool enabled, const char* tooltip),
(true, ""),
"Sets this setting to a keybind.\n\n"
"@param label The text to display as a label.\n"
"@param options A tab separated list of options.\n"
"@param wrapOptions Specify true to allow options to wrap at each end or false to prevent wrapping.\n"
"@param callback Name of a script function to use as a callback when this control is activated.\n"
"@param enabled [optional] If this control is initially enabled.")
{
   object->setKeybindSetting(label, bitmapName, callback, enabled, tooltip);
}

DefineEngineMethod(GuiGameSettingsCtrl, getCurrentOption, const char*, (), ,
   "Gets the text for the currently selected option .\n\n"
   "@return A string representing the text currently displayed as the selected option. If there is no such displayed text then the empty string is returned.")
{
   return object->getCurrentOption();
}

DefineEngineMethod(GuiGameSettingsCtrl, getCurrentOptionKey, const char*, (), ,
   "Gets the key string for the currently selected option.\n\n"
   "@return The key (or id) that was assigned to the selected option. If there is no selected option then the empty string is returned.")
{
   return object->getCurrentOptionKey();
}

DefineEngineMethod(GuiGameSettingsCtrl, getCurrentOptionIndex, S32, (), ,
   "Gets the index into the option list for the currently selected option.\n\n"
   "@return The index of the selected option. If there is no selected option then -1 is returned.")
{
   return object->getCurrentOptionIndex();
}

DefineEngineMethod(GuiGameSettingsCtrl, selectOption, bool, (const char* option), ,
   "Set the control's current option to the one specified\n\n"
   "@param option The option to be made active.\n"
   "@return True if the control contained the option and was set, false otherwise.")
{
   return object->selectOption(option);
}

DefineEngineMethod(GuiGameSettingsCtrl, selectOptionByKey, bool, (const char* optionKey), ,
   "Set the control's current option to the one with the specified key.\n\n"
   "@param optionKey The key string that was assigned to the option to be made active.\n"
   "@return True if the control contained the key and the option and was set, false otherwise.")
{
   return object->selectOptionByKey(optionKey);
}

DefineEngineMethod(GuiGameSettingsCtrl, selectOptionByIndex, bool, (S32 optionIndex), ,
   "Set the control's current option to the one at the specified index.\n\n"
   "@param optionIndex The index of the option to be made active.\n"
   "@return True if the index was valid and the option and was set, false otherwise.")
{
   return object->selectOptionByIndex(optionIndex);
}

DefineEngineMethod(GuiGameSettingsCtrl, setOptions, void, (const char* optionsList), ,
   "Sets the list of options on the given control.\n\n"
   "@param optionsList A tab separated list of options for the control.")
{
   object->setOptions(optionsList);
}

DefineEngineMethod(GuiGameSettingsCtrl, addOption, void, (const char* displayText, const char* keyText), (""),
   "Adds an option to the list of options on the given control.\n\n"
   "@param displayText The text to display for this option.\n"
   "@param keyText [Optional] The id string to associate with this value. "
   "If unset, the id will be the same as the display text.\n")
{
   object->addOption(displayText, keyText);
}

DefineEngineMethod(GuiGameSettingsCtrl, getValue, F32, (), ,
   "Gets the value of the slider on the given control.")
{
   return object->getValue();
}

DefineEngineMethod(GuiGameSettingsCtrl, setValue, void, (F32 value), ,
   "Sets the value of the slider on the given control.")
{
   object->setValue(value);
}

DefineEngineMethod(GuiGameSettingsCtrl, getIncrement, F32, (), ,
   "Gets the increment amount of the slider on a given control.")
{
   return object->getIncrement();
}

DefineEngineMethod(GuiGameSettingsCtrl, getRange, Point2F, (), ,
   "Gets the min and max values for the range of the slider on a given control.")
{
   return object->getRange();
}

DefineEngineMethod(GuiGameSettingsCtrl, getTooltip, const char*, (), ,
   "Gets the tooltip on the given control.")
{
   return object->getTooltip();
}
