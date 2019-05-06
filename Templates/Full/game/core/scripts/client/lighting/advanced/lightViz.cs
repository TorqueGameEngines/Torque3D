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


new GFXStateBlockData( AL_DepthVisualizeState )
{
   zDefined = true;
   zEnable = false;
   zWriteEnable = false;

   samplersDefined = true;
   samplerStates[0] = SamplerClampPoint; // depth    
   samplerStates[1] = SamplerClampLinear; // viz color lookup
};

new GFXStateBlockData( AL_DefaultVisualizeState )
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

new ShaderData( AL_DepthVisualizeShader )
{
   DXVertexShaderFile = "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile  = "shaders/common/lighting/advanced/dbgDepthVisualizeP.hlsl";

   OGLVertexShaderFile = "shaders/common/postFx/gl/postFxV.glsl";
   OGLPixelShaderFile  = "shaders/common/lighting/advanced/gl/dbgDepthVisualizeP.glsl";

   samplerNames[0] = "deferredTex";
   samplerNames[1] = "depthViz";

   pixVersion = 2.0;
};

singleton PostEffect( AL_DepthVisualize )
{   
   shader = AL_DepthVisualizeShader;
   stateBlock = AL_DefaultVisualizeState;
   texture[0] = "#deferred";
   texture[1] = "core/scripts/client/lighting/advanced/depthviz";   
   target = "$backBuffer";
   renderPriority = 9999;
};

function AL_DepthVisualize::onEnabled( %this )
{
   AL_NormalsVisualize.disable();
   $AL_NormalsVisualizeVar = false;
   
   return true;
}

new ShaderData( AL_GlowVisualizeShader )
{
   DXVertexShaderFile = "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile  = "shaders/common/lighting/advanced/dbgGlowVisualizeP.hlsl";
   
   OGLVertexShaderFile = "shaders/common/postFx/gl/postFxV.glsl";
   OGLPixelShaderFile  = "shaders/common/lighting/advanced/gl/dbgGlowVisualizeP.glsl";

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

new ShaderData( AL_NormalsVisualizeShader )
{
   DXVertexShaderFile = "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile  = "shaders/common/lighting/advanced/dbgNormalVisualizeP.hlsl";

   OGLVertexShaderFile = "shaders/common/postFx/gl/postFxV.glsl";
   OGLPixelShaderFile  = "shaders/common/lighting/advanced/gl/dbgNormalVisualizeP.glsl";
   
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
   $AL_DepthVisualizeVar = false;   
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

function toggleBackbufferViz( %enable )
{   
   if ( %enable $= "" )
   {
      $AL_BackbufferVisualizeVar = AL_DeferredShading.isEnabled() ? true : false;
      AL_DeferredShading.toggle();
   }
   else if ( %enable )
      AL_DeferredShading.disable();
   else if ( !%enable )
      AL_DeferredShading.enable();    
}

