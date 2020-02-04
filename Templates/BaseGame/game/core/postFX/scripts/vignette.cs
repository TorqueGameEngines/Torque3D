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

$VignettePostEffect::VMax = 0.6;
$VignettePostEffect::VMin = 0.2;

singleton ShaderData( VignetteShader )
{   
   DXVertexShaderFile 	= $Core::CommonShaderPath @ "/postFX/postFxV.hlsl";
   DXPixelShaderFile 	= $Core::CommonShaderPath @ "/postFX/vignette/VignetteP.hlsl";
   
   OGLVertexShaderFile  = $Core::CommonShaderPath @ "/postFX/gl/postFxV.glsl";
   OGLPixelShaderFile   = $Core::CommonShaderPath @ "/postFX/vignette/gl/VignetteP.glsl";
   
   samplerNames[0] = "$backBuffer";
   
   pixVersion = 2.0;
};

function vignettePostFX::onAdd( %this )
{   
   PostFXManager.registerPostEffect(%this);
}

singleton PostEffect( vignettePostFX )  
{  
   isEnabled         = false;
   allowReflectPass  = false;
   renderTime        = "PFXAfterBin";
   renderBin         = "GlowBin";
   shader            = VignetteShader;
   stateBlock        = PFX_DefaultStateBlock;
   texture[0]        = "$backBuffer";
   renderPriority    = 10;
};

function vignettePostFX::setShaderConsts(%this)
{
   %this.setShaderConst("$Vmax", $VignettePostEffect::VMax);
   %this.setShaderConst("$Vmin", $VignettePostEffect::VMin);
}

function vignettePostFX::populatePostFXSettings(%this)
{
   PostEffectEditorInspector.startGroup("General");
   PostEffectEditorInspector.addField("$PostFXManager::Settings::EnableVignette", "Enabled", "bool", "", $PostFXManager::PostFX::EnableVignette, "");
   PostEffectEditorInspector.addField("$PostFXManager::Settings::VignettePostEffect::VMin", "Vignette Min", "float", "", $VignettePostEffect::VMin, "");
   PostEffectEditorInspector.addField("$PostFXManager::Settings::VignettePostEffect::VMax", "Vignette Max", "float", "", $VignettePostEffect::VMax, "");
   PostEffectEditorInspector.endGroup();
}

function vignettePostFX::applyFromPreset(%this)
{
   //Light rays settings
   $PostFXManager::PostFX::EnableLightRays = $PostFXManager::Settings::EnableLightRays;
   $LightRayPostFX::brightScalar           = $PostFXManager::Settings::LightRays::brightScalar;
   
   $LightRayPostFX::numSamples            = $PostFXManager::Settings::LightRays::numSamples;
   $LightRayPostFX::density               = $PostFXManager::Settings::LightRays::density;
   $LightRayPostFX::weight                = $PostFXManager::Settings::LightRays::weight;
   $LightRayPostFX::decay                 = $PostFXManager::Settings::LightRays::decay;
   
   if($PostFXManager::PostFX::EnableVignette)
      %this.enable();
   else
      %this.disable();
}

function vignettePostFX::settingsApply(%this)
{
   $PostFXManager::Settings::EnableLightRays                = $PostFXManager::PostFX::EnableLightRays;
   $PostFXManager::Settings::LightRays::brightScalar        = $LightRayPostFX::brightScalar;
   
   $PostFXManager::Settings::LightRays::numSamples          = $LightRayPostFX::numSamples;
   $PostFXManager::Settings::LightRays::density             = $LightRayPostFX::density;
   $PostFXManager::Settings::LightRays::weight              = $LightRayPostFX::weight;
   $PostFXManager::Settings::LightRays::decay               = $LightRayPostFX::decay;
}