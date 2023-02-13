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

   GuiTextCtrl* mLabel;
   GuiBitmapButtonCtrl* mPreviewBorderButton;
   GuiBitmapCtrl* mPreviewImage;
   GuiButtonCtrl* mEditButton;

   DECLARE_CONOBJECT(GuiInspectorTypeImageAssetPtr);
   static void consoleInit();

   virtual GuiControl* constructEditControl();
   virtual bool updateRects();
   bool renderTooltip(const Point2I& hoverPos, const Point2I& cursorPos, const char* tipText = NULL);

   virtual void updateValue();

   void updatePreviewImage();
   void setPreviewImage(StringTableEntry assetId);
};

class GuiInspectorTypeImageAssetId : public GuiInspectorTypeImageAssetPtr
{
   typedef GuiInspectorTypeImageAssetPtr Parent;
public:

   DECLARE_CONOBJECT(GuiInspectorTypeImageAssetId);
   static void consoleInit();
};
#endif
