//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function InitializeVPathEditor()
{
    // Gui.
    exec( "./GUI/Profiles.cs" );
    exec( "./GUI/VPathEditor.gui" );
    
    // Scripts.
    exec( "./Scripts/Plugin.cs" );
    exec( "./Scripts/Editor.cs" );
}

function DestroyVPathEditor()
{
    // Void.
}
