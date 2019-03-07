//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditorPropertyStack::ClearStack( %this )
{
    while ( %this.getCount() > 0 )
    {
        // Remove Object.
        %this.remove( %this.getObject( 0 ) );
    }
}

function VerveEditorPropertyStack::CreatePropertyRollout( %this, %groupLabel )
{
    %groupWidth  = getWord( %this.getExtent(), 0 );
    %groupHeight = 32;
    
    %propertyRollout = new GuiRolloutCtrl()
    {
        Class       = "VEditorPropertyRollout";
        Profile     = "VEditorPropertyRolloutProfile";
        
        HorizSizing = "right";
        VertSizing  = "bottom";
        Position    = "0 0";
        Extent      = %groupWidth SPC 18;
        
        Caption     = %groupLabel;
    };
    
    %propertyStack = new GuiStackControl()
    {
        Class       = "VEditorPropertyStack";
        Profile     = "GuiTransparentProfile";
        
        HorizSizing = "width";
        VertSizing  = "bottom";
        Position    = "0 0";
        Extent      = %groupWidth SPC %groupHeight;
        
        StackingType  = "Vertical";
        HorizStacking = "Left to Right";
        VertStacking  = "Top to Bottom";
        Padding       = "0";
    };
    %propertyRollout.add( %propertyStack );
    
    // Add Spacer.
    VerveEditor::CreateSpacer( %propertyStack, 4 );
    
    // Reference Stack.
    %propertyRollout.Stack = %propertyStack;
    
    return %propertyRollout;
}

function VEditorPropertyRollout::InspectObject( %this, %object )
{
    %this.Stack.InspectObject( %object );
}

function VEditorPropertyStack::InspectObject( %this, %object )
{
    %fieldCount = %this.getCount();
    for ( %i = 1; %i < %fieldCount; %i++ )
    {
        %fieldContainer = %this.getObject( %i );
        %fieldControl   = %fieldContainer.findObjectByInternalName( "FieldControl" );
        if ( !isObject( %fieldControl ) )
        {
            // Nothing to Update.
            continue;
        }
        
        // Store Object.
        %fieldControl.Object = %object;
        
        // Get Values.
        %fieldName  = %fieldControl.FieldName;
        %fieldValue = %object.getFieldValue( %fieldName );
        
        // Update Control?
        if ( %fieldControl.isMethod( "Update" ) )
        {
            // Update.
            %fieldControl.Update( %fieldName, %fieldValue );
        }
    }
}

function VerveEditor::CreateField( %targetStack, %fieldName, %fieldType )
{
    %fieldWidth  = getWord( %targetStack.getExtent(), 0 );
    %fieldHeight = 20;
    
    %fieldContainer = new GuiControl()
    {
        Profile     = "VEditorTransparentProfile";
        
        HorizSizing = "width";
        VertSizing  = "bottom";
        Position    = "0 0";
        Extent      = %fieldWidth SPC %fieldHeight;
    };
    %targetStack.add( %fieldContainer );
    
    %fieldLabel = new GuiTextCtrl()
    {
        Profile     = "VEditorTextProfile";
        
        HorizSizing = "right";
        VertSizing  = "bottom";
        Position    = "6 2";
        Extent      = %fieldWidth SPC 18;
        
        Text        = %fieldName;
        MaxLength   = "1024";
    };
    %fieldContainer.add( %fieldLabel );
    
    if ( isMethod( "VerveEditor", "Create" @ %fieldType @ "Field" ) )
    {
        // Create the Input Control.
        eval( "%fieldInput = VerveEditor::Create" @ %fieldType @ "Field( %fieldContainer, %fieldName );" );
    }
    else
    {
        // Default To String Control.
        %fieldInput = VerveEditor::CreateStringField( %fieldContainer, %fieldName );
    }
    
    return %fieldContainer;
}

function VEditorPropertyField::ApplyValue( %this, %fieldName, %fieldValue )
{
    // Apply Value.
    %this.Object.setFieldValue( %fieldName, %fieldValue );
    
    // Update Control.
    %this.Update( %fieldName, %this.Object.getFieldValue( %fieldName ) );
}

function VerveEditor::CreateSpacer( %targetStack, %spacerHeight )
{
    %fieldWidth  = getWord( %targetStack.getExtent(), 0 );
    %fieldHeight = %spacerHeight;
    
    %fieldContainer = new GuiControl()
    {
        Profile     = "VEditorTransparentProfile";
        
        HorizSizing = "width";
        VertSizing  = "bottom";
        Position    = "0 0";
        Extent      = %fieldWidth SPC %fieldHeight;
    };
    %targetStack.add( %fieldContainer );
    
    return %fieldContainer;
}