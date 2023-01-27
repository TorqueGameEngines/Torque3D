//-----------------------------------------------------------------------------
// Verve
// Copyright (C) 2014 - Violent Tulip
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
#ifndef _VT_VCONTROLLER_H_
#define _VT_VCONTROLLER_H_

#ifndef _VT_VERVECONFIG_H_
#include "Verve/VerveConfig.h"
#endif

#ifndef _PLATFORM_H_
#include "platform/platform.h"
#endif

#ifndef _PROCESSLIST_H_
#include "T3D/gameBase/processList.h"
#endif

#ifndef _ITICKABLE_H_
#include "core/iTickable.h"
#endif

#ifndef _VT_VPERSISTENCE_H_
#include "Verve/Core/Persistence/VPersistence.h"
#endif

#ifndef _VT_VTREENODE_H_
#include "Verve/Core/VTreeNode.h"
#endif

#ifndef _VT_VDATATABLE_H_
#include "Verve/Core/VDataTable.h"
#endif

#ifndef _VT_TORQUE_CAMERA_H_
#include "Verve/Torque/TCamera.h"
#endif

//-----------------------------------------------------------------------------
class VObject;

class VTrack;
class VEvent;
class VGroup;

class VDirectorGroup;
class VDirectorTrack;

typedef VectorPtr<VTrack*>        VTrackVector;
typedef VTrackVector::iterator    VTrackIterator;

typedef VectorPtr<VEvent*>        VEventVector;
typedef VEventVector::iterator    VEventIterator;

typedef VectorPtr<VGroup*>        VGroupVector;
typedef VGroupVector::iterator    VGroupIterator;
//-----------------------------------------------------------------------------

class VController : public SimObject,
                    public virtual ITickable,
                    public VTreeNode
{
    typedef SimObject Parent;

public:

    enum eControllerStatus
    {
        k_StatusInit    = BIT( 0 ),

        k_StatusPlaying = BIT( 1 ),
        k_StatusPaused  = BIT( 2 ),
        k_StatusStopped = BIT( 3 ),
    };

    enum eControllerEventType
    {
        k_EventInit,
        k_EventReset,

        k_EventPlay,
        k_EventPause,
        k_EventStop,

        k_EventLoop,
    };

    enum eControllerJumpType
    {
        k_JumpTime,
        k_JumpDelta,

        k_JumpInvalid,
    };

    typedef Signal<void( const S32 &pTime, const S32 &pDelta )> ControllerUpdateSignal;
    typedef Signal<bool( eControllerEventType )> ControllerEventSignal;

private:

    // Data.

    VDataTable                mDataTable;

    // Event Signal.

    ControllerUpdateSignal    mControllerUpdateSignal;
    ControllerEventSignal     mControllerEventSignal;

    // Properties.

    S32                       mStatus;

    S32                       mTime;
    U32                       mLastTime;
    S32                       mDuration;
    F32                       mTimeScale;

    bool                      mLoop;
    bool                      mLoopBackwards;
    S32                       mLoopCount;
    S32                       mLoopIndex;
    S32                       mLoopDelay;
    S32                       mLoopDelayTime;

    eControllerJumpType       mJump;
    S32                       mJumpTime;

    bool                      mResetOnCompletion;

public:

    VController();
    ~VController();

    static  void    initPersistFields();

    // ITickable.

    void            interpolateTick( F32 pDelta ) { };
    void            advanceTime( F32 pDelta ) { };
    void            processTick( void );
    void            onPostTick( void );

    // Controller.

    void            reset( void );
    void            reset( const S32 &pTime );

    void            play( void );
    void            play( const S32 &pTime );

    void            pause( void );
    void            stop( const bool &pReset = true );

    void            jump( void );
    void            jump( const eControllerJumpType &pType, const S32 &pDelta );

    void            updateStatus( const S32 &pStatus );

    // Reference.

    VGroup *getObject( const String &pLabel );
    template <class T> inline bool getObject( const String &pLabel, T *&pObject )
    {
        // Reference Group.
        pObject = dynamic_cast<T*>( getObject( pLabel ) );

        // Valid?
        return ( pObject != NULL );
    }

    bool            getDataValue( const String &pFieldName, String &pValue );
    void            clearData( void );
    void            clearData( const S32 &pIndex );
    void            clearData( const String &pFieldName );

    void            sort( void );

    // Saving.

    bool            writeDataTable( tinyxml2::XMLElement *pElement );

    // Reading.

    bool            readDataTable( tinyxml2::XMLElement *pElement );

    // Console Declaration.

    DECLARE_CONOBJECT( VController );

public:

    inline VDataTable               &getDataTable( void )                   { return mDataTable;                     };

    inline ControllerUpdateSignal   &getControllerUpdateSignal( void )      { return mControllerUpdateSignal;        };
    inline ControllerEventSignal    &getControllerEventSignal( void )       { return mControllerEventSignal;         };
    void                             postEvent( const eControllerEventType &pEvent );

    VDirectorGroup                  *getDirectorGroup( void );
    VDirectorTrack                  *getDirectorTrack( void );

    inline void                      setTime( const S32 &pTime )            { mTime = pTime;                         };
    inline void                      setDuration( const S32 &pDuration )    { mDuration = pDuration;                 };
    void                             setTimeScale( const F32 &pTimeScale );

    inline bool                      isLooping( void )                      { return mLoop;                          };
    inline bool                      isPlaying( void )                      { return ( mStatus & k_StatusPlaying );  };
    inline bool                      isPaused( void )                       { return ( mStatus & k_StatusPaused );   };
    inline bool                      isStopped( void )                      { return ( mStatus & k_StatusStopped );  };
    inline bool                      isPlayingForward( void )               { return ( mTimeScale > 0.f );           };

    inline S32                       getTime( void )                        { return mTime;                          };
    inline S32                       getDuration( void )                    { return mDuration;                      };
    inline F32                       getTimeScale( void )                   { return mTimeScale;                     };
    inline S32                       getLoopDelayTime( void )               { return mLoopDelayTime;                 };

protected:

    static bool     setTime( void *pObject, const char *pArray, const char *pData )      { static_cast<VController*>( pObject )->setTime( dAtoi( pData ) );      return false; };
    static bool     setDuration( void *pObject, const char *pArray, const char *pData )  { static_cast<VController*>( pObject )->setDuration( dAtoi( pData ) );  return false; };
    static bool     setTimeScale( void *pObject, const char *pArray, const char *pData ) { static_cast<VController*>( pObject )->setTimeScale( dAtof( pData ) ); return false; };
};

//-----------------------------------------------------------------------------

#endif // _VT_VCONTROLLER_H_
