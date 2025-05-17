#include "SubSceneAsset.h"

#include "T3D/SubScene.h"
IMPLEMENT_CONOBJECT(SubSceneAsset);


ConsoleType(SubSceneAssetPtr, TypeSubSceneAssetPtr, const char*, "")

//-----------------------------------------------------------------------------

ConsoleGetType(TypeSubSceneAssetPtr)
{
   // Fetch asset Id.
   return *((const char**)(dptr));
}

//-----------------------------------------------------------------------------

ConsoleSetType(TypeSubSceneAssetPtr)
{
   // Was a single argument specified?
   if (argc == 1)
   {
      // Yes, so fetch field value.
      *((const char**)dptr) = StringTable->insert(argv[0]);

      return;
   }

   // Warn.
   Con::warnf("(TypeSubSceneAssetPtr) - Cannot set multiple args to a single asset.");
}

//-----------------------------------------------------------------------------
ConsoleType(assetIdString, TypeSubSceneAssetId, const char*, "")

ConsoleGetType(TypeSubSceneAssetId)
{
   // Fetch asset Id.
   return *((const char**)(dptr));
}

ConsoleSetType(TypeSubSceneAssetId)
{
   // Was a single argument specified?
   if (argc == 1)
   {
      *((const char**)dptr) = StringTable->insert(argv[0]);

      return;
   }

   // Warn.
   Con::warnf("(TypeSubSceneAssetId) - Cannot set multiple args to a single asset.");
}

SubSceneAsset::SubSceneAsset() : LevelAsset()
{
}

SubSceneAsset::~SubSceneAsset()
{
}

void SubSceneAsset::initPersistFields()
{
   docsURL;
   Parent::initPersistFields();
}


//-----------------------------------------------------------------------------
// GuiInspectorTypeAssetId
//-----------------------------------------------------------------------------
#ifdef TORQUE_TOOLS
IMPLEMENT_CONOBJECT(GuiInspectorTypeSubSceneAssetPtr);

ConsoleDocClass(GuiInspectorTypeSubSceneAssetPtr,
   "@brief Inspector field type for Shapes\n\n"
   "Editor use only.\n\n"
   "@internal"
);

void GuiInspectorTypeSubSceneAssetPtr::consoleInit()
{
   Parent::consoleInit();

   ConsoleBaseType::getType(TypeSubSceneAssetPtr)->setInspectorFieldType("GuiInspectorTypeSubSceneAssetPtr");
}

GuiControl* GuiInspectorTypeSubSceneAssetPtr::constructEditControl()
{
   // Create base filename edit controls
   GuiControl* retCtrl = Parent::constructEditControl();
   if (retCtrl == NULL)
      return retCtrl;

   // Change filespec
   char szBuffer[512];
   dSprintf(szBuffer, sizeof(szBuffer), "AssetBrowser.showDialog(\"SubSceneAsset\", \"AssetBrowser.changeAsset\", %s, \"\");",
      getIdString());
   mBrowseButton->setField("Command", szBuffer);

   setDataField(StringTable->insert("targetObject"), NULL, mInspector->getInspectObject()->getIdString());

   // Create "Open in Editor" button
   mEditButton = new GuiBitmapButtonCtrl();

   dSprintf(szBuffer, sizeof(szBuffer), "$createAndAssignField = %s; AssetBrowser.setupCreateNewAsset(\"SubSceneAsset\", AssetBrowser.selectedModule);",
      getIdString());
   mEditButton->setField("Command", szBuffer);

   char bitmapName[512] = "ToolsModule:iconAdd_image";
   mEditButton->setBitmap(StringTable->insert(bitmapName));

   mEditButton->setDataField(StringTable->insert("Profile"), NULL, "GuiButtonProfile");
   mEditButton->setDataField(StringTable->insert("tooltipprofile"), NULL, "GuiToolTipProfile");
   mEditButton->setDataField(StringTable->insert("hovertime"), NULL, "1000");
   mEditButton->setDataField(StringTable->insert("tooltip"), NULL, "Test play this sound");

   mEditButton->registerObject();
   addObject(mEditButton);

   return retCtrl;
}

bool GuiInspectorTypeSubSceneAssetPtr::updateRects()
{
   S32 dividerPos, dividerMargin;
   mInspector->getDivider(dividerPos, dividerMargin);
   Point2I fieldExtent = getExtent();
   Point2I fieldPos = getPosition();

   mCaptionRect.set(0, 0, fieldExtent.x - dividerPos - dividerMargin, fieldExtent.y);
   mEditCtrlRect.set(fieldExtent.x - dividerPos + dividerMargin, 1, dividerPos - dividerMargin - 34, fieldExtent.y);

   bool resized = mEdit->resize(mEditCtrlRect.point, mEditCtrlRect.extent);
   if (mBrowseButton != NULL)
   {
      mBrowseRect.set(fieldExtent.x - 32, 2, 14, fieldExtent.y - 4);
      resized |= mBrowseButton->resize(mBrowseRect.point, mBrowseRect.extent);
   }

   if (mEditButton != NULL)
   {
      RectI shapeEdRect(fieldExtent.x - 16, 2, 14, fieldExtent.y - 4);
      resized |= mEditButton->resize(shapeEdRect.point, shapeEdRect.extent);
   }

   return resized;
}

IMPLEMENT_CONOBJECT(GuiInspectorTypeSubSceneAssetId);

ConsoleDocClass(GuiInspectorTypeSubSceneAssetId,
   "@brief Inspector field type for SubScene\n\n"
   "Editor use only.\n\n"
   "@internal"
);

void GuiInspectorTypeSubSceneAssetId::consoleInit()
{
   Parent::consoleInit();

   ConsoleBaseType::getType(TypeSubSceneAssetId)->setInspectorFieldType("GuiInspectorTypeSubSceneAssetId");
}
#endif
