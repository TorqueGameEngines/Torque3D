//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------
    
new ScriptObject( VLightObjectGroupPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    Parent      = "VSceneObjectGroupPropertyList";
};

//-----------------------------------------------------------------------------

function VLightObjectGroup::PopulateBuildStack( %this, %stack )
{
    // Ignore Parent Fields.
    //Parent::PopulateBuildStack( %this, %stack );
    
    // Object Reference.
    %lightObjectList = %stack.CreateObjectList( VTorque::getLightObjectClass(), "LightObjectList", "Light Object:" );
    
    if ( VTorque::GetSelectedCount() )
    {
        %selection = VTorque::GetSelectedObject();
        if ( %selection.getName() !$= "" && VTorque::isLightObject( %selection ) )
        {
            // Select Object.
            %lightObjectList.setText( %selection.getName() );
        }
    }
    
    // Create Toggle Track Checkbox.
    %toggleTrackCheckBox = %stack.CreateCheckbox( "ToggleTrackToggle", "Add Toggle Track:" );
    %toggleTrackCheckBox.setStateOn( true );
}

function VLightObjectGroup::ResolveBuildStack( %this, %stack )
{
    // Ignore Parent Fields.
    //Parent::ResolveBuildStack( %this, %stack, %groupObject );
    
    // Fetch the Controller.
    %controller = %this.getRoot();
    
    // Find the Particle Effect List.
    %lightObjectList = %stack.findObjectByInternalName( "LightObjectList", true );
    if ( isObject( %lightObjectList ) )
    {
        // Fetch Selected Object.
        %lightObject = %lightObjectList.getText();
            
        // Data Field Name.
        %dataFieldName = strreplace( %this.Label, " ", "_" );
        
        // Create a New Data Field.
        %controller.addDataField( "STATIC", %dataFieldName );
        
        if ( %lightObject !$= "" )
        {
            // Set the Field Value.
            %controller.setFieldValue( %dataFieldName, %lightObject );
        }
        
        // Reference the Data Field.
        %this.Reference = %dataFieldName;
    }
    
    // Find the Track Toggle.
    %toggleTrackCheckBox = %stack.findObjectByInternalName( "ToggleTrackToggle", true );
    if ( %toggleTrackCheckBox.getValue() )
    {
        // Create the Toggle Track.
        %toggleTrackCheckBox = VerveEditor::AddTrack( "VLightObjectToggleTrack", %this, false );
    }
}

//-----------------------------------------------------------------------------

function VLightObjectGroup::GetAddTrackMenu( %this )
{
    %contextMenu = $VerveEditor::VGroup::ContextMenu[%this.getClassName()];
    if ( !isObject( %contextMenu ) )
    {
        %contextMenu = new PopupMenu()
        {
            SuperClass = "VerveWindowMenu";
            
            IsPopup  = true;
            
            Label    = "VLightObjectGroupAddTrackMenu";
            Position = 0;
            
            Item[0] = "Add Animation Track"    TAB "" TAB "VerveEditor::AddTrack( \"VLightObjectAnimationTrack\" );";
            Item[1] = "Add Motion Track"       TAB "" TAB "VerveEditor::AddTrack( \"VMotionTrack\" );";
            Item[2] = "Add Script Event Track" TAB "" TAB "VerveEditor::AddTrack( \"VScriptEventTrack\" );";
            Item[3] = "Add Sound Effect Track" TAB "" TAB "VerveEditor::AddTrack( \"VSoundEffectTrack\" );";
            Item[4] = "Add Toggle Track"       TAB "" TAB "VerveEditor::AddTrack( \"VLightObjectToggleTrack\" );";
        };
        %contextMenu.Init();
        
        // Cache.
        $VerveEditor::VGroup::ContextMenu[%this.getClassName()] = %contextMenu;
    }
    
    // Enable/Disable Adding Tracks.
    %contextMenu.enableItem( 0, %this.CanAdd( "VLightObjectAnimationTrack" ) );
    %contextMenu.enableItem( 1, %this.CanAdd( "VMotionTrack" ) );
    %contextMenu.enableItem( 2, %this.CanAdd( "VScriptEventTrack" ) );
    %contextMenu.enableItem( 3, %this.CanAdd( "VSoundEffectTrack" ) );
    %contextMenu.enableItem( 4, %this.CanAdd( "VLightObjectToggleTrack" ) );
    
    // Return Menu.
    return %contextMenu;
}

function VLightObjectGroup::isValid( %this )
{
    // Valid?
    return VTorque::isLightObject( %this.getSceneObject() );
}