//-----------------------------------------------------------------------------
// Verve
// Copyright (C) - Violent Tulip
//-----------------------------------------------------------------------------
    
new ScriptObject( VMotionTrackPropertyList )
{
    SuperClass  = "VEditorPropertyList";
    Parent      = "VObjectPropertyList";
    
    Group[0]    = "VMotionTrack";
    Field[0, 0] = "Reference";
    Type[0, 0]  = "VControllerDataEnum";
    Field[0, 1] = "OrientationMode";
    Type[0, 1]  = "VPathOrientationModeEnum";
    Field[0, 2] = "OrientationData";
    Field[0, 3] = "Relative";
};

//-----------------------------------------------------------------------------

function VMotionTrack::CreateEvent( %this, %canCreateNode )
{
    if ( %canCreateNode $= "" ) %canCreateNode = true;
    
    // Fetch Object References.
    %object = %this.getParent().getSceneObject();
    %path   = %this.getPath();
    
    if ( isObject( %object ) && isObject( %path ) )
    {
        // Create Event.
        %event = new VMotionEvent();
        
        // Create a Node?
        %createNode = ( %this.getCount() >= %path.getNodeCount() );
        if ( !%canCreateNode || !%createNode )
        {
            // Return Event.
            return %event;
        }
        
        // Use Transform.
        %transform = %object.getTransform();
        
        // Object Attached?
        if ( %path.isObjectAttached( %object ) )
        {
            // Get Offset.
            %positionOffset = %path.getPathObjectOffset( %object );
            
            // Determine Real Position.
            %newPosition = VectorSub( %object.getPosition(), %positionOffset );
            
            // Set Transform.
            %transform = %newPosition SPC getWords( %transform, 3 );
        }
        else if ( %this.Relative && %path.getNodeCount() > 0 )
        {
            // Fetch Node Position.
            %nodePosition = %path.getNodeWorldPosition( 0 );
            
            // Set Position.
            %object.setTransform( %nodePosition SPC getWords( %transform, 3 ) );
        }
        
        // Create New Node.
        %event.schedule( 32, "CreatePathNode", %transform );
        
        // Return Event.
        return %event;
    }
    
    // No Object.
    return 0;
}

function VMotionTrack::OnSelect( %this )
{
    // Fetch Path.
    %path = %this.getPath();
    if ( !isObject( EVPathEditor ) || !isObject( %path ) )
    {
        // No Editor.
        return;
    }
    
    // Update Selection.
    EVPathEditor.setSelection( %path );
}

//-----------------------------------------------------------------------------

function VMotionTrack::GetContextMenu( %this )
{
    %contextMenu = $VerveEditor::VMotionTrack::ContextMenu;
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
            
            Item[2] = "&Import Path Nodes" TAB "" TAB "VMotionTrack::ImportPathNodes();";
            
            Item[3] = "" TAB "";
             
            Item[4] = "Cu&t"    TAB "" TAB "VerveEditor::CutSelection();";
            Item[5] = "&Copy"   TAB "" TAB "VerveEditor::CopySelection();";
            Item[6] = "&Paste"  TAB "" TAB "VEditorSelectableTrack::PasteEvent();";
            
            Item[7] = "" TAB "";
            
            Item[8] = "&Delete" TAB "" TAB "VerveEditor::DeleteSelection();";
            
            AddIndex   = 0;
            PasteIndex = 4;
        };
        %contextMenu.Init();
        
        // Cache.
        $VerveEditor::VMotionTrack::ContextMenu = %contextMenu;
    }
    
    // Return Menu.
    return %contextMenu;
}

function VMotionTrack::ImportPathNodes()
{
    if ( !VerveEditor::HasSelection() )
    {
        // Invalid Selection.
        return;
    }
    
    %trackObject = $VerveEditor::InspectorObject;
    if ( !%trackObject.isMemberOfClass( "VMotionTrack" ) )
    {
        // Invalid Selection.
        return;
    }
    
    // Load the Import Options Dialog.
    if($Verve::UseSeparateWindow)
      VerveEditorWindow.pushDialog( VerveEditorImportPathNodesGUI );
    else
      Canvas.pushDialog( VerveEditorImportPathNodesGUI );
}

function VMotionTrack::_ImportPathNodes( %speed )
{
    // Awake?
    if ( VerveEditorImportPathNodesGUI.isAwake() )
    {
        // Close the GUI.
        if($Verve::UseSeparateWindow)
            VerveEditorWindow.popDialog( VerveEditorImportPathNodesGUI );
          else
            Canvas.popDialog( VerveEditorImportPathNodesGUI );
    }
    
    if ( !VerveEditor::HasSelection() )
    {
        // Invalid Selection.
        return;
    }
    
    %trackObject = $VerveEditor::InspectorObject;
    if ( !%trackObject.isMemberOfClass( "VMotionTrack" ) )
    {
        // Invalid Selection.
        return;
    }
    
    // Fetch the Controller.
    %controller = %trackObject.getRoot();
    
    // Group History Actions.
    VerveEditor::ToggleHistoryGroup();
    
    // Clear the Track.
    while( %trackObject.getCount() > 0 )
    {
        // Fetch Object.
        %event = %trackObject.getObject( 0 );
        
        // Add History Item.
        %historyObject = new UndoScriptAction()
        {
            Class      = "VerveEditorHistoryDeleteObject";
            SuperClass = "VerveEditorHistoryObject";
            
            ActionName = "Delete Object";
            
            // Store Object References.
            Parent     = %trackObject;
            Object     = %event;
        };
        
        // Detach Object.
        %trackObject.removeObject( %event );
    }
    
    // Fetch the Path.
    %pathObject = %trackObject.getPath();
    
    // New Duration.
    %controllerDuration = 0;
    // Last Event Time.
    %lastEventTime = 0;
    // Fetch the Node Count.
    %nodeCount = %pathObject.getNodeCount();
    for ( %i = 0; %i < ( %nodeCount + %controller.Loop ); %i++ )
    {
        // Create a new Event.
        %newEvent = %trackObject.CreateEvent( false );
        
        if ( %i > 0 )
        {
            // Fetch the Node Length.
            %nodeLength = %pathObject.getNodeLength( %i - 1 );
            // Determine the Trigger Time.
            %triggerInterval = 1000 * ( %nodeLength / %speed );
            
            // Determine the Trigger Time.
            %lastEventTime = ( %lastEventTime + %triggerInterval );
            
            // Update Duration.
            %controllerDuration = %lastEventTime;
            // Set the Event's Trigger Time.
            %newEvent.TriggerTime = %lastEventTime;
        }
        
        if ( %i < %nodeCount )
        {
            // Add the Event.
            %trackObject.addObject( %newEvent );
        }
        
        // Do Event Callback.
        %newEvent.OnAdd();
    }
    
    // Set the Controller Duration.
    %controller.setFieldValue( "Duration", %controllerDuration );
    
    // Finish Up.
    VerveEditor::ToggleHistoryGroup();
    
    // Refresh the Editor.
    VerveEditor::Refresh();
    
    // Set Selection.
    VerveEditor::SetSelection( %trackObject.Control );
}