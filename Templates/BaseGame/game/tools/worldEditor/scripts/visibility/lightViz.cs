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
// Debug Shaders.
singleton shaderData( AL_ColorBufferShader )
{
   DXVertexShaderFile = $Core::CommonShaderPath @ "/postFX/postFxV.hlsl";
   DXPixelShaderFile  = "./shaders/dbgColorBufferP.hlsl";
   
   OGLVertexShaderFile = $Core::CommonShaderPath @ "/postFX/gl/postFxV.glsl";
   OGLPixelShaderFile  = "./shaders/dbgColorBufferP.glsl";

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
      AL_ColorBufferVisualize.enable();
   }
   else if ( !%enable )
   {
      AL_ColorBufferVisualize.disable();    
   }
}

singleton shaderData( AL_SpecMapShader )
{
   DXVertexShaderFile = $Core::CommonShaderPath @ "/postFX/postFxV.hlsl";
   DXPixelShaderFile  = "./shaders/dbgSpecMapVisualizeP.hlsl";

   OGLVertexShaderFile = $Core::CommonShaderPath @ "/postFX/gl/postFxV.glsl";
   OGLPixelShaderFile  = "./shaders/dbgSpecMapVisualizeP.glsl";

   samplerNames[0] = "matinfoTex";
   pixVersion = 2.0;
};

singleton PostEffect( AL_SpecMapVisualize )
{   
   shader = AL_SpecMapShader;
   stateBlock = AL_DefaultVisualizeState;
   texture[0] = "#matinfo";
   target = "$backBuffer";
   renderPriority = 9999;
};

/// Toggles the visualization of the AL lighting specular power buffer.
function toggleSpecMapViz( %enable )
{   
   if ( %enable $= "" )
   {
      $AL_SpecMapShaderVar = AL_SpecMapVisualize.isEnabled() ? false : true;
      AL_SpecMapVisualize.toggle();
   }
   else if ( %enable )
      AL_SpecMapVisualize.enable();
   else if ( !%enable )
      AL_SpecMapVisualize.disable();    
}

singleton GFXStateBlockData( AL_DepthVisualizeState )
{
   zDefined = true;
   zEnable = false;
   zWriteEnable = false;

   samplersDefined = true;
   samplerStates[0] = SamplerClampPoint; // depth    
   samplerStates[1] = SamplerClampLinear; // viz color lookup
};

singleton GFXStateBlockData( AL_DefaultVisualizeState )
{
   blendDefined = true;
   blendEnable = true;
   blendSrc = GFXBlendSrcAlpha;
   blendDest = GFXBlendInvSrcAlpha;
   
   zDefined = true;
   zEnable = false;
   zWriteEnable = false;

   samplersDefined = true;
   samplerStates[0] = SamplerClampPoint;   // #deferred
   samplerStates[1] = SamplerClampLinear;  // depthviz
};

singleton shaderData( AL_DepthVisualizeShader )
{
   DXVertexShaderFile = $Core::CommonShaderPath @ "/postFX/postFxV.hlsl";
   DXPixelShaderFile  = "./shaders/dbgDepthVisualizeP.hlsl";

   OGLVertexShaderFile = $Core::CommonShaderPath @ "/postFX/gl/postFxV.glsl";
   OGLPixelShaderFile  = "./shaders/dbgDepthVisualizeP.glsl";

   samplerNames[0] = "deferredTex";
   samplerNames[1] = "depthViz";

   pixVersion = 2.0;
};

singleton PostEffect( AL_DepthVisualize )
{   
   shader = AL_DepthVisualizeShader;
   stateBlock = AL_DefaultVisualizeState;
   texture[0] = "#deferred";
   texture[1] = "tools/worldEditor/images/depthviz";   
   target = "$backBuffer";
   renderPriority = 9999;
};

function AL_DepthVisualize::onEnabled( %this )
{
   AL_NormalsVisualize.disable();
   AL_LightColorVisualize.disable();
   AL_LightSpecularVisualize.disable();
   $AL_NormalsVisualizeVar = false;
   $AL_LightColorVisualizeVar = false;
   $AL_LightSpecularVisualizeVar = false;
   
   return true;
}

singleton shaderData( AL_GlowVisualizeShader )
{
   DXVertexShaderFile = $Core::CommonShaderPath @ "/postFX/postFxV.hlsl";
   DXPixelShaderFile  = "./shaders/dbgGlowVisualizeP.hlsl";
   
   OGLVertexShaderFile = $Core::CommonShaderPath @ "/postFX/gl/postFxV.glsl";
   OGLPixelShaderFile  = "./shaders/dbgGlowVisualizeP.glsl";

   samplerNames[0] = "glowBuffer";
   pixVersion = 2.0;
};

singleton PostEffect( AL_GlowVisualize )
{   
   shader = AL_GlowVisualizeShader;
   stateBlock = AL_DefaultVisualizeState;
   texture[0] = "#glowbuffer";
   target = "$backBuffer";
   renderPriority = 9999;
};

singleton shaderData( AL_NormalsVisualizeShader )
{
   DXVertexShaderFile = $Core::CommonShaderPath @ "/postFX/postFxV.hlsl";
   DXPixelShaderFile  = "./shaders/dbgNormalVisualizeP.hlsl";

   OGLVertexShaderFile = $Core::CommonShaderPath @ "/postFX/gl/postFxV.glsl";
   OGLPixelShaderFile  = "./shaders/dbgNormalVisualizeP.glsl";
   
   samplerNames[0] = "deferredTex";
   
   pixVersion = 2.0;
};

singleton PostEffect( AL_NormalsVisualize )
{   
   shader = AL_NormalsVisualizeShader;
   stateBlock = AL_DefaultVisualizeState;
   texture[0] = "#deferred";
   target = "$backBuffer";
   renderPriority = 9999;
};

function AL_NormalsVisualize::onEnabled( %this )
{
   AL_DepthVisualize.disable();
   AL_LightColorVisualize.disable();
   AL_LightSpecularVisualize.disable();
   $AL_DepthVisualizeVar = false;
   $AL_LightColorVisualizeVar = false;
   $AL_LightSpecularVisualizeVar = false;
   
   return true;
}



singleton shaderData( AL_LightColorVisualizeShader )
{
   DXVertexShaderFile = $Core::CommonShaderPath @ "/postFX/postFxV.hlsl";
   DXPixelShaderFile  = "./shaders/dbgLightColorVisualizeP.hlsl";

   OGLVertexShaderFile = $Core::CommonShaderPath @ "/postFX/gl/postFxV.glsl";
   OGLPixelShaderFile  = "./shaders/dbgLightColorVisualizeP.glsl";
   
   samplerNames[0] = "lightDeferredTex";
   
   pixVersion = 2.0;
};

singleton PostEffect( AL_LightColorVisualize )
{   
   shader = AL_LightColorVisualizeShader;
   stateBlock = AL_DefaultVisualizeState;
   texture[0] = "#lightinfo";
   target = "$backBuffer";
   renderPriority = 9999;
};

function AL_LightColorVisualize::onEnabled( %this )
{
   AL_NormalsVisualize.disable();
   AL_DepthVisualize.disable();
   AL_LightSpecularVisualize.disable();
   $AL_NormalsVisualizeVar = false;
   $AL_DepthVisualizeVar = false;
   $AL_LightSpecularVisualizeVar = false;   
   
   return true;
}


singleton shaderData( AL_LightSpecularVisualizeShader )
{
   DXVertexShaderFile = $Core::CommonShaderPath @ "/postFX/postFxV.hlsl";
   DXPixelShaderFile  = "./shaders/dbgLightSpecularVisualizeP.hlsl";

   OGLVertexShaderFile = $Core::CommonShaderPath @ "/postFX/gl/postFxV.glsl";
   OGLPixelShaderFile  = "./shaders/dbgLightSpecularVisualizeP.glsl";
   
   samplerNames[0] = "lightDeferredTex";
   
   pixVersion = 2.0;
};

singleton PostEffect( AL_LightSpecularVisualize )
{   
   shader = AL_LightSpecularVisualizeShader;
   stateBlock = AL_DefaultVisualizeState;
   texture[0] = "#lightinfo";
   target = "$backBuffer";
   renderPriority = 9999;
};

function AL_LightSpecularVisualize::onEnabled( %this )
{
   AL_NormalsVisualize.disable();
   AL_DepthVisualize.disable();
   AL_LightColorVisualize.disable();
   $AL_NormalsVisualizeVar = false;
   $AL_DepthVisualizeVar = false;
   $AL_LightColorVisualizeVar = false;   
   
   return true;
}

/// Toggles the visualization of the AL depth buffer.
function toggleDepthViz( %enable )
{
   if ( %enable $= "" )
   {
      $AL_DepthVisualizeVar = AL_DepthVisualize.isEnabled() ? false : true;
      AL_DepthVisualize.toggle();
   }
   else if ( %enable )
      AL_DepthVisualize.enable();
   else if ( !%enable )
      AL_DepthVisualize.disable();
}

/// Toggles the visualization of the AL depth buffer.
function toggleGlowViz( %enable )
{
   if ( %enable $= "" )
   {
      $AL_GlowVisualizeVar = AL_GlowVisualize.isEnabled() ? false : true;
      AL_GlowVisualize.toggle();
   }
   else if ( %enable )
      AL_GlowVisualize.enable();
   else if ( !%enable )
      AL_GlowVisualize.disable();
}

/// Toggles the visualization of the AL normals buffer.
function toggleNormalsViz( %enable )
{
   if ( %enable $= "" )
   {
      $AL_NormalsVisualizeVar = AL_NormalsVisualize.isEnabled() ? false : true;
      AL_NormalsVisualize.toggle();
   }
   else if ( %enable )
      AL_NormalsVisualize.enable();
   else if ( !%enable )
      AL_NormalsVisualize.disable();   
}

/// Toggles the visualization of the AL lighting color buffer.
function toggleLightColorViz( %enable )
{   
   if ( %enable $= "" )
   {
      $AL_LightColorVisualizeVar = AL_LightColorVisualize.isEnabled() ? false : true;
      AL_LightColorVisualize.toggle();
   }
   else if ( %enable )
      AL_LightColorVisualize.enable();
   else if ( !%enable )
      AL_LightColorVisualize.disable();    
}

/// Toggles the visualization of the AL lighting specular power buffer.
function toggleLightSpecularViz( %enable )
{   
   if ( %enable $= "" )
   {
      $AL_LightSpecularVisualizeVar = AL_LightSpecularVisualize.isEnabled() ? false : true;
      AL_LightSpecularVisualize.toggle();
   }
   else if ( %enable )
      AL_LightSpecularVisualize.enable();
   else if ( !%enable )
      AL_LightSpecularVisualize.disable();    
}

function toggleBackbufferViz( %enable )
{   
   if ( %enable $= "" )
   {
      $AL_BackbufferVisualizeVar = AL_DeferredShading.isEnabled() ? true : false;
   }
}

//
//
//
function setLightingMode(%mode)
{
   resetLightingMode();
   
   switch$ ( %mode )
   {
      case "Unlit":
         $Shadows::disable = true;
         $Light::renderReflectionProbes = false;
         $Light::disableLights = true;
         EVisibilityLightingModesOptions.checkItem(1, true);
      case "NoShadows":
         $Shadows::disable = true;
         EVisibilityLightingModesOptions.checkItem(2, true);
      case "DetailLighting":
         $AL::DetailLightingViz = true;
         EVisibilityLightingModesOptions.checkItem(3, true);
      case "LightingOnly":
         $Light::renderReflectionProbes = false;
         EVisibilityLightingModesOptions.checkItem(4, true);
      case "ReflectionsOnly":
         $Light::disableLights = true;
         EVisibilityLightingModesOptions.checkItem(5, true);
   }
   
   reInitMaterials();
}

function resetLightingMode()
{
   for(%i=0; %i < 6; %i++)
   {
       EVisibilityLightingModesOptions.checkItem(%i, false);
   }
   
   $Light::renderReflectionProbes = true;
   $Light::disableLights = false;
   $Shadows::disable = false;
   $AL::DetailLightingViz = false;
   EVisibilityLightingModesOptions.checkItem(0, true);
}

function togglePSSMDebugViz()
{
   disableVisualizers();
   $AL::PSSMDebugRender = !$AL::PSSMDebugRender;  
}

function disablePSSMDebugViz()
{
   $AL::PSSMDebugRender = false;  
   $Light::renderReflectionProbes = true;
}

//
//
function toggleLightFrustumViz()
{
   $Light::renderLightFrustums = !$Light::renderLightFrustums; 
}

function disableLightFrustumViz()
{
   $Light::renderLightFrustums = false;
}

function toggleLightViz(%mode)
{
   setLightingMode("Lit");
   
   if($AL::DiffuseLightViz == 1)
      %lastMode = "Diffuse";
   else if($AL::SpecularLightViz == 1)
      %lastMode = "Specular";
   
   $AL::DiffuseLightViz = 0;
   $AL::SpecularLightViz = 0;
   
   EVisibilityLightsOptions.checkItem(2, false);
   EVisibilityLightsOptions.checkItem(3, false);
   
   if(%mode $= %lastMode)
   {
      //forces the forward materials to get dis viz properly
      reInitMaterials();
   
      return;
   }
         
   switch$(%mode)
   {
      case "Diffuse":
         $AL::DiffuseLightViz = 1;
         EVisibilityLightsOptions.checkItem(2, true);
      case "Specular":
         $AL::SpecularLightViz = 1;
         EVisibilityLightsOptions.checkItem(3, true);
   }
   
   //forces the forward materials to get dis viz properly
   reInitMaterials();
}

function disableLightViz()
{
   toggleLightViz(-1);
}

//Lighting Viz
singleton Material( Viz_DetailLightingMat )
{
   diffuseColor[0] = "0.5 0.5 0.5 1";
   
   preload = true;
};

function toggleDetailLightingViz()
{
   if(!isObject(lightBizBin))
      DiffuseRenderPassManager.addManager( new lightVisualizerBin(lightBizBin) { renderOrder = 1.5; processAddOrder = 1.5; } );
      
   lightBizBin.material = Viz_DetailLightingMat;
   
   //Then set the lighting bin flags for various modes here
}