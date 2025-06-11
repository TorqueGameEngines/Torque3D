#pragma once
#ifndef SCENE_GROUP_H
#define SCENE_GROUP_H

#ifndef _SCENEOBJECT_H_
#include "scene/sceneObject.h"
#endif

class SceneGroup : public SceneObject
{
   typedef SceneObject Parent;

public:
   enum MaskBits
   {
      TransformMask = Parent::NextFreeMask << 0,
      NextFreeMask = Parent::NextFreeMask << 1
   };

public:
   SceneGroup();
   virtual ~SceneGroup();

   DECLARE_CONOBJECT(SceneGroup);
   DECLARE_CATEGORY("Object \t Collection");

   static void initPersistFields();

   // SimObject
   bool onAdd() override;
   void onRemove() override;
   void onEditorEnable() override;
   void onEditorDisable() override;
   void inspectPostApply() override;
   void onInspect(GuiInspector* inspector) override;

   // NetObject
   U32 packUpdate(NetConnection* conn, U32 mask, BitStream* stream) override;
   void unpackUpdate(NetConnection* conn, BitStream* stream) override;

   // SceneObject
   void setTransform(const MatrixF& mat) override;
   void setRenderTransform(const MatrixF& mat) override;

   // Object management
   void addObject(SimObject* object) override;
   void removeObject(SimObject* object) override;
   void recalculateBoundingBox();
   void reparentOOBObjects();

   ///
   bool buildPolyList(PolyListContext context, AbstractPolyList* polyList, const Box3F& box, const SphereF& sphere) override { return false; };
   bool buildExportPolyList(ColladaUtils::ExportData* exportData, const Box3F& box, const SphereF&) override { return false; };
   void getUtilizedAssets(Vector<StringTableEntry>* usedAssetsList) override;
};
#endif
