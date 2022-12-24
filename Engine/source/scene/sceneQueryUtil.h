#ifndef _SCENEQUERY_UTIL_H_
#define _SCENEQUERY_UTIL_H_

/// A contextual hint passed to the polylist methods which
/// allows it to return the appropriate geometry.
enum PolyListContext
{
   /// A hint that the polyist is intended 
   /// for collision testing.
   PLC_Collision,

   /// A hint that the polyist is for decal
   /// geometry generation.
   PLC_Decal,

   /// A hint that the polyist is used for
   /// selection from an editor or other tool.
   PLC_Selection,

   /// A hint that the polylist is used for
   /// building a representation of the environment
   /// used for navigation.
   PLC_Navigation,

   /// A hint that the polyist will be used
   /// to export geometry and would like to have
   /// texture coords and materials.   
   PLC_Export
};

struct SceneBinRange
{
   U16 minCoord[2];
   U16 maxCoord[2];

   inline U32 getWidth() const
   {
      return maxCoord[0] - minCoord[0];
   }

   inline U32 getHeight() const
   {
      return maxCoord[1] - minCoord[1];
   }

   inline void setGlobal()
   {
      minCoord[0] = 0;
      minCoord[1] = 0;
      maxCoord[0] = 0xFFFF;
      maxCoord[1] = 0xFFFF;
   }

   static SceneBinRange makeFromBin(U32 minX, U32 maxX, U32 minY, U32 maxY)
   {
      SceneBinRange outRange;
      outRange.minCoord[0] = minX;
      outRange.minCoord[1] = minY;
      outRange.maxCoord[0] = maxX;
      outRange.maxCoord[1] = maxY;
      return outRange;
   }

   static SceneBinRange makeGlobal()
   {
      SceneBinRange outRange;
      outRange.setGlobal();
      return outRange;
   }

   inline bool isGlobal() const
   {
      return minCoord[0] == 0 &&
         minCoord[0] == 0 &&
         maxCoord[0] == 0xFFFF &&
         maxCoord[1] == 0xFFFF;
   }

   inline bool shouldOverflow() const;

   inline bool operator==(const SceneBinRange& other) const
   {
      return memcmp(minCoord, other.minCoord, sizeof(minCoord)) == 0 &&
         memcmp(maxCoord, other.maxCoord, sizeof(maxCoord)) == 0;
   }
};

/// Lookup for bins assigned to SceneObject
struct SceneBinListLookup
{
   SceneBinRange mRange; ///< Range object is placed in
   U32 mListHandle;      ///< Handle for ref list
};

/// For simple queries.  Simply creates a vector of the objects
class SimpleQueryList
{
public:

   Vector< SceneObject* > mList;

   SimpleQueryList()
   {
      VECTOR_SET_ASSOCIATION(mList);
   }

   void insertObject(SceneObject* obj) { mList.push_back(obj); }
   static void insertionCallback(SceneObject* obj, void* key)
   {
      SimpleQueryList* pList = reinterpret_cast<SimpleQueryList*>(key);
      pList->insertObject(obj);
   }
};

#endif
