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

#ifndef _VEHICLE_H_
#define _VEHICLE_H_

#ifndef _SHAPEBASE_H_
#include "T3D/rigidShape.h"
#endif

class ParticleEmitter;
class ParticleEmitterData;
class ClippedPolyList;
struct RenderInst;
class Vehicle;

//----------------------------------------------------------------------------

struct VehicleData : public RigidShapeData
{
   typedef RigidShapeData Parent;

   enum VehicleConsts
   {
      VC_NUM_DUST_EMITTERS = 1,
      VC_NUM_DAMAGE_EMITTER_AREAS = 2,
      VC_NUM_DAMAGE_LEVELS = 2,
      VC_NUM_BUBBLE_EMITTERS = 1,
      VC_NUM_DAMAGE_EMITTERS = VC_NUM_DAMAGE_LEVELS + VC_NUM_BUBBLE_EMITTERS,
      VC_NUM_SPLASH_EMITTERS = 2,
      VC_BUBBLE_EMITTER = VC_NUM_DAMAGE_EMITTERS - VC_NUM_BUBBLE_EMITTERS,
   };

   F32 maxSteeringAngle;

   F32 collDamageThresholdVel;
   F32 collDamageMultiplier;

   F32 jetForce;
   F32 jetEnergyDrain;        ///< Energy drain/tick
   F32 minJetEnergy;

   F32 steeringReturn;
   F32 steeringReturnSpeedScale;
   bool powerSteering;

   ParticleEmitterData *   damageEmitterList[ VC_NUM_DAMAGE_EMITTERS ];
   Point3F damageEmitterOffset[ VC_NUM_DAMAGE_EMITTER_AREAS ];
   S32 damageEmitterIDList[ VC_NUM_DAMAGE_EMITTERS ];
   F32 damageLevelTolerance[ VC_NUM_DAMAGE_LEVELS ];
   F32 numDmgEmitterAreas;

   bool enablePhysicsRep;

   //
   VehicleData();
   bool preload(bool server, String &errorStr);
   static void initPersistFields();
   virtual void packData(BitStream* stream);
   virtual void unpackData(BitStream* stream);

   DECLARE_CONOBJECT(VehicleData);
};


//----------------------------------------------------------------------------
class PhysicsBody;

class Vehicle : public RigidShape
{
   typedef RigidShape Parent;

  protected:

   VehicleData* mDataBlock;
   SFXSource* mWakeSound;

   // Control
   Point2F mSteering;
   F32 mThrottle;
   bool mJetting;

   GFXStateBlockRef  mSolidSB;

   SimObjectPtr<ParticleEmitter> mDamageEmitterList[VehicleData::VC_NUM_DAMAGE_EMITTERS];

   //
   virtual bool onNewDataBlock( GameBaseData *dptr, bool reload );
   void updatePos(F32 dt);
   static void findCallback(SceneObject* obj,void * key);

//   virtual bool collideBody(const MatrixF& mat,Collision* info) = 0;
   virtual void updateMove(const Move* move);
   virtual void updateForces(F32 dt);

   void writePacketData(GameConnection * conn, BitStream *stream);
   void readPacketData (GameConnection * conn, BitStream *stream);
   U32  packUpdate  (NetConnection *conn, U32 mask, BitStream *stream);
   void unpackUpdate(NetConnection *conn,           BitStream *stream);
   void setControllingClient(GameConnection* connection);

   void updateLiftoffDust( F32 dt );
   void updateDamageSmoke( F32 dt );

   virtual U32 getCollisionMask();

   void updateFroth( F32 dt );

   /// ObjectRenderInst delegate hooked up in prepBatchRender 
   /// if GameBase::gShowBoundingBox is true.
   void _renderMassAndContacts( ObjectRenderInst *ri, SceneRenderState *state, BaseMatInstance *overrideMat );

   /// ObjectRenderInst delegate hooked up in prepBatchRender 
   /// if GameBase::gShowBoundingBox is true.
   void _renderMuzzleVector( ObjectRenderInst *ri, SceneRenderState *state, BaseMatInstance *overrideMat );

public:
   // Test code...
   static ClippedPolyList* sPolyList;
   static S32 sVehicleCount;

   //
   Vehicle();
   static void consoleInit();
   static void initPersistFields();
   void processTick(const Move *move);
   bool onAdd();
   void onRemove();

   /// Interpolates between move ticks @see processTick
   /// @param   dt   Change in time between the last call and this call to the function
   void advanceTime(F32 dt);

   void prepBatchRender( SceneRenderState *state, S32 mountedImageIndex );

   ///@name Rigid body methods
   ///@{

   void getCameraParameters(F32 *min, F32* max, Point3F* offset, MatrixF* rot);
   void getCameraTransform(F32* pos, MatrixF* mat);
   ///@}

   /// @name Mounted objects
   /// @{
   virtual void mountObject( SceneObject *obj, S32 node, const MatrixF &xfm = MatrixF::Identity );
   /// @}

   DECLARE_CONOBJECT(Vehicle);
};


#endif
