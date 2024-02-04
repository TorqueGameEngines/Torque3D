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

#include "console/simBase.h"
#include "console/simDatablock.h"
#include "gui/editor/guiInspector.h"
#include "gui/editor/inspector/datablockField.h"
#include "gui/editor/inspector/group.h"
#include "gui/buttons/guiIconButtonCtrl.h"
#include "gui/editor/inspector/datablockField.h"
#include "sfx/sfxTypes.h"
#include "sfx/sfxDescription.h"
#include "sfx/sfxEnvironment.h"
#include "sfx/sfxAmbience.h"
#include "sfx/sfxTrack.h"
#include "T3D/gameBase/gameBase.h"


//-----------------------------------------------------------------------------
// GuiInspectorDatablockField 
// Field construction for datablock types
//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT(GuiInspectorDatablockField);

ConsoleDocClass( GuiInspectorDatablockField,
   "@brief Custom field type for datablock enumeration.\n\n"
   "Editor use only.\n\n"
   "@internal"
);


GuiInspectorDatablockField::GuiInspectorDatablockField( StringTableEntry className )
{
   setClassName( className );
}

void GuiInspectorDatablockField::setClassName( StringTableEntry className )
{
   if( !className || !className[ 0 ] )
      mDesiredClass = NULL;
   else
   {
      mDesiredClass = AbstractClassRep::findClassRep( className );
      if( !mDesiredClass )
         Con::errorf( "GuiInspectorDatablockField::setClassName - no class '%s' found!", className );
   }
}

void GuiInspectorDatablockField::_populateMenu( GuiPopUpMenuCtrlEx* menu )
{
   menu->setCanSearch(true);
   menu->addScheme( 1, ColorI( 80, 0, 0, 255 ), ColorI( 80, 0, 0, 255 ), ColorI( 80, 0, 0, 255 ) ); // For client-only coloring.
   menu->addEntry( "", 0 ); // For unsetting.

   SimSet* set = _getDatablockSet();
   U32 id = 1;

   //We can do some special filtering here if it's derived from GameBase a la categories
   if(mDesiredClass->isSubclassOf(AbstractClassRep::findClassRep("GameBaseData")))
   {
      //First, do categories
      Vector<String> categories;
      for (SimSet::iterator iter = set->begin(); iter != set->end(); ++iter)
      {
         SimDataBlock* datablock = dynamic_cast<SimDataBlock*>(*iter);

         // Skip non-datablocks if we somehow encounter them.
         if (!datablock)
            continue;

         if (datablock && (!mDesiredClass || datablock->getClassRep()->isClass(mDesiredClass)))
         {
            GameBaseData *data = dynamic_cast<GameBaseData*>(datablock);
            if(data)
            {
               String category = data->mCategory;
               if(category.isNotEmpty() && (categories.empty() || categories.find_next(category) == -1))
                  categories.push_back(category);
            }
         }
      }

      if (categories.size() > 0)
      {
         categories.push_back("No Category");

         //Now that we have our categories, lets populate our list
         for (Vector<String>::iterator catIter = categories.begin(); catIter != categories.end(); ++catIter)
         {
            String categoryName = String::ToLower(catIter->c_str());
            if (categoryName != String::EmptyString)
            {
               menu->addCategory(catIter->c_str());
               id++;
            }

            for (SimSet::iterator iter = set->begin(); iter != set->end(); ++iter)
            {
               GameBaseData* datablock = dynamic_cast<GameBaseData*>(*iter);

               // Skip non-datablocks if we somehow encounter them.
               if (!datablock)
                  continue;

               String dbCategory = String(datablock->mCategory).isEmpty() ? String("no category") : String::ToLower(datablock->mCategory);

               if (datablock && (!mDesiredClass || datablock->getClassRep()->isClass(mDesiredClass)) && (dbCategory == categoryName))
               {
                  menu->addEntry(datablock->getName(), id++, datablock->isClientOnly() ? 1 : 0, true);
               }
            }
         }

         return;
      }
   }

   for (SimSet::iterator iter = set->begin(); iter != set->end(); ++iter)
   {
      SimDataBlock* datablock = dynamic_cast<SimDataBlock*>(*iter);

      // Skip non-datablocks if we somehow encounter them.
      if (!datablock)
         continue;

      // Ok, now we have to figure inheritance info.
      if (datablock && (!mDesiredClass || datablock->getClassRep()->isClass(mDesiredClass)))
         menu->addEntry(datablock->getName(), id++, datablock->isClientOnly() ? 1 : 0);
   }
   
   menu->sort();
}

GuiControl* GuiInspectorDatablockField::constructEditControl()
{
   // Create base filename edit controls
   GuiControl* retCtrl = Parent::constructEditControl();
   if (retCtrl == NULL)
      return retCtrl;

   char szBuffer[512];

   // Create "Open in Editor" button
   mEditButton = new GuiButtonCtrl();
   dSprintf(szBuffer, sizeof(szBuffer), "DatablockEditorPlugin.openDatablock(%d.getText());", retCtrl->getId());
   mEditButton->setField("Command", szBuffer);
   mEditButton->setText("...");

   mEditButton->setDataField(StringTable->insert("Profile"), NULL, "GuiInspectorButtonProfile");
   mEditButton->setDataField(StringTable->insert("tooltipprofile"), NULL, "GuiToolTipProfile");
   mEditButton->setDataField(StringTable->insert("hovertime"), NULL, "1000");
   mEditButton->setDataField(StringTable->insert("tooltip"), NULL, "Edit this datablock");

   mEditButton->registerObject();
   addObject(mEditButton);

   //Add add button
   mAddButton = new GuiBitmapButtonCtrl();
   dSprintf(szBuffer, sizeof(szBuffer), "DatablockEditorPlugin.createNewDatablockOfType(%s, %d.getText());", mDesiredClass->getClassName(), retCtrl->getId());
   mAddButton->setField("Command", szBuffer);

   char addBtnBitmapName[512] = "ToolsModule:iconAdd_Image";
   mAddButton->setBitmap(StringTable->insert(addBtnBitmapName));

   mAddButton->setDataField(StringTable->insert("Profile"), NULL, "GuiButtonProfile");
   mAddButton->setDataField(StringTable->insert("tooltipprofile"), NULL, "GuiToolTipProfile");
   mAddButton->setDataField(StringTable->insert("hovertime"), NULL, "1000");
   mAddButton->setDataField(StringTable->insert("tooltip"), NULL, "Create new datablock");

   mAddButton->registerObject();
   addObject(mAddButton);

   return retCtrl;
}

bool GuiInspectorDatablockField::updateRects()
{
   S32 dividerPos, dividerMargin;
   mInspector->getDivider(dividerPos, dividerMargin);
   Point2I fieldExtent = getExtent();
   Point2I fieldPos = getPosition();

   mCaptionRect.set(0, 0, fieldExtent.x - dividerPos - dividerMargin, fieldExtent.y);
   mEditCtrlRect.set(fieldExtent.x - dividerPos + dividerMargin, 1, dividerPos - dividerMargin - 34, fieldExtent.y);

   bool resized = mEdit->resize(mEditCtrlRect.point, mEditCtrlRect.extent);
   if (mEditButton != NULL)
   {
      mBrowseRect.set(fieldExtent.x - 32, 2, 14, fieldExtent.y - 4);
      resized |= mEditButton->resize(mBrowseRect.point, mBrowseRect.extent);
   }

   if (mAddButton != NULL)
   {
      RectI shapeEdRect(fieldExtent.x - 16, 2, 14, fieldExtent.y - 4);
      resized |= mAddButton->resize(shapeEdRect.point, shapeEdRect.extent);
   }

   return resized;
}

//-----------------------------------------------------------------------------
// GuiInspectorTypeSFXDescriptionName 
//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT(GuiInspectorTypeSFXDescriptionName);

ConsoleDocClass( GuiInspectorTypeSFXDescriptionName,
   "@brief Inspector field type for SFXDescriptionName\n\n"
   "Editor use only.\n\n"
   "@internal"
);

void GuiInspectorTypeSFXDescriptionName::consoleInit()
{
   Parent::consoleInit();

   ConsoleBaseType::getType( TypeSFXDescriptionName )->setInspectorFieldType( "GuiInspectorTypeSFXDescriptionName" );
}


//-----------------------------------------------------------------------------
// GuiInspectorTypeSFXTrackName 
//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT(GuiInspectorTypeSFXTrackName);

ConsoleDocClass( GuiInspectorTypeSFXTrackName,
   "@brief Inspector field type for SFXTrackName\n\n"
   "Editor use only.\n\n"
   "@internal"
);

void GuiInspectorTypeSFXTrackName::consoleInit()
{
   Parent::consoleInit();

   ConsoleBaseType::getType( TypeSFXTrackName )->setInspectorFieldType( "GuiInspectorTypeSFXTrackName" );
}


//-----------------------------------------------------------------------------
// GuiInspectorTypeSFXEnvironmentName 
//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT(GuiInspectorTypeSFXEnvironmentName);

ConsoleDocClass( GuiInspectorTypeSFXEnvironmentName,
   "@brief Inspector field type for SFXEnvironment\n\n"
   "Editor use only.\n\n"
   "@internal"
);

void GuiInspectorTypeSFXEnvironmentName::consoleInit()
{
   Parent::consoleInit();

   ConsoleBaseType::getType( TypeSFXEnvironmentName )->setInspectorFieldType( "GuiInspectorTypeSFXEnvironmentName" );
}


//-----------------------------------------------------------------------------
// GuiInspectorTypeSFXAmbienceName 
//-----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT(GuiInspectorTypeSFXAmbienceName);

ConsoleDocClass( GuiInspectorTypeSFXAmbienceName,
   "@brief Inspector field type for SFXAmbience\n\n"
   "Editor use only.\n\n"
   "@internal"
);

void GuiInspectorTypeSFXAmbienceName::consoleInit()
{
   Parent::consoleInit();

   ConsoleBaseType::getType( TypeSFXAmbienceName )->setInspectorFieldType( "GuiInspectorTypeSFXAmbienceName" );
}
