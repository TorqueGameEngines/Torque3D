//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------
    
new ScriptObject( VLightObjectAnimationEventPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    Parent      = "VEventDPropertyList";
    
    Group[0]    = "VLightObjectAnimationEvent";
    Field[0, 0] = "AnimationData";
    Type[0, 0]  = "VLightAnimationDataEnum";
};

//-----------------------------------------------------------------------------

function VLightObjectAnimationEvent::Refresh( %this, %trackContainer )
{
    // Create Control.
    %eventButton = Parent::Refresh( %this, %trackContainer );
    
    // Reference Label.
    %eventButton.LabelField = "AnimationData";
    
    // Add Field Notify.
    %this.AddFieldNotify( "AnimationData", %eventButton );
    
    // Return Button.
    return %eventButton;
}

function VLightObjectAnimationEvent::OnFieldChange( %this, %fieldName, %oldValue, %newValue )
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
        case "AnimationData" : %parent.Update();
    }
}