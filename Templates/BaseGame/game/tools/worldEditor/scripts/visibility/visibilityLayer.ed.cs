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


//Volumes Visibility
   //Zones
   //Portals
   //Occlusion
   //Triggers
   //Physical
   //Sound
   //Mission Area
   //Sound Space
//Debug Rendering
   //Player Collision
   //Terrain
   //Decals
   //Bounding Boxes
   //Physics World
//Wireframe
//Frustum Lock
//Disable Zone Culling
//Disable Terrain Occlusion
//Lighting
  //Lighting Modes
    //Lit
    //Unlit(Full render, no reflecitons or lights)
    //No Shadows
    //Detail Lighting(diffuse is a flat gray, otherwise normal lighting)
    //Lighting Only(diffuse is flat, no normal, otherwise normal lighting)
    //Reflections(flat normal, roughness 0)
  //Probes
    //Attenuation
    //Contribution
    //Diffuse Reflections
    //Specular Reflections
  //Lights
    //Light Frustums
    //Shadowmap Cascades
//Buffer Viz
   //Base Color
   //Diffuse Color(Base + AO)
   //Material AO
   //Roughness
   //Depth
   //Specular Color(Base Color + metalness)
   //Metalness
   //Normal
   //Ambient Occlusion(posteffect)?
   //Backbuffer
   //Glow
//Colorblindness
   //All of them
//Class Visibility
function setupEditorVisibilityMenu()
{
   if(isObject(EditorVisibilityOptions))
      return;

   %volumeVizpopup = new PopupMenu(EVisibilityVolumeOptions)
   {
      superClass = "MenuBuilder";
      class = "EditorWorldMenu";
      
      item[ 0 ] = "Show Zones" TAB "" TAB "$Zone::isRenderable = !$Zone::isRenderable;";
      item[ 1 ] = "Show Portals" TAB "" TAB "$Portal::isRenderable = !$Portal::isRenderable;";
      item[ 2 ] = "Show Occlusion Volumes" TAB "" TAB "$OcclusionVolume::isRenderable = !$OcclusionVolume::isRenderable;";
      item[ 3 ] = "Show Triggers" TAB "" TAB "$Trigger::renderTriggers = !$Trigger::renderTriggers;";
      item[ 4 ] = "Show Physical Zones" TAB "" TAB "$PhysicalZone::renderZones = !$PhysicalZone::renderZones;";
      item[ 5 ] = "Show Sound Emitters" TAB "" TAB "$SFXEmitter::renderEmitters = !$SFXEmitter::renderEmitters;";
      item[ 6 ] = "Show Mission Area" TAB "" TAB "EWorldEditor.renderMissionArea = !EWorldEditor.renderMissionArea;";
      item[ 7 ] = "Show Sound Spaces" TAB "" TAB "$SFXSpace::isRenderable = !$SFXSpace::isRenderable;";
   };
   
   %debugRenderpopup = new PopupMenu(EVisibilityDebugRenderOptions)
   {
      superClass = "MenuBuilder";
      class = "EditorWorldMenu";
      
      item[ 0 ] = "Show Player Collision" TAB "" TAB "$Player::renderCollision != $Player::renderCollision;";
      item[ 1 ] = "Show Terrain Debug" TAB "" TAB "$TerrainBlock::debugRender != $TerrainBlock::debugRender;";
      item[ 2 ] = "Show Decals Debug" TAB "" TAB "$Decals::debugRender != $Decals::debugRender;";
      item[ 3 ] = "Show Bounding Boxes" TAB "" TAB "$Scene::renderBoundingBoxes != $Scene::renderBoundingBoxes;";
      item[ 4 ] = "Show Physics World" TAB "" TAB "$PhysicsWorld::render != $PhysicsWorld::render;";
      item[ 5 ] = "Show Player Collision" TAB "" TAB "";
      item[ 6 ] = "Show Texel Density" TAB "" TAB "toggleTexelDensityViz();";
   };
   
   %probespopup.enableItem(5, false);
   %probespopup.enableItem(6, false);
   
   //
   //Lighting stuff
   %lightingModepopup = new PopupMenu(EVisibilityLightingModesOptions)
   {
      superClass = "MenuBuilder";
      class = "EditorWorldMenu";
      
      item[ 0 ] = "Lit" TAB "" TAB "setLightingMode(\"Lit\");";
      item[ 1 ] = "Unlit" TAB "" TAB "setLightingMode(\"Unlit\");";
      item[ 2 ] = "No Shadows" TAB "" TAB "setLightingMode(\"NoShadows\");";
      item[ 3 ] = "Detail Lighting" TAB "" TAB "setLightingMode(\"DetailLighting\");";
      item[ 4 ] = "Lighting Only" TAB "" TAB "setLightingMode(\"LightingOnly\");";
      item[ 5 ] = "Reflections Only" TAB "" TAB "setLightingMode(\"ReflectionsOnly\");";
   };
   
   EVisibilityLightingModesOptions.checkItem(0, true);
   
   %lightspopup = new PopupMenu(EVisibilityLightsOptions)
   {
      superClass = "MenuBuilder";
      class = "EditorWorldMenu";
      
      item[ 0 ] = "Show Light Frustums" TAB "" TAB "toggleLightFrustumViz();";
      item[ 1 ] = "Show Shadowmap Cascades" TAB "" TAB "togglePSSMDebugViz();";
      item[ 2 ] = "Show Specular Light" TAB "" TAB "";
      item[ 3 ] = "Show Diffuse Light" TAB "" TAB "";
   };
   
   %lightspopup.enableItem(2, false);
   %lightspopup.enableItem(3, false);
   
   //
   //Probes
   %probespopup = new PopupMenu(EVisibilityProbesOptions)
   {
      superClass = "MenuBuilder";
      class = "EditorWorldMenu";
      
      item[ 0 ] = "Show Probe Attenuation" TAB "" TAB "toggleProbeViz(\"Attenuation\");";
      item[ 1 ] = "Show Probe Contribution" TAB "" TAB "toggleProbeViz(\"Contribution\");";
      item[ 2 ] = "Show Probe Specular Reflections Only" TAB "" TAB "toggleProbeViz(\"Specular\");";
      item[ 3 ] = "Show Probe Diffuse Reflections Only" TAB "" TAB "toggleProbeViz(\"Diffuse\");";
      item[ 4 ] = "Enable Live Updates on Selected Probe" TAB "" TAB "";
   };
   
   %probespopup.enableItem(4, false);
   
   //
   //Buffer Viz
   %bufferVizpopup = new PopupMenu(EVisibilityBufferVizOptions)
   {
      superClass = "MenuBuilder";
      class = "EditorWorldMenu";
      
      item[ 0 ] = "Base Color" TAB "" TAB "toggleSurfacePropertiesViz(\"BaseColor\");";
      item[ 1 ] = "Normals" TAB "" TAB "toggleSurfacePropertiesViz(\"Normal\");";
      item[ 2 ] = "Material Ambient Occlusion" TAB "" TAB "toggleSurfacePropertiesViz(\"AO\");";
      item[ 3 ] = "Roughness" TAB "" TAB "toggleSurfacePropertiesViz(\"Roughness\");";
      item[ 4 ] = "Metalness" TAB "" TAB "toggleSurfacePropertiesViz(\"Metalness\");";
      item[ 5 ] = "Depth" TAB "" TAB "toggleSurfacePropertiesViz(\"Depth\");";
      
      item[ 6 ] = "Diffuse Color" TAB "" TAB "toggleSurfacePropertiesViz(\"DiffuseColor\");";
      item[ 7 ] = "Specular Color" TAB "" TAB "toggleSurfacePropertiesViz(\"SpecularColor\");";
      item[ 8 ] = "Material Flags" TAB "" TAB "toggleSurfacePropertiesViz(\"MatFlag\");";
      
      item[ 9 ] = "World Position" TAB "" TAB "toggleSurfacePropertiesViz(\"WorldPos\");";
      item[ 10 ] = "Reflection Vector" TAB "" TAB "toggleSurfacePropertiesViz(\"ReflectionVector\");";
      
      item[ 11 ] = "Fresnel" TAB "" TAB "toggleSurfacePropertiesViz(\"Fresnel\");";
      
      item[ 12 ] = "Ambient Occlusion" TAB "" TAB "toggleSurfacePropertiesViz(\"SSAO\");";
      
      item[ 13 ] = "Backbuffer" TAB "" TAB "toggleSurfacePropertiesViz(\"Backbuffer\");";
      item[ 14 ] = "Glow" TAB "" TAB "toggleSurfacePropertiesViz(\"Glow\");";
   };
   
   //
   //Colorblindness
   %colorblindpopup = new PopupMenu(EVisibilityColorblindnessOptions)
   {
      superClass = "MenuBuilder";
      class = "EditorWorldMenu";
      
      item[ 0 ] = "Protanopia" TAB "" TAB "toggleColorblindnessViz(\"Protanopia\");";
      item[ 1 ] = "Protanomaly" TAB "" TAB "toggleColorblindnessViz(\"Protanomaly\");";
      item[ 2 ] = "Deuteranopia" TAB "" TAB "toggleColorblindnessViz(\"Deuteranopia\");";
      item[ 3 ] = "Deuteranomaly" TAB "" TAB "toggleColorblindnessViz(\"Deuteranomaly\");";
      item[ 4 ] = "Tritanopia" TAB "" TAB "toggleColorblindnessViz(\"Tritanopia\");";
      item[ 5 ] = "Tritanomaly" TAB "" TAB "toggleColorblindnessViz(\"Tritanomaly\");";
      item[ 6 ] = "Achromatopsia" TAB "" TAB "toggleColorblindnessViz(\"Achromatopsia\");";
      item[ 7 ] = "Achromatomaly" TAB "" TAB "toggleColorblindnessViz(\"Achromatomaly\");";
   };
   
   //
   //Class Visibility
   %classVizpopup = new PopupMenu(EVisibilityClassVizOptions)
   {
      superClass = "MenuBuilder";
      class = "EditorWorldMenu";
   };
   
   //addClassOptions(%classVizpopup);
   
   //
   %popup = new PopupMenu(EditorVisibilityOptions)
   {
      superClass = "MenuBuilder";
      class = "EditorWorldMenu";
      
      item[ 0 ] = "Volumes Visibility" TAB EVisibilityVolumeOptions;
      item[ 1 ] = "Debug Rendering" TAB EVisibilityDebugRenderOptions;
      item[ 2 ] = "-" TAB "" TAB "";
      item[ 3 ] = "Wireframe" TAB "" TAB "$gfx::wireframe = !$gfx::wireframe;";
      item[ 4 ] = "Frustum Lock" TAB "" TAB "$Scene::lockCull = !$Scene::lockCull;";
      item[ 5 ] = "Colorblindness" TAB EVisibilityColorblindnessOptions;
      item[ 6 ] = "-" TAB "" TAB "";
      item[ 7 ] = "Disable Zone Culling" TAB "" TAB "$Scene::disableZoneCulling = !$Scene::disableZoneCulling;";
      item[ 8 ] = "Disable Terrain Culling" TAB "" TAB "$Scene::disableTerrainOcclusion = !$Scene::disableTerrainOcclusion;";
      item[ 9 ] = "-" TAB "" TAB "";
      item[ 10 ] = "Lighting Modes" TAB EVisibilityLightingModesOptions;
      item[ 11 ] = "Lights" TAB EVisibilityLightsOptions;
      item[ 12 ] = "Probes" TAB EVisibilityProbesOptions;
      item[ 13 ] = "Buffer Visualization" TAB EVisibilityBufferVizOptions;
      item[ 14 ] = "-" TAB "" TAB "";
      item[ 15 ] = "Class Visibility" TAB EVisibilityClassVizOptions;
   };
}

function EVisibility::onWake( %this )
{
   // Create the array if it
   // doesn't already exist.
   if ( !isObject( %this.array ) )
      %this.array = new ArrayObject();

   // Create the array if it
   // doesn't already exist.
   if ( !isObject( %this.classArray ) )
   {
      %this.classArray = new ArrayObject();
      %this.addClassOptions();   
   }

   %this.updateOptions();

}

function EVisibility::updateOptions( %this )
{
   // First clear the stack control.
   %this-->theVisOptionsList.clear();   
    
   // Go through all the
   // parameters in our array and
   // create a check box for each.
   for ( %i = 0; %i < %this.array.count(); %i++ )
   {
      %text = "  " @ %this.array.getValue( %i );
      %val = %this.array.getKey( %i );
      %var = getWord( %val, 0 );
      %toggleFunction = getWord( %val, 1 );         
      
      %textLength = strlen( %text );
      
      %cmd = "";
      if ( %toggleFunction !$= "" )
         %cmd = %toggleFunction @ "( $thisControl.getValue() );";      
      
      %checkBox = new GuiCheckBoxCtrl()
      {
         canSaveDynamicFields = "0";
         isContainer = "0";
         Profile = "ToolsGuiCheckBoxListProfile";
         HorizSizing = "right";
         VertSizing = "bottom";
         Position = "0 0";
         Extent = (%textLength * 4) @ " 18";
         MinExtent = "8 2";
         canSave = "1";
         Visible = "1";
         Variable = %var;
         tooltipprofile = "ToolsGuiToolTipProfile";
         hovertime = "1000";
         text = %text;
         groupNum = "-1";
         buttonType = "ToggleButton";
         useMouseEvents = "0";
         useInactiveState = "0";
         Command = %cmd;
      };

      %this-->theVisOptionsList.addGuiControl( %checkBox );
   }   
}

function EVisibility::addOption( %this, %text, %varName, %toggleFunction )
{
   // Create the array if it
   // doesn't already exist.
   if ( !isObject( %this.array ) )
      %this.array = new ArrayObject();   
   
   %this.array.push_back( %varName @ " " @ %toggleFunction, %text );
   %this.array.uniqueKey();  
   %this.array.sortd(); 
   %this.updateOptions();
}

function EVisibility::addClassOptions( %this )
{
   %visList = %this-->theClassVisList;
   %selList = %this-->theClassSelList;
   
   // First clear the stack control.
   
   %visList.clear();
   %selList.clear();

   %classList = enumerateConsoleClasses( "SceneObject" );
   %classCount = getFieldCount( %classList );
   
   for ( %i = 0; %i < %classCount; %i++ )
   {
      %className = getField( %classList, %i );
      %this.classArray.push_back( %className );
   }
   
   // Remove duplicates and sort by key.
   %this.classArray.uniqueKey();
   %this.classArray.sortkd();
   
   // Go through all the
   // parameters in our array and
   // create a check box for each.
   for ( %i = 0; %i < %this.classArray.count(); %i++ )
   {
      %class = %this.classArray.getKey( %i );
      
      %visVar = "$" @ %class @ "::isRenderable";
      %selVar = "$" @ %class @ "::isSelectable";
      
      %textLength = strlen( %class );
      %text = "  " @ %class;
      
      // Add visibility toggle.
      
      %visCheckBox = new GuiCheckBoxCtrl()
      {
         canSaveDynamicFields = "0";
         isContainer = "0";
         Profile = "ToolsGuiCheckBoxListFlipedProfile";
         HorizSizing = "right";
         VertSizing = "bottom";
         Position = "0 0";
         Extent = (%textLength * 4) @ " 18";
         MinExtent = "8 2";
         canSave = "1";
         Visible = "1";
         Variable = %visVar;
         tooltipprofile = "ToolsGuiToolTipProfile";
         hovertime = "1000";
         tooltip = "Show/hide all " @ %class @ " objects.";
         text = %text;
         groupNum = "-1";
         buttonType = "ToggleButton";
         useMouseEvents = "0";
         useInactiveState = "0";
      };

      %visList.addGuiControl( %visCheckBox );

      // Add selectability toggle.
      
      %selCheckBox = new GuiCheckBoxCtrl()
      {
         canSaveDynamicFields = "0";
         isContainer = "0";
         Profile = "ToolsGuiCheckBoxListFlipedProfile";
         HorizSizing = "right";
         VertSizing = "bottom";
         Position = "0 0";
         Extent = (%textLength * 4) @ " 18";
         MinExtent = "8 2";
         canSave = "1";
         Visible = "1";
         Variable = %selVar;
         tooltipprofile = "ToolsGuiToolTipProfile";
         hovertime = "1000";
         tooltip = "Enable/disable selection of all " @ %class @ " objects.";
         text = %text;
         groupNum = "-1";
         buttonType = "ToggleButton";
         useMouseEvents = "0";
         useInactiveState = "0";
      };

      %selList.addGuiControl( %selCheckBox );
   }
}

function togglePhysicsDebugViz( %enable )
{
   if(physicsPluginPresent())
   {
      physicsDebugDraw(%enable);
   }
}

function disableVisualizers()
{
   //Set lighting mode to lit
   resetLightingMode();
         
   disableSurfacePropertiesViz();
   disableColorblindnessViz();
   disablePSSMDebugViz();
   disableLightingOnlyViz();
   disableReflectionsOnlyViz();
   disableProbeViz();
}