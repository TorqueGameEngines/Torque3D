//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------
    
new ScriptObject( VGroupPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    Parent      = "VObjectPropertyList";
};

//-----------------------------------------------------------------------------

function VGroup::OnAdd( %this )
{
    %ourClass = %this.getClassName();
    if ( isWordInList( %ourClass, $VerveEditor::UniqueGroupList ) )
    {
        %controller = $VerveEditor::Controller;
        %groupCount = %controller.getCount();
        for ( %i = 0; %i < %groupCount; %i++ )
        {
            %groupObject = %controller.getObject( %i );
            if ( %groupObject.getId() == %this.getId() )
            {
                // Skip.
                continue;
            }
            
            if ( %groupObject.isMemberOfClass( %ourClass ) )
            {
                // Alert Message.
                messageBox( "Verve Editor", "You cannot have more than one \"" @ %ourClass @ "\" in your sequence.", "Ok", "Warning" );
                
                // Invalid.
                return false;
            }
        }
    }
    
    // Regular Add.
    return Parent::OnAdd( %this );
}

function VGroup::OnAttach( %this )
{
    // Add Event Notify.
    VerveEditor::AddEventNotify( %this, "VGroupObjectUpdate", "OnGroupObjectUpdate" );
}

function VGroup::OnDetach( %this )
{
    // Remove Event Notify.
    VerveEditor::RemoveEventNotify( %this, "VGroupObjectUpdate" );
}

function VGroup::CanPaste( %this, %targetObject )
{
    if ( !isObject( %targetObject ) )
    {
        // Nope!
        return false;
    }
    
    if ( !%this.CanAdd( %targetObject.getClassName() ) )
    {
        // Nope!
        return false;
    }
    
    return %targetObject.isMemberOfClass( "VTrack" );
}

function VGroup::CanAdd( %this, %targetClass )
{
    if ( isWordInList( %targetClass, $VerveEditor::NonUniqueTrackList ) )
    {
        // Non-Unique Class.
        return true;
    }
    
    // All Tracks are Unique.
    %trackCount = %this.getCount();
    for ( %i = 0; %i < %trackCount; %i++ )
    {
        %trackObject = %this.getObject( %i );
        if ( %trackObject.isMemberOfClass( %targetClass ) )
        {
            // Invalid.
            return false;
        }
    }
    
    // All Good.
    return true;
}

function VGroup::isValid( %this )
{
    // Yup.
    return true;
}

function VGroup::Refresh( %this )
{
    // Create Control.
    %groupControl = VerveEditor::CreateGroupControl( %this );
    
    // Update Validity.
    %this.OnGroupObjectUpdate();
    
    %trackCount = %this.getCount();
    for ( %i = 0; %i < %trackCount; %i++ )
    {
        %this.getObject( %i ).Refresh();
    }
    
    // Return Control.
    return %groupControl;
}

function VGroup::OnFieldChange( %this, %fieldName, %oldValue, %newValue )
{
    // Parent Callback.
    Parent::OnFieldChange( %this, %fieldName, %oldValue, %newValue );
    
    switch$ ( %fieldName )
    {
        case "Reference" :
        
            if ( $VerveEditor::InspectorObject.getId() == %this.getId() )
            {
                // Post Event.
                VerveEditor::PostEvent( "VGroupObjectUpdate", %this );
            }
    }
}

function VGroup::OnGroupObjectUpdate( %this, %refObject )
{
    if ( !isObject( %this.Control ) )
    {
        return;
    }
        
    // Update Validity.
    if ( %this.isValid() )
    {
        // Valid.
        %this.Control.setProfile( "VEditorGroupHeaderProfile" );
    }
    else
    {
        // Invalid.
        %this.Control.setProfile( "VEditorGroupHeaderErrorProfile" );
    }
}

//-----------------------------------------------------------------------------

function VGroup::PopulateBuildStack( %this, %stack )
{
    // Void.
}

function VGroup::ResolveBuildStack( %this, %stack )
{
    // Void.
}

//-----------------------------------------------------------------------------

function VGroup::DisplayContextMenu( %this, %x, %y )
{
    %contextMenu = $VerveEditor::VGroup::ContextMenu;
    if ( !isObject( %contextMenu ) )
    {
        %contextMenu = new PopupMenu()
        {
            SuperClass = "VerveWindowMenu";
            
            IsPopup  = true;
            
            Label    = "VGroupContextMenu";
            Position = 0;
            
            Item[0] = "Add Track" TAB "";
            
            Item[1] = "" TAB "";
             
            Item[2] = "Cu&t"     TAB "" TAB "VerveEditor::CutSelection();";
            Item[3] = "&Copy"    TAB "" TAB "VerveEditor::CopySelection();";
            Item[4] = "&Paste"   TAB "" TAB "VerveEditor::Paste();";
            
            Item[5] = "" TAB "";
            
            Item[6] = "&Delete"  TAB "" TAB "VerveEditor::DeleteSelection();";
            
            AddIndex   = 0;
            PasteIndex = 4;
        };
        %contextMenu.Init();
        
        // Cache.
        $VerveEditor::VGroup::ContextMenu = %contextMenu;
    }
    
    // Remove Add Menu.
    %contextMenu.removeItem( %contextMenu.AddIndex );
    
    // Available Tracks Menu.
    %groupMenu = 0;
    if ( %this.isMethod( "GetAddTrackMenu" ) )
    {
        %groupMenu = %this.GetAddTrackMenu();
    }
    
    if ( isObject( %groupMenu ) )
    {
        // Insert Menu.
        %contextMenu.insertSubMenu( %contextMenu.AddIndex, getField( %contextMenu.Item[0], 0 ), %groupMenu );
        
        // Enable.
        %contextMenu.enableItem( %contextMenu.AddIndex, true );
    }
    else
    {
        // Add Dummy.
        %contextMenu.insertItem( %contextMenu.AddIndex, getField( %contextMenu.Item[0], 0 ) );
        
        // Disable.
        %contextMenu.enableItem( %contextMenu.AddIndex, false );
    }
    
    // Enable/Disable Pasting.
    %contextMenu.enableItem( %contextMenu.PasteIndex, VerveEditor::CanPaste() );
    
    // Display.
    %contextMenu.showPopup( VerveEditorWindow, %x, %y );
}

function VGroup::GetAddTrackMenu( %this )
{
    %contextMenu = $VerveEditor::VGroup::ContextMenu[%this.getClassName()];
    if ( !isObject( %contextMenu ) )
    {
        %contextMenu = new PopupMenu()
        {
            SuperClass = "VerveWindowMenu";
            
            IsPopup  = true;
            
            Label    = "VGroupAddTrackMenu";
            Position = 0;
            
            Item[0] = "Add Track" TAB "" TAB "VerveEditor::AddTrack( \"VTrack\" );";
        };
        %contextMenu.Init();
        
        // Cache.
        $VerveEditor::VGroup::ContextMenu[%this.getClassName()] = %contextMenu;
    }
    
    // Enable/Disable Adding Tracks.
    %contextMenu.enableItem( 0, %this.CanAdd( "VTrack" ) );
    
    // Return Menu.
    return %contextMenu;
}

//-----------------------------------------------------------------------------

function VerveEditor::CreateGroupControl( %object )
{
    %groupWidth  = getWord( VerveEditorGroupStack.getExtent(), 0 );
    %groupHeight = 26;
    %trackWidth  = getWord( VerveEditorTrackStack.getExtent(), 0 );
    %trackHeight = %groupHeight;
    
    %groupContainer = new VEditorButton()
    {
        SuperClass  = "VEditorSelectable";
        Class       = "VEditorSelectableGroup";
        Profile     = "VEditorGroupHeaderProfile";
        
        Bitmap      = "~/VerveEditor/GUI/Images/GroupBackground";
        
        HorizSizing = "width";
        VertSizing  = "bottom";
        Position    = "0 0";
        Extent      = %groupWidth SPC %groupHeight;
        
        ButtonType  = "ToggleButton";
        GroupNum    = "-1";
        
        IsContainer = "1";
    };
    VerveEditorGroupStack.add( %groupContainer );
    
    %groupCheckbox = new GuiCheckBoxCtrl()
    {
        Class        = "VEditorBoolPropertyField";
        InternalName = "Enabled";
        Profile      = "VEditorCheckBoxProfile";
        
        HorizSizing  = "width";
        VertSizing   = "bottom";
        Position     = "4 0";
        Extent       = "14" SPC %groupHeight;
        
        Object       = %object;
        FieldName    = "Enabled";
        Command      = "$ThisControl.ApplyValue();";
        
        Text         = "";
    };
    %groupContainer.add( %groupCheckbox );
    
    %trackContainer = new VEditorButton()
    {
        SuperClass  = "VEditorSelectable";
        Class       = "VEditorSelectableGroup";
        Profile     = "VEditorGroupTrackProfile";
        
        Bitmap      = "~/VerveEditor/GUI/Images/GroupBackground";
        
        HorizSizing = "width";
        VertSizing  = "bottom";
        Position    = "0 0";
        Extent      = %trackWidth SPC %trackHeight;
        
        ButtonType  = "ToggleButton";
        GroupNum    = "-1";
        
        IsContainer = "1";
    };
    VerveEditorTrackStack.add( %trackContainer );
    
    // Field Notify.
    %object.AddFieldNotify( "Label",   %groupContainer );
    %object.AddFieldNotify( "Enabled", %groupCheckbox );
    
    // Reference Siblings.
    %trackContainer.SiblingControl = %groupContainer;
    %groupContainer.SiblingControl = %trackContainer;
    
    // Reference Proxy.
    %groupContainer.Proxy = %object;
    %trackContainer.Proxy = %object;
    
    // Reference Control.
    %object.Control = %groupContainer;
    
    return %trackContainer;
}

function VEditorSelectableGroup::Update( %this, %fieldName, %fieldValue )
{
    %this.setText( %fieldValue );
}