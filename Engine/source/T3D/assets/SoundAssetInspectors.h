#pragma once

#include "SoundAsset.h"
#include "gui/editor/guiInspectorTypes.h"

#ifdef TORQUE_TOOLS
class GuiInspectorTypeSoundAssetPtr : public GuiInspectorTypeFileName
{
   typedef GuiInspectorTypeFileName Parent;
public:

   GuiBitmapButtonCtrl* mEditButton;

   DECLARE_CONOBJECT(GuiInspectorTypeSoundAssetPtr);
   static void consoleInit();

   GuiControl* constructEditControl() override;
   bool updateRects() override;
};

class GuiInspectorTypeSoundAssetId : public GuiInspectorTypeSoundAssetPtr
{
   typedef GuiInspectorTypeSoundAssetPtr Parent;
public:

   DECLARE_CONOBJECT(GuiInspectorTypeSoundAssetId);
   static void consoleInit();
};
#endif
