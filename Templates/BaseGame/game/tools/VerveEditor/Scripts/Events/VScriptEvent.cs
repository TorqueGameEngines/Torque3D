//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------
    
new ScriptObject( VScriptEventPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    Parent      = "VEventPropertyList";
    
    Group[0]    = "VScriptEvent";
    Field[0, 0] = "CommandType";
    Type[0, 0]  = "VCommandEnum";
    Field[0, 1] = "Command";
};