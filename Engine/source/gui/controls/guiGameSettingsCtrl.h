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

#ifndef _GuiGameSettingsCtrl_H_
#define _GuiGameSettingsCtrl_H_

#include "gui/buttons/guiButtonCtrl.h"
#include "T3D/assets/ImageAsset.h"

/// \class GuiGameSettingsCtrl
/// A base class for cross platform menu controls that are gamepad friendly.
class GuiGameSettingsCtrl : public GuiButtonCtrl
{
public:
   typedef GuiButtonCtrl Parent;

   enum Mode
   {
      Default = 0,
      OptionList,
      Slider,
      Keybind,
      Text
   };

protected:

   /// \struct OptionEntry
   /// Display text and ID key for each entry in an option.
   struct OptionEntry
   {
      StringTableEntry mDisplayText;   ///< The text that is displayed for the option
      StringTableEntry mKeyString;     ///< Key value that is associated with this option
      OptionEntry() : mDisplayText(StringTable->EmptyString()), mKeyString(StringTable->EmptyString()) {}
      virtual ~OptionEntry() {}
   };


   StringTableEntry mLabel;            ///< Text to display in the control as a label
   StringTableEntry mScriptCallback;   ///< Script callback when control is activated
   StringTableEntry mTooltip;          ///< A descriptive tooltip message for what the control is

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
   DECLARE_IMAGEASSET(GuiGameSettingsCtrl, KeybindBitmap, changeBitmap, GFXDefaultGUIProfile);
   DECLARE_ASSET_SETGET(GuiGameSettingsCtrl, KeybindBitmap);

   DECLARE_IMAGEASSET(GuiGameSettingsCtrl, PreviousBitmap, changeBitmap, GFXDefaultGUIProfile);
   DECLARE_ASSET_SETGET(GuiGameSettingsCtrl, PreviousBitmap);

   DECLARE_IMAGEASSET(GuiGameSettingsCtrl, NextBitmap, changeBitmap, GFXDefaultGUIProfile);
   DECLARE_ASSET_SETGET(GuiGameSettingsCtrl, NextBitmap);

   S32 mArrowSize;
   S32 mColumnSplit; //Padding between the leftmost edge of the control, and the left side of the 'option'.
   S32 mRightPad;

   bool mEnabled;
   bool mSelected;

public:
   void changeBitmap() {}

   /// Sets the control as selected . Only controls that are enabled can be selected. 
   virtual void setSelected();

   /// Determines if the specified control is enabled or disabled.
   ///
   /// \return True if the specified control is enabled. False if the control is not
   /// enabled
   virtual bool isEnabled() const;

   /// Sets a control's enabled status according to the given parameters.
   ///
   /// \param enabled Indicate true to enable the control or false to disable it.
   virtual void setEnabled(bool enabled);

   /// Gets the label displayed on the control.
   ///
   /// \return The label for the control.
   virtual StringTableEntry getLabel() const;

   /// Sets the label on the control.
   ///
   /// \param label Text to set as the label.
   virtual void setLabel(const char * label);

   /// Sets the control to a List setting.
   ///
   /// \param label The text to display on the control as a label.
   /// \param optionsList A tab separated list of options for the control.
   /// \param wrapOptions Specify true to allow options to wrap at the ends or
   /// false to prevent wrapping.
   /// \param callback [optional] Name of a script function to use as a callback
   /// when this control is activated. Default NULL means no callback.
   /// \param enabled [optional] If this control is initially enabled. Default true.
   void setListSetting(const char* label, const char* optionsList, bool wrapOptions, const char* callback,bool enabled, const char* tooltip = "", const char* defaultValue = "");

   /// Sets the control to a Slider setting
   ///
   /// \param label The text to display on the control as a label.
   /// \param defaultValue A float indicating the slider's default value
   /// \param increments A float indicating the incremental values the slider snaps along between it's range
   /// \param range A Point2F that indicates the minimum and maximum value range
   /// \param callback [optional] Name of a script function to use as a callback
   /// when this control is activated. Default NULL means no callback.
   /// \param enabled [optional] If this control is initially enabled. Default true.
   void setSliderSetting(const char* label, F32 defaultValue, F32 increments, Point2F range, const char* callback, bool enabled, const char* tooltip = "");

   /// Sets the control to a Keybind setting
   ///
   /// \param label The text to display on the control as a label.
   /// \param bitmapAssetId The assetId for the button display image
   /// \param range A Point2F that indicates the minimum and maximum value range
   /// \param callback [optional] Name of a script function to use as a callback
   /// when this control is activated. Default NULL means no callback.
   /// \param enabled [optional] If this control is initially enabled. Default true.
   void setKeybindSetting(const char* label, const char* bitmapAssetId, const char* callback, bool enabled, const char* tooltip);

   /// Gets the text for the currently selected option of the control.
   ///
   /// \return A string representing the text currently displayed as the selected
   /// option on the control. If there is no such displayed text then the empty
   /// string is returned.
   StringTableEntry getCurrentOption() const;

   /// Gets the key string for the currently selected option of the control
   ///
   /// \return The key (or id) that was assigned to the selected option on the
   ///  control. If there is no selected option then the empty string is returned.
   StringTableEntry getCurrentOptionKey() const;

   /// Gets the index into the option list for the currently selected option of the control.
   ///
   /// \return The index of the selected option on the control. If there is no
   /// selected option then -1 is returned.
   S32 getCurrentOptionIndex() const;

   /// Attempts to set the control to the specified selected option. The option
   /// will only be set if the option exists in the control.
   ///
   /// \param option The option to be made active.
   /// \return True if the control contained the option and was set, false otherwise.
   bool selectOption(const char* option);

   /// Attempts to set the control to the option with the specified key. The
   /// option will only be set if the key exists in the control.
   ///
   /// \param optionKey The key string that was assigned to the option to be made active.
   /// \return True if the control contained the key and the option and was set, false otherwise.
   bool selectOptionByKey(const char* optionKey);

   /// Attempts to set the control to the option at the specified index. The option
   /// will only be set if the index is valid.
   ///
   /// \param optionIndex The index of the option to be made active.
   /// \return True if the index was valid and the option and was set, false otherwise.
   bool selectOptionByIndex(S32 optionIndex);

   /// Sets the list of options on the control.
   ///
   /// \param optionsList A tab separated list of options for the control.
   void setOptions(const char* optionsList);

   /// Adds an option to the list of options on the control.
   ///
   /// \param displayText The text to display for this option.
   /// \param keyText The id string to associate with this value. If NULL the
   ///  id will be the same as the display text.
   void addOption(const char* displayText, const char* keyText);

   /// Activates the control. The script callback of the control will
   /// be called (if it has one).
   virtual void activate();

   /// Gets the value
   ///
   F32 getValue();

   /// Sets the value
   ///
   /// \param value The new value to be set.
   void setValue(F32 value);

   Mode getMode() { return mMode; }

   /// <summary>
   /// Gets the incremenet amount
   /// </summary>
   F32 getIncrement();

   /// <summary>
   /// Gets range of values allowed
   /// </summary>
   Point2F getRange();

   /// Gets the tooltip
   const char* getTooltip();

   GuiGameSettingsCtrl();
   ~GuiGameSettingsCtrl();

   void onRender(Point2I offset, const RectI &updateRect);

   void onRenderListOption(Point2I currentOffset);
   void onRenderSliderOption(Point2I currentOffset);

   void onRenderKeybindOption(Point2I currentOffset);

   /// Callback when the object is registered with the sim.
   ///
   /// \return True if the profile was successfully added, false otherwise.
   bool onAdd();

   /// Callback when the control wakes up.
   bool onWake();

   void clear();

   virtual void onMouseMove(const GuiEvent& event);
   virtual void onMouseUp(const GuiEvent& event);

   DECLARE_CONOBJECT(GuiGameSettingsCtrl);
   DECLARE_CATEGORY( "Gui Game" );
   DECLARE_DESCRIPTION( "Base class for cross platform menu controls that are gamepad friendly." );

   /// Initializes fields accessible through the console.
   static void initPersistFields();

   static const S32 NO_OPTION = -1; ///< Indicates there is no option

protected:
   /// Sets up the option
   ///
   /// \param label The text to display on the control as a label.
   /// \param callback Name of a script function to use as a callback when this
   /// control is activated.
   /// \param enabled [optional] If this control is initially enabled. Default true.
   virtual void set(const char* label, const char* callback, bool useHighlightIcon = true, bool enabled = true, S32 mode = 0, const char* tooltip = "");

   /// Sets the script variable $ThisControl to reflect this control.
   virtual void setThisControl();

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

private:
   /// Performs a click on the current option. The x position is used to
   /// determine if the left or right arrow were clicked. If one was clicked, the
   /// option will be changed. If neither was clicked, the option is unaffected.
   /// This method should only be called when there is an actively selected control.
   ///
   /// \param xPos The x position of the the click, relative to the control.
   void clickOption(S32 xPos);

   /// Changes the option on the currently selected control.
   ///
   /// \param delta The amount to change the option selection by. Typically this
   /// will be 1 or -1.
   void changeOption(S32 delta);

   /// Performs a click on the current slider control. The x position is used to
   /// determine if the left or right arrow were clicked, or if it landed somewhere on the sliderbar.
   /// If one was clicked, the option will be changed. If neither was clicked, the option is unaffected.
   /// This method should only be called when there is an actively selected control.
   ///
   /// \param xPos The x position of the the click, relative to the control.
   void clickSlider(S32 xPos);

   void clickKeybind(S32 xPos);

private:
   bool     mCallbackOnInputs;
   bool     mConsumeKeyInputEvents;
};

#endif
