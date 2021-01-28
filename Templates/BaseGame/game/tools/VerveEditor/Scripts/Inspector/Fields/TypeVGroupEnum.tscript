//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditor::CreateVGroupEnumField( %fieldContainer, %fieldName )
{
    // Create Enum Menu.
    return VerveEditor::CreateEnumField( %fieldContainer, %fieldName, "VEditorVGroupEnumPropertyField" );
}

function VEditorVGroupEnumPropertyField::OnWake( %this )
{
    // Clear List.
    %this.clear();

    // Iterate Over Groups.
    %groupSet   = $VerveEditor::Controller;
    %groupCount = %groupSet.getCount();
    for ( %i = 0; %i < %groupCount; %i++ )
    {
        // Add Item.
        %this.add( %groupSet.getObject( %i ).Label, %i );
    }
    
    // Sort.
    %this.sort();
}