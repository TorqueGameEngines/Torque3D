#include "Scene.h"
#include "T3D/assets/LevelAsset.h"
#include "T3D/gameBase/gameConnection.h"
#include "T3D/gameMode.h"

Scene * Scene::smRootScene = nullptr;
Vector<Scene*> Scene::smSceneList;

IMPLEMENT_CALLBACK(Scene, onSaving, void, (const char* fileName), (fileName),
   "@brief Called when a scene is saved to allow scenes to special-handle prepwork for saving if required.\n\n"

   "@param fileName The level file being saved\n");

IMPLEMENT_CO_NETOBJECT_V1(Scene);

Scene::Scene() : 
   mParentScene(nullptr),
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

   Parent::onRemove();

   smSceneList.remove(this);
   mSceneId = -1;
}

void Scene::onPostAdd()
{
   if (isMethod("onPostAdd"))
      Con::executef(this, "onPostAdd");

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

   //iterate over our subscenes to update their status of loaded or unloaded based on if any control objects intersect their bounds
   for (U32 i = 0; i < mSubScenes.size(); i++)
   {
      bool hasClients = false;

      SimGroup* pClientGroup = Sim::getClientGroup();
      for (SimGroup::iterator itr = pClientGroup->begin(); itr != pClientGroup->end(); itr++)
      {
         GameConnection* gc = dynamic_cast<GameConnection*>(*itr);
         if (gc)
         {
            GameBase* controlObj = gc->getControlObject();
            if (controlObj == nullptr)
            {
               controlObj = gc->getCameraObject();
            }

            if (mSubScenes[i]->testBox(controlObj != nullptr ? controlObj->getWorldBox() : Box3F::Zero))
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
   if (foundAssetcount == 0)
      return StringTable->EmptyString();
   else
      return query->mAssetList[0];
}

bool Scene::saveScene(StringTableEntry fileName)
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
   for (U32 i = 0; i < mSubScenes.size(); i++)
   {
      mSubScenes[i]->save();
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
Vector<SceneObject*> Scene::getObjectsByClass(String className)
{
   return Vector<SceneObject*>();
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

DefineEngineFunction(getScene, Scene*, (U32 sceneId), (0),
   "Get the root Scene object that is loaded.\n"
   "@return The id of the Root Scene. Will be 0 if no root scene is loaded")
{
   if (Scene::smSceneList.empty() || sceneId >= Scene::smSceneList.size())
      return nullptr;

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

DefineEngineMethod(Scene, getObjectsByClass, String, (String className), (""),
   "Get the root Scene object that is loaded.\n"
   "@return The id of the Root Scene. Will be 0 if no root scene is loaded")
{
   if (className == String::EmptyString)
      return "";

   //return object->getObjectsByClass(className);
   return "";
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

DefineEngineMethod(Scene, save, bool, (const char* fileName), (""),
   "Save out the object to the given file.\n"
   "@param fileName The name of the file to save to."
   "@param True on success, false on failure.")
{
   return object->saveScene(StringTable->insert(fileName));
}

DefineEngineMethod(Scene, loadAtPosition, void, (Point3F position), (Point3F::Zero),
   "Loads any subscenes at a given point by force.\n")
{
   object->loadAtPosition(position);
}
