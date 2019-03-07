//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

$VerveEditor::HistoryManager = new UndoManager( VerveEditorHistoryManager );
$VerveEditor::UndoCount      = 0;
$VerveEditor::RedoCount      = 0;

//-----------------------------------------------------------------------------

function VerveEditor::IsDirty()
{
    if ( !isObject( VerveEditorHistoryManager ) )
    {
        // Woops!
        return false;
    }
    
    return !( ( VerveEditorHistoryManager.getUndoCount() == $VerveEditor::UndoCount )
           && ( VerveEditorHistoryManager.getRedoCount() == $VerveEditor::RedoCount ) );
}

function VerveEditor::ClearDirty()
{
    // Reset.
    $VerveEditor::UndoCount = VerveEditorHistoryManager.getUndoCount();
    $VerveEditor::RedoCount = VerveEditorHistoryManager.getRedoCount();
}

function VerveEditor::ClearHistory()
{
    // Clear History.
    VerveEditorHistoryManager.clearAll();
    
    // Clear Dirty.
    VerveEditor::ClearDirty();
}

function VerveEditor::CanUndo()
{
    return ( VerveEditorHistoryManager.getUndoCount() > 0 );
}

function VerveEditor::Undo()
{
    VerveEditorHistoryManager.Undo();
    
    // Refresh.
    VerveEditor::Refresh();
}

function VerveEditor::CanRedo()
{
    return ( VerveEditorHistoryManager.getRedoCount() > 0 );
}

function VerveEditor::Redo()
{
    VerveEditorHistoryManager.Redo();
    
    // Refresh.
    VerveEditor::Refresh();
}

//-------------------------------------------------------------------------

function VerveEditorHistoryObject::onAdd( %this )
{
    %historyManager = VerveEditorHistoryManager;
    if ( %historyManager.Locked )
    {
        // Delete.
        %this.schedule( 0, delete );
        return;
    }
    
    if ( isObject( %historyManager.HistoryGroup ) )
    {
        // Add To Group.
        %historyManager.HistoryGroup.Group.add( %this );
        return;
    }
    
    // Add To Manager.
    %this.addToManager( %historyManager );
    
    // Update Window.
    VerveEditorWindow.UpdateWindowTitle();
}

//-------------------------------------------------------------------------

function VerveEditor::ToggleHistoryGroup()
{
    %historyManager = VerveEditorHistoryManager;
    if ( isObject( %historyManager.HistoryGroup ) )
    {
        // Clear.
        %historyManager.HistoryGroup = 0;
        
        // Update Window.
        VerveEditorWindow.UpdateWindowTitle();
        
        return;
    }
    
    if ( VerveEditorHistoryManager.Locked )
    {
        // Locked.
        return;
    }
    
    %historyManager.HistoryGroup = new UndoScriptAction()
    {
        Class      = "VerveEditorHistoryGroup";
        
        ActionName = "History Group";
        
        // Store Object References.
        Group      = new SimGroup();
    };
    
    // Add To Manager.
    %historyManager.HistoryGroup.addToManager( %historyManager );
}

function VerveEditorHistoryGroup::onRemove( %this )
{
    if ( isObject( %this.Group ) )
    {
        // Delete Group.
        %this.Group.delete();
    }
}

function VerveEditorHistoryGroup::Undo( %this )
{
    // Undo In Reverse Order.
    
    %undoCount = %this.Group.getCount();
    for ( %i = ( %undoCount - 1 ); %i >= 0; %i-- )
    {
        %this.Group.getObject( %i ).Undo();
    }
}

function VerveEditorHistoryGroup::Redo( %this )
{
    %undoCount = %this.Group.getCount();
    for ( %i = 0; %i < %undoCount; %i++ )
    {
        %this.Group.getObject( %i ).Redo();
    }
}

//-------------------------------------------------------------------------

function VerveEditorHistoryCreateObject::Undo( %this )
{
    // Undo Delete.
    %parentObject = %this.Parent;
    %object       = %this.Object;
    
    // Detach Object.
    %parentObject.removeObject( %object );
}

function VerveEditorHistoryCreateObject::Redo( %this )
{
    // Redo Delete.
    %parentObject = %this.Parent;
    %object       = %this.Object;
    
    // Attach Object.
    %parentObject.addObject( %object );
}

function VerveEditorHistoryCreateObject::onRemove( %this )
{
    /*
    if ( !isObject( %this.Object.getParent() ) || %this.Object.getParent().getId() != %this.Parent.getId() )
    {
        SimObject::Delete( %this.Object );
    }
    */
}

//-------------------------------------------------------------------------

function VerveEditorHistoryDeleteObject::Undo( %this )
{
    // Undo Delete.
    %parentObject = %this.Parent;
    %object       = %this.Object;
    
    // Attach Object.
    %parentObject.addObject( %object );
}

function VerveEditorHistoryDeleteObject::Redo( %this )
{
    // Redo Delete.
    %parentObject = %this.Parent;
    %object       = %this.Object;
    
    // Detach Object.
    %parentObject.removeObject( %object );
}

function VerveEditorHistoryDeleteObject::onRemove( %this )
{
    /*
    if ( !isObject( %this.Object.getParent() ) || %this.Object.getParent().getId() != %this.Parent.getId() )
    {
        SimObject::Delete( %this.Object );
    }
    */
}

//-------------------------------------------------------------------------

function VerveEditorHistoryChangeProperty::Undo( %this )
{
    // Undo Change.
    %object    = %this.Object;
    %fieldName = %this.FieldName;
    %oldValue  = %this.OldValue;
    
    // Lock History.
    VerveEditorHistoryManager.Locked = true;
    
    // Attach Object.
    %object.setFieldValue( %fieldName, %oldValue, false );
    
    // Unlock History.
    VerveEditorHistoryManager.Locked = false;
}

function VerveEditorHistoryChangeProperty::Redo( %this )
{
    // Redo Change.
    %object    = %this.Object;
    %fieldName = %this.FieldName;
    %newValue  = %this.NewValue;
    
    // Lock History.
    VerveEditorHistoryManager.Locked = true;
    
    // Attach Object.
    %object.setFieldValue( %fieldName, %newValue, false );
    
    // Unlock History.
    VerveEditorHistoryManager.Locked = false;
}

function VerveEditorHistoryManager::Lock( %this )
{
    %this.Locked = true;
}

function VerveEditorHistoryManager::UnLock( %this )
{
    %this.Locked = false;
}