//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditor::DeleteControls()
{
    while ( VerveEditorGroupStack.getCount() > 0 )
    {
        VerveEditorGroupStack.getObject( 0 ).delete();
    }
    
    while ( VerveEditorTrackStack.getCount() > 0 )
    {
        VerveEditorTrackStack.getObject( 0 ).delete();
    }
}

function VerveEditorStack::FindControl( %this, %object )
{
    %trackCount = %this.getCount();
    for ( %i = 0; %i < %trackCount; %i++ )
    {
        %track = %this.getObject( %i );
        if ( %track.Proxy.getId() == %object.getId() )
        {
            return %track;
        }
    }
    
    return -1;
}

function VerveEditorStack::FindControlIndex( %this, %object )
{
    %trackCount = %this.getCount();
    for ( %i = 0; %i < %trackCount; %i++ )
    {
        %track = %this.getObject( %i );
        if ( %track.Proxy.getId() == %object.getId() )
        {
            return %i;
        }
    }
    
    return -1;
}

//-------------------------------------------------------------------------

function VerveEditorTimeLine::onLoseFirstResponder( %this )
{
    // Clear Selection.
    %this.setSelection( false );
    
    // Force OnSelectionUpdate.
    %this.onSelectionUpdate();
}

function VerveEditorTimeLine::StopUpdate( %this )
{
    // Cancel Event.
    cancel( $VerveEditor::Controller::TickEvent );
}

function VerveEditorTimeLine::ControllerUpdate( %this )
{
    // Cancel Event.
    cancel( $VerveEditor::Controller::TickEvent );
    
    %scrollParent = %this.getParentOfType( "VEditorScrollControl" );
    if ( !isObject( %scrollParent ) )
    {
        // Woops!
        return;
    }
    
    // Fetch Point.
    %point = %this.toPoint( $VerveEditor::Controller.Time );
    
    // Fetch Scroll Point.
    %scrollPoint = %scrollParent.getScrollPositionX();
    %scrollWidth = getWord( %scrollParent.getExtent(), 0 ) - 19;
    
    if ( ( %point < %scrollPoint ) || ( %point > ( %scrollPoint + %scrollWidth ) ) )
    {
        // Scroll To View Time.
        %scrollParent.setScrollPosition( %point - %scrollWidth * 0.50, 0 );
    }
    
    // Schedule Next Event.
    $VerveEditor::Controller::TickEvent = %this.schedule( 100, "ControllerUpdate" );
}

function VerveEditorTimeLine::onSelectionUpdate( %this )
{
    // Fetch Selection.
    %selectionString = %this.getSelection();
    
    %selectionActive = getWord( %selectionString, 0 );
    if ( !%selectionActive )
    {
        // Clear Selection.
        VerveEditorTrackTimeLine.setSelection( false );
    }
    else
    {
        if ( !getWord( VerveEditorTrackTimeLine.getSelection(), 0 ) )
        {
            // Clear Editor Selection.
            VerveEditor::ClearSelection();
        }
        
        // Set Selection.
        VerveEditorTrackTimeLine.setSelection( true, getWord( %selectionString, 1 ), getWord( %selectionString, 2 ) );
    }
}

function VerveEditorTimeLine::onSelectionRightClick( %this, %point, %modifiers, %clickCount )
{
   %this.DisplayContextMenu( getWord( %point, 0 ), getWord( %point, 1 ) );
}

function VerveEditorTimeLine::DisplayContextMenu( %this, %x, %y )
{
    %contextMenu = $VerveEditor::VTimeLine::ContextMenu;
    if ( !isObject( %contextMenu ) )
    {
        %contextMenu = new PopupMenu()
        {
            SuperClass = "VerveWindowMenu";
            
            IsPopup  = true;
            
            Label    = "VTimeLineMenu";
            Position = 0;
            
            Item[0]  = "Insert Time Before" TAB "" TAB "VerveEditorTimeLine.InsertTimeBefore();";
            Item[1]  = "Insert Time After"  TAB "" TAB "VerveEditorTimeLine.InsertTimeAfter();";
            
            Item[2]  = "" TAB "";
            
            Item[3]  = "Delete Time"        TAB "" TAB "VerveEditorTimeLine.DeleteTime();";
            
        };
        %contextMenu.Init();
        
        // Cache.
        $VerveEditor::VTimeLine::ContextMenu = %contextMenu;
    }
    
    // Display.
    if($Verve::UseSeparateWindow)
      %contextMenu.showPopup( VerveEditorWindow, %x, %y );
    else
      %contextMenu.showPopup( Canvas, %x, %y );
    
}

function VerveEditorTimeLine::InsertTimeBefore( %this )
{
    // Fetch Selection.
    %selectionString = %this.getSelection();
    %selectionActive = getWord( %selectionString, 0 );
    if ( !%selectionActive )
    {
        // Woops!
        return;
    }
    
    // Determine Position.
    %selectionPosition = getWord( %selectionString, 1 );
    
    // Insert Time.
    VerveEditor::InsertTime( %selectionPosition, getWord( %selectionString, 2 ) );
}

function VerveEditorTimeLine::InsertTimeAfter( %this )
{
    // Fetch Selection.
    %selectionString = %this.getSelection();
    %selectionActive = getWord( %selectionString, 0 );
    if ( !%selectionActive )
    {
        // Woops!
        return;
    }
    
    // Determine Position.
    %selectionPosition = getWord( %selectionString, 1 ) + getWord( %selectionString, 2 );
    
    // Insert Time.
    VerveEditor::InsertTime( %selectionPosition, getWord( %selectionString, 2 ) );
}

function VerveEditorTimeLine::DeleteTime( %this )
{
    // Fetch Selection.
    %selectionString = %this.getSelection();
    %selectionActive = getWord( %selectionString, 0 );
    if ( !%selectionActive )
    {
        // Woops!
        return;
    }
    
    // Determine Position.
    %selectionPosition = getWord( %selectionString, 1 );
    
    // Delete Time.
    VerveEditor::DeleteTime( %selectionPosition, getWord( %selectionString, 2 ) );
    
    // Clear Selection.
    %this.setSelection( false );
    
    // Force OnSelectionUpdate.
    %this.onSelectionUpdate();
}

//-------------------------------------------------------------------------

function VerveEditorTimeLineBackground::onMouseUp( %this, %point, %modifiers, %clickCount )
{
    // Clear Selection.
    VerveEditor::ClearSelection();
}

function VerveEditorTimeLineBackground::onRightMouseUp( %this, %point, %modifiers, %clickCount )
{
    // Clear Selection.
    VerveEditor::ClearSelection();
    
    if ( !%this.Context )
    {
        // Return.
        return;
    }
    
    // Display Context Menu.
    $VerveEditor::Controller.schedule( 32, "DisplayContextMenu", getWord( %point, 0 ), getWord( %point, 1 ) );
}