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

#ifndef _NAVMESH_H_
#define _NAVMESH_H_

#include <queue>

#include "scene/sceneObject.h"
#include "collision/concretePolyList.h"
#include "recastPolyList.h"
#include "util/messaging/eventManager.h"

#include "torqueRecast.h"
#include "duDebugDrawTorque.h"
#include "coverPoint.h"

#include <Recast.h>
#include <DetourNavMesh.h>
#include <DetourNavMeshBuilder.h>
#include <DebugDraw.h>
#include <DetourNavMeshQuery.h>

/// @class NavMesh
/// Represents a set of bounds within which a Recast navigation mesh is generated.
/// @see NavMeshPolyList
/// @see Trigger
class NavMesh : public SceneObject {
   typedef SceneObject Parent;
   friend class NavPath;

public:
   /// @name NavMesh build
   /// @{

   /// Initiates the navmesh build process, which includes notifying the
   /// clients and posting an event.
   bool build(bool background = true, bool saveIntermediates = false);
   /// Stop a build in progress.
   void cancelBuild();
   /// Generate cover points from a nav mesh.
   bool createCoverPoints();
   /// Remove all cover points
   void deleteCoverPoints();

   /// Save the navmesh to a file.
   bool save();
   /// Load a saved navmesh from a file.
   bool load();

   /// Instantly rebuild the tiles in the navmesh that overlap the box.
   void buildTiles(const Box3F &box);

   /// Instantly rebuild a specific tile.
   void buildTile(const U32 &tile);

   /// Rebuild parts of the navmesh where links have changed.
   void buildLinks();

   /// Data file to store this nav mesh in. (From engine executable dir.)
   StringTableEntry mFileName;

   /// Name of the SimSet to store cover points in. (Usually a SimGroup.)
   StringTableEntry mCoverSet;

   /// Cell width and height.
   F32 mCellSize, mCellHeight;
   /// @name Actor data
   /// @{
   F32 mWalkableHeight,
      mWalkableClimb,
      mWalkableRadius,
      mWalkableSlope;
   /// @}
   /// @name Generation data
   /// @{
   U32 mBorderSize;
   F32 mDetailSampleDist, mDetailSampleMaxError;
   U32 mMaxEdgeLen;
   F32 mMaxSimplificationError;
   static const U32 mMaxVertsPerPoly;
   U32 mMinRegionArea;
   U32 mMergeRegionArea;
   F32 mTileSize;
   U32 mMaxPolysPerTile;
   duDebugDrawTorque mDbgDraw;
   /// @}

   /// @name Water
   /// @{
   enum WaterMethod {
      Ignore,
      Solid,
      Impassable
   };

   enum DrawMode
   {
      DRAWMODE_NAVMESH,
      DRAWMODE_NAVMESH_TRANS,
      DRAWMODE_NAVMESH_BVTREE,
      DRAWMODE_NAVMESH_NODES,
      DRAWMODE_NAVMESH_PORTALS,
      DRAWMODE_NAVMESH_INVIS,
      DRAWMODE_MESH,
      DRAWMODE_VOXELS,
      DRAWMODE_VOXELS_WALKABLE,
      DRAWMODE_COMPACT,
      DRAWMODE_COMPACT_DISTANCE,
      DRAWMODE_COMPACT_REGIONS,
      DRAWMODE_REGION_CONNECTIONS,
      DRAWMODE_RAW_CONTOURS,
      DRAWMODE_BOTH_CONTOURS,
      DRAWMODE_CONTOURS,
      DRAWMODE_POLYMESH,
      DRAWMODE_POLYMESH_DETAIL,
      MAX_DRAWMODE
   };

   WaterMethod mWaterMethod;
   /// @}

   /// @}

   /// Return the index of the tile included by this point.
   S32 getTile(const Point3F& pos);

   /// Return the box of a given tile.
   Box3F getTileBox(U32 id);

   /// @name Links
   /// @{

   /// Add an off-mesh link.
   S32 addLink(const Point3F &from, const Point3F &to, bool biDir, F32 rad, U32 flags = 0);

   /// Get the ID of the off-mesh link near the point.
   S32 getLink(const Point3F &pos);

   /// Get the number of links this mesh has.
   S32 getLinkCount();

   /// Get the starting point of a link.
   Point3F getLinkStart(U32 idx);

   /// Get the ending point of a link.
   Point3F getLinkEnd(U32 idx);

   /// Get the flags used by a link.
   LinkData getLinkFlags(U32 idx);

   bool getLinkDir(U32 idx);

   F32 getLinkRadius(U32 idx);

   void setLinkDir(U32 idx, bool biDir);

   void setLinkRadius(U32 idx, F32 rad);

   /// Set flags used by a link.
   void setLinkFlags(U32 idx, const LinkData &d);

   void setDrawMode(DrawMode mode) { m_drawMode = mode; setMaskBits(LoadFlag); }

   /// Set the selected state of a link.
   void selectLink(U32 idx, bool select, bool hover = true);

   /// Delete the selected link.
   void deleteLink(U32 idx);

   dtNavMeshQuery* getNavMeshQuery() { return mQuery; }

   /// @}

   /// Should small characters use this mesh?
   bool mSmallCharacters;
   /// Should regular-sized characters use this mesh?
   bool mRegularCharacters;
   /// Should large characters use this mesh?
   bool mLargeCharacters;
   /// Should vehicles use this mesh?
   bool mVehicles;

   /// @name Annotations
   /// @{
   /* not implemented
   /// Should we automatically generate jump-down links?
   bool mJumpDownLinks;
   /// Height of a 'small' jump link.
   F32 mJumpLinkSmall;
   /// Height of a 'large' jump link.
   F32 mJumpLinkLarge;
   */
   /// Distance to search for cover.
   F32 mCoverDist;

   /// Distance to search horizontally when peeking around cover.
   F32 mPeekDist;

   /// Add cover to walls that don't have corners?
   bool mInnerCover;

   /// @}

   /// @name SimObject
   /// @{

   void onEditorEnable() override;
   void onEditorDisable() override;

   void write(Stream &stream, U32 tabStop, U32 flags) override;

   /// @}

   /// @name SceneObject
   /// @{

   static void initPersistFields();

   bool onAdd() override;
   void onRemove() override;

   enum flags {
      BuildFlag    = Parent::NextFreeMask << 0,
      LoadFlag     = Parent::NextFreeMask << 1,
      NextFreeMask = Parent::NextFreeMask << 2,
   };

   U32 packUpdate(NetConnection *conn, U32 mask, BitStream *stream) override;
   void unpackUpdate(NetConnection *conn, BitStream *stream) override;

   void setTransform(const MatrixF &mat) override;
   void setScale(const VectorF &scale) override;

   /// @}

   /// @name ProcessObject
   /// @{

   void processTick(const Move *move) override;

   /// @}

   /// @name Rendering
   /// @{

   void prepRenderImage(SceneRenderState *state) override;
   void render(ObjectRenderInst *ri, SceneRenderState *state, BaseMatInstance *overrideMat);
   void renderLinks(duDebugDraw &dd);
   void renderSearch(duDebugDraw& dd);
   void renderTileData(duDebugDrawTorque &dd, U32 tile);

   bool mAlwaysRender;

   /// @}

   NavMesh();
   ~NavMesh();
   DECLARE_CONOBJECT(NavMesh);
   DECLARE_CATEGORY("Navigation");

   /// Return the server-side NavMesh SimSet.
   static SimSet *getServerSet();

   /// Return the EventManager for all NavMeshes.
   static EventManager *getEventManager();

   void inspectPostApply() override;

   void createNewFile();

protected:

   dtNavMesh const* getNavMesh() { return nm; }

private:
   /// Builds the next tile in the dirty list.
   void buildNextTile();

   /// Save imtermediate navmesh creation data?
   bool mSaveIntermediates;

   /// @name Tiles
   /// @{

   struct Tile {
      /// Torque-space world box of this tile.
      Box3F box;
      /// Local coordinates of this box.
      U32 x, y;
      /// Recast min and max points.
      F32 bmin[3], bmax[3];
      /// Default constructor.
      Tile() : box(Box3F::Invalid), x(0), y(0), chf(0), solid(0), cset(0), pmesh(0), dmesh(0), triareas(nullptr)
      {
         bmin[0] = bmin[1] = bmin[2] = bmax[0] = bmax[1] = bmax[2] = 0.0f;
      }
      /// Value constructor.
      Tile(const Box3F &b, U32 _x, U32 _y, const F32 *min, const F32 *max)
         : box(b), x(_x), y(_y), chf(0), solid(0), cset(0), pmesh(0), dmesh(0), triareas(nullptr)
      {
         rcVcopy(bmin, min);
         rcVcopy(bmax, max);
      }

      ~Tile()
      {
         if (chf)
            delete chf;
         if (cset)
            delete cset;
         if (solid)
            delete solid;
         if (pmesh)
            delete pmesh;
         if (dmesh)
            delete dmesh;
         if (triareas)
            delete[] triareas;
      }

      unsigned char* triareas;
      rcCompactHeightfield* chf;
      rcHeightfield* solid;
      rcContourSet* cset;
      rcPolyMesh* pmesh;
      rcPolyMeshDetail* dmesh;
   };

   /// List of tiles.
   Vector<Tile> mTiles;

   /// List of indices to the tile array which are dirty.
   Vector<U32> mDirtyTiles;

   /// Update tile dimensions.
   void updateTiles(bool dirty = false);

   /// Generates navmesh data for a single tile.
   unsigned char *buildTileData(const Tile &tile, U32 &dataSize);

   /// @}

   /// @name Off-mesh links
   /// @{

   enum SelectState {
      Unselected,
      Hovered,
      Selected
   };

   Vector<F32> mLinkVerts;            ///< Coordinates of each link vertex
   Vector<bool> mLinksUnsynced;       ///< Are the editor links unsynced from the mesh?
   Vector<F32> mLinkRads;             ///< Radius of each link
   Vector<U8> mLinkDirs;              ///< Direction (one-way or bidirectional)
   Vector<U8> mLinkAreas;             ///< Area ID
   Vector<U16> mLinkFlags; ///< Flags
   Vector<U32> mLinkIDs;              ///< ID number of each link
   Vector<U8> mLinkSelectStates;      ///< Selection state of links
   Vector<bool> mDeleteLinks;         ///< Link will be deleted next build.

   U32 mCurLinkID;

   void eraseLink(U32 idx);
   void eraseLinks();
   void setLinkCount(U32 c);

   /// @}

   dtNavMesh *nm;
   rcContext *ctx;
   dtNavMeshQuery* mQuery;

   /// @name Cover
   /// @{

   struct CoverPointData {
      MatrixF trans;
      CoverPoint::Size size;
      bool peek[3];
   };

   /// Attempt to place cover points along a given edge.
   bool testEdgeCover(const Point3F &pos, const VectorF &dir, CoverPointData &data);

   /// @}

   /// Used to perform non-standard validation. detailSampleDist can be 0, or >= 0.9.
   static bool setProtectedDetailSampleDist(void *obj, const char *index, const char *data);

   /// Updates the client when we check the alwaysRender option.
   static bool setProtectedAlwaysRender(void *obj, const char *index, const char *data);

   /// @name Threaded updates
   /// @{

   /// A simple flag to say we are building.
   bool mBuilding;

   /// @}

   /// @name Rendering
   /// @{

   void renderToDrawer();

   /// @}

   /// Server-side set for all NavMesh objects.
   static SimObjectPtr<SimSet> smServerSet;

   /// Use this object to manage update events.
   static SimObjectPtr<EventManager> smEventManager;

protected:
   RecastPolyList* m_geo;
   unsigned char* m_triareas;
   rcHeightfield* m_solid;
   rcCompactHeightfield* m_chf;
   rcContourSet* m_cset;
   rcPolyMesh* m_pmesh;
   rcPolyMeshDetail* m_dmesh;
   rcConfig m_cfg;
   DrawMode m_drawMode;
   U32 mWaterVertStart;
   U32 mWaterTriStart;

   void cleanup();
};

typedef NavMesh::WaterMethod NavMeshWaterMethod;
DefineEnumType(NavMeshWaterMethod);

#endif
