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
#ifndef _VT_VPERSISTENCE_H_
#define _VT_VPERSISTENCE_H_

#ifndef TINYXML_INCLUDED
#include "tinyxml/tinyxml.h"
#endif

#ifndef _SIMOBJECT_H_
#include "console/simObject.h"
#endif

#ifndef _VT_VOBJECT_H_
#include "Verve/Core/VObject.h"
#endif

//-----------------------------------------------------------------------------

namespace VPersistence
{
    static const char *VSFVersionString = "0.0.0a";

    // This object is used to filter fields which belong to SimObject's.
    // There is no need to serialize these fields, so they are skipped
    // entirely.
    static SimObject DummySimObject;

    //-------------------------------------------------------------------------

    template <class T> bool writeFile( const char* pFileName, T *pObject )
    {
        // Create Doc.
        TiXmlDocument xmlDocument;
        TiXmlDeclaration *xmlDeclaration = new TiXmlDeclaration( "1.0", "", "" );
        xmlDocument.LinkEndChild( xmlDeclaration );

        // Create Root.
        TiXmlElement *xmlRoot = new TiXmlElement( "VerveControllerSequence" );
        xmlDocument.LinkEndChild( xmlRoot );

        // Write Version.
        xmlRoot->SetAttribute( "Version", VSFVersionString );

        // Write Object.
        if ( !write( xmlRoot, pObject ) )
        {
            Con::errorf( "VPersistence::writeFile() - Unable to Write Object." );
            return false;
        }

        // Save File.
        return xmlDocument.SaveFile( pFileName );
    };

    template <class T> bool write( TiXmlElement *pElement, T *pObject );
    
    template <class T> bool writeProperties( TiXmlElement *pElement, T *pObject )
    {
        const AbstractClassRep::FieldList &fieldList = pObject->getFieldList();
        const AbstractClassRep::Field     *field     = NULL;

        // Create Property Root.
        TiXmlElement *propertyRoot = new TiXmlElement( "Properties" );
        pElement->LinkEndChild( propertyRoot );

        const S32 fieldCount = fieldList.size();
        for ( S32 i = 0; i < fieldCount; i++ )
        {
            field = &fieldList[i];
            
            if ( field->type >= AbstractClassRep::ARCFirstCustomField )
            {
                // Ignore Special Fields.
                continue;
            }

            // Fetch the Field Name.
            const char *fieldName = field->pFieldname;
            // SimObject Field?
            if ( DummySimObject.findField( fieldName ) != NULL )
            {
                // Skip SimObject Fields.
                continue;
            }

            // Fetch the Field Value.
            const char *fieldValue = ( *field->getDataFn )( pObject, Con::getData( field->type, ( void * ) ( ( ( const char * )pObject ) + field->offset ), 0, field->table, field->flag ) );

            if ( fieldValue )
            {
                // Create Element.
                TiXmlElement *propertyElement = new TiXmlElement( fieldName );  

                // Apply Value.
                propertyElement->InsertEndChild( TiXmlText( fieldValue ) );

                // Add.
                propertyRoot->LinkEndChild( propertyElement );
            }
        }

        // Valid Write.
        return true;
    };

    template <class T> bool writeObjects( TiXmlElement *pElement, T *pObject )
    {
        for ( ITreeNode *node = pObject->mChildNode; node != NULL; node = node->mSiblingNextNode )
        {
            // Write Group.
            if ( !write( pElement, ( VObject* )node ) )
            {
                // Invalid Write.
                return false;
            }
        }

        // Valid Write.
        return true;
    }

    //-------------------------------------------------------------------------

    template <class T> bool readFile( const char* pFileName, T *pObject )
    {
        TiXmlDocument xmlDocument;
        if ( !xmlDocument.LoadFile( pFileName ) )
        {
            Con::errorf( "VPersistence::readFile() - Unable to load file '%s'.", pFileName );
            return false;
        }

        TiXmlElement *rootElement = xmlDocument.RootElement();
        if ( !rootElement )
        {
            Con::errorf( "VPersistence::readFile() - Invalid Document '%s'.", pFileName );
            return false;
        }

        const char *docVersion = rootElement->Attribute( "Version" );
        if ( !docVersion || dStrcmp( VSFVersionString, docVersion ) != 0 )
        {
            Con::errorf( "VPersistence::readFile() - Invalid file version." );
            return false;
        }

        // Read Object.
        if ( !read( rootElement, pObject ) )
        {
            // Invalid Read.
            return false;
        }

        // Valid.
        return true;
    };

    template <class T> bool read( TiXmlElement *pElement, T *pObject );

    template <class T> bool readProperties( TiXmlElement *pElement, T *pObject )
    {
        TiXmlElement *propertyRoot = pElement->FirstChildElement( "Properties" );
        if ( propertyRoot )
        {
            for ( TiXmlElement *child = propertyRoot->FirstChildElement(); child != NULL; child = child->NextSiblingElement() )
            {
                // Get Field Data.
                const char *fieldName  = child->Value();
                const char *fieldValue = child->GetText();

                if ( !fieldValue )
                {
                    // Clear Value.
                    pObject->setField( fieldName, "" );
                }
                else
                {
                    // Apply Field Value.
                    if ( !pObject->setField( fieldName, fieldValue ) )
                    {
                        // Invalid.
                        Con::warnf( "VPersistence::readProperties() - Invalid property '%s'", fieldName );
                    }
                }
            }
        }
        
        // Valid Read.
        return true;
    };

    template <class T> bool readObjects( TiXmlElement *pElement, T *pObject )
    {
        for ( TiXmlElement *child = pElement->FirstChildElement( "VObject" ); child != NULL; child = child->NextSiblingElement( "VObject" ) )
        {
            // Get Object Type.
            const char *type = child->Attribute( "Type" );
            if ( !type || !AbstractClassRep::findClassRep( type ) )
            {
                // Invalid Type.
                Con::errorf( "VController::readObjects() - Invalid object type specified '%s'.", ( ( type ) ? type : "NULL" ) );

                // Invalid Read.
                return false;
            }

            // Create Object.
            VObject *object = dynamic_cast<VObject*>( ConsoleObject::create( type ) );

#ifdef VT_EDITOR
            // Register SimObject.
            if ( !object->registerObject() )
            {
                // Delete.
                delete object;

                // Invalid Read.
                return false;
            }
#endif

            // Add Reference.
            object->addTo( pObject );

#ifdef VT_EDITOR
            // Valid Method?
            if ( object->isMethod( "onAdd" ) )
            {
                // Callback.
                const char *retValue = Con::executef( object, "onAdd" );
                if ( !dAtob( retValue ) )
                {
                    // Delete.
                    object->deleteObject();

                    // Invalid Read.
                    return false;
                }
            }
#endif

            // Read Object.
            if ( !read( child, object ) )
            {
#ifdef VT_EDITOR
                // Delete.
                object->deleteObject();
#else
                // Delete.
                delete object;
#endif

                // Invalid Read.
                return false;
            }
        }

        // Valid Read.
        return true;
    };
};

//-----------------------------------------------------------------------------

#endif // _VT_VPERSISTENCE_H_