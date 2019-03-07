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
#include "Verve/Torque/TLightObject.h"

//-----------------------------------------------------------------------------
//
// Light Object Methods.
//
//-----------------------------------------------------------------------------

bool VTorque::isLightObjectEnabled( LightObjectType *pLightObject )
{
    if ( !pLightObject )
    {
        // Sanity!
        return false;
    }

    // Get Enabled.
    return pLightObject->getLightEnabled();
}

void VTorque::setLightObjectOn( LightObjectType *pLightObject, const bool &pStatus )
{
    if ( !pLightObject )
    {
        // Sanity!
        return;
    }

    // Set Enabled.
    pLightObject->setLightEnabled( pStatus );
}

void VTorque::playAnimation( LightObjectType *pLightObject, LightAnimationDataType *pLightAnimationData )
{
    if ( !pLightObject || !pLightAnimationData )
    {
        // Sanity!
        return;
    }

    // Play Animation.
    pLightObject->playAnimation( pLightAnimationData );
}

void VTorque::playAnimation( LightObjectType *pLightObject )
{
    if ( !pLightObject )
    {
        // Sanity!
        return;
    }

    // Play Animation.
    pLightObject->playAnimation();
}

void VTorque::pauseAnimation( LightObjectType *pLightObject )
{
    if ( !pLightObject )
    {
        // Sanity!
        return;
    }

    // Play Animation.
    pLightObject->pauseAnimation();
}