#pragma once

#ifndef _SHAPEDATABLOCKEXAMPLE_H_
#define _SHAPEDATABLOCKEXAMPLE_H_

#ifndef _GAMEBASE_H_
#include "T3D/gameBase/gameBase.h"
#endif
#ifndef _TSSHAPEINSTANCE_H_
#include "ts/tsShapeInstance.h"
#endif

#include "T3D/assets/ShapeAsset.h"

struct ShapeDatablockExampleData : public GameBaseData, protected AssetPtrCallback
{
private:
   typedef GameBaseData Parent;

public:
   AssetRef<ShapeAsset> shapeAssetRef;

   // The derived class should provide the following:
   DECLARE_CONOBJECT(ShapeDatablockExampleData);
   DECLARE_CATEGORY("Datablock");
   ShapeDatablockExampleData();
   ShapeDatablockExampleData(const ShapeDatablockExampleData&, bool = false);
   ~ShapeDatablockExampleData();

   static void initPersistFields();
   bool preload(bool server, String& errorStr) override;
   void packData(BitStream* stream) override;
   void unpackData(BitStream* stream) override;

protected:
   void onAssetRefreshed(AssetPtrBase* pAssetPtrBase) override
   {
      reloadOnLocalClient();
   }
};

class ShapeDatablockExample : public GameBase
{
   typedef GameBase Parent;

   ShapeDatablockExampleData* mDataBlock;

   // Networking masks
   // We need to implement a mask specifically to handle
   // updating our transform from the server object to its
   // client-side "ghost". We also need to implement a
   // maks for handling editor updates to our properties
   // (like material).
   enum MaskBits
   {
      TransformMask = Parent::NextFreeMask << 0,
      UpdateMask = Parent::NextFreeMask << 1,
      NextFreeMask = Parent::NextFreeMask << 2
   };

   // The actual shape instance
   TSShapeInstance* mShapeInstance;

public:
   ShapeDatablockExample();
   virtual ~ShapeDatablockExample();

   // Declare this object as a ConsoleObject so that we can
   // instantiate it into the world and network it
   DECLARE_CONOBJECT(ShapeDatablockExample);

   //--------------------------------------------------------------------------
   // Object Editing
   // Since there is always a server and a client object in Torque and we
   // actually edit the server object we need to implement some basic
   // networking functions
   //--------------------------------------------------------------------------
   // Set up any fields that we want to be editable (like position)
   static void initPersistFields();

   // Handle when we are added to the scene and removed from the scene
   bool onAdd() override;
   void onRemove() override;

   bool onNewDataBlock(GameBaseData* dptr, bool reload) override;

   // Override this so that we can dirty the network flag when it is called
   void setTransform(const MatrixF & mat) override;

   // This function handles sending the relevant data from the server
   // object to the client object
   U32 packUpdate(NetConnection* conn, U32 mask, BitStream* stream) override;
   // This function handles receiving relevant data from the server
   // object and applying it to the client object
   void unpackUpdate(NetConnection* conn, BitStream* stream) override;

   // This is the function that allows this object to submit itself for rendering
   void prepRenderImage(SceneRenderState* state) override;

   void _onDatablockModified();
};

#endif
