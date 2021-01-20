//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------
    
new ScriptObject( VMotionEventPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    Parent      = "VEventPropertyList";
};

//-----------------------------------------------------------------------------

function VMotionEvent::CreatePathNode( %this, %transform )
{
    // Fetch Track & Group.
    %track  = %this.getParent();
    %group  = %track.getParent();
    
    // Fetch Object References.
    %object = %group.getSceneObject();
    %path   = %track.getPath();
    
    // Fetch Index.
    %nodeIndex = %this.getIndex();
    
    // Create New Node.
    %path.addNode( %transform, 10, %nodeIndex );
    
    // Update Transform.
    %object.setTransform( %transform );
    
    if ( !VerveEditorHistoryManager.Locked )
    {
        // Add History Item.
        %historyObject = new UndoScriptAction()
        {
            Class      = "VerveEditorHistoryCreateMotionEvent";
            SuperClass = "VerveEditorHistoryCreateObject";
            
            ActionName = "Create Object";
            
            // Store Object References.
            Parent     = %track;
            Object     = %this;
            
            // Store Node Information.
            PathObject    = %path;
            NodeIndex     = %nodeIndex;
            NodeTransform = %path.getNodeWorldTransform( %nodeIndex );
            NodeWeight    = %path.getNodeWeight( %nodeIndex );
        };
        
        // Force OnAdd.
        VerveEditorHistoryObject::onAdd( %historyObject );
    }
    
    // Reset the Controller.
    $VerveEditor::Controller.reset( $VerveEditor::Controller.Time );
}

function VMotionEvent::Delete( %this )
{
    // Fetch Parent.
    %parentObject = %this.getParent();
    %rootObject   = %this.getRoot();
    if ( !%parentObject || ( %rootObject.getId() != $VerveEditor::Controller.getId() ) )
    {
        // Not Editing, Delete.
        Parent::delete( %this );
        return;
    }
    
    if ( !VerveEditorHistoryManager.Locked )
    {
        %path      = %parentObject.getPath();
        %nodeIndex = %this.getIndex();
        
        // Add History Item.
        %historyObject = new UndoScriptAction()
        {
            Class      = "VerveEditorHistoryDeleteMotionEvent";
            SuperClass = "VerveEditorHistoryDeleteObject";
            
            ActionName = "Delete Object";
            
            // Store Object References.
            Parent     = %parentObject;
            Object     = %this;
            
            // Store Node Information.
            PathObject    = %path;
            NodeIndex     = %nodeIndex;
            NodeTransform = %path.getNodeWorldTransform( %nodeIndex );
            NodeWeight    = %path.getNodeWeight( %nodeIndex );
        };
        
        // Force OnAdd.
        VerveEditorHistoryObject::onAdd( %historyObject );
    }
    
    // Detach Object.
    %parentObject.removeObject( %this );
}

function VMotionEvent::OnRemove( %this )
{
    // Fetch Path.
    %path = %this.getParent().getPath();
    if ( !isObject( %path ) )
    {
        return;
    }
    
    // Delete Node.
    %path.deleteNode( %this.getIndex() );
}

function VMotionEvent::OnSelect( %this )
{
    // Fetch Path.
    %path = %this.getParent().getPath();
    if ( !isObject( EVPathEditor ) || !isObject( %path ) )
    {
        // No Editor.
        return;
    }
    
    // Update Selection.
    EVPathEditor.setSelection( %path, %this.getIndex() );
}

//-------------------------------------------------------------------------

function VerveEditorHistoryCreateMotionEvent::Undo( %this )
{
    // Delete Node.
    %this.PathObject.DeleteNode( %this.NodeIndex );
    
    // Dirty.
    EVPathEditor.isDirty = true;
    
    // Regular Undo.
    Parent::Undo( %this );
}

function VerveEditorHistoryCreateMotionEvent::Redo( %this )
{
    // Create Node.
    %this.PathObject.AddNode( %this.NodeTransform, %this.NodeWeight, %this.NodeIndex );
    
    // Dirty.
    EVPathEditor.isDirty = true;
    
    // Regular Redo.
    Parent::Redo( %this );
}

//-------------------------------------------------------------------------

function VerveEditorHistoryDeleteMotionEvent::Undo( %this )
{
    // Create Node.
    %this.PathObject.AddNode( %this.NodeTransform, %this.NodeWeight, %this.NodeIndex );
    
    // Dirty.
    EVPathEditor.isDirty = true;
    
    // Regular Undo.
    Parent::Undo( %this );
}

function VerveEditorHistoryDeleteMotionEvent::Redo( %this )
{
    // Delete Node.
    %this.PathObject.DeleteNode( %this.NodeIndex );
    
    // Dirty.
    EVPathEditor.isDirty = true;
    
    // Regular Redo.
    Parent::Redo( %this );
}