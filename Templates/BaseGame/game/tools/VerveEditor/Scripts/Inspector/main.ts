//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditor::InitInspectorScripts()
{
    exec( "./Controls.ts" );
    exec( "./CutCopyPaste.ts" );
    exec( "./EventNotify.ts" );
    exec( "./Factory.ts" );
    exec( "./FactoryControls.ts" );
    exec( "./FieldNotify.ts" );
    exec( "./Lists.ts" );
    exec( "./Properties.ts" );
    exec( "./Selection.ts" );
    
    exec( "./Fields/main.ts" );
}
VerveEditor::InitInspectorScripts();