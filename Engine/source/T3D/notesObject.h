#pragma once

#ifndef _SCENEOBJECT_H_
#include "scene/sceneObject.h"
#endif
#ifndef _GFXSTATEBLOCK_H_
#include "gfx/gfxStateBlock.h"
#endif
#ifndef _GFXVERTEXBUFFER_H_
#include "gfx/gfxVertexBuffer.h"
#endif
#ifndef _GFXPRIMITIVEBUFFER_H_
#include "gfx/gfxPrimitiveBuffer.h"
#endif

//-----------------------------------------------------------------------------
// This class implements a basic SceneObject that can exist in the world at a
// 3D position and render itself. Note that NotesObject handles its own
// rendering by submitting itself as an ObjectRenderInst (see
// renderInstance\renderPassmanager.h) along with a delegate for its render()
// function. However, the preffered rendering method in the engine is to submit
// a MeshRenderInst along with a Material, vertex buffer, primitive buffer, and
// transform and allow the RenderMeshMgr handle the actual rendering. You can
// see this implemented in RenderMeshExample.
//-----------------------------------------------------------------------------

class NotesObject : public SceneObject
{
   typedef SceneObject Parent;

   String mNote;
   bool mShowArrow;
   F32 mArrowLength;
   F32 mArrowRadius;

   LinearColorF mArrowColor;

   // Networking masks
   // We need to implement at least one of these to allow
   // the client version of the object to receive updates
   // from the server version (like if it has been moved
   // or edited)
   enum MaskBits
   {
      TransformMask = Parent::NextFreeMask << 0,
      NextFreeMask = Parent::NextFreeMask << 1
   };

   //--------------------------------------------------------------------------
   // Rendering variables
   //--------------------------------------------------------------------------
   // Define our vertex format here so we don't have to
   // change it in multiple spots later
   typedef GFXVertexPCN VertexType;

   // The handles for our StateBlocks
   GFXStateBlockRef mNormalSB;
   GFXStateBlockRef mReflectSB;

   // The GFX vertex and primitive buffers
   GFXVertexBufferHandle< VertexType > mVertexBuffer;

public:
   NotesObject();
   virtual ~NotesObject();

   // Declare this object as a ConsoleObject so that we can
   // instantiate it into the world and network it
   DECLARE_CONOBJECT(NotesObject);
   DECLARE_CATEGORY("Markers");

   //--------------------------------------------------------------------------
   // Object Editing
   // Since there is always a server and a client object in Torque and we
   // actually edit the server object we need to implement some basic
   // networking functions
   //--------------------------------------------------------------------------
   // Set up any fields that we want to be editable (like position)
   static void initPersistFields();

   void inspectPostApply() override;

   // Handle when we are added to the scene and removed from the scene
   bool onAdd() override;
   void onRemove() override;

   // Override this so that we can dirty the network flag when it is called
   void setTransform(const MatrixF& mat) override;

   // This function handles sending the relevant data from the server
   // object to the client object
   U32 packUpdate(NetConnection* conn, U32 mask, BitStream* stream) override;
   // This function handles receiving relevant data from the server
   // object and applying it to the client object
   void unpackUpdate(NetConnection* conn, BitStream* stream) override;

   // This is the function that allows this object to submit itself for rendering
   void prepRenderImage(SceneRenderState* state) override;

   void _render(ObjectRenderInst* ri, SceneRenderState* state, BaseMatInstance* overrideMat);

   String getNote() { return mNote; }
   bool showArrow() { return mShowArrow; }
};
