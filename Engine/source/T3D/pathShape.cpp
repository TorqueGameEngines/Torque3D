//-----------------------------------------------------------------------------
// Torque Game Engine 
// Copyright (C) GarageGames.com, Inc.
// @author Stefan "Beffy" Moises
// this is a modified version of PathCamera that allows to move shapes along paths
//-----------------------------------------------------------------------------

#include "platform/platform.h"
#include "math/mMath.h"
#include "math/mathIO.h"
#include "console/simBase.h"
#include "console/console.h"
#include "console/consoleTypes.h"
#include "core/stream/bitStream.h"
#include "core/dnet.h"
#include "scene/pathManager.h"
#include "T3D/gameFunctions.h"
#include "T3D/gameBase/gameConnection.h"
#include "gui/worldEditor/editor.h"
#include "console/engineAPI.h"
#include "math/mTransform.h"

#include "T3D/pathShape.h"


//----------------------------------------------------------------------------

IMPLEMENT_CO_DATABLOCK_V1(PathShapeData);

void PathShapeData::consoleInit()
{
}


bool PathShapeData::preload(bool server, String &errorStr)
{

   if(!Parent::preload(server, errorStr))
      return false;

	return true;
}


void PathShapeData::initPersistFields()
{
   docsURL;
   Parent::initPersistFields();
}

void PathShapeData::packData(BitStream* stream)
{
   Parent::packData(stream);
}

void PathShapeData::unpackData(BitStream* stream)
{
   Parent::unpackData(stream);
}


//----------------------------------------------------------------------------

IMPLEMENT_CO_NETOBJECT_V1(PathShape);

PathShape::PathShape()
{
   mNetFlags.set(Ghostable|ScopeAlways);
   mTypeMask |= PathShapeObjectType | StaticShapeObjectType;
   delta.time = 0;
   delta.timeVec = 0;
   mDataBlock = NULL;
   mState = Forward;
   mNodeBase = 0;
   mNodeCount = 0;
   mPosition = 0;
   mTarget = 0;
   mTargetSet = false;

   MatrixF mat = MatrixF::Identity;
   mLastXform = MatrixF::Identity;

   Parent::setTransform(mat);
   for (U32 i = 0; i < 4; i++)
   {
      mControl[i] = StringTable->insert("");
   }
}

PathShape::~PathShape()
{
}


//----------------------------------------------------------------------------

bool PathShape::onAdd()
{
   if(!Parent::onAdd() && !mDataBlock)
      return false;

   mTypeMask |= PathShapeObjectType | StaticShapeObjectType;
   // Initialize from the current transform.
   if (!mNodeCount) {
      QuatF rot(getTransform());
      Point3F pos = getPosition();
      mSpline.removeAll();
      mSpline.push_back(new CameraSpline::Knot(pos,rot,1,
         CameraSpline::Knot::NORMAL, CameraSpline::Knot::SPLINE));
      mNodeCount = 1;
   }

   if (isServerObject()) scriptOnAdd();
   return true;

}

void PathShape::onRemove()
{
	scriptOnRemove();
	removeFromScene();

	 unmount();
    Parent::onRemove();

	   if (isGhost())
      for (S32 i = 0; i < MaxSoundThreads; i++)
         stopAudio(i);
}

bool PathShape::onNewDataBlock(GameBaseData* dptr, bool reload)
{
   mDataBlock = dynamic_cast<PathShapeData*>(dptr);
   if (!mDataBlock || !Parent::onNewDataBlock(dptr, reload))
      return false;

   scriptOnNewDataBlock();
   return true;
}

PathShapeData::PathShapeData()
{

}

//----------------------------------------------------------------------------

void PathShape::initPersistFields()
{
   docsURL;

   addField( "Path", TYPEID< SimObjectRef<SimPath::Path> >(), Offset( mSimPath, PathShape ),
         "@brief Name of a Path to follow." );

   addField("Controler", TypeString, Offset(mControl, PathShape), 4, "controlers");

   Parent::initPersistFields();

}

void PathShape::consoleInit()
{
}


//----------------------------------------------------------------------------

void PathShape::processTick(const Move* move)
{
   // client and server
   Parent::processTick(move);
   
   // Move to new time
   advancePosition(TickMs);

	MatrixF mat;
    interpolateMat(mPosition,&mat);
	Parent::setTransform(mat);

	updateContainer();
}

void PathShape::interpolateTick(F32 dt)          
{
   Parent::interpolateTick(dt);
   MatrixF mat;
   interpolateMat(delta.time + (delta.timeVec * dt),&mat);
   Parent::setRenderTransform(mat);
}

void PathShape::interpolateMat(F32 pos,MatrixF* mat)
{
   CameraSpline::Knot knot;
   mSpline.value(pos - mNodeBase,&knot);
   knot.mRotation.setMatrix(mat);
   mat->setPosition(knot.mPosition);
}

void PathShape::advancePosition(S32 ms)
{
   delta.timeVec = mPosition;

   // Advance according to current speed
   if (mState == Forward) {
      mPosition = mSpline.advanceTime(mPosition - mNodeBase,ms);
      if (mPosition > F32(mNodeCount - 1))
         mPosition = F32(mNodeCount - 1);
      mPosition += (F32)mNodeBase;
      if (mTargetSet && mPosition >= mTarget) {
         mTargetSet = false;
         mPosition = mTarget;
         mState = Stop;
      }
   }
   else
      if (mState == Backward) {
         mPosition = mSpline.advanceTime(mPosition - mNodeBase,-ms);
         if (mPosition < 0)
            mPosition = 0;
         mPosition += mNodeBase;
         if (mTargetSet && mPosition <= mTarget) {
            mTargetSet = false;
            mPosition = mTarget;
            mState = Stop;
         }
      }

   // Script callbacks
   if (int(mPosition) != int(delta.timeVec))
      onNode(int(mPosition));

   // Set frame interpolation
   delta.time = mPosition;
   delta.timeVec -= mPosition;
}


//----------------------------------------------------------------------------


void PathShape::setPosition(F32 pos)
{
   mPosition = mClampF(pos,mNodeBase,mNodeBase + mNodeCount - 1);
   MatrixF mat;
   interpolateMat(mPosition,&mat);
   Parent::setTransform(mat);
   setMaskBits(PositionMask);
}

void PathShape::setTarget(F32 pos)
{
   mTarget = pos;
   mTargetSet = true;
   if (mTarget > mPosition)
      mState = Forward;
   else
      if (mTarget < mPosition)
         mState = Backward;
      else {
         mTargetSet = false;
         mState = Stop;
      }
   setMaskBits(TargetMask | StateMask);
}

void PathShape::setState(State s)
{
   mState = s;
   setMaskBits(StateMask);
}

S32 PathShape::getState()
{
   return mState;
}


//-----------------------------------------------------------------------------

void PathShape::reset(F32 speed)
{
   CameraSpline::Knot *knot = new CameraSpline::Knot;
   mSpline.value(mPosition - mNodeBase,knot);
   if (speed)
      knot->mSpeed = speed;
   mSpline.removeAll();
   mSpline.push_back(knot);

   mNodeBase = 0;
   mNodeCount = 1;
   mPosition = 0;
   mTargetSet = false;
   mState = Forward;
   setMaskBits(StateMask | PositionMask | WindowMask | TargetMask);
}

void PathShape::pushBack(CameraSpline::Knot *knot)
{
   // Make room at the end
   if (mNodeCount == NodeWindow) {
      delete mSpline.remove(mSpline.getKnot(0));
      mNodeBase++;
   }
   else
      mNodeCount++;

   // Fill in the new node
   mSpline.push_back(knot);
   setMaskBits(WindowMask);

   // Make sure the position doesn't fall off
   if (mPosition < mNodeBase) {
      mPosition = mNodeBase;
      setMaskBits(PositionMask);
   }
}

void PathShape::pushFront(CameraSpline::Knot *knot)
{
   // Make room at the front
   if (mNodeCount == NodeWindow)
      delete mSpline.remove(mSpline.getKnot(mNodeCount));
   else
      mNodeCount++;
   mNodeBase--;

   // Fill in the new node
   mSpline.push_front(knot);
   setMaskBits(WindowMask);

   // Make sure the position doesn't fall off
   if (mPosition > mNodeBase + (NodeWindow - 1)) {
      mPosition = mNodeBase + (NodeWindow - 1);
      setMaskBits(PositionMask);
   }
}

void PathShape::popFront()
{
   if (mNodeCount < 2)
      return;

   // Remove the first node. Node base and position are unaffected.
   mNodeCount--;
   delete mSpline.remove(mSpline.getKnot(0));
}


//----------------------------------------------------------------------------

void PathShape::onNode(S32 node)
{
   if (!isGhost())
   {
      Con::executef(mDataBlock, "onNode", getIdString(), Con::getIntArg(node));
      Con::executef(mDataBlock, mSpline.getKnot(node)->mHitCommand.c_str(), getIdString());   
   }
}


//----------------------------------------------------------------------------



//----------------------------------------------------------------------------

U32 PathShape::packUpdate(NetConnection *con, U32 mask, BitStream *stream)
{

   Parent::packUpdate(con,mask,stream);

   if (stream->writeFlag(mask & StateMask))
      stream->writeInt(mState,StateBits);

   if (stream->writeFlag(mask & PositionMask))
      stream->write(mPosition);

   if (stream->writeFlag(mask & TargetMask))
      if (stream->writeFlag(mTargetSet))
         stream->write(mTarget);

   if (stream->writeFlag(mask & WindowMask)) {
      stream->write(mNodeBase);
      stream->write(mNodeCount);
      for (S32 i = 0; i < mNodeCount; i++) {
         CameraSpline::Knot *knot = mSpline.getKnot(i);
         mathWrite(*stream, knot->mPosition);
         mathWrite(*stream, knot->mRotation);
         stream->write(knot->mSpeed);
         stream->writeInt(knot->mType, CameraSpline::Knot::NUM_TYPE_BITS);
         stream->writeInt(knot->mPath, CameraSpline::Knot::NUM_PATH_BITS);
      }
   }

   // The rest of the data is part of the control object packet update.
   // If we're controlled by this client, we don't need to send it.
   if(stream->writeFlag(getControllingClient() == con && !(mask & InitialUpdateMask)))
      return 0;

   return 0;   
}

void PathShape::unpackUpdate(NetConnection *con, BitStream *stream)
{
   Parent::unpackUpdate(con,stream);   

   // StateMask
   if (stream->readFlag())
      mState = stream->readInt(StateBits);

   // PositionMask 
   if (stream->readFlag()) {
      stream->read(&mPosition);
      delta.time = mPosition;
      delta.timeVec = 0;
   }
   
   // TargetMask
   if (stream->readFlag()) { 
		mTargetSet = stream->readFlag();
		if (mTargetSet) {
		   stream->read(&mTarget);
		}
	}

   // WindowMask
   if (stream->readFlag()) {
      mSpline.removeAll();
      stream->read(&mNodeBase);
      stream->read(&mNodeCount);
      for (S32 i = 0; i < mNodeCount; i++) {
         CameraSpline::Knot *knot = new CameraSpline::Knot();
         mathRead(*stream, &knot->mPosition);
         mathRead(*stream, &knot->mRotation);
         stream->read(&knot->mSpeed);
         knot->mType = (CameraSpline::Knot::Type)stream->readInt(CameraSpline::Knot::NUM_TYPE_BITS);
         knot->mPath = (CameraSpline::Knot::Path)stream->readInt(CameraSpline::Knot::NUM_PATH_BITS);
         mSpline.push_back(knot);
      }
   }

   // Controlled by the client?
   if (stream->readFlag()) return;
}


//-----------------------------------------------------------------------------
// Console access methods
//-----------------------------------------------------------------------------
DefineEngineMethod(PathShape, setPosition, void, (F32 position), (0.0f), "Set the current position of the camera along the path.\n"
	"@param position Position along the path, from 0.0 (path start) - 1.0 (path end), to place the camera.\n"
	"@tsexample\n"
	"// Set the camera on a position along its path from 0.0 - 1.0.\n"
	"%position = \"0.35\";\n\n"
	"// Force the pathCamera to its new position along the path.\n"
	"%pathCamera.setPosition(%position);\n"
	"@endtsexample\n")
{
	object->setPosition(position);
}

DefineEngineMethod(PathShape, setTarget, void, (F32 position), (1.0f), "@brief Set the movement target for this camera along its path.\n\n"
	"The camera will attempt to move along the path to the given target in the direction provided "
	"by setState() (the default is forwards).  Once the camera moves past this target it will come "
	"to a stop, and the target state will be cleared.\n"
	"@param position Target position, between 0.0 (path start) and 1.0 (path end), for the camera to move to along its path.\n"
	"@tsexample\n"
	"// Set the position target, between 0.0 (path start) and 1.0 (path end), for this camera to move to.\n"
	"%position = \"0.50\";\n\n"
	"// Inform the pathCamera of the new target position it will move to.\n"
	"%pathCamera.setTarget(%position);\n"
	"@endtsexample\n")
{
	object->setTarget(position);
}

DefineEngineMethod(PathShape, setState, void, (const char* newState), ("forward"), "Set the movement state for this path camera.\n"
	"@param newState New movement state type for this camera. Forward, Backward or Stop.\n"
	"@tsexample\n"
	"// Set the state type (forward, backward, stop).\n"
	"// In this example, the camera will travel from the first node\n"
	"// to the last node (or target if given with setTarget())\n"
	"%state = \"forward\";\n\n"
	"// Inform the pathCamera to change its movement state to the defined value.\n"
	"%pathCamera.setState(%state);\n"
	"@endtsexample\n")
{
	if (!dStricmp(newState, "forward"))
		object->setState(PathShape::Forward);
	else
		if (!dStricmp(newState, "backward"))
			object->setState(PathShape::Backward);
		else
			object->setState(PathShape::Stop);
}

DefineEngineMethod(PathShape, reset, void, (F32 speed), (1.0f), "@brief Clear the camera's path and set the camera's current transform as the start of the new path.\n\n"
	"What specifically occurs is a new knot is created from the camera's current transform.  Then the current path "
	"is cleared and the new knot is pushed onto the path.  Any previous target is cleared and the camera's movement "
	"state is set to Forward.  The camera is now ready for a new path to be defined.\n"
	"@param speed Speed for the camera to move along its path after being reset.\n"
	"@tsexample\n"
	"//Determine the new movement speed of this camera. If not set, the speed will default to 1.0.\n"
	"%speed = \"0.50\";\n\n"
	"// Inform the path camera to start a new path at"
	"// the camera's current position, and set the new "
	"// path's speed value.\n"
	"%pathCamera.reset(%speed);\n"
	"@endtsexample\n")
{
	object->reset(speed);
}

static CameraSpline::Knot::Type resolveKnotType(const char *arg)
{
   if (dStricmp(arg, "Position Only") == 0) 
      return CameraSpline::Knot::POSITION_ONLY;
   if (dStricmp(arg, "Kink") == 0) 
      return CameraSpline::Knot::KINK;
   return CameraSpline::Knot::NORMAL;
}

static CameraSpline::Knot::Path resolveKnotPath(const char *arg)
{
   if (!dStricmp(arg, "Linear"))
      return CameraSpline::Knot::LINEAR;
   return CameraSpline::Knot::SPLINE;
}

DefineEngineMethod(PathShape, pushBack, void, (TransformF transform, F32 speed, const char* type, const char* path, const char *hitCommand),
   (TransformF::Identity, 1.0f, "Normal", "Linear",""),
   "@brief Adds a new knot to the back of a path camera's path.\n"
   "@param transform Transform for the new knot.  In the form of \"x y z ax ay az aa\" such as returned by SceneObject::getTransform()\n"
   "@param speed Speed setting for this knot.\n"
   "@param type Knot type (Normal, Position Only, Kink).\n"
   "@param path %Path type (Linear, Spline).\n"
   "@tsexample\n"
   "// Transform vector for new knot. (Pos_X Pos_Y Pos_Z Rot_X Rot_Y Rot_Z Angle)\n"
   "%transform = \"15.0 5.0 5.0 1.4 1.0 0.2 1.0\"\n\n"
   "// Speed setting for knot.\n"
   "%speed = \"1.0\"\n\n"
   "// Knot type. (Normal, Position Only, Kink)\n"
   "%type = \"Normal\";\n\n"
   "// Path Type. (Linear, Spline)\n"
   "%path = \"Linear\";\n\n"
   "// Inform the path camera to add a new knot to the back of its path\n"
   "%pathCamera.pushBack(%transform,%speed,%type,%path);\n"
   "@endtsexample\n")
{
   QuatF rot(transform.getOrientation());

   object->pushBack(new CameraSpline::Knot(transform.getPosition(), rot, speed, resolveKnotType(type), resolveKnotPath(path), String(hitCommand)));
}

DefineEngineMethod(PathShape, pushFront, void, (TransformF transform, F32 speed, const char* type, const char* path),
   (1.0f, "Normal", "Linear"),
   "@brief Adds a new knot to the front of a path camera's path.\n"
   "@param transform Transform for the new knot. In the form of \"x y z ax ay az aa\" such as returned by SceneObject::getTransform()\n"
   "@param speed Speed setting for this knot.\n"
   "@param type Knot type (Normal, Position Only, Kink).\n"
   "@param path %Path type (Linear, Spline).\n"
   "@tsexample\n"
   "// Transform vector for new knot. (Pos_X,Pos_Y,Pos_Z,Rot_X,Rot_Y,Rot_Z,Angle)\n"
   "%transform = \"15.0 5.0 5.0 1.4 1.0 0.2 1.0\"\n\n"
   "// Speed setting for knot.\n"
   "%speed = \"1.0\";\n\n"
   "// Knot type. (Normal, Position Only, Kink)\n"
   "%type = \"Normal\";\n\n"
   "// Path Type. (Linear, Spline)\n"
   "%path = \"Linear\";\n\n"
   "// Inform the path camera to add a new knot to the front of its path\n"
   "%pathCamera.pushFront(%transform, %speed, %type, %path);\n"
   "@endtsexample\n")
{
   QuatF rot(transform.getOrientation());

   object->pushFront(new CameraSpline::Knot(transform.getPosition(), rot, speed, resolveKnotType(type), resolveKnotPath(path)));
}

DefineEngineMethod(PathShape, popFront, void, (), , "Removes the knot at the front of the camera's path.\n"
   "@tsexample\n"
   "// Remove the first knot in the camera's path.\n"
   "%pathCamera.popFront();\n"
   "@endtsexample\n")
{
   object->popFront();
}

DefineEngineMethod(PathShape, getState, S32, (), , "PathShape.getState()")
{
	return object->getState(); 
}
