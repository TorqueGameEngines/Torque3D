//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
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

#include "platform/platform.h"
#include "terrain/terrMaterial.h"
#include "console/consoleTypes.h"
#include "gfx/gfxTextureManager.h"
#include "gfx/bitmap/gBitmap.h"
#include "console/typeValidators.h"

#ifdef TORQUE_TOOLS
#include "console/persistenceManager.h"
#endif

#include "T3D/assets/TerrainMaterialAsset.h"

#include <string>


IMPLEMENT_CONOBJECT( TerrainMaterial );

ConsoleDocClass( TerrainMaterial,
	"@brief The TerrainMaterial class orginizes the material settings "
	"for a single terrain material layer.\n\n"

	"@note You should not be creating TerrainMaterials by hand in code. "
	"All TerrainMaterials should be created in the editors, as intended "
	"by the system.\n\n"

	"@tsexample\n"
	"// Created by the Terrain Painter tool in the World Editor\n"
	"new TerrainMaterial()\n"
	"{\n"
	"	internalName = \"grass1\";\n"
	"	diffuseMap = \"art/terrains/Test/grass1\";\n"
	"	detailMap = \"art/terrains/Test/grass1_d\";\n"
	"	detailSize = \"10\";\n"
	"	isManaged = \"1\";\n"
	"	detailBrightness = \"1\";\n"
	"	Enabled = \"1\";\n"
	"	diffuseSize = \"200\";\n"
	"};\n"
	"@endtsexample\n\n"

	"@see Materials\n"

	"@ingroup enviroMisc\n");

TerrainMaterial::TerrainMaterial()
   :  mDiffuseSize( 500.0f ),
      mDetailSize( 5.0f ),
      mDetailStrength( 1.0f ),
      mDetailDistance( 50.0f ),
      mSideProjection( false ),
      mMacroSize( 200.0f ),
      mMacroStrength( 0.7f ),
      mMacroDistance( 500.0f ),
      mParallaxScale( 0.0f ),
      mBlendDepth( 0.0f ),
      mBlendContrast( 1.0f ),
      mBlendHardness( 0.0f ),
      mIsSRGB(false),
      mInvertRoughness(false)
{
   INIT_ASSET(DiffuseMap);
   INIT_ASSET(NormalMap);
   INIT_ASSET(DetailMap);
   INIT_ASSET(ORMConfigMap);
   INIT_ASSET(MacroMap);
}

TerrainMaterial::~TerrainMaterial()
{
}

FRangeValidator hardnessValidator(0.0f, 0.999f);

void TerrainMaterial::initPersistFields()
{
   docsURL;
   INITPERSISTFIELD_IMAGEASSET(DiffuseMap, TerrainMaterial,"Base Albedo stretched over the whole map");
   addField( "diffuseSize", TypeF32, Offset( mDiffuseSize, TerrainMaterial ), "Used to scale the diffuse map to the material square" );

   INITPERSISTFIELD_IMAGEASSET(NormalMap, TerrainMaterial,"NormalMap");
   addField( "parallaxScale", TypeF32, Offset( mParallaxScale, TerrainMaterial ), "Used to scale the height from the normal map to give some self "
	   "occlusion effect (aka parallax) to the terrain material" );

   addField("blendHeightBase", TypeF32, Offset(mBlendDepth, TerrainMaterial), "A fixed value to add while blending using heightmap-based blending."
      "Higher numbers = larger blend radius.");

   addField("blendHeightContrast", TypeF32, Offset(mBlendContrast, TerrainMaterial), "A fixed value to add while blending using heightmap-based blending."
      "Higher numbers = larger blend radius.");

   addFieldV("blendHeightHardness", TypeF32, Offset(mBlendHardness, TerrainMaterial), &hardnessValidator, "How sharply this layer blends with other textures."
      "0->1, soft->hard.");

   INITPERSISTFIELD_IMAGEASSET(DetailMap, TerrainMaterial, "Raises and lowers the RGB result of the Base Albedo up close.");
   addField( "detailSize", TypeF32, Offset( mDetailSize, TerrainMaterial ), "Used to scale the detail map to the material square" );
   addField( "detailStrength", TypeF32, Offset( mDetailStrength, TerrainMaterial ), "Exponentially sharpens or lightens the detail map rendering on the material" );
   addField( "detailDistance", TypeF32, Offset( mDetailDistance, TerrainMaterial ), "Changes how far camera can see the detail map rendering on the material" );

   addField( "useSideProjection", TypeBool, Offset( mSideProjection, TerrainMaterial ),"Makes that terrain material project along the sides of steep "
	   "slopes instead of projected downwards");

   INITPERSISTFIELD_IMAGEASSET(ORMConfigMap, TerrainMaterial, "AO|Roughness|metalness map (uses DetailMap UV Coords)");
   addField("isSRGB", TypeBool, Offset(mIsSRGB, TerrainMaterial), "Is the PBR Config map's image in sRGB format?");
   addField("invertRoughness", TypeBool, Offset(mInvertRoughness, TerrainMaterial), "Should the roughness channel of the PBR Config map be inverted?");

   //Macro maps additions
   INITPERSISTFIELD_IMAGEASSET(MacroMap, TerrainMaterial, "Raises and lowers the RGB result of the Base Albedo at a distance.");
   addField( "macroSize", TypeF32, Offset( mMacroSize, TerrainMaterial ), "Used to scale the Macro map to the material square" );
   addField( "macroStrength", TypeF32, Offset( mMacroStrength, TerrainMaterial ), "Exponentially sharpens or lightens the Macro map rendering on the material" );
   addField( "macroDistance", TypeF32, Offset( mMacroDistance, TerrainMaterial ), "Changes how far camera can see the Macro map rendering on the material" );

   Parent::initPersistFields();

   // Gotta call this at least once or it won't get created!
   Sim::getTerrainMaterialSet();
}

bool TerrainMaterial::onAdd()
{
   if ( !Parent::onAdd() )
      return false;

   SimSet *set = Sim::getTerrainMaterialSet();

   // Make sure we have an internal name set.
   if (!mInternalName || !mInternalName[0])
   {
      Con::warnf("TerrainMaterial::onAdd() - No internal name set!");
      return false;
   }
   else
   {
      SimObject *object = set->findObjectByInternalName( mInternalName );
      if (object)
      {
         Con::warnf("TerrainMaterial::onAdd() - Internal name collision; '%s' already exists!", mInternalName);
         return false;
      }
   }  

   set->addObject( this );

   return true;
}

TerrainMaterial* TerrainMaterial::getWarningMaterial()
{ 
   return findOrCreate( NULL );
}

TerrainMaterial* TerrainMaterial::findOrCreate( const char *nameOrPath )
{
   SimSet *set = Sim::getTerrainMaterialSet();
   
   if ( !nameOrPath || !nameOrPath[0] )
      nameOrPath = "warning_material";

   // See if we can just find it.
   TerrainMaterial *mat = dynamic_cast<TerrainMaterial*>( set->findObjectByInternalName( StringTable->insert( nameOrPath ) ) );
   if ( mat )
      return mat;

   StringTableEntry assetId = TerrainMaterialAsset::getAssetIdByMaterialName(nameOrPath);
   if (assetId != StringTable->EmptyString())
   {
      TerrainMaterialAsset* terrMatAsset = AssetDatabase.acquireAsset<TerrainMaterialAsset>(assetId);
      if (terrMatAsset)
      {
         mat = terrMatAsset->getMaterialDefinition();
         if (mat)
            return mat;
      }
   }

   // We didn't find it... so see if its a path to a
   // file.  If it is lets assume its the texture.
   if ( GBitmap::sFindFiles( nameOrPath, NULL ) )
   {
      mat = new TerrainMaterial();
      mat->setInternalName( nameOrPath );
      mat->_setDiffuseMap(nameOrPath);
      mat->registerObject();
      Sim::getRootGroup()->addObject( mat );
      return mat;
   }

   // Ok... return a placeholder material then.
   mat = new TerrainMaterial();
   mat->setInternalName(nameOrPath);
   mat->_setDiffuseMap(GFXTextureManager::getWarningTexturePath());
   mat->mDiffuseSize = 500;
   mat->_setDetailMap(StringTable->EmptyString());
   mat->mDetailSize = 5;
   mat->_setMacroMap(StringTable->EmptyString());
   mat->mMacroSize = 200;
   mat->registerObject();
      
   Sim::getRootGroup()->addObject(mat);

   return mat;
}

//declare general get<entry>, get<entry>Asset and set<entry> methods
//signatures are:
//using DiffuseMap as an example
//material.getDiffuseMap(); //returns the raw file referenced
//material.getDiffuseMapAsset(); //returns the asset id
//material.setDiffuseMap(%texture); //tries to set the asset and failing that attempts a flat file reference
DEF_ASSET_BINDS(TerrainMaterial, DiffuseMap);
DEF_ASSET_BINDS(TerrainMaterial, NormalMap);
DEF_ASSET_BINDS(TerrainMaterial, DetailMap);
DEF_ASSET_BINDS(TerrainMaterial, ORMConfigMap);
DEF_ASSET_BINDS(TerrainMaterial, MacroMap);
