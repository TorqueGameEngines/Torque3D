#pragma once

#include "ImageAsset.h"

#ifndef _GUI_INSPECTOR_TYPES_H_
#include "gui/editor/guiInspectorTypes.h"
#endif
#include <gui/controls/guiBitmapCtrl.h>
#include <gui/controls/guiPopUpCtrl.h>

#ifdef TORQUE_TOOLS
class GuiInspectorTypeImageAssetPtr : public GuiInspectorTypeFileName
{
   typedef GuiInspectorTypeFileName Parent;
public:

   GuiTextCtrl* mLabel = NULL;
   GuiBitmapButtonCtrl* mPreviewBorderButton = NULL;
   GuiBitmapCtrl* mPreviewImage = NULL;
   GuiBitmapButtonCtrl* mEditButton = NULL;

   /// Lets the user see and change the resolved ImageAsset's own filtering
   /// setting (GFXTextureFilterType) right from this field, without having
   /// to dig into the asset editor. The ImageAsset is the ground truth here
   /// -- this writes directly onto the resolved asset instance, not onto
   /// whatever object/field this inspector row is otherwise editing.
   GuiPopUpMenuCtrl* mFilterTypePopup = NULL;

   bool mIsDeleteButtonVisible;

   DECLARE_CONOBJECT(GuiInspectorTypeImageAssetPtr);
   static void consoleInit();

   GuiControl* constructEditControl() override;
   bool updateRects() override;
   bool renderTooltip(const Point2I& hoverPos, const Point2I& cursorPos, const char* tipText = NULL);

   void updateValue() override;

   void updatePreviewImage();
   void setPreviewImage(StringTableEntry assetId);

   /// Resolves the ImageAsset currently referenced by this field's value
   /// (the asset ID string) to a live pointer. Returns NULL if the field
   /// is empty, points at a named target, or the asset can't be found.
   AssetPtr<ImageAsset> resolveImageAsset();

   /// Rebuilds the filter type popup's entries and syncs its current
   /// selection from the resolved ImageAsset's getFilterType().
   void updateFilterTypePopup();

   /// Fired when the popup's selection changes; writes the chosen filter
   /// type directly onto the resolved ImageAsset.
   void onFilterTypeSelected();

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

class GuiInspectorTypeImageAssetRef : public GuiInspectorTypeImageAssetPtr
{
   typedef GuiInspectorTypeImageAssetPtr Parent;
public:

   DECLARE_CONOBJECT(GuiInspectorTypeImageAssetRef);
   static void consoleInit();
};
#endif
