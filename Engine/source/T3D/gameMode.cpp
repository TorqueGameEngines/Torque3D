#include "gameMode.h"

#ifdef TORQUE_TOOLS
#include "gui/containers/guiDynamicCtrlArrayCtrl.h"
#endif

#include "console/arrayObject.h"

IMPLEMENT_CONOBJECT(GameMode);

IMPLEMENT_CALLBACK(GameMode, onActivated, void, (), (),
   "@brief Called when a gamemode is activated.\n\n");
IMPLEMENT_CALLBACK(GameMode, onDeactivated, void, (), (),
   "@brief Called when a gamemode is deactivated.\n\n");
IMPLEMENT_CALLBACK(GameMode, onSceneLoaded, void, (), (),
   "@brief Called when a scene has been loaded and has game mode implications.\n\n");
IMPLEMENT_CALLBACK(GameMode, onSceneUnloaded, void, (), (),
   "@brief Called when a scene has been unloaded and has game mode implications.\n\n");
IMPLEMENT_CALLBACK(GameMode, onSubsceneLoaded, void, (SubScene*), ("SubScene"),
   "@brief Called when a subScene has been loaded and has game mode implications.\n\n");
IMPLEMENT_CALLBACK(GameMode, onSubsceneUnloaded, void, (SubScene*), ("SubScene"),
   "@brief Called when a subScene has been unloaded and has game mode implications.\n\n");


ConsoleType(GameModeList, TypeGameModeList, const char*, "")

ConsoleGetType(TypeGameModeList)
{
   // Fetch asset Id.
   return *((const char**)(dptr));
}

//-----------------------------------------------------------------------------

ConsoleSetType(TypeGameModeList)
{
   // Was a single argument specified?
   if (argc == 1)
   {
      // Yes, so fetch field value.
      *((const char**)dptr) = StringTable->insert(argv[0]);

      return;
   }

   // Warn.
   //Con::warnf("(TypeGameModeList) - Cannot set multiple args to a single asset.");
}

GameMode::GameMode() :
   mGameModeName(StringTable->EmptyString()),
   mGameModeDesc(StringTable->EmptyString()),
   mIsActive(false),
   mIsAlwaysActive(false)
{
   INIT_ASSET(PreviewImage);
}

void GameMode::initPersistFields()
{
     Parent::initPersistFields();

     addField("gameModeName", TypeString, Offset(mGameModeName, GameMode), "Human-readable name of the gamemode");
     addField("description", TypeString, Offset(mGameModeDesc, GameMode), "Description of the gamemode");

     INITPERSISTFIELD_IMAGEASSET(PreviewImage, GameMode, "Preview Image");

     addField("active", TypeBool, Offset(mIsActive, GameMode), "Is the gamemode active");
     addField("alwaysActive", TypeBool, Offset(mIsAlwaysActive, GameMode), "Is the gamemode always active");
}

bool GameMode::onAdd()
{
   if (!Parent::onAdd())
      return false;

   return true;
}

void GameMode::onRemove()
{
   Parent::onRemove();
}

void GameMode::findGameModes(const char* gameModeList, Vector<GameMode*> *outGameModes)
{
   if (outGameModes == nullptr)
      return;

   Vector<String> gameModeNames;
   U32 uCount = StringUnit::getUnitCount(gameModeList, ";");
   for (U32 i = 0; i < uCount; i++)
   {
      String name = StringUnit::getUnit(gameModeList, i, ";");
      if (!name.isEmpty())
         gameModeNames.push_back(name);
   }

   for (U32 i = 0; i < gameModeNames.size(); i++)
   {
      GameMode* gm;
      if (Sim::findObject(gameModeNames[i].c_str(), gm))
      {
         if (gm->isActive() || gm->isAlwaysActive())
            outGameModes->push_back(gm);
      }
   }
}

void GameMode::setActive(const bool& active)
{
   mIsActive = active;
   if (mIsActive)
      onActivated_callback();
   else
      onDeactivated_callback();
}

void GameMode::setAlwaysActive(const bool& alwaysActive)
{
   mIsAlwaysActive = alwaysActive;
}

DefineEngineMethod(GameMode, isActive, bool, (), ,
   "Returns if the GameMode is currently active.\n"
   "@return The active status of the GameMode")
{
   return object->isActive();
}

DefineEngineMethod(GameMode, setActive, void, (bool active), (true),
   "Sets the active state of the GameMode.\n"
   "@param active A bool of the state the GameMode should be set to")
{
   object->setActive(active);
}

DefineEngineMethod(GameMode, isALwaysActive, bool, (), ,
   "Returns if the GameMode is currently active.\n"
   "@return The active status of the GameMode")
{
   return object->isActive();
}

DefineEngineMethod(GameMode, setAlwaysActive, void, (bool alwaysActive), (true),
   "Sets the active state of the GameMode.\n"
   "@param active A bool of the state the GameMode should be set to")
{
   object->setAlwaysActive(alwaysActive);
}

DefineEngineFunction(getGameModesList, ArrayObject*, (), , "")
{
   ArrayObject* dictionary = new ArrayObject();
   dictionary->registerObject();

   char activeValBuffer[16];

   for (SimGroup::iterator itr = Sim::getRootGroup()->begin(); itr != Sim::getRootGroup()->end(); itr++)
   {
      GameMode* gm = dynamic_cast<GameMode*>(*itr);
      if (gm)
      {
         dSprintf(activeValBuffer, 16, "%d", (gm->mIsActive || gm->mIsAlwaysActive));
         dictionary->push_back(gm->getName(), activeValBuffer);
      }
   }

   return dictionary;
}

//-----------------------------------------------------------------------------
// GuiInspectorTypeAssetId
//-----------------------------------------------------------------------------
#ifdef TORQUE_TOOLS

GuiInspectorTypeGameModeList::GuiInspectorTypeGameModeList()
   : mHelper(NULL),
   mRollout(NULL),
   mArrayCtrl(NULL)
{

}
IMPLEMENT_CONOBJECT(GuiInspectorTypeGameModeList);

ConsoleDocClass(GuiInspectorTypeGameModeList,
   "@brief Inspector field type for selecting GameModes\n\n"
   "Editor use only.\n\n"
   "@internal"
);

bool GuiInspectorTypeGameModeList::onAdd()
{
   // Skip our parent because we aren't using mEditCtrl
   // and according to our parent that would be cause to fail onAdd.
   if (!Parent::Parent::onAdd())
      return false;

   if (!mInspector)
      return false;

   //build out our list of gamemodes
   Vector<GameMode*> gameModesList;

   for (SimGroup::iterator itr = Sim::getRootGroup()->begin(); itr != Sim::getRootGroup()->end(); itr++)
   {
      GameMode* gm = dynamic_cast<GameMode*>(*itr);
      if (gm)
         gameModesList.push_back(gm);
   }
   
   static StringTableEntry sProfile = StringTable->insert("profile");
   setDataField(sProfile, NULL, "GuiInspectorFieldProfile");
   setBounds(0, 0, 100, 18);

   // Allocate our children controls...

   mRollout = new GuiRolloutCtrl();
   mRollout->setMargin(14, 0, 0, 0);
   mRollout->setCanCollapse(false);
   mRollout->registerObject();
   addObject(mRollout);

   mArrayCtrl = new GuiDynamicCtrlArrayControl();
   mArrayCtrl->setDataField(sProfile, NULL, "GuiInspectorBitMaskArrayProfile");
   mArrayCtrl->setField("autoCellSize", "true");
   mArrayCtrl->setField("fillRowFirst", "true");
   mArrayCtrl->setField("dynamicSize", "true");
   mArrayCtrl->setField("rowSpacing", "4");
   mArrayCtrl->setField("colSpacing", "1");
   mArrayCtrl->setField("frozen", "true");
   mArrayCtrl->registerObject();

   mRollout->addObject(mArrayCtrl);

   GuiCheckBoxCtrl* pCheckBox = NULL;

   for (S32 i = 0; i < gameModesList.size(); i++)
   {
      pCheckBox = new GuiCheckBoxCtrl();
      pCheckBox->setText(gameModesList[i]->getName());
      pCheckBox->registerObject();
      mArrayCtrl->addObject(pCheckBox);

      pCheckBox->autoSize();

      // Override the normal script callbacks for GuiInspectorTypeCheckBox
      char szBuffer[512];
      dSprintf(szBuffer, 512, "%d.applyValue();", getId());
      pCheckBox->setField("Command", szBuffer);
   }

   mArrayCtrl->setField("frozen", "false");
   mArrayCtrl->refresh();

   mHelper = new GuiInspectorTypeGameModeListHelper();
   mHelper->init(mInspector, mParent);
   mHelper->mParentRollout = mRollout;
   mHelper->mParentField = this;
   mHelper->setInspectorField(mField, mCaption, mFieldArrayIndex);
   mHelper->registerObject();
   mHelper->setExtent(pCheckBox->getExtent());
   mHelper->setPosition(0, 0);
   mRollout->addObject(mHelper);

   mRollout->sizeToContents();
   mRollout->instantCollapse();

   updateValue();

   return true;
}

void GuiInspectorTypeGameModeList::consoleInit()
{
   Parent::consoleInit();

   ConsoleBaseType::getType(TypeGameModeList)->setInspectorFieldType("GuiInspectorTypeGameModeList");
}

void GuiInspectorTypeGameModeList::childResized(GuiControl* child)
{
   setExtent(mRollout->getExtent());
}

bool GuiInspectorTypeGameModeList::resize(const Point2I& newPosition, const Point2I& newExtent)
{
   if (!Parent::resize(newPosition, newExtent))
      return false;

   // Hack... height of 18 is hardcoded
   return mHelper->resize(Point2I(0, 0), Point2I(newExtent.x, 18));
}

bool GuiInspectorTypeGameModeList::updateRects()
{
   if (!mRollout)
      return false;

   bool result = mRollout->setExtent(getExtent());

   for (U32 i = 0; i < mArrayCtrl->size(); i++)
   {
      GuiInspectorField* pField = dynamic_cast<GuiInspectorField*>(mArrayCtrl->at(i));
      if (pField)
         if (pField->updateRects())
            result = true;
   }

   if (mHelper && mHelper->updateRects())
      result = true;

   return result;
}

StringTableEntry GuiInspectorTypeGameModeList::getValue()
{
   if (!mRollout)
      return StringTable->insert("");

   String results = "";

   for (U32 i = 0; i < mArrayCtrl->size(); i++)
   {
      GuiCheckBoxCtrl* pCheckBox = dynamic_cast<GuiCheckBoxCtrl*>(mArrayCtrl->at(i));

      if (pCheckBox->getStateOn())
         results += pCheckBox->getText() + String(";");
   }

   if (!results.isEmpty())
      return StringTable->insert(results.c_str());
   else
      return StringTable->EmptyString();
}

void GuiInspectorTypeGameModeList::setValue(StringTableEntry value)
{
   Vector<String> gameModeNames;
   U32 uCount = StringUnit::getUnitCount(value, ";");
   for (U32 i = 0; i < uCount; i++)
   {
      String name = StringUnit::getUnit(value, i, ";");
      if (!name.isEmpty())
         gameModeNames.push_back(name);
   }

   for (U32 i = 0; i < mArrayCtrl->size(); i++)
   {
      GuiCheckBoxCtrl* pCheckBox = dynamic_cast<GuiCheckBoxCtrl*>(mArrayCtrl->at(i));

      for (U32 m = 0; m < gameModeNames.size(); m++)
      {
         if (gameModeNames[m].equal(pCheckBox->getText()))
         {
            pCheckBox->setStateOn(true);
         }
      }
   }

   mHelper->setValue(value);
}

void GuiInspectorTypeGameModeList::updateData()
{
   StringTableEntry data = getValue();
   setData(data);
}

DefineEngineMethod(GuiInspectorTypeGameModeList, applyValue, void, (), , "")
{
   object->updateData();
}

GuiInspectorTypeGameModeListHelper::GuiInspectorTypeGameModeListHelper()
   : mButton(NULL),
   mParentRollout(NULL),
   mParentField(NULL)
{
}

IMPLEMENT_CONOBJECT(GuiInspectorTypeGameModeListHelper);

ConsoleDocClass(GuiInspectorTypeGameModeListHelper,
   "@brief Inspector field type support for GameModes lists.\n\n"
   "Editor use only.\n\n"
   "@internal"
);

GuiControl* GuiInspectorTypeGameModeListHelper::constructEditControl()
{
   GuiControl* retCtrl = new GuiTextEditCtrl();
   retCtrl->setDataField(StringTable->insert("profile"), NULL, "GuiInspectorTextEditProfile");
   retCtrl->setField("hexDisplay", "true");

   _registerEditControl(retCtrl);

   char szBuffer[512];
   dSprintf(szBuffer, 512, "%d.apply(%d.getText());", mParentField->getId(), retCtrl->getId());
   retCtrl->setField("AltCommand", szBuffer);
   retCtrl->setField("Validate", szBuffer);

   mButton = new GuiBitmapButtonCtrl();

   RectI browseRect(Point2I((getLeft() + getWidth()) - 26, getTop() + 2), Point2I(20, getHeight() - 4));
   dSprintf(szBuffer, 512, "%d.toggleExpanded(false);", mParentRollout->getId());
   mButton->setField("Command", szBuffer);
   mButton->setField("buttonType", "ToggleButton");
   mButton->setDataField(StringTable->insert("Profile"), NULL, "GuiInspectorButtonProfile");
   mButton->setBitmap(StringTable->insert("ToolsModule:arrowBtn_N_image"));
   mButton->setStateOn(true);
   mButton->setExtent(16, 16);
   mButton->registerObject();
   addObject(mButton);

   mButton->resize(browseRect.point, browseRect.extent);

   return retCtrl;
}

bool GuiInspectorTypeGameModeListHelper::resize(const Point2I& newPosition, const Point2I& newExtent)
{
   if (!Parent::resize(newPosition, newExtent))
      return false;

   if (mEdit != NULL)
   {
      return updateRects();
   }

   return false;
}

bool GuiInspectorTypeGameModeListHelper::updateRects()
{
   S32 dividerPos, dividerMargin;
   mInspector->getDivider(dividerPos, dividerMargin);
   Point2I fieldExtent = getExtent();
   Point2I fieldPos = getPosition();

   mCaptionRect.set(0, 0, fieldExtent.x - dividerPos - dividerMargin, fieldExtent.y);
   mEditCtrlRect.set(fieldExtent.x - dividerPos + dividerMargin, 1, dividerPos - dividerMargin - 32, fieldExtent.y);

   bool editResize = mEdit->resize(mEditCtrlRect.point, mEditCtrlRect.extent);
   bool buttonResize = false;

   if (mButton != NULL)
   {
      mButtonRect.set(fieldExtent.x - 26, 2, 16, 16);
      buttonResize = mButton->resize(mButtonRect.point, mButtonRect.extent);
   }

   return (editResize || buttonResize);
}

void GuiInspectorTypeGameModeListHelper::setValue(StringTableEntry newValue)
{
   GuiTextEditCtrl* edit = dynamic_cast<GuiTextEditCtrl*>(mEdit);
   edit->setText(newValue);
}
#endif
