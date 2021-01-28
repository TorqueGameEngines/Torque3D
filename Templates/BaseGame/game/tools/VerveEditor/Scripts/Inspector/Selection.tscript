//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

$VerveEditor::InspectorObject = 0;
$VerveEditor::SelectionSet    = new SimSet();

//-----------------------------------------------------------------------------

function VerveEditor::HasSelection()
{
    return ( isObject( $VerveEditor::InspectorObject ) || $VerveEditor::SelectionSet.getCount() > 0 );
}

//-------------------------------------------------------------------------

function VerveEditor::OnSelectionUpdate()
{
    // Clear Inspector.
    VerveEditorPropertyStack.ClearStack();
    
    %selectionSet   = $VerveEditor::SelectionSet;
    %selectionCount = %selectionSet.getCount();
    if ( %selectionCount == 1 )
    {
        // Fetch Object.
        %selection = %selectionSet.getObject( 0 );
        
        // Highlight
        %selection.setStateOn( true );
        if ( isObject( %selection.SiblingControl ) )
        {
            %selection.SiblingControl.setStateOn( true );
        }
        
        if ( isObject( %selection.Proxy ) )
        {
            // Change Selection.
            %selection = %selection.Proxy;
        }
        
        if ( isObject( %selection ) )
        {
            // Inspector Property List.
            %selectionList = %selection.getClassName() @ "PropertyList";
            if ( isObject( %selectionList ) )
            {
                // Inspect Object.
                VerveEditor::InspectObject( %selection, %selectionList );
            }
            
            // Callback?
            if ( %selection.isMethod( "onSelect" ) )
            {
                %selection.onSelect();
            }
        }
    }
    else
    {
        %selection = $VerveEditor::InspectorObject;
        if ( isObject( %selection ) )
        {
            // Callback?
            if ( %selection.isMethod( "onDeselect" ) )
            {
                %selection.onDeselect();
            }
        }
        
        // Clear Inspector Object.
        $VerveEditor::InspectorObject = 0;
        
        if ( %selectionCount == 0 )
        {
            // Inspect Controller.
            VerveEditor::InspectObject( $VerveEditor::Controller, VControllerPropertyList );
        }
    }
}

function VerveEditor::InspectObject( %object, %propertyList )
{
    // Reference Inspected Object.
    $VerveEditor::InspectorObject = %object;
    
    // Create Lists.
    %propertyList.CreateInspector();
    
    // Update Fields.
    %propertyList.InspectObject( %object );
}

function VEditorSelectable::OnMouseEnter( %this, %position, %modifiers, %clickCount )
{
    if ( isObject( %this.SiblingControl ) )
    {
        %this.SiblingControl.setStateOn( true );
    }
}

function VEditorSelectable::OnMouseLeave( %this, %position, %modifiers, %clickCount )
{
    if ( isObject( %this.SiblingControl ) )
    {
        %this.SiblingControl.setStateOn( %this.getState() );
    }
}

function VEditorSelectable::OnRightMouseUp( %this, %position, %modifiers, %clickCount )
{
    // Set Selection.
    VerveEditor::SetSelection( %this );
    
    // Repaint.
    VerveEditorWindow.Repaint();
    
    if ( %this.Proxy.isMethod( "DisplayContextMenu" ) )
    {
        // Display Context Menu.
        %this.Proxy.schedule( 32, "DisplayContextMenu", getWord( %position, 0 ),  getWord( %position, 1 ) );
    }
}

function VEditorSelectable::OnMouseUp( %this, %position, %modifiers, %clickCount )
{
    switch ( %modifiers )
    {
        case 0 : VerveEditor::SetSelection( %this );
        
        case 4 : VerveEditor::ToggleSelection( %this );
    }
}

function VEditorSelectable::OnAddSelection( %this )
{
    %this.setStateOn( true );
    
    if ( isObject( %this.SiblingControl ) )
    {
        %this.SiblingControl.setStateOn( true );
    }
    
    // Set First Responder.
    %this.setFirstResponder();
}

function VEditorSelectable::OnRemoveSelection( %this )
{
    %this.setStateOn( false );
    
    if ( isObject( %this.SiblingControl ) )
    {
        %this.SiblingControl.setStateOn( false );
    }
}

//-------------------------------------------------------------------------

function VerveEditor::SetSelection( %object )
{
    VerveEditor::ClearSelection();
    
    VerveEditor::AddSelection( %object );
}

function VerveEditor::ClearSelection()
{
    $VerveEditor::Selection::SurpressCallback = true;
    while ( $VerveEditor::SelectionSet.getCount() > 0 )
    {
        VerveEditor::RemoveSelection( $VerveEditor::SelectionSet.getObject( 0 ) );
    }
        
    if ( $VerveEditor::Selection::SurpressCallback )
    {
        VerveEditor::OnSelectionUpdate();
    }
    
    $VerveEditor::Selection::SurpressCallback = false;
}

function VerveEditor::AddSelection( %object )
{
    $VerveEditor::SelectionSet.add( %object );
    
    if ( %object.isMethod( "OnAddSelection" ) )
    {
        %object.OnAddSelection();
    }
    
    if ( !$VerveEditor::Selection::SurpressCallback )
    {
        VerveEditor::OnSelectionUpdate();
    }
}

function VerveEditor::RemoveSelection( %object )
{
    $VerveEditor::SelectionSet.remove( %object );
    
    if ( %object.isMethod( "OnRemoveSelection" ) )
    {
        %object.OnRemoveSelection();
    }
    
    if ( !$VerveEditor::Selection::SurpressCallback )
    {
        VerveEditor::OnSelectionUpdate();
    }
}

function VerveEditor::ToggleSelection( %object )
{
    if ( !$VerveEditor::SelectionSet.isMember( %object ) )
    {
        VerveEditor::AddSelection( %object );
    }
    else
    {
        VerveEditor::RemoveSelection( %object );
    }
}