//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditor::CreateVLightAnimationDataEnumField( %fieldContainer, %fieldName )
{
    // Create Enum List.
    %fieldInput = VerveEditor::CreateEnumField( %fieldContainer, %fieldName );
    
    // Populate Enum.
    %fieldInput.PopulateFromDatablockGroup( "LightAnimData" );

    return %fieldInput;
}