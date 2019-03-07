//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditor::CreateDataField( %fieldContainer, %fieldName )
{
    %fieldWidth = getWord( %fieldContainer.getExtent(), 0 );
    
    %fieldType = new GuiPopUpMenuCtrl()
    {
        Class        = "VEditorDataTypePropertyField";
        Profile      = "VEditorPopupMenuProfile";
        
        HorizSizing  = "left";
        VertSizing   = "center";
        Position     = %fieldWidth - 72 SPC 0;
        Extent       = 44 SPC 18;
        
        Command      = "$ThisControl.ApplyValue();";
        
        // Store Field Properties.
        FieldName   = %fieldName;
    };
    %fieldContainer.add( %fieldType );
    
    %fieldInput = new GuiTextEditCtrl()
    {
        Class        = "VEditorDataPropertyField";
        SuperClass   = "VEditorStringPropertyField";
        InternalName = "FieldControl";
        Profile      = "VEditorTextEditProfile";
        
        HorizSizing  = "left";
        VertSizing   = "center";
        Position     = %fieldWidth - 156 SPC 0;
        Extent       = 80 SPC 18;
        
        AltCommand   = "$ThisControl.ApplyValue();";
        Validate     = "$ThisControl.ApplyValue();";
        
        // Store Field Properties.
        FieldName   = %fieldName;
        FieldType   = %fieldType;
    };
    %fieldContainer.add( %fieldInput );
    
    %fieldButton = new GuiBitmapButtonCtrl()
    {
        Class        = "VEditorDataPropertyButton";
        InternalName = "FieldButton";
        Profile      = "VEditorBitmapButtonProfile";

        HorizSizing  = "left";
        VertSizing   = "bottom";
        Position     = %fieldWidth - 24 SPC 0;
        Extent       = "18 18";
        
        Bitmap       = "tools/VerveEditor/GUI/Images/btn_DeleteSml";
        
        Command      = %fieldInput @ ".Remove();";
    };
    %fieldContainer.add( %fieldButton );
    
    // Apply Enum Content.
    %fieldType.add( "EXP", 0 );
    %fieldType.add( "STA", 1 );
    %fieldType.add( "VAR", 2 );
    
    return %fieldInput;
}

function VEditorDataPropertyField::Update( %this, %fieldName, %fieldValue )
{
    // Fetch Object.
    %controller = $VerveEditor::Controller;
    if ( !isObject( %controller ) )
    {
        // No Object!
        return;
    }
    
    if ( %fieldName $= "" )
    {
        return;
    }
    
    Parent::Update( %this, %fieldName, %fieldValue );
    
    // Update Type.
    %fieldType = %controller.getDataFieldType( %fieldName );
    switch$( %fieldType )
    {
        case "EXPRESSION" : %fieldType = "EXP";
        case "STATIC"     : %fieldType = "STA";
        case "VARIABLE"   : %fieldType = "VAR";
    }
    
    // Apply.
    %this.FieldType.setText( %fieldType );
}

function VEditorDataPropertyField::ApplyValue( %this )
{
    // Fetch Object.
    %controller = $VerveEditor::Controller;
    if ( !isObject( %controller ) )
    {
        // No Object!
        return;
    }
    
    // Update?
    %update = stricmp( %controller.getFieldValue( %this.FieldName ), %this.getText() );
    
    // Parent Update.
    Parent::ApplyValue( %this );
    
    if ( %update )
    {
        // Post Event.
        VerveEditor::PostEvent( "VGroupObjectUpdate", %controller );
    }
}

function VEditorDataTypePropertyField::ApplyValue( %this )
{
    // Fetch Object.
    %controller = $VerveEditor::Controller;
    if ( !isObject( %controller ) )
    {
        // No Object!
        return;
    }
    
    // Update Type.
    %fieldType = %this.getText();
    switch$( %fieldType )
    {
        case "EXP" : %fieldType = "EXPRESSION";
        case "STA" : %fieldType = "STATIC";
        case "VAR" : %fieldType = "VARIABLE";
    }
    
    if ( %controller.getDataFieldType( %this.FieldName ) !$= %fieldType )
    {
        // Apply.
        %controller.addDataField( %fieldType, %this.FieldName );
        
        // Post Event.
        VerveEditor::PostEvent( "VGroupObjectUpdate", %controller );
    }
}

//-------------------------------------------------------------------------

function VEditorDataPropertyField::Insert( %fieldType, %fieldName, %fieldValue )
{
    %controller = $VerveEditor::Controller;
    if ( !isObject( %controller ) )
    {
        // No Object!
        return;
    }
    
    if ( %fieldName $= "" )
    {
        // Invalid Field Name.
        return;
    }
    
    switch$( %fieldType )
    {
        case "EXP" : %fieldType = "EXPRESSION";
        case "STA" : %fieldType = "STATIC";
        case "VAR" : %fieldType = "VARIABLE";
    }
    
    // Add Data Field.
    %controller.addDataField( %fieldType, strReplace( %fieldName, " ", "" ) );
    
    // Apply Value.
    %controller.setFieldValue( %fieldName, %fieldValue );
    
    // Refresh Inspection.
    schedule( 0, 0, "VerveEditor::OnSelectionUpdate" );
}

function VEditorDataPropertyField::Remove( %this )
{
    %controller = $VerveEditor::Controller;
    if ( !isObject( %controller ) )
    {
        // No Object!
        return;
    }
    
    // Clear Data.
    %controller.removeDataField( %this.FieldName );
    
    // Refresh Inspection.
    schedule( 0, 0, "VerveEditor::OnSelectionUpdate" );
}

//-------------------------------------------------------------------------

function VerveEditor::CreateAddDataField( %targetStack )
{
    %fieldWidth  = getWord( %targetStack.getExtent(), 0 );
    %fieldHeight = 18;
    
    %fieldContainer = new GuiControl()
    {
        Profile     = "VEditorTransparentProfile";
        
        HorizSizing = "width";
        VertSizing  = "bottom";
        Position    = "0 0";
        Extent      = %fieldWidth SPC %fieldHeight;
    };
    %targetStack.add( %fieldContainer );
    
    %fieldName = new GuiTextEditCtrl()
    {
        Class        = "VEditorAddDataNameField";
        InternalName = "FieldControl";
        Profile      = "VEditorTextEditProfile";
        
        HorizSizing  = "right";
        VertSizing   = "center";
        Position     = "6 0";
        Extent       = "106" SPC 18;
        
        Text         = "FieldName";
    };
    %fieldContainer.add( %fieldName );
    
    %fieldValue = new GuiTextEditCtrl()
    {
        Class        = "VEditorAddDataValueField";
        InternalName = "FieldValue";
        Profile      = "VEditorTextEditProfile";
        
        HorizSizing  = "left";
        VertSizing   = "center";
        Position     = %fieldWidth - 156 SPC 0;
        Extent       = 80 SPC 18;
        
        Text         = "FieldValue";
    };
    %fieldContainer.add( %fieldValue );
    
    %fieldType = new GuiPopUpMenuCtrl()
    {
        Class        = "VEditorDataTypePropertyField";
        InternalName = "FieldType";
        Profile      = "VEditorPopupMenuProfile";
        
        HorizSizing  = "left";
        VertSizing   = "center";
        Position     = %fieldWidth - 72 SPC 0;
        Extent       = 44 SPC 18;
    };
    %fieldContainer.add( %fieldType );
    
    %fieldButton = new GuiBitmapButtonCtrl()
    {
        Class        = "VEditorDataPropertyButton";
        InternalName = "FieldButton";
        Profile      = "VEditorBitmapButtonProfile";

        HorizSizing  = "left";
        VertSizing   = "bottom";
        Position     = %fieldWidth - 24 SPC 0;
        Extent       = "18 18";
        
        Bitmap       = "tools/VerveEditor/GUI/Images/btn_AddSml";
        
        Command      = "VEditorDataPropertyField::Insert(" @ %fieldType @ ".getText(), " @ %fieldName @ ".getText(), " @ %fieldValue @ ".getText() );";
    };
    %fieldContainer.add( %fieldButton );
    
    // Apply Enum Content.
    %fieldType.add( "EXP", 0 );
    %fieldType.add( "STA", 1 );
    %fieldType.add( "VAR", 2 );
    
    // Set Default.
    %fieldType.setFirstSelected();
    
    return %fieldContainer;
}

function VEditorAddDataNameField::onGainFirstResponder( %this )
{
    VEditorStringPropertyField::onGainFirstResponder( %this );
    
    if ( %this.getText() $= "FieldName" )
    {
        // Clear.
        %this.setText( "" );
    }
}

function VEditorAddDataNameField::onLoseFirstResponder( %this )
{
    VEditorStringPropertyField::onLoseFirstResponder( %this );
    
    if ( %this.getText() $= "" )
    {
        // Clear.
        %this.setText( "FieldName" );
    }
}

function VEditorAddDataValueField::onGainFirstResponder( %this )
{
    VEditorStringPropertyField::onGainFirstResponder( %this );
    
    if ( %this.getText() $= "FieldValue" )
    {
        // Clear.
        %this.setText( "" );
    }
}

function VEditorAddDataValueField::onLoseFirstResponder( %this )
{
    VEditorStringPropertyField::onLoseFirstResponder( %this );
    
    if ( %this.getText() $= "" )
    {
        // Clear.
        %this.setText( "FieldValue" );
    }
}