//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditor::CreateVCameraGroupEnumField( %fieldContainer, %fieldName )
{
    // Create Enum Menu.
    return VerveEditor::CreateEnumField( %fieldContainer, %fieldName, "VEditorVCameraGroupEnumPropertyField" );
}

function VEditorVCameraGroupEnumPropertyField::OnWake( %this )
{
    // Clear List.
    %this.clear();

    // Iterate Over Groups.
    %groupSet   = $VerveEditor::Controller;
    %groupCount = %groupSet.getCount();
    for ( %i = 0; %i < %groupCount; %i++ )
    {
        %group = %groupSet.getObject( %i );
        if ( %group.isMemberOfClass( "VCameraGroup" ) )
        {
            // Add Item.
            %this.add( %group.Label, %i );
        }
    }
    
    // Sort.
    %this.sort();
}