//-----------------------------------------------------------------------------
// Copyright (c) 2014 Daniel Buckmaster
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#include "navMesh.h"
#include "navContext.h"
#include <DetourDebugDraw.h>
#include <RecastDebugDraw.h>

#include "math/mathUtils.h"
#include "math/mRandom.h"
#include "console/consoleTypes.h"
#include "console/engineAPI.h"
#include "console/typeValidators.h"

#include "scene/sceneRenderState.h"
#include "gfx/gfxDrawUtil.h"
#include "renderInstance/renderPassManager.h"
#include "gfx/primBuilder.h"

#include "core/stream/bitStream.h"
#include "math/mathIO.h"

#include "core/stream/fileStream.h"
#include "T3D/assets/LevelAsset.h"

extern bool gEditingMission;

IMPLEMENT_CO_NETOBJECT_V1(NavMesh);

const U32 NavMesh::mMaxVertsPerPoly = DT_VERTS_PER_POLYGON;

SimObjectPtr<SimSet> NavMesh::smServerSet = NULL;

ImplementEnumType(NavMeshWaterMethod,
   "The method used to include water surfaces in the NavMesh.\n")
   { NavMesh::Ignore,     "Ignore",     "Ignore all water surfaces.\n" },
   { NavMesh::Solid,      "Solid",      "Treat water surfaces as solid and walkable.\n" },
   { NavMesh::Impassable, "Impassable", "Treat water as an impassable obstacle.\n" },
EndImplementEnumType;

SimSet *NavMesh::getServerSet()
{
   if(!smServerSet)
   {
      SimSet *set = NULL;
      if(Sim::findObject("ServerNavMeshSet", set))
         smServerSet = set;
      else
      {
         smServerSet = new SimSet();
         smServerSet->registerObject("ServerNavMeshSet");
         Sim::getRootGroup()->addObject(smServerSet);
      }
   }
   return smServerSet;
}

SimObjectPtr<EventManager> NavMesh::smEventManager = NULL;

EventManager *NavMesh::getEventManager()
{
   if(!smEventManager)
   {
      smEventManager = new EventManager();
      smEventManager->registerObject("NavEventManager");
      Sim::getRootGroup()->addObject(smEventManager);
      smEventManager->setMessageQueue("NavEventManagerQueue");
      smEventManager->registerEvent("NavMeshCreated");
      smEventManager->registerEvent("NavMeshRemoved");
      smEventManager->registerEvent("NavMeshStartUpdate");
      smEventManager->registerEvent("NavMeshUpdate");
      smEventManager->registerEvent("NavMeshTileUpdate");
      smEventManager->registerEvent("NavMeshUpdateBox");
      smEventManager->registerEvent("NavMeshObstacleAdded");
      smEventManager->registerEvent("NavMeshObstacleRemoved");
   }
   return smEventManager;
}

DefineEngineFunction(getNavMeshEventManager, S32, (),,
   "@brief Get the EventManager object for all NavMesh updates.")
{
   return NavMesh::getEventManager()->getId();
}

DefineEngineFunction(NavMeshUpdateAll, void, (S32 objid, bool remove), (0, false),
   "@brief Update all NavMesh tiles that intersect the given object's world box.")
{
   SceneObject *obj;
   if(!Sim::findObject(objid, obj))
      return;
   obj->mPathfindingIgnore = remove;
   SimSet *set = NavMesh::getServerSet();
   for(U32 i = 0; i < set->size(); i++)
   {
      NavMesh *m = dynamic_cast<NavMesh*>(set->at(i));
      if (m)
      {
         m->cancelBuild();
         m->buildTiles(obj->getWorldBox());
      }
   }
}

DefineEngineFunction(NavMeshUpdateAroundObject, void, (S32 objid, bool remove), (0, false),
   "@brief Update all NavMesh tiles that intersect the given object's world box.")
{
   SceneObject *obj;
   if (!Sim::findObject(objid, obj))
      return;
   obj->mPathfindingIgnore = remove;
   SimSet *set = NavMesh::getServerSet();
   for (U32 i = 0; i < set->size(); i++)
   {
      NavMesh *m = dynamic_cast<NavMesh*>(set->at(i));
      if (m)
      {
         m->cancelBuild();
         m->buildTiles(obj->getWorldBox());
      }
   }
}


DefineEngineFunction(NavMeshIgnore, void, (S32 objid, bool _ignore), (0, true),
   "@brief Flag this object as not generating a navmesh result.")
{
   SceneObject *obj;
   if(!Sim::findObject(objid, obj))
      return;

      obj->mPathfindingIgnore = _ignore;
}

DefineEngineFunction(NavMeshUpdateOne, void, (S32 meshid, S32 objid, bool remove), (0, 0, false),
   "@brief Update all tiles in a given NavMesh that intersect the given object's world box.")
{
   NavMesh *mesh;
   SceneObject *obj;
   if(!Sim::findObject(meshid, mesh))
   {
      Con::errorf("NavMeshUpdateOne: cannot find NavMesh %d", meshid);
      return;
   }
   if(!Sim::findObject(objid, obj))
   {
      Con::errorf("NavMeshUpdateOne: cannot find SceneObject %d", objid);
      return;
   }
   if(remove)
      obj->disableCollision();
   mesh->buildTiles(obj->getWorldBox());
   if(remove)
      obj->enableCollision();
}

NavMesh::NavMesh()
:  m_triareas(0),
   m_solid(0),
   m_chf(0),
   m_cset(0),
   m_pmesh(0),
   m_dmesh(0),
   m_drawMode(DRAWMODE_NAVMESH)
{
   mTypeMask |= StaticShapeObjectType | MarkerObjectType;
   mFileName = StringTable->EmptyString();
   mNetFlags.clear(Ghostable);

   mSaveIntermediates = false;
   nm = NULL;
   ctx = NULL;
   m_geo = NULL;

   mWaterMethod = Ignore;

   mCellSize = mCellHeight = 0.2f;
   mWalkableHeight = 2.0f;
   mWalkableClimb = 0.5f;
   mWalkableRadius = 0.5f;
   mWalkableSlope = 45.0f;
   mBorderSize = 1;
   mDetailSampleDist = 6.0f;
   mDetailSampleMaxError = 1.0f;
   mMaxEdgeLen = 12;
   mMaxSimplificationError = 1.3f;
   mMinRegionArea = 8;
   mMergeRegionArea = 20;
   mTileSize = 10.0f;
   mMaxPolysPerTile = 128;

   mSmallCharacters = false;
   mRegularCharacters = true;
   mLargeCharacters = false;
   mVehicles = false;

   mCoverSet = StringTable->EmptyString();
   mInnerCover = false;
   mCoverDist = 1.0f;
   mPeekDist = 0.7f;

   mAlwaysRender = false;

   mBuilding = false;
   mCurLinkID = 0;

   mWaterVertStart = 0;
   mWaterTriStart = 0;

   mQuery = NULL;
}

NavMesh::~NavMesh()
{
   dtFreeNavMeshQuery(mQuery);
   dtFreeNavMesh(nm);
   nm = NULL;
   delete ctx;
   ctx = NULL;
}

bool NavMesh::setProtectedDetailSampleDist(void *obj, const char *index, const char *data)
{
   F32 dist = dAtof(data);
   if(dist == 0.0f || dist >= 0.9f)
      return true;
   if (dist > 0.0f && dist < 0.9f)
   {
      NavMesh* ptr = static_cast<NavMesh*>(obj);
      ptr->mDetailSampleDist = 0.9f;
   }
   Con::errorf("NavMesh::detailSampleDist must be 0 or greater than 0.9!");
   return false;
}

bool NavMesh::setProtectedAlwaysRender(void *obj, const char *index, const char *data)
{
   NavMesh *mesh = static_cast<NavMesh*>(obj);
   bool always = dAtob(data);
   if(always)
   {
      if(!gEditingMission)
         mesh->mNetFlags.set(Ghostable);
   }
   else
   {
      if(!gEditingMission)
         mesh->mNetFlags.clear(Ghostable);
   }
   mesh->mAlwaysRender = always;
   mesh->setMaskBits(LoadFlag);
   return true;
}

FRangeValidator ValidCellSize(0.01f, 10.0f);

void NavMesh::initPersistFields()
{
   docsURL;
   addGroup("NavMesh Options");

   addField("fileName", TypeString, Offset(mFileName, NavMesh),
      "Name of the data file to store this navmesh in (relative to engine executable).");

   addField("waterMethod", TYPEID<NavMeshWaterMethod>(), Offset(mWaterMethod, NavMesh),
      "The method to use to handle water surfaces.");

   addFieldV("cellSize", TypeRangedF32, Offset(mCellSize, NavMesh), &ValidCellSize,
      "Length/width of a voxel.");
   addFieldV("cellHeight", TypeRangedF32, Offset(mCellHeight, NavMesh), &ValidCellSize,
      "Height of a voxel.");
   addFieldV("tileSize", TypeRangedF32, Offset(mTileSize, NavMesh), &CommonValidators::PositiveNonZeroFloat,
      "The horizontal size of tiles.");

   addFieldV("actorHeight", TypeRangedF32, Offset(mWalkableHeight, NavMesh), &CommonValidators::PositiveFloat,
      "Height of an actor.");
   addFieldV("actorClimb", TypeRangedF32, Offset(mWalkableClimb, NavMesh), &CommonValidators::PositiveFloat,
      "Maximum climbing height of an actor.");
   addFieldV("actorRadius", TypeRangedF32, Offset(mWalkableRadius, NavMesh), &CommonValidators::PositiveFloat,
      "Radius of an actor.");
   addFieldV("walkableSlope", TypeRangedF32, Offset(mWalkableSlope, NavMesh), &CommonValidators::ValidSlopeAngle,
      "Maximum walkable slope in degrees.");

   addField("smallCharacters", TypeBool, Offset(mSmallCharacters, NavMesh),
      "Is this NavMesh for smaller-than-usual characters?");
   addField("regularCharacters", TypeBool, Offset(mRegularCharacters, NavMesh),
      "Is this NavMesh for regular-sized characters?");
   addField("largeCharacters", TypeBool, Offset(mLargeCharacters, NavMesh),
      "Is this NavMesh for larger-than-usual characters?");
   addField("vehicles", TypeBool, Offset(mVehicles, NavMesh),
      "Is this NavMesh for characters driving vehicles?");

   endGroup("NavMesh Options");

   addGroup("NavMesh Annotations");

   addField("coverGroup", TypeString, Offset(mCoverSet, NavMesh),
      "Name of the SimGroup to store cover points in.");

   addField("innerCover", TypeBool, Offset(mInnerCover, NavMesh),
      "Add cover points everywhere, not just on corners?");

   addFieldV("coverDist", TypeRangedF32, Offset(mCoverDist, NavMesh), &CommonValidators::PositiveFloat,
      "Distance from the edge of the NavMesh to search for cover.");
   addFieldV("peekDist", TypeRangedF32, Offset(mPeekDist, NavMesh), &CommonValidators::PositiveFloat,
      "Distance to the side of each cover point that peeking happens.");

   endGroup("NavMesh Annotations");

   addGroup("NavMesh Rendering");

   addProtectedField("alwaysRender", TypeBool, Offset(mAlwaysRender, NavMesh),
      &setProtectedAlwaysRender, &defaultProtectedGetFn,
      "Display this NavMesh even outside the editor.");

   endGroup("NavMesh Rendering");

   addGroup("NavMesh Advanced Options");

   addFieldV("borderSize", TypeRangedS32, Offset(mBorderSize, NavMesh), &CommonValidators::PositiveInt,
      "Size of the non-walkable border around the navigation mesh (in voxels).");
   addProtectedFieldV("detailSampleDist", TypeRangedF32, Offset(mDetailSampleDist, NavMesh),
      &setProtectedDetailSampleDist, &defaultProtectedGetFn, &CommonValidators::PositiveFloat,
      "Sets the sampling distance to use when generating the detail mesh.");
   addFieldV("detailSampleError", TypeRangedF32, Offset(mDetailSampleMaxError, NavMesh), &CommonValidators::PositiveFloat,
      "The maximum distance the detail mesh surface should deviate from heightfield data.");
   addFieldV("maxEdgeLen", TypeRangedS32, Offset(mMaxEdgeLen, NavMesh), &CommonValidators::PositiveInt,
      "The maximum allowed length for contour edges along the border of the mesh.");
   addFieldV("simplificationError", TypeRangedF32, Offset(mMaxSimplificationError, NavMesh), &CommonValidators::PositiveFloat,
      "The maximum distance a simplfied contour's border edges should deviate from the original raw contour.");
   addFieldV("minRegionArea", TypeRangedS32, Offset(mMinRegionArea, NavMesh), &CommonValidators::PositiveInt,
      "The minimum number of cells allowed to form isolated island areas.");
   addFieldV("mergeRegionArea", TypeRangedS32, Offset(mMergeRegionArea, NavMesh), &CommonValidators::PositiveInt,
      "Any regions with a span count smaller than this value will, if possible, be merged with larger regions.");
   addFieldV("maxPolysPerTile", TypeRangedS32, Offset(mMaxPolysPerTile, NavMesh), &CommonValidators::NaturalNumber,
      "The maximum number of polygons allowed in a tile.");

   endGroup("NavMesh Advanced Options");

   Parent::initPersistFields();
}

bool NavMesh::onAdd()
{
   if(!Parent::onAdd())
      return false;

   mObjBox.set(Point3F(-0.5f, -0.5f, -0.5f),
               Point3F( 0.5f,  0.5f,  0.5f));
   resetWorldBox();

   addToScene();

   if(gEditingMission || mAlwaysRender)
   {
      mNetFlags.set(Ghostable);
      if (isClientObject())
         renderToDrawer();
   }

   if(isServerObject())
   {
      getServerSet()->addObject(this);
      ctx = new NavContext();
      setProcessTick(true);
      if(getEventManager())
         getEventManager()->postEvent("NavMeshCreated", getIdString());
   }

   load();

   return true;
}

void NavMesh::onRemove()
{
   if(getEventManager())
      getEventManager()->postEvent("NavMeshRemoved", getIdString());

   removeFromScene();

   Parent::onRemove();
}

void NavMesh::setTransform(const MatrixF &mat)
{
   Parent::setTransform(mat);
}

void NavMesh::setScale(const VectorF &scale)
{
   Parent::setScale(scale);
}

S32 NavMesh::addLink(const Point3F &from, const Point3F &to, bool biDir, F32 rad, U32 flags)
{
   Point3F rcFrom = DTStoRC(from), rcTo = DTStoRC(to);
   mLinkVerts.push_back(rcFrom.x);
   mLinkVerts.push_back(rcFrom.y);
   mLinkVerts.push_back(rcFrom.z);
   mLinkVerts.push_back(rcTo.x);
   mLinkVerts.push_back(rcTo.y);
   mLinkVerts.push_back(rcTo.z);
   mLinksUnsynced.push_back(true);
   mLinkRads.push_back(rad);
   mLinkDirs.push_back(biDir ? 1 : 0);
   mLinkAreas.push_back(OffMeshArea);
   if (flags == 0) {
      Point3F dir = to - from;
      F32 drop = -dir.z;
      dir.z = 0;
      // If we drop more than we travel horizontally, we're a drop link.
      if(drop > dir.len())
         mLinkFlags.push_back(DropFlag);
      else
         mLinkFlags.push_back(JumpFlag);
   }
   mLinkIDs.push_back(1000 + mCurLinkID);
   mLinkSelectStates.push_back(Unselected);
   mDeleteLinks.push_back(false);
   mCurLinkID++;
   return mLinkIDs.size() - 1;
}

DefineEngineMethod(NavMesh, addLink, S32, (Point3F from, Point3F to, bool biDir, U32 flags), (0),
   "Add a link to this NavMesh between two points.\n\n"
   "")
{
   return object->addLink(from, to, biDir, flags);
}

S32 NavMesh::getLink(const Point3F &pos)
{
   for(U32 i = 0; i < mLinkIDs.size(); i++)
   {
      if(mDeleteLinks[i])
         continue;
      SphereF start(getLinkStart(i), mMax(mLinkRads[i],0.25f));
      SphereF end(getLinkEnd(i), mMax(mLinkRads[i], 0.25f));
      if(start.isContained(pos) || end.isContained(pos))
         return i;
   }
   return -1;
}

DefineEngineMethod(NavMesh, getLink, S32, (Point3F pos),,
   "Get the off-mesh link closest to a given world point.")
{
   return object->getLink(pos);
}

S32 NavMesh::getLinkCount()
{
   return mLinkIDs.size();
}

DefineEngineMethod(NavMesh, getLinkCount, S32, (),,
   "Return the number of links this mesh has.")
{
   return object->getLinkCount();
}

LinkData NavMesh::getLinkFlags(U32 idx)
{
   if(idx < mLinkIDs.size())
   {
      return LinkData(mLinkFlags[idx]);
   }
   return LinkData();
}

bool NavMesh::getLinkDir(U32 idx)
{
   if (idx < mLinkIDs.size())
   {
      return mLinkDirs[idx];
   }

   return false;
}

F32 NavMesh::getLinkRadius(U32 idx)
{
   if (idx < mLinkIDs.size())
   {
      return mLinkRads[idx];
   }

   return -1.0f;
}

void NavMesh::setLinkDir(U32 idx, bool biDir)
{
   if (idx < mLinkIDs.size())
   {
      mLinkDirs[idx] = biDir ? 1 : 0;
      mLinksUnsynced[idx] = true;
   }
}

void NavMesh::setLinkRadius(U32 idx, F32 rad)
{
   if (idx < mLinkIDs.size())
   {
      mLinkRads[idx] = rad;
   }
}

DefineEngineMethod(NavMesh, getLinkFlags, S32, (U32 id),,
   "Get the flags set for a particular off-mesh link.")
{
   return object->getLinkFlags(id).getFlags();
}

void NavMesh::setLinkFlags(U32 idx, const LinkData &d)
{
   if(idx < mLinkIDs.size())
   {
      mLinkFlags[idx] = d.getFlags();
      mLinksUnsynced[idx] = true;
   }
}

DefineEngineMethod(NavMesh, setLinkFlags, void, (U32 id, U32 flags),,
   "Set the flags of a particular off-mesh link.")
{
   LinkData d(flags);
   object->setLinkFlags(id, d);
}

Point3F NavMesh::getLinkStart(U32 idx)
{
   return RCtoDTS(Point3F(
      mLinkVerts[idx*6],
      mLinkVerts[idx*6 + 1],
      mLinkVerts[idx*6 + 2]));
}

DefineEngineMethod(NavMesh, getLinkStart, Point3F, (U32 id),,
   "Get the starting point of an off-mesh link.")
{
   return object->getLinkStart(id);
}

Point3F NavMesh::getLinkEnd(U32 idx)
{
   return RCtoDTS(Point3F(
      mLinkVerts[idx*6 + 3],
      mLinkVerts[idx*6 + 4],
      mLinkVerts[idx*6 + 5]));
}

DefineEngineMethod(NavMesh, getLinkEnd, Point3F, (U32 id),,
   "Get the ending point of an off-mesh link.")
{
   return object->getLinkEnd(id);
}

void NavMesh::selectLink(U32 idx, bool select, bool hover)
{
   if(idx < mLinkIDs.size())
   {
      if(!select)
         mLinkSelectStates[idx] = Unselected;
      else
         mLinkSelectStates[idx] = hover ? Hovered : Selected;
   }
}

void NavMesh::eraseLink(U32 i)
{
   mLinkVerts.erase(i*6, 6);
   mLinksUnsynced.erase(i);
   mLinkRads.erase(i);
   mLinkDirs.erase(i);
   mLinkAreas.erase(i);
   mLinkFlags.erase(i);
   mLinkIDs.erase(i);
   mLinkSelectStates.erase(i);
   mDeleteLinks.erase(i);
}

void NavMesh::eraseLinks()
{
   mLinkVerts.clear();
   mLinksUnsynced.clear();
   mLinkRads.clear();
   mLinkDirs.clear();
   mLinkAreas.clear();
   mLinkFlags.clear();
   mLinkIDs.clear();
   mLinkSelectStates.clear();
   mDeleteLinks.clear();
}

void NavMesh::setLinkCount(U32 c)
{
   eraseLinks();
   mLinkVerts.setSize(c * 6);
   mLinksUnsynced.setSize(c);
   mLinkRads.setSize(c);
   mLinkDirs.setSize(c);
   mLinkAreas.setSize(c);
   mLinkFlags.setSize(c);
   mLinkIDs.setSize(c);
   mLinkSelectStates.setSize(c);
   mDeleteLinks.setSize(c);
}

void NavMesh::deleteLink(U32 idx)
{
   if(idx < mLinkIDs.size())
   {
      mDeleteLinks[idx] = true;
      if(mLinksUnsynced[idx])
         eraseLink(idx);
      else
         mLinksUnsynced[idx] = true;
   }
}

DefineEngineMethod(NavMesh, deleteLink, void, (U32 id),,
   "Delete a given off-mesh link.")
{
   object->deleteLink(id);
}

DefineEngineMethod(NavMesh, deleteLinks, void, (),,
   "Deletes all off-mesh links on this NavMesh.")
{
   //object->eraseLinks();
}

static void buildCallback(SceneObject* object, void* key)
{
   SceneContainer::CallbackInfo* info = reinterpret_cast<SceneContainer::CallbackInfo*>(key);
   if (!object->mPathfindingIgnore && (object->getTypeMask() & MarkerObjectType) == 0)
      object->buildPolyList(info->context, info->polyList, info->boundingBox, info->boundingSphere);
}

bool NavMesh::build(bool background, bool saveIntermediates)
{
   if(mBuilding)
      cancelBuild();
   else
   {
      if(getEventManager())
         getEventManager()->postEvent("NavMeshStartUpdate", getIdString());
   }

   mBuilding = true;
   m_geo = NULL;

   ctx->startTimer(RC_TIMER_TOTAL);

   dtFreeNavMesh(nm);
   // Allocate a new navmesh.
   nm = dtAllocNavMesh();
   if(!nm)
   {
      Con::errorf("Could not allocate dtNavMesh for NavMesh %s", getIdString());
      return false;
   }

   // Needed for the recast config and generation params.
   Box3F rc_box = DTStoRC(getWorldBox());
   S32 gw = 0, gh = 0;
   rcCalcGridSize(rc_box.minExtents, rc_box.maxExtents, mCellSize, &gw, &gh);
   const S32 ts = (S32)(mTileSize / mCellSize);
   const S32 tw = (gw + ts - 1) / ts;
   const S32 th = (gh + ts - 1) / ts;
   Con::printf("NavMesh::Build - Tiles %d x %d", tw, th);

   U32 tileBits = mMin(getBinLog2(getNextPow2(tw * th)), 14);
   if (tileBits > 14) tileBits = 14;
   U32 maxTiles = 1 << tileBits;
   U32 polyBits = 22 - tileBits;
   mMaxPolysPerTile = 1 << polyBits;

   // Build navmesh parameters from console members.
   dtNavMeshParams params;
   rcVcopy(params.orig, rc_box.minExtents);
   params.tileWidth = mTileSize;
   params.tileHeight = mTileSize;
   params.maxTiles = maxTiles;
   params.maxPolys = mMaxPolysPerTile;

   // Initialise our navmesh.
   if(dtStatusFailed(nm->init(&params)))
   {
      Con::errorf("Could not init dtNavMesh for NavMesh %s", getIdString());
      return false;
   }

   // Update links to be deleted.
   for(U32 i = 0; i < mLinkIDs.size();)
   {
      if(mDeleteLinks[i])
         eraseLink(i);
      else
         i++;
   }
   mLinksUnsynced.fill(false);
   mCurLinkID = 0;

   mSaveIntermediates = saveIntermediates;

   updateTiles(true);

   if(!background)
   {
      while(!mDirtyTiles.empty())
         buildNextTile();
   }

   return true;
}

DefineEngineMethod(NavMesh, build, bool, (bool background, bool save), (true, false),
   "@brief Create a Recast nav mesh.")
{
   return object->build(background, save);
}

void NavMesh::cancelBuild()
{
   mDirtyTiles.clear();
   ctx->stopTimer(RC_TIMER_TOTAL);
   mBuilding = false;
}

DefineEngineMethod(NavMesh, cancelBuild, void, (),,
   "@brief Cancel the current NavMesh build.")
{
   object->cancelBuild();
}

void NavMesh::inspectPostApply()
{
   if(mBuilding)
      cancelBuild();
}

void NavMesh::createNewFile()
{
   // We need to construct a default file name
   String levelAssetId(Con::getVariable("$Client::LevelAsset"));

   LevelAsset* levelAsset;
   if (!Sim::findObject(levelAssetId.c_str(), levelAsset))
   {
      Con::errorf("NavMesh::createNewFile() - Unable to find current level's LevelAsset. Unable to construct NavMesh filePath");
      return;
   }

   Torque::Path basePath(levelAsset->getNavmeshPath());

   if (basePath.isEmpty())
      basePath = (Torque::Path)(levelAsset->getLevelPath());

   String fileName = Torque::FS::MakeUniquePath(basePath.getPath(), basePath.getFileName(), "nav");
   mFileName = StringTable->insert(fileName.c_str());
}

S32 NavMesh::getTile(const Point3F& pos)
{
   if(mBuilding)
      return -1;
   for(U32 i = 0; i < mTiles.size(); i++)
   {
      if(mTiles[i].box.isContained(pos))
         return i;
   }
   return -1;
}

Box3F NavMesh::getTileBox(U32 id)
{
   if(mBuilding || id >= mTiles.size())
      return Box3F::Invalid;
   return mTiles[id].box;
}

void NavMesh::updateTiles(bool dirty)
{
   PROFILE_SCOPE(NavMesh_updateTiles);
   if(!isProperlyAdded())
      return;

   mTiles.clear();
   mDirtyTiles.clear();

   const Box3F &box = DTStoRC(getWorldBox());
   if(box.isEmpty())
      return;

   // Calculate tile dimensions.
   const F32* bmin = box.minExtents;
   const F32* bmax = box.maxExtents;
   S32 gw = 0, gh = 0;
   rcCalcGridSize(bmin, bmax, mCellSize, &gw, &gh);
   const S32 ts = (S32)(mTileSize / mCellSize);
   const S32 tw = (gw + ts - 1) / ts;
   const S32 th = (gh + ts - 1) / ts;
   const F32 tcs = mTileSize;

   // Iterate over tiles.
   F32 tileBmin[3], tileBmax[3];
   for(U32 y = 0; y < th; ++y)
   {
      for(U32 x = 0; x < tw; ++x)
      {
         tileBmin[0] = bmin[0] + x*tcs;
         tileBmin[1] = bmin[1];
         tileBmin[2] = bmin[2] + y*tcs;

         tileBmax[0] = bmin[0] + (x+1)*tcs;
         tileBmax[1] = bmax[1];
         tileBmax[2] = bmin[2] + (y+1)*tcs;

         mTiles.push_back(
            Tile(RCtoDTS(tileBmin, tileBmax),
                  x, y,
                  tileBmin, tileBmax));

         if(dirty)
            mDirtyTiles.push_back_unique(mTiles.size() - 1);
      }
   }
}

void NavMesh::processTick(const Move *move)
{
   buildNextTile();
}

void NavMesh::buildNextTile()
{
   PROFILE_SCOPE(NavMesh_buildNextTile);

   if(!mDirtyTiles.empty())
   {
      dtFreeNavMeshQuery(mQuery);
      mQuery = NULL;
      // Pop a single dirty tile and process it.
      U32 i = mDirtyTiles.front();
      mDirtyTiles.pop_front();
      Tile &tile = mTiles[i];

      // Remove any previous data.
      nm->removeTile(nm->getTileRefAt(tile.x, tile.y, 0), 0, 0);

      // Generate navmesh for this tile.
      U32 dataSize = 0;
      unsigned char* data = buildTileData(tile, dataSize);
      // cache our result (these only exist if keep intermediates is ticked)
      if (m_chf)
      {
         tile.chf = m_chf;
         m_chf = 0;
      }
      if (m_solid)
      {
         tile.solid = m_solid;
         m_solid = 0;
      }
      if (m_cset)
      {
         tile.cset = m_cset;
         m_cset = 0;
      }
      if (m_pmesh)
      {
         tile.pmesh = m_pmesh;
         m_pmesh = 0;
      }
      if (m_dmesh)
      {
         tile.dmesh = m_dmesh;
         m_dmesh = 0;
      }
      if (m_triareas)
      {
         tile.triareas = m_triareas;
         m_triareas = nullptr;
      }

      if(data)
      {
         // Add new data (navmesh owns and deletes the data).
         dtStatus status = nm->addTile(data, dataSize, DT_TILE_FREE_DATA, 0, 0);
         int success = 1;
         if(dtStatusFailed(status))
         {
            success = 0;
            dtFree(data);
         }
         if(getEventManager())
         {
            String str = String::ToString("%d %d %d (%d, %d) %d %.3f %s",
               getId(),
               i, mTiles.size(),
               tile.x, tile.y,
               success,
               ctx->getAccumulatedTime(RC_TIMER_TOTAL) / 1000.0f,
               castConsoleTypeToString(tile.box));
            getEventManager()->postEvent("NavMeshTileUpdate", str.c_str());
            setMaskBits(LoadFlag);
         }
      }
      // Did we just build the last tile?
      if(mDirtyTiles.empty())
      {
         mQuery = dtAllocNavMeshQuery();
         if (dtStatusFailed(mQuery->init(nm, 2048)))
         {
            Con::errorf("NavMesh - Failed to create navmesh query");
         }

         ctx->stopTimer(RC_TIMER_TOTAL);
         if(getEventManager())
         {
            String str = String::ToString("%d", getId());
            getEventManager()->postEvent("NavMeshUpdate", str.c_str());
            setMaskBits(LoadFlag);
         }
         mBuilding = false;
      }
   }

   if (mQuery == NULL)
   {
      mQuery = dtAllocNavMeshQuery();
      if (dtStatusFailed(mQuery->init(nm, 2048)))
      {
         Con::errorf("NavMesh - Failed to create navmesh query");
      }
   }
}

unsigned char *NavMesh::buildTileData(const Tile &tile, U32 &dataSize)
{

   cleanup();

   // Push out tile boundaries a bit.
   F32 tileBmin[3], tileBmax[3];
   rcVcopy(tileBmin, tile.bmin);
   rcVcopy(tileBmax, tile.bmax);
   // Setup our rcConfig
   dMemset(&m_cfg, 0, sizeof(m_cfg));
   m_cfg.cs = mCellSize;
   m_cfg.ch = mCellHeight;
   m_cfg.walkableSlopeAngle = mWalkableSlope;
   m_cfg.walkableHeight = (S32)mCeil(mWalkableHeight / m_cfg.ch);
   m_cfg.walkableClimb = (S32)mFloor(mWalkableClimb / m_cfg.ch);
   m_cfg.walkableRadius = (S32)mCeil(mWalkableRadius / m_cfg.cs);
   m_cfg.maxEdgeLen = (S32)(mMaxEdgeLen / mCellSize);
   m_cfg.maxSimplificationError = mMaxSimplificationError;
   m_cfg.minRegionArea = (S32)mSquared((F32)mMinRegionArea);
   m_cfg.mergeRegionArea = (S32)mSquared((F32)mMergeRegionArea);
   m_cfg.maxVertsPerPoly = (S32)mMaxVertsPerPoly;
   m_cfg.tileSize = (S32)(mTileSize / mCellSize);
   m_cfg.borderSize = mMax(m_cfg.walkableRadius + 3, mBorderSize); // use the border size if it is bigger.
   m_cfg.width = m_cfg.tileSize + m_cfg.borderSize * 2;
   m_cfg.height = m_cfg.tileSize + m_cfg.borderSize * 2;
   m_cfg.detailSampleDist = mDetailSampleDist < 0.9f ? 0 : mCellSize * mDetailSampleDist;
   m_cfg.detailSampleMaxError = mCellHeight * mDetailSampleMaxError;
   rcVcopy(m_cfg.bmin, tileBmin);
   rcVcopy(m_cfg.bmax, tileBmax);
   m_cfg.bmin[0] -= m_cfg.borderSize * m_cfg.cs;
   m_cfg.bmin[2] -= m_cfg.borderSize * m_cfg.cs;
   m_cfg.bmax[0] += m_cfg.borderSize * m_cfg.cs;
   m_cfg.bmax[2] += m_cfg.borderSize * m_cfg.cs;

   Box3F worldBox = RCtoDTS(m_cfg.bmin, m_cfg.bmax);
   SceneContainer::CallbackInfo info;
   info.context = PLC_Navigation;
   info.boundingBox = worldBox;
   m_geo = new RecastPolyList;
   info.polyList = m_geo;
   info.key = this;
   getContainer()->findObjects(worldBox, StaticObjectType | DynamicShapeObjectType, buildCallback, &info);

   // Parse water objects into the same list, but remember how much geometry was /not/ water.
   mWaterVertStart = m_geo->getVertCount();
   mWaterTriStart = m_geo->getTriCount();
   if (mWaterMethod != Ignore)
   {
      getContainer()->findObjects(worldBox, WaterObjectType, buildCallback, &info);
   }

   // Check for no geometry.
   if (!m_geo->getVertCount())
   {
      m_geo->clear();
      return NULL;
   }

   const rcChunkyTriMesh* chunkyMesh = m_geo->getChunkyMesh();

   // Create a heightfield to voxelize our input geometry.
   m_solid = rcAllocHeightfield();
   if(!m_solid)
   {
      Con::errorf("Out of memory (rcHeightField) for NavMesh %s", getIdString());
      return NULL;
   }
   if (!rcCreateHeightfield(ctx, *m_solid, m_cfg.width, m_cfg.height, m_cfg.bmin, m_cfg.bmax, m_cfg.cs, m_cfg.ch))
   {
      Con::errorf("Could not generate rcHeightField for NavMesh %s", getIdString());
      return NULL;
   }

   m_triareas = new unsigned char[chunkyMesh->maxTrisPerChunk];
   if (!m_triareas)
   {
      Con::errorf("NavMesh::buildTileData: Out of memory 'm_triareas' (%d).", chunkyMesh->maxTrisPerChunk);
      return NULL;
   }

   F32 tbmin[2], tbmax[2];
   tbmin[0] = m_cfg.bmin[0];
   tbmin[1] = m_cfg.bmin[2];
   tbmax[0] = m_cfg.bmax[0];
   tbmax[1] = m_cfg.bmax[2];
   int cid[512];
   const int ncid = rcGetChunksOverlappingRect(chunkyMesh, tbmin, tbmax, cid, 512);
   if (!ncid)
      return 0;

   for (int i = 0; i < ncid; ++i)
   {
      const rcChunkyTriMeshNode& node = chunkyMesh->nodes[cid[i]];
      const int* ctris = &chunkyMesh->tris[node.i * 3];
      const int nctris = node.n;

      memset(m_triareas, 0, nctris * sizeof(unsigned char));
      rcMarkWalkableTriangles(ctx, m_cfg.walkableSlopeAngle,
         m_geo->getVerts(), m_geo->getVertCount(), ctris, nctris, m_triareas);

      // Post-process triangle areas if we need to capture water.
      if (mWaterMethod != Ignore)
      {
         for (int t = 0; t < nctris; ++t)
         {
            const int* tri = &ctris[t * 3];

            bool isWater = false;
            for (int j = 0; j < 3; ++j)
            {
               if (tri[j] >= mWaterVertStart)
               {
                  isWater = true;
                  break;
               }
            }

            if (isWater)
            {
               if (mWaterMethod == Solid)
               {
                  m_triareas[t] = WaterArea;  // Custom enum you define, like 64
               }
               else if (mWaterMethod == Impassable)
               {
                  m_triareas[t] = NullArea;
               }
            }
         }
      }

      if (!rcRasterizeTriangles(ctx, m_geo->getVerts(), m_geo->getVertCount(), ctris, m_triareas, nctris, *m_solid, m_cfg.walkableClimb))
         return NULL;
   }

   if (!mSaveIntermediates)
   {
      delete[] m_triareas;
      m_triareas = 0;
   }

   // these should be optional.
   //if (m_filterLowHangingObstacles)
      rcFilterLowHangingWalkableObstacles(ctx, m_cfg.walkableClimb, *m_solid);
   //if (m_filterLedgeSpans)
      rcFilterLedgeSpans(ctx, m_cfg.walkableHeight, m_cfg.walkableClimb, *m_solid);
   //if (m_filterWalkableLowHeightSpans)
      rcFilterWalkableLowHeightSpans(ctx, m_cfg.walkableHeight, *m_solid);


   // Compact the heightfield so that it is faster to handle from now on.
   // This will result more cache coherent data as well as the neighbours
   // between walkable cells will be calculated.
   m_chf = rcAllocCompactHeightfield();
   if (!m_chf)
   {
      Con::errorf("NavMesh::buildTileData: Out of memory 'chf'.");
      return NULL;
   }
   if (!rcBuildCompactHeightfield(ctx, m_cfg.walkableHeight, m_cfg.walkableClimb, *m_solid, *m_chf))
   {
      Con::errorf("NavMesh::buildTileData: Could not build compact data.");
      return NULL;
   }

   if (!mSaveIntermediates)
   {
      rcFreeHeightField(m_solid);
      m_solid = NULL;
   }

   // Erode the walkable area by agent radius.
   if (!rcErodeWalkableArea(ctx, m_cfg.walkableRadius, *m_chf))
   {
      Con::errorf("NavMesh::buildTileData: Could not erode.");
      return NULL;
   }

   //--------------------------
   // Todo: mark areas here.
   //const ConvexVolume* vols = m_geom->getConvexVolumes();
   //for (int i  = 0; i < m_geom->getConvexVolumeCount(); ++i)
      //rcMarkConvexPolyArea(m_ctx, vols[i].verts, vols[i].nverts, vols[i].hmin, vols[i].hmax, (unsigned char)vols[i].area, *m_chf);
   //--------------------------

   // Partition the heightfield so that we can use simple algorithm later to triangulate the walkable areas.
   // There are 3 martitioning methods, each with some pros and cons:
   // These should be implemented.
   // 1) Watershed partitioning
   //   - the classic Recast partitioning
   //   - creates the nicest tessellation
   //   - usually slowest
   //   - partitions the heightfield into nice regions without holes or overlaps
   //   - the are some corner cases where this method creates produces holes and overlaps
   //      - holes may appear when a small obstacles is close to large open area (triangulation can handle this)
   //      - overlaps may occur if you have narrow spiral corridors (i.e stairs), this make triangulation to fail
   //   * generally the best choice if you precompute the nacmesh, use this if you have large open areas
   // 2) Monotone partioning
   //   - fastest
   //   - partitions the heightfield into regions without holes and overlaps (guaranteed)
   //   - creates long thin polygons, which sometimes causes paths with detours
   //   * use this if you want fast navmesh generation
   // 3) Layer partitoining
   //   - quite fast
   //   - partitions the heighfield into non-overlapping regions
   //   - relies on the triangulation code to cope with holes (thus slower than monotone partitioning)
   //   - produces better triangles than monotone partitioning
   //   - does not have the corner cases of watershed partitioning
   //   - can be slow and create a bit ugly tessellation (still better than monotone)
   //     if you have large open areas with small obstacles (not a problem if you use tiles)
   //   * good choice to use for tiled navmesh with medium and small sized tiles


   if (/*m_partitionType == SAMPLE_PARTITION_WATERSHED*/ true)
   {
      // Prepare for region partitioning, by calculating distance field along the walkable surface.
      if (!rcBuildDistanceField(ctx, *m_chf))
      {
         Con::errorf("NavMesh::buildTileData: Could not build distance field.");
         return 0;
      }

      // Partition the walkable surface into simple regions without holes.
      if (!rcBuildRegions(ctx, *m_chf, m_cfg.borderSize, m_cfg.minRegionArea, m_cfg.mergeRegionArea))
      {
         Con::errorf("NavMesh::buildTileData: Could not build watershed regions.");
         return NULL;
      }
   }
   else if (/*m_partitionType == SAMPLE_PARTITION_MONOTONE*/ false)
   {
      // Partition the walkable surface into simple regions without holes.
      // Monotone partitioning does not need distancefield.
      if (!rcBuildRegionsMonotone(ctx, *m_chf, m_cfg.borderSize, m_cfg.minRegionArea, m_cfg.mergeRegionArea))
      {
         Con::errorf("NavMesh::buildTileData: Could not build monotone regions.");
         return NULL;
      }
   }
   else // SAMPLE_PARTITION_LAYERS
   {
      // Partition the walkable surface into simple regions without holes.
      if (!rcBuildLayerRegions(ctx, *m_chf, m_cfg.borderSize, m_cfg.minRegionArea))
      {
         Con::errorf("NavMesh::buildTileData: Could not build layer regions.");
         return NULL;
      }
   }

   m_cset = rcAllocContourSet();
   if (!m_cset)
   {
      Con::errorf("NavMesh::buildTileData: Out of memory 'cset'");
      return NULL;
   }

   if (!rcBuildContours(ctx, *m_chf, m_cfg.maxSimplificationError, m_cfg.maxEdgeLen, *m_cset))
   {
      Con::errorf("NavMesh::buildTileData: Could not create contours");
      return NULL;
   }

   if (m_cset->nconts == 0)
      return NULL;

   // Build polygon navmesh from the contours.
   m_pmesh = rcAllocPolyMesh();
   if (!m_pmesh)
   {
      Con::errorf("NavMesh::buildTileData: Out of memory 'pmesh'.");
      return NULL;
   }
   if (!rcBuildPolyMesh(ctx, *m_cset, m_cfg.maxVertsPerPoly, *m_pmesh))
   {
      Con::errorf("NavMesh::buildTileData: Could not triangulate contours.");
      return NULL;
   }

   // Build detail mesh.
   m_dmesh = rcAllocPolyMeshDetail();
   if (!m_dmesh)
   {
      Con::errorf("NavMesh::buildTileData: Out of memory 'dmesh'.");
      return NULL;
   }

   if (!rcBuildPolyMeshDetail(ctx, *m_pmesh, *m_chf, m_cfg.detailSampleDist, m_cfg.detailSampleMaxError, *m_dmesh))
   {
      Con::errorf("NavMesh::buildTileData: Could build polymesh detail.");
      return NULL;
   }

   if (!mSaveIntermediates)
   {
      rcFreeCompactHeightfield(m_chf);
      m_chf = 0;
      rcFreeContourSet(m_cset);
      m_cset = 0;
   }

   unsigned char* navData = 0;
   int navDataSize = 0;
   if (m_cfg.maxVertsPerPoly <= DT_VERTS_PER_POLYGON)
   {
      if (m_pmesh->nverts >= 0xffff)
      {
         // The vertex indices are ushorts, and cannot point to more than 0xffff vertices.
         Con::errorf("NavMesh::buildTileData: Too many vertices per tile %d (max: %d).", m_pmesh->nverts, 0xffff);
         return NULL;
      }

      for (U32 i = 0; i < m_pmesh->npolys; i++)
      {
         if (m_pmesh->areas[i] == RC_WALKABLE_AREA)
            m_pmesh->areas[i] = GroundArea;

         if (m_pmesh->areas[i] == GroundArea)
            m_pmesh->flags[i] |= WalkFlag;
         if (m_pmesh->areas[i] == WaterArea)
            m_pmesh->flags[i] |= SwimFlag;
      }

      dtNavMeshCreateParams params;
      dMemset(&params, 0, sizeof(params));

      params.verts = m_pmesh->verts;
      params.vertCount = m_pmesh->nverts;
      params.polys = m_pmesh->polys;
      params.polyAreas = m_pmesh->areas;
      params.polyFlags = m_pmesh->flags;
      params.polyCount = m_pmesh->npolys;
      params.nvp = m_pmesh->nvp;

      params.detailMeshes = m_dmesh->meshes;
      params.detailVerts = m_dmesh->verts;
      params.detailVertsCount = m_dmesh->nverts;
      params.detailTris = m_dmesh->tris;
      params.detailTriCount = m_dmesh->ntris;

      params.offMeshConVerts = mLinkVerts.address();
      params.offMeshConRad = mLinkRads.address();
      params.offMeshConDir = mLinkDirs.address();
      params.offMeshConAreas = mLinkAreas.address();
      params.offMeshConFlags = mLinkFlags.address();
      params.offMeshConUserID = mLinkIDs.address();
      params.offMeshConCount = mLinkIDs.size();

      params.walkableHeight = mWalkableHeight;
      params.walkableRadius = mWalkableRadius;
      params.walkableClimb = mWalkableClimb;
      params.tileX = tile.x;
      params.tileY = tile.y;
      params.tileLayer = 0;
      rcVcopy(params.bmin, m_pmesh->bmin);
      rcVcopy(params.bmax, m_pmesh->bmax);
      params.cs = m_cfg.cs;
      params.ch = m_cfg.ch;
      params.buildBvTree = true;

      if (!dtCreateNavMeshData(&params, &navData, &navDataSize))
      {
         Con::errorf("NavMesh::buildTileData: Could not build Detour navmesh.");
         return NULL;
      }
   }
   dataSize = navDataSize;

   return navData;
}

/// This method should never be called in a separate thread to the rendering
/// or pathfinding logic. It directly replaces data in the dtNavMesh for
/// this NavMesh object.
void NavMesh::buildTiles(const Box3F &box)
{
   PROFILE_SCOPE(NavMesh_buildTiles);
   // Make sure we've already built or loaded.
   if(!nm)
      return;
   // Iterate over tiles.
   for(U32 i = 0; i < mTiles.size(); i++)
   {
      const Tile &tile = mTiles[i];
      // Check tile box.
      if(!tile.box.isOverlapped(box))
         continue;
      // Mark as dirty.
      mDirtyTiles.push_back_unique(i);
   }
   if(mDirtyTiles.size())
      ctx->startTimer(RC_TIMER_TOTAL);
}

DefineEngineMethod(NavMesh, buildTiles, void, (Box3F box),,
   "@brief Rebuild the tiles overlapped by the input box.")
{
   return object->buildTiles(box);
}

void NavMesh::buildTile(const U32 &tile)
{
   PROFILE_SCOPE(NavMesh_buildTile);
   if(tile < mTiles.size())
   {
      mDirtyTiles.push_back_unique(tile);
      ctx->startTimer(RC_TIMER_TOTAL);
      m_geo = NULL;
   }
}

void NavMesh::buildLinks()
{
   // Make sure we've already built or loaded.
   if(!nm)
      return;
   // Iterate over tiles.
   for(U32 i = 0; i < mTiles.size(); i++)
   {
      const Tile &tile = mTiles[i];
      // Iterate over links
      for(U32 j = 0; j < mLinkIDs.size(); j++)
      {
         if (mLinksUnsynced[j])
         {
         if(tile.box.isContained(getLinkStart(j)) ||
               tile.box.isContained(getLinkEnd(j)))
         {
            // Mark tile for build.
            mDirtyTiles.push_back_unique(i);
            // Delete link if necessary
            if(mDeleteLinks[j])
            {
               eraseLink(j);
               j--;
            }
            else
               mLinksUnsynced[j] = false;
         }
      }
   }
   }
   if(mDirtyTiles.size())
      ctx->startTimer(RC_TIMER_TOTAL);
}

DefineEngineMethod(NavMesh, buildLinks, void, (),,
   "@brief Build tiles of this mesh where there are unsynchronised links.")
{
   object->buildLinks();
}

void NavMesh::deleteCoverPoints()
{
   SimSet *set = NULL;
   if(Sim::findObject(mCoverSet, set))
      set->deleteAllObjects();
}

DefineEngineMethod(NavMesh, deleteCoverPoints, void, (),,
   "@brief Remove all cover points for this NavMesh.")
{
   object->deleteCoverPoints();
}

bool NavMesh::createCoverPoints()
{
   if(!nm || !isServerObject())
      return false;

   SimSet *set = NULL;
   if(Sim::findObject(mCoverSet, set))
   {
      set->deleteAllObjects();
   }
   else
   {
      set = new SimGroup();
      if(set->registerObject(mCoverSet))
      {
         getGroup()->addObject(set);
      }
      else
      {
         delete set;
         set = getGroup();
      }
   }

   dtNavMeshQuery *query = dtAllocNavMeshQuery();
   if(!query || dtStatusFailed(query->init(nm, 1)))
      return false;

   dtQueryFilter f;

   // Iterate over all polys in our navmesh.
   const int MAX_SEGS = 6;
   for(U32 i = 0; i < nm->getMaxTiles(); ++i)
   {
      const dtMeshTile* tile = ((const dtNavMesh*)nm)->getTile(i);
      if(!tile->header) continue;
      const dtPolyRef base = nm->getPolyRefBase(tile);
      for(U32 j = 0; j < tile->header->polyCount; ++j)
      {
         const dtPolyRef ref = base | j;
         float segs[MAX_SEGS*6];
         int nsegs = 0;
         query->getPolyWallSegments(ref, &f, segs, NULL, &nsegs, MAX_SEGS);
         for(int segIDx = 0; segIDx < nsegs; ++segIDx)
         {
            const float* sa = &segs[segIDx *6];
            const float* sb = &segs[segIDx *6+3];
            Point3F a = RCtoDTS(sa), b = RCtoDTS(sb);
            F32 len = (b - a).len();
            if(len < mWalkableRadius * 2)
               continue;
            Point3F edge = b - a;
            edge.normalize();
            // Number of points to try placing - for now, one at each end.
            U32 pointCount = (len > mWalkableRadius * 4) ? 2 : 1;
            for(U32 pointIDx = 0; pointIDx < pointCount; pointIDx++)
            {
               MatrixF mat;
               Point3F pos;
               // If we're only placing one point, put it in the middle.
               if(pointCount == 1)
                  pos = a + edge * len / 2;
               // Otherwise, stand off from edge ends.
               else
               {
                  if(pointIDx % 2)
                     pos = a + edge * (pointIDx /2+1) * mWalkableRadius;
                  else
                     pos = b - edge * (pointIDx /2+1) * mWalkableRadius;
               }
               CoverPointData data;
               if(testEdgeCover(pos, edge, data))
               {
                  CoverPoint *m = new CoverPoint();
                  if(!m->registerObject())
                     delete m;
                  else
                  {
                     m->setTransform(data.trans);
                     m->setSize(data.size);
                     m->setPeek(data.peek[0], data.peek[1], data.peek[2]);
                     if(set)
                        set->addObject(m);
                  }
               }
            }
         }
      }
   }
   return true;
}

DefineEngineMethod(NavMesh, createCoverPoints, bool, (),,
   "@brief Create cover points for this NavMesh.")
{
   return object->createCoverPoints();
}

bool NavMesh::testEdgeCover(const Point3F &pos, const VectorF &dir, CoverPointData &data)
{
   data.peek[0] = data.peek[1] = data.peek[2] = false;
   // Get the edge normal.
   Point3F norm;
   mCross(dir, Point3F(0, 0, 1), &norm);
   RayInfo ray;
   U32 hits = 0;
   for(U32 j = 0; j < CoverPoint::NumSizes; j++)
   {
      Point3F test = pos + Point3F(0.0f, 0.0f, mWalkableHeight * j / (F32)CoverPoint::NumSizes);
      if(getContainer()->castRay(test, test + norm * mCoverDist, StaticObjectType, &ray))
      {
         // Test peeking.
         Point3F left = test + dir * mPeekDist;
         data.peek[0] = !getContainer()->castRay(test, left, StaticObjectType, &ray)
            && !getContainer()->castRay(left, left + norm * mCoverDist, StaticObjectType, &ray);

         Point3F right = test - dir * mPeekDist;
         data.peek[1] = !getContainer()->castRay(test, right, StaticObjectType, &ray)
            && !getContainer()->castRay(right, right + norm * mCoverDist, StaticObjectType, &ray);

         Point3F over = test + Point3F(0, 0, 1) * 0.2f;
         data.peek[2] = !getContainer()->castRay(test, over, StaticObjectType, &ray)
            && !getContainer()->castRay(over, over + norm * mCoverDist, StaticObjectType, &ray);

         if(mInnerCover || data.peek[0] || data.peek[1] || data.peek[2])
            hits++;
         // If we couldn't peek here, we may be able to peek further up.
      }
      else
         // No cover at this height - break off.
         break;
   }
   if(hits > 0)
   {
      data.size = (CoverPoint::Size)(hits - 1);
      data.trans = MathUtils::createOrientFromDir(norm);
      data.trans.setPosition(pos);
   }
   return hits > 0;
}

void NavMesh::renderToDrawer()
{
   mDbgDraw.clearCache();
   // Recast debug draw
   NetObject* no = getServerObject();
   if (no)
   {
      NavMesh* n = static_cast<NavMesh*>(no);
      mDbgDraw.depthMask(true, true);
      if (n->nm &&
         (m_drawMode == DRAWMODE_NAVMESH ||
            m_drawMode == DRAWMODE_NAVMESH_TRANS ||
            m_drawMode == DRAWMODE_NAVMESH_BVTREE ||
            m_drawMode == DRAWMODE_NAVMESH_NODES ||
            m_drawMode == DRAWMODE_NAVMESH_PORTALS ||
            m_drawMode == DRAWMODE_NAVMESH_INVIS))
      {
         if (m_drawMode != DRAWMODE_NAVMESH_INVIS)
         {
            if (m_drawMode == DRAWMODE_NAVMESH_TRANS)
               mDbgDraw.blend(true);
            duDebugDrawNavMeshWithClosedList(&mDbgDraw, *n->nm, *n->mQuery, 0);
            mDbgDraw.blend(false);
         }
         if(m_drawMode == DRAWMODE_NAVMESH_BVTREE)
            duDebugDrawNavMeshBVTree(&mDbgDraw, *n->nm);
         if(m_drawMode == DRAWMODE_NAVMESH_PORTALS)
            duDebugDrawNavMeshPortals(&mDbgDraw, *n->nm);
      }

      mDbgDraw.depthMask(true, false);

      for (Tile& tile : n->mTiles)
      {
         if (tile.chf && m_drawMode == DRAWMODE_COMPACT)
         {
            duDebugDrawCompactHeightfieldSolid(&mDbgDraw, *tile.chf);
         }

         if (tile.chf && m_drawMode == DRAWMODE_COMPACT_DISTANCE)
         {
            duDebugDrawCompactHeightfieldDistance(&mDbgDraw, *tile.chf);
         }

         if (tile.chf && m_drawMode == DRAWMODE_COMPACT_REGIONS)
         {
            duDebugDrawCompactHeightfieldRegions(&mDbgDraw, *tile.chf);
         }

         if (tile.solid && m_drawMode == DRAWMODE_VOXELS)
         {
            duDebugDrawHeightfieldSolid(&mDbgDraw, *tile.solid);
         }

         if (tile.solid && m_drawMode == DRAWMODE_VOXELS_WALKABLE)
         {
            duDebugDrawHeightfieldWalkable(&mDbgDraw, *tile.solid);
         }

         if (tile.cset && m_drawMode == DRAWMODE_RAW_CONTOURS)
         {
            mDbgDraw.depthMask(false);
            duDebugDrawRawContours(&mDbgDraw, *tile.cset);
            mDbgDraw.depthMask(true);
         }

         if (tile.cset && m_drawMode == DRAWMODE_BOTH_CONTOURS)
         {
            mDbgDraw.depthMask(false);
            duDebugDrawRawContours(&mDbgDraw, *tile.cset);
            duDebugDrawContours(&mDbgDraw, *tile.cset);
            mDbgDraw.depthMask(true);
         }

         if (tile.cset && m_drawMode == DRAWMODE_CONTOURS)
         {
            mDbgDraw.depthMask(false);
            duDebugDrawContours(&mDbgDraw, *tile.cset);
            mDbgDraw.depthMask(true);
         }

         if (tile.chf && tile.cset && m_drawMode == DRAWMODE_REGION_CONNECTIONS)
         {
            
            duDebugDrawCompactHeightfieldRegions(&mDbgDraw, *tile.chf);
            mDbgDraw.depthMask(false);
            duDebugDrawRegionConnections(&mDbgDraw, *tile.cset);
            mDbgDraw.depthMask(true);
         }

         if (tile.pmesh && m_drawMode == DRAWMODE_POLYMESH)
         {
            mDbgDraw.depthMask(false);
            duDebugDrawPolyMesh(&mDbgDraw, *tile.pmesh);
            mDbgDraw.depthMask(true);
         }

         if (tile.dmesh && m_drawMode == DRAWMODE_POLYMESH_DETAIL)
         {
            mDbgDraw.depthMask(false);
            duDebugDrawPolyMeshDetail(&mDbgDraw, *tile.dmesh);
            mDbgDraw.depthMask(true);
         }

      }
   }
}

void NavMesh::cleanup()
{
   delete[] m_triareas;
   m_triareas = 0;
   rcFreeHeightField(m_solid);
   m_solid = 0;
   rcFreeCompactHeightfield(m_chf);
   m_chf = 0;
   rcFreeContourSet(m_cset);
   m_cset = 0;
   rcFreePolyMesh(m_pmesh);
   m_pmesh = 0;
   rcFreePolyMeshDetail(m_dmesh);
   m_dmesh = 0;
   SAFE_DELETE(m_geo);
}

void NavMesh::prepRenderImage(SceneRenderState *state)
{
   ObjectRenderInst *ri = state->getRenderPass()->allocInst<ObjectRenderInst>();
   ri->renderDelegate.bind(this, &NavMesh::render);
   ri->type = RenderPassManager::RIT_Object;
   ri->translucentSort = true;
   ri->defaultKey = 1;
   state->getRenderPass()->addInst(ri);
}

void NavMesh::render(ObjectRenderInst *ri, SceneRenderState *state, BaseMatInstance *overrideMat)
{
   if(overrideMat)
      return;

   if(state->isReflectPass())
      return;

   PROFILE_SCOPE(NavMesh_Render);
   
   // Recast debug draw
   NetObject *no = getServerObject();
   if(no)
   {
      NavMesh *n = static_cast<NavMesh*>(no);

      if ((!gEditingMission && n->mAlwaysRender) || gEditingMission)
      {
         mDbgDraw.render(state);
      }
   }
}

void NavMesh::renderLinks(duDebugDraw &dd)
{
   if(mBuilding)
      return;
   dd.begin(DU_DRAW_LINES);
   dd.depthMask(false);
   for(U32 i = 0; i < mLinkIDs.size(); i++)
   {
      U32 col = 0;
      switch(mLinkSelectStates[i])
      {
         case Unselected: col = mLinksUnsynced[i] ? duRGBA(255, 0, 0, 200) : duRGBA(0, 0, 255, 255); break;
         case Hovered:    col = duRGBA(255, 255, 255, 255); break;
         case Selected:   col = duRGBA(0, 255, 0, 255); break;
      }
      F32 *s = &mLinkVerts[i*6];
      F32 *e = &mLinkVerts[i*6 + 3];
      if(!mDeleteLinks[i])
         duAppendCircle(&dd, s[0], s[1], s[2], mLinkRads[i], col);
      duAppendArc(&dd,
         s[0], s[1], s[2],
         e[0], e[1], e[2],
         0.3f,
         (mLinkDirs[i]&1) ? 0.6f : 0.0f, mLinkFlags[i] == DropFlag ? 0.0f : 0.6f,
         col);
      if(!mDeleteLinks[i])
         duAppendCircle(&dd, e[0], e[1], e[2], mLinkRads[i], col);
   }
   dd.end();
}

void NavMesh::renderSearch(duDebugDraw& dd)
{
   if (mQuery == NULL)
      return;

   if (m_drawMode == DRAWMODE_NAVMESH_NODES)
      duDebugDrawNavMeshNodes(&dd, *mQuery);
}

void NavMesh::renderTileData(duDebugDrawTorque &dd, U32 tile)
{
   if (tile > mTiles.size())
      return;

   if(nm)
   {
      //duDebugDrawNavMesh(&dd, *nm, 0);
      if(mTiles[tile].chf)
         duDebugDrawCompactHeightfieldSolid(&dd, *mTiles[tile].chf);

      duDebugDrawNavMeshPortals(&dd, *nm);

      if (!m_geo)
         return;

      int col = duRGBA(255, 0, 255, 255);
      dd.begin(DU_DRAW_LINES);
      const F32 *verts = m_geo->getVerts();
      const S32 *tris = m_geo->getTris();
      for(U32 t = 0; t < m_geo->getTriCount(); t++)
      {
         dd.vertex(&verts[tris[t*3]*3], col);
         dd.vertex(&verts[tris[t*3+1]*3], col);
         dd.vertex(&verts[tris[t*3+1]*3], col);
         dd.vertex(&verts[tris[t*3+2]*3], col);
         dd.vertex(&verts[tris[t*3+2]*3], col);
         dd.vertex(&verts[tris[t*3]*3], col);
      }
      dd.end();
   }
}

void NavMesh::onEditorEnable()
{
   mNetFlags.set(Ghostable);
   if(isClientObject() && !mAlwaysRender)
      addToScene();
}

void NavMesh::onEditorDisable()
{
   if(!mAlwaysRender)
   {
      mNetFlags.clear(Ghostable);
      if(isClientObject())
         removeFromScene();
   }
}

U32 NavMesh::packUpdate(NetConnection *conn, U32 mask, BitStream *stream)
{
   U32 retMask = Parent::packUpdate(conn, mask, stream);

   mathWrite(*stream, getTransform());
   mathWrite(*stream, getScale());
   stream->writeFlag(mAlwaysRender);
   stream->write((U32)m_drawMode);

   return retMask;
}

void NavMesh::unpackUpdate(NetConnection *conn, BitStream *stream)
{
   Parent::unpackUpdate(conn, stream);

   mathRead(*stream, &mObjToWorld);
   mathRead(*stream, &mObjScale);
   mAlwaysRender = stream->readFlag();
   setTransform(mObjToWorld);
   U32 draw;
   stream->read(&draw);
   m_drawMode = (DrawMode)draw;

   renderToDrawer();
}

static const int NAVMESHSET_MAGIC = 'M'<<24 | 'S'<<16 | 'E'<<8 | 'T'; //'MSET';
static const int NAVMESHSET_VERSION = 1;

struct NavMeshSetHeader
{
   int magic;
   int version;
   int numTiles;
   dtNavMeshParams params;
};

struct NavMeshTileHeader
{
   dtTileRef tileRef;
   int dataSize;
};

bool NavMesh::load()
{
   if(!dStrlen(mFileName))
      return false;

   FileStream stream;
   if(!stream.open(mFileName, Torque::FS::File::Read))
   {
      Con::errorf("Could not open file %s when loading navmesh %s.",
         mFileName, getName() ? getName() : getIdString());
      return false;
   }

   // Read header.
   NavMeshSetHeader header;
   stream.read(sizeof(NavMeshSetHeader), (char*)&header);
   if(header.magic != NAVMESHSET_MAGIC)
   {
      stream.close();
      Con::errorf("Navmesh magic incorrect when loading navmesh %s; possible corrupt navmesh file %s.",
         getName() ? getName() : getIdString(), mFileName);
      return false;
   }
   if(header.version != NAVMESHSET_VERSION)
   {
      stream.close();
      Con::errorf("Navmesh version incorrect when loading navmesh %s; possible corrupt navmesh file %s.",
         getName() ? getName() : getIdString(), mFileName);
      return false;
   }

   if(nm)
      dtFreeNavMesh(nm);
   nm = dtAllocNavMesh();
   if(!nm)
   {
      stream.close();
      Con::errorf("Out of memory when loading navmesh %s.",
         getName() ? getName() : getIdString());
      return false;
   }

   dtStatus status = nm->init(&header.params);
   if(dtStatusFailed(status))
   {
      stream.close();
      Con::errorf("Failed to initialise navmesh params when loading navmesh %s.",
         getName() ? getName() : getIdString());
      return false;
   }

   // Read tiles.
   for(U32 i = 0; i < header.numTiles; ++i)
   {
      NavMeshTileHeader tileHeader;
      stream.read(sizeof(NavMeshTileHeader), (char*)&tileHeader);
      if(!tileHeader.tileRef || !tileHeader.dataSize)
         break;

      unsigned char* data = (unsigned char*)dtAlloc(tileHeader.dataSize, DT_ALLOC_PERM);
      if(!data) break;
      memset(data, 0, tileHeader.dataSize);
      stream.read(tileHeader.dataSize, (char*)data);

      nm->addTile(data, tileHeader.dataSize, DT_TILE_FREE_DATA, tileHeader.tileRef, 0);
   }

   S32 s;
   stream.read(sizeof(S32), (char*)&s);
   setLinkCount(s);
   if (s > 0)
   {
      stream.read(sizeof(F32) * s * 6, (char*)const_cast<F32*>(mLinkVerts.address()));
      stream.read(sizeof(F32) * s, (char*)const_cast<F32*>(mLinkRads.address()));
      stream.read(sizeof(U8) * s, (char*)const_cast<U8*>(mLinkDirs.address()));
      stream.read(sizeof(U8) * s, (char*)const_cast<U8*>(mLinkAreas.address()));
      stream.read(sizeof(U16) * s, (char*)const_cast<U16*>(mLinkFlags.address()));
      stream.read(sizeof(F32) * s, (char*)const_cast<U32*>(mLinkIDs.address()));
   }
   mLinksUnsynced.fill(false);
   mLinkSelectStates.fill(Unselected);
   mDeleteLinks.fill(false);

   stream.close();

   updateTiles();

   if(isServerObject())
   {
      setMaskBits(LoadFlag);
      if(getEventManager())
         getEventManager()->postEvent("NavMeshUpdate", getIdString());
   }

   return true;
}

DefineEngineMethod(NavMesh, load, bool, (),,
   "@brief Load this NavMesh from its file.")
{
   return object->load();
}

bool NavMesh::save()
{
   if (!nm)
      return false;

   if (!dStrlen(mFileName) || !nm)
   {
      createNewFile();
   }
   
   FileStream stream;
   if(!stream.open(mFileName, Torque::FS::File::Write))
   {
      Con::errorf("Could not open file %s when saving navmesh %s.",
         mFileName, getName() ? getName() : getIdString());
      return false;
   }

   // Store header.
   NavMeshSetHeader header;
   header.magic = NAVMESHSET_MAGIC;
   header.version = NAVMESHSET_VERSION;
   header.numTiles = 0;
   for(U32 i = 0; i < nm->getMaxTiles(); ++i)
   {
      const dtMeshTile* tile = ((const dtNavMesh*)nm)->getTile(i);
      if (!tile || !tile->header || !tile->dataSize) continue;
      header.numTiles++;
   }
   memcpy(&header.params, nm->getParams(), sizeof(dtNavMeshParams));
   stream.write(sizeof(NavMeshSetHeader), (const char*)&header);

   // Store tiles.
   for(U32 i = 0; i < nm->getMaxTiles(); ++i)
   {
      const dtMeshTile* tile = ((const dtNavMesh*)nm)->getTile(i);
      if(!tile || !tile->header || !tile->dataSize) continue;

      NavMeshTileHeader tileHeader;
      tileHeader.tileRef = nm->getTileRef(tile);
      tileHeader.dataSize = tile->dataSize;

      stream.write(sizeof(tileHeader), (const char*)&tileHeader);
      stream.write(tile->dataSize, (const char*)tile->data);
   }

   S32 s = mLinkIDs.size();
   stream.write(sizeof(S32), (const char*)&s);
   if (s > 0)
   {
      stream.write(sizeof(F32) * s * 6, (const char*)mLinkVerts.address());
      stream.write(sizeof(F32) * s,     (const char*)mLinkRads.address());
      stream.write(sizeof(U8) * s,      (const char*)mLinkDirs.address());
      stream.write(sizeof(U8) * s,      (const char*)mLinkAreas.address());
      stream.write(sizeof(U16) * s,     (const char*)mLinkFlags.address());
      stream.write(sizeof(U32) * s,     (const char*)mLinkIDs.address());
   }

   stream.close();

   return true;
}

DefineEngineMethod(NavMesh, save, void, (),,
   "@brief Save this NavMesh to its file.")
{
   object->save();
}

void NavMesh::write(Stream &stream, U32 tabStop, U32 flags)
{
   save();
   Parent::write(stream, tabStop, flags);
}
