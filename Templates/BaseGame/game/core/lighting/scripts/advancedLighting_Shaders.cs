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


// Vector Light State
new GFXStateBlockData( AL_VectorLightState )
{
   blendDefined = true;
   blendEnable = true;
   blendSrc = GFXBlendOne;
   blendDest = GFXBlendOne;
   blendOp = GFXBlendOpAdd;
   
   colorWriteDefined = true;
   colorWriteRed = true;
   colorWriteBlue = true;
   colorWriteGreen = true;
   colorWriteAlpha = false; //disable alpha write
   
   zDefined = true;
   zEnable = false;
   zWriteEnable = true;
   zFunc = GFXCmpGreater;

   samplersDefined = true;
   samplerStates[0] = SamplerClampPoint;  // G-buffer
   mSamplerNames[0] = "deferredBuffer";
   samplerStates[1] = SamplerClampPoint;  // Shadow Map (Do not change this to linear, as all cards can not filter equally.)
   mSamplerNames[1] = "shadowMap";
   samplerStates[2] = SamplerClampPoint;  // Shadow Map (Do not change this to linear, as all cards can not filter equally.)
   mSamplerNames[2] = "dynamicShadowMap";
   samplerStates[3] = SamplerClampLinear;  // SSAO Mask
   mSamplerNames[3] = "ssaoMask";
   samplerStates[4] = SamplerWrapPoint;   // Random Direction Map
   
   cullDefined = true;
   cullMode = GFXCullNone;
   
   stencilDefined = true;
   stencilEnable = false;

};

// Vector Light Material
new ShaderData( AL_VectorLightShader )
{
   DXVertexShaderFile = $Core::CommonShaderPath @ "/lighting/advanced/farFrustumQuadV.hlsl";
   DXPixelShaderFile  = $Core::CommonShaderPath @ "/lighting/advanced/vectorLightP.hlsl";

   OGLVertexShaderFile = $Core::CommonShaderPath @ "/lighting/advanced/gl/farFrustumQuadV.glsl";
   OGLPixelShaderFile  = $Core::CommonShaderPath @ "/lighting/advanced/gl/vectorLightP.glsl";
   
   samplerNames[0] = "$deferredBuffer";
   samplerNames[1] = "$shadowMap";
   samplerNames[2] = "$dynamicShadowMap";
   samplerNames[3] = "$ssaoMask";
   samplerNames[4] = "$gTapRotationTex";
   samplerNames[5] = "$lightBuffer";
   samplerNames[6] = "$colorBuffer";
   samplerNames[7] = "$matInfoBuffer";  
   
   pixVersion = 3.0;
};

new CustomMaterial( AL_VectorLightMaterial )
{
   shader = AL_VectorLightShader;
   stateBlock = AL_VectorLightState;
   
   sampler["deferredBuffer"] = "#deferred";
   sampler["shadowMap"] = "$dynamiclight";
   sampler["dynamicShadowMap"] = "$dynamicShadowMap";
   sampler["ssaoMask"] = "#ssaoMask";  
   sampler["lightBuffer"] = "#specularLighting";
   sampler["colorBuffer"] = "#color";
   sampler["matInfoBuffer"] = "#matinfo";
   
   target = "AL_FormatToken";
   
   pixVersion = 3.0;
};

//------------------------------------------------------------------------------

// Convex-geometry light states
new GFXStateBlockData( AL_ConvexLightState )
{
   blendDefined = true;
   blendEnable = true;
   blendSrc = GFXBlendOne;
   blendDest = GFXBlendOne;
   blendOp = GFXBlendOpAdd;
   
   colorWriteDefined = true;
   colorWriteRed = true;
   colorWriteBlue = true;
   colorWriteGreen = true;
   colorWriteAlpha = false; //disable alpha write
   
   zDefined = true;
   zEnable = true;
   zWriteEnable = false;
   zFunc = GFXCmpGreater;

   samplersDefined = true;
   samplerStates[0] = SamplerClampPoint;  // G-buffer
   mSamplerNames[0] = "deferredBuffer";
   samplerStates[1] = SamplerClampPoint;  // Shadow Map (Do not use linear, these are perspective projections)
   mSamplerNames[1] = "shadowMap";
   samplerStates[2] = SamplerClampPoint;  // Shadow Map (Do not use linear, these are perspective projections)
   mSamplerNames[2] = "dynamicShadowMap";
   samplerStates[3] = SamplerClampLinear; // Cookie Map   
   samplerStates[4] = SamplerWrapPoint;   // Random Direction Map
   
   cullDefined = true;
   cullMode = GFXCullCW;
   
   stencilDefined = true;
   stencilEnable = false;

};

// Point Light Material
new ShaderData( AL_PointLightShader )
{
   DXVertexShaderFile = $Core::CommonShaderPath @ "/lighting/advanced/convexGeometryV.hlsl";
   DXPixelShaderFile  = $Core::CommonShaderPath @ "/lighting/advanced/pointLightP.hlsl";

   OGLVertexShaderFile = $Core::CommonShaderPath @ "/lighting/advanced/gl/convexGeometryV.glsl";
   OGLPixelShaderFile  = $Core::CommonShaderPath @ "/lighting/advanced/gl/pointLightP.glsl";

   samplerNames[0] = "$deferredBuffer";
   samplerNames[1] = "$shadowMap";
   samplerNames[2] = "$dynamicShadowMap";
   samplerNames[3] = "$cookieMap";
   samplerNames[4] = "$gTapRotationTex";
   samplerNames[5] = "$lightBuffer";
   samplerNames[6] = "$colorBuffer";
   samplerNames[7] = "$matInfoBuffer";
   
   pixVersion = 3.0;
};

new CustomMaterial( AL_PointLightMaterial )
{
   shader = AL_PointLightShader;
   stateBlock = AL_ConvexLightState;
   
   sampler["deferredBuffer"] = "#deferred";
   sampler["shadowMap"] = "$dynamiclight";
   sampler["dynamicShadowMap"] = "$dynamicShadowMap";
   sampler["cookieMap"] = "$dynamiclightmask";
   sampler["lightBuffer"] = "#specularLighting";
   sampler["colorBuffer"] = "#color";
   sampler["matInfoBuffer"] = "#matinfo";
   
   target = "AL_FormatToken";
   
   pixVersion = 3.0;
};

// Spot Light Material
new ShaderData( AL_SpotLightShader )
{
   DXVertexShaderFile = $Core::CommonShaderPath @ "/lighting/advanced/convexGeometryV.hlsl";
   DXPixelShaderFile  = $Core::CommonShaderPath @ "/lighting/advanced/spotLightP.hlsl";

   OGLVertexShaderFile = $Core::CommonShaderPath @ "/lighting/advanced/gl/convexGeometryV.glsl";
   OGLPixelShaderFile  = $Core::CommonShaderPath @ "/lighting/advanced/gl/spotLightP.glsl";
   
   samplerNames[0] = "$deferredBuffer";
   samplerNames[1] = "$shadowMap";
   samplerNames[2] = "$dynamicShadowMap";
   samplerNames[3] = "$cookieMap";
   samplerNames[4] = "$gTapRotationTex";
   samplerNames[5] = "$lightBuffer";
   samplerNames[6] = "$colorBuffer";
   samplerNames[7] = "$matInfoBuffer";

   pixVersion = 3.0;
};

new CustomMaterial( AL_SpotLightMaterial )
{
   shader = AL_SpotLightShader;
   stateBlock = AL_ConvexLightState;
   
   sampler["deferredBuffer"] = "#deferred";
   sampler["shadowMap"] = "$dynamiclight";
   sampler["dynamicShadowMap"] = "$dynamicShadowMap";
   sampler["cookieMap"] = "$dynamiclightmask";
   sampler["lightBuffer"] = "#specularLighting";
   sampler["colorBuffer"] = "#color";
   sampler["matInfoBuffer"] = "#matinfo";
   
   target = "AL_FormatToken";
   
   pixVersion = 3.0;
};

/// This material is used for generating deferred 
/// materials for objects that do not have materials.
new Material( AL_DefaultDeferredMaterial )
{
   // We need something in the first pass else it 
   // won't create a proper material instance.  
   //
   // We use color here because some objects may not
   // have texture coords in their vertex format... 
   // for example like terrain.
   //
   diffuseColor[0] = "1 1 1 1";
};

/// This material is used for generating shadow 
/// materials for objects that do not have materials.
new Material( AL_DefaultShadowMaterial )
{
   // We need something in the first pass else it 
   // won't create a proper material instance.  
   //
   // We use color here because some objects may not
   // have texture coords in their vertex format... 
   // for example like terrain.
   //
   diffuseColor[0] = "1 1 1 1";
               
   // This is here mostly for terrain which uses
   // this material to create its shadow material.
   //
   // At sunset/sunrise the sun is looking thru 
   // backsides of the terrain which often are not
   // closed.  By changing the material to be double
   // sided we avoid holes in the shadowed geometry.
   //
   doubleSided = true;
};

// Particle System Point Light Material
new ShaderData( AL_ParticlePointLightShader )
{
   DXVertexShaderFile = $Core::CommonShaderPath @ "/lighting/advanced/particlePointLightV.hlsl";
   DXPixelShaderFile  = $Core::CommonShaderPath @ "/lighting/advanced/particlePointLightP.hlsl";

   OGLVertexShaderFile = $Core::CommonShaderPath @ "/lighting/advanced/gl/convexGeometryV.glsl";
   OGLPixelShaderFile  = $Core::CommonShaderPath @ "/lighting/advanced/gl/pointLightP.glsl";
   
   samplerNames[0] = "$deferredBuffer";   
      
   pixVersion = 3.0;
};

new CustomMaterial( AL_ParticlePointLightMaterial )
{
   shader = AL_ParticlePointLightShader;
   stateBlock = AL_ConvexLightState;
   
   sampler["deferredBuffer"] = "#deferred";
   target = "diffuseLighting";
   
   pixVersion = 3.0;
};

//Probe Processing
new ShaderData( IrradianceShader )
{
   DXVertexShaderFile = $Core::CommonShaderPath @ "/lighting/advanced/cubemapV.hlsl";
   DXPixelShaderFile  = $Core::CommonShaderPath @ "/lighting/advanced/irradianceP.hlsl";

   OGLVertexShaderFile = $Core::CommonShaderPath @ "/lighting/advanced/gl/cubemapV.glsl";
   OGLPixelShaderFile  = $Core::CommonShaderPath @ "/lighting/advanced/gl/irradianceP.glsl";
   
   samplerNames[0] = "$environmentMap";
   
   pixVersion = 3.0;
};

new ShaderData( PrefiterCubemapShader )
{
   DXVertexShaderFile = $Core::CommonShaderPath @ "/lighting/advanced/cubemapV.hlsl";
   DXPixelShaderFile  = $Core::CommonShaderPath @ "/lighting/advanced/prefilterP.hlsl";

   OGLVertexShaderFile = $Core::CommonShaderPath @ "/lighting/advanced/gl/cubemapV.glsl";
   OGLPixelShaderFile  = $Core::CommonShaderPath @ "/lighting/advanced/gl/prefilterP.glsl";
   
   samplerNames[0] = "$environmentMap";
   
   pixVersion = 3.0;
};

//
singleton ShaderData( PFX_ReflectionProbeArray )
{
   DXVertexShaderFile   = $Core::CommonShaderPath @ "/postFx/postFxV.hlsl";
   DXPixelShaderFile    = $Core::CommonShaderPath @ "/lighting/advanced/reflectionProbeArrayP.hlsl";

   OGLVertexShaderFile  = $Core::CommonShaderPath @ "/postFx/gl/postFxV.glsl";
   OGLPixelShaderFile   = $Core::CommonShaderPath @ "/lighting/advanced/gl/reflectionProbeArrayP.glsl";
   
   samplerNames[0] = "$deferredBuffer";
   samplerNames[1] = "$colorBuffer";
   samplerNames[2] = "$matInfoBuffer";
   samplerNames[3] = "$BRDFTexture";
   samplerNames[4] = "$specularCubemapAR";
   samplerNames[5] = "$irradianceCubemapAR";

   pixVersion = 2.0;
};  

singleton GFXStateBlockData( PFX_ReflectionProbeArrayStateBlock )
{  
   alphaDefined = true;
   alphaTestEnable = true;
   alphaTestRef = 1;
   alphaTestFunc = GFXCmpGreaterEqual;
         
   // Do a one to one blend.
   blendDefined = true;
   blendEnable = true;
   blendSrc = GFXBlendOne;
   blendDest = GFXBlendOne;
   
   zDefined = true;
   zEnable = false;
   zWriteEnable = false;
   
   samplersDefined = true;
   samplerStates[0] = SamplerClampPoint;
   samplerStates[1] = SamplerClampPoint;
   samplerStates[2] = SamplerClampPoint;
   samplerStates[3] = SamplerClampPoint;
   samplerStates[4] = SamplerClampLinear;
   samplerStates[5] = SamplerClampLinear;
};