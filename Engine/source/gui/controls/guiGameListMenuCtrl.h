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

#ifndef _GuiGameListMenuCtrl_H_
#define _GuiGameListMenuCtrl_H_

#include "gui/core/guiControl.h"
#include "gui/controls/guiBitmapCtrl.h"

class GuiGameListMenuProfile;

/// \class GuiGameListMenuCtrl
/// A base class for cross platform menu controls that are gamepad friendly.
class GuiGameListMenuCtrl : public GuiControl
{
public:
   typedef GuiControl Parent;
   typedef GuiGameListMenuProfile Profile;

protected:

   /// \struct OptionEntry
   /// Display text and ID key for each entry in an option row.
   struct OptionEntry
   {
      StringTableEntry mDisplayText;   ///< The text that is displayed for the option
      StringTableEntry mKeyString;     ///< Key value that is associated with this option
      OptionEntry() : mDisplayText(StringTable->EmptyString()), mKeyString(StringTable->EmptyString()) {}
      virtual ~OptionEntry() {}
   };


   /// \struct Row
   /// Internal data representation of a single row in the control.
   struct Row
   {
      StringTableEntry mLabel;            ///< Text to display in the row as a label
      StringTableEntry mScriptCallback;   ///< Script callback when row is activated
      StringTableEntry mTooltip;          ///< A descriptive tooltip message for what the row is
      S32 mIconIndex;                     ///< Index of the icon to display on the row (-1 = no icon)
      S32 mHeightPad;                     ///< Extra amount to pad above this row
      bool mUseHighlightIcon;             ///< Toggle the use of the highlight icon
      bool mEnabled;                      ///< If this row is enabled or not (grayed out)

      enum Mode
      {
         Default = 0,
         OptionList,
         Slider,
         Keybind
      };

      Mode mMode;

      //List options
      Vector<OptionEntry>        mOptions;         ///< Collection of options available to display
      S32                        mSelectedOption;  ///< Index into mOptions pointing at the selected option
      bool                       mWrapOptions;     ///< Determines if options should "wrap around" at the ends

      //Slider option
      F32                        mValue;           ///< When working as a slider, this contains the value
      F32                        mStepSize;        ///< When working as a slider, this is the increment levels in the range
      Point2F                    mRange;           ///< When working as a slider, this sets our min/max range

      //Keybind option
      StringTableEntry           mBitmap;
      GFXTexHandle               mBitmapTex;

      Row() : mLabel(StringTable->EmptyString()), mScriptCallback(StringTable->EmptyString()), mTooltip(StringTable->EmptyString()), mIconIndex(-1), mHeightPad(0), mUseHighlightIcon(false), mEnabled(true),
         mSelectedOption(0), mWrapOptions(false), mMode(Mode::Default), mValue(0), mStepSize(1), mRange(Point2F(0, 1)), mBitmap(StringTable->EmptyString()), mBitmapTex(nullptr)
      {
         VECTOR_SET_ASSOCIATION(mOptions);
      }

      virtual ~Row() {}
   };

public:
   /// \return The index of the highlighted row or NO_ROW if none of the rows
   /// are currently highlighted.
   virtual S32 getHighlighted() const { return mHighlighted; }

   /// \return The index of the selected row or NO_ROW if none of the rows are
   /// currently selected.
   virtual S32 getSelected() const { return mSelected; }

   /// Sets the selected row. Only rows that are enabled can be selected. Input is
   /// clamped to [0, mRows.size())
   ///
   /// \param index The index to set as selected.
   virtual void setSelected(S32 index);

   /// Determines if the specified row is enabled or disabled.
   ///
   /// \param index Index of the row to check.
   /// \return True if the specified row is enabled. False if the row is not
   /// enabled or the given index was not valid.
   virtual bool isRowEnabled(S32 index) const;

   /// Sets a row's enabled status according to the given parameters.
   ///
   /// \param index The row to set the enabled status of.
   /// \param enabled Indicate true to enable the row or false to disable it.
   virtual void setRowEnabled(S32 index, bool enabled);

   /// Gets the label displayed on the specified row.
   ///
   /// \param rowIndex Index of the row to get the label of.
   /// \return The label for the row.
   virtual StringTableEntry getRowLabel(S32 rowIndex) const;

   /// Sets the label on the given row.
   ///
   /// \param rowIndex Index of the row to set the label on.
   /// \param label Text to set as the label of the row.
   virtual void setRowLabel(S32 rowIndex, const char * label);

   /// Adds a row to the control.
   ///
   /// \param label The text to display on the row as a label.
   /// \param callback Name of a script function to use as a callback when this
   /// row is activated.
   /// \param icon [optional] Index of the icon to use as a marker. Default -1
   /// means no icon will be shown on this row.
   /// \param yPad [optional] An extra amount of height padding before the row.
   /// \param enabled [optional] If this row is initially enabled. Default true.
   virtual void addRow(const char* label, const char* callback, S32 icon = -1, S32 yPad = 0, bool useHighlightIcon = true, bool enabled = true, S32 mode = 0, const char* tooltip = "");

   /// Adds a row to the control.
   ///
   /// \param label The text to display on the row as a label.
   /// \param optionsList A tab separated list of options for the control.
   /// \param wrapOptions Specify true to allow options to wrap at the ends or
   /// false to prevent wrapping.
   /// \param callback [optional] Name of a script function to use as a callback
   /// when this row is activated. Default NULL means no callback.
   /// \param icon [optional] Index of the icon to use as a marker. Default -1
   /// means no icon will be shown on this row.
   /// \param yPad [optional] An extra amount of height padding before the row.
   /// \param enabled [optional] If this row is initially enabled. Default true.
   void addRow(const char* label, const char* optionsList, bool wrapOptions, const char* callback, S32 icon, S32 yPad, bool enabled, const char* tooltip = "", const char* defaultValue = "");

   /// Adds a row to the control.
   ///
   /// \param label The text to display on the row as a label.
   /// \param defaultValue A float indicating the slider's default value
   /// \param increments A float indicating the incremental values the slider snaps along between it's range
   /// \param range A Point2F that indicates the minimum and maximum value range
   /// \param callback [optional] Name of a script function to use as a callback
   /// when this row is activated. Default NULL means no callback.
   /// \param icon [optional] Index of the icon to use as a marker. Default -1
   /// means no icon will be shown on this row.
   /// \param yPad [optional] An extra amount of height padding before the row.
   /// \param enabled [optional] If this row is initially enabled. Default true.
   void addRow(const char* label, F32 defaultValue, F32 increments, Point2F range, const char* callback, S32 icon, S32 yPad, bool enabled, const char* tooltip = "");

   void addRow(const char* label, const char* bitmapName, const char* callback, S32 icon, S32 yPad, bool enabled, const char* tooltip);

   //Removes row at the provided index
   void removeRow(const S32& row);

   /// Gets the text for the currently selected option of the given row.
   ///
   /// \param rowIndex Index of the row to get the option from.
   /// \return A string representing the text currently displayed as the selected
   /// option on the given row. If there is no such displayed text then the empty
   /// string is returned.
   StringTableEntry getCurrentOption(S32 rowIndex) const;

   /// Gets the key string for the currently selected option of the given row
   ///
   /// \param rowIndex Index of the row to get the option from.
   /// \return The key (or id) that was assigned to the selected option on the
   ///  given row. If there is no selected option then the empty string is returned.
   StringTableEntry getCurrentOptionKey(S32 rowIndex) const;

   /// Gets the index into the option list for the currently selected option of the given row.
   ///
   /// \param rowIndex Index of the row to get the option from.
   /// \return The index of the selected option on the given row. If there is no
   /// selected option then -1 is returned.
   S32 getCurrentOptionIndex(S32 rowIndex) const;

   /// Attempts to set the given row to the specified selected option. The option
   /// will only be set if the option exists in the control.
   ///
   /// \param rowIndex Index of the row to set an option on.
   /// \param option The option to be made active.
   /// \return True if the row contained the option and was set, false otherwise.
   bool selectOption(S32 rowIndex, const char* option);

   /// Attempts to set the given row to the option with the specified key. The
   /// option will only be set if the key exists in the control.
   ///
   /// \param rowIndex Index of the row to set an option on.
   /// \param optionKey The key string that was assigned to the option to be made active.
   /// \return True if the row contained the key and the option and was set, false otherwise.
   bool selectOptionByKey(S32 rowIndex, const char* optionKey);

   /// Attempts to set the given row to the option at the specified index. The option
   /// will only be set if the index is valid.
   ///
   /// \param rowIndex Index of the row to set an option on.
   /// \param optionIndex The index of the option to be made active.
   /// \return True if the index was valid and the option and was set, false otherwise.
   bool selectOptionByIndex(S32 rowIndex, S32 optionIndex);

   /// Sets the list of options on the given row.
   ///
   /// \param rowIndex Index of the row to set options on.
   /// \param optionsList A tab separated list of options for the control.
   void setOptions(S32 rowIndex, const char* optionsList);

   /// Adds an option to the list of options on the given row.
   ///
   /// \param rowIndex Index of the row to set options on.
   /// \param displayText The text to display for this option.
   /// \param keyText The id string to associate with this value. If NULL the
   ///  id will be the same as the display text.
   void addOption(S32 rowIndex, const char* displayText, const char* keyText);

   /// Activates the current row. The script callback of  the current row will
   /// be called (if it has one).
   virtual void activateRow();

   /// Gets the number of rows in the control.
   ///
   /// \return The number of rows in this control.
   virtual S32 getRowCount() const { return mRows.size(); }

   /// Gets the value of a row
   ///
   /// \param rowIndex Index of the row to get the value of.
   F32 getValue(S32 rowIndex);

   /// Sets the value of a row
   ///
   /// \param rowIndex Index of the row to set the value of.
   /// \param value The new value to be set.
   void setValue(S32 rowIndex, F32 value);

   /// Gets the tooltip of a row
   ///
   /// \param rowIndex Index of the row to get the tooltip of.
   const char* getTooltip(S32 rowIndex);

   GuiGameListMenuCtrl();
   ~GuiGameListMenuCtrl();

   void onRender(Point2I offset, const RectI &updateRect);

   void onRenderListOption(Row* row, Point2I currentOffset);
   void onRenderSliderOption(Row* row, Point2I currentOffset);

   void onRenderKeybindOption(Row* row, Point2I currentOffset);

   /// Callback when the object is registered with the sim.
   ///
   /// \return True if the profile was successfully added, false otherwise.
   bool onAdd();

   /// Callback when the control wakes up.
   bool onWake();

   /// Callback when a key is pressed.
   ///
   /// \param event The event that triggered this callback.
   bool onKeyDown(const GuiEvent &event);

   /// Callback when a key is repeating.
   ///
   /// \param event The event that triggered this callback.
   bool onKeyRepeat(const GuiEvent &event){ return onKeyDown(event); }

   /// Callback when the mouse button is clicked on the control.
   ///
   /// \param event A reference to the event that triggered the callback.
   void onMouseDown(const GuiEvent &event);

   /// Callback when the mouse is dragged on the control.
   ///
   /// \param event A reference to the event that triggered the callback.
   void onMouseDragged(const GuiEvent &event){ onMouseDown(event); }

   /// Callback when the mouse leaves the control.
   ///
   /// \param event A reference to the event that triggered the callback.
   void onMouseLeave(const GuiEvent &event);

   /// Callback when the mouse is moving over this control
   ///
   /// \param event A reference to the event that triggered the callback.
   void onMouseMove(const GuiEvent &event);

   /// Callback when the mouse button is released.
   ///
   /// \param event A reference to the event that triggered the callback.
   void onMouseUp(const GuiEvent &event);

   virtual bool onInputEvent(const InputEventInfo& event);

   /// Callback when the gamepad axis is activated.
   ///
   /// \param event A reference to the event that triggered the callback.
   virtual bool onGamepadAxisUp(const GuiEvent & event);

   /// Callback when the gamepad axis is activated.
   ///
   /// \param event A reference to the event that triggered the callback.
   virtual bool onGamepadAxisDown(const GuiEvent & event);

   /// Callback when the gamepad axis is activated.
   ///
   /// \param event A reference to the event that triggered the callback.
   virtual bool onGamepadAxisLeft(const GuiEvent& event);

   /// Callback when the gamepad axis is activated.
   ///
   /// \param event A reference to the event that triggered the callback.
   virtual bool onGamepadAxisRight(const GuiEvent& event);

   void clearRows();

   void refresh();

   RectI getRowBounds(S32 rowIndex);

   DECLARE_CONOBJECT(GuiGameListMenuCtrl);
   DECLARE_CATEGORY( "Gui Game" );
   DECLARE_DESCRIPTION( "Base class for cross platform menu controls that are gamepad friendly." );

   /// Initializes fields accessible through the console.
   static void initPersistFields();

   static const S32 NO_ROW          = -1; ///< Indicates a query result of no row found.
   static const S32 NO_ICON         = -1; ///< Indicates a row has no extra icon available
   static const S32 NO_OPTION = -1; ///< Indicates there is no option

protected:
   /// Adds a row to the control.
   ///
   /// \param row A reference to the row object to fill.
   /// \param label The text to display on the row as a label.
   /// \param callback Name of a script function to use as a callback when this
   /// row is activated.
   /// \param icon [optional] Index of the icon to use as a marker. Default -1
   /// means no icon will be shown on this row.
   /// \param yPad [optional] An extra amount of height padding before the row.
   /// \param enabled [optional] If this row is initially enabled. Default true.
   virtual void addRow(Row * row, const char* label, const char* callback, S32 icon, S32 yPad, bool useHighlightIcon, bool enabled, S32 mode = 0, const char* tooltip = "");

   /// Determines if the given index is a valid row index. Any index pointing at
   /// an existing row is valid.
   ///
   /// \param index The index to check for validity.
   /// \return True if the index points at a valid row, false otherwise.
   virtual bool isValidRowIndex(S32 index) const;

   /// Sets the script variable $ThisControl to reflect this control.
   virtual void setThisControl();

   /// Called to implement debug rendering which displays colored lines to
   /// provide visual feedback on extents and hit zones.
   virtual void onDebugRender(Point2I offset);

   /// Looks up the row having a hit area at the given global point.
   ///
   /// \param globalPoint The point we want to check for hitting a row.
   /// \return The index of the hit row or NO_ROW if no row was hit.
   virtual S32 getRow(Point2I globalPoint);

   /// Checks to make sure our control has a profile of the correct type.
   ///
   /// \return True if the profile is of type GuiGameListMenuProfile or false if
   /// the profile is of any other type.
   virtual bool hasValidProfile() const;

   /// Enforces the validity of the fields on this control and its profile (if
   /// the profile is valid, see: hasValidProfile).
   virtual void enforceConstraints();

   /// @name Callbacks
   /// @{
   DECLARE_CALLBACK( void, onChange, () );

   DECLARE_CALLBACK(void, onInputEvent,  (const char* device, const char* action, bool state));

   DECLARE_CALLBACK(void, onAxisEvent, (const char* device, const char* action, F32 axisValue));
   /// @}

   /// Evaluates some script. If the command is empty then nothing is evaluated.
   ///
   /// \param command The script to evaluate.
   void doScriptCommand(StringTableEntry command);

   StringTableEntry  mCallbackOnA;  ///< Script callback when the 'A' button is pressed
   StringTableEntry  mCallbackOnB;  ///< Script callback when the 'B' button is pressed
   StringTableEntry  mCallbackOnX;  ///< Script callback when the 'X' button is pressed
   StringTableEntry  mCallbackOnY;  ///< Script callback when the 'Y' button is pressed

   bool              mDebugRender;  ///< Determines when to show debug render lines
   Vector<Row *>     mRows;         ///< Holds data wrappers on all the rows we have

private:
   /// Performs a click on the current option row. The x position is used to
   /// determine if the left or right arrow were clicked. If one was clicked, the
   /// option will be changed. If neither was clicked, the option is unaffected.
   /// This method should only be called when there is an actively selected row.
   ///
   /// \param row The row to perform the click on.
   /// \param xPos The x position of the the click, relative to the control.
   void clickOption(Row* row, S32 xPos);

   /// Changes the option on the currently selected row. If there is no row
   /// selected, this method does nothing.
   ///
   /// \param delta The amount to change the option selection by. Typically this
   /// will be 1 or -1.
   void changeOption(S32 delta);

   /// Changes the option on the given row.
   ///
   /// \param row The row to change the option on.
   /// \param delta The amount to change the option selection by. Typically this
   /// will be 1 or -1.
   void changeOption(Row* row, S32 delta);

   /// Performs a click on the current slider row. The x position is used to
   /// determine if the left or right arrow were clicked, or if it landed somewhere on the sliderbar.
   /// If one was clicked, the option will be changed. If neither was clicked, the option is unaffected.
   /// This method should only be called when there is an actively selected row.
   ///
   /// \param row The row to perform the click on.
   /// \param xPos The x position of the the click, relative to the control.
   void clickSlider(Row* row, S32 xPos);

   void clickKeybind(Row* row, S32 xPos);

private:
   /// Recalculates the height of this control based on the stored row height and
   /// and padding on the rows.
   virtual Point2I getMinExtent() const;

   /// Makes sure the height will allow all rows to be displayed without being
   /// truncated.
   void updateHeight();

   /// Sets the first enabled row as selected. If there are no enabled rows then
   /// selected will be set to NO_ROW.
   void selectFirstEnabledRow();

   /// Changes the currently selected row.
   ///
   /// \param delta The amount to change the row selection by. Typically this will
   /// be 1 or -1.
   void changeRow(S32 delta);

   S32      mSelected;     ///< index of the currently selected row
   S32      mHighlighted;  ///< index of the currently highlighted row

   bool     mCallbackOnInputs;
   bool     mConsumeKeyInputEvents;
};

/// \class GuiGameListMenuProfile
/// A gui profile with additional fields specific to GuiGameListMenuCtrl.
class GuiGameListMenuProfile : public GuiControlProfile
{
   typedef GuiControlProfile Parent;

public:
   /// Enforces range constraints on all required fields.
   virtual void enforceConstraints();

   /// Get the height of rows in this profile. All rows are considered to be the
   /// same base height. Rows can have an extra amount of y padding defined when
   /// they are added to the control.
   ///
   /// \return The height of rows in this profile.
   S32 getRowHeight() { return (mRowSize.y) ? mRowSize.y : getBitmapArrayRect(TEX_NORMAL).extent.y; }

   /// Get the width of rows in this profile. All rows are considered to be the
   /// same width.
   ///
   /// \return The width of rows in this profile.
   S32 getRowWidth() { return (mRowSize.x) ? mRowSize.x : getBitmapArrayRect(TEX_NORMAL).extent.x; }

   /// Row scale is the ratio between the defined row size and the raw size of
   /// the bitmap.
   ///
   /// \return The row scale.
   const Point2F & getRowScale() const { return mRowScale; }

   /// Gets the extent of icons for this profile. If there are no icons you will
   /// get a point of (0, 0);
   ///
   /// \return The extent of icons or (0, 0) if there aren't any.
   Point2I getIconExtent();

   /// Gets the extent of arrows for this profile. If there are no arrows you
   /// will get a point of (0, 0).
   ///
   /// \return The extent of icons or (0, 0) if there aren't any.
   Point2I getArrowExtent();

   /// Gets the extent of the defined hit area for this profile. If the hit area
   /// is not defined then it defaults to the full size of a row.
   ///
   /// \return The extents of the defined hit area or the full size of the row.
   Point2I getHitAreaExtent();

   /// Determines if this profile has textures for the left and right arrows.
   ///
   /// \return True if the profile's bitmap has textures for the arrows, false
   /// otherwise.
   bool hasArrows(){ return (! getBitmapArrayRect(TEX_FIRST_ARROW).extent.isZero()); }

   /// Callback when the object is registered with the sim.
   ///
   /// \return True if the profile was successfully added, false otherwise.
   bool onAdd();

   Point2I  mHitAreaUpperLeft;   ///< Offset for the upper left corner of the hit area
   Point2I  mHitAreaLowerRight;  ///< Offset for the lower right corner of the hit area
   Point2I  mIconOffset;         ///< Offset for a row's extra icon
   Point2I  mRowSize;            ///< The base size of a row

   S32   mColumnSplit;  ///< Absolute position of the split between columns
   S32   mRightPad;     ///< Extra padding between the right arrow and the hit area

   GuiGameListMenuProfile();

   DECLARE_CONOBJECT(GuiGameListMenuProfile);

   /// Initializes fields accessible through the console.
   static void initPersistFields();
   
   enum 
   {
      TEX_NORMAL      = 0,  ///< texture index for a normal, unselected row
      TEX_SELECTED    = 1,  ///< texture index for a selected row
      TEX_HIGHLIGHT   = 2,  ///< texture index for a highlighted row (moused over, not selected)
      TEX_DISABLED    = 3,  ///< texture index for a disabled row
      TEX_L_ARROW_OFF = 4,  ///< texture index for the left arrow of an unselected row
      TEX_L_ARROW_ON  = 5,  ///< texture index for the left arrow of a selected row
      TEX_R_ARROW_OFF = 6,  ///< texture index for the right arrow of an unselected row
      TEX_R_ARROW_ON  = 7,  ///< texture index for the right arrow of a selected row

      TEX_FIRST_ARROW = 4,  ///< texture index for the first arrow
      TEX_FIRST_ICON  = 8,  ///< texture index for the first row marker icon
   };

private:
   Point2F  mRowScale;           ///< Ratio of row size to actual bitmap size
};

#endif
