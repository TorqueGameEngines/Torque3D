//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
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

#ifndef _SUN_H_
#define _SUN_H_

#ifndef _SCENEOBJECT_H_
#include "scene/sceneObject.h"
#endif
#ifndef _COLOR_H_
#include "core/color.h"
#endif
#ifndef _LIGHTINFO_H_
#include "lighting/lightInfo.h"
#endif
#ifndef _LIGHTFLAREDATA_H_
#include "T3D/lightFlareData.h"
#endif

#include "T3D/assets/MaterialAsset.h"

class TimeOfDay;
class MatrixSet;

///
class Sun : public SceneObject, public ISceneLight
{
   typedef SceneObject Parent;

protected:

   F32 mSunAzimuth;
   
   F32 mSunElevation;

   LinearColorF mLightColor;

   LinearColorF mLightAmbient;

   F32 mBrightness;

   bool mAnimateSun;
   F32  mTotalTime;
   F32  mCurrTime;
   F32  mStartAzimuth;
   F32  mEndAzimuth;
   F32  mStartElevation;
   F32  mEndElevation;

   bool mCastShadows;
   S32 mStaticRefreshFreq;
   S32 mDynamicRefreshFreq;

   LightInfo *mLight;

   LightFlareData *mFlareData;
   LightFlareState mFlareState;
   F32 mFlareScale;

   bool mCoronaEnabled;

   DECLARE_MATERIALASSET(Sun, CoronaMaterial);
   DECLARE_ASSET_NET_SETGET(Sun, CoronaMaterial, UpdateMask);

   BaseMatInstance *mCoronaMatInst;
   MatrixSet *mMatrixSet;   
   F32 mCoronaScale;
   LinearColorF mCoronaTint;
   bool mCoronaUseLightColor;

   // These are not user specified.
   // These hold data calculated once used across several methods.
   F32 mCoronaWorldRadius;
   Point3F mLightWorldPos;

   void _conformLights();
   void _initCorona();
   void _renderCorona( ObjectRenderInst *ri, SceneRenderState *state, BaseMatInstance *overrideMat );
   void _updateTimeOfDay( TimeOfDay *timeOfDay, F32 time );

   // SimObject.
   void _onSelected() override;
   void _onUnselected() override;

   enum NetMaskBits 
   {
      UpdateMask = BIT(0)
   };

public:

   Sun();
   virtual ~Sun();

   // SimObject
   bool onAdd() override;
   void onRemove() override;

   // ConsoleObject
   DECLARE_CONOBJECT(Sun);
   DECLARE_CATEGORY("Lighting \t Lights");
   static void initPersistFields();
   void inspectPostApply() override;

   // NetObject
   U32 packUpdate( NetConnection *conn, U32 mask, BitStream *stream ) override;
   void unpackUpdate( NetConnection *conn, BitStream *stream ) override; 

   // ISceneLight
   void submitLights( LightManager *lm, bool staticLighting ) override;
   LightInfo* getLight() override { return mLight; }   

   // SceneObject   
   void prepRenderImage( SceneRenderState* state ) override;

   // ProcessObject
   void advanceTime( F32 dt ) override;

   ///
   void setAzimuth( F32 azimuth );

   ///
   void setElevation( F32 elevation );

   ///
   void setColor( const LinearColorF &color );

   ///
   void animate( F32 duration, F32 startAzimuth, F32 endAzimuth, F32 startElevation, F32 endElevation );
};

#endif // _SUN_H_
