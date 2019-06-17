// PIXELATE
$Pixelate::PixelWidth  = 10.0;
$Pixelate::PixelHeight = 10.0;
singleton ShaderData( PixelateShader )
{   
   DXVertexShaderFile 	= "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/Library/pixelateP.hlsl";
   pixVersion = 2.0;
};

singleton PostEffect( PixelatePostEffect )  
{  
   isEnabled         = false;
   allowReflectPass  = false;
   renderTime        = "PFXAfterBin";
   renderBin         = "GlowBin";
   shader            = PixelateShader;
   stateBlock        = PFX_DefaultStateBlock;
   texture[0]        = "$backBuffer";
   renderPriority    = 10;
};

function PixelatePostEffect::setShaderConsts(%this)
{
   %this.setShaderConst("$pixel_w", $Pixelate::PixelWidth);
   %this.setShaderConst("$pixel_h", $Pixelate::PixelHeight);
   %this.setShaderConst("$sizeX",getWord($pref::Video::mode, 0));
   %this.setShaderConst("$sizeY",getWord($pref::Video::mode, 1));
}

// BLURRED VISION
$BlurredVisionIntensity = 1.0;
singleton ShaderData( BlurredVisionShader )
{   
   DXVertexShaderFile 	= "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/Library/blurredVisionP.hlsl";
   pixVersion = 2.0;
};

singleton PostEffect( BlurredVisionPostEffect )  
{  
   isEnabled         = false;
   allowReflectPass  = false;
   renderTime        = "PFXAfterBin";
   renderBin         = "GlowBin";
   shader            = BlurredVisionShader;
   stateBlock        = PFX_DefaultStateBlock;
   texture[0]        = "$backBuffer";
   renderPriority    = 10;
};

function BlurredVisionPostEffect::setShaderConsts(%this)
{
   %this.setShaderConst("$BlurredVisionIntensity", $BlurredVisionIntensity);
}

// DREAM VIEW
$DreamViewIntensity = 1.0;
singleton ShaderData( DreamViewShader )
{   
   DXVertexShaderFile 	= "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/Library/dreamviewP.hlsl";
   pixVersion = 2.0;
};

singleton PostEffect( DreamViewPostEffect )  
{  
   isEnabled         = false;
   allowReflectPass  = false;
   renderTime        = "PFXAfterBin";
   renderBin         = "GlowBin";
   shader            = DreamViewShader;
   stateBlock        = PFX_DefaultStateBlock;
   texture[0]        = "$backBuffer";
   renderPriority    = 10;
};

function DreamViewPostEffect::setShaderConsts(%this)
{
   %this.setShaderConst("$DreamViewIntensity", $DreamViewIntensity);
}

// CROSS STITCH
$CrossStichPostEffect::StitchingSize = 6.0;
$CrossStichPostEffect::Invert = 0;
singleton ShaderData( CrossStitchShader )
{   
   DXVertexShaderFile 	= "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/Library/crossStitchP.hlsl";
   pixVersion = 3.0;
};

singleton PostEffect( CrossStitchPostEffect )  
{  
   isEnabled         = false;
   allowReflectPass  = false;
   renderTime        = "PFXAfterBin";
   renderBin         = "GlowBin";
   shader            = CrossStitchShader;
   stateBlock        = PFX_DefaultStateBlock;
   texture[0]        = "$backBuffer";
   renderPriority    = 10;
};

function CrossStitchPostEffect::setShaderConsts(%this)
{
   %this.setShaderConst( "$time", ($Sim::time - %this.timeStart) );
   %this.setShaderConst("$sizeX",getWord($pref::Video::mode, 0));
   %this.setShaderConst("$sizeY",getWord($pref::Video::mode, 1));
   %this.setShaderConst("$stitching_size", $CrossStichPostEffect::StitchingSize);
   %this.setShaderConst("$invert", $CrossStichPostEffect::Invert);
}

// POSTERISATION
$PosterisationPostEffect::Gamma     = 0.6;
$PosterisationPostEffect::NumColors = 4.0;
singleton ShaderData( PosterisationShader )
{   
   DXVertexShaderFile 	= "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/Library/posterisationP.hlsl";
   pixVersion = 2.0;
};

singleton PostEffect( PosterisationPostEffect )  
{  
   isEnabled         = false;
   allowReflectPass  = false;
   renderTime        = "PFXAfterBin";
   renderBin         = "GlowBin";
   shader            = PosterisationShader;
   stateBlock        = PFX_DefaultStateBlock;
   texture[0]        = "$backBuffer";
   renderPriority    = 10;
};

function PosterisationPostEffect::setShaderConsts(%this)
{
   %this.setShaderConst("$gamma", $PosterisationPostEffect::Gamma);
   %this.setShaderConst("$numColors", $PosterisationPostEffect::NumColors);
}

// NIGHT VISION 2
$NightVisionPostEffect::LuminanceThreshold = 0.2;
$NightVisionPostEffect::ColorAmplification = 4.0;

singleton ShaderData( NightVision2Shader )
{   
   DXVertexShaderFile 	= "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/Library/nightVision2P.hlsl";
   pixVersion = 2.0;
};

singleton PostEffect( NightVision2Fx )  
{  
   isEnabled         = false;
   allowReflectPass  = false;
   renderTime        = "PFXAfterBin";
   renderBin         = "GlowBin";
   shader            = NightVision2Shader;
   stateBlock        = PFX_DefaultStateBlock;
   texture[0]        = "$backBuffer";
   renderPriority    = 10;  
};

function NightVision2Fx::setShaderConsts(%this)
{
   %this.setShaderConst("$luminanceThreshold", $NightVisionPostEffect::LuminanceThreshold);
   %this.setShaderConst("$colorAmplification", $NightVisionPostEffect::ColorAmplification);
}

// LENS CIRCLE
$LensCirclePostEffect::RadiusX = 0.6;
$LensCirclePostEffect::RadiusY = 0.2;

singleton ShaderData( LensCircleShader )
{   
   DXVertexShaderFile 	= "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/Library/lensCircleP.hlsl";
   pixVersion = 2.0;
};

singleton PostEffect( LensCirclePostEffect )  
{  
   isEnabled         = false;
   allowReflectPass  = false;
   renderTime        = "PFXAfterBin";
   renderBin         = "GlowBin";
   shader            = LensCircleShader;
   stateBlock        = PFX_DefaultStateBlock;
   texture[0]        = "$backBuffer";
   renderPriority    = 10;
};

function LensCirclePostEffect::setShaderConsts(%this)
{
   %this.setShaderConst("$radiusX", $LensCirclePostEffect::RadiusX);
   %this.setShaderConst("$radiusY", $LensCirclePostEffect::RadiusY);
}

// CHROMATIC ABERRATION
$ChromaticAberrationPostEffect::Intensity = 0.3;
singleton ShaderData( ChromaticAberrationShader )
{   
   DXVertexShaderFile 	= "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/Library/chromaticAberrationP.hlsl";
   pixVersion = 2.0;
};

singleton PostEffect( ChromaticAberrationPostEffect )  
{  
   isEnabled         = false;
   allowReflectPass  = false;
   renderTime        = "PFXAfterBin";
   renderBin         = "GlowBin";
   shader            = ChromaticAberrationShader;
   stateBlock        = PFX_DefaultStateBlock;
   texture[0]        = "$backBuffer";
   renderPriority    = 10;
};

function ChromaticAberrationPostEffect::setShaderConsts(%this)
{
   %this.setShaderConst("$intensity", $ChromaticAberrationPostEffect::Intensity);
}

// RGB
$RGBPostEffect::RedLevel   = 1.0;
$RGBPostEffect::GreenLevel = 1.0;
$RGBPostEffect::BlueLevel  = 1.0;
singleton ShaderData( RGBShader )
{   
   DXVertexShaderFile 	= "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/Library/rgbP.hlsl";
   pixVersion = 2.0;
};

singleton PostEffect( RGBPostEffect )  
{  
   isEnabled         = false;
   allowReflectPass  = false;
   renderTime        = "PFXAfterBin";
   renderBin         = "GlowBin";
   shader            = RGBShader;
   stateBlock        = PFX_DefaultStateBlock;
   texture[0]        = "$backBuffer";
   renderPriority    = 10;
};

function RGBPostEffect::setShaderConsts(%this)
{
   %this.setShaderConst("$redLevel", $RGBPostEffect::RedLevel);
   %this.setShaderConst("$greenLevel", $RGBPostEffect::GreenLevel);
   %this.setShaderConst("$blueLevel", $RGBPostEffect::BlueLevel);
}

// ZOOM BLUR
$ZoomBlur::Amount  = 0.99;
$ZoomBlur::Samples = 6;

singleton ShaderData( ZoomBlurShader )
{   
   DXVertexShaderFile 	= "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/Library/zoomBlurP.hlsl";
   samplerNames[0]      = "$inputTex";
   pixVersion           = 3.0;
};

singleton PostEffect( ZoomBlurPostEffect )  
{  
   renderTime  = "PFXAfterDiffuse";
   shader      = ZoomBlurShader;
   stateBlock  = PFX_DefaultStateBlock;
   texture[0]  = "$backBuffer";
};

function ZoomBlurPostEffect::setShaderConsts(%this)
{
   %this.setShaderConst("$amount", $ZoomBlur::Amount);
   %this.setShaderConst("$samples", $ZoomBlur::Samples);
}

// NEGATIVE
singleton ShaderData( NegativeShader )
{   
   DXVertexShaderFile 	= "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/Library/negativeP.hlsl";
   pixVersion = 2.0;
};

singleton PostEffect( NegativePostEffect )  
{  
   renderTime  = "PFXAfterDiffuse";
   shader      = NegativeShader;
   stateBlock  = PFX_DefaultStateBlock;
   texture[0]  = "$backBuffer";
};

// BLACK AND WHITE
singleton ShaderData( BlackAndWhiteShader )
{   
   DXVertexShaderFile 	= "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/Library/blackAndWhiteP.hlsl";
   pixVersion = 2.0;
};

singleton PostEffect( BlackAndWhitePostEffect )  
{  
   renderTime  = "PFXAfterDiffuse";
   shader      = BlackAndWhiteShader;
   stateBlock  = PFX_DefaultStateBlock;
   texture[0]  = "$backBuffer";
};

// MONOCHROME
singleton ShaderData( MonochromeShader )
{   
   DXVertexShaderFile 	= "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/Library/monochromeP.hlsl";
   pixVersion = 2.0;
};

singleton PostEffect( MonochromePostEffect )  
{  
   renderTime  = "PFXAfterDiffuse";
   shader      = MonochromeShader;
   stateBlock  = PFX_DefaultStateBlock;
   texture[0]  = "$backBuffer";
};

// EDGE DETECTION
$EdgeDetection::Threshold = 0.01;

singleton ShaderData( EdgeDetectionShader )
{   
   DXVertexShaderFile 	= "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/Library/edgeDetectionP.hlsl";
   pixVersion = 2.0;
};

singleton PostEffect( EdgeDetectionPostEffect )  
{  
   renderTime  = "PFXAfterDiffuse";
   shader      = EdgeDetectionShader;
   stateBlock  = PFX_DefaultStateBlock;
   texture[0]  = "$backBuffer";
};

function EdgeDetectionPostEffect::setShaderConsts(%this)
{
   %this.setShaderConst("$threshold", $EdgeDetection::Threshold);
}