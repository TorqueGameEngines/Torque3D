//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

$VerveEditor::MapStore = new SimSet();

//-----------------------------------------------------------------------------

function VerveEditorWindow::Open()
{
    if ( isObject( VerveEditorWindow ) )
    {
        return;
    }
    
    // Create the Controller.
    VerveEditor::CreateController();
    
    // Create ActionMap.
    %actionMap = new ActionMap( VerveEditorMap );
    %actionMap.pop();
    
    // Create Edit ActionMap.
    %editActionMap = new ActionMap( VerveEditorEditMap );
    %editActionMap.pop();
    
    // Create Window.
    if($Verve::UseSeparateWindow)
    {
       %editorWindow = new VEditorWindow( VerveEditorWindow );
       
       // Init Window?
       if ( $Pref::VerveEditor::WindowSize $= "" )
       {
           // Default Window Size.
           %editorWindow.setVideoMode( 800, 253, false );
       }
       else
       {
           // Last Known Window Size.
           %editorWindow.setVideoMode( getWord( $Pref::VerveEditor::WindowSize, 0 ),
                                       getWord( $Pref::VerveEditor::WindowSize, 1 ),
                                       false );
       }
       
       return %editorWindow;
    }
    else
    {
       %editorWindow = new guiWindowCtrl(VerveEditorWindow)
       {
         position = "0 0";
         extent = "1024 768";
         minExtent = "8 2";
         horizSizing = "right";
         vertSizing = "bottom";
       };
       return %editorWindow;  
    }
}

function VerveEditorWindow::UpdateWindowTitle( %this )
{
    %fileName = fileName( $VerveEditor::Controller.FileName );
    if ( %fileName $= "" )
    {
        %fileName = "Untitled.vsf";
    }
    
    if ( VerveEditor::IsDirty() )
    {
        // Signify Unsaved Work.
        %fileName = %fileName @ "*";
    }
    
    // Set Title.
    %this.setWindowTitle( %fileName SPC "- Verve"  );
}

function VerveEditorWindow::onGainFocus( %this )
{
   if($Verve::UseSeparateWindow)
      return;
      
    %activeSet = ActiveActionMapSet;
    while ( %activeSet.getCount() > 0 )
    {
        // Get Object.
        %activeMap = %activeSet.getObject( 0 );
        
        // Pop It.
        %activeMap.pop();
        
        if ( %activeMap != GlobalActionMap.getId() )
        {
            // Store It.
            $VerveEditor::MapStore.add( %activeMap );
        }
    }
    
    // Give Our Commands Preference.
    GlobalActionMap.pop();
        VerveEditorMap.push();
        VerveEditorEditMap.push();
    GlobalActionMap.push();
    
    // Reset Cursor.
    %this.resetCursor();
}

function VerveEditorWindow::onLoseFocus( %this )
{
    %activeSet = $VerveEditor::MapStore;
    // Active Set?
    if ( isObject( %activeSet ) )
    {
        while ( %activeSet.getCount() > 0 )
        {
            // Get Object.
            %activeMap = %activeSet.getObject( 0 );
            
            // Push It.
            %activeMap.push();
            
            // Remove It.
            $VerveEditor::MapStore.remove( %activeMap );
        }
    }
    
    // Valid Map?
    if ( isObject( VerveEditorMap ) )
    {
        VerveEditorMap.pop();
    }
    
    // Valid Map?
    if ( isObject( VerveEditorEditMap ) )
    {
        VerveEditorEditMap.pop();
    }
}

function VerveEditorWindow::onRemove( %this )
{
    // Save?
    // Note: This crashes the game!
    //       At this stage, if the editor is dirty a save prompt should have
    //       been made already... Lets hope!
    //VerveEditor::SavePrompt();
    
    // Clear Inspector.
    VerveEditorPropertyStack.ClearStack();
    
    if ( isObject( VerveEditorMap ) )
    {
        VerveEditorMap.delete();
    }
    
    if ( isObject( VerveEditorEditMap ) )
    {
        VerveEditorEditMap.delete();
    }
    
    // Clear the Menu.
    %this.ClearMenu();
    
    // Force Reset.
    %this.onLoseFocus();
    
    // Store the Window Extents on Shutdown.
    $Pref::VerveEditor::WindowSize = getWords( %this.getVideoMode(), 0, 1 );
    
    // Playing?
    if ( $VerveEditor::Controller.isPlaying() )
    {
        // Stop, but do not reset.
        $VerveEditor::Controller.stop( false );
    }
    
    // Clear the Current Sequence.
    $VerveEditor::Controller.clear();
    // Clear the File Name.
    $VerveEditor::Controller.FileName = "";
    
    /*
    // Delete the Controller.
    VerveEditor::DeleteController();
    */
    
    if ( isFile( $VerveEditor::TemplateVClipboard ) )
    {
        // Clear Clipboard.
        fileDelete( $VerveEditor::TemplateVClipboard );
    }
    
    // World Editor Initialised?
    if ( isObject( VerveEditorPlugin.ToolbarButton ) )
    {
        // Toggle Off the Plugin Button.
        VerveEditorPlugin.ToolbarButton.setStateOn( false );
    }
}

function VerveEditorWindow::onWindowClose( %this )
{
    if ( !VerveEditor::SavePromptCancel() )
    {
        // Don't Close.
        return;
    }
    
    // Delete Window.
    %this.schedule( 0, delete );
}