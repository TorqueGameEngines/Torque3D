//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveWindowMenu::Clear( %this )
{
    while ( %this.getItemCount() > 0 )
    {
        %this.removeItem( 0 );
    }
}

function VerveWindowMenu::Init( %this )
{
    // Clear Items.
    %this.Clear();
    
    %i = 0;
    while ( %this.Item[%i] !$= "" )
    {
        %itemString = %this.Item[%i];
        %itemLabel  = getField( %itemString, 0 );
        %itemAccel  = getField( %itemString, 1 );
        %itemMethod = getField( %itemString, 2 );
        %itemMap    = getField( %itemString, 3 );
        
        if ( !isObject( %itemMap ) )
        {
            %itemMap = VerveEditorMap;
        }
        
        if ( isObject( %itemAccel ) )
        {
            %this.insertSubMenu( %i, %itemLabel, %itemAccel );
        }
        else
        {
            // Insert Item.
            %this.insertItem( %i, %itemLabel, %itemAccel );
            
            if ( !%this.IsPopup && %itemAccel !$= "" && isObject( %itemMap ) )
            {
                // Label Hack...
                switch$( %itemAccel )
                {
                    case "DEL" : %itemAccel = "DELETE";
                    case "ESC" : %itemAccel = "ESCAPE";
                }
                
                // Perform Keybind.
                %itemMap.bindCmd( "keyboard", strreplace( %itemAccel, "+", " " ), %itemMethod, "" );
            }
        }
        
        %i++;
    }
}

function VerveWindowMenu::onSelectItem( %this, %id, %text )
{
    %command = getField( %this.item[%id], 2 );
    if ( %command !$= "" )
    {
        eval( %command );
        return true;
    }
    
    return false;
}

//-------------------------------------------------------------------------

function VerveEditorWindow::onCreateMenu( %this )
{
    // Store Menu Bars.
    if ( !isObject( %this.MenuSet ) )
    {
        %this.MenuSet = new SimSet();
    }
    
    // CMD Key.
    %cmdKey = $platform $= "macos" ? "Cmd" : "Ctrl";
    
    //---------------------------------------------------------------------
    //
    // File Menu
    //
    //---------------------------------------------------------------------
    
    %recentSequenceMenu = new PopupMenu()
    {
        Class      = "VerveRecentFileMenu";
        SuperClass = "VerveWindowMenu";
        
        Label      = "Recent Files";
        Position   = 0;
        
        Item[0]    = "None";
    };

    %fileMenu = new PopupMenu()
    {
        SuperClass = "VerveWindowMenu";
        
        Label    = "&File";
        Position = 0;
        
        Item[0] = "&New"         TAB %cmdKey @ "+N"       TAB "VerveEditor::NewFile();";
        Item[1] = "&Open"        TAB %cmdKey @ "+O"       TAB "VerveEditor::LoadFile();";
        Item[2] = ""             TAB "";
        Item[3] = "&Save"        TAB %cmdKey @ "+S"       TAB "VerveEditor::SaveFile();";
        Item[4] = "Save &As"     TAB %cmdKey @ "-Shift+S" TAB "VerveEditor::SaveFile( true );";
        Item[5] = ""             TAB "";
        Item[6] = "Recent Files" TAB %recentSequenceMenu;
    };
    %this.MenuSet.add( %fileMenu );
    
    if ( $platform !$= "macos" )
    {
        %fileMenu.Item[7] = ""       TAB "";
        %fileMenu.Item[8] = "&Close" TAB %cmdKey @ "+F4" TAB "ToggleVerveEditor( true );";
    }
    
    //---------------------------------------------------------------------
    //
    // Edit Menu
    //
    //---------------------------------------------------------------------
    
    %editMenu = new PopupMenu()
    {
        Class      = "VerveWindowEditMenu";
        SuperClass = "VerveWindowMenu";
        
        Label    = "&Edit";
        Position = 1;
        
        Item[0]  = "&Undo"            TAB %cmdKey @ "+Z" TAB "VerveEditor::Undo();";
        Item[1]  = "&Redo"            TAB %cmdKey @ "+Y" TAB "VerveEditor::Redo();";
        Item[2]  = ""                 TAB "";
        Item[3]  = "Cu&t"             TAB %cmdKey @ "+X" TAB "VerveEditor::CutSelection();"    TAB VerveEditorEditMap;
        Item[4]  = "&Copy"            TAB %cmdKey @ "+C" TAB "VerveEditor::CopySelection();"   TAB VerveEditorEditMap;
        Item[5]  = "&Paste"           TAB %cmdKey @ "+V" TAB "VerveEditor::Paste();"           TAB VerveEditorEditMap;
        
        Item[6]  = ""                 TAB "";
        Item[7]  = "&Delete"          TAB "Del"          TAB "VerveEditor::DeleteSelection();" TAB VerveEditorEditMap;
        
        Item[8]  = ""                 TAB "";
        Item[9]  = "&Clear Selection" TAB "Esc"          TAB "VerveEditor::ClearSelection();";
        
        Item[10] = ""                 TAB "";
        Item[11] = "&Preferences"     TAB %cmdKey @ "+P" TAB "VerveEditor::LaunchEditorPreferences();";
    };
    %this.MenuSet.add( %editMenu );
    
    // Init Popups.
    %fileMenu.Init();
    %editMenu.Init();
    
    // Attach.
    %fileMenu.attachToMenuBar( %this, %fileMenu.Position, %fileMenu.Label );
    %editMenu.attachToMenuBar( %this, %editMenu.Position, %editMenu.Label );
}

function VerveEditorWindow::ClearMenu( %this )
{
    if ( isObject( %this.MenuSet ) )
    {
        while( %this.MenuSet.getCount() > 0 )
        {
            // Fetch Object.
            %menuObject = %this.MenuSet.getObject( 0 );
            
            // Detach.
            %menuObject.removeFromMenuBar();
            
            // Delete.
            %menuObject.delete();
        }
    }
}

function VerveEditorWindow::onDestroyMenu( %this )
{
    // Clear the Menu.
    %this.ClearMenu();
    
    // Delete the Menu Set.
    if ( isObject( %this.MenuSet ) )
    {
        %this.MenuSet.delete();
    }
}

function VerveRecentFileMenu::onMenuSelect( %this )
{
    %this.Refresh();
}

function VerveRecentFileMenu::onSelectItem( %this, %index, %text )
{
    // Load the File.
    VerveEditor::LoadFile( $Pref::VerveEditor::RecentFile[ %index ] );
    
    return false;
}

function VerveRecentFileMenu::Refresh( %this )
{
    // Clear The List.
    %this.Clear();
    
    // Populate Menu.
    if ( $Pref::VerveEditor::RecentFileSize == 0 || $Pref::VerveEditor::RecentFile[0] $= "" )
    {
        // Insert Default Item.
        %this.insertItem( 0, %this.Item[0], "" );
        
        // Disable.
        %this.enableItem( 0, false );
    }
    else
    {
        for ( %i = 0; %i < $Pref::VerveEditor::RecentFileSize; %i++ )
        {
            // Valid?
            if ( $Pref::VerveEditor::RecentFile[%i] $= "" )
            {
                // Nope!
                break;
            }
            
            // Insert Item.
            %this.insertItem( %i, makeRelativePath( $Pref::VerveEditor::RecentFile[%i], $VerveEditor::FilePath ), "" );
        }
    }
}

function VerveWindowEditMenu::onMenuSelect( %this )
{
    %this.Refresh();
}

function VerveWindowEditMenu::Refresh( %this )
{
    // Undo & Redo.
    %this.enableItem( 0, VerveEditor::CanUndo() );
    %this.enableItem( 1, VerveEditor::CanRedo() );
    
    // Cut, Copy & Paste.
    %this.enableItem( 3, VerveEditor::CanCopy() );
    %this.enableItem( 4, VerveEditor::CanCopy() );
    %this.enableItem( 5, VerveEditor::CanPaste() );
    
    // Delete.
    %this.enableItem( 7, VerveEditor::CanCopy() );
    
    // Clear Selection.
    %this.enableItem( 9, VerveEditor::CanCopy() );
}