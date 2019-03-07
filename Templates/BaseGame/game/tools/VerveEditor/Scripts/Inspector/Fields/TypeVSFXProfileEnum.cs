//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditor::CreateVSFXProfileEnumField( %fieldContainer, %fieldName )
{
    // Create Enum List.
    %fieldInput = VerveEditor::CreateEnumField( %fieldContainer, %fieldName );
    
    // Populate Enum.
    %fieldInput.PopulateFromDatablockGroup( "SFXProfile" );

    return %fieldInput;
}