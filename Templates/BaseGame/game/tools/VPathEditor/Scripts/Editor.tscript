//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function EVPathEditor::onDeleteKey( %this )
{
    %editPath = EVPathEditor.getSelectedPath();
    %editNode = EVPathEditor.getSelectedNode();
    if ( isObject( %editPath ) && %editNode != -1 )
    {
        // Delete the Node.
        %this.deleteSelection();
    }
    else
    {
        // Clear Selection.
        %this.clearSelection();
        
        // Delete the Path.
        MEDeleteUndoAction::submit( %editPath );
    }
}

function EVPathEditor::onUpdateSelection( %this, %editPath, %editNode )
{
    // Clear World Editor Selection.
    EWorldEditor.clearSelection();
    
    %clearNode = true;
    if ( isObject( %editPath ) )
    {
        // Reset Type.
        VPathEditorToolbarPathTypeMenu.setText( %editPath.PathType );
        
        // Set World Editor Selection.
        EWorldEditor.selectObject( %editPath );
        
        // Inspect.
        VPathInspector.inspect( %editPath );
        
        // Update the Node Inspector.
        if ( %editNode != -1 )
        {
            // Valid Node.
            %clearNode = false;
            
            VPathEditorOptionsWindow-->position.setActive( true );
            VPathEditorOptionsWindow-->position.setValue( %editPath.getNodeLocalPosition( %editNode ) );    

            VPathEditorOptionsWindow-->rotation.setActive( true );
            VPathEditorOptionsWindow-->rotation.setValue( %editPath.getNodeLocalRotation( %editNode ) );

            VPathEditorOptionsWindow-->weight.setActive( true );
            VPathEditorOptionsWindow-->weight.setValue( %editPath.getNodeWeight( %editNode ) ); 
            
            %orientationMode = %editPath.getNodeOrientationMode( %editNode );
            %orientationType = EPathEditorNodeOrientationMode.findText( strupr( getField( %orientationMode, 0 ) ) );
            %orientationData = getField( %orientationMode, 1 );
            
            EPathEditorNodeOrientationMode.setSelected( %orientationType, false );
            EPathEditorNodeOrientationData.Text = %orientationData;
        }
    }
    
    // Invalid Node?
    if ( %clearNode )
    {
        VPathEditorOptionsWindow-->position.setActive( false );
        VPathEditorOptionsWindow-->position.setValue( "" );    

        VPathEditorOptionsWindow-->rotation.setActive( true );
        VPathEditorOptionsWindow-->rotation.setValue( "" );

        VPathEditorOptionsWindow-->weight.setActive( true );
        VPathEditorOptionsWindow-->weight.setValue( "" ); 
    }
}

function VPathEditorToolbarPathTypeMenu::onSelect( %this )
{
    %editPath = EVPathEditor.getSelectedPath();
    if ( isObject( %editPath ) )
    {
        // Apply Type.
        %editPath.PathType = %this.getText();
    }
}

function VPathTreeView::onInspect( %this, %object )
{
    // VPath?
    if ( !%object.isMemberOfClass( "VPath" ) )
    {
        return;
    }
    
    // Select Object.
    EVPathEditor.setSelection( %object );
}

function VPathTreeView::DeleteSelectedPaths( %this )
{
    // Clear the Selection.
    EVPathEditor.clearSelection();
    
    // Iterate over Selection.
    %selectionList = %this.getSelectedItemList();
    %selectionCount = getWordCount( %selectionList );
    for ( %i = 0; %i < %selectionCount; %i++ )
    {
        // Fetch Index.
        %itemIndex = getWord( %selectionList, %i );
        
        // Fetch Object.
        %itemObject = %this.getItemValue( %itemIndex );
        
        // Skip Non-Path Objects.
        if ( !%itemObject.isMemberOfClass( "VPath" ) )
        {
            continue;
        }
        
        // Delete the Object.
        MEDeleteUndoAction::submit( %itemObject );
    }
    
    // Clear the Selection.
    %this.clearSelection();
    EVPathEditor.clearSelection();
    
    // Build the Tree.
    %this.open( GetServerPathSet(), true );
}

function VPathTreeView::CreatePath( %this )
{
    // Create Path Object.
    EWCreatorWindow.createObject( "ObjectBuilderGui.buildObject( \"VPath\" );" );
}

//-----------------------------------------------------------------------------
//
// Node Editing
//
//-----------------------------------------------------------------------------

function EVPathEditor::onUpdateNode( %this, %editPath, %editNode, %selected )
{
    if ( %selected )
    {
        %this.onUpdateNodePosition( %editPath, %editNode, %selected );
        %this.onUpdateNodeRotation( %editPath, %editNode, %selected );
        %this.onUpdateNodeWeight( %editPath, %editNode, %selected );
        %this.onUpdateNodeOrientation( %editPath, %editNode, %selected );
    }
}

function EVPathEditor::onUpdateNodePosition( %this, %editPath, %editNode, %selected )
{
    if ( %selected )
    {
        VPathEditorOptionsWindow-->position.setValue( %editPath.getNodeLocalPosition( %editNode ) );
    }
}

function EVPathEditor::onUpdateNodeRotation( %this, %editPath, %editNode, %selected )
{
    if ( %selected )
    {
        VPathEditorOptionsWindow-->rotation.setValue( %editPath.getNodeLocalRotation( %editNode ) );
    }
}

function EVPathEditor::onUpdateNodeWeight( %this, %editPath, %editNode, %selected )
{
    if ( %selected )
    {
        VPathEditorOptionsWindow-->weight.setValue( %editPath.getNodeWeight( %editNode ) );
    }
}

function EVPathEditor::onUpdateNodeOrientation( %this, %editPath, %editNode, %selected )
{
    if ( %selected )
    {
        %orientationMode = %editPath.getNodeOrientationMode( %editNode );
        %orientationType = EPathEditorNodeOrientationMode.findText( strupr( getField( %orientationMode, 0 ) ) );
        %orientationData = getField( %orientationMode, 1 );
        
        // Change?
        if ( EPathEditorNodeOrientationMode.getSelected() != %orientationType )
        {
            // Update.
            EPathEditorNodeOrientationMode.setSelected( %orientationType );
        }
        
        // Change?
        if ( EPathEditorNodeOrientationData.getText() !$= %orientationData )
        {
            // Update.
            EPathEditorNodeOrientationData.setText( %orientationData );
        }
    }
}

//-----------------------------------------------------------------------------
//
// Inspector
//
//-----------------------------------------------------------------------------

function VPathInspector::inspect( %this, %obj )
{
    VPathFieldInfoControl.setText( "" );
    Parent::inspect( %this, %obj );  
}

function VPathInspector::onInspectorFieldModified( %this, %object, %fieldName, %arrayIndex, %oldValue, %newValue )
{
    // Same work to do as for the regular WorldEditor Inspector.
    Inspector::onInspectorFieldModified( %this, %object, %fieldName, %arrayIndex, %oldValue, %newValue );   
}

function VPathInspector::onFieldSelected( %this, %fieldName, %fieldTypeStr, %fieldDoc )
{
    VPathFieldInfoControl.setText( "<font:ArialBold:14>" @ %fieldName @ "<font:ArialItalic:14> (" @ %fieldTypeStr @ ") " NL "<font:Arial:14>" @ %fieldDoc );
}