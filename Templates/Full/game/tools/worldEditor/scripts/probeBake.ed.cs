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
   %probeIds = parseMissionGroupForIds("ReflectionProbe", "");
   %skylightIds = parseMissionGroupForIds("Skylight", "");
   
   %probeIds = rtrim(ltrim(%probeIds SPC %skylightIds));
   %probeCount = getWordCount(%probeIds);
   
   %numIter = ProbeBakeDlg_NumIterTxt.getText();
   %resolution = ProbeBakeDlg_ProbeResList.getText();
   %progressStep = 100 / (%numIter * %probeCount);
   %currentProgressValue = 0;
   
   ProbeBakeDlg_Progress.setValue(%currentProgressValue);
   
   for(%iter=0; %iter < %numIter; %iter++)
   {
      for(%i=0; %i < %probeCount; %i++)
      {
         %probe = getWord(%probeIds, %i);
         
         %path = filePath($Server::MissionFile) @ "/" @ fileBase($Server::MissionFile) @ "/probes/";
         %probe.bake(%path, %resolution);
         
         %currentProgressValue += %progressStep;
         ProbeBakeDlg_Progress.setValue(%currentProgressValue);
         Canvas.repaint();
      }
   }
   
   EWorldEditor.isDirty = true;
}