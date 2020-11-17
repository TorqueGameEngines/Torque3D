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

// --------------------------------------------------------------------
// Message Sound
// --------------------------------------------------------------------
/*new SFXDescription(MessageBoxAudioDescription)
{
   volume      = 1.0;
   isLooping   = false;
   is3D        = false;
   channel     = $GuiAudioType;
};

new SFXProfile(messageBoxBeep)
{
   filename    = "./messageBoxSound";
   description = MessageBoxAudioDescription;
   preload     = true;
};*/

//---------------------------------------------------------------------------------------------
// messageCallback
// Calls a callback passed to a message box.
//---------------------------------------------------------------------------------------------
function messageCallback(%dlg, %callback)
{
   Canvas.popDialog(%dlg);
   eval(%callback);
}

//---------------------------------------------------------------------------------------------
// MBSetText
// Sets the text of a message box and resizes it to accomodate the new string.
//---------------------------------------------------------------------------------------------
function MBSetText(%text, %frame, %msg)
{
   // Get the extent of the text box.
   %ext = %text.getExtent();
   // Set the text in the center of the text box.
   %text.setText("<just:center>" @ %msg);
   // Force the textbox to resize itself vertically.
   %text.forceReflow();
   // Grab the new extent of the text box.
   %newExtent = %text.getExtent();

   // Get the vertical change in extent.
   %deltaY = getWord(%newExtent, 1) - getWord(%ext, 1);
   
   // Resize the window housing the text box.
   %windowPos = %frame.getPosition();
   %windowExt = %frame.getExtent();
   %frame.resize(getWord(%windowPos, 0), getWord(%windowPos, 1) - (%deltaY / 2),
                 getWord(%windowExt, 0), getWord(%windowExt, 1) + %deltaY);
                 
   %frame.canMove = "0";
   //%frame.canClose = "0";
   %frame.resizeWidth = "0";
   %frame.resizeHeight = "0";
   %frame.canMinimize = "0";
   %frame.canMaximize = "0";
   
   //sfxPlayOnce( messageBoxBeep );
}

function MessageBoxCtrl::onWake(%this)
{
}

//---------------------------------------------------------------------------------------------
// Various message box display functions. Each one takes a window title, a message, and a
// callback for each button.
//---------------------------------------------------------------------------------------------

//MessageBoxOK("Test", "This is a test message box", "echo(\"Uhhhhhawhat?\"");
function MessageBoxOK(%title, %message, %callback)
{
   Canvas.pushDialog(MessageBoxDlg);
   MessageBoxTitleText.text = %title;
   
   MessageBoxOCButtonHolder.hidden = true;
   MessageBoxYNCButtonHolder.hidden = true;
   MessageBoxOKButtonHolder.hidden = false;
   
   MessageBoxOKButtonHolder-->OKButton.set("btn_a", "Return", "OK", "MessageCallback(MessageBoxDlg,MessageBoxDlg.callback);");
   
   MessageBoxCtrl.originalMenuInputContainer = $activeMenuButtonContainer;
   MessageBoxOKButtonHolder.setActive();
   
   MBSetText(MessageBoxText, MessageBoxCtrl, %message);
   MessageBoxDlg.callback = %callback;
}

function MessageBoxOKDlg::onSleep( %this )
{
   %this.callback = "";
   MessageBoxCtrl.originalMenuInputContainer.setActive();
}

function MessageBoxOKCancel(%title, %message, %callback, %cancelCallback)
{
   Canvas.pushDialog(MessageBoxDlg);
   MessageBoxTitleText.text = %title;
   
   MessageBoxOCButtonHolder.hidden = false;
   MessageBoxYNCButtonHolder.hidden = true;
   MessageBoxOKButtonHolder.hidden = true;
   
   MessageBoxOCButtonHolder-->OKButton.set("btn_a", "Return", "OK", "MessageCallback(MessageBoxDlg,MessageBoxDlg.callback);");
   MessageBoxOCButtonHolder-->CancelButton.set("btn_b", "Escape", "Cancel", "MessageCallback(MessageBoxDlg,MessageBoxDlg.cancelCallback);");

   MessageBoxCtrl.originalMenuInputContainer = $activeMenuButtonContainer;
   MessageBoxOCButtonHolder.setActive();
   
   MBSetText(MessageBoxText, MessageBoxCtrl, %message);
   MessageBoxDlg.callback = %callback;
   MessageBoxDlg.cancelCallback = %cancelCallback;
}

function MessageBoxOKCancelDlg::onSleep( %this )
{
   %this.callback = "";
   MessageBoxCtrl.originalMenuInputContainer.setActive();
}

function MessageBoxOKCancelDetails(%title, %message, %details, %callback, %cancelCallback)
{   
   if(%details $= "")
   {
      MBOKCancelDetailsButton.setVisible(false);
   }
   
   MBOKCancelDetailsScroll.setVisible(false);
   
   MBOKCancelDetailsFrame.setText( %title );
   
   Canvas.pushDialog(MessageBoxOKCancelDetailsDlg);
   MBSetText(MBOKCancelDetailsText, MBOKCancelDetailsFrame, %message);
   MBOKCancelDetailsInfoText.setText(%details);
   
   %textExtent = MBOKCancelDetailsText.getExtent();
   %textExtentY = getWord(%textExtent, 1);
   %textPos = MBOKCancelDetailsText.getPosition();
   %textPosY = getWord(%textPos, 1);
      
   %extentY = %textPosY + %textExtentY + 65;
   
   MBOKCancelDetailsInfoText.setExtent(285, 128);
   
   MBOKCancelDetailsFrame.setExtent(300, %extentY);
   
   MessageBoxOKCancelDetailsDlg.callback = %callback;
   MessageBoxOKCancelDetailsDlg.cancelCallback = %cancelCallback;
   
   MBOKCancelDetailsFrame.defaultExtent = MBOKCancelDetailsFrame.getExtent();
}

function MBOKCancelDetailsToggleInfoFrame()
{
   if(!MBOKCancelDetailsScroll.isVisible())
   {
      MBOKCancelDetailsScroll.setVisible(true);
      MBOKCancelDetailsText.forceReflow();
      %textExtent = MBOKCancelDetailsText.getExtent();
      %textExtentY = getWord(%textExtent, 1);
      %textPos = MBOKCancelDetailsText.getPosition();
      %textPosY = getWord(%textPos, 1);
      
      %verticalStretch = %textExtentY;
      
      if((%verticalStretch > 260) || (%verticalStretch < 0))
        %verticalStretch = 260;
      
      %extent = MBOKCancelDetailsFrame.defaultExtent;
      %height = getWord(%extent, 1);
      
      %posY = %textPosY + %textExtentY + 10;
      %posX = getWord(MBOKCancelDetailsScroll.getPosition(), 0);
      MBOKCancelDetailsScroll.setPosition(%posX, %posY);
      MBOKCancelDetailsScroll.setExtent(getWord(MBOKCancelDetailsScroll.getExtent(), 0), %verticalStretch);
      MBOKCancelDetailsFrame.setExtent(300, %height + %verticalStretch + 10);    
   } else
   {
      %extent = MBOKCancelDetailsFrame.defaultExtent;
      %width = getWord(%extent, 0);
      %height = getWord(%extent, 1);
      MBOKCancelDetailsFrame.setExtent(%width, %height);
      MBOKCancelDetailsScroll.setVisible(false);
   }
}

function MessageBoxOKCancelDetailsDlg::onSleep( %this )
{
   %this.callback = "";
   MessageBoxCtrl.originalMenuInputContainer.setActive();
}

function MessageBoxYesNo(%title, %message, %yesCallback, %noCallback)
{
   Canvas.pushDialog(MessageBoxDlg);
   MessageBoxTitleText.text = %title;
   
   MessageBoxOCButtonHolder.hidden = false;
   MessageBoxYNCButtonHolder.hidden = true;
   MessageBoxOKButtonHolder.hidden = true;
   
   MessageBoxOCButtonHolder-->OKButton.set("btn_a", "Return", "Yes", "MessageCallback(MessageBoxDlg,MessageBoxDlg.yesCallBack);");
   MessageBoxOCButtonHolder-->CancelButton.set("btn_b", "Escape", "No", "MessageCallback(MessageBoxDlg,MessageBoxDlg.noCallback);");
   
   MessageBoxCtrl.originalMenuInputContainer = $activeMenuButtonContainer;
   MessageBoxOCButtonHolder.setActive();
   
   MBSetText(MessageBoxText, MessageBoxCtrl, %message);
   MessageBoxDlg.yesCallBack = %yesCallback;
   MessageBoxDlg.noCallback = %noCallback;
}

function MessageBoxYesNoCancel(%title, %message, %yesCallback, %noCallback, %cancelCallback)
{
   Canvas.pushDialog(MessageBoxDlg);
   MessageBoxTitleText.text = %title;
   
   MessageBoxOCButtonHolder.hidden = true;
   MessageBoxYNCButtonHolder.hidden = false;
   MessageBoxOKButtonHolder.hidden = true;
   
   MessageBoxYNCButtonHolder-->yesButton.set("btn_a", "Return", "Yes", "MessageCallback(MessageBoxDlg,MessageBoxDlg.yesCallBack);");
   MessageBoxYNCButtonHolder-->noButton.set("btn_x", "backspace", "No", "MessageCallback(MessageBoxDlg,MessageBoxDlg.noCallback);");
   MessageBoxYNCButtonHolder-->cancelButton.set("btn_b", "Escape", "No", "MessageCallback(MessageBoxDlg,MessageBoxDlg.cancelCallback);");
   
   MessageBoxCtrl.originalMenuInputContainer = $activeMenuButtonContainer;
   MessageBoxYNCButtonHolder.setActive();
   
   MBSetText(MessageBoxText, MessageBoxCtrl, %message);
   MessageBoxDlg.yesCallBack = %yesCallback;
   MessageBoxDlg.noCallback = %noCallback;
   MessageBoxDlg.cancelCallback = %cancelCallback;
}

function MessageBoxDlg::onSleep( %this )
{
   %this.callback = "";
   %this.cancelCallback = "";
   %this.yesCallback = "";
   %this.noCallback = "";
   %this.cancelCallback = "";
   MessageBoxCtrl.originalMenuInputContainer.setActive();
}

//---------------------------------------------------------------------------------------------
// MessagePopup
// Displays a message box with no buttons. Disappears after %delay milliseconds.
//---------------------------------------------------------------------------------------------
function MessagePopup(%title, %message, %delay)
{
   Canvas.pushDialog(MessageBoxDlg);
   MessageBoxTitleText.text = %title;
   MBSetText(MessageBoxText, MessageBoxCtrl, %message);

   if (%delay !$= "")
      schedule(%delay, 0, CloseMessagePopup);
}

function CloseMessagePopup()
{
   Canvas.popDialog(MessageBoxDlg);
}

//---------------------------------------------------------------------------------------------
// IODropdown
// By passing in a simgroup or simset, the user will be able to choose a child of that group
// through a guiPopupMenuCtrl
//---------------------------------------------------------------------------------------------

function IODropdown(%title, %message, %simgroup, %callback, %cancelCallback)
{
   IODropdownFrame.text = %title;
   Canvas.pushDialog(IODropdownDlg);
   MBSetText(IODropdownText, IODropdownFrame, %message);
   
   if(isObject(%simgroup))
   {
      for(%i = 0; %i < %simgroup.getCount(); %i++)
         IODropdownMenu.add(%simgroup.getObject(%i).getName());
      
   }
   
   IODropdownMenu.sort();
   IODropdownMenu.setFirstSelected(0);
   
   IODropdownDlg.callback = %callback;
   IODropdownDlg.cancelCallback = %cancelCallback;
}

function IODropdownDlg::onSleep( %this )
{
   %this.callback = "";
   %this.cancelCallback = "";
   IODropdownMenu.clear();
}

//The # in the function passed replaced with the output 
//of the preset menu.
function IOCallback(%dlg, %callback)
{
   %id = IODropdownMenu.getSelected();
   %text = IODropdownMenu.getTextById(%id);
   %callback = strreplace(%callback, "#", %text); 
   eval(%callback);
   
   Canvas.popDialog(%dlg);
}
