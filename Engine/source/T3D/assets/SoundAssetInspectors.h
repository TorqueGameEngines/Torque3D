#pragma once

#include "SoundAsset.h"

#ifndef _GUI_INSPECTOR_TYPES_H_
#include "gui/editor/guiInspectorTypes.h"
#endif

#ifdef TORQUE_TOOLS
class GuiInspectorTypeSoundAssetPtr : public GuiInspectorTypeFileName
{
   typedef GuiInspectorTypeFileName Parent;
public:

   GuiBitmapButtonCtrl* mEditButton;

   DECLARE_CONOBJECT(GuiInspectorTypeSoundAssetPtr);
   static void consoleInit();

   virtual GuiControl* constructEditControl();
   virtual bool updateRects();
};

class GuiInspectorTypeSoundAssetId : public GuiInspectorTypeSoundAssetPtr
{
   typedef GuiInspectorTypeSoundAssetPtr Parent;
public:

   DECLARE_CONOBJECT(GuiInspectorTypeSoundAssetId);
   static void consoleInit();
};
#endif
