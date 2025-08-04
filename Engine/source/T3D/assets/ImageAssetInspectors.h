#pragma once

#include "ImageAsset.h"

#ifndef _GUI_INSPECTOR_TYPES_H_
#include "gui/editor/guiInspectorTypes.h"
#endif
#include <gui/controls/guiBitmapCtrl.h>

#ifdef TORQUE_TOOLS
class GuiInspectorTypeImageAssetPtr : public GuiInspectorTypeFileName
{
   typedef GuiInspectorTypeFileName Parent;
public:

   GuiTextCtrl* mLabel = NULL;
   GuiBitmapButtonCtrl* mPreviewBorderButton = NULL;
   GuiBitmapCtrl* mPreviewImage = NULL;
   GuiBitmapButtonCtrl* mEditButton = NULL;

   bool mIsDeleteButtonVisible;

   DECLARE_CONOBJECT(GuiInspectorTypeImageAssetPtr);
   static void consoleInit();

   GuiControl* constructEditControl() override;
   bool updateRects() override;
   bool renderTooltip(const Point2I& hoverPos, const Point2I& cursorPos, const char* tipText = NULL);

   void updateValue() override;

   void updatePreviewImage();
   void setPreviewImage(StringTableEntry assetId);

   /// Sets this control's caption text, usually set within setInspectorField,
      /// this is exposed in case someone wants to override the normal caption.
   void setCaption(StringTableEntry caption) override;

   void setIsDeleteBtnVisible(const bool& isVisible)
   {
      if (mEditButton)
         mEditButton->setVisible(isVisible);
   }
};

class GuiInspectorTypeImageAssetId : public GuiInspectorTypeImageAssetPtr
{
   typedef GuiInspectorTypeImageAssetPtr Parent;
public:

   DECLARE_CONOBJECT(GuiInspectorTypeImageAssetId);
   static void consoleInit();
};
#endif
