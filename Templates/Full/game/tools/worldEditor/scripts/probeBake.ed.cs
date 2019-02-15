function ProbeBakeDlg::onWake(%this)
{
   //set up
   ProbeBakeDlg_ProbeResList.add( "32" );  
   ProbeBakeDlg_ProbeResList.add( "64" );
   ProbeBakeDlg_ProbeResList.add( "128" );
   ProbeBakeDlg_ProbeResList.add( "256" );
   ProbeBakeDlg_ProbeResList.add( "512" );
   ProbeBakeDlg_ProbeResList.add( "1024" );
   ProbeBakeDlg_ProbeResList.add( "2048" );
   
   ProbeBakeDlg_ProbeResList.setSelected( 1, false );
   
   ProbeBakeDlg_NumIterTxt.setText("1");
}

function ProbeBakeDlg_RunBake::onClick(%this)
{
   %boxProbeIds = parseMissionGroupForIds("BoxEnvironmentProbe", "");
   %sphereProbeIds = parseMissionGroupForIds("SphereEnvironmentProbe", "");
   %skylightIds = parseMissionGroupForIds("Skylight", "");
   
   %probeIds = rtrim(ltrim(%boxProbeIds SPC %sphereProbeIds));
   %probeIds = rtrim(ltrim(%probeIds SPC %skylightIds));
   %probeCount = getWordCount(%probeIds);
   
   %numIter = ProbeBakeDlg_NumIterTxt.getText();
   $pref::ReflectionProbes::BakeResolution = ProbeBakeDlg_ProbeResList.getText();
   %progressStep = 100 / (%numIter * %probeCount);
   %currentProgressValue = 0;
   
   ProbeBakeDlg_Progress.setValue(%currentProgressValue);
   Canvas.repaint();
   
   for(%iter=0; %iter < %numIter; %iter++)
   {
      $pref::ReflectionProbes::RenderWithProbes = false;
      
      if(%iter != 0)
         $pref::ReflectionProbes::RenderWithProbes = true;
         
      for(%i=0; %i < %probeCount; %i++)
      {
         %probe = getWord(%probeIds, %i);
         
         $pref::ReflectionProbes::CurrentLevelPath = filePath($Server::MissionFile) @ "/" @ fileBase($Server::MissionFile) @ "/probes/";
         ProbeBin.bakeProbe(%probe);
         
         %currentProgressValue += %progressStep;
         ProbeBakeDlg_Progress.setValue(%currentProgressValue);
         Canvas.repaint();
      }
   }
   
   EWorldEditor.isDirty = true;
}