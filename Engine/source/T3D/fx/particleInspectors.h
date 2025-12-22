#pragma once
#ifdef TORQUE_TOOLS
#include "gui/buttons/guiIconButtonCtrl.h"
#endif

#include "gui/containers/guiStackCtrl.h"
#include "gui/controls/guiPopUpCtrlEx.h"
#include "gui/editor/inspector/field.h"

//-----------------------------------------------------------------------------
// TypeParticleList
//-----------------------------------------------------------------------------
DefineConsoleType(TypeParticleList, Vector<const char*>)


#ifdef TORQUE_TOOLS
//-----------------------------------------------------------------------------
// GuiInspectorTypeGuiProfile Class
//-----------------------------------------------------------------------------
class GuiInspectorTypeParticleDataList : public GuiInspectorField
{
private:
   typedef GuiInspectorField Parent;

   GuiStackControl* mStack;
   GuiIconButtonCtrl* mNewParticleBtn;
   GuiControl* mParticleSlot0Ctrl;
   Vector<GuiControl*> mParticleSlotList;

public:
   DECLARE_CONOBJECT(GuiInspectorTypeParticleDataList);
   static void consoleInit();

   GuiControl* constructEditControl() override;
   bool updateRects() override;

   void _populateMenu(GuiPopUpMenuCtrlEx* menu);
   GuiControl* _buildParticleEntryField(const S32& index);
};
#endif
