//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

new ScriptObject( VDirectorTrackPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    Parent      = "VObjectPropertyList";
};

//-----------------------------------------------------------------------------

function VDirectorTrack::Refresh( %this )
{
    // Create Control.
    %trackControl = Parent::Refresh( %this );
    
    // Add Field Notify.
    VObject::AddFieldNotify( $VerveEditor::Controller, "Duration", %this );
    
    // Return Control.
    return %trackControl;
}

function VDirectorTrack::CreateEvent( %this )
{
    // Create Event.
    return new VDirectorEvent();
}

//-------------------------------------------------------------------------

function VDirectorTrack::Update( %this )
{
    // Root Update.
    %this.UpdateTrack();
    
    %trackControl = %this.Control.SiblingControl;
    if ( !isObject( %trackControl ) )
    {
        return;
    }
    
    // Update GUI Elements.
    %eventCount = %trackControl.getCount();
    for ( %i = 0; %i < %eventCount; %i++ )
    {
        // Get Control.
        %eventControl = %trackControl.getObject( %i );
        
        // Update.
        %eventControl.Update();
    }
}