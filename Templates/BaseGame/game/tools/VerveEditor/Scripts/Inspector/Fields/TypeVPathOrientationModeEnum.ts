//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditor::CreateVPathOrientationModeEnumField( %fieldContainer, %fieldName )
{
    // Create Enum Menu.
    %fieldInput = VerveEditor::CreateEnumField( %fieldContainer, %fieldName, "VEditorVPathOrientationModeEnumPropertyField" );
    
    // Populate Menu.
    %fieldInput.add( "FREE",        0 );
    %fieldInput.add( "INTERPOLATE", 1 );
    %fieldInput.add( "TOOBJECT",    2 );
    %fieldInput.add( "TOPATH",      3 );
    %fieldInput.add( "TOPOINT",     4 );
    
    return %fieldInput;
}