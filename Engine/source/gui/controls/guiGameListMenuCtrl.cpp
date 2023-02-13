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

#include "guiGameListMenuCtrl.h"

#include "console/consoleTypes.h"
#include "console/engineAPI.h"
#include "gfx/gfxDrawUtil.h"
#include "gui/containers/guiScrollCtrl.h"
#include "sim/actionMap.h"
#include "core/strings/stringUnit.h"

//-----------------------------------------------------------------------------
// GuiGameListMenuCtrl
//-----------------------------------------------------------------------------

GuiGameListMenuCtrl::GuiGameListMenuCtrl()
 : mSelected(NO_ROW),
   mDebugRender(false),
   mHighlighted(NO_ROW),
   mCallbackOnInputs(false),
   mConsumeKeyInputEvents(false)
{
   VECTOR_SET_ASSOCIATION(mRows);

   // initialize the control callbacks
   mCallbackOnA = StringTable->EmptyString();
   mCallbackOnB = mCallbackOnA;
   mCallbackOnX = mCallbackOnA;
   mCallbackOnY = mCallbackOnA;
}

GuiGameListMenuCtrl::~GuiGameListMenuCtrl()
{
   for (S32 i = 0; i < mRows.size(); ++i)
   {
      delete mRows[i];
   }
}

void GuiGameListMenuCtrl::onRender(Point2I offset, const RectI &updateRect)
{
   GuiGameListMenuProfile * profile = (GuiGameListMenuProfile *) mProfile;

   GFXDrawUtil* drawUtil = GFX->getDrawUtil();

   F32 xScale = (float) getWidth() / profile->getRowWidth();

   bool profileHasIcons = profile->hasArrows();

   S32 rowHeight = profile->getRowHeight();

   Point2I currentOffset = offset;
   Point2I extent = getExtent();
   Point2I rowExtent(extent.x, rowHeight);
   Point2I textOffset(profile->mTextOffset.x * xScale, profile->mTextOffset.y);
   Point2I textExtent(extent.x - textOffset.x, rowHeight);
   Point2I iconExtent, iconOffset(0.0f, 0.0f);
   if (profileHasIcons)
   {
      iconExtent = profile->getIconExtent();

      // icon is centered vertically plus any specified offset
      S32 iconOffsetY = (rowHeight - iconExtent.y) >> 1;
      iconOffsetY += profile->mIconOffset.y;
      iconOffset = Point2I(profile->mIconOffset.x * xScale, iconOffsetY);
   }
   for (Vector<Row *>::iterator row = mRows.begin(); row < mRows.end(); ++row)
   {
      if (row != mRows.begin())
      {
         // rows other than the first can have padding above them
         currentOffset.y += (*row)->mHeightPad;
         currentOffset.y += rowHeight;
      }

      // select appropriate colors and textures
      ColorI fontColor;
      U32 buttonTextureIndex;
      S32 iconIndex = (*row)->mIconIndex;
      bool useHighlightIcon = (*row)->mUseHighlightIcon;
      if (!(*row)->mEnabled)
      {
         buttonTextureIndex = Profile::TEX_DISABLED;
         fontColor = profile->mFontColorNA;
      }
      else if (row == &mRows[mSelected])
      {
         if (iconIndex != NO_ICON)
         {
            iconIndex++;
         }
         buttonTextureIndex = Profile::TEX_SELECTED;
         fontColor = profile->mFontColorSEL;
      }
      else if ((mHighlighted != NO_ROW) && (row == &mRows[mHighlighted]))
      {
         if (iconIndex != NO_ICON && useHighlightIcon)
         {
            iconIndex++;
         }
         buttonTextureIndex = Profile::TEX_HIGHLIGHT;
         fontColor = profile->mFontColorHL;
      }
      else
      {
         buttonTextureIndex = Profile::TEX_NORMAL;
         fontColor = profile->mFontColor;
      }

      // render the row bitmap
      drawUtil->clearBitmapModulation();
      drawUtil->drawBitmapStretchSR(profile->mBitmap, RectI(currentOffset, rowExtent), profile->getBitmapArrayRect(buttonTextureIndex));

      // render the row icon if it has one
      if ((iconIndex != NO_ICON) && profileHasIcons && (!profile->getBitmapArrayRect((U32)iconIndex).extent.isZero()))
      {
         iconIndex += Profile::TEX_FIRST_ICON;
         drawUtil->clearBitmapModulation();
         drawUtil->drawBitmapStretchSR(profile->mBitmap, RectI(currentOffset + iconOffset, iconExtent), profile->getBitmapArrayRect(iconIndex));
      }

      // render the row text
      drawUtil->setBitmapModulation(fontColor);
      renderJustifiedText(currentOffset + textOffset, textExtent, (*row)->mLabel);

      if ((*row)->mMode == Row::Mode::OptionList)
      {
         onRenderListOption((*row), currentOffset);
      }
      else if ((*row)->mMode == Row::Mode::Slider)
      {
         onRenderSliderOption((*row), currentOffset);
      }
      else if ((*row)->mMode == Row::Mode::Keybind)
      {
         onRenderKeybindOption((*row), currentOffset);
      }
   }

   if (mDebugRender)
   {
      onDebugRender(offset);
   }

   renderChildControls(offset, updateRect);
}

void GuiGameListMenuCtrl::onRenderListOption(Row* row, Point2I currentOffset)
{
   GuiGameListMenuProfile* profile = (GuiGameListMenuProfile*)mProfile;

   F32 xScale = (float)getWidth() / profile->getRowWidth();

   S32 rowHeight = profile->getRowHeight();

   bool profileHasArrows = profile->hasArrows();
   Point2I arrowExtent;
   S32 arrowOffsetY(0);
   if (profileHasArrows)
   {
      arrowExtent = profile->getArrowExtent();

      // icon is centered vertically
      arrowOffsetY = (rowHeight - arrowExtent.y) >> 1;
   }

   GFXDrawUtil* drawer = GFX->getDrawUtil();

   Point2I arrowOffset;
   S32 columnSplit = profile->mColumnSplit * xScale;

   S32 iconIndex;
   bool hasOptions = (row->mOptions.size() > 0) && row->mSelectedOption > -1;
   if (hasOptions)
   {
      bool isRowSelected = (getSelected() != NO_ROW) && (row == mRows[getSelected()]);
      bool isRowHighlighted = (getHighlighted() != NO_ROW) ? ((row == mRows[getHighlighted()]) && (row->mEnabled)) : false;
      if (profileHasArrows)
      {
         // render the left arrow
         bool arrowOnL = (isRowSelected || isRowHighlighted) && (row->mWrapOptions || (row->mSelectedOption > 0));
         iconIndex = (arrowOnL) ? Profile::TEX_L_ARROW_ON : Profile::TEX_L_ARROW_OFF;
         arrowOffset.x = currentOffset.x + columnSplit;
         arrowOffset.y = currentOffset.y + arrowOffsetY;

         drawer->clearBitmapModulation();
         drawer->drawBitmapStretchSR(profile->getBitmapResource(), RectI(arrowOffset, arrowExtent), profile->getBitmapArrayRect((U32)iconIndex));

         // render the right arrow
         bool arrowOnR = (isRowSelected || isRowHighlighted) && (row->mWrapOptions || (row->mSelectedOption < row->mOptions.size() - 1));
         iconIndex = (arrowOnR) ? Profile::TEX_R_ARROW_ON : Profile::TEX_R_ARROW_OFF;
         arrowOffset.x = currentOffset.x + (profile->mHitAreaLowerRight.x - profile->mRightPad) * xScale - arrowExtent.x;
         arrowOffset.y = currentOffset.y + arrowOffsetY;

         drawer->clearBitmapModulation();
         drawer->drawBitmapStretchSR(profile->getBitmapResource(), RectI(arrowOffset, arrowExtent), profile->getBitmapArrayRect((U32)iconIndex));
      }

      // get the appropriate font color
      ColorI fontColor;
      if (!row->mEnabled)
      {
         fontColor = profile->mFontColorNA;
      }
      else if (isRowSelected)
      {
         fontColor = profile->mFontColorSEL;
      }
      else if (isRowHighlighted)
      {
         fontColor = profile->mFontColorHL;
      }
      else
      {
         fontColor = profile->mFontColor;
      }

      // calculate text to be at the center between the arrows
      GFont* font = profile->mFont;
      StringTableEntry text = row->mOptions[row->mSelectedOption].mDisplayText;
      S32 textWidth = font->getStrWidth(text);
      S32 columnWidth = profile->mHitAreaLowerRight.x * xScale - profile->mRightPad - columnSplit;
      S32 columnCenter = columnSplit + (columnWidth >> 1);
      S32 textStartX = columnCenter - (textWidth >> 1);
      Point2I textOffset(textStartX, 0);

      // render the option text itself
      Point2I textExtent(columnWidth, rowHeight);
      drawer->setBitmapModulation(fontColor);
      renderJustifiedText(currentOffset + textOffset, textExtent, text);
   }
}

void GuiGameListMenuCtrl::onRenderSliderOption(Row* row, Point2I currentOffset)
{
   GuiGameListMenuProfile* profile = (GuiGameListMenuProfile*)mProfile;

   F32 xScale = (float)getWidth() / profile->getRowWidth();

   S32 rowHeight = profile->getRowHeight();

   bool profileHasArrows = profile->hasArrows();
   Point2I arrowExtent;
   S32 arrowOffsetY(0);
   if (profileHasArrows)
   {
      arrowExtent = profile->getArrowExtent();

      // icon is centered vertically
      arrowOffsetY = (rowHeight - arrowExtent.y) >> 1;
   }

   GFXDrawUtil* drawer = GFX->getDrawUtil();

   Point2I arrowOffset;
   S32 columnSplit = profile->mColumnSplit * xScale;

   bool isRowSelected = (getSelected() != NO_ROW) && (row == mRows[getSelected()]);
   bool isRowHighlighted = (getHighlighted() != NO_ROW) ? ((row == mRows[getHighlighted()]) && (row->mEnabled)) : false;
   /*if (profileHasArrows)
   {
      // render the left arrow
      bool arrowOnL = (isRowSelected || isRowHighlighted) && (row->mValue > row->mRange.x);
      iconIndex = (arrowOnL) ? Profile::TEX_L_ARROW_ON : Profile::TEX_L_ARROW_OFF;
      arrowOffset.x = currentOffset.x + columnSplit;
      arrowOffset.y = currentOffset.y + arrowOffsetY;

      drawer->clearBitmapModulation();
      drawer->drawBitmapStretchSR(profile->mTextureObject, RectI(arrowOffset, arrowExtent), profile->getBitmapArrayRect((U32)iconIndex));

      // render the right arrow
      bool arrowOnR = (isRowSelected || isRowHighlighted) && (row->mValue < row->mRange.y);
      iconIndex = (arrowOnR) ? Profile::TEX_R_ARROW_ON : Profile::TEX_R_ARROW_OFF;
      arrowOffset.x = currentOffset.x + (profile->mHitAreaLowerRight.x - profile->mRightPad) * xScale - arrowExtent.x;
      arrowOffset.y = currentOffset.y + arrowOffsetY;

      drawer->clearBitmapModulation();
      drawer->drawBitmapStretchSR(profile->mTextureObject, RectI(arrowOffset, arrowExtent), profile->getBitmapArrayRect((U32)iconIndex));
   }*/

   //Draw the slider bar
   if (row->mEnabled)
   {
      RectI sliderRect;

      sliderRect.point.x = currentOffset.x + columnSplit + arrowExtent.x;
      sliderRect.point.y = currentOffset.y + arrowOffsetY;

      sliderRect.extent.x = (currentOffset.x + (profile->mHitAreaLowerRight.x - profile->mRightPad) * xScale - arrowExtent.x) - sliderRect.point.x;
      sliderRect.extent.y = arrowExtent.y;

      //Now adjust the bar to match-to our value

      S32 barStart = sliderRect.point.x;
      S32 barEnd = sliderRect.point.x + sliderRect.extent.x;

      S32 xPosFill = (((row->mValue - row->mRange.x) * (barEnd - barStart)) / (row->mRange.y - row->mRange.x)) + barStart;

      RectI fillRect = sliderRect;
      fillRect.extent.x = xPosFill - sliderRect.point.x;

      ColorI barColor;
      ColorI barOutlineColor;
      if (isRowSelected)
      {
         barColor = profile->mFillColor;
         barOutlineColor = profile->mFillColorSEL;
      }
      else
      {
         barColor = profile->mFillColor;
         barOutlineColor = profile->mFillColorHL;
      }

      drawer->drawRectFill(fillRect, barColor);

      drawer->drawRect(sliderRect, barOutlineColor);
   }

   // get the appropriate font color
   ColorI fontColor;
   if (!row->mEnabled)
   {
      fontColor = profile->mFontColorNA;
   }
   else if (isRowSelected)
   {
      fontColor = profile->mFontColorSEL;
   }
   else if (isRowHighlighted)
   {
      fontColor = profile->mFontColorHL;
   }
   else
   {
      fontColor = profile->mFontColor;
   }

   // calculate text to be at the center between the arrows
   GFont* font = profile->mFont;

   char stringVal[32];
   dSprintf(stringVal, 32, "%f", row->mValue);

   S32 textWidth = font->getStrWidth(stringVal);
   S32 columnWidth = profile->mHitAreaLowerRight.x * xScale - profile->mRightPad - columnSplit;
   S32 columnCenter = columnSplit + (columnWidth >> 1);
   S32 textStartX = columnCenter - (textWidth >> 1);
   Point2I textOffset(textStartX, 0);

   // render the option text itself
   Point2I textExtent(columnWidth, rowHeight);
   drawer->setBitmapModulation(fontColor);
   renderJustifiedText(currentOffset + textOffset, textExtent, stringVal);
}

void GuiGameListMenuCtrl::onRenderKeybindOption(Row* row, Point2I currentOffset)
{
   GuiGameListMenuProfile* profile = (GuiGameListMenuProfile*)mProfile;
   F32 xScale = (float)getWidth() / profile->getRowWidth();
   S32 columnSplit = profile->mColumnSplit * xScale;

   S32 rowHeight = profile->getRowHeight();

   GFXDrawUtil* drawer = GFX->getDrawUtil();
   //drawer->drawBitmap(row->mBitmap, )

   Point2I button;
   button.x = currentOffset.x + columnSplit + (columnSplit / 2.5)/* + (optionWidth / 2)*/;
   button.y = currentOffset.y + (rowHeight / 4);

   Point2I buttonSize;
   buttonSize.x = rowHeight / 2;
   buttonSize.y = rowHeight / 2;

   if (row->mBitmapTex.isValid())
   {
      GFXTextureObject* texture = row->mBitmapTex;
      RectI rect(button, buttonSize);
      drawer->clearBitmapModulation();
      drawer->drawBitmapStretch(texture, rect, GFXBitmapFlip_None, GFXTextureFilterLinear, false);
   }

   //drawer->drawRectFill(button, ColorI::BLUE);
}

void GuiGameListMenuCtrl::onDebugRender(Point2I offset)
{
   GuiGameListMenuProfile * profile = (GuiGameListMenuProfile *) mProfile;

   F32 xScale = (float) getWidth() / profile->getRowWidth();

   ColorI controlBorderColor(200, 200, 200); // gray
   ColorI rowBorderColor(255, 127, 255); // magenta
   ColorI hitBorderColor(255, 0, 0); // red
   Point2I shrinker(-1, -1);
   Point2I extent = getExtent();

   // render a border around the entire control
   RectI borderRect(offset, extent + shrinker);
   GFX->getDrawUtil()->drawRect(borderRect, controlBorderColor);

   S32 rowHeight = profile->getRowHeight();
   Point2I currentOffset(offset);
   Point2I rowExtent(extent.x, rowHeight);
   rowExtent += shrinker;
   Point2I hitAreaExtent(profile->getHitAreaExtent());
   hitAreaExtent.x *= xScale;
   hitAreaExtent += shrinker;
   Point2I hitAreaOffset = profile->mHitAreaUpperLeft;
   hitAreaOffset.x *= xScale;
   Point2I upperLeft;
   for (Vector<Row *>::iterator row = mRows.begin(); row < mRows.end(); ++row)
   {
      // set the top of the current row
      if (row != mRows.begin())
      {
         // rows other than the first can have padding above them
         currentOffset.y += (*row)->mHeightPad;
         currentOffset.y += rowHeight;
      }

      // draw the box around the whole row's extent
      upperLeft = currentOffset;
      borderRect.point = upperLeft;
      borderRect.extent = rowExtent;
      GFX->getDrawUtil()->drawRect(borderRect, rowBorderColor);

      // draw the box around the hit area of the row
      upperLeft = currentOffset + hitAreaOffset;
      borderRect.point = upperLeft;
      borderRect.extent = hitAreaExtent;
      GFX->getDrawUtil()->drawRect(borderRect, hitBorderColor);
   }
}

void GuiGameListMenuCtrl::addRow(const char* label, const char* callback, S32 icon, S32 yPad, bool useHighlightIcon, bool enabled, S32 mode, const char* tooltip)
{
   Row * row = new Row();
   addRow(row, label, callback, icon, yPad, useHighlightIcon, enabled, mode, tooltip);
}

void GuiGameListMenuCtrl::addRow(Row * row, const char* label, const char* callback, S32 icon, S32 yPad, bool useHighlightIcon, bool enabled, S32 mode, const char* tooltip)
{
   row->mLabel = StringTable->insert(label, true);
   row->mScriptCallback = (dStrlen(callback) > 0) ? StringTable->insert(callback, true) : NULL;
   row->mIconIndex = (icon < 0) ? NO_ICON : icon;
   row->mHeightPad = yPad;
   row->mUseHighlightIcon = useHighlightIcon;
   row->mEnabled = enabled;
   row->mMode = (Row::Mode)mode;
   row->mTooltip = StringTable->insert(tooltip);

   mRows.push_back(row);

   updateHeight();

   if (mSelected == NO_ROW)
   {
      selectFirstEnabledRow();
   }
}

void GuiGameListMenuCtrl::addRow(const char* label, const char* optionsList, bool wrapOptions, const char* callback, S32 icon, S32 yPad, bool enabled, const char* tooltip, const char* defaultValue)
{
   static StringTableEntry DELIM = StringTable->insert("\t", true);
   Row* row = new Row();
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
   row->mOptions = options;
   bool hasOptions = row->mOptions.size() > 0;
   row->mSelectedOption = (hasOptions) ? defaultOption : NO_OPTION;
   row->mWrapOptions = wrapOptions;
   addRow(row, label, callback, icon, yPad, true, (hasOptions) ? enabled : false, Row::Mode::OptionList, tooltip);
}

void GuiGameListMenuCtrl::addRow(const char* label, F32 defaultValue, F32 increments, Point2F range, const char* callback, S32 icon, S32 yPad, bool enabled, const char* tooltip)
{
   static StringTableEntry DELIM = StringTable->insert("\t", true);
   Row* row = new Row();
   row->mValue = defaultValue;
   row->mStepSize = increments;
   row->mRange = range;

   addRow(row, label, callback, icon, yPad, true, enabled, Row::Mode::Slider, tooltip);
}

void GuiGameListMenuCtrl::addRow(const char* label, const char* bitmapName, const char* callback, S32 icon, S32 yPad, bool enabled, const char* tooltip)
{
   static StringTableEntry DELIM = StringTable->insert("\t", true);
   Row* row = new Row();
   row->mBitmap = StringTable->insert(bitmapName);

   if(row->mBitmap != StringTable->EmptyString())
      row->mBitmapTex.set(row->mBitmap, &GFXDefaultGUIProfile, avar("%s() - mTextureObject (line %d)", __FUNCTION__, __LINE__));

   addRow(row, label, callback, icon, yPad, true, enabled, Row::Mode::Keybind, tooltip);
}

void GuiGameListMenuCtrl::removeRow(const S32& row)
{
   if (row == -1 || row >= mRows.size())
      return;

   mRows.erase(row);
}

Point2I  GuiGameListMenuCtrl::getMinExtent() const
{
   Point2I parentMin = Parent::getMinExtent();

   GuiGameListMenuProfile * profile = dynamic_cast<GuiGameListMenuProfile*>(mProfile);
   AssertFatal(profile, "Invalid profile for GuiGameListMenuCtrl!");

   S32 minHeight = 0;
   S32 rowHeight = profile->getRowHeight();

   for (Vector<Row *>::const_iterator row = mRows.begin(); row < mRows.end(); ++row)
   {
      minHeight += rowHeight;
      if (row != mRows.begin())
      {
         minHeight += (*row)->mHeightPad;
      }
   }

   if (minHeight > parentMin.y)
      parentMin.y = minHeight;

   return parentMin;
}

bool GuiGameListMenuCtrl::onAdd()
{
   if( !Parent::onAdd() )
      return false;
      
   // If we have a non-GuiGameListMenuProfile profile, try to
   // substitute it for DefaultListMenuProfile.
      
   if( !hasValidProfile() )
   {
      GuiGameListMenuProfile* profile;
      if( !Sim::findObject( "DefaultListMenuProfile", profile ) )
      {
         Con::errorf( "GuiGameListMenuCtrl: %s can't be created with a profile of type %s. Please create it with a profile of type GuiGameListMenuProfile.",
            getName(), mProfile->getClassName() );
         return false;
      }
      else
         Con::warnf( "GuiGameListMenuCtrl: substituted non-GuiGameListMenuProfile in %s for DefaultListMenuProfile", getName() );
         
      setControlProfile( profile );
   }

   return true;
}

bool GuiGameListMenuCtrl::onWake()
{
   if( !Parent::onWake() )
      return false;
      
   if( !hasValidProfile() )
      return false;
      
   /*if( mRows.empty() )
   {
      Con::errorf( "GuiGameListMenuCtrl: %s can't be woken up without any rows. Please use \"addRow\" to add at least one row to the control before pushing it to the canvas.",
         getName() );
      return false;
   }*/

   enforceConstraints();

   selectFirstEnabledRow();

   setFirstResponder();

   mHighlighted = NO_ROW;

   return true;
}

bool GuiGameListMenuCtrl::hasValidProfile() const
{
   GuiGameListMenuProfile * profile = dynamic_cast<GuiGameListMenuProfile *>(mProfile);
   return profile;
}

void GuiGameListMenuCtrl::enforceConstraints()
{
   if( hasValidProfile() )
   {
      ((GuiGameListMenuProfile *)mProfile)->enforceConstraints();
   }
   updateHeight();
}

void GuiGameListMenuCtrl::updateHeight()
{
   if (hasValidProfile())
   {
       S32 minHeight = getMinExtent().y;
       if (getHeight() < minHeight)
       {
           setHeight(minHeight);
       }
   }
}

void GuiGameListMenuCtrl::onMouseDown(const GuiEvent &event)
{
   S32 hitRow = getRow(event.mousePoint);
   if (hitRow != NO_ROW)
   {
      S32 delta = (mSelected != NO_ROW) ? (hitRow - mSelected) : (mSelected + 1);
      changeRow(delta);
   }
}

void GuiGameListMenuCtrl::onMouseLeave(const GuiEvent &event)
{
   mHighlighted = NO_ROW;
}

void GuiGameListMenuCtrl::onMouseMove(const GuiEvent &event)
{
   S32 hitRow = getRow(event.mousePoint);
   // allow mHighligetd to be set to NO_ROW so rows can be unhighlighted
   mHighlighted = hitRow;
}

void GuiGameListMenuCtrl::onMouseUp(const GuiEvent &event)
{
   S32 hitRow = getRow(event.mousePoint);
   if ((hitRow != NO_ROW) && isRowEnabled(hitRow) && (hitRow == getSelected()))
   {
      if (mRows[hitRow]->mMode == Row::Mode::Default)
      {
         activateRow();
      }
      else if (mRows[hitRow]->mMode == Row::Mode::OptionList)
      {
         S32 xPos = globalToLocalCoord(event.mousePoint).x;
         clickOption((Row*)mRows[getSelected()], xPos);
      }
      else if (mRows[hitRow]->mMode == Row::Mode::Slider)
      {
         S32 xPos = globalToLocalCoord(event.mousePoint).x;
         clickSlider((Row*)mRows[getSelected()], xPos);
      }
      else if (mRows[hitRow]->mMode == Row::Mode::Keybind)
      {
         S32 xPos = globalToLocalCoord(event.mousePoint).x;
         clickKeybind((Row*)mRows[getSelected()], xPos);
      }
   }
}

void GuiGameListMenuCtrl::activateRow()
{
   S32 row = getSelected();
   if ((row != NO_ROW) && isRowEnabled(row) && (mRows[row]->mScriptCallback != NULL))
   {
      setThisControl();
      if (Con::isFunction(mRows[row]->mScriptCallback))
      {
         Con::executef(mRows[row]->mScriptCallback);
      }
   }
}

S32 GuiGameListMenuCtrl::getRow(Point2I globalPoint)
{
   Point2I localPoint = globalToLocalCoord(globalPoint);
   GuiGameListMenuProfile * profile = (GuiGameListMenuProfile *) mProfile;

   F32 xScale = (float) getWidth() / profile->getRowWidth();

   S32 rowHeight = profile->getRowHeight();
   Point2I currentOffset(0, 0);
   Point2I hitAreaUpperLeft = profile->mHitAreaUpperLeft;
   hitAreaUpperLeft.x *= xScale;
   Point2I hitAreaLowerRight = profile->mHitAreaLowerRight;
   hitAreaLowerRight.x *= xScale;

   Point2I upperLeft, lowerRight;
   for (Vector<Row *>::iterator row = mRows.begin(); row < mRows.end(); ++row)
   {
      if (row != mRows.begin())
      {
         // rows other than the first can have padding above them
         currentOffset.y += (*row)->mHeightPad;
      }

      upperLeft = currentOffset + hitAreaUpperLeft;
      lowerRight = currentOffset + hitAreaLowerRight;

      if ((upperLeft.x <= localPoint.x) && (localPoint.x < lowerRight.x) &&
         (upperLeft.y <= localPoint.y) && (localPoint.y < lowerRight.y))
      {
         return row - mRows.begin();
      }

      currentOffset.y += rowHeight;
   }

   return NO_ROW;
}

void GuiGameListMenuCtrl::setSelected(S32 index)
{
   if (index == NO_ROW)
   {
      // deselection
      mSelected = NO_ROW;
      return;
   }

   if (! isValidRowIndex(index))
   {
      return;
   }

   if (! isRowEnabled(index))
   {
      // row is disabled, it can't be selected
      return;
   }

   mSelected = mClamp(index, 0, mRows.size() - 1);

   //If we're childed to a scroll container, make sure us changing rows has our new position visible
   GuiScrollCtrl* scroll = dynamic_cast<GuiScrollCtrl*>(getParent());
   if (scroll)
   {
      scroll->scrollRectVisible(getRowBounds(mSelected));
   }
}

bool GuiGameListMenuCtrl::isRowEnabled(S32 index) const
{
   if (! isValidRowIndex(index))
   {
      return false;
   }

   return mRows[index]->mEnabled;
}

void GuiGameListMenuCtrl::setRowEnabled(S32 index, bool enabled)
{
   if (! isValidRowIndex(index))
   {
      return;
   }

   mRows[index]->mEnabled = enabled;

   if (getSelected() == index)
   {
      selectFirstEnabledRow();
   }
}

bool GuiGameListMenuCtrl::isValidRowIndex(S32 index) const
{
   return ((0 <= index) && (index < mRows.size()));
}

void GuiGameListMenuCtrl::selectFirstEnabledRow()
{
   setSelected(NO_ROW);
   for (Vector<Row *>::iterator row = mRows.begin(); row < mRows.end(); ++row)
   {
      if ((*row)->mEnabled)
      {
         setSelected(row - mRows.begin());
         return;
      }
   }
}

bool GuiGameListMenuCtrl::onInputEvent(const InputEventInfo& event)
{
   if (mCallbackOnInputs)
   {
      char deviceStr[32];
      if (!ActionMap::getDeviceName(event.deviceType, event.deviceInst, deviceStr))
         return false;

      String deviceString = deviceStr;

      if (event.action == SI_MAKE || event.action == SI_BREAK)
      {
         bool isModifier = false;

         bool state = event.action == SI_MAKE;

         switch (event.objInst)
         {
            case KEY_LCONTROL:
            case KEY_RCONTROL:
            case KEY_LALT:
            case KEY_RALT:
            case KEY_LSHIFT:
            case KEY_RSHIFT:
            case KEY_MAC_LOPT:
            case KEY_MAC_ROPT:
               isModifier = true;
         }

         if ((event.objType == SI_KEY) && isModifier)
         {
            char keyString[32];
            if (!ActionMap::getKeyString(event.objInst, keyString))
               return false;

            onInputEvent_callback(deviceString.c_str(), keyString, state);

            if (mConsumeKeyInputEvents)
            {
               if(deviceString.startsWith("keyboard"))
                  return true;
            }
         }
         else
         {
            const char* actionString = ActionMap::buildActionString(&event);
            onInputEvent_callback(deviceString.c_str(), actionString, state);

            if (mConsumeKeyInputEvents)
            {
               if (deviceString.startsWith("keyboard") || deviceString.startsWith("gamepad"))
                  return true;
            }
         }
      }
      else if (event.objType == SI_AXIS || event.objType == SI_INT || event.objType == SI_FLOAT)
      {
         F32 fValue = event.fValue;
         if (event.objType == SI_INT)
            fValue = (F32)event.iValue;

         if (!ActionMap::getDeviceName(event.deviceType, event.deviceInst, deviceStr))
            return false;

         const char* actionString = ActionMap::buildActionString(&event);

         onAxisEvent_callback(deviceStr, actionString, fValue);
      }
   }

   return false;
}

bool GuiGameListMenuCtrl::onKeyDown(const GuiEvent &event)
{
   switch (event.keyCode)
   {
      case KEY_UP:
         changeRow(-1);
         return true;

      case KEY_DOWN:
         changeRow(1);
         return true;

      case KEY_LEFT:
         changeOption(-1);
         return true;

      case KEY_RIGHT:
         changeOption(1);
         return true;

      case KEY_A:
      case KEY_RETURN:
      case KEY_NUMPADENTER:
      case KEY_SPACE:
      case XI_A:
      case XI_START:
         doScriptCommand(mCallbackOnA);
         return true;

      case KEY_B:
      case KEY_ESCAPE:
      case KEY_BACKSPACE:
      case KEY_DELETE:
      case XI_B:
      case XI_BACK:
         doScriptCommand(mCallbackOnB);
         return true;

      case KEY_X:
      case XI_X:
         doScriptCommand(mCallbackOnX);
         return true;

      case KEY_Y:
      case XI_Y:
         doScriptCommand(mCallbackOnY);
         return true;
      default:
         break;
   }

   return Parent::onKeyDown(event);
}

bool GuiGameListMenuCtrl::onGamepadAxisUp(const GuiEvent &event)
{
   changeRow(-1);
   return true;
}

bool GuiGameListMenuCtrl::onGamepadAxisDown(const GuiEvent &event)
{
   changeRow(1);
   return true;
}

bool GuiGameListMenuCtrl::onGamepadAxisLeft(const GuiEvent& event)
{
   changeOption(-1);
   return true;
}

bool GuiGameListMenuCtrl::onGamepadAxisRight(const GuiEvent& event)
{
   changeOption(1);
   return true;
}

void GuiGameListMenuCtrl::doScriptCommand(StringTableEntry command)
{
   if (command && command[0])
   {
      setThisControl();
      Con::evaluate(command, false, __FILE__);
   }
}

void GuiGameListMenuCtrl::changeRow(S32 delta)
{
   S32 oldRowIndex = getSelected();
   S32 newRowIndex = oldRowIndex;
   do
   {
      newRowIndex += delta;
      if (newRowIndex >= mRows.size())
      {
         newRowIndex = 0;
      }
      else if (newRowIndex < 0)
      {
         newRowIndex = mRows.size() - 1;
      }
   }
   while ((! mRows[newRowIndex]->mEnabled) && (newRowIndex != oldRowIndex));

   setSelected(newRowIndex);

   // do the callback
   onChange_callback();
}

void GuiGameListMenuCtrl::setThisControl()
{
   smThisControl = this;
}

StringTableEntry GuiGameListMenuCtrl::getRowLabel(S32 rowIndex) const
{
   if (! isValidRowIndex(rowIndex))
   {
      // not a valid row index, don't do anything
      return StringTable->EmptyString();
   }
   return mRows[rowIndex]->mLabel;
}

void GuiGameListMenuCtrl::setRowLabel(S32 rowIndex, const char * label)
{
   if (! isValidRowIndex(rowIndex))
   {
      // not a valid row index, don't do anything
      return;
   }

   mRows[rowIndex]->mLabel = StringTable->insert(label, true);
}

void GuiGameListMenuCtrl::clearRows()
{
   for (U32 i = 0; i < mRows.size(); i++)
   {
      if (mRows[i]->mBitmap != StringTable->EmptyString())
         mRows[i]->mBitmapTex = nullptr;
   }

   mRows.clear();
   setSelected(-1);
   setHeight(mMinExtent.y);
}

void GuiGameListMenuCtrl::refresh()
{
   enforceConstraints();
}

RectI GuiGameListMenuCtrl::getRowBounds(S32 rowIndex)
{
   GuiGameListMenuProfile* profile = (GuiGameListMenuProfile*)mProfile;

   S32 rowHeight = profile->getRowHeight();

   Point2I currentOffset = Point2I::Zero;
   Point2I extent = getExtent();
   Point2I rowExtent(extent.x, rowHeight);

   for (U32 i = 1; i <= rowIndex; i++)
   {
      //the top row can't pad, so we'll ignore it
      GuiGameListMenuCtrl::Row* row = mRows[i];

      // rows other than the first can have padding above them
      currentOffset.y += row->mHeightPad;
      currentOffset.y += rowHeight;
   }

   return RectI(currentOffset, rowExtent);
}
//-----------------------------------------------------------------------------
// Console stuff (GuiGameListMenuCtrl)
//-----------------------------------------------------------------------------

StringTableEntry GuiGameListMenuCtrl::getCurrentOption(S32 rowIndex) const
{
   if (isValidRowIndex(rowIndex))
   {
      Row* row = (Row*)mRows[rowIndex];
      if (row->mSelectedOption != NO_OPTION)
      {
         return row->mOptions[row->mSelectedOption].mDisplayText;
      }
   }
   return StringTable->insert("", false);
}

StringTableEntry GuiGameListMenuCtrl::getCurrentOptionKey(S32 rowIndex) const
{
   if (isValidRowIndex(rowIndex))
   {
      Row* row = (Row*)mRows[rowIndex];
      if (row->mSelectedOption != NO_OPTION)
      {
         return row->mOptions[row->mSelectedOption].mKeyString;
      }
   }
   return StringTable->insert("", false);
}

S32 GuiGameListMenuCtrl::getCurrentOptionIndex(S32 rowIndex) const
{
   if (isValidRowIndex(rowIndex))
   {
      Row* row = (Row*)mRows[rowIndex];
      if (row->mSelectedOption != NO_OPTION)
      {
         return row->mSelectedOption;
      }
   }
   return S32(-1);
}

bool GuiGameListMenuCtrl::selectOption(S32 rowIndex, const char* theOption)
{
   if (!isValidRowIndex(rowIndex))
   {
      return false;
   }

   Row* row = (Row*)mRows[rowIndex];

   for (Vector<OptionEntry>::iterator anOption = row->mOptions.begin(); anOption < row->mOptions.end(); ++anOption)
   {
      if (String::compare((*anOption).mDisplayText, theOption) == 0)
      {
         S32 newIndex = anOption - row->mOptions.begin();
         row->mSelectedOption = newIndex;
         return true;
      }
   }

   return false;
}

bool GuiGameListMenuCtrl::selectOptionByKey(S32 rowIndex, const char* optionKey)
{
   if (!isValidRowIndex(rowIndex))
   {
      return false;
   }

   Row* row = (Row*)mRows[rowIndex];

   for (Vector<OptionEntry>::iterator anOption = row->mOptions.begin(); anOption < row->mOptions.end(); ++anOption)
   {
      if (String::compare((*anOption).mKeyString, optionKey) == 0)
      {
         S32 newIndex = anOption - row->mOptions.begin();
         row->mSelectedOption = newIndex;
         return true;
      }
   }

   return false;
}

bool GuiGameListMenuCtrl::selectOptionByIndex(S32 rowIndex, S32 optionIndex)
{
   if (!isValidRowIndex(rowIndex) || (optionIndex < 0))
   {
      return false;
   }

   Row* row = (Row*)mRows[rowIndex];
   if (optionIndex < row->mOptions.size())
   {
      row->mSelectedOption = optionIndex;
      return true;
   }

   return false;
}

void GuiGameListMenuCtrl::setOptions(S32 rowIndex, const char* optionsList)
{
   static StringTableEntry DELIM = StringTable->insert("\t", true);

   if (!isValidRowIndex(rowIndex))
   {
      return;
   }

   Row* row = (Row*)mRows[rowIndex];

   S32 count = StringUnit::getUnitCount(optionsList, DELIM);
   row->mOptions.setSize(count);
   for (S32 i = 0; i < count; ++i)
   {
      const char* option = StringUnit::getUnit(optionsList, i, DELIM);
      OptionEntry e;
      e.mDisplayText = StringTable->insert(option, true);
      e.mKeyString = e.mDisplayText;
      row->mOptions[i] = e;
   }

   if (row->mSelectedOption >= row->mOptions.size())
   {
      row->mSelectedOption = row->mOptions.size() - 1;
   }
}

void GuiGameListMenuCtrl::addOption(S32 rowIndex, const char* displayText, const char* keyText)
{
   if (!isValidRowIndex(rowIndex))
   {
      return;
   }

   OptionEntry e;
   e.mDisplayText = StringTable->insert(displayText, true);
   e.mKeyString = (keyText[0] == '\0') ? e.mDisplayText : StringTable->insert(keyText, true);

   Row* row = (Row*)mRows[rowIndex];
   row->mOptions.push_back(e);
}

void GuiGameListMenuCtrl::clickOption(Row* row, S32 xPos)
{
   GuiGameListMenuProfile* profile = (GuiGameListMenuProfile*)mProfile;
   if (!profile->hasArrows())
   {
      return;
   }

   F32 xScale = (float)getWidth() / profile->getRowWidth();

   S32 bitmapArrowWidth = mProfile->getBitmapArrayRect(Profile::TEX_FIRST_ARROW).extent.x;

   S32 leftArrowX1 = profile->mColumnSplit * xScale;
   S32 leftArrowX2 = leftArrowX1 + bitmapArrowWidth;

   S32 rightArrowX2 = (profile->mHitAreaLowerRight.x - profile->mRightPad) * xScale;
   S32 rightArrowX1 = rightArrowX2 - bitmapArrowWidth;

   if ((leftArrowX1 <= xPos) && (xPos <= leftArrowX2))
   {
      changeOption(row, -1);
   }
   else if ((rightArrowX1 <= xPos) && (xPos <= rightArrowX2))
   {
      changeOption(row, 1);
   }
}

void GuiGameListMenuCtrl::changeOption(S32 delta)
{
   if (getSelected() != NO_ROW)
   {
      Row* row = (Row*)mRows[getSelected()];
      changeOption(row, delta);
   }
}

void GuiGameListMenuCtrl::changeOption(Row* row, S32 delta)
{
   S32 optionCount = row->mOptions.size();

   S32 newSelection = row->mSelectedOption + delta;
   if (optionCount == 0)
   {
      newSelection = NO_OPTION;
   }
   else if (!row->mWrapOptions)
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
   row->mSelectedOption = newSelection;

   if (row->mMode == GuiGameListMenuCtrl::Row::Slider)
   {
      row->mValue += row->mStepSize * delta;

      row->mValue = mRound(row->mValue / row->mStepSize) * row->mStepSize;

      if (row->mValue < row->mRange.x)
         row->mValue = row->mRange.x;
      if (row->mValue > row->mRange.y)
         row->mValue = row->mRange.y;
   }

   static StringTableEntry LEFT = StringTable->insert("LEFT", true);
   static StringTableEntry RIGHT = StringTable->insert("RIGHT", true);

   if (row->mScriptCallback != NULL && (row->mSelectedOption != NO_OPTION && row->mMode != GuiGameListMenuCtrl::Row::Slider))
   {
      setThisControl();
      StringTableEntry direction = NULL;
      if (delta < 0)
      {
         direction = LEFT;
      }
      else if (delta > 0)
      {
         direction = RIGHT;
      }
      if ((direction != NULL) && (Con::isFunction(row->mScriptCallback)))
      {
         Con::executef(row->mScriptCallback, direction);
      }
   }
}
IMPLEMENT_CONOBJECT(GuiGameListMenuCtrl);

void GuiGameListMenuCtrl::clickSlider(Row* row, S32 xPos)
{
   GuiGameListMenuProfile* profile = (GuiGameListMenuProfile*)mProfile;
   if (!profile->hasArrows())
   {
      return;
   }

   F32 xScale = (float)getWidth() / profile->getRowWidth();

   S32 bitmapArrowWidth = mProfile->getBitmapArrayRect(Profile::TEX_FIRST_ARROW).extent.x;

   S32 leftArrowX1 = profile->mColumnSplit * xScale;
   S32 leftArrowX2 = leftArrowX1 + bitmapArrowWidth;

   S32 rightArrowX2 = (profile->mHitAreaLowerRight.x - profile->mRightPad) * xScale;
   S32 rightArrowX1 = rightArrowX2 - bitmapArrowWidth;

   if ((leftArrowX1 <= xPos) && (xPos <= leftArrowX2))
   {
      row->mValue -= row->mStepSize;

      row->mValue = mRound(row->mValue / row->mStepSize) * row->mStepSize;

      if (row->mValue < row->mRange.x)
         row->mValue = row->mRange.x;

   }
   else if ((rightArrowX1 <= xPos) && (xPos <= rightArrowX2))
   {
      //F32 snap = row->mValue % row->mStepSize;
      //row->mValue.y -= snap;

      row->mValue += row->mStepSize;

      row->mValue = mRound(row->mValue / row->mStepSize) * row->mStepSize;

      if (row->mValue > row->mRange.y)
         row->mValue = row->mRange.y;
   }
   else
   {
      //see if we clicked on the sliderbar itself
      S32 barStart = leftArrowX2;
      S32 barEnd = rightArrowX1;

      if (xPos >= barStart && xPos <= barEnd)
      {
         //find the position
         F32 newValue = (((xPos - barStart) * (row->mRange.y - row->mRange.x)) / (barEnd - barStart)) + row->mRange.x;

         newValue = mRound(newValue / row->mStepSize) * row->mStepSize;

         row->mValue = newValue;
      }
   }
}

void GuiGameListMenuCtrl::clickKeybind(Row* row, S32 xPos)
{
   GuiGameListMenuProfile* profile = (GuiGameListMenuProfile*)mProfile;
   F32 xScale = (float)getWidth() / profile->getRowWidth();
   S32 columnSplit = profile->mColumnSplit * xScale;

   S32 rowHeight = profile->getRowHeight();

   //drawer->drawBitmap(row->mBitmap, )

   Point2I button;
   button.x = columnSplit + (columnSplit / 2)/* + (optionWidth / 2)*/;
   button.y = rowHeight / 4;

   Point2I buttonSize;
   buttonSize.x = rowHeight / 2;
   buttonSize.y = rowHeight / 2;

   RectI rect(button, buttonSize);

   if (rect.pointInRect(Point2I(xPos, rowHeight / 2)))
   {
      if (row->mScriptCallback != StringTable->EmptyString())
      {
         S32 rowId = getSelected();
         Con::executef(row->mScriptCallback, rowId);
      }
   }
}

F32 GuiGameListMenuCtrl::getValue(S32 rowIndex)
{
   if (!isValidRowIndex(rowIndex))
   {
      return 0;
   }

   Row* row = (Row*)mRows[rowIndex];

   return row->mValue;
}

void GuiGameListMenuCtrl::setValue(S32 rowIndex, F32 value)
{
   if (!isValidRowIndex(rowIndex))
   {
      return;
   }

   Row* row = (Row*)mRows[rowIndex];

   row->mValue = value;
}

const char* GuiGameListMenuCtrl::getTooltip(S32 rowIndex)
{
   if (!isValidRowIndex(rowIndex))
   {
      return "";
   }

   Row* row = (Row*)mRows[rowIndex];

   return row->mTooltip;
}

ConsoleDocClass( GuiGameListMenuCtrl,
   "@brief A base class for cross platform menu controls that are gamepad friendly.\n\n"

   "This class is used to build row-based menu GUIs that can be easily navigated "
   "using the keyboard, mouse or gamepad. The desired row can be selected using "
   "the mouse, or by navigating using the Up and Down buttons.\n\n"

   "@tsexample\n\n"
   "new GuiGameListMenuCtrl()\n"
   "{\n"
   "   debugRender = \"0\";\n"
   "   callbackOnA = \"applyOptions();\";\n"
   "   callbackOnB = \"Canvas.setContent(MainMenuGui);\";\n"
   "   callbackOnX = \"\";\n"
   "   callbackOnY = \"revertOptions();\";\n"
   "   //Properties not specific to this control have been omitted from this example.\n"
   "};\n"
   "@endtsexample\n\n"

   "@see GuiGameListMenuProfile\n\n"

   "@ingroup GuiGame"
);

IMPLEMENT_CALLBACK( GuiGameListMenuCtrl, onChange, void, (), (),
   "Called when the selected row changes." );

IMPLEMENT_CALLBACK(GuiGameListMenuCtrl, onInputEvent, void, (const char* device, const char* action, bool state),
   (device, action, state),
   "@brief Callback that occurs when an input is triggered on this control\n\n"
   "@param device The device type triggering the input, such as keyboard, mouse, etc\n"
   "@param action The actual event occuring, such as a key or button\n"
   "@param state True if the action is being pressed, false if it is being release\n\n");

IMPLEMENT_CALLBACK(GuiGameListMenuCtrl, onAxisEvent, void, (const char* device, const char* action, F32 axisValue),
   (device, action, axisValue),
   "@brief Callback that occurs when an axis event is triggered on this control\n\n"
   "@param device The device type triggering the input, such as mouse, joystick, gamepad, etc\n"
   "@param action The ActionMap code for the axis\n"
   "@param axisValue The current value of the axis\n\n");

void GuiGameListMenuCtrl::initPersistFields()
{
   docsURL;
   addField("debugRender", TypeBool, Offset(mDebugRender, GuiGameListMenuCtrl),
      "Enable debug rendering" );

   addField("callbackOnA", TypeString, Offset(mCallbackOnA, GuiGameListMenuCtrl),
      "Script callback when the 'A' button is pressed. 'A' inputs are Keyboard: A, Return, Space; Gamepad: A, Start" );

   addField("callbackOnB", TypeString, Offset(mCallbackOnB, GuiGameListMenuCtrl),
      "Script callback when the 'B' button is pressed. 'B' inputs are Keyboard: B, Esc, Backspace, Delete; Gamepad: B, Back" );

   addField("callbackOnX", TypeString, Offset(mCallbackOnX, GuiGameListMenuCtrl),
      "Script callback when the 'X' button is pressed. 'X' inputs are Keyboard: X; Gamepad: X" );

   addField("callbackOnY", TypeString, Offset(mCallbackOnY, GuiGameListMenuCtrl),
      "Script callback when the 'Y' button is pressed. 'Y' inputs are Keyboard: Y; Gamepad: Y" );

   addField("callbackOnInputs", TypeBool, Offset(mCallbackOnInputs, GuiGameListMenuCtrl),
      "Script callback when any inputs are detected, even if they aren't the regular 4 face buttons. Useful for secondary/speciality handling of menu navigation.");

   addField("consumeKeyInputEvents", TypeBool, Offset(mConsumeKeyInputEvents, GuiGameListMenuCtrl),
      "When callbackOnInputs is active, this indicates if the input event should be consumed, or allowed 'through' to let other things respond to the event as well.");
   

   Parent::initPersistFields();
}

DefineEngineMethod( GuiGameListMenuCtrl, addRow, void,
   ( const char* label, const char* callback, S32 icon, S32 yPad, bool useHighlightIcon, bool enabled, int mode ),
   ( -1, 0, true, true, 0 ),
   "Add a row to the list control.\n\n"
   "@param label The text to display on the row as a label.\n"
   "@param callback Name of a script function to use as a callback when this row is activated.\n"
   "@param icon [optional] Index of the icon to use as a marker.\n"
   "@param yPad [optional] An extra amount of height padding before the row. Does nothing on the first row.\n"
   "@param useHighlightIcon [optional] Does this row use the highlight icon?.\n"
   "@param enabled [optional] If this row is initially enabled.\n"
   "@param mode [optional] What option mode the row is in. 0 = Default, 1 = OptionList, 2 == Keybind")
{
   object->addRow( label, callback, icon, yPad, useHighlightIcon, enabled, mode);
}

DefineEngineMethod( GuiGameListMenuCtrl, isRowEnabled, bool, ( S32 row ),,
   "Determines if the specified row is enabled or disabled.\n\n"
   "@param row The row to set the enabled status of.\n"
   "@return True if the specified row is enabled. False if the row is not enabled or the given index was not valid." )
{
   return object->isRowEnabled( row );
}

DefineEngineMethod( GuiGameListMenuCtrl, setRowEnabled, void, ( S32 row, bool enabled ),,
   "Sets a row's enabled status according to the given parameters.\n\n"
   "@param row The index to check for validity.\n"
   "@param enabled Indicate true to enable the row or false to disable it." )
{
   object->setRowEnabled( row, enabled );
}

DefineEngineMethod( GuiGameListMenuCtrl, activateRow, void, (),,
   "Activates the current row. The script callback of  the current row will be called (if it has one)." )
{
   object->activateRow();
}

DefineEngineMethod( GuiGameListMenuCtrl, getRowCount, S32, (),,
   "Gets the number of rows on the control.\n\n"
   "@return (int) The number of rows on the control." )
{
   return object->getRowCount();
}

DefineEngineMethod( GuiGameListMenuCtrl, getRowLabel, const char *, ( S32 row ),,
   "Gets the label displayed on the specified row.\n\n"
   "@param row Index of the row to get the label of.\n"
   "@return The label for the row." )
{
   return object->getRowLabel( row );
}

DefineEngineMethod( GuiGameListMenuCtrl, setRowLabel, void, ( S32 row, const char* label ),,
   "Sets the label on the given row.\n\n"
   "@param row Index of the row to set the label on.\n"
   "@param label Text to set as the label of the row.\n" )
{
   object->setRowLabel( row, label );
}

DefineEngineMethod( GuiGameListMenuCtrl, setSelected, void, ( S32 row ),,
   "Sets the selected row. Only rows that are enabled can be selected.\n\n"
   "@param row Index of the row to set as selected." )
{
   object->setSelected( row );
}

DefineEngineMethod( GuiGameListMenuCtrl, getSelectedRow, S32, (),,
   "Gets the index of the currently selected row.\n\n"
   "@return Index of the selected row." )
{
   return object->getSelected();
}

DefineEngineMethod(GuiGameListMenuCtrl, clearRows, void, (), ,
   "Gets the index of the currently selected row.\n\n"
   "@return Index of the selected row.")
{
   return object->clearRows();
}

DefineEngineMethod(GuiGameListMenuCtrl, refresh, void, (), ,
   "Gets the index of the currently selected row.\n\n"
   "@return Index of the selected row.")
{
   return object->refresh();
}

DefineEngineMethod(GuiGameListMenuCtrl, addOptionRow, void,
   (const char* label, const char* options, bool wrapOptions, const char* callback, S32 icon, S32 yPad, bool enabled, const char* tooltip, const char* defaultValue),
   (-1, 0, true, "", ""),
   "Add a row to the list control.\n\n"
   "@param label The text to display on the row as a label.\n"
   "@param options A tab separated list of options.\n"
   "@param wrapOptions Specify true to allow options to wrap at each end or false to prevent wrapping.\n"
   "@param callback Name of a script function to use as a callback when this row is activated.\n"
   "@param icon [optional] Index of the icon to use as a marker.\n"
   "@param yPad [optional] An extra amount of height padding before the row. Does nothing on the first row.\n"
   "@param enabled [optional] If this row is initially enabled.")
{
   object->addRow(label, options, wrapOptions, callback, icon, yPad, enabled, tooltip, defaultValue);
}

DefineEngineMethod(GuiGameListMenuCtrl, addSliderRow, void,
(const char* label, F32 defaultValue, F32 increment, Point2F range, const char* callback, S32 icon, S32 yPad, bool enabled, const char* tooltip),
(-1, 0, true, ""),
"Add a row to the list control.\n\n"
"@param label The text to display on the row as a label.\n"
"@param options A tab separated list of options.\n"
"@param wrapOptions Specify true to allow options to wrap at each end or false to prevent wrapping.\n"
"@param callback Name of a script function to use as a callback when this row is activated.\n"
"@param icon [optional] Index of the icon to use as a marker.\n"
"@param yPad [optional] An extra amount of height padding before the row. Does nothing on the first row.\n"
"@param enabled [optional] If this row is initially enabled.")
{
   object->addRow(label, defaultValue, increment, range, callback, icon, yPad, enabled, tooltip);
}

DefineEngineMethod(GuiGameListMenuCtrl, addKeybindRow, void,
(const char* label, const char* bitmapName, const char* callback, S32 icon, S32 yPad, bool enabled, const char* tooltip),
(-1, 0, true, ""),
"Add a row to the list control.\n\n"
"@param label The text to display on the row as a label.\n"
"@param options A tab separated list of options.\n"
"@param wrapOptions Specify true to allow options to wrap at each end or false to prevent wrapping.\n"
"@param callback Name of a script function to use as a callback when this row is activated.\n"
"@param icon [optional] Index of the icon to use as a marker.\n"
"@param yPad [optional] An extra amount of height padding before the row. Does nothing on the first row.\n"
"@param enabled [optional] If this row is initially enabled.")
{
   object->addRow(label, bitmapName, callback, icon, yPad, enabled, tooltip);
}

DefineEngineMethod(GuiGameListMenuCtrl, removeRow, void, (S32 row),,
   "Removes the row at the provided index")
{
   object->removeRow(row);
}

DefineEngineMethod(GuiGameListMenuCtrl, getCurrentOption, const char*, (S32 row), ,
   "Gets the text for the currently selected option of the given row.\n\n"
   "@param row Index of the row to get the option from.\n"
   "@return A string representing the text currently displayed as the selected option on the given row. If there is no such displayed text then the empty string is returned.")
{
   return object->getCurrentOption(row);
}

DefineEngineMethod(GuiGameListMenuCtrl, getCurrentOptionKey, const char*, (S32 row), ,
   "Gets the key string for the currently selected option of the given row.\n\n"
   "@param row Index of the row to get the option from.\n"
   "@return The key (or id) that was assigned to the selected option on the given row. If there is no selected option then the empty string is returned.")
{
   return object->getCurrentOptionKey(row);
}

DefineEngineMethod(GuiGameListMenuCtrl, getCurrentOptionIndex, S32, (S32 row), ,
   "Gets the index into the option list for the currently selected option of the given row.\n\n"
   "@param row Index of the row to get the option from.\n"
   "@return The index of the selected option on the given row. If there is no selected option then -1 is returned.")
{
   return object->getCurrentOptionIndex(row);
}

DefineEngineMethod(GuiGameListMenuCtrl, selectOption, bool, (S32 row, const char* option), ,
   "Set the row's current option to the one specified\n\n"
   "@param row Index of the row to set an option on.\n"
   "@param option The option to be made active.\n"
   "@return True if the row contained the option and was set, false otherwise.")
{
   return object->selectOption(row, option);
}

DefineEngineMethod(GuiGameListMenuCtrl, selectOptionByKey, bool, (S32 row, const char* optionKey), ,
   "Set the row's current option to the one with the specified key.\n\n"
   "@param row Index of the row to set an option on.\n"
   "@param optionKey The key string that was assigned to the option to be made active.\n"
   "@return True if the row contained the key and the option and was set, false otherwise.")
{
   return object->selectOptionByKey(row, optionKey);
}

DefineEngineMethod(GuiGameListMenuCtrl, selectOptionByIndex, bool, (S32 row, S32 optionIndex), ,
   "Set the row's current option to the one at the specified index.\n\n"
   "@param row Index of the row to set an option on.\n"
   "@param optionIndex The index of the option to be made active.\n"
   "@return True if the index was valid and the option and was set, false otherwise.")
{
   return object->selectOptionByIndex(row, optionIndex);
}

DefineEngineMethod(GuiGameListMenuCtrl, setOptions, void, (S32 row, const char* optionsList), ,
   "Sets the list of options on the given row.\n\n"
   "@param row Index of the row to set options on."
   "@param optionsList A tab separated list of options for the control.")
{
   object->setOptions(row, optionsList);
}

DefineEngineMethod(GuiGameListMenuCtrl, addOption, void, (S32 row, const char* displayText, const char* keyText), (""),
   "Adds an option to the list of options on the given row.\n\n"
   "@param row Index of the row to add the option on.\n"
   "@param displayText The text to display for this option.\n"
   "@param keyText [Optional] The id string to associate with this value. "
   "If unset, the id will be the same as the display text.\n")
{
   object->addOption(row, displayText, keyText);
}

DefineEngineMethod(GuiGameListMenuCtrl, getValue, F32, (S32 row), ,
   "Sets the list of options on the given row.\n\n"
   "@param row Index of the row to set options on."
   "@param optionsList A tab separated list of options for the control.")
{
   return object->getValue(row);
}

DefineEngineMethod(GuiGameListMenuCtrl, setValue, void, (S32 row, F32 value), ,
   "Sets the list of options on the given row.\n\n"
   "@param row Index of the row to set options on."
   "@param optionsList A tab separated list of options for the control.")
{
   object->setValue(row, value);
}

DefineEngineMethod(GuiGameListMenuCtrl, getTooltip, const char*, (S32 row), ,
   "Sets the list of options on the given row.\n\n"
   "@param row Index of the row to set options on."
   "@param optionsList A tab separated list of options for the control.")
{
   return object->getTooltip(row);
}

//-----------------------------------------------------------------------------
// GuiGameListMenuProfile
//-----------------------------------------------------------------------------

GuiGameListMenuProfile::GuiGameListMenuProfile()
   : mHitAreaUpperLeft(0, 0),
   mHitAreaLowerRight(0, 0),
   mIconOffset(0, 0),
   mRowSize(0, 0),
   mRowScale(1.0f, 1.0f),
   mColumnSplit(0),
   mRightPad(0)
{
}

bool GuiGameListMenuProfile::onAdd()
{
   if (! Parent::onAdd())
   {
      return false;
   }

   // We can't call enforceConstraints() here because incRefCount initializes
   // some of the things to enforce. Do a basic sanity check here instead.
   if(mBitmapAsset.isNull())
   {
      Con::errorf( "GuiGameListMenuProfile: %s can't be created without a bitmap. Please add a 'Bitmap' property to the object definition.", getName() );
      return false;
   }
   
   if( mRowSize.x < 0 )
   {
      Con::errorf( "GuiGameListMenuProfile: %s can't have a negative row width. Please change the row width to be non-negative.", getName() );
      return false;
   }
   
   if( mRowSize.y < 0 )
   {
      Con::errorf( "GuiGameListMenuProfile: %s can't have a negative row height. Please change the row height to be non-negative.", getName() );
      return false;
   }

   return true;
}

void GuiGameListMenuProfile::enforceConstraints()
{
   if( getBitmapArrayRect(0).extent.isZero() )
      Con::errorf( "GuiGameListMenuCtrl: %s can't be created without a bitmap. Please add a bitmap to the profile's definition.", getName() );

   if( mRowSize.x < 0 )
      Con::errorf( "GuiGameListMenuProfile: %s can't have a negative row width. Please change the row width to be non-negative.", getName() );
   mRowSize.x = getMax(mRowSize.x, 0);

   if( mRowSize.y < 0 )
      Con::errorf( "GuiGameListMenuProfile: %s can't have a negative row height. Please change the row height to be non-negative.", getName() );
   mRowSize.y = getMax(mRowSize.y, 0);

   Point2I rowTexExtent = getBitmapArrayRect(TEX_NORMAL).extent;
   mRowScale.x = (float) getRowWidth() / rowTexExtent.x;
   mRowScale.y = (float) getRowHeight() / rowTexExtent.y;

   if (mHitAreaUpperLeft.x > mColumnSplit || mColumnSplit > mHitAreaLowerRight.x)
      Con::errorf("GuiGameListOptionsProfile: You can't create %s with a ColumnSplit outside the hit area. You set the split to %d. Please change the ColumnSplit to be in the range [%d, %d].",
         getName(), mColumnSplit, mHitAreaUpperLeft.x, mHitAreaLowerRight.x);

   mColumnSplit = mClamp(mColumnSplit, mHitAreaUpperLeft.x, mHitAreaLowerRight.x);
}

Point2I GuiGameListMenuProfile::getIconExtent()
{
   Point2I iconExtent = getBitmapArrayRect(TEX_FIRST_ICON).extent;

   // scale both by y to keep the aspect ratio
   iconExtent.x *= mRowScale.y;
   iconExtent.y *= mRowScale.y;

   return iconExtent;
}

Point2I GuiGameListMenuProfile::getArrowExtent()
{
   Point2I arrowExtent = getBitmapArrayRect(TEX_FIRST_ARROW).extent;

   // scale both by y to keep the aspect ratio
   arrowExtent.x *= mRowScale.y;
   arrowExtent.y *= mRowScale.y;

   return arrowExtent;
}

Point2I GuiGameListMenuProfile::getHitAreaExtent()
{
   if (mHitAreaLowerRight == mHitAreaUpperLeft)
   {
      return mRowSize;
   }
   else
   {
      return mHitAreaLowerRight - mHitAreaUpperLeft;
   }
}

//-----------------------------------------------------------------------------
// Console stuff (GuiGameListMenuProfile)
//-----------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(GuiGameListMenuProfile);

ConsoleDocClass( GuiGameListMenuProfile,
   "@brief A GuiControlProfile with additional fields specific to GuiGameListMenuCtrl.\n\n"

   "@tsexample\n"
   "new GuiGameListMenuProfile()\n"
   "{\n"
   "   hitAreaUpperLeft = \"10 2\";\n"
   "   hitAreaLowerRight = \"190 18\";\n"
   "   iconOffset = \"10 2\";\n"
   "   rowSize = \"200 20\";\n"
   "   columnSplit = \"100\";\n"
   "   rightPad = \"4\";\n"
   "   //Properties not specific to this control have been omitted from this example.\n"
   "};\n"
   "@endtsexample\n\n"

   "@ingroup GuiGame"
);

void GuiGameListMenuProfile::initPersistFields()
{
   docsURL;
   addField( "hitAreaUpperLeft", TypePoint2I, Offset(mHitAreaUpperLeft, GuiGameListMenuProfile),
      "Position of the upper left corner of the row hit area (relative to row's top left corner)" );

   addField( "hitAreaLowerRight", TypePoint2I, Offset(mHitAreaLowerRight, GuiGameListMenuProfile),
      "Position of the lower right corner of the row hit area (relative to row's top left corner)" );

   addField( "iconOffset", TypePoint2I, Offset(mIconOffset, GuiGameListMenuProfile),
      "Offset from the row's top left corner at which to render the row icon" );

   addField( "rowSize", TypePoint2I, Offset(mRowSize, GuiGameListMenuProfile),
      "The base size (\"width height\") of a row" );

   addField("columnSplit", TypeS32, Offset(mColumnSplit, GuiGameListMenuProfile),
      "Padding between the leftmost edge of the control, and the row's left arrow.");

   addField("rightPad", TypeS32, Offset(mRightPad, GuiGameListMenuProfile),
      "Padding between the rightmost edge of the control and the row's right arrow.");

   Parent::initPersistFields();

   removeField("tab");
   removeField("mouseOverSelected");

   removeField("modal");
   removeField("opaque");
   removeField("border");
   removeField("borderThickness");
   removeField("borderColor");
   removeField("borderColorHL");
   removeField("borderColorNA");

   removeField("bevelColorHL");
   removeField("bevelColorLL");

   removeField("fontColorLink");
   removeField("fontColorLinkHL");

   removeField("justify");
   removeField("returnTab");
   removeField("numbersOnly");
   removeField("cursorColor");

   removeField("profileForChildren");
}
