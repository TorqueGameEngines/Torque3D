function toggleProbeViz(%mode)
{
   setLightingMode("ReflectionsOnly");
   
   $Probes::showAttenuation = 0;
   $Probes::showSpecularCubemaps = 0;
   $Probes::showDiffuseCubemaps = 0;
   $Probes::showProbeContrib = 0;
         
   switch$(%mode)
   {
      case "Attenuation":
         $Probes::showAttenuation = 1;
      case "Contribution":
         $Probes::showProbeContrib = 1;
      case "Specular":
         $Probes::showSpecularCubemaps = 1;
      case "Diffuse":
         $Probes::showDiffuseCubemaps = 1;
   }
}

function disableProbeViz()
{
   setLightingMode("Lit");
   toggleProbeViz(-1);
}