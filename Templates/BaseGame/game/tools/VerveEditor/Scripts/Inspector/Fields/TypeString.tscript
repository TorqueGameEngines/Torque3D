//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditor::CreateStringField( %fieldContainer, %fieldName )
{
    %fieldWidth = getWord( %fieldContainer.getExtent(), 0 );
    
    %fieldInput = new GuiTextEditCtrl()
    {
        Class        = "VEditorStringPropertyField";
        InternalName = "FieldControl";
        Profile      = "VEditorTextEditProfile";
        
        HorizSizing  = "left";
        VertSizing   = "center";
        Position     = %fieldWidth - 156 SPC 0;
        Extent       = "150 18";
        
        AltCommand   = "$ThisControl.ApplyValue();";
        Validate     = "$ThisControl.ApplyValue();";
        
        // Store Field Properties.
        FieldName   = %fieldName;
    };
    %fieldContainer.add( %fieldInput );
    
    // Field Notify.
    VerveEditor::AddInspectorFieldNotify( %fieldName, %fieldInput );
    
    return %fieldInput;
}

function VEditorStringPropertyField::ApplyValue( %this )
{
    VEditorPropertyField::ApplyValue( %this, %this.FieldName, %this.getText() );
}

function VEditorStringPropertyField::Update( %this, %fieldName, %fieldValue )
{
    if ( %this.getText() !$= %fieldValue )
    {
        %this.setText( %fieldValue );
    }
}

function VEditorStringPropertyField::onGainFirstResponder( %this )
{
    // Disable Cut, Copy & Paste.
    VerveEditorEditMap.pop();
}

function VEditorStringPropertyField::onLoseFirstResponder( %this )
{
    // Enable Cut, Copy & Paste.
    VerveEditorEditMap.push();
}