//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditor::CreateEnumField( %fieldContainer, %fieldName, %class )
{
    %fieldWidth = getWord( %fieldContainer.getExtent(), 0 );
    
    %fieldInput = new GuiPopupMenuCtrl()
    {
        Class        = %class;
        SuperClass   = "VEditorEnumPropertyField";
        InternalName = "FieldControl";
        Profile      = "VEditorPopupMenuProfile";
        
        HorizSizing  = "left";
        VertSizing   = "center";
        Position     = %fieldWidth - 156 SPC 0;
        Extent       = "150 18";
        
        Command      = "$ThisControl.ApplyValue();";
        
        // Store Field Properties.
        FieldName    = %fieldName;
    };
    %fieldContainer.add( %fieldInput );
    
    // Field Notify.
    VerveEditor::AddInspectorFieldNotify( %fieldName, %fieldInput );
    
    return %fieldInput;
}

function VEditorEnumPropertyField::ApplyValue( %this )
{
    // Apply Value.
    VEditorPropertyField::ApplyValue( %this, %this.FieldName, %this.getText() );
}

function VEditorEnumPropertyField::Update( %this, %fieldName, %fieldValue )
{
    if ( %this.getText() !$= %fieldValue )
    {
        // Apply Text.
        %this.setText( %fieldValue );
    }
}

function VEditorEnumPropertyField::PopulateFromDatablockGroup( %this, %className )
{
    // Clear List.
    %this.clear();
    
    // Iterate Over Datablocks.
    %dataSet   = DataBlockGroup;
    %dataCount = %dataSet.getCount();
    for ( %i = 0; %i < %dataCount; %i++ )
    {
        // Fetch Item.
        %dataObject = %dataSet.getObject( %i );
        if ( %dataObject.isMemberOfClass( %className ) )
        {
            // Add Item.
            %this.add( %dataObject.getName(), %i );
        }
    }
    
    // Sort.
    %this.sort();
}

function VEditorEnumPropertyField::PopulateFromRootGroup( %this, %className )
{
    // Clear List.
    %this.clear();
    
    // Iterate Over RootGroup.
    %dataSet   = RootGroup;
    %dataCount = %dataSet.getCount();
    for ( %i = 0; %i < %dataCount; %i++ )
    {
        // Fetch Item.
        %dataObject = %dataSet.getObject( %i );
        if ( %dataObject.isMemberOfClass( %className ) )
        {
            // Add Item.
            %this.add( %dataObject.getName(), %i );
        }
    }
    
    // Sort.
    %this.sort();
}