//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VEditorPropertyList::CreateInspector( %this )
{
    // Target Stack.
    %targetStack = VerveEditorPropertyStack;
    
    // Clear Stack.
    %targetStack.ClearStack();
    
    %propertyList = %this;
    while ( isObject( %propertyList ) )
    {
        if ( !isObject( %propertyList.ControlCache ) )
        {
            // Create and Store Cache.
            %propertyList.ControlCache = %propertyList.CreateInspectorGroup( %targetStack );
        }
        
        if ( %propertyList.ControlCache.getClassName() !$= "SimSet" )
        {
            // Single Control.
            %targetStack.add( %propertyList.ControlCache );
        }
        else
        {
            // Multiple Controls.
            %controlSet   = %propertyList.ControlCache;
            %controlCount = %controlSet.getCount();
            for ( %i = 0; %i < %controlCount; %i++ )
            {
                %targetStack.add( %controlSet.getObject( %i ) );
            }
        }
        
        // Get the Parent.
        %propertyList = %propertyList.Parent;
    }
}

function VEditorPropertyList::CreateInspectorGroup( %this, %targetStack )
{
    %controlSet = new SimSet();
    
    %i = 0;
    while ( %this.Group[%i] !$= "" )
    {
        %groupName     = %this.Group[%i];
        %groupRollout  = %targetStack.CreatePropertyRollout( %groupName );
        %propertyStack = %groupRollout.Stack;
        
        %j = 0;
        while ( %this.Field[%i, %j] !$= "" )
        {
            %fieldName = %this.Field[%i, %j];
            %fieldType = %this.Type[%i, %j];
            
            if ( %fieldType $= "" )
            {
                // Use ConsoleObject Field Type.
                %fieldType = $VerveEditor::InspectorObject.getFieldType( %fieldName );
                %fieldType = getSubStr( %fieldType, 4, strlen( %fieldType ) - 4 );
            }
            
            if ( getWordCount( %fieldName ) == 1 )
            {
                VerveEditor::CreateField( %propertyStack, %fieldName, %fieldType );
            }
            else
            {
                %fieldType = getWord( %fieldName, 0 );
                switch$ ( %fieldType )
                {
                    case "SPACER" : VerveEditor::CreateSpacer( %propertyStack, getWord( %fieldName, 1 ) );
                }
            }
            
            // Next Field.
            %j++;
        }
        
        // Store.
        %controlSet.add( %groupRollout );
        
        // Next Group.
        %i++;
    }
    
    %controlCount = %controlSet.getCount();
    if ( %controlCount == 1 )
    {
        %control = %controlSet.getObject( 0 );
        %controlSet.delete();
        
        return %control;
    }
    
    return %controlSet;
}

function VEditorPropertyList::InspectObject( %this, %object )
{
    if ( %this.InspectorLocked )
    {
        return;
    }
    
    // Prevent Infinite Loops.
    %this.InspectorLocked = true;
    
    %propertyList = %this;
    while ( isObject( %propertyList ) )
    {
        if ( !isObject( %propertyList.ControlCache ) )
        {
            continue;
        }
        
        if ( %propertyList.ControlCache.getClassName() !$= "SimSet" )
        {
            // Single Control.
            %targetStack = %propertyList.ControlCache.InspectObject( %object );
        }
        else
        {
            // Multiple Controls.
            %controlSet   = %propertyList.ControlCache;
            %controlCount = %controlSet.getCount();
            for ( %i = 0; %i < %controlCount; %i++ )
            {
                %controlSet.getObject( %i ).InspectObject( %object );
            }
        }
        
        // Get the Parent.
        %propertyList = %propertyList.Parent;
    }
    
    // All Done.
    %this.InspectorLocked = false;
}