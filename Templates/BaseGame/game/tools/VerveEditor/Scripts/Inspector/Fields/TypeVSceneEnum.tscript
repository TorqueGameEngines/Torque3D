//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VerveEditor::CreateVSceneEnumField( %fieldContainer, %fieldName )
{
    // Create Enum Menu.
    return VerveEditor::CreateEnumField( %fieldContainer, %fieldName, "VEditorVSceneEnumPropertyField" );
}

function VEditorVSceneEnumPropertyField::OnWake( %this )
{
    // Clear List.
    %this.clear();

    // Iterate Over Groups.
    %groupSet   = $VerveEditor::Controller;
    %groupCount = %groupSet.getCount();
    for ( %i = 0; %i < %groupCount; %i++ )
    {
       %groupObject = %groupSet.getObject( %i );
       if ( %groupObject.isMemberOfClass( "VDirectorGroup" ) )
       {
           break;
       }
       
       // Clear.
       %groupObject = 0;
    }
    
    if ( !isObject( %groupObject ) )
    {
        return;
    }
    
    %trackSet   = %groupObject;
    %trackCount = %trackSet.getCount();
    for ( %i = 0; %i < %trackCount; %i++ )
    {
        %trackObject = %trackSet.getObject( %i );
        if ( %trackObject.isMemberOfClass( "VDirectorTrack" ) )
        {
            break;
        }
       
       // Clear.
       %trackObject = 0;
    }
    
    if ( !isObject( %groupObject ) )
    {
        return;
    }
    
    %eventSet   = %trackObject;
    %eventCount = %eventSet.getCount();
    for ( %i = 0; %i < %eventCount; %i++ )
    {
        %eventObject = %eventSet.getObject( %i );
        if ( %eventObject.Label !$= "" && %this.findText( %eventObject.Label ) == -1 )
        {
            %this.add( %eventObject.Label, %this.Size() );
        }
    }
    
    // Sort.
    %this.sort();
}