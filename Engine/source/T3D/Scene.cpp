#include "Scene.h"
#include "T3D/assets/LevelAsset.h"
#include "T3D/gameBase/gameConnection.h"
#include "T3D/gameMode.h"
#include "renderInstance/renderProbeMgr.h"
#include "platform/profiler.h"

//Tells a client that objects under the scene have started being ghosted to it.
//The root scene may not exist on the client yet when this arrives, so it is checked for
class ClientSceneGhostingStartingEvent : public NetEvent
{
   typedef NetEvent Parent;

public:
   U32 mNumGhostsPending;

   ClientSceneGhostingStartingEvent() : mNumGhostsPending(0) { mGuaranteeType = Guaranteed; }
   ~ClientSceneGhostingStartingEvent() {}

   void pack(NetConnection* conn, BitStream* stream) override
   {
      stream->write(mNumGhostsPending);
   }
   void write(NetConnection* conn, BitStream* stream) override
   {
      pack(conn, stream);
   }
   void unpack(NetConnection* conn, BitStream* stream) override
   {
      stream->read(&mNumGhostsPending);
   }

   void process(NetConnection* conn) override
   {
      Scene* rootScene = Scene::getRootScene();
      if (rootScene == NULL)
         return;

      rootScene->getClientGhostingStartSignal().trigger(conn, mNumGhostsPending);
      rootScene->onClientGhostingStart_callback(conn, mNumGhostsPending);
   }

   DECLARE_CONOBJECT(ClientSceneGhostingStartingEvent);
};

IMPLEMENT_CO_NETEVENT_V1(ClientSceneGhostingStartingEvent);

ConsoleDocClass(ClientSceneGhostingStartingEvent,
   "@brief Event posted to a client when objects under the scene start being ghosted to it.\n\n"
   "@internal");

//Tells a client that every object the scene expects to ghost to it has been ghosted
class ClientSceneGhostingDoneEvent : public NetEvent
{
   typedef NetEvent Parent;

public:
   ClientSceneGhostingDoneEvent() { mGuaranteeType = Guaranteed; }
   ~ClientSceneGhostingDoneEvent() {}

   void pack(NetConnection*, BitStream* bstream) override {}
   void write(NetConnection*, BitStream* bstream) override {}
   void unpack(NetConnection* /*ps*/, BitStream* bstream) override {}

   void process(NetConnection* conn) override
   {
      Scene* rootScene = Scene::getRootScene();
      if (rootScene == NULL)
         return;

      rootScene->getClientGhostingDoneSignal().trigger(conn);
      rootScene->onClientGhostingDone_callback(conn);
   }

   DECLARE_CONOBJECT(ClientSceneGhostingDoneEvent);
};
IMPLEMENT_CO_NETEVENT_V1(ClientSceneGhostingDoneEvent);

ConsoleDocClass(ClientSceneGhostingDoneEvent,
   "@brief Event posted to a client when everything under the scene that is expected to ghost to it has.\n\n"
   "@internal");

Scene * Scene::smRootScene = NULL;
Vector<Scene*> Scene::smSceneList;

IMPLEMENT_CALLBACK(Scene, onServerGhostingStart, void, (NetConnection* conn, U32 pendingGhosts), (conn, pendingGhosts),
   "@brief Called when a scene has detected that there are new objects in the scene heirarchy being ghosted down to a client.\n"
   "This generally happens because of prefabs, subScenes or SceneGroups being created and prepped to ghost down.\n"
   "This callback specifically for the server to respond to ghosting starting being sent to a client.\n\n"
   "@param conn The NetConnection ghosts are being sent to.\n"
   "@param pendingGhosts The number of ghosted objects that will be transmitted down to client.\n");
IMPLEMENT_CALLBACK(Scene, onServerGhostingDone, void, (NetConnection* conn), (conn),
   "@brief Called when a scene has finished ghosted down new objects in the scene heirarchy to a client.\n"
   "This callback specifically for the server to respond to ghosting finshing being sent to a client.\n\n"
   "@param conn The NetConnection ghosts are being sent to.\n");
IMPLEMENT_CALLBACK(Scene, onClientGhostingStart, void, (NetConnection* conn, U32 pendingGhosts), (conn, pendingGhosts),
   "@brief Called when a scene has detected that there are new objects in the scene heirarchy being ghosted down to a client.\n"
   "This generally happens because of prefabs, subScenes or SceneGroups being created and prepped to ghost down.\n"
   "This callback specifically for the client to respond to ghosting starting being sent from the server.\n\n"
   "@param conn The NetConnection ghosts are being sent to.\n"
   "@param pendingGhosts The number of ghosted objects that will be transmitted down to client.\n");
IMPLEMENT_CALLBACK(Scene, onClientGhostingDone, void, (NetConnection* conn), (conn),
   "@brief Called when a scene has finished ghosted down new objects in the scene heirarchy to a client.\n"
   "This callback specifically for the client to respond to ghosting finishing being sent from the server.\n\n"
   "@param conn The NetConnection ghosts are being sent to.\n");

IMPLEMENT_CALLBACK(Scene, onSaving, void, (const char* fileName), (fileName),   "@brief Called when a scene is saved to allow scenes to special-handle prepwork for saving if required.\n\n"

   "@param fileName The level file being saved\n");

IMPLEMENT_CO_NETOBJECT_V1(Scene);

Scene::Scene() : 
   mParentScene(NULL),
   mSceneId(-1),
   mIsEditing(false),
   mIsDirty(false),
   mEditPostFX(0)
{
   mGameModesNames = StringTable->EmptyString();
}

Scene::~Scene()
{

}

void Scene::initPersistFields()
{
   docsURL;
   Parent::initPersistFields();

   addGroup("Internal");
   addField("isEditing", TypeBool, Offset(mIsEditing, Scene), "", AbstractClassRep::FIELD_HideInInspectors);
   addField("isDirty", TypeBool, Offset(mIsDirty, Scene), "", AbstractClassRep::FIELD_HideInInspectors);
   endGroup("Internal");

   addGroup("Gameplay");
   addField("gameModes", TypeGameModeList, Offset(mGameModesNames, Scene), "The game modes that this Scene is associated with.");
   endGroup("Gameplay");

   addGroup("PostFX");
   addProtectedField("EditPostEffects", TypeBool, Offset(mEditPostFX, Scene),
      &Scene::_editPostEffects, &defaultProtectedGetFn, "Edit Scene's default Post Effects", AbstractClassRep::FieldFlags::FIELD_ComponentInspectors);
   endGroup("PostFX");
}

bool Scene::onAdd()
{
   if (!Parent::onAdd())
      return false;

   smSceneList.push_back(this);
   mSceneId = smSceneList.size() - 1;

   GameMode::findGameModes(mGameModesNames, &mGameModesList);

   return true;
}

void Scene::onRemove()
{
   for (U32 i = 0; i < mGameModesList.size(); i++)
   {
      mGameModesList[i]->onSceneUnloaded_callback();
   }

   //The level's probe atlas roster goes with the root scene
   if (this == getRootScene())
      PROBEMGR->clearLevelAtlas();

   Parent::onRemove();

   smSceneList.remove(this);
   mSceneId = -1;
}

void Scene::onPostAdd()
{
   if (isMethod("onPostAdd"))
      Con::executef(this, "onPostAdd");

   //Only the root scene owns the level's probe atlas. $pref::ReflectionProbes::CurrentLevelPath is already set by now
   if (this == getRootScene())
      PROBEMGR->loadLevelAtlas();

   for (U32 i = 0; i < mGameModesList.size(); i++)
   {
      mGameModesList[i]->onSceneLoaded_callback();
   }
}

bool Scene::_editPostEffects(void* object, const char* index, const char* data)
{
   Scene* scene = static_cast<Scene*>(object);

#ifdef TORQUE_TOOLS
   if(Con::isFunction("editScenePostEffects"))
      Con::executef("editScenePostEffects", scene);
#endif

   return false;
}

void Scene::addObject(SimObject* object)
{
   //Child scene
   SubScene* scene = dynamic_cast<SubScene*>(object);
   if (scene)
   {
      //We'll keep these principly separate so they don't get saved into each other
      mSubScenes.push_back(scene);
      Parent::addObject(object);
      return;
   }

   SceneObject* sceneObj = dynamic_cast<SceneObject*>(object);
   if (sceneObj)
   {
      //We'll operate on the presumption that if it's being added via regular parantage means, it's considered permanent
      mPermanentObjects.push_back(sceneObj);
      Parent::addObject(object);

      return;
   }

   //Do it like regular, though we should probably bail if we're trying to add non-scene objects to the scene?
   Parent::addObject(object);
}

void Scene::removeObject(SimObject* object)
{
   //Child scene
   SubScene* scene = dynamic_cast<SubScene*>(object);
   if (scene)
   {
      //We'll keep these principly separate so they don't get saved into each other
      mSubScenes.remove(scene);
      return;
   }

   SceneObject* sceneObj = dynamic_cast<SceneObject*>(object);
   if (sceneObj)
   {
      //We'll operate on the presumption that if it's being added via regular parantage means, it's considered permanent

      mPermanentObjects.remove(sceneObj);
      Parent::removeObject(object);

      return;
   }

   Parent::removeObject(object);
}

void Scene::addDynamicObject(SimObject* object)
{
   mDynamicObjects.push_back(object);

   SimGroup* cleanupGroup;
   if(Sim::findObject("MissionCleanup", cleanupGroup))
   {
      cleanupGroup->addObject(object);
   }

   //Do it like regular, though we should probably bail if we're trying to add non-scene objects to the scene?
   //Parent::addObject(object);
}

void Scene::removeDynamicObject(SimObject* object)
{
   mDynamicObjects.remove(object);

   SimGroup* cleanupGroup;
   if (Sim::findObject("MissionCleanup", cleanupGroup))
   {
      cleanupGroup->removeObject(object);
   }

   //Do it like regular, though we should probably bail if we're trying to add non-scene objects to the scene?
   //Parent::removeObject(object);
}

void Scene::interpolateTick(F32 delta)
{
}

void Scene::processTick()
{
   if (!isServerObject())
      return;

   SimGroup* pClientGroup = Sim::getClientGroup();

   //Only the root scene tracks ghosting, once per tick for each client
   if (this == getRootScene())
      updateGhostingStatus(pClientGroup);

   //iterate over our subscenes to update their status of loaded or unloaded based on if any control objects intersect their bounds
   for (U32 i = 0; i < mSubScenes.size(); i++)
   {
      bool hasClients = false;

      for (SimGroup::iterator itr = pClientGroup->begin(); itr != pClientGroup->end(); itr++)
      {
         GameConnection* gc = dynamic_cast<GameConnection*>(*itr);
         if (gc)
         {
            GameBase* controlObj = gc->getControlObject();
            if (controlObj == NULL)
            {
               controlObj = gc->getCameraObject();
            }

            if (mSubScenes[i]->testBox(controlObj != NULL ? controlObj->getWorldBox() : Box3F::Zero))
               {
                  //we have a client controlling object in the bounds, so we ensure the contents are loaded
                  hasClients = true;
                  break;
               }
         }
      }

      if (hasClients)
      {
         mSubScenes[i]->setUnloadTimeMS(-1);
         mSubScenes[i]->load();
      }
      else
      {
         if (mSubScenes[i]->isLoaded() && mSubScenes[i]->getUnloadTimsMS() == -1)
         {
            mSubScenes[i]->setUnloadTimeMS(Sim::getCurrentTime());
         }

         if (Sim::getCurrentTime() - mSubScenes[i]->getUnloadTimsMS() > 5000)
            mSubScenes[i]->unload();
      }
   }
}

void Scene::advanceTime(F32 timeDelta)
{

}

U32 Scene::packUpdate(NetConnection *conn, U32 mask, BitStream *stream)
{
   bool ret = Parent::packUpdate(conn, mask, stream);

   return ret;
}

void Scene::unpackUpdate(NetConnection *conn, BitStream *stream)
{

}

void Scene::dumpUtilizedAssets()
{
   Con::printf("Dumping utilized assets in scene!");

   Vector<StringTableEntry> utilizedAssetsList;
   /*for (U32 i = 0; i < mPermanentObjects.size(); i++)
   {
      mPermanentObjects[i]->getUtilizedAssets(&utilizedAssetsList);
   }

   for (U32 i = 0; i < mDynamicObjects.size(); i++)
   {
      mDynamicObjects[i]->getUtilizedAssets(&utilizedAssetsList);
   }*/

   for (U32 i = 0; i < utilizedAssetsList.size(); i++)
   {
      Con::printf("Utilized Asset: %s", utilizedAssetsList[i]);
   }

   Con::printf("Utilized Asset dump complete!");
}

StringTableEntry Scene::getOriginatingFile()
{
   return getFilename();
}

StringTableEntry Scene::getLevelAsset()
{
   StringTableEntry levelFile = getFilename();

   if (levelFile == StringTable->EmptyString())
      return StringTable->EmptyString();

   AssetQuery* query = new AssetQuery();
   query->registerObject();

   S32 foundAssetcount = AssetDatabase.findAssetLooseFile(query, levelFile);
   StringTableEntry assetId = StringTable->EmptyString();
   if (foundAssetcount != 0)
      assetId = query->mAssetList[0];

   query->deleteObject();
   return assetId;
}

bool Scene::saveScene(StringTableEntry fileName, const bool& saveSubScenes)
{
   if (!isServerObject())
      return false;

   //So, we ultimately want to not only save out the level, but also collate all the assets utilized
   //by the static objects in the scene so we can have those before we parse the level file itself
   //Useful for preloading or stat tracking

   //First, save the level file
   if (fileName == StringTable->EmptyString())
   {
      fileName = getOriginatingFile();
   }

   for (SimGroupIterator itr(this); *itr; ++itr)
   {
      if((*itr)->isMethod("onSaving"))
      {
         Con::executef((*itr), "onSaving", fileName);
      }
   }

   //Inform our subscenes we're saving so they can do any
   //special work required as well
   if (saveSubScenes)
   {
      for (U32 i = 0; i < mSubScenes.size(); i++)
      {
         mSubScenes[i]->save();
      }
   }

   bool saveSuccess = save(fileName);

   if (!saveSuccess)
      return false;

   //Get the level asset
   StringTableEntry levelAsset = getLevelAsset();
   if (levelAsset == StringTable->EmptyString())
      return saveSuccess;

   LevelAsset* levelAssetDef = AssetDatabase.acquireAsset<LevelAsset>(levelAsset);
   levelAssetDef->clearAssetDependencyFields("staticObjectAssetDependency");

   //Next, lets build out our 
   Vector<StringTableEntry> utilizedAssetsList;
   for (U32 i = 0; i < size(); i++)
   {
      getUtilizedAssetsFromSceneObject(getObject(i), &utilizedAssetsList);
   }

   for (U32 i = 0; i < utilizedAssetsList.size(); i++)
   {
      char depSlotName[50];
      dSprintf(depSlotName, sizeof(depSlotName), "%s%d", "staticObjectAssetDependency", i);

      char depValue[255];
      dSprintf(depValue, sizeof(depValue), "%s=%s", ASSET_ID_SIGNATURE, utilizedAssetsList[i]);

      levelAssetDef->setDataField(StringTable->insert(depSlotName), NULL, StringTable->insert(depValue));
   }

   //update the gamemode list as well
   levelAssetDef->setDataField(StringTable->insert("gameModesNames"), NULL, StringTable->insert(mGameModesNames));

   //Finally, save
   saveSuccess = levelAssetDef->saveAsset();

   return saveSuccess;
}

void Scene::getUtilizedAssetsFromSceneObject(SimObject* object, Vector<StringTableEntry>* usedAssetsList)
{
   SceneObject* obj = dynamic_cast<SceneObject*>(object);
   if(obj)
      obj->getUtilizedAssets(usedAssetsList);

   SimGroup* group = dynamic_cast<SimGroup*>(object);
   if (group)
   {
      for (U32 c = 0; c < group->size(); c++)
      {
         SceneObject* childObj = dynamic_cast<SceneObject*>(group->getObject(c));

         //Recurse down
         getUtilizedAssetsFromSceneObject(childObj, usedAssetsList);
      }
   }
}

//
void Scene::getObjectsByClass(SimObject* object, StringTableEntry className, Vector<SimObject*>* objectsList, bool checkSubscenes)
{
   if(object->getClassName() == className)
   {
      objectsList->push_back(object);
   }

   //If it's a subscene and we DON'T want to scan through them, bail out now
   SubScene* subScene = dynamic_cast<SubScene*>(object);
   if (subScene && !checkSubscenes)
      return;

   //If possible, now we iterate over the children
   SimGroup* group = dynamic_cast<SimGroup*>(object);
   if (group)
   {
      for (U32 c = 0; c < group->size(); c++)
      {
         SimObject* childObj = dynamic_cast<SimObject*>(group->getObject(c));

         //Recurse down
         getObjectsByClass(childObj, className, objectsList);
      }
   }
}

void Scene::loadAtPosition(const Point3F& position)
{
   for (U32 i = 0; i < mSubScenes.size(); i++)
   {
      Box3F testBox = Box3F(0.5);
      testBox.setCenter(position);

      if (mSubScenes[i]->testBox(testBox))
      {
         mSubScenes[i]->setUnloadTimeMS(-1);
         mSubScenes[i]->load();
      }
   }
}

U32 Scene::getUnghostedObjectCount(NetConnection* conn, SimObject* root)
{
   if (conn == NULL || !conn->isGhosting())
      return 0;

   if (root == NULL)
      root = this;

   //Only objects guaranteed to ghost to every client (Ghostable and ScopeAlways) are counted, as anything scoped by
   //distance could stay unghosted indefinitely. SpecialScope objects are handled outside normal ghosting and are skipped
   U32 unghostedObjects = 0;
   for (SimGroupIterator itr(dynamic_cast<SimGroup*>(root)); *itr; ++itr)
   {
      NetObject* netObj = dynamic_cast<NetObject*>((*itr));

      if (netObj == NULL || netObj->isSpecialScope() || !netObj->isGhostAlways())
         continue;

      if (conn->getGhostIndex(netObj) == -1)
         unghostedObjects++;
   }

   return unghostedObjects;
}

void Scene::updateGhostingStatus(SimGroup* clientGroup)
{
   PROFILE_SCOPE(Scene_updateGhostingStatus);

   //Drop connections that have gone away
   for (Map<NetConnection*, GhostingStatus>::Iterator statusItr = mClientGhostingStatus.begin(); statusItr != mClientGhostingStatus.end();)
   {
      bool stillConnected = false;
      for (SimGroup::iterator itr = clientGroup->begin(); itr != clientGroup->end() && !stillConnected; itr++)
         stillConnected = (dynamic_cast<NetConnection*>(*itr) == statusItr->key);

      if (stillConnected)
      {
         ++statusItr;
      }
      else
      {
         NetConnection* gone = statusItr->key;
         ++statusItr;
         mClientGhostingStatus.erase(gone);
      }
   }

   for (SimGroup::iterator itr = clientGroup->begin(); itr != clientGroup->end(); itr++)
   {
      NetConnection* conn = dynamic_cast<NetConnection*>(*itr);
      if (conn == NULL)
         continue;

      //Ensure we have tracking for this client
      if (!mClientGhostingStatus.contains(conn))
         mClientGhostingStatus.insert(conn, GhostingStatus::Done);

      const U32 unghostedObjCount = getUnghostedObjectCount(conn);
      if (unghostedObjCount != 0)
      {
         //Check if the status has changed, if so do our callbacks
         if (mClientGhostingStatus[conn] == GhostingStatus::Done)
         {
            onServerGhostingStart_callback(conn, unghostedObjCount);

            getServerGhostingStartSignal().trigger(conn, unghostedObjCount);

            //Now inform the client
            ClientSceneGhostingStartingEvent* event = new ClientSceneGhostingStartingEvent();
            event->mNumGhostsPending = unghostedObjCount;
            conn->postNetEvent(event);

            mClientGhostingStatus[conn] = GhostingStatus::InProgress;
         }
      }
      else if (mClientGhostingStatus[conn] == GhostingStatus::InProgress)
      {
         //We must've hit the end of the current run, so kick our callbacks
         onServerGhostingDone_callback(conn);

         getServerGhostingDoneSignal().trigger(conn);

         //Now inform the client
         ClientSceneGhostingDoneEvent* event = new ClientSceneGhostingDoneEvent();
         conn->postNetEvent(event);

         mClientGhostingStatus[conn] = GhostingStatus::Done;
      }
   }
}

SubScene* Scene::getSubScene(U32 index)
{
   if (index >= mSubScenes.size())
      return NULL;

   return mSubScenes[index];
}

SubScene* Scene::findOwningSubScene(SimObject* object)
{
   if (object == NULL)
      return NULL;

   //Walk up the SimGroup chain until a SubScene or this scene is reached
   SimGroup* group = object->getGroup();
   while (group != NULL && group != this)
   {
      SubScene* subScene = dynamic_cast<SubScene*>(group);
      if (subScene != NULL)
         return subScene;

      group = group->getGroup();
   }

   return NULL;
}

bool Scene::loadSubScene(U32 index)
{
   SubScene* subScene = getSubScene(index);
   if (subScene == NULL)
      return false;

   subScene->setPinned(true);
   subScene->setUnloadTimeMS(-1);
   subScene->load();

   return subScene->isLoaded();
}

void Scene::releaseSubScene(U32 index)
{
   SubScene* subScene = getSubScene(index);
   if (subScene == NULL)
      return;

   subScene->setPinned(false);
   subScene->setUnloadTimeMS(Sim::getCurrentTime());
}

DefineEngineFunction(getScene, Scene*, (U32 sceneId), (0),   "Get the root Scene object that is loaded.\n"
   "@return The id of the Root Scene. Will be 0 if no root scene is loaded")
{
   if (Scene::smSceneList.empty() || sceneId >= Scene::smSceneList.size())
      return NULL;

   return Scene::smSceneList[sceneId];
}

DefineEngineFunction(getSceneCount, S32, (),,
   "Get the number of active Scene objects that are loaded.\n"
   "@return The number of active scenes")
{
   return Scene::smSceneList.size();
}

DefineEngineFunction(getRootScene, S32, (), ,
   "Get the root Scene object that is loaded.\n"
   "@return The id of the Root Scene. Will be 0 if no root scene is loaded")
{
   Scene* root = Scene::getRootScene();

   if (root)
      return root->getId();

   return 0;
}

DefineEngineMethod(Scene, getRootScene, S32, (),,
   "Get the root Scene object that is loaded.\n"
   "@return The id of the Root Scene. Will be 0 if no root scene is loaded")
{
   Scene* root = Scene::getRootScene();

   if (root)
      return root->getId();

   return 0;
}

DefineEngineMethod(Scene, addDynamicObject, void, (SceneObject* sceneObj), (nullAsType<SceneObject*>()),
   "Adds an object to the scene's dynamic objects list. Used for things spawned as part of gameplay and not permanent objects to be saved out as part of the level proper.")
{
   object->addDynamicObject(sceneObj);
}

DefineEngineMethod(Scene, clearDynamicObjects, void, (),,
   "Clears all objects from the scene's dynamic objects list.")
{
   object->clearDynamicObjects();
}

DefineEngineMethod(Scene, removeDynamicObject, void, (SceneObject* sceneObj), (nullAsType<SceneObject*>()),
   "Removes an object from the scene's dynamic objects list.")
{
   object->removeDynamicObject(sceneObj);
}

DefineEngineMethod(Scene, findOwningSubScene, SubScene*, (SimObject* sceneObj), (nullAsType<SimObject*>()),
   "Finds the SubScene an object is in, by walking up its groups.\n"
   "@param sceneObj The object to look up.\n"
   "@return The SubScene that contains the object, or null if it is not in one.")
{
   return object->findOwningSubScene(sceneObj);
}

DefineEngineMethod(Scene, getObjectsByClass, String, (String className, bool checkSubScenes), ("", false),
   "Get the root Scene object that is loaded.\n"
   "@param className The name of the class of objects to get a list of.\n"
   "@param checkSubScenes If true, will also scan through currently loaded subscenes to get matching objects.\n"
   "@return A space-separated list of object ids that match the searched-for className")
{
   if (className == String::EmptyString)
      return "";

   Vector<SimObject*>* objectsList = new Vector<SimObject*>();

   object->getObjectsByClass(object, StringTable->insert(className.c_str()), objectsList, checkSubScenes);

   char* retBuffer = Con::getReturnBuffer(1024);

   U32 len = 0;
   S32 i;
   //Get the length of our return string
   for(i=0; i < objectsList->size(); i++)
      len += dStrlen((*objectsList)[i]->getIdString());

   char* ret = Con::getReturnBuffer(len + 1);
   ret[0] = 0;
   for (i = 0; i < objectsList->size(); i++)
   {
      dStrcat(ret, (*objectsList)[i]->getIdString(), len + 1);
      dStrcat(ret, " ", len + 1);
   }
      

   return ret;
}

DefineEngineMethod(Scene, dumpUtilizedAssets, void, (), ,
   "Get the root Scene object that is loaded.\n"
   "@return The id of the Root Scene. Will be 0 if no root scene is loaded")
{
   object->dumpUtilizedAssets();
}

DefineEngineMethod(Scene, getOriginatingFile, const char*, (), ,
   "Get the root Scene object that is loaded.\n"
   "@return The id of the Root Scene. Will be 0 if no root scene is loaded")
{
   return object->getOriginatingFile();
}

DefineEngineMethod(Scene, getLevelAsset, const char*, (), ,
   "Get the root Scene object that is loaded.\n"
   "@return The id of the Root Scene. Will be 0 if no root scene is loaded")
{
   return object->getLevelAsset();
}

DefineEngineMethod(Scene, save, bool, (const char* fileName, bool saveSubScenes), ("", true),
   "Save out the object to the given file.\n"
   "@param fileName The name of the file to save to."
   "@param True on success, false on failure.")
{
   return object->saveScene(StringTable->insert(fileName), saveSubScenes);
}

DefineEngineMethod(Scene, getSubSceneCount, S32, (), ,
   "Gets the number of SubScenes in the scene, loaded or not.\n")
{
   return object->getSubSceneCount();
}

DefineEngineMethod(Scene, loadSubScene, bool, (S32 index), ,
   "Loads the SubScene at the given index and keeps it loaded until releaseSubScene() is called.\n"
   "@return True if the SubScene is loaded.")
{
   return object->loadSubScene(index);
}

DefineEngineMethod(Scene, releaseSubScene, void, (S32 index), ,
   "Allows a SubScene loaded with loadSubScene() to unload normally again.\n")
{
   object->releaseSubScene(index);
}

DefineEngineMethod(Scene, loadAtPosition, void, (Point3F position), (Point3F::Zero),   "Loads any subscenes at a given point by force.\n")
{
   object->loadAtPosition(position);
}
