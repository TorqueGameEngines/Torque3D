//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------
    
new ScriptObject( VSceneObjectGroupPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    Parent      = "VGroupPropertyList";
    
    Group[0]    = "VGroup";
    Field[0, 0] = "Reference";
    Type[0, 0]  = "VControllerDataEnum";
};

//-----------------------------------------------------------------------------

function VSceneObjectGroup::OnSelect( %this )
{
    if ( !%this.isValid() )
    {
        // Invalid Object.
        return;
    }
    
    // Update Selection.
    VTorque::SetSelectedObject( %this.getSceneObject() );
}

function VSceneObjectGroup::isValid( %this )
{
    // Valid?
    return VTorque::isSceneObject( %this.getSceneObject() );
}

//-----------------------------------------------------------------------------

function VSceneObjectGroup::PopulateBuildStack( %this, %stack )
{
    Parent::PopulateBuildStack( %this, %stack );
    
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
    
    // Create Motion Track Checkbox.
    %motionTrackCheckBox = %stack.CreateCheckbox( "MotionTrackToggle", "Add Motion Track:" );
    %motionTrackCheckBox.setStateOn( true );
    
    // Object Reference.
    %pathObjectList = %stack.CreateObjectList( "VPath", "PathObjectList", "Path Object:" );
}

function VSceneObjectGroup::ResolveBuildStack( %this, %stack )
{
    Parent::ResolveBuildStack( %this, %stack, %groupObject );
    
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
    
    // Find the Path Toggle.
    %motionTrackCheckBox = %stack.findObjectByInternalName( "MotionTrackToggle", true );
    if ( %motionTrackCheckBox.getValue() )
    {
        // Create the Motion Track.
        %motionTrack = VerveEditor::AddTrack( "VMotionTrack", %this, false );
        
        %pathObjectList = %stack.findObjectByInternalName( "PathObjectList", true );
        if ( isObject( %pathObjectList ) )
        {
            // Fetch Selected Object.
            %pathObject = %pathObjectList.getText();
            
            // Data Field Name.
            %dataFieldName = strreplace( %this.Label @ "Path", " ", "_" );
            
            // Create a New Data Field.
            %controller.addDataField( "STATIC", %dataFieldName );
        
            if ( %pathObject !$= "" )
            {
                // Set the Field Value.
                %controller.setFieldValue( %dataFieldName, %pathObject );
            }
            
            // Reference the Data Field.
            %motionTrack.Reference = %dataFieldName;
        }
    }
}

//-----------------------------------------------------------------------------

function VSceneObjectGroup::GetAddTrackMenu( %this )
{
    %contextMenu = $VerveEditor::VGroup::ContextMenu[%this.getClassName()];
    if ( !isObject( %contextMenu ) )
    {
        %contextMenu = new PopupMenu()
        {
            SuperClass = "VerveWindowMenu";
            
            IsPopup  = true;
            
            Label    = "VSceneObjectGroupAddTrackMenu";
            Position = 0;
            
            Item[0] = "Add Animation Track"    TAB "" TAB "VerveEditor::AddTrack( \"VShapeAnimationTrack\" );";
            Item[1] = "Add Motion Track"       TAB "" TAB "VerveEditor::AddTrack( \"VMotionTrack\" );";
            Item[2] = "Add Script Event Track" TAB "" TAB "VerveEditor::AddTrack( \"VScriptEventTrack\" );";
            Item[3] = "Add Sound Effect Track" TAB "" TAB "VerveEditor::AddTrack( \"VSoundEffectTrack\" );";
        };
        %contextMenu.Init();
        
        // Cache.
        $VerveEditor::VGroup::ContextMenu[%this.getClassName()] = %contextMenu;
    }
    
    // Enable/Disable Adding Tracks.
    %contextMenu.enableItem( 0, %this.CanAdd( "VShapeAnimationTrack" ) );
    %contextMenu.enableItem( 1, %this.CanAdd( "VMotionTrack" ) );
    %contextMenu.enableItem( 2, %this.CanAdd( "VScriptEventTrack" ) );
    %contextMenu.enableItem( 3, %this.CanAdd( "VSoundEffectTrack" ) );
    
    // Return Menu.
    return %contextMenu;
}