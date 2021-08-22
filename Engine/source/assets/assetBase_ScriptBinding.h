//-----------------------------------------------------------------------------
// Copyright (c) 2013 GarageGames, LLC
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
#include "console/engineAPI.h"
#include "assetBase.h"
#include "assetManager.h"


DefineEngineMethod(AssetBase, refreshAsset, void, (), ,
   "Refresh the asset.\n"
   "@return No return value.\n")
{
    object->refreshAsset();
}

//-----------------------------------------------------------------------------

DefineEngineMethod(AssetBase, getAssetId, String, (), ,
   "Gets the assets' Asset Id.  This is only available if the asset was acquired from the asset manager.\n"
   "@return The assets' Asset Id.\n")
{
    return object->getAssetId();
}

DefineEngineMethod(AssetBase, getAssetDependencyFieldCount, S32, (const char* pFieldName), (""),
   "Gets the number of asset dependencies of a given field name.\n"
   "eg. Would return '2' if you searched for 'myDependencyField'\n"
   "and the asset had myDependencyField0 and myDependencyField1\n"
   "@param fieldName The name of the field to get a count of\n"
   "@return The number of dependency fields matching the search name.\n")
{
   return object->getAssetDependencyFieldCount(pFieldName);
}

DefineEngineMethod(AssetBase, getAssetDependencyField, const char*, (const char* pFieldName, S32 index), ("", 0),
   "Gets an asset dependency field to the asset definition at a given index.\n"
   "@param fieldName The name of the field.\n"
   "@param index The index of the field to look up in the event there are multiple dependency fields. Defaults to 0"
   "@return The assetID assigned to the given dependency field.\n")
{
   return object->getAssetDependencyField(pFieldName, index);
}

DefineEngineMethod(AssetBase, clearAssetDependencyFields, void, (const char* pFieldName), (""),
   "Clears any asset dependency fields matching the name provided.\n"
   "@param fieldName The name of the fields to be cleared")
{
   object->clearAssetDependencyFields(pFieldName);
}

DefineEngineMethod(AssetBase, addAssetDependencyField, void, (const char* pFieldName, const char* pAssetId), ("", ""),
   "Adds an asset dependency field to the asset definition.\n"
   "@param fieldName The name of the field. Will automatically increment the tailing number if the field is used multiple times\n"
   "@param assetId The assetId to be marked as a dependency")
{
   object->addAssetDependencyField(pFieldName, pAssetId);
}

DefineEngineMethod(AssetBase, saveAsset, bool, (), ,
   "Saves the asset definition.\n"
   "@return Whether the save was successful.\n")
{
   return object->saveAsset();
}

DefineEngineMethod(AssetBase, getStatus, S32, (), , "get status")\
{
   return object->getStatus();
}

DefineEngineMethod(AssetBase, getStatusString, const char*, (), ,
   "Returns the load status of the asset.\n"
   "@return What status code the asset had after being loaded.\n")
{
   return object->getAssetErrstrn(object->getStatus());
}
