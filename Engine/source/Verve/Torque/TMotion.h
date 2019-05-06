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
#ifndef _VT_TORQUE_MOTION_H_
#define _VT_TORQUE_MOTION_H_

#ifndef _VT_TORQUE_SCENEOBJECT_H_
#include "Verve/Torque/TSceneObject.h"
#endif

#ifndef _VT_VPATH_H_
#include "Verve/VPath/VPath.h"
#endif

namespace VTorque
{
    typedef VPath   PathObjectType;

    bool            isMovable( SimObject *pObject );
    bool            isPath( SimObject *pObject );
    bool            isPathObjectAttached( PathObjectType *pPath, SceneObjectType *pObject );

    F32             getPathNodeLength( PathObjectType *pPath, const S32 &pNode );

    void            attachPathObject( PathObjectType *pPath, SceneObjectType *pObject, const bool &pForward, const bool &pRelative, const S32 &pStartNodeIndex, const S32 &pEndNodeIndex, const String &pOrientation, const String &pOrientationData );
    void            detachPathObject( PathObjectType *pPath, SceneObjectType *pObject );

    void            setPathObjectActive( PathObjectType *pPath, SceneObjectType *pObject, const bool &pActive );
    void            setPathObjectInterp( PathObjectType *pPath, SceneObjectType *pObject, const F32 &pInterp );
    void            setPathObjectOffset( PathObjectType *pPath, SceneObjectType *pObject, const Point3F &pOffset );
    void            setPathObjectSpeed( PathObjectType *pPath, SceneObjectType *pObject, const F32 &pSpeed );
    void            setPathObjectOrientation( PathObjectType *pPath, SceneObjectType *pObject, const String &pOrientation, const String &pOrientationData = String::EmptyString );
    void            setPathObjectForward( PathObjectType *pPath, SceneObjectType *pObject, const bool &pForward );
    void            setPathObjectNode( PathObjectType *pPath, SceneObjectType *pObject, const S32 &pNode );
    void            setPathObjectEndNode( PathObjectType *pPath, SceneObjectType *pObject, const S32 &pNode );
};

#endif // _VT_TORQUE_MOTION_H_