//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------
    
new ScriptObject( VFadeEventPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    Parent      = "VEventDPropertyList";
};

//-----------------------------------------------------------------------------

function VFadeEvent::OnFieldChange( %this, %fieldName, %oldValue, %newValue )
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
    }
}