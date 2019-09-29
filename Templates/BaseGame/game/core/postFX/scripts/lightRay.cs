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


$LightRayPostFX::brightScalar = 0.75;
$LightRayPostFX::numSamples = 40;
$LightRayPostFX::density = 0.94;
$LightRayPostFX::weight = 5.65;
$LightRayPostFX::decay = 1.0;
$LightRayPostFX::exposure = 0.0005;
$LightRayPostFX::resolutionScale = 1.0;

function LightRayPostFX::onAdd( %this )
{   
   PostFXManager.registerPostEffect(%this);
}

singleton ShaderData( LightRayOccludeShader )
{
   DXVertexShaderFile 	= $Core::CommonShaderPath @ "/postFX/postFxV.hlsl";
   DXPixelShaderFile 	= $Core::CommonShaderPath @ "/postFX/lightRay/lightRayOccludeP.hlsl";
   
   OGLVertexShaderFile  = $Core::CommonShaderPath @ "/postFX/gl/postFxV.glsl";
   OGLPixelShaderFile   = $Core::CommonShaderPath @ "/postFX/lightRay/gl/lightRayOccludeP.glsl";
   
   samplerNames[0] = "$backBuffer";
   samplerNames[1] = "$deferredTex";

   pixVersion = 3.0;   
};

singleton ShaderData( LightRayShader )
{
   DXVertexShaderFile 	= $Core::CommonShaderPath @ "/postFX/postFxV.hlsl";
   DXPixelShaderFile 	= $Core::CommonShaderPath @ "/postFX/lightRay/lightRayP.hlsl";
   
   OGLVertexShaderFile  = $Core::CommonShaderPath @ "/postFX/gl/postFxV.glsl";
   OGLPixelShaderFile   = $Core::CommonShaderPath @ "/postFX/lightRay/gl/lightRayP.glsl";
   
   samplerNames[0] = "$frameSampler";
   samplerNames[1] = "$backBuffer";

   pixVersion = 3.0;   
};

singleton GFXStateBlockData( LightRayStateBlock : PFX_DefaultStateBlock )
{
   samplersDefined = true;
   samplerStates[0] = SamplerClampLinear;
   samplerStates[1] = SamplerClampLinear;     
};

singleton PostEffect( LightRayPostFX )
{
   //isEnabled = false;
   allowReflectPass = false;
        
   renderTime = "PFXBeforeBin";
   renderBin = "EditorBin";
   renderPriority = 10;
      
   shader = LightRayOccludeShader;
   stateBlock = LightRayStateBlock;
   texture[0] = "$backBuffer";
   texture[1] = "#deferred";
   target = "$outTex";
   targetFormat = "GFXFormatR16G16B16A16F";
      
   new PostEffect()
   {
      shader = LightRayShader;
      stateBlock = LightRayStateBlock;
      internalName = "final";
      texture[0] = "$inTex";
      texture[1] = "$backBuffer";
      target = "$backBuffer";
   };
};

function LightRayPostFX::preProcess( %this )
{   
   %this.targetScale = $LightRayPostFX::resolutionScale SPC $LightRayPostFX::resolutionScale;
}

function LightRayPostFX::setShaderConsts( %this )
{
   %this.setShaderConst( "$brightScalar", $LightRayPostFX::brightScalar );
   
   %pfx = %this-->final;
   %pfx.setShaderConst( "$numSamples", $LightRayPostFX::numSamples );
   %pfx.setShaderConst( "$density", $LightRayPostFX::density );
   %pfx.setShaderConst( "$weight", $LightRayPostFX::weight );
   %pfx.setShaderConst( "$decay", $LightRayPostFX::decay );
   %pfx.setShaderConst( "$exposure", $LightRayPostFX::exposure );
}

function LightRayPostFX::populatePostFXSettings(%this)
{
   PostEffectEditorInspector.startGroup("Light Ray");
   PostEffectEditorInspector.addField("$PostFXManager::Settings::EnableLightRays", "Enabled", "bool", "", $PostFXManager::PostFX::EnableLightRays, "");
   PostEffectEditorInspector.addField("$PostFXManager::Settings::LightRays::brightScalar", "Brightness", "float", "", $LightRayPostFX::brightScalar, "");
   PostEffectEditorInspector.addField("$PostFXManager::Settings::LightRays::numSamples", "Samples", "float", "", $LightRayPostFX::numSamples, "");
   PostEffectEditorInspector.addField("$PostFXManager::Settings::LightRays::density", "Density", "float", "", $LightRayPostFX::density, "");
   PostEffectEditorInspector.addField("$PostFXManager::Settings::LightRays::weight", "Weight", "float", "", $LightRayPostFX::weight, "");
   PostEffectEditorInspector.addField("$PostFXManager::Settings::LightRays::decay", "Decay", "float", "", $LightRayPostFX::decay, "");
   PostEffectEditorInspector.endGroup();
}

function LightRayPostFX::applyFromPreset(%this)
{
   //Light rays settings
   $PostFXManager::PostFX::EnableLightRays = $PostFXManager::Settings::EnableLightRays;
   $LightRayPostFX::brightScalar           = $PostFXManager::Settings::LightRays::brightScalar;
   
   $LightRayPostFX::numSamples            = $PostFXManager::Settings::LightRays::numSamples;
   $LightRayPostFX::density               = $PostFXManager::Settings::LightRays::density;
   $LightRayPostFX::weight                = $PostFXManager::Settings::LightRays::weight;
   $LightRayPostFX::decay                 = $PostFXManager::Settings::LightRays::decay;
   
   if($PostFXManager::PostFX::EnableLightRays)
      %this.enable();
   else
      %this.disable();
}

function LightRayPostFX::settingsApply(%this)
{
   $PostFXManager::Settings::EnableLightRays                = $PostFXManager::PostFX::EnableLightRays;
   $PostFXManager::Settings::LightRays::brightScalar        = $LightRayPostFX::brightScalar;
   
   $PostFXManager::Settings::LightRays::numSamples          = $LightRayPostFX::numSamples;
   $PostFXManager::Settings::LightRays::density             = $LightRayPostFX::density;
   $PostFXManager::Settings::LightRays::weight              = $LightRayPostFX::weight;
   $PostFXManager::Settings::LightRays::decay               = $LightRayPostFX::decay;
}