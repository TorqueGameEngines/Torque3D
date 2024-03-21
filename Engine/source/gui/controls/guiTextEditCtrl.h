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

#ifndef _GUITEXTEDITCTRL_H_
#define _GUITEXTEDITCTRL_H_

#ifndef _GUITYPES_H_
#include "gui/core/guiTypes.h"
#endif
#ifndef _GUITEXTCTRL_H_
#include "gui/controls/guiTextCtrl.h"
#endif
#ifndef _STRINGBUFFER_H_
#include "core/stringBuffer.h"
#endif

class SFXTrack;

class GuiTextEditCtrl : public GuiTextCtrl
{
private:
   typedef GuiTextCtrl Parent;

protected:

   DECLARE_CALLBACK( void, onTabComplete, (const char* val));
   DECLARE_CALLBACK( void, onReturn, ());
   DECLARE_CALLBACK( void, onValidate, ());

   StringBuffer mTextBuffer;

   String mValidateCommand;
   String mEscapeCommand;
   SFXTrack*  mDeniedSound;

   // for animating the cursor
   S32      mNumFramesElapsed;
   U32      mTimeLastCursorFlipped;
   ColorI   mCursorColor;
   bool     mCursorOn;

   bool     mInsertOn;
   S32      mMouseDragStart;
   Point2I  mTextOffset;
   bool     mTextOffsetReset;
   bool     mDragHit;
   bool     mTabComplete;
   S32      mScrollDir;

   //undo members
   StringBuffer mUndoText;
   S32      mUndoBlockStart;
   S32      mUndoBlockEnd;
   S32      mUndoCursorPos;
   void saveUndoState();

   S32      mBlockStart;
   S32      mBlockEnd;
   S32      mCursorPos;
   virtual S32 calculateCursorPos( const Point2I &globalPos );

   bool                 mHistoryDirty;
   S32                  mHistoryLast;
   S32                  mHistoryIndex;
   S32                  mHistorySize;
   bool                 mPasswordText;
   StringTableEntry     mPasswordMask;

   S32                  mDoubleClickTimeMS;
   S32                  mMouseUpTime;

   StringTableEntry     mPlaceholderText;

   /// If set, any non-ESC key is handled here or not at all
   bool    mSinkAllKeyEvents;   
   UTF16   **mHistoryBuf;
   void updateHistory(StringBuffer *txt, bool moveIndex);

   void playDeniedSound();
   void execConsoleCallback();

   bool mTextValid;

   virtual void handleCharInput( U16 ascii );

   S32 findNextWord();   
   S32 findPrevWord();   

public:
   GuiTextEditCtrl();
   ~GuiTextEditCtrl();
   DECLARE_CONOBJECT(GuiTextEditCtrl);
   DECLARE_DESCRIPTION( "A control that allows to edit a single line of text. ");
   static void initPersistFields();

   bool onAdd() override;

   /// Get the contents of the control.
   ///
   /// dest should be of size GuiTextCtrl::MAX_STRING_LENGTH+1.
   void getText(char *dest);
   virtual void getRenderText(char *dest);

   void setText(S32 tag);
   void setText(const UTF8* txt) override;
   virtual void setText(const UTF16* txt);
   S32   getCursorPos()   { return( mCursorPos ); }
   void  setCursorPos( const S32 newPos );
   
   void invalidText(bool playSound = true);
   void validText();
   bool isValidText();
	inline bool isPasswordText() { return mPasswordText; }

   bool isAllTextSelected();
   void selectAllText();
   void clearSelectedText();

   void forceValidateText();
   const char *getScriptValue() override;
   void setScriptValue(const char *value) override;

   bool getSinkAllKeys() { return mSinkAllKeyEvents; }
   void setSinkAllKeys(bool state) { mSinkAllKeyEvents = state; }

   bool onKeyDown(const GuiEvent &event) override;
   void onMouseDown(const GuiEvent &event) override;
   void onMouseDragged(const GuiEvent &event) override;
   void onMouseUp(const GuiEvent &event) override;
   
   void onCopy(bool andCut);
   void onPaste();
   void onUndo();

   void setFirstResponder() override;
   void onLoseFirstResponder() override;

   bool hasText();

   void onStaticModified(const char* slotName, const char* newValue = NULL) override;

   void onPreRender() override;
   void onRender(Point2I offset, const RectI &updateRect) override;
   virtual void drawText( const RectI &drawRect, bool isFocused );

   bool dealWithEnter( bool clearResponder );

   static bool setPlaceholderText(void* object, const char* index, const char* data)
   {
      static_cast<GuiTextEditCtrl*>(object)->setPlaceholderText(data); return true;
   }
   static const char* getPlaceholderText(void* obj, const char* data)
   {
      return static_cast<GuiTextEditCtrl*>(obj)->getPlaceholderText();
   }

   virtual void setPlaceholderText(const char* txt = NULL)
   {
      mPlaceholderText = StringTable->insert(txt, true);
   }

   const char* getPlaceholderText() { return (const char*)mPlaceholderText; }
};

#endif //_GUI_TEXTEDIT_CTRL_H
