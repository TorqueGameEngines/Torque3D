//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------
    
new ScriptObject( VPostEffectToggleEventPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    Parent      = "VEventPropertyList";
    
    Group[0]    = "VPostEffectToggleEvent";
    Field[0, 0] = "Action";
    Type[0, 0]  = "ToggleEnum";
};