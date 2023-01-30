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
#ifndef _VT_VEVENT_H_
#define _VT_VEVENT_H_

#ifndef _VT_VOBJECT_H_
#include "Verve/Core/VObject.h"
#endif

//-----------------------------------------------------------------------------
class VGroup;
class VTrack;
//-----------------------------------------------------------------------------

class VEvent : public VObject
{
    typedef VObject Parent;

protected:

    bool            mIsPlaying;
    bool            mTriggered;

    S32             mTriggerTime;
    S32             mDuration;
    
public:

    VEvent( void );

    static  void    initPersistFields();

    // Controller Methods.

    virtual void    onControllerReset( const S32 &pTime, const bool &pForward );
    virtual bool    onControllerUpdate( const S32 &pTime, const S32 &pDelta );

    // Callback Methods.

    virtual void    onTrigger( const S32 &pTime, const S32 &pDelta );
    virtual void    onUpdate( const S32 &pTime, const S32 &pDelta );
    virtual void    onComplete( const S32 &pTime, const S32 &pDelta );

    // Console Declaration.

    DECLARE_CONOBJECT( VEvent );

public:

    // Property Methods.

    VGroup         *getGroup( void );
    template <class T> inline bool getGroup( T *&pGroup )
    {
        // Reference Group.
        pGroup = dynamic_cast<T*>( getGroup() );
        // Validate.
        return ( pGroup != NULL );
    }

    VTrack         *getTrack( void );
    template <class T> inline bool getTrack( T *&pTrack )
    {
        // Reference Track.
        pTrack = dynamic_cast<T*>( getTrack() );
        // Validate.
        return ( pTrack != NULL );
    }

    VEvent         *getNextEvent( void );
    VEvent         *getPreviousEvent( void );

    inline bool     isPlaying( void )      { return mIsPlaying;   };
    inline S32      getTriggerTime( void ) { return mTriggerTime; };
    inline S32      getDuration( void )    { return mDuration;    };

    virtual S32     getStartTime( void );
    virtual S32     getFinishTime( void );

    virtual void    setTriggerTime( const S32 &pTime );
    virtual void    setDuration( const S32 &pDuration );

    static  bool    setTriggerTime( void *obj, const char *pArray, const char *data ) { static_cast<VEvent*>( obj )->setTriggerTime( dAtoi( data ) ); return false; };
    static  bool    setDuration( void *obj, const char *pArray, const char *data )    { static_cast<VEvent*>( obj )->setDuration( dAtoi( data ) );    return false; };
};

//-----------------------------------------------------------------------------

#endif // _VT_VEVENT_H_