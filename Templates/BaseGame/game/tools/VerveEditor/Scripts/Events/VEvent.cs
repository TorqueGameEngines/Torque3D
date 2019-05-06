//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------

new ScriptObject( VEventPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    //Parent      = "VObjectPropertyList";
    
    Group[0]    = "VEvent";
    Field[0, 0] = "TriggerTime";
};

new ScriptObject( VEventDPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    //Parent      = "VObjectPropertyList";
    
    Group[0]    = "VEvent";
    Field[0, 0] = "TriggerTime";
    Field[0, 1] = "Duration";
};

//-----------------------------------------------------------------------------

function VEvent::CanCopy( %this, %targetObject )
{
    return false;
}

function VEvent::CanPaste( %this, %targetObject )
{
    return false;
}

function VEvent::Refresh( %this, %trackContainer )
{
    // Store Container Reference.
    %this.TrackContainer = %trackContainer;
    
    // Create Control.
    return VerveEditor::CreateEventControl( %this );
}

//-------------------------------------------------------------------------

function VerveEditor::CreateEventControl( %object )
{
    %eventButton = new VEditorButton()
    {
        SuperClass  = "VEditorSelectable";
        Class       = "VEditorSelectableEvent";
        Profile     = "VEditorEventProfile";
        
        HorizSizing = "right";
        VertSizing  = "center";
        Position    = "0 2";
        Extent      = "5 22";
        MinExtent   = "1 22";
        
        ButtonType  = "ToggleButton";
        GroupNum    = "-1";
        
        // No Text.
        Text        = "";
        
        // Draggable.
        IsDraggable = "1";
    };
    %object.TrackContainer.add( %eventButton );
    
    // Reference Proxy.
    %eventButton.Proxy = %object;
    
    // Reference Control.
    %object.Control = %eventButton;
    
    // Field Notify.
    %object.AddFieldNotify( "TriggerTime", %eventButton );
    %object.AddFieldNotify( "Duration",    %eventButton );
    
    return %eventButton;
}

function VEditorSelectableEvent::onMouseDown( %this, %point, %modifiers, %clickCount )
{
    // Fetch Global Position.
    %globalPosition = %this.getGlobalPosition();
    
    // Get Local Points.
    %x = getWord( %point, 0 ) - getWord( %globalPosition, 0 );
    %y = getWord( %point, 1 ) - getWord( %globalPosition, 1 );
    
    // Store Mouse Down Point.
    %this.MouseDown = %x SPC %y;
    
    // Reset.
    %this.Proxy.DragModify = false;
}

function VEditorSelectableEvent::onMouseDragged( %this, %point, %modifiers, %clickCount )
{
    if ( !%this.Proxy.DragModify )
    {
        // Store Original Time.
        %this.Proxy.DragTime = %this.Proxy.TriggerTime;
        
        // Set Selection.
        VerveEditor::SetSelection( %this );
    }
    
    // Fetch Track.
    %trackControl  = %this.Proxy.getParent().Control.SiblingControl;
    
    // Mouse Position.
    %mousePosition = getWord( %point, 0 ) - getWord( %trackControl.getGlobalPosition(), 0 ) - getWord( %this.MouseDown, 0 );
    
    // Fetch Time.
    %time = mClamp( VerveEditorTimeLine.toTime( %mousePosition ), 0, $VerveEditor::Controller.Duration );
    
    // Apply.
    %this.Proxy.SnapToTime( %time, true );
}

function VEditorSelectableEvent::onMouseUp( %this, %point, %modifiers, %clickCount )
{
    Parent::onMouseUp( %this, %point, %modifiers, %clickCount );
    
    if ( %this.Proxy.DragModify )
    {
        // Store New Time.
        %newTime = %this.Proxy.TriggerTime;
        
        // Reset Value.
        %this.Proxy.TriggerTime = %this.Proxy.DragTime;
        
        // Set Value.
        %this.Proxy.setFieldValue( "TriggerTime", %newTime );
        
        // Clear Modify.
        %this.Proxy.DragModify = false;
    }
}

function VEvent::getSnapTime( %this, %targetTime )
{
    if ( $Pref::VerveEditor::Event::SnapToSiblings && $Pref::VerveEditor::Event::SnapToSiblingThreshold > 0 )
    {
        // Iterate Over Sibling Events.
        %trackObject = %this.getParent();
        %eventCount  = %trackObject.getCount();
        for ( %i = 0; %i < %eventCount; %i++ )
        {
            %eventObject = %trackObject.getObject( %i );
            if ( %eventObject.getId() == %this.getId() )
            {
                continue;
            }
            
            // Snap Back -> Front.
            %snapTime = %eventObject.TriggerTime - %this.Duration;
            if ( mAbs( %targetTime - %snapTime ) < $Pref::VerveEditor::Event::SnapToSiblingThreshold / 2 )
            {
                // Snap.
                return %snapTime;
            }
            
/*
            // Overlaping?
            if ( ( %this.TriggerTime + %this.Duration ) > %eventObject.TriggerTime )
            {
                // Snap.
                return %snapTime;
            }
*/
            
            // Snap Front -> Back
            %snapTime = %eventObject.TriggerTime + %eventObject.Duration;
            if ( mAbs( %targetTime - %snapTime ) < $Pref::VerveEditor::Event::SnapToSiblingThreshold / 2 )
            {
                // Snap.
                return %snapTime;
            }
            
/*
            // Overlaping?
            if ( %this.TriggerTime < ( %eventObject.TriggerTime + %eventObject.Duration ) )
            {
                // Snap.
                return %snapTime;
            }
*/
        }
    }
        
    if ( $Pref::VerveEditor::Event::SnapToTime && $Pref::VerveEditor::Event::SnapToTimeThreshold > 0 )
    {
        // Snap.
        return mRound( %targetTime, $Pref::VerveEditor::Event::SnapToTimeThreshold );
    }
    
    // No Snap!
    return %targetTime;
}

function VEvent::SnapToTime( %this, %targetTime, %dragged )
{
    // Fetch Duration.
    %duration = %this.Duration;
    
    // Nasty Hack.
    if ( %this.isMemberOfClass( "VDirectorEvent" )
         || %this.isMemberOfClass( "VShapeAnimationEvent" ) )
    {
        // Clear Duration.
        %duration = 0;
    }
    
    // Snap.
    %targetTime = %this.getSnapTime( %targetTime );
    
    if ( %dragged )
    {
        if ( %targetTime != %this.TriggerTime )
        {
            // Flag Modified.
            %this.DragModify = true;
        }
        
        // Lock History.
        VerveEditorHistoryManager.Locked = true;
        
        // Set Time.
        %this.setFieldValue( "TriggerTime", %targetTime );
        
        // UnLock History.
        VerveEditorHistoryManager.Locked = false;
    }
    else
    {
        // Set Time.
        %this.setFieldValue( "TriggerTime", %targetTime );
    }
}

function VEditorSelectableEvent::Update( %this, %fieldName, %fieldValue )
{
    if ( %this.LabelField !$= "" && %this.LabelField $= %fieldName )
    {
        // Apply Text.
        %this.Text = %fieldValue;
        
        // Return.
        return;
    }
    
    %eventTime     = %this.Proxy.getFieldValue( "TriggerTime" );
    %eventDuration = %this.Proxy.getFieldValue( "Duration" );
    switch$ ( %fieldName )
    {
        case "TriggerTime" : %eventTime = %fieldValue;
                             
        case "Duration"    : %eventDuration = %fieldValue;
    }
    
    // Update Position
    %controlPositionX  = VerveEditorTimeLine.toPoint( %eventTime );
    %controlPositionX += ( %eventDuration == 0 ) ? ( -2 ) : 0;
    
    // Update Extent.
    %controlExtentX = ( %eventDuration == 0 ) ? 5 : ( VerveEditorTimeLine.toPoint( %eventTime + %eventDuration ) - %controlPositionX );
    
    %this.setPosition( %controlPositionX, getWord( %this.getPosition(), 1 ) );
    %this.setExtent( %controlExtentX, getWord( %this.getExtent(), 1 ) );
}

function VEvent::DisplayContextMenu( %this, %x, %y )
{
    %contextMenu = $VerveEditor::VEvent::ContextMenu;
    if ( !isObject( %contextMenu ) )
    {
        %contextMenu = new PopupMenu()
        {
            SuperClass = "VerveWindowMenu";
            
            IsPopup  = true;
            
            Label    = "VEventContextMenu";
            Position = 0;
            
            Item[0] = "Cu&t"    TAB "" TAB "VerveEditor::CutSelection();";
            Item[1] = "&Copy"   TAB "" TAB "VerveEditor::CopySelection( true );";
            
            Item[2] = "" TAB "";
            
            Item[3] = "&Delete" TAB "" TAB "VerveEditor::DeleteSelection();";
        };
        %contextMenu.Init();
        
        // Cache.
        $VerveEditor::VEvent::ContextMenu = %contextMenu;
    }
    
    // Enable/Disable Cut & Copy.
    %contextMenu.enableItem( 0, VerveEditor::CanCopy() );
    %contextMenu.enableItem( 1, VerveEditor::CanCopy() );
    
    // Display.
    if($Verve::UseSeparateWindow)
      %contextMenu.showPopup( VerveEditorWindow, %x, %y );
    else
      %contextMenu.showPopup( Canvas, %x, %y );
}
