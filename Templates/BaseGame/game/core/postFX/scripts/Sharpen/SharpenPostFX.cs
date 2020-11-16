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

$PostFX::SharpenPostFX::sharpness = "1";

singleton ShaderData( SharpenPostFX_Shader )
{
   DXVertexShaderFile 	= $Core::CommonShaderPath @ "/postFX/postFxV.hlsl";
   DXPixelShaderFile 	= "./SharpenPostFXP.hlsl";   
   OGLVertexShaderFile  = $Core::CommonShaderPath @ "/postFX/gl/postFxV.glsl";
   OGLPixelShaderFile   = "./SharpenPostFXP.glsl";
   
   samplerNames[0] = "$inputTex";
   
   pixVersion = 3.0;
};

singleton GFXStateBlockData( SharpenPostFX_StateBlock )
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


function SharpenPostFX::setShaderConsts( %this )
{
   %this.setShaderConst( "$sharpness", $PostFX::SharpenPostFX::sharpness );
}

function SharpenPostFX::preProcess( %this )
{
}

function SharpenPostFX::onAdd(%this)
{
   //Register the postFX with the manager
   PostFXManager.registerPostEffect(%this);
}

function SharpenPostFX::onEnabled( %this )
{
   return true;
}

function SharpenPostFX::onDisabled( %this )
{
   return true;
}

//This is used to populate the PostFXEditor's settings so the post FX can be edited
//This is automatically polled for any postFX that has been registered(in our onAdd) and the settings
//are thus exposed for editing
function SharpenPostFX::populatePostFXSettings(%this)
{
   PostEffectEditorInspector.startGroup("SharpenPostFX - General");
   PostEffectEditorInspector.addCallbackField("$PostFX::SharpenPostFX::Enabled", "Enabled", "bool", "", $PostFX::SharpenPostFX::Enabled, "", "toggleSharpenPostFX");
   PostEffectEditorInspector.addField("$PostFX::SharpenPostFX::sharpness", "Sharpness", "range", "", $PostFX::SharpenPostFX::sharpness, "0 2 20");
   PostEffectEditorInspector.endGroup();
}

//This is called back from our callbackField defined in populatePostFXSettings to
//Allow us to easily toggle the postFX and have it respond immediately
function PostEffectEditorInspector::toggleSharpenPostFX(%this)
{
   if($PostFX::SharpenPostFX::Enabled)
      SharpenPostFX.enable();
   else
      SharpenPostFX.disable();
}

//This function pair(applyFromPreset and settingsApply) are done the way they are, with the separated variables
//so that we can effectively store the 'settings' away from the live variables that the postFX's actually utilize
//when rendering. This allows us to modify things but still leave room for reverting or temporarily applying them
function SharpenPostFX::applyFromPreset(%this)
{
   if($PostFX::SharpenPostFX::Enabled)
      %this.enable();
   else
      %this.disable();
}

function SharpenPostFX::savePresetSettings(%this)
{
   PostFXManager::savePresetSetting("$PostFX::SharpenPostFX::Enabled");
   PostFXManager::savePresetSetting("$PostFX::SharpenPostFX::sharpness");
}

//Our actual postFX
singleton PostEffect( SharpenPostFX )
{
   enabled = false;
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
   shader = SharpenPostFX_Shader;
   stateBlock = SharpenPostFX_StateBlock;
   texture[0] = "$backBuffer";
   target = "$backBuffer";
   targetFormat = "GFXFormatR16G16B16A16F"; 
   targetScale = "1 1";
};
