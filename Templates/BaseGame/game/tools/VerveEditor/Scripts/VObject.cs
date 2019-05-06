//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VObject::OnAdd( %this )
{
    // Fetch Parent.
    %parentObject = %this.getParent();
    %rootObject   = %this.getRoot();
    if ( !%parentObject || ( %rootObject.getId() != $VerveEditor::Controller.getId() ) )
    {
        return true;
    }
    
    if ( !VerveEditorHistoryManager.Locked )
    {
        // Add History Item.
        %historyObject = new UndoScriptAction()
        {
            Class      = "VerveEditorHistoryCreateObject";
            SuperClass = "VerveEditorHistoryObject";
            
            ActionName = "Create Object";
            
            // Store Object References.
            Parent     = %parentObject;
            Object     = %this;
        };
    }
    
    // Valid.
    return true;
}

function VObject::OnRemove( %this )
{
    // Void.
}

function VObject::Delete( %this )
{
    // Fetch Parent.
    %parentObject = %this.getParent();
    %rootObject   = %this.getRoot();
    if ( !%parentObject || ( %rootObject.getId() != $VerveEditor::Controller.getId() ) )
    {
        // Callback.
        %this.OnRemove();
        
        // Not Editing, Delete.
        Parent::delete( %this );
        return;
    }
    
    if ( !VerveEditorHistoryManager.Locked )
    {
        // Add History Item.
        %historyObject = new UndoScriptAction()
        {
            Class      = "VerveEditorHistoryDeleteObject";
            SuperClass = "VerveEditorHistoryObject";
            
            ActionName = "Delete Object";
            
            // Store Object References.
            Parent     = %parentObject;
            Object     = %this;
        };
    }
    
    // Callback.
    %this.OnRemove();
    
    // Detach Object.
    %parentObject.removeObject( %this );
}

function VObject::OnFieldChange( %this, %fieldName, %oldValue, %newValue )
{
    if ( !VerveEditorHistoryManager.Locked )
    {
        // Add History Item.
        %historyObject = new UndoScriptAction()
        {
            Class      = "VerveEditorHistoryChangeProperty";
            SuperClass = "VerveEditorHistoryObject";
            
            ActionName = "Change Property (" @ %fieldName @ ")";
            
            // Store References.
            Object    = %this;
            FieldName = %fieldName;
            OldValue  = %oldValue;
            NewValue  = %newValue;
        };
    }
}