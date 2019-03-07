//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

$VerveEditor::FilePath = "sequences";
$VerveEditor::FileSpec = "Verve Sequence Files (*.vsf)|*.vsf|All Files (*.*)|*.*|";

//-----------------------------------------------------------------------------

function VerveEditor::GetFileTarget( %type )
{
    %filePath = $VerveEditor::FilePath;
    if ( strlen( $Pref::VerveEditor::FilePath ) > 0 )
    {
        %filePath = $Pref::VerveEditor::FilePath;
    }

    %fileDialog = new ( %type @ "FileDialog" )()
    {
        Filters     = $VerveEditor::FileSpec;
        DefaultPath = %filePath;
        ChangePath  = false;
        MustExist   = true;
    };

    // Record the file name
    %filename = "";
    if ( %fileDialog.Execute() )
    {
        %filename = %fileDialog.FileName;

        // Store the preference
        $Pref::VerveEditor::FilePath = makeRelativePath( filePath( %filename ), getMainDotCsDir() );
    }

    // Delete the dialog
    %fileDialog.delete();

    // Return the filename
    return %filename;
}

function VerveEditor::NewFile()
{
    if ( !isObject( $VerveEditor::Controller ) )
    {
        return;
    }
    
    // Save?
    if ( !VerveEditor::SavePrompt() )
    {
        return;
    }
    
    // Clear Sequence Lists.
    $VerveEditor::Controller.clear();
    
    // Clear File.
    $VerveEditor::Controller.FileName = "";
    
    // Reset Properties.
    $VerveEditor::Controller.Time      = 0;
    $VerveEditor::Controller.Duration  = 5000;
    $VerveEditor::Controller.TimeScale = 1.0;
    
    // Clear Editor History.
    VerveEditor::ClearHistory();
    
    // Refresh Editor.
    VerveEditor::Refresh();
}

function VerveEditor::LoadFile( %fileName )
{
    if ( !isObject( $VerveEditor::Controller ) )
    {
        return;
    }
    
    // Save?
    if ( !VerveEditor::SavePrompt() )
    {
        return;
    }
    
    if ( %fileName $= "" )
    {
        %fileName = VerveEditor::GetFileTarget( "Open" );
    }
    
    // Clear File.
    $VerveEditor::Controller.FileName = "";
    
    if ( $VerveEditor::Controller.readFile( %fileName ) )
    {
        // Pause.
        VerveEditor::Pause();
        
        // Store the File.
        $VerveEditor::Controller.FileName = %fileName;
        
        // Update File History.
        VerveEditor::UpdateFileHistory( %fileName );
        
        // Clear Editor History.
        VerveEditor::ClearHistory();
        
        // Refresh Editor.
        VerveEditor::Refresh();
        
        return true;
    }
    
    // Argh!
    // Attempting to load a file which results in failure means the existing
    // sequence is messed up, ouch! Do something better than creating a new
    // sequence...
    VerveEditor::NewFile();
    
    return false;
}

function VerveEditor::SaveFile( %forceSaveAs )
{
    if ( !isObject( $VerveEditor::Controller ) )
    {
        return false;
    }
    
    %fileName = $VerveEditor::Controller.FileName;
    if ( %forceSaveAs || %fileName $= "" )
    {
        %fileName = VerveEditor::GetFileTarget( "Save" );
        if ( %fileName $= "" )
        {
            // No Save.
            return false;
        }
    }
    
    if ( fileExt( fileName( %fileName ) ) $= "" )
    {
        // Add Extension.
        %fileName = %fileName @ ".vsf";
    }
    
    // Write.
    $VerveEditor::Controller.writeFile( %fileName );
    
    // Store the File.
    $VerveEditor::Controller.FileName = %fileName;
    
    // Update File History.
    VerveEditor::UpdateFileHistory( %fileName );
    
    // Clear Dirty.
    VerveEditor::ClearDirty();
    
    // Update Window Title.
    VerveEditorWindow.UpdateWindowTitle();
    
    // Valid Save.
    return true;
}

function VerveEditor::SavePrompt()
{
    if ( !VerveEditor::IsDirty() )
    {
        return true;
    }
    
    %result = messageBox( "Verve Editor", "Save Changes to your sequence?", "SaveDontSave", "Warning" );
    if ( %result $= $MROk )
    {
        // Save.
        return VerveEditor::SaveFile();
    }
    
    return true;
}

function VerveEditor::SavePromptCancel()
{
    if ( !VerveEditor::IsDirty() )
    {
        return true;
    }
    
    %result = messageBox( "Verve Editor", "Save Changes to your sequence?", "SaveDontSaveCancel", "Warning" );
    if ( %result $= $MRCancel )
    {
        return false;
    }
    
    if ( %result $= $MROk )
    {
        // Save.
        return VerveEditor::SaveFile();
    }
    
    return true;
}

function VerveEditor::UpdateFileHistory( %filePath )
{
    // Make Relative.
    %fileLabel = makeRelativePath( %filePath, getMainDotCsDir() );
    
    // Select an Index.
    %initIndex = $Pref::VerveEditor::RecentFileSize;
    for ( %i = 0; %i < %initIndex; %i++ )
    {
        %prefFile = $Pref::VerveEditor::RecentFile[%i];
        if ( %prefFile $= %fileLabel )
        {
            %initIndex = %i;
            break;
        }
    }
    
    // Push Others Down.
    for ( %i = %initIndex; %i > 0; %i-- )
    {
        $Pref::VerveEditor::RecentFile[%i] = $Pref::VerveEditor::RecentFile[%i - 1];
    }
    
    // Push to the Front.
    $Pref::VerveEditor::RecentFile[0] = %fileLabel;
}