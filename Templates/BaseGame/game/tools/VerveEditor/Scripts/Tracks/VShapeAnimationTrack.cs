//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

new ScriptObject( VShapeAnimationTrackPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    Parent      = "VObjectPropertyList";
    
    Group[0]    = "VShapeAnimationTrack";
    Field[0, 0] = "ThreadIndex";
};

//-----------------------------------------------------------------------------

function VShapeAnimationTrack::Refresh( %this )
{
    // Create Control.
    %trackControl = Parent::Refresh( %this );
    
    // Add Field Notify.
    VObject::AddFieldNotify( $VerveEditor::Controller, "Duration", %this );
    
    // Object Reference Notify.
    VObject::AddFieldNotify( %this.getParent(), "Reference", %this );
    
    // Return Control.
    return %trackControl;
}

function VShapeAnimationTrack::CreateEvent( %this )
{
    // Create Event.
    return new VShapeAnimationEvent();
}

//-------------------------------------------------------------------------

function VShapeAnimationTrack::Update( %this )
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