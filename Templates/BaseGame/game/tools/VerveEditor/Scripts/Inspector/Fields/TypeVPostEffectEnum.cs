//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditor::CreateVPostEffectEnumField( %fieldContainer, %fieldName )
{
    // Create Enum List.
    %fieldInput = VerveEditor::CreateEnumField( %fieldContainer, %fieldName );
    
    // Populate Enum.
    %fieldInput.PopulateFromRootGroup( "PostEffect" );

    return %fieldInput;
}