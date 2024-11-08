
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

#ifndef _AFX_MOORING_H_
#define _AFX_MOORING_H_

#include "renderInstance/renderPassManager.h"

#include "afx/afxEffectDefs.h"

class afxMooringData : public GameBaseData, public afxEffectDefs
{
  typedef GameBaseData  Parent;

public:
  U8            networking;
  bool          track_pos_only;
  bool          display_axis_marker;

public:
  /*C*/         afxMooringData();
  /*C*/         afxMooringData(const afxMooringData&, bool = false);

  bool  onAdd() override;
  void  packData(BitStream*) override;
  void  unpackData(BitStream*) override;

  bool  allowSubstitutions() const override { return true; }

  static void   initPersistFields();

  DECLARE_CONOBJECT(afxMooringData);
};

//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//
// afxMooring

class afxMooring : public GameBase, public afxEffectDefs
{
  typedef GameBase Parent;

private:
  afxMooringData*       mDataBlock;
  U32                   chor_id;
  bool                  hookup_with_chor;
  StringTableEntry      ghost_cons_name;

  GFXStateBlockRef      axis_sb;
  void                  _renderAxisLines(ObjectRenderInst*, SceneRenderState*, BaseMatInstance*);

protected:
   enum MaskBits 
   {
      PositionMask = Parent::NextFreeMask,
	    NextFreeMask = Parent::NextFreeMask << 1
   };

public:
  /*C*/                 afxMooring();
  /*C*/                 afxMooring(U32 networking, U32 chor_id, StringTableEntry cons_name);
  /*D*/                 ~afxMooring();

  bool          onNewDataBlock(GameBaseData* dptr, bool reload) override;
  void          advanceTime(F32 dt) override;
  bool          onAdd() override;
  void          onRemove() override;
  U32           packUpdate(NetConnection*, U32, BitStream*) override;
  void          unpackUpdate(NetConnection*, BitStream*) override;
  void          setTransform(const MatrixF&) override;

  void          prepRenderImage(SceneRenderState*) override;

  DECLARE_CONOBJECT(afxMooring);
  DECLARE_CATEGORY("UNLISTED");
};

//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~//~~~~~~~~~~~~~~~~~~~~~//

#endif // _AFX_MOORING_H_
