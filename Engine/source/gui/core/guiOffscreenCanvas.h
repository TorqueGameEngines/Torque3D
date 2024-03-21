#ifndef _GUIOFFSCREENCANVAS_H_
#define _GUIOFFSCREENCANVAS_H_

#include "math/mMath.h"
#include "gui/core/guiCanvas.h"
#include "core/util/tVector.h"

#ifndef _MATTEXTURETARGET_H_
#include "materials/matTextureTarget.h"
#endif

class GuiTextureDebug;

class GuiOffscreenCanvas : public GuiCanvas
{
public:
   typedef GuiCanvas Parent;
   
   GuiOffscreenCanvas();
   ~GuiOffscreenCanvas();
   
   bool onAdd() override;
   void onRemove() override;
   
   void renderFrame(bool preRenderOnly, bool bufferSwap) override;
   virtual void onFrameRendered();
   
   Point2I getWindowSize() override;

   Point2I getCursorPos() override;
   void setCursorPos(const Point2I &pt) override;
   void showCursor(bool state) override;
   bool isCursorShown() override;
   
   void _onTextureEvent( GFXTexCallbackCode code );

   void _setupTargets();
   void _teardownTargets();

   NamedTexTargetRef getTarget() { return &mNamedTarget; }

   void markDirty() { mTargetDirty = true; }

   static void initPersistFields();
   
   DECLARE_CONOBJECT(GuiOffscreenCanvas);

protected:
   GFXTextureTargetRef mTarget;
   NamedTexTarget mNamedTarget;
   GFXTexHandle mTargetTexture;

   GFXFormat mTargetFormat;
   Point2I mTargetSize;
   String mTargetName;

   bool mTargetDirty;
   bool mDynamicTarget;
   
   bool mUseDepth;
   GFXTexHandle mTargetDepth;

public:
   static Vector<GuiOffscreenCanvas*> sList;
};

#endif
