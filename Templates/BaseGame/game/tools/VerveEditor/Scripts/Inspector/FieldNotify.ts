//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditor::AddInspectorFieldNotify( %fieldName, %refObject )
{
    if ( !isObject( $VerveEditor::InspectorFieldNotifySet ) )
    {
        $VerveEditor::InspectorFieldNotifySet = new SimSet();
    }
    
    %inspectorSet = $VerveEditor::InspectorFieldNotifySet;
    if ( isObject( %refObject ) && !%inspectorSet.isMember( %refObject ) )
    {
        // Add The Object.
        %inspectorSet.add( %refObject );
    }
    
    // Add Field Reference.
    %refObject.InspectorFieldNotifyList = rtrim( %fieldName SPC %refObject.InspectorFieldNotifyList );
}

function VObject::AddFieldNotify( %this, %fieldName, %refObject )
{
    if ( isObject( %refObject ) )
    {
        // Store.
        %this.FieldNotify[%fieldName] = trim( %this.FieldNotify[%fieldName] SPC %refObject );
        
        // Update.
        %refObject.Update( %fieldName, %this.getFieldValue( %fieldName ) );
    }
}

function VObject::setFieldValue( %this, %fieldName, %fieldValue )
{
    // Fetch Old Value.
    %oldValue = %this.getFieldValue( %fieldName );
    
    if ( stricmp( %oldValue , %fieldValue ) == 0 )
    {
        // No Update.
        return;
    }
    
    // Update Value.
    Parent::setFieldValue( %this, %fieldName, %fieldValue );
    
    // Notify Change.
    %this.NotifyFieldChange( %fieldName, %oldValue );
}

function VObject::NotifyFieldChange( %this, %fieldName, %oldValue )
{
    // Get Field Value.
    %newValue = %this.getFieldValue( %fieldName );
    
    %controlList  = %this.FieldNotify[%fieldName];
    %controlCount = getWordCount( %controlList );
    for ( %i = 0; %i < %controlCount; %i++ )
    {
        // Fetch the Control.
        %control = getWord( %controlList, %i );
        
        if ( !isObject( %control ) )
        {
            // Remove Deleted Controls.
            %controlList   = removeWord( %controlList, %i );
            %controlCount -= 1;
            
            %i -= 1;
            continue;
        }
        
        // Update.
        %control.Update( %fieldName, %newValue );
    }
    
    // Updated List?
    %this.FieldNotify[%fieldName] = %controlList;
    
    // Update Inspector Fields?
    if ( isObject( $VerveEditor::InspectorObject ) && $VerveEditor::InspectorObject.getId() == %this.getId() )
    {
        %refObjectSet   = $VerveEditor::InspectorFieldNotifySet;
        %refObjectCount = %refObjectSet.getCount();
        for ( %i = 0; %i < %controlCount; %i++ )
        {
            // Fetch the Object.
            %refObject = %refObjectSet.getObject( %i );
            if ( !isWordInList( %fieldName, %refObject.InspectorFieldNotifyList ) )
            {
                // Skip.
                continue;
            }
            
            if ( %refObject.isMethod( "Update" ) )
            {
                // Update.
                %refObject.Update( %fieldName, %newValue );
            }
        }
    }
    
    // Update Object?
    if ( %this.isMethod( "onFieldChange" ) )
    {
        // Notify.
        %this.onFieldChange( %fieldName, %oldValue, %newValue );
    }
}

function VController::setFieldValue( %this, %fieldName, %fieldValue )
{
    // Fetch Old Value.
    %oldValue = %this.getFieldValue( %fieldName );
    
    if ( stricmp( %oldValue , %fieldValue ) == 0 )
    {
        // No Update.
        return;
    }
    
    // Update Value.
    Parent::setFieldValue( %this, %fieldName, %fieldValue );
    
    // Notify Change.
    %this.NotifyFieldChange( %fieldName, %oldValue );
}

function VController::NotifyFieldChange( %this, %fieldName, %oldValue )
{
    // Use Default Callback.
    VObject::NotifyFieldChange( %this, %fieldName, %oldValue );
}