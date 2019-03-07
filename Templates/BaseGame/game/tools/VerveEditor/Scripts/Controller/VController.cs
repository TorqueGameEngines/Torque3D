//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

new ScriptObject( VControllerPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    
    Group[0]    = "VController";
    Field[0, 0] = "Duration";
    Field[0, 1] = "TimeScale";
    
    Field[0, 2] = "SPACER 6";
    
    Field[0, 3] = "Loop";
    Field[0, 4] = "LoopBackwards";
    Field[0, 5] = "LoopCount";
    Field[0, 6] = "LoopDelay";
    
    Field[0, 7] = "SPACER 6";
    
    Field[0, 8] = "ResetOnCompletion";
};

//-----------------------------------------------------------------------------

function VerveEditor::TogglePlay()
{
    if ( !isObject( $VerveEditor::Controller ) )
    {
        // No Controller.
        return;
    }
    
    if ( !$VerveEditor::Controller.isPlaying() )
    {
        // Play.
        VerveEditor::Play();
    }
    else
    {
        // Pause.
        VerveEditor::Pause();
    }
}

function VerveEditor::Play()
{
    // Start Playing.
    $VerveEditor::Controller.play();
}

function VerveEditor::Pause()
{
    // Stop but do not Reset.
    $VerveEditor::Controller.stop( false );
}

function VerveEditor::StepF()
{
    // Determine the time to step towards.
    %time = mClamp( $VerveEditor::Controller.Time + ( 32 * $VerveEditor::Controller.TimeScale ), 0.0, $VerveEditor::Controller.Duration );
    // Reset.
    $VerveEditor::Controller.reset( %time );
}

function VerveEditor::StepB()
{
    // Switch TimeScale.
    $VerveEditor::Controller.TimeScale *= -1.0;
    // Step.
    VerveEditor::StepF();
    // Switch Back TimeScale.
    $VerveEditor::Controller.TimeScale *= -1.0;
}

function VerveEditor::Rewind()
{
    if ( $VerveEditor::Controller.TimeScale > 0 )
    {
        // Front.
        $VerveEditor::Controller.reset( 0 );
    }
    else
    {
        // Back.
        $VerveEditor::Controller.reset( $VerveEditor::Controller.Duration );
    }
}

function VerveEditor::Forward()
{
    if ( $VerveEditor::Controller.TimeScale < 0 )
    {
        // Front.
        $VerveEditor::Controller.reset( 0 );
    }
    else
    {
        // Back.
        $VerveEditor::Controller.reset( $VerveEditor::Controller.Duration );
    }
}

function VerveEditor::InsertTimeFront()
{
    %time   = 0;
    %length = 1000;
    
    VerveEditor::InsertTime( %time, %length );
}

function VerveEditor::InsertTimeBack()
{
    %time   = $VerveEditor::Controller.Duration;
    %length = 1000;
    
    VerveEditor::InsertTime( %time, %length );
}

function VerveEditor::InsertTime( %time, %length )
{
    if ( %length <= 0 )
    {
        return;
    }
    
    // Group History Actions.
    VerveEditor::ToggleHistoryGroup();
    
    // Increase Duration.
    $VerveEditor::Controller.setFieldValue( "Duration", $VerveEditor::Controller.Duration + %length );
    
    %groupSet   = $VerveEditor::Controller;
    %groupCount = %groupSet.getCount();
    for ( %i = 0; %i < %groupCount; %i++ )
    {
        %trackSet   = %groupSet.getObject( %i );
        %trackCount = %trackSet.getCount();
        for ( %j = 0; %j < %trackCount; %j++ )
        {
            %eventSet   = %trackSet.getObject( %j );
            %eventCount = %eventSet.getCount();
            for ( %k = 0; %k < %eventCount; %k++ )
            {
                %eventSet.getObject( %k ).InsertTime( %time, %length );
            }
        }
    }
    
    if ( %time < $VerveEditor::Controller.Time )
    {
        // Update Time.
        $VerveEditor::Controller.setFieldValue( "Time", $VerveEditor::Controller.Time + %length );
    }
    
    // Finish Up.
    VerveEditor::ToggleHistoryGroup();
}

function VerveEditor::DeleteTime( %time, %length )
{
    if ( %length <= 0 )
    {
        return;
    }
    
    // Group History Actions.
    VerveEditor::ToggleHistoryGroup();
    
    %groupSet   = $VerveEditor::Controller;
    %groupCount = %groupSet.getCount();
    for ( %i = 0; %i < %groupCount; %i++ )
    {
        %trackSet   = %groupSet.getObject( %i );
        %trackCount = %trackSet.getCount();
        for ( %j = 0; %j < %trackCount; %j++ )
        {
            %eventSet   = %trackSet.getObject( %j );
            %eventCount = %eventSet.getCount();
            for ( %k = 0; %k < %eventCount; %k++ )
            {
                %eventObject = %eventSet.getObject( %k );
                if ( %eventObject.DeleteTime( %time, %length ) )
                {
                    // Delete.
                    %eventObject.delete();
                    
                    // Backstep.
                    %k          -= 1;
                    %eventCount -= 1;
                }
            }
        }
    }
    
    // Decrease Duration.
    $VerveEditor::Controller.setFieldValue( "Duration", $VerveEditor::Controller.Duration - %length );
    
    if ( $VerveEditor::Controller.Time > %time && $VerveEditor::Controller.Time < ( %time + %length ) )
    {
        // Clamp.
        $VerveEditor::Controller.setFieldValue( "Time", %time );
    }
    else if ( $VerveEditor::Controller.Time >= ( %time + %length ) )
    {
        // Push Back.
        $VerveEditor::Controller.setFieldValue( "Time", $VerveEditor::Controller.Time - %length );
    }
    
    // Finish Up.
    VerveEditor::ToggleHistoryGroup();
    
    // Refresh Editor.
    VerveEditor::Refresh();
}

function VEvent::InsertTime( %this, %time, %length )
{
    %triggerTime     = %this.getFieldValue( "TriggerTime" );
    %triggerDuration = %this.getFieldValue( "Duration" );
    
    if ( %time <= %triggerTime )
    {
        %this.setFieldValue( "TriggerTime", %triggerTime + %length );
    }
    else if ( %time > %triggerTime && %time < %triggerTime + %triggerDuration )
    {
        %this.setFieldValue( "Duration", %triggerDuration + %length );
    }
}

function VEvent::DeleteTime( %this, %time, %length )
{
    %triggerTime     = %this.getFieldValue( "TriggerTime" );
    %triggerDuration = %this.getFieldValue( "Duration" );
    
    if ( %triggerTime >= %time && %triggerTime <= ( %time + %length ) )
    {
        %tail = ( %triggerTime + %triggerDuration ) - ( %time + %length );
        if ( %tail > 0 )
        {
            // Trim Duration.
            %this.setFieldValue( "TriggerTime", %time );
            %this.setFieldValue( "Duration",    %tail );
        }
        else
        {
            // Delete This Event.
            return true;
        }
    }
    else if ( %triggerTime > %time )
    {
        // Shuffle Back.
        %this.setFieldValue( "TriggerTime", %triggerTime - %length );
    }
    else if ( %triggerTime < %time && ( %triggerTime + %triggerDuration ) > %time )
    {
        // Trim Duration.
        %this.setFieldValue( "Duration", ( %triggerTime + %triggerDuration ) - %time );
    }
    
    // No Delete.
    return false;
}

//------------------------------------------------------------------------

function VerveEditorController::CanPaste( %this, %targetObject )
{
    if ( !isObject( %targetObject ) )
    {
        // Nope!
        return false;
    }
    
    if ( !%this.CanAdd( %targetObject.getClassName() ) )
    {
        // Nope!
        return false;
    }
    
    return %targetObject.isMemberOfClass( "VGroup" );
}

function VerveEditorController::CanAdd( %this, %targetClass )
{
    if ( !isWordInList( %targetClass, $VerveEditor::UniqueGroupList ) )
    {
        // Not a Unique Group.
        return true;
    }
    
    %groupCount = %this.getCount();
    for ( %i = 0; %i < %groupCount; %i++ )
    {
        %groupObject = %this.getObject( %i );
        if ( %groupObject.isMemberOfClass( %targetClass ) )
        {
            // Invalid.
            return false;
        }
    }
    
    // All Good.
    return true;
}

function VerveEditorController::onPlay( %this )
{
    // Update Play Button.
    VerveEditorPlayButton.setBitmap( "tools/VerveEditor/GUI/Images/btn_Pause" );
    
    // Start Update Event.
    VerveEditorTimeLine.ControllerUpdate();
}

function VerveEditorController::onPause( %this )
{
    // Update Play Button.
    VerveEditorPlayButton.setBitmap( "tools/VerveEditor/GUI/Images/btn_Play" );
    
    // Stop Update Event.
    VerveEditorTimeLine.StopUpdate();
}

function VerveEditorController::onStop( %this )
{
    // Update Play Button.
    VerveEditorPlayButton.setBitmap( "tools/VerveEditor/GUI/Images/btn_Play" );
    
    // Stop Update Event.
    VerveEditorTimeLine.StopUpdate();
}

function VerveEditorController::OnFieldChange( %this, %fieldName, %oldValue, %newValue )
{
    if ( !VerveEditorHistoryManager.Locked )
    {
        // Add History Item.
        %historyObject = new UndoScriptAction()
        {
            Class      = "VerveEditorHistoryChangeProperty";
            SuperClass = "VerveEditorHistoryObject";
            
            ActionName = "Change Property (" @ %fieldName @ ")";
            
            // Store References.
            Object    = %this;
            FieldName = %fieldName;
            OldValue  = %oldValue;
            NewValue  = %newValue;
        };
    }
    
    switch$ ( %fieldName )
    {
        case "Duration" : VerveEditor::UpdateDuration();
    }
}