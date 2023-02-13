singleton ShaderData( DeferredColorShader )
{
   DXVertexShaderFile = $Core::CommonShaderPath @ "/postFX/postFxV.hlsl";
   DXPixelShaderFile  = $Core::CommonShaderPath @ "/lighting/advanced/deferredColorShaderP.hlsl";
   
   OGLVertexShaderFile = $Core::CommonShaderPath @ "/postFX/gl/postFxV.glsl";
   OGLPixelShaderFile  = $Core::CommonShaderPath @ "/lighting/advanced/gl/deferredColorShaderP.glsl";

   pixVersion = 2.0;   
};

singleton GFXStateBlockData( AL_DeferredCaptureState : PFX_DefaultStateBlock )
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

singleton shaderData( AL_ProbeShader )
{
   DXVertexShaderFile = $Core::CommonShaderPath @ "/postFX/postFxV.hlsl";
   DXPixelShaderFile  = $Core::CommonShaderPath @ "/lighting/advanced/probeShadingP.hlsl";
   
   OGLVertexShaderFile = $Core::CommonShaderPath @ "/postFX/gl/postFxV.glsl";
   OGLPixelShaderFile  = $Core::CommonShaderPath @ "/lighting/advanced/gl/probeShadingP.glsl";

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