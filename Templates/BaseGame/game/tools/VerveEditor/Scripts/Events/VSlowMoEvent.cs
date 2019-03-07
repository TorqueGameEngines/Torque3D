//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------
    
new ScriptObject( VSlowMoEventPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    Parent      = "VEventDPropertyList";
    
    Group[0]    = "VSlowMoEvent";
    Field[0, 0] = "TimeScale";
};