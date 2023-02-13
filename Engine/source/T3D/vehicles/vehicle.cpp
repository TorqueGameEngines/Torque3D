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

#include "platform/platform.h"
#include "T3D/vehicles/vehicle.h"

#include "math/mMath.h"
#include "console/simBase.h"
#include "console/console.h"
#include "console/consoleTypes.h"
#include "console/engineAPI.h"
#include "collision/clippedPolyList.h"
#include "collision/planeExtractor.h"
#include "core/stream/bitStream.h"
#include "core/dnet.h"
#include "T3D/gameBase/gameConnection.h"
#include "T3D/fx/cameraFXMgr.h"
#include "ts/tsShapeInstance.h"
#include "T3D/fx/particleEmitter.h"
#include "sfx/sfxSystem.h"
#include "sfx/sfxProfile.h"
#include "sfx/sfxSource.h"
#include "math/mathIO.h"
#include "scene/sceneRenderState.h"
#include "T3D/trigger.h"
#include "T3D/item.h"
#include "gfx/primBuilder.h"
#include "gfx/gfxDrawUtil.h"
#include "materials/materialDefinition.h"
#include "T3D/physics/physicsPlugin.h"
#include "T3D/physics/physicsBody.h"
#include "T3D/physics/physicsCollision.h"


namespace {

static U32 sWorkingQueryBoxStaleThreshold = 10;    // The maximum number of ticks that go by before
                                                   // the mWorkingQueryBox is considered stale and
                                                   // needs updating.  Set to -1 to disable.

static F32 sWorkingQueryBoxSizeMultiplier = 2.0f;  // How much larger should the mWorkingQueryBox be
                                                   // made when updating the working collision list.
                                                   // The larger this number the less often the working list
                                                   // will be updated due to motion, but any non-static shape
                                                   // that moves into the query box will not be noticed.

// Client prediction
const S32 sMaxWarpTicks = 3;           // Max warp duration in ticks
const S32 sMaxPredictionTicks = 30;    // Number of ticks to predict

// Physics and collision constants
static F32 sRestTol = 0.5;             // % of gravity energy to be at rest
static S32 sRestCount = 10;            // Consecutive ticks before comming to rest

} // namespace {}

// Trigger objects that are not normally collided with.
static U32 sTriggerMask = ItemObjectType     |
                          TriggerObjectType  |
                          CorpseObjectType;

IMPLEMENT_CONOBJECT(VehicleData);

ConsoleDocClass( VehicleData,
   "@brief Base properties shared by all Vehicles (FlyingVehicle, HoverVehicle, "
   "WheeledVehicle).\n\n"
   "This datablock defines properties shared by all Vehicle types, but should "
   "not be instantiated directly. Instead, set the desired properties in the "
   "FlyingVehicleData, HoverVehicleData or WheeledVehicleData datablock.\n"

   "@section VehicleData_damage Damage\n\n"

   "The VehicleData class extends the basic energy/damage functionality provided "
   "by ShapeBaseData to include damage from collisions, as well as particle "
   "emitters activated automatically when damage levels reach user specified "
   "thresholds.\n\n"

   "The example below shows how to setup a Vehicle to:\n"
   "<ul>\n"
   "  <li>take damage when colliding with another object\n"
   "  <li>emit gray smoke particles from two locations on the Vehicle when damaged above 50%</li>\n"
   "  <li>emit black smoke particles from two locations on the Vehicle when damaged above 85%</li>\n"
   "  <li>emit bubbles when any active damage emitter point is underwater</li>\n"
   "</ul>\n\n"

   "@tsexample\n"
   "// damage from collisions\n"
   "collDamageMultiplier = 0.05;\n"
   "collDamageThresholdVel = 15;\n\n"

   "// damage levels\n"
   "damageLevelTolerance[0] = 0.5;\n"
   "damageEmitter[0] = GraySmokeEmitter;     // emitter used when damage is >= 50%\n"
   "damageLevelTolerance[1] = 0.85;\n"
   "damageEmitter[1] = BlackSmokeEmitter;    // emitter used when damage is >= 85%\n"
   "damageEmitter[2] = DamageBubbleEmitter;  // emitter used instead of damageEmitter[0:1]\n"
   "                                         // when offset point is underwater\n"
   "// emit offsets (used for all active damage level emitters)\n"
   "damageEmitterOffset[0] = \"0.5 3 1\";\n"
   "damageEmitterOffset[1] = \"-0.5 3 1\";\n"
   "numDmgEmitterAreas = 2;\n"
   "@endtsexample\n"

   "@ingroup Vehicles\n"
);

//----------------------------------------------------------------------------

VehicleData::VehicleData()
{
   shadowSize = 256;
   shadowProjectionDistance = 14.0f;
   maxSteeringAngle = M_PI_F/4.0f; // 45 deg.
   jetForce = 500;
   jetEnergyDrain =  0.8f;
   minJetEnergy = 1;
   steeringReturn = 0.0f;
   steeringReturnSpeedScale = 0.01f;
   powerSteering = false;

   dMemset( damageEmitterList, 0, sizeof( damageEmitterList ) );
   dMemset( damageEmitterOffset, 0, sizeof( damageEmitterOffset ) );
   dMemset( damageEmitterIDList, 0, sizeof( damageEmitterIDList ) );
   dMemset( damageLevelTolerance, 0, sizeof( damageLevelTolerance ) );

   numDmgEmitterAreas = 0;

   collDamageThresholdVel = 20;
   collDamageMultiplier = 0.05f;
   enablePhysicsRep = true;
}


//----------------------------------------------------------------------------

bool VehicleData::preload(bool server, String &errorStr)
{
   if (!Parent::preload(server, errorStr))
      return false;

   // Vehicle objects must define a collision detail
   if (!collisionDetails.size() || collisionDetails[0] == -1)
   {
      Con::errorf("VehicleData::preload failed: Vehicle models must define a collision-1 detail");
      errorStr = String::ToString("VehicleData: Couldn't load shape asset \"%s\"", mShapeAsset.getAssetId());
      return false;
   }

   U32 i;
   for( i=0; i<VC_NUM_DAMAGE_EMITTERS; i++ )
   {
      if( !damageEmitterList[i] && damageEmitterIDList[i] != 0 )
      {
         if( !Sim::findObject( damageEmitterIDList[i], damageEmitterList[i] ) )
         {
            Con::errorf( ConsoleLogEntry::General, "VehicleData::preload Invalid packet, bad datablockId(damageEmitter): 0x%x", damageEmitterIDList[i] );
         }
      }
   }

   return true;
}


//----------------------------------------------------------------------------

void VehicleData::packData(BitStream* stream)
{
   S32 i;
   Parent::packData(stream);

   stream->write(maxSteeringAngle);

   stream->write(jetForce);
   stream->write(jetEnergyDrain);
   stream->write(minJetEnergy);

   stream->write(steeringReturn);
   stream->write(steeringReturnSpeedScale);
   stream->writeFlag(powerSteering);

   stream->write( numDmgEmitterAreas );

   stream->write(enablePhysicsRep);

   for (i = 0; i < VC_NUM_DAMAGE_EMITTERS; i++)
   {
      if( stream->writeFlag( damageEmitterList[i] != NULL ) )
      {
         stream->writeRangedU32( damageEmitterList[i]->getId(), DataBlockObjectIdFirst,  DataBlockObjectIdLast );
      }
   }

   for (S32 j = 0;  j < VC_NUM_DAMAGE_EMITTER_AREAS; j++)
   {
      stream->write( damageEmitterOffset[j].x );
      stream->write( damageEmitterOffset[j].y );
      stream->write( damageEmitterOffset[j].z );
   }

   for (S32 k = 0; k < VC_NUM_DAMAGE_LEVELS; k++)
   {
      stream->write( damageLevelTolerance[k] );
   }

   stream->write(collDamageThresholdVel);
   stream->write(collDamageMultiplier);
}

void VehicleData::unpackData(BitStream* stream)
{
   Parent::unpackData(stream);

   S32 i;
   stream->read(&maxSteeringAngle);

   stream->read(&jetForce);
   stream->read(&jetEnergyDrain);
   stream->read(&minJetEnergy);

   stream->read(&steeringReturn);
   stream->read(&steeringReturnSpeedScale);
   powerSteering = stream->readFlag();

   stream->read( &numDmgEmitterAreas );

   stream->read(&enablePhysicsRep);

   for (i = 0; i < VC_NUM_DAMAGE_EMITTERS; i++)
   {
      if( stream->readFlag() )
      {
         damageEmitterIDList[i] = stream->readRangedU32( DataBlockObjectIdFirst, DataBlockObjectIdLast );
      }
   }

   for( S32 j=0; j<VC_NUM_DAMAGE_EMITTER_AREAS; j++ )
   {
      stream->read( &damageEmitterOffset[j].x );
      stream->read( &damageEmitterOffset[j].y );
      stream->read( &damageEmitterOffset[j].z );
   }

   for( S32 k=0; k<VC_NUM_DAMAGE_LEVELS; k++ )
   {
      stream->read( &damageLevelTolerance[k] );
   }

   stream->read(&collDamageThresholdVel);
   stream->read(&collDamageMultiplier);
}


//----------------------------------------------------------------------------

void VehicleData::initPersistFields()
{
   docsURL;
   Parent::initPersistFields();   

   addGroup("Particle Effects");
   addField( "damageEmitter", TYPEID< ParticleEmitterData >(), Offset(damageEmitterList, VehicleData), VC_NUM_DAMAGE_EMITTERS,
      "@brief Array of particle emitters used to generate damage (dust, smoke etc) "
      "effects.\n\n"
      "Currently, the first two emitters (indices 0 and 1) are used when the damage "
      "level exceeds the associated damageLevelTolerance. The 3rd emitter is used "
      "when the emitter point is underwater.\n\n"
      "@see damageEmitterOffset" );
   addField( "damageEmitterOffset", TypePoint3F, Offset(damageEmitterOffset, VehicleData), VC_NUM_DAMAGE_EMITTER_AREAS,
      "@brief Object space \"x y z\" offsets used to emit particles for the "
      "active damageEmitter.\n\n"
      "@tsexample\n"
      "// damage levels\n"
      "damageLevelTolerance[0] = 0.5;\n"
      "damageEmitter[0] = SmokeEmitter;\n"
      "// emit offsets (used for all active damage level emitters)\n"
      "damageEmitterOffset[0] = \"0.5 3 1\";\n"
      "damageEmitterOffset[1] = \"-0.5 3 1\";\n"
      "numDmgEmitterAreas = 2;\n"
      "@endtsexample\n" );
   addField( "damageLevelTolerance", TypeF32, Offset(damageLevelTolerance, VehicleData), VC_NUM_DAMAGE_LEVELS,
      "@brief Damage levels (as a percentage of maxDamage) above which to begin "
      "emitting particles from the associated damageEmitter.\n\n"
      "Levels should be in order of increasing damage.\n\n"
      "@see damageEmitterOffset" );
   addField( "numDmgEmitterAreas", TypeF32, Offset(numDmgEmitterAreas, VehicleData),
      "Number of damageEmitterOffset values to use for each damageEmitter.\n\n"
      "@see damageEmitterOffset" );
   endGroup("Particle Effects");

   addGroup("Physics");
   addField("enablePhysicsRep", TypeBool, Offset(enablePhysicsRep, VehicleData),
      "@brief Creates a representation of the object in the physics plugin.\n");
   endGroup("Physics");

   addGroup("Collision");
   addField( "collDamageThresholdVel", TypeF32, Offset(collDamageThresholdVel, VehicleData),
      "Minimum collision velocity to cause damage to this vehicle.\nCurrently unused." );
   addField( "collDamageMultiplier", TypeF32, Offset(collDamageMultiplier, VehicleData),
      "@brief Damage to this vehicle after a collision (multiplied by collision "
      "velocity).\n\nCurrently unused." );
   endGroup("Collision");

   addGroup("Steering");
      addField( "jetForce", TypeF32, Offset(jetForce, VehicleData),
         "@brief Additional force applied to the vehicle when it is jetting.\n\n"
         "For WheeledVehicles, the force is applied in the forward direction. For "
         "FlyingVehicles, the force is applied in the thrust direction." );
      addField( "jetEnergyDrain", TypeF32, Offset(jetEnergyDrain, VehicleData),
      "@brief Energy amount to drain for each tick the vehicle is jetting.\n\n"
         "Once the vehicle's energy level reaches 0, it will no longer be able to jet." );
      addField( "minJetEnergy", TypeF32, Offset(minJetEnergy, VehicleData),
      "Minimum vehicle energy level to begin jetting." );
      addField( "maxSteeringAngle", TypeF32, Offset(maxSteeringAngle, VehicleData),
         "Maximum yaw (horizontal) and pitch (vertical) steering angle in radians." );
   endGroup("Steering");

   addGroup("AutoCorrection");
   addField( "powerSteering", TypeBool, Offset(powerSteering, VehicleData),
      "If true, steering does not auto-centre while the vehicle is being steered by its driver." );
   addField( "steeringReturn", TypeF32, Offset(steeringReturn, VehicleData),
      "Rate at which the vehicle's steering returns to forwards when it is moving." );
   addField( "steeringReturnSpeedScale", TypeF32, Offset(steeringReturnSpeedScale, VehicleData),
      "Amount of effect the vehicle's speed has on its rate of steering return." );
   endGroup("AutoCorrection");
}


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
IMPLEMENT_CONOBJECT(Vehicle);

ConsoleDocClass( Vehicle,
   "@brief Base functionality shared by all Vehicles (FlyingVehicle, HoverVehicle, "
   "WheeledVehicle).\n\n"
   "This object implements functionality shared by all Vehicle types, but should "
   "not be instantiated directly. Create a FlyingVehicle, HoverVehicle, or "
   "WheeledVehicle instead.\n"
   "@note The model used for any Vehicle must include a collision mesh at detail "
   "size -1.\n"
   "@ingroup Vehicles\n"
);

Vehicle::Vehicle()
{
   mDataBlock = 0;
   mTypeMask |= VehicleObjectType | DynamicShapeObjectType;

   mDelta.pos = Point3F(0,0,0);
   mDelta.posVec = Point3F(0,0,0);
   mDelta.warpTicks = mDelta.warpCount = 0;
   mDelta.dt = 1;
   mDelta.move = NullMove;
   mPredictionCount = 0;
   mDelta.cameraOffset.set(0,0,0);
   mDelta.cameraVec.set(0,0,0);
   mDelta.cameraRot.set(0,0,0);
   mDelta.cameraRotVec.set(0,0,0);

   mRigid.linPosition.set(0, 0, 0);
   mRigid.linVelocity.set(0, 0, 0);
   mRigid.angPosition.identity();
   mRigid.angVelocity.set(0, 0, 0);
   mRigid.linMomentum.set(0, 0, 0);
   mRigid.angMomentum.set(0, 0, 0);
   mContacts.clear();

   mSteering.set(0,0);
   mThrottle = 0;
   mJetting = false;

   mCameraOffset.set(0,0,0);

   dMemset( mDamageEmitterList, 0, sizeof( mDamageEmitterList ) );

   mDisableMove = false;
   restCount = 0;

   inLiquid = false;
   mWakeSound = NULL;

   mWorkingQueryBox.minExtents.set(-1e9f, -1e9f, -1e9f);
   mWorkingQueryBox.maxExtents.set(-1e9f, -1e9f, -1e9f);
   mWorkingQueryBoxCountDown = sWorkingQueryBoxStaleThreshold;

   mPhysicsRep = NULL;
}

U32 Vehicle::getCollisionMask()
{
   AssertFatal(false, "Vehicle::getCollisionMask is pure virtual!");
   return 0;
}

//----------------------------------------------------------------------------

bool Vehicle::onAdd()
{
   if (!Parent::onAdd())
      return false;

   mWorkingQueryBox.minExtents.set(-1e9f, -1e9f, -1e9f);
   mWorkingQueryBox.maxExtents.set(-1e9f, -1e9f, -1e9f);

   // When loading from a mission script, the base SceneObject's transform
   // will have been set and needs to be transfered to the rigid body.
   mRigid.setTransform(mObjToWorld);

   // Initialize interpolation vars.
   mDelta.rot[1] = mDelta.rot[0] = mRigid.angPosition;
   mDelta.pos = mRigid.linPosition;
   mDelta.posVec = Point3F(0,0,0);

   // Create Emitters on the client
   if( isClientObject() )
   {
      U32 j;
      for( j=0; j<VehicleData::VC_NUM_DAMAGE_EMITTERS; j++ )
      {
         if( mDataBlock->damageEmitterList[j] )
         {
            mDamageEmitterList[j] = new ParticleEmitter;
            mDamageEmitterList[j]->onNewDataBlock( mDataBlock->damageEmitterList[j], false );
            if( !mDamageEmitterList[j]->registerObject() )
            {
               Con::warnf( ConsoleLogEntry::General, "Could not register damage emitter for class: %s", mDataBlock->getName() );
               delete mDamageEmitterList[j];
               mDamageEmitterList[j] = NULL;
            }

         }
      }
   }

   // Create a new convex.
   AssertFatal(mDataBlock->collisionDetails[0] != -1, "Error, a vehicle must have a collision-1 detail!");
   mConvex.mObject    = this;
   mConvex.pShapeBase = this;
   mConvex.hullId     = 0;
   mConvex.box        = mObjBox;
   mConvex.box.minExtents.convolve(mObjScale);
   mConvex.box.maxExtents.convolve(mObjScale);
   mConvex.findNodeTransform();

   _createPhysics();

   return true;
}

void Vehicle::onRemove()
{
   SAFE_DELETE(mPhysicsRep);

   U32 i=0;

   for( i=0; i<VehicleData::VC_NUM_DAMAGE_EMITTERS; i++ )
   {
      if( mDamageEmitterList[i] )
      {
         mDamageEmitterList[i]->deleteWhenEmpty();
         mDamageEmitterList[i] = NULL;
      }
   }

   mWorkingQueryBox.minExtents.set(-1e9f, -1e9f, -1e9f);
   mWorkingQueryBox.maxExtents.set(-1e9f, -1e9f, -1e9f);

   Parent::onRemove();
}


//----------------------------------------------------------------------------

void Vehicle::processTick(const Move* move)
{
   PROFILE_SCOPE( Vehicle_ProcessTick );

   ShapeBase::processTick(move);
   if ( isMounted() )
      return;

   // Warp to catch up to server
   if (mDelta.warpCount < mDelta.warpTicks)
   {
      mDelta.warpCount++;

      // Set new pos.
      mObjToWorld.getColumn(3,&mDelta.pos);
      mDelta.pos += mDelta.warpOffset;
      mDelta.rot[0] = mDelta.rot[1];
      mDelta.rot[1].interpolate(mDelta.warpRot[0],mDelta.warpRot[1],F32(mDelta.warpCount)/mDelta.warpTicks);
      setPosition(mDelta.pos,mDelta.rot[1]);

      // Pos backstepping
      mDelta.posVec.x = -mDelta.warpOffset.x;
      mDelta.posVec.y = -mDelta.warpOffset.y;
      mDelta.posVec.z = -mDelta.warpOffset.z;
   }
   else 
   {
      if (!move) 
      {
         if (isGhost()) 
         {
            // If we haven't run out of prediction time,
            // predict using the last known move.
            if (mPredictionCount-- <= 0)
               return;
            move = &mDelta.move;
         }
         else
            move = &NullMove;
      }

      // Process input move
      updateMove(move);

      // Save current rigid state interpolation
      mDelta.posVec = mRigid.linPosition;
      mDelta.rot[0] = mRigid.angPosition;

      // Update the physics based on the integration rate
      S32 count = mDataBlock->integration;
      --mWorkingQueryBoxCountDown;

      if (!mDisableMove)
         updateWorkingCollisionSet(getCollisionMask());
      for (U32 i = 0; i < count; i++)
         updatePos(TickSec / count);

      // Wrap up interpolation info
      mDelta.pos     = mRigid.linPosition;
      mDelta.posVec -= mRigid.linPosition;
      mDelta.rot[1]  = mRigid.angPosition;

      // Update container database
      setPosition(mRigid.linPosition, mRigid.angPosition);
      setMaskBits(PositionMask);
      updateContainer();

      //TODO: Only update when position has actually changed
      //no need to check if mDataBlock->enablePhysicsRep is false as mPhysicsRep will be NULL if it is
      if (mPhysicsRep)
         mPhysicsRep->moveKinematicTo(getTransform());
   }
}

void Vehicle::advanceTime(F32 dt)
{
   PROFILE_SCOPE( Vehicle_AdvanceTime );

   Parent::advanceTime(dt);

   updateLiftoffDust( dt );
   updateDamageSmoke( dt );
}


//----------------------------------------------------------------------------

bool Vehicle::onNewDataBlock(GameBaseData* dptr,bool reload)
{
   mDataBlock = dynamic_cast<VehicleData*>(dptr);
   if (!mDataBlock || !Parent::onNewDataBlock(dptr, reload))
      return false;

   // Update Rigid Info
   mRigid.mass = mDataBlock->mass;
   mRigid.oneOverMass = 1 / mRigid.mass;
   mRigid.friction = mDataBlock->body.friction;
   mRigid.restitution = mDataBlock->body.restitution;
   mRigid.setCenterOfMass(mDataBlock->massCenter);

   // Ignores massBox, just set sphere for now. Derived objects
   // can set what they want.
   mRigid.setObjectInertia();

   if (isGhost()) 
   {
      // Create the sound ahead of time.  This reduces runtime
      // costs and makes the system easier to understand.
      SFX_DELETE( mWakeSound );
   }

   return true;
}


//----------------------------------------------------------------------------

void Vehicle::getCameraParameters(F32 *min,F32* max,Point3F* off,MatrixF* rot)
{
   *min = mDataBlock->cameraMinDist;
   *max = mDataBlock->cameraMaxDist;

   off->set(0,0,mDataBlock->cameraOffset);
   rot->identity();
}


//----------------------------------------------------------------------------

void Vehicle::getCameraTransform(F32* pos, MatrixF* mat)
{
   // Returns camera to world space transform
   // Handles first person / third person camera position
   if (isServerObject() && mShapeInstance)
      mShapeInstance->animateNodeSubtrees(true);

   if (*pos == 0) 
   {
      getRenderEyeTransform(mat);
   }
   else
   {
      // Get the shape's camera parameters.
      F32 min, max;
      MatrixF rot;
      Point3F offset;
      getCameraParameters(&min, &max, &offset, &rot);

      // Start with the current eye position
      MatrixF eye;
      getRenderEyeTransform(&eye);

      // Build a transform that points along the eye axis
      // but where the Z axis is always up.
      if (mDataBlock->cameraRoll)
         mat->mul(eye, rot);
      else
      {
         MatrixF cam(1);
         VectorF x, y, z(0, 0, 1);
         eye.getColumn(1, &y);
         mCross(y, z, &x);
         x.normalize();
         mCross(x, y, &z);
         z.normalize();
         cam.setColumn(0, x);
         cam.setColumn(1, y);
         cam.setColumn(2, z);
         mat->mul(cam, rot);
      }

      // Camera is positioned straight back along the eye's -Y axis.
      // A ray is cast to make sure the camera doesn't go through
      // anything solid.
      VectorF vp, vec;
      vp.x = vp.z = 0;
      vp.y = -(max - min) * *pos;
      eye.mulV(vp, &vec);

      // Use the camera node as the starting position if it exists.
      Point3F osp, sp;
      if (mDataBlock->cameraNode != -1)
      {
         mShapeInstance->mNodeTransforms[mDataBlock->cameraNode].getColumn(3, &osp);
         getRenderTransform().mulP(osp, &sp);
      }
      else
         eye.getColumn(3, &sp);

      // Make sure we don't hit ourself...
      disableCollision();
      if (isMounted())
         getObjectMount()->disableCollision();

      // Cast the ray into the container database to see if we're going
      // to hit anything.
      RayInfo collision;
      Point3F ep = sp + vec + offset + mCameraOffset;
      if (mContainer->castRay(sp, ep,
         ~(WaterObjectType | GameBaseObjectType | DefaultObjectType | sTriggerMask),
         &collision) == true) {

         // Shift the collision point back a little to try and
         // avoid clipping against the front camera plane.
         F32 t = collision.t - (-mDot(vec, collision.normal) / vec.len()) * 0.1;
         if (t > 0.0f)
            ep = sp + offset + mCameraOffset + (vec * t);
         else
            eye.getColumn(3, &ep);
      }
      mat->setColumn(3, ep);

      // Re-enable our collision.
      if (isMounted())
         getObjectMount()->enableCollision();
      enableCollision();
   }

   // Apply Camera FX.
   mat->mul( gCamFXMgr.getTrans() );
}

//----------------------------------------------------------------------------

void Vehicle::updateMove(const Move* move)
{
   PROFILE_SCOPE( Vehicle_UpdateMove );

   mDelta.move = *move;

   // Image Triggers
   if (mDamageState == Enabled) {
      setImageTriggerState(0,move->trigger[0]);
      setImageTriggerState(1,move->trigger[1]);
   }

   // Throttle
   if(!mDisableMove)
      mThrottle = move->y;

   // Steering
   if (move != &NullMove) {
      F32 y = move->yaw;
      mSteering.x = mClampF(mSteering.x + y,-mDataBlock->maxSteeringAngle,
                            mDataBlock->maxSteeringAngle);
      F32 p = move->pitch;
      mSteering.y = mClampF(mSteering.y + p,-mDataBlock->maxSteeringAngle,
                            mDataBlock->maxSteeringAngle);
   }
   else {
      mSteering.x = 0;
      mSteering.y = 0;
   }

   // Steering return
   if(mDataBlock->steeringReturn > 0.0f &&
      (!mDataBlock->powerSteering || (move->yaw == 0.0f && move->pitch == 0.0f)))
   {
      Point2F returnAmount(mSteering.x * mDataBlock->steeringReturn * TickSec,
                           mSteering.y * mDataBlock->steeringReturn * TickSec);
      if(mDataBlock->steeringReturnSpeedScale > 0.0f)
      {
         Point3F vel;
         mWorldToObj.mulV(getVelocity(), &vel);
         returnAmount += Point2F(mSteering.x * vel.y * mDataBlock->steeringReturnSpeedScale * TickSec,
                                 mSteering.y * vel.y * mDataBlock->steeringReturnSpeedScale * TickSec);
      }
      mSteering -= returnAmount;
   }

   // Jetting flag
   if (move->trigger[3]) {
      if (!mJetting && getEnergyLevel() >= mDataBlock->minJetEnergy)
         mJetting = true;
      if (mJetting) {
         F32 newEnergy = getEnergyLevel() - mDataBlock->jetEnergyDrain;
         if (newEnergy < 0) {
            newEnergy = 0;
            mJetting = false;
         }
         setEnergyLevel(newEnergy);
      }
   }
   else
      mJetting = false;
}

//----------------------------------------------------------------------------
/** Update the physics
*/

void Vehicle::updatePos(F32 dt)
{
   PROFILE_SCOPE( Vehicle_UpdatePos );

   Point3F origVelocity = mRigid.linVelocity;

   // Update internal forces acting on the body.
   mRigid.clearForces();
   updateForces(dt);

   // Update collision information based on our current pos.
   bool collided = false;
   if (!mRigid.atRest && !mDisableMove)
   {
      collided = updateCollision(dt);

      // Now that all the forces have been processed, lets
      // see if we're at rest.  Basically, if the kinetic energy of
      // the vehicles is less than some percentage of the energy added
      // by gravity for a short period, we're considered at rest.
      // This should really be part of the rigid class...
      if (mCollisionList.getCount()) 
      {
         F32 k = mRigid.getKineticEnergy();
         F32 G = mNetGravity * dt;
         F32 Kg = 0.5 * mRigid.mass * G * G;
         if (k < sRestTol * Kg && ++restCount > sRestCount)
            mRigid.setAtRest();
      }
      else
         restCount = 0;
   }

   // Integrate forward
   if (!mRigid.atRest && !mDisableMove)
      mRigid.integrate(dt);

   // Deal with client and server scripting, sounds, etc.
   if (isServerObject()) {

      // Check triggers and other objects that we normally don't
      // collide with.  This function must be called before notifyCollision
      // as it will queue collision.
      checkTriggers();

      // Invoke the onCollision notify callback for all the objects
      // we've just hit.
      notifyCollision();

      // Server side impact script callback
      if (collided) {
         VectorF collVec = mRigid.linVelocity - origVelocity;
         F32 collSpeed = collVec.len();
         if (collSpeed > mDataBlock->minImpactSpeed)
            onImpact(collVec);
      }

      // Water script callbacks
      if (!inLiquid && mWaterCoverage != 0.0f) {
         mDataBlock->onEnterLiquid_callback( this, mWaterCoverage, mLiquidType.c_str() );
         inLiquid = true;
      }
      else if (inLiquid && mWaterCoverage == 0.0f) {
         mDataBlock->onLeaveLiquid_callback( this, mLiquidType.c_str() );
         inLiquid = false;
      }

   }
   else {

      // Play impact sounds on the client.
      if (collided) {
         F32 collSpeed = (mRigid.linVelocity - origVelocity).len();
         S32 impactSound = -1;
         if (collSpeed >= mDataBlock->hardImpactSpeed)
            impactSound = RigidShapeData::Body::HardImpactSound;
         else
            if (collSpeed >= mDataBlock->softImpactSpeed)
               impactSound = RigidShapeData::Body::SoftImpactSound;

         if (impactSound != -1 && mDataBlock->getBodySoundsProfile(impactSound) != NULL)
            SFX->playOnce( mDataBlock->getBodySoundsProfile(impactSound), &getTransform() );
      }

      // Water volume sounds
      F32 vSpeed = getVelocity().len();
      if (!inLiquid && mWaterCoverage >= 0.8f) {
         if (vSpeed >= mDataBlock->hardSplashSoundVel)
            SFX->playOnce( mDataBlock->getWaterSoundsProfile(RigidShapeData::ImpactHard), &getTransform() );
         else
            if (vSpeed >= mDataBlock->medSplashSoundVel)
               SFX->playOnce( mDataBlock->getWaterSoundsProfile(RigidShapeData::ImpactMedium), &getTransform() );
         else
            if (vSpeed >= mDataBlock->softSplashSoundVel)
               SFX->playOnce( mDataBlock->getWaterSoundsProfile(RigidShapeData::ImpactSoft), &getTransform() );
         inLiquid = true;
      }
      else
         if(inLiquid && mWaterCoverage < 0.8f) {
            if (vSpeed >= mDataBlock->exitSplashSoundVel)
               SFX->playOnce( mDataBlock->getWaterSoundsProfile(RigidShapeData::ExitWater), &getTransform() );
         inLiquid = false;
      }
   }
}


//----------------------------------------------------------------------------

void Vehicle::updateForces(F32 /*dt*/)
{
   // Nothing here.
}


/** The callback used in by the checkTriggers() method.
   The checkTriggers method uses a container search which will
   invoke this callback on each obj that matches.
*/
void Vehicle::findCallback(SceneObject* obj,void *key)
{
   Vehicle* vehicle = reinterpret_cast<Vehicle*>(key);
   U32 objectMask = obj->getTypeMask();

   // Check: triggers, corpses and items, basically the same things
   // that the player class checks for
   if (objectMask & TriggerObjectType) {
      Trigger* pTrigger = static_cast<Trigger*>(obj);
      pTrigger->potentialEnterObject(vehicle);
   }
   else if (objectMask & CorpseObjectType) {
      ShapeBase* col = static_cast<ShapeBase*>(obj);
      vehicle->queueCollision(col,vehicle->getVelocity() - col->getVelocity());
   }
   else if (objectMask & ItemObjectType) {
      Item* item = static_cast<Item*>(obj);
      if (vehicle != item->getCollisionObject())
         vehicle->queueCollision(item,vehicle->getVelocity() - item->getVelocity());
   }
}


//----------------------------------------------------------------------------

void Vehicle::writePacketData(GameConnection *connection, BitStream *stream)
{
   Parent::writePacketData(connection, stream);
   mathWrite(*stream, mSteering);

   mathWrite(*stream, mRigid.linPosition);
   mathWrite(*stream, mRigid.angPosition);
   mathWrite(*stream, mRigid.linMomentum);
   mathWrite(*stream, mRigid.angMomentum);
   stream->writeFlag(mRigid.atRest);
   stream->writeFlag(mContacts.getCount() == 0);

   stream->writeFlag(mDisableMove);
   stream->setCompressionPoint(mRigid.linPosition);
}

void Vehicle::readPacketData(GameConnection *connection, BitStream *stream)
{
   Parent::readPacketData(connection, stream);
   mathRead(*stream, &mSteering);

   mathRead(*stream, &mRigid.linPosition);
   mathRead(*stream, &mRigid.angPosition);
   mathRead(*stream, &mRigid.linMomentum);
   mathRead(*stream, &mRigid.angMomentum);
   mRigid.atRest = stream->readFlag();
   if (stream->readFlag())
      mContacts.clear();
   mRigid.updateInertialTensor();
   mRigid.updateVelocity();
   mRigid.updateCenterOfMass();

   mDisableMove = stream->readFlag();
   stream->setCompressionPoint(mRigid.linPosition);
}


//----------------------------------------------------------------------------

U32 Vehicle::packUpdate(NetConnection *con, U32 mask, BitStream *stream)
{
   U32 retMask = Parent::packUpdate(con, mask, stream);

   stream->writeFlag(mJetting);

   // The rest of the data is part of the control object packet update.
   // If we're controlled by this client, we don't need to send it.
   if (stream->writeFlag(getControllingClient() == con && !(mask & InitialUpdateMask)))
      return retMask;

   F32 yaw = (mSteering.x + mDataBlock->maxSteeringAngle) / (2 * mDataBlock->maxSteeringAngle);
   F32 pitch = (mSteering.y + mDataBlock->maxSteeringAngle) / (2 * mDataBlock->maxSteeringAngle);
   stream->writeFloat(yaw,9);
   stream->writeFloat(pitch,9);
   mDelta.move.pack(stream);

   if (stream->writeFlag(mask & PositionMask))
   {
      stream->writeCompressedPoint(mRigid.linPosition);
      mathWrite(*stream, mRigid.angPosition);
      mathWrite(*stream, mRigid.linMomentum);
      mathWrite(*stream, mRigid.angMomentum);
      stream->writeFlag(mRigid.atRest);
   }

   
   stream->writeFloat(mClampF(getEnergyValue(), 0.f, 1.f), 8);

   return retMask;
}

void Vehicle::unpackUpdate(NetConnection *con, BitStream *stream)
{
   Parent::unpackUpdate(con,stream);

   mJetting = stream->readFlag();

   if (stream->readFlag())
      return;

   F32 yaw = stream->readFloat(9);
   F32 pitch = stream->readFloat(9);
   mSteering.x = (2 * yaw * mDataBlock->maxSteeringAngle) - mDataBlock->maxSteeringAngle;
   mSteering.y = (2 * pitch * mDataBlock->maxSteeringAngle) - mDataBlock->maxSteeringAngle;
   mDelta.move.unpack(stream);

   if (stream->readFlag()) 
   {
      mPredictionCount = sMaxPredictionTicks;
      F32 speed = mRigid.linVelocity.len();
      mDelta.warpRot[0] = mRigid.angPosition;

      // Read in new position and momentum values
      stream->readCompressedPoint(&mRigid.linPosition);
      mathRead(*stream, &mRigid.angPosition);
      mathRead(*stream, &mRigid.linMomentum);
      mathRead(*stream, &mRigid.angMomentum);
      mRigid.atRest = stream->readFlag();
      mRigid.updateVelocity();

      if (isProperlyAdded()) 
      {
         // Determine number of ticks to warp based on the average
         // of the client and server velocities.
         Point3F cp = mDelta.pos + mDelta.posVec * mDelta.dt;
         mDelta.warpOffset = mRigid.linPosition - cp;

         // Calc the distance covered in one tick as the average of
         // the old speed and the new speed from the server.
         F32 dt,as = (speed + mRigid.linVelocity.len()) * 0.5 * TickSec;

         // Cal how many ticks it will take to cover the warp offset.
         // If it's less than what's left in the current tick, we'll just
         // warp in the remaining time.
         if (!as || (dt = mDelta.warpOffset.len() / as) > sMaxWarpTicks)
            dt = mDelta.dt + sMaxWarpTicks;
         else
            dt = (dt <= mDelta.dt)? mDelta.dt : mCeil(dt - mDelta.dt) + mDelta.dt;

         // Adjust current frame interpolation
         if (mDelta.dt) {
            mDelta.pos = cp + (mDelta.warpOffset * (mDelta.dt / dt));
            mDelta.posVec = (cp - mDelta.pos) / mDelta.dt;
            QuatF cr;
            cr.interpolate(mDelta.rot[1],mDelta.rot[0],mDelta.dt);
            mDelta.rot[1].interpolate(cr,mRigid.angPosition,mDelta.dt / dt);
            mDelta.rot[0].extrapolate(mDelta.rot[1],cr,mDelta.dt);
         }

         // Calculated multi-tick warp
         mDelta.warpCount = 0;
         mDelta.warpTicks = (S32)(mFloor(dt));
         if (mDelta.warpTicks) 
         {
            mDelta.warpOffset = mRigid.linPosition - mDelta.pos;
            mDelta.warpOffset /= (F32)mDelta.warpTicks;
            mDelta.warpRot[0] = mDelta.rot[1];
            mDelta.warpRot[1] = mRigid.angPosition;
         }
      }
      else 
      {
         // Set the vehicle to the server position
         mDelta.dt  = 0;
         mDelta.pos = mRigid.linPosition;
         mDelta.posVec.set(0,0,0);
         mDelta.rot[1] = mDelta.rot[0] = mRigid.angPosition;
         mDelta.warpCount = mDelta.warpTicks = 0;
         setPosition(mRigid.linPosition, mRigid.angPosition);
      }
      mRigid.updateCenterOfMass();
   }

   setEnergyLevel(stream->readFloat(8) * mDataBlock->maxEnergy);
}

void Vehicle::setControllingClient(GameConnection* client)
{
   ShapeBase::setControllingClient(client);
}

//----------------------------------------------------------------------------

void Vehicle::consoleInit()
{
   Con::addVariable("$vehicle::workingQueryBoxStaleThreshold",TypeS32,&sWorkingQueryBoxStaleThreshold, 
      "@brief The maximum number of ticks that go by before the mWorkingQueryBox is considered stale and needs updating.\n\n"
      "Other factors can cause the collision working query box to become invalidated, such as the vehicle moving far "
      "enough outside of this cached box.  The smaller this number, the more times the working list of triangles that are "
      "considered for collision is refreshed.  This has the greatest impact with colliding with high triangle count meshes.\n\n"
      "@note Set to -1 to disable any time-based forced check.\n\n"
	   "@ingroup GameObjects\n");

   Con::addVariable("$vehicle::workingQueryBoxSizeMultiplier",TypeF32,&sWorkingQueryBoxSizeMultiplier, 
      "@brief How much larger the mWorkingQueryBox should be made when updating the working collision list.\n\n"
      "The larger this number the less often the working list will be updated due to motion, but any non-static shape that "
      "moves into the query box will not be noticed.\n\n"
	   "@ingroup GameObjects\n");
}

void Vehicle::initPersistFields()
{
   docsURL;
   addField( "disableMove", TypeBool, Offset(mDisableMove, Vehicle),
      "When this flag is set, the vehicle will ignore throttle changes." );

   Parent::initPersistFields();
}


void Vehicle::mountObject(SceneObject *obj, S32 node, const MatrixF &xfm )
{
   Parent::mountObject( obj, node, xfm );

   // Clear objects off the working list that are from objects mounted to us.
   //  (This applies mostly to players...)
   for ( CollisionWorkingList* itr = mConvex.getWorkingList().wLink.mNext; 
         itr != &mConvex.getWorkingList(); 
         itr = itr->wLink.mNext) 
   {
      if (itr->mConvex->getObject() == obj) 
      {
         CollisionWorkingList* cl = itr;
         itr = itr->wLink.mPrev;
         cl->free();
      }
   }
}

//----------------------------------------------------------------------------

void Vehicle::updateLiftoffDust( F32 dt )
{
   Point3F offset( 0.0, 0.0, mDataBlock->dustHeight );
   emitDust( mDustEmitterList[ 0 ], mDataBlock->triggerDustHeight, offset,
             ( U32 )( dt * 1000 ) );
}

//----------------------------------------------------------------------------

void Vehicle::updateDamageSmoke( F32 dt )
{

   for( S32 j=VehicleData::VC_NUM_DAMAGE_LEVELS-1; j>=0; j-- )
   {
      F32 damagePercent = mDamage / mDataBlock->maxDamage;
      if( damagePercent >= mDataBlock->damageLevelTolerance[j] )
      {
         for( S32 i=0; i<mDataBlock->numDmgEmitterAreas; i++ )
         {
            MatrixF trans = getTransform();
            Point3F offset = mDataBlock->damageEmitterOffset[i];
            trans.mulP( offset );
            Point3F emitterPoint = offset;

            if( pointInWater(offset ) )
            {
               U32 emitterOffset = VehicleData::VC_BUBBLE_EMITTER;
               if( mDamageEmitterList[emitterOffset] )
               {
                  mDamageEmitterList[emitterOffset]->emitParticles( emitterPoint, emitterPoint, Point3F( 0.0, 0.0, 1.0 ), getVelocity(), (U32)( dt * 1000 ) );
               }
            }
            else
            {
               if( mDamageEmitterList[j] )
               {
                  mDamageEmitterList[j]->emitParticles( emitterPoint, emitterPoint, Point3F( 0.0, 0.0, 1.0 ), getVelocity(), (U32)(dt * 1000));
               }
            }
         }
         break;
      }
   }

}


//--------------------------------------------------------------------------
void Vehicle::updateFroth( F32 dt )
{
   // update bubbles
   Point3F moveDir = getVelocity();

   Point3F contactPoint;
   if( !collidingWithWater( contactPoint ) )
   {
      if ( mWakeSound )
         mWakeSound->stop();
      return;
   }

   F32 speed = moveDir.len();
   if( speed < mDataBlock->splashVelEpsilon ) speed = 0.0;

   U32 emitRate = (U32)(speed * mDataBlock->splashFreqMod * dt);

   U32 i;

   if ( mWakeSound )
   {
      if ( !mWakeSound->isPlaying() )
         mWakeSound->play();

      mWakeSound->setTransform( getTransform() );
      mWakeSound->setVelocity( getVelocity() );
   }

   for( i=0; i<VehicleData::VC_NUM_SPLASH_EMITTERS; i++ )
   {
      if( mSplashEmitterList[i] )
      {
         mSplashEmitterList[i]->emitParticles( contactPoint, contactPoint, Point3F( 0.0, 0.0, 1.0 ),
                                               moveDir, emitRate );
      }
   }

}

void Vehicle::prepBatchRender( SceneRenderState *state, S32 mountedImageIndex )
{
   Parent::prepBatchRender( state, mountedImageIndex );

   if ( !gShowBoundingBox )
      return;

   if ( mountedImageIndex != -1 )
   {
      ObjectRenderInst *ri = state->getRenderPass()->allocInst<ObjectRenderInst>();
      ri->renderDelegate.bind( this, &Vehicle::_renderMuzzleVector );
      ri->objectIndex = mountedImageIndex;
      ri->type = RenderPassManager::RIT_Editor;
      state->getRenderPass()->addInst( ri );
      return;
   }

   ObjectRenderInst *ri = state->getRenderPass()->allocInst<ObjectRenderInst>();
   ri->renderDelegate.bind( this, &Vehicle::_renderMassAndContacts );
   ri->type = RenderPassManager::RIT_Editor;
   state->getRenderPass()->addInst( ri );
}

void Vehicle::_renderMassAndContacts( ObjectRenderInst *ri, SceneRenderState *state, BaseMatInstance *overrideMat )
{
   GFXStateBlockDesc desc;
   desc.setBlend(false, GFXBlendSrcAlpha, GFXBlendInvSrcAlpha);
   desc.setZReadWrite(false,true);
   desc.fillMode = GFXFillWireframe;

   // Render the mass center.   
   GFX->getDrawUtil()->drawCube(desc, Point3F(0.1f,0.1f,0.1f),mDataBlock->massCenter, ColorI(255, 255, 255), &mRenderObjToWorld);

   // Now render all the contact points.
   for (S32 i = 0; i < mCollisionList.getCount(); i++)
   {
      const Collision& collision = mCollisionList[i];
      GFX->getDrawUtil()->drawCube(desc, Point3F(0.05f,0.05f,0.05f),collision.point, ColorI(0, 0, 255));
   }

   // Finally render the normals as one big batch.
   PrimBuild::begin(GFXLineList, mCollisionList.getCount() * 2);
   for (S32 i = 0; i < mCollisionList.getCount(); i++)
   {
      const Collision& collision = mCollisionList[i];
      PrimBuild::color3f(1, 1, 1);
      PrimBuild::vertex3fv(collision.point);
      PrimBuild::vertex3fv(collision.point + collision.normal * 0.05f);
   }
   PrimBuild::end();

   // Build and render the collision polylist which is returned
   // in the server's world space.
   ClippedPolyList polyList;
   polyList.mPlaneList.setSize(6);
   polyList.mPlaneList[0].set(getWorldBox().minExtents,VectorF(-1,0,0));
   polyList.mPlaneList[1].set(getWorldBox().minExtents,VectorF(0,-1,0));
   polyList.mPlaneList[2].set(getWorldBox().minExtents,VectorF(0,0,-1));
   polyList.mPlaneList[3].set(getWorldBox().maxExtents,VectorF(1,0,0));
   polyList.mPlaneList[4].set(getWorldBox().maxExtents,VectorF(0,1,0));
   polyList.mPlaneList[5].set(getWorldBox().maxExtents,VectorF(0,0,1));
   Box3F dummyBox;
   SphereF dummySphere;
   buildPolyList(PLC_Collision, &polyList, dummyBox, dummySphere);
   //polyList.render();
}

void Vehicle::_renderMuzzleVector( ObjectRenderInst *ri, SceneRenderState *state, BaseMatInstance *overrideMat )
{
   const U32 index = ri->objectIndex;

   AssertFatal( index > 0 && index < MaxMountedImages, "Vehicle::_renderMuzzleVector() - Bad object index!" );
   AssertFatal( mMountedImageList[index].dataBlock, "Vehicle::_renderMuzzleVector() - Bad object index!" );

	Point3F muzzlePoint, muzzleVector, endpoint;
	getMuzzlePoint(index, &muzzlePoint);
	getMuzzleVector(index, &muzzleVector);
	endpoint = muzzlePoint + muzzleVector * 250;

   if (mSolidSB.isNull())
   {
      GFXStateBlockDesc desc;
      desc.setBlend(false, GFXBlendSrcAlpha, GFXBlendInvSrcAlpha);
      desc.setZReadWrite(false);
      mSolidSB = GFX->createStateBlock(desc);
   }

   GFX->setStateBlock(mSolidSB);

   PrimBuild::begin(GFXLineList, 2);

   PrimBuild::color4f(0, 1, 0, 1);
   PrimBuild::vertex3fv(muzzlePoint);
	PrimBuild::vertex3fv(endpoint);

   PrimBuild::end();
}
