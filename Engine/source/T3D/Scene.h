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

   enum GhostingStatus
   {
      Done,
      InProgress
   };

   Map<NetConnection*, GhostingStatus> mClientGhostingStatus;

   void updateGhostingStatus(SimGroup* clientGroup);

protected:
   static Scene * smRootScene;

   typedef Signal<void(NetConnection*, U32)> SceneGhostingStartSignal;
   SceneGhostingStartSignal mServerGhostingStartSignal;
   SceneGhostingStartSignal mClientGhostingStartSignal;

   typedef Signal<void(NetConnection*)> SceneGhostingDoneSignal;
   SceneGhostingDoneSignal mServerGhostingDoneSignal;
   SceneGhostingDoneSignal mClientGhostingDoneSignal;

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

   U32 getSubSceneCount() { return mSubScenes.size(); }
   SubScene* getSubScene(U32 index);

   /// Finds the SubScene that contains object, walking up its SimGroup chain. Returns NULL if it is not in one
   SubScene* findOwningSubScene(SimObject* object);

   /// Loads the SubScene and keeps it loaded until releaseSubScene() is called. Returns true if it is loaded.
   bool loadSubScene(U32 index);
   void releaseSubScene(U32 index);

   static Scene *getRootScene() 
   { 
      if (Scene::smSceneList.empty())
         return NULL;

      return Scene::smSceneList[0];
   }

   /// Number of objects under root (this scene by default, or e.g. one SubScene) that are guaranteed to ghost to conn
   /// (Ghostable + ScopeAlways, not SpecialScope) and have not been yet. 0 means everything expected has ghosted.
   U32 getUnghostedObjectCount(NetConnection* conn, SimObject* root = NULL);

   static Vector<Scene*> smSceneList;

public:
   SceneGhostingStartSignal& getServerGhostingStartSignal() { return mServerGhostingStartSignal; }
   SceneGhostingDoneSignal& getServerGhostingDoneSignal() { return mServerGhostingDoneSignal; }
   SceneGhostingStartSignal& getClientGhostingStartSignal() { return mClientGhostingStartSignal; }
   SceneGhostingDoneSignal& getClientGhostingDoneSignal() { return mClientGhostingDoneSignal; }

   DECLARE_CALLBACK(void, onSaving, (const char* fileName));
   DECLARE_CALLBACK(void, onServerGhostingStart, (NetConnection* conn, U32 pendingGhosts));
   DECLARE_CALLBACK(void, onServerGhostingDone, (NetConnection* conn));
   DECLARE_CALLBACK(void, onClientGhostingStart, (NetConnection* conn, U32 pendingGhosts));
   DECLARE_CALLBACK(void, onClientGhostingDone, (NetConnection* conn));
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
