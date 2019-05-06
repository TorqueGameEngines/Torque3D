//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------
    
new ScriptObject( VSoundEffectEventPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    Parent      = "VEventPropertyList";
    
    Group[0]    = "VSoundEffectEvent";
    Field[0, 0] = "SoundEffect";
    Type[0, 0]  = "VSFXProfileEnum";
};

//-----------------------------------------------------------------------------

function VSoundEffectEvent::Refresh( %this, %trackContainer )
{
    // Create Control.
    %eventButton = Parent::Refresh( %this, %trackContainer );
    
    // Reference Label.
    %eventButton.LabelField = "SoundEffect";
    
    // Add Field Notify.
    %this.AddFieldNotify( "SoundEffect", %eventButton );
    
    // Return Button.
    return %eventButton;
}

function VSoundEffectEvent::OnFieldChange( %this, %fieldName, %oldValue, %newValue )
{
    switch$ ( %fieldName )
    {
        case "SoundEffect" : %this.NotifyFieldChange( "Duration", 0 );
    }
}