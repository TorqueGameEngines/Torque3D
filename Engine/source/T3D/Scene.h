#pragma once
#ifndef SCENE_H
#include "console/engineAPI.h"

#ifndef _NETOBJECT_H_
#include "sim/netObject.h"
#endif

#ifndef _ITICKABLE_H_
#include "core/iTickable.h"
#endif
#ifndef _SCENEOBJECT_H_
#include "scene/sceneObject.h"
#endif

#ifndef GAME_MODE_H
#include "gameMode.h"
#endif
#ifndef SUB_SCENE_H
#include "SubScene.h"
#endif

/// Scene
/// This object is effectively a smart container to hold and manage any relevent scene objects and data
/// used to run things.
class Scene : public NetObject, public virtual ITickable
{
   typedef NetObject Parent;

   Scene* mParentScene;

   Vector<SubScene*> mSubScenes;

   Vector<SimObject*> mPermanentObjects;
   Vector<SimObject*> mDynamicObjects;

   S32 mSceneId;

   bool mIsEditing;

   bool mIsDirty;

   bool mEditPostFX;

   StringTableEntry mGameModesNames;
   Vector<GameMode*> mGameModesList;

protected:
   static Scene * smRootScene;

   DECLARE_CONOBJECT(Scene);

public:
   Scene();
   ~Scene();

   static void initPersistFields();

   static bool _editPostEffects(void* object, const char* index, const char* data);

   bool onAdd() override;
   void onRemove() override;
   void onPostAdd() override;

   void interpolateTick(F32 delta) override;
   void processTick() override;
   void advanceTime(F32 timeDelta) override;

   void addObject(SimObject* object) override;
   void removeObject(SimObject* object) override;

   void addDynamicObject(SimObject* object);
   void removeDynamicObject(SimObject* object);
   void clearDynamicObjects() { mDynamicObjects.clear(); }

   void dumpUtilizedAssets();

   StringTableEntry getOriginatingFile();
   StringTableEntry getLevelAsset();

   bool saveScene(StringTableEntry fileName, const bool& saveSubScenes = true);

   //
   //Networking
   U32 packUpdate(NetConnection *conn, U32 mask, BitStream *stream) override;
   void unpackUpdate(NetConnection *conn, BitStream *stream) override;

   //
   void getObjectsByClass(SimObject* object, StringTableEntry className, Vector<SimObject*>* objectsList, bool checkSubscenes = false);

   void getUtilizedAssetsFromSceneObject(SimObject* object, Vector<StringTableEntry>* usedAssetsList);

   template <class T>
   Vector<T*> getObjectsByClass();

   void loadAtPosition(const Point3F& position);

   static Scene *getRootScene() 
   { 
      if (Scene::smSceneList.empty())
         return NULL;

      return Scene::smSceneList[0];
   }

   static Vector<Scene*> smSceneList;

   DECLARE_CALLBACK(void, onSaving, (const char* fileName));
};


template <class T>
Vector<T*> Scene::getObjectsByClass()
{
   Vector<T*> foundObjects;

   T* curObject;

   //first, check ourself
   for (U32 i = 0; i < mPermanentObjects.size(); i++)
   {
      curObject = dynamic_cast<T*>(mPermanentObjects[i]);
      if (curObject)
         foundObjects.push_back(curObject);
   }

   for (U32 i = 0; i < mDynamicObjects.size(); i++)
   {
      curObject = dynamic_cast<T*>(mDynamicObjects[i]);
      if (curObject)
         foundObjects.push_back(curObject);
   }

   return foundObjects;
}
#endif
