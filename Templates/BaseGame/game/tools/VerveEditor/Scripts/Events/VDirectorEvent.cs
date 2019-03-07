//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------
    
new ScriptObject( VDirectorEventPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    Parent      = "VEventPropertyList";
    
    Group[0]    = "VDirectorEvent";
    Field[0, 0] = "Label";
    Field[0, 1] = "Target";
    Type[0, 1]  = "VCameraGroupEnum";
};

//-----------------------------------------------------------------------------

function VDirectorEvent::onRemove( %this )
{
    // Schedule Update.
    %this.getParent().schedule( 0, "update" );
}

function VDirectorEvent::Refresh( %this, %trackContainer )
{
    // Create Control.
    %eventButton = Parent::Refresh( %this, %trackContainer );
    
    // Reference Label.
    %eventButton.LabelField = "EventLabel";
    
    // Add Field Notify.
    %this.AddFieldNotify( "EventLabel", %eventButton );
    
    // Update Label.
    %this.UpdateLabel();
}

function VDirectorEvent::OnFieldChange( %this, %fieldName, %oldValue, %newValue )
{
    // Parent Callback.
    Parent::OnFieldChange( %this, %fieldName, %oldValue, %newValue );
    
    // Fetch Parent.
    %parent = %this.getParent();
    if ( !isObject( %parent ) )
    {
        return;
    }
    
    switch$( %fieldName )
    {
        case "TriggerTime" : %parent.Update();

        case "Duration"    : %parent.Update();
        
        case "Target"      : %this.UpdateLabel();
        
        case "Label"       : %this.UpdateLabel();
    }
}

function VDirectorEvent::UpdateLabel( %this )
{
    // Valid Target Camera?
    %targetLabel = %this.Target;
    if ( %targetLabel $= "" )
    {
        %targetLabel = "Invalid Target";
    }
    
    // Valid Scene Label?
    if ( %this.Label !$= "" )
    {
        %eventLabel = %this.Label @ ": " @ %targetLabel;
    }
    else
    {
        %eventLabel = %targetLabel;
    }
    
    // Set Value.
    %this.setFieldValue( "EventLabel", %eventLabel );
}

function VDirectorEvent::getSnapTime( %this, %targetTime )
{
    // Don't Snap to Other Events.
    
    if ( $VerveEditor::Event::SnapTime > 0 )
    {
        // Snap.
        return mRound( %targetTime, $VerveEditor::Event::SnapTime );
    }
    
    // No Snap!
    return %targetTime;
}