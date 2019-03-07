//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------
    
new ScriptObject( VParticleEffectToggleEventPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    Parent      = "VEventPropertyList";
    
    Group[0]    = "VParticleEffectToggleEvent";
    Field[0, 0] = "Action";
    Type[0, 0]  = "ToggleEnum";
};