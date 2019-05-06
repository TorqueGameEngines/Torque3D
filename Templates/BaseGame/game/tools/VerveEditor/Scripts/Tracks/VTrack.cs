//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------
    
new ScriptObject( VTrackPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    Parent      = "VObjectPropertyList";
};

//-----------------------------------------------------------------------------

function VTrack::OnAdd( %this )
{
    %ourClass = %this.getClassName();
    if ( !isWordInList( %ourClass, $VerveEditor::NonUniqueTrackList ) )
    {
        %group      = %this.getParent();
        %trackCount = %group.getCount();
        for ( %i = 0; %i < %trackCount; %i++ )
        {
            %trackObject = %group.getObject( %i );
            if ( %trackObject.getId() == %this.getId() )
            {
                // Skip.
                continue;
            }
            
            if ( %trackObject.isMemberOfClass( %ourClass ) )
            {
                // Alert Message.
                messageBox( "Verve Editor", "You cannot have more than one \"" @ %ourClass @ "\" in a group.", "Ok", "Warning" );
                
                // Invalid.
                return false;
            }
        }
    }
    
    // Regular Add.
    return Parent::OnAdd( %this );
}

function VTrack::CanPaste( %this, %targetObject )
{
    if ( !isObject( %targetObject ) )
    {
        // Nope!
        return false;
    }
    
    return %targetObject.isMemberOfClass( "VEvent" );
}

function VTrack::Refresh( %this )
{
    // Create Control.
    %trackControl = VerveEditor::CreateTrackControl( %this );
    
    %eventCount = %this.getCount();
    for ( %i = 0; %i < %eventCount; %i++ )
    {
        %this.getObject( %i ).Refresh( %trackControl );
    }
    
    // Return Control.
    return %trackControl;
}

function VTrack::CreateEvent( %this )
{
    // Create Event.
    return new VEvent();
}

//-------------------------------------------------------------------------

function VerveEditor::CreateTrackControl( %object )
{
    %groupWidth  = getWord( VerveEditorGroupStack.getExtent(), 0 );
    %groupHeight = 26;
    %trackWidth  = getWord( VerveEditorTrackStack.getExtent(), 0 );
    %trackHeight = %groupHeight;
    
    %groupContainer = new VEditorButton()
    {
        SuperClass  = "VEditorSelectable";
        Class       = "VEditorSelectableTrack";
        Profile     = "VEditorTrackProfile";
        
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
        Extent       = "14" SPC %trackHeight;
        
        Object       = %object;
        FieldName    = "Enabled";
        Command      = "$ThisControl.ApplyValue();";
        
        Text         = "";
    };
    %groupContainer.add( %groupCheckbox );
    
    %trackContainer = new VEditorButton()
    {
        SuperClass  = "VEditorSelectable";
        Class       = "VEditorSelectableTrack";
        Profile     = "VEditorTrackProfile";
        
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

function VEditorSelectableTrack::Update( %this, %fieldName, %fieldValue )
{
    %this.setText( %fieldValue );
}

function VTrack::GetContextMenu( %this )
{
    %contextMenu = $VerveEditor::VTrack::ContextMenu;
    if ( !isObject( %contextMenu ) )
    {
        %contextMenu = new PopupMenu()
        {
            SuperClass = "VerveWindowMenu";
            
            IsPopup  = true;
            
            Label    = "VTrackContextMenu";
            Position = 0;
            
            Item[0] = "&Add Event" TAB "" TAB "VEditorSelectableTrack::AddEvent();";
            
            Item[1] = "" TAB "";
             
            Item[2] = "Cu&t"    TAB "" TAB "VerveEditor::CutSelection();";
            Item[3] = "&Copy"   TAB "" TAB "VerveEditor::CopySelection();";
            Item[4] = "&Paste"  TAB "" TAB "VEditorSelectableTrack::PasteEvent();";
            
            Item[5] = "" TAB "";
            
            Item[6] = "&Delete" TAB "" TAB "VerveEditor::DeleteSelection();";
            
            AddIndex   = 0;
            PasteIndex = 4;
        };
        %contextMenu.Init();
        
        // Cache.
        $VerveEditor::VTrack::ContextMenu = %contextMenu;
    }
    
    // Return Menu.
    return %contextMenu;
}

function VTrack::DisplayContextMenu( %this, %x, %y )
{
    // Fetch the Context Menu.
    %contextMenu = %this.GetContextMenu();
    
    // Fetch Track Control.
    %trackControl = %this.Control.SiblingControl;
    
    // Enable If Track Stack Member.
    %enableAdd = VerveEditorTrackStack.isMember( %trackControl );
    
    if ( %enableAdd )
    {
        // Time.
        %time = VerveEditorTimeLine.toTime( %x - getWord( %trackControl.getGlobalPosition(), 0 ) );
        if ( %time < 0 || %time > $VerveEditor::Controller.Duration )
        {
            // Disable.
            %enableAdd = false;
        }
        
        // Store Time.
        %this.MouseTime = %time;
    }
    
    // Enable/Disable Adding Events.
    %contextMenu.enableItem( %contextMenu.AddIndex , %enableAdd  );
    
    // Enable/Disable Pasting.
    %contextMenu.enableItem( %contextMenu.PasteIndex, %enableAdd & VerveEditor::CanPaste() );
    
    // Display.
    if($Verve::UseSeparateWindow)
      %contextMenu.showPopup( VerveEditorWindow, %x, %y );
    else
      %contextMenu.showPopup( Canvas, %x, %y );
}

function VEditorSelectableTrack::AddEvent()
{
    if ( !VerveEditor::HasSelection() )
    {
        // Invalid Selection.
        return;
    }
    
    %trackObject = $VerveEditor::InspectorObject;
    if ( !%trackObject.isMemberOfClass( "VTrack" ) )
    {
        // Invalid Selection.
        return;
    }
    
    // Create Event.
    VerveEditor::AddEvent( %trackObject, %trackObject.MouseTime );
    
    // Clear.
    %trackObject.MouseTime = "";
}

function VEditorSelectableTrack::PasteEvent()
{
    // Void.
}
