//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------
    
new ScriptObject( VSpawnSphereGroupPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    Parent      = "VSceneObjectGroupPropertyList";
};

//-----------------------------------------------------------------------------

function VSceneObjectGroup::PopulateBuildStack( %this, %stack )
{
    VGroup::PopulateBuildStack( %this, %stack );
    
    // Object Reference.
    %sceneObjectList = %stack.CreateObjectList( "SceneObject", "SceneObjectList", "Scene Object:" );
    
    if ( VTorque::GetSelectedCount() )
    {
        %selection = VTorque::GetSelectedObject();
        if ( %selection.getName() !$= "" && %selection.isMemberOfClass( "SceneObject" ) )
        {
            // Select Object.
            %sceneObjectList.setText( %selection.getName() );
        }
    }
}

function VSceneObjectGroup::ResolveBuildStack( %this, %stack )
{
    VGroup::ResolveBuildStack( %this, %stack, %groupObject );
    
    // Fetch the Controller.
    %controller = %this.getRoot();
    
    // Find the Scene Object List.
    %sceneObjectList = %stack.findObjectByInternalName( "SceneObjectList", true );
    if ( isObject( %sceneObjectList ) )
    {
        // Fetch Selected Object.
        %sceneObject = %sceneObjectList.getText();
            
        // Data Field Name.
        %dataFieldName = strreplace( %this.Label, " ", "_" );
        
        // Create a New Data Field.
        %controller.addDataField( "STATIC", %dataFieldName );
        
        if ( %sceneObject !$= "" )
        {
            // Set the Field Value.
            %controller.setFieldValue( %dataFieldName, %sceneObject );
        }
        
        // Reference the Data Field.
        %this.Reference = %dataFieldName;
    }
}

//-----------------------------------------------------------------------------

function VSpawnSphereGroup::GetAddTrackMenu( %this )
{
    %contextMenu = $VerveEditor::VGroup::ContextMenu[%this.getClassName()];
    if ( !isObject( %contextMenu ) )
    {
        %contextMenu = new PopupMenu()
        {
            SuperClass = "VerveWindowMenu";
            
            IsPopup  = true;
            
            Label    = "VSpawnSphereGroupAddTrackMenu";
            Position = 0;
            
            Item[0] = "Add Script Event Track" TAB "" TAB "VerveEditor::AddTrack( \"VScriptEventTrack\" );";
            Item[1] = "Add Spawn Target Track" TAB "" TAB "VerveEditor::AddTrack( \"VSpawnSphereSpawnTargetTrack\" );";
        };
        %contextMenu.Init();
        
        // Cache.
        $VerveEditor::VGroup::ContextMenu[%this.getClassName()] = %contextMenu;
    }
    
    // Enable/Disable Adding Tracks.
    %contextMenu.enableItem( 0, %this.CanAdd( "VScriptEventTrack" ) );
    %contextMenu.enableItem( 1, %this.CanAdd( "VSpawnSphereSpawnTargetTrack" ) );
    
    // Return Menu.
    return %contextMenu;
}

function VSpawnSphereGroup::isValid( %this )
{
    // Valid?
    return VTorque::isSpawnSphereObject( %this.getSceneObject() );
}