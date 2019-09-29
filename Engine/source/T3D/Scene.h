#pragma once

#include "console/engineAPI.h"

#ifndef _NETOBJECT_H_
#include "sim/netObject.h"
#endif

#ifndef _ITICKABLE_H_
#include "core/iTickable.h"
#endif

#include "scene/sceneObject.h"

/// Scene
/// This object is effectively a smart container to hold and manage any relevent scene objects and data
/// used to run things.
class Scene : public NetObject, public virtual ITickable
{
   typedef NetObject Parent;

   bool mIsSubScene;

   Scene* mParentScene;

   Vector<Scene*> mSubScenes;

   Vector<SceneObject*> mPermanentObjects;

   Vector<SceneObject*> mDynamicObjects;

   S32 mSceneId;

   bool mIsEditing;

   bool mIsDirty;

   StringTableEntry mGameModeName;

protected:
   static Scene * smRootScene;

   DECLARE_CONOBJECT(Scene);

public:
   Scene();
   ~Scene();

   static void initPersistFields();

   virtual bool onAdd();
   virtual void onRemove();
   virtual void onPostAdd();

   virtual void interpolateTick(F32 delta);
   virtual void processTick();
   virtual void advanceTime(F32 timeDelta);

   virtual void addObject(SimObject* object);
   virtual void removeObject(SimObject* object);

   void addDynamicObject(SceneObject* object);
   void removeDynamicObject(SceneObject* object);

   //
   //Networking
   U32 packUpdate(NetConnection *conn, U32 mask, BitStream *stream);
   void unpackUpdate(NetConnection *conn, BitStream *stream);

   //
   Vector<SceneObject*> getObjectsByClass(String className, bool checkSubscenes);

   template <class T>
   Vector<T*> getObjectsByClass(bool checkSubscenes);

   static Scene *getRootScene() 
   { 
      if (Scene::smSceneList.empty())
         return nullptr;

      return Scene::smSceneList[0];
   }

   static Vector<Scene*> smSceneList;
};


template <class T>
Vector<T*> Scene::getObjectsByClass(bool checkSubscenes)
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

   if (checkSubscenes)
   {
      for (U32 i = 0; i < mSubScenes.size(); i++)
      {
         Vector<T*> appendList = mSubScenes[i]->getObjectsByClass<T>(true);

         for (U32 a = 0; a < appendList.size(); a++)
         {
            foundObjects.push_back(appendList[a]);
         }
      }
   }

   return foundObjects;
}
