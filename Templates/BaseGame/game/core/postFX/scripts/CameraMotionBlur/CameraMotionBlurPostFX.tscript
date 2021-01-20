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

$PostFX::CameraMotionBlurPostFX::samples = 5;
$PostFX::CameraMotionBlurPostFX::velocityMultiplier = 3000;

singleton ShaderData( CameraMotionBlurPostFX_Shader )
{
   DXVertexShaderFile 	= $Core::CommonShaderPath @ "/postFX/postFxV.hlsl";
   DXPixelShaderFile 	= "./CameraMotionBlurPostFXP.hlsl";   
   OGLVertexShaderFile  = $Core::CommonShaderPath @ "/postFX/gl/postFxV.glsl";
   OGLPixelShaderFile   = "./CameraMotionBlurPostFXP.glsl";
   
   samplerNames[0] = "$backBuffer";
   samplerNames[1] = "$deferredTex";
   
   pixVersion = 3.0;
};

singleton GFXStateBlockData( CameraMotionBlurPostFX_StateBlock )
{
   zDefined = true;
   zEnable = false;
   zWriteEnable = false;
      
   samplersDefined = true;
   samplerStates[0] = SamplerClampLinear;
};


function CameraMotionBlurPostFX::setShaderConsts( %this )
{
   %this.setShaderConst( "$velocityMultiplier", $PostFX::CameraMotionBlurPostFX::velocityMultiplier );
   %this.setShaderConst( "$samples", $PostFX::CameraMotionBlurPostFX::samples );
}

function CameraMotionBlurPostFX::preProcess( %this )
{
}

function CameraMotionBlurPostFX::onAdd(%this)
{
   //Register the postFX with the manager
   PostFXManager.registerPostEffect(%this);
}

function CameraMotionBlurPostFX::onEnabled( %this )
{
   return true;
}

function CameraMotionBlurPostFX::onDisabled( %this )
{
   return true;
}

//This is used to populate the PostFXEditor's settings so the post FX can be edited
//This is automatically polled for any postFX that has been registered(in our onAdd) and the settings
//are thus exposed for editing
function CameraMotionBlurPostFX::populatePostFXSettings(%this)
{
   PostEffectEditorInspector.startGroup("CameraMotionBlurPostFX - General");
   PostEffectEditorInspector.addCallbackField("$PostFX::CameraMotionBlurPostFX::Enabled", "Enabled", "bool", "", $PostFX::CameraMotionBlurPostFX::Enabled, "", "toggleCameraMotionBlurPostFX");
   PostEffectEditorInspector.addField("$PostFX::CameraMotionBlurPostFX::velocityMultiplier", "Velocity Multiplier", "float", "", $PostFX::CameraMotionBlurPostFX::velocityMultiplier, "");
   PostEffectEditorInspector.addField("$PostFX::CameraMotionBlurPostFX::samples", "Sample Count", "float", "", $PostFX::CameraMotionBlurPostFX::samples, "");
   PostEffectEditorInspector.endGroup();
}

//This is called back from our callbackField defined in populatePostFXSettings to
//Allow us to easily toggle the postFX and have it respond immediately
function PostEffectEditorInspector::toggleCameraMotionBlurPostFX(%this)
{
   if($PostFX::CameraMotionBlurPostFX::Enabled)
      CameraMotionBlurPostFX.enable();
   else
      CameraMotionBlurPostFX.disable();
}

function CameraMotionBlurPostFX::applyFromPreset(%this)
{
   if($PostFX::CameraMotionBlurPostFX::Enabled)
      %this.enable();
   else
      %this.disable();
}

function CameraMotionBlurPostFX::savePresetSettings(%this)
{
   PostFXManager::savePresetSetting("$PostFX::CameraMotionBlurPostFX::Enabled");
   PostFXManager::savePresetSetting("$PostFX::CameraMotionBlurPostFX::velocityMultiplier");
   PostFXManager::savePresetSetting("$PostFX::CameraMotionBlurPostFX::samples");
}

//Our actual postFX
singleton PostEffect( CameraMotionBlurPostFX )
{
   enabled = false;
   renderTime = "PFXAfterDiffuse"; 

   shader = CameraMotionBlurPostFX_Shader;
   stateBlock = CameraMotionBlurPostFX_StateBlock;
   texture[0] = "$backbuffer";
   texture[1] = "#deferred";
   target = "$backBuffer";
};
