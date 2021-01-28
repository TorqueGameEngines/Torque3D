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

singleton ShaderData( LUTColorGradePostFX_Shader )
{
   DXVertexShaderFile 	= $Core::CommonShaderPath @ "/postFX/postFxV.hlsl";
   DXPixelShaderFile 	= "./LUTColorGradePostFXP.hlsl";   
   OGLVertexShaderFile  = $Core::CommonShaderPath @ "/postFX/gl/postFxV.glsl";
   OGLPixelShaderFile   = "./LUTColorGradePostFXP.glsl";
   
   samplerNames[0] = "$inputTex";
   samplerNames[1] = "$colorCorrectionTex";
   
   pixVersion = 3.0;
};

singleton GFXStateBlockData( LUTColorGradePostFX_StateBlock )
{
   samplersDefined = true;
   samplerStates[0] = SamplerClampLinear;
   samplerStates[1] = SamplerClampLinear;
   
   blendDefined = true;
   blendDest = GFXBlendOne;
   blendSrc = GFXBlendZero;
   
   zDefined = true;
   zEnable = false;
   zWriteEnable = false;
   
   cullDefined = true;
   cullMode = GFXCullNone;
};


function LUTColorGradePostFX::setShaderConsts( %this )
{
}

function LUTColorGradePostFX::preProcess( %this )
{
   if($PostFX::LUTColorGradePostFX::LUTImage $= "")
      $PostFX::LUTColorGradePostFX::LUTImage = "core/postFX/images/null_color_ramp.png";
      
   if ( %this.texture[1] !$= $PostFX::LUTColorGradePostFX::LUTImage )
      %this.setTexture( 1, $PostFX::LUTColorGradePostFX::LUTImage );
}

function LUTColorGradePostFX::onAdd(%this)
{
   //Register the postFX with the manager
   PostFXManager.registerPostEffect(%this);
}

function LUTColorGradePostFX::onEnabled( %this )
{
   return true;
}

function LUTColorGradePostFX::onDisabled( %this )
{
}

//This is used to populate the PostFXEditor's settings so the post FX can be edited
//This is automatically polled for any postFX that has been registered(in our onAdd) and the settings
//are thus exposed for editing
function LUTColorGradePostFX::populatePostFXSettings(%this)
{
   PostEffectEditorInspector.startGroup("LUTColorGradePostFX - General");
   PostEffectEditorInspector.addCallbackField("$PostFX::LUTColorGradePostFX::Enabled", "Enable", "bool", "", $PostFX::LUTColorGradePostFX::Enabled, "", "toggleLUTColorGradePostFX");
   PostEffectEditorInspector.addField("$PostFX::LUTColorGradePostFX::LUTImage", "LUT Image", "image", "", $PostFX::LUTColorGradePostFX::LUTImage, "");
   PostEffectEditorInspector.endGroup();
}

function PostEffectEditorInspector::toggleLUTColorGradePostFX(%this)
{
   if($PostFX::LUTColorGradePostFX::Enabled)
      LUTColorGradePostFX.enable();
   else
      LUTColorGradePostFX.disable();
}

//This function pair(applyFromPreset and settingsApply) are done the way they are, with the separated variables
//so that we can effectively store the 'settings' away from the live variables that the postFX's actually utilize
//when rendering. This allows us to modify things but still leave room for reverting or temporarily applying them
function LUTColorGradePostFX::applyFromPreset(%this)
{
   //LUTColorGradePostFX Settings
   if($PostFX::LUTColorGradePostFX::Enable)
      %this.enable();
   else
      %this.disable();
}

function LUTColorGradePostFX::savePresetSettings(%this)
{
   PostFXManager::savePresetSetting("$PostFX::LUTColorGradePostFX::Enabled");
   PostFXManager::savePresetSetting("$PostFX::LUTColorGradePostFX::LUTImage");
}

//Our actual postFX
singleton PostEffect( LUTColorGradePostFX )
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
   shader = LUTColorGradePostFX_Shader;
   stateBlock = LUTColorGradePostFX_StateBlock;
   texture[0] = "$backBuffer";
   texture[1] = $PostFX::LUTColorGradePostFX::LUTImage;
   target = "$backBuffer";
   targetFormat = "GFXFormatR16G16B16A16F"; 
   targetScale = "1 1";
};
