//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditor::CreateBoolField( %fieldContainer, %fieldName )
{
    %fieldWidth = getWord( %fieldContainer.getExtent(), 0 );
    
    %fieldInput = new GuiCheckBoxCtrl()
    {
        Class        = "VEditorBoolPropertyField";
        InternalName = "FieldControl";
        Profile      = "VEditorCheckBoxProfile";
        
        HorizSizing  = "width";
        VertSizing   = "center";
        Position     = %fieldWidth - 156 SPC 0;
        Extent       = "150 18";
        
        Text         = "";
        
        Command      = "$ThisControl.ApplyValue();";
        
        // Store Field Properties.
        FieldName    = %fieldName;
    };
    %fieldContainer.add( %fieldInput );
    
    // Field Notify.
    VerveEditor::AddInspectorFieldNotify( %fieldName, %fieldInput );
    
    return %fieldInput;
}

function VEditorBoolPropertyField::ApplyValue( %this )
{
    VEditorPropertyField::ApplyValue( %this, %this.FieldName, %this.getValue() );
}

function VEditorBoolPropertyField::Update( %this, %fieldName, %fieldValue )
{
    if ( %this.getValue() !$= %fieldValue )
    {
        %this.setValue( %fieldValue );
    }
}