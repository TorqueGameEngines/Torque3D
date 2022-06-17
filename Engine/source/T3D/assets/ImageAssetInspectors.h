#pragma once

#include "ImageAsset.h"

#ifndef _GUI_INSPECTOR_TYPES_H_
#include "gui/editor/guiInspectorTypes.h"
#endif

#ifdef TORQUE_TOOLS
class GuiInspectorTypeImageAssetPtr : public GuiInspectorTypeFileName
{
   typedef GuiInspectorTypeFileName Parent;
public:

   GuiBitmapButtonCtrl* mImageEdButton;

   DECLARE_CONOBJECT(GuiInspectorTypeImageAssetPtr);
   static void consoleInit();

   virtual GuiControl* constructEditControl();
   virtual bool updateRects();
   bool renderTooltip(const Point2I& hoverPos, const Point2I& cursorPos, const char* tipText = NULL);
};

class GuiInspectorTypeImageAssetId : public GuiInspectorTypeImageAssetPtr
{
   typedef GuiInspectorTypeImageAssetPtr Parent;
public:

   DECLARE_CONOBJECT(GuiInspectorTypeImageAssetId);
   static void consoleInit();
};
#endif
