//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditor::InitInspectorScripts()
{
    exec( "./Controls.cs" );
    exec( "./CutCopyPaste.cs" );
    exec( "./EventNotify.cs" );
    exec( "./Factory.cs" );
    exec( "./FactoryControls.cs" );
    exec( "./FieldNotify.cs" );
    exec( "./Lists.cs" );
    exec( "./Properties.cs" );
    exec( "./Selection.cs" );
    
    exec( "./Fields/main.cs" );
}
VerveEditor::InitInspectorScripts();