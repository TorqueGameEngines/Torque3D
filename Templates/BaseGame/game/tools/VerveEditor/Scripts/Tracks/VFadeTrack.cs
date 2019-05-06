//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

new ScriptObject( VFadeTrackPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    Parent      = "VObjectPropertyList";
};

//-----------------------------------------------------------------------------

function VFadeTrack::CreateEvent( %this )
{
    // Create Event.
    return new VFadeEvent();
}

function VFadeTrack::Refresh( %this )
{
    // Create Control.
    %trackControl = Parent::Refresh( %this );
    
    // Update Labels.
    %this.Update();
    
    // Return Track.
    return %trackControl;
}

function VFadeTrack::Update( %this )
{
    %eventCount = %this.getCount();
    for ( %i = 0; %i < %eventCount; %i++ )
    {
        %eventObject = %this.getObject( %i );
        %eventButton = %eventObject.Control;
        
        // Set The Label.
        %eventButton.Text = ( ( %i % 2 )  == 0 ) ? "Fade In" : "Fade Out";
    }
}