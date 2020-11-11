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

/// The lens distortion coefficient.
$PostFX::EnableChromaticAberrationPostFX::DistCoefficient =  -0.05;

/// The cubic distortion value.
$PostFX::EnableChromaticAberrationPostFX::CubeDistortionFactor =  -0.1;

/// The amount and direction of the maxium shift for
/// the red, green, and blue channels.
$PostFX::EnableChromaticAberrationPostFX::ColorDistFactor = "0.005 -0.005 0.01";

singleton ShaderData( ChromaticAberrationPostFX_Shader )
{
   DXVertexShaderFile 	= $Core::CommonShaderPath @ "/postFX/postFxV.hlsl";
   DXPixelShaderFile 	= "./ChromaticAberrationPostFXP.hlsl";   
   OGLVertexShaderFile  = $Core::CommonShaderPath @ "/postFX/gl/postFxV.glsl";
   OGLPixelShaderFile   = "./ChromaticAberrationPostFXP.glsl";
   
   samplerNames[0] = "$inputTex";
   
   pixVersion = 2.0;
};

singleton GFXStateBlockData( ChromaticAberrationPostFX_StateBlock )
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


function ChromaticAberrationPostFX::setShaderConsts( %this )
{
   %this.setShaderConst( "$distCoeff", $PostFX::EnableChromaticAberrationPostFX::DistCoefficient );   
   %this.setShaderConst( "$cubeDistort", $PostFX::EnableChromaticAberrationPostFX::CubeDistortionFactor );    
   %this.setShaderConst( "$colorDistort", $PostFX::EnableChromaticAberrationPostFX::ColorDistFactor ); 
}

function ChromaticAberrationPostFX::preProcess( %this )
{
}

function ChromaticAberrationPostFX::onAdd(%this)
{
   //Register the postFX with the manager
   PostFXManager.registerPostEffect(%this);
}

function ChromaticAberrationPostFX::onEnabled( %this )
{
   return true;
}

function ChromaticAberrationPostFX::onDisabled( %this )
{
}

//This is used to populate the PostFXEditor's settings so the post FX can be edited
//This is automatically polled for any postFX that has been registered(in our onAdd) and the settings
//are thus exposed for editing
function ChromaticAberrationPostFX::populatePostFXSettings(%this)
{
   PostEffectEditorInspector.startGroup("ChromaticAberrationPostFX - General");
   PostEffectEditorInspector.addCallbackField("$PostFX::EnableChromaticAberrationPostFX::Enabled", "Enabled", "bool", "", $PostFX::EnableChromaticAberrationPostFX::Enabled, "", "toggleChromaticAberrationPostFX");
   PostEffectEditorInspector.addField("$PostFX::EnableChromaticAberrationPostFX::DistCoefficient", "Dist Coefficient", "float", "", $PostFX::EnableChromaticAberrationPostFX::DistCoefficient, "");
   PostEffectEditorInspector.addField("$PostFX::EnableChromaticAberrationPostFX::CubeDistortionFactor", "Cube Distortion Factor", "float", "", $PostFX::EnableChromaticAberrationPostFX::CubeDistortionFactor, "");
   PostEffectEditorInspector.addField("$PostFX::EnableChromaticAberrationPostFX::ColorDistFactor", "Color Distortion Factor", "string", "", $PostFX::EnableChromaticAberrationPostFX::ColorDistFactor, "");
   PostEffectEditorInspector.endGroup();
}

function PostEffectEditorInspector::toggleChromaticAberrationPostFX(%this)
{
   if($PostFX::EnableChromaticAberrationPostFX::Enabled)
      ChromaticAberrationPostFX.enable();
   else
      ChromaticAberrationPostFX.disable();
}

//This function pair(applyFromPreset and settingsApply) are done the way they are, with the separated variables
//so that we can effectively store the 'settings' away from the live variables that the postFX's actually utilize
//when rendering. This allows us to modify things but still leave room for reverting or temporarily applying them
function ChromaticAberrationPostFX::applyFromPreset(%this)
{
   if($PostFX::EnableChromaticAberrationPostFX::Enabled)
      %this.enable();
   else
      %this.disable();
}

function ChromaticAberrationPostFX::savePresetSettings(%this)
{
   PostFXManager::savePresetSetting("$PostFX::EnableChromaticAberrationPostFX::Enabled");
   PostFXManager::savePresetSetting("$PostFX::EnableChromaticAberrationPostFX::DistCoefficient");
   PostFXManager::savePresetSetting("$PostFX::EnableChromaticAberrationPostFX::CubeDistortionFactor");
   PostFXManager::savePresetSetting("$PostFX::EnableChromaticAberrationPostFX::ColorDistFactor");
}

//Our actual postFX
singleton PostEffect( ChromaticAberrationPostFX )
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
   shader = ChromaticAberrationPostFX_Shader;
   stateBlock = PFX_DefaultStateBlock;
   texture[0] = "$backBuffer";
   target = "$backBuffer";
   targetFormat = "GFXFormatR16G16B16A16F"; 
   targetScale = "1 1";
};
