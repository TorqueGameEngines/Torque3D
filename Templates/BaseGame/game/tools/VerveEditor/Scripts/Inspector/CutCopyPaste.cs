//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditor::CanCut()
{
    return VerveEditor::CanCopy();
}

function VerveEditor::CutSelection()
{
    if ( !isObject( $VerveEditor::Controller ) || !VerveEditor::HasSelection() )
    {
        return;
    }
    
    %targetObject = $VerveEditor::InspectorObject;
    if ( isObject( %targetObject ) )
    {
        // Write To File.
        %targetObject.writeFile( $VerveEditor::TemplateVClipboard );
        
        // Store Object Type.
        $VerveEditor::TemplateVClipboardObject = %targetObject;
        
        // Delete Object.
        %targetObject.Delete();
        
        // Refresh Editor.
        VerveEditor::Refresh();
    }
}

function VerveEditor::CanCopy()
{
    if ( VerveEditor::HasSelection() )
    {
        if ( $VerveEditor::InspectorObject == $VerveEditor::Controller )
        {
            return false;
        }
    }
    
    if ( $VerveEditor::InspectorObject.isMethod( "CanCopy" ) )
    {
        if ( !$VerveEditor::InspectorObject.CanCopy() )
        {
            return false;
        }
    }
    
    return ActiveActionMapSet.isMember( VerveEditorEditMap );
}

function VerveEditor::CopySelection()
{
    if ( !isObject( $VerveEditor::Controller ) || !VerveEditor::CanCopy() )
    {
        return;
    }
    
    %targetObject = $VerveEditor::InspectorObject;
    if ( isObject( %targetObject ) )
    {
        // Write To File.
        %targetObject.writeFile( $VerveEditor::TemplateVClipboard );
        
        // Reference Object.
        $VerveEditor::TemplateVClipboardObject = %targetObject;
    }
}

function VerveEditor::CanPaste()
{
    if ( !VerveEditor::HasSelection() || !isFile( $VerveEditor::TemplateVClipboard ) )
    {
        return false;
    }
    
    return $VerveEditor::InspectorObject.CanPaste( $VerveEditor::TemplateVClipboardObject );
}

function VerveEditor::Paste()
{
    if ( !isObject( $VerveEditor::Controller ) || !VerveEditor::CanPaste() )
    {
        return;
    }
    
    if ( $VerveEditor::InspectorObject.getId() == $VerveEditor::Controller.getId() )
    {
        // Special Paste.
        VerveEditor::AddTemplateGroup( $VerveEditor::TemplateVClipboard );
        
        return;
    }
    
    if ( isObject( $VerveEditor::InspectorObject ) )
    {
        // Group History Actions.
        VerveEditor::ToggleHistoryGroup();
        
        // Read From File.
        $VerveEditor::InspectorObject.readFile( $VerveEditor::TemplateVClipboard );
        
        // Finish Up.
        VerveEditor::ToggleHistoryGroup();
        
        // Refresh Editor.
        VerveEditor::Refresh();
    }
}

function VerveEditor::DeleteSelection()
{
    if ( !isObject( $VerveEditor::Controller ) || !VerveEditor::HasSelection() )
    {
        return;
    }
    
    %selectionSet = $VerveEditor::SelectionSet;
    while ( %selectionSet.getCount() > 0 )
    {
        %selection = %selectionSet.getObject( 0 );
        
        if ( isObject( %selection.SiblingControl ) )
        {
            // Delete Sibling Control.
            %selection.SiblingControl.delete();
        }
        
        if ( isObject( %selection.Proxy ) )
        {
            // Do Callback?
            if ( %selection.Proxy.isMethod( "onRemove" ) )
            {
                // Quick Callback.
                %selection.Proxy.onRemove();
            }
            
            // Delete Reference Object.
            %selection.Proxy.delete();
        }
        
        // Delete Control.
        %selection.delete();
    }
    
    // Refresh.
    VerveEditor::Refresh();
}