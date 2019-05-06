//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------
    
new ScriptObject( VParticleEffectGroupPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    Parent      = "VSceneObjectGroupPropertyList";
};

//-----------------------------------------------------------------------------

function VParticleEffectGroup::PopulateBuildStack( %this, %stack )
{
    // Ignore Parent Fields.
    //Parent::PopulateBuildStack( %this, %stack );
    
    // Object Reference.
    %particleEffectList = %stack.CreateObjectList( VTorque::getParticleEffectClass(), "ParticleEffectList", "Particle Effect:" );
    
    if ( VTorque::GetSelectedCount() )
    {
        %selection = VTorque::GetSelectedObject();
        if ( %selection.getName() !$= "" && VTorque::isParticleEffect( %selection ) )
        {
            // Select Object.
            %particleEffectList.setText( %selection.getName() );
        }
    }
    
    // Create Toggle Track Checkbox.
    %toggleTrackCheckBox = %stack.CreateCheckbox( "ToggleTrackToggle", "Add Toggle Track:" );
    %toggleTrackCheckBox.setStateOn( true );
}

function VParticleEffectGroup::ResolveBuildStack( %this, %stack )
{
    // Ignore Parent Fields.
    //Parent::ResolveBuildStack( %this, %stack, %groupObject );
    
    // Fetch the Controller.
    %controller = %this.getRoot();
    
    // Find the Particle Effect List.
    %particleEffectList = %stack.findObjectByInternalName( "ParticleEffectList", true );
    if ( isObject( %particleEffectList ) )
    {
        // Fetch Selected Object.
        %particlEffect = %particleEffectList.getText();
            
        // Data Field Name.
        %dataFieldName = strreplace( %this.Label, " ", "_" );
        
        // Create a New Data Field.
        %controller.addDataField( "STATIC", %dataFieldName );
        
        if ( %particlEffect !$= "" )
        {
            // Set the Field Value.
            %controller.setFieldValue( %dataFieldName, %particlEffect );
        }
        
        // Reference the Data Field.
        %this.Reference = %dataFieldName;
    }
    
    // Find the Track Toggle.
    %toggleTrackCheckBox = %stack.findObjectByInternalName( "ToggleTrackToggle", true );
    if ( %toggleTrackCheckBox.getValue() )
    {
        // Create the Toggle Track.
        %toggleTrackCheckBox = VerveEditor::AddTrack( "VParticleEffectToggleTrack", %this, false );
    }
}

//-----------------------------------------------------------------------------

function VParticleEffectGroup::GetAddTrackMenu( %this )
{
    %contextMenu = $VerveEditor::VGroup::ContextMenu[%this.getClassName()];
    if ( !isObject( %contextMenu ) )
    {
        %contextMenu = new PopupMenu()
        {
            SuperClass = "VerveWindowMenu";
            
            IsPopup  = true;
            
            Label    = "VParticleEffectGroupAddTrackMenu";
            Position = 0;
            
            Item[0] = "Add Motion Track"       TAB "" TAB "VerveEditor::AddTrack( \"VMotionTrack\" );";
            Item[1] = "Add Script Event Track" TAB "" TAB "VerveEditor::AddTrack( \"VScriptEventTrack\" );";
            Item[2] = "Add Sound Effect Track" TAB "" TAB "VerveEditor::AddTrack( \"VSoundEffectTrack\" );";
            Item[3] = "Add Toggle Track"       TAB "" TAB "VerveEditor::AddTrack( \"VParticleEffectToggleTrack\" );";
        };
        %contextMenu.Init();
        
        // Cache.
        $VerveEditor::VGroup::ContextMenu[%this.getClassName()] = %contextMenu;
    }
    
    // Enable/Disable Adding Tracks.
    %contextMenu.enableItem( 0, %this.CanAdd( "VMotionTrack" ) );
    %contextMenu.enableItem( 1, %this.CanAdd( "VScriptEventTrack" ) );
    %contextMenu.enableItem( 2, %this.CanAdd( "VSoundEffectTrack" ) );
    %contextMenu.enableItem( 3, %this.CanAdd( "VParticleEffectToggleTrack" ) );
    
    // Return Menu.
    return %contextMenu;
}

function VParticleEffectGroup::isValid( %this )
{
    // Valid?
    return VTorque::isParticleEffect( %this.getSceneObject() );
}