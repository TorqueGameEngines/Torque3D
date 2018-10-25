singleton ShaderData( DeferredColorShader )
{
   DXVertexShaderFile = "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile  = "shaders/common/lighting/advanced/deferredColorShaderP.hlsl";
   
   OGLVertexShaderFile = "shaders/common/postFx/gl/postFxV.glsl";
   OGLPixelShaderFile  = "shaders/common/lighting/advanced/gl/deferredColorShaderP.glsl";

   pixVersion = 2.0;   
};

// Primary Deferred Shader
new GFXStateBlockData( AL_DeferredShadingState : PFX_DefaultStateBlock )
{  
   cullMode = GFXCullNone;
   
   blendDefined = true;
   blendEnable = true; 
   blendSrc = GFXBlendSrcAlpha;
   blendDest = GFXBlendInvSrcAlpha;
   
   samplersDefined = true;
   samplerStates[0] = SamplerWrapLinear;
   samplerStates[1] = SamplerWrapLinear;
   samplerStates[2] = SamplerWrapLinear;
   samplerStates[3] = SamplerWrapLinear;
   samplerStates[4] = SamplerWrapLinear;
};

new ShaderData( AL_DeferredShader )
{
   DXVertexShaderFile = "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile  = "shaders/common/lighting/advanced/deferredShadingP.hlsl";
   
   OGLVertexShaderFile = "shaders/common/postFx/gl/postFxV.glsl";
   OGLPixelShaderFile  = "shaders/common/lighting/advanced/gl/deferredShadingP.glsl";

   samplerNames[0] = "colorBufferTex";
   samplerNames[1] = "diffuseLightingBuffer";
   samplerNames[2] = "matInfoTex";
   samplerNames[3] = "specularLightingBuffer";
   samplerNames[4] = "deferredTex";
   pixVersion = 2.0;
};

new GFXStateBlockData( AL_DeferredCaptureState : PFX_DefaultStateBlock )
{        
   blendEnable = false; 
   
   separateAlphaBlendDefined = true;
   separateAlphaBlendEnable = true;
   separateAlphaBlendSrc = GFXBlendSrcAlpha;
   separateAlphaBlendDest = GFXBlendDestAlpha;
   separateAlphaBlendOp = GFXBlendOpMin;
   
   samplersDefined = true;
   samplerStates[0] = SamplerWrapLinear;
   samplerStates[1] = SamplerWrapLinear;
   samplerStates[2] = SamplerWrapLinear;
   samplerStates[3] = SamplerWrapLinear;
   samplerStates[4] = SamplerWrapLinear;
};

new ShaderData( AL_ProbeShader )
{
   DXVertexShaderFile = "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile  = "shaders/common/lighting/advanced/probeShadingP.hlsl";
   
   OGLVertexShaderFile = "shaders/common/postFx/gl/postFxV.glsl";
   OGLPixelShaderFile  = "shaders/common/lighting/advanced/gl/probeShadingP.glsl";

   samplerNames[0] = "colorBufferTex";
   samplerNames[1] = "diffuseLightingBuffer";
   samplerNames[2] = "matInfoTex";
   samplerNames[3] = "specularLightingBuffer";
   samplerNames[4] = "deferredTex";
   pixVersion = 2.0;
};


singleton PostEffect( AL_PreCapture )
{
   renderTime = "PFXBeforeBin";
   renderBin = "EditorBin";
   shader = AL_ProbeShader;
   stateBlock = AL_DeferredCaptureState;
   texture[0] = "#color";
   texture[1] = "#diffuseLighting";
   texture[2] = "#matinfo";
   texture[3] = "#specularLighting";
   texture[4] = "#deferred";
   target = "$backBuffer";
   renderPriority = 10000;
   allowReflectPass = true;
};

singleton PostEffect( AL_DeferredShading )
{
   renderTime = "PFXAfterBin";
   renderBin = "BeginBin";
   shader = AL_DeferredShader;
   stateBlock = AL_DeferredShadingState;
   texture[0] = "#color";
   texture[1] = "#diffuseLighting";
   texture[2] = "#matinfo";
   texture[3] = "#specularLighting";
   texture[4] = "#deferred";
   
   target = "$backBuffer";
   renderPriority = 10000;
   allowReflectPass = true;
};

// Debug Shaders.
new ShaderData( AL_ColorBufferShader )
{
   DXVertexShaderFile = "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile  = "shaders/common/lighting/advanced/dbgColorBufferP.hlsl";
   
   OGLVertexShaderFile = "shaders/common/postFx/gl/postFxV.glsl";
   OGLPixelShaderFile  = "shaders/common/lighting/advanced/gl/dbgColorBufferP.glsl";

   samplerNames[0] = "colorBufferTex";
   pixVersion = 2.0;
};

singleton PostEffect( AL_ColorBufferVisualize )
{   
   shader = AL_ColorBufferShader;
   stateBlock = AL_DefaultVisualizeState;
   texture[0] = "#color";
   target = "$backBuffer";
   renderPriority = 9999;
};

/// Toggles the visualization of the AL lighting specular power buffer.
function toggleColorBufferViz( %enable )
{   
   if ( %enable $= "" )
   {
      $AL_ColorBufferShaderVar = AL_ColorBufferVisualize.isEnabled() ? false : true;
      AL_ColorBufferVisualize.toggle();
   }
   else if ( %enable )
   {
      AL_DeferredShading.disable();
      AL_ColorBufferVisualize.enable();
   }
   else if ( !%enable )
   {
      AL_ColorBufferVisualize.disable();    
      AL_DeferredShading.enable();
   }
}

//roughness map display (matinfo.b)
new ShaderData( AL_RoughMapShader )
{
   DXVertexShaderFile = "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile  = "shaders/common/lighting/advanced/dbgRoughMapVisualizeP.hlsl";

   OGLVertexShaderFile = "shaders/common/postFx/gl/postFxV.glsl";
   OGLPixelShaderFile  = "shaders/common/lighting/advanced/gl/dbgRoughMapVisualizeP.glsl";

   samplerNames[0] = "matinfoTex";
   pixVersion = 2.0;
};

singleton PostEffect( AL_RoughMapVisualize )
{   
   shader = AL_RoughMapShader;
   stateBlock = AL_DefaultVisualizeState;
   texture[0] = "#matinfo";
   target = "$backBuffer";
   renderPriority = 9999;
};

function toggleRoughMapViz( %enable )
{   
   if ( %enable $= "" )
   {
      $AL_RoughMapShaderVar = AL_RoughMapVisualize.isEnabled() ? false : true;
      AL_RoughMapVisualize.toggle();
   }
   else if ( %enable )
      AL_RoughMapVisualize.enable();
   else if ( !%enable )
      AL_RoughMapVisualize.disable();    
}

//metalness map display (matinfo.a)
new ShaderData( AL_MetalMapShader )
{
   DXVertexShaderFile = "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile  = "shaders/common/lighting/advanced/dbgMetalMapVisualizeP.hlsl";

   OGLVertexShaderFile = "shaders/common/postFx/gl/postFxV.glsl";
   OGLPixelShaderFile  = "shaders/common/lighting/advanced/gl/dbgMetalMapVisualizeP.glsl";

   samplerNames[0] = "matinfoTex";
   pixVersion = 2.0;
};

singleton PostEffect( AL_MetalMapVisualize )
{   
   shader = AL_MetalMapShader;
   stateBlock = AL_DefaultVisualizeState;
   texture[0] = "#matinfo";
   target = "$backBuffer";
   renderPriority = 9999;
};

function toggleMetalMapViz( %enable )
{   
   if ( %enable $= "" )
   {
      $AL_MetalMapShaderVar = AL_MetalMapVisualize.isEnabled() ? false : true;
      AL_MetalMapVisualize.toggle();
   }
   else if ( %enable )
      AL_MetalMapVisualize.enable();
   else if ( !%enable )
      AL_MetalMapVisualize.disable();    
}

//Light map display (indirectLighting)
new ShaderData( AL_LightMapShader )
{
   DXVertexShaderFile = "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile  = "shaders/common/lighting/advanced/dbgLightMapVisualizeP.hlsl";

   OGLVertexShaderFile = "shaders/common/postFx/gl/postFxV.glsl";
   OGLPixelShaderFile  = "shaders/common/lighting/advanced/gl/dbgLightMapVisualizeP.glsl";

   samplerNames[0] = "specularLightingBuffer";
   pixVersion = 2.0;
};

singleton PostEffect( AL_LightMapVisualize )
{   
   shader = AL_LightMapShader;
   stateBlock = AL_DefaultVisualizeState;
   texture[0] = "#specularLighting";
   target = "$backBuffer";
   renderPriority = 9999;
};

function toggleLightMapViz( %enable )
{   
   if ( %enable $= "" )
   {
      $AL_LightMapShaderVar = AL_LightMapVisualize.isEnabled() ? false : true;
      AL_LightMapVisualize.toggle();
   }
   else if ( %enable )
      AL_LightMapVisualize.enable();
   else if ( !%enable )
      AL_LightMapVisualize.disable();    
}