//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------
    
new ScriptObject( VShapeAnimationEventPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    Parent      = "VEventDPropertyList";
    
    Group[0]    = "VShapeAnimationEvent";
    Field[0, 0] = "AnimationData";
    Type[0, 0]  = "VShapeAnimationEnum";
    Field[0, 1] = "AutoDuration";
};

//-----------------------------------------------------------------------------

function VShapeAnimationEvent::Refresh( %this, %trackContainer )
{
    // Create Control.
    %eventButton = Parent::Refresh( %this, %trackContainer );
    
    // Reference Label.
    %eventButton.LabelField = "AnimationData";
    
    // Add Field Notify.
    %this.AddFieldNotify( "AnimationData", %eventButton );
    %this.AddFieldNotify( "AutoDuration",  %eventButton );
    
    // Return Button.
    return %eventButton;
}

function VShapeAnimationEvent::OnFieldChange( %this, %fieldName, %oldValue, %newValue )
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
        
        case "AutoDuration"  : %parent.Update();
        
        case "TriggerTime"   : %parent.Update();
    }
}