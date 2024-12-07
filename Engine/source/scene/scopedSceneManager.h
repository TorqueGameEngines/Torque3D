#pragma once
#ifndef _SCOPED_SCENE_MANAGER_H_
#define _SCOPED_SCENE_MANAGER_H_

#ifndef _SCENEMANAGER_H_
#include "scene/sceneManager.h"
#endif

/// <summary>
/// Simple class for a scoped scene, place the reference to this class in a function
/// or inbetween { } and it will automatically delete
/// </summary>
class ScopedSceneManager
{
private:

   /// <summary>
   /// The scene to restore when we are out of scope.
   /// </summary>
   SceneManager* mPrevScene;
public:

   /// <summary>
   /// Constructor for the scopedSceneManager, if you new this class be sure to delete it
   /// in the same function.
   /// </summary>
   /// <param name="tempScene">The scene to replace the current scene.</param>
   /// <param name="isClient">Whether this is a replacement for the client (defaults: True).</param>
   ScopedSceneManager(SceneManager* tempScene)
   {
      mPrevScene = getActiveClientScene();

      setActiveClientScene(tempScene);
      setActiveServerScene(tempScene->mServerSide);
      setActiveClientContainer(tempScene->mSceneContainer);
      setActiveServerContainer(tempScene->mServerSide->mSceneContainer);
   }

   ~ScopedSceneManager()
   {
      setActiveClientScene(mPrevScene);
      setActiveServerScene(mPrevScene->mServerSide);
      setActiveClientContainer(mPrevScene->mSceneContainer);
      setActiveServerContainer(mPrevScene->mServerSide->mSceneContainer);
   }
};

#endif
