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
#ifndef _VT_VDATATABLE_H_
#define _VT_VDATATABLE_H_

#ifndef CORE_TDICTIONARY_H
#include "core/util/tDictionary.h"
#endif

#ifndef _CONSOLE_H_
#include "console/console.h"
#endif

#ifndef _DYNAMIC_CONSOLETYPES_H_
#include "console/dynamicTypes.h"
#endif

#ifndef _STRINGTABLE_H_
#include "core/stringTable.h"
#endif

//-----------------------------------------------------------------------------

class VDataTable
{
public:

    enum eDataType
    {
        k_TypeExpression,
        k_TypeStatic,
        k_TypeVariable,

        k_TypeInvalid,
    };

    struct sDataItem
    {
        eDataType    Type;
        String       FieldName;

        sDataItem( void ) :
                Type( k_TypeInvalid ),
                FieldName( String::EmptyString )
        {
            // Void.
        };

        sDataItem( eDataType pType, const String &pFieldName ) :
                Type( pType ),
                FieldName( pFieldName )
        {
            // Void.
        };
    };

    // Enum Lookup.
    static VDataTable::eDataType    getDataTypeEnum( const char *pLabel );
    static const char              *getDataTypeDescription( const VDataTable::eDataType pEnum );

    // Map Type.
    typedef Map<String, sDataItem> VDataMap;

public:

    VDataMap    mDataMap;

public:

    VDataTable( void );
    ~VDataTable( void );

    // Data.

    void        insert( eDataType pType, const String &pFieldName );
    void        clear( const String &pFieldName );
    void        clear( void );

    // Reference.

    S32         getCount( void );
    bool        getItem( const S32 &pIndex, sDataItem *pDataItem = NULL );
    bool        getItem( const String &pFieldName, sDataItem *pDataItem = NULL );

    bool        getValue( SimObject *pObject, const String &pFieldName, String &pValue );
};

//-----------------------------------------------------------------------------

// Define Types.
typedef VDataTable::eDataType VDataTableDataType;

// Declare Enum Types.
DefineEnumType( VDataTableDataType );

//-----------------------------------------------------------------------------

#endif // _VT_VDATATABLE_H_