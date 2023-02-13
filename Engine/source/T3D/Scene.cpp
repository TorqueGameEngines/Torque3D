#include "Scene.h"
#include "T3D/assets/LevelAsset.h"

Scene * Scene::smRootScene = nullptr;
Vector<Scene*> Scene::smSceneList;

IMPLEMENT_CO_NETOBJECT_V1(Scene);

Scene::Scene() : 
   mIsSubScene(false),
   mParentScene(nullptr),
   mSceneId(-1),
   mIsEditing(false),
   mIsDirty(false),
   mEditPostFX(0)
{
   mGameModeName = StringTable->EmptyString();
}

Scene::~Scene()
{

}

void Scene::initPersistFields()
{
   docsURL;
   Parent::initPersistFields();

   addGroup("Internal");
   addField("isSubscene", TypeBool, Offset(mIsSubScene, Scene), "", AbstractClassRep::FIELD_HideInInspectors);
   addField("isEditing", TypeBool, Offset(mIsEditing, Scene), "", AbstractClassRep::FIELD_HideInInspectors);
   addField("isDirty", TypeBool, Offset(mIsDirty, Scene), "", AbstractClassRep::FIELD_HideInInspectors);
   endGroup("Internal");

   addGroup("Gameplay");
   addField("gameModeName", TypeString, Offset(mGameModeName, Scene), "The name of the gamemode that this scene utilizes");
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

   /*if (smRootScene == nullptr)
   {
      //we're the first scene, so we're the root. woo!
      smRootScene = this;
   }
   else
   {
      mIsSubScene = true;
      smRootScene->mSubScenes.push_back(this);
   }*/

   return true;
}

void Scene::onRemove()
{
   Parent::onRemove();

   smSceneList.remove(this);
   mSceneId = -1;

   /*if (smRootScene == this)
   {
      for (U32 i = 0; i < mSubScenes.size(); i++)
      {
         mSubScenes[i]->deleteObject();
      }
   }
   else if (smRootScene != nullptr)
   {
      for (U32 i = 0; i < mSubScenes.size(); i++)
      {
         if(mSubScenes[i]->getId() == getId())
            smRootScene->mSubScenes.erase(i);
      }
   }*/
}

void Scene::onPostAdd()
{
   if (isMethod("onPostAdd"))
      Con::executef(this, "onPostAdd");
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
   Scene* scene = dynamic_cast<Scene*>(object);
   if (scene)
   {
      //We'll keep these principly separate so they don't get saved into each other
      mSubScenes.push_back(scene);
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
   Scene* scene = dynamic_cast<Scene*>(object);
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

void Scene::addDynamicObject(SceneObject* object)
{
   mDynamicObjects.push_back(object);

   //Do it like regular, though we should probably bail if we're trying to add non-scene objects to the scene?
   Parent::addObject(object);
}

void Scene::removeDynamicObject(SceneObject* object)
{
   mDynamicObjects.remove(object);

   //Do it like regular, though we should probably bail if we're trying to add non-scene objects to the scene?
   Parent::removeObject(object);
}

void Scene::interpolateTick(F32 delta)
{

}

void Scene::processTick()
{

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
   for (U32 i = 0; i < mPermanentObjects.size(); i++)
   {
      mPermanentObjects[i]->getUtilizedAssets(&utilizedAssetsList);
   }

   for (U32 i = 0; i < mDynamicObjects.size(); i++)
   {
      mDynamicObjects[i]->getUtilizedAssets(&utilizedAssetsList);
   }

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
   //So, we ultimately want to not only save out the level, but also collate all the assets utilized
   //by the static objects in the scene so we can have those before we parse the level file itself
   //Useful for preloading or stat tracking

   //First, save the level file
   if (fileName == StringTable->EmptyString())
   {
      fileName = getOriginatingFile();
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
Vector<SceneObject*> Scene::getObjectsByClass(String className, bool checkSubscenes)
{
   return Vector<SceneObject*>();
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
   "Get the root Scene object that is loaded.\n"
   "@return The id of the Root Scene. Will be 0 if no root scene is loaded")
{
   object->addDynamicObject(sceneObj);
}

DefineEngineMethod(Scene, removeDynamicObject, void, (SceneObject* sceneObj), (nullAsType<SceneObject*>()),
   "Get the root Scene object that is loaded.\n"
   "@return The id of the Root Scene. Will be 0 if no root scene is loaded")
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
   "@param selectedOnly If true, only objects marked as selected will be saved out.\n"
   "@param preAppendString Text which will be preprended directly to the object serialization.\n"
   "@param True on success, false on failure.")
{
   return object->saveScene(StringTable->insert(fileName));
}
