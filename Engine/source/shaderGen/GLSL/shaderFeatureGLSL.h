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
#ifndef _SHADERGEN_GLSL_SHADERFEATUREGLSL_H_
#define _SHADERGEN_GLSL_SHADERFEATUREGLSL_H_

#ifndef _SHADERFEATURE_H_
   #include "shaderGen/shaderFeature.h"
#endif

struct LangElement;
struct MaterialFeatureData;
struct RenderPassData;


class ShaderFeatureGLSL : public ShaderFeature
{
public:
   ShaderFeatureGLSL();

   ///
   Var* getOutTexCoord( const char *name,
                        const char *type,
                        bool useTexAnim,
                        MultiLine *meta,
                        Vector<ShaderComponent*> &componentList );

   /// Returns an input texture coord by name adding it
   /// to the input connector if it doesn't exist.
   static Var* getInTexCoord( const char *name,
                              const char *type,
                              Vector<ShaderComponent*> &componentList );

   static Var* getInColor( const char *name,
                           const char *type,
                           Vector<ShaderComponent*> &componentList );

   ///
   static Var* addOutVpos( MultiLine *meta,
                           Vector<ShaderComponent*> &componentList );

   /// Returns the VPOS input register for the pixel shader.
   static Var* getInVpos(  MultiLine *meta,
                           Vector<ShaderComponent*> &componentList );

   /// Returns the "objToTangentSpace" transform or creates one if this
   /// is the first feature to need it.
   Var* getOutObjToTangentSpace( Vector<ShaderComponent*> &componentList,
                                 MultiLine *meta,
                                 const MaterialFeatureData &fd );

   /// Returns the existing output "outWorldToTangent" transform or 
   /// creates one if this is the first feature to need it.
   Var* getOutWorldToTangent( Vector<ShaderComponent*> &componentList,
                              MultiLine *meta,
                              const MaterialFeatureData &fd );

   /// Returns the input "worldToTanget" space transform 
   /// adding it to the input connector if it doesn't exist.
   static Var* getInWorldToTangent( Vector<ShaderComponent*> &componentList );
   
   /// Returns the existing output "outViewToTangent" transform or 
   /// creates one if this is the first feature to need it.
   Var* getOutViewToTangent( Vector<ShaderComponent*> &componentList,
      MultiLine *meta,
      const MaterialFeatureData &fd );

   /// Returns the input "viewToTangent" space transform 
   /// adding it to the input connector if it doesn't exist.
   static Var* getInViewToTangent( Vector<ShaderComponent*> &componentList );
	
	/// Calculates the world space position in the vertex shader and 
   /// assigns it to the passed language element.  It does not pass 
   /// it across the connector to the pixel shader.
   /// @see addOutWsPosition
   void getWsPosition(  Vector<ShaderComponent*> &componentList,                
							 bool useInstancing,
							 MultiLine *meta,
							 LangElement *wsPosition );
	
   /// Adds the "wsPosition" to the input connector if it doesn't exist.
   Var* addOutWsPosition(  Vector<ShaderComponent*> &componentList,             
								 bool useInstancing,
								 MultiLine *meta );
	
   /// Returns the input world space position from the connector.
   static Var* getInWsPosition( Vector<ShaderComponent*> &componentList );
	
   /// Returns the world space view vector from the wsPosition.
   static Var* getWsView( Var *wsPosition, MultiLine *meta );
	
   /// Returns the input normal map texture.
   static Var* getNormalMapTex();
	
   ///
   Var* addOutDetailTexCoord( Vector<ShaderComponent*> &componentList, 
									  MultiLine *meta,
									  bool useTexAnim,
                             bool useFoliageTexCoord);

	///
	Var* getObjTrans( Vector<ShaderComponent*> &componentList,                                       
						  bool useInstancing,
						  MultiLine *meta );
	
	///
   Var* getModelView( Vector<ShaderComponent*> &componentList,                                       
							bool useInstancing,
							MultiLine *meta );
	
   ///
   Var* getWorldView( Vector<ShaderComponent*> &componentList,                
							bool useInstancing,
							MultiLine *meta );
	
   ///
   Var* getInvWorldView( Vector<ShaderComponent*> &componentList,                                       
								bool useInstancing,
								MultiLine *meta );

   Var* getSurface(Vector<ShaderComponent*>& componentList, MultiLine* meta, const MaterialFeatureData& fd);
   Var* getInWorldNormal(Vector<ShaderComponent*>& componentList);
		
   // ShaderFeature
   Var* getVertTexCoord( const String &name ) override;
   LangElement* setupTexSpaceMat(  Vector<ShaderComponent*> &componentList, Var **texSpaceMat ) override;
   LangElement* assignColor( LangElement *elem, Material::BlendOp blend, LangElement *lerpElem = NULL, ShaderFeature::OutputTarget outputTarget = ShaderFeature::DefaultTarget ) override;
   LangElement* expandNormalMap( LangElement *sampleNormalOp, LangElement *normalDecl, LangElement *normalVar, const MaterialFeatureData &fd ) override;
};


class NamedFeatureGLSL : public ShaderFeatureGLSL
{
protected:
   String mName;

public:
   NamedFeatureGLSL( const String &name )
      : mName( name )
   {}

   String getName() override { return mName; }
};

class RenderTargetZeroGLSL : public ShaderFeatureGLSL
{
protected:
   ShaderFeature::OutputTarget mOutputTargetMask;
   String mFeatureName;
	
public:
   RenderTargetZeroGLSL( const ShaderFeature::OutputTarget target )
	: mOutputTargetMask( target )
   {
      char buffer[256];
      dSprintf(buffer, sizeof(buffer), "Render Target Output = 0.0, output mask %04b", mOutputTargetMask);
      mFeatureName = buffer;
   }
	
   String getName() override { return mFeatureName; }
	
   void processPix( Vector<ShaderComponent*> &componentList, 
									const MaterialFeatureData &fd ) override;
   
   U32 getOutputTargets( const MaterialFeatureData &fd ) const override { return mOutputTargetMask; }
};


/// Vertex position
class VertPositionGLSL : public ShaderFeatureGLSL
{
public:
   void processVert( Vector<ShaderComponent*> &componentList,
                             const MaterialFeatureData &fd ) override;
                             
   String getName() override
   {
      return "Vert Position";
   }

   void determineFeature(   Material *material,
                                    const GFXVertexFormat *vertexFormat,
                                    U32 stageNum,
                                    const FeatureType &type,
                                    const FeatureSet &features,
                                    MaterialFeatureData *outFeatureData ) override;

};


/// Vertex lighting based on the normal and the light 
/// direction passed through the vertex color.
class RTLightingFeatGLSL : public ShaderFeatureGLSL
{
protected:

   ShaderIncludeDependency mDep;

public:

   RTLightingFeatGLSL();

   void processVert( Vector<ShaderComponent*> &componentList,
                             const MaterialFeatureData &fd ) override;

   void processPix( Vector<ShaderComponent*> &componentList, 
                            const MaterialFeatureData &fd ) override;

   Material::BlendOp getBlendOp() override{ return Material::None; }
   
   Resources getResources( const MaterialFeatureData &fd ) override;

   String getName() override
   {
      return "RT Lighting";
   }
};


/// Base texture
class DiffuseMapFeatGLSL : public ShaderFeatureGLSL
{

protected:

	ShaderIncludeDependency mTorqueDep;
public:
	DiffuseMapFeatGLSL();
   void processVert( Vector<ShaderComponent*> &componentList,
                             const MaterialFeatureData &fd ) override;

   void processPix( Vector<ShaderComponent*> &componentList, 
                            const MaterialFeatureData &fd ) override;

   U32 getOutputTargets(const MaterialFeatureData &fd) const override;

   Material::BlendOp getBlendOp() override{ return Material::LerpAlpha; }

   Resources getResources( const MaterialFeatureData &fd ) override;

   // Sets textures and texture flags for current pass
   void setTexData( Material::StageData &stageDat,
                            const MaterialFeatureData &fd,
                            RenderPassData &passData,
                            U32 &texIndex ) override;
                            
   String getName() override
   {
      return "Base Texture";
   }
};


/// Overlay texture
class OverlayTexFeatGLSL : public ShaderFeatureGLSL
{
public:
   void processVert( Vector<ShaderComponent*> &componentList,
                             const MaterialFeatureData &fd ) override;

   void processPix( Vector<ShaderComponent*> &componentList, 
                            const MaterialFeatureData &fd ) override;

   Material::BlendOp getBlendOp() override{ return Material::LerpAlpha; }

   Resources getResources( const MaterialFeatureData &fd ) override;

   // Sets textures and texture flags for current pass
   void setTexData( Material::StageData &stageDat,
                            const MaterialFeatureData &fd,
                            RenderPassData &passData,
                            U32 &texIndex ) override;

   String getName() override
   {
      return "Overlay Texture";
   }
};


/// Diffuse color
class DiffuseFeatureGLSL : public ShaderFeatureGLSL
{
public:   
   void processPix(   Vector<ShaderComponent*> &componentList, 
                              const MaterialFeatureData &fd ) override;

   Material::BlendOp getBlendOp() override{ return Material::None; }

   U32 getOutputTargets(const MaterialFeatureData &fd) const override;

   String getName() override
   {
      return "Diffuse Color";
   }
};

/// Diffuse vertex color
class DiffuseVertColorFeatureGLSL : public ShaderFeatureGLSL
{
public:   

   void processVert(  Vector< ShaderComponent* >& componentList,
                              const MaterialFeatureData& fd ) override;
   void processPix(   Vector< ShaderComponent* >&componentList, 
                              const MaterialFeatureData& fd ) override;

   Material::BlendOp getBlendOp() override{ return Material::None; }

   String getName() override
   {
      return "Diffuse Vertex Color";
   }
};

/// Lightmap
class LightmapFeatGLSL : public ShaderFeatureGLSL
{
public:
   void processVert(  Vector<ShaderComponent*> &componentList,
                              const MaterialFeatureData &fd ) override;

   void processPix(   Vector<ShaderComponent*> &componentList, 
                              const MaterialFeatureData &fd ) override;

   Material::BlendOp getBlendOp() override{ return Material::LerpAlpha; }

   Resources getResources( const MaterialFeatureData &fd ) override;

   // Sets textures and texture flags for current pass
   void setTexData( Material::StageData &stageDat,
                            const MaterialFeatureData &fd,
                            RenderPassData &passData,
                            U32 &texIndex ) override;
                            
   String getName() override
   {
      return "Lightmap";
   }
   
   U32 getOutputTargets( const MaterialFeatureData &fd ) const override;
};


/// Tonemap
class TonemapFeatGLSL : public ShaderFeatureGLSL
{
public:
   void processVert(  Vector<ShaderComponent*> &componentList,
                              const MaterialFeatureData &fd ) override;

   void processPix(   Vector<ShaderComponent*> &componentList, 
                              const MaterialFeatureData &fd ) override;

   Material::BlendOp getBlendOp() override{ return Material::LerpAlpha; }

   Resources getResources( const MaterialFeatureData &fd ) override;

   // Sets textures and texture flags for current pass
   void setTexData( Material::StageData &stageDat,
                            const MaterialFeatureData &fd,
                            RenderPassData &passData,
                            U32 &texIndex ) override;
                            
   String getName() override
   {
      return "Tonemap";
   }
   
   U32 getOutputTargets( const MaterialFeatureData &fd ) const override;
};


/// Baked lighting stored on the vertex color
class VertLitGLSL : public ShaderFeatureGLSL
{
public:
   void processVert( Vector<ShaderComponent*> &componentList,
                             const MaterialFeatureData &fd ) override;

   void processPix( Vector<ShaderComponent*> &componentList, 
                            const MaterialFeatureData &fd ) override;

   Material::BlendOp getBlendOp() override{ return Material::None; }
   
   String getName() override
   {
      return "Vert Lit";
   }
   
   U32 getOutputTargets( const MaterialFeatureData &fd ) const override;
};


/// Detail map
class DetailFeatGLSL : public ShaderFeatureGLSL
{
public:
   void processVert( Vector<ShaderComponent*> &componentList,
                             const MaterialFeatureData &fd ) override;

   void processPix( Vector<ShaderComponent*> &componentList, 
                            const MaterialFeatureData &fd ) override;

   Resources getResources( const MaterialFeatureData &fd ) override;

   Material::BlendOp getBlendOp() override{ return Material::Mul; }

   // Sets textures and texture flags for current pass
   void setTexData( Material::StageData &stageDat,
                            const MaterialFeatureData &fd,
                            RenderPassData &passData,
                            U32 &texIndex ) override;

   String getName() override
   {
      return "Detail";
   }
};


/// Reflect Cubemap
class ReflectCubeFeatGLSL : public ShaderFeatureGLSL
{
public:
   void processVert( Vector<ShaderComponent*> &componentList,
                             const MaterialFeatureData &fd ) override;

   void processPix( Vector<ShaderComponent*> &componentList, 
                            const MaterialFeatureData &fd ) override;

   Resources getResources( const MaterialFeatureData &fd ) override;

   // Sets textures and texture flags for current pass
   void setTexData( Material::StageData &stageDat,
                            const MaterialFeatureData &fd,
                            RenderPassData &passData,
                            U32 &texIndex ) override;

   String getName() override
   {
      return "Reflect Cube";
   }
};


/// Fog
class FogFeatGLSL : public ShaderFeatureGLSL
{
protected:

   ShaderIncludeDependency mFogDep;

public:
   FogFeatGLSL();

   void processVert( Vector<ShaderComponent*> &componentList,
                             const MaterialFeatureData &fd ) override;

   void processPix( Vector<ShaderComponent*> &componentList, 
                            const MaterialFeatureData &fd ) override;

   Resources getResources( const MaterialFeatureData &fd ) override;

   Material::BlendOp getBlendOp() override { return Material::LerpAlpha; }

   String getName() override
   {
      return "Fog";
   }
};


/// Tex Anim
class TexAnimGLSL : public ShaderFeatureGLSL
{
public:
   Material::BlendOp getBlendOp() override { return Material::None; }

   String getName() override
   {
      return "Texture Animation";
   }
};


/// Visibility
class VisibilityFeatGLSL : public ShaderFeatureGLSL
{
protected:

   ShaderIncludeDependency mTorqueDep;

public:

   VisibilityFeatGLSL();

   void processVert( Vector<ShaderComponent*> &componentList,
                             const MaterialFeatureData &fd ) override;

   void processPix( Vector<ShaderComponent*> &componentList, 
                            const MaterialFeatureData &fd ) override;

   Resources getResources( const MaterialFeatureData &fd ) override;

   Material::BlendOp getBlendOp() override { return Material::None; }

   String getName() override
   {
      return "Visibility";
   }
};


///
class AlphaTestGLSL : public ShaderFeatureGLSL
{
public:
   void processPix(   Vector<ShaderComponent*> &componentList, 
                              const MaterialFeatureData &fd ) override;

   Material::BlendOp getBlendOp() override { return Material::None; }

   String getName() override
   {
      return "Alpha Test";
   }
};


/// Special feature used to mask out the RGB color for
/// non-glow passes of glow materials.
/// @see RenderGlowMgr
class GlowMaskGLSL : public ShaderFeatureGLSL
{
public:
   void processPix(   Vector<ShaderComponent*> &componentList, 
                              const MaterialFeatureData &fd ) override;

   Material::BlendOp getBlendOp() override { return Material::None; }

   String getName() override
   {
      return "Glow Mask";
   }
};

/// This should be the final feature on most pixel shaders which
/// encodes the color for the current HDR target format.
/// @see HDRPostFx
/// @see LightManager
/// @see torque.glsl
class HDROutGLSL : public ShaderFeatureGLSL
{
protected:
	
   ShaderIncludeDependency mTorqueDep;
	
public:
	
   HDROutGLSL();
	
   void processPix(   Vector<ShaderComponent*> &componentList, 
									const MaterialFeatureData &fd ) override;
	
   Material::BlendOp getBlendOp() override { return Material::None; }
	
   String getName() override { return "HDR Output"; }
};

///
class FoliageFeatureGLSL : public ShaderFeatureGLSL
{
protected:
	
   ShaderIncludeDependency mDep;
	
public:
	
   FoliageFeatureGLSL();
	
   void processVert( Vector<ShaderComponent*> &componentList,
									 const MaterialFeatureData &fd ) override;

   void processPix( Vector<ShaderComponent*> &componentList,
                           const MaterialFeatureData &fd ) override;   
	
   String getName() override
   {
      return "Foliage Feature";
   }
	
   void determineFeature( Material *material, 
											const GFXVertexFormat *vertexFormat,
											U32 stageNum,
											const FeatureType &type,
											const FeatureSet &features,
											MaterialFeatureData *outFeatureData ) override;

   ShaderFeatureConstHandles* createConstHandles( GFXShader *shader, SimObject *userObject ) override;   
};

class ParticleNormalFeatureGLSL : public ShaderFeatureGLSL
{
public:
	
   void processVert( Vector<ShaderComponent*> &componentList,
									 const MaterialFeatureData &fd ) override;
	
   String getName() override
   {
      return "Particle Normal Generation Feature";
   }
	
};


/// Special feature for unpacking imposter verts.
/// @see RenderImposterMgr
class ImposterVertFeatureGLSL : public ShaderFeatureGLSL
{
protected:
	
   ShaderIncludeDependency mDep;
	
public:

   ImposterVertFeatureGLSL();

	void processVert(  Vector<ShaderComponent*> &componentList,
									 const MaterialFeatureData &fd ) override;

	void processPix(  Vector<ShaderComponent*> &componentList,
									const MaterialFeatureData &fd ) override;
	
   String getName() override { return "Imposter Vert"; }
	
   void determineFeature( Material *material, 
											const GFXVertexFormat *vertexFormat,
											U32 stageNum,
											const FeatureType &type,
											const FeatureSet &features,
											MaterialFeatureData *outFeatureData ) override;
};

/// Hardware Skinning
class HardwareSkinningFeatureGLSL : public ShaderFeatureGLSL
{
protected:

public:

   void processVert(Vector<ShaderComponent*> &componentList,
      const MaterialFeatureData &fd) override;

   String getName() override { return "Hardware Skinning"; }
};

/// Reflection Probes
class ReflectionProbeFeatGLSL : public ShaderFeatureGLSL
{
protected:
   ShaderIncludeDependency mDep;

public:
   ReflectionProbeFeatGLSL();

   void processVert(Vector<ShaderComponent*>& componentList,
      const MaterialFeatureData& fd) override;
   
   void processPix(Vector<ShaderComponent*>& componentList,
      const MaterialFeatureData& fd) override;

   Resources getResources(const MaterialFeatureData& fd) override;

   // Sets textures and texture flags for current pass
   void setTexData(Material::StageData& stageDat,
      const MaterialFeatureData& fd,
      RenderPassData& passData,
      U32& texIndex) override;

   String getName() override
   {
      return "Reflection Probes";
   }
};
#endif // _SHADERGEN_GLSL_SHADERFEATUREGLSL_H_
