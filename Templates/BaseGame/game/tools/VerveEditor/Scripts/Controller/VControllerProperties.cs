//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

function VControllerPropertyList::CreateInspectorGroup( %this, %targetStack )
{
    %baseGroup = Parent::CreateInspectorGroup( %this, %targetStack );
    if ( %baseGroup.getClassName() !$= "ScriptGroup" )
    {
        // Temp Store.
        %temp = %baseGroup;
        
        // Create SimSet.
        %baseGroup = new SimSet();
        
        // Add Original Control.
        %baseGroup.add( %temp );
    }
    
    // Create Data Table Group.
    %groupRollout  = %targetStack.CreatePropertyRollout( "VController DataTable" );
    %propertyStack = %groupRollout.Stack;
    
    // Reference.
    %propertyStack.InternalName = "DataTableStack";
    
    // Store.
    %baseGroup.add( %groupRollout );
    
    // Return.
    return %baseGroup;
}

function VControllerPropertyList::InspectObject( %this, %object )
{
    if ( !%object.isMemberOfClass( "VController" ) )
    {
        // Invalid Object.
        return;
    }
    
    // Default Inspect.
    Parent::InspectObject( %this, %object );
    
    // Update Data Table.
    %dataTableStack = %this.ControlCache.findObjectByInternalName( "DataTableStack", true );
    if ( !isObject( %dataTableStack ) )
    {
        // Invalid Table.
        return;
    }
    
    // Clear Stack.
    while ( %dataTableStack.getCount() > 1 )
    {
        // Delete Object.
        %dataTableStack.getObject( 1 ).delete();
    }
    
    %dataFieldCount = %object.getDataFieldCount();
    for ( %i = 0; %i < %dataFieldCount; %i++ )
    {
        // Add To List.
        %dataFieldList = trim( %dataFieldList SPC %object.getDataFieldName( %i ) );
    }
    
    // Sort Word List.
    %dataFieldList = sortWordList( %dataFieldList );
    
    for ( %i = 0; %i < %dataFieldCount; %i++ )
    {
        // Fetch Field Name.
        %dataFieldName = getWord( %dataFieldList, %i );
        
        // Create Field.
        VerveEditor::CreateField( %dataTableStack, %dataFieldName, "Data" );
    }
    
    // Create Add Field.
    VerveEditor::CreateAddDataField( %dataTableStack );
    
    // Update.
    %dataTableStack.InspectObject( %object );
}

function VController::DisplayContextMenu( %this, %x, %y )
{
    %contextMenu = $VerveEditor::VController::ContextMenu;
    if ( !isObject( %contextMenu ) )
    {
        %contextMenu = new PopupMenu()
        {
            SuperClass = "VerveWindowMenu";
            
            IsPopup  = true;
            
            Label    = "VControllerContextMenu";
            Position = 0;
            
            Item[0] = "Add Group" TAB "";
            
            Item[1] = "" TAB "";
             
            Item[2] = "Cu&t"     TAB "" TAB "";
            Item[3] = "&Copy"    TAB "" TAB "";
            Item[4] = "&Paste"   TAB "" TAB "VerveEditor::Paste();";
            
            Item[5] = "" TAB "";
            
            Item[6] = "&Delete"  TAB "" TAB "";
            
            PasteIndex = 4;
        };
        %contextMenu.Init();
        
        // Disable Cut, Copy & Delete.
        %contextMenu.enableItem( 2, false );
        %contextMenu.enableItem( 3, false );
        %contextMenu.enableItem( 6, false );
        
        // Cache.
        $VerveEditor::VController::ContextMenu = %contextMenu;
    }
    
    // Remove Add Menu.
    %contextMenu.removeItem( %contextMenu.AddIndex );
    
    // Insert Menu.
    %contextMenu.insertSubMenu( %contextMenu.AddIndex, getField( %contextMenu.Item[0], 0 ), %this.GetAddGroupMenu() );
    
    // Enable/Disable Pasting.
    %contextMenu.enableItem( %contextMenu.PasteIndex, VerveEditor::CanPaste() );
    
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

function VController::GetAddGroupMenu( %this )
{
    %contextMenu = $VerveEditor::VController::ContextMenu[%this.getClassName()];
    if ( !isObject( %contextMenu ) )
    {
        %customTemplateMenu = new PopupMenu()
        {
            Class      = "VerveCustomTemplateMenu";
            SuperClass = "VerveWindowMenu";
            
            IsPopup    = true;
            
            Label      = "VGroupAddGroupMenu";
            Position   = 0;
        };
        %customTemplateMenu.Init();
        
        %contextMenu = new PopupMenu()
        {
            SuperClass = "VerveWindowMenu";
            
            IsPopup  = true;
            
            Label    = "VGroupAddGroupMenu";
            Position = 0;
            
            Item[0] = "Add Camera Group"          TAB "" TAB "VerveEditor::AddGroup(\"VCameraGroup\");";
            Item[1] = "Add Director Group"        TAB "" TAB "VerveEditor::AddGroup(\"VDirectorGroup\");";
            Item[2] = "Add Light Object Group"    TAB "" TAB "VerveEditor::AddGroup(\"VLightObjectGroup\");";
            Item[3] = "Add Particle Effect Group" TAB "" TAB "VerveEditor::AddGroup(\"VParticleEffectGroup\");";
            Item[4] = "Add Scene Object Group"    TAB "" TAB "VerveEditor::AddGroup(\"VSceneObjectGroup\");";
            Item[5] = "Add Spawn Sphere Group"    TAB "" TAB "VerveEditor::AddGroup(\"VSpawnSphereGroup\");";
            
            Item[6] = "" TAB "";
            
            Item[7] = "Add Custom Group"       TAB %customTemplateMenu;
            
            DirectorIndex = 1;
            CustomIndex   = 7;
            CustomMenu    = %customTemplateMenu;
        };
        %contextMenu.Init();
        
        // Refresh Menu.
        %customTemplateMenu = %contextMenu.CustomMenu;
        if ( %customTemplateMenu.getItemCount() == 0 )
        {
            // Remove Item.
            %contextMenu.removeItem( %contextMenu.CustomIndex );
            
            // Add Dummy.
            %contextMenu.insertItem( %contextMenu.CustomIndex, getField( %contextMenu.Item[%contextMenu.CustomIndex], 0 ) );
        
            // Disable Custom Menu.
            %contextMenu.enableItem( %contextMenu.CustomIndex, false );
        }
        
        // Cache.
        $VerveEditor::VController::ContextMenu[%this.getClassName()] = %contextMenu;
    }
    
    // Enable / Disable Director Group.
    %contextMenu.enableItem( %contextMenu.DirectorIndex, %this.CanAdd( "VDirectorGroup" ) );
    
    // Return Menu.
    return %contextMenu;
}