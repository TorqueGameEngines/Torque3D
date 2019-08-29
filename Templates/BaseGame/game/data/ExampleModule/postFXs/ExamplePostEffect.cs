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

singleton ShaderData( ExamplePostEffect_Shader )
{
   DXVertexShaderFile 	= $Core::CommonShaderPath @ "/postFX/postFxV.hlsl";
   DXPixelShaderFile 	= $Core:modulePath @ "ExamplePostEffectP.hlsl";   
   OGLVertexShaderFile  = $Core::CommonShaderPath @ "/postFX/gl/postFxV.glsl";
   OGLPixelShaderFile   = $Core:modulePath @ "ExamplePostEffectP.glsl";
   
   samplerNames[0] = "$inputTex";
   
   pixVersion = 3.0;
};

singleton GFXStateBlockData( ExamplePostEffect_StateBlock )
{
   samplersDefined = true;
   samplerStates[0] = SamplerClampLinear;
   samplerStates[1] = SamplerClampLinear;
   samplerStates[2] = SamplerClampLinear;
   samplerStates[3] = SamplerClampLinear;
   
   blendDefined = true;
   blendDest = GFXBlendOne;
   blendSrc = GFXBlendZero;
   
   zDefined = true;
   zEnable = false;
   zWriteEnable = false;
   
   cullDefined = true;
   cullMode = GFXCullNone;
};


function ExamplePostEffect::setShaderConsts( %this )
{
}

function ExamplePostEffect::preProcess( %this )
{
}

function ExamplePostEffect::onEnabled( %this )
{
   return true;
}

function ExamplePostEffect::onDisabled( %this )
{
}

singleton PostEffect( ExamplePostEffect )
{
   isEnabled = false;
   allowReflectPass = false;

   // Resolve the HDR before we render any editor stuff
   // and before we resolve the scene to the backbuffer.
   renderTime = "PFXBeforeBin";
   renderBin = "EditorBin";
   renderPriority = 9999;
      
   // The bright pass generates a bloomed version of 
   // the scene for pixels which are brighter than a 
   // fixed threshold value.
   //
   // This is then used in the final HDR combine pass
   // at the end of this post effect chain.
   shader = ExamplePostEffect_Shader;
   stateBlock = ExamplePostEffect_StateBlock;
   texture[0] = "$backBuffer";
   target = "$outTex";
   targetFormat = "GFXFormatR16G16B16A16F"; 
   targetScale = "1 1";
};
