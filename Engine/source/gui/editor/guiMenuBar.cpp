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

#include "platform/platform.h"
#include "gui/editor/guiMenuBar.h"

#include "console/consoleTypes.h"
#include "console/console.h"
#include "gui/core/guiCanvas.h"
#include "gui/core/guiDefaultControlRender.h"
#include "gui/controls/guiTextListCtrl.h"
#include "sim/actionMap.h"
#include "gfx/gfxDevice.h"
#include "gfx/gfxDrawUtil.h"
#include "gfx/primBuilder.h"
#include "console/engineAPI.h"
#include "gui/editor/guiPopupMenuCtrl.h"

// menu bar:
// basic idea - fixed height control bar at the top of a window, placed and sized in gui editor
// menu text for menus or menu items should not begin with a digit
// all menus can be removed via the clearMenus() console command
// each menu is added via the addMenu(menuText, menuId) console command
// each menu is added with a menu id
// menu items are added to menus via that addMenuItem(menu, menuItemText, menuItemId, accelerator, checkGroup) console command
// each menu item is added with a menu item id and an optional accelerator
// menu items are initially enabled, but can be disabled/re-enabled via the setMenuItemEnable(menu,menuItem,bool)
// menu text can be set via the setMenuText(menu, newMenuText) console method
// menu item text can be set via the setMenuItemText console method
// menu items can be removed via the removeMenuItem(menu, menuItem) console command
// menu items can be cleared via the clearMenuItems(menu) console command
// menus can be hidden or shown via the setMenuVisible(menu, bool) console command
// menu items can be hidden or shown via the setMenuItemVisible(menu, menuItem, bool) console command
// menu items can be check'd via the setMenuItemChecked(menu, menuItem, bool) console command
//    if the bool is true, any other items in that menu item's check group become unchecked.
//
// menu items can have a bitmap set on them via the setMenuItemBitmap(menu, menuItem, bitmapIndex)
//    passing -1 for the bitmap index will result in no bitmap being shown
//    the index paramater is an index into the bitmap array of the associated profile
//    this can be used, for example, to display a check next to a selected menu item
//    bitmap indices are actually multiplied by 3 when indexing into the bitmap
//    since bitmaps have normal, selected and disabled states.
//
// menus can be removed via the removeMenu console command
// specification arguments for menus and menu items can be either the id or the text of the menu or menu item
// adding the menu item "-" will add an un-selectable seperator to the menu
// callbacks:
// when a menu is clicked, before it is displayed, the menu calls its onMenuSelect(menuId, menuText) method -
//    this allows the callback to enable/disable menu items, or add menu items in a context-sensitive way
// when a menu item is clicked, the menu removes itself from display, then calls onMenuItemSelect(menuId, menuText, menuItemId, menuItemText)

// the initial implementation does not support:
//    hierarchal menus
//    keyboard accelerators on menu text (i.e. via alt-key combos)

//------------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(GuiMenuBar);

ConsoleDocClass( GuiMenuBar,
   "@brief GUI Control which displays a horizontal bar with individual drop-down menu items. Each menu item may also have submenu items.\n\n"

   "@tsexample\n"
   "new GuiMenuBar(newMenuBar)\n"
   "{\n"
   "  Padding = \"0\";\n"
   "  //Properties not specific to this control have been omitted from this example.\n"
   "};\n\n"
   "// Add a menu to the menu bar\n"
   "newMenuBar.addMenu(0,\"New Menu\");\n\n"
   "// Add a menu item to the New Menu\n"
   "newMenuBar.addMenuItem(0,\"New Menu Item\",0,\"n\",-1);\n\n"
   "// Add a submenu item to the New Menu Item\n"
   "newMenuBar.addSubmenuItem(0,1,\"New Submenu Item\",0,\"s\",-1);\n"
   "@endtsexample\n\n"

   "@see GuiTickCtrl\n\n"

   "@ingroup GuiCore\n"
);

IMPLEMENT_CALLBACK( GuiMenuBar, onMouseInMenu, void, (bool isInMenu),( isInMenu ),
   "@brief Called whenever the mouse enters, or persists is in the menu.\n\n"
   "@param isInMenu True if the mouse has entered the menu, otherwise is false.\n"
   "@note To receive this callback, call setProcessTicks(true) on the menu bar.\n"
   "@tsexample\n"
   "// Mouse enters or persists within the menu, causing the callback to occur.\n"
   "GuiMenuBar::onMouseInMenu(%this,%hasLeftMenu)\n"
   "{\n"
   "  // Code to run when the callback occurs\n"
   "}\n"
   "@endtsexample\n\n"
   "@see GuiTickCtrl\n\n"
);

IMPLEMENT_CALLBACK( GuiMenuBar, onMenuSelect, void, ( S32 menuId, const char* menuText ),( menuId , menuText ),
   "@brief Called whenever a menu is selected.\n\n"
   "@param menuId Index id of the clicked menu\n"
   "@param menuText Text of the clicked menu\n\n"
   "@tsexample\n"
   "// A menu has been selected, causing the callback to occur.\n"
   "GuiMenuBar::onMenuSelect(%this,%menuId,%menuText)\n"
   "{\n"
   "  // Code to run when the callback occurs\n"
   "}\n"
   "@endtsexample\n\n"
   "@see GuiTickCtrl\n\n"
);

IMPLEMENT_CALLBACK( GuiMenuBar, onMenuItemSelect, void, ( S32 menuId, const char* menuText, S32 menuItemId, const char* menuItemText ),
                                       ( menuId, menuText, menuItemId, menuItemText ),
   "@brief Called whenever an item in a menu is selected.\n\n"
   "@param menuId Index id of the menu which contains the selected menu item\n"
   "@param menuText Text of the menu which contains the selected menu item\n\n"
   "@param menuItemId Index id of the selected menu item\n"
   "@param menuItemText Text of the selected menu item\n\n"
   "@tsexample\n"
   "// A menu item has been selected, causing the callback to occur.\n"
   "GuiMenuBar::onMenuItemSelect(%this,%menuId,%menuText,%menuItemId,%menuItemText)\n"
   "{\n"
   "  // Code to run when the callback occurs\n"
   "}\n"
   "@endtsexample\n\n"
   "@see GuiTickCtrl\n\n"
);

//------------------------------------------------------------------------------
// initialization, input and render methods
//------------------------------------------------------------------------------

GuiMenuBar::GuiMenuBar()
{
   //mMenuList.clear();
   menuBarDirty = true;
   mouseDownMenu = NULL;
   mouseOverMenu = NULL;
   mCurAcceleratorIndex = 0;
   mPadding = 0;

   mCheckmarkBitmapIndex = 0; // Default to the first image in the bitmap array for the check mark

   mHorizontalMargin = 6; // Default number of pixels on the left and right side of a manu's text
   mVerticalMargin = 1;   // Default number of pixels on the top and bottom of a menu's text
   mBitmapMargin = 2;     // Default number of pixels between a menu's bitmap and text
   
   mMenubarHeight = 24;

   //  Added:
   mouseDownSubmenu = NULL;
   mouseOverSubmenu = NULL;

   mMouseInMenu = false;

   setProcessTicks(false);
}

void GuiMenuBar::onRemove()
{
   GuiPopupMenuBackgroundCtrl* backgroundCtrl;
   if (Sim::findObject("PopUpMenuControl", backgroundCtrl))
   {
      if (backgroundCtrl->mMenuBarCtrl == this)
         backgroundCtrl->mMenuBarCtrl = nullptr;
   }

   Parent::onRemove();
}

void GuiMenuBar::initPersistFields()
{
   docsURL;
   addField("padding", TypeS32, Offset( mPadding, GuiMenuBar ),"Extra padding to add to the bounds of the control.\n");

   addField("menubarHeight", TypeS32, Offset(mMenubarHeight, GuiMenuBar), "Sets the height of the menubar when attached to the canvas.\n");

   Parent::initPersistFields();
}

bool GuiMenuBar::onWake()
{
   if(!Parent::onWake())
      return false;
   mProfile->constructBitmapArray();  // if a bitmap was specified...
   maxBitmapSize.set(0,0);
   S32 numBitmaps = mProfile->mBitmapArrayRects.size();
   if(numBitmaps)
   {
      RectI *bitmapBounds = mProfile->mBitmapArrayRects.address();
      for(S32 i = 0; i < numBitmaps; i++)
      {
         if(bitmapBounds[i].extent.x > maxBitmapSize.x)
            maxBitmapSize.x = bitmapBounds[i].extent.x;
         if(bitmapBounds[i].extent.y > maxBitmapSize.y)
            maxBitmapSize.y = bitmapBounds[i].extent.y;
      }
   }
   return true;
}

void GuiMenuBar::addObject(SimObject* object)
{
   PopupMenu* popup = dynamic_cast<PopupMenu*>(object);

   if (!popup)
   {
      //if it's not a popup, handle it normally
      Parent::addObject(object);
   }
   else
   {
      //otherwise, if it IS a popup, don't add it as a child object, but instead just insert it as a menu entry
      insert(object, -1);
   }
}

GuiMenuBar::MenuEntry *GuiMenuBar::findHitMenu(Point2I mousePoint)
{
   Point2I pos = globalToLocalCoord(mousePoint);

   for (U32 i = 0; i < mMenuList.size(); ++i)
   {
      if (mMenuList[i].visible && mMenuList[i].bounds.pointInRect(pos))
         return &mMenuList[i];
   }

   return NULL;
}

void GuiMenuBar::onPreRender()
{
   setHeight(mMenubarHeight);

   Parent::onPreRender();
   if (menuBarDirty)
   {
      menuBarDirty = false;
      U32 curX = mPadding;
      for (U32 i = 0; i < mMenuList.size(); ++i)
      {
         if (!mMenuList[i].visible)
            continue;

         // Bounds depends on if there is a bitmap to be drawn or not
         if (mMenuList[i].bitmapIndex == -1)
         {
            // Text only
            mMenuList[i].bounds.set(curX, 0, mProfile->mFont->getStrWidth(mMenuList[i].text) + (mHorizontalMargin * 2), getHeight() - (mVerticalMargin * 2));

         }
         else
         {
            // Will the bitmap and text be draw?
            if (!mMenuList[i].drawBitmapOnly)
            {
               // Draw the bitmap and the text
               RectI *bitmapBounds = mProfile->mBitmapArrayRects.address();
               mMenuList[i].bounds.set(curX, 0, bitmapBounds[mMenuList[i].bitmapIndex].extent.x + mProfile->mFont->getStrWidth(mMenuList[i].text) + (mHorizontalMargin * 2), getHeight() + (mVerticalMargin * 2));

            }
            else
            {
               // Only the bitmap will be drawn
               RectI *bitmapBounds = mProfile->mBitmapArrayRects.address();
               mMenuList[i].bounds.set(curX, 0, bitmapBounds[mMenuList[i].bitmapIndex].extent.x + mBitmapMargin + (mHorizontalMargin * 2), getHeight() + (mVerticalMargin * 2));
            }
         }

         curX += mMenuList[i].bounds.extent.x;
      }
      mouseOverMenu = NULL;
      mouseDownMenu = NULL;
   }
}

void GuiMenuBar::checkMenuMouseMove(const GuiEvent &event)
{
   MenuEntry *hit = findHitMenu(event.mousePoint);
   if(hit && hit != mouseDownMenu)
   {
      // gotta close out the current menu...
      mouseDownMenu->popupMenu->hidePopup();
      
      mouseOverMenu = mouseDownMenu = hit;
      setUpdate();
      onAction();
   }
}

void GuiMenuBar::onMouseMove(const GuiEvent &event)
{
   MenuEntry *hit = findHitMenu(event.mousePoint);

   if (mouseDownMenu != nullptr && hit != nullptr)
   {
      //we have a standing click, so just update and go
      mouseDownMenu = mouseOverMenu = hit;
      setUpdate();
      onAction();

      return;
   }

   mouseOverMenu = hit;
   setUpdate();
}

void GuiMenuBar::onMouseEnter(const GuiEvent &event)
{
   onMouseInMenu_callback(true);
   mMouseInMenu = true;
}

void GuiMenuBar::onMouseLeave(const GuiEvent &event)
{
   if(mouseOverMenu)
      setUpdate();

   mouseOverMenu = NULL;
   mMouseInMenu = false;
}

void GuiMenuBar::onMouseDragged(const GuiEvent &event)
{
}

void GuiMenuBar::onMouseDown(const GuiEvent &event)
{
}

void GuiMenuBar::onMouseUp(const GuiEvent &event)
{
   mouseDownMenu = mouseOverMenu = findHitMenu(event.mousePoint);
   setUpdate();
   onAction();
}

void GuiMenuBar::onRender(Point2I offset, const RectI &updateRect)
{
   Point2I extent = getExtent();

   RectI ctrlRect(offset, extent);

   GFXDrawUtil* drawUtil = GFX->getDrawUtil();

   //if opaque, fill the update rect with the fill color
   if (mProfile->mOpaque)
      drawUtil->drawRectFill(RectI(offset, extent), mProfile->mFillColor);

   //if there's a border, draw the border
   if (mProfile->mBorder)
      renderBorder(ctrlRect, mProfile);

   for (U32 i = 0; i < mMenuList.size(); ++i)
   {
      if (!mMenuList[i].visible)
         continue;

      ColorI fontColor = mProfile->mFontColor;
      RectI bounds = mMenuList[i].bounds;
      bounds.point += offset;

      Point2I start;

      start.x = mMenuList[i].bounds.point.x + mHorizontalMargin;
      start.y = mMenuList[i].bounds.point.y + (mMenuList[i].bounds.extent.y - mProfile->mFont->getHeight()) / 2;

      // Draw the border
      if (mMenuList[i].drawBorder)
      {
         RectI highlightBounds = bounds;
         highlightBounds.inset(1, 1);
         if (&mMenuList[i] == mouseDownMenu)
            renderFilledBorder(highlightBounds, mProfile->mBorderColorHL, mProfile->mFillColorHL);
         else if (&mMenuList[i] == mouseOverMenu && mouseDownMenu == NULL)
            renderFilledBorder(highlightBounds, mProfile->mBorderColorHL, mProfile->mFillColorHL);
      }

      // Do we draw a bitmap?
      if (mMenuList[i].bitmapIndex != -1)
      {
         S32 index = mMenuList[i].bitmapIndex * 3;
         if (&mMenuList[i] == mouseDownMenu)
            ++index;
         else if (&mMenuList[i] == mouseOverMenu && mouseDownMenu == NULL)
            index += 2;

         RectI rect = mProfile->mBitmapArrayRects[index];

         Point2I bitmapstart(start);
         bitmapstart.y = mMenuList[i].bounds.point.y + (mMenuList[i].bounds.extent.y - rect.extent.y) / 2;

         drawUtil->clearBitmapModulation();
         drawUtil->drawBitmapSR(mProfile->getBitmapResource(), offset + bitmapstart, rect);

         // Should we also draw the text?
         if (!mMenuList[i].drawBitmapOnly)
         {
            start.x += mBitmapMargin;
            drawUtil->setBitmapModulation(fontColor);
            drawUtil->drawText(mProfile->mFont, start + offset, mMenuList[i].text, mProfile->mFontColors);
         }
      }
      else
      {
         drawUtil->setBitmapModulation(fontColor);
         drawUtil->drawText(mProfile->mFont, start + offset, mMenuList[i].text, mProfile->mFontColors);
      }
   }

   renderChildControls(offset, updateRect);
}

void GuiMenuBar::buildWindowAcceleratorMap(WindowInputGenerator &inputGenerator)
{
   // ok, accelerator map is cleared...
   // add all our keys:
   mCurAcceleratorIndex = 1;

   for (U32 i = 0; i < mMenuList.size(); ++i)
   {
      for (U32 item = 0; item < mMenuList[i].popupMenu->mMenuItems.size(); item++)
      {
         if (!mMenuList[i].popupMenu->mMenuItems[item].mAccelerator)
         {
            mMenuList[i].popupMenu->mMenuItems[item].mAccelerator = 0;
            continue;
         }

         EventDescriptor accelEvent;
         ActionMap::createEventDescriptor(mMenuList[i].popupMenu->mMenuItems[item].mAccelerator, &accelEvent);

         //now we have a modifier, and a key, add them to the canvas
         inputGenerator.addAcceleratorKey(this, mMenuList[i].popupMenu->mMenuItems[item].mCMD, accelEvent.eventCode, accelEvent.flags);

         mMenuList[i].popupMenu->mMenuItems[item].mAcceleratorIndex = mCurAcceleratorIndex;
         mCurAcceleratorIndex++;
      }
   }
}

void GuiMenuBar::removeWindowAcceleratorMap( WindowInputGenerator &inputGenerator )
{
    inputGenerator.removeAcceleratorKeys( this );
}

void GuiMenuBar::acceleratorKeyPress(U32 index)
{
   // loop through all the menus
   // and find the item that corresponds to the accelerator index
   for (U32 i = 0; i < mMenuList.size(); ++i)
   {
      if (!mMenuList[i].visible)
         continue;

      for(U32 item = 0; item < mMenuList[i].popupMenu->mMenuItems.size(); item++)
      {
         if(mMenuList[i].popupMenu->mMenuItems[item].mAcceleratorIndex == index)
         {
            // first, call the script callback for menu selection:
            onMenuSelect_callback(mMenuList[i].popupMenu->getId(), mMenuList[i].text);
            return;
         }
      }
   }
}

void GuiMenuBar::onSleep()
{
   Parent::onSleep();
}

//------------------------------------------------------------------------------
void GuiMenuBar::onAction()
{
   if(!mouseDownMenu)
      return;

   mouseDownMenu->popupMenu->hidePopup();

   // first, call the script callback for menu selection:
   onMenuSelect_callback(mouseDownMenu->popupMenu->getId(), mouseDownMenu->text);

   mouseDownMenu->popupMenu->mMenuBarCtrl = this;

   GuiCanvas *root = getRoot();
   Point2I pos = Point2I(mouseDownMenu->bounds.point.x, mouseDownMenu->bounds.point.y + mouseDownMenu->bounds.extent.y);
   mouseDownMenu->popupMenu->showPopup(root, pos.x, pos.y);
}

//  Process a tick
void GuiMenuBar::processTick()
{
   if(mMouseInMenu)
      onMouseInMenu_callback(true);
}

void GuiMenuBar::insert(SimObject* pObject, S32 pos)
{
   PopupMenu* menu = dynamic_cast<PopupMenu*>(pObject);
   if (menu == nullptr)
   {
      Con::errorf("GuiMenuBar::insert() - attempted to insert non-popupMenu object: %d", pObject->getId());
      return;
   }

   MenuEntry newMenu;
   newMenu.pos = pos >= mMenuList.size() || pos == -1 ? pos = mMenuList.size() : pos;
   newMenu.drawBitmapOnly = false;
   newMenu.drawBorder = true;
   newMenu.bitmapIndex = -1;
   newMenu.text = menu->mBarTitle;
   newMenu.visible = true;
   newMenu.popupMenu = menu;

   if (pos >= mMenuList.size() || pos == -1)
      mMenuList.push_back(newMenu);
   else
      mMenuList.insert(pos, newMenu);

   menuBarDirty = true; //ensure we refresh
}

void GuiMenuBar::remove(SimObject* pObject)
{
   PopupMenu* menu = dynamic_cast<PopupMenu*>(pObject);
   if (menu == nullptr)
   {
      Con::errorf("GuiMenuBar::remove() - attempted to remove non-popupMenu object: %d", pObject->getId());
      return;
   }

   for(U32 i=0; i < mMenuList.size(); i++)
   {
      if(mMenuList[i].popupMenu == menu)
      {
                 mMenuList.erase(i);
         menuBarDirty = true; //ensure we refresh
         return;
      }
   }
}

PopupMenu* GuiMenuBar::getMenu(U32 index)
{
   if (index >= mMenuList.size())
      return nullptr;

   return mMenuList[index].popupMenu;
}

PopupMenu* GuiMenuBar::findMenu(String barTitle)
{
   for (U32 i = 0; i < mMenuList.size(); i++)
   {
      if (String::ToLower(mMenuList[i].text) == String::ToLower(barTitle))
         return mMenuList[i].popupMenu;
   }

   return nullptr;
}

//-----------------------------------------------------------------------------
// Console Methods
//-----------------------------------------------------------------------------
#ifdef TORQUE_TOOLS
DefineEngineMethod(GuiMenuBar, attachToCanvas, void, (const char *canvas, S32 pos), , "(GuiCanvas, pos)")
{
   GuiCanvas* canv = dynamic_cast<GuiCanvas*>(Sim::findObject(canvas));
   if (canv)
   {
      canv->setMenuBar(object);
   }
}

DefineEngineMethod(GuiMenuBar, removeFromCanvas, void, (), , "()")
{
   GuiCanvas* canvas = object->getRoot();

   if(canvas)
      canvas->setMenuBar(nullptr);
}
#endif

DefineEngineMethod(GuiMenuBar, getMenuCount, S32, (), , "()")
{
   return object->getMenuListCount();
}

DefineEngineMethod(GuiMenuBar, getMenu, S32, (S32 index), (0), "(Index)")
{
   return object->getMenu(index)->getId();
}

//-----------------------------------------------------------------------------
DefineEngineMethod(GuiMenuBar, insert, void, (SimObject* pObject, S32 pos), (nullAsType<SimObject*>(), -1), "(object, pos) insert object at position")
{
   if(pObject == nullptr)
   {
      Con::errorf("GuiMenuBar::insert() - null object");
      return;
   }
   object->insert(pObject, pos);
}

DefineEngineMethod(GuiMenuBar, remove, void, (SimObject* pObject), (nullAsType<SimObject*>()), "(object, pos) remove object")
{
   if (pObject == nullptr)
   {
      Con::errorf("GuiMenuBar::remove() - null object");
      return;
   }
   object->remove(pObject);
}


DefineEngineMethod(GuiMenuBar, findMenu, S32, (const char* barTitle), (""), "(barTitle)")
{
   PopupMenu* menu = object->findMenu(barTitle);

   if (menu)
      return menu->getId();
   else
      return 0;
}
