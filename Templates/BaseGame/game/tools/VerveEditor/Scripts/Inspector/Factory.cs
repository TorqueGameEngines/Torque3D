//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditor::AddGroup( %groupType )
{
    if ( !isObject( $VerveEditor::Controller ) )
    {
        // No Controller.
        return;
    }
    
    if ( %groupType $= "" )
    {
        // Default.
        %groupType = "VGroup";
    }
    
    /*
    // Add Template Group.
    VerveEditor::AddTemplateGroup( $VerveEditor::TemplateFolder @ "/" @ %groupType @ ".vsf" );
    */
    
    // Get the Name of the Target Group.
    VerveEditorGroupBuilderGUI.Build( %groupType, "VerveEditor::_AddGroup" );
}

function VerveEditor::_AddGroup( %groupType, %groupLabel )
{
    // Group History Actions.
    VerveEditor::ToggleHistoryGroup();
    
    // Create the Group.
    %groupObject = new ( %groupType )();
    
    // Add to Group.
    $VerveEditor::Controller.addObject( %groupObject );
    
    // Apply the Label.
    %groupObject.setLabelUnique( %groupLabel );
    
    // Callback.
    if ( !%groupObject.OnAdd() )
    {
        // Remove Object.
        $VerveEditor::Controller.removeObject( %groupObject );
        
        // Delete Object.
        %groupObject.delete();
        
        // Finish Up.
        VerveEditor::ToggleHistoryGroup();
        
        return;
    }
    
    // Resolve the Field Stack.
    %groupObject.ResolveBuildStack( VerveEditorGroupBuilderFieldStack );
    
    // Finish Up.
    VerveEditor::ToggleHistoryGroup();
    
    // Refresh Editor.
    VerveEditor::Refresh();
    
    // Set Selection.
    VerveEditor::SetSelection( %groupObject.Control );
}

function VerveEditor::AddTemplateGroup( %templateFile )
{
    if ( !isObject( $VerveEditor::Controller ) || !isFile( %templateFile ) )
    {
        // No Controller.
        return;
    }
    
    // Fetch Current Count.
    %groupCount = $VerveEditor::Controller.getCount();
    
    // Group History Actions.
    VerveEditor::ToggleHistoryGroup();
    
    // Load Template.
    $VerveEditor::Controller.readTemplate( %templateFile );
    
    // Finish Up.
    VerveEditor::ToggleHistoryGroup();
    
    %newCount   = $VerveEditor::Controller.getCount();
    if ( %groupCount != %newCount )
    {
        if ( %newCount > %groupCount )
        {
            // Select New Object.
            %selectedObject = $VerveEditor::Controller.getObject( %newCount - 1 );
        }
        
        // Refresh Editor.
        VerveEditor::Refresh();
        
        if ( isObject( %selectedObject ) )
        {
            // Set Selection.
            VerveEditor::SetSelection( %selectedObject.Control );
        }
    }
}

function VerveEditor::AddTrack( %trackType, %targetGroup, %refresh )
{
    if ( !isObject( $VerveEditor::Controller ) )
    {
        // No Controller.
        return;
    }
    
    if ( !isObject( %targetGroup ) )
    {
        if ( !isObject( $VerveEditor::InspectorObject ) )
        {
            // No Controller or Selection.
            return;
        }
        
        // Use Current Selection.
        %targetGroup = $VerveEditor::InspectorObject;
    }
    
    if ( !%targetGroup.isMemberOfClass( "VGroup" ) )
    {
        // Invalid Target.
        return;
    }
    
    if ( %trackType $= "" )
    {
        // Default.
        %trackType = "VTrack";
    }
    
    // Create Track.
    %trackObject = new ( %trackType )();
    
    // Add to Group.
    %targetGroup.addObject( %trackObject );
    
    // Refresh Label.
    %trackObject.setLabelUnique( %trackObject.Label );
    
    // Callback.
    if ( !%trackObject.OnAdd() )
    {
        // Remove Object.
        %targetGroup.removeObject( %trackObject );
        
        // Delete Object.
        %trackObject.delete();
        
        // Return.
        return 0;
    }
    
    if ( %refresh $= "" || %refresh == true )
    {
        // Refresh.
        VerveEditor::Refresh();
        
        // Select New Object.
        VerveEditor::SetSelection( %trackObject.Control );
    }
    
    // Return Track.
    return %trackObject;
}

function VerveEditor::AddEvent( %targetTrack, %targetTime, %refresh )
{
    if ( !isObject( $VerveEditor::Controller ) )
    {
        // No Controller.
        return;
    }
    
    if ( !isObject( %targetTrack ) )
    {
        if ( !isObject( $VerveEditor::InspectorObject ) )
        {
            // No Controller or Selection.
            return;
        }
        
        // Use Current Selection.
        %targetTrack = $VerveEditor::InspectorObject;
    }
    
    if ( !%targetTrack.isMemberOfClass( "VTrack" ) )
    {
        // Invalid Target.
        return;
    }
    
    // Create Event.
    %eventObject = %targetTrack.CreateEvent();
    if ( !isObject( %eventObject ) )
    {
        // Return.
        return;
    }
    
    // Add to Track.
    %targetTrack.addObject( %eventObject );
    
    if ( %targetTime $= "" )
    {
        // User Controller Time.
        %targetTime = $VerveEditor::Controller.Time;
    }
    
    // Apply Time.
    %eventObject.SnapToTime( %targetTime, true );
    
    // Callback.
    if ( !%eventObject.OnAdd() )
    {
        // Remove Object.
        %targetTrack.removeObject( %eventObject );
        
        // Delete Object.
        %eventObject.delete();
        
        // Return.
        return 0;
    }
    
    if ( %refresh $= "" || %refresh == true )
    {
        // Refresh.
        VerveEditor::Refresh();
        
        // Select Existing Track.
        VerveEditor::SetSelection( %targetTrack.Control );
    }
    
    // Return Event.
    return %eventObject;
}