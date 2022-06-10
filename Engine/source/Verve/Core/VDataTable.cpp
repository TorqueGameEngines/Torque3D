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
#include "Verve/Core/VDataTable.h"

#include "console/simObject.h"

//-----------------------------------------------------------------------------

// Implement the DataType enum list.
ImplementEnumType( VDataTableDataType, "" )
    { VDataTable::k_TypeExpression, "EXPRESSION" },
    { VDataTable::k_TypeStatic,     "STATIC"     },
    { VDataTable::k_TypeVariable,   "VARIABLE"   },
EndImplementEnumType;

VDataTable::eDataType VDataTable::getDataTypeEnum( const char *pLabel )
{
    VDataTable::eDataType out;
    if ( !castConsoleTypeFromString( out, pLabel ) )
    {
        // Bah!
        return VDataTable::k_TypeInvalid;
    }

    // Return.
    return out;
}

const char *VDataTable::getDataTypeDescription( const VDataTable::eDataType pEnum )
{
    // Return.
    return castConsoleTypeToString( pEnum );
}

//-----------------------------------------------------------------------------

VDataTable::VDataTable( void )
{
    mDataMap.clear();
}

VDataTable::~VDataTable( void )
{
    mDataMap.clear();
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VDataTable::insert( pType, pFieldName );
// 
// Add a DataTable entry, referencing the field name and assign it the given
// data type.
// 
// For a full list of possible data types, see the 'eDataType' declaration in
// VDataTable.h.
// 
//-----------------------------------------------------------------------------
void VDataTable::insert( eDataType pType, const String &pFieldName )
{
    if ( mDataMap.contains( pFieldName ) )
    {
        // Change Field Type.
        mDataMap.find( pFieldName )->value.Type = pType;

        // Return.
        return;
    }

    // Insert Item.
    mDataMap.insert( pFieldName, sDataItem( pType, pFieldName ) );
}

//-----------------------------------------------------------------------------
// 
// VDataTable::clear( pFieldName );
// 
// Clear the DataTable entry with the given field name.
// 
//-----------------------------------------------------------------------------
void VDataTable::clear( const String &pFieldName )
{
    // Clear Item.
    mDataMap.erase( pFieldName );
}

//-----------------------------------------------------------------------------
// 
// VDataTable::clear();
// 
// Clear the contents of the DataTable entirely.
// 
//-----------------------------------------------------------------------------
void VDataTable::clear( void )
{
    // Clear.
    mDataMap.clear();
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 
// VDataTable::getCount();
// 
// Return the number of DataTable entries.
// 
//-----------------------------------------------------------------------------
S32 VDataTable::getCount( void )
{
    return mDataMap.size();
}

//-----------------------------------------------------------------------------
// 
// VDataTable::getItem( pIndex, *pDataItem );
// 
// Return the item with the given index. This method will return false if there
// is no valid data entry with that index.
// 
//-----------------------------------------------------------------------------
bool VDataTable::getItem( const S32 &pIndex, sDataItem *pDataItem )
{
    if ( pIndex < 0 || pIndex >= mDataMap.size() )
    {
        // Invalid Field.
        return false;
    }

    S32 index = 0;
    for ( VDataMap::Iterator itr = mDataMap.begin(); itr != mDataMap.end(); ++itr )
    {
        if ( index == pIndex )
        {
            if ( pDataItem )
            {
                // Store Reference.
                *pDataItem = ( itr->value );
            }

            // Valid Field.
            return true;
        }

        // Increment.
        ++index;
    }

    // Invalid Field.
    return false;
}

//-----------------------------------------------------------------------------
// 
// VDataTable::getItem( pFieldName, *pDataItem );
// 
// Return the item with the given field name. This method will return false if
// there is no valid data entry with that name.
// 
//-----------------------------------------------------------------------------
bool VDataTable::getItem( const String &pFieldName, sDataItem *pDataItem )
{
    if ( mDataMap.contains( pFieldName ) )
    {
        if ( pDataItem )
        {
            // Fetch Item
            *pDataItem = mDataMap.find( pFieldName )->value;
        }

        // Valid Field.
        return true;
    }

    // Invalid Field.
    return false;
}

//-----------------------------------------------------------------------------
// 
// VDataTable::getValue( pObject, pFieldName, *pValue );
// 
// Evaluate and return the expression provided in the data field.
// 
//-----------------------------------------------------------------------------
bool VDataTable::getValue( SimObject *pObject, const String &pFieldName, String &pValue )
{
    if ( !pObject || pFieldName.isEmpty() )
    {
        // Sanity!
        return false;
    }

    // Fetch Data.
    sDataItem *data = &( mDataMap.find( pFieldName )->value );
    if ( !data )
    {
        // No Field.
        return false;
    }

    // Field Value.
    const char *fieldValue = pObject->getDataField( StringTable->insert( data->FieldName ), NULL );

    switch ( data->Type )
    {
        case VDataTable::k_TypeExpression :
            {
                // Evaluate.
                pValue = Con::evaluate( fieldValue, false ).getString();

            } break;

        case VDataTable::k_TypeStatic :
            {
                // Use Value.    
                pValue = fieldValue;

            } break;

        case VDataTable::k_TypeVariable :
            {

                // Fetch Variable.
                pValue = Con::getVariable( fieldValue );

            } break;
    }

    // Valid Field.
    return true;
}
