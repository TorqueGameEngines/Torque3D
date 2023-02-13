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
#include "Verve/Core/Persistence/VPersistence.h"

#include "Verve/Core/VController.h"
#include "Verve/Core/VObject.h"

namespace VPersistence
{
    //-----------------------------------------------------------------------------
    //
    // VController
    //
    //-----------------------------------------------------------------------------

    template <>
    bool write( tinyxml2::XMLElement *pElement, VController *pObject )
    {
        // Write Properties.
        if ( !writeProperties( pElement, pObject ) )
        {
            return false;
        }

        // Write Data Table.
        if ( !pObject->writeDataTable( pElement ) )
        {
            return false;
        }

        // Write Objects.
        return writeObjects( pElement, pObject );
    }

    template <>
    bool read( tinyxml2::XMLElement *pElement, VController *pObject )
    {
        // Read Properties.
        if ( !readProperties( pElement, pObject ) )
        {
            // Invalid Properties.
            return false;
        }

        // Read Data Table.
        if ( !pObject->readDataTable( pElement ) )
        {
            // Invalid Data Table.
            return false;
        }

        // Read Objects.
        if ( !readObjects( pElement, pObject ) )
        {
            // Invalid Read.
            return false;
        }

        // Valid Read.
        return true;
    }

    //-----------------------------------------------------------------------------
    //
    // VObject
    //
    //-----------------------------------------------------------------------------

    template <>
    bool write( tinyxml2::XMLElement *pElement, VObject *pObject )
    {
        // Create Element.
        tinyxml2::XMLElement *objectElement = pElement->GetDocument()->NewElement( "VObject" );
        pElement->LinkEndChild( objectElement );

        // Attributes.
        objectElement->SetAttribute( "Type", pObject->getClassName() );

        // Write Properties.
        if ( !writeProperties( objectElement, pObject ) )
        {
            return false;
        }

        // Write Objects.
        return writeObjects( objectElement, pObject );
    }

    template <>
    bool read( tinyxml2::XMLElement *pElement, VObject *pObject )
    {
        // Read Properties.
        if ( !readProperties( pElement, pObject ) )
        {
            // Invalid Properties.
            return false;
        }

        // Set Name Unique.
        pObject->setLabelUnique( pObject->getLabel() );

        // Read Objects.
        if ( !readObjects( pElement, pObject ) )
        {
            // Invalid Objects.
            return false;
        }

#ifdef VT_EDITOR
        // Callback.
        Con::executef( pObject, "onRead" );
#endif

        // Valid Read.
        return true;
    }
}
