//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

$VerveEditor::TemplateFolder           = getMainDotCsDir() @ "/" @ expandFileName( "tools/VerveEditor/Templates" );
$VerveEditor::TemplateCustomFolder     = $VerveEditor::TemplateFolder @ "/Custom";
$VerveEditor::TemplateVClipboard       = $VerveEditor::TemplateFolder @ "/VClipboard.vsf";
$VerveEditor::TemplateVClipboardObject = "";

//-----------------------------------------------------------------------------

function VerveCustomTemplateMenu::Init( %this )
{
    %fieldCount = 0;
    %fileSpec   = $VerveEditor::TemplateCustomFolder @ "/*.vsf";
    for ( %file = findFirstFile( %fileSpec ); %file !$= ""; %file = findNextFile( %fileSpec ) )
    {
        // Create Item.
        %this.Item[%fieldCount] = "Add" SPC fileBase( %file ) TAB "" TAB "VerveEditor::AddTemplateGroup(\"" @ %file @ "\");";
        
        // Increment.
        %fieldCount += 1;
    }
    
    // Sort By File Name.
    for ( %j = 0; %j < %fieldCount; %j++ )
    {
        for ( %i = %fieldCount - 1; %i > %j; %i-- )
        {
            %itemA = getField( %this.Item[%i - 0], 0 );
            %itemB = getField( %this.Item[%i - 1], 0 );

            if ( strcmp( strlwr( %itemA ), strlwr( %itemB ) ) < 0 )
            {
                // Swap.
                %itemTmp = %this.Item[%i];
                %this.Item[%i - 0] = %this.Item[%i - 1];
                %this.Item[%i - 1] = %itemTmp;
            }
        }
    }
    
    // Parent Init.
    Parent::Init( %this );
}

function VEditorAddGroupButton::DisplayContextMenu( %this, %x, %y )
{
    // Use Current Controller.
    %targetController = $VerveEditor::Controller;
    
    // Get Context Menu.
    %contextMenu = %targetController.GetAddGroupMenu();
    if ( !isObject( %contextMenu ) )
    {
        return;
    }
    
    if ( %x $= "" || %y $= "" )
    {
        %position = %this.getGlobalPosition();
        %extent   = %this.getExtent();
        
        %x = getWord( %position, 0 ) + getWord( %extent, 0 );
        %y = getWord( %position, 1 );
    }
    
    // Display.
    if($Verve::UseSeparateWindow)
      %contextMenu.showPopup( VerveEditorWindow, %x, %y );
    else
      %contextMenu.showPopup( Canvas, %x, %y );
}

function VEditorAddTrackButton::DisplayContextMenu( %this, %x, %y )
{
    if ( !isObject( $VerveEditor::InspectorObject ) )
    {
        // No Controller or Selection.
        return;
    }
    
    // Use Current Selection.
    %targetGroup = $VerveEditor::InspectorObject;
    
    if ( !%targetGroup.isMemberOfClass( "VGroup" ) )
    {
        // Invalid Target.
        return;
    }
    
    // Get Context Menu.
    %contextMenu = %targetGroup.GetAddTrackMenu();
    if ( !isObject( %contextMenu ) )
    {
        return;
    }
    
    if ( %x $= "" || %y $= "" )
    {
        %position = %this.getGlobalPosition();
        %extent   = %this.getExtent();
        
        %x = getWord( %position, 0 ) + getWord( %extent, 0 );
        %y = getWord( %position, 1 );
    }
    
    // Display.
    // Display.
    if($Verve::UseSeparateWindow)
      %contextMenu.showPopup( VerveEditorWindow, %x, %y );
    else
      %contextMenu.showPopup( Canvas, %x, %y );
}