
//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//
// Arcane-FX for MIT Licensed Open Source version of Torque 3D from GarageGames
// Copyright (C) 2015 Faust Logic, Inc.
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
//
//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//

#ifndef _AFX_STATIC_SHAPE_H_
#define _AFX_STATIC_SHAPE_H_

#include "T3D/staticShape.h"

//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//
// afxStaticShapeData

class afxStaticShapeData : public StaticShapeData
{
  typedef StaticShapeData Parent;

public:
  StringTableEntry  sequence;
  bool              ignore_scene_amb;
  bool              use_custom_scene_amb;
  LinearColorF            custom_scene_amb;
  bool              do_spawn;

public:
  /*C*/       afxStaticShapeData();
  /*C*/       afxStaticShapeData(const afxStaticShapeData&, bool = false);

  void        packData(BitStream* stream) override;
  void        unpackData(BitStream* stream) override;

  bool allowSubstitutions() const override { return true; }

  static void initPersistFields();

  DECLARE_CONOBJECT(afxStaticShapeData);
};

//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//
// afxStaticShape

class afxStaticShape : public StaticShape
{
  typedef StaticShape Parent;

private:
  StaticShapeData*      mDataBlock;
  afxStaticShapeData*   mAFX_data;
  bool                  mIs_visible;
  U32                   mChor_id;
  bool                  mHookup_with_chor;
  StringTableEntry      mGhost_cons_name;

protected:
  void          prepRenderImage(SceneRenderState*) override;

public:
  /*C*/                 afxStaticShape();
  /*D*/                 ~afxStaticShape();

  void                  init(U32 chor_id, StringTableEntry cons_name);

  bool          onNewDataBlock(GameBaseData* dptr, bool reload) override;
  void          advanceTime(F32 dt) override;
  U32           packUpdate(NetConnection*, U32, BitStream*) override;
  void          unpackUpdate(NetConnection*, BitStream*) override;

  const char*           getShapeFileName() const { return mDataBlock->mShapeAsset->getShapeFileName(); }
  void                  setVisibility(bool flag) { mIs_visible = flag; }

  DECLARE_CONOBJECT(afxStaticShape);
  DECLARE_CATEGORY("UNLISTED");
};

//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//

#endif // _AFX_STATIC_SHAPE_H_
