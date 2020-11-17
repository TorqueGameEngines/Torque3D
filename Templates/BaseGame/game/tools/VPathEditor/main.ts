//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function InitializeVPathEditor()
{
    // Gui.
    exec( "./GUI/Profiles.ts" );
    exec( "./GUI/VPathEditor.gui" );
    
    // Scripts.
    exec( "./Scripts/Plugin.ts" );
    exec( "./Scripts/Editor.ts" );
}

function DestroyVPathEditor()
{
    // Void.
}
