#include "console/console.h"
#include "console/consoleTypes.h"
#include "gfx/bitmap/gBitmap.h"
#include "gui/core/guiControl.h"
#include "gfx/gfxDevice.h"
#include "gfx/gfxTextureHandle.h"
#include "gfx/gfxDrawUtil.h"
#include "console/engineAPI.h"

#include "T3D/assets/ImageAsset.h"

class GuiChunkedBitmapCtrl : public GuiControl
{
private:
   typedef GuiControl Parent;
   void renderRegion(const Point2I &offset, const Point2I &extent);

protected:

   DECLARE_IMAGEASSET(GuiChunkedBitmapCtrl, Bitmap, onImageChanged, GFXDefaultGUIProfile);
   DECLARE_ASSET_SETGET(GuiChunkedBitmapCtrl, Bitmap);

   bool  mUseVariable;
   bool  mTile;

public:
   //creation methods
   DECLARE_CONOBJECT(GuiChunkedBitmapCtrl);
   DECLARE_CATEGORY( "Gui Images" );
   
   GuiChunkedBitmapCtrl();
   static void initPersistFields();

   //Parental methods
   bool onWake();
   void onSleep();

   void setBitmap(const char *name);

   void onRender(Point2I offset, const RectI &updateRect);

   void onImageChanged() {}
};
