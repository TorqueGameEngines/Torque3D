function NewEditorGui::AddWindow(%this)
{
   %page = new GuiTabPageCtrl()
   {
      fitBook = "1";
      text = "Object Viewer";
      maxLength = "1024";
      margin = "0 0 0 0";
      padding = "0 0 0 0";
      anchorTop = "1";
      anchorBottom = "0";
      anchorLeft = "1";
      anchorRight = "0";
      position = "0 0";
      extent = "1024 768";
      minExtent = "8 2";
      horizSizing = "width";
      vertSizing = "height";
      profile = "GuiTabPageProfile";
      visible = "1";
      active = "1";
      tooltipProfile = "GuiToolTipProfile";
      hovertime = "1000";
      isContainer = "1";
      canSave = "1";
      canSaveDynamicFields = "1";
   };
   
   %page.add(ObjectViewer);
   
   MainEditorBasePanel.add(%page);
   
   //Ensure the sidebar is spaced sanely
   %pos = MainEditorBasePanel.extent.x * 0.8;
   ObjectViewer-->splitContainer.splitPoint.x = MainEditorBasePanel.extent.x * 0.8;
   
}

function AssetBrowserWindow::onMouseDragged(%this)
{
   %payload = new GuiBitmapButtonCtrl();
   %payload.assignFieldsFrom( %this );
   %payload.className = "AssetPreviewControl";
   %payload.position = "0 0";
   %payload.dragSourceControl = %this;
   %payload.bitmap = %this.icon;
   %payload.extent.x /= 2;
   %payload.extent.y /= 2;
   
   %xOffset = getWord( %payload.extent, 0 ) / 2;
   %yOffset = getWord( %payload.extent, 1 ) / 2;
   
   // Compute the initial position of the GuiDragAndDrop control on the cavas based on the current
   // mouse cursor position.
   
   %cursorpos = Canvas.getCursorPos();
   %xPos = getWord( %cursorpos, 0 ) - %xOffset;
   %yPos = getWord( %cursorpos, 1 ) - %yOffset;
   
   if(!isObject(EditorDragAndDropLayer))
   {
      new GuiControl(EditorDragAndDropLayer)
      {
         position = "0 0";
         extent = Canvas.extent;
      };
   }
   
   // Create the drag control.
   %ctrl = new GuiDragAndDropControl()
   {
      canSaveDynamicFields    = "0";
      Profile                 = "GuiSolidDefaultProfile";
      HorizSizing             = "right";
      VertSizing              = "bottom";
      Position                = %xPos SPC %yPos;
      extent                  = %payload.extent;
      MinExtent               = "4 4";
      canSave                 = "1";
      Visible                 = "1";
      hovertime               = "1000";

      // Let the GuiDragAndDropControl delete itself on mouse-up.  When the drag is aborted,
      // this not only deletes the drag control but also our payload.
      deleteOnMouseUp         = true;
      
      useWholeCanvas = true;

      // To differentiate drags, use the namespace hierarchy to classify them.
      // This will allow a color swatch drag to tell itself apart from a file drag, for example.
      class                   = "AssetPreviewControlType_AssetDrop";
   };
   
   // Add the temporary color swatch to the drag control as the payload.
   %ctrl.add( %payload );
   
   // Start drag by adding the drag control to the canvas and then calling startDragging().
   //Canvas.getContent().add( %ctrl );
   EditorDragAndDropLayer.add(%ctrl);
   Canvas.pushDialog(EditorDragAndDropLayer);
   
   %ctrl.startDragging( %xOffset, %yOffset );
}