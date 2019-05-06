//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditor::CreateVControllerDataEnumField( %fieldContainer, %fieldName )
{
    // Create Enum Menu.
    return VerveEditor::CreateEnumField( %fieldContainer, %fieldName, "VEditorVControllerDataEnumPropertyField" );
}

function VEditorVControllerDataEnumPropertyField::OnWake( %this, %eventName )
{
    // Clear List.
    %this.clear();

    // Iterate Over Data Items.
    %dataObject     = $VerveEditor::Controller;
    %dataFieldCount = %dataObject.getDataFieldCount();
    for ( %i = 0; %i < %dataFieldCount; %i++ )
    {
        // Add Field Name.
        %this.add( %dataObject.getDataFieldName( %i ), %i );
    }
    
    // Sort.
    %this.sort();
}