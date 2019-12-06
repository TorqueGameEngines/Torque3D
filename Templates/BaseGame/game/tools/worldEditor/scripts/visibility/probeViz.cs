function toggleProbeViz(%mode)
{
   if($Probes::showAttenuation == 1)
      %lastMode = "Attenuation";
   else if($Probes::showProbeContrib == 1)
      %lastMode = "Contribution";
   else if($Probes::showSpecularCubemaps == 1)
      %lastMode = "Specular";
   else if($Probes::showDiffuseCubemaps == 1)
      %lastMode = "Diffuse";
   
   $Probes::showAttenuation = 0;
   $Probes::showSpecularCubemaps = 0;
   $Probes::showDiffuseCubemaps = 0;
   $Probes::showProbeContrib = 0;
   
   for(%i=0; %i < 4; %i++)
   {
      EVisibilityProbesOptions.checkItem(%i, false);
   }
   
   if(%mode $= %lastMode)
   {
      setLightingMode("Lit"); 
      
      //forces the forward materials to get dis viz properly
      reInitMaterials();
   
      return;
   }
   else
   {
      setLightingMode("ReflectionsOnly");  
      toggleLightViz(-1);
   }
         
   switch$(%mode)
   {
      case "Attenuation":
         $Probes::showAttenuation = 1;
         EVisibilityProbesOptions.checkItem(0, true);
      case "Contribution":
         $Probes::showProbeContrib = 1;
         EVisibilityProbesOptions.checkItem(1, true);
      case "Specular":
         $Probes::showSpecularCubemaps = 1;
         EVisibilityProbesOptions.checkItem(2, true);
      case "Diffuse":
         $Probes::showDiffuseCubemaps = 1;
         EVisibilityProbesOptions.checkItem(3, true);
   }
   
   //forces the forward materials to get dis viz properly
   reInitMaterials();
}

function disableProbeViz()
{
   setLightingMode("Lit");
   toggleProbeViz(-1);
}

function toggleProbeLiveUpdates()
{
   if($Probes::liveUpdates $= "")
      $Probes::liveUpdates = false;
      
   $Probes::liveUpdates = !$Probes::liveUpdates;
   
   EVisibilityProbesOptions.checkItem(5, $Probes::liveUpdates);
}