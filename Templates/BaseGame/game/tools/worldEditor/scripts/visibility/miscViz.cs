singleton GFXStateBlockData( Viz_DefaultVisualizeState )
{
   /*alphaDefined = true;
   alphaTestEnable = true;
   alphaTestRef = 1;
   alphaTestFunc = GFXCmpGreaterEqual;
         
   // Do a one to one blend.
   blendDefined = true;
   blendEnable = true;
   blendSrc = GFXBlendOne;
   blendDest = GFXBlendOne;
   
   zDefined = true;
   zEnable = false;
   zWriteEnable = false;
   
   samplersDefined = true;
   samplerStates[0] = SamplerClampPoint;
   samplerStates[1] = SamplerClampPoint;
   samplerStates[2] = SamplerClampPoint;
   samplerStates[3] = SamplerClampPoint;
   samplerStates[4] = SamplerClampLinear;
   samplerStates[5] = SamplerClampLinear;*/
   blendDefined = true;
   blendEnable = true;
   blendSrc = GFXBlendSrcAlpha;
   blendDest = GFXBlendInvSrcAlpha;
   
   zDefined = true;
   zEnable = false;
   zWriteEnable = false;

   samplersDefined = true;
   samplerStates[0] = SamplerClampPoint;   // #deferred
   samplerStates[1] = SamplerClampPoint;
   samplerStates[2] = SamplerClampPoint;
   samplerStates[3] = SamplerClampLinear;  // depthviz
   samplerStates[4] = SamplerClampLinear;  // depthviz
};

singleton shaderData( Viz_TexelDensity )
{
   DXVertexShaderFile = $Core::CommonShaderPath @ "/postFX/postFxV.hlsl";
   DXPixelShaderFile  = "./shaders/Viz_TexelDensityP.hlsl";
   
   OGLVertexShaderFile = $Core::CommonShaderPath @ "/postFX/gl/postFxV.glsl";
   OGLPixelShaderFile  = "./shaders/Viz_TexelDensityP.glsl";

   pixVersion = 2.0;
};

singleton PostEffect( Viz_TexelDensityPFX )
{   
   shader = Viz_TexelDensity;
   stateBlock = AL_DefaultVisualizeState;
   texture[0] = "tools/resources/checkerboard";
   target = "$backBuffer";
   renderPriority = 9999;
};

/// Toggles the visualization of the AL lighting specular power buffer.
function toggleTexelDensityViz( %enable )
{   
   if ( %enable $= "" )
   {
      $Viz_TexelDensityVar = Viz_TexelDensityPFX.isEnabled() ? false : true;
      Viz_TexelDensityPFX.toggle();
   }
   else if ( %enable )
   {
      Viz_TexelDensityPFX.enable();
   }
   else if ( !%enable )
   {
      Viz_TexelDensityPFX.disable();    
   }
}

//
//
singleton shaderData( Viz_SurfaceProperties )
{
   DXVertexShaderFile = $Core::CommonShaderPath @ "/postFX/postFxV.hlsl";
   DXPixelShaderFile  = "./shaders/Viz_SurfacePropertiesP.hlsl";
   
   OGLVertexShaderFile = $Core::CommonShaderPath @ "/postFX/gl/postFxV.glsl";
   OGLPixelShaderFile  = "./shaders/Viz_SurfacePropertiesP.glsl";
   
   samplerNames[0] = "$deferredBuffer";
   samplerNames[1] = "$colorBuffer";
   samplerNames[2] = "$matInfoBuffer";
   samplerNames[3] = "$ssaoMaskTex";
   samplerNames[4] = "$backbufferTex";
   samplerNames[5] = "$glowBuffer";

   pixVersion = 2.0;
};

singleton PostEffect( Viz_SurfacePropertiesPFX )
{   
   shader = Viz_SurfaceProperties;
   stateBlock = Viz_DefaultVisualizeState;
   texture[0] = "#deferred";
   texture[1] = "#color";
   texture[2] = "#matinfo";
   texture[3] = "#ssaoMask";
   texture[4] = "$backBuffer";
   texture[5] = "#glowbuffer";
   
   target = "$backBuffer";
   renderPriority = 9999;
   
   renderTime = "PFXBeforeBin";
   renderBin = "ObjTranslucentBin"; 
};

function toggleDebugVizMode( %mode )
{
   switch$ ( %mode )
   {
      case "All Materials":
         $Viz_DisplayMode = "0";
      case "Forward Materials Only":
         $Viz_DisplayMode = "1";
      case "Deferred Materials Only":
         $Viz_DisplayMode = "2"; 
      default:
         $Viz_DisplayMode = "0";
   }
   
   if($Viz_DisplayMode == 1)
   {
      Viz_SurfacePropertiesPFX.disable(); 
   }
   else
   {
      if($Viz_SurfacePropertiesModeVar !$= "" && $Viz_SurfacePropertiesModeVar != -1)
         Viz_SurfacePropertiesPFX.enable(); 
   }
   
   for(%i=0; %i < 3; %i++)
   {
      if(%i == $Viz_DisplayMode)
         EBufferVizModeOptions.checkItem(%i, true);
      else
         EBufferVizModeOptions.checkItem(%i, false);
   }
   
   //forces the forward materials to get dis viz properly
   reInitMaterials();
}

/// Toggles the visualization of the AL lighting specular power buffer.
function toggleSurfacePropertiesViz( %mode )
{   
   %previousMode = $Viz_SurfacePropertiesModeVar;
   
   switch$ ( %mode )
   {
      case "BaseColor":
         $Viz_SurfacePropertiesModeVar = "0";
      case "Normal":
         $Viz_SurfacePropertiesModeVar = "1";
      case "AO":
         $Viz_SurfacePropertiesModeVar = "2";   
      case "Roughness":
         $Viz_SurfacePropertiesModeVar = "3";
      case "Metalness":
         $Viz_SurfacePropertiesModeVar = "4";
      case "Depth":
         $Viz_SurfacePropertiesModeVar = "5";
      case "DiffuseColor":
         $Viz_SurfacePropertiesModeVar = "6";
      case "SpecularColor":
         $Viz_SurfacePropertiesModeVar = "7";   
      case "MatFlag":
         $Viz_SurfacePropertiesModeVar = "8";
      case "WorldPos":
         $Viz_SurfacePropertiesModeVar = "9";
      case "ReflectionVector":
         $Viz_SurfacePropertiesModeVar = "10";
      case "Fresnel":
         $Viz_SurfacePropertiesModeVar = "11";
      case "SSAO":
         $Viz_SurfacePropertiesModeVar = "12";
      case "Backbuffer":
         $Viz_SurfacePropertiesModeVar = "13";
      case "Glow":
         $Viz_SurfacePropertiesModeVar = "14";
      default:
         $Viz_SurfacePropertiesModeVar = "-1";
   }
   
   if($Viz_DisplayMode == 1)
   {
      Viz_SurfacePropertiesPFX.disable(); 
   }
   else
   {
      //If the visualizer isn't enabled, we just flip it on
      if(!Viz_SurfacePropertiesPFX.isEnabled())
      {
         Viz_SurfacePropertiesPFX.enable();  
      }
      else //if it's currently enabled, check if we clicked the same mode again. If so, disable. If not, just swap modes to the new one
      {
         if(%previousMode == $Viz_SurfacePropertiesModeVar)
         {
            $Viz_SurfacePropertiesModeVar = -1;
            Viz_SurfacePropertiesPFX.disable(); 
         }
      }
   }
   
   for(%i=0; %i < 15; %i++)
   {
      if(%i == $Viz_SurfacePropertiesModeVar)
         EVisibilityBufferVizOptions.checkItem(%i+1, true);
      else
         EVisibilityBufferVizOptions.checkItem(%i+1, false);
   }
   
   //forces the forward materials to get dis viz properly
   reInitMaterials();
}

function Viz_SurfacePropertiesPFX::setShaderConsts(%this)
{
   %this.setShaderConst("$mode", $Viz_SurfacePropertiesModeVar);
}

function disableSurfacePropertiesViz()
{
   Viz_SurfacePropertiesPFX.disable();
   $Viz_SurfacePropertiesModeVar = -1;
   
   for(%i=0; %i < 14; %i++)
   {
      EVisibilityBufferVizOptions.checkItem(%i, false);
   }  
}

function Viz_SurfacePropertiesPFX::onEnabled( %this )
{
   //Disable the buffer visualization
   disableColorblindnessViz();
   
   return true;
}

//
//
//
singleton shaderData( Viz_ColorBlindness )
{
   DXVertexShaderFile = $Core::CommonShaderPath @ "/postFX/postFxV.hlsl";
   DXPixelShaderFile  = "./shaders/Viz_ColorblindnessP.hlsl";

   OGLVertexShaderFile = $Core::CommonShaderPath @ "/postFX/gl/postFxV.glsl";
   OGLPixelShaderFile  = "./shaders/Viz_ColorblindnessP.glsl";
   
   samplerNames[0] = "$backBuffer";
   
   pixVersion = 2.0;
};

singleton PostEffect( Viz_ColorBlindnessPFX )
{   
   isEnabled         = false;
   allowReflectPass  = false;
   renderTime        = "PFXAfterBin";
   renderBin         = "GlowBin";
   
   shader = Viz_ColorBlindness;
   stateBlock = PFX_DefaultStateBlock;
   texture[0] = "$backBuffer";
   
   target = "$backBuffer";
   renderPriority    = 10;
};

function toggleColorblindnessViz( %mode )
{   
   %previousMode = $Viz_ColorblindnessModeVar;
   
   switch$ ( %mode )
   {
      case "Protanopia":
         $Viz_ColorblindnessModeVar = "0";
      case "Protanomaly":
         $Viz_ColorblindnessModeVar = "1";
      case "Deuteranopia":
         $Viz_ColorblindnessModeVar = "2";   
      case "Deuteranomaly":
         $Viz_ColorblindnessModeVar = "3";
      case "Tritanopia":
         $Viz_ColorblindnessModeVar = "4";
      case "Tritanomaly":
         $Viz_ColorblindnessModeVar = "5";
      case "Achromatopsia":
         $Viz_ColorblindnessModeVar = "6";
      case "Achromatomaly":
         $Viz_ColorblindnessModeVar = "7";   
      default:
         $Viz_ColorblindnessModeVar = "-1";
   }
   
   //If the visualizer isn't enabled, we just flip it on
   if(!Viz_ColorBlindnessPFX.isEnabled())
   {
      Viz_ColorBlindnessPFX.enable();  
   }
   else //if it's currently enabled, check if we clicked the same mode again. If so, disable. If not, just swap modes to the new one
   {
      if(%previousMode == $Viz_ColorblindnessModeVar)
      {
         $Viz_ColorblindnessModeVar = -1;
         Viz_ColorBlindnessPFX.disable(); 
      }
   }
   
   for(%i=0; %i < 8; %i++)
   {
      if(%i == $Viz_ColorblindnessModeVar)
         EVisibilityColorblindnessOptions.checkItem(%i, true);
      else
         EVisibilityColorblindnessOptions.checkItem(%i, false);
   }
}

function Viz_ColorBlindnessPFX::setShaderConsts(%this)
{
   %this.setShaderConst("$mode", $Viz_ColorblindnessModeVar);
}

function disableColorblindnessViz()
{
   Viz_ColorBlindnessPFX.disable();
   $Viz_ColorblindnessModeVar = -1;
   
   for(%i=0; %i < 8; %i++)
   {
      EVisibilityColorblindnessOptions.checkItem(%i, false);
   }
}

function Viz_ColorBlindnessPFX::onEnabled( %this )
{
   //Disable the buffer visualization
   disableSurfacePropertiesViz();
   
   return true;
}


//
//Material Complexity Viz
singleton shaderData( Viz_MaterialComplexity )
{
   DXVertexShaderFile   = "./shaders/Viz_materialComplexityV.hlsl";
   DXPixelShaderFile    = "./shaders/Viz_materialComplexityP.hlsl";
 
   OGLVertexShaderFile   = "./shaders/basicRibbonShaderV.glsl";
   OGLPixelShaderFile    = "./shaders/basicRibbonShaderP.glsl";
 
   //samplerNames[0] = "$ribTex";
 
   pixVersion = 2.0;
};
 
singleton CustomMaterial( Viz_MaterialComplexityMat )
{
   shader = Viz_MaterialComplexity;
   version = 2.0;
   
   emissive[0] = true;
   
   doubleSided = true;
   translucent = true;
   
   preload = true;
};

function toggleMatComplexityViz()
{
   if(!isObject(MatComplexityVizBin))
      DiffuseRenderPassManager.addManager( new MaterailComplexityVisualizerBin(MatComplexityVizBin) { renderOrder = 1.55; processAddOrder = 1.55; } );
      
   MatComplexityVizBin.material = Viz_MaterialComplexityMat;
   MatComplexityVizBin.maxComplexity = 10;
}

//
//
function toggleVolumeViz(%vizName)
{
   if(%vizName $= "Zones")
   {
      $Zone::isRenderable = !$Zone::isRenderable;
      EVisibilityVolumeOptions.checkItem(0, $Zone::isRenderable);
   }
   else if(%vizName $= "Portals")
   {
      $Portal::isRenderable = !$Portal::isRenderable;
      EVisibilityVolumeOptions.checkItem(1, $Portal::isRenderable);
   }
   else if(%vizName $= "Occlusion")
   {
      $OcclusionVolume::isRenderable = !$OcclusionVolume::isRenderable;
      EVisibilityVolumeOptions.checkItem(2, $OcclusionVolume::isRenderable);
   }
   else if(%vizName $= "Triggers")
   {
      $Trigger::renderTriggers = !$Trigger::renderTriggers;
      EVisibilityVolumeOptions.checkItem(3, $Trigger::renderTriggers);
   }
   else if(%vizName $= "PhysicalZone")
   {
      $PhysicalZone::renderZones = !$PhysicalZone::renderZones;
      EVisibilityVolumeOptions.checkItem(4, $PhysicalZone::renderZones);
   }
   else if(%vizName $= "SoundEmitters")
   {
      $SFXEmitter::renderEmitters = !$SFXEmitter::renderEmitters;
      EVisibilityVolumeOptions.checkItem(5, $SFXEmitter::renderEmitters);
   }
   else if(%vizName $= "MissionArea")
   {
      EWorldEditor.renderMissionArea = !EWorldEditor.renderMissionArea;
      EVisibilityVolumeOptions.checkItem(6, EWorldEditor.renderMissionArea);
   }
   else if(%vizName $= "SoundSpaces")
   {
      $SFXSpace::isRenderable = !$SFXSpace::isRenderable;
      EVisibilityVolumeOptions.checkItem(7, $SFXSpace::isRenderable);
   }
}